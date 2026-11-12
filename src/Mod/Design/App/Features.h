// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <App/PropertyLinks.h>
#include <App/PropertyStandard.h>
#include <App/PropertyUnits.h>
#include <Mod/Design/DesignGlobal.h>
#include <Mod/Part/App/PartFeature.h>

#include <functional>

#include "RedPen.h"

namespace App
{
class Document;
class DocumentObjectGroup;
class Part;
}  // namespace App

/// Fusion-artiges Datenmodell:
/// - Ein Design hat eine Root-Komponente (App::Part, Type "Design") mit Ordnern "Bodies" und "Sketches".
/// - Features (Extrude, …) erzeugen oder verändern Bodies. Ein Body merkt sich nur sein letztes Feature (Tip).
/// - Jede Skizze hat einen unsichtbaren Profiles-Begleiter mit allen geschlossenen Flächen der Skizze.
namespace Design
{

DesignExport App::Part* root(App::Document* doc, bool create);
DesignExport App::DocumentObjectGroup* folder(App::Part* root, const char* label);
/// Root-Komponente (Type "Design") oder Unterkomponente (Type "Component")
DesignExport bool isComponent(const App::DocumentObject* obj);
/// Komponente, in der ein Objekt liegt (auch für Ursprungsebenen); sonst die Root-Komponente
DesignExport App::Part* componentOf(const App::DocumentObject* obj);
/// neue leere Komponente mit Origin, Bodies und Sketches in parent
DesignExport App::Part* newComponent(App::Part* parent);
class Body;
class Feature;

/// @name Timeline (Reihenfolge und Rollback-Marker liegen an der Root-Komponente)
///@{
DesignExport std::vector<App::DocumentObject*> timeline(App::Document* doc);
/// neuen Eintrag an der Marker-Position einfügen (ohne Marker: anhängen)
DesignExport void addToTimeline(App::DocumentObject* obj);
DesignExport int rollbackMarker(App::Document* doc);  ///< Anzahl aktiver Einträge, -1 = alle
DesignExport void setRollbackMarker(App::Document* doc, int active);
DesignExport bool isRolledBack(const App::DocumentObject* obj);
/// Zustand eines Bodies am Marker (letztes nicht zurückgerolltes Feature)
DesignExport App::DocumentObject* stateAtMarker(Body* body);
/// Feature verändert die Bodies: Basis = Zustand am Marker, spätere Features bauen auf ihm auf
DesignExport void attachToBodies(Feature* feature, const std::vector<Body*>& bodies);
/// Gegenstück; liefert Bodies, die nur dieses Feature erzeugt hat
DesignExport std::vector<std::string> detachFromBodies(Feature* feature);
/// Skizze oder Feature aus der Timeline löschen und die Kette dahinter neu verbinden
DesignExport void removeFromTimeline(App::DocumentObject* obj);
/// Eintrag an Position to schieben. Geht nicht, wenn er dann vor etwas stünde, das er braucht (Skizze, Bezug), oder
/// hinter etwas, das ihn braucht; error nennt es. Features auf demselben Body werden dabei neu verkettet.
DesignExport bool moveInTimeline(App::DocumentObject* obj, int to, std::string& error);
/// Aufeinanderfolgende Einträge zu einer Gruppe (name leer = Gruppe auflösen); false, wenn sie nicht aneinander liegen
DesignExport bool setTimelineGroup(const std::vector<App::DocumentObject*>& objs, const std::string& name);
DesignExport std::string timelineGroup(const App::DocumentObject* obj);
/// New Body: neuer Body im Ordner "Bodies" von component (ohne: Komponente des Features), Ergebnis von feature
DesignExport Body* newBody(Feature* feature, App::Part* component = nullptr);
/// Neue, nicht angehängte Skizze mit Profiles-Begleiter in component, am Ende der Timeline (ohne Transaktion)
DesignExport App::DocumentObject* newSketch(App::Part* component);
///@}

/// @name Physisches Material (Part::Feature::ShapeMaterial, Karten aus Mod/Material)
///@{
struct PhysicalMaterial
{
    const char* name;  ///< englisch, für die Auswahl
    const char* uuid;  ///< Werkstoffkarte in Mod/Material/Resources/Materials/Standard
};
DesignExport const std::vector<PhysicalMaterial>& physicalMaterials();
/// Werkstoff, der zu einer Appearance passt (Name und Gruppe wie im Appearance-Panel); leer bei Lack, Farbe, Gummi …
DesignExport std::string physicalMaterialFor(const std::string& appearance, const std::string& group);
/// Werkstoff setzen; chosen = vom Nutzer gewählt (eine spätere Appearance ändert ihn dann nicht mehr)
DesignExport bool setPhysicalMaterial(Part::Feature* body, const std::string& uuid, bool chosen);
DesignExport bool physicalMaterialChosen(const App::DocumentObject* body);
/// Masse in kg aus Volumen und Dichte des Werkstoffs; 0, wenn der Werkstoff keine Dichte hat
DesignExport double mass(const Part::Feature* body);
///@}

/// Körper der Komponente moving (mit Unterkomponenten), die einen Körper außerhalb durchdringen: Paare (innen, außen).
/// ponytail: prüft jedes Paar mit einer booleschen Schnittmenge, für Baugruppen mit wenigen Dutzend Körpern gedacht
DesignExport std::vector<std::pair<App::DocumentObject*, App::DocumentObject*>> collisions(App::Part* moving);

/// Idee 1: Rotstift. Eine gelesene Zeile an einer Stelle des Modells wird eine Korrektur am nächsten passenden
/// Element: Kante (R2, C2), ebene Fläche (+5, M5/Ø8 als Bohrung an der Stelle), runde Fläche (M5 Gewinde, Ø8, H7),
/// Fläche mit Maß (12), Feature einer Fläche (3×).
struct Correction
{
    std::string text;  ///< wie gelesen
    RedPen::Command command;
    Body* body = nullptr;
    std::string element;                    ///< Ziel, z. B. "Edge3" (im Zustand des Bodys)
    std::vector<std::string> alternatives;  ///< gleich nah (mit element): Auswahl statt Raten
    Base::Vector3d at;                      ///< Mitte der Tinte (global)
    Base::Vector3d onModel;                 ///< nächster Punkt am Ziel (global)
    Base::Vector3d view;                    ///< Blickrichtung beim Schreiben (global, Länge 1)
    std::string error;                      ///< nicht verstanden oder nichts in der Nähe (englisch)
};
/// Rotstift: wie weit hinter at (entlang into) die Oberfläche eines sichtbaren Körpers liegt, sonst sein nächster Punkt
/// (Tinte neben einer Kante); 0 ohne Körper
DesignExport double modelDepth(App::Document* doc, const Base::Vector3d& at, const Base::Vector3d& into);
/// view: Blickrichtung (in die Szene); die Tinte zielt entlang dieser Richtung auf das Modell
DesignExport Correction readCorrection(App::Document* doc, const std::string& text, const Base::Vector3d& at,
                                       const Base::Vector3d& view);
/// Feature anlegen (Timeline); nullptr und error, wenn es nicht geht. Ohne Transaktion.
DesignExport App::DocumentObject* applyCorrection(const Correction& correction, std::string& error);
/// Kurzbeschreibung für die Karte, englisch: "Fillet R2 on 1 edge"
DesignExport std::string describeCorrection(const Correction& correction);

/// Idee 5: Druckansicht. Dreiecke (je drei Punkte) eines Körpers nach Überhang, Bettfläche und zu dünner Wand
struct PrintCheckResult
{
    std::vector<Base::Vector3f> overhang, bed, thin;
    double overhangArea = 0, bedArea = 0, thinArea = 0;
};
/// shape in eigenen Koordinaten (Placement wird ignoriert), up in denselben; maxAngle in Grad, minWall in mm (0: ohne)
DesignExport PrintCheckResult printCheck(Part::TopoShape shape, const Base::Vector3d& up, double maxAngle, double minWall);
/// Körper mit der Druckrichtung des Designs und den Grenzen aus den Einstellungen (Koordinaten seiner Komponente)
DesignExport PrintCheckResult printCheck(Body* body);
/// Druckrichtung des Designs (global, "nach oben"); Vorgabe +Z. Gespeichert am Wurzel-Bauteil.
DesignExport Base::Vector3d printUp(App::Document* doc);
DesignExport void setPrintUp(App::Document* doc, const Base::Vector3d& up);

/// Name ("FaceN", "EdgeN", "VertexN") des Elements in shape, das geometrisch element entspricht (Schwerpunkt + Größe)
DesignExport std::string elementName(const TopoDS_Shape& shape, const TopoDS_Shape& element);
/// Bezug auf einen Body durch seinen Timeline-Zustand ersetzen (das Feature, das ihn gerade erzeugt hat).
/// Sonst entsteht ein Kreis, sobald ein Feature aus einer Skizze/Ebene darauf denselben Body verändert.
DesignExport void stableRef(App::DocumentObject*& obj, std::string& element);

class DesignExport Body: public Part::Feature
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Body);

