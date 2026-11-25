# SPDX-License-Identifier: LGPL-2.1-or-later
"""Phase 14 Leistung: eine Arbeitssitzung an einem komplexen Teil, wie ein Mensch (auch in WSL mit Software-OpenGL soll
MyCAD flüssig sein). Teil: Grundplatte mit Maßen, 8 Bohrungen, Rundungen an den Ecken, Flansch an der Seite, Zapfen
mit Fase, Muster. Gemessen (timed): Drehen, Verschieben, Zoomen und Überfahren mit über die Zeit verteilten
Mausbewegungen (Bilder pro Sekunde = Bilder / Dauer), Skizze auf einer Fläche mit Rechteck per Klicks, Extrude mit
Tippen, Rundung per Kantenklick, ein frühes Maß ändern, Rückgängig/Wiederholen. Tabelle in $OUT.perf.txt."""
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


def build():
    d = doc()
    base = D.sketch(d, D.rect(0, 0, 120, 80))
    C = Sketcher.Constraint
    for c in [C("Coincident", i, 2, (i + 1) % 4, 1) for i in range(4)] + [
            C("Horizontal", 0), C("Horizontal", 2), C("Vertical", 1), C("Vertical", 3), C("Coincident", 0, 1, -1, 1),
            C("DistanceX", 0, 1, 0, 2, 120), C("DistanceY", 1, 1, 1, 2, 80)]:
        base.addConstraint(c)
    d.recompute()
    _, b = D.extrude(d, base, 12)
    holes = D.sketch(d, sum((D.circle(15 + 30 * i, 12 + 56 * j, 3) for i in range(4) for j in range(2)), []),
                     support=(b, D.top_face(b)))
    D.extrude(d, holes, 12, op="Cut", bodies=[b], Reversed=True)
    for cx, cy in ((0, 0), (120, 0), (120, 80), (0, 80)):
        e = D.edge_where(b, lambda p, cx=cx, cy=cy: abs(p.x - cx) < 1e-6 and abs(p.y - cy) < 1e-6 and abs(p.z - 6) < 1e-6)
        D.dress(d, "Design::Fillet", b, [e], Size=8)
    side = D.sketch(d, D.rect(30, 0, 90, 30), App.Placement(V(0, 0, 0), App.Rotation(V(1, 0, 0), 90)))
    D.extrude(d, side, 6, op="Join", bodies=[b])
    boss = D.sketch(d, D.circle(60, 40, 12), App.Placement(V(0, 0, 12), App.Rotation()))
    D.extrude(d, boss, 20, op="Join", bodies=[b])
    ring = D.edge_where(b, lambda p: abs(p.z - 32) < 1e-6 and abs(p.x - 60) < 1e-3 and abs(p.y - 40) < 1e-3)
    D.dress(d, "Design::Chamfer", b, [ring], Size=2)
    bore = D.sketch(d, D.circle(60, 40, 6), App.Placement(V(0, 0, 32), App.Rotation()))
    D.extrude(d, bore, 32, op="Cut", bodies=[b], Reversed=True)
    for o in d.Objects:
        if o.TypeId in ("Sketcher::SketchObject", "Design::Profiles"):
            o.Visibility = False
    d.recompute()
    S.update(body=b, base=base)
    Gui.ActiveDocument.ActiveView.viewIsometric(); Gui.SendMsgToActiveView("ViewFit")
    L("  part: %d steps, %d faces, errors %s" % (len(Design.timeline(d)), len(b.Shape.Faces), errors()))


# --- Maus über die Zeit, wie eine Hand (60 Bewegungen pro Sekunde) ---------------------------------------------------------
def send(kind, pos, button, buttons, mods=QtCore.Qt.NoModifier):
    vp = view().viewport()
    QtWidgets.QApplication.sendEvent(vp, QtGui.QMouseEvent(kind, pos, QtCore.QPointF(vp.mapToGlobal(pos.toPoint())),
                                                           button, buttons, mods))


def drag(dx, dy, mods, button=QtCore.Qt.MiddleButton, moves=60):
    vp = view().viewport()
    start = QtCore.QPointF(vp.width() * 0.5, vp.height() * 0.5)
    send(QtCore.QEvent.MouseButtonPress, start, button, button, mods)
    for k in range(1, moves + 1):
        p = start + QtCore.QPointF(dx * k / moves, dy * k / moves)
        QtCore.QTimer.singleShot(16 * k, lambda p=p: send(QtCore.QEvent.MouseMove, p, QtCore.Qt.NoButton, button, mods))
    end = start + QtCore.QPointF(dx, dy)
    QtCore.QTimer.singleShot(16 * moves + 20, lambda: send(QtCore.QEvent.MouseButtonRelease, end, button, QtCore.Qt.NoButton, mods))


def orbit():
    drag(240, 90, QtCore.Qt.ShiftModifier)


def pan():
    drag(-200, 60, QtCore.Qt.NoModifier)


