// SPDX-License-Identifier: LGPL-2.1-or-later

#include <App/Datums.h>
#include <App/Document.h>
#include <App/DocumentObjectGroup.h>
#include <App/Origin.h>
#include <App/Part.h>
#include <Gui/Application.h>
#include <Gui/Command.h>
#include <Gui/Control.h>
#include <Gui/Document.h>
#include <Gui/QuantitySpinBox.h>
#include <Gui/TaskView/TaskDialog.h>
#include <Base/Interpreter.h>
#include <Gui/ActiveObjectList.h>
#include <Gui/MainWindow.h>
#include <Gui/MDIView.h>
#include <Gui/Selection/Selection.h>
#include <Gui/ViewProviderCoordinateSystem.h>
#include <Gui/ViewProviderGeometryObject.h>
#include <Mod/Design/App/Features.h>
#include <Mod/Sketcher/App/SketchObject.h>
#include <Mod/Part/App/Geometry.h>
#include <BRep_Tool.hxx>
#include <GeomConvert.hxx>
#include <Geom_BezierCurve.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <QPaintDevice>
#include <QPaintEngine>
#include <QPainter>
#include <QPainterPath>
#include <QRegularExpression>
#include <QSvgRenderer>
#include <QXmlStreamReader>

#include "ViewProviders.h"

#include <BRepAdaptor_Surface.hxx>
#include <BRepGProp.hxx>
#include <GProp_GProps.hxx>
#include <TopExp.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>

#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QFormLayout>
#include <QMessageBox>
#include <QTimer>

#include <functional>
#include <memory>

namespace
{

/// Aktive Komponente (Doppelklick im Browser), sonst die Root-Komponente
App::Part* activeContainer(App::Document* doc)
{
    if (auto gdoc = Gui::Application::Instance->getDocument(doc)) {
        if (auto view = gdoc->getActiveView()) {
            auto part = view->getActiveObject<App::Part*>(PARTKEY);
            if (part && Design::isComponent(part)) {
                return part;
            }
        }
    }
    return Design::root(doc, true);
}

Gui::ViewProviderCoordinateSystem* originView(App::Part* root)
{
    return freecad_cast<Gui::ViewProviderCoordinateSystem*>(
        Gui::Application::Instance->getViewProvider(root->getOrigin())
    );
}

/// Name ("FaceN") der Fläche in shape, die geometrisch face entspricht (Schwerpunkt + Flächeninhalt).
/// ponytail: geometrischer Abgleich statt topologischer Benennung; kann bei zwei deckungsgleichen Flächen irren
std::string faceName(const TopoDS_Shape& shape, const TopoDS_Shape& face)
{
    if (face.IsNull()) {
        return {};
    }
    auto props = [](const TopoDS_Shape& f) {
        GProp_GProps p;
        BRepGProp::SurfaceProperties(f, p);
        return p;
    };
    const GProp_GProps ref = props(face);
    TopTools_IndexedMapOfShape faces;
    TopExp::MapShapes(shape, TopAbs_FACE, faces);
    for (int i = 1; i <= faces.Extent(); ++i) {
        const GProp_GProps p = props(faces(i));
        if (std::abs(p.Mass() - ref.Mass()) < 1e-6 * (1 + ref.Mass())
            && p.CentreOfMass().Distance(ref.CentreOfMass()) < 1e-6) {
            return "Face" + std::to_string(i);
        }
    }
    return {};
}

/// Ursprungsebene oder Konstruktionsebene (Offset Plane)
bool isPlane(const App::DocumentObject* obj)
{
    static const Base::Type datum = Base::Type::fromName("Part::Datum");
    return obj && (obj->isDerivedFrom<App::Plane>() || (!datum.isBad() && obj->getTypeId().isDerivedFrom(datum)));
}

bool isPlanarFace(App::DocumentObject* obj, const std::string& element)
{
    auto feature = freecad_cast<Part::Feature*>(obj);
    if (!feature || element.rfind("Face", 0) != 0) {
        return false;
    }
    const Part::TopoShape face = feature->Shape.getShape().getSubTopoShape(element.c_str(), true);
    return !face.isNull() && BRepAdaptor_Surface(TopoDS::Face(face.getShape())).GetType() == GeomAbs_Plane;
}

/// Neue Skizze mit Profiles-Begleiter in der Komponente der Ebene bzw. des Körpers (ohne Transaktion)
Sketcher::SketchObject* addSketch(App::DocumentObject* support, const std::string& element)
{
    App::Document* doc = support->getDocument();
    App::Part* root = Design::componentOf(support);
    auto sketch = static_cast<Sketcher::SketchObject*>(doc->addObject("Sketcher::SketchObject", "Sketch"));
    Design::folder(root, "Sketches")->addObject(sketch);
    Design::addToTimeline(sketch);
    sketch->AttachmentSupport.setValue(support, std::vector<std::string> {element});
    sketch->MapMode.setValue("FlatFace");
    auto profiles = static_cast<Design::Profiles*>(doc->addObject("Design::Profiles", "Profiles"));
    root->addObject(profiles);
    profiles->Sketch.setValue(sketch);
    return sketch;
}

void createSketch(App::DocumentObject* support, std::string element)
{
    // Skizze auf einer Körperfläche an den Timeline-Zustand hängen (das Feature, das den Body gerade
    // erzeugt hat), nicht an den Body: sonst entsteht ein Kreis, sobald ein Feature aus dieser Skizze
    // denselben Body verändert. So bezieht sich die Skizze wie in Fusion auf den Körper zu diesem Zeitpunkt.
    if (auto body = freecad_cast<Design::Body*>(support)) {
        if (auto tip = freecad_cast<Design::Feature*>(Design::stateAtMarker(body))) {
            const TopoDS_Shape face = body->Shape.getShape().getSubShape(element.c_str(), true);
            const std::string name = faceName(tip->Shape.getShape().getShape(), face);
            if (!name.empty()) {
                support = tip;
                element = name;
            }
        }
    }

    App::Document* doc = support->getDocument();
    doc->openTransaction("Create Sketch");
    Sketcher::SketchObject* sketch = addSketch(support, element);
    doc->recompute();
    doc->commitTransaction();

    Gui::Document* gdoc = Gui::Application::Instance->getDocument(doc);
    gdoc->setEdit(gdoc->getViewProvider(sketch));
}

/// Wartet nach "Create Sketch" auf einen Klick auf eine Ursprungsebene oder eine ebene Körperfläche.
/// Solange sind die Ursprungsebenen eingeblendet, wie in Fusion.
class PlanePicker: public Gui::SelectionObserver
{
public:
    explicit PlanePicker(App::Part* root)
        : root(root)
    {
        if (auto view = originView(root)) {
            view->setTemporaryVisibility(Gui::DatumElement::Planes);
        }
        Gui::Selection().clearSelection();
        Gui::getMainWindow()->showMessage(QStringLiteral("Select a plane or a planar face for the sketch"));
    }