public:
    Body();
    /// letztes Feature, das diesen Body erzeugt oder verändert hat. Global: das Feature darf in der übergeordneten
    /// Komponente liegen (Extrude -> New Component)
    App::PropertyLinkGlobal Tip;

    App::DocumentObjectExecReturn* execute() override;
    const char* getViewProviderName() const override
    {
        return "DesignGui::ViewProviderBody";
    }
};

/// Alle geschlossenen Regionen einer Skizze als einzeln anklickbare Flächen (wie die Profile in Fusion).
class DesignExport Profiles: public Part::Feature
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Profiles);

public:
    Profiles();
    App::PropertyLink Sketch;
    App::PropertyStringList Signatures;  ///< je Profil die begrenzenden Skizzenkanten (für die Wiedererkennung)

    App::DocumentObjectExecReturn* execute() override;
    const char* getViewProviderName() const override
    {
        return "DesignGui::ViewProviderProfiles";
    }

    static Profiles* forSketch(App::DocumentObject* sketch);
};

/// Basis aller Timeline-Features. Shape ist ein Compound mit einem Ergebnis pro Eintrag in Bodies.
class DesignExport Feature: public Part::Feature
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Feature);

public:
    enum class Op
    {
        NewBody,
        Join,
        Cut,
        Intersect
    };

    Feature();
    App::PropertyEnumeration Operation;
    App::PropertyLinkListHidden Bodies;  ///< betroffene Bodies (Hidden: Body hängt vom Feature ab, nicht umgekehrt)
    App::PropertyLinkList BaseFeatures;  ///< je Body das vorherige Feature (leer bei New Body)
    App::PropertyBool Suppressed;        ///< unterdrückt: Bodies bleiben unverändert (New Body: leer)
    /// Idee 6: Fehler erklären und reparieren. Fixes: je Vorschlag "Beschriftung\tProperty\tWert" (beim Rechnen neu);
    /// ErrorElements: betroffene Kanten/Flächen im Body-Zustand davor; Warning: Hinweis ohne Fehler (bleibt, bis bestätigt)
    App::PropertyStringList Fixes;
    App::PropertyStringList ErrorElements;
    App::PropertyString Warning;

    Op op() const
    {
        return static_cast<Op>(Operation.getValue());
    }
    const char* getViewProviderName() const override
    {
        return "DesignGui::ViewProviderFeature";
    }
    /// Ergebnis dieses Features für einen der betroffenen Bodies
    Part::TopoShape shapeFor(const App::DocumentObject* body) const;

    App::DocumentObjectExecReturn* execute() override;

    /// Werkzeugkörper (Extrude, Revolve, Hole), z. B. für Pattern
    virtual bool makeTool(Part::TopoShape& tool, std::string& error) const
    {
        (void)tool;
        error = "This feature cannot be patterned";
        return false;
    }

    /// Vorschlag merken: setzt man property auf value, geht das Feature wieder
    void suggest(const std::string& label, const char* property, double value);

