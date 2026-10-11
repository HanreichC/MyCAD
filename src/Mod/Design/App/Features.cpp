// SPDX-License-Identifier: LGPL-2.1-or-later

#include "Features.h"

#include <App/Document.h>
#include <App/DocumentObjectGroup.h>
#include <App/Part.h>
#include <App/Origin.h>
#include <App/GeoFeatureGroupExtension.h>
#include <App/ElementNamingUtils.h>
#include <App/IndexedName.h>
#include <App/MappedName.h>
#include <Base/Placement.h>
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
#include <BRepOffset_MakeOffset.hxx>
#include <BRepAdaptor_Curve.hxx>
#include <BRepAlgoAPI_Cut.hxx>
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

using namespace Design;

namespace
{
const char* OpEnums[] = {"New Body", "Join", "Cut", "Intersect", nullptr};
const char* ExtentEnums[] = {"One Side", "Symmetric", "Two Sides", nullptr};
const char* AxisEnums[] = {"Sketch X", "Sketch Y", "X", "Y", "Z", nullptr};
const char* XYZEnums[] = {"X", "Y", "Z", nullptr};
const char* PlaneEnums[] = {"XY", "XZ", "YZ", nullptr};
const char* PatternEnums[] = {"Rectangular", "Circular", nullptr};
const char* HoleEnums[] = {"Simple", "Counterbore", "Countersink", nullptr};
const char* PrimitiveEnums[] = {"Box", "Cylinder", "Sphere", "Torus", "Coil", nullptr};
const char* CenterEnums[] = {"Origin", "Body center", nullptr};
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
        obj, Part::ShapeOption::ResolveLink | Part::ShapeOption::Transform, subs.front().c_str());
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

