// SPDX-License-Identifier: LGPL-2.1-or-later

#include <iomanip>
#include <sstream>

#include <App/Datums.h>
#include <App/Document.h>
#include <App/DocumentObjectGroup.h>
#include <App/Origin.h>
#include <App/Part.h>
#include <Gui/Application.h>
#include <Gui/Action.h>
#include <Gui/Command.h>
#include <Gui/Control.h>
#include <Gui/Document.h>
#include <Gui/QuantitySpinBox.h>
#include <Gui/TaskView/TaskDialog.h>
#include <Base/Console.h>
#include <Base/Interpreter.h>
#include <Gui/ActiveObjectList.h>
#include <Gui/MainWindow.h>
#include <Gui/MDIView.h>
#include <Gui/Selection/Selection.h>
#include <Gui/ViewProviderCoordinateSystem.h>
#include <Gui/ViewProviderGeometryObject.h>
#include <Mod/Design/App/Features.h>
#include <Mod/Sketcher/App/Constraint.h>
#include <Mod/Sketcher/App/SketchObject.h>
#include <Mod/Sketcher/Gui/FontProvider.h>
#include <Base/BoundBox.h>
#include <Standard_Failure.hxx>
#include <Mod/Part/App/Geometry.h>
#include <Mod/Part/App/AttachExtension.h>
#include <Mod/Part/App/Attacher.h>
#include <Gui/View3DInventor.h>
#include <Gui/View3DInventorViewer.h>
#include <BRepAdaptor_Curve.hxx>
#include <BRepBndLib.hxx>
#include <BRepExtrema_DistShapeShape.hxx>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <TopoDS_Iterator.hxx>
#include <Bnd_Box.hxx>
#include <TopExp_Explorer.hxx>
#include <Mod/Part/App/Part2DObject.h>
#include <TopTools_ListOfShape.hxx>
#include <TopTools_IndexedDataMapOfShapeListOfShape.hxx>
#include <TopoDS_Vertex.hxx>
#include <gp_Pln.hxx>
#include <QCheckBox>
#include <QScrollArea>
#include <QComboBox>
#include <QInputDialog>
#include <QListWidget>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <Mod/Part/App/TopoShapePy.h>
#include <QStandardPaths>
#include <QLabel>
#include <cstring>
#include <App/ObjectIdentifier.h>
#include <App/Expression.h>
#include <App/ExpressionParser.h>
#include <Mod/Design/App/DxfCleanup.h>
#include <Mod/Design/App/NoteParameters.h>
#include <QImage>
#include <Mod/Design/App/PhotoContour.h>
#include <QDialogButtonBox>
#include <QDialog>
#include <QLineEdit>
#include <QHeaderView>
#include <QTableWidget>
#include <App/Material.h>
#include <QToolButton>
#include <QAbstractButton>
#include <QApplication>
#include <QDrag>
#include <QDropEvent>
#include <QMenu>
#include <QMimeData>
#include <QMouseEvent>
#include <QPointer>
#include <Inventor/SoPickedPoint.h>
#include <App/Application.h>
#include <App/GeoFeature.h>
#include <Mod/Part/App/PartFeature.h>
#include <array>
#include <map>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <BRep_Tool.hxx>
#include <BRepGProp_Face.hxx>
#include <GeomAPI_ProjectPointOnSurf.hxx>
#include <TopExp.hxx>
#include <TopoDS.hxx>
#include <GeomConvert.hxx>
#include <Geom_BezierCurve.hxx>
#include <Geom_Ellipse.hxx>
#include <gp_Ax2.hxx>
#include <Geom_TrimmedCurve.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <QPaintDevice>
#include <QPaintEngine>
#include <QPainter>
#include <QPainterPath>
#include <QRegularExpression>
#include <set>
#include <QSvgRenderer>
#include <QXmlStreamReader>

#include "ScribbleShapes.h"
#include "ViewProviders.h"

#include <BRepAdaptor_Surface.hxx>
#include <BRepGProp.hxx>
#include <GProp_GProps.hxx>
#include <TopExp.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>

#include <QDesktopServices>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QDateTime>
#include <QLocale>
#include <QFormLayout>
#include <QMessageBox>
#include <QTimer>

#include <functional>
#include <memory>
#include <Gui/Shell/GlassPanel.h>
#include <Gui/Shell/Shell.h>
#include <Gui/Shell/Theme.h>

using Gui::Shell::T;

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

using Design::elementName;
using Design::stableRef;

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

/// Neue, nicht angehängte Skizze mit Profiles-Begleiter in der Komponente root (ohne Transaktion)
Sketcher::SketchObject* newSketch(App::Part* root)
{
    return static_cast<Sketcher::SketchObject*>(Design::newSketch(root));
}

/// Neue Skizze mit Profiles-Begleiter in der Komponente der Ebene bzw. des Körpers (ohne Transaktion)
Sketcher::SketchObject* addSketch(App::DocumentObject* support, const std::string& element)
{
    Sketcher::SketchObject* sketch = newSketch(Design::componentOf(support));
    sketch->AttachmentSupport.setValue(support, std::vector<std::string> {element});
    sketch->MapMode.setValue("FlatFace");
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
    // Körperfläche: ihren Rand wie in Fusion projizieren, als Hilfslinien zum Fangen (bilden keine Profile).
    // Erst nach dem Recompute: die Projektion braucht die Lage der Skizze.
    if (!element.empty()) {
        sketch->addExternal(support, element.c_str(), /*defining*/ false);
        doc->recompute();
    }
    doc->commitTransaction();

    Gui::Document* gdoc = Gui::Application::Instance->getDocument(doc);
    gdoc->setEdit(gdoc->getViewProvider(sketch));
}

/// Wartet nach "Create Sketch" auf einen Klick auf eine Ursprungsebene oder eine ebene Körperfläche.
/// Solange sind die Ursprungsebenen eingeblendet, wie in Fusion. Esc bricht ab.
/// Mit eigenem picked (Bohrung) nur ebene Körperflächen, ohne eingeblendete Ebenen.
class PlanePicker: public QObject, public Gui::SelectionObserver
{
public:
    /// Gewählte Ebene oder Fläche: Objekt, Element ("FaceN", bei Ebenen leer) und Klickpunkt (global)
    using Picked = std::function<void(App::DocumentObject*, const std::string&, const Base::Vector3d&)>;

    PlanePicker(App::Part* root, Picked picked, bool planes)
        : root(root)
        , picked(std::move(picked))
        , planes(planes)
    {
        if (auto view = planes ? originView(root) : nullptr) {
            view->setTemporaryVisibility(Gui::DatumElement::Planes);
        }
        Gui::Selection().clearSelection();
        if (planes) {
            Gui::getMainWindow()->showMessage(T("Select a plane or a planar face for the sketch"));
        }
        qApp->installEventFilter(this);
    }

    ~PlanePicker() override
    {
        if (root.expired() || !planes) {
            return;
        }
        if (auto view = originView(root.get<App::Part>())) {
            view->resetTemporaryVisibility();
        }
    }

    static void start(App::Part* root)
    {
        start(root, [](App::DocumentObject* obj, const std::string& element, const Base::Vector3d&) {
            createSketch(obj, isPlane(obj) ? std::string() : element);
        }, true);
    }
    static void start(App::Part* root, Picked picked, bool planes)
    {
        active.reset();  // erst den alten abbauen, sonst blendet sein Destruktor die Ebenen des neuen wieder aus
        active = std::make_unique<PlanePicker>(root, std::move(picked), planes);
    }
    static void stop()
    {
        active.reset();
    }

private:
    bool eventFilter(QObject*, QEvent* event) override
    {
        if (event->type() == QEvent::KeyPress && static_cast<QKeyEvent*>(event)->key() == Qt::Key_Escape) {
            QTimer::singleShot(0, &stop);  // nicht mitten im eigenen Filter löschen
        }
        return false;
    }

    void onSelectionChanged(const Gui::SelectionChanges& msg) override
    {
        if (msg.Type != Gui::SelectionChanges::AddSelection) {
            return;
        }
        if (Gui::Control().activeDialog()) {  // ein anderes Werkzeug läuft (Abrunden …): dessen Klick, nicht unserer
            QTimer::singleShot(0, &stop);
            return;
        }
        App::DocumentObject* leaf = msg.Object.getSubObject();
        const std::string element = msg.Object.getOldElementName();
        if (!leaf || !((planes && isPlane(leaf)) || isPlanarFace(leaf, element))) {
            return;
        }
        App::DocumentObjectT target(leaf);
        const Base::Vector3d point(msg.x, msg.y, msg.z);
        // Nicht mitten im Selektions-Callback Objekte anlegen und den Edit-Modus starten
        QTimer::singleShot(0, [target, element, point] {
            if (!active) {  // inzwischen abgebrochen oder schon aus einer Vorauswahl skizziert
                return;
            }
            const Picked pick = active->picked;
            stop();
            Gui::Selection().clearSelection();
            if (auto obj = target.getObject()) {
                pick(obj, element, point);
            }
        });
    }

    App::DocumentObjectWeakPtrT root;
    Picked picked;
    bool planes;
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

void toolHint(const QString& tool, const QString& text);

/// Phase 11.6 "Was fehlt noch?" in der Sketch Palette: die Zeile sagt, wie viele Maße fehlen ("Fully defined", wenn
/// nichts), ein Klick ergänzt sie nach Absicht (Design::completeDimensions), in einer Transaktion.
class SketchCompleteCommand: public DesignCommand
{
public:
    SketchCompleteCommand()
        : DesignCommand("Design_SketchComplete", "Complete Dimensions",
                        "Complete Dimensions: add the dimensions the sketch still needs", "Sketcher_Dimension", "",
                        [](App::Document*) { complete(); })
    {}

private:
    static Sketcher::SketchObject* edited()
    {
        Gui::Document* gdoc = Gui::Application::Instance->activeDocument();
        auto vp = gdoc ? dynamic_cast<Gui::ViewProviderDocumentObject*>(gdoc->getInEdit()) : nullptr;
        return vp ? freecad_cast<Sketcher::SketchObject*>(vp->getObject()) : nullptr;
    }