protected:
    /// Eigentliche Berechnung (execute kümmert sich um Suppressed)
    virtual App::DocumentObjectExecReturn* compute()
    {
        return StdReturn;
    }
    /// Wendet die Operation mit dem Werkzeug-Körper auf alle Bodies an und setzt Shape.
    App::DocumentObjectExecReturn* applyTool(const Part::TopoShape& tool);
    /// Setzt je Body ein Ergebnis (gleiche Reihenfolge wie Bodies)
    void setResults(const std::vector<Part::TopoShape>& results);
    /// Zustand von Bodies[i] vor diesem Feature
    Part::TopoShape baseShape(size_t i) const;
};

class DesignExport Extrude: public Feature
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Extrude);

public:
    Extrude();
    App::PropertyLinkSub Profile;  ///< Profiles-Objekt + gewählte Flächen (leer = alle)
    App::PropertyStringList ProfileKeys;  ///< Signaturen der gewählten Profile
    App::PropertyEnumeration Extent;
    App::PropertyLength Distance;
    App::PropertyLength Distance2;
    App::PropertyBool Reversed;
    App::PropertyDistance StartOffset;  ///< Profil vorher entlang der Skizzennormalen verschieben (Fusion: Start Versatz)
    App::PropertyLinkSub ToObject;  ///< Extent "To Object": Fläche oder Ebene
    App::PropertyAngle TaperAngle;  ///< positiv = schmaler (Entformung), nicht bei "To Object"
    App::PropertyBool Thin;         ///< dünne Wand entlang des Profilrands
    App::PropertyLength Thickness;
    App::PropertyEnumeration ThinSide;  ///< Inside, Outside, Center

    enum ExtentType
    {
        ExtentOneSide,
        ExtentSymmetric,
        ExtentTwoSides,
        ExtentToObject,
        ExtentAll
    };

    bool makeTool(Part::TopoShape& tool, std::string& error) const override;
    App::DocumentObjectExecReturn* compute() override;

protected:
    void onChanged(const App::Property* prop) override;
    void onDocumentRestored() override;

private:
    void updateVisibility();
};

class DesignExport Revolve: public Feature
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Revolve);

public:
    Revolve();
    App::PropertyLinkSub Profile;
    App::PropertyStringList ProfileKeys;
    App::PropertyEnumeration Axis;  ///< Skizzen-X/Y-Achse oder Ursprungsachse X/Y/Z
    App::PropertyAngle Angle;
    App::PropertyBool Reversed;

    bool makeTool(Part::TopoShape& tool, std::string& error) const override;
    App::DocumentObjectExecReturn* compute() override;

private:
    bool revolveAround(long axis, Part::TopoShape& tool, std::string& error) const;
};

/// Kanten-Features (Fillet, Chamfer): verändern genau einen Body.
/// Edges sind Namen ("EdgeN", oder "FaceN" für alle Kanten einer Fläche) im Body-Zustand vor diesem Feature.
class DesignExport DressUp: public Feature
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::DressUp);

public:
    DressUp();
    App::PropertyStringList Edges;
    App::PropertyLength Size;  ///< Radius bzw. Fasenabstand
    App::PropertyStringList ElementMaps;  ///< verfolgbare Namen zu Edges (topologische Benennung)
    App::PropertyStringList ElementHints;  ///< je Element "x y z Größe": wiederfinden, wenn der Name verloren geht
    App::PropertyIntegerList ElementBodies;  ///< je Element der Index in Bodies (leer: alle zu Bodies[0])

