// SPDX-License-Identifier: LGPL-2.1-or-later

#include <App/Application.h>
#include <App/Document.h>
#include <App/DocumentObserver.h>
#include <Base/Console.h>
#include <Base/Interpreter.h>
#include <CXX/Extensions.hxx>
#include <Gui/Application.h>
#include <Gui/Shell/Shell.h>
#include <App/VarSet.h>
#include <App/DocumentPy.h>
#include <Base/VectorPy.h>
#include <Gui/Document.h>
#include <Gui/ViewProviderDocumentObject.h>
#include <Mod/Design/App/Features.h>
#include <Mod/Sketcher/App/SketchObject.h>
#include <Mod/Sketcher/Gui/EditDatumDialog.h>

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
        add_varargs_method("showCorrections", &Module::showCorrections,
                           "showCorrections(doc, [(text, at, view), ...]): red pen cards as if read from ink");
        initialize("MyCAD Design GUI");
    }

private:
    Py::Object showCorrections(const Py::Tuple& args)
    {
        if (!PyObject_TypeCheck(args[0].ptr(), &App::DocumentPy::Type)) {
            throw Py::TypeError("expected a document");
        }
        App::Document* doc = static_cast<App::DocumentPy*>(args[0].ptr())->getDocumentPtr();
        const auto vec = [](const Py::Object& o) { return *static_cast<Base::VectorPy*>(o.ptr())->getVectorPtr(); };
        std::vector<Design::Correction> list;
        for (const auto& item : Py::List(args[1])) {
            const Py::Tuple t(item);
            list.push_back(Design::readCorrection(doc, Py::String(t[0]).as_std_string(), vec(t[1]), vec(t[2])));
        }
        DesignGui::showCorrections(doc, list);
        return Py::None();
    }
};

void applyBackgroundProfiles(const App::DocumentObjectT& target, int ticks);

void setProfilesVisible(const Gui::ViewProviderDocumentObject& vp, bool visible)
{
    if (auto profiles = Design::Profiles::forSketch(vp.getObject())) {
        if (!visible || vp.getObject()->Visibility.getValue()) {
            profiles->Visibility.setValue(visible);
        }
        // ausgeblendet heißt: Skizze in Bearbeitung, Profile erst danach neu berechnen
        if (!visible || !profiles->skipped) {
            profiles->paused = !visible;
            return;
        }
        // Skizze nach Änderungen verlassen: noch pausiert, damit das Neuberechnen von "Fertig" (gleich nach diesem
        // Signal) nicht auf die Profile wartet; danach rechnen sie im Hintergrund (große DXF-Skizzen: Sekunden)
        const App::DocumentObjectT target(profiles);
        QTimer::singleShot(0, [target] {
            auto p = freecad_cast<Design::Profiles*>(target.getObject());
            if (!p) {
                return;
            }
            if (App::DocumentObject* sketch = p->Sketch.getValue(); sketch && sketch->isTouched()) {
                p->getDocument()->recompute();  // Abbrechen rechnet nicht selbst neu
            }
            p->skipped = false;
            p->paused = false;
            p->computeInBackground();
            p->touch();
            applyBackgroundProfiles(target, 0);
        });
    }
}

/// Fertig im Hintergrund gerechnete Profile übernehmen (das Neuberechnen nimmt das Ergebnis sofort). Nicht in einer
/// offenen Transaktion: ein abgebrochenes Werkzeug nähme sonst die neuen Profile mit zurück
void applyBackgroundProfiles(const App::DocumentObjectT& target, int ticks)
{
    auto p = freecad_cast<Design::Profiles*>(target.getObject());
    if (!p) {
        return;  // Design geschlossen
    }
    if (p->computingInBackground() || p->getDocument()->hasPendingTransaction()) {
        if (ticks == 10 && p->computingInBackground()) {  // nach 1 s: sagen, worauf man wartet
            Base::Console().send<Base::LogStyle::Notification, Base::IntendedRecipient::User, Base::ContentType::Translated>(
                "MyCAD", "{}", Gui::Shell::T("Sketch: finding its closed areas …").toStdString());
        }
        QTimer::singleShot(100, [target, ticks] { applyBackgroundProfiles(target, ticks + 1); });
        return;
    }
    if (p->isTouched()) {
        p->getDocument()->recompute();
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
    DesignGui::ViewProviderNote::init();
    DesignGui::ViewProviderScribble::init();
#ifdef MYCAD_HTR
    // Handschrift suchen: Feld in der Scribble-Palette (das Modell lädt erst bei der ersten Suche)
    Gui::Shell::setScribbleFind([](const QString& text) { return DesignGui::ViewProviderScribble::find(text); });
#endif

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
    // Deutsche Oberfläche: neue Objekte heißen deutsch (Skizze1, Extrusion001, Ordner Skizzen …). Erst danach setzen,
    // weil die Befehle die Beschriftung nach dem Anlegen noch selbst setzen; geöffnete Dateien bleiben unverändert.
    App::GetApplication().signalNewObject.connect([](const App::DocumentObject& obj) {
        if (obj.getDocument()->testStatus(App::Document::Restoring) || obj.isDerivedFrom<App::VarSet>()) {
            return;  // "Parameters" wird über die Beschriftung gefunden
        }
        const std::string doc = obj.getDocument()->getName(), name = obj.getNameInDocument();
        QTimer::singleShot(0, [doc, name] {
            App::Document* d = App::GetApplication().getDocument(doc.c_str());
            App::DocumentObject* o = d ? d->getObject(name.c_str()) : nullptr;
            if (!o) {
                return;
            }
            const std::string label = o->Label.getValue();
            const size_t digits = label.find_last_not_of("0123456789") + 1;
            const std::string key = "label:" + label.substr(0, digits);
            const QString german = Gui::Shell::T(key.c_str());
            if (german != QString::fromStdString(key)) {
                o->Label.setValue(german.toStdString() + label.substr(digits));
            }
        });
    });
    DesignGui::startFaceDimensions();
    SketcherGui::datumExpression = DesignGui::parameterExpression;  // Skizzenmaße nehmen Parameternamen
    // Profilflächen nicht über die Skizze legen, solange sie bearbeitet wird
    Gui::Application::Instance->signalInEdit.connect([](const Gui::ViewProviderDocumentObject& vp) {
        DesignGui::setProfilesVisible(vp, false);
    });
    Gui::Application::Instance->signalResetEdit.connect([](const Gui::ViewProviderDocumentObject& vp) {
        DesignGui::setProfilesVisible(vp, true);
    });
    // Während der Bearbeitung übersprungene Profile als offen speichern: das übersprungene Neuberechnen gilt als
    // erledigt, ohne das stünden nach einem Absturz in der Skizze Profile in der Datei, die nicht zu ihr passen
    App::GetApplication().signalStartSaveDocument.connect([](const App::Document& doc, const std::string&) {
        for (auto obj : doc.getObjectsOfType(Design::Profiles::getClassTypeId())) {
            if (auto profiles = static_cast<Design::Profiles*>(obj); profiles->paused && profiles->skipped) {
                profiles->touch();
            }
        }
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
