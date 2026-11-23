// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <Mod/Design/DesignGlobal.h>
#include <Mod/Part/Gui/ViewProviderExt.h>
#include <Gui/ViewProviderDocumentObject.h>

#include "ScribbleRead.h"

#include <functional>
#include <memory>

#include <QObject>

namespace Design
{
class Body;
class Joint;
class Scribble;
struct Correction;
}
namespace Part
{
class TopoShape;
class Geometry;
}

class SoNodeSensor;
class SoPolygonOffset;
namespace Sketcher
{
class Constraint;
}
namespace Base
{
template<class T>
class Vector3;
using Vector3d = Vector3<double>;
}
namespace Gui
{
class View3DInventorViewer;
}

namespace DesignGui
{
/// Ruft moved bei jeder Kamerabewegung der Ansicht (Coin-Sensor auf der Kamera, auch nach einem Wechsel
/// Perspektive/Orthografisch) und wenn die Ansicht ihre Größe ändert: Glas-Karten an Modellpunkten folgen Bild für Bild
class CameraFollow: public QObject
{
public:
    explicit CameraFollow(std::function<void()> moved);
    ~CameraFollow() override;
    void start(Gui::View3DInventorViewer* viewer);
    void stop();

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    std::function<void()> moved;
    std::unique_ptr<SoNodeSensor> sensor;
    Gui::View3DInventorViewer* viewer = nullptr;
    QMetaObject::Connection swapped, gone;
};


/// Handschrift auf dem aktuellen Blatt eines Scribbles lesen (freie Fineliner- und Bleistift-Striche), mit
/// CAD-Schreibweise; die Strich-Nummern der Zeilen zählen in scribble->strokes(). Leer ohne Handschrift-Modell.
std::vector<ScribbleRead::Line> readScribble(const Design::Scribble* scribble);
/// Geometrie eines Strichs (Punkte in Skizzen-Koordinaten, kind wie Design::Scribble::Kind) und die Bedingungen, die
/// Strich-Geometrie zusammenhalten (waagerecht/senkrecht, Enden koinzident): Scribble -> Skizze, Stift in der Skizze
void strokeGeometry(int kind, const std::vector<Base::Vector3d>& pts, std::vector<std::unique_ptr<Part::Geometry>>& geos);
std::vector<std::unique_ptr<Sketcher::Constraint>> strokeConstraints(const std::vector<std::unique_ptr<Part::Geometry>>& geos);
/// Stift in einer offenen Skizze: Striche werden Skizzengeometrie (an beim Öffnen, aus beim Schließen)
void sketchPen(Gui::ViewProviderDocumentObject* sketch, bool on);

/// Parameter-Tabelle des Designs (App::VarSet "Parameters" in der Root-Komponente), wie Fusions "Change Parameters"
DesignGuiExport App::DocumentObject* parameters(App::Document* doc, bool create);
/// Phase 11.10: Bohrungen in die vier Ecken der gewählten Fläche (oder der Oberseite des Körpers), offset vom Rand;
/// size "M3" (ISO-Durchgangsloch) oder diameter in mm. Öffnet den Bohrungs-Dialog: dort Vorschau, OK übernimmt.
DesignGuiExport void cornerHoles(const std::string& size, double diameter, double offset);
/// 12.9 "Warum ist das rot?": was an der Auswahl (sonst im Design) nicht rechnet oder warnt, als Hinweis; markiert es
DesignGuiExport void explainProblems();
/// 12.9 Grundkörper per Satz: type 0 Quader (a, b, c = Länge, Breite, Höhe), 1 Zylinder (a = Durchmesser, b = Höhe);
/// öffnet das Werkzeug mit diesen Maßen (Vorschau, OK übernimmt)
DesignGuiExport void primitive(long type, double a, double b, double c);
/// 12.9 Verschieben per Satz: gewählte (sonst den einzigen sichtbaren) Körper um x, y, z; Panel offen, OK übernimmt
DesignGuiExport void moveBy(double x, double y, double z);
/// 12.9 "Was hängt daran?": was die Auswahl benutzt, als Hinweis; wählt es aus
DesignGuiExport void showDependents();
/// Bohrmuster (11.10): circle = Lochkreis mit pitch Durchmesser um die Mitte der Fläche, sonst Reihe durch die Mitte mit
/// pitch Abstand (0: gleichmäßig verteilt); count Bohrungen, size "M4" oder diameter
DesignGuiExport void patternHoles(bool circle, int count, const std::string& size, double diameter, double pitch);
/// Phase 11.10: Rundung ("Fillet") oder Fase ("Chamfer") mit size an den gewählten Kanten, mit all an allen Kanten
DesignGuiExport void dressUp(const std::string& kind, double size, bool all);
/// Phase 11.9: Umrisse eines Teils auf hellem Papier aus dem Foto file als Skizze, widthMm breit (Breite im Bild); auf
/// Rasterpapier statt dessen squareMm = Kantenlänge eines Kästchens
DesignGuiExport App::DocumentObject* photoToSketch(const std::string& file, double widthMm, double squareMm = 0);
/// Zeigt das Foto ein ganzes Blatt (A4) auf dunklerem Grund? Dann photoToSketch(file, 0, 0): entzerrt, ohne Frage
DesignGuiExport bool photoSheet(const std::string& file);
/// Kästchengröße in Pixeln, wenn das Foto Rasterpapier zeigt, sonst 0
DesignGuiExport double photoGrid(const std::string& file);
/// Idee 2: Karte mit den Maßen einer doppelt angeklickten Körperfläche (einmal beim Laden des Moduls)
DesignGuiExport void startFaceDimensions();
/// Parameternamen in einem Ausdruck auf die Tabelle beziehen: "Width * 2" -> "Parameters.Width * 2"
DesignGuiExport std::string parameterExpression(App::Document* doc, const std::string& text);
/// Rückweg für die Anzeige: "Parameters.Width * 2" -> "Width * 2"
DesignGuiExport std::string displayExpression(App::Document* doc, const std::string& text);
/// Idee 5: Druckansicht an allen Körpern an- oder ausschalten (Überhang, Bett, dünne Wand; Legende in der Ansicht)
DesignGuiExport void setPrintView(bool on);
DesignGuiExport bool printView();
/// Druckansicht neu rechnen (nach geänderter Druckrichtung oder Grenze)
DesignGuiExport void refreshPrintView();
/// Idee 1: Karten der gelesenen Rotstift-Korrekturen in der Ansicht (Ausführen, Verwerfen, Alle ausführen; bei
/// gleich nahen Zielen eine Auswahl, Zeigen hebt das Ziel hervor). Leere Liste schließt sie.
DesignGuiExport void showCorrections(App::Document* doc, const std::vector<Design::Correction>& corrections);
/// Idee 7: Vergleich mit einer Version oder Variante als Geisterbild in der Ansicht: hinzugekommen grün gepunktet,
/// entfernt rot schraffiert, dazu Legende und die geänderten Schritte. Leere Formen schließen ihn.
DesignGuiExport void showComparison(const QString& title, const Part::TopoShape& added, const Part::TopoShape& removed,
                                    const QStringList& steps);

class DesignGuiExport ViewProviderBody: public PartGui::ViewProviderPartExt
{
    PROPERTY_HEADER_WITH_OVERRIDE(DesignGui::ViewProviderBody);

public:
    ViewProviderBody();
    QIcon getIcon() const override;
    void attach(App::DocumentObject* obj) override;
    void updateData(const App::Property* prop) override;
    void onChanged(const App::Property* prop) override;
    /// Druckansicht dieses Körpers neu aufbauen bzw. ausblenden
    void refreshPrintOverlay();

private:
    void updateTransparentOffset();
    class SoSwitch* printSwitch = nullptr;
    SoPolygonOffset* transparentOffset = nullptr;  ///< durchsichtig: Flächen weiter nach hinten (attach)
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
    /// Nie sichtbar: das Ergebnis zeigt der Body. Sonst blendet der Sketcher beim Bearbeiten die Fläche, auf der die
    /// Skizze liegt, als zweiten, deckungsgleichen Körper ein (ShowSupport/ShowLinks): ohne Material, Auge am Body wirkungslos
    void show() override
    {
        Visibility.setValue(false);
    }
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
    /// wie die Tasten E und V: noch einmal dasselbe Werkzeug geht zurück zum letzten Stift
    static void toggleTool(Tool tool);
    static void setColor(const Base::Color& color);
    static const Base::Color& color();
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
