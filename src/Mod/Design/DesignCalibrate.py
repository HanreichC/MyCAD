# SPDX-License-Identifier: LGPL-2.1-or-later
"""Testteil fürs Druckerprofil (Plan 12.4): Passungsplatte mit acht Löchern (Spiel 0,05 … 0,40 mm je Seite) und ein
Stift dazu, eine Grenzen-Platte mit Überhängen (30 … 70°) und dünnen Wänden (0,4 … 1,2 mm). Ausdrucken, ansehen und in
den Einstellungen anklicken, was passt: daraus werden Spiel, Überhanggrenze und kleinste Wand (values())."""

PIN = 6.0                                        # Stift-Durchmesser in mm
CLEARANCES = [0.05 * (i + 1) for i in range(8)]  # Spiel je Seite der Löcher 1 … 8
ANGLES = [30, 40, 50, 60, 70]                    # Überhänge, gemessen ab der Senkrechten (wie die Druckansicht)
WALLS = [0.4, 0.6, 0.8, 1.0, 1.2]                # Wandstärken in mm


def values(hole=None, angle=None, wall=None):
    """Einstellungen aus dem, was gepasst hat: hole = Loch 1 … 8, in das der Stift gerade so gleitet (normal);
    eng und locker je 0,1 mm weniger und mehr (Loch 4 ergibt die Vorgaben 0,1 / 0,2 / 0,3).
    angle = letzter saubere Überhang, wall = dünnste ganze Wand"""
    out = {}
    if hole:
        c = CLEARANCES[hole - 1]
        out.update(PrintFitTight=round(max(0.0, c - 0.1), 2), PrintFitNormal=round(c, 2), PrintFitLoose=round(c + 0.1, 2))
    if angle:
        out["OverhangAngle"] = float(angle)
    if wall:
        out["MinWall"] = float(wall)
    return out


def apply(**answers):
    """values() in die Einstellungen schreiben (Passung, Gewinde und Druckansicht lesen sie dort); Rückgabe: values()"""
    import FreeCAD as App
    found = values(**answers)
    grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")
    for key, value in found.items():
        grp.SetFloat(key, value)
    return found


def _engrave(solid, texts, font, size, top):
    """Ziffern 0,6 mm tief in die Oberseite (z = top) schneiden: [(Text, x, y)]; ohne Schrift nur Kerben am ersten"""
    import FreeCAD as App
    import Part
    V = App.Vector
    cutters = []
    for text, x, y in texts:
        if font:
            for char in Part.makeWireString(text, font, size):
                if char:
                    face = Part.makeFace(char, "Part::FaceMakerBullseye")
                    face.translate(V(x, y, top - 0.6))
                    cutters.append(face.extrude(V(0, 0, 1)))
        elif text in ("1", "30", "0.4"):  # ponytail: ohne Schrift zählt man ab der Kerbe; reicht für acht Löcher
            cutters.append(Part.makeCylinder(0.8, 1, V(x + 1, y + size / 2, top - 0.6)))
    return solid.cut(Part.makeCompound(cutters)).removeSplitter() if cutters else solid


def shapes(font=""):
    """[(Name, Solid)]: Passungsplatte, Stift, Grenzen-Platte; flach aufs Bett gelegt, nebeneinander"""
    import math
    import FreeCAD as App
    import Part
    V = App.Vector
    # Passungsplatte 88 x 24 x 4: Löcher in einer Reihe, darunter ihre Nummer
    plate = Part.makeBox(88, 24, 4)
    holes = [Part.makeCylinder(PIN / 2 + c, 6, V(8 + 10 * i, 15, -1)) for i, c in enumerate(CLEARANCES)]
    plate = plate.cut(Part.makeCompound(holes))
    plate = _engrave(plate, [(str(i + 1), 6.5 + 10 * i, 2.5) for i in range(len(CLEARANCES))], font, 4, 4)
    # Stift: steht (wird rund), oben 0,5 mm Fase zum Einführen
    pin = Part.makeCylinder(PIN / 2, 12, V(100, 12, 0))
    pin = pin.makeChamfer(0.5, [e for e in pin.Edges if e.CenterOfMass.z > 11.9])
    # Grenzen-Platte 70 x 36 x 2 hinter der Passungsplatte: links Überhänge (Finnen, die um den Winkel kippen),
    # rechts Wände; jede Reihe 7 mm, dahinter ihre Zahl
    y0, h = 34, 5
    limits = Part.makeBox(70, 36, 2, V(0, y0, 0))
    for k, a in enumerate(ANGLES):
        lean = h * math.tan(math.radians(a))
        y = y0 + 2 + 7 * k
        profile = Part.Face(Part.makePolygon([V(3, y, 2), V(5, y, 2), V(5 + lean, y, 2 + h), V(3 + lean, y, 2 + h), V(3, y, 2)]))
        limits = limits.fuse(profile.extrude(V(0, 4, 0)))
    for k, t in enumerate(WALLS):
        y = y0 + 3.5 + 7 * k
        limits = limits.fuse(Part.makeBox(14, t, 8, V(38, y - t / 2, 2)))
    labels = [(str(a), 21, y0 + 2 + 7 * k) for k, a in enumerate(ANGLES)]
    labels += [(("%.1f" % t), 55, y0 + 2 + 7 * k) for k, t in enumerate(WALLS)]
    limits = _engrave(limits.removeSplitter(), labels, font, 3.5, 2)
    return [("Fit Plate", plate), ("Pin", pin), ("Limits", limits)]


def make(doc, font="", names=None):
    """Testteile als Körper in doc (je ein Eintrag in der Timeline), names: übersetzte Namen; Rückgabe: die Körper"""
    import Design
    root = Design.root(doc)
    bodies = []
    for i, (name, solid) in enumerate(shapes(font)):
        name = names[i] if names else name
        feature = doc.addObject("Design::Import", "Import")
        feature.Label = name + " (Test)"  # der Körper trägt den Namen; gleiche Namen machte FreeCAD zu "Pin001"
        feature.Imported = solid
        root.addObject(feature)
        Design.addToTimeline(feature)
        body = Design.newBody(feature)
        body.Label = name
        bodies.append(body)
    doc.recompute()
    return bodies
