# SPDX-License-Identifier: LGPL-2.1-or-later
"""Phase 13.4 Szenario C: Skizzenarbeit mit echten Klicks, wie ein Mensch sie macht. Polylinie 50 x 30 und
schließen, Bogen auf die Oberkante (Halbkreis außen dran), Ecke abrunden (Radius tippen), eine Linie quer durch und
die Überstände trimmen, den Halbkreis an der Querlinie spiegeln (darf die Skizze nicht überbestimmen), "Was fehlt
noch", den gespiegelten Bogen anklicken und mit Entf löschen,
Skizze verlassen und wieder öffnen. Nach jedem Schritt: Profile (Flächen und Inhalte) wie erwartet. Messwerte
in $OUT.perf.txt."""
import math
from PySide6 import QtGui
from harness import *
import Design

S = {}
W = ("wait", lambda: None)
V = App.Vector
HALF = math.pi * 100 / 2  # Halbkreis r = 10
FILLET = 25 - math.pi * 25 / 4  # Ecke r = 5 weg


def sk():
    e = Gui.ActiveDocument.getInEdit()
    return e.Object if e else S.get("sketch")


def areas():
    """Profile, wie man sie nach dem Verlassen sieht (in der Bearbeitung pausieren sie, siehe peek)"""
    prof = [o for o in S["sketch"].InList if o.TypeId == "Design::Profiles"][0]
    return sorted(round(f.Area, 2) for f in prof.Shape.Faces)


def peek():
    """Skizze verlassen (Profile rechnen im Hintergrund), nach einer Weile wieder öffnen (look)"""
    Gui.ActiveDocument.resetEdit()


def look():
    S["areas"] = areas()
    Gui.ActiveDocument.setEdit(S["sketch"].Name)  # die Kamera danach eigener Schritt (frame): erst wenn alles ruhig ist


def same(got, want):
    """Flächen wie erwartet; geklickte Punkte liegen auf ein paar Hundertstel genau (Pixel), darum 1 %"""
    return len(got) == len(want) and all(abs(a - b) < 0.01 * b for a, b in zip(sorted(got), sorted(want)))


def key(k):
    QtTest.QTest.keyClick(view().viewport(), k)


def move_at(p):
    vp = view().viewport(); q = screen_of(p)
    QtWidgets.QApplication.sendEvent(vp, QtGui.QMouseEvent(QtCore.QEvent.MouseMove, QtCore.QPointF(q),
                                                           QtCore.QPointF(vp.mapToGlobal(q)), QtCore.Qt.NoButton,
                                                           QtCore.Qt.NoButton, QtCore.Qt.NoModifier))


def later(ms, fn):
    QtCore.QTimer.singleShot(ms, fn)


def frame():
    """Blick auf die Gegend um (25, 15), 120 mm hoch (die Skizze schaut schon von oben; viewTop wäre eine Kamerafahrt,
    und die Klicks landeten daneben)"""
    cam = Gui.ActiveDocument.ActiveView.getCameraNode()
    cam.position.setValue(25, 15, 100)
    cam.height.setValue(120)


def start():
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XY_Plane")][0])
    click(button("Design_CreateSketch"))


def clicks(name, points):
    """jeder Klick ein eigener Schritt: der Harness wartet dazwischen, bis MyCAD ruhig ist (unter Last in der CI kamen
    Klicks und Esc nach festen Zeiten durcheinander)"""
    return [("%s %d" % (name, k), lambda p=p: click_at(V(p[0], p[1], 0))) for k, p in enumerate(points)]


def esc():
    return ("esc", lambda: key(QtCore.Qt.Key_Escape))


POLYLINE = [timed("polyline tool", lambda: click(button("Sketcher_CreatePolyline")), 500)] + \
    clicks("polyline", [(0, 0), (50, 0), (50, 30), (0, 30), (0, 0)]) + [esc()]


def closed():
    check("polyline 50 x 30, clicked closed: one profile", same(S["areas"], [1500]), str(S["areas"]))


def arc_end():
    """wie ein Mensch über die Oberkante zum Ende: die Richtung des Bogens folgt dem Weg der Maus"""
    for a in range(10, 180, 10):
        move_at(V(25 + 10 * math.cos(math.radians(a)), 30 + 10 * math.sin(math.radians(a)), 0))
        QtWidgets.QApplication.processEvents()
    click_at(V(15, 30, 0))


# Bogen Mitte, Anfang, Ende: Halbkreis über der Oberkante, die Enden liegen auf ihr (nicht an ihren Ecken)
ARC = [timed("arc tool", lambda: click(button("Sketcher_CompCreateArc")), 500)] + clicks("arc", [(25, 30), (35, 30)]) + \
    [("arc end", arc_end), esc()]


def arc_ok():
    check("an arc with its ends on the top edge adds a second profile (half disc)", same(S["areas"], [1500, HALF]), str(S["areas"]))


def radius():
    """das Feld erscheint modal nach dem Klick auf die Ecke: abwarten, 5 tippen, Enter"""
    import time
    end = time.monotonic() + 15
    m = QtWidgets.QApplication.activeModalWidget()
    while (m is None or m.findChild(QtWidgets.QAbstractSpinBox) is None) and time.monotonic() < end:
        QtWidgets.QApplication.processEvents(QtCore.QEventLoop.AllEvents, 50)
        m = QtWidgets.QApplication.activeModalWidget()
    if m is None:
        L("  no radius field"); return
    box = m.findChild(QtWidgets.QAbstractSpinBox)
    box.lineEdit().selectAll(); QtTest.QTest.keyClicks(box.lineEdit(), "5")
    QtTest.QTest.keyClick(box.lineEdit(), QtCore.Qt.Key_Return)


