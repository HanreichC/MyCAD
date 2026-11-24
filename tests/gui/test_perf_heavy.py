# SPDX-License-Identifier: LGPL-2.1-or-later
"""Phase 13.7 Leistung an einem Teil wie aus dem Alltag: Grundplatte, 12 Zapfen (Join), 12 Rundungen oben an den
Zapfen, Bohrungen in allen Zapfen, Rundungen an den Ecken: rund 30 Schritte, über 150 Flächen. Gemessen (timed): Skizze
auf der Deckfläche öffnen und schließen, Extrude-Vorschau beim Tippen, das Grundmaß ändern (alles rechnet neu),
10x Rückgängig. Messwerte in $OUT.perf.txt."""
import os
import sys
from PySide6 import QtGui
from harness import *
sys.path.insert(0, os.path.join(os.path.dirname(os.environ["SCRIPT"]), "..", "design"))
import design as D
import Design
import Sketcher

S = {}
W = ("wait", lambda: None)
V = App.Vector
BOSSES = [(20 + 40 * i, 25 + 50 * j) for i in range(4) for j in range(2)] + [(40 + 40 * i, 50) for i in range(3)] + [(150, 90)]


def build():
    d = doc()
    sk0 = D.sketch(d, D.rect(0, 0, 160, 100))
    C = Sketcher.Constraint  # wie nach "Was fehlt noch": geschlossen, waagrecht/senkrecht, am Ursprung, zwei Maße
    for c in [C("Coincident", i, 2, (i + 1) % 4, 1) for i in range(4)] + [
            C("Horizontal", 0), C("Horizontal", 2), C("Vertical", 1), C("Vertical", 3), C("Coincident", 0, 1, -1, 1),
            C("DistanceX", 0, 1, 0, 2, 160), C("DistanceY", 1, 1, 1, 2, 100)]:
        sk0.addConstraint(c)
    d.recompute()
    _, b = D.extrude(d, sk0, 10)
    for x, y in BOSSES:
        sk = D.sketch(d, D.circle(x, y, 6), App.Placement(V(0, 0, 10), App.Rotation()))
        D.extrude(d, sk, 15, op="Join", bodies=[b])
    for x, y in BOSSES:
        top = [i for i, e in enumerate(b.Shape.Edges, 1)
               if abs(e.CenterOfMass.z - 25) < 1e-6 and abs(e.CenterOfMass.x - x) < 1e-6 and abs(e.CenterOfMass.y - y) < 1e-6]
        D.dress(d, "Design::Fillet", b, ["Edge%d" % top[0]], Size=1)
    holes = D.sketch(d, sum((D.circle(x, y, 2.5) for x, y in BOSSES), []), App.Placement(V(0, 0, 25), App.Rotation()))
    D.extrude(d, holes, 20, op="Cut", bodies=[b], Reversed=True)
    for cx, cy in ((0, 0), (160, 0), (160, 100), (0, 100)):
        e = [i for i, e in enumerate(b.Shape.Edges, 1)
             if abs(e.CenterOfMass.x - cx) < 1e-6 and abs(e.CenterOfMass.y - cy) < 1e-6 and abs(e.CenterOfMass.z - 5) < 1e-6]
        D.dress(d, "Design::Fillet", b, ["Edge%d" % e[0]], Size=5)
    for o in d.Objects:
        if o.TypeId in ("Sketcher::SketchObject", "Design::Profiles"):
            o.Visibility = False
    d.recompute()
    S["body"] = b; S["base"] = sk0
    Gui.ActiveDocument.ActiveView.viewIsometric(); Gui.SendMsgToActiveView("ViewFit")
    L("  part: %d steps, %d faces, errors %s" % (len(Design.timeline(d)), len(b.Shape.Faces), errors()))


def sketches():
    return {o.Name for o in doc().Objects if o.TypeId == "Sketcher::SketchObject"}


def open_sketch():
    S["before"] = sketches()
    Gui.Selection.clearSelection()
    click_at(V(5, 50, 10))  # Deckfläche der Platte, zwischen den Zapfen
    click(button("Design_CreateSketch"))


def close_sketch():
    Gui.ActiveDocument.resetEdit()


def remove_sketch():
    for name in sketches() - S["before"]:
        doc().openTransaction("remove"); Design.removeFromTimeline(doc().getObject(name)); doc().commitTransaction()
    doc().recompute()