def zoom():
    vp = view().viewport(); p = QtCore.QPointF(vp.rect().center())
    for k in range(12):
        def w(k=k):
            ev = QtGui.QWheelEvent(p, QtCore.QPointF(vp.mapToGlobal(p.toPoint())), QtCore.QPoint(),
                                   QtCore.QPoint(0, 120 if k < 6 else -120), QtCore.Qt.NoButton, QtCore.Qt.NoModifier,
                                   QtCore.Qt.NoScrollPhase, False)
            QtWidgets.QApplication.sendEvent(vp, ev)
        QtCore.QTimer.singleShot(40 * k, w)


def hover():
    b = S["body"].Shape.BoundBox
    for k in range(40):
        p = V(b.XMin + b.XLength * k / 39, b.YMin + b.YLength * (0.3 + 0.4 * k / 39), b.ZMax)
        QtCore.QTimer.singleShot(16 * k, lambda p=p: send(QtCore.QEvent.MouseMove, QtCore.QPointF(screen_of(p)),
                                                          QtCore.Qt.NoButton, QtCore.Qt.NoButton))


# --- Modellieren --------------------------------------------------------------------------------------------------------
def sketch_on_top():
    Gui.Selection.clearSelection()
    click_at(V(100, 40, 12))  # Deckfläche rechts vom Zapfen
    click(button("Design_CreateSketch"))


def rectangle():
    s = Gui.ActiveDocument.getInEdit().Object
    S["sk"] = s
    a = s.Placement.multVec(V(0, 0, 0))
    click(button("Sketcher_CompCreateRectangles"))
    QtCore.QTimer.singleShot(300, lambda: click_at(V(92, 30, 12)))
    QtCore.QTimer.singleShot(600, lambda: click_at(V(108, 50, 12)))


def leave():
    QtTest.QTest.keyClick(view().viewport(), QtCore.Qt.Key_Escape)
    Gui.ActiveDocument.resetEdit()


def extrude_open():
    prof = [o for o in S["sk"].InList if o.TypeId == "Design::Profiles"][0]
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(prof, "Face1")
    click(button("Design_Extrude"))


def enter():
    button("Design_Extrude").setFocus()
    QtTest.QTest.keyClick(view().viewport(), QtCore.Qt.Key_Return)


def fillet_open():
    """hintere obere Kante der Platte (gut sichtbar in der Iso-Ansicht) wählen, Rundung öffnen"""
    b = S["body"]
    for i, e in enumerate(b.Shape.Edges, 1):
        m = e.valueAt((e.FirstParameter + e.LastParameter) / 2)
        if abs(m.z - 12) < 1e-6 and abs(m.y - 80) < 1e-3:
            Gui.Selection.clearSelection(); Gui.Selection.addSelection(doc().Name, b.Name, "Edge%d" % i); break
    click(button("Design_Fillet"))


def wider():
    s = S["base"]
    i = [k for k, c in enumerate(s.Constraints) if c.Type == "DistanceX"][0]
    doc().openTransaction("wider"); s.setDatum(i, App.Units.Quantity("140 mm")); doc().recompute(); doc().commitTransaction()


def undo5():
    for _ in range(5):
        Gui.runCommand("Std_Undo")


def redo5():
    for _ in range(5):
        Gui.runCommand("Std_Redo")


def fps_report():
    import harness
    for name, ms, worst, paints, budget in harness._perf:
        if ms > 0 and name.startswith(("orbit", "pan", "zoom", "hover")):
            L("  %-28s %5.1f frames/s, longest block %4.0f ms" % (name, paints / (ms / 1000.0), worst))


run([("activate", activate), ("build", build), W, W,
     timed("orbit 1 s", orbit, 1200), W, timed("pan 1 s", pan, 1200), W, timed("zoom 12 steps", zoom, 1000), W,
     timed("fit all (animated)", lambda: Gui.SendMsgToActiveView("ViewFit"), 300), W,
     timed("hover 40 moves", hover, 900), W,
     timed("sketch on top face opens", sketch_on_top, 500), W, timed("rectangle, 2 clicks", rectangle, 1200), W,
     timed("finish sketch", leave, 300), W,
     timed("extrude opens", extrude_open, 300), W, timed("extrude: type 10, preview", lambda: type_field("Distance", "10"), 500), W,
     timed("extrude OK", enter, 500), W,
     timed("fillet opens (edge click)", fillet_open, 300), W, timed("fillet: type 2, preview", lambda: type_field("Radius", "2"), 500), W,
     timed("fillet OK", enter, 500), W,
     timed("orbit 1 s (after edits)", orbit, 1200), W,
     timed("base 120 -> 140", wider, 1500), W,
     timed("5x undo", undo5, 1500), W, timed("5x redo", redo5, 1500), W,
     ("fps", fps_report),
     ("errors", lambda: check("no errors", not errors(), str(errors()))),
     ])