protected:
    /// größter Wert von Size (unter dem jetzigen), bei dem try_ gelingt; 0 wenn keiner (Bisektion, 12 Versuche)
    double largestWorking(const std::function<bool(double)>& try_) const;
    App::DocumentObjectExecReturn* run(bool fillet);
    /// Gewählte Elemente von Bodies[body] vor diesem Feature (shape = dessen Zustand)
    std::vector<Part::TopoShape> elements(const Part::TopoShape& shape, TopAbs_ShapeEnum type, size_t body = 0);
};

/// Rundung; tangential anschließende Kanten rundet OCCT von selbst mit (Kette)
class DesignExport Fillet: public DressUp
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Fillet);

public:
    Fillet();
    App::PropertyBool Variable;      ///< Radius ändert sich linear vom Anfang (Size) zum Ende (RadiusEnd)
    App::PropertyLength RadiusEnd;
    App::DocumentObjectExecReturn* compute() override
    {
        return run(true);
    }

protected:
    void onChanged(const App::Property* prop) override;
};

class DesignExport Chamfer: public DressUp
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Chamfer);

public:
    Chamfer();
    App::PropertyEnumeration Type;  ///< Equal distance, Two distances, Distance and angle
    App::PropertyLength Distance2;
    App::PropertyAngle ChamferAngle;
    App::PropertyBool FlipSide;     ///< Abstand und Winkel auf der anderen Fläche messen
    App::DocumentObjectExecReturn* compute() override
    {
        return run(false);
    }

protected:
    void onChanged(const App::Property* prop) override;
};

/// Körper aushöhlen: Edges = zu öffnende Flächen, Size = Wandstärke
class DesignExport Shell: public DressUp
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Shell);

public:
    Shell();
    App::PropertyBool Outside;
    App::DocumentObjectExecReturn* compute() override;
};

/// Ziel-Body mit Werkzeug-Bodies vereinen, abziehen oder schneiden
class DesignExport Combine: public Feature
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Combine);

public:
    Combine();
    App::PropertyLinkListHidden ToolBodies;
    App::PropertyLinkList ToolFeatures;  ///< Zustand der Werkzeug-Bodies (wie bei Skizzen: Timeline-Zustand)
    App::PropertyBool KeepTools;
    App::DocumentObjectExecReturn* compute() override;
};

/// Bodies verschieben und drehen (um ihren Mittelpunkt)
class DesignExport Move: public Feature
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Move);

public:
    Move();
    App::PropertyVector Translation;
    App::PropertyEnumeration RotationAxis;
    App::PropertyAngle Angle;
    App::PropertyPlacement Alignment;  ///< Align: vor Drehung und Verschiebung angewandt
    App::PropertyLinkSub AxisReference;  ///< Drehachse frei (Achse, Kante, Zylinder); leer = RotationAxis durch die Mitte
    App::DocumentObjectExecReturn* compute() override;
};

/// Bodies an einer Ursprungsebene spiegeln; jedes Ergebnis ist ein neuer Body
class DesignExport Mirror: public Feature
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Mirror);

public:
    Mirror();
    App::PropertyLinkListHidden SourceBodies;
    App::PropertyLinkList SourceFeatures;
    App::PropertyEnumeration Plane;
    App::PropertyLinkSub PlaneReference;  ///< Spiegelebene frei (Ebene, ebene Fläche); leer = Plane
    App::DocumentObjectExecReturn* compute() override;

protected:
    void onChanged(const App::Property* prop) override;
};

/// Ein Feature (Extrude, Revolve, Hole) rechteckig oder kreisförmig wiederholen
class DesignExport Pattern: public Feature
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Pattern);

public:
    Pattern();
    App::PropertyLink Source;
    App::PropertyLinkListHidden SourceBodies;  ///< Körper-Muster: zu wiederholende Bodies (Bodies = neue Bodies)
    App::PropertyLinkList SourceFeatures;      ///< Zustand der Quell-Bodies
    App::PropertyEnumeration Type;  ///< Rectangular, Circular
    App::PropertyEnumeration Direction1;
    App::PropertyIntegerConstraint Count1;
    App::PropertyLength Spacing1;
    App::PropertyEnumeration Direction2;
    App::PropertyIntegerConstraint Count2;
    App::PropertyLength Spacing2;
    App::PropertyEnumeration Axis;
    App::PropertyAngle Angle;
    App::PropertyLinkSub Direction1Reference;  ///< Richtungen frei (Kante, Achse, Ebene/Fläche = Normale)
    App::PropertyLinkSub Direction2Reference;
    App::PropertyLinkSub AxisReference;        ///< Achse des Kreismusters frei (Achse, Kante, Zylinder)
    App::PropertyLinkSub Path;                 ///< Typ "Path": Kanten, entlang derer wiederholt wird
    App::PropertyBool FollowPath;              ///< Kopien drehen sich mit der Pfadrichtung
    App::DocumentObjectExecReturn* compute() override;

protected:
    void onChanged(const App::Property* prop) override;
    void onDocumentRestored() override;

private:
    /// Lagen der Kopien, global; leer mit error, wenn ein Bezug nicht passt
    std::vector<Base::Matrix4D> transforms(std::string& error) const;
    void updateVisibility();
};

/// Bohrungen an allen Punkten einer Skizze (wie "Hole from sketch" in Fusion)
class DesignExport Hole: public Feature
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Hole);

