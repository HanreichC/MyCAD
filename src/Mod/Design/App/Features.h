// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <App/PropertyLinks.h>
#include <App/PropertyStandard.h>
#include <App/PropertyUnits.h>
#include <Mod/Design/DesignGlobal.h>
#include <Mod/Part/App/PartFeature.h>

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
///@}

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

    bool makeTool(Part::TopoShape& tool, std::string& error) const override;
    App::DocumentObjectExecReturn* compute() override;
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

protected:
    App::DocumentObjectExecReturn* run(bool fillet);
    /// Gewählte Elemente des Bodies vor diesem Feature; Flächen werden bei expandFaces zu ihren Kanten
    std::vector<Part::TopoShape> elements(const Part::TopoShape& shape, TopAbs_ShapeEnum type);
};

class DesignExport Fillet: public DressUp
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Fillet);

public:
    App::DocumentObjectExecReturn* compute() override
    {
        return run(true);
    }
};

class DesignExport Chamfer: public DressUp
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Chamfer);

public:
    App::DocumentObjectExecReturn* compute() override
    {
        return run(false);
    }
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
    App::DocumentObjectExecReturn* compute() override;
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
    App::DocumentObjectExecReturn* compute() override;

private:
    std::vector<Base::Matrix4D> transforms() const;
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
    bool makeTool(Part::TopoShape& tool, std::string& error) const override;
    App::DocumentObjectExecReturn* compute() override;
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

/// Modelliertes Gewinde auf einer Zylinderfläche (außen: Welle, innen: Bohrung)
class DesignExport Thread: public DressUp
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Thread);

public:
    Thread();
    App::PropertyLength Pitch;
    App::PropertyBool LeftHanded;
    App::DocumentObjectExecReturn* compute() override;
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

/// Ebene Flächen herausziehen (positiv) oder hineindrücken (negativ)
class DesignExport PressPull: public DressUp
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::PressPull);

public:
    PressPull();
    App::PropertyDistance Distance;
    App::DocumentObjectExecReturn* compute() override;
};

}  // namespace Design
