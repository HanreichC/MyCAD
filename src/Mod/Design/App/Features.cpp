// SPDX-License-Identifier: LGPL-2.1-or-later

#include "Features.h"

#include <App/Datums.h>
#include <App/Document.h>
#include <App/DocumentObjectGroup.h>
#include <App/Part.h>
#include <App/ObjectIdentifier.h>
#include <App/ExpressionParser.h>
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
#include "NoteParameters.h"
#include "Fits.h"
#include "PrintCheck.h"
#include "AssemblySolver.h"
#include <BRepExtrema_DistShapeShape.hxx>
#include <BRepOffsetAPI_MakeOffset.hxx>
#include <BRepPrimAPI_MakeRevol.hxx>
#include <Base/Interpreter.h>
#include <Mod/Part/App/Geometry.h>
#include <Mod/Part/App/TopoShapePy.h>
#include <Mod/Sketcher/App/SketchObject.h>
#include <IntCurvesFace_ShapeIntersector.hxx>
#include <gp_Lin.hxx>
#include <Mod/Part/App/ExtrusionHelper.h>
#include <Mod/Part/App/TopoShapeOpCode.h>

#include <BRepAlgoAPI_Splitter.hxx>
#include <BRepAdaptor_Surface.hxx>
#include <ShapeFix_Wireframe.hxx>
#include <ShapeUpgrade_UnifySameDomain.hxx>
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
#include <TopTools_ListOfShape.hxx>
#include <TopTools_IndexedDataMapOfShapeListOfShape.hxx>
#include <BRepAdaptor_Curve2d.hxx>
#include <BRepGProp_Face.hxx>
#include <cctype>
#include <set>
#include <thread>
#include <future>
#include <TopoDS_Iterator.hxx>
#include <gp_Ax1.hxx>
#include <gp_Ax2.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <GC_MakeArcOfCircle.hxx>
#include <GeomAPI_Interpolate.hxx>
#include <TColgp_HArray1OfPnt.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepOffsetAPI_MakePipe.hxx>
#include <BRepOffsetAPI_MakePipeShell.hxx>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeTorus.hxx>
#include <BRepTools.hxx>
#include <ElSLib.hxx>
#include <BRepAlgoAPI_Common.hxx>
#include <BRepClass_FaceClassifier.hxx>
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
#include <regex>
#include <iomanip>
#include <BRepBuilderAPI_MakeVertex.hxx>
#include <BRepExtrema_DistShapeShape.hxx>
#include <Mod/Sketcher/App/GeometryFacade.h>
#include <Mod/Sketcher/App/SketchObject.h>
#include <App/Expression.h>
#include <App/VarSet.h>
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
std::string mm(double v);
/// Schraube (0 Zylinderkopf ISO 4762, 1 Senkkopf ISO 10642, 2 Linsenkopf ISO 7380), stehend: Spitze auf z = 0, Kopf
/// oben; l unter dem Kopf (Senkkopf: über alles). Leer mit error, wenn es sie so nicht gibt
TopoDS_Shape screwSolid(int kind, const std::string& size, double l, std::string& error);
}  // namespace

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
// ab 5: Normteile (Plan 12.7); neue nur hinten anhängen, die Nummer steht in den Dateien
const char* PrimitiveEnums[] = {"Box", "Cylinder", "Sphere", "Torus", "Coil", "Socket Head Screw", "Countersunk Screw",
                                "Button Head Screw", "Hex Nut", "Washer", "Heat-Set Insert", "Ball Bearing", "Disc Magnet",
                                "Block Magnet", "Aluminum Profile", "Spur Gear", "Print-in-Place Hinge", "Snap Hook",
                                "Snap Hook Recess", nullptr};
const char* BearingEnums[] = {"623", "624", "625", "626", "608", "6000", "6001", "6200", nullptr};
const char* ProfileEnums[] = {"2020", "2040", "3030", nullptr};
const char* CenterEnums[] = {"Origin", "Body center", nullptr};
const char* RibEnums[] = {"Rib", "Web", nullptr};
const char* ChamferEnums[] = {"Equal distance", "Two distances", "Distance and angle", nullptr};
const char* EmbossEnums[] = {"Emboss", "Deboss", nullptr};
const char* JointEnums[] = {"Rigid", "Revolute", "Slider", "Cylindrical", "Pin-Slot", "Planar", "Ball", nullptr};
const App::PropertyIntegerConstraint::Constraints CountRange = {1, 1000, 1};

/// Flächen tragen Reste früherer Boolescher Schritte: Kanten kürzer als die Toleranz ihrer Ecken (ConceptKey: 0,000002 mm
/// bei 0,0007). Ihr Prisma schneidet sich selbst: Drücken/Ziehen wurde ungültig und ließ den Körper verschwinden, ein
/// geteiltes Profil machte die Wände von Basis zu Müll. Vor jedem Prisma solche Kanten entfernen; sonst die Fläche selbst
Part::TopoShape withoutTinyEdges(const Part::TopoShape& face)
{
    if (face.isNull()) {
        return face;
    }
    ShapeFix_Wireframe fix(face.getShape());
    fix.SetPrecision(std::max(BRep_Tool::MaxTolerance(face.getShape(), TopAbs_VERTEX), Precision::Confusion()));
    fix.ModeDropSmallEdges() = Standard_True;
    return fix.FixSmallEdges() ? Part::TopoShape(fix.Shape()) : face;
}

constexpr const char* LostProfile =
    "Profile gone: the sketch changed and the profile of this step no longer exists; edit the step and pick a profile";
constexpr const char* ModelChanged =
    "The model changed under this step; check that it still uses the right edges or faces: ";
constexpr const char* CutMisses = "This cut no longer touches the body and removes nothing; check the sketch or the "
                                  "distance";
/// Join ganz im Körper (Skizze liegt im Material, z. B. die Grundskizze unter dem Rand): vorher passierte still nichts
constexpr const char* JoinInside = "Adds nothing: the profile lies inside the body; set a start offset or extrude "
                                   "from a face on top";

