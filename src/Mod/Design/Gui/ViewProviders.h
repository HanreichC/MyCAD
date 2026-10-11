// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <Mod/Design/DesignGlobal.h>
#include <Mod/Part/Gui/ViewProviderExt.h>

namespace Design
{
class Body;
}

namespace DesignGui
{

/// Parameter-Tabelle des Designs (App::VarSet "Parameters" in der Root-Komponente), wie Fusions "Change Parameters"
DesignGuiExport App::DocumentObject* parameters(App::Document* doc, bool create);
/// Parameternamen in einem Ausdruck auf die Tabelle beziehen: "Width * 2" -> "Parameters.Width * 2"
DesignGuiExport std::string parameterExpression(App::Document* doc, const std::string& text);
/// Rückweg für die Anzeige: "Parameters.Width * 2" -> "Width * 2"
DesignGuiExport std::string displayExpression(App::Document* doc, const std::string& text);

class DesignGuiExport ViewProviderBody: public PartGui::ViewProviderPartExt
{
    PROPERTY_HEADER_WITH_OVERRIDE(DesignGui::ViewProviderBody);

public:
    QIcon getIcon() const override;
};

/// Geschlossene Skizzen-Regionen: hellblau, halbtransparent, anklickbar, nicht im Browser.
class DesignGuiExport ViewProviderProfiles: public PartGui::ViewProviderPartExt
{
    PROPERTY_HEADER_WITH_OVERRIDE(DesignGui::ViewProviderProfiles);

public:
    ViewProviderProfiles();
    void attach(App::DocumentObject* obj) override;
};

/// Timeline-Feature: im 3D unsichtbar (das Ergebnis zeigt der Body), nicht im Browser, Doppelklick bearbeitet.
class DesignGuiExport ViewProviderFeature: public PartGui::ViewProviderPartExt
{
    PROPERTY_HEADER_WITH_OVERRIDE(DesignGui::ViewProviderFeature);

public:
    ViewProviderFeature();
    void attach(App::DocumentObject* obj) override;
    QIcon getIcon() const override;
    bool doubleClicked() override;
    bool setEdit(int ModNum) override;
    void unsetEdit(int ModNum) override;

    /// vom Befehl gesetzt: der Dialog wählt dann Operation und Ziel-Body selbst (Extrude, Revolve)
    bool createMode = false;
    Design::Body* defaultTarget = nullptr;
};

}  // namespace DesignGui