public:
    Hole();
    App::PropertyLink Sketch;
    App::PropertyEnumeration HoleType;  ///< Simple, Counterbore, Countersink
    App::PropertyLength Diameter;
    App::PropertyLength Depth;
    App::PropertyBool ThroughAll;
    App::PropertyLength HeadDiameter;
    App::PropertyLength HeadDepth;
    App::PropertyAngle CountersinkAngle;
    App::PropertyBool Reversed;
    /// Norm: Größe, Durchgang oder Gewinde, Passung und Schraube füllen Diameter und Senkung aus den Tabellen
    App::PropertyEnumeration Standard;  ///< Custom, ISO metric, ISO metric fine, UNC, UNF
    App::PropertyEnumeration Size;      ///< z. B. "M5x0.8" (Liste je Norm)
    App::PropertyEnumeration Kind;      ///< Clearance hole, Tapped hole
    App::PropertyEnumeration Fit;       ///< Durchgang: Fine, Medium, Coarse
    App::PropertyEnumeration Screw;     ///< Senkung nach Schraubennorm (Liste je Bohrungstyp)
    App::PropertyBool Modeled;          ///< Gewinde modelliert (sonst nur Kernloch, kosmetisch)
    App::PropertyString ThreadDesignation;  ///< Ausgabe: Gewinde der Bohrung, leer ohne Gewinde

    bool makeTool(Part::TopoShape& tool, std::string& error) const override;
    App::DocumentObjectExecReturn* compute() override;

protected:
    void onChanged(const App::Property* prop) override;
    void onDocumentRestored() override;

private:
    void applyStandard();
    bool applying = false;
};

/// Profil entlang eines Pfads ziehen (Skizzenkanten oder Körperkanten). Einstellbare Werte liegen in der
/// Gruppe "Parameters": der Feature-Dialog baut daraus seine Felder.
class DesignExport Sweep: public Feature
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Sweep);

public:
    Sweep();
    App::PropertyLinkSub Profile;
    App::PropertyStringList ProfileKeys;
    App::PropertyLinkSub Path;  ///< Objekt mit Kanten ("EdgeN"; leer = alle Kanten)

    bool makeTool(Part::TopoShape& tool, std::string& error) const override;
    App::DocumentObjectExecReturn* compute() override;
};

/// Körper durch zwei oder mehr Profile (aus verschiedenen Skizzen)
class DesignExport Loft: public Feature
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Loft);

public:
    Loft();
    App::PropertyLinkSubList Sections;  ///< Profiles-Objekte mit je einer Fläche, in Reihenfolge
    App::PropertyBool Ruled;
    App::PropertyBool Closed;

    bool makeTool(Part::TopoShape& tool, std::string& error) const override;
    App::DocumentObjectExecReturn* compute() override;
};

/// Grundkörper auf einer Ebene (ohne Ebene: XY): Box, Cylinder, Sphere, Torus, Coil
class DesignExport Primitive: public Feature
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Primitive);

public:
    Primitive();
    App::PropertyLinkSub Plane;
    App::PropertyEnumeration Type;
    App::PropertyLength Length;
    App::PropertyLength Width;
    App::PropertyLength Height;
    App::PropertyLength Radius;
    App::PropertyLength TubeRadius;
    App::PropertyLength Pitch;
    App::PropertyFloatConstraint Turns;
    App::PropertyDistance PositionX;
    App::PropertyDistance PositionY;

    bool makeTool(Part::TopoShape& tool, std::string& error) const override;
    App::DocumentObjectExecReturn* compute() override;

protected:
    void onChanged(const App::Property* prop) override;
};

/// Seitenflächen um einen Winkel neigen (Entformungsschräge); Zugrichtung = Normale der Ebene (ohne: Z)
class DesignExport Draft: public DressUp
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Draft);

public:
    Draft();
    App::PropertyAngle Angle;
    App::PropertyBool Reversed;
    App::PropertyLinkSub Plane;
    App::DocumentObjectExecReturn* compute() override;
};

/// Bodies gleichmäßig skalieren (um den Ursprung oder ihren Mittelpunkt)
class DesignExport Scale: public Feature
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Scale);

public:
    Scale();
    App::PropertyFloatConstraint Factor;
    App::PropertyEnumeration Center;
    App::DocumentObjectExecReturn* compute() override;
};

/// Body an einer Ebene oder Fläche teilen. Bodies[0] ist der geteilte Body (behält das erste Teil),
/// die übrigen Einträge sind die neuen Bodies der weiteren Teile.
class DesignExport Split: public Feature
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Split);

public:
    Split();
    App::PropertyLinkSub Tool;
    App::PropertyInteger Pieces;  ///< Anzahl der Teile beim letzten Berechnen
    App::DocumentObjectExecReturn* compute() override;
};

/// Rippe aus Skizzenlinien: füllt mit der Dicke den Bereich zwischen Linie und Körper (wie Fusions Rib)
class DesignExport Rib: public Feature
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Rib);

public:
    Rib();
    App::PropertyLinkSub Curves;  ///< Skizze mit Linien ("EdgeN"; leer = alle Linien)
    App::PropertyLength Thickness;
    App::PropertyEnumeration Mode;  ///< Rib: wächst in der Skizzenebene; Web: senkrecht zur Skizze
    App::DocumentObjectExecReturn* compute() override;
};

