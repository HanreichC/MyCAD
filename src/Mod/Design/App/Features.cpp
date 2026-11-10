// SPDX-License-Identifier: LGPL-2.1-or-later

#include "Features.h"

#include <App/Datums.h>
#include <App/Document.h>
#include <App/DocumentObjectGroup.h>
#include <App/Part.h>
#include <App/ObjectIdentifier.h>
#include <App/Origin.h>
#include <App/GeoFeatureGroupExtension.h>
#include <App/ElementNamingUtils.h>
#include <App/IndexedName.h>
#include <App/MappedName.h>
#include <Base/Placement.h>
#include <App/Application.h>
#include <Base/Console.h>
#include <Mod/Material/App/MaterialManager.h>
#include <Mod/Material/App/Materials.h>
#include <Mod/PartDesign/App/FeatureHole.h>
#include <Mod/Part/App/ExtrusionHelper.h>
#include <Mod/Part/App/TopoShapeOpCode.h>

#include <BRepAlgoAPI_Splitter.hxx>
#include <BRepAdaptor_Surface.hxx>
#include <gp_Pln.hxx>
#include <BRep_Builder.hxx>
#include <TopoDS_Compound.hxx>
#include <BRepBndLib.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepGProp.hxx>
#include <BRep_Tool.hxx>
#include <Bnd_Box.hxx>
#include <GProp_GProps.hxx>
#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TopTools_DataMapOfShapeInteger.hxx>
#include <TopTools_ListIteratorOfListOfShape.hxx>
#include <set>
#include <TopoDS_Iterator.hxx>
#include <gp_Ax1.hxx>
#include <gp_Ax2.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepOffsetAPI_MakePipe.hxx>
#include <BRepOffsetAPI_MakePipeShell.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepTools.hxx>
#include <ElSLib.hxx>
#include <BRepAlgoAPI_Common.hxx>
#include <BRepAlgoAPI_Section.hxx>
#include <BRepFeat_SplitShape.hxx>
#include <BRepPrimAPI_MakeHalfSpace.hxx>
#include <TopoDS_Solid.hxx>
#include <BRepOffset_MakeOffset.hxx>
#include <BRepAdaptor_CompCurve.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <GCPnts_AbscissaPoint.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepClass3d_SolidClassifier.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepBuilderAPI_MakePolygon.hxx>
#include <TopTools_ListOfShape.hxx>
#include <gp_Cylinder.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Wire.hxx>
#include <gp_Ax3.hxx>
#include <gp_Circ.hxx>
#include <BRepPrimAPI_MakeCone.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <Standard_Failure.hxx>
#include <gp_Pln.hxx>

#include <algorithm>
#include <functional>
#include <sstream>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <map>
#include <nlohmann/json.hpp>

using namespace Design;

namespace
{
const char* OpEnums[] = {"New Body", "Join", "Cut", "Intersect", nullptr};
const char* ExtentEnums[] = {"One Side", "Symmetric", "Two Sides", "To Object", "All", nullptr};
const char* ThinEnums[] = {"Inside", "Outside", "Center", nullptr};
const char* AxisEnums[] = {"Sketch X", "Sketch Y", "X", "Y", "Z", nullptr};
const char* XYZEnums[] = {"X", "Y", "Z", nullptr};
const char* PlaneEnums[] = {"XY", "XZ", "YZ", nullptr};
const char* PatternEnums[] = {"Rectangular", "Circular", "Path", nullptr};
const char* HoleEnums[] = {"Simple", "Counterbore", "Countersink", nullptr};
const char* PrimitiveEnums[] = {"Box", "Cylinder", "Sphere", "Torus", "Coil", nullptr};
const char* CenterEnums[] = {"Origin", "Body center", nullptr};
const char* RibEnums[] = {"Rib", "Web", nullptr};
const char* ChamferEnums[] = {"Equal distance", "Two distances", "Distance and angle", nullptr};
const char* EmbossEnums[] = {"Emboss", "Deboss", nullptr};
const char* JointEnums[] = {"Rigid", "Revolute", "Slider", "Cylindrical", "Pin-Slot", "Planar", "Ball", nullptr};
const App::PropertyIntegerConstraint::Constraints CountRange = {1, 1000, 1};

/// Gewählte Profilflächen (leer = alle) und die zugehörige Skizze. Leerer Vektor mit Fehlertext bei Problemen.
/// Gewählte Profilflächen (leer = alle) und die zugehörige Skizze. Profile werden über ihre Signatur
/// (begrenzende Skizzenkanten) wiedergefunden; keys hält die Signaturen der gewählten Profile aktuell.
std::vector<Part::TopoShape> profileFaces(const App::PropertyLinkSub& profile, App::PropertyStringList& keys,
                                          Part::Feature*& sketch, const char*& error)
{
    auto profiles = freecad_cast<Profiles*>(profile.getValue());
    sketch = profiles ? freecad_cast<Part::Feature*>(profiles->Sketch.getValue()) : nullptr;
    if (!sketch) {
        error = "Select a profile";
        return {};
    }
    const Part::TopoShape all = profiles->Shape.getShape();
    const auto& signatures = profiles->Signatures.getValues();
    const auto& subs = profile.getSubValues();
    std::vector<std::string> known = keys.getValues();
    known.resize(subs.size());
    std::vector<Part::TopoShape> faces;
    for (size_t i = 0; i < subs.size(); ++i) {
        std::string name = subs[i];
        const auto match = std::ranges::find(signatures, known[i]);
        if (!known[i].empty() && match != signatures.end() && std::ranges::count(signatures, known[i]) == 1) {
            name = "Face" + std::to_string(match - signatures.begin() + 1);
        }
        const int idx = std::atoi(name.c_str() + 4);
        known[i] = idx >= 1 && idx <= static_cast<int>(signatures.size()) ? signatures[idx - 1] : std::string();
        faces.push_back(all.getSubTopoShape(name.c_str(), true));
    }
    keys.setValues(known);  // Ausgabe-Property: markiert das Feature nicht als geändert
    if (faces.empty()) {
        faces = all.getSubTopoShapes(TopAbs_FACE);
    }
    std::erase_if(faces, [](const Part::TopoShape& f) { return f.isNull(); });
    if (faces.empty()) {
        error = "Sketch has no closed profile";
    }
    return faces;
}

/// Ein Body ist ein Solid: Compound-Hüllen um genau einen Solid auspacken (Fillet/Chamfer scheitern sonst)
Part::TopoShape solidOf(const Part::TopoShape& shape)
{
    if (shape.getShape().ShapeType() == TopAbs_COMPOUND && shape.countSubShapes(TopAbs_SOLID) == 1) {
        return shape.getSubTopoShape(TopAbs_SOLID, 1);
    }
    return shape;
}

/// Lage einer Ebene (Ursprungsebene, Konstruktionsebene oder ebene Fläche); ohne Bezug: XY
bool planeAxes(const App::PropertyLinkSub& link, gp_Ax3& ax)
{
    App::DocumentObject* obj = link.getValue();
    if (!obj) {
        ax = gp_Ax3();
        return true;
    }
    const auto& subs = link.getSubValues();
    if (subs.empty() || subs.front().empty()) {
        auto geo = freecad_cast<App::GeoFeature*>(obj);
        if (!geo) {
            return false;
        }
        const Base::Placement p = geo->globalPlacement();
        Base::Vector3d z, x;
        p.getRotation().multVec(Base::Vector3d(0, 0, 1), z);
        p.getRotation().multVec(Base::Vector3d(1, 0, 0), x);
        const Base::Vector3d o = p.getPosition();
        ax = gp_Ax3(gp_Pnt(o.x, o.y, o.z), gp_Dir(z.x, z.y, z.z), gp_Dir(x.x, x.y, x.z));
        return true;
    }
    const Part::TopoShape face = Part::Feature::getTopoShape(
        obj, Part::ShapeOption::ResolveLink | Part::ShapeOption::Transform | Part::ShapeOption::NeedSubElement, subs.front().c_str());
    if (face.isNull() || face.getShape().ShapeType() != TopAbs_FACE) {
        return false;
    }
    BRepAdaptor_Surface surface(TopoDS::Face(face.getShape()));
    if (surface.GetType() != GeomAbs_Plane) {
        return false;
    }
    ax = surface.Plane().Position();
    if (face.getShape().Orientation() == TopAbs_REVERSED) {
        ax.ZReverse();  // Normale zeigt aus dem Körper heraus
    }
    return true;
}

/// Bodies rechnen in den Koordinaten ihrer Komponente. Eine globale Transformation m wirkt auf einen Body
/// in seiner Komponente als P^-1 * m * P (bei Komponenten ohne Verschiebung: m selbst).
Base::Matrix4D inComponent(const App::DocumentObject* body, const Base::Matrix4D& m)
{
    const Base::Placement p = Design::componentOf(body)->globalPlacement();
    return p.inverse().toMatrix() * m * p.toMatrix();
}

/// Große Fläche auf einer Ebene, die den ganzen Bereich around abdeckt (um dessen Projektion, nicht um den Ursprung)
TopoDS_Face planeFace(const gp_Pln& pln, const Base::BoundBox3d& around)
{
    const double far = around.CalcDiagonalLength() * 2 + 10;
    const Base::Vector3d c = around.GetCenter();
    double u = 0, v = 0;
    ElSLib::Parameters(pln, gp_Pnt(c.x, c.y, c.z), u, v);
    return BRepBuilderAPI_MakeFace(pln, u - far, u + far, v - far, v + far).Face();
}

/// Werkzeugform aus einem Bezug: Ebene -> große Fläche über den Körper, Skizze -> Kanten senkrecht zur Skizze
/// gezogen (Flächen), sonst die gewählte Fläche bzw. das Objekt selbst
TopoDS_Shape toolShape(const App::PropertyLinkSub& link, const Base::BoundBox3d& around)
{
    App::DocumentObject* obj = link.getValue();
    if (!obj) {
        return {};
    }
    const double far = around.CalcDiagonalLength() * 2 + 10;
    const auto& subs = link.getSubValues();
    const std::string sub = subs.empty() ? std::string() : subs.front();
    if (obj->getTypeId().isDerivedFrom(Base::Type::fromName("Sketcher::SketchObject")) && sub.empty()) {
        auto sketch = static_cast<Part::Feature*>(obj);
        Base::Vector3d n;
        sketch->Placement.getValue().getRotation().multVec(Base::Vector3d(0, 0, 1), n);
        const gp_Vec dir(n.x * far, n.y * far, n.z * far);
        BRep_Builder builder;
        TopoDS_Compound walls;
        builder.MakeCompound(walls);
        for (TopExp_Explorer e(sketch->Shape.getShape().getShape(), TopAbs_EDGE); e.More(); e.Next()) {
            gp_Trsf back;
            back.SetTranslation(-dir);
            const TopoDS_Shape start = BRepBuilderAPI_Transform(e.Current(), back, Standard_True).Shape();
            builder.Add(walls, BRepPrimAPI_MakePrism(start, dir * 2).Shape());
        }
        return walls;
    }
    gp_Ax3 ax;
    if (planeAxes(link, ax) && (sub.empty() || sub.rfind("Face", 0) == 0)) {
        return planeFace(gp_Pln(ax), around);
    }
    return Part::Feature::getTopoShape(obj, Part::ShapeOption::ResolveLink | Part::ShapeOption::Transform | Part::ShapeOption::NeedSubElement,
                                       sub.empty() ? nullptr : sub.c_str())
        .getShape();
}

/// Nach außen zeigende Normale einer ebenen Fläche und ihr Schwerpunkt
bool planarFrame(const TopoDS_Face& face, gp_Pnt& center, gp_Vec& normal)
{
    BRepAdaptor_Surface surface(face);
    if (surface.GetType() != GeomAbs_Plane) {
        return false;
    }
    GProp_GProps props;
    BRepGProp::SurfaceProperties(face, props);
    center = props.CentreOfMass();
    normal = gp_Vec(surface.Plane().Axis().Direction());
    if (face.Orientation() == TopAbs_REVERSED) {
        normal.Reverse();
    }
    return true;
}

/// Achse eines frei gewählten Bezugs, global. Ebenen (Ursprung, Konstruktion, ebene Fläche): Normale durch einen
/// Punkt der Ebene, planar = true. Achsen und gerade Kanten: ihre Richtung. Zylinderflächen und Kreiskanten: ihre
/// Mittelachse. Leerer Bezug oder etwas anderes: false.
bool referenceAxis(const App::PropertyLinkSub& link, gp_Ax1& axis, bool& planar)
{
    App::DocumentObject* obj = link.getValue();
    if (!obj) {
        return false;
    }
    const auto& subs = link.getSubValues();
    const std::string sub = subs.empty() ? std::string() : subs.front();
    planar = false;
    if (sub.empty()) {
        if (auto datum = freecad_cast<App::DatumElement*>(obj)) {  // Ursprungsebene oder -achse
            const Base::Placement p = datum->globalPlacement();
            const Base::Vector3d d = p.getRotation().multVec(datum->getBaseDirection());
            const Base::Vector3d o = p.getPosition();
            if (d.Length() < Precision::Confusion()) {
                return false;  // Ursprungspunkt
            }
            axis = gp_Ax1(gp_Pnt(o.x, o.y, o.z), gp_Dir(d.x, d.y, d.z));
            planar = obj->isDerivedFrom<App::Plane>();
            return true;
        }
    }
    // Konstruktionsebene/-achse (Form = eine Fläche bzw. Kante) oder ein Element eines Körpers
    Part::TopoShape shape = Part::Feature::getTopoShape(
        obj, Part::ShapeOption::ResolveLink | Part::ShapeOption::Transform | Part::ShapeOption::NeedSubElement,
        sub.empty() ? nullptr : sub.c_str());
    if (sub.empty()) {
        if (shape.countSubShapes(TopAbs_FACE) == 1) {
            shape = shape.getSubTopoShape(TopAbs_FACE, 1);
        }
        else if (shape.countSubShapes(TopAbs_FACE) == 0 && shape.countSubShapes(TopAbs_EDGE) == 1) {
            shape = shape.getSubTopoShape(TopAbs_EDGE, 1);
        }
    }
    const TopoDS_Shape s = shape.getShape();
    if (s.IsNull()) {
        return false;
    }
    if (s.ShapeType() == TopAbs_FACE) {
        BRepAdaptor_Surface surface(TopoDS::Face(s));
        if (surface.GetType() == GeomAbs_Plane) {
            gp_Pnt center;
            gp_Vec normal;
            planarFrame(TopoDS::Face(s), center, normal);
            axis = gp_Ax1(center, gp_Dir(normal));
            planar = true;
            return true;
        }
        if (surface.GetType() == GeomAbs_Cylinder) {
            axis = surface.Cylinder().Axis();
            return true;
        }
        return false;
    }
    if (s.ShapeType() == TopAbs_EDGE) {
        BRepAdaptor_Curve curve(TopoDS::Edge(s));
        if (curve.GetType() == GeomAbs_Line) {
            axis = gp_Ax1(curve.Value(curve.FirstParameter()), curve.Line().Direction());
            return true;
        }
        if (curve.GetType() == GeomAbs_Circle) {
            axis = curve.Circle().Axis();
            return true;
        }
    }
    return false;
}

/// Mehrere Werkzeugkörper zu einem vereinen
Part::TopoShape fuseAll(const std::vector<Part::TopoShape>& shapes, App::StringHasherRef hasher)
{
    if (shapes.size() == 1) {
        return shapes.front();
    }
    Part::TopoShape tool = Part::TopoShape(0, hasher).makeElementFuse(shapes);
    return tool.makeElementRefine(nullptr, Part::RefineFail::shapeUntouched);
}

/// "Durch alles": eine Länge, die von around aus hinter jeden Körper des Designs reicht
double throughAllLength(const App::Document* doc, Base::BoundBox3d around)
{
    for (auto obj : doc->getObjectsOfType(Body::getClassTypeId())) {
        const Part::TopoShape s = static_cast<Body*>(obj)->Shape.getShape();
        if (!s.isNull()) {
            around.Add(s.getBoundBox());
        }
    }
    return around.CalcDiagonalLength() * 2 + 10;
}

// --- Normen: Gewinde und Bohrungen (Tabellen aus PartDesign, Senkungen aus dessen JSON-Dateien) -----------

/// Index in PartDesign::Hole::threadDescription; "Custom" = eigene Maße
const char* StandardEnums[] = {"Custom", "ISO metric", "ISO metric fine", "UNC", "UNF", nullptr};
const char* KindEnums[] = {"Clearance hole", "Tapped hole", nullptr};
const char* FitEnums[] = {"Fine", "Medium", "Coarse", nullptr};

const std::vector<PartDesign::Hole::ThreadDescription>* threadTable(long standard)
{
    return standard >= 1 && standard <= 4 ? &PartDesign::Hole::threadDescription[standard] : nullptr;
}

const PartDesign::Hole::ThreadDescription* threadSize(long standard, const std::string& designation)
{
    if (auto table = threadTable(standard)) {
        for (const auto& t : *table) {
            if (designation == t.designation) {
                return &t;
            }
        }
    }
    return nullptr;
}

/// Durchgangsbohrung für eine Schraube: ISO 273 (fein/mittel/grob) bzw. ASME B18.2.8 (close/normal/loose)
double clearanceDiameter(long standard, const PartDesign::Hole::ThreadDescription& t, long fit)
{
    if (standard <= 2) {
        for (const auto& row : PartDesign::Hole::metricHoleDiameters) {
            if (std::abs(row[0] - t.diameter) < 1e-6) {
                return row[1 + fit];  // {Schraube, fein, mittel, grob}
            }
        }
    }
    else {
        for (const auto& row : PartDesign::Hole::UTSHoleDiameters) {
            if (row.designation == t.designation) {
                return fit == 0 ? row.close : fit == 1 ? row.normal : row.loose;
            }
        }
    }
    return t.diameter * (1.06 + 0.06 * fit);  // ponytail: Näherung für Größen außerhalb der Tabellen
}

/// Senkung je Schraubennorm (Mod/PartDesign/Resources/Hole/*.json); gleichnamige Dateien (Regel/Fein) zusammen
struct HeadTable
{
    std::string name;
    bool countersink = false;
    double angle = 90;
    std::map<std::string, std::pair<double, double>> sizes;  ///< Gewinde -> (Durchmesser, Tiefe)
};

const std::vector<HeadTable>& headTables()
{
    static const std::vector<HeadTable> tables = [] {
        std::vector<HeadTable> result;
        const std::filesystem::path dir = App::Application::getResourceDir() + "Mod/PartDesign/Resources/Hole";
        std::error_code ec;
        std::vector<std::filesystem::path> files;
        for (const auto& entry : std::filesystem::directory_iterator(dir, ec)) {
            if (entry.path().extension() == ".json") {
                files.push_back(entry.path());
            }
        }
        std::ranges::sort(files);
        for (const auto& file : files) {
            try {
                std::ifstream in(file);
                const nlohmann::json j = nlohmann::json::parse(in);
                const std::string name = j.at("name");
                auto it = std::ranges::find(result, name, &HeadTable::name);
                if (it == result.end()) {
                    result.push_back({name, j.at("cut_type") == "countersink", j.value("angle", 90.0), {}});
                    it = result.end() - 1;
                }
                for (const auto& row : j.at("data")) {
                    it->sizes[row.at("thread")] = {row.at("diameter").get<double>(), row.value("depth", 0.0)};
                }
            }
            catch (const std::exception&) {
                Base::Console().warning("Design: could not read %s\n", file.string().c_str());
            }
        }
        return result;
    }();
    return tables;
}

TopoDS_Shape threadGrooves(const gp_Ax1& axis, double start, double length, double r, double pitch, bool external,
                           bool left, double clearance);

/// Gewinde-Rillen als Werkzeug zum Abziehen, ISO-Profil (60°). external: Welle mit Außenradius r, sonst Bohrung
/// mit Kernradius r. Die Rillen gehen über die ganze Länge [start, start + length] entlang der Achse und enden dort
/// glatt abgeschnitten (nichts dahinter wird angeschnitten: Schulter, Bohrungsgrund). clearance > 0 macht die Welle
/// kleiner bzw. die Bohrung größer (Spiel je Seite, radial), < 0 gibt Übermaß. Die Rillen liegen auf einem festen
/// Raster entlang der Achse (Innengewinde um eine halbe Steigung versetzt): Welle und Bohrung greifen ineinander.
TopoDS_Shape threadTool(const gp_Ax1& axis, double start, double length, double r, double pitch, bool external,
                        bool left, double clearance)
{
    // Zwei Steigungen vor der Fläche anfangen (sonst fehlt bei jedem Winkel kurz vor dem ersten Umlauf der Gang davor
    // und am Rand bleibt Material stehen), eine danach aufhören, dann auf die Länge zuschneiden
    const TopoDS_Shape raw = threadGrooves(axis, start - 2 * pitch, length + 3 * pitch, r, pitch, external, left, clearance);
    gp_Ax2 clipAxis(axis.Location().Translated(gp_Vec(axis.Direction()) * start), axis.Direction());
    const double outer = r + pitch + std::abs(clearance) + 1;
    const TopoDS_Shape clipped = BRepAlgoAPI_Common(raw, BRepPrimAPI_MakeCylinder(clipAxis, outer, length).Shape()).Shape();
    // Common liefert einen Compound um den Solid; als Werkzeug zählt nur der Solid selbst (sonst trennt der Schnitt
    // nur Flächen auf, ohne etwas abzuziehen)
    TopExp_Explorer solid(clipped, TopAbs_SOLID);
    if (!solid.More()) {
        throw Standard_Failure("thread tool is empty");
    }
    return solid.Current();
}

TopoDS_Shape threadGrooves(const gp_Ax1& axis, double start, double length, double r, double pitch, bool external,
                           bool left, double clearance)
{
    const double p = pitch, t30 = std::tan(M_PI / 6);
    const double depth = external ? 0.6134 * p : 0.5413 * p;  // ISO 68-1/724: d3 bzw. D1
    const double surfaceHalf = external ? 7 * p / 16 : 3 * p / 8;  // halbe Rillenbreite an der Oberfläche
    const double margin = 0.05 * p + std::abs(clearance);
    const double s = external ? -1 : 1;                                     // Richtung in den Werkstoff
    const double surface = external ? r - clearance : r + clearance;        // Oberfläche nach dem Spiel
    const double cap = 0.49 * p;
    const double outerHalf = std::min(cap, surfaceHalf + margin * t30);
    // Profil in der XZ-Ebene: x = Radius, z = Lage entlang der Achse
    BRepBuilderAPI_MakePolygon profile(gp_Pnt(surface - s * margin, 0, -outerHalf), gp_Pnt(surface - s * margin, 0, outerHalf),
                                       gp_Pnt(surface + s * depth, 0, surfaceHalf - depth * t30),
                                       gp_Pnt(surface + s * depth, 0, -(surfaceHalf - depth * t30)), Standard_True);
    // makeLongHelix: mit makeHelix (Kurve auf einer Zylinderfläche) legt MakePipeShell das Profil auf den doppelten
    // Radius und baut einen umgestülpten Körper, der Schnitt entfernt dann nichts (so war es bis 2026-11)
    const TopoDS_Shape helix = Part::TopoShape().makeLongHelix(p, length, r, 0, left);
    TopExp_Explorer spine(helix, TopAbs_WIRE);
    BRepOffsetAPI_MakePipeShell pipe(TopoDS::Wire(spine.Current()));
    pipe.SetMode(gp::DZ());  // Profil bleibt parallel zur Achse
    pipe.Add(profile.Wire());
    pipe.Build();
    pipe.MakeSolid();
    TopoDS_Shape tool = pipe.Shape();
    BRepClass3d_SolidClassifier inside(tool);
    inside.PerformInfinitePoint(Precision::Confusion());
    if (inside.State() == TopAbs_IN) {  // innen und außen vertauscht
        tool.Reverse();
    }
    // Spiel: die Oberfläche selbst abdrehen bzw. aufbohren (Ring zwischen r und der neuen Oberfläche)
    if (std::abs(clearance) > Precision::Confusion() && clearance > 0) {
        const double inner = external ? surface : r - margin, outer = external ? r + margin : surface;
        TopoDS_Shape ring = BRepAlgoAPI_Cut(BRepPrimAPI_MakeCylinder(outer, length).Shape(),
                                            BRepPrimAPI_MakeCylinder(inner, length).Shape()).Shape();
        tool = BRepAlgoAPI_Fuse(tool, ring).Shape();
    }
    gp_Trsf place;
    const double phase = external ? p / 2 : p;  // Rillen der Welle bei start + p/2 + k·p, der Bohrung dazwischen
    place.SetDisplacement(gp_Ax3(gp::XOY()),
                          gp_Ax3(axis.Location().Translated(gp_Vec(axis.Direction()) * (start + phase)), axis.Direction()));
    return BRepBuilderAPI_Transform(tool, place, Standard_True).Shape();
}
}  // namespace

