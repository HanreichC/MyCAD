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
#include <Bnd_Box.hxx>
#include <TopExp_Explorer.hxx>
#include <Mod/Part/App/Part2DObject.h>
#include <TopTools_ListIteratorOfListOfShape.hxx>
#include <TopTools_IndexedDataMapOfShapeListOfShape.hxx>
#include <TopoDS_Vertex.hxx>
#include <gp_Pln.hxx>
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
        Gui::getMainWindow()->showMessage(T("Select a plane or a planar face for the sketch"));
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
        QMessageBox::information(Gui::getMainWindow(), T("Convert to Sketch"),
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
        QMessageBox::information(Gui::getMainWindow(), T(name),
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
    QMessageBox::information(Gui::getMainWindow(), T("Sweep"),
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
        QMessageBox::information(Gui::getMainWindow(), T("Loft"),
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
        QMessageBox::information(Gui::getMainWindow(), T(name),
                                 T("Select edges (or faces) of a body first."));
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
        QMessageBox::information(Gui::getMainWindow(), T("Fit"),
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
                for (TopTools_ListIteratorOfListOfShape it(i ? owners(i) : TopTools_ListOfShape()); it.More(); it.Next()) {
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
            QMessageBox::information(Gui::getMainWindow(), T("Screw Here"), T(e.what()));
        }
        return;
    }
    QMessageBox::information(Gui::getMainWindow(), T("Screw Here"),
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
        QMessageBox::information(Gui::getMainWindow(), T("Extrude"), T("Click a flat face of the body to extrude it."));
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

/// Alle in derselben Komponente? Verweise über Komponentengrenzen erlaubt FreeCAD nicht.
/// ponytail: Operationen über mehrere Komponenten (Fusion kann das) brauchen globale Links + Transformationen
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
        QMessageBox::information(Gui::getMainWindow(), T("Combine"),
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
        QMessageBox::information(Gui::getMainWindow(), T("Align"),
                                 T("Select a face, edge or point of the body to move, "
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
    auto selection = Gui::Selection().getSelectionEx();
    for (auto& sel : selection) {
        App::DocumentObject* obj = sel.getObject();
        const auto& names = sel.getSubNames();
        // ein Klick auf den Body in der Ansicht wählt eine Fläche: als Erstes gewählt und mit Werkzeug danach zählt er
        // als der Body
        const bool first = &sel == &selection.front() && selection.size() > 1;
        if (!body && freecad_cast<Design::Body*>(obj) && (names.empty() || first)) {
            body = static_cast<Design::Body*>(obj);
        }
        else if (!tool && (isPlane(obj) || (names.size() == 1 && names.front().rfind("Face", 0) == 0))) {
            tool = obj;
            element = names.empty() ? std::string() : names.front();
            stableRef(tool, element);
        }
    }
    if (!body || !tool || tool == body) {
        QMessageBox::information(Gui::getMainWindow(), T("Split Body"),
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
        QMessageBox::information(Gui::getMainWindow(), T("Rib"),
                                 T("Select the body and the sketch lines of the rib (or the whole sketch)."));
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
        QMessageBox::information(Gui::getMainWindow(), T(name), T(hint));
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
        QMessageBox::information(Gui::getMainWindow(), T("Emboss"),
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
        QMessageBox::information(Gui::getMainWindow(), T("Joint"), problem);
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
        QMessageBox::information(Gui::getMainWindow(), T("Scale"),
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
        QMessageBox::information(Gui::getMainWindow(), T("Move"),
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
        QMessageBox::information(Gui::getMainWindow(), T("Mirror"),
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
        Gui::getMainWindow(), T("Insert"), QString(),
        T("CAD files (*.step *.stp *.dxf *.svg);;STEP (*.step *.stp);;DXF (*.dxf);;SVG (*.svg)")
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
        QMessageBox::information(Gui::getMainWindow(), title, at >= 0 ? T(text.mid(at + 7).toUtf8().constData()) : text);
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
        QMessageBox::information(Gui::getMainWindow(), T("Compare"), QString::fromUtf8(e.what()));
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
    QObject::connect(list, &QListWidget::currentRowChanged, &dlg, [=](int r) {
        for (auto b : {open, compare, restore}) {
            b->setEnabled(r >= 0);
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
    QMessageBox::information(Gui::getMainWindow(), T("Choose Bottom Face"), T("Click the flat face that should lie on the print bed."));
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
        QMessageBox::information(Gui::getMainWindow(), T("Print"), T("There is no body to print."));
        return;
    }
    ParameterGrp::handle params = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD");
    QStringList names;
    try {
        Base::PyGILStateLocker lock;
        const std::string found = Base::Interpreter().runStringWithKey(
            "import DesignExport\n_r = '\\n'.join(n for n, c in DesignExport.find_slicers())", "_r");
        names = QString::fromStdString(found).split(QLatin1Char('\n'), Qt::SkipEmptyParts);
    }
    catch (const Base::Exception& e) {
        Base::Console().error("Print: %s\n", e.what());
    }
    if (names.isEmpty()) {
        QMessageBox::information(Gui::getMainWindow(), T("Print"),
                                 T("No slicer found (OrcaSlicer, Bambu Studio, PrusaSlicer or Cura). Save a 3MF file and open it "
                                   "in your slicer."));
        exportBodies(doc);
        return;
    }
    QString slicer = QString::fromStdString(params->GetASCII("Slicer", ""));
    if (!names.contains(slicer)) {
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
    QString folder = QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + QStringLiteral("/print");
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
        Base::Interpreter().runString(
            ("import DesignExport, Design, FreeCAD as App\nDesignExport.open_in_slicer(" + objs + ", '" + folder.toStdString()
             + "', dict(DesignExport.find_slicers())['" + name.toStdString() + "'], up=Design.printUp(App.getDocument('"
             + doc->getName() + "')), quality='" + qualities[quality] + "')")
                .c_str());
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
        QMessageBox::information(Gui::getMainWindow(), T("Export"), T("There is no body to export."));
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
        QMessageBox::information(
            Gui::getMainWindow(), T("Export"), dxf ? T("There is no sketch to export.") : T("There is no body to export.")
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
        code = "try:\n    import ImportGui as Step\nexcept ImportError:\n    import Import as Step\nStep.export(" + objs + ", "
            + target + ")";
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
        QMessageBox::information(Gui::getMainWindow(), T("Hole"),
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
        QMessageBox::information(Gui::getMainWindow(), T("Pattern"),
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
    explicit TaskOffsetPlane(App::DocumentObject* plane)
        : plane(plane)
    {
        auto w = new QWidget;
        w->setWindowTitle(T("Offset Plane"));
        auto form = new QFormLayout(w);
        auto distance = new Gui::QuantitySpinBox;
        distance->setUnit(Base::Unit::Length);
        distance->setRange(-1e7, 1e7);
        distance->setValue(Base::Quantity(10.0, Base::Unit::Length));
        form->addRow(T("Distance"), distance);
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
        QMessageBox::information(Gui::getMainWindow(), T(name), T(hint));
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
        QMessageBox::information(Gui::getMainWindow(), T(name),
                                 T("This selection does not define a %1. %2")
                                     .arg(T(name), T(hint)));
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
        QMessageBox::information(Gui::getMainWindow(), T("Midplane"),
                                 T("Select two parallel planes or planar faces."));
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
                        row(T("Material"), T(whole->ShapeMaterial.getValue().getName().toStdString().c_str()));
                    }
                    const gp_Pnt c = p.CentreOfMass();
                    row(T("Center of mass"), QStringLiteral("%1, %2, %3").arg(length(c.X()), length(c.Y()), length(c.Z())));
                    GProp_GProps area;
                    BRepGProp::SurfaceProperties(s, area);
                    row(T("Area"), QStringLiteral("%1 mm²").arg(area.Mass(), 0, 'f', 2));
                    Bnd_Box box;
                    BRepBndLib::Add(s, box);
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
            BRepExtrema_DistShapeShape dist(shapes[0], shapes[1]);
            if (dist.IsDone()) {
                row(T("Distance"), length(dist.Value()));
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
                row(T("Angle"), QStringLiteral("%1°").arg(angle, 0, 'f', 2));
            }
        }
        result->setText(rows.isEmpty() ? T("Select a point, edge, face or body. "
                                           "Select two to measure distance and angle.")
                                       : QStringLiteral("<table>%1</table>").arg(rows.join(QString())));
    }
    QLabel* result;
};

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
void showParameters(App::Document* doc)
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
    table->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    lay->addWidget(table);

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
    auto setExpression = [set, doc](const std::string& name, const QString& text) {
        App::Property* prop = set->getPropertyByName(name.c_str());
        // Tabelleneintrag selbst ist der Eigentümer: andere Parameter heißen dort einfach "Width"
        set->setExpression(App::ObjectIdentifier(*prop),
                           std::shared_ptr<App::Expression>(App::Expression::parse(set, text.toStdString()).release()));
        doc->recompute();
    };
    refresh = [&, set, table] {
        table->blockSignals(true);
        table->setRowCount(0);
        for (const auto& name : names()) {
            auto prop = static_cast<App::PropertyQuantity*>(set->getPropertyByName(name.c_str()));
            const int r = table->rowCount();
            table->insertRow(r);
            auto nameItem = new QTableWidgetItem(QString::fromStdString(name));
            nameItem->setFlags(Qt::ItemIsEnabled);
            table->setItem(r, 0, nameItem);
            const auto info = set->getExpression(App::ObjectIdentifier(*prop));
            table->setItem(r, 1, new QTableWidgetItem(info.expression ? QString::fromStdString(info.expression->toString())
                                                                      : QString()));
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
                auto from = new QLabel(T("In note %1").arg(QString::fromUtf8(source->Label.getValue())));
                from->setContentsMargins(8, 0, 8, 0);
                table->setCellWidget(r, 3, from);
                continue;
            }
            auto remove = new QPushButton(T("Remove"));
            remove->setAutoDefault(false);
            QObject::connect(remove, &QPushButton::clicked, table, [&, set, name] {
                set->removeDynamicProperty(name.c_str());
                doc->recompute();
                QTimer::singleShot(0, table, [&] { refresh(); });
            });
            table->setCellWidget(r, 3, remove);
        }
        table->blockSignals(false);
    };
    QObject::connect(table, &QTableWidget::itemChanged, table, [&, table](QTableWidgetItem* item) {
        if (item->column() != 1) {
            return;
        }
        const std::string name = table->item(item->row(), 0)->text().toStdString();
        try {
            setExpression(name, item->text());
            item->setToolTip(QString());
        }
        catch (const Base::Exception& e) {
            item->setToolTip(QString::fromUtf8(e.what()));
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
    auto error = new QLabel;
    error->setStyleSheet(QStringLiteral("color: %1;").arg(Gui::Shell::theme().red.name()));
    lay->addWidget(error);
    QObject::connect(add, &QPushButton::clicked, &dlg, [&, set] {
        static const QRegularExpression valid(QStringLiteral("^[A-Za-z_][A-Za-z0-9_]*$"));
        const QString name = nameEdit->text().trimmed();
        if (!valid.match(name).hasMatch() || set->getPropertyByName(name.toLatin1().constData())) {
            error->setText(T("Use a new name of letters, digits and _ (no spaces)."));
            return;
        }
        set->addDynamicProperty("App::PropertyQuantity", name.toLatin1().constData(), "Parameters");
        try {
            setExpression(name.toStdString(), exprEdit->text().trimmed().isEmpty() ? QStringLiteral("0 mm") : exprEdit->text());
            error->clear();
            nameEdit->clear();
            exprEdit->clear();
        }
        catch (const Base::Exception& e) {
            set->removeDynamicProperty(name.toLatin1().constData());
            error->setText(QString::fromUtf8(e.what()));
        }
        refresh();
    });
    refresh();

    auto buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    QObject::connect(buttons, &QDialogButtonBox::accepted, &dlg, &QDialog::accept);
    QObject::connect(buttons, &QDialogButtonBox::rejected, &dlg, &QDialog::reject);
    lay->addWidget(buttons);
    if (dlg.exec() == QDialog::Accepted) {
        doc->commitTransaction();
    }
    else {
        doc->abortTransaction();
        doc->recompute();
    }
}

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
        QMessageBox::information(Gui::getMainWindow(), T("Section Analysis"),
                                 T("Select a plane or a planar face to cut the model at."));
        return;
    }
    const gp_Pnt o = pln.Location();
    const gp_Dir n = pln.Axis().Direction();
    const Base::Placement placement(Base::Vector3d(o.X(), o.Y(), o.Z()),
                                    Base::Rotation(Base::Vector3d(0, 0, 1), Base::Vector3d(n.X(), n.Y(), n.Z())));
    Gui::Selection().clearSelection();
    viewer->toggleClippingPlane(1, false, false, placement);
}

/// Ebene durch eine gerade Kante unter einem Winkel zur Bezugsebene (Fläche an der Kante, Skizzenebene oder gewählte Ebene)
class TaskAnglePlane: public Gui::TaskView::TaskDialog
{
public:
    /// axisPoint/axisDir: Kante in den lokalen Koordinaten der Bezugsebene
    TaskAnglePlane(App::DocumentObject* plane, Base::Vector3d axisPoint, Base::Vector3d axisDir)
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
        angle->setValue(Base::Quantity(45.0, Base::Unit::Angle));
        form->addRow(T("Angle"), angle);
        addTaskBox(w, false);
        QObject::connect(angle, qOverload<double>(&Gui::QuantitySpinBox::valueChanged), [this](double a) { setAngle(a); });
        setAngle(45.0);
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
        // Drehung um die Kante: Ebene liegt auf der Bezugsebene, Kante als Achse durch ihren Punkt
        auto offset = static_cast<App::PropertyPlacement*>(plane->getPropertyByName("AttachmentOffset"));
        offset->setValue(Base::Placement(Base::Vector3d(), Base::Rotation(dir, a * M_PI / 180.0), point));
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
                p0 = c.Value(c.FirstParameter());
                d0 = c.Line().Direction();
                line = true;
            }
        }
    }
    if (!line) {
        QMessageBox::information(Gui::getMainWindow(), T("Plane at Angle"),
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
                for (TopTools_ListIteratorOfListOfShape it(adjacency(idx)); it.More(); it.Next()) {
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
    styleDatum(plane);
    plane->recomputeFeature();
    // Kante in lokale Koordinaten der befestigten (noch ungedrehten) Ebene umrechnen
    const Base::Placement inverse = static_cast<App::GeoFeature*>(plane)->Placement.getValue().inverse();
    Base::Vector3d point, dir;
    inverse.multVec(Base::Vector3d(p0.X(), p0.Y(), p0.Z()), point);
    inverse.getRotation().multVec(Base::Vector3d(d0.X(), d0.Y(), d0.Z()), dir);
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
        QMessageBox::information(Gui::getMainWindow(), T("Offset Plane"),
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

}  // namespace

void CreateDesignCommands()
{
    auto& mgr = Gui::Application::Instance->commandManager();
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
    mgr.addCommand(new DesignCommand("Design_Delete", "Delete", "Delete: remove features or sketches from the timeline",
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
        tool("Design_ScribbleEraser", "Eraser",
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
        tool("Design_ScribbleSelect", "Select",
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
        for (const auto& ink : inks) {
            const Base::Color color = ink.color;
            mgr.addCommand(new ScribbleTool(ink.name, ink.text, "Color for the next strokes",
                                            [color](ViewProviderScribble*) { ViewProviderScribble::setColor(color); }));
        }
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
                                     "New Component: an empty part with its own origin (double-click to activate)",
                                     "Std_Part", "", startNewComponent));
    mgr.addCommand(new DesignCommand("Design_Chamfer", "Chamfer", "Chamfer: select edges or faces of a body",
                                     "PartDesign_Chamfer", "", [](App::Document* doc) {
                                         startDressUp(doc, "Design::Chamfer", "Chamfer");
                                     }));
}
