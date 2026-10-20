# SPDX-License-Identifier: LGPL-2.1-or-later
"""Bemaßen wie in Fusion. Rechteck (Ecken verbunden, waagrecht/senkrecht):
1. Dimension auf der unteren Kante, 50 eintippen, Enter → treibendes Maß, Kante 50 lang
2. Dimension auf der oberen Kante: überbestimmt → getriebenes Maß (Referenz) statt zu verschwinden
3. Doppelklick auf die rechte Kante → Längeneingabe, 20 + Enter → Kante 20 lang
4. Doppelklick auf die linke Kante: überbestimmt → getriebenes Maß"""
from harness import *
import Sketcher

S = {}


def setup():
    sk = Gui.ActiveDocument.getInEdit().Object
    sk.addGeometry(rect(10, 10, 70, 50))  # nicht auf den Achsen, sonst trifft der Klick die Achse
    for i in range(4):
        sk.addConstraint(Sketcher.Constraint("Coincident", i, 2, (i + 1) % 4, 1))
    for c in (("Horizontal", 0), ("Horizontal", 2), ("Vertical", 1), ("Vertical", 3)):
        sk.addConstraint(Sketcher.Constraint(*c))
    doc().recompute(); S["sk"] = sk


def at(x, y):
    p = Gui.ActiveDocument.ActiveView.getPointOnViewport(App.Vector(x, y, 0))
    vp = view().viewport(); dpr = vp.devicePixelRatioF()
    return QtCore.QPoint(int(p[0] / dpr), int(vp.height() - p[1] / dpr))


def zoom():
    """ganzes Rechteck frei sichtbar (nicht unter Toolbar/Palette): Kamera mittig darüber, 200 mm hoch"""
    cam = Gui.ActiveDocument.ActiveView.getCameraNode()
    c = (S["sk"].Geometry[0].StartPoint + S["sk"].Geometry[1].EndPoint) / 2
    cam.position.setValue(c.x, c.y, cam.position.getValue()[2]); cam.height.setValue(200)


def mid(i):
    g = S["sk"].Geometry[i]; return ((g.StartPoint + g.EndPoint) / 2).x, ((g.StartPoint + g.EndPoint) / 2).y


def inside():
    """freier Punkt innen (abseits der Symbole an den Kantenmitten) zum Ablegen eines Maßes"""
    return (mid(3)[0] * 3 + mid(1)[0]) / 4, (mid(0)[1] * 2 + mid(2)[1]) / 3


def view_click_at(x, y):
    vp = view().viewport(); QtTest.QTest.mouseMove(vp, at(x, y))
    QtTest.QTest.mouseClick(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, at(x, y))


def dclick_at(x, y):
    vp = view().viewport(); p = at(x, y); QtTest.QTest.mouseMove(vp, p)
    for _ in range(2):  # die Skizze erkennt den Doppelklick selbst an zwei schnellen Klicks
        QtTest.QTest.mouseClick(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)


def dimension(edge):
    """Kante vorwählen, Dimension, Maß innen ablegen"""
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(doc().Name, S["sk"].Name, edge)
    click(button("Sketcher_Dimension"))
    QtCore.QTimer.singleShot(300, lambda: view_click_at(*inside()))


def enter_value(text):
    box = QtWidgets.QApplication.focusWidget()
    L("  input=%s" % (box and box.metaObject().className()))
    box.lineEdit().selectAll(); QtTest.QTest.keyClicks(box, text); QtTest.QTest.keyClick(box, QtCore.Qt.Key_Return)


def report(tag):
    dims = [(c.First, round(c.Value, 2), c.Driving) for c in S["sk"].Constraints if c.Type == "Distance"]
    L("%s: lengths=%s dims=%s redundant=%s" % (tag, [round(g.length(), 2) for g in S["sk"].Geometry], dims, S["sk"].RedundantConstraints))


run([
    ("Create Sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick XY", lambda: Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XY_Plane")][0])),
    ("setup", setup), ("zoom0", zoom),
    ("dim bottom", lambda: dimension("Edge1")), ("wait", lambda: shot("place")),
    ("type 50", lambda: enter_value("50")),
    ("report1", lambda: report("1 bottom=50")),
    ("esc", esc),
    ("dim top", lambda: dimension("Edge3")), ("wait2", lambda: None),
    ("report2", lambda: report("2 top redundant")),
    ("esc3", esc), ("zoom", zoom),
    ("dclick right", lambda: QtCore.QTimer.singleShot(0, lambda: dclick_at(*mid(1)))),
    ("type 20", lambda: enter_value("20")),
    ("report3", lambda: report("3 right=20")),
    ("dclick left", lambda: QtCore.QTimer.singleShot(0, lambda: dclick_at(*mid(3)))), ("wait3", lambda: None),
    ("report4", lambda: report("4 left redundant")),
    ("errors", lambda: L("errors=%s" % errors())), ("final", lambda: shot("final")),
])
