# SPDX-License-Identifier: LGPL-2.1-or-later
"""Ziehpfeil: im Extrude-Dialog den Griff an der Pfeilspitze nach oben ziehen."""
from harness import *


def screen(p):  # 3D-Punkt -> Qt-Koordinaten im Viewport (Coin zählt y von unten)
    v = view(); x, y = Gui.ActiveDocument.ActiveView.getPointOnViewport(p)
    dpr = v.viewport().devicePixelRatioF()
    return QtCore.QPoint(int(x / dpr), int(v.viewport().height() - y / dpr))


def drag():
    v = view().viewport(); tip = screen(App.Vector(10, 5, 10))  # Rechteck 0..20 x 0..10, Abstand 10
    QtTest.QTest.mouseMove(v, tip)
    QtTest.QTest.mousePress(v, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, tip)
    for k in range(1, 9):
        QtTest.QTest.mouseMove(v, tip + QtCore.QPoint(0, -10 * k))
    QtTest.QTest.mouseRelease(v, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, tip + QtCore.QPoint(0, -80))


def distance():
    return [o for o in doc().Objects if o.TypeId == "Design::Extrude"][0].Distance


run([
    ("Create Sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick XY", lambda: Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XY_Plane")][0])),
    ("rect", lambda: [Gui.ActiveDocument.getInEdit().Object.addGeometry(g) for g in rect(0, 0, 20, 10)]),
    ("finish", lambda: click(button("Sketcher_LeaveSketch"))),
    ("iso", lambda: (Gui.ActiveDocument.ActiveView.viewIsometric(), Gui.SendMsgToActiveView("ViewFit"))),
    ("Extrude", lambda: click(button("Design_Extrude"))),
    ("before", lambda: L("before distance=%s" % distance())),
    ("shot", lambda: shot("arrow")),
    ("drag", drag),
    ("after", lambda: L("after distance=%s volumes=%s" % (distance(), volumes()))),
    ("OK", ok),
    ("final", lambda: L("final %s errors=%s" % (volumes(), errors()))),
])
