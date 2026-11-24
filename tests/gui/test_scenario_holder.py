# SPDX-License-Identifier: LGPL-2.1-or-later
"""Phase 13.2 Szenario A: ein Halter, gebaut wie ein Mensch es tut, jede typische Handlung gemessen (13.0, timed).
Skizze auf XY, Rechteck, "Was fehlt noch", Maße 40 x 30, Extrude 8 (Tippen, Enter); Skizze auf der Deckfläche per
Klick auf die Fläche, zwei Kreise, Extrude ins Material (Cut); Rundung an einer senkrechten Kante und Fase an einer
oberen Kante per Klick auf die Kante; Grundskizze breiter -> alles folgt; 10x Rückgängig, 10x Wiederholen; Speichern,
Neuöffnen, gleiches Ergebnis. Messwerte in $OUT.perf.txt."""
import math
import os
from harness import *
import Design

S = {}
W = ("wait", lambda: None)
V = App.Vector
FILE = os.environ["OUT"] + ".holder.mycad"


def sk():
    return Gui.ActiveDocument.getInEdit().Object


def the_body():
    return [o for o in doc().Objects if o.TypeId == "Design::Body"][0]


def enter():
    button("Design_Extrude").setFocus()
    QtTest.QTest.keyClick(view(), QtCore.Qt.Key_Return)


# --- Grundkörper --------------------------------------------------------------------------------------------------------
def pick_xy():
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XY_Plane")][0])


def rectangle():
    click(button("Sketcher_CompCreateRectangles"))
    QtCore.QTimer.singleShot(300, lambda: click_at(V(0, 0, 0)))
    QtCore.QTimer.singleShot(700, lambda: click_at(V(37, 28, 0)))  # ungefähr; die Maße kommen danach


def sizes():
    """"Was fehlt noch" ergänzt die Maße, dann Breite 40 und Höhe 30 wie im Maßfeld (setDatum ist dasselbe wie Tippen)"""
    QtTest.QTest.keyClick(view().viewport(), QtCore.Qt.Key_Escape)
    Gui.runCommand("Design_SketchComplete")
    s = sk()
    lengths = [(i, c) for i, c in enumerate(s.Constraints) if c.Type in ("Distance", "DistanceX", "DistanceY") and c.Value > 20]
    for i, c in lengths:
        s.setDatum(i, App.Units.Quantity("40 mm" if c.Value > 33 else "30 mm"))
    doc().recompute()
    S["base"] = s


def leave():
    Gui.ActiveDocument.resetEdit()


def extrude_base():
    prof = [o for o in S["base"].InList if o.TypeId == "Design::Profiles"][0]
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(prof, "Face1")
    click(button("Design_Extrude"))


def base_ok():
    b = the_body()
    check("base plate 40 x 30 x 8", abs(b.Shape.Volume - 40 * 30 * 8) < 0.5 and not errors(), "%.2f %s" % (b.Shape.Volume, errors()))


# --- Bohrungen auf der Deckfläche ---------------------------------------------------------------------------------------
def top_sketch():
    b = the_body()
    top = face_where(b, lambda c: abs(c.z - 8) < 1e-6)
    Gui.Selection.clearSelection()
    click_at(face_point(b, top))
    S["picked"] = [(s.ObjectName, s.SubElementNames) for s in Gui.Selection.getSelectionEx()]
    click(button("Design_CreateSketch"))


def circles():
    check("a click on the top face picked it", any("Face" in n for _, names in S["picked"] for n in names), str(S["picked"]))
    s = sk(); S["top"] = s
    for x in (10, 30):
        c = s.Placement.inverse().multVec(V(x, 15, 8))
        s.addGeometry(Part.Circle(V(c.x, c.y, 0), V(0, 0, 1), 3))
    doc().recompute()


def extrude_holes():
    prof = [o for o in S["top"].InList if o.TypeId == "Design::Profiles"][0]
    faces = [n for n in ("Face%d" % i for i in range(1, len(prof.Shape.Faces) + 1))
             if abs(prof.Shape.getElement(n).Area - math.pi * 9) < 1e-3]
    Gui.Selection.clearSelection()
    for n in faces:
        Gui.Selection.addSelection(prof, n)
    click(button("Design_Extrude"))


def holes_ok():
    want = 40 * 30 * 8 - 2 * math.pi * 9 * 8
    check("two through holes (extrude into the part became Cut)", abs(the_body().Shape.Volume - want) < 0.5,
          "%.2f want %.2f" % (the_body().Shape.Volume, want))


