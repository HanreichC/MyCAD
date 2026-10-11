// SPDX-License-Identifier: LGPL-2.1-or-later

#include <Base/Console.h>
#include <Base/Interpreter.h>
#include <Base/PyObjectBase.h>
#include <CXX/Extensions.hxx>

#include "Features.h"

namespace Design
{
class Module: public Py::ExtensionModule<Module>
{
public:
    Module()
        : Py::ExtensionModule<Module>("Design")
    {
        initialize("MyCAD Design: components, bodies and timeline features");
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

    PyMOD_Return(mod);
}