    ~PlanePicker() override
    {
        if (root.expired()) {
            return;
        }
        if (auto view = originView(root.get<App::Part>())) {
            view->resetTemporaryVisibility();
        }
    }

    static void start(App::Part* root)
    {
        active = std::make_unique<PlanePicker>(root);
    }
    static void stop()
    {
        active.reset();
    }

private:
    void onSelectionChanged(const Gui::SelectionChanges& msg) override
    {
        if (msg.Type != Gui::SelectionChanges::AddSelection) {
            return;
        }
        App::DocumentObject* leaf = msg.Object.getSubObject();
        const std::string element = msg.Object.getOldElementName();
        if (!leaf || !(isPlane(leaf) || isPlanarFace(leaf, element))) {
            return;
        }
        App::DocumentObjectT target(leaf);
        // Nicht mitten im Selektions-Callback Objekte anlegen und den Edit-Modus starten
        QTimer::singleShot(0, [target, element] {
            stop();
            Gui::Selection().clearSelection();
            if (auto obj = target.getObject()) {
                createSketch(obj, isPlane(obj) ? std::string() : element);
            }
        });
    }

    App::DocumentObjectWeakPtrT root;
    static inline std::unique_ptr<PlanePicker> active;
};

/// Kleiner Befehl mit Funktion statt eigener Klasse je Werkzeug
class DesignCommand: public Gui::Command
{
public:
    DesignCommand(const char* name, const char* text, const char* tip, const char* pixmap, const char* accel,
                  std::function<void(App::Document*)> run)
        : Command(name)
        , run(std::move(run))
    {
        sAppModule = "Design";
        sGroup = "Design";
        sMenuText = text;
        sToolTipText = tip;
        sWhatsThis = name;
        sStatusTip = tip;
        sPixmap = pixmap;
        sAccel = accel;
        eType = NoTransaction;  // Transaktion verwaltet der Werkzeug-Dialog selbst (Abbrechen = alles zurück)
    }
    const char* className() const override
    {
        return "DesignCommand";
    }

protected:
    void activated(int) override
    {
        run(getDocument());
    }
    bool isActive() override
    {
        return hasActiveDocument() && !Gui::Control().activeDialog();
    }

private:
    std::function<void(App::Document*)> run;
};

void createSketchCommand(App::Document* doc)
{
    App::Part* root = activeContainer(doc);
    // Bereits etwas Passendes ausgewählt? Dann sofort darauf skizzieren.
    auto selection = Gui::Selection().getSelectionEx();
    for (auto& sel : selection) {
        App::DocumentObject* obj = sel.getObject();
        const auto& subs = sel.getSubNames();
        if (isPlane(obj) && subs.empty()) {
            createSketch(obj, std::string());
            return;
        }
        if (obj && subs.size() == 1 && isPlanarFace(obj, subs.front())) {
            createSketch(obj, subs.front());
            return;
        }
    }
    PlanePicker::start(root);
}

void startEditing(App::DocumentObject* feature, bool createMode, Design::Body* target)
{
    Gui::Selection().clearSelection();
    Gui::Document* gdoc = Gui::Application::Instance->getDocument(feature->getDocument());
    auto vp = static_cast<DesignGui::ViewProviderFeature*>(gdoc->getViewProvider(feature));
    vp->createMode = createMode;
    vp->defaultTarget = target;
    gdoc->setEdit(vp);
}

/// Extrude, Revolve: Profile aus der Auswahl (Profilflächen oder ganze Skizze)
void startProfileFeature(App::Document* doc, const char* type, const char* name)
{
    Design::Profiles* profiles = nullptr;
    std::vector<std::string> faces;
    auto selection = Gui::Selection().getSelectionEx();
    for (auto& sel : selection) {
        App::DocumentObject* obj = sel.getObject();
        if (auto p = freecad_cast<Design::Profiles*>(obj)) {
            profiles = p;
            for (const auto& sub : sel.getSubNames()) {
                if (sub.rfind("Face", 0) == 0) {
                    faces.push_back(sub);
                }
            }
        }
        else if (obj && obj->isDerivedFrom<Sketcher::SketchObject>()) {
            profiles = Design::Profiles::forSketch(obj);
        }
    }
    // Nichts gewählt: hat die zuletzt erstellte Skizze genau ein Profil, nimm es (wie Fusion)
    if (!profiles) {
        auto all = doc->getObjectsOfType(Design::Profiles::getClassTypeId());
        if (!all.empty()) {
            auto last = static_cast<Design::Profiles*>(all.back());
            if (last->Shape.getShape().countSubShapes(TopAbs_FACE) == 1) {
                profiles = last;
            }
        }
    }
    if (!profiles) {
        QMessageBox::information(Gui::getMainWindow(), QString::fromLatin1(name),
                                 QStringLiteral("Select one or more profiles (closed areas of a sketch) first."));
        return;
    }

    doc->openTransaction(name);
    auto feature = static_cast<Design::Feature*>(doc->addObject(type, name));
    Design::componentOf(profiles->Sketch.getValue())->addObject(feature);
    Design::addToTimeline(feature);
    static_cast<App::PropertyLinkSub*>(feature->getPropertyByName("Profile"))->setValue(profiles, faces);

    // Skizze auf einer Körperfläche: standardmäßig mit diesem Körper vereinen
    Design::Body* target = nullptr;
    if (auto sketch = freecad_cast<Part::Part2DObject*>(profiles->Sketch.getValue())) {
        const auto& support = sketch->AttachmentSupport.getValues();
        const auto& subs = sketch->AttachmentSupport.getSubValues();
        auto base = support.empty() ? nullptr : freecad_cast<Design::Feature*>(support.front());
        if (base && !subs.empty()) {
            const TopoDS_Shape face = base->Shape.getShape().getSubShape(subs.front().c_str(), true);
            for (auto obj : base->Bodies.getValues()) {
                if (!faceName(base->shapeFor(obj).getShape(), face).empty()) {
                    target = freecad_cast<Design::Body*>(obj);
                }
            }
        }
    }
    startEditing(feature, true, target);
}

/// Fillet, Chamfer: Kanten oder Flächen eines Bodies aus der Auswahl
void startDressUp(App::Document* doc, const char* type, const char* name, bool bodyAlone = false)
{
    Design::Body* body = nullptr;
    std::vector<std::string> edges;
    auto selection = Gui::Selection().getSelectionEx();
    for (auto& sel : selection) {
        auto b = freecad_cast<Design::Body*>(sel.getObject());
        if (!b || (body && b != body)) {
            continue;
        }
        body = b;
        for (const auto& sub : sel.getSubNames()) {
            if (sub.rfind("Edge", 0) == 0 || sub.rfind("Face", 0) == 0) {
                edges.push_back(sub);
            }
        }
    }
    if (!body || (edges.empty() && !bodyAlone) || !Design::stateAtMarker(body)) {
        QMessageBox::information(Gui::getMainWindow(), QString::fromLatin1(name),
                                 QStringLiteral("Select edges (or faces) of a body first."));
        return;
    }

    doc->openTransaction(name);
    auto feature = static_cast<Design::DressUp*>(doc->addObject(type, name));
    Design::componentOf(body)->addObject(feature);
    Design::addToTimeline(feature);
    feature->Edges.setValues(edges);
    Design::attachToBodies(feature, {body});
    doc->recompute();
    startEditing(feature, false, nullptr);
}

/// Gewählte Bodies in Auswahlreihenfolge (ohne Doppelte)
std::vector<Design::Body*> selectedBodies()
{
    std::vector<Design::Body*> bodies;
    auto selection = Gui::Selection().getSelectionEx();
    for (auto& sel : selection) {
        auto b = freecad_cast<Design::Body*>(sel.getObject());
        if (b && Design::stateAtMarker(b) && std::ranges::find(bodies, b) == bodies.end()) {
            bodies.push_back(b);
        }
    }
    return bodies;
}

/// Alle in derselben Komponente? Verweise über Komponentengrenzen erlaubt FreeCAD nicht.
/// ponytail: Operationen über mehrere Komponenten (Fusion kann das) brauchen globale Links + Transformationen
bool sameComponent(const std::vector<Design::Body*>& bodies, const char* tool)
{
    for (auto b : bodies) {
        if (Design::componentOf(b) != Design::componentOf(bodies.front())) {
            QMessageBox::information(Gui::getMainWindow(), QString::fromLatin1(tool),
                                     QStringLiteral("All bodies must be in the same component."));
            return false;
        }
    }
    return true;
}

Design::Feature* addFeature(App::Document* doc, const char* type, const char* name, App::DocumentObject* near)
{
    doc->openTransaction(name);
    auto feature = static_cast<Design::Feature*>(doc->addObject(type, name));
    Design::componentOf(near)->addObject(feature);  // in die Komponente der Eingaben
    Design::addToTimeline(feature);
    return feature;
}

/// Feature verändert die Bodies (Basis = Zustand am Rollback-Marker)
void modifyBodies(Design::Feature* feature, const std::vector<Design::Body*>& bodies)
{
    Design::attachToBodies(feature, bodies);
}

void startCombine(App::Document* doc)
{
    const auto bodies = selectedBodies();
    if (bodies.size() < 2) {
        QMessageBox::information(Gui::getMainWindow(), QStringLiteral("Combine"),
                                 QStringLiteral("Select the target body first, then one or more tool bodies."));
        return;
    }
    if (!sameComponent(bodies, "Combine")) {
        return;
    }
    auto feature = static_cast<Design::Combine*>(addFeature(doc, "Design::Combine", "Combine", bodies.front()));
    std::vector<App::DocumentObject*> tools, states;
    for (size_t i = 1; i < bodies.size(); ++i) {
        tools.push_back(bodies[i]);
        states.push_back(Design::stateAtMarker(bodies[i]));
    }
    feature->ToolBodies.setValues(tools);
    feature->ToolFeatures.setValues(states);
    modifyBodies(feature, {bodies.front()});
    doc->recompute();
    startEditing(feature, false, nullptr);
}

/// Komponente verschieben/drehen: ändert direkt ihre Lage (wie das Verschieben von Komponenten in Fusion)
class TaskPlaceComponent: public Gui::TaskView::TaskDialog
{
public:
    explicit TaskPlaceComponent(App::Part* part)
        : part(part)
        , start(part->Placement.getValue())
    {
        auto w = new QWidget;
        w->setWindowTitle(QStringLiteral("Move Component"));
        auto form = new QFormLayout(w);
        auto box = [](const Base::Unit& unit) {
            auto b = new Gui::QuantitySpinBox;
            b->setUnit(unit);
            b->setRange(-1e7, 1e7);
            b->setValue(Base::Quantity(0, unit));
            return b;
        };
        x = box(Base::Unit::Length);
        y = box(Base::Unit::Length);
        z = box(Base::Unit::Length);
        angle = box(Base::Unit::Angle);
        form->addRow(QStringLiteral("X distance"), x);
        form->addRow(QStringLiteral("Y distance"), y);
        form->addRow(QStringLiteral("Z distance"), z);
        form->addRow(QStringLiteral("Rotate around Z"), angle);
        addTaskBox(w, false);
        for (auto b : {x, y, z, angle}) {
            QObject::connect(b, qOverload<double>(&Gui::QuantitySpinBox::valueChanged), [this] { apply(); });
        }
    }
    QDialogButtonBox::StandardButtons getStandardButtons() const override
    {
        return QDialogButtonBox::Ok | QDialogButtonBox::Cancel;
    }
    bool accept() override
    {
        part->getDocument()->commitTransaction();
        return true;
    }
    bool reject() override
    {
        App::Document* doc = part->getDocument();
        doc->abortTransaction();
        doc->recompute();
        return true;
    }

private:
    void apply()
    {
        const Base::Placement move(
            Base::Vector3d(x->value().getValue(), y->value().getValue(), z->value().getValue()),
            Base::Rotation(Base::Vector3d(0, 0, 1), angle->value().getValue() * M_PI / 180.0)
        );
        part->Placement.setValue(move * start);
        part->getDocument()->recompute();
    }
    App::Part* part;
    Base::Placement start;
    Gui::QuantitySpinBox *x, *y, *z, *angle;
};

void startNewComponent(App::Document* doc)
{
    App::Part* parent = activeContainer(doc);
    doc->openTransaction("New Component");
    App::Part* part = Design::newComponent(parent);
    doc->recompute();
    doc->commitTransaction();
    // Wie in Fusion: die neue Komponente ist gleich aktiv
    if (auto view = Gui::Application::Instance->getDocument(doc)->getActiveView()) {
        view->setActiveObject(part, PARTKEY);
    }
}

void startMove(App::Document* doc)
{
    // Komponente gewählt: ganze Komponente verschieben (Teile nebeneinander anordnen)
    for (auto obj : Gui::Selection().getObjectsOfType(App::Part::getClassTypeId())) {
        if (Design::isComponent(obj) && obj != Design::root(doc, false)) {
            Gui::Selection().clearSelection();
            doc->openTransaction("Move Component");
            Gui::Control().showDialog(new TaskPlaceComponent(static_cast<App::Part*>(obj)));
            return;
        }
    }
    const auto bodies = selectedBodies();
    if (!bodies.empty() && !sameComponent(bodies, "Move")) {
        return;
    }
    if (bodies.empty()) {
        QMessageBox::information(Gui::getMainWindow(), QStringLiteral("Move"),
                                 QStringLiteral("Select one or more bodies or a component first."));
        return;
    }
    auto feature = addFeature(doc, "Design::Move", "Move", bodies.front());
    modifyBodies(feature, bodies);
    doc->recompute();
    startEditing(feature, false, nullptr);
}

void startMirror(App::Document* doc)
{
    const auto bodies = selectedBodies();
    if (bodies.empty()) {
        QMessageBox::information(Gui::getMainWindow(), QStringLiteral("Mirror"),
                                 QStringLiteral("Select one or more bodies first."));
        return;
    }
    if (!sameComponent(bodies, "Mirror")) {
        return;
    }
    auto feature = static_cast<Design::Mirror*>(addFeature(doc, "Design::Mirror", "Mirror", bodies.front()));
    std::vector<App::DocumentObject*> sources, states, created;
    for (auto b : bodies) {
        sources.push_back(b);
        states.push_back(Design::stateAtMarker(b));
        auto copy = static_cast<Design::Body*>(doc->addObject("Design::Body", "Body"));
        copy->Label.setValue(std::string(b->Label.getValue()) + " Mirror");
        Design::folder(Design::componentOf(b), "Bodies")->addObject(copy);
        copy->Tip.setValue(feature);
        created.push_back(copy);
    }
    feature->SourceBodies.setValues(sources);
    feature->SourceFeatures.setValues(states);
    feature->Bodies.setValues(created);
    doc->recompute();
    startEditing(feature, false, nullptr);
}

/// Features und Skizzen aus der Timeline löschen (Kette wird neu verbunden), alles andere wie gewohnt
void deleteSelected(App::Document* doc)
{
    std::vector<App::DocumentObjectT> items;
    for (auto obj : Gui::Selection().getObjectsOfType(App::DocumentObject::getClassTypeId())) {
        if (obj->isDerivedFrom<Design::Feature>() || obj->isDerivedFrom<Sketcher::SketchObject>()) {
            items.emplace_back(obj);
        }
    }
    if (items.empty()) {
        Gui::Application::Instance->commandManager().runCommandByName("Std_Delete");
        return;
    }
    Gui::Selection().clearSelection();
    doc->openTransaction("Delete");
    for (const auto& item : items) {
        if (auto obj = item.getObject()) {
            Design::removeFromTimeline(obj);
        }
    }
    doc->recompute();
    doc->commitTransaction();
}

/// SVG-Pfade beim Rendern mitschneiden: Qt kennt alle SVG-Formen, Transformationen und Bögen
class PathRecorder: public QPaintEngine
{
public:
    PathRecorder()
        : QPaintEngine(QPaintEngine::AllFeatures)
    {}
    bool begin(QPaintDevice*) override
    {
        return true;
    }
    bool end() override
    {
        return true;
    }
    void updateState(const QPaintEngineState& state) override
    {
        if (state.state() & QPaintEngine::DirtyTransform) {
            transform = state.transform();
        }
    }
    void drawPath(const QPainterPath& path) override
    {
        paths.push_back(transform.map(path));
    }
    void drawPolygon(const QPointF* points, int count, PolygonDrawMode mode) override
    {
        QPainterPath path;
        path.addPolygon(QPolygonF(QList<QPointF>(points, points + count)));
        if (mode != PolylineMode) {
            path.closeSubpath();
        }
        drawPath(path);
    }
    void drawLines(const QLineF* lines, int count) override
    {
        for (int i = 0; i < count; ++i) {
            QPainterPath path(lines[i].p1());
            path.lineTo(lines[i].p2());
            drawPath(path);
        }
    }
    void drawPixmap(const QRectF&, const QPixmap&, const QRectF&) override
    {}
    Type type() const override
    {
        return User;
    }

