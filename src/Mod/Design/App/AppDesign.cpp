// SPDX-License-Identifier: LGPL-2.1-or-later

#include <App/Document.h>
#include <App/DocumentObjectPy.h>
#include <App/DocumentPy.h>
#include <App/Part.h>
#include <Base/Console.h>
#include <Base/Interpreter.h>
#include <Base/PyObjectBase.h>
#include <CXX/Extensions.hxx>

#include "Features.h"

namespace Design
{
/// Die Timeline-Verdrahtung, die sonst nur die Werkzeuge der Oberfläche machen, für Skripte und Headless-Tests
class Module: public Py::ExtensionModule<Module>
{
public:
    Module()
        : Py::ExtensionModule<Module>("Design")
    {
        add_varargs_method("root", &Module::root, "root(doc): root component, created if missing");
        add_varargs_method("newComponent", &Module::newComponent, "newComponent(parent): empty component in parent");
        add_varargs_method("newSketch", &Module::newSketch, "newSketch(component): sketch with profiles, in the timeline");
        add_varargs_method("newBody", &Module::newBody, "newBody(feature[, component]): body created by feature");
        add_varargs_method("addToTimeline", &Module::addToTimeline, "addToTimeline(obj): insert at the rollback marker");
        add_varargs_method("removeFromTimeline", &Module::removeFromTimeline, "removeFromTimeline(obj): delete and rewire");
        add_varargs_method("timeline", &Module::timeline, "timeline(doc): sketches and features in order");
        add_varargs_method("attachToBodies", &Module::attachToBodies, "attachToBodies(feature, [bodies]): feature changes bodies");
        add_varargs_method("rollbackMarker", &Module::rollbackMarker, "rollbackMarker(doc): active entries, -1 = all");
        add_varargs_method("setRollbackMarker", &Module::setRollbackMarker, "setRollbackMarker(doc, n): roll back");
        add_varargs_method("componentOf", &Module::componentOf, "componentOf(obj): component containing obj");
        add_varargs_method("moveInTimeline", &Module::moveInTimeline,
                           "moveInTimeline(obj, index): move; raises ValueError naming the dependency when not allowed");
        add_varargs_method("setTimelineGroup", &Module::setTimelineGroup,
                           "setTimelineGroup([objs], name): group consecutive entries ('' ungroups); False if not consecutive");
        add_varargs_method("timelineGroup", &Module::timelineGroup, "timelineGroup(obj): name of its group or ''");
        add_varargs_method("mass", &Module::mass, "mass(body): mass in kg from volume and the density of ShapeMaterial");
        add_varargs_method("physicalMaterialFor", &Module::physicalMaterialFor,
                           "physicalMaterialFor(appearance, group): UUID of the matching material card or ''");
        add_varargs_method("setPhysicalMaterial", &Module::setPhysicalMaterial,
                           "setPhysicalMaterial(body, uuid[, chosen=True]): set ShapeMaterial; False if unknown");
        add_varargs_method("physicalMaterials", &Module::physicalMaterials, "physicalMaterials(): [(name, uuid)]");
        add_varargs_method("stableRef", &Module::stableRef,
                           "stableRef(obj, element): (obj, element) with a body replaced by its timeline state");
        initialize("MyCAD Design: components, bodies and timeline features");
    }

private:
    static App::Document* doc(const Py::Tuple& args, size_t i = 0)
    {
        if (args.size() <= i || !PyObject_TypeCheck(args[i].ptr(), &App::DocumentPy::Type)) {
            throw Py::TypeError("expected a document");
        }
        return static_cast<App::DocumentPy*>(args[i].ptr())->getDocumentPtr();
    }
    template<class T = App::DocumentObject>
    static T* obj(const Py::Object& o)
    {
        T* result = nullptr;
        if (PyObject_TypeCheck(o.ptr(), &App::DocumentObjectPy::Type)) {
            result = freecad_cast<T*>(static_cast<App::DocumentObjectPy*>(o.ptr())->getDocumentObjectPtr());
        }
        if (!result) {
            throw Py::TypeError("expected a " + std::string(T::getClassTypeId().getName()));
        }
        return result;
    }
    static Py::Object py(App::DocumentObject* o)
    {
        return o ? Py::asObject(o->getPyObject()) : Py::None();
    }

