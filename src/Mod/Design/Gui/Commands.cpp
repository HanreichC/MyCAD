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
#include <Mod/Part/App/AttachExtension.h>
#include <Mod/Part/App/Attacher.h>
#include <Gui/View3DInventor.h>
#include <Gui/View3DInventorViewer.h>
#include <BRepAdaptor_Curve.hxx>
#include <BRepBndLib.hxx>
#include <BRepExtrema_DistShapeShape.hxx>
#include <Bnd_Box.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Vertex.hxx>
#include <gp_Pln.hxx>
#include <QLabel>
#include <QVBoxLayout>
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

/// Name ("FaceN", "EdgeN", "VertexN") des Elements in shape, das geometrisch element entspricht (Schwerpunkt + Größe).
/// ponytail: geometrischer Abgleich statt topologischer Benennung; kann bei zwei deckungsgleichen Elementen irren
std::string elementName(const TopoDS_Shape& shape, const TopoDS_Shape& element)
{
    if (element.IsNull()) {
        return {};
    }
    const TopAbs_ShapeEnum type = element.ShapeType();
    auto props = [type](const TopoDS_Shape& s) {
        GProp_GProps p(type == TopAbs_VERTEX ? BRep_Tool::Pnt(TopoDS::Vertex(s)) : gp::Origin());
        if (type == TopAbs_FACE) {
            BRepGProp::SurfaceProperties(s, p);
        }
        else if (type == TopAbs_EDGE) {
            BRepGProp::LinearProperties(s, p);
        }
        return p;
    };
    const char* prefix = type == TopAbs_FACE ? "Face" : type == TopAbs_EDGE ? "Edge" : "Vertex";
    const GProp_GProps ref = props(element);
    TopTools_IndexedMapOfShape all;
    TopExp::MapShapes(shape, type, all);
    for (int i = 1; i <= all.Extent(); ++i) {
        const GProp_GProps p = props(all(i));
        if (std::abs(p.Mass() - ref.Mass()) < 1e-6 * (1 + ref.Mass())
            && p.CentreOfMass().Distance(ref.CentreOfMass()) < 1e-6) {
            return prefix + std::to_string(i);
        }
    }
    return {};
}