/// Flächen bis zu einer Zielebene oder -fläche verlängern bzw. zurückschneiden (wie Fusions Replace Face)
class DesignExport ReplaceFace: public DressUp
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::ReplaceFace);

public:
    ReplaceFace();
    App::PropertyLinkSub Target;
    App::DocumentObjectExecReturn* compute() override;
};

/// Flächen an einer Ebene, Fläche oder Skizze teilen (Körper bleibt gleich, bekommt neue Kanten)
class DesignExport SplitFace: public DressUp
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::SplitFace);

public:
    SplitFace();
    App::PropertyLinkSub Tool;
    App::DocumentObjectExecReturn* compute() override;
};

/// Skizzenprofile (auch Text) auf Flächen prägen: erhaben (Emboss) oder vertieft (Deboss)
class DesignExport Emboss: public DressUp
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Emboss);

public:
    Emboss();
    App::PropertyLinkSub Profile;
    App::PropertyStringList ProfileKeys;
    App::PropertyEnumeration Type;
    App::PropertyLength Depth;
    App::DocumentObjectExecReturn* compute() override;
};

/// Modelliertes Gewinde auf einer Zylinderfläche (außen: Welle, innen: Bohrung)
class DesignExport Thread: public DressUp
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Thread);

public:
    Thread();
    App::PropertyEnumeration Standard;    ///< Custom (Pitch frei) oder eine Norm wie bei Hole
    App::PropertyEnumeration ThreadSize;  ///< "Auto" = passend zum Flächendurchmesser, sonst z. B. "M8x1.25"
    App::PropertyLength Pitch;
    App::PropertyDistance Clearance;  ///< Spiel je Seite (3D-Druck), negativ = Übermaß
    App::PropertyBool LeftHanded;
    App::PropertyBool ForPrinting;  ///< Idee 4: Spiel für den 3D-Druck, Hinweis bei zu feiner Steigung
    App::PropertyString AutoSize;   ///< Ausgabe: die Größe, die "Auto" gewählt hat (leer bei fester Größe)
    App::DocumentObjectExecReturn* compute() override;

protected:
    void onChanged(const App::Property* prop) override;
    void onDocumentRestored() override;
    /// nur für neu angelegte Gewinde: Norm ISO metrisch, Größe automatisch (geladene behalten ihre Werte)
    void setupObject() override;

private:
    void updateSizes();
    bool checkPitch = true;  ///< Druck-Hinweis nur nach einer Änderung (sonst käme er nach "Sieht richtig aus" wieder)
};

/// Eingefügte Geometrie (STEP): je Solid ein neuer Body, ohne Verlauf (wie Fusions Base Feature)
class DesignExport Import: public Feature
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Import);

public:
    Import();
    Part::PropertyPartShape Imported;
    App::PropertyString SourceFile;
    /// Solids einzeln (ohne Solids: Schalen, sonst die ganze Form), je einer pro Body
    static std::vector<Part::TopoShape> pieces(const Part::TopoShape& shape);
    App::DocumentObjectExecReturn* compute() override;
};

/// Flächen entfernen wie Fusions "Delete Face": die Nachbarflächen wachsen über die Lücke (Defeaturing), z. B. eine
/// Fase, Rundung, Bohrung oder Tasche verschwindet wieder
class DesignExport RemoveFace: public DressUp
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::RemoveFace);

public:
    RemoveFace();
    App::DocumentObjectExecReturn* compute() override;
};

/// Ebene Flächen herausziehen (positiv) oder hineindrücken (negativ)
class DesignExport PressPull: public DressUp
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::PressPull);

public:
    PressPull();
    App::PropertyDistance Distance;
    App::DocumentObjectExecReturn* compute() override;
};

/// Idee 4: Passung. Runde Flächen auf das Mittelmaß einer ISO-286-Passung (H7/g6 …: Bohrung und Welle, auch in
/// zwei Bodies), beim 3D-Druck die Bohrung (sonst die Welle bzw. ebene Flächen) um das Spiel versetzt
class DesignExport Fitting: public DressUp
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Fitting);

public:
    Fitting();
    App::PropertyEnumeration Fit;   ///< 3D print tight/normal/loose, H7/g6, H7/h6, H7/k6, H7/p6, H8/f7
    App::PropertyLength Clearance;  ///< Spiel je Seite beim 3D-Druck (Vorgabe aus den Einstellungen)
    App::PropertyLength Nominal;    ///< Nennmaß der Paarung; 0 = Durchmesser der Bohrung (sonst der Welle)
    App::PropertyString Play;       ///< Ausgabe: Spiel am Durchmesser, z. B. "+7 … +41 µm"; negativ = Übermaß
    App::DocumentObjectExecReturn* compute() override;

protected:
    void onChanged(const App::Property* prop) override;
};

/// Idee 4: Schraube hier. Ein Punkt auf der oberen Komponente und die Richtung hinein: oben Durchgang mit Senkung
/// nach Schraubennorm, unten Gewinde-Kernloch, Einschmelzmutter oder Mutterfalle; die Länge schlägt es vor
class DesignExport Fastener: public Feature
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Fastener);