App::Part* Design::root(App::Document* doc, bool create)
{
    for (auto obj : doc->getObjectsOfType(App::Part::getClassTypeId())) {
        auto part = static_cast<App::Part*>(obj);
        if (std::string(part->Type.getValue()) == "Design") {
            return part;
        }
    }
    if (!create) {
        return nullptr;
    }
    auto part = static_cast<App::Part*>(doc->addObject("App::Part", "Root"));
    part->Type.setValue("Design");
    part->Label.setValue("Design");  // der Dokumentname steht schon darüber im Browser
    for (const char* label : {"Bodies", "Sketches"}) {
        auto group = doc->addObject("App::DocumentObjectGroup", label);
        group->Label.setValue(label);
        part->addObject(group);
    }
    return part;
}

bool Design::isComponent(const App::DocumentObject* obj)
{
    auto part = freecad_cast<const App::Part*>(obj);
    if (!part) {
        return false;
    }
    const std::string type = part->Type.getValue();
    return type == "Design" || type == "Component";
}

App::Part* Design::componentOf(const App::DocumentObject* obj)
{
    const App::DocumentObject* current = obj;
    for (int guard = 0; current && guard < 64; ++guard) {
        if (auto group = App::GeoFeatureGroupExtension::getGroupOfObject(current)) {
            if (isComponent(group)) {
                return static_cast<App::Part*>(group);
            }
            current = group;
            continue;
        }
        // Ursprungsebenen/-achsen gehören zum Origin, der Origin zur Komponente
        const App::DocumentObject* owner = nullptr;
        for (auto in : current->getInList()) {
            if (in->isDerivedFrom<App::Origin>() || isComponent(in)) {
                owner = in;
                break;
            }
        }
        if (!owner) {
            break;
        }
        if (isComponent(owner)) {
            return static_cast<App::Part*>(const_cast<App::DocumentObject*>(owner));
        }
        current = owner;
    }
    return root(obj->getDocument(), true);
}

App::Part* Design::newComponent(App::Part* parent)
{
    App::Document* doc = parent->getDocument();
    int count = 0;
    for (auto obj : doc->getObjectsOfType(App::Part::getClassTypeId())) {
        count += std::string(static_cast<App::Part*>(obj)->Type.getValue()) == "Component";
    }
    auto part = static_cast<App::Part*>(doc->addObject("App::Part", "Component"));
    part->Type.setValue("Component");
    part->Label.setValue("Component" + std::to_string(count + 1));
    parent->addObject(part);
    folder(part, "Bodies");
    folder(part, "Sketches");
    return part;
}

App::DocumentObjectGroup* Design::folder(App::Part* root, const char* label)
{
    // über den internen Namen, die Beschriftung ist übersetzt oder umbenannt;
    // FreeCAD macht Namen eindeutig: in Komponenten heißen die Ordner "Bodies001" usw.
    for (auto obj : root->Group.getValues()) {
        auto group = freecad_cast<App::DocumentObjectGroup*>(obj);
        if (!group) {
            continue;
        }
        std::string name = group->getNameInDocument();
        name.erase(name.find_last_not_of("0123456789") + 1);
        if (name == label) {
            return group;
        }
    }
    auto group = static_cast<App::DocumentObjectGroup*>(
        root->getDocument()->addObject("App::DocumentObjectGroup", label)
    );
    group->Label.setValue(label);
    root->addObject(group);
    return group;
}

namespace
{
App::PropertyLinkList* timelineProperty(App::Document* doc, bool create)
{
    App::Part* r = Design::root(doc, create);
    if (!r) {
        return nullptr;
    }
    auto prop = freecad_cast<App::PropertyLinkList*>(r->getPropertyByName("Timeline"));
    if (!prop && create) {
        // Bisherige Einträge in Dokument-Reihenfolge übernehmen (Dateien vor dem Rollback-Marker)
        const auto existing = Design::timeline(doc);
        prop = static_cast<App::PropertyLinkList*>(r->addDynamicProperty(
            "App::PropertyLinkListHidden", "Timeline", "Design", "Order of the timeline", App::Prop_Hidden
        ));
        r->addDynamicProperty("App::PropertyInteger", "RollbackMarker", "Design",
                              "Number of active timeline entries (-1 = all)", App::Prop_Hidden);
        static_cast<App::PropertyInteger*>(r->getPropertyByName("RollbackMarker"))->setValue(-1);
        prop->setValues(existing);
    }
    return prop;
}

App::PropertyInteger* markerProperty(App::Document* doc)
{
    App::Part* r = Design::root(doc, false);
    return r ? freecad_cast<App::PropertyInteger*>(r->getPropertyByName("RollbackMarker")) : nullptr;
}

/// In states (parallel zu stateBodies) für body den Eintrag from durch to ersetzen
void replaceState(App::PropertyLinkList& states, const std::vector<App::DocumentObject*>& stateBodies,
                  const App::DocumentObject* body, App::DocumentObject* from, App::DocumentObject* to)
{
    auto values = states.getValues();
    bool changed = false;
    for (size_t j = 0; j < values.size() && j < stateBodies.size(); ++j) {
        if (values[j] == from && stateBodies[j] == body && to) {
            values[j] = to;
            changed = true;
        }
    }
    if (changed) {
        states.setValues(values);
    }
}

/// Alle Features, die für body auf dem Zustand from aufbauen, bauen stattdessen auf to auf
void rewireUsers(App::DocumentObject* from, App::DocumentObject* to, const App::DocumentObject* body,
                 const App::DocumentObject* except)
{
    for (auto user : from->getInList()) {
        if (user == except) {
            continue;
        }
        if (auto later = freecad_cast<Design::Feature*>(user)) {
            replaceState(later->BaseFeatures, later->Bodies.getValues(), body, from, to);
        }
        if (auto combine = freecad_cast<Design::Combine*>(user)) {
            replaceState(combine->ToolFeatures, combine->ToolBodies.getValues(), body, from, to);
        }
        if (auto mirror = freecad_cast<Design::Mirror*>(user)) {
            replaceState(mirror->SourceFeatures, mirror->SourceBodies.getValues(), body, from, to);
        }
        if (auto pattern = freecad_cast<Design::Pattern*>(user)) {
            replaceState(pattern->SourceFeatures, pattern->SourceBodies.getValues(), body, from, to);
        }
    }
}
}  // namespace

std::vector<App::DocumentObject*> Design::timeline(App::Document* doc)
{
    if (auto prop = timelineProperty(doc, false)) {
        auto items = prop->getValues();
        std::erase(items, nullptr);
        return items;
    }
    std::vector<App::DocumentObject*> items;
    for (auto obj : doc->getObjects()) {
        if (obj->isDerivedFrom<Feature>() || obj->getTypeId().isDerivedFrom(Base::Type::fromName("Sketcher::SketchObject"))) {
            items.push_back(obj);
        }
    }
    return items;
}

void Design::addToTimeline(App::DocumentObject* obj)
{
    App::Document* doc = obj->getDocument();
    auto prop = timelineProperty(doc, true);
    auto items = prop->getValues();
    std::erase(items, obj);
    auto marker = markerProperty(doc);
    const int m = marker ? marker->getValue() : -1;
    if (m < 0 || m >= static_cast<int>(items.size())) {
        items.push_back(obj);
        if (marker && m >= 0) {
            marker->setValue(static_cast<int>(items.size()));
        }
    }
    else {
        items.insert(items.begin() + m, obj);  // an der Marker-Position einfügen
        marker->setValue(m + 1);
    }
    prop->setValues(items);
}

int Design::rollbackMarker(App::Document* doc)
{
    auto marker = markerProperty(doc);
    return marker ? marker->getValue() : -1;
}

void Design::setRollbackMarker(App::Document* doc, int active)
{
    timelineProperty(doc, true);
    const int count = static_cast<int>(timeline(doc).size());
    markerProperty(doc)->setValue(active < 0 || active >= count ? -1 : active);
    for (auto obj : doc->getObjectsOfType(Feature::getClassTypeId())) {
        obj->touch();
    }
    doc->recompute();
}

bool Design::isRolledBack(const App::DocumentObject* obj)
{
    const int m = rollbackMarker(obj->getDocument());
    if (m < 0) {
        return false;
    }
    const auto items = timeline(obj->getDocument());
    const auto idx = std::ranges::find(items, obj) - items.begin();
    return idx < static_cast<long>(items.size()) && idx >= m;
}

App::DocumentObject* Design::stateAtMarker(Body* body)
{
    App::DocumentObject* state = body->Tip.getValue();
    while (auto f = freecad_cast<Feature*>(state)) {
        if (!isRolledBack(f)) {
            return f;
        }
        // Zurückgerollt: Zustand davor für diesen Body
        const auto& bodies = f->Bodies.getValues();
        const auto& bases = f->BaseFeatures.getValues();
        const auto idx = std::ranges::find(bodies, body) - bodies.begin();
        state = idx < static_cast<long>(bases.size()) ? bases[idx] : nullptr;
    }
    return state;
}

void Design::attachToBodies(Feature* feature, const std::vector<Body*>& bodies)
{
    std::vector<App::DocumentObject*> objs, bases;
    for (auto b : bodies) {
        objs.push_back(b);
        bases.push_back(stateAtMarker(b));
    }
    feature->Bodies.setValues(objs);
    feature->BaseFeatures.setValues(bases);
    for (size_t i = 0; i < bodies.size(); ++i) {
        if (!bases[i]) {
            continue;
        }
        rewireUsers(bases[i], feature, bodies[i], feature);  // eingefügt: spätere Features bauen auf diesem auf
        if (bodies[i]->Tip.getValue() == bases[i]) {
            bodies[i]->Tip.setValue(feature);
        }
    }
}

std::vector<std::string> Design::detachFromBodies(Feature* feature)
{
    const auto bodies = feature->Bodies.getValues();
    const auto bases = feature->BaseFeatures.getValues();
    std::vector<std::string> orphans;
    for (size_t i = 0; i < bodies.size(); ++i) {
        App::DocumentObject* base = i < bases.size() ? bases[i] : nullptr;
        if (base) {
            rewireUsers(feature, base, bodies[i], nullptr);
        }
        auto body = freecad_cast<Body*>(bodies[i]);
        if (body && body->Tip.getValue() == feature) {
            if (base) {
                body->Tip.setValue(base);
            }
            else {
                orphans.emplace_back(body->getNameInDocument());  // nur von diesem Feature erzeugt
            }
        }
    }
    feature->Bodies.setValues({});
    feature->BaseFeatures.setValues({});
    return orphans;
}

void Design::removeFromTimeline(App::DocumentObject* obj)
{
    App::Document* doc = obj->getDocument();
    if (auto prop = timelineProperty(doc, false)) {
        auto items = prop->getValues();
        const auto idx = std::ranges::find(items, obj) - items.begin();
        auto marker = markerProperty(doc);
        if (marker && marker->getValue() > idx) {
            marker->setValue(marker->getValue() - 1);
        }
        std::erase(items, obj);
        prop->setValues(items);
    }
    auto feature = freecad_cast<Feature*>(obj);
    if (!feature) {  // Skizze: mit ihrem Profiles-Begleiter
        if (auto profiles = Profiles::forSketch(obj)) {
            doc->removeObject(profiles->getNameInDocument());
        }
        doc->removeObject(obj->getNameInDocument());
        return;
    }
    const auto orphans = detachFromBodies(feature);
    doc->removeObject(feature->getNameInDocument());
    for (const auto& name : orphans) {
        doc->removeObject(name.c_str());
    }
}