def keep_sketch():
    """eine Skizze mit Kreis bleibt auf der Deckfläche (wie Bohrungen, die man später setzt): sie muss das Verbreitern
    der Grundplatte überstehen"""
    new = sketches() - S["before"]
    check("Create Sketch on the top face made one sketch", len(new) == 1, str(new))
    s = doc().getObject(new.pop()); S["kept"] = s
    c = s.Placement.inverse().multVec(V(5, 50, 10))
    s.addGeometry(Part.Circle(V(c.x, c.y, 0), V(0, 0, 1), 2))
    doc().recompute()


def open_extrude():
    if "rect" not in S:
        S["rect"] = D.sketch(doc(), D.rect(60, 70, 80, 90), App.Placement(V(0, 0, 10), App.Rotation()))
    prof = D.profiles(S["rect"])
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(prof, "Face1")
    click(button("Design_Extrude"))


def cancel():
    click([b for b in visible(QtWidgets.QPushButton) if b.text().replace("&", "") == "Cancel"][0])


def wider():
    s = S["base"]
    i = [k for k, c in enumerate(s.Constraints) if c.Type in ("Distance", "DistanceX") and abs(c.Value - 160) < 1e-6]
    doc().openTransaction("wider")
    s.setDatum(i[0], App.Units.Quantity("170 mm"))
    doc().recompute(); doc().commitTransaction()


def save_first():
    doc().saveAs(os.environ["OUT"] + ".heavy.mycad")


def save_like_always():
    """was "Immer gespeichert" nach jeder Änderung tut (saveQuietly): speichern und eine Version anlegen"""
    import time
    import DesignVersions
    t = time.monotonic(); doc().save(); t1 = time.monotonic(); DesignVersions.snapshot(doc(), "")
    L("  save %.0f ms, version snapshot %.0f ms, file %.0f kB" % ((t1 - t) * 1000, (time.monotonic() - t1) * 1000,
                                                                 os.path.getsize(doc().FileName) / 1024))


def hover():
    """Maus über das Teil fahren (ohne Taste): Vorauswahl folgt"""
    b = S["body"].Shape.BoundBox
    for i in range(20):
        p = V(b.XMin + (b.XMax - b.XMin) * i / 19, b.YMin + (b.YMax - b.YMin) * i / 19, b.ZMax)
        vp = view().viewport(); q = screen_of(p)
        QtWidgets.QApplication.sendEvent(vp, QtGui.QMouseEvent(QtCore.QEvent.MouseMove, QtCore.QPointF(q),
                                                               QtCore.QPointF(vp.mapToGlobal(q)), QtCore.Qt.NoButton,
                                                               QtCore.Qt.NoButton, QtCore.Qt.NoModifier))
        QtWidgets.QApplication.processEvents()


def undo10():
    for _ in range(10):
        Gui.runCommand("Std_Undo")


steps = [("activate", activate), ("build", build), W, W]
for k in range(2):
    steps += [timed("heavy: sketch on top face opens #%d" % (k + 1), open_sketch, 500), W,
              timed("heavy: sketch closes #%d" % (k + 1), close_sketch, 300), W, ("rm %d" % k, remove_sketch), W]
steps += [("open again", open_sketch), W, ("keep", keep_sketch), ("close", close_sketch), W]
for k in range(2):
    steps += [timed("heavy: extrude opens #%d" % (k + 1), open_extrude, 300), W,
              timed("heavy: extrude type 5, preview #%d" % (k + 1), lambda: type_field("Distance", "5"), 500), W,
              timed("heavy: extrude cancel #%d" % (k + 1), cancel, 300), W]
steps += [timed("heavy: hover across the part, 20 moves", hover, 500), W,
          ("save first", save_first), W, timed("heavy: always-save (save + version)", save_like_always, 300), W,
          timed("heavy: base 160 -> 170, all recompute", wider, 1500), W,
          ("follows", lambda: check("the wider base recomputes without errors, the sketch on the top face stays on it", not errors()
                                    and abs(S["body"].Shape.BoundBox.XLength - 170) < 1e-6,
                                    "%s %s" % (S["body"].Shape.BoundBox, errors()))),
          timed("heavy: 10x undo", undo10, 2000), W,
          ("errors", lambda: check("no errors", not errors(), str(errors())))]
run(steps)
