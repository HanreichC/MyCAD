// SPDX-License-Identifier: LGPL-2.1-or-later

#include "Features.h"

#include <App/Document.h>
#include <App/DocumentObjectGroup.h>
#include <App/Part.h>
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
#include <TopoDS_Iterator.hxx>
#include <gp_Ax1.hxx>
#include <gp_Ax2.hxx>
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
const App::PropertyIntegerConstraint::Constraints CountRange = {1, 1000, 1};

/// Gewählte Profilflächen (leer = alle) und die zugehörige Skizze. Leerer Vektor mit Fehlertext bei Problemen.
std::vector<Part::TopoShape> profileFaces(const App::PropertyLinkSub& profile, Part::Feature*& sketch, const char*& error)
{
    auto profiles = freecad_cast<Profiles*>(profile.getValue());
    sketch = profiles ? freecad_cast<Part::Feature*>(profiles->Sketch.getValue()) : nullptr;
    if (!sketch) {
        error = "Select a profile";
        return {};
    }
    const Part::TopoShape all = profiles->Shape.getShape();
    std::vector<Part::TopoShape> faces;
    for (const auto& sub : profile.getSubValues()) {
        faces.push_back(all.getSubTopoShape(sub.c_str(), true));
    }
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
    part->Label.setValue(doc->Label.getValue());
    for (const char* label : {"Bodies", "Sketches"}) {
        auto group = doc->addObject("App::DocumentObjectGroup", label);
        group->Label.setValue(label);
        part->addObject(group);
    }
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

    struct Region
    {
        TopoDS_Face face;
        gp_Pnt center;
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
            regions.push_back({TopoDS::Face(ex.Current()), props.CentreOfMass()});
        }
    }
    // Feste Reihenfolge (links nach rechts, unten nach oben), damit Face1… bei kleinen Änderungen gleich bleiben
    // ponytail: echte topologische Benennung der Profile fehlt noch; Upgrade über Element-Maps der Skizzenkanten
    std::ranges::sort(regions, [](const Region& a, const Region& b) {
        return a.center.X() != b.center.X() ? a.center.X() < b.center.X() : a.center.Y() < b.center.Y();
    });

    std::vector<Part::TopoShape> faces;
    for (auto& r : regions) {
        faces.emplace_back(r.face);
    }
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
    int i = 0;
    // ponytail: die Teil-Shapes verlieren hier ihre Element-Map (topologische Benennung); Upgrade: eigene Shape-Property je Body
    for (TopoDS_Iterator it(Shape.getShape().getShape()); it.More(); it.Next(), ++i) {
        if (i == idx) {
            return Part::TopoShape(it.Value());
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
    const auto faces = profileFaces(Profile, sketch, reason);
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
    const auto faces = profileFaces(Profile, sketch, reason);
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
    Operation.setStatus(App::Property::Hidden, true);  // verändert immer den eigenen Body
}

std::vector<Part::TopoShape> DressUp::elements(const Part::TopoShape& shape, TopAbs_ShapeEnum type) const
{
    std::vector<Part::TopoShape> result;
    TopTools_IndexedMapOfShape seen;
    for (const auto& name : Edges.getValues()) {
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
        const Base::BoundBox3d bb = base.getBoundBox();
        Base::Vector3d axis;
        axis[RotationAxis.getValue()] = 1;
        Base::Placement rot(Base::Vector3d(), Base::Rotation(axis, Angle.getValue() * M_PI / 180.0), bb.GetCenter());
        Base::Placement move(Translation.getValue(), Base::Rotation());
        Base::Matrix4D mat = (move * rot).toMatrix();
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

App::DocumentObjectExecReturn* Pattern::compute()
{
    auto source = freecad_cast<Feature*>(Source.getValue());
    if (!source) {
        return new App::DocumentObjectExecReturn("Select a feature to pattern");
    }
    Part::TopoShape tool;
    std::string error;
    if (!source->makeTool(tool, error)) {
        return new App::DocumentObjectExecReturn(error);
    }

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
    if (transforms.empty()) {
        return new App::DocumentObjectExecReturn("Count must be at least 2");
    }

    std::vector<Part::TopoShape> copies;
    for (const auto& m : transforms) {
        copies.push_back(Part::TopoShape(0, getDocument()->getStringHasher())
                             .makeElementTransform(tool, m, nullptr, Part::CheckScale::noScaleCheck,
                                                   Part::CopyType::copy));
    }
    return applyTool(fuseAll(copies, getDocument()->getStringHasher()));
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
    std::vector<Part::TopoShape> prisms;
    for (const auto& face : elements(shape, TopAbs_FACE)) {
        BRepAdaptor_Surface surf(TopoDS::Face(face.getShape()));
        if (surf.GetType() != GeomAbs_Plane) {
            return new App::DocumentObjectExecReturn("Press Pull supports planar faces");
        }
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