    Py::Object root(const Py::Tuple& args)
    {
        return py(Design::root(doc(args), true));
    }
    Py::Object newComponent(const Py::Tuple& args)
    {
        return py(Design::newComponent(obj<App::Part>(args[0])));
    }
    Py::Object newSketch(const Py::Tuple& args)
    {
        return py(Design::newSketch(obj<App::Part>(args[0])));
    }
    Py::Object newBody(const Py::Tuple& args)
    {
        App::Part* component = args.size() > 1 && !args[1].isNone() ? obj<App::Part>(args[1]) : nullptr;
        return py(Design::newBody(obj<Feature>(args[0]), component));
    }
    Py::Object addToTimeline(const Py::Tuple& args)
    {
        Design::addToTimeline(obj(args[0]));
        return Py::None();
    }
    Py::Object removeFromTimeline(const Py::Tuple& args)
    {
        Design::removeFromTimeline(obj(args[0]));
        return Py::None();
    }
    Py::Object timeline(const Py::Tuple& args)
    {
        Py::List list;
        for (auto o : Design::timeline(doc(args))) {
            list.append(py(o));
        }
        return list;
    }
    Py::Object attachToBodies(const Py::Tuple& args)
    {
        std::vector<Body*> bodies;
        for (const auto& item : Py::Sequence(args[1])) {
            bodies.push_back(obj<Body>(item));
        }
        Design::attachToBodies(obj<Feature>(args[0]), bodies);
        return Py::None();
    }
    Py::Object rollbackMarker(const Py::Tuple& args)
    {
        return Py::Long(Design::rollbackMarker(doc(args)));
    }
    Py::Object setRollbackMarker(const Py::Tuple& args)
    {
        Design::setRollbackMarker(doc(args), static_cast<int>(Py::Long(args[1])));
        return Py::None();
    }
    Py::Object componentOf(const Py::Tuple& args)
    {
        return py(Design::componentOf(obj(args[0])));
    }
    Py::Object moveInTimeline(const Py::Tuple& args)
    {
        std::string error;
        if (!Design::moveInTimeline(obj(args[0]), static_cast<int>(Py::Long(args[1])), error)) {
            throw Py::ValueError(error);
        }
        return Py::None();
    }
    Py::Object setTimelineGroup(const Py::Tuple& args)
    {
        std::vector<App::DocumentObject*> objs;
        for (const auto& item : Py::Sequence(args[0])) {
            objs.push_back(obj(item));
        }
        return Py::Boolean(Design::setTimelineGroup(objs, Py::String(args[1]).as_std_string()));
    }
    Py::Object timelineGroup(const Py::Tuple& args)
    {
        return Py::String(Design::timelineGroup(obj(args[0])));
    }
    Py::Object mass(const Py::Tuple& args)
    {
        return Py::Float(Design::mass(obj<Part::Feature>(args[0])));
    }
    Py::Object physicalMaterialFor(const Py::Tuple& args)
    {
        return Py::String(Design::physicalMaterialFor(Py::String(args[0]).as_std_string(),
                                                      Py::String(args[1]).as_std_string()));
    }
    Py::Object setPhysicalMaterial(const Py::Tuple& args)
    {
        const bool chosen = args.size() < 3 || bool(Py::Boolean(args[2]));
        return Py::Boolean(
            Design::setPhysicalMaterial(obj<Part::Feature>(args[0]), Py::String(args[1]).as_std_string(), chosen));
    }
    Py::Object physicalMaterials(const Py::Tuple&)
    {
        Py::List list;
        for (const auto& m : Design::physicalMaterials()) {
            list.append(Py::TupleN(Py::String(m.name), Py::String(m.uuid)));
        }
        return list;
    }
    Py::Object stableRef(const Py::Tuple& args)
    {
        App::DocumentObject* o = obj(args[0]);
        std::string element = Py::String(args[1]).as_std_string();
        Design::stableRef(o, element);
        return Py::TupleN(py(o), Py::String(element));
    }
};
}  // namespace Design

PyMOD_INIT_FUNC(Design)
{
    try {
        Base::Interpreter().runString("import Part");
        Base::Interpreter().runString("import Sketcher");
    }
    catch (const Base::Exception& e) {
        PyErr_SetString(PyExc_ImportError, e.what());
        PyMOD_Return(nullptr);
    }
    PyObject* mod = Base::Interpreter().addModule(new Design::Module);

    Design::Body::init();
    Design::Profiles::init();
    Design::Feature::init();
    Design::Extrude::init();
    Design::Revolve::init();
    Design::DressUp::init();
    Design::Fillet::init();
    Design::Chamfer::init();
    Design::Shell::init();
    Design::Combine::init();
    Design::Move::init();
    Design::Mirror::init();
    Design::Pattern::init();
    Design::Hole::init();
    Design::PressPull::init();
    Design::Import::init();
    Design::Sweep::init();
    Design::Loft::init();
    Design::Primitive::init();
    Design::Draft::init();
    Design::Scale::init();
    Design::Split::init();
    Design::Thread::init();
    Design::Rib::init();
    Design::ReplaceFace::init();
    Design::SplitFace::init();
    Design::Emboss::init();
    Design::Joint::init();
    Design::Note::init();
    Design::Scribble::init();

    PyMOD_Return(mod);
}
