# SPDX-License-Identifier: LGPL-2.1-or-later
"""Linie zeichnen, Maus nahe an die Mitte einer anderen Linie: der Punkt fängt dort, ein Dreieck markiert die Mitte
(wie Fusion), der Klick setzt die Mitte-Bedingung. Weiter weg von der Mitte verschwindet das Dreieck."""
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


def marks():
    """Punkte des Mitte-Dreiecks im Szenengraph"""
    from pivy import coin
    search = coin.SoSearchAction(); search.setName(coin.SbName("MidpointHintSet")); search.setInterest(coin.SoSearchAction.FIRST)
    search.apply(Gui.ActiveDocument.ActiveView.getSceneGraph())
    path = search.getPath()
    if not path:
        return None
    sep = path.getNodeFromTail(1)
    coords = [sep.getChild(i) for i in range(sep.getNumChildren()) if sep.getChild(i).isOfType(coin.SoCoordinate3.getClassTypeId())][0]
    return [tuple(round(c, 6) for c in coords.point[i].getValue()[:2]) for i in range(coords.point.getNum())]


def setup():
    sketch().addGeometry(Part.LineSegment(V(-20, 10, 0), V(40, 10, 0)))
    doc().recompute()
    Gui.SendMsgToActiveView("ViewFit")


def near_middle():
    m = marks()
    check("near the middle a triangle marks the midpoint", m == [(10, 10)], str(m))


def off_middle():
    m = marks()
    check("away from the middle there is no triangle", m == [], str(m))


def placed():
    s = sketch()
    end = s.Geometry[-1].EndPoint
    sym = [c for c in s.Constraints if c.Type == "Symmetric"]
    check("the line ends exactly in the middle with a midpoint constraint", (end - V(10, 10, 0)).Length < 1e-9 and len(sym) == 1,
          "%s %s" % (end, [(c.Type, c.First, c.Second, c.Third) for c in s.Constraints]))
    check("after the click the triangle is gone", marks() == [], str(marks()))


in_order([
    ("activate", activate),
    ("sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick XY", lambda: Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XY_Plane")][0])), wait, wait,
    ("setup", setup), wait,
    ("line tool", lambda: click(button("Sketcher_CreateLine"))), wait,
    ("start", lambda: press(-10, 25)), wait,
    ("off middle", lambda: hover(25, 10, 0, 3)), wait,
    ("check off", off_middle),
    ("near middle", lambda: hover(10.8, 10, 0, 3)), wait,
    ("check near", near_middle),
    ("shot", lambda: shot("midpoint")),
    ("end", lambda: press(10.8, 10, 0, 3)), wait,
    ("esc", lambda: QtTest.QTest.keyClick(view().viewport(), QtCore.Qt.Key_Escape)), wait,
    ("placed", placed),
])