/// Bezug auf einen Body durch seinen Timeline-Zustand ersetzen (das Feature, das ihn gerade erzeugt hat).
/// Sonst entsteht ein Kreis, sobald ein Feature aus einer Skizze/Ebene darauf denselben Body verändert.
void stableRef(App::DocumentObject*& obj, std::string& element)
{
    auto body = freecad_cast<Design::Body*>(obj);
    auto tip = body ? freecad_cast<Design::Feature*>(Design::stateAtMarker(body)) : nullptr;
    if (!tip || element.empty()) {
        return;
    }
    const TopoDS_Shape sub = body->Shape.getShape().getSubShape(element.c_str(), true);
    const std::string name = elementName(tip->Shape.getShape().getShape(), sub);
    if (!name.empty()) {
        obj = tip;
        element = name;
    }
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
    stableRef(support, element);

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
/// setup: zusätzliche Eingaben aus der Auswahl übernehmen (Sweep: Pfad); false = abbrechen
void startProfileFeature(App::Document* doc, const char* type, const char* name,
                         const std::function<bool(Design::Feature*)>& setup = {})
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
        else if (obj && obj->isDerivedFrom<Sketcher::SketchObject>()
                 && std::ranges::none_of(sel.getSubNames(), [](const std::string& s) { return s.rfind("Edge", 0) == 0; })) {
            profiles = Design::Profiles::forSketch(obj);  // Skizze mit gewählten Kanten ist ein Pfad (Sweep)
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
    if (setup && !setup(feature)) {
        doc->abortTransaction();
        return;
    }

    // Skizze auf einer Körperfläche: standardmäßig mit diesem Körper vereinen
    Design::Body* target = nullptr;
    if (auto sketch = freecad_cast<Part::Part2DObject*>(profiles->Sketch.getValue())) {
        const auto& support = sketch->AttachmentSupport.getValues();
        const auto& subs = sketch->AttachmentSupport.getSubValues();
        auto base = support.empty() ? nullptr : freecad_cast<Design::Feature*>(support.front());
        if (base && !subs.empty()) {
            const TopoDS_Shape face = base->Shape.getShape().getSubShape(subs.front().c_str(), true);
            for (auto obj : base->Bodies.getValues()) {
                if (!elementName(base->shapeFor(obj).getShape(), face).empty()) {
                    target = freecad_cast<Design::Body*>(obj);
                }
            }
        }
    }
    startEditing(feature, true, target);
}

/// Sweep: Pfad aus gewählten Skizzen- oder Körperkanten
bool setSweepPath(Design::Feature* feature)
{
    for (auto& sel : Gui::Selection().getSelectionEx()) {
        std::vector<std::string> edges;
        for (const auto& sub : sel.getSubNames()) {
            if (sub.rfind("Edge", 0) == 0) {
                edges.push_back(sub);
            }
        }
        App::DocumentObject* obj = sel.getObject();
        if (edges.empty() || obj->isDerivedFrom<Design::Profiles>()) {
            continue;
        }
        if (freecad_cast<Design::Body*>(obj)) {  // Körperkanten über den Timeline-Zustand (sonst Kreis)
            for (auto& edge : edges) {
                App::DocumentObject* ref = obj;
                stableRef(ref, edge);
                if (ref != obj && edge == edges.front()) {
                    obj = ref;
                }
            }
        }
        static_cast<Design::Sweep*>(feature)->Path.setValue(obj, edges);
        return true;
    }
    QMessageBox::information(Gui::getMainWindow(), QStringLiteral("Sweep"),
                             QStringLiteral("Select a profile and the path (sketch lines or body edges)."));
    return false;
}

/// Loft: zwei oder mehr Profile aus verschiedenen Skizzen, in Auswahlreihenfolge
void startLoft(App::Document* doc)
{
    std::vector<App::DocumentObject*> objs;
    std::vector<std::string> subs;
    for (auto& sel : Gui::Selection().getSelectionEx()) {
        auto profiles = freecad_cast<Design::Profiles*>(sel.getObject());
        if (!profiles && sel.getObject()->isDerivedFrom<Sketcher::SketchObject>()) {
            profiles = Design::Profiles::forSketch(sel.getObject());
        }
        if (!profiles) {
            continue;
        }
        const auto& names = sel.getSubNames();
        if (names.empty()) {
            objs.push_back(profiles);
            subs.emplace_back("Face1");
        }
        for (const auto& name : names) {
            objs.push_back(profiles);
            subs.push_back(name);
        }
    }
    if (objs.size() < 2) {
        QMessageBox::information(Gui::getMainWindow(), QStringLiteral("Loft"),
                                 QStringLiteral("Select two or more profiles from different sketches, in order."));
        return;
    }
    doc->openTransaction("Loft");
    auto feature = static_cast<Design::Loft*>(doc->addObject("Design::Loft", "Loft"));
    Design::componentOf(objs.front())->addObject(feature);
    Design::addToTimeline(feature);
    feature->Sections.setValues(objs, subs);
    startEditing(feature, true, nullptr);
}

/// Grundkörper auf der gewählten Ebene oder Fläche (sonst XY); auf einer Körperfläche standardmäßig Join
void startPrimitive(App::Document* doc, long type)
{
    App::DocumentObject* plane = nullptr;
    std::string element;
    Design::Body* target = nullptr;
    for (auto& sel : Gui::Selection().getSelectionEx()) {
        App::DocumentObject* obj = sel.getObject();
        const auto& names = sel.getSubNames();
        if (isPlane(obj) && names.empty()) {
            plane = obj;
        }
        else if (names.size() == 1 && isPlanarFace(obj, names.front())) {
            target = freecad_cast<Design::Body*>(obj);
            plane = obj;
            element = names.front();
            stableRef(plane, element);
        }
    }
    doc->openTransaction("Primitive");
    auto feature = static_cast<Design::Primitive*>(doc->addObject("Design::Primitive", "Primitive"));
    App::Part* comp = plane ? Design::componentOf(plane) : activeContainer(doc);
    comp->addObject(feature);
    Design::addToTimeline(feature);
    feature->Type.setValue(type);
    if (plane) {
        feature->Plane.setValue(plane, std::vector<std::string> {element});
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

/// Bezugspunkt und -richtung eines Elements: Ebene/ebene Fläche (Mitte + Normale), Zylinderfläche (Achse),
/// gerade Kante (Mitte + Richtung), Kreiskante (Mittelpunkt + Achse), Punkt
struct Frame
{
    gp_Pnt point;
    gp_Dir dir;
    bool hasDir = false;
    bool planar = false;
};

bool frameOf(App::DocumentObject* obj, const std::string& sub, Frame& f)
{
    if (sub.empty() && isPlane(obj)) {
        const Base::Placement p = static_cast<App::GeoFeature*>(obj)->globalPlacement();
        Base::Vector3d z;
        p.getRotation().multVec(Base::Vector3d(0, 0, 1), z);
        f = {gp_Pnt(p.getPosition().x, p.getPosition().y, p.getPosition().z), gp_Dir(z.x, z.y, z.z), true, true};
        return true;
    }
    const TopoDS_Shape s = Part::Feature::getTopoShape(obj, Part::ShapeOption::ResolveLink | Part::ShapeOption::Transform
                                                           | Part::ShapeOption::NeedSubElement,
                                                       sub.empty() ? nullptr : sub.c_str())
                               .getShape();
    if (s.IsNull()) {
        return false;
    }
    GProp_GProps props;
    switch (s.ShapeType()) {
        case TopAbs_VERTEX:
            f.point = BRep_Tool::Pnt(TopoDS::Vertex(s));
            return true;
        case TopAbs_EDGE: {
            BRepGProp::LinearProperties(s, props);
            f.point = props.CentreOfMass();
            BRepAdaptor_Curve c(TopoDS::Edge(s));
            if (c.GetType() == GeomAbs_Line) {
                f.dir = c.Line().Direction();
                f.hasDir = true;
            }
            else if (c.GetType() == GeomAbs_Circle) {
                f.point = c.Circle().Location();
                f.dir = c.Circle().Axis().Direction();
                f.hasDir = true;
            }
            return true;
        }
        case TopAbs_FACE: {
            BRepGProp::SurfaceProperties(s, props);
            f.point = props.CentreOfMass();
            BRepAdaptor_Surface surface(TopoDS::Face(s));
            if (surface.GetType() == GeomAbs_Plane) {
                f.dir = surface.Plane().Axis().Direction();
                if (s.Orientation() == TopAbs_REVERSED) {
                    f.dir.Reverse();
                }
                f.hasDir = f.planar = true;
            }
            else if (surface.GetType() == GeomAbs_Cylinder) {
                const gp_Ax1 axis = surface.Cylinder().Axis();
                f.dir = axis.Direction();
                f.point = axis.Location().Translated(
                    gp_Vec(axis.Direction()) * gp_Vec(axis.Location(), f.point).Dot(gp_Vec(axis.Direction())));
                f.hasDir = true;
            }
            return true;
        }
        default:
            return false;
    }
}

/// Align wie in Fusion: erst ein Element des zu bewegenden Bodies, dann das Ziel. Flächen liegen danach bündig
/// aufeinander, Kanten/Achsen fluchten, Punkte fallen zusammen. Feinjustieren im Move-Dialog.
/// ponytail: die Ausrichtung wird beim Erstellen berechnet und folgt späteren Änderungen der Geometrie nicht
void startAlign(App::Document* doc)
{
    std::vector<std::pair<App::DocumentObject*, std::string>> refs;
    for (auto& sel : Gui::Selection().getSelectionEx()) {
        const auto& names = sel.getSubNames();
        if (names.empty()) {
            refs.emplace_back(sel.getObject(), std::string());
        }
        for (const auto& name : names) {
            refs.emplace_back(sel.getObject(), name);
        }
    }
    auto body = refs.size() == 2 ? freecad_cast<Design::Body*>(refs[0].first) : nullptr;
    Frame from, to;
    if (!body || refs[1].first == body || !frameOf(refs[0].first, refs[0].second, from)
        || !frameOf(refs[1].first, refs[1].second, to)) {
        QMessageBox::information(Gui::getMainWindow(), QStringLiteral("Align"),
                                 QStringLiteral("Select a face, edge or point of the body to move, "
                                                "then the face, edge, point or plane to align it to."));
        return;
    }
    Base::Rotation rot;
    if (from.hasDir && to.hasDir) {
        const gp_Dir target = from.planar && to.planar ? to.dir.Reversed() : to.dir;
        rot = Base::Rotation(Base::Vector3d(from.dir.X(), from.dir.Y(), from.dir.Z()),
                             Base::Vector3d(target.X(), target.Y(), target.Z()));
    }
    Base::Vector3d moved;
    rot.multVec(Base::Vector3d(from.point.X(), from.point.Y(), from.point.Z()), moved);
    auto feature = static_cast<Design::Move*>(addFeature(doc, "Design::Move", "Align", body));
    feature->Label.setValue("Align");
    feature->Alignment.setValue(Base::Placement(Base::Vector3d(to.point.X(), to.point.Y(), to.point.Z()) - moved, rot));
    modifyBodies(feature, {body});
    doc->recompute();
    startEditing(feature, false, nullptr);
}

/// Split Body: erst den Body, dann die Ebene oder Fläche, an der geteilt wird; jedes weitere Teil wird ein Body
void startSplit(App::Document* doc)
{
    Design::Body* body = nullptr;
    App::DocumentObject* tool = nullptr;
    std::string element;
    for (auto& sel : Gui::Selection().getSelectionEx()) {
        App::DocumentObject* obj = sel.getObject();
        const auto& names = sel.getSubNames();
        if (!body && freecad_cast<Design::Body*>(obj) && names.empty()) {
            body = static_cast<Design::Body*>(obj);
        }
        else if (!tool && (isPlane(obj) || (names.size() == 1 && names.front().rfind("Face", 0) == 0))) {
            tool = obj;
            element = names.empty() ? std::string() : names.front();
            stableRef(tool, element);
        }
    }
    if (!body || !tool || tool == body) {
        QMessageBox::information(Gui::getMainWindow(), QStringLiteral("Split Body"),
                                 QStringLiteral("Select the body to split and a plane or face to split it with."));
        return;
    }
    auto feature = static_cast<Design::Split*>(addFeature(doc, "Design::Split", "Split", body));
    feature->Tool.setValue(tool, std::vector<std::string> {element});
    modifyBodies(feature, {body});
    doc->recompute();
    // je weiteres Teil ein neuer Body
    auto bodies = feature->Bodies.getValues();
    for (long i = 1; i < feature->Pieces.getValue(); ++i) {
        auto piece = static_cast<Design::Body*>(doc->addObject("Design::Body", "Body"));
        piece->Label.setValue(std::string(body->Label.getValue()) + " (" + std::to_string(i + 1) + ")");
        Design::folder(Design::componentOf(body), "Bodies")->addObject(piece);
        piece->Tip.setValue(feature);
        bodies.push_back(piece);
    }
    feature->Bodies.setValues(bodies);
    doc->recompute();
    if (feature->isError()) {
        QMessageBox::warning(Gui::getMainWindow(), QStringLiteral("Split Body"),
                             QString::fromUtf8(feature->getStatusString()));
        doc->abortTransaction();
        doc->recompute();
        return;
    }
    doc->commitTransaction();
    Gui::Selection().clearSelection();
}

/// Scale: gewählte Bodies
void startScale(App::Document* doc)
{
    const auto bodies = selectedBodies();
    if (bodies.empty()) {
        QMessageBox::information(Gui::getMainWindow(), QStringLiteral("Scale"),
                                 QStringLiteral("Select one or more bodies first."));
        return;
    }
    if (!sameComponent(bodies, "Scale")) {
        return;
    }
    auto feature = addFeature(doc, "Design::Scale", "Scale", bodies.front());
    modifyBodies(feature, bodies);
    doc->recompute();
    startEditing(feature, false, nullptr);
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
            if (absolute.matchView(xml.attributes().value(QStringLiteral("width"))).hasMatch()) {
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
        if (!elementName(base->shapeFor(b).getShape(), face).empty()) {
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
        // Körper-Muster: Kopien der gewählten Bodies, je Quelle ein neuer Body (wie Mirror)
        const auto selected = selectedBodies();
        if (!selected.empty() && sameComponent(selected, "Pattern")) {
            auto feature = static_cast<Design::Pattern*>(addFeature(doc, "Design::Pattern", "Pattern", selected.front()));
            std::vector<App::DocumentObject*> sources, states, created;
            for (auto b : selected) {
                sources.push_back(b);
                states.push_back(Design::stateAtMarker(b));
                auto copy = static_cast<Design::Body*>(doc->addObject("Design::Body", "Body"));
                copy->Label.setValue(std::string(b->Label.getValue()) + " Pattern");
                Design::folder(Design::componentOf(b), "Bodies")->addObject(copy);
                copy->Tip.setValue(feature);
                created.push_back(copy);
            }
            feature->SourceBodies.setValues(sources);
            feature->SourceFeatures.setValues(states);
            feature->Bodies.setValues(created);
            feature->Operation.setValue(0L);
            doc->recompute();
            startEditing(feature, false, nullptr);
            return;
        }
        QMessageBox::information(Gui::getMainWindow(), QStringLiteral("Pattern"),
                                 QStringLiteral("Select bodies, or an Extrude, Revolve or Hole in the timeline first."));
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

/// Konstruktionselemente dezent statt FreeCAD-Gelb; Ebenen so groß wie die vorhandenen Körper
void styleDatum(App::DocumentObject* datum)
{
    auto length = freecad_cast<App::PropertyLength*>(datum->getPropertyByName("Length"));
    auto width = freecad_cast<App::PropertyLength*>(datum->getPropertyByName("Width"));
    auto resize = freecad_cast<App::PropertyEnumeration*>(datum->getPropertyByName("ResizeMode"));
    if (length && width && resize) {  // nur Ebenen (Achsen haben keine Breite)
        Base::BoundBox3d bb;
        for (auto b : datum->getDocument()->getObjectsOfType(Design::Body::getClassTypeId())) {
            bb.Add(static_cast<Design::Body*>(b)->Shape.getShape().getBoundBox());
        }
        const double size = bb.IsValid() ? std::max(bb.LengthX(), bb.LengthY()) * 1.2 : 60.0;
        resize->setValue("Manual");
        length->setValue(size);
        width->setValue(size);
    }
    if (auto vp = freecad_cast<Gui::ViewProviderGeometryObject*>(Gui::Application::Instance->getViewProvider(datum))) {
        vp->ShapeAppearance.setDiffuseColor(0.45F, 0.62F, 1.0F);
        vp->Transparency.setValue(80);
    }
}

/// Gewählte Elemente als Bezüge (Body-Elemente über den Timeline-Zustand)
void selectedRefs(std::vector<App::DocumentObject*>& objs, std::vector<std::string>& subs)
{
    for (auto& sel : Gui::Selection().getSelectionEx()) {
        std::vector<std::string> names = sel.getSubNames();
        if (names.empty()) {
            names.emplace_back();
        }
        for (auto name : names) {
            App::DocumentObject* obj = sel.getObject();
            stableRef(obj, name);
            objs.push_back(obj);
            subs.push_back(name);
        }
    }
}

/// Konstruktionsebene, -achse oder -punkt aus der Auswahl; FreeCADs Attacher wählt die passende Befestigung
/// (drei Punkte, Fläche + Punkt, Kante + Punkt, Zylinderfläche, zwei Punkte, zwei Ebenen, Kreiskante, …)
void startConstruct(App::Document* doc, const char* type, const char* name, const char* hint)
{
    std::vector<App::DocumentObject*> objs;
    std::vector<std::string> subs;
    selectedRefs(objs, subs);
    if (objs.empty()) {
        QMessageBox::information(Gui::getMainWindow(), QString::fromLatin1(name), QString::fromLatin1(hint));
        return;
    }
    doc->openTransaction(name);
    App::DocumentObject* datum = doc->addObject(type, name);
    auto attach = datum ? datum->getExtensionByType<Part::AttachExtension>() : nullptr;
    if (!attach) {
        doc->abortTransaction();
        return;
    }
    attach->AttachmentSupport.setValues(objs, subs);
    attach->attacher().setReferences(attach->AttachmentSupport);
    Attacher::SuggestResult suggestion;
    attach->attacher().suggestMapModes(suggestion);
    if (suggestion.message != Attacher::SuggestResult::srOK) {
        doc->abortTransaction();
        QMessageBox::information(Gui::getMainWindow(), QString::fromLatin1(name),
                                 QStringLiteral("This selection does not define a %1. %2")
                                     .arg(QString::fromLatin1(name).toLower(), QString::fromLatin1(hint)));
        return;
    }
    attach->MapMode.setValue(Attacher::AttachEngine::getModeName(suggestion.bestFitMode).c_str());
    Design::folder(Design::componentOf(objs.front()), "Construction")->addObject(datum);
    styleDatum(datum);
    doc->recompute();
    doc->commitTransaction();
    Gui::Selection().clearSelection();
}

/// Ebene genau zwischen zwei parallelen Ebenen oder ebenen Flächen.
/// ponytail: Abstand wird beim Erstellen berechnet; verschieben sich die Flächen später, bleibt er stehen
void startMidplane(App::Document* doc)
{
    std::vector<App::DocumentObject*> objs;
    std::vector<std::string> subs;
    selectedRefs(objs, subs);
    auto planeOf = [&](size_t i, gp_Pln& pln) {
        const Part::TopoShape s = Part::Feature::getTopoShape(objs[i], Part::ShapeOption::ResolveLink
                                                                       | Part::ShapeOption::Transform,
                                                               subs[i].empty() ? nullptr : subs[i].c_str());
        TopExp_Explorer face(s.getShape(), TopAbs_FACE);
        if (!face.More()) {
            return false;
        }
        BRepAdaptor_Surface surface(TopoDS::Face(face.Current()));
        if (surface.GetType() != GeomAbs_Plane) {
            return false;
        }
        pln = surface.Plane();
        return true;
    };
    gp_Pln a, b;
    if (objs.size() != 2 || !planeOf(0, a) || !planeOf(1, b) || !a.Axis().IsParallel(b.Axis(), 1e-6)) {
        QMessageBox::information(Gui::getMainWindow(), QStringLiteral("Midplane"),
                                 QStringLiteral("Select two parallel planes or planar faces."));
        return;
    }
    doc->openTransaction("Midplane");
    App::DocumentObject* plane = doc->addObject("PartDesign::Plane", "Midplane");
    auto attach = plane->getExtensionByType<Part::AttachExtension>();
    attach->AttachmentSupport.setValue(objs[0], std::vector<std::string> {subs[0]});
    attach->MapMode.setValue("FlatFace");
    Design::folder(Design::componentOf(objs.front()), "Construction")->addObject(plane);
    plane->recomputeFeature();
    // halber Abstand entlang der Normalen der befestigten Ebene (Vorzeichen aus deren Lage)
    const Base::Placement placed = static_cast<App::GeoFeature*>(plane)->Placement.getValue();
    Base::Vector3d n;
    placed.getRotation().multVec(Base::Vector3d(0, 0, 1), n);
    const gp_Pnt o = b.Location();
    const double d = (Base::Vector3d(o.X(), o.Y(), o.Z()) - placed.getPosition()) * n;
    attach->AttachmentOffset.setValue(Base::Placement(Base::Vector3d(0, 0, d / 2), Base::Rotation()));
    styleDatum(plane);
    doc->recompute();
    doc->commitTransaction();
    Gui::Selection().clearSelection();
}

/// Messen wie in Fusion: Werte der aktuellen Auswahl, live aktualisiert
class TaskMeasure: public Gui::TaskView::TaskDialog, public Gui::SelectionObserver
{
public:
    TaskMeasure()
    {
        auto w = new QWidget;
        w->setWindowTitle(QStringLiteral("Measure"));
        auto lay = new QVBoxLayout(w);
        result = new QLabel;
        result->setTextInteractionFlags(Qt::TextSelectableByMouse);
        result->setWordWrap(true);
        lay->addWidget(result);
        addTaskBox(w, false);
        update();
    }
    QDialogButtonBox::StandardButtons getStandardButtons() const override
    {
        return QDialogButtonBox::Close;
    }
    bool accept() override
    {
        return true;
    }
    bool reject() override
    {
        return true;
    }

private:
    void onSelectionChanged(const Gui::SelectionChanges& msg) override
    {
        if (msg.Type == Gui::SelectionChanges::AddSelection || msg.Type == Gui::SelectionChanges::RmvSelection
            || msg.Type == Gui::SelectionChanges::SetSelection || msg.Type == Gui::SelectionChanges::ClrSelection) {
            QTimer::singleShot(0, result, [this] { update(); });
        }
    }
    static QString length(double v)
    {
        return QString::fromStdString(Base::Quantity(v, Base::Unit::Length).getUserString());
    }
    void update()
    {
        std::vector<TopoDS_Shape> shapes;
        for (auto& sel : Gui::Selection().getSelectionEx()) {
            std::vector<std::string> names = sel.getSubNames();
            if (names.empty()) {
                names.emplace_back();
            }
            for (const auto& name : names) {
                const Part::TopoShape s = Part::Feature::getTopoShape(
                    sel.getObject(), Part::ShapeOption::ResolveLink | Part::ShapeOption::Transform
                                         | Part::ShapeOption::NeedSubElement,
                    name.empty() ? nullptr : name.c_str());
                if (!s.isNull()) {
                    shapes.push_back(s.getShape());
                }
            }
        }
        QStringList rows;
        auto row = [&rows](const QString& label, const QString& value) {
            rows << QStringLiteral("<tr><td style='color:gray; padding-right:12px'>%1</td><td><b>%2</b></td></tr>")
                        .arg(label, value);
        };
        if (shapes.size() == 1) {
            const TopoDS_Shape& s = shapes.front();
            GProp_GProps p;
            switch (s.ShapeType()) {
                case TopAbs_VERTEX: {
                    const gp_Pnt v = BRep_Tool::Pnt(TopoDS::Vertex(s));
                    row(QStringLiteral("X"), length(v.X()));
                    row(QStringLiteral("Y"), length(v.Y()));
                    row(QStringLiteral("Z"), length(v.Z()));
                    break;
                }
                case TopAbs_EDGE: {
                    BRepGProp::LinearProperties(s, p);
                    row(QStringLiteral("Length"), length(p.Mass()));
                    BRepAdaptor_Curve curve(TopoDS::Edge(s));
                    if (curve.GetType() == GeomAbs_Circle) {
                        row(QStringLiteral("Radius"), length(curve.Circle().Radius()));
                        row(QStringLiteral("Diameter"), length(2 * curve.Circle().Radius()));
                    }
                    break;
                }
                case TopAbs_FACE: {
                    BRepGProp::SurfaceProperties(s, p);
                    row(QStringLiteral("Area"), QStringLiteral("%1 mm²").arg(p.Mass(), 0, 'f', 2));
                    BRepAdaptor_Surface surface(TopoDS::Face(s));
                    if (surface.GetType() == GeomAbs_Cylinder) {
                        row(QStringLiteral("Radius"), length(surface.Cylinder().Radius()));
                        row(QStringLiteral("Diameter"), length(2 * surface.Cylinder().Radius()));
                    }
                    break;
                }
                default: {
                    BRepGProp::VolumeProperties(s, p);
                    row(QStringLiteral("Volume"), QStringLiteral("%1 mm³").arg(p.Mass(), 0, 'f', 2));
                    GProp_GProps area;
                    BRepGProp::SurfaceProperties(s, area);
                    row(QStringLiteral("Area"), QStringLiteral("%1 mm²").arg(area.Mass(), 0, 'f', 2));
                    Bnd_Box box;
                    BRepBndLib::Add(s, box);
                    if (!box.IsVoid()) {
                        double x0, y0, z0, x1, y1, z1;
                        box.Get(x0, y0, z0, x1, y1, z1);
                        row(QStringLiteral("Size"), QStringLiteral("%1 × %2 × %3")
                                                        .arg(length(x1 - x0), length(y1 - y0), length(z1 - z0)));
                    }
                    break;
                }
            }
        }
        else if (shapes.size() == 2) {
            BRepExtrema_DistShapeShape dist(shapes[0], shapes[1]);
            if (dist.IsDone()) {
                row(QStringLiteral("Distance"), length(dist.Value()));
            }
            // Winkel zwischen zwei geraden Kanten oder zwei ebenen Flächen
            auto direction = [](const TopoDS_Shape& s, gp_Dir& d) {
                if (s.ShapeType() == TopAbs_EDGE) {
                    BRepAdaptor_Curve c(TopoDS::Edge(s));
                    if (c.GetType() == GeomAbs_Line) {
                        d = c.Line().Direction();
                        return true;
                    }
                }
                else if (s.ShapeType() == TopAbs_FACE) {
                    BRepAdaptor_Surface f(TopoDS::Face(s));
                    if (f.GetType() == GeomAbs_Plane) {
                        d = f.Plane().Axis().Direction();
                        return true;
                    }
                }
                return false;
            };
            gp_Dir a, b;
            if (direction(shapes[0], a) && direction(shapes[1], b)) {
                double angle = a.Angle(b) * 180 / M_PI;
                angle = std::min(angle, 180 - angle);
                row(QStringLiteral("Angle"), QStringLiteral("%1°").arg(angle, 0, 'f', 2));
            }
        }
        result->setText(rows.isEmpty() ? QStringLiteral("Select a point, edge, face or body. "
                                                         "Select two to measure distance and angle.")
                                       : QStringLiteral("<table>%1</table>").arg(rows.join(QString())));
    }
    QLabel* result;
};

void startMeasure(App::Document*)
{
    Gui::Control().showDialog(new TaskMeasure);
}

/// Schnittansicht: das Modell an einer Ebene oder ebenen Fläche aufschneiden (nochmal: Schnitt aufheben)
void toggleSection(App::Document* doc)
{
    auto gdoc = Gui::Application::Instance->getDocument(doc);
    auto view = gdoc ? dynamic_cast<Gui::View3DInventor*>(gdoc->getActiveView()) : nullptr;
    if (!view) {
        return;
    }
    Gui::View3DInventorViewer* viewer = view->getViewer();
    if (viewer->hasClippingPlane()) {
        viewer->toggleClippingPlane(0);
        return;
    }
    gp_Pln pln;
    bool found = false;
    for (auto& sel : Gui::Selection().getSelectionEx()) {
        const auto& names = sel.getSubNames();
        const Part::TopoShape s = Part::Feature::getTopoShape(
            sel.getObject(), Part::ShapeOption::ResolveLink | Part::ShapeOption::Transform,
            names.empty() ? nullptr : names.front().c_str());
        TopExp_Explorer face(s.getShape(), TopAbs_FACE);
        if (face.More()) {
            BRepAdaptor_Surface surface(TopoDS::Face(face.Current()));
            if (surface.GetType() == GeomAbs_Plane) {
                pln = surface.Plane();
                found = true;
                break;
            }
        }
    }
    if (!found) {
        QMessageBox::information(Gui::getMainWindow(), QStringLiteral("Section Analysis"),
                                 QStringLiteral("Select a plane or a planar face to cut the model at."));
        return;
    }
    const gp_Pnt o = pln.Location();
    const gp_Dir n = pln.Axis().Direction();
    const Base::Placement placement(Base::Vector3d(o.X(), o.Y(), o.Z()),
                                    Base::Rotation(Base::Vector3d(0, 0, 1), Base::Vector3d(n.X(), n.Y(), n.Z())));
    Gui::Selection().clearSelection();
    viewer->toggleClippingPlane(1, false, false, placement);
}

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
    stableRef(support, element);
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

    styleDatum(plane);
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
    mgr.addCommand(new DesignCommand("Design_Plane", "Plane",
                                     "Plane: select three points, a face and a point, or an edge and a point",
                                     "PartDesign_Plane", "", [](App::Document* doc) {
                                         startConstruct(doc, "PartDesign::Plane", "Plane",
                                                        "Select three points, a face and a point, or an edge "
                                                        "and a point.");
                                     }));
    mgr.addCommand(new DesignCommand("Design_Midplane", "Midplane", "Midplane: select two parallel planes or faces",
                                     "PartDesign_Plane", "", startMidplane));
    mgr.addCommand(new DesignCommand("Design_Axis", "Axis",
                                     "Axis: select a cylindrical face, a straight edge, two points or two planes",
                                     "PartDesign_Line", "", [](App::Document* doc) {
                                         startConstruct(doc, "PartDesign::Line", "Axis",
                                                        "Select a cylindrical face, a straight edge, two points "
                                                        "or two planes.");
                                     }));
    mgr.addCommand(new DesignCommand("Design_Point", "Point",
                                     "Point: select a vertex, a circular edge, an edge and a plane, or three planes",
                                     "PartDesign_Point", "", [](App::Document* doc) {
                                         startConstruct(doc, "PartDesign::Point", "Point",
                                                        "Select a vertex, a circular edge, an edge and a plane, "
                                                        "or three planes.");
                                     }));
    mgr.addCommand(new DesignCommand("Design_Measure", "Measure",
                                     "Measure: select one or two points, edges, faces or bodies", "Std_Measure",
                                     "I", startMeasure));
    mgr.addCommand(new DesignCommand("Design_Section", "Section Analysis",
                                     "Section Analysis: select a plane or face to cut the view (again: turn off)",
                                     "Std_ToggleClipPlane", "", toggleSection));
    mgr.addCommand(new DesignCommand("Design_Sweep", "Sweep", "Sweep: select a profile and a path",
                                     "PartDesign_AdditivePipe", "", [](App::Document* doc) {
                                         startProfileFeature(doc, "Design::Sweep", "Sweep", setSweepPath);
                                     }));
    mgr.addCommand(new DesignCommand("Design_Loft", "Loft", "Loft: select two or more profiles in order",
                                     "PartDesign_AdditiveLoft", "", startLoft));
    struct Shape
    {
        const char* command;
        const char* text;
        long type;
    };
    for (const Shape& s : {Shape {"Design_Box", "Box", 0}, Shape {"Design_Cylinder", "Cylinder", 1},
                           Shape {"Design_Sphere", "Sphere", 2}, Shape {"Design_Torus", "Torus", 3},
                           Shape {"Design_Coil", "Coil", 4}}) {
        const long type = s.type;
        mgr.addCommand(new DesignCommand(s.command, s.text,
                                         "Primitive on the selected plane or face (otherwise XY)", "Part_Box", "",
                                         [type](App::Document* doc) { startPrimitive(doc, type); }));
    }
    mgr.addCommand(new DesignCommand("Design_Draft", "Draft", "Draft: select side faces of a body to tilt",
                                     "PartDesign_Draft", "", [](App::Document* doc) {
                                         startDressUp(doc, "Design::Draft", "Draft");
                                     }));
    mgr.addCommand(new DesignCommand("Design_Scale", "Scale", "Scale: select one or more bodies", "Part_Scale",
                                     "", startScale));
    mgr.addCommand(new DesignCommand("Design_Align", "Align",
                                     "Align: select a face, edge or point of a body, then the target", "Std_TransformManip",
                                     "", startAlign));
    mgr.addCommand(new DesignCommand("Design_SplitBody", "Split Body",
                                     "Split Body: select a body and a plane or face to split it with", "Part_Slice", "",
                                     startSplit));
    mgr.addCommand(new DesignCommand("Design_Thread", "Thread", "Thread: select a cylindrical face of a body",
                                     "PartDesign_Hole", "", [](App::Document* doc) {
                                         startDressUp(doc, "Design::Thread", "Thread");
                                     }));
    mgr.addCommand(new DesignCommand("Design_NewComponent", "New Component",
                                     "New Component: an empty part with its own origin (double-click to activate)",
                                     "Std_Part", "", startNewComponent));
    mgr.addCommand(new DesignCommand("Design_Chamfer", "Chamfer", "Chamfer: select edges or faces of a body",
                                     "PartDesign_Chamfer", "", [](App::Document* doc) {
                                         startDressUp(doc, "Design::Chamfer", "Chamfer");
                                     }));
}