# --- Rundung, Fase ------------------------------------------------------------------------------------------------------
def click_edge(pred):
    b = the_body()
    for i, e in enumerate(b.Shape.Edges, 1):
        m = e.valueAt((e.FirstParameter + e.LastParameter) / 2)
        if pred(e, m):
            Gui.Selection.clearSelection()
            click_at(m)
            S["edge"] = [(s.ObjectName, s.SubElementNames) for s in Gui.Selection.getSelectionEx()]
            return
    raise AssertionError("no edge")


def fillet():
    click_edge(lambda e, m: abs(m.x - 40) < 1e-6 and abs(m.y) < 1e-6)  # senkrechte Kante vorn rechts
    click(button("Design_Fillet"))


def chamfer():
    click_edge(lambda e, m: abs(m.z - 8) < 1e-6 and abs(m.y - 30) < 1e-6)  # obere Kante hinten
    click(button("Design_Chamfer"))


def dressed():
    b = the_body()
    check("fillet and chamfer applied by clicking edges", not errors() and b.Shape.isValid()
          and any(f.Surface.TypeId == "Part::GeomCylinder" and abs(f.Surface.Radius - 3) < 1e-6 for f in b.Shape.Faces),
          "edge picks %s errors %s" % (S.get("edge"), errors()))
    S["before"] = (round(b.Shape.Volume, 3), len(b.Shape.Faces))


# --- später ändern, Rückgängig, Speichern -------------------------------------------------------------------------------
def wider():
    s = S["base"]
    i = [k for k, c in enumerate(s.Constraints) if c.Type in ("Distance", "DistanceX") and abs(c.Value - 40) < 1e-6][0]
    doc().openTransaction("wider"); s.setDatum(i, App.Units.Quantity("60 mm")); doc().recompute(); doc().commitTransaction()


def follows():
    b = the_body()
    check("the base got wider and every later step still works", abs(b.Shape.BoundBox.XLength - 60) < 1e-6 and not errors()
          and b.Shape.isValid(), "x=%.2f errors=%s" % (b.Shape.BoundBox.XLength, errors()))
    S["after"] = (round(b.Shape.Volume, 3), len(b.Shape.Faces))


def undo10():
    for _ in range(10):
        Gui.runCommand("Std_Undo")


def redo10():
    for _ in range(10):
        Gui.runCommand("Std_Redo")


def back():
    b = the_body()
    check("10x undo and 10x redo end where they started", (round(b.Shape.Volume, 3), len(b.Shape.Faces)) == S["after"],
          "%s vs %s" % ((round(b.Shape.Volume, 3), len(b.Shape.Faces)), S["after"]))


def save_reopen():
    doc().saveAs(FILE)
    name = doc().Name
    App.closeDocument(name)
    App.openDocument(FILE)


def same():
    b = the_body()
    check("saved and reopened: same body", (round(b.Shape.Volume, 3), len(b.Shape.Faces)) == S["after"] and not errors(),
          "%s vs %s %s" % ((round(b.Shape.Volume, 3), len(b.Shape.Faces)), S["after"], errors()))


run([("activate", activate), ("xy", pick_xy),
     timed("sketch on XY opens", lambda: click(button("Design_CreateSketch")), 500), W,
     ("rect", rectangle), W, W,
     timed("complete dimensions", sizes, 300), W,
     timed("finish sketch", leave, 300), W,
     timed("extrude opens", extrude_base, 200), W,
     timed("extrude: type 8, preview", lambda: type_field("Distance", "8"), 300), W,
     timed("extrude OK", enter, 300), W, ("base ok", base_ok),
     timed("sketch on top face opens", top_sketch, 500), W, ("circles", circles),
     timed("finish sketch on face", leave, 300), W,
     timed("extrude holes opens", extrude_holes, 300), W,
     timed("holes: type -8 (into the part), preview", lambda: type_field("Distance", "-8"), 300), W,
     timed("holes OK", enter, 300), W, ("holes ok", holes_ok),
     timed("fillet opens (edge click)", fillet, 300), W,
     timed("fillet: type 3, preview", lambda: type_field("Radius", "3"), 300), W,
     timed("fillet OK", enter, 300), W,
     timed("chamfer opens (edge click)", chamfer, 300), W,
     timed("chamfer: type 1, preview", lambda: type_field("Distance", "1"), 300), W,
     timed("chamfer OK", enter, 300), W, ("dressed", dressed),
     timed("base sketch 40 -> 60, recompute", wider, 500), W, ("follows", follows),
     timed("10x undo", undo10, 1500), W, timed("10x redo", redo10, 1500), W, ("back", back),
     timed("save, close, reopen", save_reopen, 1500), W, W, ("same", same),
     ("errors", lambda: check("no errors", not errors(), str(errors()))),
     ])