ROUND_CORNER = [timed("fillet tool", lambda: click(button("Sketcher_CompCreateFillets")), 500),
          ("corner", lambda: later(0, lambda: click_at(V(50, 0, 0)))),  # der Klick öffnet ein modales Feld
          ("radius 5", radius), W, esc()]


def fillet_ok():
    check("corner rounded with r = 5 (typed)", same(S["areas"], [1500 - FILLET, HALF]), str(S["areas"]))


CROSS = [timed("line tool", lambda: click(button("Sketcher_CreateLine")), 500)] + clicks("line", [(-10, 15), (60, 15)]) + [esc()]


def crossed():
    check("a line across splits the rectangle in two", same(S["areas"], [750, 750 - FILLET, HALF]), str(S["areas"]))


TRIM = [timed("trim tool", lambda: Gui.runCommand("Sketcher_Trimming"), 500)] + clicks("trim", [(-5, 15), (55, 15)]) + [esc()]


def trimmed():
    s = sk()
    outside = [g for g in s.Geometry if hasattr(g, "StartPoint") and min(g.StartPoint.x, g.EndPoint.x) < -0.5
               or hasattr(g, "StartPoint") and max(g.StartPoint.x, g.EndPoint.x) > 50.5]
    check("trim removes both overhangs, the profiles stay", not outside and same(S["areas"], [750, 750 - FILLET, HALF]),
          "%s %s" % (outside, S["areas"]))


def pick_arc():
    s = sk()
    a = [i for i, g in enumerate(s.Geometry, 1) if g.TypeId == "Part::GeomArcOfCircle" and abs(g.Center.y - 30) < 0.5]
    S["geo before mirror"] = len(s.Geometry)
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(doc().Name, s.Name, "Edge%d" % a[0])


# der Knopf wird erst kurz nach der Auswahl aktiv; an der Querlinie gespiegelt landet der Bogen unten an der Kante
MIRROR = [("pick arc", pick_arc), W, timed("mirror tool", lambda: click(button("Sketcher_Symmetry")), 500)] + \
    clicks("mirror line", [(40, 15)]) + [esc()]


def mirrored():
    s = sk()
    check("mirroring a half circle leaves the sketch solvable (no redundant constraint)",
          len(s.Geometry) == S["geo before mirror"] + 1 and not s.RedundantConstraints and not s.ConflictingConstraints,
          "geo %d -> %d redundant %s conflicting %s" % (S["geo before mirror"], len(s.Geometry), s.RedundantConstraints,
                                                       s.ConflictingConstraints))


def complete():
    Gui.runCommand("Design_SketchComplete")


def completed():
    s = sk()
    check("\"What's missing\" constrains the sketch fully without moving it",
          s.solve() == 0 and s.FullyConstrained and same(S["areas"], [750, 750 - FILLET, HALF]),
          "solve %s full %s %s" % (s.solve(), s.FullyConstrained, S["areas"]))


def pick_mirrored():
    Gui.Selection.clearSelection()
    click_at(V(25, -10, 0))  # unterster Punkt des gespiegelten Bogens
    S["picked"] = [(x.ObjectName, x.SubElementNames) for x in Gui.Selection.getSelectionEx()]


DELETE = [("pick mirrored", pick_mirrored), W, ("Del", lambda: key(QtCore.Qt.Key_Delete))]


def deleted():
    check("click the mirrored arc, Del: it is gone, the profiles stay",
          len(sk().Geometry) == S["geo before mirror"] and same(S["areas"], [750, 750 - FILLET, HALF]),
          "%d geometries, %s picked %s" % (len(sk().Geometry), S["areas"], S["picked"]))
    S["before leave"] = (len(sk().Geometry), len(sk().Constraints), S["areas"])


def leave():
    Gui.ActiveDocument.resetEdit()


def reopen():
    Gui.ActiveDocument.setEdit(S["sketch"].Name)


def reopened():
    s = sk()
    now = (len(s.Geometry), len(s.Constraints), areas())
    check("leave and open again: same sketch, same profiles, no errors", now == S["before leave"] and not errors(),
          "%s vs %s %s" % (now, S["before leave"], errors()))


run([("activate", activate),
     timed("sketch on XY opens", start, 500), W, ("remember", lambda: S.update(sketch=sk())), ("frame", frame), W,
     *POLYLINE, W, ("peek closed", peek), W, W, ("look closed", look), W, W, ("frame closed", frame), W, ("closed", closed),
     *ARC, W, ("peek arc ok", peek), W, W, ("look arc ok", look), W, W, ("frame arc ok", frame), W, ("arc ok", arc_ok),
     *ROUND_CORNER, W, ("peek fillet ok", peek), W, W, ("look fillet ok", look), W, W, ("frame fillet ok", frame), W, ("fillet ok", fillet_ok),
     *CROSS, W, ("peek crossed", peek), W, W, ("look crossed", look), W, W, ("frame crossed", frame), W, ("crossed", crossed),
     *TRIM, W, ("peek trimmed", peek), W, W, ("look trimmed", look), W, W, ("frame trimmed", frame), W, ("trimmed", trimmed),
     *MIRROR, W, ("peek mirrored", peek), W, W, ("look mirrored", look), W, W, ("frame mirrored", frame), W, ("mirrored", mirrored),
     timed("what's missing", complete, 800), W, ("peek completed", peek), W, W, ("look completed", look), W, W, ("frame completed", frame), W, ("completed", completed),
     *DELETE, W, ("peek deleted", peek), W, W, ("look deleted", look), W, W, ("frame deleted", frame), W, ("deleted", deleted),
     timed("leave sketch", leave, 500), W,
     timed("open sketch again", reopen, 500), W, ("reopened", reopened),
     ("errors", lambda: check("no errors", not errors(), str(errors()))),
     ])
