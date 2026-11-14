# SPDX-License-Identifier: LGPL-2.1-or-later
"""Abrunden in der Skizze fragt wie Fusion gleich den Radius ab: Klick auf eine Ecke, Wert tippen, Enter → Bogen mit
genau diesem Radius und einem Radius-Maß. Esc im Feld nimmt das Abrunden ganz zurück."""
import os
from PySide6 import QtGui
from harness import *

V = App.Vector
wait = ("wait", lambda: None)
S = {}


def sketch():
    return Gui.ActiveDocument.getInEdit().Object


def click_corner(x, y):
    """Echter Klick auf die Ecke (x, y); der Feld-Dialog ist modal, darum aus der Ereignisschleife heraus"""
    vp = view().viewport(); dpr = vp.devicePixelRatioF()
    px, py = Gui.ActiveDocument.ActiveView.getPointOnViewport(V(x, y, 0))
    p = QtCore.QPoint(int(px / dpr), int(vp.height() - py / dpr))

    def go():
        for q in (p - QtCore.QPoint(1, 1), p):
            QtWidgets.QApplication.sendEvent(vp, QtGui.QMouseEvent(QtCore.QEvent.MouseMove, QtCore.QPointF(q), QtCore.QPointF(vp.mapToGlobal(q)), QtCore.Qt.NoButton, QtCore.Qt.NoButton, QtCore.Qt.NoModifier))
        QtTest.QTest.mouseClick(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)
    QtCore.QTimer.singleShot(0, go)


def setup():
    s = sketch()
    for g in rect(0, 0, 40, 20):
        s.addGeometry(g)
    import Sketcher
    for i in range(4):
        s.addConstraint(Sketcher.Constraint("Coincident", i, 2, (i + 1) % 4, 1))
    doc().recompute()
    Gui.SendMsgToActiveView("ViewFit")


def dialog_open():
    m = QtWidgets.QApplication.activeModalWidget()
    S["dialog"] = m
    check("clicking a corner asks for the radius", m is not None, str(m and m.windowTitle()))


def type_value(text):
    box = QtWidgets.QApplication.focusWidget()
    box.lineEdit().selectAll(); QtTest.QTest.keyClicks(box, text); QtTest.QTest.keyClick(box, QtCore.Qt.Key_Return)


def rounded():
    s = sketch()
    arcs = [g for g in s.Geometry if isinstance(g, Part.ArcOfCircle)]
    radius = [c.Value for c in s.Constraints if c.Type == "Radius"]
    check("the corner is rounded with exactly the typed radius and keeps a radius dimension",
          len(arcs) == 1 and abs(arcs[0].Radius - 3) < 1e-6 and radius == [3.0],
          "arcs=%s radius=%s" % ([round(a.Radius, 4) for a in arcs], radius))
    S["count"] = s.GeometryCount


def esc():
    QtTest.QTest.keyClick(QtWidgets.QApplication.focusWidget(), QtCore.Qt.Key_Escape)


def undone():
    s = sketch()
    check("esc in the radius field takes the whole fillet back",
          QtWidgets.QApplication.activeModalWidget() is None and s.GeometryCount == S["count"]
          and len([c for c in s.Constraints if c.Type == "Radius"]) == 1,
          "geometry %d -> %d" % (S["count"], s.GeometryCount))


in_order([
    ("activate", activate),
    ("sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick XY", lambda: Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XY_Plane")][0])), wait, wait,
    ("setup", setup), wait,
    ("fillet tool", lambda: Gui.runCommand("Sketcher_CreateFillet")), wait,
    ("corner", lambda: click_corner(40, 20)), wait, wait,
    ("dialog", dialog_open),
    ("shot", lambda: (shot("fillet_dialog"), S["dialog"] and S["dialog"].grab().save(os.environ["OUT"] + ".fillet_field.png"))),
    ("type", lambda: type_value("3")), wait,
    ("rounded", rounded),
    ("corner 2", lambda: click_corner(0, 0)), wait, wait,
    ("dialog 2", dialog_open),
    ("esc", esc), wait,
    ("undone", undone),
])