/// Name ("FaceN", "EdgeN", "VertexN") des Elements in shape, das geometrisch element entspricht (Schwerpunkt + Größe).
/// ponytail: geometrischer Abgleich statt topologischer Benennung; kann bei zwei deckungsgleichen Elementen irren
std::string Design::elementName(const TopoDS_Shape& shape, const TopoDS_Shape& element)
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
void Design::stableRef(App::DocumentObject*& obj, std::string& element)
{
    auto body = freecad_cast<Body*>(obj);
    auto tip = body ? freecad_cast<Feature*>(stateAtMarker(body)) : nullptr;
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

namespace
{
/// a braucht b – ohne a's eigene Körper-Kette (BaseFeatures), die beim Umsortieren neu verbunden wird
bool dependsOn(const App::DocumentObject* a, const App::DocumentObject* b)
{
    std::set<const App::DocumentObject*> seen;
    std::vector<const App::DocumentObject*> todo;
    std::vector<App::Property*> props;
    a->getPropertyList(props);
    for (App::Property* prop : props) {
        if (std::strcmp(prop->getName(), "BaseFeatures") != 0) {
            for (auto o : a->getOutListOfProperty(prop)) {
                todo.push_back(o);
            }
        }
    }
    while (!todo.empty()) {
        const App::DocumentObject* o = todo.back();
        todo.pop_back();
        if (o == b) {
            return true;
        }
        if (o && seen.insert(o).second) {
            for (auto next : o->getOutList()) {
                todo.push_back(next);
            }
        }
    }
    return false;
}
}  // namespace

bool Design::moveInTimeline(App::DocumentObject* obj, int to, std::string& error)
{
    App::Document* doc = obj->getDocument();
    auto prop = timelineProperty(doc, true);
    auto items = prop->getValues();
    std::erase(items, nullptr);
    const int from = static_cast<int>(std::ranges::find(items, obj) - items.begin());
    if (from >= static_cast<int>(items.size())) {
        error = "Not in the timeline";
        return false;
    }
    to = std::clamp(to, 0, static_cast<int>(items.size()) - 1);
    if (to == from) {
        return true;
    }
    for (int i = std::min(from, to); i <= std::max(from, to); ++i) {
        App::DocumentObject* other = items[i];
        if (other == obj) {
            continue;
        }
        if (to < from ? dependsOn(obj, other) : dependsOn(other, obj)) {
            error = std::string(to < from ? "It needs " : "It is needed by ") + other->Label.getValue();
            return false;
        }
    }
    // Ein Feature, das Bodies verändert, an der neuen Stelle in deren Kette einhängen
    auto feature = freecad_cast<Feature*>(obj);
    std::vector<Body*> bodies;
    if (feature && feature->BaseFeatures.getSize() > 0) {
        for (auto b : feature->Bodies.getValues()) {
            if (auto body = freecad_cast<Body*>(b)) {
                bodies.push_back(body);
            }
        }
        detachFromBodies(feature);
    }
    items.erase(items.begin() + from);
    items.insert(items.begin() + to, obj);
    prop->setValues(items);
    if (!bodies.empty()) {
        auto marker = markerProperty(doc);
        const int saved = marker->getValue();
        marker->setValue(to);  // Zustand der Bodies direkt vor der neuen Stelle
        attachToBodies(feature, bodies);
        marker->setValue(saved);
    }
    for (auto o : doc->getObjectsOfType(Feature::getClassTypeId())) {
        o->touch();
    }
    doc->recompute();
    return true;
}

bool Design::setTimelineGroup(const std::vector<App::DocumentObject*>& objs, const std::string& name)
{
    if (objs.empty()) {
        return false;
    }
    const auto items = timeline(objs.front()->getDocument());
    std::vector<long> idx;
    for (auto o : objs) {
        idx.push_back(std::ranges::find(items, o) - items.begin());
    }
    std::ranges::sort(idx);
    if (idx.back() >= static_cast<long>(items.size()) || idx.back() - idx.front() + 1 != static_cast<long>(idx.size())) {
        return false;  // nur aufeinanderfolgende Einträge
    }
    for (auto o : objs) {
        auto group = freecad_cast<App::PropertyString*>(o->getPropertyByName("TimelineGroup"));
        if (!group) {
            group = static_cast<App::PropertyString*>(
                o->addDynamicProperty("App::PropertyString", "TimelineGroup", "Design", "Group in the timeline", App::Prop_Hidden));
        }
        group->setValue(name);
    }
    return true;
}

std::string Design::timelineGroup(const App::DocumentObject* obj)
{
    auto group = freecad_cast<App::PropertyString*>(obj->getPropertyByName("TimelineGroup"));
    return group ? group->getValue() : std::string();
}

const std::vector<Design::PhysicalMaterial>& Design::physicalMaterials()
{
    static const std::vector<PhysicalMaterial> list = {
        {"Aluminum", "9bf060e9-1663-44a2-88e2-2ff6ee858efe"},
        {"Steel", "90bbd8ef-8623-4d78-b3bf-e0bdb9b74dd3"},
        {"Cast Iron", "1826c364-d26a-43fb-8f61-288281236836"},
        {"Titanium", "f8013463-8008-4063-818c-ab6884cfa015"},
        {"Wood", "b588224e-e8d6-47ad-ba1f-a058333fd1c6"},
        {"PLA", "93861244-fbbe-41a9-a7e0-aeed53abd782"},
        {"PETG", "f73004e3-6fb4-4591-8be7-89d1370be312"},
        {"ABS", "73371529-2983-47dd-b988-6739a2e20029"},
        {"Nylon", "9d59dc3b-ce66-4bec-82c9-b962082e7c9e"},
        {"Acrylic", "f255cd82-91d5-4e97-9032-1843128a2eaa"},
        {"Glass", "3e3a3e13-04a4-410e-8e36-bbd83ca66847"},
        {"Concrete", "26042aa5-56e6-4d99-8b63-dd8b9ea5a37a"},
    };
    return list;
}

std::string Design::physicalMaterialFor(const std::string& appearance, const std::string& group)
{
    const auto has = [&appearance](const char* word) { return appearance.find(word) != std::string::npos; };
    const auto uuid = [](const char* name) {
        for (const auto& m : physicalMaterials()) {
            if (std::strcmp(m.name, name) == 0) {
                return std::string(m.uuid);
            }
        }
        return std::string();
    };
    // ponytail: Zuordnung über Namen und Gruppe; Messing, Kupfer, Gummi, Stein und Lacke bleiben offen (keine passende
    // Karte bzw. Farbe sagt nichts über den Werkstoff)
    if (group == "Anodized" || has("Aluminum")) {
        return uuid("Aluminum");
    }
    if (has("Steel") || has("Chrome")) {
        return uuid("Steel");
    }
    if (has("Iron")) {
        return uuid("Cast Iron");
    }
    if (has("Titanium")) {
        return uuid("Titanium");
    }
    if (group == "Wood") {
        return uuid("Wood");
    }
    if (has("PLA")) {
        return uuid("PLA");
    }
    if (has("PETG")) {
        return uuid("PETG");
    }
    if (has("Nylon")) {
        return uuid("Nylon");
    }
    if (has("Acrylic")) {
        return uuid("Acrylic");
    }
    if (group == "Glass") {
        return uuid("Glass");
    }
    if (has("Concrete")) {
        return uuid("Concrete");
    }
    if (group == "Plastic") {
        return uuid("ABS");
    }
    return {};
}

bool Design::setPhysicalMaterial(Part::Feature* body, const std::string& uuid, bool chosen)
{
    try {
        auto material = Materials::MaterialManager::getManager().getMaterial(QString::fromStdString(uuid));
        if (!material) {
            return false;
        }
        body->ShapeMaterial.setValue(*material);
    }
    catch (const Base::Exception&) {
        return false;
    }
    auto flag = freecad_cast<App::PropertyBool*>(body->getPropertyByName("PhysicalMaterialChosen"));
    if (!flag) {
        flag = static_cast<App::PropertyBool*>(body->addDynamicProperty(
            "App::PropertyBool", "PhysicalMaterialChosen", "Design", "Material picked by the user", App::Prop_Hidden));
    }
    flag->setValue(chosen);
    return true;
}

bool Design::physicalMaterialChosen(const App::DocumentObject* body)
{
    auto flag = freecad_cast<App::PropertyBool*>(body->getPropertyByName("PhysicalMaterialChosen"));
    return flag && flag->getValue();
}

double Design::mass(const Part::Feature* body)
{
    const Materials::Material& material = body->ShapeMaterial.getValue();
    if (!material.hasPhysicalProperty(QStringLiteral("Density"))) {
        return 0;
    }
    const Base::Quantity density = material.getPhysicalQuantity(QStringLiteral("Density"));
    const TopoDS_Shape shape = body->Shape.getShape().getShape();
    if (shape.IsNull()) {
        return 0;
    }
    GProp_GProps props;
    BRepGProp::VolumeProperties(shape, props);
    return density.getValue() * props.Mass();  // intern kg/mm³ mal mm³
}

std::vector<std::pair<App::DocumentObject*, App::DocumentObject*>> Design::collisions(App::Part* moving)
{
    std::vector<std::pair<App::DocumentObject*, App::DocumentObject*>> hits;
    const auto inside = [moving](const App::DocumentObject* body) {
        for (App::Part* c = componentOf(body); c; ) {
            if (c == moving) {
                return true;
            }
            App::Part* parent = nullptr;
            for (auto in : c->getInList()) {
                if (auto part = freecad_cast<App::Part*>(in); part && part->hasObject(c)) {
                    parent = part;
                }
            }
            c = parent;
        }
        return false;
    };
    std::vector<App::DocumentObject*> mine, others;
    for (auto obj : moving->getDocument()->getObjectsOfType(Body::getClassTypeId())) {
        if (obj->Visibility.getValue() && !static_cast<Body*>(obj)->Shape.getShape().isNull()) {
            (inside(obj) ? mine : others).push_back(obj);
        }
    }
    const auto global = [](App::DocumentObject* o) {  // mit der Lage aller übergeordneten Komponenten
        Part::TopoShape s = static_cast<Body*>(o)->Shape.getShape();
        s.setPlacement(static_cast<Body*>(o)->globalPlacement());
        return s.getShape();
    };
    for (auto a : mine) {
        const TopoDS_Shape sa = global(a);
        for (auto b : others) {
            const TopoDS_Shape sb = global(b);
            Bnd_Box ba, bb;
            BRepBndLib::Add(sa, ba);
            BRepBndLib::Add(sb, bb);
            if (ba.IsOut(bb)) {
                continue;
            }
            GProp_GProps props;
            BRepGProp::VolumeProperties(BRepAlgoAPI_Common(sa, sb).Shape(), props);
            if (props.Mass() > 1e-6) {
                hits.emplace_back(a, b);
            }
        }
    }
    return hits;
}

Design::Body* Design::newBody(Feature* feature, App::Part* component)
{
    App::Document* doc = feature->getDocument();
    const auto count = doc->getObjectsOfType(Body::getClassTypeId()).size();
    auto body = static_cast<Body*>(doc->addObject("Design::Body", "Body"));
    body->Label.setValue("Body" + std::to_string(count + 1));
    folder(component ? component : componentOf(feature), "Bodies")->addObject(body);
    feature->Bodies.setValues({body});
    feature->BaseFeatures.setValues({});
    body->Tip.setValue(feature);
    return body;
}

App::DocumentObject* Design::newSketch(App::Part* component)
{
    App::Document* doc = component->getDocument();
    auto sketch = doc->addObject("Sketcher::SketchObject", "Sketch");
    folder(component, "Sketches")->addObject(sketch);
    addToTimeline(sketch);
    auto profiles = static_cast<Profiles*>(doc->addObject("Design::Profiles", "Profiles"));
    component->addObject(profiles);
    profiles->Sketch.setValue(sketch);
    return sketch;
}

// ---------------------------------------------------------------------------------------------

PROPERTY_SOURCE(Design::Body, Part::Feature)

Body::Body()
{
    ADD_PROPERTY_TYPE(Tip, (nullptr), "Design", App::Prop_Hidden, "Last feature that changed this body");
}

App::DocumentObjectExecReturn* Body::execute()
{
    auto tip = freecad_cast<Design::Feature*>(Tip.getValue());
    Shape.setValue(tip ? tip->shapeFor(this) : Part::TopoShape());
    return StdReturn;
}

// ---------------------------------------------------------------------------------------------

PROPERTY_SOURCE(Design::Profiles, Part::Feature)

Profiles::Profiles()
{
    ADD_PROPERTY_TYPE(Sketch, (nullptr), "Design", App::Prop_None, "Sketch whose closed regions are offered");
    ADD_PROPERTY_TYPE(Signatures, (), "Design", App::PropertyType(App::Prop_Output | App::Prop_Hidden),
                      "Bounding sketch edges of each profile");
}

Profiles* Profiles::forSketch(App::DocumentObject* sketch)
{
    for (auto obj : sketch->getInList()) {
        auto profiles = freecad_cast<Profiles*>(obj);
        if (profiles && profiles->Sketch.getValue() == sketch) {
            return profiles;
        }
    }
    return nullptr;
}

App::DocumentObjectExecReturn* Profiles::execute()
{
    auto sketch = freecad_cast<Part::Feature*>(Sketch.getValue());
    if (!sketch) {
        return new App::DocumentObjectExecReturn("No sketch linked");
    }
    // In Skizzen-Koordinaten (XY-Ebene) rechnen, Ergebnis wieder auf die Skizzen-Lage setzen
    const TopoDS_Shape local = sketch->Shape.getShape().getShape().Located(TopLoc_Location());
    TopTools_ListOfShape edges;
    for (TopExp_Explorer ex(local, TopAbs_EDGE); ex.More(); ex.Next()) {
        edges.Append(ex.Current());
    }
    if (edges.IsEmpty()) {
        Shape.setValue(Part::TopoShape());
        return StdReturn;
    }

    // Eine große Fläche um die Skizze mit allen Kanten zerschneiden: jede entstehende Fläche,
    // die den äußeren Rand nicht berührt, ist eine geschlossene Region. Überlappende Formen
    // ergeben so automatisch mehrere Regionen, offene Linien werden ignoriert.
    Bnd_Box box;
    BRepBndLib::Add(local, box);
    double x0, y0, z0, x1, y1, z1;
    box.Get(x0, y0, z0, x1, y1, z1);
    const double m = std::max(x1 - x0, y1 - y0) * 0.1 + 1.0;
    x0 -= m, y0 -= m, x1 += m, y1 += m;
    TopTools_ListOfShape args;
    args.Append(BRepBuilderAPI_MakeFace(gp_Pln(gp::XOY()), x0, x1, y0, y1).Face());

    BRepAlgoAPI_Splitter splitter;
    splitter.SetArguments(args);
    splitter.SetTools(edges);
    splitter.Build();
    if (!splitter.IsDone()) {
        return new App::DocumentObjectExecReturn("Could not compute sketch profiles");
    }

    // Welche Skizzenkante steckt hinter jedem Kantenstück? (für die Profil-Signaturen)
    TopTools_DataMapOfShapeInteger source;
    int edgeIndex = 0;
    for (TopTools_ListIteratorOfListOfShape it(edges); it.More(); it.Next(), ++edgeIndex) {
        source.Bind(it.Value(), edgeIndex);
        for (TopTools_ListIteratorOfListOfShape piece(splitter.Modified(it.Value())); piece.More(); piece.Next()) {
            source.Bind(piece.Value(), edgeIndex);
        }
    }
    struct Region
    {
        TopoDS_Face face;
        gp_Pnt center;
        std::string signature;  ///< sortierte Indizes der begrenzenden Skizzenkanten
    };
    std::vector<Region> regions;
    const double tol = 1e-6 * m;
    for (TopExp_Explorer ex(splitter.Shape(), TopAbs_FACE); ex.More(); ex.Next()) {
        bool outer = false;
        for (TopExp_Explorer vx(ex.Current(), TopAbs_VERTEX); vx.More() && !outer; vx.Next()) {
            const gp_Pnt p = BRep_Tool::Pnt(TopoDS::Vertex(vx.Current()));
            outer = std::abs(p.X() - x0) < tol || std::abs(p.X() - x1) < tol
                || std::abs(p.Y() - y0) < tol || std::abs(p.Y() - y1) < tol;
        }
        if (!outer) {
            GProp_GProps props;
            BRepGProp::SurfaceProperties(ex.Current(), props);
            std::set<int> ids;
            for (TopExp_Explorer ed(ex.Current(), TopAbs_EDGE); ed.More(); ed.Next()) {
                const TopoDS_Shape forward = ed.Current().Oriented(TopAbs_FORWARD);
                if (source.IsBound(forward)) {
                    ids.insert(source.Find(forward));
                }
                else if (source.IsBound(ed.Current())) {
                    ids.insert(source.Find(ed.Current()));
                }
            }
            std::string signature;
            for (int id : ids) {
                signature += (signature.empty() ? "" : ",") + std::to_string(id);
            }
            regions.push_back({TopoDS::Face(ex.Current()), props.CentreOfMass(), signature});
        }
    }
    // Feste Reihenfolge (links nach rechts, unten nach oben); Extrude & Co. finden ihre Profile zusätzlich
    // über die Signaturen wieder, wenn sich die Nummerierung durch Skizzenänderungen verschiebt
    std::ranges::sort(regions, [](const Region& a, const Region& b) {
        return a.center.X() != b.center.X() ? a.center.X() < b.center.X() : a.center.Y() < b.center.Y();
    });

    std::vector<Part::TopoShape> faces;
    std::vector<std::string> signatures;
    for (auto& r : regions) {
        faces.emplace_back(r.face);
        signatures.push_back(r.signature);
    }
    Signatures.setValues(signatures);
    Part::TopoShape result;
    if (!faces.empty()) {
        result.makeElementCompound(faces);
    }
    // Lage über die Placement-Eigenschaft: Part::Feature überschreibt beim Recompute die Shape-Lage damit
    Placement.setValue(sketch->Placement.getValue());
    Shape.setValue(result);
    return StdReturn;
}

// ---------------------------------------------------------------------------------------------

PROPERTY_SOURCE(Design::Feature, Part::Feature)

Feature::Feature()
{
    ADD_PROPERTY_TYPE(Operation, (0L), "Design", App::Prop_None, "New body, join, cut or intersect");
    Operation.setEnums(OpEnums);
    ADD_PROPERTY_TYPE(Bodies, (nullptr), "Design", App::Prop_None, "Bodies changed by this feature");
    ADD_PROPERTY_TYPE(BaseFeatures, (nullptr), "Design", App::Prop_Hidden, "Previous feature per body");
    ADD_PROPERTY_TYPE(Suppressed, (false), "Design", App::Prop_None, "Skip this feature");
    const auto output = App::PropertyType(App::Prop_Output | App::Prop_Hidden);
    ADD_PROPERTY_TYPE(Fixes, (), "Design", output, "Suggested fixes: label, property, value");
    ADD_PROPERTY_TYPE(ErrorElements, (), "Design", output, "Edges or faces the error or warning is about");
    ADD_PROPERTY_TYPE(Warning, (""), "Design", App::Prop_Hidden, "Problem that does not stop the feature");
    // Zustände dürfen aus anderen Komponenten kommen (Move/Combine über Komponenten). Nur sichtbare Abhängigkeiten:
    // die versteckten Bodies-Listen global zu machen, erzeugt Kreise (Body -> Feature -> Body)
    BaseFeatures.setScope(App::LinkScope::Global);
}

void Feature::suggest(const std::string& label, const char* property, double value)
{
    auto fixes = Fixes.getValues();
    std::ostringstream entry;
    entry << label << '\t' << property << '\t' << value;
    fixes.push_back(entry.str());
    Fixes.setValues(fixes);
}

App::DocumentObjectExecReturn* Feature::execute()
{
    Fixes.setValues(std::vector<std::string>());
    ErrorElements.setValues(std::vector<std::string>());
    if (Suppressed.getValue() || isRolledBack(this)) {  // unterdrückt oder hinter dem Rollback-Marker
        std::vector<Part::TopoShape> results;
        for (int i = 0; i < Bodies.getSize(); ++i) {
            results.push_back(baseShape(i));  // Vorzustand durchreichen; ohne Vorzustand (neuer Body) leer
        }
        setResults(results);
        return StdReturn;
    }
    return compute();
}

Part::TopoShape Feature::shapeFor(const App::DocumentObject* body) const
{
    const auto& bodies = Bodies.getValues();
    const auto idx = std::ranges::find(bodies, body) - bodies.begin();
    if (idx >= static_cast<long>(bodies.size())) {
        return {};
    }
    const Part::TopoShape all = Shape.getShape();
    if (bodies.size() == 1) {
        return all;  // ein Body: Ergebnis direkt, mit Element-Map (verfolgbare Namen)
    }
    int i = 0;
    for (TopoDS_Iterator it(all.getShape()); it.More(); it.Next(), ++i) {
        if (i == idx) {
            Part::TopoShape child(it.Value());
            child.mapSubElement(all);  // Namen aus dem Compound übernehmen
            return child;
        }
    }
    return {};
}

App::DocumentObjectExecReturn* Feature::applyTool(const Part::TopoShape& tool)
{
    const auto& bodies = Bodies.getValues();
    const auto& bases = BaseFeatures.getValues();
    std::vector<Part::TopoShape> results;

    if (op() == Op::NewBody) {
        results.push_back(solidOf(tool));
    }
    else {
        if (bodies.empty() || bases.size() != bodies.size()) {
            return new App::DocumentObjectExecReturn("Select a body to join, cut or intersect");
        }
        for (size_t i = 0; i < bodies.size(); ++i) {
            auto base = freecad_cast<Feature*>(bases[i]);
            if (!base) {
                return new App::DocumentObjectExecReturn("Body has no previous feature");
            }
            const Part::TopoShape baseShape = base->shapeFor(bodies[i]);
            Part::TopoShape res(0, getDocument()->getStringHasher());
            switch (op()) {
                case Op::Join:
                    res.makeElementFuse({baseShape, tool});
                    break;
                case Op::Cut:
                    res.makeElementCut({baseShape, tool});
                    break;
                default:
                    res.makeElementBoolean(Part::OpCodes::Common, {baseShape, tool});
                    break;
            }
            if (res.isNull() || res.countSubShapes(TopAbs_SOLID) == 0) {
                return new App::DocumentObjectExecReturn("Result would be empty");
            }
            results.push_back(solidOf(res.makeElementRefine(nullptr, Part::RefineFail::shapeUntouched)));
        }
    }

    setResults(results);
    return StdReturn;
}

void Feature::setResults(const std::vector<Part::TopoShape>& results)
{
    std::vector<Part::TopoShape> solids;
    for (const auto& r : results) {
        if (r.isNull()) {  // leerer Platzhalter, damit shapeFor-Indizes stimmen
            TopoDS_Compound empty;
            BRep_Builder().MakeCompound(empty);
            solids.emplace_back(empty);
        }
        else {
            solids.push_back(solidOf(r));
        }
    }
    if (solids.size() == 1) {  // ein Body: ohne Compound-Hülle speichern, damit die Element-Map erhalten bleibt
        Shape.setValue(solids.front());
        return;
    }
    Part::TopoShape compound(0, getDocument()->getStringHasher());
    compound.makeElementCompound(solids);
    Shape.setValue(compound);
}

Part::TopoShape Feature::baseShape(size_t i) const
{
    const auto& bodies = Bodies.getValues();
    const auto& bases = BaseFeatures.getValues();
    auto base = i < bases.size() ? freecad_cast<Feature*>(bases[i]) : nullptr;
    return base && i < bodies.size() ? base->shapeFor(bodies[i]) : Part::TopoShape();
}

// ---------------------------------------------------------------------------------------------

PROPERTY_SOURCE(Design::Extrude, Design::Feature)

Extrude::Extrude()
{
    ADD_PROPERTY_TYPE(ProfileKeys, (), "Extrude", App::PropertyType(App::Prop_Output | App::Prop_Hidden),
                      "Signatures of the selected profiles");
    ADD_PROPERTY_TYPE(Profile, (nullptr), "Extrude", App::Prop_None, "Profiles to extrude");
    ADD_PROPERTY_TYPE(Extent, (0L), "Extrude", App::Prop_None, "One side, symmetric or two sides");
    Extent.setEnums(ExtentEnums);
    ADD_PROPERTY_TYPE(Distance, (10.0), "Extrude", App::Prop_None, "Distance");
    ADD_PROPERTY_TYPE(Distance2, (10.0), "Extrude", App::Prop_None, "Distance of the second side");
    ADD_PROPERTY_TYPE(Reversed, (false), "Extrude", App::Prop_None, "Flip direction");
    // Gruppe "Parameters": der Dialog baut die Felder selbst, Sichtbarkeit über Hidden (updateVisibility)
    ADD_PROPERTY_TYPE(ToObject, (nullptr), "Parameters", App::Prop_None, "Face or plane to extrude to");
    ToObject.setScope(App::LinkScope::Global);
    ADD_PROPERTY_TYPE(TaperAngle, (0.0), "Parameters", App::Prop_None, "Taper angle; positive narrows the extrusion");
    ADD_PROPERTY_TYPE(Thin, (false), "Parameters", App::Prop_None, "Thin wall");
    ADD_PROPERTY_TYPE(Thickness, (2.0), "Parameters", App::Prop_None, "Wall thickness");
    ADD_PROPERTY_TYPE(ThinSide, (0L), "Parameters", App::Prop_None, "Side of the wall");
    ThinSide.setEnums(ThinEnums);
    updateVisibility();
}

void Extrude::updateVisibility()
{
    const bool toObject = Extent.getValue() == ExtentToObject;
    ToObject.setStatus(App::Property::Hidden, !toObject);
    TaperAngle.setStatus(App::Property::Hidden, toObject);
    Thickness.setStatus(App::Property::Hidden, !Thin.getValue());
    ThinSide.setStatus(App::Property::Hidden, !Thin.getValue());
}

void Extrude::onChanged(const App::Property* prop)
{
    if (prop == &Extent || prop == &Thin) {
        updateVisibility();
    }
    Feature::onChanged(prop);
}

void Extrude::onDocumentRestored()
{
    updateVisibility();
    Feature::onDocumentRestored();
}

bool Extrude::makeTool(Part::TopoShape& tool, std::string& error) const
{
    Part::Feature* sketch = nullptr;
    const char* reason = nullptr;
    auto faces = profileFaces(Profile, const_cast<App::PropertyStringList&>(ProfileKeys), sketch, reason);
    if (faces.empty()) {
        error = reason;
        return false;
    }
    const auto hasher = getDocument()->getStringHasher();

    // Dünne Wand: aus jeder Profilfläche ein Band entlang ihres Randes (Löcher bekommen auch eine Wand)
    if (Thin.getValue()) {
        const double t = Thickness.getValue();
        if (t < Precision::Confusion()) {
            error = "Wall thickness must be greater than zero";
            return false;
        }
        const double outer = ThinSide.getValue() == 0 ? 0 : ThinSide.getValue() == 1 ? t : t / 2;
        std::vector<Part::TopoShape> bands;
        try {
            for (const auto& face : faces) {
                // Fläche um d vergrößern: Außenrand nach außen, Löcher nach innen (Offset2D allein füllt die Löcher)
                const auto offset = [&](double d) {
                    return std::abs(d) < Precision::Confusion() ? face
                                                                : Part::TopoShape(0, hasher).makeElementOffsetFace(face, d, -d);
                };
                const Part::TopoShape big = offset(outer), small = offset(outer - t);
                bands.push_back(small.isNull() || small.countSubShapes(TopAbs_FACE) == 0
                                    ? big
                                    : Part::TopoShape(0, hasher).makeElementCut({big, small}));
            }
        }
        catch (const Standard_Failure&) {
            error = "The wall is too thick for this profile";
            return false;
        }
        catch (const Base::Exception&) {
            error = "The wall is too thick for this profile";
            return false;
        }
        faces.clear();
        for (const auto& band : bands) {
            for (const auto& f : band.getSubTopoShapes(TopAbs_FACE)) {
                faces.push_back(f);
            }
        }
        if (faces.empty()) {
            error = "The wall is too thick for this profile";
            return false;
        }
    }

    Base::Vector3d n = sketch->Placement.getValue().getRotation().multVec(Base::Vector3d(0, 0, 1));
    if (Reversed.getValue()) {
        n = -n;
    }
    gp_Dir dir(n.x, n.y, n.z);

    if (Extent.getValue() == ExtentToObject) {
        // Ziel in die Koordinaten der eigenen Komponente holen (Bezüge liefern globale Formen)
        Base::BoundBox3d around;
        for (const auto& f : faces) {
            around.Add(f.getBoundBox());
        }
        TopoDS_Shape target = toolShape(ToObject, around);
        if (target.IsNull()) {
            error = "Click the face or plane to extrude to";
            return false;
        }
        Part::TopoShape upTo(target);
        upTo.transformShape(componentOf(this)->globalPlacement().inverse().toMatrix(), false, true);
        if (upTo.shapeType(true) != TopAbs_FACE) {
            error = "Extrude to a face or a plane, not a whole body";
            return false;
        }
        // Liegt das Ziel hinter dem Profil, in die andere Richtung ziehen
        const Base::Vector3d toTarget = upTo.getBoundBox().GetCenter() - around.GetCenter();
        if (toTarget.Dot(n) < 0) {
            dir.Reverse();
        }
        std::vector<Part::TopoShape> prisms;
        try {
            for (const auto& face : faces) {
                prisms.push_back(Part::TopoShape(0, hasher).makeElementPrismUntil(
                    Part::TopoShape(), face, Part::TopoShape(), upTo, dir, Part::TopoShape::PrismMode::None, true));
            }
        }
        catch (...) {
            error = "The profile does not reach this face. Choose a face in front of the profile";
            return false;
        }
        std::erase_if(prisms, [](const Part::TopoShape& p) { return p.isNull() || p.countSubShapes(TopAbs_SOLID) == 0; });
        if (prisms.size() != faces.size()) {
            error = "The profile does not reach this face. Choose a face in front of the profile";
            return false;
        }
        tool = fuseAll(prisms, hasher);
        return true;
    }

    double start = 0, end = Distance.getValue();
    if (Extent.getValue() == ExtentSymmetric) {
        start = -end / 2;
        end /= 2;
    }
    else if (Extent.getValue() == ExtentTwoSides) {
        start = -Distance2.getValue();
    }
    else if (Extent.getValue() == ExtentAll) {
        // Durch alles: bis hinter den äußersten Körper des Designs
        Base::BoundBox3d box;
        for (const auto& f : faces) {
            box.Add(f.getBoundBox());
        }
        for (auto obj : getDocument()->getObjectsOfType(Body::getClassTypeId())) {
            const Part::TopoShape s = static_cast<Body*>(obj)->Shape.getShape();
            if (!s.isNull()) {
                box.Add(s.getBoundBox());
            }
        }
        end = box.CalcDiagonalLength() * 2 + 10;
    }
    if (end - start < Precision::Confusion()) {
        error = "Distance must be greater than zero";
        return false;
    }

    const double taper = TaperAngle.getValue();
    std::vector<Part::TopoShape> prisms;
    if (std::abs(taper) > Precision::Angular()) {
        if (std::abs(taper) >= 89.0) {
            error = "Taper angle must be between -89° and 89°";
            return false;
        }
        Part::ExtrusionParameters params;
        params.dir = dir;
        params.lengthFwd = end;
        params.lengthRev = -start;
        params.solid = true;
        params.taperAngleFwd = params.taperAngleRev = -taper * M_PI / 180.0;  // positiv = schmaler
        try {
            for (const auto& face : faces) {
                std::vector<Part::TopoShape> drafts;
                Part::ExtrusionHelper::makeElementDraft(params, face, drafts, hasher);
                prisms.insert(prisms.end(), drafts.begin(), drafts.end());
            }
        }
        catch (...) {
            error = "Taper angle too large for this distance";
            return false;
        }
        std::erase_if(prisms, [](const Part::TopoShape& p) { return p.isNull() || !p.isValid(); });
        if (prisms.empty()) {
            error = "Taper angle too large for this distance";
            return false;
        }
    }
    else {
        for (const auto& face : faces) {
            Part::TopoShape base = face;
            if (start != 0) {
                Base::Matrix4D mov;
                mov.move(n * start);
                base = Part::TopoShape(0, hasher).makeElementTransform(face, mov);
            }
            const Base::Vector3d v = n * (end - start);
            prisms.push_back(Part::TopoShape(0, hasher).makeElementPrism(base, gp_Vec(v.x, v.y, v.z)));
        }
    }
    tool = fuseAll(prisms, hasher);
    return true;
}

App::DocumentObjectExecReturn* Extrude::compute()
{
    Part::TopoShape tool;
    std::string error;
    if (!makeTool(tool, error)) {
        return new App::DocumentObjectExecReturn(error);
    }
    return applyTool(tool);
}

// ---------------------------------------------------------------------------------------------

PROPERTY_SOURCE(Design::Revolve, Design::Feature)

Revolve::Revolve()
{
    ADD_PROPERTY_TYPE(ProfileKeys, (), "Revolve", App::PropertyType(App::Prop_Output | App::Prop_Hidden),
                      "Signatures of the selected profiles");
    ADD_PROPERTY_TYPE(Profile, (nullptr), "Revolve", App::Prop_None, "Profiles to revolve");
    ADD_PROPERTY_TYPE(Axis, (0L), "Revolve", App::Prop_None, "Axis of revolution");
    Axis.setEnums(AxisEnums);
    ADD_PROPERTY_TYPE(Angle, (360.0), "Revolve", App::Prop_None, "Angle");
    ADD_PROPERTY_TYPE(Reversed, (false), "Revolve", App::Prop_None, "Flip direction");
}

bool Revolve::makeTool(Part::TopoShape& tool, std::string& error) const
{
    return revolveAround(Axis.getValue(), tool, error);
}

bool Revolve::revolveAround(long axisIndex, Part::TopoShape& tool, std::string& error) const
{
    Part::Feature* sketch = nullptr;
    const char* reason = nullptr;
    const auto faces = profileFaces(Profile, const_cast<App::PropertyStringList&>(ProfileKeys), sketch, reason);
    if (faces.empty()) {
        error = reason;
        return false;
    }
    const double angle = Angle.getValue();
    if (angle < Precision::Angular() || angle > 360.0 + Precision::Angular()) {
        error = "Angle must be between 0 and 360 degrees";
        return false;
    }

    const Base::Placement pla = sketch->Placement.getValue();
    Base::Vector3d origin, dir;
    switch (axisIndex) {
        case 0:
            origin = pla.getPosition();
            dir = pla.getRotation().multVec(Base::Vector3d(1, 0, 0));
            break;
        case 1:
            origin = pla.getPosition();
            dir = pla.getRotation().multVec(Base::Vector3d(0, 1, 0));
            break;
        default:
            dir[axisIndex - 2] = 1;
            break;
    }
    if (Reversed.getValue()) {
        dir = -dir;
    }
    const gp_Ax1 axis(gp_Pnt(origin.x, origin.y, origin.z), gp_Dir(dir.x, dir.y, dir.z));

    std::vector<Part::TopoShape> solids;
    try {
        for (const auto& face : faces) {
            solids.push_back(Part::TopoShape(0, getDocument()->getStringHasher())
                                 .makeElementRevolve(face, axis, angle * M_PI / 180.0));
        }
    }
    catch (...) {  // OpenCascade meldet nur "BRep_API: command not done"
        error = "The axis passes through the profile. Choose an axis beside it.";
        return false;
    }
    tool = fuseAll(solids, getDocument()->getStringHasher());
    return true;
}

App::DocumentObjectExecReturn* Revolve::compute()
{
    Part::TopoShape tool;
    std::string error;
    if (!makeTool(tool, error)) {
        // Eine Achse vorschlagen, um die es geht
        for (long k = 0; k < static_cast<long>(Axis.getEnumVector().size()); ++k) {
            Part::TopoShape probe;
            std::string ignored;
            if (k != Axis.getValue() && revolveAround(k, probe, ignored)) {
                suggest(std::string("Use axis ") + Axis.getEnumVector()[k], "Axis", double(k));
                break;
            }
        }
        return new App::DocumentObjectExecReturn(error);
    }
    return applyTool(tool);
}

// ---------------------------------------------------------------------------------------------

PROPERTY_SOURCE(Design::DressUp, Design::Feature)

DressUp::DressUp()
{
    ADD_PROPERTY_TYPE(Edges, (), "DressUp", App::Prop_None, "Edges (or faces) of the body before this feature");
    ADD_PROPERTY_TYPE(Size, (1.0), "DressUp", App::Prop_None, "Radius or distance");
    ADD_PROPERTY_TYPE(ElementMaps, (), "DressUp", App::PropertyType(App::Prop_Output | App::Prop_Hidden),
                      "Traceable names of the selected elements");
    ADD_PROPERTY_TYPE(ElementHints, (), "DressUp", App::PropertyType(App::Prop_Output | App::Prop_Hidden),
                      "Position and size of the selected elements");
    Operation.setStatus(App::Property::Hidden, true);  // verändert immer den eigenen Body
}

double DressUp::largestWorking(const std::function<bool(double)>& try_) const
{
    double lo = 0, hi = Size.getValue();
    for (int i = 0; i < 12; ++i) {  // ponytail: 12 Versuche je Fehler, reicht auf 0,03 % der Größe genau
        const double mid = (lo + hi) / 2;
        (try_(mid) ? lo : hi) = mid;
    }
    return std::floor(lo * 100) / 100;  // abgerundet auf 0,01 mm: sicher noch gültig
}

namespace
{
/// "x y z Größe" eines Elements (Kante: Länge, Fläche: Inhalt)
std::string elementHint(const TopoDS_Shape& s)
{
    GProp_GProps p;
    if (s.ShapeType() == TopAbs_FACE) {
        BRepGProp::SurfaceProperties(s, p);
    }
    else {
        BRepGProp::LinearProperties(s, p);
    }
    std::ostringstream out;
    out << p.CentreOfMass().X() << ' ' << p.CentreOfMass().Y() << ' ' << p.CentreOfMass().Z() << ' ' << p.Mass();
    return out.str();
}

/// Element gleicher Art, das am besten zu hint passt (Lage und Größe); leer, wenn keins da ist
std::string closestElement(const Part::TopoShape& shape, const std::string& name, const std::string& hint)
{
    std::istringstream in(hint);
    double x = 0, y = 0, z = 0, size = 0;
    if (!(in >> x >> y >> z >> size)) {
        return {};
    }
    const bool face = name.rfind("Face", 0) == 0;
    const TopAbs_ShapeEnum type = face ? TopAbs_FACE : TopAbs_EDGE;
    std::string best;
    double bestScore = 1e300;
    const int count = shape.countSubShapes(type);
    for (int i = 1; i <= count; ++i) {
        const std::string candidate = (face ? "Face" : "Edge") + std::to_string(i);
        std::istringstream h(elementHint(shape.getSubShape(candidate.c_str())));
        double cx = 0, cy = 0, cz = 0, cs = 0;
        h >> cx >> cy >> cz >> cs;
        const double score = std::hypot(cx - x, cy - y, cz - z) + std::abs(cs - size) / std::max(1.0, size) * 10;
        if (score < bestScore) {
            bestScore = score;
            best = candidate;
        }
    }
    return best;
}
}  // namespace

std::vector<Part::TopoShape> DressUp::elements(const Part::TopoShape& shape, TopAbs_ShapeEnum type)
{
    // Gewählte Elemente über ihre verfolgbaren Namen wiederfinden (topologische Benennung):
    // 1. derselbe Name existiert noch, 2. ein Element, das laut Entstehungsgeschichte daraus hervorging
    //    (z. B. wenn davor ein Feature eingefügt wurde), 3. sonst die ursprüngliche Nummer.
    std::vector<std::string> names = Edges.getValues();
    std::vector<std::string> maps = ElementMaps.getValues();
    std::vector<std::string> hints = ElementHints.getValues();
    maps.resize(names.size());
    hints.resize(names.size());
    std::vector<std::string> uncertain;
    App::DocumentObject* base = BaseFeatures.getSize() ? BaseFeatures.getValues().front() : nullptr;
    for (size_t i = 0; i < names.size(); ++i) {
        if (!maps[i].empty()) {
            bool found = false;
            const Data::IndexedName idx = shape.getIndexedName(Data::MappedName(maps[i]));
            if (idx) {
                names[i] = idx.toString();
                found = true;
            }
            else if (base) {
                const auto related = Part::Feature::getRelatedElements(
                    base, (std::string(Data::ELEMENT_MAP_PREFIX) + maps[i]).c_str()
                );
                if (!related.isEmpty()) {
                    names[i] = related.front().index.toString();
                    found = true;
                }
            }
            // Name verloren: nicht still die alte Nummer nehmen, sondern das Element, das nach Lage und Größe am
            // besten passt, und warnen (Idee 6, "War es diese Kante?")
            if (!found) {
                const std::string guess = closestElement(shape, names[i], hints[i]);
                if (!guess.empty()) {
                    names[i] = guess;
                }
                uncertain.push_back(names[i]);
            }
        }
        const Data::MappedName mapped = shape.getMappedName(Data::IndexedName(names[i].c_str()));
        if (mapped) {
            maps[i] = mapped.toString();
        }
        const TopoDS_Shape sub = shape.getSubShape(names[i].c_str(), true);
        if (!sub.IsNull()) {
            hints[i] = elementHint(sub);
        }
    }
    ElementMaps.setValues(maps);  // Ausgabe-Property: markiert das Feature nicht als geändert
    ElementHints.setValues(hints);
    if (!uncertain.empty()) {
        std::string list;
        for (const auto& n : uncertain) {
            list += (list.empty() ? "" : ", ") + n;
        }
        Warning.setValue("The model changed under this step; check that it still uses the right edges or faces: " + list);
        ErrorElements.setValues(uncertain);
    }

    std::vector<Part::TopoShape> result;
    TopTools_IndexedMapOfShape seen;
    for (const auto& name : names) {
        const Part::TopoShape sub = shape.getSubTopoShape(name.c_str(), true);
        for (const auto& el : sub.isNull() ? std::vector<Part::TopoShape>() : sub.getSubTopoShapes(type)) {
            if (seen.Add(el.getShape()) == seen.Extent()) {
                result.push_back(el);
            }
        }
    }
    return result;
}

App::DocumentObjectExecReturn* DressUp::run(bool fillet)
{
    if (Bodies.getSize() != 1 || BaseFeatures.getSize() != 1) {
        return new App::DocumentObjectExecReturn("Select edges of one body");
    }
    const Part::TopoShape shape = baseShape(0);
    // Flächen stehen für alle ihre Kanten; doppelte Kanten zählen einmal
    const auto edges = elements(shape, TopAbs_EDGE);
    if (edges.empty()) {
        return new App::DocumentObjectExecReturn("Select one or more edges");
    }
    const double size = Size.getValue();
    if (size < Precision::Confusion()) {
        return new App::DocumentObjectExecReturn("Size must be greater than zero");
    }
    const char* failed = fillet ? "Fillet failed: radius too large?" : "Chamfer failed: distance too large?";
    Part::TopoShape res(0, getDocument()->getStringHasher());
    try {
        if (fillet) {
            auto f = static_cast<Fillet*>(this);
            const double end = f->Variable.getValue() ? f->RadiusEnd.getValue() : size;
            if (end < Precision::Confusion()) {
                return new App::DocumentObjectExecReturn("Radius must be greater than zero");
            }
            res.makeElementFillet(shape, edges, size, end);
        }
        else {
            auto c = static_cast<Chamfer*>(this);
            const long type = c->Type.getValue();
            const double second = type == 1 ? c->Distance2.getValue() : type == 2 ? c->ChamferAngle.getValue() : size;
            if (type == 1 && second < Precision::Confusion()) {
                return new App::DocumentObjectExecReturn("Distance must be greater than zero");
            }
            if (type == 2 && (second <= 0 || second >= 90)) {
                return new App::DocumentObjectExecReturn("The chamfer angle must be between 0° and 90°");
            }
            res.makeElementChamfer(shape, edges, static_cast<Part::ChamferType>(type), size, second, nullptr,
                                   c->FlipSide.getValue() ? Part::Flip::flip : Part::Flip::none);
        }
    }
    catch (const Standard_Failure&) {
        res = Part::TopoShape();
    }
    if (res.isNull() || !res.isValid()) {
        // Vorschlag: der größte Wert, der für diese Kanten noch geht (konstanter Radius bzw. gleicher Abstand)
        const double best = largestWorking([&](double s) {
            try {
                Part::TopoShape probe(0, getDocument()->getStringHasher());
                if (fillet) {
                    probe.makeElementFillet(shape, edges, s, s);
                }
                else {
                    probe.makeElementChamfer(shape, edges, Part::ChamferType::equalDistance, s, s);
                }
                return !probe.isNull() && probe.isValid();
            }
            catch (const Standard_Failure&) {
                return false;
            }
        });
        if (best > 0) {
            std::ostringstream label;
            label << (fillet ? "Use radius " : "Use distance ") << best << " mm";
            suggest(label.str(), "Size", best);
        }
        ErrorElements.setValues(Edges.getValues());
        return new App::DocumentObjectExecReturn(failed);
    }
    setResults({res});
    return StdReturn;
}

PROPERTY_SOURCE(Design::Fillet, Design::DressUp)
PROPERTY_SOURCE(Design::Chamfer, Design::DressUp)

Fillet::Fillet()
{
    ADD_PROPERTY_TYPE(Variable, (false), "Parameters", App::Prop_None, "Variable radius");
    ADD_PROPERTY_TYPE(RadiusEnd, (2.0), "Parameters", App::Prop_None, "Radius at the end of the edge");
    RadiusEnd.setStatus(App::Property::Hidden, true);
}

void Fillet::onChanged(const App::Property* prop)
{
    if (prop == &Variable) {
        RadiusEnd.setStatus(App::Property::Hidden, !Variable.getValue());
    }
    DressUp::onChanged(prop);
}

Chamfer::Chamfer()
{
    ADD_PROPERTY_TYPE(Type, (0L), "Parameters", App::Prop_None, "How the chamfer is measured");
    Type.setEnums(ChamferEnums);
    ADD_PROPERTY_TYPE(Distance2, (2.0), "Parameters", App::Prop_None, "Distance on the other face");
    ADD_PROPERTY_TYPE(ChamferAngle, (45.0), "Parameters", App::Prop_None, "Angle of the chamfer");
    ADD_PROPERTY_TYPE(FlipSide, (false), "Parameters", App::Prop_None, "Swap the two faces");
    for (App::Property* p : std::initializer_list<App::Property*> {&Distance2, &ChamferAngle, &FlipSide}) {
        p->setStatus(App::Property::Hidden, true);
    }
}

void Chamfer::onChanged(const App::Property* prop)
{
    if (prop == &Type) {
        const long type = Type.getValue();
        Distance2.setStatus(App::Property::Hidden, type != 1);
        ChamferAngle.setStatus(App::Property::Hidden, type != 2);
        FlipSide.setStatus(App::Property::Hidden, type == 0);
    }
    DressUp::onChanged(prop);
}

// ---------------------------------------------------------------------------------------------

PROPERTY_SOURCE(Design::Shell, Design::DressUp)

Shell::Shell()
{
    ADD_PROPERTY_TYPE(Outside, (false), "Shell", App::Prop_None, "Add the wall thickness outside");
}

App::DocumentObjectExecReturn* Shell::compute()
{
    if (Bodies.getSize() != 1 || BaseFeatures.getSize() != 1) {
        return new App::DocumentObjectExecReturn("Select faces of one body");
    }
    const Part::TopoShape shape = baseShape(0);
    const auto faces = elements(shape, TopAbs_FACE);
    const double t = Size.getValue();
    if (t < Precision::Confusion()) {
        return new App::DocumentObjectExecReturn("Thickness must be greater than zero");
    }
    const auto hollow = [&](double thickness) {  // ohne geöffnete Fläche entsteht ein geschlossener Hohlkörper
        Part::TopoShape r(0, getDocument()->getStringHasher());
        try {
            r.makeElementThickSolid(shape, faces, Outside.getValue() ? thickness : -thickness, 1e-6, true, false, 0,
                                    Part::JoinType::intersection);
        }
        catch (const Standard_Failure&) {
            return Part::TopoShape();
        }
        if (r.isNull() || !r.isValid() || r.countSubShapes(TopAbs_SOLID) == 0) {
            return Part::TopoShape();
        }
        // Plausibel? Eine Wand nach innen nimmt Material weg, eine nach außen kommt dazu (OCCT liefert bei zu dicken
        // Wänden sonst gültige, aber unsinnige Körper)
        GProp_GProps before, after;
        BRepGProp::VolumeProperties(shape.getShape(), before);
        BRepGProp::VolumeProperties(r.getShape(), after);
        const bool sensible = Outside.getValue() ? after.Mass() > before.Mass() : after.Mass() > 0 && after.Mass() < before.Mass();
        return sensible ? r : Part::TopoShape();
    };
    const Part::TopoShape res = hollow(t);
    if (res.isNull()) {
        if (const double best = largestWorking([&](double s) { return !hollow(s).isNull(); }); best > 0) {
            std::ostringstream label;
            label << "Use thickness " << best << " mm";
            suggest(label.str(), "Size", best);
        }
        return new App::DocumentObjectExecReturn("Shell failed: thickness too large?");
    }
    setResults({res});
    return StdReturn;
}

// ---------------------------------------------------------------------------------------------

PROPERTY_SOURCE(Design::Combine, Design::Feature)

Combine::Combine()
{
    ADD_PROPERTY_TYPE(ToolBodies, (nullptr), "Combine", App::Prop_None, "Tool bodies");
    ADD_PROPERTY_TYPE(ToolFeatures, (nullptr), "Combine", App::Prop_Hidden, "State of the tool bodies");
    ToolFeatures.setScope(App::LinkScope::Global);
    ADD_PROPERTY_TYPE(KeepTools, (false), "Combine", App::Prop_None, "Keep the tool bodies visible");
    Operation.setValue(1L);  // Join
}

App::DocumentObjectExecReturn* Combine::compute()
{
    const auto& tools = ToolBodies.getValues();
    const auto& states = ToolFeatures.getValues();
    if (tools.empty() || tools.size() != states.size()) {
        return new App::DocumentObjectExecReturn("Select a target body and one or more tool bodies");
    }
    if (op() == Op::NewBody) {
        return new App::DocumentObjectExecReturn("Choose join, cut or intersect");
    }
    std::vector<Part::TopoShape> shapes;
    for (size_t i = 0; i < tools.size(); ++i) {
        auto state = freecad_cast<Feature*>(states[i]);
        if (!state) {
            return new App::DocumentObjectExecReturn("Tool body has no feature");
        }
        // Werkzeug aus einer anderen Komponente in die Koordinaten der Ziel-Komponente holen
        const Base::Placement from = Design::componentOf(tools[i])->globalPlacement();
        const Base::Placement to = Bodies.getSize() ? Design::componentOf(Bodies[0])->globalPlacement() : from;
        const Base::Matrix4D m = (to.inverse() * from).toMatrix();
        shapes.push_back(m.isUnity() ? state->shapeFor(tools[i])
                                     : Part::TopoShape(0, getDocument()->getStringHasher())
                                           .makeElementTransform(state->shapeFor(tools[i]), m, nullptr,
                                                                 Part::CheckScale::noScaleCheck, Part::CopyType::copy));
    }
    return applyTool(fuseAll(shapes, getDocument()->getStringHasher()));
}

// ---------------------------------------------------------------------------------------------

PROPERTY_SOURCE(Design::Move, Design::Feature)

Move::Move()
{
    ADD_PROPERTY_TYPE(Translation, (Base::Vector3d()), "Move", App::Prop_None, "Translation");
    ADD_PROPERTY_TYPE(RotationAxis, (2L), "Move", App::Prop_None, "Rotation axis through the body center");
    RotationAxis.setEnums(XYZEnums);
    ADD_PROPERTY_TYPE(Angle, (0.0), "Move", App::Prop_None, "Rotation angle");
    ADD_PROPERTY_TYPE(Alignment, (Base::Placement()), "Move", App::Prop_Hidden, "Alignment (Align)");
    ADD_PROPERTY_TYPE(AxisReference, (nullptr), "Parameters", App::Prop_None, "Axis, edge or round face to rotate around");
    AxisReference.setScope(App::LinkScope::Global);
    Operation.setStatus(App::Property::Hidden, true);
}

App::DocumentObjectExecReturn* Move::compute()
{
    if (Bodies.getSize() == 0 || Bodies.getSize() != BaseFeatures.getSize()) {
        return new App::DocumentObjectExecReturn("Select one or more bodies");
    }
    std::vector<Part::TopoShape> results;
    for (int i = 0; i < Bodies.getSize(); ++i) {
        const Part::TopoShape base = baseShape(i);
        // global rechnen, dann in die Komponente des Bodies umrechnen
        const Base::Matrix4D toGlobal = Design::componentOf(Bodies[i])->globalPlacement().toMatrix();
        Base::BoundBox3d bb = base.getBoundBox().Transformed(toGlobal);
        bb = bb.Transformed(Alignment.getValue().toMatrix());  // gedreht wird um die Mitte nach dem Ausrichten
        Base::Vector3d axis, center = bb.GetCenter();
        axis[RotationAxis.getValue()] = 1;
        if (AxisReference.getValue()) {  // frei gewählte Achse (bei einer Ebene: ihre Normale durch ihren Punkt)
            gp_Ax1 ref;
            bool planar = false;
            if (!referenceAxis(AxisReference, ref, planar)) {
                return new App::DocumentObjectExecReturn("Rotate around an axis, a straight or round edge or a round face");
            }
            axis = Base::Vector3d(ref.Direction().X(), ref.Direction().Y(), ref.Direction().Z());
            center = Base::Vector3d(ref.Location().X(), ref.Location().Y(), ref.Location().Z());
        }
        Base::Placement rot(Base::Vector3d(), Base::Rotation(axis, Angle.getValue() * M_PI / 180.0), center);
        Base::Placement move(Translation.getValue(), Base::Rotation());
        Base::Matrix4D mat = inComponent(Bodies[i], (move * rot * Alignment.getValue()).toMatrix());
        // Geometrie wirklich umrechnen (copy): eine bloße Lage würde Part::Feature beim Speichern im Body überschreiben
        results.push_back(Part::TopoShape(0, getDocument()->getStringHasher())
                              .makeElementTransform(base, mat, nullptr, Part::CheckScale::noScaleCheck,
                                                    Part::CopyType::copy));
    }
    setResults(results);
    return StdReturn;
}

// ---------------------------------------------------------------------------------------------

PROPERTY_SOURCE(Design::Mirror, Design::Feature)

Mirror::Mirror()
{
    ADD_PROPERTY_TYPE(SourceBodies, (nullptr), "Mirror", App::Prop_None, "Bodies to mirror");
    ADD_PROPERTY_TYPE(SourceFeatures, (nullptr), "Mirror", App::Prop_Hidden, "State of the source bodies");
    SourceFeatures.setScope(App::LinkScope::Global);
    ADD_PROPERTY_TYPE(Plane, (2L), "Mirror", App::Prop_None, "Mirror plane");
    Plane.setEnums(PlaneEnums);
    ADD_PROPERTY_TYPE(PlaneReference, (nullptr), "Parameters", App::Prop_None, "Plane or flat face to mirror at");
    PlaneReference.setScope(App::LinkScope::Global);
    Operation.setStatus(App::Property::Hidden, true);
}

void Mirror::onChanged(const App::Property* prop)
{
    if (prop == &PlaneReference) {  // ein Bezug ersetzt die Ursprungsebene
        Plane.setStatus(App::Property::ReadOnly, PlaneReference.getValue() != nullptr);
    }
    Feature::onChanged(prop);
}

App::DocumentObjectExecReturn* Mirror::compute()
{
    const auto& sources = SourceBodies.getValues();
    const auto& states = SourceFeatures.getValues();
    if (sources.empty() || sources.size() != states.size() || Bodies.getSize() != int(sources.size())) {
        return new App::DocumentObjectExecReturn("Select one or more bodies");
    }
    static const gp_Dir normals[] = {gp::DZ(), gp::DY(), gp::DX()};
    gp_Ax2 plane(gp::Origin(), normals[Plane.getValue()]);
    if (PlaneReference.getValue()) {
        gp_Ax1 ref;
        bool planar = false;
        if (!referenceAxis(PlaneReference, ref, planar) || !planar) {
            return new App::DocumentObjectExecReturn("Mirror at a plane or a flat face");
        }
        plane = gp_Ax2(ref.Location(), ref.Direction());
    }
    std::vector<Part::TopoShape> results;
    for (size_t i = 0; i < sources.size(); ++i) {
        auto state = freecad_cast<Feature*>(states[i]);
        if (!state) {
            return new App::DocumentObjectExecReturn("Body has no feature");
        }
        // Ursprungsebene ist global: Spiegelung in die Komponente des Quell-Bodies umrechnen
        const Base::Placement p = Design::componentOf(sources[i])->globalPlacement();
        const Part::TopoShape global = Part::TopoShape(0, getDocument()->getStringHasher())
                                           .makeElementTransform(state->shapeFor(sources[i]), p.toMatrix(), nullptr,
                                                                 Part::CheckScale::noScaleCheck, Part::CopyType::copy);
        const Part::TopoShape mirrored = Part::TopoShape(0, getDocument()->getStringHasher()).makeElementMirror(global, plane);
        results.push_back(Part::TopoShape(0, getDocument()->getStringHasher())
                              .makeElementTransform(mirrored, p.inverse().toMatrix(), nullptr,
                                                    Part::CheckScale::noScaleCheck, Part::CopyType::copy));
    }
    setResults(results);
    return StdReturn;
}

// ---------------------------------------------------------------------------------------------

PROPERTY_SOURCE(Design::Pattern, Design::Feature)

Pattern::Pattern()
{
    ADD_PROPERTY_TYPE(Source, (nullptr), "Pattern", App::Prop_None, "Feature to repeat");
    ADD_PROPERTY_TYPE(SourceBodies, (nullptr), "Pattern", App::Prop_None, "Bodies to repeat");
    ADD_PROPERTY_TYPE(SourceFeatures, (nullptr), "Pattern", App::Prop_Hidden, "State of the source bodies");
    SourceFeatures.setScope(App::LinkScope::Global);
    ADD_PROPERTY_TYPE(Type, (0L), "Pattern", App::Prop_None, "Rectangular or circular");
    Type.setEnums(PatternEnums);
    ADD_PROPERTY_TYPE(Direction1, (0L), "Pattern", App::Prop_None, "First direction");
    Direction1.setEnums(XYZEnums);
    ADD_PROPERTY_TYPE(Count1, (3L), "Pattern", App::Prop_None, "Count in the first direction");
    Count1.setConstraints(&CountRange);
    ADD_PROPERTY_TYPE(Spacing1, (10.0), "Pattern", App::Prop_None, "Spacing in the first direction");
    ADD_PROPERTY_TYPE(Direction2, (1L), "Pattern", App::Prop_None, "Second direction");
    Direction2.setEnums(XYZEnums);
    ADD_PROPERTY_TYPE(Count2, (1L), "Pattern", App::Prop_None, "Count in the second direction");
    Count2.setConstraints(&CountRange);
    ADD_PROPERTY_TYPE(Spacing2, (10.0), "Pattern", App::Prop_None, "Spacing in the second direction");
    ADD_PROPERTY_TYPE(Axis, (2L), "Pattern", App::Prop_None, "Axis of a circular pattern (through the origin)");
    Axis.setEnums(XYZEnums);
    ADD_PROPERTY_TYPE(Angle, (360.0), "Pattern", App::Prop_None, "Total angle of a circular pattern");
    ADD_PROPERTY_TYPE(Direction1Reference, (nullptr), "Parameters", App::Prop_None, "Edge, axis or plane for the first direction");
    ADD_PROPERTY_TYPE(Direction2Reference, (nullptr), "Parameters", App::Prop_None, "Edge, axis or plane for the second direction");
    ADD_PROPERTY_TYPE(AxisReference, (nullptr), "Parameters", App::Prop_None, "Axis, edge or round face of a circular pattern");
    ADD_PROPERTY_TYPE(Path, (nullptr), "Parameters", App::Prop_None, "Edges to repeat along");
    ADD_PROPERTY_TYPE(FollowPath, (false), "Parameters", App::Prop_None, "Rotate copies along the path");
    for (auto link : {&Direction1Reference, &Direction2Reference, &AxisReference, &Path}) {
        link->setScope(App::LinkScope::Global);
    }
    Operation.setValue(1L);
    updateVisibility();
}

void Pattern::onChanged(const App::Property* prop)
{
    if (prop == &Type || prop == &Direction1Reference || prop == &Direction2Reference || prop == &AxisReference) {
        updateVisibility();
    }
    Feature::onChanged(prop);
}

void Pattern::onDocumentRestored()
{
    updateVisibility();
    Feature::onDocumentRestored();
}

/// Bezüge passend zum Typ zeigen; ein gesetzter Bezug sperrt die X/Y/Z-Auswahl, die er ersetzt
void Pattern::updateVisibility()
{
    const long type = Type.getValue();
    Direction1Reference.setStatus(App::Property::Hidden, type != 0);
    Direction2Reference.setStatus(App::Property::Hidden, type != 0);
    AxisReference.setStatus(App::Property::Hidden, type != 1);
    Path.setStatus(App::Property::Hidden, type != 2);
    FollowPath.setStatus(App::Property::Hidden, type != 2);
    Direction1.setStatus(App::Property::ReadOnly, Direction1Reference.getValue() != nullptr);
    Direction2.setStatus(App::Property::ReadOnly, Direction2Reference.getValue() != nullptr);
    Axis.setStatus(App::Property::ReadOnly, AxisReference.getValue() != nullptr);
}

std::vector<Base::Matrix4D> Pattern::transforms(std::string& error) const
{
    std::vector<Base::Matrix4D> transforms;
    // Richtung aus einem Bezug (Kante/Achse: entlang, Ebene/Fläche: senkrecht) oder X/Y/Z
    const auto direction = [&error](const App::PropertyLinkSub& ref, long xyz, Base::Vector3d& d) {
        d = Base::Vector3d();
        if (!ref.getValue()) {
            d[xyz] = 1;
            return true;
        }
        gp_Ax1 axis;
        bool planar = false;
        if (!referenceAxis(ref, axis, planar)) {
            error = "Choose an edge, an axis or a flat face as direction";
            return false;
        }
        d = Base::Vector3d(axis.Direction().X(), axis.Direction().Y(), axis.Direction().Z());
        return true;
    };
    if (Type.getValue() == 0) {
        Base::Vector3d d1, d2;
        if (!direction(Direction1Reference, Direction1.getValue(), d1)
            || !direction(Direction2Reference, Direction2.getValue(), d2)) {
            return {};
        }
        d1 *= Spacing1.getValue();
        d2 *= Spacing2.getValue();
        for (long i = 0; i < Count1.getValue(); ++i) {
            for (long j = 0; j < Count2.getValue(); ++j) {
                if (i || j) {
                    Base::Matrix4D m;
                    m.move(d1 * double(i) + d2 * double(j));
                    transforms.push_back(m);
                }
            }
        }
    }
    else if (Type.getValue() == 1) {
        const long n = Count1.getValue();
        const double total = Angle.getValue();
        const bool full = std::abs(total - 360.0) < Precision::Angular();
        const double step = n > 1 ? (full ? total / n : total / (n - 1)) : 0;
        Base::Vector3d axis, center;
        axis[Axis.getValue()] = 1;
        if (AxisReference.getValue()) {
            gp_Ax1 ref;
            bool planar = false;
            if (!referenceAxis(AxisReference, ref, planar)) {
                error = "Choose an axis, a straight or round edge or a round face";
                return {};
            }
            axis = Base::Vector3d(ref.Direction().X(), ref.Direction().Y(), ref.Direction().Z());
            center = Base::Vector3d(ref.Location().X(), ref.Location().Y(), ref.Location().Z());
        }
        for (long k = 1; k < n; ++k) {
            transforms.push_back(
                Base::Placement(Base::Vector3d(), Base::Rotation(axis, k * step * M_PI / 180.0), center).toMatrix());
        }
    }
    else {
        // Entlang eines Pfads: Kopien im Abstand Spacing1 (Bogenlänge) ab dem Pfadanfang
        App::DocumentObject* obj = Path.getValue();
        if (!obj) {
            error = "Click the edges of the path";
            return {};
        }
        const auto opts = Part::ShapeOption::ResolveLink | Part::ShapeOption::Transform;
        std::vector<Part::TopoShape> edges;
        for (const auto& sub : Path.getSubValues()) {
            if (!sub.empty()) {
                edges.push_back(Part::Feature::getTopoShape(obj, opts | Part::ShapeOption::NeedSubElement, sub.c_str()));
            }
        }
        if (edges.empty()) {  // ganze Skizze bzw. Objekt
            edges = Part::Feature::getTopoShape(obj, opts).getSubTopoShapes(TopAbs_EDGE);
        }
        BRepBuilderAPI_MakeWire wire;
        for (const auto& e : edges) {
            if (!e.isNull() && e.getShape().ShapeType() == TopAbs_EDGE) {
                wire.Add(TopoDS::Edge(e.getShape()));
            }
        }
        if (!wire.IsDone()) {
            error = "The path must be connected edges";
            return {};
        }
        BRepAdaptor_CompCurve curve(wire.Wire());
        const double length = GCPnts_AbscissaPoint::Length(curve);
        gp_Pnt p0;
        gp_Vec t0;
        curve.D1(curve.FirstParameter(), p0, t0);
        for (long k = 1; k < Count1.getValue(); ++k) {
            const double s = k * Spacing1.getValue();
            if (s > length + Precision::Confusion()) {
                error = "The copies do not fit on the path; reduce Count or Spacing";
                return {};
            }
            GCPnts_AbscissaPoint at(curve, s, curve.FirstParameter());
            gp_Pnt p;
            gp_Vec t;
            curve.D1(at.Parameter(), p, t);
            gp_Trsf trsf;
            trsf.SetTranslation(p0, p);
            if (FollowPath.getValue() && t0.Magnitude() > Precision::Confusion() && t.Magnitude() > Precision::Confusion()
                && !t0.IsParallel(t, Precision::Angular())) {
                gp_Trsf turn;  // erst am Anfang des Pfads mitdrehen, dann an die neue Stelle schieben
                turn.SetRotation(gp_Ax1(p0, gp_Dir(t0.Crossed(t))), t0.Angle(t));
                trsf.Multiply(turn);
            }
            Base::Matrix4D m;
            for (int r = 0; r < 3; ++r) {
                for (int c = 0; c < 4; ++c) {
                    m[r][c] = trsf.Value(r + 1, c + 1);
                }
            }
            transforms.push_back(m);
        }
    }
    if (transforms.empty() && error.empty()) {
        error = "Count must be at least 2";
    }
    return transforms;
}

App::DocumentObjectExecReturn* Pattern::compute()
{
    std::string error;
    const std::vector<Base::Matrix4D> transforms = this->transforms(error);
    if (transforms.empty()) {
        return new App::DocumentObjectExecReturn(error);
    }
    auto copiesOf = [&](const Part::TopoShape& shape) {
        std::vector<Part::TopoShape> copies;
        for (const auto& m : transforms) {  // Lagen sind global, das Werkzeug liegt in der Komponente des Musters
            copies.push_back(Part::TopoShape(0, getDocument()->getStringHasher())
                                 .makeElementTransform(shape, inComponent(this, m), nullptr,
                                                       Part::CheckScale::noScaleCheck, Part::CopyType::copy));
        }
        return copies;
    };
    // Körper-Muster: je Quell-Body ein neuer Body mit allen Kopien
    const auto& sources = SourceBodies.getValues();
    if (!sources.empty()) {
        const auto& states = SourceFeatures.getValues();
        if (states.size() != sources.size() || Bodies.getSize() != int(sources.size())) {
            return new App::DocumentObjectExecReturn("Select one or more bodies");
        }
        std::vector<Part::TopoShape> results;
        for (size_t i = 0; i < sources.size(); ++i) {
            auto state = freecad_cast<Feature*>(states[i]);
            if (!state) {
                return new App::DocumentObjectExecReturn("Body has no feature");
            }
            std::vector<Part::TopoShape> copies;
            for (const auto& m : transforms) {  // Richtungen und Achse sind global
                copies.push_back(Part::TopoShape(0, getDocument()->getStringHasher())
                                     .makeElementTransform(state->shapeFor(sources[i]), inComponent(sources[i], m),
                                                           nullptr, Part::CheckScale::noScaleCheck, Part::CopyType::copy));
            }
            results.push_back(Part::TopoShape(0, getDocument()->getStringHasher()).makeElementCompound(copies));
        }
        setResults(results);
        return StdReturn;
    }
    auto source = freecad_cast<Feature*>(Source.getValue());
    if (!source) {
        return new App::DocumentObjectExecReturn("Select a feature or bodies to pattern");
    }
    Part::TopoShape tool;
    if (!source->makeTool(tool, error)) {
        return new App::DocumentObjectExecReturn(error);
    }
    return applyTool(fuseAll(copiesOf(tool), getDocument()->getStringHasher()));
}

// ---------------------------------------------------------------------------------------------

PROPERTY_SOURCE(Design::Hole, Design::Feature)

Hole::Hole()
{
    ADD_PROPERTY_TYPE(Sketch, (nullptr), "Hole", App::Prop_None, "Sketch whose points are the hole centers");
    ADD_PROPERTY_TYPE(HoleType, (0L), "Hole", App::Prop_None, "Simple, counterbore or countersink");
    HoleType.setEnums(HoleEnums);
    ADD_PROPERTY_TYPE(Diameter, (5.0), "Hole", App::Prop_None, "Hole diameter");
    ADD_PROPERTY_TYPE(Depth, (10.0), "Hole", App::Prop_None, "Hole depth");
    ADD_PROPERTY_TYPE(ThroughAll, (false), "Hole", App::Prop_None, "Through all");
    ADD_PROPERTY_TYPE(HeadDiameter, (9.0), "Hole", App::Prop_None, "Counterbore/countersink diameter");
    ADD_PROPERTY_TYPE(HeadDepth, (3.0), "Hole", App::Prop_None, "Counterbore depth");
    ADD_PROPERTY_TYPE(CountersinkAngle, (90.0), "Hole", App::Prop_None, "Countersink angle");
    ADD_PROPERTY_TYPE(Reversed, (false), "Hole", App::Prop_None, "Flip direction");
    ADD_PROPERTY_TYPE(Standard, (0L), "Parameters", App::Prop_None, "Thread standard");
    Standard.setEnums(StandardEnums);
    ADD_PROPERTY_TYPE(Size, (0L), "Parameters", App::Prop_None, "Screw size");
    ADD_PROPERTY_TYPE(Kind, (0L), "Parameters", App::Prop_None, "Clearance hole or tapped hole");
    Kind.setEnums(KindEnums);
    ADD_PROPERTY_TYPE(Fit, (1L), "Parameters", App::Prop_None, "Fit of the clearance hole");
    Fit.setEnums(FitEnums);
    ADD_PROPERTY_TYPE(Screw, (0L), "Parameters", App::Prop_None, "Screw for the counterbore or countersink");
    ADD_PROPERTY_TYPE(Modeled, (false), "Parameters", App::Prop_None, "Modeled thread");
    ADD_PROPERTY_TYPE(ThreadDesignation, (""), "Hole", App::PropertyType(App::Prop_Output | App::Prop_ReadOnly),
                      "Thread of the hole, empty without thread");
    Operation.setValue(2L);  // Cut
    applyStandard();
}

void Hole::onChanged(const App::Property* prop)
{
    if (!isRestoring()
        && (prop == &Standard || prop == &Size || prop == &Kind || prop == &Fit || prop == &Screw || prop == &HoleType)) {
        applyStandard();
    }
    Feature::onChanged(prop);
}

void Hole::onDocumentRestored()
{
    applyStandard();
    Feature::onDocumentRestored();
}

/// Maße aus der Norm übernehmen und die Felder ein- und ausblenden. Ohne Norm bleiben alle Maße frei.
void Hole::applyStandard()
{
    if (applying) {
        return;
    }
    applying = true;
    const long standard = Standard.getValue();
    const PartDesign::Hole::ThreadDescription* t = nullptr;
    if (auto table = threadTable(standard)) {
        std::vector<std::string> sizes;
        for (const auto& d : *table) {
            sizes.emplace_back(d.designation);
        }
        if (Size.getEnumVector() != sizes) {
            // Neue Norm: die Größe nehmen, die dem bisherigen Durchmesser am nächsten kommt
            const std::string current = Size.isValid() ? Size.getValueAsString() : std::string();
            std::string keep = current;
            if (std::ranges::find(sizes, current) == sizes.end()) {
                const auto best = std::ranges::min_element(*table, {}, [this](const auto& d) {
                    return std::abs(d.diameter - Diameter.getValue());
                });
                keep = best->designation;
            }
            Size.setEnums(sizes);
            Size.setValue(keep.c_str());
        }
        t = threadSize(standard, Size.isValid() ? Size.getValueAsString() : "");
    }
    const bool tapped = Kind.getValue() == 1;
    if (t) {
        Diameter.setValue(tapped ? t->TapDrill : clearanceDiameter(standard, *t, Fit.getValue()));
    }
    ThreadDesignation.setValue(t && tapped ? t->designation : "");

    // Senkung nach Schraubennorm
    const HeadTable* head = nullptr;
    std::vector<std::string> screws;
    if (t && HoleType.getValue() != 0) {
        for (const auto& h : headTables()) {
            if (h.countersink == (HoleType.getValue() == 2) && h.sizes.contains(t->designation)) {
                screws.push_back(h.name);
            }
        }
    }
    if (screws.empty()) {
        screws.emplace_back("None");
    }
    // die gängigsten Schrauben zuerst (Zylinderkopf ISO 4762, Senkkopf ISO 10642), dann alphabetisch
    std::ranges::stable_partition(screws, [](const std::string& n) { return n == "ISO 4762" || n == "ISO 10642"; });
    if (Screw.getEnumVector() != screws) {
        const std::string current = Screw.isValid() ? Screw.getValueAsString() : std::string();
        Screw.setEnums(screws);
        Screw.setValue(std::ranges::find(screws, current) != screws.end() ? current.c_str() : screws.front().c_str());
    }
    if (t && HoleType.getValue() != 0) {
        const std::string name = Screw.getValueAsString();
        for (const auto& h : headTables()) {
            if (h.name == name && h.countersink == (HoleType.getValue() == 2) && h.sizes.contains(t->designation)) {
                head = &h;
            }
        }
    }
    if (head) {
        const auto& [diameter, depth] = head->sizes.at(t->designation);
        HeadDiameter.setValue(diameter);
        if (head->countersink) {
            CountersinkAngle.setValue(head->angle);
        }
        else {
            HeadDepth.setValue(depth);
        }
    }

    const bool custom = standard == 0;
    Diameter.setStatus(App::Property::ReadOnly, t != nullptr);
    for (App::Property* p : std::initializer_list<App::Property*> {&HeadDiameter, &HeadDepth, &CountersinkAngle}) {
        p->setStatus(App::Property::ReadOnly, head != nullptr);
    }
    Size.setStatus(App::Property::Hidden, custom);
    Kind.setStatus(App::Property::Hidden, custom);
    Fit.setStatus(App::Property::Hidden, custom || tapped);
    Modeled.setStatus(App::Property::Hidden, custom || !tapped);
    Screw.setStatus(App::Property::Hidden, custom || HoleType.getValue() == 0 || !head);
    applying = false;
}

bool Hole::makeTool(Part::TopoShape& tool, std::string& error) const
{
    auto sketch = freecad_cast<Part::Feature*>(Sketch.getValue());
    if (!sketch) {
        error = "Select a sketch with points";
        return false;
    }
    // Einzelne Skizzenpunkte sind die Vertices direkt unter dem Compound der Skizze
    std::vector<gp_Pnt> centers;
    for (TopoDS_Iterator it(sketch->Shape.getShape().getShape()); it.More(); it.Next()) {
        if (it.Value().ShapeType() == TopAbs_VERTEX) {
            centers.push_back(BRep_Tool::Pnt(TopoDS::Vertex(it.Value())));
        }
    }
    if (centers.empty()) {
        error = "The sketch has no points; place points where the holes go";
        return false;
    }
    const double r = Diameter.getValue() / 2, head = HeadDiameter.getValue() / 2;
    if (r < Precision::Confusion()) {
        error = "Diameter must be greater than zero";
        return false;
    }
    Base::Vector3d n = sketch->Placement.getValue().getRotation().multVec(Base::Vector3d(0, 0, -1));
    if (Reversed.getValue()) {
        n = -n;
    }
    const gp_Dir dir(n.x, n.y, n.z);
    constexpr double lead = 0.01;  // knapp über der Fläche beginnen, sonst schneidet die Bohrung koplanar
    Base::BoundBox3d around;
    for (const auto& c : centers) {
        around.Add(Base::Vector3d(c.X(), c.Y(), c.Z()));
    }
    const double depth = (ThroughAll.getValue() ? throughAllLength(getDocument(), around) : Depth.getValue()) + lead;

    // Modelliertes Gewinde: Rillen vom Kerndurchmesser D1 bis zum Nenndurchmesser, über die ganze Tiefe
    const PartDesign::Hole::ThreadDescription* thread = Modeled.getValue() && Kind.getValue() == 1 && Size.isValid()
        ? threadSize(Standard.getValue(), Size.getValueAsString())
        : nullptr;

    std::vector<Part::TopoShape> holes;
    try {
        for (const auto& c : centers) {
            const gp_Ax2 ax(c.Translated(gp_Vec(dir) * -lead), dir);
            std::vector<Part::TopoShape> parts {Part::TopoShape(BRepPrimAPI_MakeCylinder(ax, r, depth).Shape())};
            if (HoleType.getValue() == 1 && head > r) {
                parts.emplace_back(BRepPrimAPI_MakeCylinder(ax, head, HeadDepth.getValue() + lead).Shape());
            }
            else if (HoleType.getValue() == 2 && head > r) {
                const double h = head / std::tan(CountersinkAngle.getValue() * M_PI / 360.0);
                parts.emplace_back(BRepPrimAPI_MakeCone(ax, head, 0, h + lead).Shape());
            }
            if (thread) {
                const double minor = (thread->diameter - 1.082532 * thread->pitch) / 2;
                // ab der Oberfläche bis eine Steigung vor den Grund (wie ein Gewindebohrer im Sackloch); die
                // Enden liegen so nicht in denselben Ebenen wie die Bohrung
                parts.emplace_back(threadTool(gp_Ax1(c, dir), lead, depth - lead - thread->pitch - lead, minor,
                                              thread->pitch, false, false, 0));
            }
            holes.push_back(fuseAll(parts, getDocument()->getStringHasher()));
        }
    }
    catch (const Standard_Failure&) {
        error = "The thread could not be modeled; try a cosmetic thread";
        return false;
    }
    tool = fuseAll(holes, getDocument()->getStringHasher());
    return true;
}

App::DocumentObjectExecReturn* Hole::compute()
{
    Part::TopoShape tool;
    std::string error;
    if (!makeTool(tool, error)) {
        return new App::DocumentObjectExecReturn(error);
    }
    return applyTool(tool);
}

// ---------------------------------------------------------------------------------------------

PROPERTY_SOURCE(Design::PressPull, Design::DressUp)

PressPull::PressPull()
{
    ADD_PROPERTY_TYPE(Distance, (5.0), "PressPull", App::Prop_None, "Positive pulls out, negative pushes in");
    Size.setStatus(App::Property::Hidden, true);
}

App::DocumentObjectExecReturn* PressPull::compute()
{
    if (Bodies.getSize() != 1 || BaseFeatures.getSize() != 1) {
        return new App::DocumentObjectExecReturn("Select faces of one body");
    }
    const double d = Distance.getValue();
    if (std::abs(d) < Precision::Confusion()) {
        return new App::DocumentObjectExecReturn("Distance must not be zero");
    }
    const Part::TopoShape shape = baseShape(0);
    const auto faces = elements(shape, TopAbs_FACE);
    // Gekrümmte Flächen (Zylinder, Freiform): Fläche versetzen wie Fusions Offset Face, die Nachbarn passen sich an
    if (std::ranges::any_of(faces, [](const Part::TopoShape& f) {
            return BRepAdaptor_Surface(TopoDS::Face(f.getShape())).GetType() != GeomAbs_Plane;
        })) {
        BRepOffset_MakeOffset offset;
        offset.Initialize(shape.getShape(), 0.0, 1e-6, BRepOffset_Skin, Standard_False, Standard_False,
                          GeomAbs_Intersection);
        for (const auto& face : faces) {
            offset.SetOffsetOnFace(TopoDS::Face(face.getShape()), d);
        }
        try {
            offset.MakeOffsetShape();
        }
        catch (const Standard_Failure&) {
            return new App::DocumentObjectExecReturn("Press Pull failed: distance too large?");
        }
        if (!offset.IsDone() || offset.Shape().IsNull()) {
            return new App::DocumentObjectExecReturn("Press Pull failed: distance too large?");
        }
        Part::TopoShape res(offset.Shape());
        if (!res.isValid() || res.countSubShapes(TopAbs_SOLID) == 0) {
            return new App::DocumentObjectExecReturn("Press Pull failed: distance too large?");
        }
        setResults({res});
        return StdReturn;
    }
    std::vector<Part::TopoShape> prisms;
    for (const auto& face : faces) {
        BRepAdaptor_Surface surf(TopoDS::Face(face.getShape()));
        gp_Dir n = surf.Plane().Axis().Direction();  // nach außen zeigende Normale
        if (face.getShape().Orientation() == TopAbs_REVERSED) {
            n.Reverse();
        }
        prisms.push_back(Part::TopoShape(0, getDocument()->getStringHasher())
                             .makeElementPrism(face, gp_Vec(n) * d));
    }
    if (prisms.empty()) {
        return new App::DocumentObjectExecReturn("Select one or more faces");
    }
    const Part::TopoShape tool = fuseAll(prisms, getDocument()->getStringHasher());
    Part::TopoShape res(0, getDocument()->getStringHasher());
    if (d > 0) {
        res.makeElementFuse({shape, tool});
    }
    else {
        res.makeElementCut({shape, tool});
    }
    if (res.isNull() || res.countSubShapes(TopAbs_SOLID) == 0) {
        return new App::DocumentObjectExecReturn("Result would be empty");
    }
    setResults({res.makeElementRefine(nullptr, Part::RefineFail::shapeUntouched)});
    return StdReturn;
}

// ---------------------------------------------------------------------------------------------

PROPERTY_SOURCE(Design::Import, Design::Feature)

Import::Import()
{
    ADD_PROPERTY_TYPE(Imported, (TopoDS_Shape()), "Import", App::Prop_Hidden, "Imported geometry");
    ADD_PROPERTY_TYPE(SourceFile, (""), "Import", App::Prop_ReadOnly, "File the geometry came from");
    Operation.setStatus(App::Property::Hidden, true);
}

std::vector<Part::TopoShape> Import::pieces(const Part::TopoShape& shape)
{
    for (auto type : {TopAbs_SOLID, TopAbs_SHELL}) {
        if (shape.countSubShapes(type) > 0) {
            return shape.getSubTopoShapes(type);
        }
    }
    return shape.isNull() ? std::vector<Part::TopoShape>() : std::vector<Part::TopoShape> {shape};
}

App::DocumentObjectExecReturn* Import::compute()
{
    const auto parts = pieces(Imported.getShape());
    if (parts.empty() || parts.size() != size_t(Bodies.getSize())) {
        return new App::DocumentObjectExecReturn("Imported geometry is missing");
    }
    setResults(parts);
    return StdReturn;
}

// ---------------------------------------------------------------------------------------------

PROPERTY_SOURCE(Design::Sweep, Design::Feature)

Sweep::Sweep()
{
    ADD_PROPERTY_TYPE(ProfileKeys, (), "Sweep", App::PropertyType(App::Prop_Output | App::Prop_Hidden),
                      "Signatures of the selected profiles");
    ADD_PROPERTY_TYPE(Profile, (nullptr), "Sweep", App::Prop_None, "Profiles to sweep");
    ADD_PROPERTY_TYPE(Path, (nullptr), "Sweep", App::Prop_None, "Path edges");
}

bool Sweep::makeTool(Part::TopoShape& tool, std::string& error) const
{
    Part::Feature* sketch = nullptr;
    const char* reason = nullptr;
    const auto faces = profileFaces(Profile, const_cast<App::PropertyStringList&>(ProfileKeys), sketch, reason);
    if (faces.empty()) {
        error = reason;
        return false;
    }
    auto path = freecad_cast<Part::Feature*>(Path.getValue());
    if (!path) {
        error = "Select a path (sketch lines or body edges)";
        return false;
    }
    const Part::TopoShape all = path->Shape.getShape();
    std::vector<Part::TopoShape> edges;
    for (const auto& sub : Path.getSubValues()) {
        edges.push_back(all.getSubTopoShape(sub.c_str(), true));
    }
    if (edges.empty()) {
        edges = all.getSubTopoShapes(TopAbs_EDGE);
    }
    std::erase_if(edges, [](const Part::TopoShape& e) { return e.isNull(); });
    const Part::TopoShape wires = Part::TopoShape(0, getDocument()->getStringHasher()).makeElementWires(edges);
    TopExp_Explorer wire(wires.getShape(), TopAbs_WIRE);
    if (!wire.More()) {
        error = "The path must be a connected chain of edges";
        return false;
    }
    std::vector<Part::TopoShape> pipes;
    try {
        for (const auto& face : faces) {
            BRepOffsetAPI_MakePipe pipe(TopoDS::Wire(wire.Current()), face.getShape());
            pipe.Build();
            pipes.emplace_back(pipe.Shape());
        }
    }
    catch (const Standard_Failure&) {
        error = "Sweep failed: does the path cross itself or the profile?";
        return false;
    }
    tool = fuseAll(pipes, getDocument()->getStringHasher());
    return true;
}

App::DocumentObjectExecReturn* Sweep::compute()
{
    Part::TopoShape tool;
    std::string error;
    if (!makeTool(tool, error)) {
        return new App::DocumentObjectExecReturn(error);
    }
    return applyTool(tool);
}

// ---------------------------------------------------------------------------------------------

PROPERTY_SOURCE(Design::Loft, Design::Feature)

Loft::Loft()
{
    ADD_PROPERTY_TYPE(Sections, (nullptr), "Loft", App::Prop_None, "Profiles in order");
    ADD_PROPERTY_TYPE(Ruled, (false), "Parameters", App::Prop_None, "Straight transitions");
    ADD_PROPERTY_TYPE(Closed, (false), "Parameters", App::Prop_None, "Connect the last profile back to the first");
}

bool Loft::makeTool(Part::TopoShape& tool, std::string& error) const
{
    const auto& objs = Sections.getValues();
    const auto& subs = Sections.getSubValues();
    std::vector<Part::TopoShape> wires;
    for (size_t i = 0; i < objs.size(); ++i) {
        auto profiles = freecad_cast<Profiles*>(objs[i]);
        if (!profiles) {
            continue;
        }
        const Part::TopoShape all = profiles->Shape.getShape();
        const std::string sub = i < subs.size() && !subs[i].empty() ? subs[i] : std::string("Face1");
        const TopoDS_Shape face = all.getSubShape(sub.c_str(), true);
        if (!face.IsNull()) {
            wires.emplace_back(BRepTools::OuterWire(TopoDS::Face(face)));
        }
    }
    if (wires.size() < 2) {
        error = "Select two or more profiles from different sketches";
        return false;
    }
    try {
        tool = Part::TopoShape(0, getDocument()->getStringHasher())
                   .makeElementLoft(wires, Part::IsSolid::solid,
                                    Ruled.getValue() ? Part::IsRuled::ruled : Part::IsRuled::notRuled,
                                    Closed.getValue() ? Part::IsClosed::closed : Part::IsClosed::notClosed);
    }
    catch (const Standard_Failure&) {
        error = "Loft failed: are the profiles compatible?";
        return false;
    }
    catch (const Base::Exception& e) {
        error = e.what();
        return false;
    }
    return !tool.isNull();
}

App::DocumentObjectExecReturn* Loft::compute()
{
    Part::TopoShape tool;
    std::string error;
    if (!makeTool(tool, error)) {
        return new App::DocumentObjectExecReturn(error);
    }
    return applyTool(tool);
}

// ---------------------------------------------------------------------------------------------

PROPERTY_SOURCE(Design::Primitive, Design::Feature)

Primitive::Primitive()
{
    static const App::PropertyFloatConstraint::Constraints turns = {0.25, 1000.0, 0.25};
    ADD_PROPERTY_TYPE(Plane, (nullptr), "Primitive", App::Prop_None, "Plane or planar face (empty: XY)");
    ADD_PROPERTY_TYPE(Type, (0L), "Parameters", App::Prop_None, "Shape");
    Type.setEnums(PrimitiveEnums);
    ADD_PROPERTY_TYPE(Length, (20.0), "Parameters", App::Prop_None, "Length along X");
    ADD_PROPERTY_TYPE(Width, (20.0), "Parameters", App::Prop_None, "Width along Y");
    ADD_PROPERTY_TYPE(Height, (20.0), "Parameters", App::Prop_None, "Height");
    ADD_PROPERTY_TYPE(Radius, (10.0), "Parameters", App::Prop_None, "Radius");
    ADD_PROPERTY_TYPE(TubeRadius, (2.0), "Parameters", App::Prop_None, "Tube radius (torus, coil)");
    ADD_PROPERTY_TYPE(Pitch, (6.0), "Parameters", App::Prop_None, "Height per turn");
    ADD_PROPERTY_TYPE(Turns, (4.0), "Parameters", App::Prop_None, "Number of turns");
    Turns.setConstraints(&turns);
    ADD_PROPERTY_TYPE(PositionX, (0.0), "Parameters", App::Prop_None, "Position on the plane (X)");
    ADD_PROPERTY_TYPE(PositionY, (0.0), "Parameters", App::Prop_None, "Position on the plane (Y)");
    onChanged(&Type);
}

void Primitive::onChanged(const App::Property* prop)
{
    if (prop == &Type) {  // nur die Maße der gewählten Form zeigen
        const long t = Type.getValue();
        Length.setStatus(App::Property::Hidden, t != 0);
        Width.setStatus(App::Property::Hidden, t != 0);
        Height.setStatus(App::Property::Hidden, t != 0 && t != 1);
        Radius.setStatus(App::Property::Hidden, t == 0);
        TubeRadius.setStatus(App::Property::Hidden, t != 3 && t != 4);
        Pitch.setStatus(App::Property::Hidden, t != 4);
        Turns.setStatus(App::Property::Hidden, t != 4);
    }
    Feature::onChanged(prop);
}

bool Primitive::makeTool(Part::TopoShape& tool, std::string& error) const
{
    gp_Ax3 ax;
    if (!planeAxes(Plane, ax)) {
        error = "Select a plane or a planar face";
        return false;
    }
    const double l = Length.getValue(), w = Width.getValue(), h = Height.getValue();
    const double r = Radius.getValue(), r2 = TubeRadius.getValue();
    TopoDS_Shape shape;
    try {
        switch (Type.getValue()) {
            case 0:
                shape = BRepPrimAPI_MakeBox(gp_Pnt(-l / 2, -w / 2, 0), l, w, h).Shape();
                break;
            case 1:
                shape = BRepPrimAPI_MakeCylinder(r, h).Shape();
                break;
            case 2:
                shape = BRepPrimAPI_MakeSphere(r).Shape();
                break;
            case 3:
                if (r2 >= r) {
                    error = "Tube radius must be smaller than the radius";
                    return false;
                }
                shape = BRepPrimAPI_MakeTorus(r, r2).Shape();
                break;
            default: {
                if (r2 >= r) {
                    error = "Tube radius must be smaller than the radius";
                    return false;
                }
                const double pitch = Pitch.getValue();
                const TopoDS_Shape helix = Part::TopoShape().makeHelix(pitch, pitch * Turns.getValue(), r);
                TopExp_Explorer spine(helix, TopAbs_WIRE);
                // Querschnitt am Anfang der Helix, quer zur Laufrichtung
                const TopoDS_Edge circle = BRepBuilderAPI_MakeEdge(gp_Circ(gp_Ax2(gp_Pnt(r, 0, 0), gp::DY()), r2));
                BRepOffsetAPI_MakePipeShell pipe(TopoDS::Wire(spine.Current()));
                pipe.SetMode(Standard_True);  // Frenet: Querschnitt dreht mit
                pipe.Add(BRepBuilderAPI_MakeWire(circle).Wire());
                pipe.Build();
                pipe.MakeSolid();
                shape = pipe.Shape();
                break;
            }
        }
    }
    catch (const Standard_Failure&) {
        error = "Check the dimensions: all must be greater than zero";
        return false;
    }
    gp_Trsf place, offset;
    place.SetDisplacement(gp_Ax3(gp::XOY()), ax);
    offset.SetTranslation(gp_Vec(PositionX.getValue(), PositionY.getValue(), 0));
    tool = Part::TopoShape(BRepBuilderAPI_Transform(shape, place * offset, Standard_True).Shape());
    return true;
}

App::DocumentObjectExecReturn* Primitive::compute()
{
    Part::TopoShape tool;
    std::string error;
    if (!makeTool(tool, error)) {
        return new App::DocumentObjectExecReturn(error);
    }
    return applyTool(tool);
}

// ---------------------------------------------------------------------------------------------

PROPERTY_SOURCE(Design::Draft, Design::DressUp)

Draft::Draft()
{
    ADD_PROPERTY_TYPE(Angle, (3.0), "Parameters", App::Prop_None, "Draft angle");
    ADD_PROPERTY_TYPE(Reversed, (false), "Parameters", App::Prop_None, "Flip direction");
    ADD_PROPERTY_TYPE(Plane, (nullptr), "Draft", App::Prop_None, "Neutral plane (empty: bottom of the body)");
    Size.setStatus(App::Property::Hidden, true);
}

App::DocumentObjectExecReturn* Draft::compute()
{
    if (Bodies.getSize() != 1 || BaseFeatures.getSize() != 1) {
        return new App::DocumentObjectExecReturn("Select faces of one body");
    }
    const Part::TopoShape shape = baseShape(0);
    const auto faces = elements(shape, TopAbs_FACE);
    if (faces.empty()) {
        return new App::DocumentObjectExecReturn("Select the faces to draft");
    }
    gp_Ax3 ax;
    if (Plane.getValue()) {
        if (!planeAxes(Plane, ax)) {
            return new App::DocumentObjectExecReturn("The neutral plane must be a plane or planar face");
        }
    }
    else {
        ax = gp_Ax3(gp_Pnt(0, 0, shape.getBoundBox().MinZ), gp::DZ());
    }
    gp_Dir pull = ax.Direction();
    if (Reversed.getValue()) {
        pull.Reverse();
    }
    Part::TopoShape res(0, getDocument()->getStringHasher());
    try {
        res.makeElementDraft(shape, faces, pull, Angle.getValue() * M_PI / 180.0, gp_Pln(ax), false);
    }
    catch (const Standard_Failure&) {
        return new App::DocumentObjectExecReturn("Draft failed: are the faces planar and adjacent to the plane?");
    }
    catch (const Base::Exception& e) {
        return new App::DocumentObjectExecReturn(e.what());
    }
    if (res.isNull() || !res.isValid()) {
        return new App::DocumentObjectExecReturn("Draft failed");
    }
    setResults({res});
    return StdReturn;
}

// ---------------------------------------------------------------------------------------------

PROPERTY_SOURCE(Design::Scale, Design::Feature)

Scale::Scale()
{
    static const App::PropertyFloatConstraint::Constraints factor = {0.001, 1000.0, 0.1};
    ADD_PROPERTY_TYPE(Factor, (1.0), "Parameters", App::Prop_None, "Scale factor");
    Factor.setConstraints(&factor);
    ADD_PROPERTY_TYPE(Center, (1L), "Parameters", App::Prop_None, "Scale around");
    Center.setEnums(CenterEnums);
    Operation.setStatus(App::Property::Hidden, true);
}

App::DocumentObjectExecReturn* Scale::compute()
{
    if (Bodies.getSize() == 0 || Bodies.getSize() != BaseFeatures.getSize()) {
        return new App::DocumentObjectExecReturn("Select one or more bodies");
    }
    std::vector<Part::TopoShape> results;
    for (int i = 0; i < Bodies.getSize(); ++i) {
        const Part::TopoShape base = baseShape(i);
        const Base::Matrix4D toGlobal = Design::componentOf(Bodies[i])->globalPlacement().toMatrix();
        const Base::Vector3d c = Center.getValue() == 1 ? base.getBoundBox().Transformed(toGlobal).GetCenter()
                                                        : Base::Vector3d();
        Base::Matrix4D global;
        global.move(-c);
        global.scale(Factor.getValue());
        global.move(c);
        const Base::Matrix4D mat = inComponent(Bodies[i], global);
        results.push_back(Part::TopoShape(0, getDocument()->getStringHasher())
                              .makeElementTransform(base, mat, nullptr, Part::CheckScale::checkScale,
                                                    Part::CopyType::copy));
    }
    setResults(results);
    return StdReturn;
}

// ---------------------------------------------------------------------------------------------

PROPERTY_SOURCE(Design::Split, Design::Feature)

Split::Split()
{
    ADD_PROPERTY_TYPE(Tool, (nullptr), "Split", App::Prop_None, "Plane or face to split with");
    ADD_PROPERTY_TYPE(Pieces, (0L), "Split", App::PropertyType(App::Prop_Output | App::Prop_Hidden), "Pieces");
    Operation.setStatus(App::Property::Hidden, true);
}

App::DocumentObjectExecReturn* Split::compute()
{
    if (Bodies.getSize() < 1 || BaseFeatures.getSize() < 1) {
        return new App::DocumentObjectExecReturn("Select a body and a plane or face");
    }
    const Part::TopoShape shape = baseShape(0);
    // Ebene: große Fläche über den ganzen Körper; sonst die gewählte Fläche selbst
    TopoDS_Shape tool;
    gp_Ax3 ax;
    if (Tool.getValue() && planeAxes(Tool, ax)) {
        tool = planeFace(gp_Pln(ax), shape.getBoundBox());
    }
    else if (Tool.getValue()) {
        const auto& subs = Tool.getSubValues();
        tool = Part::Feature::getTopoShape(Tool.getValue(), Part::ShapeOption::ResolveLink | Part::ShapeOption::Transform | Part::ShapeOption::NeedSubElement,
                                           subs.empty() ? nullptr : subs.front().c_str())
                   .getShape();
    }
    if (tool.IsNull()) {
        return new App::DocumentObjectExecReturn("Select a plane or face to split with");
    }
    TopTools_ListOfShape args, tools;
    args.Append(shape.getShape());
    tools.Append(tool);
    BRepAlgoAPI_Splitter splitter;
    splitter.SetArguments(args);
    splitter.SetTools(tools);
    splitter.Build();
    if (!splitter.IsDone()) {
        return new App::DocumentObjectExecReturn("Split failed");
    }
    std::vector<Part::TopoShape> pieces;
    for (TopExp_Explorer it(splitter.Shape(), TopAbs_SOLID); it.More(); it.Next()) {
        pieces.emplace_back(it.Current());
    }
    if (pieces.size() < 2) {
        return new App::DocumentObjectExecReturn("The plane or face does not cut through the body");
    }
    if (Pieces.getValue() != long(pieces.size())) {
        Pieces.setValue(long(pieces.size()));
    }
    std::vector<Part::TopoShape> results;
    for (int i = 0; i < Bodies.getSize(); ++i) {
        results.push_back(i < int(pieces.size()) ? pieces[i] : Part::TopoShape());
    }
    // mehr Teile als Bodies (Werkzeug verschoben): die übrigen bleiben beim letzten Body
    for (size_t i = Bodies.getSize(); i < pieces.size(); ++i) {
        results.back() = Part::TopoShape(0, getDocument()->getStringHasher()).makeElementCompound({results.back(), pieces[i]});
    }
    setResults(results);
    return StdReturn;
}

// ---------------------------------------------------------------------------------------------

PROPERTY_SOURCE(Design::Thread, Design::DressUp)

Thread::Thread()
{
    ADD_PROPERTY_TYPE(Standard, (0L), "Parameters", App::Prop_None, "Thread standard");
    Standard.setEnums(StandardEnums);
    ADD_PROPERTY_TYPE(ThreadSize, (0L), "Parameters", App::Prop_None, "Thread size; Auto fits the face");
    ADD_PROPERTY_TYPE(Pitch, (1.5), "Parameters", App::Prop_None, "Thread pitch");
    ADD_PROPERTY_TYPE(Clearance, (0.0), "Parameters", App::Prop_None,
                      "Clearance per side, e.g. 0.2 mm for 3D printing; negative gives interference");
    ADD_PROPERTY_TYPE(LeftHanded, (false), "Parameters", App::Prop_None, "Left-handed thread");
    Size.setStatus(App::Property::Hidden, true);
    updateSizes();
}

void Thread::onChanged(const App::Property* prop)
{
    if (!isRestoring() && (prop == &Standard || prop == &ThreadSize)) {
        updateSizes();
    }
    DressUp::onChanged(prop);
}

void Thread::setupObject()
{
    Standard.setValue(1L);
    DressUp::setupObject();
}

void Thread::onDocumentRestored()
{
    updateSizes();
    DressUp::onDocumentRestored();
}

/// Größenliste der Norm; eine feste Größe trägt ihre Steigung ein, "Auto" sucht beim Rechnen die passende
void Thread::updateSizes()
{
    std::vector<std::string> sizes {"Auto"};
    if (auto table = threadTable(Standard.getValue())) {
        for (const auto& d : *table) {
            sizes.emplace_back(d.designation);
        }
    }
    if (ThreadSize.getEnumVector() != sizes) {
        const std::string current = ThreadSize.isValid() ? ThreadSize.getValueAsString() : std::string();
        ThreadSize.setEnums(sizes);
        ThreadSize.setValue(std::ranges::find(sizes, current) != sizes.end() ? current.c_str() : "Auto");
    }
    const auto* t = threadSize(Standard.getValue(), ThreadSize.getValueAsString());
    if (t) {
        Pitch.setValue(t->pitch);
    }
    ThreadSize.setStatus(App::Property::Hidden, Standard.getValue() == 0);
    Pitch.setStatus(App::Property::Hidden, Standard.getValue() != 0);  // bei Auto stünde sonst eine falsche Steigung da
}

App::DocumentObjectExecReturn* Thread::compute()
{
    if (Bodies.getSize() != 1 || BaseFeatures.getSize() != 1) {
        return new App::DocumentObjectExecReturn("Select a cylindrical face of one body");
    }
    const Part::TopoShape shape = baseShape(0);
    const auto faces = elements(shape, TopAbs_FACE);
    if (faces.size() != 1) {
        return new App::DocumentObjectExecReturn("Select one cylindrical face");
    }
    const TopoDS_Face face = TopoDS::Face(faces.front().getShape());
    BRepAdaptor_Surface surface(face);
    if (surface.GetType() != GeomAbs_Cylinder) {
        return new App::DocumentObjectExecReturn("The face must be cylindrical");
    }
    const gp_Cylinder cyl = surface.Cylinder();
    // Achse immer gleich ausrichten (größte Komponente positiv): Welle und Bohrung derselben Lage bekommen dieselbe
    // Gewinde-Phase, egal wie ihre Flächen entstanden sind
    gp_Ax1 axis = cyl.Axis();
    const gp_Dir d = axis.Direction();
    const double big = std::abs(d.X()) >= std::abs(d.Y()) && std::abs(d.X()) >= std::abs(d.Z()) ? d.X()
                     : std::abs(d.Y()) >= std::abs(d.Z())                                    ? d.Y()
                                                                                             : d.Z();
    if (big < 0) {
        axis.Reverse();
    }
    const double r = cyl.Radius();

    // Welle: Rillen nach innen; Bohrung (Fläche zeigt zur Achse): Rillen nach außen. Beides wird abgezogen.
    // Zeigt die Flächennormale von der Achse weg, ist es eine Welle (die Orientierung allein hängt von der Entstehung ab)
    gp_Pnt mid;
    gp_Vec du, dv;
    surface.D1((surface.FirstUParameter() + surface.LastUParameter()) / 2,
               (surface.FirstVParameter() + surface.LastVParameter()) / 2, mid, du, dv);
    gp_Vec normal = du.Crossed(dv);
    if (face.Orientation() == TopAbs_REVERSED) {
        normal.Reverse();
    }
    const gp_Vec fromAxis(axis.Location().Translated(gp_Vec(axis.Direction())
                                                     * gp_Vec(axis.Location(), mid).Dot(gp_Vec(axis.Direction()))),
                          mid);
    const bool external = normal.Dot(fromAxis) > 0;

    // Steigung: aus der Norm (Auto: Größe nach dem Durchmesser der Fläche) oder frei
    double p = Pitch.getValue();
    if (auto table = threadTable(Standard.getValue())) {
        const PartDesign::Hole::ThreadDescription* t = threadSize(Standard.getValue(), ThreadSize.getValueAsString());
        if (!t) {  // Auto: Welle nach Nenndurchmesser, Bohrung nach Kerndurchmesser
            t = &*std::ranges::min_element(*table, {}, [r, external](const auto& s) {
                return std::abs((external ? s.diameter : s.diameter - 1.082532 * s.pitch) - 2 * r);
            });
        }
        p = t->pitch;
    }
    // Länge der Fläche entlang der Achse
    double t0 = 1e100, t1 = -1e100;
    for (TopExp_Explorer v(face, TopAbs_VERTEX); v.More(); v.Next()) {
        const double t = gp_Vec(axis.Location(), BRep_Tool::Pnt(TopoDS::Vertex(v.Current()))).Dot(gp_Vec(axis.Direction()));
        t0 = std::min(t0, t);
        t1 = std::max(t1, t);
    }
    const double height = t1 - t0;
    if (p < Precision::Confusion() || height < 2 * p) {
        return new App::DocumentObjectExecReturn("The face is too short for this pitch");
    }
    if (std::abs(Clearance.getValue()) >= 0.3 * p) {
        return new App::DocumentObjectExecReturn("Clearance must be smaller than a third of the pitch");
    }
    // ponytail: Gewinde läuft bis an die Flächenenden und ist dort abgeschnitten (kein Auslauf, keine Fase)
    Part::TopoShape res(0, getDocument()->getStringHasher());
    try {
        const TopoDS_Shape tool = threadTool(axis, t0, height, r, p, external, LeftHanded.getValue(),
                                             Clearance.getValue());
        // Toleranz: die Enden der Rillen liegen genau in den Stirnflächen, ohne sie trennt OCCT nur Flächen auf
        res.makeElementCut({shape, Part::TopoShape(tool)}, nullptr, 1e-5);
    }
    catch (const Standard_Failure&) {
        return new App::DocumentObjectExecReturn("Thread failed");
    }
    if (res.isNull() || !res.isValid()) {
        return new App::DocumentObjectExecReturn("Thread failed");
    }
    setResults({res});
    return StdReturn;
}

// ---------------------------------------------------------------------------------------------

PROPERTY_SOURCE(Design::Rib, Design::Feature)

Rib::Rib()
{
    ADD_PROPERTY_TYPE(Curves, (nullptr), "Rib", App::Prop_None, "Sketch lines of the rib");
    ADD_PROPERTY_TYPE(Thickness, (3.0), "Parameters", App::Prop_None, "Rib thickness");
    ADD_PROPERTY_TYPE(Mode, (0L), "Rib", App::Prop_None, "Rib: grows in the sketch plane; Web: perpendicular to it");
    Mode.setEnums(RibEnums);
    Operation.setStatus(App::Property::Hidden, true);
}

App::DocumentObjectExecReturn* Rib::compute()
{
    if (Bodies.getSize() != 1 || BaseFeatures.getSize() != 1) {
        return new App::DocumentObjectExecReturn("Select a body and sketch lines");
    }
    auto sketch = freecad_cast<Part::Feature*>(Curves.getValue());
    if (!sketch) {
        return new App::DocumentObjectExecReturn("Select sketch lines for the rib");
    }
    const double t = Thickness.getValue();
    if (t < Precision::Confusion()) {
        return new App::DocumentObjectExecReturn("Thickness must be greater than zero");
    }
    Part::TopoShape shape = baseShape(0);
    const TopoDS_Shape original = shape.getShape();  // jede Rippe gegen den Körper ohne die anderen (sich kreuzende Linien)
    const Base::BoundBox3d bb = shape.getBoundBox();
    const double far = bb.CalcDiagonalLength() * 2 + 10;
    Base::Vector3d sn;
    sketch->Placement.getValue().getRotation().multVec(Base::Vector3d(0, 0, 1), sn);
    const gp_Vec normal(sn.x, sn.y, sn.z);

    const Part::TopoShape all = sketch->Shape.getShape();
    std::vector<TopoDS_Shape> edges;
    for (const auto& sub : Curves.getSubValues()) {
        edges.push_back(all.getSubShape(sub.c_str(), true));
    }
    if (edges.empty()) {
        for (TopExp_Explorer e(all.getShape(), TopAbs_EDGE); e.More(); e.Next()) {
            edges.push_back(e.Current());
        }
    }
    int made = 0;
    for (const auto& edge : edges) {
        BRepAdaptor_Curve curve(TopoDS::Edge(edge));
        if (curve.GetType() != GeomAbs_Line) {
            continue;  // ponytail: nur gerade Linien; gebogene Rippen bräuchten einen 2D-Versatz
        }
        const gp_Pnt a = curve.Value(curve.FirstParameter()), b = curve.Value(curve.LastParameter());
        const gp_Vec along(a, b);
        const gp_Vec inPlane = normal.Crossed(along).Normalized();  // in der Skizzenebene quer zur Linie
        // Rib wächst in der Ebene (quer zur Linie), die Dicke liegt senkrecht dazu; Web umgekehrt
        const bool web = Mode.getValue() == 1;
        const gp_Vec grow = web ? normal.Normalized() : inPlane;
        const gp_Vec across = web ? inPlane : normal.Normalized();
        const gp_Vec side = grow;
        const gp_Pnt mid = a.Translated(along * 0.5);
        // beide Seiten probieren: genommen wird das Stück an der Linie, das ringsum vom Körper begrenzt ist
        bool done = false;
        for (double s : {1.0, -1.0}) {
            const gp_Vec out = grow * (s * far);
            BRepBuilderAPI_MakePolygon outline(a, b, b.Translated(out), a.Translated(out), Standard_True);
            const TopoDS_Face face = BRepBuilderAPI_MakeFace(outline.Wire()).Face();
            gp_Trsf shift;
            shift.SetTranslation(across * (-t / 2));
            const TopoDS_Shape slab = BRepPrimAPI_MakePrism(BRepBuilderAPI_Transform(face, shift).Shape(), across * t)
                                          .Shape();
            BRepAlgoAPI_Cut cut(slab, original);
            if (!cut.IsDone()) {
                continue;
            }
            const gp_Pnt probe = mid.Translated(side * (s * 1e-3 * (1 + along.Magnitude())));
            for (TopExp_Explorer piece(cut.Shape(), TopAbs_SOLID); piece.More(); piece.Next()) {
                BRepClass3d_SolidClassifier inside(piece.Current(), probe, 1e-7);
                if (inside.State() != TopAbs_IN) {
                    continue;
                }
                Bnd_Box box;
                BRepBndLib::Add(piece.Current(), box);
                double x0, y0, z0, x1, y1, z1;
                box.Get(x0, y0, z0, x1, y1, z1);
                const double tol = t + 1e-3;
                if (x0 < bb.MinX - tol || y0 < bb.MinY - tol || z0 < bb.MinZ - tol || x1 > bb.MaxX + tol
                    || y1 > bb.MaxY + tol || z1 > bb.MaxZ + tol) {
                    break;  // läuft ins Leere: diese Seite ist offen
                }
                shape = Part::TopoShape(0, getDocument()->getStringHasher())
                            .makeElementFuse({shape, Part::TopoShape(piece.Current())})
                            .makeElementRefine(nullptr, Part::RefineFail::shapeUntouched);
                done = true;
                break;
            }
            if (done) {
                break;
            }
        }
        if (!done) {
            return new App::DocumentObjectExecReturn("Both ends of each rib line must touch the body");
        }
        ++made;
    }
    if (!made) {
        return new App::DocumentObjectExecReturn("Select straight sketch lines for the rib");
    }
    setResults({shape});
    return StdReturn;
}

// ---------------------------------------------------------------------------------------------

PROPERTY_SOURCE(Design::ReplaceFace, Design::DressUp)

ReplaceFace::ReplaceFace()
{
    ADD_PROPERTY_TYPE(Target, (nullptr), "Replace Face", App::Prop_None, "Plane or face to extend or trim to");
    Size.setStatus(App::Property::Hidden, true);
}

App::DocumentObjectExecReturn* ReplaceFace::compute()
{
    if (Bodies.getSize() != 1 || BaseFeatures.getSize() != 1) {
        return new App::DocumentObjectExecReturn("Select faces of one body and a target");
    }
    Part::TopoShape shape = baseShape(0);
    const auto faces = elements(shape, TopAbs_FACE);
    const TopoDS_Shape target = toolShape(Target, shape.getBoundBox());
    TopExp_Explorer targetFace(target, TopAbs_FACE);
    if (faces.empty() || !targetFace.More()) {
        return new App::DocumentObjectExecReturn("Select the faces to replace and a target plane or face");
    }
    const double far = shape.getBoundBox().CalcDiagonalLength() * 4 + 10;
    for (const auto& f : faces) {
        const TopoDS_Face face = TopoDS::Face(f.getShape());
        gp_Pnt c;
        gp_Vec n;
        if (!planarFrame(face, c, n)) {
            return new App::DocumentObjectExecReturn("Replace Face supports planar faces");
        }
        // Ziel ist eine Ebene (bzw. ebene Fläche): wo trifft die Flächennormale sie? t > 0: Ziel liegt außen
        BRepAdaptor_Surface targetSurface(TopoDS::Face(targetFace.Current()));
        if (targetSurface.GetType() != GeomAbs_Plane) {
            return new App::DocumentObjectExecReturn("The target must be a plane or planar face");
        }
        const gp_Pln pln = targetSurface.Plane();
        const gp_Vec tn(pln.Axis().Direction());
        const double dot = tn.Dot(n);
        if (std::abs(dot) < 1e-9) {
            return new App::DocumentObjectExecReturn("The target must cross the direction of the face");
        }
        const double t = tn.Dot(gp_Vec(c, pln.Location())) / dot;
        if (std::abs(t) < Precision::Confusion()) {
            continue;  // liegt schon dort
        }
        const bool outward = t > 0;
        // Prisma der Fläche Richtung Ziel, geschnitten mit einer dicken Platte an der Zielebene auf der Seite der Fläche
        const TopoDS_Shape prism = BRepPrimAPI_MakePrism(face, (outward ? n : -n) * far).Shape();
        const double side = tn.Dot(gp_Vec(pln.Location(), c)) > 0 ? 1.0 : -1.0;
        const TopoDS_Shape slab = BRepPrimAPI_MakePrism(TopoDS::Face(targetFace.Current()), tn * (side * far)).Shape();
        BRepAlgoAPI_Common region(prism, slab);
        if (!region.IsDone()) {
            return new App::DocumentObjectExecReturn("Replace Face failed");
        }
        const Part::TopoShape piece(region.Shape());
        Part::TopoShape res(0, getDocument()->getStringHasher());
        if (outward) {
            res.makeElementFuse({shape, piece});
        }
        else {
            res.makeElementCut({shape, piece});
        }
        shape = res.makeElementRefine(nullptr, Part::RefineFail::shapeUntouched);
    }
    if (shape.isNull() || !shape.isValid()) {
        return new App::DocumentObjectExecReturn("Replace Face failed");
    }
    setResults({shape});
    return StdReturn;
}

// ---------------------------------------------------------------------------------------------

PROPERTY_SOURCE(Design::SplitFace, Design::DressUp)

SplitFace::SplitFace()
{
    ADD_PROPERTY_TYPE(Tool, (nullptr), "Split Face", App::Prop_None, "Plane, face or sketch to split with");
    Size.setStatus(App::Property::Hidden, true);
}

App::DocumentObjectExecReturn* SplitFace::compute()
{
    if (Bodies.getSize() != 1 || BaseFeatures.getSize() != 1) {
        return new App::DocumentObjectExecReturn("Select faces of one body and a splitting tool");
    }
    const Part::TopoShape shape = baseShape(0);
    const auto faces = elements(shape, TopAbs_FACE);
    const TopoDS_Shape tool = toolShape(Tool, shape.getBoundBox());
    if (faces.empty() || tool.IsNull()) {
        return new App::DocumentObjectExecReturn("Select the faces to split and a plane, face or sketch");
    }
    BRepFeat_SplitShape split(shape.getShape());
    int added = 0;
    for (const auto& f : faces) {
        BRepAlgoAPI_Section section(f.getShape(), tool, Standard_False);
        section.ComputePCurveOn1(Standard_True);
        section.Approximation(Standard_True);
        section.Build();
        if (!section.IsDone()) {
            continue;
        }
        for (TopExp_Explorer e(section.Shape(), TopAbs_EDGE); e.More(); e.Next()) {
            split.Add(TopoDS::Edge(e.Current()), TopoDS::Face(f.getShape()));
            ++added;
        }
    }
    if (!added) {
        return new App::DocumentObjectExecReturn("The tool does not cross the selected faces");
    }
    try {
        split.Build();
    }
    catch (const Standard_Failure&) {
        return new App::DocumentObjectExecReturn("Split Face failed");
    }
    if (!split.IsDone()) {
        return new App::DocumentObjectExecReturn("Split Face failed");
    }
    setResults({Part::TopoShape(split.Shape())});
    return StdReturn;
}

// ---------------------------------------------------------------------------------------------

PROPERTY_SOURCE(Design::Emboss, Design::DressUp)

Emboss::Emboss()
{
    ADD_PROPERTY_TYPE(ProfileKeys, (), "Emboss", App::PropertyType(App::Prop_Output | App::Prop_Hidden),
                      "Signatures of the selected profiles");
    ADD_PROPERTY_TYPE(Profile, (nullptr), "Emboss", App::Prop_None, "Profiles (sketch areas, text) to emboss");
    ADD_PROPERTY_TYPE(Type, (0L), "Parameters", App::Prop_None, "Raised or engraved");
    Type.setEnums(EmbossEnums);
    ADD_PROPERTY_TYPE(Depth, (1.0), "Parameters", App::Prop_None, "Height or depth");
    Size.setStatus(App::Property::Hidden, true);
}

App::DocumentObjectExecReturn* Emboss::compute()
{
    if (Bodies.getSize() != 1 || BaseFeatures.getSize() != 1) {
        return new App::DocumentObjectExecReturn("Select a face of one body and a profile");
    }
    Part::Feature* sketch = nullptr;
    const char* reason = nullptr;
    const auto profiles = profileFaces(Profile, ProfileKeys, sketch, reason);
    if (profiles.empty()) {
        return new App::DocumentObjectExecReturn(reason);
    }
    const Part::TopoShape shape = baseShape(0);
    const auto faces = elements(shape, TopAbs_FACE);
    const double depth = Depth.getValue();
    if (faces.empty() || depth < Precision::Confusion()) {
        return new App::DocumentObjectExecReturn("Select the face to emboss on and a depth greater than zero");
    }
    // Profile senkrecht zur Skizze durch alles ziehen ...
    const double far = shape.getBoundBox().CalcDiagonalLength() * 2 + 10;
    Base::Vector3d sn;
    sketch->Placement.getValue().getRotation().multVec(Base::Vector3d(0, 0, 1), sn);
    const gp_Vec dir(sn.x * far, sn.y * far, sn.z * far);
    std::vector<Part::TopoShape> prisms;
    for (const auto& p : profiles) {
        gp_Trsf back;
        back.SetTranslation(-dir);
        prisms.emplace_back(BRepPrimAPI_MakePrism(BRepBuilderAPI_Transform(p.getShape(), back, Standard_True).Shape(),
                                                  dir * 2)
                                .Shape());
    }
    const Part::TopoShape tool = fuseAll(prisms, getDocument()->getStringHasher());
    // ... und mit einer Schicht der gewählten Flächen (außen bzw. innen, Dicke = Tiefe) schneiden
    const bool raised = Type.getValue() == 0;
    Part::TopoShape res = shape;
    try {
        for (const auto& face : faces) {
            Part::TopoShape skin(0, getDocument()->getStringHasher());
            skin.makeElementOffset(face, raised ? depth : -depth, 1e-6, false, false, 0, Part::JoinType::arc,
                                   Part::FillType::fill);
            Part::TopoShape part(0, getDocument()->getStringHasher());
            part.makeElementBoolean(Part::OpCodes::Common, {tool, skin});
            Part::TopoShape next(0, getDocument()->getStringHasher());
            if (raised) {
                next.makeElementFuse({res, part});
            }
            else {
                next.makeElementCut({res, part});
            }
            res = next;
        }
    }
    catch (const Standard_Failure&) {
        return new App::DocumentObjectExecReturn("Emboss failed: depth too large for the face?");
    }
    catch (const Base::Exception& e) {
        return new App::DocumentObjectExecReturn(e.what());
    }
    if (res.isNull() || !res.isValid()) {
        return new App::DocumentObjectExecReturn("Emboss failed");
    }
    setResults({res.makeElementRefine(nullptr, Part::RefineFail::shapeUntouched)});
    return StdReturn;
}

// ---------------------------------------------------------------------------------------------

namespace
{
/// Bezugsrahmen eines Elements in den Koordinaten seiner Komponente: Z = Normale (ebene Fläche), Achse
/// (Zylinderfläche, Kreiskante), Richtung (gerade Kante); Ursprung = Mitte bzw. Achspunkt bzw. Punkt
bool jointFrame(const App::PropertyLinkSub& link, Base::Placement& frame, bool& planar)
{
    App::DocumentObject* obj = link.getValue();
    if (!obj) {
        return false;
    }
    const auto& subs = link.getSubValues();
    const std::string sub = subs.empty() ? std::string() : subs.front();
    const TopoDS_Shape s = Part::Feature::getTopoShape(obj, Part::ShapeOption::ResolveLink | Part::ShapeOption::Transform
                                                           | Part::ShapeOption::NeedSubElement,
                                                       sub.empty() ? nullptr : sub.c_str())
                               .getShape();
    if (s.IsNull()) {
        return false;
    }
    gp_Pnt p;
    gp_Dir d = gp::DZ();
    planar = false;
    GProp_GProps props;
    switch (s.ShapeType()) {
        case TopAbs_VERTEX:
            p = BRep_Tool::Pnt(TopoDS::Vertex(s));
            break;
        case TopAbs_EDGE: {
            BRepGProp::LinearProperties(s, props);
            p = props.CentreOfMass();
            BRepAdaptor_Curve c(TopoDS::Edge(s));
            if (c.GetType() == GeomAbs_Line) {
                d = c.Line().Direction();
            }
            else if (c.GetType() == GeomAbs_Circle) {
                p = c.Circle().Location();
                d = c.Circle().Axis().Direction();
            }
            break;
        }
        case TopAbs_FACE: {
            BRepGProp::SurfaceProperties(s, props);
            p = props.CentreOfMass();
            BRepAdaptor_Surface surface(TopoDS::Face(s));
            if (surface.GetType() == GeomAbs_Plane) {
                d = surface.Plane().Axis().Direction();
                if (s.Orientation() == TopAbs_REVERSED) {
                    d.Reverse();
                }
                planar = true;
            }
            else if (surface.GetType() == GeomAbs_Cylinder) {
                const gp_Ax1 axis = surface.Cylinder().Axis();
                d = axis.Direction();
                p = axis.Location().Translated(gp_Vec(d) * gp_Vec(axis.Location(), p).Dot(gp_Vec(d)));
            }
            break;
        }
        default:
            return false;
    }
    frame = Base::Placement(Base::Vector3d(p.X(), p.Y(), p.Z()),
                            Base::Rotation(Base::Vector3d(0, 0, 1), Base::Vector3d(d.X(), d.Y(), d.Z())));
    return true;
}

/// übergeordnete Komponente (App::Part) eines Objekts, sonst nullptr
App::Part* parentPart(const App::DocumentObject* obj)
{
    for (auto in : obj->getInList()) {
        if (auto part = freecad_cast<App::Part*>(in); part && part->hasObject(obj)) {
            return part;
        }
    }
    return nullptr;
}
}  // namespace

PROPERTY_SOURCE(Design::Joint, App::DocumentObject)

Joint::Joint()
{
    ADD_PROPERTY_TYPE(Type, (0L), "Joint", App::Prop_None, "Rigid, revolute, slider or cylindrical");
    Type.setEnums(JointEnums);
    ADD_PROPERTY_TYPE(Moving, (nullptr), "Joint", App::Prop_None, "Component moved by this joint");
    ADD_PROPERTY_TYPE(Origin1, (nullptr), "Joint", App::Prop_None, "Snap point on the moving component");
    ADD_PROPERTY_TYPE(Origin2, (nullptr), "Joint", App::Prop_None, "Snap point to join to");
    ADD_PROPERTY_TYPE(Angle, (0.0), "Joint", App::Prop_None, "Rotation around the joint axis");
    ADD_PROPERTY_TYPE(Offset, (0.0), "Joint", App::Prop_None, "Distance along the joint axis");
    ADD_PROPERTY_TYPE(Flip, (false), "Joint", App::Prop_None, "Flip the moving component");
    ADD_PROPERTY_TYPE(Result, (Base::Placement()), "Joint", App::PropertyType(App::Prop_Output | App::Prop_ReadOnly),
                      "Placement of the moving component");
    ADD_PROPERTY_TYPE(Offset2, (0.0), "Joint", App::Prop_None, "Second distance in the plane (planar joint)");
    ADD_PROPERTY_TYPE(Angle2, (0.0), "Joint", App::Prop_None, "Pitch (ball joint)");
    ADD_PROPERTY_TYPE(Angle3, (0.0), "Joint", App::Prop_None, "Roll (ball joint)");
    ADD_PROPERTY_TYPE(Limited, (false), "Joint", App::Prop_None, "Keep angle and distance within limits");
    ADD_PROPERTY_TYPE(AngleMin, (-180.0), "Joint", App::Prop_None, "Smallest angle");
    ADD_PROPERTY_TYPE(AngleMax, (180.0), "Joint", App::Prop_None, "Largest angle");
    ADD_PROPERTY_TYPE(OffsetMin, (0.0), "Joint", App::Prop_None, "Smallest distance");
    ADD_PROPERTY_TYPE(OffsetMax, (50.0), "Joint", App::Prop_None, "Largest distance");
    ADD_PROPERTY_TYPE(Follows, (nullptr), "Joint", App::PropertyType(App::Prop_Hidden | App::Prop_Output),
                      "Component of the second snap point");
    Origin1.setScope(App::LinkScope::Global);
    Origin2.setScope(App::LinkScope::Global);
    Follows.setScope(App::LinkScope::Global);
    onChanged(&Type);  // Sichtbarkeit der Felder von Anfang an
}

bool Joint::turns() const
{
    const long t = Type.getValue();
    return t == Revolute || t == Cylindrical || t == PinSlot || t == Planar || t == Ball;
}

bool Joint::slides() const
{
    const long t = Type.getValue();
    return t == Slider || t == Cylindrical || t == PinSlot || t == Planar;
}

void Joint::onChanged(const App::Property* prop)
{
    if (prop == &Origin2 && !isRestoring()) {  // die Wurzel bewegt sich nie (und enthält den Joint: kein Kreis)
        App::Part* other = Origin2.getValue() ? componentOf(Origin2.getValue()) : nullptr;
        Follows.setValue(other && other != root(getDocument(), false) ? other : nullptr);
    }
    if (prop == &Type || prop == &Limited) {
        const long t = Type.getValue();
        Offset2.setStatus(App::Property::Hidden, t != Planar);
        Angle2.setStatus(App::Property::Hidden, t != Ball);
        Angle3.setStatus(App::Property::Hidden, t != Ball);
        for (App::Property* p : std::initializer_list<App::Property*> {&AngleMin, &AngleMax}) {
            p->setStatus(App::Property::Hidden, !Limited.getValue() || !turns());
        }
        for (App::Property* p : std::initializer_list<App::Property*> {&OffsetMin, &OffsetMax}) {
            p->setStatus(App::Property::Hidden, !Limited.getValue() || !slides());
        }
    }
    App::DocumentObject::onChanged(prop);
}

App::DocumentObjectExecReturn* Joint::execute()
{
    auto moving = freecad_cast<App::Part*>(Moving.getValue());
    Base::Placement f1, f2;
    bool planar1 = false, planar2 = false;
    if (!moving || !jointFrame(Origin1, f1, planar1) || !jointFrame(Origin2, f2, planar2)) {
        return new App::DocumentObjectExecReturn("Select a snap point on each component");
    }
    if (Design::componentOf(Origin1.getValue()) != moving) {
        return new App::DocumentObjectExecReturn("The first snap point must be on the moving component itself");
    }
    // Eine Komponente folgt genau einem Joint; der später angelegte meldet den Konflikt, statt still zu überschreiben
    for (auto other : getDocument()->getObjectsOfType(Joint::getClassTypeId())) {
        if (other != this && static_cast<Joint*>(other)->Moving.getValue() == moving
            && std::string(other->getNameInDocument()) < getNameInDocument()) {
            return new App::DocumentObjectExecReturn(std::string("This component already follows ") + other->Label.getValue()
                                                     + "; a component follows one joint");
        }
    }
    // Gegenstelle global: ihre Komponente kann selbst verschoben sein
    const Base::Placement target = Design::componentOf(Origin2.getValue())->globalPlacement() * f2;
    // zwei ebene Flächen liegen wie in Fusion aufeinander (Normalen gegenläufig); Flip kehrt das um
    Base::Placement flip;
    if ((planar1 && planar2) != Flip.getValue()) {
        flip = Base::Placement(Base::Vector3d(), Base::Rotation(Base::Vector3d(1, 0, 0), M_PI));
    }
    // Bewegung im Rahmen der Gegenstelle (Z = Achse bzw. Normale), mit Grenzen
    const auto clamp = [this](double v, const App::PropertyQuantity& lo, const App::PropertyQuantity& hi) {
        return Limited.getValue() ? std::clamp(v, std::min(lo.getValue(), hi.getValue()), std::max(lo.getValue(), hi.getValue()))
                                  : v;
    };
    const double angle = clamp(Angle.getValue(), AngleMin, AngleMax) * M_PI / 180.0;
    const double offset = clamp(Offset.getValue(), OffsetMin, OffsetMax);
    Base::Vector3d move;
    Base::Rotation turn(Base::Vector3d(0, 0, 1), angle);
    switch (Type.getValue()) {
        case Slider:
            move.z = offset;
            turn = Base::Rotation();
            break;
        case Revolute:
            break;
        case PinSlot:  // drehen um die Achse und im Schlitz (X) schieben
            move.x = offset;
            break;
        case Planar:  // in der Ebene schieben und um die Normale drehen
            move = Base::Vector3d(offset, Offset2.getValue(), 0);
            break;
        case Ball:  // Gieren, Nicken, Rollen um den Punkt
            turn.setYawPitchRoll(Angle.getValue(), Angle2.getValue(), Angle3.getValue());
            break;
        default:  // Rigid: feste Lage aus beiden Werten; Cylindrical: drehen und schieben
            move.z = offset;
            break;
    }
    const Base::Placement motion(move, turn);
    const Base::Placement global = target * motion * flip * f1.inverse();
    const App::Part* parent = parentPart(moving);
    Result.setValue(parent ? parent->globalPlacement().inverse() * global : global);
    return StdReturn;
}

void Joint::unsetupObject()
{
    // Komponente behält ihre letzte Lage, wird aber nicht mehr vom (gelöschten) Joint gesteuert
    if (auto moving = freecad_cast<App::Part*>(Moving.getValue())) {
        moving->setExpression(App::ObjectIdentifier(moving->Placement), nullptr);
    }
    App::DocumentObject::unsetupObject();
}

PROPERTY_SOURCE(Design::Note, App::DocumentObject)

Note::Note()
{
    ADD_PROPERTY_TYPE(Text, (""), "Note", App::Prop_NoRecompute, "Text of the note");
    ADD_PROPERTY_TYPE(Corner, (3L), "Note", App::Prop_NoRecompute, "Window corner it stays in: bit 0 right, bit 1 bottom");
    ADD_PROPERTY_TYPE(OffsetX, (12L), "Note", App::Prop_NoRecompute, "Horizontal distance to that corner");
    ADD_PROPERTY_TYPE(OffsetY, (12L), "Note", App::Prop_NoRecompute, "Vertical distance to that corner");
}

void Note::onBeforeChange(const App::Property* prop)
{
    if (prop != &Text && prop != &Corner && prop != &OffsetX && prop != &OffsetY && prop != &Visibility) {
        App::DocumentObject::onBeforeChange(prop);
    }
}

PROPERTY_SOURCE(Design::Scribble, App::GeoFeature)

Scribble::Scribble()
{
    // nichts davon braucht ein Neuberechnen: Striche ändern kein Modell, also auch kein "veraltet"-Abzeichen
    constexpr auto hidden = App::PropertyType(App::Prop_NoRecompute | App::Prop_Hidden);
    ADD_PROPERTY_TYPE(Points, (), "Scribble", hidden, "Points of all strokes, one after another");
    ADD_PROPERTY_TYPE(Widths, (), "Scribble", hidden, "Stroke width at each point (mm)");
    ADD_PROPERTY_TYPE(Counts, (), "Scribble", hidden, "Number of points of each stroke");
    ADD_PROPERTY_TYPE(Tools, (), "Scribble", hidden, "Tool of each stroke: 0 pencil, 1 pen, 2 marker");
    ADD_PROPERTY_TYPE(Kinds, (), "Scribble", hidden, "Shape of each stroke: 0 free, 1 line, 2 circle, 3 rectangle, 4 polygon, 5 ellipse, 6 fill");
    ADD_PROPERTY_TYPE(Colors, (), "Scribble", hidden, "Color of each stroke");
    ADD_PROPERTY_TYPE(Normals, (), "Scribble", hidden, "Normal of the sheet each stroke lies on");
    ADD_PROPERTY_TYPE(Sheet, (Base::Placement()), "Scribble", App::Prop_NoRecompute, "Current drawing sheet (its XY plane)");
    ADD_PROPERTY_TYPE(Tracing, (false), "Scribble", App::Prop_NoRecompute, "Tracing paper: the model shows through the sheet");
    Placement.setStatus(App::Property::Hidden, true);
}

std::vector<Scribble::Stroke> Scribble::strokes() const
{
    const auto& counts = Counts.getValues();
    const size_t n = counts.size();
    size_t total = 0;
    for (long c : counts) {
        total += size_t(std::max(0L, c));
    }
    if (Tools.getSize() != int(n) || Kinds.getSize() != int(n) || Colors.getSize() != int(n) || Normals.getSize() != int(n)
        || Points.getSize() != int(total) || Widths.getSize() != int(total)) {
        return {};
    }
    std::vector<Stroke> result(n);
    size_t at = 0;
    for (size_t i = 0; i < n; ++i) {
        Stroke& s = result[i];
        const auto count = size_t(std::max(0L, counts[i]));
        s.points.assign(Points.getValues().begin() + long(at), Points.getValues().begin() + long(at + count));
        s.widths.assign(Widths.getValues().begin() + long(at), Widths.getValues().begin() + long(at + count));
        s.tool = Tools[int(i)];
        s.kind = Kinds[int(i)];
        s.color = Colors[int(i)];
        s.normal = Normals[int(i)];
        at += count;
    }
    return result;
}

void Scribble::setStrokes(const std::vector<Stroke>& strokes)
{
    std::vector<Base::Vector3d> points, normals;
    std::vector<double> widths;
    std::vector<long> counts, tools, kinds;
    std::vector<Base::Color> colors;
    for (const Stroke& s : strokes) {
        points.insert(points.end(), s.points.begin(), s.points.end());
        widths.insert(widths.end(), s.widths.begin(), s.widths.end());
        counts.push_back(long(s.points.size()));
        tools.push_back(s.tool);
        kinds.push_back(s.kind);
        colors.push_back(s.color);
        normals.push_back(s.normal);
    }
    // Counts zuletzt: erst dann passen die Listen wieder zusammen (die Ansicht zeichnet nur zusammenpassende)
    Points.setValues(points);
    Widths.setValues(widths);
    Tools.setValues(tools);
    Kinds.setValues(kinds);
    Colors.setValues(colors);
    Normals.setValues(normals);
    Counts.setValues(counts);
}
