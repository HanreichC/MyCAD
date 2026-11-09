// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <Mod/Design/DesignGlobal.h>
#include <Mod/Part/Gui/ViewProviderExt.h>
#include <Gui/ViewProviderDocumentObject.h>

#include "ScribbleRead.h"

#include <memory>

namespace Design
{
class Body;
class Joint;
class Scribble;
}

namespace DesignGui
{

/// Handschrift auf dem aktuellen Blatt eines Scribbles lesen (freie Fineliner- und Bleistift-Striche), mit
/// CAD-Schreibweise; die Strich-Nummern der Zeilen zählen in scribble->strokes(). Leer ohne Handschrift-Modell.
std::vector<ScribbleRead::Line> readScribble(const Design::Scribble* scribble);

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
    ViewProviderBody();
    QIcon getIcon() const override;
};

/// Geschlossene Skizzen-Regionen: hellblau, halbtransparent, anklickbar, nicht im Browser.
class DesignGuiExport ViewProviderProfiles: public PartGui::ViewProviderPartExt
{
    PROPERTY_HEADER_WITH_OVERRIDE(DesignGui::ViewProviderProfiles);

public:
    ViewProviderProfiles();
    void attach(App::DocumentObject* obj) override;
    void finishRestoring() override;
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

/// Joint im Browser (Ordner "Joints"): Doppelklick öffnet den Joint-Dialog
class DesignGuiExport ViewProviderJoint: public Gui::ViewProviderDocumentObject
{
    PROPERTY_HEADER_WITH_OVERRIDE(DesignGui::ViewProviderJoint);

public:
    QIcon getIcon() const override;
    bool doubleClicked() override;
    bool setEdit(int ModNum) override;
    void unsetEdit(int ModNum) override;
    bool createMode = false;
};

/// Post-it im Browser (Ordner "Notes"): Doppelklick öffnet es wieder
class DesignGuiExport ViewProviderNote: public Gui::ViewProviderDocumentObject
{
    PROPERTY_HEADER_WITH_OVERRIDE(DesignGui::ViewProviderNote);

public:
    QIcon getIcon() const override;
    bool doubleClicked() override;
    /// Ohne 3D-Darstellung gälte es sonst immer als ausgeblendet (Auge im Browser)
    bool isShow() const override
    {
        return Visibility.getValue();
    }
};

/// Scribble im Browser (Ordner "Scribbles"): Striche im Modell; Doppelklick öffnet das Zeichenblatt (Scribble.cpp)
class DesignGuiExport ViewProviderScribble: public Gui::ViewProviderDocumentObject
{
    PROPERTY_HEADER_WITH_OVERRIDE(DesignGui::ViewProviderScribble);

public:
    enum class Tool
    {
        Pencil,
        Pen,
        Marker,
        Eraser,
        Sheet,  ///< Blatt umstellen: Tippen auf Fläche, geraden Strich oder ins Leere
        Line,   ///< Formen: ziehen von Punkt zu Punkt (Linie, Pfeil), über die Diagonale (Rechteck, Dreieck, Ellipse)
        Rectangle,  ///< oder von der Mitte aus (Kreis, Sechseck)
        Circle,
        Arrow,
        Triangle,
        Hexagon,
        Ellipse,
        Fill,   ///< in eine geschlossene Form tippen oder eine Fläche umranden: färbt sie ein
        Select,  ///< auf Striche tippen oder sie umranden, dann ziehen; Entf löscht, eine Farbe färbt um
        Text     ///< aufs Blatt klicken und tippen; der Text wird zu gefüllten Buchstaben (je Zeile ein Strich)
    };

    ViewProviderScribble();
    ~ViewProviderScribble() override;
    void attach(App::DocumentObject* obj) override;
    void updateData(const App::Property* prop) override;
    std::vector<std::string> getDisplayModes() const override;
    const char* getDefaultDisplayMode() const override;
    void setDisplayMode(const char* mode) override;
    QIcon getIcon() const override;
    bool doubleClicked() override;
    bool setEdit(int ModNum) override;
    void unsetEdit(int ModNum) override;
    void setEditViewer(Gui::View3DInventorViewer* viewer, int ModNum) override;
    void unsetEditViewer(Gui::View3DInventorViewer* viewer) override;
    bool keyPressed(bool pressed, int key) override;

    /// Scribble, auf dem gerade gezeichnet wird, sonst nullptr
    static ViewProviderScribble* editing();
    static Tool tool();
    static void setTool(Tool tool);
    static void setColor(const Base::Color& color);
    /// Tinte "Schwarz" (im Dunkelmodus ohne Blatt hell dargestellt)
    static const Base::Color& ink();
    /// Kamera gerade aufs Blatt (nur im Zeichenmodus)
    void lookAtSheet();
    /// ausgewählte Striche löschen (Leiste an der Auswahl, Entf)
    void deleteSelection();
    /// Handschrift-Suche (Feld in der Scribble-Palette): wählt die nächste Zeile auf dem Blatt, die den Text enthält,
    /// und zeigt sie in der Mitte; false, wenn nichts passt
    static bool find(const QString& text);

    struct Private;

private:
    std::unique_ptr<Private> d;
};

}  // namespace DesignGui
