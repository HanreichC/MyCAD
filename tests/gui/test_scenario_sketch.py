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
    Gui.ActiveDocument.setEdit(S["sketch"].Name)
    QtCore.QTimer.singleShot(600, frame)


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


def polyline():
    click(button("Sketcher_CreatePolyline"))
    for i, p in enumerate([(0, 0), (50, 0), (50, 30), (0, 30), (0, 0)]):
        later(300 + 250 * i, lambda p=p: click_at(V(p[0], p[1], 0)))
    later(1800, lambda: key(QtCore.Qt.Key_Escape))


def closed():
    check("polyline 50 x 30, clicked closed: one profile", same(S["areas"], [1500]), str(S["areas"]))


def arc():
    """Bogen Mitte, Anfang, Ende: Halbkreis über der Oberkante, die Enden liegen auf ihr (nicht an ihren Ecken)"""
    click(button("Sketcher_CompCreateArc"))
    later(300, lambda: click_at(V(25, 30, 0)))
    later(550, lambda: click_at(V(35, 30, 0)))
    # wie ein Mensch über die Oberkante zum Ende: die Richtung des Bogens folgt dem Weg der Maus
    for i, a in enumerate(range(10, 180, 10)):
        later(700 + 30 * i, lambda a=a: move_at(V(25 + 10 * math.cos(math.radians(a)), 30 + 10 * math.sin(math.radians(a)), 0)))
    later(1400, lambda: click_at(V(15, 30, 0)))
    later(1800, lambda: key(QtCore.Qt.Key_Escape))


def arc_ok():
    check("an arc with its ends on the top edge adds a second profile (half disc)", same(S["areas"], [1500, HALF]), str(S["areas"]))


def fillet():
    click(button("Sketcher_CompCreateFillets"))
    later(400, lambda: click_at(V(50, 0, 0)))

    def radius():
        m = QtWidgets.QApplication.activeModalWidget()
        if m is None:
            L("  no radius field"); return
        box = m.findChild(QtWidgets.QAbstractSpinBox)
        box.lineEdit().selectAll(); QtTest.QTest.keyClicks(box.lineEdit(), "5")
        QtTest.QTest.keyClick(box.lineEdit(), QtCore.Qt.Key_Return)
    later(1400, radius)
    later(1900, lambda: key(QtCore.Qt.Key_Escape))


def fillet_ok():
    check("corner rounded with r = 5 (typed)", same(S["areas"], [1500 - FILLET, HALF]), str(S["areas"]))


def cross():
    click(button("Sketcher_CreateLine"))
    later(300, lambda: click_at(V(-10, 15, 0)))
    later(600, lambda: click_at(V(60, 15, 0)))
    later(1000, lambda: key(QtCore.Qt.Key_Escape))


def crossed():
    check("a line across splits the rectangle in two", same(S["areas"], [750, 750 - FILLET, HALF]), str(S["areas"]))


def trim():
    Gui.runCommand("Sketcher_Trimming")
    later(300, lambda: click_at(V(-5, 15, 0)))
    later(700, lambda: click_at(V(55, 15, 0)))
    later(1100, lambda: key(QtCore.Qt.Key_Escape))


def trimmed():
    s = sk()
    outside = [g for g in s.Geometry if hasattr(g, "StartPoint") and min(g.StartPoint.x, g.EndPoint.x) < -0.5
               or hasattr(g, "StartPoint") and max(g.StartPoint.x, g.EndPoint.x) > 50.5]
    check("trim removes both overhangs, the profiles stay", not outside and same(S["areas"], [750, 750 - FILLET, HALF]),
          "%s %s" % (outside, S["areas"]))


def mirror():
    s = sk()
    a = [i for i, g in enumerate(s.Geometry, 1) if g.TypeId == "Part::GeomArcOfCircle" and abs(g.Center.y - 30) < 0.5]
    S["geo before mirror"] = len(s.Geometry)
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(doc().Name, s.Name, "Edge%d" % a[0])
    # der Knopf wird erst kurz nach der Auswahl aktiv
    later(500, lambda: click(button("Sketcher_Symmetry")))
    later(1000, lambda: click_at(V(40, 15, 0)))  # an der Querlinie: landet unten an der Kante
    later(1500, lambda: key(QtCore.Qt.Key_Escape))


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


def delete_mirror():
    Gui.Selection.clearSelection()
    click_at(V(25, -10, 0))  # unterster Punkt des gespiegelten Bogens
    S["picked"] = [(x.ObjectName, x.SubElementNames) for x in Gui.Selection.getSelectionEx()]
    later(300, lambda: key(QtCore.Qt.Key_Delete))


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
     timed("polyline, 5 clicks", polyline, 3000), W, ("peek closed", peek), W, W, ("look closed", look), W, W, ("closed", closed),
     timed("arc, 3 clicks", arc, 2500), W, ("peek arc ok", peek), W, W, ("look arc ok", look), W, W, ("arc ok", arc_ok),
     timed("fillet a corner, type 5", fillet, 3000), W, ("peek fillet ok", peek), W, W, ("look fillet ok", look), W, W, ("fillet ok", fillet_ok),
     timed("line across", cross, 2000), W, ("peek crossed", peek), W, W, ("look crossed", look), W, W, ("crossed", crossed),
     timed("trim two overhangs", trim, 2000), W, ("peek trimmed", peek), W, W, ("look trimmed", look), W, W, ("trimmed", trimmed),
     timed("mirror the arc", mirror, 2000), W, ("peek mirrored", peek), W, W, ("look mirrored", look), W, W, ("mirrored", mirrored),
     timed("what's missing", complete, 800), W, ("peek completed", peek), W, W, ("look completed", look), W, W, ("completed", completed),
     timed("click and delete", delete_mirror, 1000), W, ("peek deleted", peek), W, W, ("look deleted", look), W, W, ("deleted", deleted),
     timed("leave sketch", leave, 500), W,
     timed("open sketch again", reopen, 500), W, ("reopened", reopened),
     ("errors", lambda: check("no errors", not errors(), str(errors()))),
     ])