    QTransform transform;
    std::vector<QPainterPath> paths;
};

class PathDevice: public QPaintDevice
{
public:
    explicit PathDevice(QSize size)
        : size(size)
    {}
    QPaintEngine* paintEngine() const override
    {
        return &engine;
    }
    mutable PathRecorder engine;

protected:
    int metric(PaintDeviceMetric metric) const override
    {
        switch (metric) {
            case PdmWidth:
                return size.width();
            case PdmHeight:
                return size.height();
            case PdmDpiX:
            case PdmDpiY:
            case PdmPhysicalDpiX:
            case PdmPhysicalDpiY:
                return 96;
            case PdmDepth:
                return 32;
            case PdmDevicePixelRatio:
                return 1;
            case PdmDevicePixelRatioScaled:
                return int(devicePixelRatioFScale());
            default:
                return 0;
        }
    }

private:
    QSize size;
};

using Geometries = std::vector<std::unique_ptr<Part::Geometry>>;

Geometries svgGeometry(const QString& file, std::string& error)
{
    QSvgRenderer renderer(file);
    if (!renderer.isValid()) {
        error = "This is not a valid SVG file.";
        return {};
    }
    PathDevice device(renderer.defaultSize());
    QPainter painter(&device);
    renderer.render(&painter);
    painter.end();

    // Qt rechnet absolute Einheiten (mm, in, pt) mit 90 dpi in Pixel um; Pixel ohne Einheit sind CSS-Pixel (96 dpi)
    double scale = 25.4 / 96;
    QFile in(file);
    if (in.open(QIODevice::ReadOnly)) {
        QXmlStreamReader xml(&in);
        while (xml.readNextStartElement()) {
            static const QRegularExpression absolute(QStringLiteral("\\d\\s*(mm|cm|in|pt|pc)\\s*$"));
            if (absolute.match(xml.attributes().value(QStringLiteral("width"))).hasMatch()) {
                scale = 25.4 / 90;
            }
            break;  // nur das <svg>-Element
        }
    }
    auto point = [scale](const QPointF& p) {
        return Base::Vector3d(p.x() * scale, -p.y() * scale, 0);  // SVG zeigt mit y nach unten
    };

    Geometries result;
    for (const QPainterPath& path : device.engine.paths) {
        Base::Vector3d current;
        for (int i = 0; i < path.elementCount(); ++i) {
            const QPainterPath::Element e = path.elementAt(i);
            const Base::Vector3d p = point(e);
            if (e.isMoveTo()) {
                current = p;
            }
            else if (e.isLineTo()) {
                if (Base::DistanceP2(current, p) > 1e-12) {
                    auto line = std::make_unique<Part::GeomLineSegment>();
                    line->setPoints(current, p);
                    result.push_back(std::move(line));
                }
                current = p;
            }
            else if (e.isCurveTo() && i + 2 < path.elementCount()) {
                TColgp_Array1OfPnt poles(1, 4);
                const Base::Vector3d c2 = point(path.elementAt(i + 1)), end = point(path.elementAt(i + 2));
                int k = 1;
                for (const auto& v : {current, p, c2, end}) {
                    poles.SetValue(k++, gp_Pnt(v.x, v.y, v.z));
                }
                Handle(Geom_BezierCurve) bezier = new Geom_BezierCurve(poles);
                result.push_back(std::make_unique<Part::GeomBSplineCurve>(GeomConvert::CurveToBSplineCurve(bezier)));
                current = end;
                i += 2;
            }
        }
    }
    if (result.empty()) {
        error = "The SVG file contains no paths.";
    }
    return result;
}

/// Skizzentaugliche Geometrie einer Kante (Linie, Kreis, Bogen, Ellipse, B-Spline; alles andere als B-Spline)
std::unique_ptr<Part::Geometry> sketchGeometry(const TopoDS_Edge& edge)
{
    auto geo = Part::Geometry::fromShape(edge, true);
    static const Base::Type supported[] = {Part::GeomLineSegment::getClassTypeId(), Part::GeomCircle::getClassTypeId(),
                                           Part::GeomArcOfCircle::getClassTypeId(), Part::GeomEllipse::getClassTypeId(),
                                           Part::GeomArcOfEllipse::getClassTypeId(),
                                           Part::GeomBSplineCurve::getClassTypeId()};
    if (geo && std::ranges::find(supported, geo->getTypeId()) != std::end(supported)) {
        return geo;
    }
    double first {}, last {};
    Handle(Geom_Curve) curve = BRep_Tool::Curve(edge, first, last);
    if (curve.IsNull()) {
        return nullptr;
    }
    return std::make_unique<Part::GeomBSplineCurve>(
        GeomConvert::CurveToBSplineCurve(new Geom_TrimmedCurve(curve, first, last))
    );
}

Geometries dxfGeometry(const std::string& file, std::string& error)
{
    // FreeCADs DXF-Leser legt Part-Objekte an: in ein unsichtbares Hilfsdokument lesen und die Kanten übernehmen
    App::Document* tmp = App::GetApplication().newDocument("MyCADImport", "MyCADImport", {false, true});
    const std::string name = tmp->getName();
    // eigene Optionen: Layer und Farben bräuchten das Draft-Modul (fehlt; die erste Linie ginge verloren)
    const char* options = "User parameter:BaseApp/Preferences/Mod/Design/DXF";
    auto grp = App::GetApplication().GetParameterGroupByPath(options);
    grp->SetBool("dxfUseDraftVisGroups", false);
    grp->SetBool("dxfGetOriginalColors", false);
    grp->SetBool("dxfImportPoints", false);
    try {
        const QString hex = QString::fromLatin1(QByteArray::fromStdString(file).toHex());
        Base::Interpreter().runString(("import Import\nImport.readDXF(bytes.fromhex('" + hex.toStdString()
                                       + "').decode(), '" + name + "', True, '" + options + "')")
                                          .c_str());
    }
    catch (const Base::Exception& e) {
        error = e.what();
    }
    Geometries result;
    for (auto obj : tmp->getObjectsOfType(Part::Feature::getClassTypeId())) {
        if (!obj->getInList().empty()) {
            continue;  // Teil eines Compounds: kommt über das Compound
        }
        for (const auto& edge : static_cast<Part::Feature*>(obj)->Shape.getShape().getSubTopoShapes(TopAbs_EDGE)) {
            if (auto geo = sketchGeometry(TopoDS::Edge(edge.getShape()))) {
                result.push_back(std::move(geo));
            }
        }
    }
    App::GetApplication().closeDocument(name.c_str());
    if (result.empty() && error.empty()) {
        error = "The DXF file contains no supported geometry.";
    }
    return result;
}

/// STEP: Timeline-Eintrag "Import" mit je einem Body pro Solid; DXF/SVG: Skizze auf der XY-Ebene
void importFile(App::Document* doc)
{
    const QString file = QFileDialog::getOpenFileName(
        Gui::getMainWindow(), QStringLiteral("Insert"), QString(),
        QStringLiteral("CAD files (*.step *.stp *.dxf *.svg);;STEP (*.step *.stp);;DXF (*.dxf);;SVG (*.svg)")
    );
    if (file.isEmpty()) {
        return;
    }
    const QString stem = QFileInfo(file).completeBaseName();
    const QString suffix = QFileInfo(file).suffix().toLower();
    App::Part* comp = activeContainer(doc);
    std::string error;
    try {
        if (suffix == QLatin1String("step") || suffix == QLatin1String("stp")) {
            Part::TopoShape shape;
            shape.read(file.toUtf8().constData());
            const auto pieces = Design::Import::pieces(shape);
            if (pieces.empty()) {
                throw Base::RuntimeError("The STEP file contains no geometry.");
            }
            doc->openTransaction("Insert");
            auto feature = static_cast<Design::Import*>(doc->addObject("Design::Import", "Import"));
            feature->Label.setValue(stem.toStdString());
            feature->SourceFile.setValue(file.toStdString());
            feature->Imported.setValue(shape);
            comp->addObject(feature);
            Design::addToTimeline(feature);
            std::vector<App::DocumentObject*> bodies;
            for (size_t i = 0; i < pieces.size(); ++i) {
                auto body = static_cast<Design::Body*>(doc->addObject("Design::Body", "Body"));
                body->Label.setValue(
                    pieces.size() == 1 ? stem.toStdString() : stem.toStdString() + " " + std::to_string(i + 1)
                );
                Design::folder(comp, "Bodies")->addObject(body);
                body->Tip.setValue(feature);
                bodies.push_back(body);
            }
            feature->Bodies.setValues(bodies);
        }
        else {
            Geometries geos = suffix == QLatin1String("svg") ? svgGeometry(file, error)
                                                             : dxfGeometry(file.toStdString(), error);
            if (geos.empty()) {
                throw Base::RuntimeError(error);
            }
            doc->openTransaction("Insert");
            Sketcher::SketchObject* sketch = addSketch(comp->getOrigin()->getXY(), std::string());
            sketch->Label.setValue(stem.toStdString());
            std::vector<Part::Geometry*> raw;
            for (const auto& g : geos) {
                raw.push_back(g.get());
            }
            sketch->addGeometry(raw);
        }
        doc->recompute();
        doc->commitTransaction();
        Gui::Application::Instance->commandManager().runCommandByName("Std_ViewFitAll");
    }
    catch (const Base::Exception& e) {
        doc->abortTransaction();
        QMessageBox::warning(Gui::getMainWindow(), QStringLiteral("Insert"), QString::fromUtf8(e.what()));
    }
    catch (const Standard_Failure& e) {
        doc->abortTransaction();
        QMessageBox::warning(Gui::getMainWindow(), QStringLiteral("Insert"), QString::fromUtf8(e.GetMessageString()));
    }
}

/// Gewählte Bodies exportieren, ohne Auswahl alle sichtbaren. 3MF/STL über Mesh, STEP über Import.
void exportBodies(App::Document* doc)
{
    std::vector<App::DocumentObject*> bodies;
    for (auto b : selectedBodies()) {
        bodies.push_back(b);
    }
    if (bodies.empty()) {
        for (auto obj : doc->getObjectsOfType(Design::Body::getClassTypeId())) {
            if (obj->Visibility.getValue() && !static_cast<Design::Body*>(obj)->Shape.getShape().isNull()) {
                bodies.push_back(obj);
            }
        }
    }
    if (bodies.empty()) {
        QMessageBox::information(Gui::getMainWindow(), QStringLiteral("Export"), QStringLiteral("There is no body to export."));
        return;
    }

    // Die eingetippte Endung bestimmt das Format; nur ohne Endung kommt die des gewählten Filters dazu
    const QString start = QDir::home().filePath(QString::fromUtf8(doc->Label.getValue()));
    QString filter;
    QString file = QFileDialog::getSaveFileName(
        Gui::getMainWindow(), QStringLiteral("Export"), start,
        QStringLiteral("3MF for 3D printing (*.3mf);;STL (*.stl);;STEP (*.step *.stp)"), &filter
    );
    if (file.isEmpty()) {
        return;
    }
    static const QStringList known = {QStringLiteral("3mf"), QStringLiteral("stl"), QStringLiteral("step"), QStringLiteral("stp")};
    if (!known.contains(QFileInfo(file).suffix().toLower())) {
        file += filter.startsWith(QLatin1String("STL")) ? QStringLiteral(".stl")
            : filter.startsWith(QLatin1String("STEP")) ? QStringLiteral(".step")
                                                        : QStringLiteral(".3mf");
    }

    // Pfad als Python-String: nur Backslash und Apostroph escapen
    QString path = file;
    path.replace(QLatin1Char('\\'), QStringLiteral("\\\\")).replace(QLatin1Char('\''), QStringLiteral("\\'"));
    std::string objs = "[";
    for (auto b : bodies) {
        objs += "App.getDocument('" + std::string(doc->getName()) + "').getObject('" + b->getNameInDocument() + "'),";
    }
    objs += "]";
    const QString suffix = QFileInfo(file).suffix().toLower();
    const std::string module = (suffix == QLatin1String("step") || suffix == QLatin1String("stp")) ? "Import" : "Mesh";
    try {
        Base::Interpreter().runString(
            ("import FreeCAD as App, " + module + "\n" + module + ".export(" + objs + ", '" + path.toStdString() + "')").c_str()
        );
        Gui::getMainWindow()->showMessage(QStringLiteral("Exported %1 bodies to %2").arg(bodies.size()).arg(file));
    }
    catch (const Base::Exception& e) {
        QMessageBox::warning(Gui::getMainWindow(), QStringLiteral("Export"), QString::fromUtf8(e.what()));
    }
}

/// Body, auf dessen Fläche eine Skizze liegt (über den Timeline-Zustand), sonst nullptr
Design::Body* bodyUnderSketch(App::DocumentObject* obj)
{
    auto sketch = freecad_cast<Part::Part2DObject*>(obj);
    if (!sketch) {
        return nullptr;
    }
    const auto& support = sketch->AttachmentSupport.getValues();
    const auto& subs = sketch->AttachmentSupport.getSubValues();
    auto base = support.empty() ? nullptr : freecad_cast<Design::Feature*>(support.front());
    if (!base || subs.empty()) {
        return nullptr;
    }
    const TopoDS_Shape face = base->Shape.getShape().getSubShape(subs.front().c_str(), true);
    for (auto b : base->Bodies.getValues()) {
        if (!faceName(base->shapeFor(b).getShape(), face).empty()) {
            return freecad_cast<Design::Body*>(b);
        }
    }
    return nullptr;
}

void startHole(App::Document* doc)
{
    App::DocumentObject* sketch = nullptr;
    for (auto obj : Gui::Selection().getObjectsOfType(Sketcher::SketchObject::getClassTypeId())) {
        sketch = obj;
    }
    if (!sketch) {  // sonst die zuletzt erstellte Skizze
        auto sketches = doc->getObjectsOfType(Sketcher::SketchObject::getClassTypeId());
        sketch = sketches.empty() ? nullptr : sketches.back();
    }
    Design::Body* target = bodyUnderSketch(sketch);
    if (!target) {
        QMessageBox::information(Gui::getMainWindow(), QStringLiteral("Hole"),
                                 QStringLiteral("Create a sketch on a face of a body and place points where the holes go."));
        return;
    }
    auto feature = static_cast<Design::Hole*>(addFeature(doc, "Design::Hole", "Hole", target));
    feature->Sketch.setValue(sketch);
    modifyBodies(feature, {target});
    doc->recompute();
    startEditing(feature, false, nullptr);
}

void startPattern(App::Document* doc)
{
    Design::Feature* source = nullptr;
    for (auto obj : Gui::Selection().getObjectsOfType(Design::Feature::getClassTypeId())) {
        Part::TopoShape tool;
        std::string error;
        if (static_cast<Design::Feature*>(obj)->makeTool(tool, error)) {
            source = static_cast<Design::Feature*>(obj);
        }
    }
    if (!source) {
        QMessageBox::information(Gui::getMainWindow(), QStringLiteral("Pattern"),
                                 QStringLiteral("Select an Extrude, Revolve or Hole in the timeline first."));
        return;
    }
    std::vector<Design::Body*> bodies;
    for (auto b : source->Bodies.getValues()) {
        if (auto body = freecad_cast<Design::Body*>(b)) {
            bodies.push_back(body);
        }
    }
    auto feature = static_cast<Design::Pattern*>(addFeature(doc, "Design::Pattern", "Pattern", source));
    feature->Source.setValue(source);
    feature->Operation.setValue(source->op() == Design::Feature::Op::NewBody ? 1L : source->Operation.getValue());
    modifyBodies(feature, bodies);
    doc->recompute();
    startEditing(feature, false, nullptr);
}

/// Konstruktionsebene im Abstand zu einer Ebene oder ebenen Fläche
class TaskOffsetPlane: public Gui::TaskView::TaskDialog
{
public:
    explicit TaskOffsetPlane(App::DocumentObject* plane)
        : plane(plane)
    {
        auto w = new QWidget;
        w->setWindowTitle(QStringLiteral("Offset Plane"));
        auto form = new QFormLayout(w);
        auto distance = new Gui::QuantitySpinBox;
        distance->setUnit(Base::Unit::Length);
        distance->setRange(-1e7, 1e7);
        distance->setValue(Base::Quantity(10.0, Base::Unit::Length));
        form->addRow(QStringLiteral("Distance"), distance);
        addTaskBox(w, false);
        QObject::connect(distance, qOverload<double>(&Gui::QuantitySpinBox::valueChanged), [this](double d) {
            setOffset(d);
        });
        setOffset(10.0);
    }
    QDialogButtonBox::StandardButtons getStandardButtons() const override
    {
        return QDialogButtonBox::Ok | QDialogButtonBox::Cancel;
    }
    bool accept() override
    {
        plane->getDocument()->commitTransaction();
        return true;
    }
    bool reject() override
    {
        App::Document* doc = plane->getDocument();
        doc->abortTransaction();
        doc->recompute();
        return true;
    }

private:
    void setOffset(double d)
    {
        auto offset = static_cast<App::PropertyPlacement*>(plane->getPropertyByName("AttachmentOffset"));
        offset->setValue(Base::Placement(Base::Vector3d(0, 0, d), Base::Rotation()));
        plane->getDocument()->recompute();
    }
    App::DocumentObject* plane;
};

void startOffsetPlane(App::Document* doc)
{
    App::DocumentObject* support = nullptr;
    std::string element;
    auto selection = Gui::Selection().getSelectionEx();
    for (auto& sel : selection) {
        App::DocumentObject* obj = sel.getObject();
        const auto& subs = sel.getSubNames();
        if (isPlane(obj) && subs.empty()) {
            support = obj;
        }
        else if (obj && subs.size() == 1 && isPlanarFace(obj, subs.front())) {
            support = obj;
            element = subs.front();
        }
    }
    if (!support) {
        QMessageBox::information(Gui::getMainWindow(), QStringLiteral("Offset Plane"),
                                 QStringLiteral("Select a plane or a planar face first."));
        return;
    }
    doc->openTransaction("Offset Plane");
    App::DocumentObject* plane = doc->addObject("PartDesign::Plane", "Plane");
    if (!plane) {
        doc->abortTransaction();
        return;
    }
    Design::folder(Design::componentOf(support), "Construction")->addObject(plane);
    static_cast<App::PropertyLinkSubList*>(plane->getPropertyByName("AttachmentSupport"))
        ->setValue(support, std::vector<std::string> {element});
    static_cast<App::PropertyEnumeration*>(plane->getPropertyByName("MapMode"))->setValue("FlatFace");

    // Dezent statt FreeCAD-Gelb, Größe passend zu den vorhandenen Körpern
    Base::BoundBox3d bb;
    for (auto b : doc->getObjectsOfType(Design::Body::getClassTypeId())) {
        bb.Add(static_cast<Design::Body*>(b)->Shape.getShape().getBoundBox());
    }
    const double size = bb.IsValid() ? std::max(bb.LengthX(), bb.LengthY()) * 1.2 : 60.0;
    static_cast<App::PropertyEnumeration*>(plane->getPropertyByName("ResizeMode"))->setValue("Manual");
    static_cast<App::PropertyLength*>(plane->getPropertyByName("Length"))->setValue(size);
    static_cast<App::PropertyLength*>(plane->getPropertyByName("Width"))->setValue(size);
    if (auto vp = freecad_cast<Gui::ViewProviderGeometryObject*>(Gui::Application::Instance->getViewProvider(plane))) {
        vp->ShapeAppearance.setDiffuseColor(0.45F, 0.62F, 1.0F);
        vp->Transparency.setValue(80);
    }
    Gui::Selection().clearSelection();
    Gui::Control().showDialog(new TaskOffsetPlane(plane));
}

}  // namespace

