// SPDX-License-Identifier: LGPL-2.1-or-later

#include "Features.h"

#include <App/Document.h>
#include <App/DocumentObjectGroup.h>
#include <App/Part.h>
#include <Base/Placement.h>
#include <Mod/Part/App/TopoShapeOpCode.h>

#include <BRepAlgoAPI_Splitter.hxx>
#include <BRepBndLib.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepGProp.hxx>
#include <BRep_Tool.hxx>
#include <Bnd_Box.hxx>
#include <GProp_GProps.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Iterator.hxx>
#include <gp_Pln.hxx>

#include <algorithm>

using namespace Design;

namespace
{
const char* OpEnums[] = {"New Body", "Join", "Cut", "Intersect", nullptr};
const char* ExtentEnums[] = {"One Side", "Symmetric", "Two Sides", nullptr};
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
        results.push_back(tool);
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
            results.push_back(res.makeElementRefine(nullptr, Part::RefineFail::shapeUntouched));
        }
    }

    Part::TopoShape compound(0, getDocument()->getStringHasher());
    compound.makeElementCompound(results);
    Shape.setValue(compound);
    return StdReturn;
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

App::DocumentObjectExecReturn* Extrude::execute()
{
    auto profiles = freecad_cast<Profiles*>(Profile.getValue());
    auto sketch = profiles ? freecad_cast<Part::Feature*>(profiles->Sketch.getValue()) : nullptr;
    if (!sketch) {
        return new App::DocumentObjectExecReturn("Select a profile to extrude");
    }

    const Part::TopoShape all = profiles->Shape.getShape();
    std::vector<Part::TopoShape> faces;
    for (const auto& sub : Profile.getSubValues()) {
        faces.push_back(all.getSubTopoShape(sub.c_str(), true));
    }
    if (faces.empty()) {
        faces = all.getSubTopoShapes(TopAbs_FACE);
    }
    std::erase_if(faces, [](const Part::TopoShape& f) { return f.isNull(); });
    if (faces.empty()) {
        return new App::DocumentObjectExecReturn("Sketch has no closed profile");
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
        return new App::DocumentObjectExecReturn("Distance must be greater than zero");
    }

    std::vector<Part::TopoShape> prisms;
    for (auto& face : faces) {
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
    Part::TopoShape tool = prisms.front();
    if (prisms.size() > 1) {
        tool = Part::TopoShape(0, getDocument()->getStringHasher()).makeElementFuse(prisms);
        tool = tool.makeElementRefine(nullptr, Part::RefineFail::shapeUntouched);
    }
    return applyTool(tool);
}
