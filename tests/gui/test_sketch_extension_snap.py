# SPDX-License-Identifier: LGPL-2.1-or-later
"""Kreismittelpunkt nahe an der gedachten Verlängerung einer Linie: der Punkt fängt genau darauf (wie Fusion), aber es
entsteht kein "liegt darauf". Sonst hängt der Kreis unsichtbar an der Linie und zieht sie beim Verschieben mit."""
from PySide6 import QtGui
from harness import *

V = App.Vector
wait = ("wait", lambda: None)


def sketch():
    return Gui.ActiveDocument.getInEdit().Object


def hover(x, y, dx=0, dy=0):
    vp = view().viewport(); dpr = vp.devicePixelRatioF()
    px, py = Gui.ActiveDocument.ActiveView.getPointOnViewport(V(x, y, 0))
    p = QtCore.QPoint(int(px / dpr) + dx, int(vp.height() - py / dpr) + dy)
    for q in (p - QtCore.QPoint(1, 1), p):
        QtWidgets.QApplication.sendEvent(vp, QtGui.QMouseEvent(QtCore.QEvent.MouseMove, QtCore.QPointF(q), QtCore.QPointF(vp.mapToGlobal(q)), QtCore.Qt.NoButton, QtCore.Qt.NoButton, QtCore.Qt.NoModifier))
    return p


def press(x, y, dx=0, dy=0):
    QtTest.QTest.mouseClick(view().viewport(), QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, hover(x, y, dx, dy))


def setup():
    sketch().addGeometry(Part.LineSegment(V(0, 5, 0), V(10, 5, 0)))
    sketch().addGeometry(Part.LineSegment(V(0, 15, 0), V(30, 15, 0)))  # nur damit ViewFit Platz rechts der Linie lässt
    doc().recompute()
    Gui.SendMsgToActiveView("ViewFit")


def placed():
    s = sketch()
    circles = [(i, g) for i, g in enumerate(s.Geometry) if isinstance(g, Part.Circle)]
    on = [(c.Type, c.First, c.Second) for c in s.Constraints if c.Type == "PointOnObject"]
    check("one circle was drawn", len(circles) == 1, str(s.Geometry))
    if circles:
        check("its center lands exactly on the extension of the line", abs(circles[0][1].Center.y - 5) < 1e-9, str(circles[0][1].Center))
    check("no 'lies on' binds the circle to the line", on == [], str(on))


in_order([
    ("activate", activate),
    ("sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick XY", lambda: Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XY_Plane")][0])), wait, wait,
    ("setup", setup), wait,
    ("circle tool", lambda: Gui.runCommand("Sketcher_CreateCircle")), wait,
    ("center", lambda: press(22, 5, 0, 1)), wait,
    ("rim", lambda: press(25, 4)), wait,
    ("esc", lambda: QtTest.QTest.keyClick(view().viewport(), QtCore.Qt.Key_Escape)), wait,
    ("shot", lambda: shot("extension_snap")),
    ("placed", placed),
])
