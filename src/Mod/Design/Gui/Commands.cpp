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
#include <Gui/MainWindow.h>
#include <Gui/Selection/Selection.h>
#include <Gui/ViewProviderCoordinateSystem.h>
#include <Gui/ViewProviderGeometryObject.h>
#include <Mod/Design/App/Features.h>
#include <Mod/Sketcher/App/SketchObject.h>

#include "ViewProviders.h"

#include <BRepAdaptor_Surface.hxx>
#include <BRepGProp.hxx>
#include <GProp_GProps.hxx>
#include <TopExp.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopoDS.hxx>

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

void createSketch(App::DocumentObject* support, std::string element)
{
    // Skizze auf einer Körperfläche an den Timeline-Zustand hängen (das Feature, das den Body gerade
    // erzeugt hat), nicht an den Body: sonst entsteht ein Kreis, sobald ein Feature aus dieser Skizze
    // denselben Body verändert. So bezieht sich die Skizze wie in Fusion auf den Körper zu diesem Zeitpunkt.
    if (auto body = freecad_cast<Design::Body*>(support)) {
        if (auto tip = freecad_cast<Design::Feature*>(body->Tip.getValue())) {
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
    App::Part* root = Design::root(doc, true);
    auto sketch = static_cast<Sketcher::SketchObject*>(doc->addObject("Sketcher::SketchObject", "Sketch"));
    Design::folder(root, "Sketches")->addObject(sketch);
    sketch->AttachmentSupport.setValue(support, std::vector<std::string> {element});
    sketch->MapMode.setValue("FlatFace");
    auto profiles = static_cast<Design::Profiles*>(doc->addObject("Design::Profiles", "Profiles"));
    root->addObject(profiles);
    profiles->Sketch.setValue(sketch);
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
    App::Part* root = Design::root(doc, true);
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
    Design::root(doc, true)->addObject(feature);
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
    if (!body || (edges.empty() && !bodyAlone) || !body->Tip.getValue()) {
        QMessageBox::information(Gui::getMainWindow(), QString::fromLatin1(name),
                                 QStringLiteral("Select edges (or faces) of a body first."));
        return;
    }

    doc->openTransaction(name);
    auto feature = static_cast<Design::DressUp*>(doc->addObject(type, name));
    Design::root(doc, true)->addObject(feature);
    feature->Bodies.setValues({body});
    feature->BaseFeatures.setValues({body->Tip.getValue()});
    feature->Edges.setValues(edges);
    body->Tip.setValue(feature);
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
        if (b && b->Tip.getValue() && std::ranges::find(bodies, b) == bodies.end()) {
            bodies.push_back(b);
        }
    }
    return bodies;
}

Design::Feature* addFeature(App::Document* doc, const char* type, const char* name)
{
    doc->openTransaction(name);
    auto feature = static_cast<Design::Feature*>(doc->addObject(type, name));
    Design::root(doc, true)->addObject(feature);
    return feature;
}

/// Feature verändert die Bodies: je Body vorheriger Zustand als Basis, das Feature wird neuer Tip
void modifyBodies(Design::Feature* feature, const std::vector<Design::Body*>& bodies)
{
    std::vector<App::DocumentObject*> objs, bases;
    for (auto b : bodies) {
        objs.push_back(b);
        bases.push_back(b->Tip.getValue());
    }
    feature->Bodies.setValues(objs);
    feature->BaseFeatures.setValues(bases);
    for (auto b : bodies) {
        b->Tip.setValue(feature);
    }
}

void startCombine(App::Document* doc)
{
    const auto bodies = selectedBodies();
    if (bodies.size() < 2) {
        QMessageBox::information(Gui::getMainWindow(), QStringLiteral("Combine"),
                                 QStringLiteral("Select the target body first, then one or more tool bodies."));
        return;
    }
    auto feature = static_cast<Design::Combine*>(addFeature(doc, "Design::Combine", "Combine"));
    std::vector<App::DocumentObject*> tools, states;
    for (size_t i = 1; i < bodies.size(); ++i) {
        tools.push_back(bodies[i]);
        states.push_back(bodies[i]->Tip.getValue());
    }
    feature->ToolBodies.setValues(tools);
    feature->ToolFeatures.setValues(states);
    modifyBodies(feature, {bodies.front()});
    doc->recompute();
    startEditing(feature, false, nullptr);
}

void startMove(App::Document* doc)
{
    const auto bodies = selectedBodies();
    if (bodies.empty()) {
        QMessageBox::information(Gui::getMainWindow(), QStringLiteral("Move"),
                                 QStringLiteral("Select one or more bodies first."));
        return;
    }
    auto feature = addFeature(doc, "Design::Move", "Move");
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
    auto feature = static_cast<Design::Mirror*>(addFeature(doc, "Design::Mirror", "Mirror"));
    std::vector<App::DocumentObject*> sources, states, created;
    for (auto b : bodies) {
        sources.push_back(b);
        states.push_back(b->Tip.getValue());
        auto copy = static_cast<Design::Body*>(doc->addObject("Design::Body", "Body"));
        copy->Label.setValue(std::string(b->Label.getValue()) + " Mirror");
        Design::folder(Design::root(doc, true), "Bodies")->addObject(copy);
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
    auto feature = static_cast<Design::Hole*>(addFeature(doc, "Design::Hole", "Hole"));
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
    auto feature = static_cast<Design::Pattern*>(addFeature(doc, "Design::Pattern", "Pattern"));
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
    Design::folder(Design::root(doc, true), "Construction")->addObject(plane);
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
    mgr.addCommand(new DesignCommand("Design_Chamfer", "Chamfer", "Chamfer: select edges or faces of a body",
                                     "PartDesign_Chamfer", "", [](App::Document* doc) {
                                         startDressUp(doc, "Design::Chamfer", "Chamfer");
                                     }));
}
