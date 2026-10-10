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
/// Skizze oder Feature aus der Timeline löschen und die Kette dahinter neu verbinden
DesignExport void removeFromTimeline(App::DocumentObject* obj);

class DesignExport Body: public Part::Feature
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Body);

public:
    Body();
    App::PropertyLink Tip;  ///< letztes Feature, das diesen Body erzeugt oder verändert hat

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
    App::PropertyEnumeration Extent;
    App::PropertyLength Distance;
    App::PropertyLength Distance2;
    App::PropertyBool Reversed;

    App::DocumentObjectExecReturn* compute() override;
};

class DesignExport Revolve: public Feature
{
    PROPERTY_HEADER_WITH_OVERRIDE(Design::Revolve);

public:
    Revolve();
    App::PropertyLinkSub Profile;
    App::PropertyEnumeration Axis;  ///< Skizzen-X/Y-Achse oder Ursprungsachse X/Y/Z
    App::PropertyAngle Angle;
    App::PropertyBool Reversed;

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

protected:
    App::DocumentObjectExecReturn* run(bool fillet);
    /// Gewählte Elemente des Bodies vor diesem Feature; Flächen werden bei expandFaces zu ihren Kanten
    std::vector<Part::TopoShape> elements(const Part::TopoShape& shape, TopAbs_ShapeEnum type) const;
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

}  // namespace Design