/// Gewählte Profilflächen (leer = alle) und die zugehörige Skizze. Leerer Vektor mit Fehlertext bei Problemen.
/// Gewählte Profilflächen (leer = alle) und die zugehörige Skizze. Profile werden über ihre Signatur
/// (begrenzende Skizzenkanten) wiedergefunden; keys hält die Signaturen der gewählten Profile aktuell.
std::vector<Part::TopoShape> profileFaces(const App::PropertyLinkSub& profile, App::PropertyStringList& keys,
                                          Part::Feature*& sketch, const char*& error)
{
    auto profiles = freecad_cast<Profiles*>(profile.getValue());
    sketch = profiles ? freecad_cast<Part::Feature*>(profiles->Sketch.getValue()) : nullptr;
    if (!sketch) {
        // Hatte der Schritt schon ein Profil, ist seine Skizze gelöscht: wie ein verlorenes Profil überspringen
        error = keys.getValues().empty() ? "Select a profile" : LostProfile;
        return {};
    }
    const Part::TopoShape all = profiles->Shape.getShape();
    const auto& signatures = profiles->Signatures.getValues();
    const auto& subs = profile.getSubValues();
    std::vector<std::string> known = keys.getValues();
    known.resize(subs.size());
    std::vector<Part::TopoShape> faces;
    const auto faceOf = [](const Part::TopoShape& shape, size_t k) {
        return shape.getSubTopoShape(("Face" + std::to_string(k + 1)).c_str(), true);
    };
    const auto area = [](const TopoDS_Shape& shape) {
        GProp_GProps props;
        BRepGProp::SurfaceProperties(shape, props);
        return props.Mass();
    };
    // Teile eines geteilten Profils wieder zu einer Fläche verschmolzen (sonst blieb ihre Naht als Kante im Körper, und
    // eine Skizze, die die Wand projiziert, bekam andere Linien: Härtetest Seed 3, Extrusion006 −4,7 mm³)
    const auto addPieces = [&](const std::vector<size_t>& ks) {
        std::vector<Part::TopoShape> pieces;
        for (size_t k : ks) {
            pieces.push_back(faceOf(all, k));
        }
        if (pieces.size() > 1) {
            try {
                Part::TopoShape fused(0, all.Hasher);
                fused.makeElementFuse(pieces);
                // Flächen und Kanten vereinheitlichen: eine Linie durch ein Loch ließ seinen Rand sonst in Bögen zerlegt
                // (Projektion mit 15 statt 13 Linien, Bedingungen am Kreis widersprachen sich; Härtetest Seed 10)
                ShapeUpgrade_UnifySameDomain unify(fused.getShape(), true, true, false);
                unify.Build();
                // Bewusst ohne Entstehungsgeschichte: die Namen der Teilflächen sind Nummern aus dem Flächenteiler und
                // wechseln mit jeder Änderung. Mit Geschichte entstanden daraus Namen, die verfolgbar aussahen, es aber
                // nicht waren; Projektionen auf Körperkanten verloren ihre Kante ganz (Härtetest 2, 26.11.). Schlichte
                // Nummern gelten überall als unsicher und werden über die Lage geprüft
                const Part::TopoShape merged(unify.Shape());
                const auto mergedFaces = merged.getSubTopoShapes(TopAbs_FACE);
                if (!mergedFaces.empty() && mergedFaces.size() < pieces.size()) {
                    pieces = mergedFaces;
                }
            }
            catch (...) {
            }
        }
        faces.insert(faces.end(), pieces.begin(), pieces.end());
    };
    for (size_t i = 0; i < subs.size(); ++i) {
        std::string name = subs[i];
        // Geteiltes Profil: "alt|Teil|Teil". Gibt es das alte wieder (Skizze zurückgeändert), gilt es; sonst die Teile
        std::vector<std::string> split;
        {
            std::stringstream in(known[i]);
            for (std::string t; std::getline(in, t, '|');) {
                split.push_back(t);
            }
        }
        const std::string original = split.empty() ? known[i] : split.front();
        if (split.size() > 1 && std::ranges::find(signatures, original) == signatures.end()) {
            std::vector<std::string> wanted(split.begin() + 1, split.end()), have;
            std::vector<size_t> found;
            for (size_t k = 0; k < signatures.size(); ++k) {
                if (std::ranges::find(wanted, signatures[k]) != wanted.end()) {
                    found.push_back(k);
                    have.push_back(signatures[k]);
                }
            }
            std::ranges::sort(wanted);
            std::ranges::sort(have);
            if (have == wanted) {
                addPieces(found);
                continue;
            }
        }
        known[i] = original;
        const auto match = std::ranges::find(signatures, known[i]);
        if (!known[i].empty() && match != signatures.end() && std::ranges::count(signatures, known[i]) == 1) {
            name = "Face" + std::to_string(match - signatures.begin() + 1);
        }
        else if ((known[i].starts_with("g") || known[i].starts_with("x")) && match == signatures.end()) {
            // Geteilt (Linie quer, Kreis um ein Loch oder über den Rand): die neuen Flächen, die im alten Profil liegen
            // und es zusammen genau füllen. Über die Lage, nicht über die Kanten: ein Kreis über den Rand grenzt außen an
            // dieselben Kanten wie innen und wurde sonst mitgenommen (Härtetest ConceptKey). Die Teile in den Schlüssel,
            // damit es nach dem nächsten Rechnen und nach dem Laden genauso bleibt.
            // Alte Fläche(n): das Profil selbst oder, schon einmal geteilt, seine Teile (mehrmals hintereinander in
            // derselben Skizze gearbeitet: sonst fand die zweite Teilung nur das Original nicht und das Profil war weg)
            const auto& before = profiles->PreviousSignatures.getValues();
            const Part::TopoShape previous = profiles->PreviousShape.getShape();
            std::vector<std::string> oldSigs(split.begin(), split.end());
            if (oldSigs.empty()) {
                oldSigs.push_back(known[i]);
            }
            TopoDS_Compound old;
            BRep_Builder builder;
            builder.MakeCompound(old);
            double oldArea = 0;
            std::set<std::string> ownTokens;
            if (!previous.isNull()) {
                for (size_t k = 0; k < before.size(); ++k) {
                    if (std::ranges::find(oldSigs, before[k]) != oldSigs.end()) {
                        const TopoDS_Shape face = faceOf(previous, k).getShape();
                        builder.Add(old, face);
                        oldArea += area(face);
                        std::stringstream in(before[k]);
                        for (std::string t; std::getline(in, t, ',');) {
                            ownTokens.insert(t);
                        }
                    }
                }
            }
            if (oldArea > 0) {
                std::vector<size_t> inside;
                double sum = 0;  // Teile und neue Inseln zusammen füllen das alte Profil
                const auto mineTokens = [&](const std::string& sig) {
                    std::stringstream in(sig);
                    for (std::string t; std::getline(in, t, ',');) {
                        if (ownTokens.contains(t)) {
                            return true;
                        }
                    }
                    return false;
                };
                for (size_t k = 0; k < signatures.size(); ++k) {
                    const TopoDS_Shape face = faceOf(all, k).getShape();
                    const double a = area(face);
                    if (a > 0 && area(BRepAlgoAPI_Common(face, old).Shape()) > 0.999 * a) {
                        sum += a;
                        // nur neue Kanten: eine neue Insel (Kreis, Versatz hinein), bleibt ein Loch (wie Fusion); sie
                        // zählt aber zur Fläche, sonst galt das ganze Profil als verloren (ConceptKey)
                        if (mineTokens(signatures[k])) {
                            inside.push_back(k);
                        }
                    }
                }
                if (!inside.empty() && std::abs(sum - oldArea) <= 1e-6 * (1 + oldArea)) {
                    std::string key = known[i];
                    for (size_t k : inside) {
                        key += "|" + signatures[k];
                    }
                    addPieces(inside);
                    known[i] = inside.size() == 1 ? signatures[inside.front()] : key;
                    continue;
                }
            }
            // Signatur aus festen IDs, aber kein exakter Treffer: das ähnlichste Profil ist dasselbe, nur verändert
            // (Kreis hinein = Ring). Ähnlich heißt: viele gemeinsame Kanten im Verhältnis zu allen (Jaccard). Nur die
            // Anzahl zu zählen zog jede Lasche auf die große Innenfläche, die mehr ihrer Kanten berührt (ConceptKey).
            // Teilt keines eine Kante, ist es weg; dann nicht auf die alte Nummer zurückfallen, die jetzt ein fremdes
            // Profil trägt.
            const auto tokens = [](const std::string& sig) {
                std::set<std::string> out;
                std::stringstream in(sig);
                for (std::string t; std::getline(in, t, ',');) {
                    out.insert(t);
                }
                return out;
            };
            const auto mine = tokens(known[i]);
            // Phase 14, geteilt (Linie quer durch das Profil, Kreis um ein vorhandenes Loch): Teilflächen, die nur über
            // neue Kanten aneinanderstoßen und deren Außenrand zusammen genau die alten Kanten sind, füllen das alte
            // Profil: alle nehmen, wie zwei gewählte Profile. Jedes Teil hat eine alte und eine neue Kante; nur alte =
            // ein anderes Profil (das Loch selbst), nur neue = eine neue Insel (Kreis hinein bleibt ein Ring).
            // Kandidaten mit einer neuen Kante, die keine andere teilt, grenzen nach außen und fallen weg. Vorher nur bei
            // Gleichstand: ein 3,8-mm-Kreis um ein 2,6-mm-Loch nahm das Quadrat ohne den Ring, das Loch wuchs (ConceptKey).
            {
                std::vector<std::pair<size_t, std::set<std::string>>> parts;
                for (size_t k = 0; k < signatures.size(); ++k) {
                    auto theirs = tokens(signatures[k]);
                    if (std::ranges::any_of(theirs, [&](const std::string& t) { return mine.contains(t); })
                        && std::ranges::any_of(theirs, [&](const std::string& t) { return !mine.contains(t); })) {
                        parts.emplace_back(k, std::move(theirs));
                    }
                }
                for (bool changed = true; changed;) {
                    changed = false;
                    std::map<std::string, int> extraUse;
                    for (const auto& [k, theirs] : parts) {
                        for (const auto& t : theirs) {
                            extraUse[t] += mine.contains(t) ? 0 : 1;
                        }
                    }
                    const auto outward = std::ranges::find_if(parts, [&](const auto& part) {
                        return std::ranges::any_of(part.second, [&](const std::string& t) {
                            return !mine.contains(t) && extraUse[t] < 2;
                        });
                    });
                    if (outward != parts.end()) {
                        parts.erase(outward);
                        changed = true;
                    }
                }
                std::set<std::string> outer;
                for (const auto& [k, theirs] : parts) {
                    for (const auto& t : theirs) {
                        if (mine.contains(t)) {
                            outer.insert(t);
                        }
                    }
                }
                if (parts.size() >= 2 && outer == mine) {
                    std::vector<size_t> ks;
                    for (const auto& [k, theirs] : parts) {
                        ks.push_back(k);
                    }
                    addPieces(ks);
                    continue;  // Signatur bleibt die alte: beim nächsten Neuberechnen wieder so
                }
            }
            double best = 0;
            size_t bestIdx = 0, ties = 0;
            // Hauchdünne Bereiche (Spalt zwischen fast deckungsgleichen Linien) sind Zeichenungenauigkeiten, nie gemeint:
            // keine Kandidaten. Sonst gewann ein Splitter mit denselben Linien gegen die Lasche daneben (ConceptKey).
            // Maß ist die mittlere Breite (2 Fläche / Umfang) gegen die Größe der Skizze; ein schmaler Rahmen bleibt
            const double size = all.getBoundBox().CalcDiagonalLength();
            const auto sliver = [&all, size](size_t k) {
                const TopoDS_Shape face = all.getSubShape(("Face" + std::to_string(k + 1)).c_str(), true);
                GProp_GProps area, rim;
                BRepGProp::SurfaceProperties(face, area);
                BRepGProp::LinearProperties(face, rim);
                return rim.Mass() > 0 && 2 * area.Mass() / rim.Mass() < 1e-4 * size;
            };
            for (size_t k = 0; k < signatures.size(); ++k) {
                if (sliver(k)) {
                    continue;
                }
                const auto theirs = tokens(signatures[k]);
                const size_t shared = std::ranges::count_if(mine, [&](const std::string& t) { return theirs.contains(t); });
                const double similar = double(shared) / double(mine.size() + theirs.size() - shared);
                if (similar > best + 1e-12) {
                    best = similar, bestIdx = k, ties = 1;
                }
                else if (shared > 0 && std::abs(similar - best) <= 1e-12) {
                    ++ties;
                }
            }
            if (best == 0 || ties > 1) {
                faces.emplace_back();
                continue;
            }
            name = "Face" + std::to_string(bestIdx + 1);
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
        // Gewählte Profile gibt es nach einer Änderung der Skizze nicht mehr: eigener Text, Feature::execute macht
        // daraus eine Warnung und reicht den Körper durch (sonst blockierte der Fehler alle Schritte danach)
        // Hatte der Schritt ein Profil, ist es verloren (Warnung, der Körper geht durch), auch wenn die Skizze gerade
        // gar keins mehr schließt (projizierte Kanten weg): als Fehler blockierte es alles danach (ConceptKey)
        error = subs.empty() ? "Sketch has no closed profile" : LostProfile;
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
    // Größen, die ISO 273 nicht nennt (dritte Wahl wie M9, M11, M15 …): Spiel zwischen den Nachbarn der Tabelle
    // geradlinig verteilt; über das Ende der Tabelle hinaus wie ihr letzter Eintrag
    if (standard <= 2) {
        const double(*below)[4] = nullptr;
        const double(*above)[4] = nullptr;
        for (const auto& row : PartDesign::Hole::metricHoleDiameters) {
            if (row[0] < t.diameter && (!below || row[0] > (*below)[0])) {
                below = &row;
            }
            if (row[0] > t.diameter && (!above || row[0] < (*above)[0])) {
                above = &row;
            }
        }
        if (below || above) {
            const auto play = [fit](const double(*r)[4]) { return (*r)[1 + fit] - (*r)[0]; };
            const double k = below && above ? (t.diameter - (*below)[0]) / ((*above)[0] - (*below)[0]) : 0;
            const double extra = below && above ? play(below) + k * (play(above) - play(below)) : play(below ? below : above);
            return t.diameter + extra;
        }
    }
    return t.diameter * (1.06 + 0.06 * fit);  // ponytail: Zoll-Größen außerhalb der Tabelle, Näherung
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

/// Senkung einer Schraubennorm für ein Gewinde wie "M3x0.5": (Durchmesser, Tiefe); nullptr ohne Eintrag
const std::pair<double, double>* headSize(const std::string& screw, const std::string& designation,
                                          bool* countersink = nullptr, double* angle = nullptr)
{
    for (const auto& h : headTables()) {
        if (h.name == screw && h.sizes.contains(designation)) {
            if (countersink) {
                *countersink = h.countersink;
            }
            if (angle) {
                *angle = h.angle;
            }
            return &h.sizes.at(designation);
        }
    }
    return nullptr;
}

/// Zylinderfläche einer Welle (Normale zeigt von der Achse weg), sonst einer Bohrung. Die Orientierung allein hängt
/// davon ab, wie die Fläche entstand.
bool isShaftFace(const TopoDS_Face& face)
{
    BRepAdaptor_Surface surface(face);
    const gp_Ax1 axis = surface.Cylinder().Axis();
    gp_Pnt mid;
    gp_Vec du, dv;
    surface.D1((surface.FirstUParameter() + surface.LastUParameter()) / 2,
               (surface.FirstVParameter() + surface.LastVParameter()) / 2, mid, du, dv);
    gp_Vec normal = du.Crossed(dv);
    if (face.Orientation() == TopAbs_REVERSED) {
        normal.Reverse();
    }
    const gp_Vec along(axis.Direction());
    const gp_Vec fromAxis(axis.Location().Translated(along * gp_Vec(axis.Location(), mid).Dot(along)), mid);
    return normal.Dot(fromAxis) > 0;
}

/// Flächen versetzen wie Fusions Offset Face (positiv: aus dem Körper heraus), die Nachbarn passen sich an
bool offsetFaces(const TopoDS_Shape& shape, const std::vector<std::pair<TopoDS_Face, double>>& faces,
                 Part::TopoShape& out)
{
    BRepOffset_MakeOffset offset;
    offset.Initialize(shape, 0.0, 1e-6, BRepOffset_Skin, Standard_False, Standard_False, GeomAbs_Intersection);
    for (const auto& [face, d] : faces) {
        offset.SetOffsetOnFace(face, d);
    }
    try {
        offset.MakeOffsetShape();
    }
    catch (const Standard_Failure&) {
        return false;
    }
    if (!offset.IsDone() || offset.Shape().IsNull()) {
        return false;
    }
    out = Part::TopoShape(offset.Shape());
    return out.isValid() && out.countSubShapes(TopAbs_SOLID) > 0;
}

/// Bohrung ab ax (liegt lead über der Fläche) mit Senkung: type 1 Zylinder-, 2 Kegelsenkung (Radius head)
std::vector<Part::TopoShape> holeShape(const gp_Ax2& ax, double r, double depth, long type, double head,
                                       double headDepth, double angle, double lead)
{
    std::vector<Part::TopoShape> parts {Part::TopoShape(BRepPrimAPI_MakeCylinder(ax, r, depth).Shape())};
    if (type == 1 && head > r) {
        parts.emplace_back(BRepPrimAPI_MakeCylinder(ax, head, headDepth + lead).Shape());
    }
    else if (type == 2 && head > r) {
        const double h = head / std::tan(angle * M_PI / 360.0);
        parts.emplace_back(BRepPrimAPI_MakeCone(ax, head, 0, h + lead).Shape());
    }
    return parts;
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
        // Körper, den es am Marker noch nicht gibt (sein Erzeuger ist zurückgerollt): nichts zu verändern. Ein leerer
        // Vorzustand ließ BaseFeatures.setValues werfen (Zufalls-Workflow, Seed 30)
        if (App::DocumentObject* state = stateAtMarker(b)) {
            objs.push_back(b);
            bases.push_back(state);
        }
    }
    feature->Bodies.setValues(objs);
    feature->BaseFeatures.setValues(bases);
    for (size_t i = 0; i < objs.size(); ++i) {
        auto body = static_cast<Body*>(objs[i]);
        rewireUsers(bases[i], feature, body, feature);  // eingefügt: spätere Features bauen auf diesem auf
        if (body->Tip.getValue() == bases[i]) {
            body->Tip.setValue(feature);
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

namespace
{
void eraseAt(App::PropertyLinkList& list, size_t i)
{
    auto values = list.getValues();
    if (i < values.size()) {
        values.erase(values.begin() + long(i));
        list.setValues(values);
    }
}

/// Body löschen: Schritte nur auf ihm gehen mit, Schritte auf mehreren Bodies verlieren ihn; Bodies, die es nur durch
/// ihn gibt (Teile seiner Teilung, Spiegel- und Musterkopien), gehen auch. Skizzen, die nur die entfernten Schritte
/// gebraucht haben oder auf ihm lagen, bleiben und werden wieder eingeblendet (wie Fusion; man will sie neu benutzen).
void removeBody(Design::Body* body)
{
    using namespace Design;
    App::Document* doc = body->getDocument();
    const std::string name = body->getNameInDocument();
    static const Base::Type sketchType = Base::Type::fromName("Sketcher::SketchObject");
    std::vector<std::string> sketches;
    const auto remember = [&](App::DocumentObject* obj) {  // benutzte und darauf gezeichnete Skizzen
        auto links = obj->getOutList();
        const auto& in = obj->getInList();
        links.insert(links.end(), in.begin(), in.end());
        for (auto o : links) {
            if (auto p = freecad_cast<Profiles*>(o)) {
                o = p->Sketch.getValue();
            }
            if (o && o->isDerivedFrom(sketchType)) {
                sketches.emplace_back(o->getNameInDocument());
            }
        }
    };
    const auto remove = [&](Feature* f) {
        remember(f);
        removeFromTimeline(f);
    };
    remember(body);
    std::vector<std::string> steps;
    for (auto obj : timeline(doc)) {
        steps.emplace_back(obj->getNameInDocument());
    }
    // von hinten: spätere Schritte bauen auf früheren auf; der erzeugende Schritt nimmt den Body mit
    for (auto it = steps.rbegin(); it != steps.rend() && doc->getObject(name.c_str()); ++it) {
        auto f = freecad_cast<Feature*>(doc->getObject(it->c_str()));
        if (!f) {
            continue;
        }
        App::PropertyLinkList *sources = nullptr, *states = nullptr;
        if (auto m = freecad_cast<Mirror*>(f)) {
            sources = &m->SourceBodies;
            states = &m->SourceFeatures;
        }
        else if (auto p = freecad_cast<Pattern*>(f)) {
            sources = &p->SourceBodies;
            states = &p->SourceFeatures;
        }
        auto combine = freecad_cast<Combine*>(f);
        if (combine) {
            const auto& tools = combine->ToolBodies.getValues();
            if (const size_t t = std::ranges::find(tools, body) - tools.begin(); t < tools.size()) {
                if (tools.size() == 1) {
                    remove(f);
                    continue;
                }
                eraseAt(combine->ToolBodies, t);
                eraseAt(combine->ToolFeatures, t);
            }
        }
        const auto bodies = f->Bodies.getValues();
        if (sources) {  // Spiegeln, Muster: Bodies[s] ist die Kopie von SourceBodies[s]
            const auto& src = sources->getValues();
            const size_t s = std::ranges::find(src, body) - src.begin();
            if (s < src.size() && s < bodies.size()) {
                if (auto copy = freecad_cast<Body*>(bodies[s])) {
                    removeBody(copy);
                }
                continue;
            }
        }
        const size_t i = std::ranges::find(bodies, body) - bodies.begin();
        if (i >= bodies.size()) {
            continue;
        }
        if (i == 0 && freecad_cast<Split*>(f)) {
            for (size_t j = 1; j < bodies.size(); ++j) {
                if (auto piece = freecad_cast<Body*>(bodies[j])) {
                    removeBody(piece);
                }
            }
        }
        if (f->Bodies.getSize() == 1) {
            remove(f);
            continue;
        }
        if (auto split = freecad_cast<Split*>(f); split && i > 0) {
            // Body i hat das i-te noch nicht gelöschte Teil: dieses Teil künftig auslassen
            auto dropped = split->Dropped.getValues();
            long piece = -1;
            for (long seen = -1; seen < long(i);) {
                ++piece;
                if (std::ranges::find(dropped, piece) == dropped.end()) {
                    ++seen;
                }
            }
            dropped.push_back(piece);
            split->Dropped.setValues(dropped);
        }
        eraseAt(f->Bodies, i);
        eraseAt(f->BaseFeatures, i);
        if (sources) {
            eraseAt(*sources, i);
            eraseAt(*states, i);
        }
        if (auto imported = freecad_cast<Import*>(f)) {
            auto parts = Import::pieces(imported->Imported.getShape());
            if (i < parts.size()) {
                parts.erase(parts.begin() + long(i));
                imported->Imported.setValue(Part::TopoShape().makeElementCompound(parts));
            }
        }
        // (ein Teil einer Teilung merkt sich die Teilung als gelöscht, siehe oben: die Teile dahinter rücken nicht auf)
    }
    if (doc->getObject(name.c_str())) {
        doc->removeObject(name.c_str());
    }
    const auto used = [](App::DocumentObject* o) {
        return o && std::ranges::any_of(o->getInList(), [](auto u) { return u->template isDerivedFrom<Feature>(); });
    };
    for (const auto& n : sketches) {
        auto sketch = doc->getObject(n.c_str());
        if (sketch && !used(sketch) && !used(Profiles::forSketch(sketch))) {
            sketch->Visibility.setValue(true);
        }
    }
}

constexpr const char* FaceGone = "Face gone: the step this sketch was drawn on was deleted; it stays where it was";

/// Fläche face eines gelöschten Schritts im Zustand davor (before): dieselbe (Schwerpunkt + Größe) oder, weil einer
/// Skizze die Ebene genügt, die nächste ebene Fläche in derselben Ebene und Richtung (eine Rundung oder Fase am Rand
/// ändert die Größe der Fläche).
/// Unter mehreren Flächen in der Ebene gewinnt die, die die alte am meisten überdeckt; nur ohne Überdeckung die nächste.
std::string faceBefore(const TopoDS_Shape& before, const TopoDS_Shape& face)
{
    std::string name = Design::elementName(before, face);
    if (!name.empty() || face.IsNull() || face.ShapeType() != TopAbs_FACE) {
        return name;
    }
    const auto normal = [](const TopoDS_Face& f, gp_Pln& pln) {
        BRepAdaptor_Surface surface(f);
        if (surface.GetType() != GeomAbs_Plane) {
            return false;
        }
        pln = surface.Plane();
        if (f.Orientation() == TopAbs_REVERSED) {
            pln.SetAxis(pln.Axis().Reversed());
        }
        return true;
    };
    gp_Pln plane, other;
    if (!normal(TopoDS::Face(face), plane)) {
        return name;
    }
    GProp_GProps props;
    BRepGProp::SurfaceProperties(face, props);
    const TopoDS_Vertex centre = BRepBuilderAPI_MakeVertex(props.CentreOfMass());
    TopTools_IndexedMapOfShape faces;
    TopExp::MapShapes(before, TopAbs_FACE, faces);
    double best = Precision::Infinite(), overlap = 0;
    for (int i = 1; i <= faces.Extent(); ++i) {
        if (!normal(TopoDS::Face(faces(i)), other) || !other.Axis().Direction().IsEqual(plane.Axis().Direction(), Precision::Angular())
            || plane.Distance(other.Location()) > Precision::Confusion()) {
            continue;
        }
        // zwei getrennte Flächen in derselben Ebene (z. B. durch eine Nut geteilt): die mit der größten Überdeckung
        GProp_GProps shared;
        BRepAlgoAPI_Common common(face, faces(i));
        if (common.IsDone()) {
            BRepGProp::SurfaceProperties(common.Shape(), shared);
        }
        if (shared.Mass() > overlap + 1e-9) {
            overlap = shared.Mass();
            name = "Face" + std::to_string(i);
            continue;
        }
        BRepExtrema_DistShapeShape dist(centre, faces(i));
        if (overlap <= 0 && dist.IsDone() && dist.Value() < best) {
            best = dist.Value();
            name = "Face" + std::to_string(i);
        }
    }
    return name;
}

/// Skizzen auf einer Fläche von gone (Feature oder Body, wird gleich gelöscht) an dieselbe Fläche in einem der Zustände
/// before hängen. Gibt es sie dort nicht (gone hat sie erzeugt), bleibt die Skizze an ihrem Platz und bekommt eine
/// Warnung für die Timeline; vorher löste sie sich still von der Fläche.
void reattachSketches(Part::Feature* gone, const std::vector<App::DocumentObject*>& before)
{
    const auto users = gone->getInList();  // Kopie: das Umhängen ändert die Liste
    for (auto user : users) {
        auto sketch = freecad_cast<Sketcher::SketchObject*>(user);
        if (!sketch) {
            continue;
        }
        auto objs = sketch->AttachmentSupport.getValues();
        auto subs = sketch->AttachmentSupport.getSubValues();
        bool moved = false, lost = false;
        for (size_t i = 0; i < objs.size() && i < subs.size(); ++i) {
            if (objs[i] != gone) {
                continue;
            }
            const TopoDS_Shape face = gone->Shape.getShape().getSubShape(subs[i].c_str(), true);
            std::string name;
            for (auto base : before) {
                auto before = freecad_cast<Part::Feature*>(base);
                if (before && name.empty() && !face.IsNull()) {
                    name = faceBefore(before->Shape.getShape().getShape(), face);
                    objs[i] = base;
                }
            }
            lost = lost || name.empty();
            moved = moved || !name.empty();
            subs[i] = name;
        }
        if (moved && !lost) {
            sketch->AttachmentSupport.setValues(objs, subs);
        }
        if (lost) {
            auto warning = freecad_cast<App::PropertyString*>(sketch->getPropertyByName("Warning"));
            if (!warning) {
                warning = static_cast<App::PropertyString*>(sketch->addDynamicProperty(
                    "App::PropertyString", "Warning", "Design", "Hint without an error (stays until confirmed)", App::Prop_Hidden));
            }
            warning->setValue(FaceGone);
        }
    }
}
}  // namespace

Design::DeletionImpact Design::deletionImpact(App::DocumentObject* obj)
{
    DeletionImpact impact;
    if (!obj) {
        return impact;
    }
    const auto add = [](std::vector<App::DocumentObject*>& list, App::DocumentObject* o) {
        if (std::ranges::find(list, o) == list.end()) {
            list.push_back(o);
        }
    };
    static const std::set<std::string> chainLinks {"BaseFeatures", "ToolFeatures", "SourceFeatures", "Bodies",
                                                   "ToolBodies", "SourceBodies"};
    if (auto body = freecad_cast<Body*>(obj)) {
        // wie removeBody: eigene Schritte gehen still mit (das erwartet man); genannt wird, was darüber hinaus geschieht
        std::set<App::DocumentObject*> own;
        for (App::DocumentObject* item : timeline(body->getDocument())) {
            auto f = freecad_cast<Feature*>(item);
            if (!f) {
                continue;
            }
            const auto& bodies = f->Bodies.getValues();
            if (bodies.size() == 1 && bodies.front() == body) {
                own.insert(f);
            }
            if (auto combine = freecad_cast<Combine*>(f)) {
                const auto& tools = combine->ToolBodies.getValues();
                if (tools.size() == 1 && tools.front() == body) {
                    own.insert(f);
                    add(impact.bodies, f);  // ein Schritt eines anderen Körpers verschwindet
                }
            }
            App::PropertyLinkList* sources = nullptr;
            if (auto m = freecad_cast<Mirror*>(f)) {
                sources = &m->SourceBodies;
            }
            else if (auto p = freecad_cast<Pattern*>(f)) {
                sources = &p->SourceBodies;
            }
            if (sources) {  // Kopien dieses Körpers
                const auto& src = sources->getValues();
                const size_t s = std::ranges::find(src, body) - src.begin();
                if (s < src.size() && s < bodies.size()) {
                    add(impact.bodies, bodies[s]);
                }
            }
            if (freecad_cast<Split*>(f) && !bodies.empty() && bodies.front() == body) {
                for (size_t j = 1; j < bodies.size(); ++j) {  // die anderen Teile einer Teilung
                    add(impact.bodies, bodies[j]);
                }
            }
        }
        std::vector<App::DocumentObject*> sources {body};
        sources.insert(sources.end(), own.begin(), own.end());
        for (App::DocumentObject* source : sources) {
            for (App::DocumentObject* user : source->getInList()) {
                if (user == body || own.contains(user) || user->isDerivedFrom<Body>() || user->isDerivedFrom<Profiles>()
                    || user->isDerivedFrom<App::DocumentObjectGroup>() || user->isDerivedFrom<App::Part>()) {
                    continue;
                }
                if (auto sketch = freecad_cast<Sketcher::SketchObject*>(user)) {
                    // auf einer Fläche des Körpers: geht still mit, wenn nur eigene Schritte sie nutzen
                    std::vector<App::DocumentObject*> users = sketch->getInList();
                    if (auto profiles = Profiles::forSketch(sketch)) {
                        const auto& more = profiles->getInList();
                        users.insert(users.end(), more.begin(), more.end());
                    }
                    const bool onlyOwn = std::ranges::all_of(users, [&](App::DocumentObject* u) {
                        return own.contains(u) || !u->isDerivedFrom<Feature>();
                    });
                    const auto& supports = sketch->AttachmentSupport.getValues();
                    if (!onlyOwn && std::ranges::find(supports, source) != supports.end()) {
                        add(impact.sketches, sketch);
                    }
                    continue;
                }
                std::vector<App::Property*> props;
                user->getPropertyList(props);
                for (App::Property* prop : props) {
                    const auto links = user->getOutListOfProperty(prop);
                    if (!chainLinks.contains(prop->getName()) && std::ranges::find(links, source) != links.end()) {
                        add(impact.broken, user);  // z. B. Bis-Fläche, Gelenk an einer Fläche des Körpers
                        break;
                    }
                }
            }
        }
        return impact;
    }
    // Schritte, die obj (bzw. das Profil einer Skizze) anders als über die Kette eines Körpers nutzen
    std::vector<App::DocumentObject*> sources {obj};
    if (auto profiles = Profiles::forSketch(obj)) {
        sources.push_back(profiles);
    }
    const std::set<std::string>& chain = chainLinks;
    for (App::DocumentObject* source : sources) {
        for (App::DocumentObject* user : source->getInList()) {
            if (user == obj || !user->isDerivedFrom<Feature>()) {
                continue;
            }
            std::vector<App::Property*> props;
            user->getPropertyList(props);
            for (App::Property* prop : props) {
                const auto links = user->getOutListOfProperty(prop);
                if (!chain.contains(prop->getName()) && std::ranges::find(links, source) != links.end()) {
                    add(impact.broken, user);
                    break;
                }
            }
        }
    }
    auto feature = freecad_cast<Feature*>(obj);
    if (!feature) {
        return impact;
    }
    // Körper, die es nur durch diesen Schritt gibt, und Skizzen auf einer Fläche, die es davor nicht gibt
    const auto bodies = feature->Bodies.getValues();
    const auto bases = feature->BaseFeatures.getValues();
    for (size_t i = 0; i < bodies.size(); ++i) {
        auto body = freecad_cast<Body*>(bodies[i]);
        if (body && body->Tip.getValue() == feature && (i >= bases.size() || !bases[i])) {
            add(impact.bodies, body);
            for (App::DocumentObject* user : body->getInList()) {
                if (user->isDerivedFrom<Sketcher::SketchObject>()) {
                    add(impact.sketches, user);
                }
            }
        }
    }
    for (App::DocumentObject* user : feature->getInList()) {
        auto sketch = freecad_cast<Sketcher::SketchObject*>(user);
        if (!sketch) {
            continue;
        }
        const auto& objs = sketch->AttachmentSupport.getValues();
        const auto& subs = sketch->AttachmentSupport.getSubValues();
        for (size_t i = 0; i < objs.size() && i < subs.size(); ++i) {
            if (objs[i] != feature) {
                continue;
            }
            const TopoDS_Shape face = feature->Shape.getShape().getSubShape(subs[i].c_str(), true);
            bool kept = false;
            for (auto base : bases) {
                auto before = freecad_cast<Part::Feature*>(base);
                kept = kept || (before && !face.IsNull() && !faceBefore(before->Shape.getShape().getShape(), face).empty());
            }
            if (!kept) {
                add(impact.sketches, sketch);
            }
        }
    }
    return impact;
}

void Design::removeFromTimeline(App::DocumentObject* obj)
{
    if (auto body = freecad_cast<Body*>(obj)) {
        removeBody(body);
        return;
    }
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
    reattachSketches(feature, feature->BaseFeatures.getValues());
    const auto orphans = detachFromBodies(feature);
    doc->removeObject(feature->getNameInDocument());
    for (const auto& name : orphans) {
        if (auto body = freecad_cast<Body*>(doc->getObject(name.c_str()))) {
            reattachSketches(body, {});  // Skizze direkt auf dem Body, den es ohne diesen Schritt nicht gibt
        }
        doc->removeObject(name.c_str());
    }
}

/// Name ("FaceN", "EdgeN", "VertexN") des Elements in shape, das geometrisch element entspricht (Schwerpunkt + Größe).
/// Passen mehrere (deckungsgleich), entscheidet erst die topologische Gleichheit, dann die Richtung (Normale bzw. Lauf
/// der Kante); erst danach der erste Treffer.
std::string Design::sameFaceBefore(const TopoDS_Shape& before, const TopoDS_Shape& face)
{
    return faceBefore(before, face);
}

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
    std::vector<int> matches;
    for (int i = 1; i <= all.Extent(); ++i) {
        const GProp_GProps p = props(all(i));
        if (std::abs(p.Mass() - ref.Mass()) < 1e-6 * (1 + ref.Mass())
            && p.CentreOfMass().Distance(ref.CentreOfMass()) < 1e-6) {
            matches.push_back(i);
        }
    }
    if (matches.size() > 1) {
        // Richtung: Flächennormale (mit Orientierung) bzw. Anfang -> Ende der Kante
        const auto direction = [type](const TopoDS_Shape& s) {
            if (type == TopAbs_FACE) {
                BRepAdaptor_Surface surface(TopoDS::Face(s));
                const double u = (surface.FirstUParameter() + surface.LastUParameter()) / 2;
                const double v = (surface.FirstVParameter() + surface.LastVParameter()) / 2;
                gp_Pnt p;
                gp_Vec du, dv;
                surface.D1(u, v, p, du, dv);
                gp_Vec n = du.Crossed(dv);
                return s.Orientation() == TopAbs_REVERSED ? n.Reversed() : n;
            }
            if (type == TopAbs_EDGE) {
                BRepAdaptor_Curve curve(TopoDS::Edge(s));
                return gp_Vec(curve.Value(curve.FirstParameter()), curve.Value(curve.LastParameter()));
            }
            return gp_Vec();
        };
        for (int i : matches) {
            if (all(i).IsPartner(element)) {
                return prefix + std::to_string(i);
            }
        }
        const gp_Vec want = direction(element);
        for (int i : matches) {
            const gp_Vec have = direction(all(i));
            if (want.Magnitude() > 1e-12 && have.Magnitude() > 1e-12 && want.IsParallel(have, 1e-6) && want.Dot(have) > 0) {
                return prefix + std::to_string(i);
            }
        }
    }
    return matches.empty() ? std::string() : prefix + std::to_string(matches.front());
}

/// Bezug auf einen Body durch seinen Timeline-Zustand ersetzen (das Feature, das ihn gerade erzeugt hat).
/// Sonst entsteht ein Kreis, sobald ein Feature aus einer Skizze/Ebene darauf denselben Body verändert.
void Design::stableRef(App::DocumentObject*& obj, std::string& element)
{
    auto body = freecad_cast<Body*>(obj);
    if (!body || element.empty()) {
        return;
    }
    // Der Body zeigt den letzten gelungenen Zustand: ist der letzte Schritt rot (leeres Ergebnis), steht das Element
    // weiter vorn. Ohne Treffer blieb der Bezug am Body, und der nächste Cut aus dieser Skizze schloss einen Kreis
    const TopoDS_Shape sub = body->Shape.getShape().getSubShape(element.c_str(), true);
    for (auto f = freecad_cast<Feature*>(stateAtMarker(body)); f;) {
        const std::string name = elementName(f->Shape.getShape().getShape(), sub);
        if (!name.empty()) {
            obj = f;
            element = name;
            return;
        }
        const auto& bodies = f->Bodies.getValues();
        const auto& bases = f->BaseFeatures.getValues();
        const auto idx = std::ranges::find(bodies, body) - bodies.begin();
        f = idx < static_cast<long>(bases.size()) ? freecad_cast<Feature*>(bases[idx]) : nullptr;
    }
}

void Design::sketchRef(const App::DocumentObject* sketch, App::DocumentObject*& obj, std::string& element)
{
    auto body = freecad_cast<Body*>(obj);
    App::DocumentObject* state = body ? stateAtMarker(body) : nullptr;
    if (!state || element.empty()) {
        return;
    }
    // Zustand vor der Skizze: spätere Schritte dieses Bodies zurückgehen (eine ältere Skizze bearbeitet)
    const auto items = timeline(sketch->getDocument());
    const auto at = [&](const App::DocumentObject* o) { return std::ranges::find(items, o) - items.begin(); };
    for (auto f = freecad_cast<Feature*>(state); f && at(f) > at(sketch); f = freecad_cast<Feature*>(state)) {
        const auto& bodies = f->Bodies.getValues();
        const auto& bases = f->BaseFeatures.getValues();
        const auto idx = std::ranges::find(bodies, body) - bodies.begin();
        state = idx < static_cast<long>(bases.size()) ? bases[idx] : nullptr;
    }
    auto feature = freecad_cast<Part::Feature*>(state);
    if (!feature) {
        return;
    }
    // Gleiche Kante im Zustand suchen; nicht gefunden: Namen behalten (so hieß sie, als der Body dieser Zustand war)
    const TopoDS_Shape sub = body->Shape.getShape().getSubShape(element.c_str(), true);
    const std::string name = elementName(feature->Shape.getShape().getShape(), sub);
    obj = feature;
    if (!name.empty()) {
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
        {"Brass", "231a3664-7285-4340-b5af-63a9e9a2d7af"},  // Copper-443, Admiralitätsmessing 8,53 g/cm³
        {"Copper", "6c03899d-496e-4c60-a41b-3d66f2337fb9"},
        {"Rubber", "5a0ae2b7-e3cb-4aae-babd-2896596c63f4"},  // eigene Karten: Standard/Elastomer, Standard/Stone
        {"Silicone", "1dcdd60c-07fb-433a-8bb7-da9032f85515"},
        {"Granite", "9e646032-d41f-4380-bd2c-7068865eb2c9"},
        {"Marble", "212c193d-5cfb-4e51-a638-a9e0037f4ef5"},
        {"Ceramic", "71f4a808-b025-4770-bef4-9c04f94ad771"},
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
    // Zuordnung über Namen und Gruppe; Lacke, Pulverlack und reine Farben bleiben offen: eine Beschichtung sagt nichts
    // über den Werkstoff darunter
    if (group == "Anodized" || has("Aluminum")) {
        return uuid("Aluminum");
    }
    if (has("Steel") || has("Chrome")) {
        return uuid("Steel");
    }
    if (has("Brass")) {
        return uuid("Brass");
    }
    if (has("Copper")) {
        return uuid("Copper");
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
    if (has("Granite")) {
        return uuid("Granite");
    }
    if (has("Marble")) {
        return uuid("Marble");
    }
    if (has("Ceramic") || has("Porcelain") || has("Stoneware")) {
        return uuid("Ceramic");
    }
    if (group == "Rubber") {
        return uuid(has("Silicone") ? "Silicone" : "Rubber");
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

Design::Feature* faceCreator(Design::Body* body, const TopoDS_Face& face);

namespace
{
/// Welche Elemente eine Korrektur meint
enum class Aim
{
    Edge,
    Face,       ///< jede Fläche (Maß, Muster)
    Flat,       ///< ebene Fläche
    Round,      ///< Zylinderfläche
    RoundOrFlat ///< Zylinder (Gewinde, Durchmesser), sonst eine Bohrung an der Stelle der ebenen Fläche
};

Aim aimOf(RedPen::Kind kind)
{
    switch (kind) {
        case RedPen::Kind::Fillet:
        case RedPen::Kind::Chamfer: return Aim::Edge;
        case RedPen::Kind::Offset: return Aim::Flat;
        case RedPen::Kind::Fit: return Aim::Round;
        case RedPen::Kind::Thread:
        case RedPen::Kind::Diameter: return Aim::RoundOrFlat;
        default: return Aim::Face;
    }
}

struct Candidate
{
    Design::Body* body;
    std::string name;
    double distance;  ///< quer zur Blickrichtung
    double depth;     ///< entlang der Blickrichtung (kleiner = näher am Auge)
    bool round;
    Base::Vector3d point;  ///< global
};
}  // namespace

double Design::modelDepth(App::Document* doc, const Base::Vector3d& at, const Base::Vector3d& intoIn)
{
    Base::Vector3d into = intoIn;
    into.Normalize();
    std::optional<std::pair<double, double>> best;  // (Abstand zum Strahl, Tiefe): erst der nächste, dann der vordere
    for (auto obj : doc->getObjectsOfType(Body::getClassTypeId())) {
        auto body = static_cast<Body*>(obj);
        Part::TopoShape shape = body->Shape.getShape();
        if (!body->Visibility.getValue() || shape.isNull()) {
            continue;
        }
        shape.setPlacement(componentOf(body)->globalPlacement());
        // nur die Flächen: ein Volumenkörper hieße für den Strahl durch ihn hindurch überall "Abstand 0"
        TopoDS_Compound faces;
        BRep_Builder builder;
        builder.MakeCompound(faces);
        for (TopExp_Explorer f(shape.getShape(), TopAbs_FACE); f.More(); f.Next()) {
            builder.Add(faces, f.Current());
        }
        Base::BoundBox3d box = shape.getBoundBox();
        box.Add(at);
        const Base::Vector3d end = at + into * (box.CalcDiagonalLength() * 2 + 10);
        const TopoDS_Edge ray = BRepBuilderAPI_MakeEdge(gp_Pnt(at.x, at.y, at.z), gp_Pnt(end.x, end.y, end.z)).Edge();
        BRepExtrema_DistShapeShape dist(faces, ray);
        for (int i = 1; dist.IsDone() && i <= dist.NbSolution(); ++i) {
            const gp_Pnt q = dist.PointOnShape2(i);
            const std::pair<double, double> c {dist.Value(), (Base::Vector3d(q.X(), q.Y(), q.Z()) - at) * into};
            if (!best || c.first < best->first - 1e-6 || (c.first < best->first + 1e-6 && c.second < best->second)) {
                best = c;
            }
        }
    }
    return best ? std::max(0.0, best->second) : 0.0;
}

Design::Correction Design::readArrow(App::Document* doc, const Base::Vector3d& tail, const Base::Vector3d& tip,
                                     const Base::Vector3d& view)
{
    // Länge auf ganze mm (von Hand gezogen); zeigt der Pfeil im Bild aus der Fläche heraus: ziehen, sonst drücken
    const long length = std::max(1L, std::lround((tip - tail).Length()));
    Correction c = readCorrection(doc, "+" + std::to_string(length), tail, view);
    if (c.command.kind != RedPen::Kind::Offset || !c.body) {
        return c;
    }
    Part::TopoShape shape = c.body->Shape.getShape();
    shape.setPlacement(Base::Placement());
    const TopoDS_Shape element = shape.getSubShape(c.element.c_str(), true);
    if (element.IsNull() || element.ShapeType() != TopAbs_FACE) {
        return c;
    }
    BRepAdaptor_Surface surface(TopoDS::Face(element));
    gp_Dir out = surface.Plane().Axis().Direction();
    if (element.Orientation() == TopAbs_REVERSED) {
        out.Reverse();
    }
    Base::Vector3d n(out.X(), out.Y(), out.Z()), v = view;
    componentOf(c.body)->globalPlacement().getRotation().multVec(n, n);
    v.Normalize();
    const Base::Vector3d inImage = n - v * (n * v), arrow = (tip - tail) - v * ((tip - tail) * v);
    if (inImage * arrow < 0) {
        c.command.value = -double(length);
        c.text = "-" + std::to_string(length);
    }
    return c;
}

Design::Correction Design::readCorrection(App::Document* doc, const std::string& text, const Base::Vector3d& at,
                                          const Base::Vector3d& viewIn)
{
    Correction c;
    c.text = text;
    c.at = at;
    c.command = RedPen::parse(text);
    if (c.command.kind == RedPen::Kind::None) {
        c.error = "Not a correction";
        return c;
    }
    Base::Vector3d view = viewIn;
    view.Normalize();
    c.view = view;
    const Aim aim = aimOf(c.command.kind);
    std::vector<Candidate> candidates;
    for (auto obj : doc->getObjectsOfType(Body::getClassTypeId())) {
        auto body = static_cast<Body*>(obj);
        Part::TopoShape shape = body->Shape.getShape();
        if (!body->Visibility.getValue() || shape.isNull()) {
            continue;
        }
        shape.setPlacement(Base::Placement());
        // Sehstrahl durch die Tinte in den Koordinaten der Komponente
        const Base::Placement inv = componentOf(body)->globalPlacement().inverse();
        Base::Vector3d p = at, d = view;
        inv.multVec(p, p);
        inv.getRotation().multVec(d, d);
        Base::BoundBox3d box = shape.getBoundBox();
        box.Add(p);
        const double reach = box.CalcDiagonalLength() * 2 + 10;
        const TopoDS_Edge ray = BRepBuilderAPI_MakeEdge(gp_Pnt(p.x - d.x * reach, p.y - d.y * reach, p.z - d.z * reach),
                                                        gp_Pnt(p.x + d.x * reach, p.y + d.y * reach, p.z + d.z * reach)).Edge();
        // Was die Sichtlinie deutlich hinter der ersten getroffenen Fläche streift, ist verdeckt: R2 oben an der Vorderkante
        // traf sonst die hintere untere Kante, durch die dieselbe Linie genau hindurchgeht
        double hidden = std::numeric_limits<double>::infinity();
        {
            IntCurvesFace_ShapeIntersector hit;
            hit.Load(shape.getShape(), Precision::Confusion());
            hit.Perform(gp_Lin(gp_Pnt(p.x, p.y, p.z), gp_Dir(d.x, d.y, d.z)), -reach, reach);
            for (int k = 1; k <= hit.NbPnt(); ++k) {
                hidden = std::min(hidden, hit.WParameter(k) + std::max(1.0, 0.1 * box.CalcDiagonalLength()));
            }
        }
        const TopAbs_ShapeEnum type = aim == Aim::Edge ? TopAbs_EDGE : TopAbs_FACE;
        const int count = shape.countSubShapes(type);
        for (int i = 1; i <= count; ++i) {
            const std::string name = (type == TopAbs_EDGE ? "Edge" : "Face") + std::to_string(i);
            const TopoDS_Shape element = shape.getSubShape(name.c_str());
            bool round = false;
            if (type == TopAbs_FACE) {
                const GeomAbs_SurfaceType s = BRepAdaptor_Surface(TopoDS::Face(element)).GetType();
                round = s == GeomAbs_Cylinder;
                if ((aim == Aim::Flat && s != GeomAbs_Plane) || (aim == Aim::Round && !round)
                    || (aim == Aim::RoundOrFlat && !round && s != GeomAbs_Plane)) {
                    continue;
                }
                // Muster: nur Flächen von Features, die etwas an den Körper setzen oder herausnehmen (nicht der Grundkörper)
                Feature* creator = c.command.kind == RedPen::Kind::Pattern ? faceCreator(body, TopoDS::Face(element)) : nullptr;
                Part::TopoShape tool;
                std::string why;
                if (c.command.kind == RedPen::Kind::Pattern
                    && (!creator || creator->op() == Feature::Op::NewBody || !creator->makeTool(tool, why))) {
                    continue;
                }
            }
            BRepExtrema_DistShapeShape dist(element, ray);
            if (!dist.IsDone() || dist.NbSolution() == 0) {
                continue;
            }
            const gp_Pnt onRay = dist.PointOnShape2(1), onElement = dist.PointOnShape1(1);
            if ((Base::Vector3d(onRay.X(), onRay.Y(), onRay.Z()) - p) * d > hidden) {
                continue;
            }
            Base::Vector3d point(onElement.X(), onElement.Y(), onElement.Z());
            componentOf(body)->globalPlacement().multVec(point, point);
            candidates.push_back({body, name, dist.Value(),
                                  (Base::Vector3d(onRay.X(), onRay.Y(), onRay.Z()) - p) * d, round, point});
        }
    }
    if (candidates.empty()) {
        c.error = "There is nothing to correct near the ink";
        return c;
    }
    // Gewinde und Durchmesser: eine runde Fläche in der Nähe geht vor (Tinte über einer Bohrung trifft deren Wand nicht)
    const auto nearest = [](const std::vector<Candidate>& list) {
        return std::ranges::min_element(list, [](const Candidate& a, const Candidate& b) {
            return std::abs(a.distance - b.distance) > 1e-6 ? a.distance < b.distance : a.depth < b.depth;
        });
    };
    if (aim == Aim::RoundOrFlat) {
        std::vector<Candidate> round, flat;
        for (const auto& k : candidates) {
            (k.round ? round : flat).push_back(k);
        }
        candidates = !round.empty() && (flat.empty() || nearest(round)->distance <= nearest(flat)->distance + 1.0) ? round : flat;
    }
    const Candidate best = *nearest(candidates);
    c.body = best.body;
    c.element = best.name;
    c.onModel = best.point;
    // gleich nah und gleich tief (z. B. zwei parallele Kanten, die Tinte dazwischen): nicht raten
    const double band = std::max(0.25 * best.distance, 0.3);
    for (const auto& k : candidates) {
        if (k.distance - best.distance < band && std::abs(k.depth - best.depth) < 0.5) {
            c.alternatives.push_back(k.body == best.body ? k.name : std::string(k.body->getNameInDocument()) + "." + k.name);
        }
    }
    if (c.alternatives.size() < 2) {
        c.alternatives.clear();
    }
    return c;
}

std::string Design::describeCorrection(const Correction& c)
{
    const auto number = [](double v) {
        std::ostringstream out;
        out << v;
        return out.str();
    };
    const bool round = c.element.rfind("Face", 0) == 0 && c.body
        && BRepAdaptor_Surface(TopoDS::Face(c.body->Shape.getShape().getSubShape(c.element.c_str()))).GetType() == GeomAbs_Cylinder;
    switch (c.command.kind) {
        case RedPen::Kind::Fillet: return "Fillet R" + number(c.command.value) + " on 1 edge";
        case RedPen::Kind::Chamfer: return "Chamfer " + number(c.command.value) + " mm on 1 edge";
        case RedPen::Kind::Offset: return std::string(c.command.value > 0 ? "Pull face by " : "Push face by ")
            + number(std::abs(c.command.value)) + " mm";
        case RedPen::Kind::Thread: return round ? "Thread " + c.command.size : "Tapped hole " + c.command.size;
        case RedPen::Kind::Diameter: return round ? "Diameter " + number(c.command.value) + " mm"
                                                  : "Hole Ø" + number(c.command.value) + " mm";
        case RedPen::Kind::Fit: return c.command.fit == "print" ? "3D print fit" : "Fit " + c.command.fit;
        case RedPen::Kind::Pattern: return "Pattern " + std::to_string(c.command.count) + "×";
        case RedPen::Kind::Value: return "Dimension " + number(c.command.value) + " mm";
        case RedPen::Kind::Remove: return "Remove face";
        default: return c.text;
    }
}

namespace
{
/// Neues Feature in der Komponente des Bodys, in der Timeline, am Body
template<class T>
T* newFeature(Design::Body* body, const char* type, const char* name)
{
    App::Document* doc = body->getDocument();
    auto f = static_cast<T*>(doc->addObject(type, name));
    Design::componentOf(body)->addObject(f);
    Design::addToTimeline(f);
    return f;
}

/// Skizze auf der ebenen Fläche mit einem Punkt an point (global), für eine Bohrung
Sketcher::SketchObject* pointSketch(Design::Body* body, const std::string& face, const Base::Vector3d& point)
{
    auto sk = static_cast<Sketcher::SketchObject*>(Design::newSketch(Design::componentOf(body)));
    App::DocumentObject* owner = body;
    std::string element = face;
    Design::stableRef(owner, element);
    sk->AttachmentSupport.setValue(owner, std::vector<std::string> {element});
    sk->MapMode.setValue("FlatFace");
    body->getDocument()->recompute();
    Base::Vector3d local;
    sk->globalPlacement().inverse().multVec(point, local);
    Part::GeomPoint p(Base::Vector3d(local.x, local.y, 0));
    sk->addGeometry(&p);
    sk->Visibility.setValue(false);
    return sk;
}
}  // namespace

App::DocumentObject* Design::applyCorrection(const Correction& c, std::string& error)
{
    if (!c.error.empty() || !c.body) {
        error = c.error.empty() ? "Nothing to correct" : c.error;
        return nullptr;
    }
    Body* body = c.body;
    App::Document* doc = body->getDocument();
    const TopoDS_Shape element = body->Shape.getShape().getSubShape(c.element.c_str(), true);
    if (element.IsNull()) {
        error = "The element is gone";
        return nullptr;
    }
    const bool round = element.ShapeType() == TopAbs_FACE
        && BRepAdaptor_Surface(TopoDS::Face(element)).GetType() == GeomAbs_Cylinder;
    const double v = c.command.value;
    App::DocumentObject* result = nullptr;
    switch (c.command.kind) {
        case RedPen::Kind::Fillet:
        case RedPen::Kind::Chamfer:
        case RedPen::Kind::Offset: {
            const bool fillet = c.command.kind == RedPen::Kind::Fillet, chamfer = c.command.kind == RedPen::Kind::Chamfer;
            auto f = fillet ? static_cast<DressUp*>(newFeature<Fillet>(body, "Design::Fillet", "Fillet"))
                : chamfer   ? static_cast<DressUp*>(newFeature<Chamfer>(body, "Design::Chamfer", "Chamfer"))
                            : static_cast<DressUp*>(newFeature<PressPull>(body, "Design::PressPull", "PressPull"));
            f->Edges.setValues(std::vector<std::string> {c.element});
            if (auto pull = freecad_cast<PressPull*>(f)) {
                pull->Distance.setValue(v);
            }
            else {
                f->Size.setValue(v);
            }
            attachToBodies(f, {body});
            result = f;
            break;
        }
        case RedPen::Kind::Thread:
        case RedPen::Kind::Diameter: {
            if (round && c.command.kind == RedPen::Kind::Thread) {
                auto t = newFeature<Thread>(body, "Design::Thread", "Thread");
                t->Edges.setValues(std::vector<std::string> {c.element});
                t->Standard.setValue(1L);
                for (const auto& size : t->ThreadSize.getEnumVector()) {
                    if (size.rfind(c.command.size + "x", 0) == 0) {
                        t->ThreadSize.setValue(size.c_str());
                    }
                }
                attachToBodies(t, {body});
                result = t;
            }
            else if (round) {  // Durchmesser über das Maß, das die Fläche treibt (Idee 2)
                for (const auto& d : drivingDimensions(body, c.element)) {
                    const bool radius = d.label == "Radius";
                    if (d.label == "Diameter" || radius) {
                        std::string message;
                        if (!setDrivingDimension(d.owner, d.path, radius ? v / 2 : v, message)) {
                            error = message;
                            return nullptr;
                        }
                        return d.owner;
                    }
                }
                error = "No dimension sets this diameter";
                return nullptr;
            }
            else {  // Bohrung an der Stelle auf der ebenen Fläche
                auto sk = pointSketch(body, c.element, c.onModel);
                auto hole = newFeature<Hole>(body, "Design::Hole", "Hole");
                hole->Sketch.setValue(sk);
                if (c.command.kind == RedPen::Kind::Thread) {
                    hole->Standard.setValue(1L);
                    for (const auto& size : hole->Size.getEnumVector()) {
                        if (size.rfind(c.command.size + "x", 0) == 0) {
                            hole->Size.setValue(size.c_str());
                        }
                    }
                    hole->Kind.setValue(1L);
                }
                else {
                    hole->Diameter.setValue(v);
                }
                hole->ThroughAll.setValue(true);
                attachToBodies(hole, {body});
                result = hole;
            }
            break;
        }
        case RedPen::Kind::Remove: {
            auto f = newFeature<RemoveFace>(body, "Design::RemoveFace", "RemoveFace");
            f->Edges.setValues(std::vector<std::string> {c.element});
            attachToBodies(f, {body});
            result = f;
            break;
        }
        case RedPen::Kind::Fit: {
            auto f = newFeature<Fitting>(body, "Design::Fitting", "Fit");
            f->Edges.setValues(std::vector<std::string> {c.element});
            f->Fit.setValue(c.command.fit == "print" ? "3D print normal" : c.command.fit == "H8" ? "H8/f7" : "H7/g6");
            attachToBodies(f, {body});
            result = f;
            break;
        }
        case RedPen::Kind::Value: {
            const auto dims = drivingDimensions(body, c.element);
            if (dims.empty()) {
                error = "No dimension sets this face";
                return nullptr;
            }
            std::string message;
            if (!setDrivingDimension(dims.front().owner, dims.front().path, v, message)) {
                error = message;
                return nullptr;
            }
            return dims.front().owner;
        }
        case RedPen::Kind::Pattern: {
            Feature* source = element.ShapeType() == TopAbs_FACE ? faceCreator(body, TopoDS::Face(element)) : nullptr;
            Part::TopoShape tool;
            std::string why;
            if (!source || !source->makeTool(tool, why)) {
                error = "Write 3× next to a face of an extrusion or hole";
                return nullptr;
            }
            // Richtung: von der Fläche zur Tinte, quer zur Blickrichtung, auf die nächste Achse; Abstand 1,5 × Größe
            // ponytail: nur X/Y/Z; schräge Muster im Muster-Dialog
            Base::Vector3d toward = c.at - c.onModel;
            toward -= c.view * (toward * c.view);  // quer zur Blickrichtung: wohin auf dem Bildschirm geschrieben
            const double comps[3] = {std::abs(toward.x), std::abs(toward.y), std::abs(toward.z)};
            const int axis = int(std::max_element(comps, comps + 3) - comps);
            const Base::BoundBox3d box = tool.getBoundBox();
            const double size[3] = {box.LengthX(), box.LengthY(), box.LengthZ()};
            const double sign = (axis == 0 ? toward.x : axis == 1 ? toward.y : toward.z) < 0 ? -1 : 1;
            auto p = newFeature<Pattern>(body, "Design::Pattern", "Pattern");
            p->Source.setValue(source);
            p->Operation.setValue(source->op() == Feature::Op::NewBody ? 1L : source->Operation.getValue());
            p->Direction1.setValue(long(axis));
            p->Count1.setValue(c.command.count);
            p->Spacing1.setValue(sign * std::max(size[axis] * 1.5, 1.0));
            std::vector<Body*> bodies;
            for (auto b : source->Bodies.getValues()) {
                if (auto sb = freecad_cast<Body*>(b)) {
                    bodies.push_back(sb);
                }
            }
            attachToBodies(p, bodies);
            result = p;
            break;
        }
        default:
            error = "Not a correction";
            return nullptr;
    }
    doc->recompute();
    return result;
}

Design::PrintCheckResult Design::printCheck(Part::TopoShape shape, const Base::Vector3d& upIn, double maxAngle, double minWall)
{
    PrintCheckResult result;
    shape.setPlacement(Base::Placement());
    Base::Vector3d up = upIn;
    if (up.Length() < 1e-12 || shape.isNull()) {
        return result;
    }
    up.Normalize();
    std::vector<Base::Vector3d> points;
    std::vector<Data::ComplexGeoData::Facet> facets;
    shape.getFaces(points, facets, 0.05);
    double bed = 1e100;
    for (const auto& p : points) {
        bed = std::min(bed, p * up);
    }
    // Wanddicke je Dreieck per Strahl (unten, parallel über alle Kerne). ponytail: über 400 000 Dreiecken nur jedes k-te
    const size_t step = std::max<size_t>(1, facets.size() / 400000);
    std::vector<size_t> probe;  // Dreiecke, deren Wanddicke geprüft wird
    const double u[3] = {up.x, up.y, up.z};
    for (size_t i = 0; i < facets.size(); ++i) {
        const Base::Vector3d& a = points[facets[i].I1];
        const Base::Vector3d& b = points[facets[i].I2];
        const Base::Vector3d& c = points[facets[i].I3];
        Base::Vector3d n = (b - a) % (c - a);
        const double area = n.Length() / 2;
        if (area < 1e-12) {
            continue;
        }
        n.Normalize();
        const auto add = [&](std::vector<Base::Vector3f>& list, double& sum) {
            for (const auto* p : {&a, &b, &c}) {
                list.emplace_back(float(p->x), float(p->y), float(p->z));
            }
            sum += area;
        };
        const double nn[3] = {n.x, n.y, n.z};
        const double height = std::max({a * up, b * up, c * up}) - bed;
        const PrintCheck::Kind kind = PrintCheck::classify(nn, u, maxAngle, height);
        if (kind == PrintCheck::Kind::Overhang) {
            add(result.overhang, result.overhangArea);
        }
        else if (kind == PrintCheck::Kind::Bed) {
            add(result.bed, result.bedArea);
        }
        if (minWall > 0 && i % step == 0) {
            probe.push_back(i);
        }
    }
    if (probe.empty()) {
        return result;
    }
    // vom Mittelpunkt gegen die Normale ins Material: verlässt der Strahl das Material vor minWall wieder, ist die Wand
    // hier dünner. Nur Austritte zählen: in einer Bohrung liegt der Mittelpunkt eines Dreiecks (Sehne) bis zur
    // Netzgenauigkeit in der Luft, der Strahl tritt dort erst durch die eigene Fläche ein. Je Faden ein eigener
    // Schnitt-Rechner (OCCT-Objekte sind nicht threadsicher), jeder schreibt nur seine eigenen Einträge.
    std::vector<char> thin(probe.size(), 0);
    const auto check = [&](size_t from, size_t to) {
        IntCurvesFace_ShapeIntersector inside;
        inside.Load(shape.getShape(), 1e-6);
        for (size_t j = from; j < to; ++j) {
            const auto& f = facets[probe[j]];
            const Base::Vector3d &a = points[f.I1], &b = points[f.I2], &c = points[f.I3];
            const Base::Vector3d n = ((b - a) % (c - a)).Normalize();
            const Base::Vector3d m = (a + b + c) / 3 - n * 1e-4;
            const gp_Dir dir(-n.x, -n.y, -n.z);
            inside.Perform(gp_Lin(gp_Pnt(m.x, m.y, m.z), dir), 1e-6, minWall);
            bool leaves = false;
            for (int k = 1; inside.IsDone() && k <= inside.NbPnt() && !leaves; ++k) {
                gp_Pnt p;
                gp_Vec out;
                BRepGProp_Face(inside.Face(k)).Normal(inside.UParameter(k), inside.VParameter(k), p, out);
                leaves = out.Dot(gp_Vec(dir)) > 0;
            }
            thin[j] = leaves;
        }
    };
    // unter ~2000 Strahlen lohnt kein Faden (Load kostet je Faden)
    const size_t threads = std::clamp<size_t>(probe.size() / 2000, 1, std::max(1U, std::thread::hardware_concurrency()));
    std::vector<std::thread> pool;
    for (size_t t = 1; t < threads; ++t) {
        pool.emplace_back(check, probe.size() * t / threads, probe.size() * (t + 1) / threads);
    }
    check(0, probe.size() / threads);
    for (auto& t : pool) {
        t.join();
    }
    for (size_t j = 0; j < probe.size(); ++j) {
        if (thin[j]) {
            const auto& f = facets[probe[j]];
            const Base::Vector3d &a = points[f.I1], &b = points[f.I2], &c = points[f.I3];
            for (const auto* p : {&a, &b, &c}) {
                result.thin.emplace_back(float(p->x), float(p->y), float(p->z));
            }
            result.thinArea += ((b - a) % (c - a)).Length() / 2;
        }
    }
    return result;
}

Design::QuickMeasure Design::quickMeasure(const std::vector<TopoDS_Shape>& shapes)
{
    QuickMeasure m;
    const auto point = [](const gp_Pnt& p) { return Base::Vector3d(p.X(), p.Y(), p.Z()); };
    if (shapes.size() == 1 && !shapes[0].IsNull()) {
        const TopoDS_Shape& s = shapes[0];
        if (s.ShapeType() == TopAbs_EDGE) {
            BRepAdaptor_Curve c(TopoDS::Edge(s));
            if (c.GetType() == GeomAbs_Circle) {
                m.diameter = 2 * c.Circle().Radius();
                m.anchor = point(c.Value((c.FirstParameter() + c.LastParameter()) / 2));
            }
        }
        else if (s.ShapeType() == TopAbs_FACE) {
            BRepAdaptor_Surface f(TopoDS::Face(s));
            if (f.GetType() == GeomAbs_Cylinder) {
                m.diameter = 2 * f.Cylinder().Radius();
                m.anchor = point(f.Value((f.FirstUParameter() + f.LastUParameter()) / 2,
                                         (f.FirstVParameter() + f.LastVParameter()) / 2));
            }
        }
        return m;
    }
    if (shapes.size() != 2 || shapes[0].IsNull() || shapes[1].IsNull()) {
        return m;
    }
    BRepExtrema_DistShapeShape dist(shapes[0], shapes[1]);
    if (dist.IsDone() && dist.NbSolution() > 0) {
        m.distance = dist.Value();
        // parallele Flächen haben mehrere gleich kurze Verbindungen (Ecken): deren Mitte, nicht eine Ecke
        for (int i = 1; i <= dist.NbSolution(); ++i) {
            m.anchor += (point(dist.PointOnShape1(i)) + point(dist.PointOnShape2(i))) / (2.0 * dist.NbSolution());
        }
    }
    // Richtung einer geraden Kante oder Normale einer ebenen Fläche
    const auto direction = [](const TopoDS_Shape& s, gp_Dir& d) {
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
        if (shapes[0].ShapeType() != shapes[1].ShapeType()) {
            // Kante zu Fläche: Winkel zur Fläche, nicht zu ihrer Normalen
            m.angle = std::abs(90 - a.Angle(b) * 180 / M_PI);
        }
        else {
            const double angle = a.Angle(b) * 180 / M_PI;
            m.angle = std::min(angle, 180 - angle);
        }
    }
    return m;
}

std::map<std::string, int> Design::partsList(App::Document* doc)
{
    // Stück je Körper: ein Normteil-Körper 1, eine Muster-Kopie so viele, wie sie Volumen hat, eine Spiegel-Kopie 1;
    // dazu alle späteren Kopien dieses Körpers (Muster eines Musters, Spiegeln eines Musters ...)
    std::vector<Feature*> copiers;
    for (App::DocumentObject* obj : timeline(doc)) {
        auto f = freecad_cast<Feature*>(obj);
        if (f && !f->Suppressed.getValue() && !f->isError() && !isRolledBack(f)
            && (f->isDerivedFrom<Pattern>() || f->isDerivedFrom<Mirror>())) {
            copiers.push_back(f);
        }
    }
    std::function<int(const App::DocumentObject*, int)> total = [&](const App::DocumentObject* body, int own) {
        int n = own;
        for (Feature* f : copiers) {
            const auto& sources = f->isDerivedFrom<Pattern>() ? static_cast<Pattern*>(f)->SourceBodies.getValues()
                                                              : static_cast<Mirror*>(f)->SourceBodies.getValues();
            const auto& copies = f->Bodies.getValues();
            for (size_t i = 0; i < sources.size() && i < copies.size(); ++i) {
                if (sources[i] == body && copies[i] != body) {
                    const int solids = int(f->shapeFor(copies[i]).countSubShapes(TopAbs_SOLID));
                    n += total(copies[i], std::max(solids, 1));
                }
            }
        }
        return n;
    };
    std::map<std::string, int> count;
    for (auto obj : doc->getObjectsOfType(Primitive::getClassTypeId())) {
        auto part = static_cast<Primitive*>(obj);
        const std::string name = part->partName();
        if (name.empty() || part->isError() || part->Suppressed.getValue() || isRolledBack(part)) {
            continue;
        }
        // neuer Körper: er und seine Kopien; eingefügt in einen anderen Körper: ein Stück
        const auto& bodies = part->Bodies.getValues();
        count[name] += part->Operation.getValue() == 0 && !bodies.empty() ? total(bodies.front(), 1) : 1;
    }
    for (auto obj : doc->getObjectsOfType(Fastener::getClassTypeId())) {
        auto f = static_cast<Fastener*>(obj);
        if (f->isError() || f->Suppressed.getValue() || isRolledBack(f)) {
            continue;
        }
        const std::string size = f->Size.getValueAsString();
        count[std::string(f->Screw.getValueAsString()) + " " + size + " × " + mm(f->Length.getValue())] += 1;
        if (f->Bottom.getValue() == 1) {
            count["Heat-set insert " + size] += 1;
        }
        else if (f->Bottom.getValue() == 2) {
            count["ISO 4032 " + size] += 1;
        }
    }
    return count;
}

std::vector<std::pair<App::DocumentObject*, std::string>> Design::problems(App::Document* doc)
{
    // erst, was nicht rechnet (rot in der Timeline), dann Warnungen und verlorene Bezüge
    std::vector<std::pair<App::DocumentObject*, std::string>> out;
    for (App::DocumentObject* obj : doc->getObjects()) {
        if (obj->isError()) {
            const char* status = obj->getStatusString();
            out.emplace_back(obj, status && *status ? status : "This step does not compute");
        }
    }
    for (const auto& issue : referenceIssues(doc)) {
        if (!issue.object->isError()) {
            out.emplace_back(issue.object, issue.text);
        }
    }
    return out;
}

std::vector<App::DocumentObject*> Design::dependents(const App::DocumentObject* obj)
{
    // nur, was man in Timeline und Browser sieht: Schritte, Skizzen, Körper; keine Ordner und Komponenten
    // die verborgenen Profile einer Skizze reichen durch: Extrusionen hängen an ihnen, gemeint ist die Skizze
    std::vector<App::DocumentObject*> out;
    for (App::DocumentObject* user : obj->getInList()) {
        const bool shown = user->isDerivedFrom<Feature>() || user->isDerivedFrom<Body>()
            || user->getTypeId().isDerivedFrom(Base::Type::fromName("Sketcher::SketchObject"));
        const auto users = user->isDerivedFrom<Profiles>() ? dependents(user) : std::vector<App::DocumentObject*> {user};
        for (App::DocumentObject* u : shown || user->isDerivedFrom<Profiles>() ? users : std::vector<App::DocumentObject*>()) {
            if (u != obj && std::ranges::find(out, u) == out.end()) {
                out.push_back(u);
            }
        }
    }
    return out;
}

std::vector<Design::ReferenceIssue> Design::referenceIssues(App::Document* doc)
{
    std::vector<ReferenceIssue> issues;
    for (App::DocumentObject* obj : doc->getObjects()) {
        if (auto warning = freecad_cast<App::PropertyString*>(obj->getPropertyByName("Warning")); warning && *warning->getValue()) {
            issues.push_back({obj, "Warning", "", warning->getValue(), true});
        }
        std::vector<App::Property*> props;
        obj->getPropertyList(props);
        for (App::Property* prop : props) {
            auto link = freecad_cast<App::PropertyLinkBase*>(prop);
            if (!link) {
                continue;
            }
            // Profile findet ein Schritt über ihre Schlüssel (ProfileKeys), nicht über die Flächennummer: zählen die
            // Profilflächen neu durch, ist die alte Nummer weg, das Profil aber da. Ein wirklich verlorenes Profil meldet
            // der Schritt selbst (Warnung "Profile gone"). Sonst falscher Alarm "Lost reference: Face34" (26.11.)
            if (std::string(prop->getName()) == "Profile") {
                auto keys = freecad_cast<App::PropertyStringList*>(obj->getPropertyByName("ProfileKeys"));
                if (keys && keys->getSize() > 0) {
                    continue;
                }
            }
            std::vector<App::DocumentObject*> targets;
            std::vector<std::string> subs;
            link->getLinks(targets, true, &subs, false);  // alte Schreibweise: verlorene Elemente tragen "?"
            for (const std::string& sub : subs) {
                if (Data::hasMissingElement(sub.c_str())) {
                    std::string shown = sub;
                    std::erase(shown, '?');
                    issues.push_back({obj, prop->getName(), shown, "Lost reference: " + shown, false});
                }
            }
        }
    }
    return issues;
}

int Design::completeDimensions(Sketcher::SketchObject* sketch, int& dof)
{
    using Sketcher::Constraint;
    using Sketcher::PointPos;
    const auto freedom = [sketch] {
        sketch->solve();
        return sketch->getLastDoF();
    };
    int added = 0;
    dof = freedom();
    // nur behalten, was einen Freiheitsgrad nimmt; sonst (doppelt, Widerspruch) wieder weg
    const auto tryAdd = [&](Sketcher::ConstraintType type, int first, PointPos firstPos, int second, PointPos secondPos,
                            double value, int third = Sketcher::GeoEnum::GeoUndef, PointPos thirdPos = PointPos::none) {
        if (dof <= 0) {
            return false;
        }
        auto c = std::make_unique<Constraint>();
        c->Type = type;
        c->First = first;
        c->FirstPos = firstPos;
        c->Second = second;
        c->SecondPos = secondPos;
        c->Third = third;
        c->ThirdPos = thirdPos;
        c->setValue(value);
        const int index = sketch->addConstraint(std::move(c));
        const int now = freedom();
        if (now < dof && !sketch->getLastHasConflicts() && !sketch->getLastHasRedundancies()) {
            dof = now;
            ++added;
            return true;
        }
        sketch->delConstraint(index);
        dof = freedom();
        return false;
    };
    // je Zugriff neu holen: jedes Lösen kann die Geometrie-Objekte ersetzen
    const int count = sketch->getHighestCurveIndex() + 1;
    const auto drawn = [sketch](int i) {
        const Part::Geometry* g = sketch->getGeometry(i);
        return g && !Sketcher::GeometryFacade::getConstruction(g) ? g : nullptr;
    };
    // 1. Absicht "mittig": Profil um den Ursprung zentriert -> die zwei äußersten Ecken symmetrisch zum Ursprung
    Base::BoundBox3d box;
    std::pair<int, PointPos> low {-1, PointPos::none}, high {-1, PointPos::none};
    double lowSum = 1e100, highSum = -1e100;
    for (int i = 0; i < count; ++i) {
        auto line = dynamic_cast<const Part::GeomLineSegment*>(drawn(i));
        if (!line) {
            continue;
        }
        for (const auto& [p, pos] : {std::pair {line->getStartPoint(), PointPos::start}, {line->getEndPoint(), PointPos::end}}) {
            box.Add(p);
            if (p.x + p.y < lowSum) {
                lowSum = p.x + p.y;
                low = {i, pos};
            }
            if (p.x + p.y > highSum) {
                highSum = p.x + p.y;
                high = {i, pos};
            }
        }
    }
    if (box.IsValid() && low.first >= 0 && low != high) {
        const double size = std::max(box.LengthX(), box.LengthY());
        if (Base::Vector3d(box.GetCenter().x, box.GetCenter().y, 0).Length() < 0.02 * size) {
            tryAdd(Sketcher::Symmetric, low.first, low.second, high.first, high.second, 0, Sketcher::GeoEnum::RtPnt,
                   PointPos::start);
        }
    }
    // 1b. Absicht "ganze Form" (12.14): geschlossene Züge aus Linien. Fast rechte Winkel werden rechtwinklig, fast
    // parallele Gegenseiten eines Vierecks parallel, fast gleich lange Seiten gleich (Rechteck, Quadrat, Raute,
    // gleichseitiges Dreieck, regelmäßiges Vieleck). Was schon gilt (waagrecht/senkrecht), nimmt tryAdd nicht doppelt.
    {
        std::vector<int> lines;
        for (int i = 0; i < count; ++i) {
            if (dynamic_cast<const Part::GeomLineSegment*>(drawn(i))) {
                lines.push_back(i);
            }
        }
        const auto end = [sketch](int geo, bool start) {
            auto line = static_cast<const Part::GeomLineSegment*>(sketch->getGeometry(geo));
            return start ? line->getStartPoint() : line->getEndPoint();
        };
        // Nachbarlinie an einem Punkt: genau eine andere Linie beginnt oder endet dort
        const auto next = [&](int geo, const Base::Vector3d& p) {
            int found = -1, hits = 0;
            for (int other : lines) {
                if (other != geo && ((end(other, true) - p).Length() < 1e-6 || (end(other, false) - p).Length() < 1e-6)) {
                    found = other;
                    ++hits;
                }
            }
            return hits == 1 ? found : -1;
        };
        std::set<int> seen;
        for (int first : lines) {
            if (seen.contains(first)) {
                continue;
            }
            std::vector<int> loop {first};
            Base::Vector3d at = end(first, false);
            for (int geo = next(first, at); geo >= 0 && geo != first && loop.size() <= 8; geo = next(geo, at)) {
                loop.push_back(geo);
                at = (end(geo, true) - at).Length() < 1e-6 ? end(geo, false) : end(geo, true);
            }
            seen.insert(loop.begin(), loop.end());
            if (loop.size() < 3 || loop.size() > 8 || (at - end(first, true)).Length() > 1e-6) {
                continue;  // nicht geschlossen
            }
            const auto dir = [&](int geo) { return (end(geo, false) - end(geo, true)).Normalize(); };
            const auto len = [&](int geo) { return (end(geo, false) - end(geo, true)).Length(); };
            const double tight = std::sin(M_PI / 180);  // 1°
            for (size_t k = 0; k < loop.size(); ++k) {
                const int a = loop[k], b = loop[(k + 1) % loop.size()];
                if (std::abs(dir(a) * dir(b)) < tight) {
                    tryAdd(Sketcher::Perpendicular, a, PointPos::none, b, PointPos::none, 0);
                }
            }
            if (loop.size() == 4) {
                for (size_t k = 0; k < 2; ++k) {
                    if ((dir(loop[k]) % dir(loop[k + 2])).Length() < tight) {
                        tryAdd(Sketcher::Parallel, loop[k], PointPos::none, loop[k + 2], PointPos::none, 0);
                    }
                }
            }
            for (size_t k = 1; k < loop.size(); ++k) {
                if (std::abs(len(loop[k]) - len(loop[0])) < 0.01 * len(loop[0])) {
                    tryAdd(Sketcher::Equal, loop[0], PointPos::none, loop[k], PointPos::none, 0);
                }
            }
        }
    }
    // 2. Größen: Längen, Durchmesser, Radien
    for (int i = 0; i < count && dof > 0; ++i) {
        const Part::Geometry* g = drawn(i);
        if (auto line = dynamic_cast<const Part::GeomLineSegment*>(g)) {
            tryAdd(Sketcher::Distance, i, PointPos::none, Sketcher::GeoEnum::GeoUndef, PointPos::none,
                   (line->getEndPoint() - line->getStartPoint()).Length());
        }
        else if (auto circle = dynamic_cast<const Part::GeomCircle*>(g)) {
            tryAdd(Sketcher::Diameter, i, PointPos::none, Sketcher::GeoEnum::GeoUndef, PointPos::none,
                   2 * circle->getRadius());
        }
        else if (auto arc = dynamic_cast<const Part::GeomArcOfCircle*>(g)) {
            tryAdd(Sketcher::Radius, i, PointPos::none, Sketcher::GeoEnum::GeoUndef, PointPos::none, arc->getRadius());
        }
    }
    // 3. Lage und Richtung von dem, was noch frei ist: Punkte mit Abstand zum Ursprung, Linien waagrecht/senkrecht/Winkel
    for (int pass = 0; pass < 3 && dof > 0; ++pass) {
        std::vector<std::pair<int, PointPos>> loose;
        sketch->getGeometryWithDependentParameters(loose);
        for (const auto& [geo, pos] : loose) {
            if (geo < 0 || geo >= count || !drawn(geo)) {
                continue;
            }
            // freie Kante: Lage an ihrem Bezugspunkt (Kreis/Bogen: Mitte, Linie: Anfang), Linie zuerst ihre Richtung
            auto line = dynamic_cast<const Part::GeomLineSegment*>(sketch->getGeometry(geo));
            // ein Vollkreis hat nur seine Mitte (der Solver meldet sie als start)
            const bool full = dynamic_cast<const Part::GeomCircle*>(sketch->getGeometry(geo));
            const PointPos at = full ? PointPos::mid : pos != PointPos::none ? pos : line ? PointPos::start : PointPos::mid;
            if (line) {  // auch bei freiem Punkt: der Solver schreibt eine freie Drehung dem Anfang zu
                const Base::Vector3d d = line->getEndPoint() - line->getStartPoint();
                if (std::abs(d.y) <= 0.02 * std::abs(d.x)) {
                    tryAdd(Sketcher::Horizontal, geo, PointPos::none, Sketcher::GeoEnum::GeoUndef, PointPos::none, 0);
                }
                else if (std::abs(d.x) <= 0.02 * std::abs(d.y)) {
                    tryAdd(Sketcher::Vertical, geo, PointPos::none, Sketcher::GeoEnum::GeoUndef, PointPos::none, 0);
                }
                else {
                    tryAdd(Sketcher::Angle, geo, PointPos::none, Sketcher::GeoEnum::GeoUndef, PointPos::none, std::atan2(d.y, d.x));
                }
            }
            const Base::Vector3d p = sketch->getPoint(geo, at);
            tryAdd(Sketcher::DistanceX, Sketcher::GeoEnum::RtPnt, PointPos::start, geo, at, p.x);
            tryAdd(Sketcher::DistanceY, Sketcher::GeoEnum::RtPnt, PointPos::start, geo, at, p.y);
        }
    }
    return added;
}

Design::PrintCheckResult Design::printCheck(Body* body)
{
    ParameterGrp::handle params = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD");
    Base::Vector3d up = printUp(body->getDocument());
    componentOf(body)->globalPlacement().getRotation().inverse().multVec(up, up);
    return printCheck(body->Shape.getShape(), up, params->GetFloat("OverhangAngle", 45), params->GetFloat("MinWall", 0.8));
}

namespace
{
struct PrintTriangle
{
    Base::Vector3d a, b, c, n;
    double area;
};

std::vector<PrintTriangle> printTriangles(const std::vector<Part::TopoShape>& shapes)
{
    std::vector<PrintTriangle> tris;
    for (const auto& shape : shapes) {
        std::vector<Base::Vector3d> points;
        std::vector<Data::ComplexGeoData::Facet> facets;
        shape.getFaces(points, facets, 0.05);
        for (const auto& f : facets) {
            const Base::Vector3d &a = points[f.I1], &b = points[f.I2], &c = points[f.I3];
            Base::Vector3d n = (b - a) % (c - a);
            const double area = n.Length() / 2;
            if (area > 1e-12) {
                tris.push_back({a, b, c, n.Normalize(), area});
            }
        }
    }
    return tris;
}

/// Maße nach dem Drehen von up auf +Z, wie DesignExport.print_rotation es für den Slicer tut
Base::Vector3d printExtents(const std::vector<PrintTriangle>& tris, const Base::Vector3d& up)
{
    const Base::Rotation turn(up, Base::Vector3d(0, 0, 1));
    Base::BoundBox3d box;
    for (const auto& t : tris) {
        for (const auto* p : {&t.a, &t.b, &t.c}) {
            Base::Vector3d q;
            turn.multVec(*p, q);
            box.Add(q);
        }
    }
    return box.IsValid() ? Base::Vector3d(box.LengthX(), box.LengthY(), box.LengthZ()) : Base::Vector3d();
}

/// passt auf das Bett (x, y, z; 0 = egal); um z drehen darf der Slicer
bool fitsBed(const Base::Vector3d& size, const Base::Vector3d& bed)
{
    if (bed.x <= 0 || bed.y <= 0 || bed.z <= 0) {
        return true;
    }
    const double eps = 1e-6;
    return size.z <= bed.z + eps
        && std::max(size.x, size.y) <= std::max(bed.x, bed.y) + eps && std::min(size.x, size.y) <= std::min(bed.x, bed.y) + eps;
}

Part::TopoShape globalPrintShape(Design::Body* body)
{
    Part::TopoShape s = body->Shape.getShape();
    s.setPlacement(Design::componentOf(body)->globalPlacement());  // wie printCheck(Body*): Komponente zählt
    return s;
}

std::vector<Part::TopoShape> visiblePrintShapes(App::Document* doc)
{
    std::vector<Part::TopoShape> shapes;
    for (auto obj : doc->getObjectsOfType(Design::Body::getClassTypeId())) {
        auto body = static_cast<Design::Body*>(obj);
        if (body->Visibility.getValue() && !body->Shape.getShape().isNull()) {
            shapes.push_back(globalPrintShape(body));
        }
    }
    return shapes;
}

Base::Vector3d bedSize()
{
    ParameterGrp::handle params = App::GetApplication().GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD");
    return Base::Vector3d(params->GetFloat("BedWidth", 220), params->GetFloat("BedDepth", 220), params->GetFloat("BedHeight", 250));
}
}  // namespace

Base::Vector3d Design::suggestPrintUp(const std::vector<Part::TopoShape>& shapes, double maxAngle, const Base::Vector3d& bed)
{
    const std::vector<PrintTriangle> tris = printTriangles(shapes);
    if (tris.empty()) {
        return Base::Vector3d(0, 0, 1);
    }
    // jeder Körper muss für sich aufs Bett passen: der Slicer verteilt sie
    std::vector<std::vector<PrintTriangle>> each;
    for (const auto& shape : shapes) {
        each.push_back(printTriangles({shape}));
    }
    // Kandidaten: +Z zuerst (bei Gleichstand bleibt es, wie gezeichnet), die anderen Achsen, dann jede ebene Fläche
    // nach unten, die größten zuerst. Ebene Flächen erkennt man an gleichen Dreiecksnormalen.
    std::vector<Base::Vector3d> candidates;
    for (const auto& [x, y, z] : {std::tuple {0, 0, 1}, {0, 0, -1}, {1, 0, 0}, {-1, 0, 0}, {0, 1, 0}, {0, -1, 0}}) {
        candidates.emplace_back(x, y, z);
    }
    std::map<std::tuple<long, long, long>, std::pair<double, Base::Vector3d>> planes;
    double volume = 0;
    Base::BoundBox3d box;
    for (const auto& t : tris) {
        auto& [area, n] = planes[{std::lround(t.n.x * 1000), std::lround(t.n.y * 1000), std::lround(t.n.z * 1000)}];
        area += t.area;
        n = t.n;
        volume += t.a * (t.b % t.c) / 6;
        box.Add(t.a);
        box.Add(t.b);
        box.Add(t.c);
    }
    std::vector<std::pair<double, Base::Vector3d>> byArea;
    for (const auto& [key, plane] : planes) {
        byArea.push_back(plane);
    }
    std::sort(byArea.begin(), byArea.end(), [](const auto& l, const auto& r) { return l.first > r.first; });
    // ponytail: nur die 24 größten Ebenen; Freiformteile ohne Ebenen bekommen nur die Achsen
    for (size_t i = 0; i < byArea.size() && i < 24; ++i) {
        const Base::Vector3d up = -byArea[i].second;
        if (std::none_of(candidates.begin(), candidates.end(), [&](const Base::Vector3d& c) { return c * up > 0.9999; })) {
            candidates.push_back(up);
        }
    }
    volume = std::max(std::abs(volume), 1e-9);
    const double diagonal = std::max(box.CalcDiagonalLength(), 1e-9);
    // Kosten: Stützmaterial (Überhangfläche, waagrecht gemessen, mal Höhe über dem Bett) im Verhältnis zum Teil, dazu
    // halb so stark die Bauhöhe (Druckzeit, Kippen). Passt es so nicht aufs Bett, kommt es nur, wenn nichts passt.
    Base::Vector3d best(0, 0, 1);
    double bestCost = 1e300;
    for (const Base::Vector3d& up : candidates) {
        double low = 1e300, high = -1e300;
        for (const auto& t : tris) {
            for (const auto* p : {&t.a, &t.b, &t.c}) {
                low = std::min(low, *p * up);
                high = std::max(high, *p * up);
            }
        }
        const double u[3] = {up.x, up.y, up.z};
        double support = 0;
        for (const auto& t : tris) {
            const double n[3] = {t.n.x, t.n.y, t.n.z};
            const double top = std::max({t.a * up, t.b * up, t.c * up}) - low;
            if (PrintCheck::classify(n, u, maxAngle, top) == PrintCheck::Kind::Overhang) {
                support += t.area * -(t.n * up) * ((t.a + t.b + t.c) / 3 * up - low);
            }
        }
        double cost = support / volume + 0.5 * (high - low) / diagonal;
        if (std::ranges::any_of(each, [&](const auto& t) { return !fitsBed(printExtents(t, up), bed); })) {
            cost += 100;
        }
        if (cost < bestCost - 1e-9) {
            bestCost = cost;
            best = up;
        }
    }
    return best;
}

Base::Vector3d Design::suggestPrintUp(App::Document* doc)
{
    const double angle = App::GetApplication()
                             .GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD")
                             ->GetFloat("OverhangAngle", 45);
    return suggestPrintUp(visiblePrintShapes(doc), angle, bedSize());
}

Base::Vector3d Design::printSize(Body* body)
{
    return printExtents(printTriangles({globalPrintShape(body)}), printUp(body->getDocument()));
}

bool Design::fitsPrintBed(const Base::Vector3d& size)
{
    return fitsBed(size, bedSize());
}

Design::Body* Design::tooBigToPrint(App::Document* doc)
{
    for (auto obj : doc->getObjectsOfType(Body::getClassTypeId())) {
        auto body = static_cast<Body*>(obj);
        if (body->Visibility.getValue() && !body->Shape.getShape().isNull() && !fitsPrintBed(printSize(body))) {
            return body;
        }
    }
    return nullptr;
}

Base::Placement Design::printSplitPlane(Body* body)
{
    // in Drucklage (up nach +Z): die Richtung, die das Bett am weitesten überragt; x und y darf der Slicer tauschen
    const Base::Rotation turn(printUp(body->getDocument()), Base::Vector3d(0, 0, 1));
    Base::BoundBox3d box;
    for (const auto& t : printTriangles({globalPrintShape(body)})) {
        for (const auto* p : {&t.a, &t.b, &t.c}) {
            Base::Vector3d q;
            turn.multVec(*p, q);
            box.Add(q);
        }
    }
    const Base::Vector3d bed = bedSize();
    const bool xLonger = box.LengthX() >= box.LengthY();
    const double over[3] = {box.LengthX() / (xLonger ? std::max(bed.x, bed.y) : std::min(bed.x, bed.y)),
                            box.LengthY() / (xLonger ? std::min(bed.x, bed.y) : std::max(bed.x, bed.y)),
                            box.LengthZ() / bed.z};
    const int k = int(std::max_element(over, over + 3) - over);
    // so viele gleich lange Stücke, wie nötig sind; der Schnitt trennt das erste ab (der Rest wird weiter geteilt)
    const int pieces = std::max(2, int(std::ceil(over[k] - 1e-9)));
    Base::Vector3d normal(k == 0, k == 1, k == 2), center = box.GetCenter();
    const double low[3] = {box.MinX, box.MinY, box.MinZ}, size[3] = {box.LengthX(), box.LengthY(), box.LengthZ()};
    (k == 0 ? center.x : k == 1 ? center.y : center.z) = low[k] + size[k] / pieces;
    const Base::Rotation back = turn.inverse();
    back.multVec(normal, normal);
    back.multVec(center, center);
    return Base::Placement(center, Base::Rotation(Base::Vector3d(0, 0, 1), normal));
}

Base::Vector3d Design::printUp(App::Document* doc)
{
    App::Part* part = root(doc, false);
    auto prop = part ? freecad_cast<App::PropertyVector*>(part->getPropertyByName("PrintUp")) : nullptr;
    return prop && prop->getValue().Length() > 1e-12 ? prop->getValue() : Base::Vector3d(0, 0, 1);
}

void Design::setPrintUp(App::Document* doc, const Base::Vector3d& up)
{
    App::Part* part = root(doc, true);
    auto prop = freecad_cast<App::PropertyVector*>(part->getPropertyByName("PrintUp"));
    if (!prop) {
        prop = static_cast<App::PropertyVector*>(
            part->addDynamicProperty("App::PropertyVector", "PrintUp", "Print", "Print direction (up)", App::Prop_Hidden));
    }
    Base::Vector3d v = up;
    v.Normalize();
    prop->setValue(v);
    // Tropfenform und gefaste Unterkanten hängen an der Druckrichtung
    for (auto obj : doc->getObjects()) {
        auto hole = freecad_cast<Hole*>(obj);
        auto fillet = freecad_cast<Fillet*>(obj);
        if ((hole && hole->Teardrop.getValue()) || (fillet && fillet->PrintChamfer.getValue())) {
            obj->touch();
        }
    }
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
    // Lage und Hüllquader je Körper einmal; die teure Schnittmenge nur, wo sich die Quader überlappen
    const auto prepare = [&global](const std::vector<App::DocumentObject*>& list) {
        std::vector<std::pair<TopoDS_Shape, Bnd_Box>> out;
        for (auto o : list) {
            out.emplace_back(global(o), Bnd_Box());
            BRepBndLib::Add(out.back().first, out.back().second);
        }
        return out;
    };
    const auto inner = prepare(mine), outer = prepare(others);
    for (size_t i = 0; i < mine.size(); ++i) {
        const auto& [sa, ba] = inner[i];
        for (size_t k = 0; k < others.size(); ++k) {
            const auto& [sb, bb] = outer[k];
            App::DocumentObject* a = mine[i];
            App::DocumentObject* b = others[k];
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

// --- Idee 2: Fläche antippen, Zahl ändern -------------------------------------------------------------------------

namespace
{
/// Trägerfläche einer Fläche als Text: gleiche Ebene/gleicher Zylinder … ergibt denselben Schlüssel, auch wenn die
/// Fläche selbst inzwischen ein Loch hat oder beschnitten ist
std::string surfaceKey(const TopoDS_Face& face)
{
    BRepAdaptor_Surface s(face);
    const auto unsignedDir = [](gp_Dir d) {  // Richtung ohne Vorzeichen: größte Komponente positiv
        const double big = std::abs(d.X()) >= std::abs(d.Y()) && std::abs(d.X()) >= std::abs(d.Z()) ? d.X()
                         : std::abs(d.Y()) >= std::abs(d.Z())                                    ? d.Y()
                                                                                                 : d.Z();
        return big < 0 ? d.Reversed() : d;
    };
    std::ostringstream key;
    key << std::fixed << std::setprecision(4);
    const auto put = [&key](double v) { key << ' ' << (std::abs(v) < 5e-5 ? 0.0 : v); };
    switch (s.GetType()) {
        case GeomAbs_Plane: {
            const gp_Dir n = unsignedDir(s.Plane().Axis().Direction());
            key << 'P';
            put(n.X()), put(n.Y()), put(n.Z()), put(gp_Vec(n).Dot(gp_Vec(s.Plane().Location().XYZ())));
            break;
        }
        case GeomAbs_Cylinder: {
            const gp_Ax1 axis = s.Cylinder().Axis();
            const gp_Dir d = unsignedDir(axis.Direction());
            // Punkt der Achse, der dem Ursprung am nächsten liegt
            const gp_XYZ p = axis.Location().XYZ() - gp_Vec(d).XYZ() * gp_Vec(d).Dot(gp_Vec(axis.Location().XYZ()));
            key << 'C';
            put(d.X()), put(d.Y()), put(d.Z()), put(p.X()), put(p.Y()), put(p.Z()), put(s.Cylinder().Radius());
            break;
        }
        default: {  // Kegel, Kugel, Torus, Freiform: Lage und Größe der Fläche selbst
            GProp_GProps p;
            BRepGProp::SurfaceProperties(face, p);
            key << 'S' << int(s.GetType());
            put(p.CentreOfMass().X()), put(p.CentreOfMass().Y()), put(p.CentreOfMass().Z()), put(p.Mass());
            break;
        }
    }
    return key.str();
}

bool hasSurface(const Part::TopoShape& shape, const std::string& key)
{
    for (TopExp_Explorer f(shape.getShape(), TopAbs_FACE); f.More(); f.Next()) {
        if (surfaceKey(TopoDS::Face(f.Current())) == key) {
            return true;
        }
    }
    return false;
}

/// Wert hängt an einem Parameter ("Hoehe" oder "Parameters.Hoehe")? Dann dessen Property, sonst nullptr
App::PropertyQuantity* boundParameter(App::DocumentObject* owner, const App::ObjectIdentifier& path)
{
    const auto info = owner->getExpression(path);
    if (!info.expression) {
        return nullptr;
    }
    std::string text = info.expression->toString();
    if (text.rfind("Parameters.", 0) == 0) {
        text.erase(0, std::strlen("Parameters."));
    }
    for (auto set : owner->getDocument()->getObjectsOfType(App::VarSet::getClassTypeId())) {
        if (std::strcmp(set->Label.getValue(), "Parameters") == 0) {
            if (auto prop = freecad_cast<App::PropertyQuantity*>(set->getPropertyByName(text.c_str()))) {
                return prop;
            }
        }
    }
    return nullptr;
}
}  // namespace

/// Feature, das eine Fläche des Bodys erzeugte: das letzte der Kette, in dessen Zustand davor es ihre Trägerfläche
/// noch nicht gab
Design::Feature* faceCreator(Design::Body* body, const TopoDS_Face& face)
{
    const std::string key = surfaceKey(face);
    auto creator = freecad_cast<Design::Feature*>(body->Tip.getValue());
    while (creator) {
        const auto& bodies = creator->Bodies.getValues();
        const auto idx = std::ranges::find(bodies, body) - bodies.begin();
        const auto& bases = creator->BaseFeatures.getValues();
        auto base = idx < static_cast<long>(bases.size()) ? freecad_cast<Design::Feature*>(bases[idx]) : nullptr;
        if (!base || !hasSurface(base->shapeFor(body), key)) {
            break;
        }
        creator = base;
    }
    return creator;
}

std::vector<Design::DrivingDimension> Design::drivingDimensions(Body* body, const std::string& faceName)
{
    std::vector<DrivingDimension> out;
    const Part::TopoShape shape = body->Shape.getShape();
    const TopoDS_Shape sub = shape.getSubShape(faceName.c_str(), true);
    if (sub.IsNull() || sub.ShapeType() != TopAbs_FACE) {
        return out;
    }
    const TopoDS_Face face = TopoDS::Face(sub);
    GProp_GProps props;
    BRepGProp::SurfaceProperties(face, props);
    const gp_Pnt center = props.CentreOfMass();
    const Base::Vector3d anchor = componentOf(body)->globalPlacement().getPosition()
        + componentOf(body)->globalPlacement().getRotation().multVec(Base::Vector3d(center.X(), center.Y(), center.Z()));

    Feature* creator = faceCreator(body, face);
    if (!creator) {
        return out;
    }

    const auto add = [&](App::DocumentObject* owner, const char* prop, const char* label) {
        auto q = freecad_cast<App::PropertyQuantity*>(owner->getPropertyByName(prop));
        if (!q || q->testStatus(App::Property::Hidden) || q->testStatus(App::Property::ReadOnly)) {
            return;
        }
        DrivingDimension d {owner, prop, label, q->getValue(), q->getUnit() == Base::Unit::Angle, "", anchor};
        if (const auto info = owner->getExpression(App::ObjectIdentifier(*q)); info.expression) {
            d.expression = info.expression->toString();
        }
        out.push_back(d);
    };
    // Bemaßungen der Skizzenkanten, die in dieser Fläche liegen (Seitenflächen von Extrude/Revolve)
    const auto sketchDims = [&](App::PropertyLinkSub& profile) {
        auto profiles = freecad_cast<Profiles*>(profile.getValue());
        auto sketch = profiles ? freecad_cast<Part::Feature*>(profiles->Sketch.getValue()) : nullptr;
        auto constraints = sketch ? freecad_cast<App::PropertyLists*>(sketch->getPropertyByName("Constraints")) : nullptr;
        if (!sketch || !constraints) {
            return;
        }
        auto sk = static_cast<Sketcher::SketchObject*>(sketch);
        const Base::Placement pla = sketch->Placement.getValue();
        // Geometrien, deren Mitte auf der Fläche liegt: aus ihnen wurde die Fläche gezogen bzw. gedreht
        std::set<int> geos;
        for (int g = 0; g <= sk->getHighestCurveIndex(); ++g) {
            auto curve = dynamic_cast<const Part::GeomCurve*>(sk->getGeometry(g));
            if (!curve || Sketcher::GeometryFacade::getConstruction(curve)) {
                continue;
            }
            BRepAdaptor_Curve c(TopoDS::Edge(curve->toShape()));
            const gp_Pnt local = c.Value((c.FirstParameter() + c.LastParameter()) / 2);
            Base::Vector3d mid;
            pla.multVec(Base::Vector3d(local.X(), local.Y(), local.Z()), mid);
            BRepExtrema_DistShapeShape dist(BRepBuilderAPI_MakeVertex(gp_Pnt(mid.x, mid.y, mid.z)).Vertex(), face);
            if (dist.IsDone() && dist.Value() < 1e-6) {
                geos.insert(g);
            }
        }
        if (geos.empty()) {
            return;
        }
        const auto& list = sk->Constraints.getValues();
        for (size_t i = 0; i < list.size(); ++i) {
            const Sketcher::Constraint* c = list[i];
            if (!c->isDimensional() || !c->isDriving) {
                continue;
            }
            const bool touches = geos.contains(c->First) || geos.contains(c->Second) || geos.contains(c->Third);
            if (!touches) {
                continue;
            }
            const char* label = c->Type == Sketcher::Radius ? "Radius"
                              : c->Type == Sketcher::Diameter ? "Diameter"
                              : c->Type == Sketcher::Angle ? "Angle"
                              : c->Type == Sketcher::DistanceX ? "Horizontal distance"
                              : c->Type == Sketcher::DistanceY ? "Vertical distance"
                                                               : "Length";
            const bool angle = c->Type == Sketcher::Angle;
            DrivingDimension d {sk, "Constraints[" + std::to_string(i) + "]", c->Name.empty() ? label : c->Name,
                                angle ? c->getValue() * 180 / M_PI : c->getValue(), angle, "", anchor};
            if (const auto info = sk->getExpression(sk->Constraints.createPath(int(i))); info.expression) {
                d.expression = info.expression->toString();
            }
            out.push_back(d);
        }
    };

    if (auto extrude = freecad_cast<Extrude*>(creator)) {
        // End- oder Seitenfläche? Endflächen stehen senkrecht zur Zugrichtung
        auto profiles = freecad_cast<Profiles*>(extrude->Profile.getValue());
        auto sketch = profiles ? freecad_cast<Part::Feature*>(profiles->Sketch.getValue()) : nullptr;
        BRepAdaptor_Surface s(face);
        if (sketch && s.GetType() == GeomAbs_Plane) {
            const Base::Placement pla = sketch->Placement.getValue();
            Base::Vector3d n = pla.getRotation().multVec(Base::Vector3d(0, 0, 1));
            const gp_Dir fn = s.Plane().Axis().Direction();
            if (std::abs(std::abs(fn.Dot(gp_Dir(n.x, n.y, n.z))) - 1) < 1e-6) {
                if (extrude->Reversed.getValue()) {
                    n = -n;
                }
                const double offset = extrude->StartOffset.getValue();
                // Abstand ab der versetzten Startebene (der Versatz geht immer entlang der Skizzennormalen)
                const double d = (Base::Vector3d(center.X(), center.Y(), center.Z()) - pla.getPosition()) * n
                    - (extrude->Reversed.getValue() ? -offset : offset);
                const long ext = extrude->Extent.getValue();
                if (std::abs(d) < 1e-6 && std::abs(offset) > 1e-6 && ext != Extrude::ExtentSymmetric) {
                    add(extrude, "StartOffset", "Start offset");
                }
                else if (ext == Extrude::ExtentTwoSides && d < -1e-6) {
                    add(extrude, "Distance2", "Distance 2");
                }
                else if (std::abs(d) > 1e-6 || ext == Extrude::ExtentSymmetric) {
                    add(extrude, "Distance", "Distance");
                }
                return out;
            }
        }
        sketchDims(extrude->Profile);
        if (std::abs(extrude->TaperAngle.getValue()) > 1e-9) {
            add(extrude, "TaperAngle", "Taper angle");
        }
        if (extrude->Thin.getValue()) {
            add(extrude, "Thickness", "Thickness");
        }
    }
    else if (auto revolve = freecad_cast<Revolve*>(creator)) {
        sketchDims(revolve->Profile);
        add(revolve, "Angle", "Angle");
    }
    else if (auto hole = freecad_cast<Hole*>(creator)) {
        add(hole, "Diameter", "Diameter");
        if (!hole->ThroughAll.getValue()) {
            add(hole, "Depth", "Depth");
        }
        if (hole->HoleType.getValue() != 0) {
            add(hole, "HeadDiameter", "Head diameter");
            if (hole->HoleType.getValue() == 1) {
                add(hole, "HeadDepth", "Head depth");
            }
        }
    }
    else if (auto pull = freecad_cast<PressPull*>(creator)) {
        add(pull, "Distance", "Distance");
    }
    else if (freecad_cast<Fillet*>(creator)) {
        add(creator, "Size", "Radius");
        add(creator, "RadiusEnd", "Radius end");
    }
    else if (freecad_cast<Chamfer*>(creator)) {
        add(creator, "Size", "Distance");
        add(creator, "Distance2", "Distance 2");
    }
    else if (freecad_cast<Shell*>(creator)) {
        add(creator, "Size", "Thickness");
    }
    else if (freecad_cast<Draft*>(creator)) {
        add(creator, "Angle", "Angle");
    }
    else if (auto primitive = freecad_cast<Primitive*>(creator)) {
        for (const char* p : {"Length", "Width", "Height", "Radius", "TubeRadius", "Pitch"}) {
            add(primitive, p, p);
        }
    }
    return out;
}

namespace
{
std::set<App::DocumentObject*> failedObjects(App::Document* doc)
{
    std::set<App::DocumentObject*> out;
    for (auto obj : doc->getObjects()) {
        if (obj->isError()) {
            out.insert(obj);
        }
    }
    return out;
}

/// Neu rechnen; false mit der Meldung des ersten Objekts, das dabei fehlschlägt (vorher schon kaputte zählen nicht).
/// Der Aufrufer bricht dann seine Transaktion ab und rechnet neu.
bool recomputeClean(App::Document* doc, const std::set<App::DocumentObject*>& before, std::string& error)
{
    doc->recompute();
    for (auto obj : failedObjects(doc)) {
        if (!before.count(obj)) {
            error = obj->getStatusString();
            return false;
        }
    }
    return true;
}
}  // namespace

bool Design::setDrivingDimension(App::DocumentObject* owner, const std::string& path, double value, std::string& error)
{
    // Sketch-Bemaßung "Constraints[i]"
    if (path.rfind("Constraints[", 0) == 0) {
        auto sk = freecad_cast<Sketcher::SketchObject*>(owner);
        const int i = std::atoi(path.c_str() + std::strlen("Constraints["));
        if (!sk || i < 0 || i >= sk->Constraints.getSize()) {
            error = "This dimension no longer exists";
            return false;
        }
        const App::ObjectIdentifier id = sk->Constraints.createPath(i);
        if (auto param = boundParameter(sk, id)) {
            return setDrivingDimension(param->getContainer() ? static_cast<App::DocumentObject*>(param->getContainer())
                                                             : nullptr,
                                       param->getName(), value, error);
        }
        if (sk->getExpression(id).expression) {
            error = "This value comes from a formula; change it in Parameters";
            return false;
        }
        const bool angle = sk->Constraints.getValues()[i]->Type == Sketcher::Angle;
        const auto before = failedObjects(sk->getDocument());
        if (sk->setDatum(i, angle ? value * M_PI / 180 : value) != Sketcher::SketchSolveStatus::Success) {
            error = "The sketch cannot take this value";
            return false;
        }
        return recomputeClean(owner->getDocument(), before, error);
    }
    auto q = owner ? freecad_cast<App::PropertyQuantity*>(owner->getPropertyByName(path.c_str())) : nullptr;
    if (!q) {
        error = "This value cannot be changed here";
        return false;
    }
    const App::ObjectIdentifier id(*q);
    if (auto param = boundParameter(owner, id)) {  // am Parameter ändern, die Formel bleibt
        return setDrivingDimension(static_cast<App::DocumentObject*>(param->getContainer()), param->getName(), value, error);
    }
    const auto before = failedObjects(owner->getDocument());
    if (const auto info = owner->getExpression(id); info.expression) {
        // Parameter, dessen Wert eine Zahl ist: Zahl ersetzen; sonst gehört der Wert zu einer Formel
        if (!freecad_cast<App::VarSet*>(owner) || info.expression->getDeps().size() > 0) {
            error = "This value comes from a formula; change it in Parameters";
            return false;
        }
        std::ostringstream text;
        text << value << ' ' << (q->getUnit() == Base::Unit::Angle ? "deg" : q->getUnit() == Base::Unit::Length ? "mm" : "");
        owner->setExpression(id, std::shared_ptr<App::Expression>(App::Expression::parse(owner, text.str()).release()));
    }
    else {
        q->setValue(value);
    }
    return recomputeClean(owner->getDocument(), before, error);
}


// --- Idee 3: Die Notiz ist die Parameterliste --------------------------------------------------------------------

App::DocumentObject* Design::parameterSet(App::Document* doc, bool create)
{
    App::Part* r = root(doc, create);
    if (!r) {
        return nullptr;
    }
    for (auto obj : r->Group.getValues()) {
        if (obj->isDerivedFrom<App::VarSet>() && std::strcmp(obj->Label.getValue(), "Parameters") == 0) {
            return obj;
        }
    }
    if (!create) {
        return nullptr;
    }
    App::DocumentObject* set = doc->addObject("App::VarSet", "Parameters");
    set->Label.setValue("Parameters");
    r->addObject(set);
    return set;
}

std::string Design::toParameterExpression(App::Document* doc, const std::string& text)
{
    App::DocumentObject* set = parameterSet(doc, false);
    if (!set) {
        return NoteParameters::identifier(text);
    }
    const std::string folded = NoteParameters::identifier(text);  // Wandstärke -> Wandstaerke
    const std::string prefix = std::string(set->getNameInDocument()) + ".";
    static const std::regex word(R"([A-Za-z_]\w*)");
    std::string out;
    size_t last = 0;
    for (auto it = std::sregex_iterator(folded.begin(), folded.end(), word); it != std::sregex_iterator(); ++it) {
        const size_t at = it->position();
        const bool afterDot = at > 0 && folded[at - 1] == '.';
        App::Property* prop = afterDot ? nullptr : set->getPropertyByName(it->str().c_str());
        out += folded.substr(last, at - last);
        out += prop && prop->getGroup() && std::strcmp(prop->getGroup(), "Parameters") == 0 ? prefix + it->str() : it->str();
        last = at + it->length();
    }
    return out + folded.substr(last);
}

std::string Design::fromParameterExpression(App::Document* doc, const std::string& text)
{
    App::DocumentObject* set = parameterSet(doc, false);
    if (!set) {
        return text;
    }
    std::string out = text;
    const std::string prefix = std::string(set->getNameInDocument()) + ".";
    for (size_t pos; (pos = out.find(prefix)) != std::string::npos;) {
        out.erase(pos, prefix.size());
    }
    // geschriebene Namen (mit Umlauten) stehen in der Beschreibung des Parameters
    std::vector<App::Property*> props;
    set->getPropertyList(props);
    for (App::Property* p : props) {
        const char* doc_ = p->getDocumentation();
        if (p->getGroup() && std::strcmp(p->getGroup(), "Parameters") == 0 && doc_ && *doc_
            && NoteParameters::identifier(doc_) == p->getName() && std::strcmp(doc_, p->getName()) != 0) {
            const std::regex whole("\\b" + std::string(p->getName()) + "\\b");
            out = std::regex_replace(out, whole, doc_);
        }
    }
    return out;
}

void Design::setParameterExpression(App::DocumentObject* set, App::Property* prop, const std::string& text)
{
    // Dezimalkomma wie in den Rechenzeilen der Notiz: 2,5 -> 2.5
    const std::string expression = std::regex_replace(text, std::regex(R"((\d),(\d))"), "$1.$2");
    std::shared_ptr<App::Expression> expr(App::Expression::parse(set, toParameterExpression(set->getDocument(), expression)).release());
    // Erst rechnen: ein unbekannter Name ("abc") ließe sonst das Set bei jedem Recompute scheitern, und kein
    // Parameter bekäme mehr seinen Wert
    App::anyToQuantity(expr->getValueAsAny());
    set->setExpression(App::ObjectIdentifier(*prop), expr);
}

std::vector<std::string> Design::parameterUsers(App::DocumentObject* set, const std::string& id)
{
    std::vector<std::string> users;
    const std::regex reference(R"(\b)" + std::string(set->getNameInDocument()) + R"(\.)" + id + R"(\b)");
    for (auto obj : set->getDocument()->getObjects()) {
        for (const auto& [path, expr] : obj->ExpressionEngine.getExpressions()) {
            if (!(obj == set && path.getPropertyName() == id) && std::regex_search(expr->toString(), reference)) {
                users.emplace_back(obj == set ? "Parameters" : obj->Label.getValue());
                break;
            }
        }
    }
    return users;
}

namespace
{
bool syncingNotes = false;  ///< Notiz schreibt Parameter: die Gegenrichtung (parameterChanged) schweigt solange

std::vector<std::string> splitLines(const std::string& text)
{
    std::vector<std::string> lines;
    std::string line;
    std::istringstream in(text);
    while (std::getline(in, line)) {
        lines.push_back(line);
    }
    if (!text.empty() && text.back() == '\n') {
        lines.emplace_back();
    }
    return lines;
}

std::string joinLines(const std::vector<std::string>& lines)
{
    std::string out;
    for (size_t i = 0; i < lines.size(); ++i) {
        out += (i ? "\n" : "") + lines[i];
    }
    return out;
}
}  // namespace

namespace
{
/// Werte hinter Formeln (→), Fehler hinter fehlerhafte Zeilen (⚠); ohne errors bleiben vorhandene Fehlerhinweise stehen
void writeNoteHints(std::vector<std::string>& lines, App::DocumentObject* set, const std::map<size_t, std::string>* errorsIn)
{
    std::map<size_t, std::string> errors = errorsIn ? *errorsIn : std::map<size_t, std::string>();
    for (size_t i = 0; set && i < lines.size(); ++i) {
        const NoteParameters::Line line = NoteParameters::parse(lines[i]);
        if (!line.definition || (!errorsIn && lines[i].find(" \xE2\x9A\xA0 ") != std::string::npos)) {
            continue;
        }
        std::string value;
        if (!errors.contains(i)) {
            auto q = freecad_cast<App::PropertyQuantity*>(set->getPropertyByName(line.id.c_str()));
            // Formel: Rechenzeichen oder ein anderer Parameter; eine bloße Zahl mit Einheit braucht keinen Hinweis
            bool formula = line.expression.find_first_of("+-*/^()") != std::string::npos;
            static const std::regex word(R"([A-Za-z_]\w*)");
            const std::string folded = NoteParameters::identifier(line.expression);
            for (auto it = std::sregex_iterator(folded.begin(), folded.end(), word); !formula && it != std::sregex_iterator(); ++it) {
                App::Property* other = set->getPropertyByName(it->str().c_str());
                formula = other && other->getGroup() && std::strcmp(other->getGroup(), "Parameters") == 0;
            }
            if (q && formula) {
                value = q->getQuantityValue().getUserString();
            }
        }
        lines[i] = NoteParameters::withHint(lines[i], value, errors.contains(i) ? errors[i] : std::string());
    }
}
}  // namespace

void Design::syncNoteParameters(Note* note)
{
    App::Document* doc = note->getDocument();
    auto lines = splitLines(note->Text.getValue());
    // Namen, die andere Notizen schon anlegen
    std::map<std::string, std::string> others;
    for (auto obj : doc->getObjectsOfType(Note::getClassTypeId())) {
        if (obj != note) {
            for (const auto& id : static_cast<Note*>(obj)->Defines.getValues()) {
                others[id] = obj->Label.getValue();
            }
        }
    }
    std::map<size_t, std::string> errors;
    const auto resolved = NoteParameters::resolve(lines, errors);  // Konfigurationen: Ausdruck der aktiven Spalte
    const bool any = std::ranges::any_of(resolved, [](const NoteParameters::Line& l) { return l.definition; });
    App::DocumentObject* set = parameterSet(doc, any);
    std::vector<std::string> defined;
    syncingNotes = true;
    for (size_t i = 0; set && i < lines.size(); ++i) {
        const NoteParameters::Line& line = resolved[i];
        if (!line.definition) {
            continue;
        }
        if (others.contains(line.id)) {
            errors[i] = "Already defined in " + others[line.id];
            continue;
        }
        if (std::ranges::find(defined, line.id) != defined.end()) {
            errors[i] = "This name is used twice";
            continue;
        }
        App::Property* prop = set->getPropertyByName(line.id.c_str());
        // Einheiten und Konstanten ("mm", "h", "pi") gehen nicht: "Parameters.mm" ließe sich nicht mehr lesen
        if ((prop && (!prop->getGroup() || std::strcmp(prop->getGroup(), "Parameters") != 0))
            || !App::ExpressionParser::isTokenAnIndentifier(line.id)) {
            errors[i] = "Choose another name";
            continue;
        }
        const bool created = !prop;
        if (created) {
            prop = set->addDynamicProperty("App::PropertyQuantity", line.id.c_str(), "Parameters", line.name.c_str());
        }
        try {
            setParameterExpression(set, prop, line.expression);
            defined.push_back(line.id);
        }
        catch (const Base::Exception& e) {
            if (created) {
                set->removeDynamicProperty(line.id.c_str());
            }
            errors[i] = "Not a value or formula";
        }
    }
    // weggefallene Zeilen: Parameter löschen, außer er wird noch gebraucht
    std::vector<std::string> kept;
    for (const auto& id : note->Defines.getValues()) {
        if (std::ranges::find(defined, id) != defined.end() || !set || !set->getPropertyByName(id.c_str())) {
            continue;
        }
        const auto users = parameterUsers(set, id);
        if (users.empty()) {
            set->removeDynamicProperty(id.c_str());
            continue;
        }
        kept.push_back(id);
        std::string list;
        for (const auto& u : users) {
            list += (list.empty() ? "" : ", ") + u;
        }
        const char* shown = set->getPropertyByName(id.c_str())->getDocumentation();
        const std::string marker = "\xE2\x9A\xA0 " + std::string(shown && *shown ? shown : id.c_str()) + " is still used by ";
        std::erase_if(lines, [&marker](const std::string& l) { return l.rfind(marker, 0) == 0; });
        lines.push_back(marker + list);
    }
    // Hinweise der übrigen "noch benutzt"-Zeilen weg, wenn der Parameter wieder in der Notiz steht oder weg ist
    std::erase_if(lines, [&](const std::string& l) {
        if (l.rfind("\xE2\x9A\xA0 ", 0) != 0 || l.find(" is still used by ") == std::string::npos) {
            return false;
        }
        const std::string name = l.substr(4, l.find(" is still used by ") - 4);
        return std::ranges::find(kept, NoteParameters::identifier(name)) == kept.end();
    });
    doc->recompute();
    writeNoteHints(lines, set, &errors);
    for (const auto& id : kept) {
        defined.push_back(id);
    }
    note->Defines.setValues(defined);
    const std::string text = joinLines(lines);
    if (text != note->Text.getValue()) {
        note->Text.setValue(text);
    }
    syncingNotes = false;
}

void Design::refreshNoteValues(App::Document* doc)
{
    App::DocumentObject* set = parameterSet(doc, false);
    if (!set || syncingNotes) {
        return;
    }
    for (auto obj : doc->getObjectsOfType(Note::getClassTypeId())) {
        auto note = static_cast<Note*>(obj);
        if (note->Defines.getSize() == 0) {
            continue;
        }
        auto lines = splitLines(note->Text.getValue());
        writeNoteHints(lines, set, nullptr);
        const std::string text = joinLines(lines);
        if (text != note->Text.getValue()) {
            syncingNotes = true;
            note->Text.setValue(text);
            syncingNotes = false;
        }
    }
}

void Design::parameterChanged(App::DocumentObject* set, const char* name)
{
    if (syncingNotes || !set) {
        return;
    }
    App::Property* prop = set->getPropertyByName(name);
    if (!prop || !prop->getGroup() || std::strcmp(prop->getGroup(), "Parameters") != 0) {
        return;
    }
    const auto info = set->getExpression(App::ObjectIdentifier(*prop));
    std::string expression = info.expression ? fromParameterExpression(set->getDocument(), info.expression->toString())
                                             : static_cast<App::PropertyQuantity*>(prop)->getQuantityValue().getUserString();
    for (auto obj : set->getDocument()->getObjectsOfType(Note::getClassTypeId())) {
        auto note = static_cast<Note*>(obj);
        const auto& ids = note->Defines.getValues();
        if (std::ranges::find(ids, std::string(name)) == ids.end()) {
            continue;
        }
        auto lines = splitLines(note->Text.getValue());
        bool changed = false;
        std::map<size_t, std::string> errors;
        const auto resolved = NoteParameters::resolve(lines, errors);
        for (size_t i = 0; i < lines.size(); ++i) {
            const NoteParameters::Line& line = resolved[i];
            if (line.definition && line.id == name
                && toParameterExpression(set->getDocument(), line.expression)
                       != toParameterExpression(set->getDocument(), expression)) {
                // mit Konfigurationen nur die aktive Spalte, die anderen bleiben
                lines[i] = line.column >= 0 ? NoteParameters::withColumn(line, expression) : line.name + " = " + expression;
                changed = true;
            }
        }
        if (changed) {  // die Werte der Formeln zieht refreshNoteValues nach dem Rechnen nach
            syncingNotes = true;
            note->Text.setValue(joinLines(lines));
            syncingNotes = false;
        }
    }
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
    ADD_PROPERTY_TYPE(PreviousShape, (TopoDS_Shape()), "Design", App::PropertyType(App::Prop_Output | App::Prop_Hidden),
                      "Profiles before the last sketch change");
    ADD_PROPERTY_TYPE(PreviousSignatures, (), "Design", App::PropertyType(App::Prop_Output | App::Prop_Hidden),
                      "Signatures of the profiles before the last sketch change");
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

/// Gleiche Bereiche in gleicher Reihenfolge (Schwerpunkt und Fläche)? before liegt auf der Skizze (place), now in
/// Skizzen-Koordinaten
static bool sameRegions(const Part::TopoShape& before, const Base::Placement& place, const Part::TopoShape& now)
{
    const auto a = before.getSubTopoShapes(TopAbs_FACE), b = now.getSubTopoShapes(TopAbs_FACE);
    if (a.empty() || a.size() != b.size()) {
        return false;
    }
    const Base::Matrix4D toLocal = place.inverse().toMatrix();
    for (size_t i = 0; i < a.size(); ++i) {
        GProp_GProps pa, pb;
        BRepGProp::SurfaceProperties(a[i].getShape(), pa);
        BRepGProp::SurfaceProperties(b[i].getShape(), pb);
        const gp_Pnt c = pa.CentreOfMass();
        const Base::Vector3d local = toLocal * Base::Vector3d(c.X(), c.Y(), c.Z());
        const gp_Pnt d = pb.CentreOfMass();
        if (std::abs(pa.Mass() - pb.Mass()) > 1e-6 * (1 + pa.Mass())
            || (local - Base::Vector3d(d.X(), d.Y(), d.Z())).Length() > 1e-6 * (1 + std::sqrt(pa.Mass()))) {
            return false;
        }
    }
    return true;
}

/// Signaturen der Bereiche aus festen IDs bilden und übernehmen; waren es dieselben Bereiche, die Schlüssel der Schritte
/// mit übersetzen
void Profiles::adopt(Regions& regions, const Part::TopoShape& sketchShape)
{
    // Signaturen aus den festen Geometrie-IDs der Skizze ("g12") statt laufender Kantennummern: löscht man andere
    // Geometrie, rutschen die Nummern, und ein Schritt fand still ein fremdes Profil (gleiche Nummern, andere Kanten)
    for (std::string& signature : regions.signatures) {
        std::string ids;
        std::stringstream in(signature);
        for (std::string t; std::getline(in, t, ',');) {
            const Data::MappedName mapped = sketchShape.getMappedName(
                Data::IndexedName::fromConst("Edge", std::atoi(t.c_str()) + 1));
            std::string id = mapped ? mapped.toString() : std::string();
            id = id.substr(0, id.find(';'));
            // Projizierte Geometrie ("e5;SKT") hat ebenfalls eine feste Nummer: als "x5". Vorher fiel sie auf die laufende
            // Kantennummer zurück, die sich mit jeder neuen Linie verschiebt; nach einer Skizzenänderung fand ein Schritt
            // seine Profile nicht mehr und wurde leer (ConceptKey). "e<Kante>" bleibt nur für Kanten ohne Namen.
            const bool external = id.size() > 1 && id[0] == 'e' && std::isdigit(static_cast<unsigned char>(id[1]));
            ids += (ids.empty() ? "" : ",") + (id.starts_with("g") ? id : external ? "x" + id.substr(1) : "e" + t);
        }
        signature = ids;
    }
    // Dieselben Bereiche wie vorher, aber andere Signaturen (ältere Datei: projizierte Kanten mit laufender Nummer): die
    // gespeicherten Schlüssel der Schritte gleich mit übersetzen, solange die Zuordnung über die Lage noch eindeutig ist.
    // Sonst fände ein Schritt nach der nächsten Skizzenänderung über die alte Nummer ein fremdes Profil.
    const auto& old = Signatures.getValues();
    if (old.size() == regions.signatures.size() && old != regions.signatures && sameRegions(Shape.getShape(), Placement.getValue(), regions.shape)) {
        std::map<std::string, std::string> renamed;
        for (size_t k = 0; k < old.size(); ++k) {
            if (std::ranges::count(old, old[k]) == 1) {
                renamed[old[k]] = regions.signatures[k];
            }
        }
        for (App::DocumentObject* user : getInList()) {
            auto keys = dynamic_cast<App::PropertyStringList*>(user->getPropertyByName("ProfileKeys"));
            auto link = dynamic_cast<App::PropertyLinkSub*>(user->getPropertyByName("Profile"));
            if (!keys || !link || link->getValue() != this) {
                continue;
            }
            auto values = keys->getValues();
            for (auto& key : values) {
                if (auto it = renamed.find(key); it != renamed.end()) {
                    key = it->second;
                }
            }
            keys->setValues(values);
        }
    }
    if (old != regions.signatures) {
        PreviousShape.setValue(Shape.getShape());
        PreviousSignatures.setValues(old);
    }
    Signatures.setValues(regions.signatures);
}

App::DocumentObjectExecReturn* Profiles::execute()
{
    auto sketch = freecad_cast<Part::Feature*>(Sketch.getValue());
    if (!sketch) {
        return new App::DocumentObjectExecReturn("No sketch linked");
    }
    if (paused) {
        skipped = true;
        return StdReturn;
    }
    // In Skizzen-Koordinaten (XY-Ebene) rechnen, Ergebnis wieder auf die Skizzen-Lage setzen
    const TopoDS_Shape local = sketch->Shape.getShape().getShape().Located(TopLoc_Location());
    // Im Hintergrund vorgerechnet (beim Verlassen der Skizze) und für genau diese Skizzenform: nehmen, notfalls darauf
    // warten. Sonst (Skizze inzwischen geändert, nichts vorgerechnet) hier rechnen.
    Regions regions;
    if (background.valid() && backgroundInput.IsSame(local)) {
        regions = background.get();
    }
    else {
        regions = computeRegions(local);
    }
    background = {};
    backgroundInput.Nullify();
    if (!regions.error.empty()) {
        return new App::DocumentObjectExecReturn(regions.error);
    }
    adopt(regions, sketch->Shape.getShape());
    // Lage über die Placement-Eigenschaft: Part::Feature überschreibt beim Recompute die Shape-Lage damit
    Placement.setValue(sketch->Placement.getValue());
    Shape.setValue(regions.shape);
    return StdReturn;
}

void Profiles::onDocumentRestored()
{
    Part::Feature::onDocumentRestored();
    // "e12" in einer Signatur war früher auch eine projizierte Kante mit ihrer laufenden Nummer; heute heißt sie "x3".
    // Dann die Signaturen neu bilden; adopt übersetzt dabei die Schlüssel der Schritte (gleiche Bereiche, neue Namen)
    auto sketch = freecad_cast<Part::Feature*>(Sketch.getValue());
    if (!sketch) {
        return;
    }
    const Part::TopoShape shape = sketch->Shape.getShape();
    for (const auto& signature : Signatures.getValues()) {
        std::stringstream in(signature);
        for (std::string t; std::getline(in, t, ',');) {
            if (t.size() < 2 || t[0] != 'e' || !std::isdigit(static_cast<unsigned char>(t[1]))) {
                continue;
            }
            const Data::MappedName mapped = shape.getMappedName(Data::IndexedName::fromConst("Edge", std::atoi(t.c_str() + 1) + 1));
            const std::string name = mapped ? mapped.toString() : std::string();
            if (name.size() > 1 && name[0] == 'e' && std::isdigit(static_cast<unsigned char>(name[1]))) {
                // gleich hier umstellen: was beim Laden zum Neuberechnen markiert wird, verwirft FreeCAD danach
                Regions regions = computeRegions(shape.getShape().Located(TopLoc_Location()));
                if (regions.error.empty()) {
                    adopt(regions, shape);
                }
                return;
            }
        }
    }
}

void Profiles::computeInBackground()
{
    auto sketch = freecad_cast<Part::Feature*>(Sketch.getValue());
    if (!sketch) {
        return;
    }
    backgroundInput = sketch->Shape.getShape().getShape().Located(TopLoc_Location());
    std::packaged_task<Regions()> task([input = backgroundInput] { return computeRegions(input); });
    background = task.get_future().share();
    std::thread(std::move(task)).detach();  // hält nur eine Kopie der Form, darf das Objekt überleben
}

bool Profiles::computingInBackground() const
{
    return background.valid() && background.wait_for(std::chrono::seconds(0)) != std::future_status::ready;
}

namespace
{
/// Die Fläche ohne lose Kanten in ihrem Inneren. Eine offene Linie mitten in einem Profil (berührt den Rand nicht)
/// lässt der Splitter als innere Kante in der Fläche stehen; jeder Körper daraus bekam eine Phantomkante auf Deck- und
/// Bodenfläche, an der z. B. eine Fase am Rand scheiterte (Härtetest 2, 26.11.: Linie im Kreis eines Zapfens)
TopoDS_Face withoutLooseEdges(const TopoDS_Face& face)
{
    const auto loose = [](const TopoDS_Shape& s) {
        return s.Orientation() == TopAbs_INTERNAL || s.Orientation() == TopAbs_EXTERNAL;
    };
    BRep_Builder builder;
    TopoDS_Shape clean = face.EmptyCopied();
    bool dropped = false;
    for (TopoDS_Iterator it(face, Standard_False); it.More(); it.Next()) {
        TopoDS_Shape child = it.Value();
        if (loose(child)) {
            dropped = true;
            continue;
        }
        if (child.ShapeType() == TopAbs_WIRE) {
            TopoDS_Wire wire;
            builder.MakeWire(wire);
            bool cut = false;
            for (TopoDS_Iterator e(child, Standard_False); e.More(); e.Next()) {
                if (loose(e.Value())) {
                    cut = true;
                }
                else {
                    builder.Add(wire, e.Value());
                }
            }
            if (cut) {
                dropped = true;
                wire.Closed(Standard_True);
                wire.Orientation(child.Orientation());
                child = wire;
            }
        }
        builder.Add(clean, child);
    }
    return dropped ? TopoDS::Face(clean) : face;
}
}  // namespace

Profiles::Regions Profiles::computeRegions(const TopoDS_Shape& local)
{
    TopTools_ListOfShape edges;
    for (TopExp_Explorer ex(local, TopAbs_EDGE); ex.More(); ex.Next()) {
        edges.Append(ex.Current());
    }
    Regions out;
    if (edges.IsEmpty()) {
        return out;
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
    splitter.SetRunParallel(true);   // DXF-Importe bringen tausende Kanten mit
    splitter.SetNonDestructive(true);  // die Skizzenform nicht anfassen: der Hauptthread liest sie währenddessen
    // Fast deckungsgleiche Linien (von Hand auf eine andere gezeichnet, 0,00002 mm daneben) gelten als eine. Ohne das
    // entschied der Zufall: mal ein Spalt (Fläche 0), mal eine Linie, je nachdem, was sonst noch in der Skizze lag;
    // eine neue Linie weit weg ließ die Trennung zwischen einer Lasche und der großen Innenfläche verschwinden, die
    // Lasche wurde still zur ganzen Innenfläche (ConceptKey, Härtetest Seed 19, 26.11.: Basis 201 -> 773 cm³)
    splitter.SetFuzzyValue(1e-4);
    splitter.Build();
    if (!splitter.IsDone()) {
        out.error = "Could not compute sketch profiles";
        return out;
    }

    // Welche Skizzenkante steckt hinter jedem Kantenstück? (für die Profil-Signaturen)
    TopTools_DataMapOfShapeInteger source;
    int edgeIndex = 0;
    for (TopTools_ListOfShape::Iterator it(edges); it.More(); it.Next(), ++edgeIndex) {
        source.Bind(it.Value(), edgeIndex);
        for (TopTools_ListOfShape::Iterator piece(splitter.Modified(it.Value())); piece.More(); piece.Next()) {
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
            const TopoDS_Face region = withoutLooseEdges(TopoDS::Face(ex.Current()));
            GProp_GProps props;
            BRepGProp::SurfaceProperties(region, props);
            std::set<int> ids;
            for (TopExp_Explorer ed(region, TopAbs_EDGE); ed.More(); ed.Next()) {
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
            regions.push_back({region, props.CentreOfMass(), signature});
        }
    }
    // Feste Reihenfolge (links nach rechts, unten nach oben); Extrude & Co. finden ihre Profile zusätzlich
    // über die Signaturen wieder, wenn sich die Nummerierung durch Skizzenänderungen verschiebt
    std::ranges::sort(regions, [](const Region& a, const Region& b) {
        return a.center.X() != b.center.X() ? a.center.X() < b.center.X() : a.center.Y() < b.center.Y();
    });

    std::vector<Part::TopoShape> faces;
    for (auto& r : regions) {
        faces.emplace_back(r.face);
        out.signatures.push_back(r.signature);
    }
    if (!faces.empty()) {
        out.shape.makeElementCompound(faces);
    }
    return out;
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
    // Was ein Schritt sich über seine gewählten Kanten und Flächen merkt (Name, Lage), gilt vom letzten Mal, als er
    // rechnete. Scheitert er, bleibt es dabei: in einem kaputten Zwischenstand (Platte kurz 4 mm breit, alle Rundungen
    // rot) überschrieb er es sonst mit dem, was dort gerade lag, und fand nach dem Zurückstellen eine fremde Kante,
    // die zufällig an der gemerkten Stelle lag, ohne Warnung (Härtetest 2, 26.11.)
    auto dressUp = dynamic_cast<DressUp*>(this);
    const std::vector<std::string> maps = dressUp ? dressUp->ElementMaps.getValues() : std::vector<std::string>();
    const std::vector<std::string> hints = dressUp ? dressUp->ElementHints.getValues() : std::vector<std::string>();
    App::DocumentObjectExecReturn* result = compute();
    if (dressUp && result && result != StdReturn) {
        dressUp->ElementMaps.setValues(maps);
        dressUp->ElementHints.setValues(hints);
    }
    // Wie Fusion: ein Schritt, dessen Profil weggefallen ist, wird übersprungen (Warnung in der Timeline, Körper
    // unverändert) statt rot zu werden. Ein Fehler hielte das Neuberechnen aller späteren Schritte an, auch neue
    // Extrudes kämen nie an ("Sketch has no closed profile").
    if (result && result != StdReturn && result->Why == LostProfile) {
        delete result;
        std::vector<Part::TopoShape> results;
        for (int i = 0; i < Bodies.getSize(); ++i) {
            results.push_back(baseShape(i));
        }
        setResults(results);
        Warning.setValue(LostProfile);
        return StdReturn;
    }
    if (result == StdReturn && std::string(Warning.getValue()) == LostProfile) {
        Warning.setValue("");  // wieder ein Profil gewählt
    }
    if (result && result != StdReturn) {
        // Phase 14, wie Fusion: rot (der Fehler bleibt), aber der Körper geht ohne diesen Schritt weiter; die späteren
        // Schritte rechnen damit (recomputeDependentsOnError), statt alle anzuhalten
        std::vector<Part::TopoShape> results;
        for (int i = 0; i < Bodies.getSize(); ++i) {
            results.push_back(baseShape(i));
        }
        setResults(results);
    }
    return result;
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

App::DocumentObjectExecReturn* Feature::applyTool(const Part::TopoShape& toolIn)
{
    const Part::TopoShape& tool = toolIn;  // in Koordinaten der eigenen Komponente
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
        // 13.5: ein Schnitt, der (nach einer späteren Änderung davor) nichts mehr trifft, lief still ins Leere
        bool missesAll = op() == Op::Cut;
        bool addsNothing = op() == Op::Join;
        const auto volume = [](const Part::TopoShape& s) {
            GProp_GProps props;
            BRepGProp::VolumeProperties(s.getShape(), props);
            return props.Mass();
        };
        for (size_t i = 0; i < bodies.size(); ++i) {
            auto base = freecad_cast<Feature*>(bases[i]);
            if (!base) {
                return new App::DocumentObjectExecReturn("Body has no previous feature");
            }
            const Part::TopoShape baseShape = base->shapeFor(bodies[i]);
            const Part::TopoShape tool = toolFor(i, toolIn);
            Part::TopoShape res(0, getDocument()->getStringHasher());
            switch (op()) {
                case Op::Join:
                    res.makeElementFuse({baseShape, tool});
                    addsNothing = addsNothing && !res.isNull()
                        && std::abs(volume(res) - volume(baseShape)) < Precision::Confusion();
                    break;
                case Op::Cut:
                    res.makeElementCut({baseShape, tool});
                    missesAll = missesAll && !res.isNull()
                        && std::abs(volume(res) - volume(baseShape)) < Precision::Confusion();
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
        if (missesAll) {
            Warning.setValue(CutMisses);
        }
        else if (addsNothing) {
            Warning.setValue(JoinInside);
        }
        else if (std::string(Warning.getValue()) == CutMisses || std::string(Warning.getValue()) == JoinInside) {
            Warning.setValue("");  // trifft wieder
        }
    }

    setResults(results);
    return StdReturn;
}

Part::TopoShape Feature::toolFor(size_t i, const Part::TopoShape& tool) const
{
    // Phase 11.8: Körper einer anderen Komponente -> Werkzeug in deren Koordinaten (Cut durch alles darunter)
    const Base::Placement here = Design::componentOf(this)->globalPlacement();
    const Base::Matrix4D m = (Design::componentOf(Bodies.getValues()[i])->globalPlacement().inverse() * here).toMatrix();
    return m.isUnity() ? tool
                       : Part::TopoShape(0, getDocument()->getStringHasher())
                             .makeElementTransform(tool, m, nullptr, Part::CheckScale::noScaleCheck, Part::CopyType::copy);
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
    ADD_PROPERTY_TYPE(StartOffset, (0.0), "Parameters", App::Prop_None,
                      "Start the extrusion this far from the sketch plane; negative goes below it");
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
    const Base::Vector3d normal = sketch->Placement.getValue().getRotation().multVec(Base::Vector3d(0, 0, 1));

    // Startversatz: das Profil vorher parallel zur Skizzenebene verschieben, unabhängig von "Flip direction"
    if (std::abs(StartOffset.getValue()) > Precision::Confusion()) {
        Base::Matrix4D mov;
        mov.move(normal * StartOffset.getValue());
        for (auto& face : faces) {
            face = Part::TopoShape(0, hasher).makeElementTransform(face, mov);
        }
    }

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

    Base::Vector3d n = Reversed.getValue() ? -normal : normal;
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
            prisms.push_back(Part::TopoShape(0, hasher).makeElementPrism(withoutTinyEdges(base), gp_Vec(v.x, v.y, v.z)));
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

void Revolve::axisLine(long axisIndex, const Base::Placement& sketch, Base::Vector3d& origin, Base::Vector3d& dir) const
{
    origin = dir = Base::Vector3d();
    switch (axisIndex) {
        case 0:
            origin = sketch.getPosition();
            dir = sketch.getRotation().multVec(Base::Vector3d(1, 0, 0));
            break;
        case 1:
            origin = sketch.getPosition();
            dir = sketch.getRotation().multVec(Base::Vector3d(0, 1, 0));
            break;
        default:
            dir[axisIndex - 2] = 1;
            break;
    }
    if (Reversed.getValue()) {
        dir = -dir;
    }
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

    Base::Vector3d origin, dir;
    axisLine(axisIndex, sketch->Placement.getValue(), origin, dir);
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
    ADD_PROPERTY_TYPE(WarnedMaps, (), "DressUp", App::PropertyType(App::Prop_Output | App::Prop_Hidden),
                      "Traceable names of the elements when the step last had to guess");
    ADD_PROPERTY_TYPE(WarnedHints, (), "DressUp", App::PropertyType(App::Prop_Output | App::Prop_Hidden),
                      "Where the selected elements were when they last had to be guessed");
    ADD_PROPERTY_TYPE(ElementBodies, (), "DressUp", App::Prop_Hidden, "Index in Bodies of each selected element");
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

/// Element gleicher Art, das am besten zu hint passt (Lage und Größe); leer, wenn keins da ist. among: nur unter diesen.
/// exact: genau eins liegt dort und ist gleich groß (bis auf die Rundung des Hinweises), es ist dasselbe Element
std::string closestElement(const Part::TopoShape& shape, const std::string& name, const std::string& hint,
                           const std::vector<std::string>& among = {}, bool* exact = nullptr)
{
    if (exact) {
        *exact = false;
    }
    std::istringstream in(hint);
    double x = 0, y = 0, z = 0, size = 0;
    if (!(in >> x >> y >> z >> size)) {
        return {};
    }
    const bool face = name.rfind("Face", 0) == 0;
    const TopAbs_ShapeEnum type = face ? TopAbs_FACE : TopAbs_EDGE;
    std::string best;
    double bestScore = 1e300;
    std::vector<std::string> candidates = among;
    const int count = among.empty() ? shape.countSubShapes(type) : 0;
    for (int i = 1; i <= count; ++i) {
        candidates.push_back((face ? "Face" : "Edge") + std::to_string(i));
    }
    constexpr double same = 1e-3;  // der Hinweis steht mit 6 Stellen in der Datei
    int matches = 0;
    for (const std::string& candidate : candidates) {
        std::istringstream h(elementHint(shape.getSubShape(candidate.c_str())));
        double cx = 0, cy = 0, cz = 0, cs = 0;
        h >> cx >> cy >> cz >> cs;
        const double score = std::hypot(cx - x, cy - y, cz - z) + std::abs(cs - size) / std::max(1.0, size) * 10;
        matches += score < same ? 1 : 0;
        if (score < bestScore) {
            bestScore = score;
            best = candidate;
        }
    }
    if (exact) {
        *exact = matches == 1;
    }
    return best;
}
/// Teilstücke einer geteilten ebenen Fläche: face und die Flächen derselben Ebene, die über Kanten zusammenhängen.
/// Leer, wenn sie zusammen nicht genau die Fläche des Hinweises ergeben (Größe und Schwerpunkt)
std::vector<TopoDS_Shape> splitPieces(const TopoDS_Shape& shape, const TopoDS_Face& face, const std::string& hint)
{
    std::istringstream in(hint);
    double x = 0, y = 0, z = 0, size = 0;
    if (!(in >> x >> y >> z >> size) || size <= 0) {
        return {};
    }
    BRepAdaptor_Surface surface(face);
    if (surface.GetType() != GeomAbs_Plane) {
        return {};
    }
    const gp_Pln plane = surface.Plane();
    GProp_GProps own;
    BRepGProp::SurfaceProperties(face, own);
    if (std::abs(own.Mass() - size) < 1e-3 * std::max(1.0, size)) {
        return {};  // nicht kleiner geworden: nicht geteilt
    }
    TopTools_IndexedDataMapOfShapeListOfShape facesOf;
    TopExp::MapShapesAndAncestors(shape, TopAbs_EDGE, TopAbs_FACE, facesOf);
    std::vector<TopoDS_Shape> pieces {face};
    TopTools_IndexedMapOfShape inside;
    inside.Add(face);
    for (size_t k = 0; k < pieces.size(); ++k) {
        for (TopExp_Explorer e(pieces[k], TopAbs_EDGE); e.More(); e.Next()) {
            const int at = facesOf.FindIndex(e.Current());
            if (at == 0) {
                continue;
            }
            for (TopTools_ListIteratorOfListOfShape it(facesOf(at)); it.More(); it.Next()) {
                const TopoDS_Face next = TopoDS::Face(it.Value());
                if (inside.Contains(next)) {
                    continue;
                }
                BRepAdaptor_Surface s(next);
                if (s.GetType() == GeomAbs_Plane && s.Plane().Axis().Direction().IsParallel(plane.Axis().Direction(), 1e-9)
                    && plane.Distance(s.Plane().Location()) < 1e-6) {
                    inside.Add(next);
                    pieces.push_back(next);
                }
            }
        }
    }
    double area = 0;
    gp_XYZ moment;
    for (const auto& piece : pieces) {
        GProp_GProps p;
        BRepGProp::SurfaceProperties(piece, p);
        area += p.Mass();
        moment += p.CentreOfMass().XYZ() * p.Mass();
    }
    const gp_XYZ centre = area > 0 ? moment / area : gp_XYZ();
    if (std::abs(area - size) > 1e-3 * std::max(1.0, size) || (centre - gp_XYZ(x, y, z)).Modulus() > 1e-3 * (1 + std::sqrt(size))) {
        return {};
    }
    return pieces;
}
}  // namespace

std::vector<Part::TopoShape> DressUp::elements(const Part::TopoShape& shape, TopAbs_ShapeEnum type, size_t body)
{
    const std::vector<long> owners = ElementBodies.getValues();
    const auto mine = [&owners, body](size_t i) { return i < owners.size() ? size_t(owners[i]) == body : body == 0; };
    // Gewählte Elemente über ihre verfolgbaren Namen wiederfinden (topologische Benennung):
    // 1. derselbe Name existiert noch, 2. ein Element, das laut Entstehungsgeschichte daraus hervorging
    //    (z. B. wenn davor ein Feature eingefügt wurde), 3. sonst die ursprüngliche Nummer.
    std::vector<std::string> names = Edges.getValues();
    std::vector<std::string> maps = ElementMaps.getValues();
    std::vector<std::string> hints = ElementHints.getValues();
    maps.resize(names.size());
    hints.resize(names.size());
    const std::vector<std::string> before = hints;  // Lage vor diesem Durchgang (für WarnedHints)
    const std::vector<std::string> beforeMaps = maps;
    if (!std::string(Warning.getValue()).starts_with(ModelChanged)) {
        WarnedHints.setValues(std::vector<std::string>());  // bestätigt ("Sieht richtig aus") oder nie gewarnt
        WarnedMaps.setValues(std::vector<std::string>());
    }
    // Solange die Warnung steht (es wurde geraten, niemand hat bestätigt), gilt weiter, was der Mensch gewählt hatte:
    // ist das Element von damals wieder da (derselbe verfolgbare Name, oder genau eins unverändert an der alten Stelle),
    // nimmt der Schritt es wieder. Vorher blieb er für immer bei der geratenen Ersatzkante (Härtetest 2, 26.11.: Bohrung
    // kurz viel zu groß, die Ecke war weg; nach dem Zurückstellen saßen die Eckrundungen an fremden Kanten)
    const std::vector<std::string> pickedHints = WarnedHints.getValues();
    const std::vector<std::string> pickedMaps = WarnedMaps.getValues();
    std::vector<bool> restored(names.size(), false);
    // Ein "Name", der nur eine Nummer ist ("Edge2", auch mit Anhang späterer Schritte), ist nicht verfolgbar. Ein
    // späterer Schritt (die Rundung davor) verpackt ihn in ein Kürzel ("#28d:1"), das verfolgbar aussieht: auspacken
    const auto numberOnly = [&shape](const std::string& name) {
        static const std::regex number("(Face|Edge|Vertex)[0-9]+(;.*)?");
        if (std::regex_match(name, number)) {
            return true;
        }
        bool found = false;  // die Entstehung zurückverfolgen: hieß es irgendwann nur nach seiner Nummer?
        if (!shape.getElementMap().empty()) {
            shape.traceElement(Data::MappedName(name), [&found](const Data::MappedName& step, int, long, long) {
                found = std::regex_match(step.toString(), number);
                return found;
            });
        }
        return found;
    };
    std::vector<std::string> uncertain;
    std::vector<std::vector<TopoDS_Shape>> extra(names.size());  ///< weitere Teilstücke einer geteilten Fläche
    App::DocumentObject* base = BaseFeatures.getSize() > int(body) ? BaseFeatures.getValues()[body] : nullptr;
    for (size_t i = 0; i < names.size(); ++i) {
        if (!mine(i)) {
            continue;
        }
        if (pickedHints.size() == names.size()) {
            std::string picked;
            const std::string old = i < pickedMaps.size() ? pickedMaps[i] : std::string();
            const Data::IndexedName idx = old.empty() ? Data::IndexedName() : shape.getIndexedName(Data::MappedName(old));
            if (idx && !numberOnly(old)) {
                picked = idx.toString();
            }
            else {
                bool exact = false;
                const std::string at = closestElement(shape, names[i], pickedHints[i], {}, &exact);
                picked = exact ? at : std::string();
            }
            if (!picked.empty()) {
                names[i] = picked;
                maps[i].clear();  // unten neu aus dem Element
                restored[i] = true;
            }
        }
        if (!maps[i].empty()) {
            bool found = false;
            const Data::IndexedName idx = shape.getIndexedName(Data::MappedName(maps[i]));
            // Ein "Name", der nur die Nummer ist ("Face1": ohne verfolgte Entstehung), zeigt nach einer Änderung weiter vorn
            // oft auf ein anderes Element. Nur trauen, wenn es noch so aussieht wie gespeichert; sonst unten nach Lage und
            // Größe (ConceptKey: Drücken/Ziehen zog nach einer Linie in der Grundskizze eine fremde Fläche, Basis halbiert)
            const bool trusted = idx && !numberOnly(maps[i]);
            const auto looksSame = [&](const std::string& name) {
                const TopoDS_Shape sub = shape.getSubShape(name.c_str(), true);
                if (sub.IsNull() || hints[i].empty()) {
                    return !sub.IsNull();
                }
                std::istringstream a(hints[i]), b(elementHint(sub));
                double x0, y0, z0, s0, x1, y1, z1, s1;
                return (a >> x0 >> y0 >> z0 >> s0) && (b >> x1 >> y1 >> z1 >> s1)
                    && std::hypot(x0 - x1, y0 - y1, z0 - z1) + std::abs(s0 - s1) / std::max(1.0, s0) * 10 < 1e-3;
            };
            if (idx && (trusted || looksSame(idx.toString()))) {
                names[i] = idx.toString();
                found = true;
            }
            else if (base) {
                const auto related = Part::Feature::getRelatedElements(
                    base, (std::string(Data::ELEMENT_MAP_PREFIX) + maps[i]).c_str()
                );
                // Ober- und Unterseite eines Prismas gehen beide aus derselben Profilfläche hervor: unter mehreren
                // verwandten Elementen das nach Lage und Größe passendste, nicht einfach das erste
                std::vector<std::string> among;
                for (const auto& r : related) {
                    among.push_back(r.index.toString());
                }
                if (!among.empty()) {
                    const std::string best = among.size() > 1 ? closestElement(shape, names[i], hints[i], among) : "";
                    const std::string related = best.empty() ? among.front() : best;
                    // Die Entstehungsgeschichte nannte ein Element, das ganz anders aussieht als gespeichert (ConceptKey:
                    // statt der Randfläche eine 57-mm²-Fläche weiter unten, still), und genau ein Element liegt unverändert
                    // an der alten Stelle: das ist es. Sonst gilt die Geschichte (die Fläche hat sich wirklich verändert)
                    bool exact = false;
                    const std::string same = looksSame(related) ? "" : closestElement(shape, names[i], hints[i], {}, &exact);
                    names[i] = exact ? same : related;  // gewachsene Oberseite nach Löschen einer Rundung: die Geschichte
                    found = true;
                }
            }
            // Name verloren: nicht still die alte Nummer nehmen, sondern das Element, das nach Lage und Größe am
            // besten passt, und warnen (Idee 6, "War es diese Kante?"). Liegt genau ein Element unverändert an der alten
            // Stelle, ist es dieselbe Kante (ein früherer Schritt wurde gelöscht und ihr Name trägt ihn nicht mehr):
            // keine Warnung
            if (!found) {
                bool exact = false;
                const std::string guess = closestElement(shape, names[i], hints[i], {}, &exact);
                if (!guess.empty()) {
                    names[i] = guess;
                }
                if (!exact) {
                    uncertain.push_back(names[i]);
                }
            }
        }
        const Data::MappedName mapped = shape.getMappedName(Data::IndexedName(names[i].c_str()));
        if (mapped) {
            maps[i] = mapped.toString();
        }
        const TopoDS_Shape sub = shape.getSubShape(names[i].c_str(), true);
        // Fläche durch eine Änderung weiter vorn geteilt (Linie quer durch die Grundskizze): der Name trifft nur ein
        // Teilstück. Ergeben es und seine Nachbarn in derselben Ebene genau die alte Fläche (Größe und Schwerpunkt wie
        // gespeichert), alle Teile nehmen; der Hinweis bleibt der der ganzen Fläche. Vorher zog Drücken/Ziehen still nur
        // ein Stück (ConceptKey, Härtetest Seeds 4/9: Basis −10 cm³)
        if (!sub.IsNull() && sub.ShapeType() == TopAbs_FACE && !hints[i].empty()) {
            const auto pieces = splitPieces(shape.getShape(), TopoDS::Face(sub), hints[i]);
            if (pieces.size() > 1) {
                for (const TopoDS_Shape& piece : pieces) {
                    if (!piece.IsSame(sub)) {
                        extra[i].push_back(piece);
                    }
                }
                continue;  // Hinweis der ganzen Fläche behalten
            }
        }
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
        Warning.setValue(ModelChanged + list);
        ErrorElements.setValues(uncertain);
        if (WarnedHints.getSize() == 0) {
            WarnedHints.setValues(before);  // wo der Mensch die Elemente gewählt hatte
            WarnedMaps.setValues(beforeMaps);
        }
    }
    else if (WarnedHints.getSize() == int(hints.size())) {
        // Phase 14: alle Elemente ohne Raten wieder genau dort, wo sie vor dem Raten lagen (Rückgängig nach einer
        // drastischen Änderung): es gibt nichts mehr zu prüfen. Sonst blieb die Warnung veraltet stehen; sie entstand
        // beim Neuberechnen außerhalb der Transaktion, das Rückgängig nicht zurückholt
        const auto near = [](const std::string& a, const std::string& b) {
            std::istringstream ia(a), ib(b);
            double x0, y0, z0, s0, x1, y1, z1, s1;
            return (ia >> x0 >> y0 >> z0 >> s0) && (ib >> x1 >> y1 >> z1 >> s1)
                && std::hypot(x0 - x1, y0 - y1, z0 - z1) + std::abs(s0 - s1) / std::max(1.0, s0) * 10 < 1e-3;
        };
        const auto& warned = WarnedHints.getValues();
        bool back = true;
        for (size_t i = 0; i < hints.size(); ++i) {
            back = back && (!mine(i) || restored[i] || near(hints[i], warned[i]));
        }
        if (back) {
            Warning.setValue("");
            WarnedHints.setValues(std::vector<std::string>());
            WarnedMaps.setValues(std::vector<std::string>());
        }
    }

    std::vector<Part::TopoShape> result;
    TopTools_IndexedMapOfShape seen;
    for (size_t i = 0; i < names.size(); ++i) {
        if (!mine(i)) {
            continue;
        }
        const Part::TopoShape sub = shape.getSubTopoShape(names[i].c_str(), true);
        for (const auto& el : sub.isNull() ? std::vector<Part::TopoShape>() : sub.getSubTopoShapes(type)) {
            if (seen.Add(el.getShape()) == seen.Extent()) {
                result.push_back(el);
            }
        }
        for (const TopoDS_Shape& piece : extra[i]) {
            if (seen.Add(piece) == seen.Extent()) {
                result.push_back(shape.getSubTopoShape(TopAbs_FACE, shape.findShape(piece)));
            }
        }
    }
    return result;
}

namespace
{
/// Druckrichtung des Designs in Koordinaten der Komponente von obj
gp_Dir printUpIn(const App::DocumentObject* obj)
{
    Base::Vector3d up = Design::printUp(obj->getDocument());
    Design::componentOf(obj)->globalPlacement().getRotation().inverse().multVec(up, up);
    return gp_Dir(up.x, up.y, up.z);
}

/// Hinge die Rundung dieser Kante beim Drucken über? Die Winkelhalbierende der beiden Flächennormalen (aus dem Körper
/// heraus) zeigt dann deutlich nach unten: eine Unterkante. Senkrechte Kanten und Oberkanten drucken.
bool overhangingEdge(const TopoDS_Shape& shape, const TopoDS_Edge& edge, const gp_Dir& up)
{
    TopTools_IndexedDataMapOfShapeListOfShape facesOf;
    TopExp::MapShapesAndAncestors(shape, TopAbs_EDGE, TopAbs_FACE, facesOf);
    const TopTools_ListOfShape* faces = facesOf.Seek(edge);
    if (!faces || faces->Extent() != 2) {
        return false;
    }
    gp_Vec sum;
    for (TopTools_ListOfShape::Iterator f(*faces); f.More(); f.Next()) {
        const TopoDS_Face& face = TopoDS::Face(f.Value());
        BRepAdaptor_Curve2d curve(edge, face);
        const gp_Pnt2d uv = curve.Value((curve.FirstParameter() + curve.LastParameter()) / 2);
        gp_Pnt p;
        gp_Vec n;
        BRepGProp_Face(face).Normal(uv.X(), uv.Y(), p, n);
        if (n.Magnitude() < 1e-9) {
            return false;
        }
        sum += n.Normalized();
    }
    return sum.Magnitude() > 1e-9 && sum.Normalized().Dot(gp_Vec(up)) < -0.3;
}
}  // namespace

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
        return new App::DocumentObjectExecReturn(fillet ? "Radius must be greater than zero"
                                                        : "Distance must be greater than zero");
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
            // Druckbar (11.3): Unterkanten erst fasen (45°, gleicher Abstand), dann den Rest runden. Die übrigen
            // Kanten liegen nach dem Fasen auf denselben Kurven, nur gekürzt: dort wiederfinden.
            std::vector<Part::TopoShape> down, rest;
            const gp_Dir up = printUpIn(this);
            for (const auto& e : edges) {
                (f->PrintChamfer.getValue() && e.getShape().ShapeType() == TopAbs_EDGE
                         && overhangingEdge(shape.getShape(), TopoDS::Edge(e.getShape()), up)
                     ? down
                     : rest)
                    .push_back(e);
            }
            if (down.empty()) {
                res.makeElementFillet(shape, edges, size, end);
            }
            else {
                Part::TopoShape chamfered(0, getDocument()->getStringHasher());
                chamfered.makeElementChamfer(shape, down, Part::ChamferType::equalDistance, size, size);
                std::vector<Part::TopoShape> again;
                for (const auto& r : rest) {
                    for (const auto& candidate : chamfered.getSubTopoShapes(TopAbs_EDGE)) {
                        BRepAdaptor_Curve c(TopoDS::Edge(candidate.getShape()));
                        const TopoDS_Vertex mid = BRepBuilderAPI_MakeVertex(c.Value((c.FirstParameter() + c.LastParameter()) / 2));
                        BRepExtrema_DistShapeShape dist(mid, r.getShape());
                        if (dist.IsDone() && dist.Value() < 1e-6) {
                            again.push_back(candidate);
                            break;
                        }
                    }
                }
                if (again.empty()) {
                    res = chamfered;
                }
                else {
                    res.makeElementFillet(chamfered, again, size, end);
                }
            }
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
    // 12.14 Teilergebnis: geht es mit allen Kanten nicht, werden die gerundet bzw. gefast, die einzeln gehen; die
    // anderen sind markiert (Warnung statt Fehler), der Vorschlag unten gilt weiter für alle
    static const std::string someFailed[2] = {"Some edges could not be chamfered; the others are",
                                              "Some edges could not be rounded; the others are"};
    std::vector<std::string> bad;
    if ((res.isNull() || !res.isValid()) && edges.size() > 1
        && !(fillet && static_cast<Fillet*>(this)->PrintChamfer.getValue())) {
        const auto attempt = [&](const std::vector<Part::TopoShape>& list) {
            Part::TopoShape out(0, getDocument()->getStringHasher());
            try {
                if (fillet) {
                    auto f = static_cast<Fillet*>(this);
                    out.makeElementFillet(shape, list, size, f->Variable.getValue() ? f->RadiusEnd.getValue() : size);
                }
                else {
                    auto c = static_cast<Chamfer*>(this);
                    const long type = c->Type.getValue();
                    const double second = type == 1 ? c->Distance2.getValue() : type == 2 ? c->ChamferAngle.getValue() : size;
                    out.makeElementChamfer(shape, list, static_cast<Part::ChamferType>(type), size, second, nullptr,
                                           c->FlipSide.getValue() ? Part::Flip::flip : Part::Flip::none);
                }
            }
            catch (const Standard_Failure&) {
                return Part::TopoShape();
            }
            return out.isNull() || !out.isValid() ? Part::TopoShape() : out;
        };
        std::vector<Part::TopoShape> good;
        for (const auto& e : edges) {
            if (attempt({e}).isNull()) {
                bad.push_back(elementName(shape.getShape(), e.getShape()));
            }
            else {
                good.push_back(e);
            }
        }
        if (!good.empty() && !bad.empty()) {
            res = attempt(good);
        }
    }
    // gleicher Wert (Radius bzw. Abstand) an allen Kanten: geht er? (für den Vorschlag des größten, der geht)
    const auto works = [&](double s) {
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
    };
    if (res.isNull() || !res.isValid()) {
        ErrorElements.setValues(Edges.getValues());
        // Kante zwischen tangential anschließenden Flächen (Deckfläche eines schon gerundeten Quaders): dort ist nichts
        // zu runden, kein Wert ginge
        TopTools_IndexedDataMapOfShapeListOfShape facesOf;
        TopExp::MapShapesAndAncestors(shape.getShape(), TopAbs_EDGE, TopAbs_FACE, facesOf);
        for (const auto& e : edges) {
            const TopoDS_Edge& edge = TopoDS::Edge(e.getShape());
            const TopTools_ListOfShape* faces = facesOf.Seek(edge);
            if (!faces || faces->Extent() != 2) {
                continue;
            }
            gp_Vec normals[2];
            int i = 0;
            for (TopTools_ListOfShape::Iterator f(*faces); f.More(); f.Next()) {
                const TopoDS_Face& face = TopoDS::Face(f.Value());
                BRepAdaptor_Curve2d curve(edge, face);
                const gp_Pnt2d uv = curve.Value((curve.FirstParameter() + curve.LastParameter()) / 2);
                gp_Pnt p;
                BRepGProp_Face(face).Normal(uv.X(), uv.Y(), p, normals[i++]);
            }
            if (normals[0].Magnitude() > 1e-9 && normals[1].Magnitude() > 1e-9 && normals[0].Angle(normals[1]) < 1e-3) {
                return new App::DocumentObjectExecReturn(
                    "Some edges are already smooth (the faces meet tangentially); select only sharp edges");
            }
        }
        // Vorschlag: der größte Wert, der für diese Kanten noch geht (konstanter Radius bzw. gleicher Abstand)
        const double best = largestWorking(works);
        if (best > 0) {
            std::ostringstream label;
            label << (fillet ? "Use radius " : "Use distance ") << best << " mm";
            suggest(label.str(), "Size", best);
        }
        return new App::DocumentObjectExecReturn(failed);
    }
    if (!bad.empty()) {
        ErrorElements.setValues(bad);
        Warning.setValue(someFailed[fillet]);
        const double best = largestWorking(works);
        if (best > 0) {
            std::ostringstream label;
            label << (fillet ? "Use radius " : "Use distance ") << best << " mm";
            suggest(label.str(), "Size", best);
        }
    }
    else if (Warning.getValue() == someFailed[0] || Warning.getValue() == someFailed[1]) {
        Warning.setValue("");
        ErrorElements.setValues(std::vector<std::string>());
    }
    setResults({res});
    return StdReturn;
}

std::vector<Design::PrintFix> Design::printFixes(App::Document* doc)
{
    std::vector<PrintFix> fixes;
    const double minWall = App::GetApplication()
                               .GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD")
                               ->GetFloat("MinWall", 0.8);
    for (App::DocumentObject* obj : timeline(doc)) {
        auto feature = freecad_cast<Feature*>(obj);
        if (!feature || feature->Suppressed.getValue() || isRolledBack(feature)) {
            continue;
        }
        if (auto hole = freecad_cast<Hole*>(feature); hole && !hole->Teardrop.getValue()) {
            auto sketch = freecad_cast<App::GeoFeature*>(hole->Sketch.getValue());
            Base::Vector3d n;
            if (sketch) {
                sketch->Placement.getValue().getRotation().multVec(Base::Vector3d(0, 0, 1), n);
            }
            const gp_Dir up = printUpIn(hole);
            if (sketch && std::abs(n.x * up.X() + n.y * up.Y() + n.z * up.Z()) < 0.1) {
                fixes.push_back({hole, "Teardrop hole: prints without support", "Teardrop", 1});
            }
        }
        else if (auto fillet = freecad_cast<Fillet*>(feature); fillet && !fillet->PrintChamfer.getValue()) {
            auto base = fillet->BaseFeatures.getSize() ? freecad_cast<Feature*>(fillet->BaseFeatures.getValues().front()) : nullptr;
            if (!base || fillet->Bodies.getSize() == 0) {
                continue;
            }
            const Part::TopoShape before = base->shapeFor(fillet->Bodies.getValues().front());
            const gp_Dir up = printUpIn(fillet);
            for (const auto& name : fillet->Edges.getValues()) {
                const TopoDS_Shape edge = name.rfind("Edge", 0) == 0 ? before.getSubShape(name.c_str(), true) : TopoDS_Shape();
                if (!edge.IsNull() && overhangingEdge(before.getShape(), TopoDS::Edge(edge), up)) {
                    fixes.push_back({fillet, "Chamfer the bottom edges: no overhang", "PrintChamfer", 1});
                    break;
                }
            }
        }
        else if (auto shell = freecad_cast<Shell*>(feature); shell && shell->Size.getValue() < minWall - 1e-9) {
            fixes.push_back({shell, "Wall to %1 mm", "Size", minWall});
        }
        else if (auto extrude = freecad_cast<Extrude*>(feature);
                 extrude && extrude->Thin.getValue() && extrude->Thickness.getValue() < minWall - 1e-9) {
            fixes.push_back({extrude, "Wall to %1 mm", "Thickness", minWall});
        }
    }
    return fixes;
}

PROPERTY_SOURCE(Design::Fillet, Design::DressUp)
PROPERTY_SOURCE(Design::Chamfer, Design::DressUp)

Fillet::Fillet()
{
    ADD_PROPERTY_TYPE(Variable, (false), "Parameters", App::Prop_None, "Variable radius");
    ADD_PROPERTY_TYPE(RadiusEnd, (2.0), "Parameters", App::Prop_None, "Radius at the end of the edge");
    RadiusEnd.setStatus(App::Property::Hidden, true);
    ADD_PROPERTY_TYPE(PrintChamfer, (false), "Fillet", App::Prop_None,
                      "Bottom edges in the print direction get a 45° chamfer instead (no overhang)");
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
            if (faces.empty()) {
                // ganz geschlossen: ThickSolid braucht eine offene Fläche. Stattdessen den Körper um die Wand versetzen
                // und den Unterschied nehmen (innen: Hohlraum im Körper, außen: Hülle um ihn)
                Part::TopoShape other(0, getDocument()->getStringHasher());
                other.makeElementOffset(shape, Outside.getValue() ? thickness : -thickness, 1e-6, true, false, 0,
                                        Part::JoinType::intersection);
                r.makeElementCut(Outside.getValue() ? std::vector<Part::TopoShape> {other, shape}
                                                    : std::vector<Part::TopoShape> {shape, other});
            }
            else {
                r.makeElementThickSolid(shape, faces, Outside.getValue() ? thickness : -thickness, 1e-6, true, false, 0,
                                        Part::JoinType::intersection);
            }
        }
        catch (const Base::Exception&) {
            return Part::TopoShape();
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
        // geschlossene Hülle außen: der alte Körper wird zum Hohlraum, sie wiegt also weniger als er
        const bool sensible = Outside.getValue() ? after.Mass() > (faces.empty() ? 0 : before.Mass())
                                                 : after.Mass() > 0 && after.Mass() < before.Mass();
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
    ADD_PROPERTY_TYPE(AlignFrom, (""), "Move", App::Prop_Hidden, "Align: element of the moved body (before this step)");
    ADD_PROPERTY_TYPE(AlignTo, (nullptr), "Move", App::Prop_Hidden, "Align: element or plane it is aligned to");
    AlignTo.setScope(App::LinkScope::Global);
    Alignment.setStatus(App::Property::Output, true);  // compute() schreibt die zuletzt berechnete Lage hinein
    ADD_PROPERTY_TYPE(AxisReference, (nullptr), "Parameters", App::Prop_None, "Axis, edge or round face to rotate around");
    AxisReference.setScope(App::LinkScope::Global);
    Operation.setStatus(App::Property::Hidden, true);
}

App::DocumentObjectExecReturn* Move::compute()
{
    if (Bodies.getSize() == 0 || Bodies.getSize() != BaseFeatures.getSize()) {
        return new App::DocumentObjectExecReturn("Select one or more bodies");
    }
    // Align (B6): aus beiden Bezügen neu, damit die Ausrichtung Änderungen folgt; fehlt ein Bezug, die letzte Lage
    Base::Placement align = Alignment.getValue();
    if (AlignTo.getValue() && *AlignFrom.getValue()) {
        const TopoDS_Shape element = baseShape(0).getSubShape(AlignFrom.getValue(), true);
        Frame from, to;
        const auto& subs = AlignTo.getSubValues();
        if (!element.IsNull() && frameOf(element, from)
            && frameOf(AlignTo.getValue(), subs.empty() ? std::string() : subs.front(), to)) {
            // das Element in globalen Koordinaten (die Form liegt in der Komponente des Bodies)
            const Base::Placement comp = Design::componentOf(Bodies[0])->globalPlacement();
            Base::Vector3d p(from.point.X(), from.point.Y(), from.point.Z()), d(from.dir.X(), from.dir.Y(), from.dir.Z());
            comp.multVec(p, p);
            comp.getRotation().multVec(d, d);
            from.point = gp_Pnt(p.x, p.y, p.z);
            from.dir = gp_Dir(d.x, d.y, d.z);
            align = alignment(from, to);
            if (!align.isSame(Alignment.getValue(), 1e-12)) {
                Alignment.setValue(align);  // für den Fall, dass ein Bezug später fehlt
            }
            if (std::string(Warning.getValue()).rfind("Align lost", 0) == 0) {
                Warning.setValue("");  // Bezug wieder da
            }
        }
        else {
            Warning.setValue("Align lost one of its references; the body keeps its last position");
        }
    }
    std::vector<Part::TopoShape> results;
    for (int i = 0; i < Bodies.getSize(); ++i) {
        const Part::TopoShape base = baseShape(i);
        // global rechnen, dann in die Komponente des Bodies umrechnen
        const Base::Matrix4D toGlobal = Design::componentOf(Bodies[i])->globalPlacement().toMatrix();
        Base::BoundBox3d bb = base.getBoundBox().Transformed(toGlobal);
        bb = bb.Transformed(align.toMatrix());  // gedreht wird um die Mitte nach dem Ausrichten
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
        Base::Matrix4D mat = inComponent(Bodies[i], (move * rot * align).toMatrix());
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
        const bool full = std::abs(std::abs(total) - 360.0) < Precision::Angular();  // negativ: andersherum
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
        if (Spacing1.getValue() < 0) {  // im Rechteckmuster dreht ein negativer Abstand die Richtung um, hier geht das nicht
            error = "The spacing along a path must be greater than zero";
            return {};
        }
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
    ADD_PROPERTY_TYPE(Teardrop, (false), "Hole", App::Prop_None,
                      "Across the print direction: a 45° tip on top (teardrop) that prints without support");
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
            std::vector<Part::TopoShape> parts = holeShape(ax, r, depth, HoleType.getValue(), head,
                                                           HeadDepth.getValue(), CountersinkAngle.getValue(), lead);
            // Druckbar (11.3): quer zur Druckrichtung oben eine 45°-Spitze (Tropfenform) statt der flachen Decke des
            // Kreises, die ohne Stütze durchhängt. ponytail: nur der Schaft, Senkungen bleiben rund
            if (Teardrop.getValue()) {
                const gp_Vec along(dir);
                gp_Vec u(printUpIn(this));
                u -= along * u.Dot(along);
                if (u.Magnitude() > 0.99) {  // Achse waagrecht (höchstens ~8° geneigt)
                    u.Normalize();
                    const gp_Vec side = along.Crossed(u);
                    const gp_Pnt s = c.Translated(along * -lead);
                    const double k = r / std::sqrt(2.0);
                    BRepBuilderAPI_MakePolygon tip(s.Translated(u * (r * std::sqrt(2.0))), s.Translated(u * k + side * k), s,
                                                   s.Translated(u * k - side * k), true);
                    parts.emplace_back(BRepPrimAPI_MakePrism(BRepBuilderAPI_MakeFace(tip.Wire()).Face(), along * depth).Shape());
                }
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

PROPERTY_SOURCE(Design::RemoveFace, Design::DressUp)

RemoveFace::RemoveFace()
{
    Size.setStatus(App::Property::Hidden, true);
}

App::DocumentObjectExecReturn* RemoveFace::compute()
{
    if (Bodies.getSize() != 1 || BaseFeatures.getSize() != 1) {
        return new App::DocumentObjectExecReturn("Select faces of one body");
    }
    const Part::TopoShape shape = baseShape(0);
    const auto faces = elements(shape, TopAbs_FACE);
    if (faces.empty()) {
        return new App::DocumentObjectExecReturn("Select the faces to remove");
    }
    Part::TopoShape res;
    try {
        res = shape.makeElementDefeaturing(faces);
    }
    catch (const Base::Exception&) {
        res = Part::TopoShape();
    }
    catch (const Standard_Failure&) {
        res = Part::TopoShape();
    }
    // OCCT gibt manchmal still die unveränderte Form zurück (etwa für die Oberseite eines Quaders)
    const auto volume = [](const Part::TopoShape& s) {
        GProp_GProps props;
        BRepGProp::VolumeProperties(s.getShape(), props);
        return props.Mass();
    };
    if (res.isNull() || !res.isValid() || res.countSubShapes(TopAbs_SOLID) == 0
        || (res.countSubShapes(TopAbs_FACE) == shape.countSubShapes(TopAbs_FACE) && std::abs(volume(res) - volume(shape)) < 1e-9)) {
        return new App::DocumentObjectExecReturn("This face cannot be removed: the faces around it cannot close the gap");
    }
    setResults({res});
    return StdReturn;
}

PROPERTY_SOURCE(Design::PressPull, Design::DressUp)

PressPull::PressPull()
{
    ADD_PROPERTY_TYPE(Distance, (5.0), "PressPull", App::Prop_None, "Positive pulls out, negative pushes in");
    Size.setStatus(App::Property::Hidden, true);
}

bool PressPull::makeTool(Part::TopoShape& tool, std::string& error) const
{
    const double d = Distance.getValue();
    std::vector<Part::TopoShape> prisms;
    for (const auto& face : const_cast<PressPull*>(this)->elements(baseShape(0), TopAbs_FACE)) {  // pflegt nur Ausgaben
        BRepAdaptor_Surface surf(TopoDS::Face(face.getShape()));
        if (surf.GetType() != GeomAbs_Plane) {
            error = "Only flat faces can be pushed through";
            return false;
        }
        gp_Dir n = surf.Plane().Axis().Direction();  // nach außen zeigende Normale
        if (face.getShape().Orientation() == TopAbs_REVERSED) {
            n.Reverse();
        }
        prisms.push_back(Part::TopoShape(0, getDocument()->getStringHasher()).makeElementPrism(withoutTinyEdges(face), gp_Vec(n) * d));
    }
    if (prisms.empty()) {
        error = "Select one or more faces";
        return false;
    }
    tool = fuseAll(prisms, getDocument()->getStringHasher());
    return true;
}

void PressPull::onDocumentRestored()
{
    DressUp::onDocumentRestored();
    // Vor dem Mini-Kanten-Fix (makeTool) gespeichert: das ungültige Ergebnis beim nächsten Rechnen ersetzen. touch()
    // hilft hier nicht, das Laden setzt es danach zurück; einmal prüfen statt bei jedem mustExecute
    invalidOnRestore = !Shape.getShape().isNull() && !Shape.getShape().isValid();
}

short PressPull::mustExecute() const
{
    return invalidOnRestore ? 1 : DressUp::mustExecute();
}

App::DocumentObjectExecReturn* PressPull::compute()
{
    invalidOnRestore = false;
    // Bodies[0] trägt die Flächen; weitere Bodies schneidet das Hineindrücken mit (wie Extrude-Cut durch alles)
    if (Bodies.getSize() < 1 || BaseFeatures.getSize() != Bodies.getSize()) {
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
        std::vector<std::pair<TopoDS_Face, double>> offsets;
        for (const auto& face : faces) {
            offsets.emplace_back(TopoDS::Face(face.getShape()), d);
        }
        Part::TopoShape res;
        if (!offsetFaces(shape.getShape(), offsets, res)) {
            return new App::DocumentObjectExecReturn("Press Pull failed: distance too large?");
        }
        setResults({res});
        return StdReturn;
    }
    Part::TopoShape tool;
    std::string error;
    if (!makeTool(tool, error)) {
        return new App::DocumentObjectExecReturn(error);
    }
    std::vector<Part::TopoShape> results;
    for (int i = 0; i < Bodies.getSize(); ++i) {
        if (i > 0 && d > 0) {  // Herausziehen ändert nur den eigenen Körper
            results.push_back(baseShape(i));
            continue;
        }
        Part::TopoShape res(0, getDocument()->getStringHasher());
        if (d > 0) {
            res.makeElementFuse({shape, tool});
        }
        else {
            res.makeElementCut({baseShape(i), toolFor(i, tool)});
        }
        if (res.isNull() || res.countSubShapes(TopAbs_SOLID) == 0) {
            return new App::DocumentObjectExecReturn("Result would be empty");
        }
        results.push_back(res.makeElementRefine(nullptr, Part::RefineFail::shapeUntouched));
    }
    setResults(results);
    return StdReturn;
}

// ---------------------------------------------------------------------------------------------

namespace
{
const char* FittingEnums[] = {"3D print tight", "3D print normal", "3D print loose", "H7/g6", "H7/h6", "H7/k6",
                              "H7/p6", "H8/f7", nullptr};

/// Spiel je Seite für die Druck-Passungen 0 … 2 (Einstellungen, Vorgabe 0,1 / 0,2 / 0,3 mm)
double printClearance(long fit)
{
    static const char* names[] = {"PrintFitTight", "PrintFitNormal", "PrintFitLoose"};
    return App::GetApplication()
        .GetParameterGroupByPath("User parameter:BaseApp/Preferences/MyCAD")
        ->GetFloat(names[std::clamp<long>(fit, 0, 2)], 0.1 * (std::clamp<long>(fit, 0, 2) + 1));
}

std::string signedNumber(double v, int decimals)
{
    std::ostringstream out;
    out << std::fixed << std::setprecision(decimals) << std::showpos << (std::abs(v) < 1e-9 ? 0.0 : v);
    return out.str();
}
}  // namespace

PROPERTY_SOURCE(Design::Fitting, Design::DressUp)

Fitting::Fitting()
{
    ADD_PROPERTY_TYPE(Fit, (1L), "Parameters", App::Prop_None, "3D print clearance or ISO 286 fit");
    Fit.setEnums(FittingEnums);
    ADD_PROPERTY_TYPE(Clearance, (printClearance(1)), "Parameters", App::Prop_None, "Clearance per side for 3D printing");
    ADD_PROPERTY_TYPE(Nominal, (0.0), "Parameters", App::Prop_None,
                      "Nominal diameter of the pair; 0 takes the diameter of the hole");
    ADD_PROPERTY_TYPE(Play, (""), "Parameters", App::PropertyType(App::Prop_Output | App::Prop_ReadOnly),
                      "Play on the diameter; negative is interference");
    ADD_PROPERTY_TYPE(UsedNominal, (0.0), "Fit", App::PropertyType(App::Prop_Output | App::Prop_Hidden | App::Prop_Transient),
                      "Nominal diameter used (with Nominal 0: the diameter of the hole)");
    Size.setStatus(App::Property::Hidden, true);
    Nominal.setStatus(App::Property::Hidden, true);  // Druck-Passung: kein Nennmaß nötig
}

void Fitting::onChanged(const App::Property* prop)
{
    if (prop == &Fit) {
        const bool print = Fit.getValue() <= 2;
        if (print && !isRestoring()) {
            Clearance.setValue(printClearance(Fit.getValue()));
        }
        Clearance.setStatus(App::Property::Hidden, !print);
        Nominal.setStatus(App::Property::Hidden, print);
    }
    DressUp::onChanged(prop);
}

App::DocumentObjectExecReturn* Fitting::compute()
{
    if (Bodies.getSize() < 1 || Bodies.getSize() > 2 || BaseFeatures.getSize() != Bodies.getSize()) {
        return new App::DocumentObjectExecReturn("Select faces of one or two bodies");
    }
    const bool print = Fit.getValue() <= 2;
    const double c = Clearance.getValue();
    // gewählte Flächen je Body; Bohrungen und Wellen erkennen
    std::vector<Part::TopoShape> shapes;
    std::vector<std::vector<TopoDS_Face>> faces;
    bool anyHole = false, anyRound = false;
    double holeD = 0, shaftD = 0;
    for (int i = 0; i < Bodies.getSize(); ++i) {
        shapes.push_back(baseShape(i));
        faces.emplace_back();
        for (const auto& f : elements(shapes.back(), TopAbs_FACE, i)) {
            const TopoDS_Face face = TopoDS::Face(f.getShape());
            BRepAdaptor_Surface surface(face);
            if (surface.GetType() == GeomAbs_Cylinder) {
                anyRound = true;
                const double d = 2 * surface.Cylinder().Radius();
                (isShaftFace(face) ? shaftD : holeD) = d;
                anyHole = anyHole || !isShaftFace(face);
            }
            else if (surface.GetType() != GeomAbs_Plane) {
                return new App::DocumentObjectExecReturn("Select round or flat faces");
            }
            else if (!print) {
                return new App::DocumentObjectExecReturn("ISO fits are for round faces; use a 3D print fit for flat faces");
            }
            faces.back().push_back(face);
        }
    }
    if (std::ranges::all_of(faces, &std::vector<TopoDS_Face>::empty)) {
        return new App::DocumentObjectExecReturn("Select round or flat faces");
    }
    const double nominal = Nominal.getValue() > 0 ? Nominal.getValue() : anyHole ? holeD : shaftD;
    if (std::abs(UsedNominal.getValue() - nominal) > 1e-9) {
        UsedNominal.setValue(nominal);  // der Dialog zeigt es statt "0.00 mm"
    }
    Fits::Deviation hole, shaft;
    double minPlay = 0, maxPlay = 0;
    if (!print && !Fits::fit(Fit.getValueAsString(), nominal, hole, shaft, minPlay, maxPlay)) {
        return new App::DocumentObjectExecReturn("ISO fits go up to 500 mm");
    }
    std::vector<Part::TopoShape> results;
    for (size_t i = 0; i < shapes.size(); ++i) {
        std::vector<std::pair<TopoDS_Face, double>> offsets;
        for (const auto& face : faces[i]) {
            double d = -c;  // ebene Fläche: um das Spiel zurück
            if (BRepAdaptor_Surface(face).GetType() == GeomAbs_Cylinder) {
                const bool isShaft = isShaftFace(face);
                const double r = BRepAdaptor_Surface(face).Cylinder().Radius();
                if (print && isShaft && anyHole) {
                    continue;  // Druck: die Bohrung bekommt das Spiel, die Welle bleibt
                }
                // Zielradius: Mittelmaß des Toleranzfelds (µm am Durchmesser) bzw. um das Spiel größer/kleiner
                const double target = print ? r + (isShaft ? -c : c)
                                            : nominal / 2 + (isShaft ? shaft.mean() : hole.mean()) / 2000;
                // Offset zeigt aus dem Material: bei der Welle nach außen, bei der Bohrung zur Achse
                d = isShaft ? target - r : r - target;
            }
            if (std::abs(d) > 1e-9) {
                offsets.emplace_back(face, d);
            }
        }
        Part::TopoShape res = shapes[i];
        if (!offsets.empty() && !offsetFaces(shapes[i].getShape(), offsets, res)) {
            return new App::DocumentObjectExecReturn("The fit could not be applied to these faces");
        }
        results.push_back(res);
    }
    Play.setValue(print ? signedNumber(anyRound ? 2 * c : c, 2) + " mm"
                        : signedNumber(minPlay, 0) + " … " + signedNumber(maxPlay, 0) + " µm");
    setResults(results);
    return StdReturn;
}

// ---------------------------------------------------------------------------------------------

namespace
{
const char* ScrewEnums[] = {"ISO 4762", "ISO 10642", "ISO 7380", nullptr};
const char* FastenerSizeEnums[] = {"M2", "M2.5", "M3", "M4", "M5", "M6", "M8", "M10", "M12", nullptr};
const char* BottomEnums[] = {"Tapped hole", "Heat-set insert", "Nut trap", nullptr};

/// Regelgewinde zu "M3"
const PartDesign::Hole::ThreadDescription* metricThread(const std::string& size)
{
    for (const auto& t : *threadTable(1)) {
        if (std::string(t.designation).rfind(size + "x", 0) == 0) {
            return &t;
        }
    }
    return nullptr;
}

/// Einschmelzmutter: Bohrung (Durchmesser, Tiefe). ponytail: übliche Werte für Ruthex-artige Muttern; andere
/// Hersteller weichen ab, dann Durchmesser per Hand (eigenes Hole-Feature)
bool insertHole(const std::string& size, double& diameter, double& depth)
{
    static const std::map<std::string, std::pair<double, double>> sizes = {
        {"M2", {3.2, 4.0}}, {"M2.5", {3.6, 5.7}}, {"M3", {4.0, 5.7}}, {"M4", {5.6, 8.1}},
        {"M5", {6.4, 9.5}}, {"M6", {8.0, 12.7}},  {"M8", {9.7, 12.7}}};
    const auto it = sizes.find(size);
    if (it == sizes.end()) {
        return false;
    }
    std::tie(diameter, depth) = it->second;
    return true;
}

/// Sechskantmutter ISO 4032: (Schlüsselweite, Höhe)
std::pair<double, double> nutSize(const std::string& size)
{
    static const std::map<std::string, std::pair<double, double>> sizes = {
        {"M2", {4, 1.6}},   {"M2.5", {5, 2}},   {"M3", {5.5, 2.4}},  {"M4", {7, 3.2}},    {"M5", {8, 4.7}},
        {"M6", {10, 5.2}}, {"M8", {13, 6.8}}, {"M10", {16, 8.4}}, {"M12", {18, 10.8}}};
    return sizes.at(size);
}

/// Längen nach ISO 4762 / 10642 / 7380 (Auswahl)
constexpr double ScrewLengths[] = {3, 4, 5, 6, 8, 10, 12, 16, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 80, 90, 100, 110, 120};

/// Schnittstellen der Geraden p + t·d mit shape, aufsteigend
std::vector<double> crossings(const TopoDS_Shape& shape, const gp_Pnt& p, const gp_Dir& d)
{
    IntCurvesFace_ShapeIntersector inter;
    inter.Load(shape, 1e-6);
    inter.Perform(gp_Lin(p, d), -1e-3, 1e5);
    std::vector<double> ts;
    for (int i = 1; inter.IsDone() && i <= inter.NbPnt(); ++i) {
        ts.push_back(inter.WParameter(i));
    }
    std::ranges::sort(ts);
    return ts;
}

/// Sechskant-Prisma um die Achse ax, Schlüsselweite s, Höhe h
TopoDS_Shape hexPrism(const gp_Ax2& ax, double s, double h)
{
    BRepBuilderAPI_MakePolygon poly;
    const double r = s / 2 / std::cos(M_PI / 6);
    for (int k = 0; k < 6; ++k) {
        const double a = k * M_PI / 3;
        poly.Add(ax.Location().Translated(gp_Vec(ax.XDirection()) * (r * std::cos(a))
                                          + gp_Vec(ax.YDirection()) * (r * std::sin(a))));
    }
    poly.Close();
    return BRepPrimAPI_MakePrism(BRepBuilderAPI_MakeFace(poly.Wire()).Face(), gp_Vec(ax.Direction()) * h).Shape();
}
}  // namespace

PROPERTY_SOURCE(Design::Fastener, Design::Feature)

Fastener::Fastener()
{
    ADD_PROPERTY_TYPE(Position, (Base::Vector3d()), "Fastener", App::Prop_Hidden, "Entry point on the top face");
    ADD_PROPERTY_TYPE(Direction, (Base::Vector3d(0, 0, -1)), "Fastener", App::Prop_Hidden, "Into the parts");
    ADD_PROPERTY_TYPE(Screw, (0L), "Parameters", App::Prop_None, "Screw standard");
    Screw.setEnums(ScrewEnums);
    ADD_PROPERTY_TYPE(Size, (2L), "Parameters", App::Prop_None, "Screw size");
    Size.setEnums(FastenerSizeEnums);
    ADD_PROPERTY_TYPE(Bottom, (0L), "Parameters", App::Prop_None, "What holds the screw in the lower part");
    Bottom.setEnums(BottomEnums);
    ADD_PROPERTY_TYPE(AutoLength, (true), "Parameters", App::Prop_None, "Pick the standard length that fits");
    ADD_PROPERTY_TYPE(Length, (10.0), "Parameters", App::Prop_None, "Screw length");
    Length.setStatus(App::Property::ReadOnly, true);  // folgt AutoLength
    Operation.setValue(2L);  // Cut
    Operation.setStatus(App::Property::Hidden, true);
}

void Fastener::onChanged(const App::Property* prop)
{
    if (prop == &AutoLength) {
        Length.setStatus(App::Property::ReadOnly, AutoLength.getValue());
    }
    Feature::onChanged(prop);
}

App::DocumentObjectExecReturn* Fastener::compute()
{
    // zwei Teile, die gebohrt werden; ein dritter Körper (12.7, neue Befestigungen) ist die Schraube selbst
    if ((Bodies.getSize() != 2 && Bodies.getSize() != 3) || BaseFeatures.getSize() != 2) {
        return new App::DocumentObjectExecReturn("Click the top face of a part that lies on another part");
    }
    const std::string size = Size.getValueAsString();
    const PartDesign::Hole::ThreadDescription* t = metricThread(size);
    Base::Vector3d dir = Direction.getValue();
    if (!t || dir.Length() < Precision::Confusion()) {
        return new App::DocumentObjectExecReturn("Choose a screw size");
    }
    dir.Normalize();
    const std::string screw = Screw.getValueAsString();
    bool countersink = false;
    double angle = 90;
    const auto* head = headSize(screw, t->designation, &countersink, &angle);
    if (!head) {
        return new App::DocumentObjectExecReturn(screw + " has no size " + size);
    }
    // Lage je Body in den Koordinaten seiner Komponente; die Parameter entlang der Achse sind überall gleich
    std::vector<Part::TopoShape> shapes {baseShape(0), baseShape(1)};
    std::vector<gp_Ax2> axes;
    for (int i = 0; i < 2; ++i) {
        const Base::Placement inv = Design::componentOf(Bodies[i])->globalPlacement().inverse();
        Base::Vector3d p = Position.getValue(), d = dir;
        inv.multVec(p, p);
        inv.getRotation().multVec(d, d);
        axes.emplace_back(gp_Pnt(p.x, p.y, p.z), gp_Dir(d.x, d.y, d.z));
    }
    const auto top = crossings(shapes[0].getShape(), axes[0].Location(), axes[0].Direction());
    const auto exitTop = std::ranges::find_if(top, [](double v) { return v > 1e-4; });
    if (exitTop == top.end()) {
        return new App::DocumentObjectExecReturn("The point is not on the top part");
    }
    const double t1 = *exitTop;
    // Kopf versenkt: Länge zählt ab dem Grund der Senkung. Ist das obere Teil dafür zu dünn (Deckel 2 mm, Senkung M3
    // 3,4 mm), sitzt der Kopf obendrauf; sonst bliebe ein Loch in Kopfgröße und die Schraube hielte nichts
    const double recess = countersink || head->second > t1 - 0.5 ? 0 : head->second;
    const auto lower = crossings(shapes[1].getShape(), axes[1].Location(), axes[1].Direction());
    const auto entry = std::ranges::find_if(lower, [t1](double v) { return v > t1 - 1e-4; });
    if (entry == lower.end() || entry + 1 == lower.end()) {
        return new App::DocumentObjectExecReturn("There is no second part below this point");
    }
    const double t2 = *entry, t3 = *(entry + 1);

    // Länge: unter dem Kopf bis in das untere Teil, so weit wie es hält
    const long bottom = Bottom.getValue();
    const double nominal = t->diameter;
    double insertD = 0, insertDepth = 0;
    if (bottom == 1 && !insertHole(size, insertD, insertDepth)) {
        return new App::DocumentObjectExecReturn("There is no heat-set insert for " + size
                                                 + "; use a tapped hole or a nut trap");
    }
    const auto [nutWidth, nutHeight] = nutSize(size);
    const double grip = t2 - recess;
    const double needed = bottom == 0 ? grip + 1.5 * nominal  // ponytail: 1,5 × d hält in Kunststoff und Alu
                        : bottom == 1 ? grip + insertDepth
                                      : t3 - recess - 0.5;  // Mutterfalle: bis zur Unterseite, darf knapp drüber
    double length = Length.getValue();
    if (AutoLength.getValue()) {
        const auto fits = std::ranges::find_if(ScrewLengths, [needed](double l) { return l >= needed - 1e-6; });
        length = fits == std::end(ScrewLengths) ? ScrewLengths[std::size(ScrewLengths) - 1] : *fits;
        // Sackloch: Spitze samt Bohrung (1 mm weiter) bleibt im unteren Teil, sonst stünde sie unten heraus (kurzer
        // Sockel im Gehäuse). Dann die längste Normlänge, die noch hält; reicht keine, geht die Bohrung eben durch
        if (bottom != 2 && recess + length + 1.5 > t3) {
            for (double l : ScrewLengths) {
                if (recess + l + 1.5 <= t3 && recess + l >= t2 + nominal) {
                    length = l;  // aufsteigend: die letzte passende ist die längste
                }
            }
        }
        if (std::abs(Length.getValue() - length) > 1e-9) {
            Length.setValue(length);
            Length.purgeTouched();
        }
    }
    const double tip = recess + length;
    if (tip < t2 + nominal) {  // nur bei Länge von Hand
        const auto longer = std::ranges::find_if(ScrewLengths, [&](double l) { return recess + l >= t2 + nominal; });
        if (longer != std::end(ScrewLengths)) {
            suggest("Use a longer screw", "Length", *longer);
        }
        return new App::DocumentObjectExecReturn("The screw is too short to hold the lower part");
    }

    constexpr double lead = 0.01;
    const auto at = [&](int i, double t) {
        return gp_Ax2(axes[i].Location().Translated(gp_Vec(axes[i].Direction()) * t), axes[i].Direction());
    };
    // oben: Durchgang (ISO 273 mittel) mit Senkung (Zylinderkopf auf dünnem Teil: ohne)
    const double clearance = clearanceDiameter(1, *t, 1);
    const long sink = countersink ? 2 : recess > 0 ? 1 : 0;
    const Part::TopoShape upper = fuseAll(holeShape(at(0, -lead), clearance / 2, t1 + 2 * lead, sink,
                                                    head->first / 2, recess, angle, lead),
                                          getDocument()->getStringHasher());
    // unten: Kernloch, Einschmelzmutter oder Durchgang mit Mutterfalle an der Unterseite
    std::vector<Part::TopoShape> lowerParts;
    const double from = std::min(t1, t2) - lead;
    if (bottom == 0) {
        lowerParts.emplace_back(BRepPrimAPI_MakeCylinder(at(1, from), t->TapDrill / 2, tip + 1 - from).Shape());
    }
    else if (bottom == 1) {
        lowerParts.emplace_back(
            BRepPrimAPI_MakeCylinder(at(1, from), insertD / 2, std::max(t2 + insertDepth + 1, tip + 1) - from).Shape());
    }
    else {
        constexpr double play = 0.15;  // Mutter muss beim Druck hineinpassen
        lowerParts.emplace_back(BRepPrimAPI_MakeCylinder(at(1, from), clearance / 2, t3 + lead - from).Shape());
        lowerParts.emplace_back(hexPrism(at(1, t3 - nutHeight - play), nutWidth + 2 * play, nutHeight + play + lead));
    }
    const Part::TopoShape lowerTool = fuseAll(lowerParts, getDocument()->getStringHasher());

    std::vector<Part::TopoShape> results;
    for (const auto& [shape, tool] : {std::pair {shapes[0], upper}, std::pair {shapes[1], lowerTool}}) {
        Part::TopoShape res(0, getDocument()->getStringHasher());
        res.makeElementCut({shape, tool});
        if (res.isNull() || res.countSubShapes(TopAbs_SOLID) == 0) {
            return new App::DocumentObjectExecReturn("The holes would cut the part apart");
        }
        results.push_back(res);
    }
    if (Bodies.getSize() == 3) {
        // Schraube in der Bohrung: Spitze bei tip, Kopf zum Eintrittspunkt (im Teil oben versenkt bzw. gesenkt)
        std::string error;
        TopoDS_Shape solid = screwSolid(int(Screw.getValue()), size, length, error);
        if (solid.IsNull()) {
            return new App::DocumentObjectExecReturn(error);
        }
        gp_Trsf place;
        place.SetDisplacement(gp_Ax3(), gp_Ax3(at(0, tip).Location(), -axes[0].Direction()));
        results.emplace_back(BRepBuilderAPI_Transform(solid, place, true).Shape());
    }
    setResults(results);
    return StdReturn;
}

Fastener* Design::makeFastener(Body* top, const Base::Vector3d& point, const Base::Vector3d& direction)
{
    App::Document* doc = top->getDocument();
    Base::Vector3d dir = direction;
    dir.Normalize();
    // untere Komponente: der nächste andere Body auf der Achse
    Body* lower = nullptr;
    double nearest = 1e100;
    for (auto obj : doc->getObjectsOfType(Body::getClassTypeId())) {
        auto body = static_cast<Body*>(obj);
        if (body == top || body->Shape.getShape().isNull()) {
            continue;
        }
        const Base::Placement inv = body->globalPlacement().inverse();
        Base::Vector3d p = point, d = dir;
        inv.multVec(p, p);
        inv.getRotation().multVec(d, d);
        Part::TopoShape shape = body->Shape.getShape();
        shape.setPlacement(Base::Placement());
        const auto ts = crossings(shape.getShape(), gp_Pnt(p.x, p.y, p.z), gp_Dir(d.x, d.y, d.z));
        const auto hit = std::ranges::find_if(ts, [](double v) { return v > 1e-4; });
        if (hit != ts.end() && *hit < nearest) {
            nearest = *hit;
            lower = body;
        }
    }
    if (!lower) {
        throw Base::ValueError("There is no second part below this point");
    }
    auto fastener = static_cast<Fastener*>(doc->addObject("Design::Fastener", "Fastener"));
    componentOf(top)->addObject(fastener);
    addToTimeline(fastener);
    fastener->Position.setValue(point);
    fastener->Direction.setValue(dir);
    attachToBodies(fastener, {top, lower});
    // 12.7: die Schraube kommt als eigener Körper mit (folgt Größe, Länge und Lage der Bohrung)
    auto screw = static_cast<Body*>(doc->addObject("Design::Body", "Body"));
    folder(componentOf(top), "Bodies")->addObject(screw);
    screw->Label.setValue("Screw");
    screw->Tip.setValue(fastener);
    auto bodies = fastener->Bodies.getValues();
    bodies.push_back(screw);
    fastener->Bodies.setValues(bodies);
    doc->recompute();
    return fastener;
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

PROPERTY_SOURCE(Design::CodeStep, Design::Feature)

CodeStep::CodeStep()
{
    ADD_PROPERTY_TYPE(Code, (""), "Code", App::Prop_None, "Python code that sets result to a shape");
    ADD_PROPERTY_TYPE(Parameters, (nullptr), "Code", App::Prop_Hidden, "Parameter table the code reads as p.Name");
}

void CodeStep::setupObject()
{
    Parameters.setValue(parameterSet(getDocument(), true));
    Feature::setupObject();
}

App::DocumentObjectExecReturn* CodeStep::compute()
{
    // DesignCode.run prüft die Freigabe selbst und wirft sonst; die Meldung steht dann am Schritt
    Part::TopoShape tool;
    try {
        Base::PyGILStateLocker lock;
        Py::Module module(PyImport_ImportModule("DesignCode"), true);
        if (module.isNull()) {
            throw Py::Exception();
        }
        Py::Tuple args(2);
        args[0] = Py::String(Code.getValue());
        args[1] = Py::asObject(getDocument()->getPyObject());
        const Py::Object result = Py::Callable(module.getAttr("run")).apply(args);
        if (!PyObject_TypeCheck(result.ptr(), &Part::TopoShapePy::Type)) {
            return new App::DocumentObjectExecReturn("The code must set result to a shape");
        }
        tool = *static_cast<Part::TopoShapePy*>(result.ptr())->getTopoShapePtr();
    }
    catch (Py::Exception&) {
        Base::PyException error;  // holt die Python-Meldung und räumt den Fehler ab
        return new App::DocumentObjectExecReturn(error.getMessage());
    }
    if (tool.isNull()) {
        return new App::DocumentObjectExecReturn("The code must set result to a shape");
    }
    return applyTool(tool);
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
    ADD_PROPERTY_TYPE(Closed, (false), "Parameters", App::Prop_None, "Closed; connects the last profile back to the first");
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
    ADD_PROPERTY_TYPE(Size, (2L), "Parameters", App::Prop_None, "Thread size");
    Size.setEnums(FastenerSizeEnums);
    ADD_PROPERTY_TYPE(Bearing, (4L), "Parameters", App::Prop_None, "Ball bearing (inner × outer × width)");
    Bearing.setEnums(BearingEnums);
    ADD_PROPERTY_TYPE(Profile, (0L), "Parameters", App::Prop_None, "Aluminum profile (B-type slot)");
    Profile.setEnums(ProfileEnums);
    static const App::PropertyIntegerConstraint::Constraints teeth = {6, 400, 1};
    ADD_PROPERTY_TYPE(Module, (1.0), "Parameters", App::Prop_None, "Gear module: pitch diameter = module × teeth");
    ADD_PROPERTY_TYPE(Teeth, (20L), "Parameters", App::Prop_None, "Number of teeth");
    Teeth.setConstraints(&teeth);
    ADD_PROPERTY_TYPE(PressureAngle, (20.0), "Parameters", App::Prop_None, "Pressure angle, usually 20°");
    ADD_PROPERTY_TYPE(Bore, (5.0), "Parameters", App::Prop_None, "Diameter of the hole in the middle (0: none)");
    ADD_PROPERTY_TYPE(Rotation, (0.0), "Parameters", App::Prop_None, "Turn about its own axis, e.g. to mesh with another gear");
    ADD_PROPERTY_TYPE(ProfileShift, (0.0), "Parameters", App::Prop_None,
                      "Profile shift coefficient x: teeth move out by x times the module (fewer teeth without undercut)");
    ADD_PROPERTY_TYPE(Backlash, (0.0), "Parameters", App::Prop_None,
                      "Play between the teeth, measured on the pitch circle (3D printed gears: about 0.2 mm)");
    static const App::PropertyIntegerConstraint::Constraints knuckles = {3, 21, 1};
    ADD_PROPERTY_TYPE(Knuckles, (5L), "Parameters", App::Prop_None, "Number of knuckles along the hinge");
    Knuckles.setConstraints(&knuckles);
    // Spiel aus dem Druckerprofil (12.4, "locker"); im Design gespeichert, damit es auf jedem Rechner gleich baut
    ADD_PROPERTY_TYPE(Clearance, (printClearance(2)), "Parameters", App::Prop_None, "Gap between the moving parts");
    ADD_PROPERTY_TYPE(Thickness, (1.5), "Parameters", App::Prop_None, "Thickness of the flexing beam");
    ADD_PROPERTY_TYPE(Undercut, (1.0), "Parameters", App::Prop_None, "How far the hook reaches over the edge it holds");
    onChanged(&Type);
}

namespace
{
enum PrimitiveType : long
{
    BoxType, CylinderType, SphereType, TorusType, CoilType, SocketScrew, CountersunkScrew, ButtonScrew, HexNut, Washer,
    HeatSetInsert, BallBearing, DiscMagnet, BlockMagnet, AluProfile, SpurGear, Hinge, SnapHook, SnapRecess
};

/// Scharnier zum Drucken in einem Stück, flach auf dem Bett: Achse entlang X auf Höhe r, Blatt A nach -Y, Blatt B nach
/// +Y, je Blatt w breit und 2r dick. Knöchel abwechselnd A, B, A …; der Stift (halber Knöchelradius) gehört zu A und
/// läuft durch die Bohrungen von B. Zwischen allem, was sich bewegt, liegt das Spiel c. Ergebnis: zwei Volumenkörper
/// in einem Bündel. ponytail: Bohrung quer zum Bett ohne Tropfenform; bei kleinem c und schlechtem Drucker verklebt es
bool hinge(double length, double w, double r, int n, double c, TopoDS_Shape& shape, std::string& error)
{
    const double gap = c, segment = (length - (n - 1) * gap) / n, pin = r / 2;
    if (segment < 2 * c + 1 || w <= r || c <= 0 || pin <= c) {
        error = "The hinge is too small for this many knuckles and this clearance";
        return false;
    }
    const auto along = [&](double x0, double x1, double radius) {  // Zylinder auf der Achse von x0 bis x1
        return BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(x0, 0, r), gp::DX()), radius, x1 - x0).Shape();
    };
    TopoDS_Shape a = BRepPrimAPI_MakeBox(gp_Pnt(0, -w, 0), length, w, 2 * r).Shape();
    TopoDS_Shape b = BRepPrimAPI_MakeBox(gp_Pnt(0, 0, 0), length, w, 2 * r).Shape();
    for (int k = 0; k < n; ++k) {
        const double x0 = k * (segment + gap), x1 = x0 + segment;
        TopoDS_Shape& own = k % 2 == 0 ? a : b;
        TopoDS_Shape& other = k % 2 == 0 ? b : a;
        own = BRepAlgoAPI_Fuse(own, along(x0, x1, r)).Shape();
        // das andere Blatt macht dem Knöchel Platz, auch in den Fugen daneben
        other = BRepAlgoAPI_Cut(other, along(std::max(0.0, x0 - gap), std::min(length, x1 + gap), r + c)).Shape();
    }
    b = BRepAlgoAPI_Cut(b, along(-1, length + 1, pin + c)).Shape();  // Bohrung für den Stift
    a = BRepAlgoAPI_Fuse(a, along(0, length, pin)).Shape();
    TopoDS_Compound both;
    BRep_Builder builder;
    builder.MakeCompound(both);
    for (const TopoDS_Shape& half : {a, b}) {
        for (TopExp_Explorer solid(half, TopAbs_SOLID); solid.More(); solid.Next()) {
            builder.Add(both, solid.Current());
        }
    }
    shape = both;
    return true;
}

/// Schnapphaken: Biegebalken (Dicke t, Länge l) steht auf der Ebene, oben die Rastnase y weit nach +X mit 30°
/// Einführschräge und waagerechter Haltekante; w breit entlang Y
TopoDS_Shape snapHook(double l, double t, double y, double w)
{
    const double lead = y / std::tan(30 * M_PI / 180);  // Höhe der Schräge
    BRepBuilderAPI_MakePolygon poly;
    for (const gp_Pnt& p : {gp_Pnt(0, 0, 0), gp_Pnt(t, 0, 0), gp_Pnt(t, 0, l - lead), gp_Pnt(t + y, 0, l - lead),
                            gp_Pnt(t, 0, l), gp_Pnt(0, 0, l)}) {
        poly.Add(p);
    }
    poly.Close();
    return BRepPrimAPI_MakePrism(BRepBuilderAPI_MakeFace(poly.Wire()).Face(), gp_Vec(0, w, 0)).Shape();
}

/// größte Dehnung am Fuß eines Biegebalkens mit Rechteckquerschnitt, wenn sich die Spitze um y biegt
double hookStrain(double l, double t, double y)
{
    return 1.5 * t * y / (l * l);
}
constexpr double HookStrainLimit = 0.025;  // PLA und PETG halten wiederholt etwa 2,5 % (PLA bricht ab rund 4 %)

/// Stirnrad mit Evolventen-Flanken: Teilkreis m·z/2 um den Ursprung, Kopf m darüber, Fuß 1,25·m darunter, Dicke h
/// nach +Z. Flanken als Kurve durch Punkte der Evolvente, Kopf und Fuß als Kreisbögen: glatte Flächen statt Facetten.
/// Profilverschiebung shift (x · m nach außen: Kopf m(1 + x), Fuß m(1,25 − x), Zahn am Teilkreis um 2x·m·tan α dicker)
/// und Spiel backlash (Zahn am Teilkreis so viel dünner, in mm Bogen). ponytail: ohne Fußrundung; unter 17 Zähnen (20°)
/// ohne Verschiebung schneidet ein echtes Rad unter
bool spurGear(double m, int z, double alphaDeg, double h, double bore, double shift, double backlash, TopoDS_Shape& shape,
              std::string& error)
{
    const double alpha = alphaDeg * M_PI / 180;
    if (m <= 0 || h <= 0 || alpha <= 0 || alpha >= M_PI / 4) {
        error = "Module and height must be greater than zero, the pressure angle between 0 and 45°";
        return false;
    }
    const double r = m * z / 2, rb = r * std::cos(alpha), ra = r + m * (1 + shift), rf = r - m * (1.25 - shift);
    const double r0 = std::max(rb, rf);
    if (rf <= 0 || backlash < 0) {
        error = "The profile shift is too small for this many teeth, or the backlash is negative";
        return false;
    }
    const auto inv = [](double a) { return std::tan(a) - a; };
    // halber Zahnwinkel am Grundkreis: Zahndicke am Teilkreis m(π/2 + 2x tan α) − Spiel, geteilt durch den Durchmesser
    const double half = (M_PI / 2 + 2 * shift * std::tan(alpha)) / z - backlash / (m * z) + inv(alpha);
    const auto psi = [&](double rr) { return half - inv(std::acos(std::min(1.0, rb / rr))); };
    if (psi(ra) <= 0) {
        error = "With so few teeth the tips would be pointed; use more teeth";
        return false;
    }
    if (bore >= 2 * rf) {
        error = "The bore is larger than the gear";
        return false;
    }
    const auto at = [](double rr, double ang) { return gp_Pnt(rr * std::cos(ang), rr * std::sin(ang), 0); };
    const auto arc = [](const gp_Pnt& a, const gp_Pnt& mid, const gp_Pnt& b) {
        return BRepBuilderAPI_MakeEdge(GC_MakeArcOfCircle(a, mid, b).Value()).Edge();
    };
    constexpr int n = 12;  // Punkte je Flanke
    BRepBuilderAPI_MakeWire wire;
    for (int k = 0; k < z; ++k) {
        const double c = 2 * M_PI * k / z, next = 2 * M_PI * (k + 1) / z;
        for (int side : {-1, 1}) {
            Handle(TColgp_HArray1OfPnt) pts = new TColgp_HArray1OfPnt(1, n);
            for (int i = 0; i < n; ++i) {
                const double rr = i == n - 1 ? ra : r0 + (ra - r0) * i / (n - 1);
                pts->SetValue(i + 1, at(rr, c + side * psi(rr)));
            }
            GeomAPI_Interpolate curve(pts, Standard_False, 1e-9);
            curve.Perform();
            if (side < 0 && rb > rf) {  // unter dem Grundkreis radial bis zum Fuß
                wire.Add(BRepBuilderAPI_MakeEdge(at(rf, c - half), at(r0, c - half)).Edge());
            }
            wire.Add(BRepBuilderAPI_MakeEdge(curve.Curve()).Edge());
            if (side < 0) {
                wire.Add(arc(at(ra, c - psi(ra)), at(ra, c), at(ra, c + psi(ra))));  // Kopf
            }
        }
        if (rb > rf) {
            wire.Add(BRepBuilderAPI_MakeEdge(at(r0, c + half), at(rf, c + half)).Edge());
        }
        const double from = c + psi(r0), to = next - psi(r0);
        wire.Add(arc(at(rf, from), at(rf, (from + to) / 2), at(rf, to)));  // Fuß bis zum nächsten Zahn
    }
    if (!wire.IsDone()) {
        error = "The gear outline could not be built";
        return false;
    }
    shape = BRepPrimAPI_MakePrism(BRepBuilderAPI_MakeFace(wire.Wire()).Face(), gp_Vec(0, 0, h)).Shape();
    if (bore > 0) {
        shape = BRepAlgoAPI_Cut(shape, BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, -1), gp::DZ()), bore / 2, h + 2).Shape()).Shape();
    }
    return true;
}

/// Schraubenkopf je Gewinde: Zylinderkopf ISO 4762 (dk, k), Senkkopf ISO 10642 (dk), Linsenkopf ISO 7380 (dk, k),
/// Schlüsselweite des Innensechskants je Kopfform. ponytail: Nennmaße ohne Toleranzen; M2/M2.5 bei 10642/7380 sind
/// nicht genormt, Werte wie bei den Händlern
struct ScrewHead
{
    double socketDk, socketK, socketKey, sinkDk, sinkKey, buttonDk, buttonK, buttonKey;
};
const ScrewHead& screwHead(const std::string& size)
{
    static const std::map<std::string, ScrewHead> heads = {
        {"M2", {3.8, 2, 1.5, 4, 1.3, 3.5, 1.3, 1.3}},       {"M2.5", {4.5, 2.5, 2, 5, 1.5, 4.7, 1.5, 1.5}},
        {"M3", {5.5, 3, 2.5, 6, 2, 5.7, 1.65, 2}},          {"M4", {7, 4, 3, 8, 2.5, 7.6, 2.2, 2.5}},
        {"M5", {8.5, 5, 4, 10, 3, 9.5, 2.75, 3}},           {"M6", {10, 6, 5, 12, 4, 10.5, 3.3, 4}},
        {"M8", {13, 8, 6, 16, 5, 14, 4.4, 5}},              {"M10", {16, 10, 8, 20, 6, 17.5, 5.5, 6}},
        {"M12", {18, 12, 10, 24, 8, 21, 6.6, 8}}};
    return heads.at(size);
}

/// Scheibe ISO 7089: (innen, außen, Dicke)
std::tuple<double, double, double> washerSize(const std::string& size)
{
    static const std::map<std::string, std::tuple<double, double, double>> sizes = {
        {"M2", {2.2, 5, 0.3}},  {"M2.5", {2.7, 6, 0.5}}, {"M3", {3.2, 7, 0.5}},   {"M4", {4.3, 9, 0.8}},  {"M5", {5.3, 10, 1}},
        {"M6", {6.4, 12, 1.6}}, {"M8", {8.4, 16, 1.6}},  {"M10", {10.5, 20, 2}}, {"M12", {13, 24, 2.5}}};
    return sizes.at(size);
}

/// Rillenkugellager: (innen, außen, Breite)
std::tuple<double, double, double> bearingSize(const std::string& name)
{
    static const std::map<std::string, std::tuple<double, double, double>> sizes = {
        {"623", {3, 10, 4}}, {"624", {4, 13, 5}},    {"625", {5, 16, 5}},    {"626", {6, 19, 6}},
        {"608", {8, 22, 7}}, {"6000", {10, 26, 8}}, {"6001", {12, 28, 8}}, {"6200", {10, 30, 9}}};
    return sizes.at(name);
}

/// Zylinder um Z von z0 bis z1
TopoDS_Shape zCylinder(double r, double z0, double z1)
{
    return BRepPrimAPI_MakeCylinder(gp_Ax2(gp_Pnt(0, 0, z0), gp::DZ()), r, z1 - z0).Shape();
}

/// Innensechskant von oben in einen Kopf (Oberseite bei z, Tiefe depth)
TopoDS_Shape withSocket(const TopoDS_Shape& head, double key, double z, double depth)
{
    return BRepAlgoAPI_Cut(head, hexPrism(gp_Ax2(gp_Pnt(0, 0, z - depth), gp::DZ()), key, depth + 0.01)).Shape();
}

/// Querschnitt eines Alu-Profils (Nut Typ B): Außenmaß a × b, Nuten mittig je 20 bzw. 30 mm, Kernbohrung je Raster
TopoDS_Shape profileSection(const std::string& name, double length)
{
    const bool big = name == "3030";
    const double grid = big ? 30 : 20, slot = big ? 8.2 : 6.2, depth = big ? 9 : 6, bore = big ? 6.8 : 4.2;
    const double w = grid, h = name == "2040" ? 40 : grid;
    TopoDS_Shape shape = BRepPrimAPI_MakeBox(gp_Pnt(-w / 2, -h / 2, 0), w, h, length).Shape();
    std::vector<gp_Pnt> centers;  // Mitte je Rasterfeld
    for (double y = -h / 2 + grid / 2; y < h / 2; y += grid) {
        centers.emplace_back(0, y, 0);
    }
    for (const gp_Pnt& c : centers) {
        shape = BRepAlgoAPI_Cut(shape, BRepPrimAPI_MakeCylinder(gp_Ax2(c, gp::DZ()), bore / 2, length).Shape()).Shape();
        for (int side : {-1, 1}) {  // Nuten links und rechts
            const double x = side < 0 ? -w / 2 : w / 2 - depth;
            shape = BRepAlgoAPI_Cut(shape, BRepPrimAPI_MakeBox(gp_Pnt(x, c.Y() - slot / 2, 0), depth, slot, length).Shape()).Shape();
        }
    }
    for (int side : {-1, 1}) {  // Nuten oben und unten
        const double y = side < 0 ? -h / 2 : h / 2 - depth;
        shape = BRepAlgoAPI_Cut(shape, BRepPrimAPI_MakeBox(gp_Pnt(-slot / 2, y, 0), slot, depth, length).Shape()).Shape();
    }
    return shape;
}

std::string mm(double v)
{
    std::ostringstream out;
    out << v;
    return out.str();
}

TopoDS_Shape screwSolid(int kind, const std::string& size, double l, std::string& error)
{
    const auto* thread = metricThread(size);
    if (!thread) {
        error = "Choose a thread size";
        return {};
    }
    const double d = thread->diameter;
    const ScrewHead& head = screwHead(size);
    if (kind == 0) {
        const TopoDS_Shape shape =
            BRepAlgoAPI_Fuse(zCylinder(d / 2, 0, l), zCylinder(head.socketDk / 2, l, l + head.socketK)).Shape();
        return withSocket(shape, head.socketKey, l + head.socketK, head.socketK * 0.6);
    }
    if (kind == 1) {  // Nennlänge über alles, Kopf 90°
        const double k = (head.sinkDk - d) / 2;
        if (l <= k) {
            error = "The screw is shorter than its head";
            return {};
        }
        const TopoDS_Shape cone = BRepPrimAPI_MakeCone(gp_Ax2(gp_Pnt(0, 0, l - k), gp::DZ()), d / 2, head.sinkDk / 2, k).Shape();
        return withSocket(BRepAlgoAPI_Fuse(zCylinder(d / 2, 0, l - k), cone).Shape(), head.sinkKey, l, k * 0.7);
    }
    // Linsenkopf: Kugelkappe über dem Schaft
    const double a = head.buttonDk / 2, k = head.buttonK, rs = (a * a + k * k) / (2 * k);
    const TopoDS_Shape cap =
        BRepAlgoAPI_Common(BRepPrimAPI_MakeSphere(gp_Pnt(0, 0, l + k - rs), rs).Shape(), zCylinder(a, l, l + k)).Shape();
    return withSocket(BRepAlgoAPI_Fuse(zCylinder(d / 2, 0, l), cap).Shape(), head.buttonKey, l + k, k * 0.7);
}
}  // namespace

std::string Primitive::partName() const
{
    const std::string size = Size.getValueAsString();
    switch (Type.getValue()) {
        case SocketScrew:
            return "ISO 4762 " + size + " × " + mm(Length.getValue());
        case CountersunkScrew:
            return "ISO 10642 " + size + " × " + mm(Length.getValue());
        case ButtonScrew:
            return "ISO 7380 " + size + " × " + mm(Length.getValue());
        case HexNut:
            return "ISO 4032 " + size;
        case Washer:
            return "ISO 7089 " + size;
        case HeatSetInsert:
            return "Heat-set insert " + size;
        case BallBearing:
            return std::string("Ball bearing ") + Bearing.getValueAsString();
        case DiscMagnet:
            return "Disc magnet " + mm(2 * Radius.getValue()) + " × " + mm(Height.getValue());
        case BlockMagnet:
            return "Block magnet " + mm(Length.getValue()) + " × " + mm(Width.getValue()) + " × " + mm(Height.getValue());
        case AluProfile:
            return std::string("Aluminum profile ") + Profile.getValueAsString() + " × " + mm(Length.getValue());
        default:
            return {};
    }
}

void Primitive::onChanged(const App::Property* prop)
{
    if (prop == &Type) {  // nur die Maße der gewählten Form zeigen
        const long t = Type.getValue();
        const bool screw = t == SocketScrew || t == CountersunkScrew || t == ButtonScrew;
        Length.setStatus(App::Property::Hidden, t != BoxType && !screw && t != BlockMagnet && t != AluProfile);
        Width.setStatus(App::Property::Hidden, t != BoxType && t != BlockMagnet);
        Height.setStatus(App::Property::Hidden, t != BoxType && t != CylinderType && t != DiscMagnet && t != BlockMagnet);
        Radius.setStatus(App::Property::Hidden, t != CylinderType && t != SphereType && t != TorusType && t != CoilType
                                                    && t != DiscMagnet);
        TubeRadius.setStatus(App::Property::Hidden, t != TorusType && t != CoilType);
        Pitch.setStatus(App::Property::Hidden, t != CoilType);
        Turns.setStatus(App::Property::Hidden, t != CoilType);
        Size.setStatus(App::Property::Hidden, t < SocketScrew || t > HeatSetInsert);
        Bearing.setStatus(App::Property::Hidden, t != BallBearing);
        Profile.setStatus(App::Property::Hidden, t != AluProfile);
        for (App::Property* p :
             std::initializer_list<App::Property*> {&Module, &Teeth, &PressureAngle, &Bore, &Rotation, &ProfileShift, &Backlash}) {
            p->setStatus(App::Property::Hidden, t != SpurGear);
        }
        if (t == SpurGear) {
            Height.setStatus(App::Property::Hidden, false);  // Dicke des Rads
        }
        Knuckles.setStatus(App::Property::Hidden, t != Hinge);
        Clearance.setStatus(App::Property::Hidden, t != Hinge && t != SnapRecess);
        Thickness.setStatus(App::Property::Hidden, t != SnapHook && t != SnapRecess);
        Undercut.setStatus(App::Property::Hidden, t != SnapHook && t != SnapRecess);
        if (t == Hinge || t == SnapHook || t == SnapRecess) {  // Länge entlang der Achse bzw. des Balkens, Breite des Blatts bzw. Hakens
            Length.setStatus(App::Property::Hidden, false);
            Width.setStatus(App::Property::Hidden, false);
        }
        Radius.setStatus(App::Property::Hidden, Radius.testStatus(App::Property::Hidden) && t != Hinge);  // Knöchel
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
            case SocketScrew:
            case CountersunkScrew:
            case ButtonScrew:  // stehend: Spitze auf der Ebene, Kopf oben
                shape = screwSolid(int(Type.getValue() - SocketScrew), Size.getValueAsString(), l, error);
                if (shape.IsNull()) {
                    return false;
                }
                break;
            case HexNut: {
                const std::string size = Size.getValueAsString();
                const auto* thread = metricThread(size);
                if (!thread) {
                    error = "Choose a thread size";
                    return false;
                }
                const auto [s, m] = nutSize(size);
                shape = BRepAlgoAPI_Cut(hexPrism(gp_Ax2(gp::Origin(), gp::DZ()), s, m), zCylinder(thread->diameter / 2, -1, m + 1))
                            .Shape();
                break;
            }
            case Washer: {
                const auto [di, da, s] = washerSize(Size.getValueAsString());
                shape = BRepAlgoAPI_Cut(zCylinder(da / 2, 0, s), zCylinder(di / 2, -1, s + 1)).Shape();
                break;
            }
            case HeatSetInsert: {  // vereinfacht ohne Rändel: außen so groß wie die Bohrung + 0,6 mm
                double hole = 0, depth = 0;
                const std::string size = Size.getValueAsString();
                const auto* thread = metricThread(size);
                if (!thread || !insertHole(size, hole, depth)) {
                    error = "There is no heat-set insert for " + size;
                    return false;
                }
                shape = BRepAlgoAPI_Cut(zCylinder(hole / 2 + 0.3, 0, depth), zCylinder(thread->diameter / 2, -1, depth + 1))
                            .Shape();
                break;
            }
            case BallBearing: {  // Ring mit flacher Mulde zwischen Innen- und Außenring auf beiden Seiten
                const auto [di, da, b] = bearingSize(Bearing.getValueAsString());
                const double ring = (da - di) / 4, dip = std::min(0.3, b / 10);
                shape = BRepAlgoAPI_Cut(zCylinder(da / 2, 0, b), zCylinder(di / 2, -1, b + 1)).Shape();
                for (double z : {-1.0, b - dip}) {
                    const TopoDS_Shape groove = BRepAlgoAPI_Cut(zCylinder(da / 2 - ring, z, z + 1 + dip),
                                                                zCylinder(di / 2 + ring, z - 1, z + 2 + dip))
                                                    .Shape();
                    shape = BRepAlgoAPI_Cut(shape, groove).Shape();
                }
                break;
            }
            case DiscMagnet:
                shape = BRepPrimAPI_MakeCylinder(r, h).Shape();
                break;
            case BlockMagnet:
                shape = BRepPrimAPI_MakeBox(gp_Pnt(-l / 2, -w / 2, 0), l, w, h).Shape();
                break;
            case AluProfile:
                shape = profileSection(Profile.getValueAsString(), l);
                break;
            case SpurGear:
                if (!spurGear(Module.getValue(), int(Teeth.getValue()), PressureAngle.getValue(), h, Bore.getValue(),
                               ProfileShift.getValue(), Backlash.getValue(), shape,
                              error)) {
                    return false;
                }
                break;
            case Hinge:
                if (!hinge(l, w, r, int(Knuckles.getValue()), Clearance.getValue(), shape, error)) {
                    return false;
                }
                break;
            case SnapHook:
                if (Thickness.getValue() <= 0 || Undercut.getValue() <= 0 || l <= Undercut.getValue() * 2) {
                    error = "Length, thickness and undercut must be greater than zero, the beam longer than the hook";
                    return false;
                }
                shape = snapHook(l, Thickness.getValue(), Undercut.getValue(), w);
                break;
            case SnapRecess: {  // 12.7: Fenster für die Rastnase eines Hakens mit denselben Maßen und derselben Lage;
                // die Unterkante liegt an der Halteseite der Nase (dort rastet sie ein), sonst rundum das Spiel
                const double t = Thickness.getValue(), y = Undercut.getValue(), c = Clearance.getValue();
                if (t <= 0 || y <= 0 || l <= y * 2) {
                    error = "Length, thickness and undercut must be greater than zero, the beam longer than the hook";
                    return false;
                }
                const double lead = y / std::tan(30 * M_PI / 180);
                shape = BRepPrimAPI_MakeBox(gp_Pnt(t - c, -c, l - lead), y + 2 * c, w + 2 * c, lead + c).Shape();
                break;
            }
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
    gp_Trsf place, offset, turn;
    place.SetDisplacement(gp_Ax3(gp::XOY()), ax);
    turn.SetRotation(gp::OZ(), Rotation.getValue() * M_PI / 180);  // nur beim Zahnrad sichtbar
    // alle stehen auf der Ebene wie Quader und Zylinder: Kugel um r, Torus und Spirale um den Rohrradius angehoben
    const long type = Type.getValue();
    offset.SetTranslation(gp_Vec(PositionX.getValue(), PositionY.getValue(),
                                 type == SphereType                         ? r
                                     : type == TorusType || type == CoilType ? r2
                                                                            : 0));
    tool = Part::TopoShape(BRepBuilderAPI_Transform(shape, place * offset * turn, Standard_True).Shape());
    return true;
}

App::DocumentObjectExecReturn* Primitive::compute()
{
    Part::TopoShape tool;
    std::string error;
    if (!makeTool(tool, error)) {
        return new App::DocumentObjectExecReturn(error);
    }
    // Schnapphaken: zu kurzer Balken bricht beim Einrasten. Bauen, aber warnen und die Länge vorschlagen, die hält
    // (Dehnung am Fuß 1,5·t·y/l², HookStrainLimit). Fester Satz, damit er übersetzt wird; die Zahl steht im Vorschlag
    static const std::string tooStiff = "The hook bends too much and may break; make the beam longer or the catch smaller";
    const bool bends = Type.getValue() == SnapHook
        && hookStrain(Length.getValue(), Thickness.getValue(), Undercut.getValue()) > HookStrainLimit;
    if (bends) {
        const double longer = std::ceil(std::sqrt(1.5 * Thickness.getValue() * Undercut.getValue() / HookStrainLimit));
        suggest("Use length " + mm(longer) + " mm", "Length", longer);
        Warning.setValue(tooStiff);
    }
    else if (Warning.getValue() == tooStiff) {
        Warning.setValue("");
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

namespace
{
const char* ConnectorEnums[] = {"None", "Pins", "Dovetail", nullptr};

/// 12.8: Stifte über einen ebenen Schnitt. Auf jeder Schnittfläche der Teile unter der Ebene (gegen die Normale) wächst
/// ein Zapfen nach oben, das Teil darüber bekommt die Bohrung mit Spiel. Zwei Stifte, wo Platz ist (verdrehsicher),
/// sonst einer in der Mitte des größten Platzes. Liefert die Zahl der Stifte.
int addPins(std::vector<Part::TopoShape>& pieces, const gp_Ax3& ax, double clearance)
{
    const gp_Pln plane(ax);
    const gp_Vec n(ax.Direction());
    std::vector<size_t> below, above;
    for (size_t i = 0; i < pieces.size(); ++i) {
        GProp_GProps props;
        BRepGProp::VolumeProperties(pieces[i].getShape(), props);
        (gp_Vec(ax.Location(), props.CentreOfMass()).Dot(n) < 0 ? below : above).push_back(i);
    }
    std::vector<TopoDS_Shape> holes;
    int count = 0;
    for (size_t i : below) {
        TopTools_ListOfShape pegs;
        for (TopExp_Explorer it(pieces[i].getShape(), TopAbs_FACE); it.More(); it.Next()) {
            const TopoDS_Face face = TopoDS::Face(it.Current());
            BRepAdaptor_Surface surface(face);
            if (surface.GetType() != GeomAbs_Plane || !surface.Plane().Axis().IsParallel(ax.Axis(), 1e-6)
                || plane.Distance(surface.Plane().Location()) > 1e-6) {
                continue;  // keine Schnittfläche
            }
            // Raster über die Fläche: je Punkt innen der Abstand zum Rand (ponytail: 17 x 17 Punkte; sehr lange,
            // schmale Schnitte treffen die Mitte nur ungefähr)
            Bnd_Box box;
            BRepBndLib::Add(face, box);
            double lo[2] = {1e300, 1e300}, hi[2] = {-1e300, -1e300};
            const gp_Vec axes[2] = {gp_Vec(ax.XDirection()), gp_Vec(ax.YDirection())};
            for (int corner = 0; corner < 8; ++corner) {
                const gp_Pnt c = corner & 1 ? box.CornerMax() : box.CornerMin();
                const gp_Pnt d = corner & 2 ? box.CornerMax() : box.CornerMin();
                const gp_Pnt e = corner & 4 ? box.CornerMax() : box.CornerMin();
                const gp_Vec v(ax.Location(), gp_Pnt(c.X(), d.Y(), e.Z()));
                for (int k = 0; k < 2; ++k) {
                    lo[k] = std::min(lo[k], v.Dot(axes[k]));
                    hi[k] = std::max(hi[k], v.Dot(axes[k]));
                }
            }
            TopoDS_Compound rim;
            BRep_Builder builder;
            builder.MakeCompound(rim);
            for (TopExp_Explorer e(face, TopAbs_EDGE); e.More(); e.Next()) {
                builder.Add(rim, e.Current());
            }
            std::vector<std::pair<gp_Pnt, double>> spots;
            const int steps = 16;
            for (int a = 0; a <= steps; ++a) {
                for (int b = 0; b <= steps; ++b) {
                    const gp_Pnt p = ax.Location().Translated(axes[0] * (lo[0] + (hi[0] - lo[0]) * a / steps)
                                                              + axes[1] * (lo[1] + (hi[1] - lo[1]) * b / steps));
                    if (BRepClass_FaceClassifier(face, p, 1e-6).State() != TopAbs_IN) {
                        continue;
                    }
                    BRepExtrema_DistShapeShape dist(BRepBuilderAPI_MakeVertex(p).Vertex(), rim);
                    if (dist.IsDone()) {
                        spots.emplace_back(p, dist.Value());
                    }
                }
            }
            if (spots.empty()) {
                continue;
            }
            const auto roomiest = *std::ranges::max_element(spots, {}, &std::pair<gp_Pnt, double>::second);
            // Stift ein Drittel des Platzes, 3 bis 8 mm dick; rundum bleibt mindestens ein Radius Wand
            const double r = std::min(roomiest.second / 3, 4.0);
            if (r < 1.5) {
                continue;  // zu schmal für einen Stift
            }
            std::vector<gp_Pnt> centers {roomiest.first};
            double far = 6 * r;
            for (size_t s = 0; s < spots.size(); ++s) {
                for (size_t t = s + 1; t < spots.size(); ++t) {
                    if (spots[s].second >= 2 * r && spots[t].second >= 2 * r && spots[s].first.Distance(spots[t].first) > far) {
                        far = spots[s].first.Distance(spots[t].first);
                        centers = {spots[s].first, spots[t].first};
                    }
                }
            }
            for (const gp_Pnt& c : centers) {
                const gp_Ax2 axis(c, ax.Direction());
                // die Bohrung muss ganz im Teil darüber liegen, sonst stünde der Zapfen heraus: 5 r lang (höchstens
                // 12 mm), in dünnem Material kürzer, aber mindestens 2 r
                for (double length = std::min(5 * r, 12.0); length >= 2 * r - 1e-9; length *= 0.75) {
                    TopoDS_Shape hole = BRepPrimAPI_MakeCylinder(axis, r + clearance, length + clearance).Shape();
                    GProp_GProps whole;
                    BRepGProp::VolumeProperties(hole, whole);
                    const bool inside = std::ranges::any_of(above, [&](size_t j) {
                        GProp_GProps common;
                        BRepGProp::VolumeProperties(BRepAlgoAPI_Common(pieces[j].getShape(), hole).Shape(), common);
                        return common.Mass() > whole.Mass() * 0.999;
                    });
                    if (inside) {
                        pegs.Append(BRepPrimAPI_MakeCylinder(axis, r, length).Shape());
                        holes.push_back(hole);
                        ++count;
                        break;
                    }
                }
            }
        }
        if (!pegs.IsEmpty()) {
            TopTools_ListOfShape args;
            args.Append(pieces[i].getShape());
            BRepAlgoAPI_Fuse fuse;
            fuse.SetArguments(args);
            fuse.SetTools(pegs);
            fuse.Build();
            if (fuse.IsDone()) {
                pieces[i] = Part::TopoShape(fuse.Shape());
            }
        }
    }
    if (!holes.empty()) {
        TopTools_ListOfShape tools;
        for (const auto& h : holes) {
            tools.Append(h);
        }
        for (size_t j : above) {
            TopTools_ListOfShape args;
            args.Append(pieces[j].getShape());
            BRepAlgoAPI_Cut cut;
            cut.SetArguments(args);
            cut.SetTools(tools);
            cut.Build();
            if (cut.IsDone()) {
                pieces[j] = Part::TopoShape(cut.Shape());
            }
        }
    }
    return count;
}

/// 12.8 Schwalbenschwanz über einen ebenen Schnitt: auf jeder Schnittfläche unter der Ebene eine Feder, die über die
/// ganze kürzere Richtung der Fläche läuft (dort schiebt man die Stücke zusammen), im Querschnitt ein Trapez, das sich
/// mit 15° vom Schnitt weg verbreitert; das Stück darüber bekommt die Nut mit Spiel. Die Feder bleibt im Material des
/// oberen Stücks (sie ragt nirgends heraus). Liefert die Zahl der Federn.
int addDovetails(std::vector<Part::TopoShape>& pieces, const gp_Ax3& ax, double clearance)
{
    const gp_Pln plane(ax);
    const gp_Vec n(ax.Direction());
    std::vector<size_t> below, above;
    for (size_t i = 0; i < pieces.size(); ++i) {
        GProp_GProps props;
        BRepGProp::VolumeProperties(pieces[i].getShape(), props);
        (gp_Vec(ax.Location(), props.CentreOfMass()).Dot(n) < 0 ? below : above).push_back(i);
    }
    const auto volume = [](const TopoDS_Shape& s) {
        GProp_GProps props;
        BRepGProp::VolumeProperties(s, props);
        return props.Mass();
    };
    int count = 0;
    for (size_t i : below) {
        for (TopExp_Explorer it(pieces[i].getShape(), TopAbs_FACE); it.More(); it.Next()) {
            const TopoDS_Face face = TopoDS::Face(it.Current());
            BRepAdaptor_Surface surface(face);
            if (surface.GetType() != GeomAbs_Plane || !surface.Plane().Axis().IsParallel(ax.Axis(), 1e-6)
                || plane.Distance(surface.Plane().Location()) > 1e-6) {
                continue;  // keine Schnittfläche
            }
            // Ausdehnung der Fläche in der Ebene; geschoben wird entlang der kürzeren Richtung
            Bnd_Box box;
            BRepBndLib::Add(face, box);
            const gp_Vec axes[2] = {gp_Vec(ax.XDirection()), gp_Vec(ax.YDirection())};
            double lo[2] = {1e300, 1e300}, hi[2] = {-1e300, -1e300};
            for (int corner = 0; corner < 8; ++corner) {
                const gp_Pnt c((corner & 1 ? box.CornerMax() : box.CornerMin()).X(),
                               (corner & 2 ? box.CornerMax() : box.CornerMin()).Y(),
                               (corner & 4 ? box.CornerMax() : box.CornerMin()).Z());
                for (int k = 0; k < 2; ++k) {
                    const double v = gp_Vec(ax.Location(), c).Dot(axes[k]);
                    lo[k] = std::min(lo[k], v);
                    hi[k] = std::max(hi[k], v);
                }
            }
            const int slide = hi[0] - lo[0] <= hi[1] - lo[1] ? 0 : 1, across = 1 - slide;
            const double span = hi[across] - lo[across];
            const double narrow = std::clamp(0.3 * span, 3.0, 15.0);       // Breite am Schnitt
            const double depth = std::clamp(0.6 * narrow, 2.0, 8.0);       // so tief geht sie in das obere Stück
            const double flare = depth * std::tan(15 * M_PI / 180);        // je Seite breiter am Ende
            const double mid = (lo[across] + hi[across]) / 2;
            const auto prism = [&](double grow) {  // Trapez quer zur Schieberichtung, über die ganze Fläche gezogen
                const auto at = [&](double w, double d) {
                    return ax.Location().Translated(axes[across] * w + axes[slide] * (lo[slide] - 1) + n * d);
                };
                BRepBuilderAPI_MakePolygon poly;
                poly.Add(at(mid - narrow / 2 - grow, 0));
                poly.Add(at(mid + narrow / 2 + grow, 0));
                poly.Add(at(mid + narrow / 2 + flare + grow, depth + grow));
                poly.Add(at(mid - narrow / 2 - flare - grow, depth + grow));
                poly.Close();
                return BRepPrimAPI_MakePrism(BRepBuilderAPI_MakeFace(poly.Wire()).Face(),
                                             axes[slide] * (hi[slide] - lo[slide] + 2))
                    .Shape();
            };
            const TopoDS_Shape tongue = prism(0), slot = prism(clearance);
            // das obere Stück, in dem die Feder liegt; nur im Material (ragt nirgends heraus)
            size_t best = pieces.size();
            double most = 0;
            for (size_t j : above) {
                const double v = volume(BRepAlgoAPI_Common(pieces[j].getShape(), tongue).Shape());
                if (v > most) {
                    most = v;
                    best = j;
                }
            }
            if (best == pieces.size() || most < 0.5 * volume(tongue)) {
                continue;  // Querschnitt zu unregelmäßig oder zu dünn
            }
            const TopoDS_Shape inside = BRepAlgoAPI_Common(pieces[best].getShape(), tongue).Shape();
            const TopoDS_Shape grown = BRepAlgoAPI_Fuse(pieces[i].getShape(), inside).Shape();
            const TopoDS_Shape cut = BRepAlgoAPI_Cut(pieces[best].getShape(), slot).Shape();
            if (grown.IsNull() || cut.IsNull()) {
                continue;
            }
            pieces[i] = Part::TopoShape(grown);
            pieces[best] = Part::TopoShape(cut);
            ++count;
            break;  // eine Feder je Stück (ein weiteres Durchlaufen der Flächen sähe das neue Stück)
        }
    }
    return count;
}
}  // namespace

Split::Split()
{
    ADD_PROPERTY_TYPE(Tool, (nullptr), "Split", App::Prop_None, "Plane or face to split with");
    ADD_PROPERTY_TYPE(Pieces, (0L), "Split", App::PropertyType(App::Prop_Output | App::Prop_Hidden), "Pieces");
    ADD_PROPERTY_TYPE(Dropped, (), "Split", App::Prop_Hidden, "Pieces whose body was deleted (skipped)");
    ADD_PROPERTY_TYPE(Connector, (0L), "Split", App::Prop_None,
                      "Pins or a dovetail join the pieces again after printing");
    Connector.setEnums(ConnectorEnums);
    ADD_PROPERTY_TYPE(Clearance, (printClearance(1)), "Split", App::Prop_None,
                      "Clearance per side around the pins or the dovetail");
    ADD_PROPERTY_TYPE(PinCount, (0L), "Split", App::PropertyType(App::Prop_Output | App::Prop_Hidden), "Pins");
    Clearance.setStatus(App::Property::Hidden, true);
    Operation.setStatus(App::Property::Hidden, true);
}

void Split::onChanged(const App::Property* prop)
{
    if (prop == &Connector) {
        Clearance.setStatus(App::Property::Hidden, Connector.getValue() == 0);
    }
    Feature::onChanged(prop);
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
    const bool flat = Tool.getValue() && planeAxes(Tool, ax);
    if (flat) {
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
    const long kind = Connector.getValue();
    const int pins = !flat ? 0
        : kind == 1        ? addPins(pieces, ax, Clearance.getValue())
        : kind == 2        ? addDovetails(pieces, ax, Clearance.getValue())
                           : 0;
    if (PinCount.getValue() != pins) {
        PinCount.setValue(pins);
    }
    static const std::string narrow = "The cut is too narrow for pins";
    static const std::string noDovetail = "The cut is too small or too thin for a dovetail";
    if (kind != 0 && pins == 0) {
        Warning.setValue(kind == 1 ? narrow : noDovetail);
    }
    else if (Warning.getValue() == narrow || Warning.getValue() == noDovetail) {
        Warning.setValue("");
    }
    // gelöschte Teile (Body gelöscht) auslassen: sonst rückten die Teile dahinter in fremde Bodies auf
    const auto& dropped = Dropped.getValues();
    std::vector<Part::TopoShape> kept;
    for (size_t i = 0; i < pieces.size(); ++i) {
        if (std::ranges::find(dropped, long(i)) == dropped.end()) {
            kept.push_back(pieces[i]);
        }
    }
    pieces = kept;
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
    // aus für alte Dateien und Skripte (Form bleibt), neue Gewinde aus der Oberfläche schalten es ein
    ADD_PROPERTY_TYPE(EndChamfer, (false), "Parameters", App::Prop_None, "Chamfer the free ends");
    ADD_PROPERTY_TYPE(ForPrinting, (false), "Parameters", App::Prop_None,
                      "Clearance for 3D printing; warns when the pitch is too fine to print");
    ADD_PROPERTY_TYPE(AutoSize, (""), "Thread", App::PropertyType(App::Prop_Output | App::Prop_Hidden | App::Prop_Transient),
                      "Size that Auto picked, e.g. M12");
    Size.setStatus(App::Property::Hidden, true);
    updateSizes();
}

void Thread::onChanged(const App::Property* prop)
{
    if (!isRestoring() && (prop == &Standard || prop == &ThreadSize)) {
        updateSizes();
    }
    if (prop == &ForPrinting) {
        Clearance.setStatus(App::Property::Hidden, ForPrinting.getValue());  // das Spiel kommt dann von selbst
    }
    if (!isRestoring() && (prop == &ForPrinting || prop == &Standard || prop == &ThreadSize || prop == &Pitch)) {
        checkPitch = true;
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
    checkPitch = false;  // ein Hinweis von damals steht noch in Warning
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
    const bool external = isShaftFace(face);

    // Steigung: aus der Norm (Auto: Größe nach dem Durchmesser der Fläche) oder frei
    double p = Pitch.getValue();
    std::string autoSize;
    if (auto table = threadTable(Standard.getValue())) {
        const PartDesign::Hole::ThreadDescription* t = threadSize(Standard.getValue(), ThreadSize.getValueAsString());
        if (!t) {  // Auto: Welle nach Nenndurchmesser, Bohrung nach Kerndurchmesser
            t = &*std::ranges::min_element(*table, {}, [r, external](const auto& s) {
                return std::abs((external ? s.diameter : s.diameter - 1.082532 * s.pitch) - 2 * r);
            });
            autoSize = t->designation;
        }
        p = t->pitch;
    }
    if (autoSize != AutoSize.getValue()) {
        AutoSize.setValue(autoSize);  // der Dialog zeigt "Auto (M12)"
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
        return new App::DocumentObjectExecReturn(
            "The face is too short for this pitch: it must be at least two pitches long. Make the face longer or "
            "choose a finer pitch (e.g. ISO metric fine)");
    }
    // 3D-Druck: Spiel der normalen Druck-Passung, höchstens ein Viertel der Steigung (sonst bleibt kein Gang übrig)
    const double clearance = ForPrinting.getValue() ? std::min(printClearance(1) * 0.75, 0.25 * p) : Clearance.getValue();
    if (checkPitch && ForPrinting.getValue() && p < 1 - 1e-9) {
        Warning.setValue("A pitch below 1 mm prints poorly with a 0.4 mm nozzle; use M8 or larger, or a custom pitch of 1.5 mm");
    }
    checkPitch = false;
    if (std::abs(clearance) >= 0.3 * p) {
        return new App::DocumentObjectExecReturn("Clearance must be smaller than a third of the pitch");
    }
    // ponytail: kein Auslauf (an einem Absatz endet der Gang abrupt); freie Enden bekommen auf Wunsch eine Fase
    Part::TopoShape res(0, getDocument()->getStringHasher());
    try {
        const TopoDS_Shape tool = threadTool(axis, t0, height, r, p, external, LeftHanded.getValue(), clearance);
        // Toleranz: die Enden der Rillen liegen genau in den Stirnflächen, ohne sie trennt OCCT nur Flächen auf
        res.makeElementCut({shape, Part::TopoShape(tool)}, nullptr, 1e-5);
        if (external && EndChamfer.getValue()) {
            // 45° vom Kern (r - Gewindetiefe) an der Stirn bis r: der erste Gang beginnt ohne scharfe Kante
            const double depth = 0.6134 * p;
            const gp_Dir along = axis.Direction();
            gp_Dir radial = along.IsParallel(gp::DZ(), 1e-6) ? gp_Dir(along.Crossed(gp::DX())) : gp_Dir(along.Crossed(gp::DZ()));
            const auto at = [&](double t, double rad) {
                return axis.Location().Translated(gp_Vec(along) * t).Translated(gp_Vec(radial) * rad);
            };
            BRepClass3d_SolidClassifier inside(shape.getShape());
            for (const auto& [end, inward] : {std::pair {t0, 1.0}, std::pair {t1, -1.0}}) {
                // ein Absatz (Material gleich hinter der Stirn): dort keine Fase
                inside.Perform(at(end - inward * 0.1 * p, r - depth / 2), 1e-6);
                if (inside.State() == TopAbs_IN) {
                    continue;
                }
                const double e = 0.05 * p;  // über die Stirn und r hinaus, damit OCCT sauber schneidet
                BRepBuilderAPI_MakePolygon tri(at(end - inward * e, r - depth - e), at(end - inward * e, r + e),
                                               at(end + inward * (depth + e), r + e), true);
                const TopoDS_Shape ring = BRepPrimAPI_MakeRevol(BRepBuilderAPI_MakeFace(tri.Wire()).Face(), axis, 2 * M_PI).Shape();
                Part::TopoShape cut(0, getDocument()->getStringHasher());
                cut.makeElementCut({res, Part::TopoShape(ring)}, nullptr, 1e-5);
                res = cut;
            }
        }
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
    const bool web = Mode.getValue() == 1;
    for (const auto& edge : edges) {
        BRepAdaptor_Curve curve(TopoDS::Edge(edge));
        const bool straight = curve.GetType() == GeomAbs_Line;
        // Web (wächst senkrecht zur Skizze) auch aus Bögen, Splines und geschlossenen Kurven: die Dicke ist dann ein
        // 2D-Versatz der Kurve. ponytail: eine Rippe in der Ebene aus einer Kurve (Versatz bis zum Körper, auf der
        // Innenseite eines Bogens überschlägt er sich) nur aus geraden Linien
        if (!straight && !web) {
            continue;
        }
        const gp_Pnt a = curve.Value(curve.FirstParameter()), b = curve.Value(curve.LastParameter());
        const bool closed = !straight && a.Distance(b) < Precision::Confusion();
        const gp_Vec along = straight ? gp_Vec(a, b) : gp_Vec(normal.Crossed(gp_Vec(1, 0, 0)).Magnitude() > 1e-6
                                                                    ? normal.Crossed(gp_Vec(1, 0, 0)) : normal.Crossed(gp_Vec(0, 1, 0)));
        const gp_Vec inPlane = normal.Crossed(along).Normalized();  // in der Skizzenebene quer zur Linie
        // Rib wächst in der Ebene (quer zur Linie), die Dicke liegt senkrecht dazu; Web umgekehrt
        const gp_Vec grow = web ? normal.Normalized() : inPlane;
        const gp_Vec across = web ? inPlane : normal.Normalized();
        const gp_Vec side = grow;
        const gp_Pnt mid = curve.Value((curve.FirstParameter() + curve.LastParameter()) / 2);
        // Grundfläche der Wand aus einer Kurve: die Kurve um t/2 nach beiden Seiten versetzt (geschlossen: Ring)
        TopoDS_Face curvedFoot;
        if (!straight) {
            try {
                const TopoDS_Wire wire = BRepBuilderAPI_MakeWire(TopoDS::Edge(edge)).Wire();
                const auto offset = [&](double d) {
                    BRepOffsetAPI_MakeOffset off(wire, GeomAbs_Arc, false);
                    off.Perform(d);
                    TopExp_Explorer w(off.Shape(), TopAbs_WIRE);
                    return w.More() ? BRepBuilderAPI_MakeFace(TopoDS::Wire(w.Current()), true).Face() : TopoDS_Face();
                };
                if (closed) {
                    const TopoDS_Face outer = offset(t / 2), inner = offset(-t / 2);
                    TopExp_Explorer f(BRepAlgoAPI_Cut(outer, inner).Shape(), TopAbs_FACE);
                    curvedFoot = f.More() ? TopoDS::Face(f.Current()) : TopoDS_Face();
                }
                else {
                    curvedFoot = offset(t / 2);  // offener Draht: Kontur rund um die Kurve
                }
            }
            catch (const Standard_Failure&) {
            }
            if (curvedFoot.IsNull()) {
                return new App::DocumentObjectExecReturn("This curve cannot be thickened into a web; try a thinner web");
            }
            // der Versatz eines geschlossenen Drahts trägt die Lage der Skizze doppelt: zurück in die Skizzenebene
            TopExp_Explorer v(curvedFoot, TopAbs_VERTEX);
            const gp_Vec n = normal.Normalized();
            const double off = gp_Vec(BRep_Tool::Pnt(TopoDS::Vertex(v.Current())), mid).Dot(n);
            if (std::abs(off) > Precision::Confusion()) {
                gp_Trsf back;
                back.SetTranslation(n * off);
                curvedFoot = TopoDS::Face(BRepBuilderAPI_Transform(curvedFoot, back).Shape());
            }
        }
        // beide Seiten probieren: genommen wird das Stück an der Linie, das ringsum vom Körper begrenzt ist
        bool done = false;
        for (double s : {1.0, -1.0}) {
            const gp_Vec out = grow * (s * far);
            TopoDS_Shape slab;
            if (straight) {
                BRepBuilderAPI_MakePolygon outline(a, b, b.Translated(out), a.Translated(out), Standard_True);
                const TopoDS_Face face = BRepBuilderAPI_MakeFace(outline.Wire()).Face();
                gp_Trsf shift;
                shift.SetTranslation(across * (-t / 2));
                slab = BRepPrimAPI_MakePrism(BRepBuilderAPI_Transform(face, shift).Shape(), across * t).Shape();
            }
            else {
                slab = BRepPrimAPI_MakePrism(curvedFoot, out).Shape();
                GProp_GProps props;  // Fläche gegen die Wuchsrichtung orientiert: der Körper wäre umgestülpt
                BRepGProp::VolumeProperties(slab, props);
                if (props.Mass() < 0) {
                    slab.Reverse();
                }
            }
            BRepAlgoAPI_Cut cut(slab, original);
            if (!cut.IsDone()) {
                continue;
            }
            const gp_Pnt probe = mid.Translated(side * (s * 1e-3 * (1 + (straight ? along.Magnitude() : 1.0))));
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
                // Web: beide Enden der Linie liegen an einer Wand an, sonst stünde die Wand frei im Raum (nur am Boden).
                // Eine gebogene Linie prüft ihre Endpunkte; eine geschlossene hat keine Enden (Ring auf dem Boden)
                if (web && !straight && !closed) {
                    const auto touchesAt = [&](const gp_Pnt& end) {
                        const gp_Pnt below = end.Translated(side * (s * 1e-3 * 2));
                        const gp_Vec tangent = gp_Vec(end, mid).Normalized();
                        const gp_Pnt beyond = below.Translated(tangent * (-(t / 2 + 1e-3)));  // ein Stück hinter dem Ende
                        for (TopExp_Explorer solid(original, TopAbs_SOLID); solid.More(); solid.Next()) {
                            if (BRepClass3d_SolidClassifier(solid.Current(), beyond, 1e-6).State() != TopAbs_OUT) {
                                return true;
                            }
                        }
                        return false;
                    };
                    if (!touchesAt(a) || !touchesAt(b)) {
                        break;
                    }
                }
                else if (web && straight) {
                    const gp_Vec dir = along.Normalized();
                    double u0 = 1e100, u1 = -1e100;
                    for (TopExp_Explorer v(piece.Current(), TopAbs_VERTEX); v.More(); v.Next()) {
                        const double u = gp_Vec(a, BRep_Tool::Pnt(TopoDS::Vertex(v.Current()))).Dot(dir);
                        u0 = std::min(u0, u);
                        u1 = std::max(u1, u);
                    }
                    const auto touches = [&](double u) {  // dicht unter der Linie am Ende des Stücks
                        const gp_Pnt end = a.Translated(dir * u + side * (s * 1e-3 * (1 + along.Magnitude())));
                        for (TopExp_Explorer solid(original, TopAbs_SOLID); solid.More(); solid.Next()) {
                            if (BRepClass3d_SolidClassifier(solid.Current(), end, 1e-6).State() != TopAbs_OUT) {
                                return true;
                            }
                        }
                        return false;
                    };
                    if (!touches(u0) || !touches(u1)) {
                        break;
                    }
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
            return new App::DocumentObjectExecReturn(web ? "Both ends of each web line must touch a wall"
                                                         : "Both ends of each rib line must touch the body");
        }
        ++made;
    }
    if (!made) {
        return new App::DocumentObjectExecReturn(web ? "Select sketch lines or curves for the web"
                                                     : "Select straight sketch lines for the rib");
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
    // Wie ein Schnitt, der nichts mehr trifft: nach einer Änderung weiter vorn Warnung und Körper durchreichen. Ein
    // Fehler hielt alles danach an (Teilung, neue Skizzen darauf erschienen nicht; ConceptKey)
    static constexpr const char* misses = "Nothing split: the tool no longer crosses the selected faces";
    if (!added) {
        setResults({shape});
        Warning.setValue(misses);
        return StdReturn;
    }
    if (std::string(Warning.getValue()) == misses) {
        Warning.setValue("");
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

namespace
{
/// Joints, die über gemeinsame Komponenten mit joint verbunden sind (die Wurzel trennt: sie bewegt sich nie)
std::vector<Design::Joint*> jointGroup(Design::Joint* joint)
{
    App::Document* doc = joint->getDocument();
    const App::Part* rootPart = Design::root(doc, false);
    std::vector<Design::Joint*> all;
    for (auto obj : doc->getObjectsOfType(Design::Joint::getClassTypeId())) {
        all.push_back(static_cast<Design::Joint*>(obj));
    }
    const auto parts = [](Design::Joint* j) {
        std::vector<App::DocumentObject*> p {j->Moving.getValue()};
        if (j->Origin2.getValue()) {
            p.push_back(Design::componentOf(j->Origin2.getValue()));
        }
        return p;
    };
    std::vector<Design::Joint*> group {joint};
    for (size_t i = 0; i < group.size(); ++i) {
        for (Design::Joint* j : all) {
            if (std::ranges::find(group, j) != group.end()) {
                continue;
            }
            for (auto a : parts(group[i])) {
                for (auto b : parts(j)) {
                    if (a && a == b && a != rootPart) {
                        group.push_back(j);
                        goto next;
                    }
                }
            }
        next:;
        }
    }
    std::ranges::sort(group, {}, [](Design::Joint* j) { return std::string(j->getNameInDocument()); });
    return group;
}
}  // namespace

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
    // Hat eine Komponente der Gruppe zwei Joints, ist die Kette geschlossen (Viergelenk): dann löst der Solver alles
    // zusammen. Sonst wie bisher: jeder Joint setzt seine Komponente direkt.
    const std::vector<Joint*> group = jointGroup(this);
    std::map<App::DocumentObject*, int> moves;
    for (Joint* j : group) {
        ++moves[j->Moving.getValue()];
    }
    if (std::ranges::any_of(moves, [](const auto& m) { return m.second > 1; })) {
        return solveLoop(group);
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
        case Revolute:  // wie Fusion: Versatz entlang der Achse (Arm auf statt in der Platte, 13.6)
            move.z = offset;
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

short Joint::mustExecute() const
{
    if (isTouched()) {
        return 1;
    }
    const auto group = jointGroup(const_cast<Joint*>(this));
    std::map<App::DocumentObject*, int> moves;
    for (Joint* j : group) {
        ++moves[j->Moving.getValue()];
    }
    const bool loop = std::ranges::any_of(moves, [](const auto& m) { return m.second > 1; });
    return loop && std::ranges::any_of(group, [](Joint* j) { return j->isTouched(); }) ? 1 : App::DocumentObject::mustExecute();
}

Base::Placement Joint::motion() const
{
    const auto clamp = [this](double v, const App::PropertyQuantity& lo, const App::PropertyQuantity& hi) {
        return Limited.getValue() ? std::clamp(v, std::min(lo.getValue(), hi.getValue()), std::max(lo.getValue(), hi.getValue()))
                                  : v;
    };
    const double angle = clamp(Angle.getValue(), AngleMin, AngleMax) * M_PI / 180.0;
    const double offset = clamp(Offset.getValue(), OffsetMin, OffsetMax);
    Base::Vector3d move;
    Base::Rotation turn(Base::Vector3d(0, 0, 1), angle);
    switch (Type.getValue()) {
        case Slider: move.z = offset; turn = Base::Rotation(); break;
        case Revolute: move.z = offset; break;
        case PinSlot: move.x = offset; break;
        case Planar: move = Base::Vector3d(offset, Offset2.getValue(), 0); break;
        case Ball: turn.setYawPitchRoll(Angle.getValue(), Angle2.getValue(), Angle3.getValue()); break;
        default: move.z = offset; break;
    }
    return Base::Placement(move, turn);
}

/// Geschlossene Kette (L6): alle Joints der Gruppe gemeinsam mit dem Solver. Der erste Joint der Gruppe treibt mit
/// seinem Winkel bzw. Weg (wie Fusions "Drive Joints"), feste Joints ebenso; die übrigen bewegen sich frei. Komponenten,
/// die keiner der Joints bewegt, bleiben stehen. Jeder Joint setzt danach die Lage seiner Komponente in Result.
/// Jeder Joint der Gruppe braucht dieselbe Lösung: sie wird einmal gerechnet und für gleiche Eingaben (feste Teile,
/// Joints) wiederverwendet. Die Startlagen der beweglichen Teile zählen nicht, nach dem ersten Joint stehen sie schon
/// auf der Lösung.
App::DocumentObjectExecReturn* Joint::solveLoop(const std::vector<Joint*>& group)
{
    std::vector<Solver::Part> parts;
    std::vector<Solver::Link> links;
    const auto partOf = [&parts](App::Part* comp, bool fixed) {
        const std::string name = comp->getNameInDocument();
        auto it = std::ranges::find(parts, name, &Solver::Part::name);
        if (it == parts.end()) {
            parts.push_back({name, comp->globalPlacement(), fixed});
            return;
        }
        it->fixed = it->fixed && fixed;
    };
    for (Joint* j : group) {
        partOf(static_cast<App::Part*>(j->Moving.getValue()), false);
    }
    for (Joint* j : group) {
        App::Part* other = componentOf(j->Origin2.getValue());
        const bool moved = std::ranges::any_of(group, [other](Joint* k) { return k->Moving.getValue() == other; });
        partOf(other, !moved);
    }
    for (Joint* j : group) {
        Base::Placement f1, f2;
        bool planar1 = false, planar2 = false;
        if (!jointFrame(j->Origin1, f1, planar1) || !jointFrame(j->Origin2, f2, planar2)) {
            return new App::DocumentObjectExecReturn(std::string(j->Label.getValue()) + " has no snap point");
        }
        Base::Placement flip;
        if ((planar1 && planar2) != j->Flip.getValue()) {
            flip = Base::Placement(Base::Vector3d(), Base::Rotation(Base::Vector3d(1, 0, 0), M_PI));
        }
        // Rahmen in den Komponenten (f1, f2 sind schon komponenten-lokal): global gilt Lage(b) * onB = Lage(a) * onA
        const Base::Placement& placeA = f2;
        const bool drives = j == group.front() || j->Type.getValue() == Rigid;
        Solver::Kind kind = Solver::Kind::Fixed;
        if (!drives) {
            switch (j->Type.getValue()) {
                case Revolute: kind = Solver::Kind::Revolute; break;
                case Slider: kind = Solver::Kind::Slider; break;
                case Cylindrical: kind = Solver::Kind::Cylindrical; break;
                case Planar: kind = Solver::Kind::Planar; break;
                case Ball: kind = Solver::Kind::Ball; break;
                default: kind = Solver::Kind::PinSlot; break;
            }
        }
        links.push_back({j->getNameInDocument(), kind, componentOf(j->Origin2.getValue())->getNameInDocument(),
                         j->Moving.getValue()->getNameInDocument(), drives ? placeA * j->motion() : placeA,
                         f1 * flip.inverse()});
    }
    std::ostringstream key;
    key << std::setprecision(17);
    const auto put = [&key](const Base::Placement& p) {
        const Base::Vector3d& v = p.getPosition();
        double q[4];
        p.getRotation().getValue(q[0], q[1], q[2], q[3]);
        key << v.x << ' ' << v.y << ' ' << v.z << ' ' << q[0] << ' ' << q[1] << ' ' << q[2] << ' ' << q[3] << ';';
    };
    for (const auto& p : parts) {
        key << p.name << (p.fixed ? '!' : '~');
        if (p.fixed) {
            put(p.pose);
        }
    }
    for (const auto& l : links) {
        key << l.name << int(l.kind) << l.a << '>' << l.b;
        put(l.onA);
        put(l.onB);
    }
    static std::map<std::string, std::vector<Solver::Part>> solved;  // Eingaben -> gelöste Lagen
    if (auto hit = solved.find(key.str()); hit != solved.end()) {
        parts = hit->second;
    }
    else {
        std::string error;
        if (!Solver::solve(parts, links, error)) {
            return new App::DocumentObjectExecReturn(error);
        }
        if (solved.size() > 64) {
            solved.clear();  // genug: Ziehen am Antrieb erzeugt laufend neue Eingaben
        }
        solved[key.str()] = parts;
    }
    // Grenzen der frei folgenden Joints: wo der Mechanismus sie verlassen müsste, sagen statt still überschreiten
    for (size_t i = 0; i < group.size(); ++i) {
        Joint* j = group[i];
        if (!j->Limited.getValue() || links[i].kind == Solver::Kind::Fixed) {
            continue;
        }
        const auto pose = [&parts](const std::string& name) {
            return std::ranges::find(parts, name, &Solver::Part::name)->pose;
        };
        const Base::Placement rel = (pose(links[i].a) * links[i].onA).inverse() * (pose(links[i].b) * links[i].onB);
        Base::Vector3d axis;
        double angle = 0;
        rel.getRotation().getRawValue(axis, angle);
        angle = std::remainder((axis.z < 0 ? -angle : angle) * 180 / M_PI, 360.0);
        const double offset = j->Type.getValue() == PinSlot || j->Type.getValue() == Planar ? rel.getPosition().x : rel.getPosition().z;
        const auto outside = [](double v, const App::PropertyQuantity& lo, const App::PropertyQuantity& hi) {
            return v < std::min(lo.getValue(), hi.getValue()) - 1e-6 || v > std::max(lo.getValue(), hi.getValue()) + 1e-6;
        };
        if (j->turns() && outside(angle, j->AngleMin, j->AngleMax)) {
            return new App::DocumentObjectExecReturn(std::string(j->Label.getValue()) + " would have to turn past its limits (to "
                                                     + std::to_string(int(std::round(angle))) + " degrees)");
        }
        if (j->slides() && outside(offset, j->OffsetMin, j->OffsetMax)) {
            return new App::DocumentObjectExecReturn(std::string(j->Label.getValue()) + " would have to slide past its limits");
        }
    }
    // nur der erste Joint einer Komponente setzt ihre Lage (an ihn ist Placement gebunden)
    auto moving = static_cast<App::Part*>(Moving.getValue());
    const auto pose = std::ranges::find(parts, std::string(moving->getNameInDocument()), &Solver::Part::name);
    const App::Part* parent = parentPart(moving);
    Result.setValue(parent ? parent->globalPlacement().inverse() * pose->pose : pose->pose);
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

bool Design::frameOf(App::DocumentObject* obj, const std::string& sub, Frame& f)
{
    static const Base::Type datum = Base::Type::fromName("Part::Datum");
    const bool plane = obj && (obj->isDerivedFrom<App::Plane>() || (!datum.isBad() && obj->getTypeId().isDerivedFrom(datum)));
    if (sub.empty() && plane) {
        const Base::Placement p = static_cast<App::GeoFeature*>(obj)->globalPlacement();
        Base::Vector3d z;
        p.getRotation().multVec(Base::Vector3d(0, 0, 1), z);
        f = {gp_Pnt(p.getPosition().x, p.getPosition().y, p.getPosition().z), gp_Dir(z.x, z.y, z.z), true, true};
        return true;
    }
    return frameOf(Part::Feature::getTopoShape(obj, Part::ShapeOption::ResolveLink | Part::ShapeOption::Transform
                                                        | Part::ShapeOption::NeedSubElement,
                                                    sub.empty() ? nullptr : sub.c_str())
                       .getShape(),
                   f);
}

bool Design::frameOf(const TopoDS_Shape& s, Frame& f)
{
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

Base::Placement Design::alignment(const Frame& from, const Frame& to)
{
    Base::Rotation rot;
    if (from.hasDir && to.hasDir) {
        const gp_Dir target = from.planar && to.planar ? to.dir.Reversed() : to.dir;
        rot = Base::Rotation(Base::Vector3d(from.dir.X(), from.dir.Y(), from.dir.Z()),
                             Base::Vector3d(target.X(), target.Y(), target.Z()));
    }
    Base::Vector3d moved;
    rot.multVec(Base::Vector3d(from.point.X(), from.point.Y(), from.point.Z()), moved);
    return Base::Placement(Base::Vector3d(to.point.X(), to.point.Y(), to.point.Z()) - moved, rot);
}

PROPERTY_SOURCE(Design::Midplane, PartDesign::Plane)

Midplane::Midplane()
{
    ADD_PROPERTY_TYPE(Faces, (nullptr), "Midplane", App::Prop_None, "The two parallel planes or planar faces");
    Faces.setScope(App::LinkScope::Global);
    MapMode.setValue("Deactivated");  // die Lage rechnet execute(), nicht der Attacher
}

App::DocumentObjectExecReturn* Midplane::execute()
{
    const auto& objs = Faces.getValues();
    const auto& subs = Faces.getSubValues();
    if (objs.size() != 2 || subs.size() != 2) {
        return new App::DocumentObjectExecReturn("Select two parallel planes or planar faces");
    }
    gp_Pnt centre[2];
    gp_Dir normal[2];
    for (int i = 0; i < 2; ++i) {
        const Part::TopoShape s = Part::Feature::getTopoShape(
            objs[i], Part::ShapeOption::ResolveLink | Part::ShapeOption::Transform | Part::ShapeOption::NeedSubElement,
            subs[i].empty() ? nullptr : subs[i].c_str());
        TopExp_Explorer face(s.getShape(), TopAbs_FACE);
        if (!face.More() || BRepAdaptor_Surface(TopoDS::Face(face.Current())).GetType() != GeomAbs_Plane) {
            return new App::DocumentObjectExecReturn("The midplane lost one of its planes or faces");
        }
        GProp_GProps props;
        BRepGProp::SurfaceProperties(face.Current(), props);
        centre[i] = props.CentreOfMass();
        normal[i] = BRepAdaptor_Surface(TopoDS::Face(face.Current())).Plane().Axis().Direction();
        if (face.Current().Orientation() == TopAbs_REVERSED) {
            normal[i].Reverse();
        }
    }
    if (!normal[0].IsParallel(normal[1], 1e-6)) {
        return new App::DocumentObjectExecReturn("The two planes are no longer parallel");
    }
    // Mitte der beiden Flächenmitten liegt auf der Mittelebene (parallele Ebenen); Normale wie die erste Fläche
    const Base::Vector3d at((centre[0].X() + centre[1].X()) / 2, (centre[0].Y() + centre[1].Y()) / 2,
                            (centre[0].Z() + centre[1].Z()) / 2);
    const Base::Rotation turn(Base::Vector3d(0, 0, 1), Base::Vector3d(normal[0].X(), normal[0].Y(), normal[0].Z()));
    const Base::Placement global(at, turn);
    App::Part* container = Design::componentOf(this);
    Placement.setValue(container ? container->globalPlacement().inverse() * global : global);
    return PartDesign::Plane::execute();
}

PROPERTY_SOURCE(Design::Note, App::DocumentObject)

Note::Note()
{
    ADD_PROPERTY_TYPE(Text, (""), "Note", App::Prop_NoRecompute, "Text of the note");
    ADD_PROPERTY_TYPE(Corner, (3L), "Note", App::Prop_NoRecompute, "Window corner it stays in: bit 0 right, bit 1 bottom");
    ADD_PROPERTY_TYPE(OffsetX, (12L), "Note", App::Prop_NoRecompute, "Horizontal distance to that corner");
    ADD_PROPERTY_TYPE(OffsetY, (12L), "Note", App::Prop_NoRecompute, "Vertical distance to that corner");
    ADD_PROPERTY_TYPE(Defines, (), "Note", App::PropertyType(App::Prop_Hidden | App::Prop_NoRecompute),
                      "Parameters defined by lines of this note");
}

void Note::onBeforeChange(const App::Property* prop)
{
    if (prop != &Text && prop != &Corner && prop != &OffsetX && prop != &OffsetY && prop != &Visibility && prop != &Defines) {
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
    ADD_PROPERTY_TYPE(Depths, (), "Scribble", hidden, "Red pen: how far behind the sheet the model lies under each stroke");
    ADD_PROPERTY_TYPE(OnModel, (false), "Scribble", hidden, "Red pen: each stroke shows on the model under it");
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
        s.depth = Depths.getSize() == int(n) ? Depths[int(i)] : 0;
        at += count;
    }
    return result;
}

void Scribble::setStrokes(const std::vector<Stroke>& strokes)
{
    std::vector<Base::Vector3d> points, normals;
    std::vector<double> widths, depths;
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
        depths.push_back(s.depth);
    }
    // Counts zuletzt: erst dann passen die Listen wieder zusammen (die Ansicht zeichnet nur zusammenpassende)
    Points.setValues(points);
    Widths.setValues(widths);
    Tools.setValues(tools);
    Kinds.setValues(kinds);
    Colors.setValues(colors);
    Normals.setValues(normals);
    Depths.setValues(depths);
    Counts.setValues(counts);
}
