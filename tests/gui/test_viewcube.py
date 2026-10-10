# SPDX-License-Identifier: LGPL-2.1-or-later
"""Eigener ViewCube: Home-Knopf und Klick auf die obere Seite drehen die Kamera."""
from harness import *


def cube_click(x, y):  # Koordinaten relativ zum ViewCube (120x150, oben rechts mit 12 px Rand)
    v = view(); p = QtCore.QPoint(int(v.width() - 132 + x), int(12 + y))
    QtTest.QTest.mouseMove(v.viewport(), p)
    QtTest.QTest.mouseClick(v.viewport(), QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)


def direction():
    d = Gui.ActiveDocument.ActiveView.getViewDirection()
    return "(%.2f, %.2f, %.2f)" % (d.x, d.y, d.z)


run([
    ("setup", lambda: make_body(rect(0, 0, 60, 40), 0, 15, "Box")),
    ("front", lambda: Gui.ActiveDocument.ActiveView.viewFront()),
    ("dir", lambda: L("front view dir=" + direction())),
    ("home", lambda: cube_click(19, 131)), ("wait", lambda: None),
    ("dir", lambda: L("after home dir=" + direction() + " (iso erwartet ~(-0.58, 0.58, -0.58))")),
    ("top face", lambda: cube_click(60, 40)), ("wait", lambda: None),
    ("dir", lambda: L("after top dir=" + direction() + " (oben erwartet (0, 0, -1))")),
    ("home again", lambda: cube_click(19, 131)), ("wait", lambda: None), ("shot", lambda: shot("cube")),
])