    static void complete()
    {
        Sketcher::SketchObject* sketch = edited();
        if (!sketch) {
            return;
        }
        App::Document* doc = sketch->getDocument();
        doc->openTransaction("Complete Dimensions");
        int dof = 0;
        const int added = Design::completeDimensions(sketch, dof);
        doc->commitTransaction();
        sketch->touch();
        doc->recompute();
        toolHint(T("Complete Dimensions"), dof == 0 ? T("Added %1 dimensions. The sketch is fully defined.").arg(added)
                                                    : T("Added %1 dimensions. Still free: %2 (e.g. construction lines).")
                                                          .arg(added)
                                                          .arg(dof));
    }

protected:
    bool isActive() override
    {
        Sketcher::SketchObject* sketch = edited();
        const int dof = sketch ? sketch->getLastDoF() : 0;
        if (QAction* action = getAction() ? getAction()->action() : nullptr) {
            // Text der Zeile in der Palette (Shell liest paletteText, wenn sich die Aktion ändert)
            const QString text = dof == 1 ? T("1 dimension missing")
                                 : dof > 1 ? T("%1 dimensions missing").arg(dof)
                                           : T("Fully defined");
            if (action->property("paletteText").toString() != text) {
                action->setProperty("paletteText", text);
                action->setToolTip(text + QStringLiteral(". ") + (dof > 0 ? T("Click to add the missing dimensions: symmetric when centered, then "
                                               "sizes, then the distance to the origin")
                                           : T("Nothing missing: every element has its size and place")));
            }
        }
        return sketch && dof > 0;
    }
};

/// Neues Post-it. Auch mitten in der Skizze (man rechnet oft beim Zeichnen), aber nicht in einem Werkzeug-Dialog:
/// dessen Abbrechen nähme das neue Post-it mit zurück.
class NoteCommand: public DesignCommand
{
public:
    NoteCommand()
        : DesignCommand("Design_Note", "Note", "Note: stays on screen, also in sketches. A line ending in = is calculated",
                        "TextDocument", "", run)
    {}

protected:
    bool isActive() override
    {
        if (!hasActiveDocument()) {
            return false;
        }
        auto edit = dynamic_cast<Gui::ViewProviderDocumentObject*>(getActiveGuiDocument()->getInEdit());
        return !Gui::Control().activeDialog() || (edit && edit->getObject()->isDerivedFrom<Sketcher::SketchObject>());
    }

private:
    static void run(App::Document* doc)
    {
        const bool own = !doc->hasPendingTransaction();
        if (own) {
            doc->openTransaction("New Note");
        }
        // leicht versetzt, damit ein neues Post-it das vorige nicht genau verdeckt
        const int shift = 24 * (int(doc->getObjectsOfType(Design::Note::getClassTypeId()).size()) % 6);
        auto note = static_cast<Design::Note*>(doc->addObject("Design::Note", "Note"));
        Design::folder(Design::root(doc, true), "Notes")->addObject(note);
        note->OffsetX.setValue(note->OffsetX.getValue() + shift);
        note->OffsetY.setValue(note->OffsetY.getValue() + shift);
        if (own) {
            doc->recompute();
            doc->commitTransaction();
        }
        else {
            note->purgeTouched();  // in der Skizze kein Neuberechnen: kein "veraltet"-Abzeichen im Browser
        }
    }
};

/// Neues Scribble in der aktiven Komponente, im Ordner "Scribbles" (ohne Transaktion)
App::DocumentObject* newScribble(App::Document* doc)
{
    App::Part* root = activeContainer(doc);
    auto scribble = doc->addObject("Design::Scribble", "Scribble");
    App::DocumentObjectGroup* folder = Design::folder(root, "Scribbles");
    folder->addObject(scribble);
    // im Browser zwischen Skizzen und Notizen: ein neuer Ordner käme sonst hinter einen schon vorhandenen "Notes"
    auto items = root->Group.getValues();
    const auto notes = std::find_if(items.begin(), items.end(), [](App::DocumentObject* obj) {
        std::string name = obj->getNameInDocument();
        name.erase(name.find_last_not_of("0123456789") + 1);
        return obj->isDerivedFrom<App::DocumentObjectGroup>() && name == "Notes";
    });
    const auto mine = std::find(items.begin(), items.end(), folder);
    if (notes < mine && mine != items.end()) {
        items.erase(mine);
        items.insert(notes, folder);
        root->Group.setValues(items);
    }
    return scribble;
}

/// Neues Scribble in der aktiven Komponente; das Zeichenblatt öffnet sich gleich (XY-Ebene, Kamera gerade darauf)
class ScribbleCommand: public DesignCommand
{
public:
    ScribbleCommand()
        : DesignCommand("Design_Scribble", "Scribble",
                        "Scribble: draw freely with a pen tablet or the mouse. Hold still at the end of a stroke to "
                        "straighten it",
                        nullptr, "", run)
    {}

protected:
    bool isActive() override
    {
        return hasActiveDocument() && !Gui::Control().activeDialog() && !getActiveGuiDocument()->getInEdit();
    }

private:
    static void run(App::Document* doc)
    {
        doc->openTransaction("New Scribble");
        auto scribble = newScribble(doc);
        doc->recompute();
        doc->commitTransaction();
        Gui::Document* gdoc = Gui::Application::Instance->getDocument(doc);
        gdoc->setEdit(gdoc->getViewProvider(scribble));
    }
};

/// Idee 1: Rotstift. Ein Korrektur-Scribble mit Transparentpapier, das Blatt quer zur Blickrichtung vor dem Modell,
/// roter Fineliner: aufs Modell schreiben (R2 an eine Kante, M5 auf eine Fläche …), dann "Korrekturen ausführen"
/// Hinweis wie MyCADs übrige Meldungen: Benachrichtigung unter dem ViewCube, verschwindet von selbst
void notify(const QString& text)
{
    Base::Console().send<Base::LogStyle::Notification, Base::IntendedRecipient::User, Base::ContentType::Translated>(
        "MyCAD", "{}", text.toStdString());
}

/// Hinweis eines Werkzeugs ("Skalieren: Wähle erst …") unter dem ViewCube statt als Fenster, das man wegklicken muss
/// (MyStyle: keine Meldungsfenster nur zur Information; echte Fehler bleiben Fenster)
void toolHint(const QString& tool, const QString& text)
{
    notify(tool + QStringLiteral(": ") + text);
}

void startRedPen(App::Document* doc)
{
    auto view = qobject_cast<Gui::View3DInventor*>(Gui::getMainWindow()->activeWindow());
    if (!view) {
        return;
    }
    Gui::View3DInventorViewer* viewer = view->getViewer();
    const SbRotation orientation = viewer->getCameraOrientation();
    float q[4];
    orientation.getValue(q[0], q[1], q[2], q[3]);
    const Base::Rotation rotation(q[0], q[1], q[2], q[3]);
    const Base::Vector3d toEye = rotation.multVec(Base::Vector3d(0, 0, 1));
    Base::BoundBox3d box;
    for (auto obj : doc->getObjectsOfType(Design::Body::getClassTypeId())) {
        auto body = static_cast<Design::Body*>(obj);
        if (body->Visibility.getValue() && !body->Shape.getShape().isNull()) {
            Part::TopoShape shape = body->Shape.getShape();
            shape.setPlacement(Design::componentOf(body)->globalPlacement());
            box.Add(shape.getBoundBox());
        }
    }
    const Base::Vector3d center = box.IsValid() ? box.GetCenter() : Base::Vector3d();
    const double ahead = box.IsValid() ? box.CalcDiagonalLength() / 2 + 1 : 0;  // vor dem Modell, damit die Tinte vorn liegt
    doc->openTransaction("Red Pen");
    auto scribble = static_cast<Design::Scribble*>(newScribble(doc));
    scribble->Label.setValue(T("Corrections").toStdString());
    scribble->Sheet.setValue(Base::Placement(center + toEye * ahead, rotation));
    scribble->Tracing.setValue(true);
    scribble->OnModel.setValue(true);  // die Tinte zeigt sich auf dem Modell, nicht auf dem Blatt davor
    doc->recompute();
    doc->commitTransaction();
    DesignGui::ViewProviderScribble::setTool(DesignGui::ViewProviderScribble::Tool::Pen);
    DesignGui::ViewProviderScribble::setColor(Base::Color(0xFF383CFFu));
    Gui::Document* gdoc = Gui::Application::Instance->getDocument(doc);
    gdoc->setEdit(gdoc->getViewProvider(scribble));
}

/// Gelesene Zeilen des Scribbles als Rotstift-Korrekturen: Tinte zielt entlang der Blatt-Normale aufs Modell
void readCorrections(DesignGui::ViewProviderScribble* vp)
{
    auto scribble = static_cast<Design::Scribble*>(vp->getObject());
    App::Document* doc = scribble->getDocument();
    const auto strokes = scribble->strokes();
    const Base::Matrix4D toSheet = scribble->Sheet.getValue().inverse().toMatrix();
    // Durchgestrichen: ein gerader, eher waagerechter Freihand-Strich auf diesem Blatt, allein (eine geschriebene 1 steht
    // senkrecht, ein Minus gehört zu einer Zeile mit Zahl) heißt "weg". Die Erkennung liest so einen Strich meist gar nicht.
    const auto straightAcross = [&](size_t i) {
        const auto& s = strokes[i];
        if (s.kind != Design::Scribble::Free || s.tool == Design::Scribble::Marker || s.points.size() < 2) {
            return false;
        }
        double path = 0;
        for (size_t k = 1; k < s.points.size(); ++k) {
            path += (s.points[k] - s.points[k - 1]).Length();
        }
        const Base::Vector3d a = toSheet * s.points.front(), b = toSheet * s.points.back();
        return std::abs(a.z) < 1e-3 && std::abs(b.z) < 1e-3 && path > 1e-6 && (b - a).Length() > 0.95 * path
            && std::abs(b.x - a.x) > std::abs(b.y - a.y);
    };
    auto lines = DesignGui::readScribble(scribble);
    std::set<size_t> written;  // Striche, die zu einer gelesenen Zeile mit mehr als einem Strich gehören
    for (const auto& line : lines) {
        if (line.strokes.size() > 1) {
            written.insert(line.strokes.begin(), line.strokes.end());
        }
    }
    std::erase_if(lines, [&](const ScribbleRead::Line& line) { return line.strokes.size() == 1 && straightAcross(line.strokes.front()); });
    for (size_t i = 0; i < strokes.size(); ++i) {
        if (!written.count(i) && straightAcross(i)) {
            ScribbleRead::Line strike;
            strike.text = QStringLiteral("weg");
            strike.strokes = {i};
            lines.push_back(strike);
        }
    }
    std::vector<Design::Correction> corrections;
    for (ScribbleRead::Line& line : lines) {
        if (line.text != QLatin1String("weg") || line.strokes.size() != 1 || !straightAcross(line.strokes.front())) {
            ScribbleRead::correct(line);
        }
        Base::Vector3d center, normal;
        size_t count = 0;
        for (size_t i : line.strokes) {
            for (const auto& p : strokes[i].points) {
                center += p;
                ++count;
            }
            normal = strokes[i].normal;
        }
        if (!count) {
            continue;
        }
        Design::Correction c = Design::readCorrection(doc, line.text.toStdString(), center / double(count), -normal);
        if (c.command.kind != RedPen::Kind::None) {  // Notizen und Skizzen auf dem Blatt bleiben einfach Tinte
            corrections.push_back(c);
        }
    }
    if (corrections.empty()) {  // nur ein Hinweis, kein Meldungsfenster (MyStyle: keine Alerts nur zur Information)
        notify(T("No corrections found. Write for example R2 next to an edge, M5 on a face or +5 on a face."));
        return;
    }
    DesignGui::showCorrections(doc, corrections);
}

/// Befehl im offenen Scribble (Toolbar und Palette des Zeichenmodus)
class ScribbleTool: public DesignCommand
{
public:
    ScribbleTool(const char* name, const char* text, const char* tip, std::function<void(DesignGui::ViewProviderScribble*)> act)
        : DesignCommand(name, text, tip, nullptr, "", [act](App::Document*) {
            if (auto vp = DesignGui::ViewProviderScribble::editing()) {
                act(vp);
            }
        })
    {}

protected:
    bool isActive() override
    {
        return DesignGui::ViewProviderScribble::editing() != nullptr;
    }
};

/// Striche auf dem aktuellen Blatt werden eine Skizze: Linien, Rechtecke und Vielecke zu Linien, Kreise zu Kreisen,
/// Ellipsen zu Ellipsen, Freihand zu B-Splines; Füllflächen bleiben im Scribble. Enden, die aufeinanderliegen (eingerastet), werden koinzident, achsparallele Linien waagerecht/senkrecht.
/// Danach ist das Scribble ausgeblendet und die Skizze offen, zum Bemaßen.
void scribbleToSketch(DesignGui::ViewProviderScribble* vp)
{
    auto scribble = static_cast<Design::Scribble*>(vp->getObject());
    App::Document* doc = scribble->getDocument();
    const Base::Placement sheet = scribble->Sheet.getValue();
    const Base::Placement toSheet = sheet.inverse();
    std::vector<std::unique_ptr<Part::Geometry>> geos;
    const auto segment = [&geos](const Base::Vector3d& a, const Base::Vector3d& b) {
        if ((b - a).Length() > 1e-6) {
            auto line = std::make_unique<Part::GeomLineSegment>();
            line->setPoints(a, b);
            geos.push_back(std::move(line));
        }
    };
    const auto strokes = scribble->strokes();

    // Maße aus der Handschrift: "Ø12" oder "R5" an einem Kreis, "40" an einer Linie werden Bemaßungen statt Geometrie
    struct Dimension
    {
        QChar kind;  ///< Ø, R oder 0 (nur eine Zahl)
        double value;
        Base::Vector3d center;
        double height;  ///< Schrifthöhe, so weit darf das Maß von seiner Geometrie weg sein (mal 4)
    };
    std::vector<Dimension> dimensions;
    std::set<size_t> written;  // Striche der Maße
    static const QRegularExpression number(QString::fromUtf8("^([ØR]?)\\s*(\\d+(?:[.,]\\d+)?)\\s*(?:mm)?$"));
    for (const ScribbleRead::Line& line : DesignGui::readScribble(scribble)) {
        const QRegularExpressionMatch m = number.match(line.text);
        if (!m.hasMatch()) {
            continue;
        }
        Base::BoundBox3d box;
        for (size_t i : line.strokes) {
            for (const auto& p : strokes[i].points) {
                box.Add(toSheet.toMatrix() * p);
            }
        }
        const QString kind = m.captured(1);
        dimensions.push_back({kind.isEmpty() ? QChar() : kind.front(), m.captured(2).replace(QLatin1Char(','), QLatin1Char('.')).toDouble(),
                              box.GetCenter(), box.LengthY()});
        written.insert(line.strokes.begin(), line.strokes.end());
    }

    for (size_t si = 0; si < strokes.size(); ++si) {
        const auto& s = strokes[si];
        if (s.kind == Design::Scribble::Fill || written.count(si)) {
            continue;
        }
        std::vector<Base::Vector3d> pts;
        bool flat = true;
        for (const auto& p : s.points) {
            Base::Vector3d q = toSheet.toMatrix() * p;
            flat = flat && std::abs(q.z) < 1e-3;
            q.z = 0;
            pts.push_back(q);
        }
        if (!flat || pts.size() < 2) {
            continue;  // liegt auf einem anderen Blatt (3D) oder ist nur ein Tupfer
        }
        if (s.kind == Design::Scribble::Line || s.kind == Design::Scribble::Rectangle || s.kind == Design::Scribble::Polygon
            || pts.size() == 2) {
            for (size_t i = 1; i < pts.size(); ++i) {
                segment(pts[i - 1], pts[i]);
            }
        }
        else if (s.kind == Design::Scribble::Circle) {
            Base::Vector3d center;
            for (size_t i = 0; i + 1 < pts.size(); ++i) {  // der letzte Punkt wiederholt den ersten
                center += pts[i] / double(pts.size() - 1);
            }
            auto circle = std::make_unique<Part::GeomCircle>();
            circle->setCenter(center);
            circle->setRadius((pts.front() - center).Length());
            geos.push_back(std::move(circle));
        }
        else if (s.kind == Design::Scribble::Arc && pts.size() > 2) {
            // Kreis durch Anfang, Mitte und Ende; die Skizze will Bögen gegen den Uhrzeigersinn
            const Base::Vector3d a = pts.front(), m = pts[pts.size() / 2], b = pts.back();
            const double d = 2 * (a.x * (m.y - b.y) + m.x * (b.y - a.y) + b.x * (a.y - m.y));
            if (std::abs(d) > 1e-9) {
                const auto sq = [](const Base::Vector3d& p) { return p.x * p.x + p.y * p.y; };
                const Base::Vector3d c((sq(a) * (m.y - b.y) + sq(m) * (b.y - a.y) + sq(b) * (a.y - m.y)) / d,
                                       (sq(a) * (b.x - m.x) + sq(m) * (a.x - b.x) + sq(b) * (m.x - a.x)) / d, 0);
                const auto angle = [&c](const Base::Vector3d& p) { return std::atan2(p.y - c.y, p.x - c.x); };
                double t0 = angle(a), t1 = angle(b);
                const auto ccw = [](double from, double to) { return std::fmod(to - from + 4 * M_PI, 2 * M_PI); };
                if (ccw(t0, angle(m)) > ccw(t0, t1)) {
                    std::swap(t0, t1);  // die Mitte liegt nicht gegen den Uhrzeigersinn zwischen den Enden
                }
                auto arc = std::make_unique<Part::GeomArcOfCircle>();
                arc->setCenter(c);
                arc->setRadius((a - c).Length());
                arc->setRange(t0, t0 + ccw(t0, t1), true);
                geos.push_back(std::move(arc));
            }
        }
        else if (s.kind == Design::Scribble::Ellipse && pts.size() == 97) {
            Base::Vector3d center;
            for (size_t i = 0; i + 1 < pts.size(); ++i) {
                center += pts[i] / double(pts.size() - 1);
            }
            Base::Vector3d major = pts[0] - center, minor = pts[24] - center;  // Halbachsen (Features.h, Kind::Ellipse)
            if (major.Length() < minor.Length()) {
                std::swap(major, minor);
            }
            if (minor.Length() > 1e-6) {
                Handle(Geom_Ellipse) e = new Geom_Ellipse(
                    gp_Ax2(gp_Pnt(center.x, center.y, 0), gp_Dir(0, 0, 1), gp_Dir(major.x, major.y, 0)), major.Length(),
                    minor.Length());
                geos.push_back(std::make_unique<Part::GeomEllipse>(e));
            }
        }
        else {
            // Freihand: vereinfacht und an Knicken geteilt. Gerade Stücke werden Linien, gebogene ein Spline durch ihre
            // wenigen Punkte; ein Spline über alle Punkte schösse mit seinen Polen weit über jede Ecke hinaus
            Base::BoundBox3d box;
            std::vector<ScribbleShapes::P> flat2d;
            for (const auto& p : pts) {
                box.Add(p);
                flat2d.push_back({p.x, p.y});
            }
            for (const auto& piece : ScribbleShapes::pieces(flat2d, std::max(1e-3, 0.01 * box.CalcDiagonalLength()))) {
                if (piece.size() == 2) {
                    segment(Base::Vector3d(piece[0].x, piece[0].y, 0), Base::Vector3d(piece[1].x, piece[1].y, 0));
                    continue;
                }
                std::vector<gp_Pnt> through;
                for (const auto& q : piece) {
                    through.emplace_back(q.x, q.y, 0);
                }
                auto spline = std::make_unique<Part::GeomBSplineCurve>();
                try {
                    spline->interpolate(through);
                    geos.push_back(std::move(spline));
                }
                catch (const Standard_Failure&) {
                }
                catch (const Base::Exception&) {
                }
            }
        }
    }
    if (geos.empty()) {
        toolHint(T("Convert to Sketch"),
                                 T("There are no strokes on this sheet. Only strokes on the current sheet become a "
                                   "sketch."));
        return;
    }

    std::vector<std::unique_ptr<Sketcher::Constraint>> constraints;
    struct End
    {
        int geo;
        Sketcher::PointPos pos;
        Base::Vector3d p;
    };
    std::vector<End> ends;
    for (int i = 0; i < int(geos.size()); ++i) {
        if (auto curve = dynamic_cast<Part::GeomBoundedCurve*>(geos[i].get())) {
            ends.push_back({i, Sketcher::PointPos::start, curve->getStartPoint()});
            ends.push_back({i, Sketcher::PointPos::end, curve->getEndPoint()});
        }
        if (auto line = dynamic_cast<Part::GeomLineSegment*>(geos[i].get())) {
            const Base::Vector3d d = line->getEndPoint() - line->getStartPoint();
            if (std::abs(d.y) < 1e-7 || std::abs(d.x) < 1e-7) {
                auto c = std::make_unique<Sketcher::Constraint>();
                c->Type = std::abs(d.y) < 1e-7 ? Sketcher::Horizontal : Sketcher::Vertical;
                c->First = i;
                constraints.push_back(std::move(c));
            }
        }
    }
    // jedes Maß an die nächste passende Geometrie, jede Geometrie höchstens ein Maß: Ø und R nur an Kreise, eine Zahl
    // allein an einen Kreis (Durchmesser) oder eine Linie (Länge). Text im Kreis zählt als am Kreis.
    std::set<int> dimensioned;
    for (const Dimension& dim : dimensions) {
        int best = -1;
        double bestDist = 4 * dim.height;
        for (int i = 0; i < int(geos.size()); ++i) {
            double dist = INFINITY;
            if (auto circle = dynamic_cast<Part::GeomCircle*>(geos[i].get())) {
                dist = std::max(0.0, (dim.center - circle->getCenter()).Length() - circle->getRadius());
            }
            else if (auto line = dynamic_cast<Part::GeomLineSegment*>(geos[i].get()); line && dim.kind.isNull()) {
                dist = dim.center.DistanceToLineSegment(line->getStartPoint(), line->getEndPoint()).Length();
            }
            if (dist < bestDist && !dimensioned.count(i) && dim.value > 0) {
                bestDist = dist;
                best = i;
            }
        }
        if (best < 0) {
            continue;
        }
        dimensioned.insert(best);
        const bool circle = dynamic_cast<Part::GeomCircle*>(geos[best].get());
        auto c = std::make_unique<Sketcher::Constraint>();
        c->Type = dim.kind == QLatin1Char('R') ? Sketcher::Radius : circle ? Sketcher::Diameter : Sketcher::Distance;
        c->First = best;
        c->setValue(dim.value);
        constraints.push_back(std::move(c));
    }
    std::vector<bool> joined(ends.size(), false);  // jeder Punkt nur an den ersten, der auf ihm liegt
    for (size_t a = 0; a < ends.size(); ++a) {
        for (size_t b = a + 1; b < ends.size(); ++b) {
            if (joined[b] || ends[a].geo == ends[b].geo || (ends[a].p - ends[b].p).Length() > 1e-4) {
                continue;
            }
            joined[b] = true;
            auto c = std::make_unique<Sketcher::Constraint>();
            c->Type = Sketcher::Coincident;
            c->First = ends[a].geo;
            c->FirstPos = ends[a].pos;
            c->Second = ends[b].geo;
            c->SecondPos = ends[b].pos;
            constraints.push_back(std::move(c));
        }
    }

    doc->openTransaction("Convert to Sketch");
    Sketcher::SketchObject* sketch = newSketch(Design::componentOf(scribble));
    sketch->Placement.setValue(sheet);
    std::vector<Part::Geometry*> geoList;
    for (const auto& g : geos) {
        geoList.push_back(g.get());
    }
    sketch->addGeometry(geoList);  // kopiert
    std::vector<Sketcher::Constraint*> constraintList;
    for (const auto& c : constraints) {
        constraintList.push_back(c.get());
    }
    sketch->addConstraints(constraintList);  // kopiert
    scribble->Visibility.setValue(false);
    doc->recompute();
    doc->commitTransaction();

    Gui::Document* gdoc = Gui::Application::Instance->getDocument(doc);
    gdoc->resetEdit();
    const App::DocumentObjectT target(sketch);
    QTimer::singleShot(0, [target] {
        App::DocumentObject* obj = target.getObject();
        if (Gui::Document* g = obj ? Gui::Application::Instance->getDocument(obj->getDocument()) : nullptr) {
            g->setEdit(g->getViewProvider(obj));
        }
    });
}

void createSketchCommand(App::Document* doc)
{
    App::Part* root = activeContainer(doc);
    PlanePicker::stop();  // ein noch wartender Aufruf skizziert sonst ein zweites Mal
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
    // Nichts gewählt: hat die zuletzt erstellte, sichtbare Skizze genau ein Profil, nimm es (wie Fusion). Nicht bei einer
    // anderen Auswahl und nicht, wenn die Skizze nach dem Extrude ausgeblendet ist: sonst extrudierte ein zweiter Klick
    // auf Extrude dasselbe Profil noch einmal
    if (!profiles && selection.empty()) {
        auto all = doc->getObjectsOfType(Design::Profiles::getClassTypeId());
        if (!all.empty()) {
            auto last = static_cast<Design::Profiles*>(all.back());
            if (last->Visibility.getValue() && last->Shape.getShape().countSubShapes(TopAbs_FACE) == 1) {
                profiles = last;
            }
        }
    }
    if (!profiles) {
        toolHint(T(name),
                                 T("Select one or more profiles (closed areas of a sketch) first."));
        return;
    }
    // Ganze Skizze bzw. das einzige Profil: die jetzigen Profile fest übernehmen (wie Fusion), sonst
    // würden später in dieselbe Skizze gezeichnete Formen von diesem Feature mit extrudiert
    if (faces.empty()) {
        const int count = profiles->Shape.getShape().countSubShapes(TopAbs_FACE);
        for (int i = 1; i <= count; ++i) {
            faces.push_back("Face" + std::to_string(i));
        }
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
    toolHint(T("Sweep"),
                             T("Select a profile and the path (sketch lines or body edges)."));
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
        toolHint(T("Loft"),
                                 T("Select two or more profiles from different sketches, in order."));
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
/// size > 0: Radius bzw. Fasenabstand vorgeben (11.10, "Kanten 2 mm abrunden"); all: jede Kante des gewählten oder
/// einzigen sichtbaren Körpers statt der gewählten Kanten
void startDressUp(App::Document* doc, const char* type, const char* name, bool bodyAlone = false, double size = 0,
                  bool all = false)
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
    if (all || (size > 0 && edges.empty())) {
        if (!body) {  // nichts gewählt: der einzige sichtbare Körper
            std::vector<Design::Body*> shown;
            for (auto obj : doc->getObjectsOfType(Design::Body::getClassTypeId())) {
                if (obj->Visibility.getValue()) {
                    shown.push_back(static_cast<Design::Body*>(obj));
                }
            }
            body = shown.size() == 1 ? shown.front() : nullptr;
        }
        edges.clear();
        const int count = body ? body->Shape.getShape().countSubShapes(TopAbs_EDGE) : 0;
        for (int i = 1; i <= count; ++i) {
            edges.push_back("Edge" + std::to_string(i));
        }
    }
    if (!body || (edges.empty() && !bodyAlone) || !Design::stateAtMarker(body)) {
        toolHint(T(name),
                                 T("Select edges (or faces) of a body first."));
        return;
    }

    doc->openTransaction(name);
    auto feature = static_cast<Design::DressUp*>(doc->addObject(type, name));
    Design::componentOf(body)->addObject(feature);
    Design::addToTimeline(feature);
    feature->Edges.setValues(edges);
    if (size > 0) {
        feature->Size.setValue(size);
    }
    Design::attachToBodies(feature, {body});
    doc->recompute();
    startEditing(feature, false, nullptr);
}

/// Idee 4: Passung. Flächen aus einem oder zwei Bodies (Bohrung und Welle, oder ebene Flächen beim 3D-Druck)
void startFit(App::Document* doc)
{
    std::vector<Design::Body*> bodies;
    std::vector<std::string> faces;
    std::vector<long> owners;
    for (auto& sel : Gui::Selection().getSelectionEx()) {
        auto b = freecad_cast<Design::Body*>(sel.getObject());
        if (!b || !Design::stateAtMarker(b)) {
            continue;
        }
        for (const auto& sub : sel.getSubNames()) {
            auto it = std::ranges::find(bodies, b);
            if (sub.rfind("Face", 0) != 0 || (it == bodies.end() && bodies.size() == 2)) {
                continue;
            }
            if (it == bodies.end()) {
                bodies.push_back(b);
                it = bodies.end() - 1;
            }
            faces.push_back(sub);
            owners.push_back(it - bodies.begin());
        }
    }
    if (faces.empty()) {
        toolHint(T("Fit"),
                                 T("Select the faces that fit together, e.g. a hole and its pin."));
        return;
    }
    doc->openTransaction("Fit");
    auto fit = static_cast<Design::Fitting*>(doc->addObject("Design::Fitting", "Fit"));
    Design::componentOf(bodies.front())->addObject(fit);
    Design::addToTimeline(fit);
    fit->Edges.setValues(faces);
    fit->ElementBodies.setValues(owners);
    Design::attachToBodies(fit, bodies);
    doc->recompute();
    startEditing(fit, false, nullptr);
}

/// Idee 4: Schraube hier. Ein Klick auf die Oberseite (oder die Kante einer runden Bohrung darin): von dort in das
/// Teil darunter. Rechnet in den Koordinaten der Komponente und gibt global weiter.
void startFastener(App::Document* doc)
{
    for (auto& sel : Gui::Selection().getSelectionEx()) {
        auto b = freecad_cast<Design::Body*>(sel.getObject());
        if (!b || sel.getSubNames().empty() || !Design::stateAtMarker(b)) {
            continue;
        }
        const std::string sub = sel.getSubNames().front();
        const Part::TopoShape shape = b->Shape.getShape();
        const TopoDS_Shape element = shape.getSubShape(sub.c_str(), true);
        const Base::Placement toGlobal = Design::componentOf(b)->globalPlacement();
        // Fläche und Punkt darauf: geklickter Punkt, bei einer Kreiskante deren Mitte auf der ebenen Nachbarfläche
        TopoDS_Face face;
        gp_Pnt point;
        if (!element.IsNull() && element.ShapeType() == TopAbs_FACE && !sel.getPickedPoints().empty()) {
            face = TopoDS::Face(element);
            Base::Vector3d p = sel.getPickedPoints().front();
            toGlobal.inverse().multVec(p, p);
            point = gp_Pnt(p.x, p.y, p.z);
        }
        else if (!element.IsNull() && element.ShapeType() == TopAbs_EDGE) {
            BRepAdaptor_Curve curve(TopoDS::Edge(element));
            if (curve.GetType() == GeomAbs_Circle) {
                point = curve.Circle().Location();
                TopTools_IndexedDataMapOfShapeListOfShape owners;
                TopExp::MapShapesAndAncestors(shape.getShape(), TopAbs_EDGE, TopAbs_FACE, owners);
                const int i = owners.FindIndex(element);
                for (TopTools_ListOfShape::Iterator it(i ? owners(i) : TopTools_ListOfShape()); it.More(); it.Next()) {
                    if (BRepAdaptor_Surface(TopoDS::Face(it.Value())).GetType() == GeomAbs_Plane) {
                        face = TopoDS::Face(it.Value());
                    }
                }
            }
        }
        if (face.IsNull() || BRepAdaptor_Surface(face).GetType() != GeomAbs_Plane) {
            continue;
        }
        GeomAPI_ProjectPointOnSurf project(point, BRep_Tool::Surface(face));
        double u = 0, v = 0;
        project.LowerDistanceParameters(u, v);
        gp_Pnt onFace;
        gp_Vec normal;
        BRepGProp_Face(face).Normal(u, v, onFace, normal);  // zeigt aus dem Körper heraus
        Base::Vector3d p(point.X(), point.Y(), point.Z()), d(-normal.X(), -normal.Y(), -normal.Z());
        toGlobal.multVec(p, p);
        toGlobal.getRotation().multVec(d, d);
        doc->openTransaction("Screw Here");
        try {
            startEditing(Design::makeFastener(b, p, d), false, nullptr);
        }
        catch (const Base::ValueError& e) {
            doc->abortTransaction();
            toolHint(T("Screw Here"), T(e.what()));
        }
        return;
    }
    toolHint(T("Screw Here"),
                             T("Click the flat top face where the screw goes in, or the edge of a round hole in it."));
}

/// Extrude: Skizzenprofile, oder wie in Fusion eine ebene Körperfläche (zieht sie wie Press Pull heraus)
void startExtrude(App::Document* doc)
{
    bool profile = false, faceOfBody = false, otherPartOfBody = false;
    for (auto& sel : Gui::Selection().getSelectionEx()) {
        App::DocumentObject* obj = sel.getObject();
        profile = profile || obj->isDerivedFrom<Design::Profiles>() || obj->isDerivedFrom<Sketcher::SketchObject>();
        if (obj->isDerivedFrom<Design::Body>()) {
            const auto& subs = sel.getSubNames();
            const bool flat = !subs.empty() && std::ranges::all_of(subs, [obj](const std::string& s) { return isPlanarFace(obj, s); });
            faceOfBody = faceOfBody || flat;
            otherPartOfBody = otherPartOfBody || !flat;
        }
    }
    if (!profile && faceOfBody && !otherPartOfBody) {
        startDressUp(doc, "Design::PressPull", "PressPull");
    }
    else if (!profile && otherPartOfBody) {
        toolHint(T("Extrude"), T("Click a flat face of the body to extrude it."));
    }
    else {
        startProfileFeature(doc, "Design::Extrude", "Extrude");
    }
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

/// Neuer Schritt in der Komponente von near. Körper anderer Komponenten darf er trotzdem ändern (11.8): Feature::applyTool
/// bringt das Werkzeug in deren Koordinaten, die Verweise darauf sind global bzw. versteckt
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
        toolHint(T("Combine"),
                                 T("Select the target body first, then one or more tool bodies."));
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
        w->setWindowTitle(T("Move Component"));
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
        form->addRow(T("X distance"), x);
        form->addRow(T("Y distance"), y);
        form->addRow(T("Z distance"), z);
        form->addRow(T("Rotate around Z"), angle);
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
    // Die neue Komponente ist gleich aktiv (die nächste Skizze landet darin). Eine weitere neue kommt daneben statt
    // hinein; verschachtelt wird nur in eine per Doppelklick aktivierte Komponente.
    static std::string autoActive, autoParent;  // getFullName() der zuletzt selbst aktivierten und ihres Elternteils
    App::Part* parent = activeContainer(doc);
    if (parent->getFullName() == autoActive) {
        if (auto p = freecad_cast<App::Part*>(doc->getObject(autoParent.substr(autoParent.find('#') + 1).c_str()))) {
            parent = p;
        }
    }
    doc->openTransaction("New Component");
    App::Part* part = Design::newComponent(parent);
    doc->recompute();
    doc->commitTransaction();
    if (auto view = Gui::Application::Instance->getDocument(doc)->getActiveView()) {
        view->setActiveObject(part, PARTKEY);
        autoActive = part->getFullName();
        autoParent = parent->getFullName();
    }
}

/// Bezugspunkt und -richtung eines Elements: Ebene/ebene Fläche (Mitte + Normale), Zylinderfläche (Achse),
/// gerade Kante (Mitte + Richtung), Kreiskante (Mittelpunkt + Achse), Punkt

/// Align wie in Fusion: erst ein Element des zu bewegenden Bodies, dann das Ziel. Flächen liegen danach bündig
/// aufeinander, Kanten/Achsen fluchten, Punkte fallen zusammen. Feinjustieren im Move-Dialog.
/// Der Schritt merkt sich beide Bezüge und richtet bei jeder Neuberechnung neu aus (Aufräumliste B6).
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
    Design::Frame from, to;
    if (!body || refs[1].first == body || !Design::frameOf(refs[0].first, refs[0].second, from)
        || !Design::frameOf(refs[1].first, refs[1].second, to)) {
        toolHint(T("Align"),
                                 T("Select a face, edge or point of the body to move, "
                                   "then the face, edge, point or plane to align it to."));
        return;
    }
    auto feature = static_cast<Design::Move*>(addFeature(doc, "Design::Move", "Align", body));
    feature->Label.setValue("Align");
    feature->Alignment.setValue(Design::alignment(from, to));
    // Bezüge merken: der Schritt rechnet die Ausrichtung bei jeder Neuberechnung aus ihnen (folgt Änderungen)
    feature->AlignFrom.setValue(refs[0].second);
    feature->AlignTo.setValue(refs[1].first, std::vector<std::string> {refs[1].second});
    modifyBodies(feature, {body});
    doc->recompute();
    startEditing(feature, false, nullptr);
}

/// Split Body: den Body und die Ebene oder Fläche, an der geteilt wird (beliebige Reihenfolge); jedes weitere Teil wird ein Body
void startSplit(App::Document* doc)
{
    Design::Body* body = nullptr;
    App::DocumentObject* tool = nullptr;
    std::string element;
    auto selection = Gui::Selection().getSelectionEx();
    for (auto& sel : selection) {
        App::DocumentObject* obj = sel.getObject();
        const auto& names = sel.getSubNames();
        // ein Klick auf den Body in der Ansicht wählt eine Fläche: als Erstes gewählt (Werkzeug danach) oder nach dem
        // Werkzeug zählt er als der Body
        const bool first = &sel == &selection.front() && selection.size() > 1;
        if (!body && freecad_cast<Design::Body*>(obj) && (names.empty() || first || tool)) {
            body = static_cast<Design::Body*>(obj);
        }
        else if (!tool && (isPlane(obj) || (names.size() == 1 && names.front().rfind("Face", 0) == 0))) {
            tool = obj;
            element = names.empty() ? std::string() : names.front();
            stableRef(tool, element);
        }
    }
    if (!body || !tool || tool == body) {
        toolHint(T("Split Body"),
                                 T("Select the body to split and a plane or face to split it with."));
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
        QMessageBox::warning(Gui::getMainWindow(), T("Split Body"),
                             T(feature->getStatusString()));
        doc->abortTransaction();
        doc->recompute();
        return;
    }
    doc->commitTransaction();
    Gui::Selection().clearSelection();
}

/// Rib: einen Body und Skizzenlinien wählen
void startRib(App::Document* doc, long mode = 0)
{
    Design::Body* body = nullptr;
    App::DocumentObject* sketch = nullptr;
    std::vector<std::string> lines;
    for (auto& sel : Gui::Selection().getSelectionEx()) {
        App::DocumentObject* obj = sel.getObject();
        if (auto b = freecad_cast<Design::Body*>(obj)) {
            body = b;
        }
        else if (obj->isDerivedFrom<Sketcher::SketchObject>()) {
            sketch = obj;
            for (const auto& sub : sel.getSubNames()) {
                if (sub.rfind("Edge", 0) == 0) {
                    lines.push_back(sub);
                }
            }
        }
    }
    if (!body || !sketch || !Design::stateAtMarker(body)) {
        toolHint(T(mode ? "Web" : "Rib"),
                                 mode ? T("Select the body and the sketch lines of the web (or the whole sketch).")
                                      : T("Select the body and the sketch lines of the rib (or the whole sketch)."));
        return;
    }
    auto feature = static_cast<Design::Rib*>(addFeature(doc, "Design::Rib", mode ? "Web" : "Rib", body));
    feature->Mode.setValue(mode);
    feature->Curves.setValue(sketch, lines);
    modifyBodies(feature, {body});
    doc->recompute();
    startEditing(feature, false, nullptr);
}

/// Flächen eines Bodies + Bezug (zuletzt gewählt): Replace Face (Ziel), Split Face (Werkzeug).
/// Ohne Einstellungen: wird sofort berechnet, Fehler zeigt eine Meldung.
void startFaceTool(App::Document* doc, const char* type, const char* name, const char* refProperty, const char* hint)
{
    std::vector<std::pair<App::DocumentObject*, std::string>> refs;
    for (auto& sel : Gui::Selection().getSelectionEx()) {
        const auto& names = sel.getSubNames();
        if (names.empty()) {
            refs.emplace_back(sel.getObject(), std::string());
        }
        for (const auto& n : names) {
            refs.emplace_back(sel.getObject(), n);
        }
    }
    auto body = refs.size() >= 2 ? freecad_cast<Design::Body*>(refs.front().first) : nullptr;
    std::vector<std::string> faces;
    for (size_t i = 0; body && i + 1 < refs.size(); ++i) {
        if (refs[i].first == body && refs[i].second.rfind("Face", 0) == 0) {
            faces.push_back(refs[i].second);
        }
    }
    if (!body || faces.empty() || !Design::stateAtMarker(body)) {
        toolHint(T(name), T(hint));
        return;
    }
    App::DocumentObject* ref = refs.back().first;
    std::string refSub = refs.back().second;
    stableRef(ref, refSub);
    doc->openTransaction(name);
    auto feature = static_cast<Design::DressUp*>(doc->addObject(type, name));
    Design::componentOf(body)->addObject(feature);
    Design::addToTimeline(feature);
    feature->Edges.setValues(faces);
    static_cast<App::PropertyLinkSub*>(feature->getPropertyByName(refProperty))
        ->setValue(ref, refSub.empty() ? std::vector<std::string>() : std::vector<std::string> {refSub});
    Design::attachToBodies(feature, {body});
    doc->recompute();
    if (feature->isError()) {
        QMessageBox::warning(Gui::getMainWindow(), T(name), T(feature->getStatusString()));
        doc->abortTransaction();
        doc->recompute();
        return;
    }
    doc->commitTransaction();
    Gui::Selection().clearSelection();
}

/// Emboss: Profile (Skizzenflächen oder Text) und die Fläche des Bodies, auf die geprägt wird
void startEmboss(App::Document* doc)
{
    Design::Profiles* profiles = nullptr;
    std::vector<std::string> areas;
    Design::Body* body = nullptr;
    std::vector<std::string> faces;
    for (auto& sel : Gui::Selection().getSelectionEx()) {
        App::DocumentObject* obj = sel.getObject();
        if (auto p = freecad_cast<Design::Profiles*>(obj)) {
            profiles = p;
            for (const auto& n : sel.getSubNames()) {
                areas.push_back(n);
            }
        }
        else if (obj->isDerivedFrom<Sketcher::SketchObject>()) {
            profiles = Design::Profiles::forSketch(obj);
        }
        else if (auto b = freecad_cast<Design::Body*>(obj)) {
            body = b;
            for (const auto& n : sel.getSubNames()) {
                if (n.rfind("Face", 0) == 0) {
                    faces.push_back(n);
                }
            }
        }
    }
    if (!profiles || !body || faces.empty() || !Design::stateAtMarker(body)) {
        toolHint(T("Emboss"),
                                 T("Select the profiles or text of a sketch and the face to emboss on."));
        return;
    }
    doc->openTransaction("Emboss");
    auto feature = static_cast<Design::Emboss*>(doc->addObject("Design::Emboss", "Emboss"));
    Design::componentOf(body)->addObject(feature);
    Design::addToTimeline(feature);
    feature->Profile.setValue(profiles, areas);
    feature->Edges.setValues(faces);
    Design::attachToBodies(feature, {body});
    doc->recompute();
    startEditing(feature, false, nullptr);
}

/// Joint wie in Fusion: zuerst ein Element der Komponente, die sich bewegen soll (Fläche, Kante, Bohrung, Punkt),
/// dann die Gegenstelle an einer anderen Komponente oder in der Wurzel
void startJoint(App::Document* doc)
{
    std::vector<std::pair<App::DocumentObject*, std::string>> refs;
    for (auto& sel : Gui::Selection().getSelectionEx()) {
        const auto& names = sel.getSubNames();
        if (names.empty()) {
            refs.emplace_back(sel.getObject(), std::string());
        }
        for (const auto& n : names) {
            refs.emplace_back(sel.getObject(), n);
        }
    }
    App::Part* root = Design::root(doc, true);
    App::Part* moving = refs.size() == 2 ? Design::componentOf(refs[0].first) : nullptr;
    QString problem;
    if (!moving) {
        problem = T("Select a face, edge, hole or point on the component to move, then the place to join it to.");
    }
    else if (moving == root) {
        problem = T("The first selection must belong to a component (the design itself stays in place).");
    }
    else if (Design::componentOf(refs[1].first) == moving) {
        problem = T("The second selection must be on another component.");
    }
    if (!problem.isEmpty()) {
        toolHint(T("Joint"), problem);
        return;
    }
    doc->openTransaction("Joint");
    auto joint = static_cast<Design::Joint*>(doc->addObject("Design::Joint", "Joint"));
    Design::folder(root, "Joints")->addObject(joint);
    joint->Moving.setValue(moving);
    auto sub = [](const std::string& s) { return s.empty() ? std::vector<std::string>() : std::vector<std::string> {s}; };
    joint->Origin1.setValue(refs[0].first, sub(refs[0].second));
    joint->Origin2.setValue(refs[1].first, sub(refs[1].second));
    doc->recompute();
    // die Lage folgt dem ersten Joint der Komponente; ein zweiter schließt eine Kette (der Solver rechnet sie zusammen)
    if (!moving->getExpression(App::ObjectIdentifier(moving->Placement)).expression) {
        moving->setExpression(App::ObjectIdentifier(moving->Placement),
                              std::shared_ptr<App::Expression>(
                                  App::Expression::parse(moving, std::string(joint->getNameInDocument()) + ".Result").release()));
    }
    doc->recompute();
    Gui::Selection().clearSelection();
    Gui::Document* gdoc = Gui::Application::Instance->getDocument(doc);
    auto vp = static_cast<DesignGui::ViewProviderJoint*>(gdoc->getViewProvider(joint));
    vp->createMode = true;
    gdoc->setEdit(vp);
}

/// Scale: gewählte Bodies
void startScale(App::Document* doc)
{
    const auto bodies = selectedBodies();
    if (bodies.empty()) {
        toolHint(T("Scale"),
                                 T("Select one or more bodies first."));
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
    if (bodies.empty()) {
        toolHint(T("Move"),
                                 T("Select one or more bodies or a component first."));
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
        toolHint(T("Mirror"),
                                 T("Select one or more bodies first."));
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

/// Features und Skizzen aus der Timeline löschen (Kette wird neu verbunden), Bodies samt ihrer Schritte, alles andere
/// wie gewohnt
void deleteSelected(App::Document* doc)
{
    std::vector<App::DocumentObjectT> items;
    for (auto obj : Gui::Selection().getObjectsOfType(App::DocumentObject::getClassTypeId())) {
        if (obj->isDerivedFrom<Design::Feature>() || obj->isDerivedFrom<Sketcher::SketchObject>()
            || obj->isDerivedFrom<Design::Body>()) {
            items.emplace_back(obj);
        }
    }
    if (items.empty()) {
        Gui::Application::Instance->commandManager().runCommandByName("Std_Delete");
        return;
    }
    // Phase 11.2: hängt außer dem Gewählten etwas daran, vorher sagen was, wie SolidWorks (Rückgängig ginge, aber
    // man soll es nicht erst hinterher merken). Ohne Folgen wird still gelöscht wie bisher.
    Design::DeletionImpact impact;
    std::vector<App::DocumentObject*> chosen;
    for (const auto& item : items) {
        if (auto obj = item.getObject()) {
            chosen.push_back(obj);
        }
    }
    for (auto obj : chosen) {
        const auto one = Design::deletionImpact(obj);
        for (auto [from, to] : {std::pair {&one.bodies, &impact.bodies}, std::pair {&one.sketches, &impact.sketches},
                                std::pair {&one.broken, &impact.broken}}) {
            for (auto o : *from) {
                if (std::ranges::find(chosen, o) == chosen.end() && std::ranges::find(*to, o) == to->end()) {
                    to->push_back(o);
                }
            }
        }
    }
    if (!impact.empty()) {
        const auto names = [](const std::vector<App::DocumentObject*>& list) {
            QStringList out;
            for (auto o : list) {
                out << QString::fromUtf8(o->Label.getValue());
            }
            return out.join(QStringLiteral(", "));
        };
        QStringList lines;
        if (!impact.bodies.empty()) {
            lines << T("Goes along: %1").arg(names(impact.bodies));
        }
        if (!impact.sketches.empty()) {
            lines << T("Loses the face it lies on and stays where it is: %1").arg(names(impact.sketches));
        }
        if (!impact.broken.empty()) {
            lines << T("Loses its input and shows an error: %1").arg(names(impact.broken));
        }
        QMessageBox box(Gui::getMainWindow());
        box.setObjectName(QStringLiteral("DeleteImpact"));
        box.setWindowTitle(T("Delete %1?").arg(names(chosen)));
        box.setText(lines.join(QLatin1Char('\n')));
        QPushButton* remove = box.addButton(T("Delete"), QMessageBox::DestructiveRole);
        box.setDefaultButton(box.addButton(QMessageBox::Cancel));
        box.exec();
        if (box.clickedButton() != remove) {
            return;
        }
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

/// layers: je Geometrie die Ebene (Layer) aus der DXF-Datei, leer ohne Ebene
Geometries dxfGeometry(const std::string& file, std::string& error, std::vector<std::string>& layers)
{
    // FreeCADs DXF-Leser legt Part-Objekte an: in ein unsichtbares Hilfsdokument lesen und die Kanten übernehmen
    App::Document* tmp = App::GetApplication().newDocument("MyCADImport", "MyCADImport", {false, true});
    const std::string name = tmp->getName();
    // eigene Optionen: Ebenen ohne das (fehlende) Draft-Modul, nur als OriginalLayer je Objekt für die Ebenen-Wahl;
    // Farben bräuchten Draft
    const char* options = "User parameter:BaseApp/Preferences/Mod/Design/DXF";
    auto grp = App::GetApplication().GetParameterGroupByPath(options);
    grp->SetBool("dxfUseDraftVisGroups", true);
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
        auto layer = freecad_cast<App::PropertyString*>(obj->getPropertyByName("OriginalLayer"));
        for (const auto& edge : static_cast<Part::Feature*>(obj)->Shape.getShape().getSubTopoShapes(TopAbs_EDGE)) {
            if (auto geo = sketchGeometry(TopoDS::Edge(edge.getShape()))) {
                result.push_back(std::move(geo));
                layers.emplace_back(layer ? layer->getValue() : "");
            }
        }
    }
    App::GetApplication().closeDocument(name.c_str());
    if (result.empty() && error.empty()) {
        error = "The DXF file contains no supported geometry.";
    }
    return result;
}

/// Ein Element für die Bereinigung (Art, Lage, Größe)
DxfCleanup::Piece cleanupPiece(const Part::Geometry* geo)
{
    DxfCleanup::Piece p;
    if (auto line = freecad_cast<const Part::GeomLineSegment*>(geo)) {
        const Base::Vector3d s = line->getStartPoint(), e = line->getEndPoint();
        p.kind = DxfCleanup::Piece::Kind::Line;
        p.a = {s.x, s.y};
        p.b = {e.x, e.y};
    }
    else if (auto arc = freecad_cast<const Part::GeomArcOfCircle*>(geo)) {
        p.kind = DxfCleanup::Piece::Kind::Arc;
        p.a = {arc->getCenter().x, arc->getCenter().y};
        p.r = arc->getRadius();
        arc->getRange(p.start, p.end, true);
    }
    else if (auto circle = freecad_cast<const Part::GeomCircle*>(geo)) {
        p.kind = DxfCleanup::Piece::Kind::Circle;
        p.a = {circle->getCenter().x, circle->getCenter().y};
        p.r = circle->getRadius();
    }
    else {
        p.size = Part::TopoShape(geo->toShape()).getBoundBox().CalcDiagonalLength();
    }
    return p;
}

/// DXF einfügen wie in Fusion mit Rückfrage: Größe (falsche Einheit fällt hier auf), Ebenen, Winzlinge und Doppelte.
/// Behält in geos nur, was übernommen wird, skaliert es; false = abgebrochen
/// H4: ein Text einer DXF-Datei: Inhalt, Einfügepunkt (links unten), Höhe, Drehung in Grad
struct DxfText
{
    QString text;
    Base::Vector3d at;
    double height = 0;
    double angle = 0;
};

/// H4: Texte einer DXF-Datei (TEXT, MTEXT; Gruppencodes 1/3 Inhalt, 10/20 Punkt, 40 Höhe, 50 Drehung). FreeCADs
/// Leser legt Texte nur über das Draft-Modul an, das MyCAD nicht hat; ohne diesen Blick gingen sie still verloren.
std::vector<DxfText> dxfTexts(const QString& file)
{
    std::vector<DxfText> texts;
    QFile f(file);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return texts;
    }
    QString kind;
    DxfText cur;
    const auto flush = [&] {
        if ((kind == QLatin1String("TEXT") || kind == QLatin1String("MTEXT")) && !cur.text.isEmpty()) {
            // MTEXT-Formate (\fArial|b0; \P {…}) weg
            cur.text.replace(QRegularExpression(QStringLiteral("\\\\[A-Za-z][^;]*;|[{}]|\\\\P")), QStringLiteral(" "));
            cur.text = cur.text.simplified();
            if (!cur.text.isEmpty()) {
                texts.push_back(cur);
            }
        }
        cur = DxfText();
    };
    while (!f.atEnd()) {
        const QString code = QString::fromUtf8(f.readLine()).trimmed();
        const QString value = QString::fromUtf8(f.readLine()).trimmed();
        if (code == QLatin1String("0")) {
            flush();
            kind = value;
        }
        else if (code == QLatin1String("1") || code == QLatin1String("3")) {
            cur.text += value;  // 3: Vorlauf langer MTEXTe, 1: der Rest
        }
        else if (code == QLatin1String("10")) {
            cur.at.x = value.toDouble();
        }
        else if (code == QLatin1String("20")) {
            cur.at.y = value.toDouble();
        }
        else if (code == QLatin1String("40")) {
            cur.height = value.toDouble();
        }
        else if (code == QLatin1String("50")) {
            cur.angle = value.toDouble();
        }
    }
    flush();
    return texts;
}

/// Schrift für übernommene Texte: wie das Text-Werkzeug der Skizze Inter, sonst eine schlichte Sans; leer ohne Schrift
std::string dxfTextFont()
{
    const QMap<QString, QString> fonts = SketcherGui::findAvailableFontFiles();
    for (const char* want : {"Inter-Regular", "Inter", "DejaVuSans", "NotoSans-Regular"}) {
        for (auto it = fonts.begin(); it != fonts.end(); ++it) {
            if (it.key().compare(QString::fromUtf8(want), Qt::CaseInsensitive) == 0) {
                return it.value().toStdString();
            }
        }
    }
    for (auto it = fonts.begin(); it != fonts.end(); ++it) {
        if (it.key().endsWith(QLatin1String("Sans"), Qt::CaseInsensitive)) {
            return it.value().toStdString();
        }
    }
    return fonts.isEmpty() ? std::string() : fonts.first().toStdString();
}

/// Texte als Skizzentext wie das Text-Werkzeug: Griff-Linie vom Einfügepunkt quer zur Grundlinie, so lang wie die
/// Texthöhe, dazu die Text-Bedingung. Als Hilfsgeometrie: Beschriftung soll sichtbar sein, aber kein Profil werden
/// (Buchstaben-Löcher in der Platte)
void addDxfTexts(Sketcher::SketchObject* sketch, const std::vector<DxfText>& texts, const std::string& font)
{
    const auto hex = [](const QString& s) { return QString::fromLatin1(s.toUtf8().toHex()).toStdString(); };
    for (const DxfText& t : texts) {
        if (t.height <= 0) {
            continue;
        }
        const double r = t.angle * M_PI / 180;
        const Base::Vector3d up(-std::sin(r) * t.height, std::cos(r) * t.height, 0);
        std::ostringstream py;
        py << std::setprecision(17) << "import FreeCAD as App, Part, Sketcher\n"
           << "sk = App.getDocument('" << sketch->getDocument()->getName() << "').getObject('" << sketch->getNameInDocument() << "')\n"
           << "t = bytes.fromhex('" << hex(t.text) << "').decode()\n"
           << "f = bytes.fromhex('" << hex(QString::fromStdString(font)) << "').decode()\n"
           << "h = sk.addGeometry(Part.LineSegment(App.Vector(" << t.at.x << ", " << t.at.y << ", 0), App.Vector("
           << t.at.x + up.x << ", " << t.at.y + up.y << ", 0)), True)\n"
           << "sk.addConstraint(Sketcher.Constraint('Text', [h, 0], t, f, True))\n"
           << "sk.setTextAndFont(len(sk.Constraints) - 1, t, f, True, True)\n";
        try {
            Base::Interpreter().runString(py.str().c_str());
        }
        catch (const Base::Exception& e) {
            Base::Console().warning("DXF text not inserted: %s\n", e.what());
        }
    }
}

bool reviewDxf(Geometries& geos, const std::vector<std::string>& layers, const QString& name,
               std::vector<DxfText>* texts = nullptr, bool canInsertTexts = false)
{
    std::vector<DxfCleanup::Piece> pieces;
    std::vector<Base::BoundBox3d> boxes;
    for (const auto& g : geos) {
        pieces.push_back(cleanupPiece(g.get()));
        boxes.push_back(Part::TopoShape(g->toShape()).getBoundBox());
    }
    std::map<std::string, int> perLayer;
    for (const auto& l : layers) {
        ++perLayer[l];
    }
    constexpr double tolerance = 0.001;  // 1 µm: kleiner zeichnet und druckt nichts

    QDialog dlg(Gui::getMainWindow());
    dlg.setWindowTitle(T("Insert DXF"));
    dlg.setMinimumWidth(440);  // Zusammenfassung mit Größe in einer Zeile
    auto lay = new QVBoxLayout(&dlg);
    auto summary = new QLabel;
    summary->setWordWrap(true);
    lay->addWidget(summary);
    if (texts && !texts->empty()) {
        QStringList shown;
        for (size_t i = 0; i < texts->size() && i < 3; ++i) {
            shown << QStringLiteral("„%1“").arg((*texts)[i].text);
        }
        if (texts->size() > 3) {
            shown << QStringLiteral("…");
        }
        const QString what = canInsertTexts ? T("%1 texts become construction text in the sketch: %2")
                                            : T("%1 texts are not inserted, only the drawing: %2");
        auto note = new QLabel(what.arg(texts->size()).arg(shown.join(QStringLiteral(", "))));
        note->setObjectName(QStringLiteral("DxfTexts"));
        note->setWordWrap(true);
        lay->addWidget(note);
    }
    auto scaleRow = new QHBoxLayout;
    scaleRow->addWidget(new QLabel(T("Drawn in")));
    auto scale = new QComboBox;
    scale->setAccessibleName(T("Drawn in"));
    const std::array<std::pair<QString, double>, 4> scales {std::pair {T("Units of the file"), 1.0},
                                                            std::pair {T("Inches"), 25.4},
                                                            std::pair {T("Centimeters"), 10.0},
                                                            std::pair {T("Meters"), 1000.0}};
    for (const auto& [text, factor] : scales) {
        scale->addItem(text, factor);
    }
    scaleRow->addWidget(scale, 1);
    lay->addLayout(scaleRow);
    std::vector<std::pair<QCheckBox*, std::string>> layerBoxes;  // je Ebene ein Haken wie die Optionen unten
    if (perLayer.size() > 1) {
        lay->addWidget(new QLabel(T("Layers")));
        auto inner = new QWidget;
        inner->setAccessibleName(T("Layers"));
        auto column = new QVBoxLayout(inner);
        column->setContentsMargins(0, 0, 0, 0);
        for (const auto& [layer, count] : perLayer) {
            auto box = new QCheckBox(T("%1 (%2)").arg(layer.empty() ? T("No layer") : QString::fromStdString(layer)).arg(count));
            box->setChecked(true);
            column->addWidget(box);
            layerBoxes.emplace_back(box, layer);
        }
        if (perLayer.size() > 6) {  // viele Ebenen: scrollen statt eines hohen Dialogs
            auto scroll = new QScrollArea;
            scroll->setWidget(inner);
            scroll->setWidgetResizable(true);
            scroll->setFrameShape(QFrame::NoFrame);
            scroll->setMaximumHeight(6 * inner->sizeHint().height() / int(perLayer.size()));
            lay->addWidget(scroll);
        }
        else {
            lay->addWidget(inner);
        }
    }
    lay->addSpacing(6);
    auto cleanupTitle = new QLabel(T("Clean up"));
    lay->addWidget(cleanupTitle);
    auto tiny = new QCheckBox;
    auto duplicates = new QCheckBox;
    for (auto option : {tiny, duplicates}) {
        option->setChecked(true);
        lay->addWidget(option);
    }
    auto buttons = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
    buttons->button(QDialogButtonBox::Ok)->setText(T("Insert"));
    lay->addWidget(buttons);
    QObject::connect(buttons, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    QObject::connect(buttons, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);

    // gewählte Ebenen → Elemente; Zähler und Größe folgen der Wahl
    std::vector<bool> keep;
    const auto update = [&] {
        std::set<std::string> chosen;
        for (const auto& [box, layer] : layerBoxes) {
            if (box->isChecked()) {
                chosen.insert(layer);
            }
        }
        std::vector<DxfCleanup::Piece> inLayers;
        std::vector<size_t> index;
        for (size_t i = 0; i < pieces.size(); ++i) {
            if (layerBoxes.empty() || chosen.contains(layers[i])) {
                inLayers.push_back(pieces[i]);
                index.push_back(i);
            }
        }
        const auto all = DxfCleanup::cleanup(inLayers, tolerance, true, true);
        const auto chosenResult = DxfCleanup::cleanup(inLayers, tolerance, tiny->isChecked(), duplicates->isChecked());
        keep.assign(pieces.size(), false);
        int count = 0;
        Base::BoundBox3d box;  // Größe dessen, was eingefügt wird
        for (size_t k = 0; k < index.size(); ++k) {
            keep[index[k]] = chosenResult.keep[k];
            if (chosenResult.keep[k]) {
                ++count;
                box.Add(boxes[index[k]]);
            }
        }
        tiny->setText(T("Remove %1 tiny pieces (under 0.001 mm)").arg(all.tiny));
        tiny->setVisible(all.tiny > 0);
        duplicates->setText(T("Merge %1 duplicates (drawn twice)").arg(all.duplicates));
        duplicates->setVisible(all.duplicates > 0);
        cleanupTitle->setVisible(all.tiny > 0 || all.duplicates > 0);
        const double f = scale->currentData().toDouble();
        const QString size = box.IsValid()
            ? T("%1 × %2 mm").arg(QLocale().toString(box.LengthX() * f, 'f', 1), QLocale().toString(box.LengthY() * f, 'f', 1))
            : QString();
        summary->setText(T("“%1”: %2 elements, %3").arg(name).arg(count).arg(size));
        buttons->button(QDialogButtonBox::Ok)->setEnabled(count > 0);
    };
    update();
    QObject::connect(scale, &QComboBox::currentIndexChanged, &dlg, [&] { update(); });
    QObject::connect(tiny, &QCheckBox::toggled, &dlg, [&] { update(); });
    QObject::connect(duplicates, &QCheckBox::toggled, &dlg, [&] { update(); });
    for (const auto& [box, layer] : layerBoxes) {
        QObject::connect(box, &QCheckBox::toggled, &dlg, [&] { update(); });
    }
    if (dlg.exec() != QDialog::Accepted) {
        return false;
    }
    const double f = scale->currentData().toDouble();
    if (texts) {
        for (DxfText& t : *texts) {  // Texte im selben Maßstab wie die Zeichnung
            t.at *= f;
            t.height *= f;
        }
    }
    Geometries kept;
    for (size_t i = 0; i < geos.size(); ++i) {
        if (keep[i]) {
            if (f != 1.0) {
                geos[i]->scale(Base::Vector3d(), f);
            }
            kept.push_back(std::move(geos[i]));
        }
    }
    geos = std::move(kept);
    return true;
}

/// STEP: Timeline-Eintrag "Import" mit je einem Body pro Solid; DXF/SVG: Skizze auf der XY-Ebene
/// Phase 11.9: Maßstab erfragen und nachzeichnen. Auf Rasterpapier nur die Kästchengröße (meist 5 mm), sonst die Breite
void askAndTrace(const QString& file)
{
    if (DesignGui::photoSheet(file.toStdString())) {  // ganzes A4-Blatt im Bild: Maßstab und Perspektive von selbst
        DesignGui::photoToSketch(file.toStdString(), 0, 0);
        return;
    }
    bool ok = false;
    if (DesignGui::photoGrid(file.toStdString()) > 0) {
        const double square = QInputDialog::getDouble(Gui::getMainWindow(), T("Photo to Sketch"),
                                                      T("Grid paper found. How big is one square (mm)?"), 5, 0.5, 100, 1, &ok);
        if (ok) {
            DesignGui::photoToSketch(file.toStdString(), 0, square);
        }
        return;
    }
    const double width = QInputDialog::getDouble(Gui::getMainWindow(), T("Photo to Sketch"),
                                                 T("How wide is the part, left to right in the photo (mm)?"), 100, 1, 10000,
                                                 1, &ok);
    if (ok) {
        DesignGui::photoToSketch(file.toStdString(), width);
    }
}

/// 12.1: STL, 3MF oder OBJ als Körper (DesignMesh: Ebenen als eine Fläche, Bohrungen als echte Zylinder). Fehler als
/// übersetzter Satz; der Weg über eine BREP-Datei spart die Python-Bindung von Part hier
Part::TopoShape meshBody(const QString& file)
{
    const auto py = [](const QString& s) { return "bytes.fromhex('" + QString::fromLatin1(s.toUtf8().toHex()).toStdString() + "').decode()"; };
    const QString brep = QDir::temp().filePath(QStringLiteral("mycad-mesh-%1.brep").arg(QCoreApplication::applicationPid()));
    std::string error;
    {
        struct Busy  // Warte-Cursor, auch wenn Python eine Ausnahme wirft
        {
            Busy()
            {
                QApplication::setOverrideCursor(Qt::WaitCursor);
            }
            ~Busy()
            {
                QApplication::restoreOverrideCursor();
            }
        } busy;
        Base::PyGILStateLocker lock;
        error = Base::Interpreter().runStringWithKey(("import DesignMesh\n_r = ''\ntry:\n    DesignMesh.solid(DesignMesh.read("
                                                      + py(file) + ")).exportBrep(" + py(brep)
                                                      + ")\nexcept DesignMesh.MeshError as e:\n    _r = e.key()\n")
                                                         .c_str(),
                                                     "_r");
    }
    if (!error.empty()) {
        const QStringList parts = QString::fromStdString(error).split(QChar(0x1f));
        QString text = T(parts.first().toUtf8().constData());
        for (int i = 1; i < parts.size(); ++i) {
            text = text.arg(parts[i]);
        }
        throw Base::RuntimeError(text.toStdString());
    }
    Part::TopoShape shape;
    shape.read(brep.toUtf8().constData());
    QFile::remove(brep);
    return shape;
}

void importFile(App::Document* doc)
{
    // startet im zuletzt benutzten Ordner, sonst im Projektordner wie Öffnen und Speichern
    ParameterGrp::handle params = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD");
    const QString file = QFileDialog::getOpenFileName(
        Gui::getMainWindow(), T("Insert"),
        QString::fromStdString(params->GetASCII("InsertFolder", Gui::Shell::projectsFolder().toStdString().c_str())),
        T("CAD files, meshes and photos (*.step *.stp *.stl *.3mf *.obj *.dxf *.svg *.png *.jpg *.jpeg *.bmp *.webp);;"
          "STEP (*.step *.stp);;Mesh (*.stl *.3mf *.obj);;DXF (*.dxf);;SVG (*.svg);;Photo to Sketch (*.png *.jpg *.jpeg *.bmp *.webp)")
    );
    if (file.isEmpty()) {
        return;
    }
    params->SetASCII("InsertFolder", QFileInfo(file).absolutePath().toStdString());
    const QString stem = QFileInfo(file).completeBaseName();
    const QString suffix = QFileInfo(file).suffix().toLower();
    // Phase 11.9: ein Foto wird zur Skizze nachgezeichnet (Breite fragen, Maßstab daraus)
    if (QStringList {QStringLiteral("png"), QStringLiteral("jpg"), QStringLiteral("jpeg"), QStringLiteral("bmp"),
                     QStringLiteral("webp")}
            .contains(suffix)) {
        askAndTrace(file);
        return;
    }
    App::Part* comp = activeContainer(doc);
    std::string error;
    try {
        const bool mesh = QStringList {QStringLiteral("stl"), QStringLiteral("3mf"), QStringLiteral("obj")}.contains(suffix);
        if (suffix == QLatin1String("step") || suffix == QLatin1String("stp") || mesh) {
            Part::TopoShape shape;
            if (mesh) {
                shape = meshBody(file);
            }
            else {
                shape.read(file.toUtf8().constData());
            }
            const auto pieces = Design::Import::pieces(shape);
            if (pieces.empty()) {
                throw Base::RuntimeError("The STEP file contains no geometry.");
            }
            doc->openTransaction("Insert");
            auto feature = static_cast<Design::Import*>(doc->addObject("Design::Import", "Import"));
            // der Körper trägt den Dateinamen; gleiche Namen machte FreeCAD zu "Teil001"
            feature->Label.setValue(T("Inserted %1").arg(stem).toStdString());
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
            std::vector<std::string> layers;
            Geometries geos = suffix == QLatin1String("svg") ? svgGeometry(file, error)
                                                             : dxfGeometry(file.toStdString(), error, layers);
            if (geos.empty()) {
                throw Base::RuntimeError(error);
            }
            std::vector<DxfText> texts = suffix == QLatin1String("dxf") ? dxfTexts(file) : std::vector<DxfText>();
            const std::string font = texts.empty() ? std::string() : dxfTextFont();
            if (suffix == QLatin1String("dxf") && !reviewDxf(geos, layers, QFileInfo(file).fileName(), &texts, !font.empty())) {
                return;
            }
            doc->openTransaction("Insert");
            Sketcher::SketchObject* sketch = addSketch(comp->getOrigin()->getXY(), std::string());
            sketch->Label.setValue(stem.toStdString());
            std::vector<Part::Geometry*> raw;
            for (const auto& g : geos) {
                raw.push_back(g.get());
            }
            sketch->addGeometry(raw);
            if (!font.empty()) {
                addDxfTexts(sketch, texts, font);
            }
        }
        doc->recompute();
        doc->commitTransaction();
        Gui::Application::Instance->commandManager().runCommandByName("Std_ViewFitAll");
    }
    catch (const Base::Exception& e) {
        doc->abortTransaction();
        QMessageBox::warning(Gui::getMainWindow(), T("Insert"), QString::fromUtf8(e.what()));
    }
    catch (const Standard_Failure& e) {
        doc->abortTransaction();
        QMessageBox::warning(Gui::getMainWindow(), T("Insert"), QString::fromUtf8(e.GetMessageString()));
    }
}

/// Gewählte Bodies exportieren, ohne Auswahl alle sichtbaren. 3MF/STL über Mesh, STEP über Import.
/// DXF: gewählte Skizzen, ohne Auswahl alle sichtbaren; jede flach in ihrer eigenen Ebene, eine Ebene (Layer) je Skizze.
void exportBodies(App::Document* doc);

namespace
{
/// Python-Zeichenkette (Pfad, Name)
std::string pyString(QString s)
{
    s.replace(QLatin1Char('\\'), QStringLiteral("\\\\")).replace(QLatin1Char('\''), QStringLiteral("\\'"));
    return "'" + s.toStdString() + "'";
}

/// DesignVersions aufrufen; Ergebnis als JSON (leer bei Fehler, der dann als Hinweis erscheint)
QJsonValue versionsCall(const std::string& expr, const QString& title)
{
    try {
        Base::PyGILStateLocker lock;
        const std::string r = Base::Interpreter().runStringWithKey(
            ("import DesignVersions, FreeCAD as App, json, base64\n_r = json.dumps(" + expr + ")").c_str(), "_r");
        return QJsonDocument::fromJson(QByteArray::fromStdString("[" + r + "]")).array().first();
    }
    catch (const Base::Exception& e) {
        QString text = QString::fromUtf8(e.what()).trimmed();
        const int at = text.lastIndexOf(QLatin1String("Error: "));
        toolHint(title, at >= 0 ? T(text.mid(at + 7).toUtf8().constData()) : text);
        return {};
    }
}

/// Vergleich mit einer anderen Datei des Designs als Geisterbild
void compareWith(App::Document* doc, const QString& path, const QString& title)
{
    try {
        Base::PyGILStateLocker lock;
        Py::Module mod(PyImport_ImportModule("DesignVersions"), true);
        Py::Dict d(mod.callMemberFunction("compare", Py::TupleN(Py::asObject(doc->getPyObject()), Py::String(path.toStdString()))));
        const auto shape = [&d](const char* key) {
            Py::Object o = d[key];
            return PyObject_TypeCheck(o.ptr(), &Part::TopoShapePy::Type)
                ? *static_cast<Part::TopoShapePy*>(o.ptr())->getTopoShapePtr()
                : Part::TopoShape();
        };
        QStringList steps;
        Py::Dict features(d["features"]);
        const std::pair<const char*, QString> kinds[] = {
            {"added", T("New step: %1")}, {"removed", T("Removed step: %1")}, {"changed", T("Changed step: %1")}};
        for (const auto& [key, text] : kinds) {
            for (const auto& label : Py::List(features[key])) {
                steps << text.arg(QString::fromStdString(Py::String(label).as_std_string()));
            }
        }
        if (steps.isEmpty()) {
            steps << T("No steps changed");
        }
        DesignGui::showComparison(title, shape("added"), shape("removed"), steps);
    }
    catch (const Py::Exception&) {
        Base::PyException e;
        toolHint(T("Compare"), QString::fromUtf8(e.what()));
    }
}
}  // namespace

/// Idee 7: Versionen und Varianten des Designs. Versionen entstehen beim immer laufenden Speichern; Öffnen zeigt eine
/// Kopie, Wiederherstellen legt eine neue Version an und löscht nie. Varianten: "Was wäre wenn", wechseln, übernehmen.
void showVersions(App::Document* doc)
{
    if (!*doc->FileName.getValue() && !Gui::Shell::saveQuietly(doc)) {
        return;
    }
    const QString path = QString::fromUtf8(doc->FileName.getValue());
    const std::string pdoc = "App.getDocument('" + std::string(doc->getName()) + "')";
    QDialog dlg(Gui::getMainWindow());
    dlg.setWindowTitle(T("Versions"));
    dlg.setMinimumSize(560, 520);
    auto lay = new QVBoxLayout(&dlg);
    lay->setContentsMargins(24, 20, 24, 20);
    auto list = new QListWidget;
    list->setAccessibleName(T("Versions"));
    list->setIconSize(QSize(64, 48));
    lay->addWidget(list, 2);
    const QJsonArray versions = versionsCall(
        "[dict(v, thumb=base64.b64encode(DesignVersions.thumbnail(v['path']) or b'').decode()) for v in "
        "DesignVersions.versions(" + pyString(path) + ")]", T("Versions")).toArray();
    for (const QJsonValue& v : versions) {
        const QJsonObject o = v.toObject();
        const QDateTime when = QDateTime::fromSecsSinceEpoch(qint64(o[QStringLiteral("time")].toDouble()));
        const QString day = when.date() == QDate::currentDate() ? T("Today") : QLocale().toString(when.date(), QLocale::ShortFormat);
        QString text = day + QStringLiteral(" ") + QLocale().toString(when.time(), QLocale::ShortFormat);
        if (!o[QStringLiteral("title")].toString().isEmpty()) {
            text += QStringLiteral("  ·  ") + o[QStringLiteral("title")].toString();
        }
        auto item = new QListWidgetItem(text);
        QPixmap thumb;
        if (thumb.loadFromData(QByteArray::fromBase64(o[QStringLiteral("thumb")].toString().toLatin1()))) {
            item->setIcon(QIcon(thumb));
        }
        item->setData(Qt::UserRole, o[QStringLiteral("path")].toString());
        list->addItem(item);
    }
    auto row = new QHBoxLayout;
    auto open = new QPushButton(T("Open Copy"));
    auto compare = new QPushButton(T("Compare"));
    auto restore = new QPushButton(T("Restore"));
    for (auto b : {open, compare, restore}) {
        b->setAutoDefault(false);
        b->setEnabled(false);
        row->addWidget(b);
    }
    lay->addLayout(row);
    // nach der Auswahl, nicht der aktuellen Zeile: der Fokus setzt Zeile 0 aktuell, ohne sie zu markieren
    QObject::connect(list, &QListWidget::itemSelectionChanged, &dlg, [=] {
        for (auto b : {open, compare, restore}) {
            b->setEnabled(!list->selectedItems().isEmpty());
        }
    });
    const auto chosen = [list] { return list->currentItem() ? list->currentItem()->data(Qt::UserRole).toString() : QString(); };
    QObject::connect(open, &QPushButton::clicked, &dlg, [&, chosen] {
        // Kopie zum Ansehen: die Version selbst bleibt, wie sie ist
        versionsCall("(lambda p: (lambda c: (__import__('shutil').copy2(p, c), App.openDocument(c).Name)[1])("
                     "__import__('os').path.join(__import__('tempfile').mkdtemp(), __import__('os').path.basename(p))))("
                         + pyString(chosen()) + ")",
                     T("Versions"));
        dlg.accept();
    });
    QObject::connect(compare, &QPushButton::clicked, &dlg, [&, chosen] {
        const QString title = T("Compared with %1").arg(list->currentItem()->text());
        dlg.accept();
        compareWith(doc, chosen(), title);
    });
    QObject::connect(restore, &QPushButton::clicked, &dlg, [&, chosen] {
        versionsCall("DesignVersions.restore(" + pdoc + ", " + pyString(chosen()) + ").Name", T("Restore"));
        dlg.accept();
    });

    // Varianten
    lay->addWidget(Gui::Shell::sectionLabel(T("Variants")));
    auto variants = new QListWidget;
    variants->setAccessibleName(T("Variants"));
    const bool isVariant = versionsCall("DesignVersions.is_variant(" + pyString(path) + ")", T("Variants")).toBool();
    const QString main = versionsCall("DesignVersions.main_of(" + pyString(path) + ")", T("Variants")).toString();
    auto mainItem = new QListWidgetItem(T("Main design") + (isVariant ? QString() : QStringLiteral("  ·  ") + T("open")));
    mainItem->setData(Qt::UserRole, main);
    variants->addItem(mainItem);
    for (const QJsonValue& v : versionsCall("DesignVersions.variants(" + pyString(path) + ")", T("Variants")).toArray()) {
        const QJsonObject o = v.toObject();
        const bool current = QFileInfo(o[QStringLiteral("path")].toString()) == QFileInfo(path);
        auto item = new QListWidgetItem(o[QStringLiteral("name")].toString() + (current ? QStringLiteral("  ·  ") + T("open") : QString()));
        item->setData(Qt::UserRole, o[QStringLiteral("path")].toString());
        variants->addItem(item);
    }
    lay->addWidget(variants, 1);
    auto vrow = new QHBoxLayout;
    auto create = new QPushButton(T("New Variant…"));
    auto switchTo = new QPushButton(T("Switch To"));
    auto compareVariant = new QPushButton(T("Compare"));
    auto adopt = new QPushButton(T("Make Main Design"));
    adopt->setEnabled(isVariant);
    adopt->setToolTip(T("The open variant becomes the main design; the old main design is kept as a version"));
    for (auto b : {create, switchTo, compareVariant, adopt}) {
        b->setAutoDefault(false);
        vrow->addWidget(b);
    }
    lay->addLayout(vrow);
    const auto variantPath = [variants] {
        return variants->currentItem() ? variants->currentItem()->data(Qt::UserRole).toString() : QString();
    };
    // Wechseln und Vergleichen nur mit einer anderen als der geöffneten Variante
    for (auto b : {switchTo, compareVariant}) {
        b->setEnabled(false);
    }
    QObject::connect(variants, &QListWidget::itemSelectionChanged, &dlg, [=] {
        const bool other = !variants->selectedItems().isEmpty() && QFileInfo(variantPath()) != QFileInfo(path);
        for (auto b : {switchTo, compareVariant}) {
            b->setEnabled(other);
        }
    });
    QObject::connect(create, &QPushButton::clicked, &dlg, [&] {
        bool ok = false;
        const QString name = QInputDialog::getText(&dlg, T("New Variant"), T("What do you want to try?"), QLineEdit::Normal,
                                                   QString(), &ok);
        if (ok && !name.trimmed().isEmpty()) {
            const QJsonValue made = versionsCall("DesignVersions.make_variant(" + pdoc + ", " + pyString(name.trimmed()) + ")",
                                                 T("New Variant"));
            if (made.isString()) {
                versionsCall("DesignVersions.switch(" + pdoc + ", " + pyString(made.toString()) + ").Name", T("Variants"));
                dlg.accept();
            }
        }
    });
    QObject::connect(switchTo, &QPushButton::clicked, &dlg, [&, variantPath] {
        if (!variantPath().isEmpty() && QFileInfo(variantPath()) != QFileInfo(path)) {
            versionsCall("DesignVersions.switch(" + pdoc + ", " + pyString(variantPath()) + ").Name", T("Variants"));
            dlg.accept();
        }
    });
    QObject::connect(compareVariant, &QPushButton::clicked, &dlg, [&, variantPath] {
        if (!variantPath().isEmpty() && QFileInfo(variantPath()) != QFileInfo(path)) {
            const QString title = T("Compared with %1").arg(variants->currentItem()->text());
            dlg.accept();
            compareWith(doc, variantPath(), title);
        }
    });
    QObject::connect(adopt, &QPushButton::clicked, &dlg, [&] {
        versionsCall("DesignVersions.adopt(" + pdoc + ").Name", T("Variants"));
        dlg.accept();
    });

    auto buttons = new QDialogButtonBox(QDialogButtonBox::Close);
    QObject::connect(buttons, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);
    lay->addWidget(buttons);
    dlg.exec();
}

/// Idee 5: die gewählte ebene Fläche liegt beim Drucken auf dem Bett (Druckrichtung = ihre Normale nach innen)
void choosePrintBottom(App::Document* doc)
{
    for (auto& sel : Gui::Selection().getSelectionEx()) {
        auto b = freecad_cast<Design::Body*>(sel.getObject());
        if (!b || sel.getSubNames().empty() || !isPlanarFace(b, sel.getSubNames().front())) {
            continue;
        }
        const TopoDS_Face face = TopoDS::Face(b->Shape.getShape().getSubShape(sel.getSubNames().front().c_str()));
        BRepAdaptor_Surface surface(face);
        gp_Dir n = surface.Plane().Axis().Direction();
        if (face.Orientation() == TopAbs_REVERSED) {
            n.Reverse();  // aus dem Körper heraus
        }
        Base::Vector3d up(-n.X(), -n.Y(), -n.Z());
        Design::componentOf(b)->globalPlacement().getRotation().multVec(up, up);
        doc->openTransaction("Print Direction");
        Design::setPrintUp(doc, up);
        doc->commitTransaction();
        Gui::Selection().clearSelection();
        DesignGui::setPrintView(true);
        return;
    }
    toolHint(T("Choose Bottom Face"), T("Click the flat face that should lie on the print bed."));
}

/// Idee 5: Drucken. Sichtbare (oder gewählte) Körper als 3MF mit Druckrichtung nach oben im Slicer öffnen; welcher
/// Slicer, merkt sich MyCAD. Ohne Slicer: Export.
void printBodies(App::Document* doc)
{
    const auto chosen = selectedBodies();
    std::vector<App::DocumentObject*> bodies(chosen.begin(), chosen.end());
    if (bodies.empty()) {
        for (auto obj : doc->getObjectsOfType(Design::Body::getClassTypeId())) {
            if (obj->Visibility.getValue() && !static_cast<Design::Body*>(obj)->Shape.getShape().isNull()) {
                bodies.push_back(obj);
            }
        }
    }
    if (bodies.empty()) {
        toolHint(T("Print"), T("There is no body to print."));
        return;
    }
    ParameterGrp::handle params = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD");
    // Flatpak (12.6): Programme des Rechners starten ginge nur am Sandkasten vorbei. Stattdessen öffnet das System das
    // 3MF über das Portal und fragt einmal, mit welchem Slicer (auch Flatpak-Slicer)
    const bool sandboxed = QFile::exists(QStringLiteral("/.flatpak-info"));
    QStringList names;
    try {
        Base::PyGILStateLocker lock;
        const std::string found = sandboxed ? std::string() : Base::Interpreter().runStringWithKey(
            "import DesignExport\n_r = '\\n'.join(n for n, c in DesignExport.find_slicers())", "_r");
        names = QString::fromStdString(found).split(QLatin1Char('\n'), Qt::SkipEmptyParts);
    }
    catch (const Base::Exception& e) {
        Base::Console().error("Print: %s\n", e.what());
    }
    if (names.isEmpty() && !sandboxed) {
        toolHint(T("Print"),
                                 T("No slicer found (OrcaSlicer, Bambu Studio, PrusaSlicer or Cura). Save a 3MF file and open it "
                                   "in your slicer."));
        exportBodies(doc);
        return;
    }
    QString slicer = QString::fromStdString(params->GetASCII("Slicer", ""));
    if (!sandboxed && !names.contains(slicer)) {
        bool ok = names.size() == 1;
        slicer = ok ? names.front()
                    : QInputDialog::getItem(Gui::getMainWindow(), T("Print"), T("Open in which slicer?"), names, 0, false, &ok);
        if (!ok) {
            return;
        }
        params->SetASCII("Slicer", slicer.toStdString());
    }
    static const char* qualities[] = {"coarse", "normal", "fine"};
    const long quality = std::clamp<long>(params->GetInt("ExportQuality", 1), 0, 2);
    QString folder = QStandardPaths::writableLocation(QStandardPaths::GenericCacheLocation) + QStringLiteral("/MyCAD/print");
    QDir().mkpath(folder);
    folder.replace(QLatin1Char('\\'), QStringLiteral("\\\\")).replace(QLatin1Char('\''), QStringLiteral("\\'"));
    QString name = slicer;
    name.replace(QLatin1Char('\''), QStringLiteral("\\'"));
    std::string objs = "[";
    for (auto o : bodies) {
        objs += "App.getDocument('" + std::string(doc->getName()) + "').getObject('" + o->getNameInDocument() + "'),";
    }
    objs += "]";
    try {
        Base::PyGILStateLocker lock;
        const std::string command = sandboxed ? "None" : "dict(DesignExport.find_slicers())['" + name.toStdString() + "']";
        const std::string path = Base::Interpreter().runStringWithKey(
            ("import DesignExport, Design, FreeCAD as App\n_r = DesignExport.open_in_slicer(" + objs + ", '"
             + folder.toStdString() + "', " + command + ", up=Design.printUp(App.getDocument('" + doc->getName()
             + "')), quality='" + qualities[quality] + "')")
                .c_str(),
            "_r");
        if (sandboxed) {
            QDesktopServices::openUrl(QUrl::fromLocalFile(QString::fromStdString(path)));
        }
    }
    catch (const Base::Exception& e) {
        QMessageBox::warning(Gui::getMainWindow(), T("Print"), T("The slicer could not be started: %1").arg(QString::fromUtf8(e.what())));
    }
}

void exportBodies(App::Document* doc)
{
    std::vector<App::DocumentObject*> bodies;
    for (auto b : selectedBodies()) {
        bodies.push_back(b);
    }
    std::vector<App::DocumentObject*> sketches;
    for (auto& sel : Gui::Selection().getSelectionEx()) {
        auto obj = sel.getObject();
        if (obj && obj->isDerivedFrom<Sketcher::SketchObject>() && std::ranges::find(sketches, obj) == sketches.end()) {
            sketches.push_back(obj);
        }
    }
    const bool onlySketches = bodies.empty() && !sketches.empty();
    if (bodies.empty()) {
        for (auto obj : doc->getObjectsOfType(Design::Body::getClassTypeId())) {
            if (obj->Visibility.getValue() && !static_cast<Design::Body*>(obj)->Shape.getShape().isNull()) {
                bodies.push_back(obj);
            }
        }
    }
    if (sketches.empty()) {
        for (auto obj : doc->getObjectsOfType(Sketcher::SketchObject::getClassTypeId())) {
            if (obj->Visibility.getValue()) {
                sketches.push_back(obj);
            }
        }
    }
    if (bodies.empty() && sketches.empty()) {
        toolHint(T("Export"), T("There is no body to export."));
        return;
    }

    // Die eingetippte Endung bestimmt das Format; nur ohne Endung kommt die des gewählten Filters dazu.
    // Nur Skizzen gewählt: DXF vorauswählen
    const QString start = QDir::home().filePath(QString::fromUtf8(doc->Label.getValue()));
    const QStringList filters = T("3MF for 3D printing (*.3mf);;STL (*.stl);;STEP (*.step *.stp);;DXF sketches (*.dxf)")
                                    .split(QStringLiteral(";;"));
    QString filter = onlySketches ? filters.last() : filters.first();
    QString file = QFileDialog::getSaveFileName(
        Gui::getMainWindow(), T("Export"), start, filters.join(QStringLiteral(";;")), &filter
    );
    if (file.isEmpty()) {
        return;
    }
    static const QStringList known = {QStringLiteral("3mf"), QStringLiteral("stl"), QStringLiteral("step"),
                                      QStringLiteral("stp"), QStringLiteral("dxf")};
    if (!known.contains(QFileInfo(file).suffix().toLower())) {
        file += filter.startsWith(QLatin1String("STL")) ? QStringLiteral(".stl")
            : filter.startsWith(QLatin1String("STEP")) ? QStringLiteral(".step")
            : filter.startsWith(QLatin1String("DXF"))  ? QStringLiteral(".dxf")
                                                        : QStringLiteral(".3mf");
    }
    const QString suffix = QFileInfo(file).suffix().toLower();
    const bool dxf = suffix == QLatin1String("dxf");
    const auto& objects = dxf ? sketches : bodies;
    if (objects.empty()) {
        toolHint(T("Export"), dxf ? T("There is no sketch to export.") : T("There is no body to export.")
        );
        return;
    }

    // Pfad als Python-String: nur Backslash und Apostroph escapen
    QString path = file;
    path.replace(QLatin1Char('\\'), QStringLiteral("\\\\")).replace(QLatin1Char('\''), QStringLiteral("\\'"));
    std::string objs = "[";
    for (auto o : objects) {
        objs += "App.getDocument('" + std::string(doc->getName()) + "').getObject('" + o->getNameInDocument() + "'),";
    }
    objs += "]";
    // 3MF: eigener Writer mit Farbe und Name je Body; STL in derselben Auflösung; STEP mit Farben und Struktur
    static const char* qualities[] = {"coarse", "normal", "fine"};
    static const double tolerances[] = {0.1, 0.02, 0.005};  // wie DesignExport.QUALITY
    const long quality = std::clamp<long>(App::GetApplication()
                                              .GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD")
                                              ->GetInt("ExportQuality", 1),
                                          0, 2);
    const std::string target = "'" + path.toStdString() + "'";
    std::string code;
    if (dxf) {
        code = "import Import\nImport.writeDXFObject(" + objs + ", " + target + ")";
    }
    else if (suffix == QLatin1String("step") || suffix == QLatin1String("stp")) {
        code = "import DesignExport\nDesignExport.write_step(" + target + ", " + objs + ")";  // U6: Namen als ASCII
    }
    else if (suffix == QLatin1String("3mf")) {
        code = "import DesignExport\nDesignExport.write_3mf(" + target + ", " + objs + ", '" + qualities[quality] + "')";
    }
    else {
        code = "import Mesh\nMesh.export(" + objs + ", " + target + ", tolerance=" + std::to_string(tolerances[quality]) + ")";
    }
    try {
        Base::Interpreter().runString(("import FreeCAD as App\n" + code).c_str());
        // als Hinweis unter dem ViewCube (Benachrichtigung): die Statusleiste ist in MyCAD ausgeblendet
        const QString done = objects.size() == 1
            ? (dxf ? T("Exported 1 sketch to %1") : T("Exported 1 body to %1")).arg(file)
            : (dxf ? T("Exported %1 sketches to %2") : T("Exported %1 bodies to %2")).arg(objects.size()).arg(file);
        notify(done);
    }
    catch (const Base::Exception& e) {
        QMessageBox::warning(Gui::getMainWindow(), T("Export"), QString::fromUtf8(e.what()));
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

/// Maßstab der Ansicht an einer Stelle der Skizze: wohin 1 mm in x und in y der Skizze auf dem Bildschirm führt. Schräg
/// gesehen ist er je Richtung anders. Leer (alles 0) ohne Ansicht.
struct ViewScale
{
    double xu = 0, xv = 0, yu = 0, yv = 0;
    /// Pixel je mm entlang d (Skizze, 2D)
    double along(const Base::Vector3d& d) const
    {
        const double len = std::hypot(d.x, d.y);
        return len > 0 ? std::hypot(d.x * xu + d.y * yu, d.x * xv + d.y * yv) / len : std::max(std::hypot(xu, xv), std::hypot(yu, yv));
    }
};

/// Phase 11.5: Lage einer Bohrung auf der Fläche fangen und bemaßen wie Fusion. p (Skizze, 2D) liegt danach
/// - auf der Mitte eines Kreises/Bogens der Fläche, wenn der Klick weniger als SnapPx davon weg war (deckungsgleich), sonst
/// - mit Abständen zu den zwei nächsten nicht parallelen Kanten: je Kante auf der Mitte der Fläche quer zu ihr, wenn der
///   Klick nah dran war, sonst gerundet auf ein Raster, das zum Zoom passt (0,1 … 10 mm, ein Schritt mindestens 6 px;
///   grid ist das Raster ohne Ansicht, 0 = nicht runden). Beide Abstände werden Maße, der Punkt ist voll bestimmt.
/// scale: Maßstab der Ansicht an der Klickstelle (leer ohne Ansicht: nur runden).
void dimensionHolePoint(Sketcher::SketchObject* sketch, int point, Base::Vector3d& p, const ViewScale& scale, double grid = 0.5)
{
    constexpr double SnapPx = 12;
    const auto snaps = [&](double mm, const Base::Vector3d& dir) {
        const double px = scale.along(dir);
        return px > 0 && std::abs(mm) * px < SnapPx;
    };
    struct Line
    {
        int geo;
        Base::Vector3d a, n;  ///< Punkt auf der Kante, Normale in der Skizze
    };
    std::vector<Line> lines;
    std::vector<Base::Vector3d> corners;
    const auto& ext = sketch->getExternalGeometry();  // 0 und 1 sind die Achsen der Skizze
    for (size_t i = 2; i < ext.size(); ++i) {
        const int geo = -static_cast<int>(i) - 1;
        Base::Vector3d centre;
        bool round = false;
        if (auto circle = dynamic_cast<const Part::GeomCircle*>(ext[i])) {
            centre = circle->getCenter();
            round = true;
        }
        else if (auto arc = dynamic_cast<const Part::GeomArcOfCircle*>(ext[i])) {
            centre = arc->getCenter();
            round = true;
        }
        if (round) {
            centre.z = 0;
            if (snaps((centre - p).Length(), centre - p)) {
                p = centre;
                auto c = std::make_unique<Sketcher::Constraint>();
                c->Type = Sketcher::Coincident;
                c->First = point;
                c->FirstPos = Sketcher::PointPos::start;
                c->Second = geo;
                c->SecondPos = Sketcher::PointPos::mid;
                sketch->setGeometry(point, std::make_unique<Part::GeomPoint>(p).get());
                sketch->addConstraint(std::move(c));
                return;
            }
            continue;
        }
        auto seg = dynamic_cast<const Part::GeomLineSegment*>(ext[i]);
        if (!seg) {
            continue;
        }
        Base::Vector3d a = seg->getStartPoint(), b = seg->getEndPoint();
        a.z = b.z = 0;
        if ((b - a).Length() < 1e-9) {
            continue;
        }
        Base::Vector3d d = (b - a).Normalize();
        lines.push_back({geo, a, Base::Vector3d(-d.y, d.x, 0)});
        corners.push_back(a);
        corners.push_back(b);
    }
    const auto distance = [&p](const Line& l) { return (p - l.a) * l.n; };
    const Line* first = nullptr;
    const Line* second = nullptr;
    for (const auto& l : lines) {
        if (!first || std::abs(distance(l)) < std::abs(distance(*first))) {
            first = &l;
        }
    }
    for (const auto& l : lines) {
        if (first && std::abs((l.n % first->n).z) > 0.1 && (!second || std::abs(distance(l)) < std::abs(distance(*second)))) {
            second = &l;
        }
    }
    std::vector<std::pair<const Line*, double>> dims;
    for (const Line* l : {first, second}) {
        if (!l) {
            continue;
        }
        const double s = distance(*l);
        double across = 0;  // Breite der Fläche quer zur Kante, auf der Seite des Klicks
        for (const auto& c : corners) {
            const double t = (c - l->a) * l->n;
            if (t * s > 0 && std::abs(t) > std::abs(across)) {
                across = t;
            }
        }
        double step = grid;
        if (const double px = scale.along(l->n); grid > 0 && px > 0) {
            for (double g : {0.1, 0.2, 0.5, 1.0, 2.0, 5.0, 10.0}) {
                step = g;
                if (g * px >= 6) {
                    break;
                }
            }
        }
        double want = step > 0 ? std::round(s / step) * step : s;
        if (across != 0 && snaps(s - across / 2, l->n)) {
            want = across / 2;
        }
        // gleicher Randabstand wie eine Bohrung davor (weitere Klicks, 11.5): genau den, dann bindet ihn die Reihe
        for (const Sketcher::Constraint* other : sketch->Constraints.getValues()) {
            if (other->Type == Sketcher::Distance && other->Second == l->geo && other->First != point
                && snaps(std::abs(s) - other->getValue(), l->n)) {
                want = s < 0 ? -other->getValue() : other->getValue();
            }
        }
        if (std::abs(want) < 1e-9) {
            want = s;  // auf der Kante geklickt: so lassen, ein Maß 0 hält den Punkt nicht auf der Seite
        }
        dims.emplace_back(l, want);
    }
    // Punkt auf die gewünschten Abstände schieben: (p - a)·n = want je Kante, zwei Kanten = 2×2-Gleichungssystem
    if (dims.size() == 2) {
        const auto& [l1, w1] = dims[0];
        const auto& [l2, w2] = dims[1];
        const double r1 = w1 + l1->a * l1->n, r2 = w2 + l2->a * l2->n;
        const double det = l1->n.x * l2->n.y - l1->n.y * l2->n.x;
        p = Base::Vector3d((r1 * l2->n.y - r2 * l1->n.y) / det, (l1->n.x * r2 - l2->n.x * r1) / det, 0);
    }
    else if (dims.size() == 1) {
        p += dims[0].first->n * (dims[0].second - distance(*dims[0].first));
    }
    sketch->setGeometry(point, std::make_unique<Part::GeomPoint>(p).get());
    for (const auto& [l, value] : dims) {
        // gleicher Abstand zur selben Kante wie eine frühere Bohrung: an deren Maß binden, die Reihe bleibt zusammen
        int same = -1;
        const auto& existing = sketch->Constraints.getValues();
        for (size_t k = 0; k < existing.size() && same < 0; ++k) {
            const Sketcher::Constraint* other = existing[k];
            if (other->Type == Sketcher::Distance && other->Second == l->geo && other->First != point
                && std::abs(other->getValue() - std::abs(value)) < 1e-9) {
                same = static_cast<int>(k);
            }
        }
        auto c = std::make_unique<Sketcher::Constraint>();
        c->Type = Sketcher::Distance;
        c->First = point;
        c->FirstPos = Sketcher::PointPos::start;
        c->Second = l->geo;
        c->setValue(std::abs(value));
        const int index = sketch->addConstraint(std::move(c));
        if (same >= 0) {
            std::string name = sketch->Constraints.getValues()[same]->Name;
            if (name.empty()) {
                name = "Row" + std::to_string(same + 1);
                sketch->renameConstraint(same, name);
            }
            sketch->setExpression(sketch->Constraints.createPath(index),
                                  std::shared_ptr<App::Expression>(App::Expression::parse(sketch, "Constraints." + name)));
        }
    }
}

/// Maßstab der Ansicht an p (Skizze, 2D), in x und y der Skizze; leer ohne 3D-Ansicht
ViewScale viewScaleAt(Design::Body* body, Sketcher::SketchObject* sketch, const Base::Vector3d& p)
{
    auto gdoc = Gui::Application::Instance->getDocument(body->getDocument());
    auto view = gdoc ? dynamic_cast<Gui::View3DInventor*>(gdoc->getActiveView()) : nullptr;
    if (!view) {
        return {};
    }
    const Base::Placement toGlobal = Design::componentOf(body)->globalPlacement() * sketch->Placement.getValue();
    const auto screen = [&](double x, double y) {
        Base::Vector3d g;
        toGlobal.multVec(Base::Vector3d(x, y, 0), g);
        return view->getViewer()->getPointOnViewport(SbVec3f(float(g.x), float(g.y), float(g.z)));
    };
    // 10 mm statt 1 mm: der Bildschirm rundet auf ganze Pixel, weit herausgezoomt wäre 1 mm sonst 0 px
    const SbVec2s o = screen(p.x, p.y), x = screen(p.x + 10, p.y), y = screen(p.x, p.y + 10);
    return {(x[0] - o[0]) / 10.0, (x[1] - o[1]) / 10.0, (y[0] - o[0]) / 10.0, (y[1] - o[1]) / 10.0};
}

/// Phase 11.5: Solange der Dialog der eben angeklickten Bohrung offen ist, macht jeder weitere Klick auf dieselbe Fläche
/// (Ebene der Skizze) dort eine weitere Bohrung derselben Art: ein Punkt mehr in ihrer Skizze, gefangen und bemaßt wie
/// der erste. Gleicher Randabstand wie eine frühere Bohrung bindet das Maß an deren (eine Reihe). Abbrechen nimmt alle.
class MoreHoles: public Gui::SelectionObserver
{
public:
    static MoreHoles& instance()
    {
        static MoreHoles holes;
        return holes;
    }
    void start(Design::Body* body, Sketcher::SketchObject* sketch)
    {
        this->body = App::DocumentObjectT(body);
        this->sketch = App::DocumentObjectT(sketch);
        dialog = Gui::Control().activeDialog();
    }

private:
    void onSelectionChanged(const Gui::SelectionChanges& msg) override
    {
        if (!dialog || msg.Type != Gui::SelectionChanges::AddSelection) {
            return;
        }
        if (Gui::Control().activeDialog() != dialog) {
            dialog = nullptr;  // Dialog zu: fertig
            return;
        }
        auto b = freecad_cast<Design::Body*>(body.getObject());
        auto sk = freecad_cast<Sketcher::SketchObject*>(sketch.getObject());
        if (!b || !sk || msg.pObjectName != std::string(b->getNameInDocument())) {
            return;
        }
        const Base::Vector3d picked(msg.x, msg.y, msg.z);
        QTimer::singleShot(0, [this, picked] { add(picked); });
    }

    void add(const Base::Vector3d& picked)
    {
        auto b = freecad_cast<Design::Body*>(body.getObject());
        auto sk = freecad_cast<Sketcher::SketchObject*>(sketch.getObject());
        if (!b || !sk || Gui::Control().activeDialog() != dialog) {
            return;
        }
        Base::Vector3d p;
        (Design::componentOf(b)->globalPlacement() * sk->Placement.getValue()).inverse().multVec(picked, p);
        if (std::abs(p.z) > 1e-2) {
            return;  // andere Fläche des Körpers: kein Teil dieser Bohrung
        }
        p.z = 0;
        const Part::GeomPoint centre(p);
        const int point = sk->addGeometry(&centre);
        dimensionHolePoint(sk, point, p, viewScaleAt(b, sk, p));
        Gui::Selection().clearSelection();
        sk->getDocument()->recompute();
    }

    App::DocumentObjectT body, sketch;
    Gui::TaskView::TaskDialog* dialog = nullptr;  ///< nur vergleichen, nie benutzen
};

/// Bohrung auf einer ebenen Körperfläche wie in Fusion: eine verborgene Skizze auf der Fläche mit einem Punkt an der
/// Klickstelle (der Rand der Fläche ist projiziert), daraus die Bohrung. Der Punkt fängt und bekommt Maße zu den Kanten
/// (dimensionHolePoint). Liegt point nicht auf der Fläche (Auswahl per Skript ohne Klickpunkt), in ihrer Mitte. Alles
/// in der Transaktion der Bohrung: Abbrechen nimmt auch die Skizze zurück. Lage ändern = Maße in der Skizze ändern.
/// cornerOffset >= 0 (11.10, "in die Ecken"): statt des Klickpunkts vier Bohrungen in die Ecken der Fläche, so weit vom
/// Rand, genau (ohne Raster), ihre Randabstände als Reihe gebunden. setup stellt die Bohrung vor dem Dialog ein.
/// layout (11.10, Bohrmuster): legt die Punkte selbst an; bekommt die Skizze (Punkt 0 gibt es schon) und das Rechteck um
/// den Rand der Fläche (Skizzen-Koordinaten)
using HoleLayout = std::function<void(Sketcher::SketchObject*, const Base::BoundBox3d&)>;

void holeOnFace(Design::Body* body, std::string face, const Base::Vector3d& point, double cornerOffset = -1,
                const std::function<void(Design::Hole*)>& setup = {}, const HoleLayout& layout = {})
{
    const TopoDS_Shape shape = body->Shape.getShape().getSubShape(face.c_str(), true);
    if (shape.IsNull()) {
        return;
    }
    Base::Vector3d at;  // in Koordinaten der Komponente, wie die Formen
    Design::componentOf(body)->globalPlacement().inverse().multVec(point, at);
    BRepExtrema_DistShapeShape onFace(BRepBuilderAPI_MakeVertex(gp_Pnt(at.x, at.y, at.z)), shape);
    if (!onFace.IsDone() || onFace.Value() > 1e-2) {  // Klickpunkt aus Coin: float-genau
        GProp_GProps props;
        BRepGProp::SurfaceProperties(shape, props);
        at = Base::Vector3d(props.CentreOfMass().X(), props.CentreOfMass().Y(), props.CentreOfMass().Z());
    }
    App::Document* doc = body->getDocument();
    App::DocumentObject* support = body;
    stableRef(support, face);
    auto feature = static_cast<Design::Hole*>(addFeature(doc, "Design::Hole", "Hole", body));
    Sketcher::SketchObject* sketch = addSketch(support, face);
    doc->recompute();  // Lage der Skizze auf der Fläche
    sketch->addExternal(support, face.c_str(), /*defining*/ false);
    Base::Vector3d onSketch;
    sketch->Placement.getValue().inverse().multVec(at, onSketch);
    const Part::GeomPoint centre(Base::Vector3d(onSketch.x, onSketch.y, 0));
    sketch->addGeometry(&centre);
    if (sketch->getExternalGeometry().size() <= 2) {
        doc->recompute();  // Projektion des Rands
    }
    Base::Vector3d p(onSketch.x, onSketch.y, 0);
    // Rechteck um den Rand der Fläche (Linien und Kreise), für Ecken und Muster
    Base::BoundBox3d box;
    const auto& ext = sketch->getExternalGeometry();
    for (size_t i = 2; i < ext.size(); ++i) {
        if (auto seg = dynamic_cast<const Part::GeomLineSegment*>(ext[i])) {
            box.Add(seg->getStartPoint());
            box.Add(seg->getEndPoint());
        }
        else if (auto circle = dynamic_cast<const Part::GeomCircle*>(ext[i])) {
            const Base::Vector3d c = circle->getCenter();
            const double r = circle->getRadius();
            box.Add(Base::Vector3d(c.x - r, c.y - r, 0));
            box.Add(Base::Vector3d(c.x + r, c.y + r, 0));
        }
    }
    if (!box.IsValid()) {
        box.Add(p);
    }
    if (layout) {
        layout(sketch, box);
    }
    else if (cornerOffset < 0) {
        dimensionHolePoint(sketch, 0, p, viewScaleAt(body, sketch, p));
    }
    else {  // Ecken des Rands (Rechteck um die projizierten Kanten), nach innen versetzt
        const double o = cornerOffset;
        const Base::Vector3d corners[] = {Base::Vector3d(box.MinX + o, box.MinY + o, 0), Base::Vector3d(box.MaxX - o, box.MinY + o, 0),
                                          Base::Vector3d(box.MaxX - o, box.MaxY - o, 0), Base::Vector3d(box.MinX + o, box.MaxY - o, 0)};
        for (int k = 0; k < 4; ++k) {
            Base::Vector3d c = corners[k];
            const Part::GeomPoint at(c);
            const int index = k == 0 ? 0 : sketch->addGeometry(&at);
            if (k == 0) {
                sketch->setGeometry(0, &at);
            }
            dimensionHolePoint(sketch, index, c, {}, 0);
        }
    }
    sketch->Visibility.setValue(false);
    const auto items = Design::timeline(doc);  // Skizze vor die Bohrung, die sie braucht
    std::string error;
    Design::moveInTimeline(sketch, static_cast<int>(std::ranges::find(items, feature) - items.begin()), error);
    feature->Sketch.setValue(sketch);
    modifyBodies(feature, {body});
    if (setup) {
        setup(feature);
    }
    doc->recompute();
    startEditing(feature, false, nullptr);
    MoreHoles::instance().start(body, sketch);  // weitere Klicks: weitere Bohrungen
}

/// Hat die Skizze einzelne Punkte (die Mitten der Bohrungen)?
bool hasPoints(App::DocumentObject* sketch)
{
    auto feature = freecad_cast<Part::Feature*>(sketch);
    for (TopoDS_Iterator it(feature ? feature->Shape.getShape().getShape() : TopoDS_Shape()); it.More(); it.Next()) {
        if (it.Value().ShapeType() == TopAbs_VERTEX) {
            return true;
        }
    }
    return false;
}

void startHole(App::Document* doc)
{
    PlanePicker::stop();
    App::DocumentObject* sketch = nullptr;
    for (auto obj : Gui::Selection().getObjectsOfType(Sketcher::SketchObject::getClassTypeId())) {
        sketch = obj;
    }
    // Eine gewählte Körperfläche ohne Skizze: Bohrung dort, wo die Fläche angeklickt wurde (wie Fusion), nicht die
    // zuletzt erstellte Skizze irgendwo anders (die Bohrung landete sonst z. B. oben, obwohl die Seite gewählt war)
    auto selection = Gui::Selection().getSelectionEx();
    for (auto& sel : selection) {
        auto body = freecad_cast<Design::Body*>(sel.getObject());
        if (sketch || !body || sel.getSubNames().empty()) {
            continue;
        }
        if (!isPlanarFace(body, sel.getSubNames().front())) {
            toolHint(T("Hole"), T("Click a flat face of a body where the hole goes."));
            return;
        }
        const auto& points = sel.getPickedPoints();
        holeOnFace(body, sel.getSubNames().front(), points.empty() ? Base::Vector3d() : points.front());
        return;
    }
    if (!sketch) {  // sonst die zuletzt erstellte Skizze, wenn sie Punkte hat und noch keine Bohrung sie nutzt (sonst
                    // landete die nächste Bohrung per Klick auf der verborgenen Skizze der letzten)
        auto sketches = doc->getObjectsOfType(Sketcher::SketchObject::getClassTypeId());
        const auto used = [](App::DocumentObject* s) {
            return std::ranges::any_of(s->getInList(), [](auto o) { return o->template isDerivedFrom<Design::Hole>(); });
        };
        sketch = sketches.empty() || !hasPoints(sketches.back()) || used(sketches.back()) ? nullptr : sketches.back();
    }
    if (!sketch) {  // wie Fusion: auf einen Klick auf eine Fläche warten, dort entsteht die Bohrung
        PlanePicker::start(activeContainer(doc), [](App::DocumentObject* obj, const std::string& face, const Base::Vector3d& point) {
            if (auto body = freecad_cast<Design::Body*>(obj)) {
                holeOnFace(body, face, point);
            }
            else {
                toolHint(T("Hole"), T("Click a flat face of a body where the hole goes."));
            }
        }, false);
        toolHint(T("Hole"), T("Click a flat face of a body where the hole goes."));
        return;
    }
    Design::Body* target = bodyUnderSketch(sketch);
    if (!target) {
        toolHint(T("Hole"),
                                 T("Create a sketch on a face of a body and place points where the holes go."));
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
        if (!selected.empty()) {
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
        toolHint(T("Pattern"),
                                 T("Select bodies, or an Extrude, Revolve or Hole in the timeline first."));
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
    /// d: Startabstand (neu 10 mm, Nachbearbeiten: der bisherige)
    explicit TaskOffsetPlane(App::DocumentObject* plane, double d = 10.0)
        : plane(plane)
    {
        auto w = new QWidget;
        w->setWindowTitle(T("Offset Plane"));
        auto form = new QFormLayout(w);
        auto distance = new Gui::QuantitySpinBox;
        distance->setUnit(Base::Unit::Length);
        distance->setRange(-1e7, 1e7);
        distance->setValue(Base::Quantity(d, Base::Unit::Length));
        form->addRow(T("Distance"), distance);
        addTaskBox(w, false);
        QObject::connect(distance, qOverload<double>(&Gui::QuantitySpinBox::valueChanged), [this](double d) {
            setOffset(d);
        });
        setOffset(d);
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
        // nur den Abstand: die Verschiebung in der Ebene (mittig über der Fläche, styleDatum) bleibt
        auto offset = static_cast<App::PropertyPlacement*>(plane->getPropertyByName("AttachmentOffset"));
        const Base::Vector3d p = offset->getValue().getPosition();
        offset->setValue(Base::Placement(Base::Vector3d(p.x, p.y, d), Base::Rotation()));
        plane->getDocument()->recompute();
    }
    App::DocumentObject* plane;
};

/// Konstruktionselemente dezent statt FreeCAD-Gelb. Ebenen so groß wie der Körper, an dem sie hängen, und mittig über
/// den gewählten Elementen (Fläche, Punkte, …) statt am Ursprung der Fläche; halbtransparent nur Ebenen, Achsen und
/// Punkte deckend (sonst kaum zu sehen)
void styleDatum(App::DocumentObject* datum)
{
    auto length = freecad_cast<App::PropertyLength*>(datum->getPropertyByName("Length"));
    auto width = freecad_cast<App::PropertyLength*>(datum->getPropertyByName("Width"));
    auto resize = freecad_cast<App::PropertyEnumeration*>(datum->getPropertyByName("ResizeMode"));
    auto attach = datum->getExtensionByType<Part::AttachExtension>(true);
    const bool plane = length && width && resize && attach;  // Achsen haben keine Breite
    if (plane) {
        Base::BoundBox3d body, picked;
        const auto& objs = attach->AttachmentSupport.getValues();
        const auto& subs = attach->AttachmentSupport.getSubValues();
        for (size_t i = 0; i < objs.size() && i < subs.size(); ++i) {
            if (objs[i]->isDerivedFrom<Part::Feature>()) {  // Ursprungsebenen und -achsen sind unendlich
                const auto opts = Part::ShapeOption::ResolveLink | Part::ShapeOption::Transform;
                body.Add(Part::Feature::getTopoShape(objs[i], opts).getBoundBox());
                if (!subs[i].empty()) {
                    picked.Add(Part::Feature::getTopoShape(objs[i], opts | Part::ShapeOption::NeedSubElement,
                                                           subs[i].c_str())
                                   .getBoundBox());
                }
            }
        }
        if (!body.IsValid()) {
            for (auto b : datum->getDocument()->getObjectsOfType(Design::Body::getClassTypeId())) {
                body.Add(static_cast<Design::Body*>(b)->Shape.getShape().getBoundBox());
            }
        }
        const double size = body.IsValid() ? std::max({body.LengthX(), body.LengthY(), body.LengthZ()}) * 1.2 : 60.0;
        resize->setValue("Manual");
        length->setValue(size);
        width->setValue(size);
        datum->recomputeFeature();
        if (picked.IsValid()) {  // Mitte der Auswahl in die Ebene projiziert, als Verschiebung in der Ebene
            Base::Vector3d c;
            static_cast<App::GeoFeature*>(datum)->Placement.getValue().inverse().multVec(picked.GetCenter(), c);
            const Base::Placement offset = attach->AttachmentOffset.getValue();
            attach->AttachmentOffset.setValue(offset * Base::Placement(Base::Vector3d(c.x, c.y, 0), Base::Rotation()));
        }
    }
    if (auto vp = freecad_cast<Gui::ViewProviderGeometryObject*>(Gui::Application::Instance->getViewProvider(datum))) {
        vp->ShapeAppearance.setDiffuseColor(0.45F, 0.62F, 1.0F);
        vp->Transparency.setValue(plane ? 80 : 0);
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
        toolHint(T(name), T(hint));
        return;
    }
    // Achse einer Zylinder- oder Kegelfläche über eine ihrer Kreiskanten (AxisOfCurvature, auch für Teilflächen
    // wie Rundungen); FreeCAD nähme sonst die Trägheitsachse, die es bei rotationssymmetrischen Flächen nicht gibt
    auto feature = freecad_cast<Part::Feature*>(objs.front());
    if (objs.size() == 1 && feature && std::strcmp(type, "PartDesign::Line") == 0 && subs[0].rfind("Face", 0) == 0) {
        const TopoDS_Shape face = feature->Shape.getShape().getSubShape(subs[0].c_str(), true);
        const auto kind = face.IsNull() ? GeomAbs_OtherSurface : BRepAdaptor_Surface(TopoDS::Face(face)).GetType();
        for (TopExp_Explorer e(face, TopAbs_EDGE); (kind == GeomAbs_Cylinder || kind == GeomAbs_Cone) && e.More(); e.Next()) {
            const std::string edge = elementName(feature->Shape.getShape().getShape(), e.Current());
            if (BRepAdaptor_Curve(TopoDS::Edge(e.Current())).GetType() == GeomAbs_Circle && !edge.empty()) {
                subs[0] = edge;
                break;
            }
        }
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
        toolHint(T(name),
                                 T("This selection does not define a %1. %2")
                                     .arg(T(name), T(hint)));
        return;
    }
    attach->MapMode.setValue(Attacher::AttachEngine::getModeName(suggestion.bestFitMode).c_str());
    Design::folder(Design::componentOf(objs.front()), "Construction")->addObject(datum);
    styleDatum(datum);
    doc->recompute();
    if (!datum->isValid()) {  // passender Modus, aber nicht berechenbar (z. B. Trägheitsachse einer Kugel): nichts Kaputtes anlegen
        doc->abortTransaction();
        toolHint(T(name),
                                 T("This selection does not define a %1. %2").arg(T(name), T(hint)));
        return;
    }
    doc->commitTransaction();
    Gui::Selection().clearSelection();
}

/// Ebene genau zwischen zwei parallelen Ebenen oder ebenen Flächen; bleibt in der Mitte, wenn sich eine verschiebt
/// (Design::Midplane rechnet ihre Lage aus beiden)
void startMidplane(App::Document* doc)
{
    std::vector<App::DocumentObject*> objs;
    std::vector<std::string> subs;
    selectedRefs(objs, subs);
    auto planeOf = [&](size_t i, gp_Pln& pln) {
        const Part::TopoShape s = Part::Feature::getTopoShape(objs[i], Part::ShapeOption::ResolveLink
                                                                       | Part::ShapeOption::Transform | Part::ShapeOption::NeedSubElement,
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
        toolHint(T("Midplane"),
                                 T("Select two parallel planes or planar faces."));
        return;
    }
    doc->openTransaction("Midplane");
    auto plane = static_cast<Design::Midplane*>(doc->addObject("Design::Midplane", "Midplane"));
    plane->Faces.setValues(objs, subs);
    Design::folder(Design::componentOf(objs.front()), "Construction")->addObject(plane);
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
        w->setWindowTitle(T("Measure"));
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
        const Part::Feature* whole = nullptr;  // genau ein ganzer Körper gewählt: Masse anzeigen
        const auto selection = Gui::Selection().getSelectionEx();
        for (auto& sel : selection) {
            std::vector<std::string> names = sel.getSubNames();
            if (names.empty()) {
                names.emplace_back();
                if (selection.size() == 1) {
                    whole = freecad_cast<const Part::Feature*>(sel.getObject());
                }
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
            rows << QStringLiteral("<tr><td style='color:gray; padding-right:12px'>%1</td><td style='white-space:nowrap'><b>%2</b></td></tr>")
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
                    row(T("Length"), length(p.Mass()));
                    BRepAdaptor_Curve curve(TopoDS::Edge(s));
                    if (curve.GetType() == GeomAbs_Circle) {
                        row(T("Radius"), length(curve.Circle().Radius()));
                        row(T("Diameter"), length(2 * curve.Circle().Radius()));
                    }
                    break;
                }
                case TopAbs_FACE: {
                    BRepGProp::SurfaceProperties(s, p);
                    row(T("Area"), QStringLiteral("%1 mm²").arg(p.Mass(), 0, 'f', 2));
                    BRepAdaptor_Surface surface(TopoDS::Face(s));
                    if (surface.GetType() == GeomAbs_Cylinder) {
                        row(T("Radius"), length(surface.Cylinder().Radius()));
                        row(T("Diameter"), length(2 * surface.Cylinder().Radius()));
                    }
                    break;
                }
                default: {
                    BRepGProp::VolumeProperties(s, p);
                    row(T("Volume"), QStringLiteral("%1 mm³").arg(p.Mass(), 0, 'f', 2));
                    if (const double kg = whole ? Design::mass(whole) : 0; kg > 0) {
                        row(T("Mass"), kg < 1 ? QStringLiteral("%1 g").arg(kg * 1000, 0, 'f', 1)
                                              : QStringLiteral("%1 kg").arg(kg, 0, 'f', 3));
                        // Anzeigename wie in der Auswahl des Aussehens-Panels statt des Kartennamens ("Steel-Generic")
                        QString name = whole->ShapeMaterial.getValue().getName();
                        for (const auto& m : Design::physicalMaterials()) {
                            if (whole->ShapeMaterial.getValue().getUUID() == QLatin1String(m.uuid)) {
                                name = QString::fromLatin1(m.name);
                            }
                        }
                        row(T("Material"), T(name.toStdString().c_str()));
                    }
                    const gp_Pnt c = p.CentreOfMass();
                    row(T("Center of mass"), QStringLiteral("%1, %2, %3").arg(length(c.X()), length(c.Y()), length(c.Z())));
                    GProp_GProps area;
                    BRepGProp::SurfaceProperties(s, area);
                    row(T("Area"), QStringLiteral("%1 mm²").arg(area.Mass(), 0, 'f', 2));
                    Bnd_Box box;
                    BRepBndLib::AddOptimal(s, box, false, false);  // ohne Toleranzzugabe: 80 × 40 statt 80,06 × 40,06
                    if (!box.IsVoid()) {
                        double x0, y0, z0, x1, y1, z1;
                        box.Get(x0, y0, z0, x1, y1, z1);
                        row(T("Size"), QStringLiteral("%1 × %2 × %3")
                                                        .arg(length(x1 - x0), length(y1 - y0), length(z1 - z0)));
                    }
                    break;
                }
            }
        }
        else if (shapes.size() == 2) {
            const Design::QuickMeasure m = Design::quickMeasure(shapes);
            if (m.distance >= 0) {
                row(T("Distance"), length(m.distance));
            }
            if (m.angle >= 0) {
                row(T("Angle"), QStringLiteral("%1°").arg(m.angle, 0, 'f', 2));
            }
        }
        result->setText(!rows.isEmpty() ? QStringLiteral("<table>%1</table>").arg(rows.join(QString()))
                        : shapes.size() > 2 ? T("Select one or two items: one shows its sizes, two their distance and angle.")
                                            : T("Select a point, edge, face or body. "
                                                "Select two to measure distance and angle."));
    }
    QLabel* result;
};

/// Phase 11.11 Bezüge, die sich selbst prüfen: alles, was nicht sicher zugeordnet ist (Design::referenceIssues), in
/// einer Liste. Je Zeile Zeigen (wählt den Schritt und die betroffenen Elemente), Bearbeiten (Dialog zum neu Wählen)
/// und bei Warnungen Sieht richtig aus (bestätigen). Leer: "Alle Bezüge sind sicher".
class TaskReferences: public Gui::TaskView::TaskDialog
{
public:
    explicit TaskReferences(App::Document* doc)
        : doc(doc)
    {
        box = new QWidget;
        box->setWindowTitle(T("Check References"));
        box->setObjectName(QStringLiteral("References"));
        new QVBoxLayout(box);
        addTaskBox(box, false);
        refresh();
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
    void refresh()
    {
        for (QWidget* w : box->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly)) {
            w->deleteLater();
        }
        auto lay = static_cast<QVBoxLayout*>(box->layout());
        const auto issues = Design::referenceIssues(doc);
        if (issues.empty()) {
            auto ok = new QLabel(T("All references are certain: every step finds the edges and faces it was made with."));
            ok->setWordWrap(true);
            lay->addWidget(ok);
            return;
        }
        for (const auto& issue : issues) {
            auto row = new QWidget;
            row->setObjectName(QStringLiteral("ReferenceIssue"));
            auto rowLay = new QVBoxLayout(row);
            rowLay->setContentsMargins(0, 4, 0, 8);
            QString text = issue.warning ? T(issue.text.c_str()) : T("Lost reference: %1").arg(QString::fromStdString(issue.element));
            auto label = new QLabel(QStringLiteral("<b>%1</b><br>%2").arg(QString::fromUtf8(issue.object->Label.getValue()).toHtmlEscaped(),
                                                                       text.toHtmlEscaped()));
            label->setWordWrap(true);
            rowLay->addWidget(label);
            auto buttons = new QHBoxLayout;
            const App::DocumentObjectT target(issue.object);
            const auto add = [&buttons](const QString& name, std::function<void()> run) {
                auto b = new QPushButton(name);
                b->setAutoDefault(false);
                QObject::connect(b, &QPushButton::clicked, b, [run] { QTimer::singleShot(0, run); });
                buttons->addWidget(b);
            };
            add(T("Show"), [target] {
                App::DocumentObject* o = target.getObject();
                if (!o) {
                    return;
                }
                Gui::Selection().clearSelection();
                Gui::Selection().addSelection(o->getDocument()->getName(), o->getNameInDocument());
                // betroffene Kanten/Flächen am Körper (Warnung "Kanten nach Lage wiedergefunden")
                auto elements = freecad_cast<App::PropertyStringList*>(o->getPropertyByName("ErrorElements"));
                auto bodies = freecad_cast<App::PropertyLinkList*>(o->getPropertyByName("Bodies"));
                if (elements && bodies && bodies->getSize()) {
                    App::DocumentObject* body = bodies->getValues().front();
                    for (const auto& e : elements->getValues()) {
                        Gui::Selection().addSelection(o->getDocument()->getName(), body->getNameInDocument(), e.c_str());
                    }
                }
            });
            add(T("Edit"), [target] {
                App::DocumentObject* o = target.getObject();
                if (!o) {
                    return;
                }
                Gui::Control().closeDialog();  // ein Dialog zur Zeit: erst die Liste zu, dann der Schritt
                QTimer::singleShot(0, [target] {
                    if (App::DocumentObject* again = target.getObject()) {
                        auto gdoc = Gui::Application::Instance->getDocument(again->getDocument());
                        gdoc->setEdit(gdoc->getViewProvider(again));
                    }
                });
            });
            if (issue.warning) {
                add(T("Looks Right"), [this, target] {
                    App::DocumentObject* o = target.getObject();
                    auto warning = o ? freecad_cast<App::PropertyString*>(o->getPropertyByName("Warning")) : nullptr;
                    if (!warning) {
                        return;
                    }
                    doc->openTransaction("Confirm");
                    warning->setValue("");
                    doc->commitTransaction();
                    refresh();
                });
            }
            buttons->addStretch(1);
            rowLay->addLayout(buttons);
            lay->addWidget(row);
        }
    }

    App::Document* doc;
    QWidget* box = nullptr;
};

void startCheckReferences(App::Document* doc)
{
    Gui::Control().showDialog(new TaskReferences(doc));
}

/// Phase 11.9: Foto wählen, Breite des Teils angeben, Skizze daraus (DesignGui::photoToSketch)
void startPhotoToSketch(App::Document*)
{
    const QString file = QFileDialog::getOpenFileName(Gui::getMainWindow(), T("Photo to Sketch"), QString(),
                                                      T("Images (*.png *.jpg *.jpeg *.bmp *.webp)"));
    if (file.isEmpty()) {
        return;
    }
    askAndTrace(file);
}

/// Material per Ziehen: Kugel oder Chip ziehen, auf einem Körper in der Ansicht loslassen
constexpr const char* MaterialMime = "application/x-mycad-material";

class MaterialDrag: public QObject
{
public:
    MaterialDrag(QAbstractButton* button, std::function<int()> index)
        : QObject(button)
        , index(std::move(index))
    {
        button->installEventFilter(this);
    }

protected:
    bool eventFilter(QObject* obj, QEvent* event) override
    {
        auto button = static_cast<QAbstractButton*>(obj);
        if (event->type() == QEvent::MouseButtonPress) {
            start = static_cast<QMouseEvent*>(event)->position().toPoint();
        }
        else if (event->type() == QEvent::MouseMove && (static_cast<QMouseEvent*>(event)->buttons() & Qt::LeftButton)
                 && (static_cast<QMouseEvent*>(event)->position().toPoint() - start).manhattanLength()
                     >= QApplication::startDragDistance()) {
            auto mime = new QMimeData;
            mime->setData(QLatin1String(MaterialMime), QByteArray::number(index()));
            auto drag = new QDrag(button);
            drag->setMimeData(mime);
            drag->setPixmap(Gui::Shell::materialPreview(index(), 40, button->devicePixelRatioF()));
            drag->setHotSpot(QPoint(20, 20));
            button->setDown(false);
            drag->exec(Qt::CopyAction);
            return true;
        }
        return false;
    }

private:
    std::function<int()> index;
    QPoint start;
};

/// Material auf einen Körper oder einzelne Flächen (Indizes ab 0). Flächen tragen keine Textur (FreeCAD färbt Flächen nur
/// einfarbig), sie bekommen die mittlere Farbe des Fotos.
// ponytail: Je Fläche wechselt in Coin nur die Farbe (Bindung PER_PART), Glanz, Metall und Lack kommen von der ersten
// Fläche. Echte Materialien je Fläche bräuchten eigene Flächen-Gruppen im SoBrepFaceSet.
void applyMaterial(App::DocumentObject* obj, const std::vector<int>& faces, App::Material material)
{
    auto vp = freecad_cast<Gui::ViewProviderGeometryObject*>(Gui::Application::Instance->getViewProvider(obj));
    auto part = freecad_cast<Part::Feature*>(obj);
    if (!vp) {
        return;
    }
    if (faces.empty() || !part) {
        vp->ShapeAppearance.setValue(material);
        // eigene Wahl merken: ein anderes Körper-Material in den Einstellungen färbt nur Körper im Standard-Look um,
        // auch wenn diese Wahl zufällig genauso aussieht (Shell::setBodyMaterial)
        auto flag = freecad_cast<App::PropertyBool*>(obj->getPropertyByName("AppearanceChosen"));
        if (!flag) {
            flag = static_cast<App::PropertyBool*>(obj->addDynamicProperty(
                "App::PropertyBool", "AppearanceChosen", "Design", "Appearance picked by the user", App::Prop_Hidden));
        }
        flag->setValue(true);
        return;
    }
    material.imagePath.clear();
    const auto count = part->Shape.getShape().countSubShapes(TopAbs_FACE);
    std::vector<App::Material> list = vp->ShapeAppearance.getValues();
    if (list.size() != count) {
        list.assign(count, list.empty() ? App::Material() : list.front());
    }
    for (int f : faces) {
        if (f >= 0 && std::size_t(f) < count) {
            list[f] = material;
        }
    }
    vp->ShapeAppearance.setValues(list);
}

/// Aussehen: die Materialbibliothek als Kugeln, gerendert wie im Modell; Varianten einer Oberfläche (Farben, Finish)
/// als Chips darunter. Suche, "In diesem Design", Favoriten (Kontextmenü). Klick wendet auf die Auswahl an, Ziehen auf
/// einen Körper in der Ansicht auch ohne Auswahl. Mit gewählten Flächen: nur diese Flächen oder der ganze Körper.
class TaskAppearance: public Gui::TaskView::TaskDialog
{
public:
    TaskAppearance(App::Document* doc, std::vector<App::DocumentObject*> bodies, std::map<App::DocumentObject*, std::vector<int>> faces)
        : doc(doc)
        , bodies(std::move(bodies))
        , faces(std::move(faces))
        , list(Gui::Shell::bodyMaterialList())
    {
        doc->openTransaction("Appearance");
        auto w = new QWidget;
        w->setWindowTitle(T("Appearance"));
        auto lay = new QVBoxLayout(w);
        auto summary = new QLabel(this->bodies.empty() ? T("Drag a material onto a body, or select bodies first.")
                                  : this->bodies.size() == 1 ? T("%1 selected").arg(QString::fromUtf8(this->bodies.front()->Label.getValue()))
                                                             : T("%1 selected").arg(T("%1 bodies").arg(this->bodies.size())));
        summary->setWordWrap(true);
        lay->addWidget(summary);
        if (!this->faces.empty()) {
            onFaces = true;
            lay->addWidget(Gui::Shell::segmented({T("Faces"), T("Body")}, 0, [this](int i) { onFaces = i == 0; }));
        }
        // Physisches Material (Dichte für Masse): folgt der Appearance, bis man selbst einen Werkstoff wählt
        if (!this->bodies.empty()) {
            auto row = new QHBoxLayout;
            auto label = new QLabel(T("Physical material"));
            physical = new QComboBox;
            physical->setAccessibleName(T("Physical material"));
            physical->addItem(T("From appearance"));
            for (const auto& m : Design::physicalMaterials()) {
                physical->addItem(T(m.name), QString::fromLatin1(m.uuid));
            }
            auto first = freecad_cast<Part::Feature*>(this->bodies.front());
            if (first && Design::physicalMaterialChosen(first)) {
                physical->setCurrentIndex(std::max(0, physical->findData(first->ShapeMaterial.getValue().getUUID())));
            }
            QObject::connect(physical, &QComboBox::currentIndexChanged, physical, [this](int i) {
                for (auto body : this->bodies) {
                    auto part = freecad_cast<Part::Feature*>(body);
                    if (!part) {
                        continue;
                    }
                    if (i > 0) {
                        Design::setPhysicalMaterial(part, physical->itemData(i).toString().toStdString(), true);
                    }
                    else {  // zurück zur Appearance: Werkstoff aus der aktuellen Appearance ableiten
                        auto vp = freecad_cast<Gui::ViewProviderGeometryObject*>(
                            Gui::Application::Instance->getViewProvider(body));
                        const int index = vp ? Gui::Shell::bodyMaterialIndex(vp->ShapeAppearance[0]) : -1;
                        const std::string uuid = index >= 0
                            ? Design::physicalMaterialFor(list[index].name, list[index].category)
                            : std::string();
                        if (!uuid.empty() || Design::physicalMaterialChosen(part)) {
                            Design::setPhysicalMaterial(part, uuid.empty() ? Design::physicalMaterials().front().uuid : uuid,
                                                        false);
                        }
                    }
                }
            });
            row->addWidget(label);
            row->addWidget(physical, 1);
            lay->addLayout(row);
        }
        search = new QLineEdit;
        search->setPlaceholderText(T("Search materials"));
        search->setClearButtonEnabled(true);
        search->setAccessibleName(T("Search materials"));
        lay->addWidget(search);
        content = new QWidget;
        lay->addWidget(content);
        QObject::connect(search, &QLineEdit::textChanged, w, [this] { rebuild(); });
        rebuild();
        addTaskBox(w, false);
        watchDrops();
    }
    ~TaskAppearance() override
    {
        if (viewport) {
            viewport->removeEventFilter(dropFilter);
        }
        delete dropFilter;
    }
    QDialogButtonBox::StandardButtons getStandardButtons() const override
    {
        return QDialogButtonBox::Ok | QDialogButtonBox::Cancel;
    }
    bool accept() override
    {
        doc->commitTransaction();
        return true;
    }
    bool reject() override
    {
        doc->abortTransaction();
        return true;
    }

private:
    static ParameterGrp::handle params()
    {
        return App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD");
    }
    static std::set<int> favorites()
    {
        std::set<int> out;
        for (const QString& n : QString::fromStdString(params()->GetASCII("MaterialFavorites", "")).split(QLatin1Char(','), Qt::SkipEmptyParts)) {
            out.insert(n.toInt());
        }
        return out;
    }
    static void toggleFavorite(int index)
    {
        std::set<int> favs = favorites();
        if (!favs.erase(index)) {
            favs.insert(index);
        }
        QStringList out;
        for (int i : favs) {
            out << QString::number(i);
        }
        params()->SetASCII("MaterialFavorites", out.join(QLatin1Char(',')).toStdString());
    }

    void apply(const App::Material& material)
    {
        for (auto body : bodies) {
            auto f = faces.find(body);
            const bool wholeBody = !(onFaces && f != faces.end());
            applyMaterial(body, wholeBody ? std::vector<int>() : f->second, material);
            // Walnuss -> Holz, PLA -> PLA …: Masse stimmt ohne eigenen Schritt; eine eigene Wahl bleibt stehen
            auto part = freecad_cast<Part::Feature*>(body);
            const int index = Gui::Shell::bodyMaterialIndex(material);
            if (wholeBody && part && index >= 0 && !Design::physicalMaterialChosen(part)) {
                const std::string uuid = Design::physicalMaterialFor(list[index].name, list[index].category);
                if (!uuid.empty()) {
                    Design::setPhysicalMaterial(part, uuid, false);
                }
            }
        }
    }

    /// Materialien, die in diesem Design schon vorkommen (ganze Körper und einzelne Flächen)
    std::vector<int> usedInDesign() const
    {
        std::vector<int> used;
        for (auto obj : doc->getObjectsOfType(Part::Feature::getClassTypeId())) {
            auto vp = freecad_cast<Gui::ViewProviderGeometryObject*>(Gui::Application::Instance->getViewProvider(obj));
            if (!vp || !obj->isDerivedFrom<Design::Body>()) {
                continue;
            }
            for (const auto& m : vp->ShapeAppearance.getValues()) {
                const int i = Gui::Shell::bodyMaterialIndex(m);
                if (i >= 0 && std::ranges::find(used, i) == used.end()) {
                    used.push_back(i);
                }
            }
        }
        return used;
    }

    bool matches(int i, const QString& text) const
    {
        const auto& e = list[i];
        for (const char* s : {e.name, e.family, e.category}) {
            if (QString::fromLatin1(s).contains(text, Qt::CaseInsensitive) || T(s).contains(text, Qt::CaseInsensitive)) {
                return true;
            }
        }
        return false;
    }

    /// Kugel mit Namen, darunter die Varianten als Chips; Klick auf einen Chip zeigt ihn auch in der Kugel
    QWidget* tile(const std::vector<int>& variants, bool familyName)
    {
        const qreal ratio = content->devicePixelRatioF();
        auto box = new QWidget;
        auto column = new QVBoxLayout(box);
        column->setContentsMargins(0, 0, 0, 0);
        column->setSpacing(4);
        auto sphere = new QToolButton;
        const QSize size(56, 56);
        sphere->setIconSize(size);
        sphere->setStyleSheet(Gui::Shell::themed(QStringLiteral("QToolButton { padding: 0; background: transparent; border-radius: 30px; "
                                                                "border: 2px solid transparent; }"
                                                                "QToolButton:hover, QToolButton:focus { border: 2px solid @focusRing; }")));
        auto caption = new QLabel;
        caption->setWordWrap(true);
        caption->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
        caption->setFont(Gui::Shell::textFont(Gui::Shell::Text::Caption));
        auto shown = std::make_shared<int>(variants.front());
        auto show = [=, this](int i) {
            *shown = i;
            sphere->setIcon(Gui::Shell::materialPreview(i, size.width(), ratio));
            sphere->setToolTip(T(list[i].name));
            sphere->setAccessibleName(T(list[i].name));
            caption->setText(T(familyName ? list[i].family : list[i].name));
        };
        show(variants.front());
        new MaterialDrag(sphere, [shown] { return *shown; });
        QObject::connect(sphere, &QToolButton::clicked, box, [this, shown] { apply(Gui::Shell::bodyMaterialAppearance(*shown)); });
        sphere->setContextMenuPolicy(Qt::CustomContextMenu);
        QObject::connect(sphere, &QWidget::customContextMenuRequested, box, [this, shown, sphere](const QPoint& at) {
            QMenu menu;
            const bool fav = favorites().contains(*shown);
            menu.addAction(fav ? T("Remove from Favorites") : T("Add to Favorites"), [this, shown] {
                toggleFavorite(*shown);
                QTimer::singleShot(0, content, [this] { rebuild(); });
            });
            menu.exec(sphere->mapToGlobal(at));
        });
        column->addWidget(sphere, 0, Qt::AlignHCenter);
        column->addWidget(caption);
        if (variants.size() > 1) {
            auto chips = new QGridLayout;
            chips->setSpacing(4);
            int n = 0;
            for (int i : variants) {
                auto chip = new QToolButton;
                chip->setFixedSize(Gui::Shell::Token::IconL, Gui::Shell::Token::IconL);
                chip->setIconSize(QSize(Gui::Shell::Token::IconM, Gui::Shell::Token::IconM));
                chip->setIcon(Gui::Shell::materialPreview(i, Gui::Shell::Token::IconM, ratio));
                chip->setToolTip(T(list[i].name));
                chip->setAccessibleName(T(list[i].name));
                chip->setStyleSheet(Gui::Shell::themed(QStringLiteral("QToolButton { padding: 0; background: transparent; border-radius: 10px; "
                                                                      "border: 1px solid @separator; }"
                                                                      "QToolButton:hover, QToolButton:focus { border: 2px solid @focusRing; }")));
                new MaterialDrag(chip, [i] { return i; });
                QObject::connect(chip, &QToolButton::clicked, box, [this, show, i] {
                    show(i);
                    apply(Gui::Shell::bodyMaterialAppearance(i));
                });
                chips->addWidget(chip, n / 4, n % 4);
                ++n;
            }
            column->addLayout(chips);
            column->setAlignment(chips, Qt::AlignHCenter);
        }
        column->addStretch();
        return box;
    }

    void section(QVBoxLayout* lay, const QString& title, const std::vector<std::vector<int>>& tiles, bool familyNames)
    {
        if (tiles.empty()) {
            return;
        }
        auto label = Gui::Shell::sectionLabel(title);
        label->setContentsMargins(0, 8, 0, 4);
        lay->addWidget(label);
        auto grid = new QGridLayout;
        grid->setSpacing(8);
        for (int column = 0; column < 3; ++column) {
            grid->setColumnStretch(column, 1);  // gleich breite Spalten
        }
        for (int i = 0; i < int(tiles.size()); ++i) {
            grid->addWidget(tile(tiles[i], familyNames), i / 3, i % 3);
        }
        lay->addLayout(grid);
    }

    void rebuild()
    {
        auto fresh = new QWidget;
        auto lay = new QVBoxLayout(fresh);
        lay->setContentsMargins(0, 0, 0, 0);
        content->parentWidget()->layout()->replaceWidget(content, fresh);
        content->hide();  // sofort weg, gelöscht wird später
        content->deleteLater();
        content = fresh;
        fresh->show();
        const QString text = search->text().trimmed();
        auto single = [&](const auto& indices) {
            std::vector<std::vector<int>> out;
            for (int i : indices) {
                if (text.isEmpty() || matches(i, text)) {
                    out.push_back({i});
                }
            }
            return out;
        };
        section(lay, T("In this design"), single(usedInDesign()), false);
        section(lay, T("Favorites"), single(favorites()), false);
        // je Gruppe der Bibliothek die Oberflächen (Familien) in der Reihenfolge der Tabelle
        std::vector<QString> categories;
        for (const auto& e : list) {
            if (std::ranges::find(categories, QLatin1String(e.category)) == categories.end()) {
                categories.emplace_back(QLatin1String(e.category));
            }
        }
        for (const QString& category : categories) {
            std::vector<std::vector<int>> families;
            std::vector<QString> names;
            for (int i = 0; i < int(list.size()); ++i) {
                if (category != QLatin1String(list[i].category) || (!text.isEmpty() && !matches(i, text))) {
                    continue;
                }
                const QString family = QLatin1String(list[i].family);
                auto known = std::ranges::find(names, family);
                if (known == names.end()) {
                    names.push_back(family);
                    families.push_back({i});
                }
                else {
                    families[known - names.begin()].push_back(i);
                }
            }
            section(lay, T(category.toLatin1().constData()), families, true);
        }
        if (text.isEmpty()) {
            colors(lay);
        }
        else if (lay->count() == 0) {
            auto none = new QLabel(T("No material matches “%1”.").arg(text));
            none->setWordWrap(true);
            lay->addWidget(none);
        }
    }

    /// Eigene Farbe: die Systemfarben als Kunststoff
    void colors(QVBoxLayout* lay)
    {
        auto label = Gui::Shell::sectionLabel(T("Color"));
        label->setContentsMargins(0, 8, 0, 4);
        lay->addWidget(label);
        auto swatches = new QGridLayout;
        swatches->setSpacing(8);
        const char* hexes[] = {"#FF3B30", "#FF9500", "#FFCC00", "#34C759", "#00C7BE", "#30B0C7", "#007AFF",
                               "#5856D6", "#AF52DE", "#FF2D55", "#A2845E", "#8E8E93", "#F2F2F7", "#1C1C1E"};
        int i = 0;
        for (const char* hex : hexes) {
            auto swatch = new QToolButton;
            swatch->setFixedSize(30, 30);
            swatch->setToolTip(QString::fromLatin1(hex));
            // Farbfelder sind Inhalt (Körperfarben), nur Rand und Hover-Ring kommen aus dem Theme
            swatch->setStyleSheet(Gui::Shell::themed(QStringLiteral("QToolButton { background: %1; border-radius: 15px; "
                                                                     "border: 1px solid @separator; }"
                                                                     "QToolButton:hover, QToolButton:focus { border: 2px solid @focusRing; }"))
                                      .arg(QString::fromLatin1(hex)));
            swatch->setAccessibleName(QString::fromLatin1(hex));
            const QColor c(QString::fromLatin1(hex));
            QObject::connect(swatch, &QToolButton::clicked, swatch, [this, c] {
                App::Material material(App::Material::PLASTIC);
                material.diffuseColor = Base::Color(float(c.redF()), float(c.greenF()), float(c.blueF()));
                material.emissiveColor = Base::Color(0, 0, 1 / 255.0F);  // Markierung: kein Metall (BodyShading.h)
                apply(material);
            });
            swatches->addWidget(swatch, i / 7, i % 7);
            ++i;
        }
        lay->addLayout(swatches);
    }

    /// Ablegen auf der 3D-Ansicht: Körper (oder mit "Flächen" die Fläche) unter dem Mauszeiger bekommt das Material
    void watchDrops()
    {
        auto gdoc = Gui::Application::Instance->getDocument(doc);
        auto view = gdoc ? dynamic_cast<Gui::View3DInventor*>(gdoc->getActiveView()) : nullptr;
        if (!view) {
            return;
        }
        Gui::View3DInventorViewer* viewer = view->getViewer();
        viewport = viewer->viewport();
        dropFilter = new DropFilter([this, viewer](QDropEvent* e) {
            bool number = false;  // die Daten können auch aus einem anderen Programm kommen
            const int index = e->mimeData()->data(QLatin1String(MaterialMime)).toInt(&number);
            if (!number || index < 0 || index >= int(list.size())) {
                return false;
            }
            const QPoint at = e->position().toPoint();
            std::unique_ptr<SoPickedPoint> pp(viewer->pickPoint(viewer->fromQPoint(at)));
            // wie die Auswahl: Treffer in der Komponente ("Body001.Face6") zum Körper und seiner Fläche auflösen
            auto vp = dynamic_cast<Gui::ViewProviderDocumentObject*>(pp ? viewer->getViewProviderByPath(pp->getPath()) : nullptr);
            std::string sub;
            if (!vp || !vp->getElementPicked(pp.get(), sub)) {
                return false;
            }
            App::ElementNamePair element;
            App::DocumentObject* obj = App::GeoFeature::resolveElement(vp->getObject(), sub.c_str(), element);
            if (!obj || !obj->isDerivedFrom<Part::Feature>()) {
                return false;
            }
            std::vector<int> face;
            if (onFaces && element.oldName.starts_with("Face")) {
                face.push_back(std::atoi(element.oldName.c_str() + 4) - 1);
            }
            applyMaterial(obj, face, Gui::Shell::bodyMaterialAppearance(index));
            return true;
        });
        viewport->setAcceptDrops(true);
        viewport->installEventFilter(dropFilter);
    }

    class DropFilter: public QObject
    {
    public:
        explicit DropFilter(std::function<bool(QDropEvent*)> drop)
            : drop(std::move(drop))
        {}

    protected:
        bool eventFilter(QObject*, QEvent* event) override
        {
            const auto type = event->type();
            if (type != QEvent::DragEnter && type != QEvent::DragMove && type != QEvent::Drop) {
                return false;
            }
            auto e = static_cast<QDropEvent*>(event);
            if (!e->mimeData()->hasFormat(QLatin1String(MaterialMime))) {
                return false;  // Dateien usw. wie bisher
            }
            if (type != QEvent::Drop || drop(e)) {
                e->acceptProposedAction();
            }
            return true;
        }

    private:
        std::function<bool(QDropEvent*)> drop;
    };

    App::Document* doc;
    std::vector<App::DocumentObject*> bodies;
    std::map<App::DocumentObject*, std::vector<int>> faces;  ///< gewählte Flächen je Körper
    std::vector<Gui::Shell::BodyMaterialEntry> list;
    bool onFaces = false;
    QLineEdit* search;
    QComboBox* physical = nullptr;
    QWidget* content;
    QPointer<QWidget> viewport;
    DropFilter* dropFilter = nullptr;
};

void startAppearance(App::Document* doc)
{
    std::vector<App::DocumentObject*> bodies;
    std::map<App::DocumentObject*, std::vector<int>> faces;
    for (auto b : selectedBodies()) {
        bodies.push_back(b);
    }
    for (auto& sel : Gui::Selection().getSelectionEx(doc->getName())) {
        for (const std::string& sub : sel.getSubNames()) {
            if (sub.starts_with("Face") && std::ranges::find(bodies, sel.getObject()) != bodies.end()) {
                faces[sel.getObject()].push_back(std::atoi(sub.c_str() + 4) - 1);
            }
        }
    }
    Gui::Selection().clearSelection();
    Gui::Control().showDialog(new TaskAppearance(doc, bodies, faces));
}

/// Parameter wie in Fusion ("Change Parameters"): Name und Ausdruck ("40 mm", "Width / 10"); Maßfelder der
/// Features nehmen diese Namen an. Änderungen wirken sofort, Abbrechen nimmt alle zurück.
/// value: Messwert aus "Messen ohne Werkzeug", steht schon im Wertfeld; der Name fehlt noch
void showParametersWith(App::Document* doc, const QString& value)
{
    doc->openTransaction("Parameters");
    App::DocumentObject* set = DesignGui::parameters(doc, true);
    QDialog dlg(Gui::getMainWindow());
    dlg.setWindowTitle(T("Parameters"));
    dlg.setMinimumSize(520, 360);
    auto lay = new QVBoxLayout(&dlg);
    lay->setContentsMargins(24, 20, 24, 20);
    auto hint = new QLabel(T("Use the names in any dimension field, e.g. “Width * 2”."));
    hint->setWordWrap(true);
    lay->addWidget(hint);
    auto table = new QTableWidget(0, 4);
    table->setHorizontalHeaderLabels({T("Name"), T("Expression"), T("Value"), QString()});
    table->verticalHeader()->hide();
    table->setShowGrid(false);
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);  // Breite der Knöpfe setzt refresh
    lay->addWidget(table);
    auto error = new QLabel;  // unter der Eingabezeile, auch für Fehler in der Tabelle
    error->setWordWrap(true);
    error->setStyleSheet(QStringLiteral("color: %1;").arg(Gui::Shell::theme().red.name()));

    auto names = [set] {
        std::vector<App::Property*> props;
        set->getPropertyList(props);
        std::vector<std::string> result;
        for (auto prop : props) {
            if (prop->getGroup() && std::strcmp(prop->getGroup(), "Parameters") == 0) {
                result.emplace_back(prop->getName());
            }
        }
        return result;
    };
    std::function<void()> refresh;
    // wie in der Notiz: Namen mit Umlauten, Dezimalkomma; was keinen Wert ergibt, wirft
    auto setExpression = [set, doc](const std::string& name, const QString& text) {
        Design::setParameterExpression(set, set->getPropertyByName(name.c_str()), text.toStdString());
        doc->recompute();
    };
    refresh = [&, set, table] {
        table->blockSignals(true);
        table->setRowCount(0);
        int buttonWidth = 0;
        for (const auto& name : names()) {
            auto prop = static_cast<App::PropertyQuantity*>(set->getPropertyByName(name.c_str()));
            const int r = table->rowCount();
            table->insertRow(r);
            const char* written = prop->getDocumentation();  // geschriebener Name, z. B. "Wandstärke"
            const QString shown = QString::fromUtf8(written && *written ? written : name.c_str());
            auto nameItem = new QTableWidgetItem(shown);
            nameItem->setFlags(Qt::ItemIsEnabled);
            nameItem->setData(Qt::UserRole, QString::fromStdString(name));
            table->setItem(r, 0, nameItem);
            const auto info = set->getExpression(App::ObjectIdentifier(*prop));
            auto expression = new QTableWidgetItem(
                info.expression ? QString::fromStdString(Design::fromParameterExpression(doc, info.expression->toString()))
                                : QString());
            table->setItem(r, 1, expression);
            auto value = new QTableWidgetItem(QString::fromStdString(prop->getQuantityValue().getUserString()));
            value->setFlags(Qt::ItemIsEnabled);
            table->setItem(r, 2, value);
            // aus einer Notiz (Idee 3): dort steht er, dort wird er gelöscht
            const App::DocumentObject* source = nullptr;
            for (auto note : doc->getObjectsOfType(Design::Note::getClassTypeId())) {
                const auto& defined = static_cast<Design::Note*>(note)->Defines.getValues();
                if (std::ranges::find(defined, name) != defined.end()) {
                    source = note;
                }
            }
            if (source) {
                // geändert wird in der Notiz, sonst liefen Notiz und Tabelle auseinander
                expression->setFlags(Qt::ItemIsEnabled);
                auto from = new QLabel(T("In note %1").arg(QString::fromUtf8(source->Label.getValue())));
                from->setContentsMargins(8, 0, 8, 0);
                table->setCellWidget(r, 3, from);
                buttonWidth = std::max(buttonWidth, from->sizeHint().width());
                continue;
            }
            auto remove = new QPushButton(T("Remove"));
            remove->setAutoDefault(false);
            // destruktiv: Text system.red (MyStyle 9.3)
            remove->setStyleSheet(QStringLiteral("color: %1;").arg(Gui::Shell::theme().red.name()));
            QObject::connect(remove, &QPushButton::clicked, table, [&, set, name, shown] {
                // ein gebrauchter Parameter bleibt: die Formeln, die ihn nennen, ergäben sonst keinen Wert mehr
                const auto users = Design::parameterUsers(set, name);
                if (!users.empty()) {
                    QStringList labels;
                    for (const auto& u : users) {
                        labels << QString::fromUtf8(u.c_str());
                    }
                    error->setText(T("“%1” is still used by %2. Change that formula first.").arg(shown, labels.join(QStringLiteral(", "))));
                    return;
                }
                error->clear();
                set->removeDynamicProperty(name.c_str());
                doc->recompute();
                QTimer::singleShot(0, table, [&] { refresh(); });
            });
            table->setCellWidget(r, 3, remove);
            buttonWidth = std::max(buttonWidth, remove->sizeHint().width());
        }
        // ResizeToContents misst die Knöpfe in den Zellen nicht mit ("Remove" wurde zu "emove")
        table->horizontalHeader()->resizeSection(3, buttonWidth + 8);
        table->blockSignals(false);
    };
    QObject::connect(table, &QTableWidget::itemChanged, table, [&, table](QTableWidgetItem* item) {
        if (item->column() != 1) {
            return;
        }
        const std::string name = table->item(item->row(), 0)->data(Qt::UserRole).toString().toStdString();
        try {
            setExpression(name, item->text());
            error->clear();
        }
        catch (const Base::Exception&) {
            error->setText(T("“%1” is not a value or formula. Write e.g. 40 mm or Width / 4.").arg(item->text()));
        }
        QTimer::singleShot(0, table, [&] { refresh(); });
    });

    auto row = new QHBoxLayout;
    auto nameEdit = new QLineEdit;
    nameEdit->setPlaceholderText(T("Name, e.g. Width"));
    auto exprEdit = new QLineEdit;
    exprEdit->setPlaceholderText(T("Value, e.g. 40 mm"));
    auto add = new QPushButton(T("Add"));
    add->setAutoDefault(false);
    row->addWidget(nameEdit);
    row->addWidget(exprEdit);
    row->addWidget(add);
    lay->addLayout(row);
    lay->addWidget(error);
    QObject::connect(add, &QPushButton::clicked, &dlg, [&, set] {
        // Namen wie in der Notiz: "Wandstärke" wird zur Property "Wandstaerke", angezeigt wird der geschriebene
        static const QRegularExpression valid(QStringLiteral("^[A-Za-z_][A-Za-z0-9_]*$"));
        const QString name = nameEdit->text().trimmed();
        const std::string id = NoteParameters::identifier(name.toStdString());
        if (!valid.match(QString::fromStdString(id)).hasMatch() || set->getPropertyByName(id.c_str())) {
            error->setText(T("Use a new name of letters, digits and _ (no spaces)."));
            return;
        }
        if (!App::ExpressionParser::isTokenAnIndentifier(id)) {  // "mm", "h", "pi": in Formeln nicht lesbar
            error->setText(T("“%1” is a unit or a constant. Choose another name.").arg(name));
            return;
        }
        const QString text = exprEdit->text().trimmed().isEmpty() ? QStringLiteral("0 mm") : exprEdit->text();
        set->addDynamicProperty("App::PropertyQuantity", id.c_str(), "Parameters", name.toUtf8().constData());
        try {
            setExpression(id, text);
            error->clear();
            nameEdit->clear();
            exprEdit->clear();
        }
        catch (const Base::Exception&) {
            set->removeDynamicProperty(id.c_str());
            error->setText(T("“%1” is not a value or formula. Write e.g. 40 mm or Width / 4.").arg(text));
        }
        refresh();
    });
    refresh();

    auto buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    QObject::connect(buttons, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    QObject::connect(buttons, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);
    lay->addWidget(buttons);
    if (!value.isEmpty()) {
        exprEdit->setText(value);
        nameEdit->setFocus();
        add->setDefault(true);  // Name tippen, Enter legt an
    }
    if (dlg.exec() == QDialog::Accepted) {
        doc->commitTransaction();
    }
    else {
        doc->abortTransaction();
        doc->recompute();
    }
}

void showParameters(App::Document* doc)
{
    showParametersWith(doc, QString());
}

void startMeasure(App::Document*)
{
    Gui::Control().showDialog(new TaskMeasure);
}

/// Messen ohne Werkzeug (Phase 11.4): zwei gewählte Elemente (oder ein Kreis/Zylinder) zeigen sofort Abstand, Winkel
/// oder Durchmesser als kleine Glas-Karte daneben. Ein Klick auf einen Wert legt damit einen Parameter an. Nur ohne
/// offenes Werkzeug und außerhalb der Skizze; jede andere Auswahl schließt die Karte.
class QuickMeasureChip: public Gui::SelectionObserver
{
public:
    QuickMeasureChip()
    {
        // die Kamera bewegt die Karte (CameraFollow); ein geöffnetes Werkzeug ändert nicht immer die Auswahl (H5: Signal)
        QObject::connect(&Gui::Control(), &Gui::ControlSingleton::dialogChanged, &follow, [this] {
            if (Gui::Control().activeDialog()) {
                hide();
            }
        }, Qt::QueuedConnection);
    }

private:
    void onSelectionChanged(const Gui::SelectionChanges& msg) override
    {
        if (msg.Type == Gui::SelectionChanges::AddSelection || msg.Type == Gui::SelectionChanges::RmvSelection
            || msg.Type == Gui::SelectionChanges::ClrSelection || msg.Type == Gui::SelectionChanges::SetSelection) {
            QTimer::singleShot(0, &follow, [this] { refresh(); });
        }
    }

    void hide()
    {
        follow.stop();
        if (panel) {
            panel->hide();
        }
    }

    void refresh()
    {
        hide();
        std::vector<TopoDS_Shape> shapes;
        App::Document* doc = nullptr;
        for (const auto& sel : Gui::Selection().getSelectionEx()) {
            doc = sel.getObject() ? sel.getObject()->getDocument() : nullptr;
            for (const auto& name : sel.getSubNames()) {
                const Part::TopoShape s = Part::Feature::getTopoShape(
                    sel.getObject(), Part::ShapeOption::ResolveLink | Part::ShapeOption::Transform
                                         | Part::ShapeOption::NeedSubElement, name.c_str());
                if (s.isNull() || shapes.size() == 2) {
                    return;  // mehr als zwei Elemente: nichts zu zeigen
                }
                shapes.push_back(s.getShape());
            }
        }
        auto gdoc = doc ? Gui::Application::Instance->getDocument(doc) : nullptr;
        if (shapes.empty() || !gdoc || gdoc->getInEdit() || Gui::Control().activeDialog()) {
            return;
        }
        measured = Design::quickMeasure(shapes);
        auto view = dynamic_cast<Gui::View3DInventor*>(gdoc->getActiveView());
        viewer = view ? view->getViewer() : nullptr;
        // Abstand null zwischen zwei Elementen, die sich berühren, sagt nichts; dann zählt nur der Winkel
        if (measured.distance < 1e-7 && measured.angle >= 0) {
            measured.distance = -1;
        }
        // parallel (0°) sagt neben dem Abstand nichts
        if (measured.angle >= 0 && measured.angle < 1e-6 && measured.distance >= 0) {
            measured.angle = -1;
        }
        if (!viewer || (measured.distance < 0 && measured.angle < 0 && measured.diameter < 0)) {
            return;
        }
        build(doc);
        place();
        panel->show();
        QCoreApplication::sendPostedEvents(content);  // Schrift und Stil der Szene, erst dann stimmt die Größe
        for (QWidget* w : content->findChildren<QWidget*>()) {
            QCoreApplication::sendPostedEvents(w);
        }
        content->adjustSize();
        place();
        follow.start(viewer);
    }

    void build(App::Document* doc)
    {
        if (!panel) {
            content = new QWidget;
            content->setObjectName(QStringLiteral("QuickMeasure"));
            auto lay = new QHBoxLayout(content);
            lay->setContentsMargins(6, 4, 6, 4);
            lay->setSpacing(2);
            panel = new Gui::Shell::GlassPanel(content, Gui::Shell::Token::RadiusTile, true);
            panel->setZValue(9);
        }
        if (panel->scene() != viewer->scene()) {
            viewer->scene()->addItem(panel);
        }
        for (QWidget* w : content->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly)) {
            delete w;
        }
        const auto length = [](double v) {
            return QString::fromStdString(Base::Quantity(v, Base::Unit::Length).getUserString());
        };
        // Anzeige in der Einheit des Benutzers, als Parameter eine Zahl, die jede Formel liest (Punkt, keine Rundung)
        const std::tuple<double, QString, QString, const char*> values[] = {
            {measured.distance, length(measured.distance), QStringLiteral("%1 mm"), "Distance"},
            {measured.angle, QStringLiteral("∠ %1°").arg(measured.angle, 0, 'f', 2), QStringLiteral("%1 °"), "Angle"},
            {measured.diameter, QStringLiteral("⌀ ") + length(measured.diameter), QStringLiteral("%1 mm"), "Diameter"}};
        const App::DocumentT target(doc);
        for (const auto& [value, text, expression, label] : values) {
            if (value < 0) {
                continue;
            }
            auto button = new QPushButton(text);
            button->setObjectName(QStringLiteral("QuickMeasureValue"));
            button->setFlat(true);
            button->setAutoDefault(false);
            button->setCursor(Qt::PointingHandCursor);
            button->setAccessibleName(T(label));
            button->setToolTip(T("%1: click to use it as a parameter").arg(T(label)));
            const QString parameter = expression.arg(QString::number(value, 'g', 10));
            QObject::connect(button, &QPushButton::clicked, button, [this, target, parameter] {
                hide();
                QTimer::singleShot(0, [target, parameter] {  // modal: erst nach dem Klick öffnen
                    if (App::Document* d = target.getDocument()) {
                        showParametersWith(d, parameter);
                    }
                });
            });
            content->layout()->addWidget(button);
        }
        content->adjustSize();
    }

    /// unter dem Messpunkt, im Fenster gehalten (rechts daneben steht nach Doppelklick die Karte der Flächen-Maße)
    void place()
    {
        if (!panel || !viewer || !panel->isVisible()) {
            return;
        }
        const Base::Vector3d& a = measured.anchor;
        const QPoint p = viewer->toQPoint(viewer->getPointOnViewport(SbVec3f(float(a.x), float(a.y), float(a.z))));
        const QSizeF s = content->sizeHint();
        const QRectF view = viewer->scene()->sceneRect();
        const qreal x = std::clamp<qreal>(p.x() - s.width() / 2, view.left() + 12, view.right() - s.width() - 12);
        const qreal y = std::clamp<qreal>(p.y() + 20, view.top() + 80, view.bottom() - s.height() - 80);
        panel->setGeometry(QRectF(x, y, s.width(), s.height()));
    }

    Design::QuickMeasure measured;
    QPointer<Gui::View3DInventorViewer> viewer;
    QPointer<Gui::Shell::GlassPanel> panel;  // stirbt mit der Szene eines geschlossenen Designs
    QWidget* content = nullptr;
    DesignGui::CameraFollow follow {[this] { place(); }};
};

/// Kontext-Leiste (Phase 12.2): die paar Werkzeuge, die zur Auswahl passen, als Glas-Kapsel direkt über ihr (die
/// Messkarte steht darunter). Profil → Extrude, Revolve …; ebene Fläche → Press Pull, Skizze, Bohrung …; runde Fläche →
/// Gewinde, Passung …; Kante → Rundung, Fase; ganzer Körper → Bewegen, Spiegeln, Muster …; Ebene → Skizze. "Suchen"
/// am Ende öffnet alle Befehle. Nur ohne offenes Werkzeug, außerhalb von Skizze und Scribble; abschaltbar
/// (Einstellungen › Allgemein › Werkzeuge an der Auswahl).
class ContextBar: public Gui::SelectionObserver
{
public:
    ContextBar()
    {
        QObject::connect(&Gui::Control(), &Gui::ControlSingleton::dialogChanged, &follow, [this] {
            if (Gui::Control().activeDialog()) {
                hide();
            }
        }, Qt::QueuedConnection);
    }

    /// Befehle zur aktuellen Auswahl, in dieser Reihenfolge; leer = keine Leiste
    static std::vector<const char*> commandsForSelection()
    {
        enum class Kind
        {
            None,
            Profile,
            FlatFaces,
            CurvedFaces,
            Edges,
            Bodies,
            Plane
        } kind = Kind::None;
        bool mixed = false;
        int bodies = 0;
        const auto is = [&](Kind k) {
            mixed = mixed || (kind != Kind::None && kind != k);
            kind = k;
        };
        for (auto& sel : Gui::Selection().getSelectionEx()) {
            App::DocumentObject* obj = sel.getObject();
            if (!obj) {
                continue;
            }
            const auto& subs = sel.getSubNames();
            if (obj->isDerivedFrom<Design::Profiles>() || obj->isDerivedFrom<Sketcher::SketchObject>()) {
                is(Kind::Profile);
            }
            else if (obj->isDerivedFrom<Design::Body>()) {
                ++bodies;
                if (subs.empty()) {
                    is(Kind::Bodies);
                }
                for (const std::string& s : subs) {
                    if (s.rfind("Edge", 0) == 0) {
                        is(Kind::Edges);
                    }
                    else if (s.rfind("Face", 0) == 0) {
                        is(isPlanarFace(obj, s) ? Kind::FlatFaces : Kind::CurvedFaces);
                    }
                    else {
                        mixed = true;  // Ecken: nichts Eindeutiges anzubieten
                    }
                }
            }
            else if (obj->isDerivedFrom<App::Plane>() || obj->getTypeId().isDerivedFrom(Base::Type::fromName("PartDesign::Plane"))) {
                is(Kind::Plane);
            }
            else {
                mixed = true;
            }
        }
        if (mixed) {
            return {};
        }
        switch (kind) {
            case Kind::Profile:
                return {"Design_Extrude", "Design_Revolve", "Design_Sweep", "Design_Loft", "MyCAD_Search"};
            case Kind::FlatFaces:
                return {"Design_PressPull", "Design_CreateSketch", "Design_Hole", "Design_Shell", "Design_Appearance", "MyCAD_Search"};
            case Kind::CurvedFaces:
                return {"Design_PressPull", "Design_Thread", "Design_Fit", "Design_Appearance", "MyCAD_Search"};
            case Kind::Edges:
                return {"Design_Fillet", "Design_Chamfer", "MyCAD_Search"};
            case Kind::Bodies:
                if (bodies >= 2) {
                    return {"Design_Combine", "Design_Move", "Design_Mirror", "Design_Pattern", "Design_Appearance", "MyCAD_Search"};
                }
                return {"Design_Move", "Design_Mirror", "Design_Pattern", "Design_Shell", "Design_Appearance", "MyCAD_Search"};
            case Kind::Plane:
                return {"Design_CreateSketch", "Design_OffsetPlane", "MyCAD_Search"};
            default:
                return {};
        }
    }

private:
    void onSelectionChanged(const Gui::SelectionChanges& msg) override
    {
        if (msg.Type == Gui::SelectionChanges::AddSelection || msg.Type == Gui::SelectionChanges::RmvSelection
            || msg.Type == Gui::SelectionChanges::ClrSelection || msg.Type == Gui::SelectionChanges::SetSelection) {
            QTimer::singleShot(0, &follow, [this] { refresh(); });
        }
    }

    void hide()
    {
        follow.stop();
        if (panel) {
            panel->hide();
        }
    }

    void refresh()
    {
        hide();
        const auto selection = Gui::Selection().getSelectionEx();
        App::Document* doc = selection.empty() || !selection.back().getObject() ? nullptr : selection.back().getObject()->getDocument();
        auto gdoc = doc ? Gui::Application::Instance->getDocument(doc) : nullptr;
        if (!gdoc || gdoc->getInEdit() || Gui::Control().activeDialog()
            || !App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD")->GetBool("ContextBar", true)) {
            return;
        }
        std::vector<const char*> commands;
        for (const char* name : commandsForSelection()) {
            if (Gui::Shell::actionOf(name)) {
                commands.push_back(name);
            }
        }
        auto view = dynamic_cast<Gui::View3DInventor*>(gdoc->getActiveView());
        viewer = view ? view->getViewer() : nullptr;
        if (commands.empty() || !viewer || !anchorOf(selection)) {
            return;
        }
        build(commands);
        panel->show();
        // wie die Messkarte: erst Schrift und Stil der Szene an alle Knöpfe, dann messen; sonst stand die Leiste mit
        // der Größe vor dem Stil (8 × 9 px) und wuchs danach über den angeklickten Punkt
        QCoreApplication::sendPostedEvents(content);
        for (QWidget* w : content->findChildren<QWidget*>()) {
            QCoreApplication::sendPostedEvents(w);
        }
        content->adjustSize();
        place();
        QTimer::singleShot(0, &follow, [this] { place(); });
        follow.start(viewer);
    }

    /// Wo die Leiste hingehört: der zuletzt angeklickte Punkt, sonst die Mitte der Auswahl (gewählt im Browser)
    bool anchorOf(const std::vector<Gui::SelectionObject>& selection)
    {
        for (auto it = selection.rbegin(); it != selection.rend(); ++it) {
            if (!it->getPickedPoints().empty()) {
                anchor = it->getPickedPoints().back();
                return true;
            }
        }
        Base::BoundBox3d box;
        for (const auto& sel : selection) {
            const auto& subs = sel.getSubNames();
            for (size_t i = 0; i < std::max<size_t>(1, subs.size()); ++i) {
                const Part::TopoShape s = Part::Feature::getTopoShape(
                    sel.getObject(), Part::ShapeOption::ResolveLink | Part::ShapeOption::Transform
                                         | (subs.empty() ? Part::ShapeOption::NoFlag : Part::ShapeOption::NeedSubElement),
                    subs.empty() ? nullptr : subs[i].c_str());
                if (!s.isNull()) {
                    box.Add(s.getBoundBox());
                }
            }
        }
        if (!box.IsValid()) {
            return false;
        }
        anchor = box.GetCenter();
        return true;
    }

    void build(const std::vector<const char*>& commands)
    {
        if (!panel) {
            content = new QWidget;
            content->setObjectName(QStringLiteral("GlassContent"));
            auto lay = new QHBoxLayout(content);
            lay->setContentsMargins(4, 4, 4, 4);
            lay->setSpacing(2);
            panel = new Gui::Shell::GlassPanel(content, Gui::Shell::Token::RadiusCapsule);
            panel->setZValue(9);
        }
        if (panel->scene() != viewer->scene()) {
            viewer->scene()->addItem(panel);
        }
        for (QWidget* w : content->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly)) {
            delete w;
        }
        for (const char* name : commands) {
            QAction* action = Gui::Shell::actionOf(name);
            auto button = new QToolButton;
            button->setObjectName(QStringLiteral("GlassButton"));
            button->setProperty("command", QString::fromLatin1(name));
            button->setProperty("contextBar", true);  // für Tests: von den gleichen Knöpfen der Werkzeugleiste zu unterscheiden
            button->setIcon(Gui::Shell::iconOf(name));  // MyCADs Symbol wie in der Werkzeugleiste, nicht das von FreeCAD
            button->setIconSize(QSize(Gui::Shell::Token::IconWindow, Gui::Shell::Token::IconWindow));
            button->setFixedSize(Gui::Shell::Token::WindowButton, Gui::Shell::Token::WindowButton);
            button->setToolTip(action->toolTip().isEmpty() ? action->text() : action->toolTip());
            button->setAccessibleName(Gui::Shell::labelOf(name));
            button->setCursor(Qt::PointingHandCursor);
            const std::string command = name;
            QObject::connect(button, &QToolButton::clicked, button, [this, command] {
                hide();
                QTimer::singleShot(0, [command] {  // die Auswahl bleibt, das Werkzeug nimmt sie
                    Gui::Application::Instance->commandManager().runCommandByName(command.c_str());
                });
            });
            content->layout()->addWidget(button);
        }
        content->adjustSize();
    }

    /// über dem Anker, ist dort kein Platz (Toolbar), darunter; nie auf dem Anker selbst: der zweite Klick eines
    /// Doppelklicks (Maße an der Fläche) muss die Fläche treffen, nicht die Leiste
    void place()
    {
        if (!panel || !viewer || !panel->isVisible()) {
            return;
        }
        const QPoint p = viewer->toQPoint(viewer->getPointOnViewport(SbVec3f(float(anchor.x), float(anchor.y), float(anchor.z))));
        const QSizeF s = content->sizeHint();
        const QRectF view = viewer->scene()->sceneRect();
        constexpr qreal gap = 24, top = 150, bottom = 90;  // Abstand zum Punkt; oben Toolbar, unten Timeline frei
        const qreal x = std::clamp<qreal>(p.x() - s.width() / 2, view.left() + 12, view.right() - s.width() - 12);
        const qreal above = p.y() - gap - s.height();
        const qreal y = above >= view.top() + top ? above : std::min<qreal>(p.y() + gap, view.bottom() - s.height() - bottom);
        panel->setGeometry(QRectF(x, y, s.width(), s.height()));
    }

    Base::Vector3d anchor;
    QPointer<Gui::View3DInventorViewer> viewer;
    QPointer<Gui::Shell::GlassPanel> panel;
    QWidget* content = nullptr;
    DesignGui::CameraFollow follow {[this] { place(); }};
};

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
            sel.getObject(), Part::ShapeOption::ResolveLink | Part::ShapeOption::Transform | Part::ShapeOption::NeedSubElement,
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
        toolHint(T("Section Analysis"),
                                 T("Select a plane or a planar face to cut the model at."));
        return;
    }
    const gp_Pnt o = pln.Location();
    const gp_Dir n = pln.Axis().Direction();
    const Base::Placement placement(Base::Vector3d(o.X(), o.Y(), o.Z()),
                                    Base::Rotation(Base::Vector3d(0, 0, 1), Base::Vector3d(n.X(), n.Y(), n.Z())));
    Gui::Selection().clearSelection();
    viewer->toggleClippingPlane(1, false, true, placement);  // ohne FreeCADs Ziehgriffe: die Ebene legt die Auswahl fest
}

/// Ebene durch eine gerade Kante unter einem Winkel zur Bezugsebene (Fläche an der Kante, Skizzenebene oder gewählte Ebene)
class TaskAnglePlane: public Gui::TaskView::TaskDialog
{
public:
    /// axisPoint/axisDir: Kantenmitte und -richtung in den lokalen Koordinaten der Bezugsebene; a: Startwinkel in Grad
    TaskAnglePlane(App::DocumentObject* plane, Base::Vector3d axisPoint, Base::Vector3d axisDir, double a = 45.0)
        : plane(plane)
        , point(axisPoint)
        , dir(axisDir)
    {
        auto w = new QWidget;
        w->setWindowTitle(T("Plane at Angle"));
        auto form = new QFormLayout(w);
        auto angle = new Gui::QuantitySpinBox;
        angle->setUnit(Base::Unit::Angle);
        angle->setRange(-360, 360);
        angle->setValue(Base::Quantity(a, Base::Unit::Angle));
        form->addRow(T("Angle"), angle);
        addTaskBox(w, false);
        QObject::connect(angle, qOverload<double>(&Gui::QuantitySpinBox::valueChanged), [this](double a) { setAngle(a); });
        setAngle(a);
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
    void setAngle(double a)
    {
        // Ursprung in der Kantenmitte (Ebene mittig an der Kante), um die Kante gedreht. Achse und Winkel bleiben so in
        // AttachmentOffset stehen und lassen sich beim Nachbearbeiten wieder auslesen (getRawValue, auch bei 0°)
        auto offset = static_cast<App::PropertyPlacement*>(plane->getPropertyByName("AttachmentOffset"));
        offset->setValue(Base::Placement(point, Base::Rotation(dir, a * M_PI / 180.0)));
        plane->getDocument()->recompute();
    }
    App::DocumentObject* plane;
    Base::Vector3d point, dir;
};

void startAnglePlane(App::Document* doc)
{
    App::DocumentObject* edgeObj = nullptr;
    std::string edgeName;
    App::DocumentObject* ref = nullptr;
    std::string refName;
    for (auto& sel : Gui::Selection().getSelectionEx()) {
        App::DocumentObject* obj = sel.getObject();
        const auto& names = sel.getSubNames();
        if (names.empty() && isPlane(obj)) {
            ref = obj;
        }
        else if (names.empty() && obj->isDerivedFrom<App::Line>()) {
            edgeObj = obj;  // Ursprungsachse
        }
        for (const auto& name : names) {
            if (name.rfind("Edge", 0) == 0 && !edgeObj) {
                edgeObj = obj;
                edgeName = name;
            }
            else if (name.rfind("Face", 0) == 0 && isPlanarFace(obj, name)) {
                ref = obj;
                refName = name;
            }
        }
    }
    gp_Pnt p0;
    gp_Dir d0;
    bool line = false;
    if (edgeObj) {
        const TopoDS_Shape s = Part::Feature::getTopoShape(edgeObj, Part::ShapeOption::ResolveLink | Part::ShapeOption::Transform
                                                                         | Part::ShapeOption::NeedSubElement,
                                                           edgeName.empty() ? nullptr : edgeName.c_str())
                                   .getShape();
        TopExp_Explorer e(s, TopAbs_EDGE);
        if (e.More()) {
            BRepAdaptor_Curve c(TopoDS::Edge(e.Current()));
            if (c.GetType() == GeomAbs_Line) {
                p0 = c.Value((c.FirstParameter() + c.LastParameter()) / 2);  // Mitte (Ursprungsachsen: 0)
                d0 = c.Line().Direction();
                line = true;
            }
        }
    }
    if (!line) {
        toolHint(T("Plane at Angle"),
                                 T("Select a straight edge, sketch line or axis (and optionally the "
                                   "plane or face to measure the angle from)."));
        return;
    }
    // Bezugsebene: gewählt, sonst die Skizzenebene, eine ebene Fläche an der Kante oder XY
    if (!ref) {
        if (edgeObj->isDerivedFrom<Part::Part2DObject>()) {
            ref = static_cast<Part::Part2DObject*>(edgeObj)->AttachmentSupport.getValue();
            const auto& subs = static_cast<Part::Part2DObject*>(edgeObj)->AttachmentSupport.getSubValues();
            refName = subs.empty() ? std::string() : subs.front();
        }
        else if (auto body = freecad_cast<Design::Body*>(edgeObj)) {
            const TopoDS_Shape edge = body->Shape.getShape().getSubShape(edgeName.c_str(), true);
            TopTools_IndexedDataMapOfShapeListOfShape adjacency;
            TopExp::MapShapesAndAncestors(body->Shape.getShape().getShape(), TopAbs_EDGE, TopAbs_FACE, adjacency);
            const int idx = adjacency.FindIndex(edge);
            if (idx > 0) {
                for (TopTools_ListOfShape::Iterator it(adjacency(idx)); it.More(); it.Next()) {
                    const std::string name = elementName(body->Shape.getShape().getShape(), it.Value());
                    if (isPlanarFace(body, name)) {
                        ref = body;
                        refName = name;
                        break;
                    }
                }
            }
        }
        if (!ref) {
            ref = activeContainer(doc)->getOrigin()->getXY();
        }
    }
    stableRef(ref, refName);
    doc->openTransaction("Plane at Angle");
    App::DocumentObject* plane = doc->addObject("PartDesign::Plane", "Plane");
    auto attach = plane->getExtensionByType<Part::AttachExtension>();
    attach->AttachmentSupport.setValue(ref, std::vector<std::string> {refName});
    attach->MapMode.setValue("FlatFace");
    Design::folder(Design::componentOf(ref), "Construction")->addObject(plane);
    plane->recomputeFeature();
    // Kante in lokale Koordinaten der befestigten (noch ungedrehten) Ebene umrechnen
    const Base::Placement inverse = static_cast<App::GeoFeature*>(plane)->Placement.getValue().inverse();
    Base::Vector3d point, dir;
    inverse.multVec(Base::Vector3d(p0.X(), p0.Y(), p0.Z()), point);
    inverse.getRotation().multVec(Base::Vector3d(d0.X(), d0.Y(), d0.Z()), dir);
    styleDatum(plane);  // erst danach: die Verschiebung zur Flächenmitte ersetzt TaskAnglePlane durch die Kantenmitte
    Gui::Selection().clearSelection();
    Gui::Control().showDialog(new TaskAnglePlane(plane, point, dir));
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
        toolHint(T("Offset Plane"),
                                 T("Select a plane or a planar face first."));
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

/// Doppelklick auf eine Konstruktionsebene im Browser (PartDesigns ViewProviderDatum ruft Design_EditConstruction):
/// Abstand bzw. Winkel ändern, beides steht in AttachmentOffset. Mittelebenen rechnen ihren Abstand selbst.
void editConstruction(App::Document* doc)
{
    const auto picked = Gui::Selection().getSelection(doc->getName());
    App::DocumentObject* plane = picked.size() == 1 ? picked.front().pObject : nullptr;
    auto offset = plane ? freecad_cast<App::PropertyPlacement*>(plane->getPropertyByName("AttachmentOffset")) : nullptr;
    if (!offset || !plane->getPropertyByName("Width") || std::string(plane->getNameInDocument()).rfind("Midplane", 0) == 0) {
        return;  // Achsen, Punkte: keine Werte zum Ändern
    }
    const Base::Placement value = offset->getValue();
    Base::Vector3d axis;
    double angle = 0;
    value.getRotation().getRawValue(axis, angle);
    Gui::Selection().clearSelection();
    doc->openTransaction("Edit Plane");
    if (value.getRotation().isIdentity() && axis.z > 0.999) {
        Gui::Control().showDialog(new TaskOffsetPlane(plane, value.getPosition().z));
    }
    else {
        Gui::Control().showDialog(new TaskAnglePlane(plane, value.getPosition(), axis, angle * 180.0 / M_PI));
    }
}

/// Oberste ebene Fläche eines Körpers (Normale nach oben, am höchsten), "" ohne
std::string topFace(Design::Body* body)
{
    std::string best;
    double height = -1e100;
    const Part::TopoShape shape = body->Shape.getShape();
    const auto faces = shape.getSubTopoShapes(TopAbs_FACE);
    for (size_t i = 0; i < faces.size(); ++i) {
        const TopoDS_Face& f = TopoDS::Face(faces[i].getShape());
        BRepAdaptor_Surface surface(f);
        if (surface.GetType() != GeomAbs_Plane) {
            continue;
        }
        gp_Dir n = surface.Plane().Axis().Direction();
        if (f.Orientation() == TopAbs_REVERSED) {
            n.Reverse();
        }
        GProp_GProps props;
        BRepGProp::SurfaceProperties(f, props);
        if (n.Z() > 0.99 && props.CentreOfMass().Z() > height) {
            height = props.CentreOfMass().Z();
            best = "Face" + std::to_string(i + 1);
        }
    }
    return best;
}
}  // namespace

namespace
{
/// Foto als Graustufen; ponytail: auf höchstens 1000 Pixel verkleinert (schnell, glättet Papierstruktur), feine Teile
/// brauchen ein näheres Foto
bool loadGray(const std::string& file, std::vector<std::uint8_t>& gray, int& w, int& h)
{
    QImage image(QString::fromStdString(file));
    if (image.isNull()) {
        return false;
    }
    if (std::max(image.width(), image.height()) > 1000) {
        image = image.scaled(1000, 1000, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    image = image.convertToFormat(QImage::Format_Grayscale8);
    w = image.width();
    h = image.height();
    gray.assign(size_t(w) * h, 0);
    for (int y = 0; y < h; ++y) {
        std::copy_n(image.constScanLine(y), w, gray.begin() + size_t(y) * w);
    }
    return true;
}
}  // namespace

bool DesignGui::photoSheet(const std::string& file)
{
    std::vector<std::uint8_t> gray;
    int w = 0, h = 0;
    return loadGray(file, gray, w, h) && PhotoContour::findSheet(gray, w, h).found;
}

double DesignGui::photoGrid(const std::string& file)
{
    std::vector<std::uint8_t> gray;
    int w = 0, h = 0;
    return loadGray(file, gray, w, h) ? PhotoContour::gridPeriod(gray, w, h, PhotoContour::partMask(gray, w, h)) : 0;
}

App::DocumentObject* DesignGui::photoToSketch(const std::string& file, double widthMm, double squareMm)
{
    App::Document* doc = App::GetApplication().getActiveDocument();
    std::vector<std::uint8_t> gray;
    int w = 0, h = 0;
    if (!doc || !loadGray(file, gray, w, h)) {
        toolHint(T("Photo to Sketch"), T("The photo could not be opened."));
        return nullptr;
    }
    double gridPx = 0;  // Rasterpapier: Maßstab aus der Kästchengröße
    if (squareMm > 0) {
        gridPx = PhotoContour::gridPeriod(gray, w, h, PhotoContour::partMask(gray, w, h));
        if (gridPx <= 0) {
            toolHint(T("Photo to Sketch"), T("No grid found on the paper. Type the width of the part instead."));
            return nullptr;
        }
    }
    // ohne Breite und Kästchen: ganzes A4-Blatt im Bild, entzerrt, Koordinaten schon in mm (y nach unten)
    const bool sheet = widthMm <= 0 && squareMm <= 0;
    const auto loops = sheet ? PhotoContour::outlinesOnSheet(gray, w, h, 210, 297, 0.4)
                             : PhotoContour::outlines(gray, w, h, 1.5);  // runde Löcher als Kreise
    if (loops.empty()) {
        toolHint(T("Photo to Sketch"), T("No part found. Lay it on plain paper that fills the photo and take the photo from straight above."));
        return nullptr;
    }
    double minX = 1e100, maxX = -1e100, maxY = -1e100;
    for (const auto& loop : loops) {
        if (loop.circle) {
            minX = std::min(minX, loop.c.centre.x - loop.c.radius);
            maxX = std::max(maxX, loop.c.centre.x + loop.c.radius);
            maxY = std::max(maxY, loop.c.centre.y + loop.c.radius);
        }
        for (const auto& p : loop.points) {
            minX = std::min(minX, p.x);
            maxX = std::max(maxX, p.x);
            maxY = std::max(maxY, p.y);
        }
    }
    const double scale = sheet ? 1.0 : gridPx > 0 ? squareMm / gridPx : widthMm / std::max(1e-9, maxX - minX);  // mm je Pixel
    widthMm = (maxX - minX) * scale;
    doc->openTransaction("Photo to Sketch");
    Sketcher::SketchObject* sketch = newSketch(activeContainer(doc));
    sketch->Label.setValue("Photo");
    int circles = 0;
    for (const auto& outline : loops) {
        const int first = sketch->getHighestCurveIndex() + 1;
        const auto mm = [&](const PhotoContour::Point& p) {
            return Base::Vector3d((p.x - minX) * scale, (maxY - p.y) * scale, 0);  // Bild-y nach unten, Skizze nach oben
        };
        if (outline.circle) {
            Part::GeomCircle circle;
            circle.setCenter(mm(outline.c.centre));
            circle.setRadius(outline.c.radius * scale);
            sketch->addGeometry(&circle);
            ++circles;
            continue;
        }
        const auto& loop = outline.points;
        for (size_t i = 0; i < loop.size(); ++i) {
            auto segment = std::make_unique<Part::GeomLineSegment>();
            segment->setPoints(mm(loop[i]), mm(loop[(i + 1) % loop.size()]));
            sketch->addGeometry(segment.get());
        }
        const int n = static_cast<int>(loop.size());
        for (int i = 0; i < n; ++i) {
            auto c = std::make_unique<Sketcher::Constraint>();
            c->Type = Sketcher::Coincident;
            c->First = first + i;
            c->FirstPos = Sketcher::PointPos::end;
            c->Second = first + (i + 1) % n;
            c->SecondPos = Sketcher::PointPos::start;
            sketch->addConstraint(std::move(c));
        }
    }
    doc->recompute();
    doc->commitTransaction();
    toolHint(T("Photo to Sketch"), T("Traced %1 outlines (%2 of them circles), %3 mm wide. Check the size with Measure, then extrude it.")
                                      .arg(loops.size())
                                      .arg(circles)
                                      .arg(widthMm));
    return sketch;
}

void DesignGui::dressUp(const std::string& kind, double size, bool all)
{
    App::Document* doc = App::GetApplication().getActiveDocument();
    if (!doc || Gui::Control().activeDialog()) {
        return;
    }
    if (kind == "Chamfer") {
        startDressUp(doc, "Design::Chamfer", "Chamfer", false, size, all);
    }
    else {
        startDressUp(doc, "Design::Fillet", "Fillet", false, size, all);
    }
}

namespace
{
/// Fläche für Bohrungen per Satz: gewählte ebene Körperfläche, sonst Oberseite des gewählten oder einzigen sichtbaren
/// Körpers; false mit Hinweis, wenn es keine gibt
bool holeTarget(App::Document* doc, Design::Body*& body, std::string& face)
{
    body = nullptr;
    face.clear();
    for (const auto& sel : Gui::Selection().getSelectionEx()) {
        if (auto b = freecad_cast<Design::Body*>(const_cast<App::DocumentObject*>(sel.getObject()))) {
            body = b;
            for (const auto& name : sel.getSubNames()) {
                face = isPlanarFace(b, name) ? name : face;
            }
        }
    }
    if (!body) {
        std::vector<Design::Body*> shown;
        for (auto obj : doc->getObjectsOfType(Design::Body::getClassTypeId())) {
            if (obj->Visibility.getValue()) {
                shown.push_back(static_cast<Design::Body*>(obj));
            }
        }
        body = shown.size() == 1 ? shown.front() : nullptr;
    }
    if (body && face.empty()) {
        face = topFace(body);
    }
    if (!body || face.empty()) {
        toolHint(T("Hole"), T("Select the face (or the body) the holes go into."));
        return false;
    }
    return true;
}

/// Bohrung als ISO-Durchgangsloch size ("M3") oder mit diameter, durch alles
std::function<void(Design::Hole*)> holeSize(const std::string& size, double diameter)
{
    return [size, diameter](Design::Hole* hole) {
        hole->ThroughAll.setValue(true);
        if (!size.empty()) {
            hole->Standard.setValue("ISO metric");
            for (const auto& name : hole->Size.getEnumVector()) {
                if (name.rfind(size + "x", 0) == 0) {
                    hole->Size.setValue(name.c_str());
                    hole->Kind.setValue("Clearance hole");
                    return;
                }
            }
        }
        if (diameter > 0) {
            hole->Diameter.setValue(diameter);
        }
    };
}
}  // namespace

void DesignGui::patternHoles(bool circle, int count, const std::string& size, double diameter, double pitch)
{
    App::Document* doc = App::GetApplication().getActiveDocument();
    Design::Body* body = nullptr;
    std::string face;
    if (!doc || Gui::Control().activeDialog() || count < 2 || !holeTarget(doc, body, face)) {
        return;
    }
    const double nominal = size.empty() ? diameter : std::strtod(size.c_str() + 1, nullptr);
    holeOnFace(body, face, Base::Vector3d(), -1, holeSize(size, diameter),
               [circle, count, pitch, nominal](Sketcher::SketchObject* sketch, const Base::BoundBox3d& box) {
                   const Base::Vector3d centre(box.GetCenter().x, box.GetCenter().y, 0);
                   std::vector<Base::Vector3d> at;
                   if (circle) {  // erste Bohrung oben, dann gleichmäßig herum
                       for (int k = 0; k < count; ++k) {
                           const double a = M_PI / 2 + 2 * M_PI * k / count;
                           at.emplace_back(centre.x + pitch / 2 * std::cos(a), centre.y + pitch / 2 * std::sin(a), 0);
                       }
                   }
                   else {  // durch die Mitte entlang der längeren Seite; ohne Abstand gleichmäßig, 2 × Nennmaß vom Rand
                       const bool alongX = box.LengthX() >= box.LengthY();
                       const double length = alongX ? box.LengthX() : box.LengthY();
                       const double step = pitch > 0 ? pitch : (length - 4 * nominal) / (count - 1);
                       for (int k = 0; k < count; ++k) {
                           const double t = (k - (count - 1) / 2.0) * step;
                           at.push_back(alongX ? Base::Vector3d(centre.x + t, centre.y, 0) : Base::Vector3d(centre.x, centre.y + t, 0));
                       }
                   }
                   int construction = -1;
                   if (circle) {  // Lochkreis als Hilfskreis mit Durchmesser: im Skizzen-Bearbeiten änderbar
                       Part::GeomCircle guide;
                       guide.setCenter(centre);
                       guide.setRadius(pitch / 2);
                       construction = sketch->addGeometry(&guide, true);
                       auto d = std::make_unique<Sketcher::Constraint>();
                       d->Type = Sketcher::Diameter;
                       d->First = construction;
                       d->setValue(pitch);
                       sketch->addConstraint(std::move(d));
                   }
                   for (int k = 0; k < count; ++k) {
                       Base::Vector3d p = at[k];
                       const Part::GeomPoint point(p);
                       int index = 0;
                       if (k == 0) {
                           sketch->setGeometry(0, &point);
                       }
                       else {
                           index = sketch->addGeometry(&point);
                       }
                       if (circle) {
                           auto on = std::make_unique<Sketcher::Constraint>();
                           on->Type = Sketcher::PointOnObject;
                           on->First = index;
                           on->FirstPos = Sketcher::PointPos::start;
                           on->Second = construction;
                           sketch->addConstraint(std::move(on));
                       }
                       else {
                           dimensionHolePoint(sketch, index, p, {}, 0);  // Randabstände, als Reihe gebunden
                       }
                   }
               });
}

void DesignGui::cornerHoles(const std::string& size, double diameter, double offset)
{
    App::Document* doc = App::GetApplication().getActiveDocument();
    Design::Body* body = nullptr;
    std::string face;
    if (!doc || Gui::Control().activeDialog() || !holeTarget(doc, body, face)) {
        return;
    }
    holeOnFace(body, face, Base::Vector3d(), offset, holeSize(size, diameter));
}

/// 12.4: Testteil fürs Druckerprofil (DesignCalibrate) in einem neuen Design, mit einer Notiz, was zu tun ist. Geht
/// auch ohne offenes Design (von der Startseite und aus den Einstellungen)
class PrinterTestCommand: public DesignCommand
{
public:
    PrinterTestCommand()
        : DesignCommand("Design_PrinterTest", "Printer Test",
                        "Printer Test: print it once, then click in Settings what fit; fits, threads and the print view use it",
                        "Std_Print", "", [](App::Document*) { make(); })
    {}

protected:
    bool isActive() override
    {
        return !Gui::Control().activeDialog();
    }

private:
    static void make()
    {
        Gui::Application::Instance->commandManager().runCommandByName("Std_New");
        App::Document* doc = App::GetApplication().getActiveDocument();
        if (!doc) {
            return;
        }
        const auto hex = [](const QString& s) { return QString::fromLatin1(s.toUtf8().toHex()).toStdString(); };
        doc->Label.setValue(T("Printer Test").toStdString());
        doc->openTransaction("Printer Test");
        try {
            Base::Interpreter().runString(
                ("import DesignCalibrate, FreeCAD\nDesignCalibrate.make(FreeCAD.ActiveDocument, bytes.fromhex('"
                 + hex(QString::fromStdString(dxfTextFont())) + "').decode(), [bytes.fromhex(n).decode() for n in ('"
                 + hex(T("Fit Plate")) + "', '" + hex(T("Pin")) + "', '" + hex(T("Limits")) + "')])")
                    .c_str());
        }
        catch (const Base::Exception& e) {
            doc->abortTransaction();
            e.reportException();
            return;
        }
        auto note = static_cast<Design::Note*>(doc->addObject("Design::Note", "Note"));
        Design::folder(Design::root(doc, true), "Notes")->addObject(note);
        note->Text.setValue(T("Printer test\n"
                              "1. Print all three parts with your usual settings.\n"
                              "2. Push the pin into the holes: which is the first it slides into?\n"
                              "3. Look at the overhangs (30 to 70°) and walls (0.4 to 1.2 mm).\n"
                              "4. Settings › 3D Printing: click what fit.")
                                .toStdString());
        doc->recompute();
        doc->commitTransaction();
        Gui::Command::doCommand(Gui::Command::Gui, "Gui.SendMsgToActiveView('ViewFit')");
    }
};

void CreateDesignCommands()
{
    static QuickMeasureChip quickMeasure;
    static ContextBar contextBar;
    auto& mgr = Gui::Application::Instance->commandManager();
    mgr.addCommand(new SketchCompleteCommand);
    mgr.addCommand(new PrinterTestCommand);
    mgr.addCommand(new DesignCommand("Design_CreateSketch", "Create Sketch",
                                     "Create Sketch: click a plane or planar face to sketch on",
                                     "Sketcher_NewSketch", "S", createSketchCommand));
    mgr.addCommand(new DesignCommand("Design_Extrude", "Extrude",
                                     "Extrude: select sketch profiles or a flat face of a body",
                                     "PartDesign_Pad", "E", startExtrude));
    mgr.addCommand(new DesignCommand("Design_Revolve", "Revolve", "Revolve: select one or more sketch profiles",
                                     "PartDesign_Revolution", "", [](App::Document* doc) {
                                         startProfileFeature(doc, "Design::Revolve", "Revolve", [](Design::Feature* f) {
                                             // erste Achse, die den Querschnitt nicht schneidet (Donut: Kreis neben
                                             // der Achse); Reihenfolge Skizze Y, Skizze X, Z, X, Y
                                             auto revolve = static_cast<Design::Revolve*>(f);
                                             Part::TopoShape tool;
                                             std::string error;
                                             for (int axis : {1, 0, 4, 2, 3}) {
                                                 revolve->Axis.setValue(axis);
                                                 if (revolve->makeTool(tool, error)) {
                                                     return true;
                                                 }
                                             }
                                             revolve->Axis.setValue(1);
                                             return true;
                                         });
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
    mgr.addCommand(new DesignCommand("Design_Delete", "Delete", "Delete: remove features, sketches or bodies with their steps",
                                     "edit-delete", "", deleteSelected));
    mgr.addCommand(new DesignCommand("Design_Export", "Export", "Export bodies as 3MF, STL or STEP, or sketches as DXF",
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
    mgr.addCommand(new DesignCommand("Design_RemoveFace", "Remove Face",
                                     "Remove Face: select faces of a body, e.g. a fillet or a hole; the faces around close the gap",
                                     "Part_Defeaturing", "", [](App::Document* doc) {
                                         startDressUp(doc, "Design::RemoveFace", "RemoveFace");
                                     }));
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
    mgr.addCommand(new DesignCommand("Design_AnglePlane", "Plane at Angle",
                                     "Plane at Angle: select a straight edge or axis (and optionally a plane)",
                                     "PartDesign_Plane", "", startAnglePlane));
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
    // ohne Menütext: nicht in Suche und Leisten, nur für den Doppelklick auf eine Konstruktionsebene
    mgr.addCommand(new DesignCommand("Design_EditConstruction", "", "", "", "", editConstruction));
    mgr.addCommand(new DesignCommand("Design_PhotoToSketch", "Photo to Sketch",
                                     "Photo to Sketch: trace a part photographed on plain paper into a sketch to scale",
                                     "Design_PhotoToSketch", "", startPhotoToSketch));
    mgr.addCommand(new DesignCommand("Design_CheckReferences", "Check References",
                                     "Check References: list every step that no longer finds its edges or faces for certain",
                                     "Design_CheckReferences", "", startCheckReferences));
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
    mgr.addCommand(new DesignCommand("Design_Versions", "Versions",
                                     "Versions: every state is kept; open, compare or restore one, or try a variant",
                                     "Std_Revert", "", showVersions));
    mgr.addCommand(new DesignCommand("Design_RedPen", "Red Pen",
                                     "Red Pen: write corrections straight on the model, e.g. R2 next to an edge or M5 on a face",
                                     nullptr, "", startRedPen));
    mgr.addCommand(new DesignCommand("Design_PrintView", "Print View",
                                     "Print View: shows overhangs, faces on the bed and thin walls; click again to hide",
                                     "Std_ViewIvIssueCamPos", "", [](App::Document*) {
                                         DesignGui::setPrintView(!DesignGui::printView());
                                     }));
    mgr.addCommand(new DesignCommand("Design_PrintDown", "Choose Bottom Face",
                                     "Choose Bottom Face: click the flat face that lies on the print bed",
                                     "Std_ViewBottom", "", choosePrintBottom));
    mgr.addCommand(new DesignCommand("Design_Print", "Print",
                                     "Print: opens the design in your slicer (OrcaSlicer, Bambu Studio, PrusaSlicer, Cura)",
                                     "Std_Print", "", printBodies));
    mgr.addCommand(new DesignCommand("Design_Fit", "Fit",
                                     "Fit: select a hole and its pin (or flat faces) for a 3D print or ISO fit",
                                     "Part_Offset", "", startFit));
    mgr.addCommand(new DesignCommand("Design_Fastener", "Screw Here",
                                     "Screw Here: click the top face of a part that lies on another part",
                                     "PartDesign_Hole", "", startFastener));
    mgr.addCommand(new DesignCommand("Design_Thread", "Thread", "Thread: select a cylindrical face of a body",
                                     "PartDesign_Hole", "", [](App::Document* doc) {
                                         startDressUp(doc, "Design::Thread", "Thread");
                                         // neue Gewinde mit Fase an freien Enden (alte Dateien behalten ihre Form)
                                         auto threads = doc->getObjectsOfType(Design::Thread::getClassTypeId());
                                         if (!threads.empty() && Gui::Control().activeDialog()) {
                                             static_cast<Design::Thread*>(threads.back())->EndChamfer.setValue(true);
                                             doc->recompute();
                                         }
                                     }));
    mgr.addCommand(new DesignCommand("Design_Appearance", "Appearance",
                                     "Appearance: select bodies, then pick a material or color", "Std_SetAppearance",
                                     "A", startAppearance));
    mgr.addCommand(new DesignCommand("Design_Rib", "Rib", "Rib: select a body and sketch lines", "PartDesign_Rib",
                                     "", [](App::Document* doc) { startRib(doc, 0); }));
    mgr.addCommand(new DesignCommand("Design_Web", "Web",
                                     "Web: select a body and sketch lines; walls grow perpendicular to the sketch",
                                     "PartDesign_Rib", "", [](App::Document* doc) { startRib(doc, 1); }));
    mgr.addCommand(new DesignCommand("Design_Parameters", "Change Parameters",
                                     "Parameters: named values to use in any dimension field", "Std_VarSet", "",
                                     showParameters));
    mgr.addCommand(new NoteCommand);
    mgr.addCommand(new ScribbleCommand);
    {
        using DesignGui::ViewProviderScribble;
        using Tool = ViewProviderScribble::Tool;
        const auto tool = [&mgr](const char* name, const char* text, const char* tip, Tool t) {
            mgr.addCommand(new ScribbleTool(name, text, tip, [t](ViewProviderScribble*) { ViewProviderScribble::setTool(t); }));
        };
        tool("Design_ScribblePencil", "Pencil", "Pencil: a soft line, thinner the lighter you press", Tool::Pencil);
        tool("Design_ScribblePen", "Fineliner", "Fineliner: an even, dark line", Tool::Pen);
        tool("Design_ScribbleMarker", "Marker", "Marker: a broad, see-through stroke for highlighting", Tool::Marker);
        // Radierer und Auswählen schalten wie E und V um: noch einmal geht zurück zum Stift (auch für Tablett-Tasten)
        const auto toggle = [&mgr](const char* name, const char* text, const char* tip, Tool t) {
            mgr.addCommand(new ScribbleTool(name, text, tip, [t](ViewProviderScribble*) { ViewProviderScribble::toggleTool(t); }));
        };
        toggle("Design_ScribbleEraser", "Eraser",
               "Eraser (E): wipe over strokes to remove them. E again goes back to the pen. On pens with an eraser end, the back of the pen erases too", Tool::Eraser);
        tool("Design_ScribbleSheet", "Move Sheet",
             "Move Sheet: tap a body face to lay the sheet on it, a straight stroke to stand it up along that line, "
             "or empty space to turn it towards you",
             Tool::Sheet);
        tool("Design_ScribbleLine", "Line", "Line: drag from start to end. It snaps level, plumb and to stroke ends", Tool::Line);
        tool("Design_ScribbleRectangle", "Rectangle", "Rectangle: drag from one corner to the opposite one", Tool::Rectangle);
        tool("Design_ScribbleCircle", "Circle", "Circle: drag from the center outwards", Tool::Circle);
        tool("Design_ScribbleArrow", "Arrow", "Arrow: drag from the tail to the tip", Tool::Arrow);
        tool("Design_ScribbleTriangle", "Triangle", "Triangle: drag across it, the tip points up", Tool::Triangle);
        tool("Design_ScribbleHexagon", "Hexagon", "Hexagon: drag from the center to a corner", Tool::Hexagon);
        tool("Design_ScribbleEllipse", "Ellipse", "Ellipse: drag across it from corner to corner", Tool::Ellipse);
        toggle("Design_ScribbleSelect", "Select",
               "Select (V): tap a stroke or draw around strokes, then drag them. Delete removes them, a colour recolours them",
               Tool::Select);
        tool("Design_ScribbleText", "Text", "Text: click on the sheet and type. Enter or Esc puts it down, Shift+Enter starts a new line", Tool::Text);
        tool("Design_ScribbleFill", "Fill",
             "Fill: tap inside a closed shape to colour it, or draw around an area to fill it", Tool::Fill);
        // Farben: MyStyle-Systemfarben des hellen Modus, das Blatt ist immer hell
        const struct
        {
            const char* name;
            const char* text;
            Base::Color color;
        } inks[] = {
            {"Design_ScribbleBlack", "Black", ViewProviderScribble::ink()},
            {"Design_ScribbleBlue", "Blue", Base::Color(0x0088FFFFu)},
            {"Design_ScribbleRed", "Red", Base::Color(0xFF383CFFu)},
            {"Design_ScribbleGreen", "Green", Base::Color(0x34C759FFu)},
            {"Design_ScribbleYellow", "Yellow", Base::Color(0xFFCC00FFu)},
        };
        std::vector<Base::Color> colors;
        for (const auto& ink : inks) {
            const Base::Color color = ink.color;
            colors.push_back(color);
            mgr.addCommand(new ScribbleTool(ink.name, ink.text, "Color for the next strokes",
                                            [color](ViewProviderScribble*) { ViewProviderScribble::setColor(color); }));
        }
        // für eine Tablett-Taste: reihum durch die Farben oben (eine eigene Farbe geht zurück zur ersten)
        mgr.addCommand(new ScribbleTool("Design_ScribbleNextColor", "Next Color", "Next Color: switch to the next Scribble color",
                                        [colors](ViewProviderScribble*) {
                                            const auto it = std::find(colors.begin(), colors.end(), ViewProviderScribble::color());
                                            const size_t i = it == colors.end() ? colors.size() - 1 : size_t(it - colors.begin());
                                            ViewProviderScribble::setColor(colors[(i + 1) % colors.size()]);
                                        }));
        mgr.addCommand(new ScribbleTool("Design_ScribbleLookAt", "Look At", "Look At (L): view the sheet straight on",
                                        [](ViewProviderScribble* vp) { vp->lookAtSheet(); }));
        mgr.addCommand(new ScribbleTool("Design_ScribbleTracing", "Tracing Paper",
                                        "Tracing Paper: the model shows through the sheet, so you can draw over it",
                                        [](ViewProviderScribble* vp) {
                                            auto scribble = static_cast<Design::Scribble*>(vp->getObject());
                                            scribble->Tracing.setValue(!scribble->Tracing.getValue());
                                        }));
        mgr.addCommand(new ScribbleTool("Design_ScribbleCorrect", "Apply Corrections",
                                        "Apply Corrections: what you wrote on the model (R2, M5, Ø8, +5, 3×, H7, 12) becomes "
                                        "features, after you confirm each one",
                                        readCorrections));
        mgr.addCommand(new ScribbleTool("Design_ScribbleToSketch", "Convert to Sketch",
                                        "Convert to Sketch: lines, circles and rectangles on this sheet become sketch "
                                        "geometry you can dimension and extrude. Written sizes like Ø12, R5 or 40 next "
                                        "to a circle or line become its dimension",
                                        scribbleToSketch));
        mgr.addCommand(new ScribbleTool("Design_ScribbleFocus", "Only the Sheet",
                                        "Only the Sheet (Tab): toolbar, browser and palette fold into a small pill at the top. "
                                        "Tab again brings them back",
                                        [](ViewProviderScribble*) { Gui::Shell::setScribbleFocus(!Gui::Shell::scribbleFocus()); }));
        mgr.addCommand(new ScribbleTool("Design_ScribbleDeleteSelection", "Delete", "Delete the selected strokes (Del)",
                                        [](ViewProviderScribble* vp) { vp->deleteSelection(); }));
        mgr.addCommand(new ScribbleTool("Design_ScribbleFinish", "Finish Scribble", "Finish Scribble (Esc)",
                                        [](ViewProviderScribble* vp) {
                                            Gui::Application::Instance->getDocument(vp->getObject()->getDocument())->resetEdit();
                                        }));
    }
    mgr.addCommand(new DesignCommand("Design_ReplaceFace", "Replace Face",
                                     "Replace Face: select faces of a body, then the target plane or face",
                                     "Part_Extrude", "", [](App::Document* doc) {
                                         startFaceTool(doc, "Design::ReplaceFace", "Replace Face", "Target",
                                                       "Select the faces to replace, then the target plane or face.");
                                     }));
    mgr.addCommand(new DesignCommand("Design_SplitFace", "Split Face",
                                     "Split Face: select faces of a body, then a plane, face or sketch",
                                     "Part_Slice", "", [](App::Document* doc) {
                                         startFaceTool(doc, "Design::SplitFace", "Split Face", "Tool",
                                                       "Select the faces to split, then a plane, face or sketch.");
                                     }));
    mgr.addCommand(new DesignCommand("Design_Emboss", "Emboss",
                                     "Emboss: select sketch profiles or text and the face to emboss on",
                                     "PartDesign_Pad", "", startEmboss));
    mgr.addCommand(new DesignCommand("Design_Joint", "Joint",
                                     "Joint: select a snap point on the component to move, then where to join it",
                                     "Assembly_CreateJointFixed", "J", startJoint));
    mgr.addCommand(new DesignCommand("Design_NewComponent", "New Component",
                                     "New Component: an empty part with its own origin, active right away",
                                     "Std_Part", "", startNewComponent));
    mgr.addCommand(new DesignCommand("Design_Chamfer", "Chamfer", "Chamfer: select edges or faces of a body",
                                     "PartDesign_Chamfer", "", [](App::Document* doc) {
                                         startDressUp(doc, "Design::Chamfer", "Chamfer");
                                     }));
}