public:
    Fastener();
    App::PropertyVector Position;     ///< Eintrittspunkt auf der Oberfläche (global)
    App::PropertyVector Direction;    ///< in die Teile hinein (global)
    App::PropertyEnumeration Screw;   ///< ISO 4762, ISO 10642, ISO 7380
    App::PropertyEnumeration Size;    ///< M2 … M12
    App::PropertyEnumeration Bottom;  ///< Tapped hole, Heat-set insert, Nut trap
    App::PropertyBool AutoLength;
    App::PropertyLength Length;  ///< Schraubenlänge nach Norm (Zylinder-/Flachkopf: unter dem Kopf, Senkkopf: gesamt)
    App::DocumentObjectExecReturn* compute() override;

protected:
    void onChanged(const App::Property* prop) override;
};

/// Schraube an point (global, auf top) in Richtung direction; die untere Komponente ist der nächste Body dahinter.
/// Wirft Base::ValueError, wenn dort keiner ist.
DesignExport Fastener* makeFastener(Body* top, const Base::Vector3d& point, const Base::Vector3d& direction);

/// Joint wie in Fusion: setzt die bewegliche Komponente so, dass ihr Bezug (Fläche, Kante, Bohrung, Punkt) auf dem der
/// Gegenstelle liegt. Rigid, Revolute (Angle), Slider (Offset), Cylindrical (beides). Die Komponente übernimmt
/// Result per Ausdruck; Bezüge auf die Komponenten sind versteckt (sonst Kreis Komponente -> Joint -> Komponente).
class DesignExport Joint: public App::DocumentObject
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Joint);

public:
    Joint();
    App::PropertyEnumeration Type;
    App::PropertyLinkHidden Moving;  ///< bewegte Komponente
    App::PropertyLinkSub Origin1;    ///< Bezug an der bewegten Komponente (Body-Element oder Ebene darin)
    App::PropertyLinkSub Origin2;    ///< Bezug der Gegenstelle
    App::PropertyAngle Angle;
    App::PropertyDistance Offset;
    App::PropertyBool Flip;
    App::PropertyPlacement Result;  ///< Lage der bewegten Komponente relativ zu ihrer übergeordneten
    App::PropertyDistance Offset2;  ///< Planar: zweite Richtung in der Ebene
    App::PropertyAngle Angle2;      ///< Ball: Nicken (um Y)
    App::PropertyAngle Angle3;      ///< Ball: Rollen (um X)
    App::PropertyBool Limited;      ///< Winkel und Weg zwischen den Grenzen halten
    App::PropertyAngle AngleMin;
    App::PropertyAngle AngleMax;
    App::PropertyDistance OffsetMin;
    App::PropertyDistance OffsetMax;
    /// Komponente der Gegenstelle: echte Abhängigkeit, damit der Joint nachrechnet, wenn sie sich bewegt (Ketten)
    App::PropertyLink Follows;

    enum JointType
    {
        Rigid,
        Revolute,
        Slider,
        Cylindrical,
        PinSlot,
        Planar,
        Ball
    };
    /// Welche Werte bewegen dieses Gelenk (für Dialog und Animation)
    bool turns() const;
    bool slides() const;

    App::DocumentObjectExecReturn* execute() override;
    /// geschlossene Kette: ändert sich ein Joint der Gruppe, rechnen alle nach
    short mustExecute() const override;
    void unsetupObject() override;
    /// Bewegung aus Winkel und Weg (mit Grenzen) im Rahmen der Gegenstelle
    Base::Placement motion() const;

protected:
    void onChanged(const App::Property* prop) override;

private:
    App::DocumentObjectExecReturn* solveLoop(const std::vector<Joint*>& group);

public:
    const char* getViewProviderName() const override
    {
        return "DesignGui::ViewProviderJoint";
    }
};

/// Post-it (Ordner "Notes"): schwebt über der Ansicht, die Shell zeichnet es. Offen = Visibility (Auge im Browser).
/// Position: Abstand zur nächsten Fensterecke, damit es beim Ändern der Fenstergröße in dieser Ecke bleibt.
class DesignExport Note: public App::DocumentObject
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Note);

public:
    Note();
    App::PropertyString Text;
    App::PropertyInteger Corner;  ///< Bit 0: rechts, Bit 1: unten
    App::PropertyInteger OffsetX;
    App::PropertyInteger OffsetY;
    App::PropertyStringList Defines;  ///< Parameter (Property-Namen), die Zeilen dieser Notiz anlegen (Idee 3)

    const char* getViewProviderName() const override
    {
        return "DesignGui::ViewProviderNote";
    }

protected:
    /// Inhalt, Position und Offen-Zustand laufen nicht über Undo: Strg+Z in der Konstruktion oder ein abgebrochener
    /// Werkzeug-Dialog darf keine Notiz zurückdrehen
    void onBeforeChange(const App::Property* prop) override;
};

/// Scribble (Ordner "Scribbles"): Freihand-Striche mit Stift oder Maus. Jeder Strich liegt auf dem Blatt, auf dem er
/// gezeichnet wurde; das Blatt lässt sich im Raum umstellen, so entstehen 3D-Scribbles. Punkte in Koordinaten der
/// Komponente (Placement bleibt die Identität), alle Listen parallel: Counts sagt, wie viele Punkte zu jedem Strich gehören.
class DesignExport Scribble: public App::GeoFeature
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Scribble);