/// Mehrere Werkzeugkörper zu einem vereinen
Part::TopoShape fuseAll(const std::vector<Part::TopoShape>& shapes, App::StringHasherRef hasher)
{
    if (shapes.size() == 1) {
        return shapes.front();
    }
    Part::TopoShape tool = Part::TopoShape(0, hasher).makeElementFuse(shapes);
    return tool.makeElementRefine(nullptr, Part::RefineFail::shapeUntouched);
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
    for (auto obj : root->Group.getValues()) {
        auto group = freecad_cast<App::DocumentObjectGroup*>(obj);
        if (group && std::string(group->Label.getValue()) == label) {
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
}

App::DocumentObjectExecReturn* Feature::execute()
{
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
}

bool Extrude::makeTool(Part::TopoShape& tool, std::string& error) const
{
    Part::Feature* sketch = nullptr;
    const char* reason = nullptr;
    const auto faces = profileFaces(Profile, const_cast<App::PropertyStringList&>(ProfileKeys), sketch, reason);
    if (faces.empty()) {
        error = reason;
        return false;
    }

    Base::Vector3d n = sketch->Placement.getValue().getRotation().multVec(Base::Vector3d(0, 0, 1));
    if (Reversed.getValue()) {
        n = -n;
    }
    double start = 0, end = Distance.getValue();
    if (Extent.getValue() == 1) {  // Symmetric
        start = -end / 2;
        end /= 2;
    }
    else if (Extent.getValue() == 2) {  // Two Sides
        start = -Distance2.getValue();
    }
    if (end - start < Precision::Confusion()) {
        error = "Distance must be greater than zero";
        return false;
    }

    std::vector<Part::TopoShape> prisms;
    for (const auto& face : faces) {
        Part::TopoShape base = face;
        if (start != 0) {
            Base::Matrix4D mov;
            mov.move(n * start);
            base = Part::TopoShape(0, getDocument()->getStringHasher()).makeElementTransform(face, mov);
        }
        const Base::Vector3d v = n * (end - start);
        prisms.push_back(Part::TopoShape(0, getDocument()->getStringHasher())
                             .makeElementPrism(base, gp_Vec(v.x, v.y, v.z)));
    }
    tool = fuseAll(prisms, getDocument()->getStringHasher());
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
    switch (Axis.getValue()) {
        case 0:
            origin = pla.getPosition();
            dir = pla.getRotation().multVec(Base::Vector3d(1, 0, 0));
            break;
        case 1:
            origin = pla.getPosition();
            dir = pla.getRotation().multVec(Base::Vector3d(0, 1, 0));
            break;
        default:
            dir[Axis.getValue() - 2] = 1;
            break;
    }
    if (Reversed.getValue()) {
        dir = -dir;
    }
    const gp_Ax1 axis(gp_Pnt(origin.x, origin.y, origin.z), gp_Dir(dir.x, dir.y, dir.z));

    std::vector<Part::TopoShape> solids;
    for (const auto& face : faces) {
        solids.push_back(Part::TopoShape(0, getDocument()->getStringHasher())
                             .makeElementRevolve(face, axis, angle * M_PI / 180.0));
    }
    tool = fuseAll(solids, getDocument()->getStringHasher());
    return true;
}

App::DocumentObjectExecReturn* Revolve::compute()
{
    Part::TopoShape tool;
    std::string error;
    if (!makeTool(tool, error)) {
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
    Operation.setStatus(App::Property::Hidden, true);  // verändert immer den eigenen Body
}

std::vector<Part::TopoShape> DressUp::elements(const Part::TopoShape& shape, TopAbs_ShapeEnum type)
{
    // Gewählte Elemente über ihre verfolgbaren Namen wiederfinden (topologische Benennung):
    // 1. derselbe Name existiert noch, 2. ein Element, das laut Entstehungsgeschichte daraus hervorging
    //    (z. B. wenn davor ein Feature eingefügt wurde), 3. sonst die ursprüngliche Nummer.
    std::vector<std::string> names = Edges.getValues();
    std::vector<std::string> maps = ElementMaps.getValues();
    maps.resize(names.size());
    App::DocumentObject* base = BaseFeatures.getSize() ? BaseFeatures.getValues().front() : nullptr;
    for (size_t i = 0; i < names.size(); ++i) {
        if (!maps[i].empty()) {
            const Data::IndexedName idx = shape.getIndexedName(Data::MappedName(maps[i]));
            if (idx) {
                names[i] = idx.toString();
            }
            else if (base) {
                const auto related = Part::Feature::getRelatedElements(
                    base, (std::string(Data::ELEMENT_MAP_PREFIX) + maps[i]).c_str()
                );
                if (!related.isEmpty()) {
                    names[i] = related.front().index.toString();
                }
            }
        }
        const Data::MappedName mapped = shape.getMappedName(Data::IndexedName(names[i].c_str()));
        if (mapped) {
            maps[i] = mapped.toString();
        }
    }
    ElementMaps.setValues(maps);  // Ausgabe-Property: markiert das Feature nicht als geändert

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
            res.makeElementFillet(shape, edges, size, size);
        }
        else {
            res.makeElementChamfer(shape, edges, Part::ChamferType::equalDistance, size, size);
        }
    }
    catch (const Standard_Failure&) {
        return new App::DocumentObjectExecReturn(failed);
    }
    if (res.isNull() || !res.isValid()) {
        return new App::DocumentObjectExecReturn(failed);
    }
    setResults({res});
    return StdReturn;
}

PROPERTY_SOURCE(Design::Fillet, Design::DressUp)
PROPERTY_SOURCE(Design::Chamfer, Design::DressUp)

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
    Part::TopoShape res(0, getDocument()->getStringHasher());
    try {
        // Ohne geöffnete Fläche entsteht ein geschlossener Hohlkörper
        res.makeElementThickSolid(shape, faces, Outside.getValue() ? t : -t, 1e-6, true, false, 0,
                                  Part::JoinType::intersection);
    }
    catch (const Standard_Failure&) {
        return new App::DocumentObjectExecReturn("Shell failed: thickness too large?");
    }
    if (res.isNull() || !res.isValid()) {
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
        shapes.push_back(state->shapeFor(tools[i]));
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
        Base::BoundBox3d bb = base.getBoundBox();
        bb = bb.Transformed(Alignment.getValue().toMatrix());  // gedreht wird um die Mitte nach dem Ausrichten
        Base::Vector3d axis;
        axis[RotationAxis.getValue()] = 1;
        Base::Placement rot(Base::Vector3d(), Base::Rotation(axis, Angle.getValue() * M_PI / 180.0), bb.GetCenter());
        Base::Placement move(Translation.getValue(), Base::Rotation());
        Base::Matrix4D mat = (move * rot * Alignment.getValue()).toMatrix();
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
    ADD_PROPERTY_TYPE(Plane, (2L), "Mirror", App::Prop_None, "Mirror plane");
    Plane.setEnums(PlaneEnums);
    Operation.setStatus(App::Property::Hidden, true);
}

App::DocumentObjectExecReturn* Mirror::compute()
{
    const auto& sources = SourceBodies.getValues();
    const auto& states = SourceFeatures.getValues();
    if (sources.empty() || sources.size() != states.size() || Bodies.getSize() != int(sources.size())) {
        return new App::DocumentObjectExecReturn("Select one or more bodies");
    }
    static const gp_Dir normals[] = {gp::DZ(), gp::DY(), gp::DX()};
    const gp_Ax2 plane(gp::Origin(), normals[Plane.getValue()]);
    std::vector<Part::TopoShape> results;
    for (size_t i = 0; i < sources.size(); ++i) {
        auto state = freecad_cast<Feature*>(states[i]);
        if (!state) {
            return new App::DocumentObjectExecReturn("Body has no feature");
        }
        results.push_back(Part::TopoShape(0, getDocument()->getStringHasher())
                              .makeElementMirror(state->shapeFor(sources[i]), plane));
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
    Operation.setValue(1L);
}

std::vector<Base::Matrix4D> Pattern::transforms() const
{
    std::vector<Base::Matrix4D> transforms;
    if (Type.getValue() == 0) {
        Base::Vector3d d1, d2;
        d1[Direction1.getValue()] = Spacing1.getValue();
        d2[Direction2.getValue()] = Spacing2.getValue();
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
    else {
        const long n = Count1.getValue();
        const double total = Angle.getValue();
        const bool full = std::abs(total - 360.0) < Precision::Angular();
        const double step = n > 1 ? (full ? total / n : total / (n - 1)) : 0;
        Base::Vector3d axis;
        axis[Axis.getValue()] = 1;
        for (long k = 1; k < n; ++k) {
            transforms.push_back(Base::Placement(Base::Vector3d(), Base::Rotation(axis, k * step * M_PI / 180.0)).toMatrix());
        }
    }
    return transforms;
}

App::DocumentObjectExecReturn* Pattern::compute()
{
    const std::vector<Base::Matrix4D> transforms = this->transforms();
    if (transforms.empty()) {
        return new App::DocumentObjectExecReturn("Count must be at least 2");
    }
    auto copiesOf = [&](const Part::TopoShape& shape) {
        std::vector<Part::TopoShape> copies;
        for (const auto& m : transforms) {
            copies.push_back(Part::TopoShape(0, getDocument()->getStringHasher())
                                 .makeElementTransform(shape, m, nullptr, Part::CheckScale::noScaleCheck,
                                                       Part::CopyType::copy));
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
            results.push_back(Part::TopoShape(0, getDocument()->getStringHasher())
                                  .makeElementCompound(copiesOf(state->shapeFor(sources[i]))));
        }
        setResults(results);
        return StdReturn;
    }
    auto source = freecad_cast<Feature*>(Source.getValue());
    if (!source) {
        return new App::DocumentObjectExecReturn("Select a feature or bodies to pattern");
    }
    Part::TopoShape tool;
    std::string error;
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
    Operation.setValue(2L);  // Cut
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
    const double depth = (ThroughAll.getValue() ? 10000.0 : Depth.getValue()) + lead;  // ponytail: "durch alles" = 10 m

    std::vector<Part::TopoShape> holes;
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
        holes.push_back(fuseAll(parts, getDocument()->getStringHasher()));
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
        const Base::Vector3d c = Center.getValue() == 1 ? base.getBoundBox().GetCenter() : Base::Vector3d();
        Base::Matrix4D mat;
        mat.move(-c);
        mat.scale(Factor.getValue());
        mat.move(c);
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
        const Base::BoundBox3d bb = shape.getBoundBox();
        const double s = bb.CalcDiagonalLength() * 2 + 10;
        tool = BRepBuilderAPI_MakeFace(gp_Pln(ax), -s, s, -s, s).Face();
    }
    else if (Tool.getValue()) {
        const auto& subs = Tool.getSubValues();
        tool = Part::Feature::getTopoShape(Tool.getValue(), Part::ShapeOption::ResolveLink | Part::ShapeOption::Transform,
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
    ADD_PROPERTY_TYPE(Pitch, (1.5), "Parameters", App::Prop_None, "Thread pitch");
    ADD_PROPERTY_TYPE(LeftHanded, (false), "Parameters", App::Prop_None, "Left-handed thread");
    Size.setStatus(App::Property::Hidden, true);
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
    const gp_Ax1 axis = cyl.Axis();
    const double r = cyl.Radius(), p = Pitch.getValue();
    // Länge der Fläche entlang der Achse
    double t0 = 1e100, t1 = -1e100;
    for (TopExp_Explorer v(face, TopAbs_VERTEX); v.More(); v.Next()) {
        const double t = gp_Vec(axis.Location(), BRep_Tool::Pnt(TopoDS::Vertex(v.Current()))).Dot(gp_Vec(axis.Direction()));
        t0 = std::min(t0, t);
        t1 = std::max(t1, t);
    }
    const double height = t1 - t0 - p;  // eine halbe Steigung Abstand an beiden Enden
    if (p < Precision::Confusion() || height < p) {
        return new App::DocumentObjectExecReturn("The face is too short for this pitch");
    }
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
    const double depth = (external ? 0.6134 : 0.5413) * p;
    const double out = external ? 0.05 : -0.05, in = external ? -depth : depth;
    // ponytail: vereinfachtes V-Profil ohne Abflachungen, Gewindeenden enden stumpf
    TopoDS_Shape tool;
    try {
        const TopoDS_Shape helix = Part::TopoShape().makeHelix(p, height, r, 0, LeftHanded.getValue());
        TopExp_Explorer spine(helix, TopAbs_WIRE);
        BRepBuilderAPI_MakePolygon profile(gp_Pnt(r + out, 0, -0.45 * p), gp_Pnt(r + out, 0, 0.45 * p),
                                           gp_Pnt(r + in, 0, 0), Standard_True);
        BRepOffsetAPI_MakePipeShell pipe(TopoDS::Wire(spine.Current()));
        pipe.SetMode(gp::DZ());  // Profil bleibt parallel zur Achse
        pipe.Add(profile.Wire());
        pipe.Build();
        pipe.MakeSolid();
        gp_Trsf place;
        place.SetDisplacement(gp_Ax3(gp::XOY()),
                              gp_Ax3(axis.Location().Translated(gp_Vec(axis.Direction()) * (t0 + p / 2)),
                                     axis.Direction()));
        tool = BRepBuilderAPI_Transform(pipe.Shape(), place, Standard_True).Shape();
    }
    catch (const Standard_Failure&) {
        return new App::DocumentObjectExecReturn("Thread failed");
    }
    Part::TopoShape res(0, getDocument()->getStringHasher());
    try {
        res.makeElementCut({shape, Part::TopoShape(tool)});
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
        const gp_Vec side = normal.Crossed(along).Normalized();  // in der Skizzenebene quer zur Linie
        const gp_Pnt mid = a.Translated(along * 0.5);
        // beide Seiten probieren: genommen wird das Stück an der Linie, das ringsum vom Körper begrenzt ist
        bool done = false;
        for (double s : {1.0, -1.0}) {
            const gp_Vec out = side * (s * far);
            BRepBuilderAPI_MakePolygon outline(a, b, b.Translated(out), a.Translated(out), Standard_True);
            const TopoDS_Face face = BRepBuilderAPI_MakeFace(outline.Wire()).Face();
            gp_Trsf shift;
            shift.SetTranslation(normal.Normalized() * (-t / 2));
            const TopoDS_Shape slab = BRepPrimAPI_MakePrism(BRepBuilderAPI_Transform(face, shift).Shape(),
                                                            normal.Normalized() * t)
                                          .Shape();
            BRepAlgoAPI_Cut cut(slab, shape.getShape());
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