void CreateDesignCommands()
{
    auto& mgr = Gui::Application::Instance->commandManager();
    mgr.addCommand(new DesignCommand("Design_CreateSketch", "Create Sketch",
                                     "Create Sketch: click a plane or planar face to sketch on",
                                     "Sketcher_NewSketch", "S", createSketchCommand));
    mgr.addCommand(new DesignCommand("Design_Extrude", "Extrude", "Extrude: select one or more sketch profiles",
                                     "PartDesign_Pad", "E", [](App::Document* doc) {
                                         startProfileFeature(doc, "Design::Extrude", "Extrude");
                                     }));
    mgr.addCommand(new DesignCommand("Design_Revolve", "Revolve", "Revolve: select one or more sketch profiles",
                                     "PartDesign_Revolution", "", [](App::Document* doc) {
                                         startProfileFeature(doc, "Design::Revolve", "Revolve");
                                     }));
    mgr.addCommand(new DesignCommand("Design_Fillet", "Fillet", "Fillet: select edges or faces of a body",
                                     "PartDesign_Fillet", "F", [](App::Document* doc) {
                                         startDressUp(doc, "Design::Fillet", "Fillet");
                                     }));
    mgr.addCommand(new DesignCommand("Design_Shell", "Shell", "Shell: select faces to remove (or the body)",
                                     "PartDesign_Thickness", "", [](App::Document* doc) {
                                         startDressUp(doc, "Design::Shell", "Shell", true);
                                     }));
    mgr.addCommand(new DesignCommand("Design_Combine", "Combine",
                                     "Combine: select the target body, then the tool bodies",
                                     "Part_Fuse", "", startCombine));
    mgr.addCommand(new DesignCommand("Design_Move", "Move", "Move: select bodies to move or rotate",
                                     "Std_TransformManip", "M", startMove));
    mgr.addCommand(new DesignCommand("Design_Mirror", "Mirror", "Mirror: select bodies to mirror",
                                     "PartDesign_Mirrored", "", startMirror));
    mgr.addCommand(new DesignCommand("Design_Delete", "Delete", "Delete: remove features or sketches from the timeline",
                                     "edit-delete", "", deleteSelected));
    mgr.addCommand(new DesignCommand("Design_Export", "Export", "Export bodies as 3MF, STL or STEP",
                                     "document-save-as", "", exportBodies));
    mgr.addCommand(new DesignCommand("Design_Import", "Insert",
                                     "Insert a STEP file as bodies, or a DXF or SVG file as a sketch",
                                     "document-open", "", importFile));
    mgr.addCommand(new DesignCommand("Design_Hole", "Hole", "Hole: place points in a sketch on a face",
                                     "PartDesign_Hole", "H", startHole));
    mgr.addCommand(new DesignCommand("Design_Pattern", "Pattern",
                                     "Pattern: select an Extrude, Revolve or Hole in the timeline",
                                     "PartDesign_LinearPattern", "", startPattern));
    mgr.addCommand(new DesignCommand("Design_OffsetPlane", "Offset Plane",
                                     "Offset Plane: select a plane or planar face", "PartDesign_Plane", "",
                                     startOffsetPlane));
    mgr.addCommand(new DesignCommand("Design_PressPull", "Press Pull", "Press Pull: select planar faces of a body",
                                     "Part_Extrude", "Q", [](App::Document* doc) {
                                         startDressUp(doc, "Design::PressPull", "PressPull");
                                     }));
    mgr.addCommand(new DesignCommand("Design_NewComponent", "New Component",
                                     "New Component: an empty part with its own origin (double-click to activate)",
                                     "Std_Part", "", startNewComponent));
    mgr.addCommand(new DesignCommand("Design_Chamfer", "Chamfer", "Chamfer: select edges or faces of a body",
                                     "PartDesign_Chamfer", "", [](App::Document* doc) {
                                         startDressUp(doc, "Design::Chamfer", "Chamfer");
                                     }));
}
