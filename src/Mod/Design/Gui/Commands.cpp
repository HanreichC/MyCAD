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
#include <Gui/MainWindow.h>
#include <Gui/Selection/Selection.h>
#include <Gui/ViewProviderCoordinateSystem.h>
#include <Mod/Design/App/Features.h>
#include <Mod/Sketcher/App/SketchObject.h>

#include "ViewProviders.h"

#include <BRepAdaptor_Surface.hxx>
#include <BRepGProp.hxx>
#include <GProp_GProps.hxx>
#include <TopExp.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopoDS.hxx>

#include <QMessageBox>
#include <QTimer>

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
        if (!leaf || !(leaf->isDerivedFrom<App::Plane>() || isPlanarFace(leaf, element))) {
            return;
        }
        App::DocumentObjectT target(leaf);
        // Nicht mitten im Selektions-Callback Objekte anlegen und den Edit-Modus starten
        QTimer::singleShot(0, [target, element] {
            stop();
            Gui::Selection().clearSelection();
            if (auto obj = target.getObject()) {
                createSketch(obj, obj->isDerivedFrom<App::Plane>() ? std::string() : element);
            }
        });
    }

    App::DocumentObjectWeakPtrT root;
    static inline std::unique_ptr<PlanePicker> active;
};

}  // namespace

// ---------------------------------------------------------------------------------------------

DEF_STD_CMD_A(CmdDesignCreateSketch)

CmdDesignCreateSketch::CmdDesignCreateSketch()
    : Command("Design_CreateSketch")
{
    sAppModule = "Design";
    sGroup = "Design";
    sMenuText = QT_TR_NOOP("Create Sketch");
    sToolTipText = QT_TR_NOOP("Create Sketch: click a plane or planar face to sketch on");
    sWhatsThis = "Design_CreateSketch";
    sStatusTip = sToolTipText;
    sPixmap = "Sketcher_NewSketch";
    sAccel = "S";
    eType = NoTransaction;
}

void CmdDesignCreateSketch::activated(int)
{
    App::Document* doc = getDocument();
    App::Part* root = Design::root(doc, true);

    // Bereits etwas Passendes ausgewählt? Dann sofort darauf skizzieren.
    auto selection = Gui::Selection().getSelectionEx();
    for (auto& sel : selection) {
        App::DocumentObject* obj = sel.getObject();
        const auto& subs = sel.getSubNames();
        if (obj && obj->isDerivedFrom<App::Plane>()) {
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

bool CmdDesignCreateSketch::isActive()
{
    return hasActiveDocument() && !Gui::Control().activeDialog();
}

// ---------------------------------------------------------------------------------------------

DEF_STD_CMD_A(CmdDesignExtrude)

CmdDesignExtrude::CmdDesignExtrude()
    : Command("Design_Extrude")
{
    sAppModule = "Design";
    sGroup = "Design";
    sMenuText = QT_TR_NOOP("Extrude");
    sToolTipText = QT_TR_NOOP("Extrude: select one or more sketch profiles");
    sWhatsThis = "Design_Extrude";
    sStatusTip = sToolTipText;
    sPixmap = "PartDesign_Pad";
    sAccel = "E";
    eType = NoTransaction;
}

void CmdDesignExtrude::activated(int)
{
    App::Document* doc = getDocument();
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
        QMessageBox::information(Gui::getMainWindow(), QStringLiteral("Extrude"),
                                 QStringLiteral("Select one or more profiles (closed areas of a sketch) first."));
        return;
    }

    doc->openTransaction("Extrude");
    App::Part* root = Design::root(doc, true);
    auto ext = static_cast<Design::Extrude*>(doc->addObject("Design::Extrude", "Extrude"));
    root->addObject(ext);
    ext->Profile.setValue(profiles, faces);

    // Skizze auf einer Körperfläche: standardmäßig mit diesem Körper vereinen
    Design::Body* target = nullptr;
    if (auto sketch = freecad_cast<Part::Part2DObject*>(profiles->Sketch.getValue())) {
        const auto& support = sketch->AttachmentSupport.getValues();
        const auto& subs = sketch->AttachmentSupport.getSubValues();
        auto feature = support.empty() ? nullptr : freecad_cast<Design::Feature*>(support.front());
        if (feature && !subs.empty()) {
            const TopoDS_Shape face = feature->Shape.getShape().getSubShape(subs.front().c_str(), true);
            for (auto obj : feature->Bodies.getValues()) {
                if (!faceName(feature->shapeFor(obj).getShape(), face).empty()) {
                    target = freecad_cast<Design::Body*>(obj);
                }
            }
        }
    }

    Gui::Selection().clearSelection();
    Gui::Document* gdoc = Gui::Application::Instance->getDocument(doc);
    auto vp = static_cast<DesignGui::ViewProviderExtrude*>(gdoc->getViewProvider(ext));
    vp->createMode = true;
    vp->defaultTarget = target;
    gdoc->setEdit(vp);
}

bool CmdDesignExtrude::isActive()
{
    return hasActiveDocument() && !Gui::Control().activeDialog();
}

void CreateDesignCommands()
{
    auto& mgr = Gui::Application::Instance->commandManager();
    mgr.addCommand(new CmdDesignCreateSketch());
    mgr.addCommand(new CmdDesignExtrude());
}