public:
    enum Tool
    {
        Pencil,
        Pen,
        Marker
    };
    enum Kind  ///< Form des Strichs; in einer Skizze wird Freihand zu Splines, Formen zu Linien, Kreisen und Ellipsen
    {
        Free,
        Line,
        Circle,
        Rectangle,
        Polygon,  ///< gerade Stücke von Punkt zu Punkt: Pfeil, Dreieck, Sechseck
        Ellipse,  ///< achsparallel zum Blatt, Punkt 0 auf der x-Halbachse, Punkt 24 auf der y-Halbachse (96 + 1 Punkte)
        Fill      ///< gefüllte Fläche innerhalb der Punkte (Umriss), ohne Linie
    };
    struct Stroke
    {
        std::vector<Base::Vector3d> points;
        std::vector<double> widths;  ///< Strichbreite je Punkt in mm (Druck schon eingerechnet)
        long tool = Pen;
        long kind = Free;
        Base::Color color;
        Base::Vector3d normal {0, 0, 1};  ///< Blatt-Normale: das Band des Strichs liegt in dieser Ebene
        double depth = 0;  ///< Rotstift: so weit hinter dem Blatt (entlang -normal) liegt das Modell; nur die Anzeige rückt dorthin
    };

    Scribble();
    App::PropertyVectorList Points;
    App::PropertyFloatList Widths;
    App::PropertyIntegerList Counts;
    App::PropertyIntegerList Tools;
    App::PropertyIntegerList Kinds;
    App::PropertyColorList Colors;
    App::PropertyVectorList Normals;
    App::PropertyPlacement Sheet;  ///< aktuelles Zeichenblatt: die XY-Ebene dieser Lage
    App::PropertyBool Tracing;     ///< Transparentpapier: das Modell scheint durchs Blatt
    App::PropertyFloatList Depths; ///< Stroke::depth je Strich (fehlt in älteren Dateien: 0)
    App::PropertyBool OnModel;     ///< Rotstift: jeder Strich zeigt sich auf dem Modell unter ihm, nicht auf dem Blatt davor

    /// leer, solange die Listen nicht zusammenpassen (mitten in einem Undo)
    std::vector<Stroke> strokes() const;
    void setStrokes(const std::vector<Stroke>& strokes);

    const char* getViewProviderName() const override
    {
        return "DesignGui::ViewProviderScribble";
    }
};

/// @name Idee 2: Maße, die eine Fläche treiben (Fläche antippen, Zahl ändern)
///@{
struct DrivingDimension
{
    App::DocumentObject* owner = nullptr;  ///< Feature oder Skizze
    std::string path;                      ///< Property ("Distance") oder Skizzenbemaßung ("Constraints[3]")
    std::string label;                     ///< englisch (bzw. Name der Bemaßung)
    double value = 0;                      ///< mm bzw. Grad
    bool angle = false;
    std::string expression;                ///< Formel, wenn der Wert daran hängt (z. B. ein Parameter)
    Base::Vector3d anchor;                 ///< Mitte der Fläche, global (Anzeige am Modell)
};
/// Werte, die diese Fläche des Bodies erzeugen; leer, wenn keiner (z. B. eingefügte Geometrie)
DesignExport std::vector<DrivingDimension> drivingDimensions(Body* body, const std::string& face);
/// Wert setzen und neu rechnen; hängt er an einem Parameter, ändert sich der Parameter. false mit error, wenn nicht
DesignExport bool setDrivingDimension(App::DocumentObject* owner, const std::string& path, double value, std::string& error);
///@}

/// @name Idee 3: Die Notiz ist die Parameterliste
///@{
/// Parameter-Set des Designs (VarSet "Parameters" in der Wurzel), auf Wunsch angelegt
DesignExport App::DocumentObject* parameterSet(App::Document* doc, bool create);
/// Ausdruck mit Parameter-Namen, auch mit Umlauten ("Wandstärke * 2"), als Property-Ausdruck ("Parameters.Wandstaerke * 2")
DesignExport std::string toParameterExpression(App::Document* doc, const std::string& text);
/// Gegenrichtung zum Anzeigen: ohne "Parameters.", mit den geschriebenen Namen
DesignExport std::string fromParameterExpression(App::Document* doc, const std::string& text);
/// Ausdruck des Parameters setzen (Namen mit Umlauten, Dezimalkomma); wirft, wenn er keinen Wert ergibt
DesignExport void setParameterExpression(App::DocumentObject* set, App::Property* prop, const std::string& text);
/// Objekte, deren Formeln den Parameter noch brauchen (Beschriftungen)
DesignExport std::vector<std::string> parameterUsers(App::DocumentObject* set, const std::string& id);
/// Zeilen "Name = Ausdruck" in Parameter übernehmen; schreibt Werte (→) und Fehler (⚠) in die Zeilen
DesignExport void syncNoteParameters(Note* note);
/// Ein Parameter hat sich anderswo geändert (Maß am Modell, Parameter-Dialog): die Zeile der Notiz nachziehen
DesignExport void parameterChanged(App::DocumentObject* set, const char* name);
/// nach dem Rechnen: Werte hinter den Formeln aller Notizen aktualisieren
DesignExport void refreshNoteValues(App::Document* doc);
///@}

}  // namespace Design
