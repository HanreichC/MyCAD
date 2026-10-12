// SPDX-License-Identifier: LGPL-2.1-or-later

#include <App/Application.h>
#include <App/Document.h>
#include <Base/Console.h>
#include <Base/Interpreter.h>
#include <CXX/Extensions.hxx>
#include <Gui/Application.h>
#include <Gui/Document.h>
#include <Gui/ViewProviderDocumentObject.h>
#include <Mod/Design/App/Features.h>
#include <Mod/Sketcher/App/SketchObject.h>

#include "ViewProviders.h"

#include <QTimer>

void CreateDesignCommands();

namespace DesignGui
{
class Module: public Py::ExtensionModule<Module>
{
public:
    Module()
        : Py::ExtensionModule<Module>("DesignGui")
    {
        initialize("MyCAD Design GUI");
    }
};

void setProfilesVisible(const Gui::ViewProviderDocumentObject& vp, bool visible)
{
    if (auto profiles = Design::Profiles::forSketch(vp.getObject())) {
        if (!visible || vp.getObject()->Visibility.getValue()) {
            profiles->Visibility.setValue(visible);
        }
    }
}
}  // namespace DesignGui

PyMOD_INIT_FUNC(DesignGui)
{
    if (!Gui::Application::Instance) {
        PyErr_SetString(PyExc_ImportError, "Cannot load Gui module in console application.");
        PyMOD_Return(nullptr);
    }
    try {
        Base::Interpreter().loadModule("Design");
    }
    catch (const Base::Exception& e) {
        PyErr_SetString(PyExc_ImportError, e.what());
        PyMOD_Return(nullptr);
    }
    PyObject* mod = Base::Interpreter().addModule(new DesignGui::Module);

    CreateDesignCommands();
    DesignGui::ViewProviderBody::init();
    DesignGui::ViewProviderProfiles::init();
    DesignGui::ViewProviderFeature::init();
    DesignGui::ViewProviderJoint::init();

    // Jedes neue Design bekommt sofort seine Root-Komponente (Origin, Bodies, Sketches)
    App::GetApplication().signalNewDocument.connect([](const App::Document& doc, bool) {
        const std::string name = doc.getName();
        QTimer::singleShot(0, [name] {
            App::Document* d = App::GetApplication().getDocument(name.c_str());
            if (!d || d->countObjects() > 0) {
                return;  // geöffnete Datei oder schon befüllt
            }
            Design::root(d, true);
            d->recompute();
            if (auto gd = Gui::Application::Instance->getDocument(d)) {
                gd->setModified(false);
            }
        });
    });
    // Profilflächen nicht über die Skizze legen, solange sie bearbeitet wird
    Gui::Application::Instance->signalInEdit.connect([](const Gui::ViewProviderDocumentObject& vp) {
        DesignGui::setProfilesVisible(vp, false);
    });
    Gui::Application::Instance->signalResetEdit.connect([](const Gui::ViewProviderDocumentObject& vp) {
        DesignGui::setProfilesVisible(vp, true);
    });
    // Profile sind sichtbar, solange ihre Skizze sichtbar ist (Auge im Browser, nach Extrude ausgeblendet, …)
    App::GetApplication().signalChangedObject.connect([](const App::DocumentObject& obj, const App::Property& prop) {
        if (&prop != &obj.Visibility || !obj.isDerivedFrom<Sketcher::SketchObject>()) {
            return;
        }
        auto gdoc = Gui::Application::Instance->getDocument(obj.getDocument());
        auto edit = gdoc ? dynamic_cast<Gui::ViewProviderDocumentObject*>(gdoc->getInEdit()) : nullptr;
        if (edit && edit->getObject() == &obj) {
            return;  // beim Bearbeiten bleiben die Profile aus
        }
        auto profiles = Design::Profiles::forSketch(const_cast<App::DocumentObject*>(&obj));
        if (profiles && profiles->Visibility.getValue() != obj.Visibility.getValue()) {
            profiles->Visibility.setValue(obj.Visibility.getValue());
        }
    });

    PyMOD_Return(mod);
}
