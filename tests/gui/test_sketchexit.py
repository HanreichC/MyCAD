# SPDX-License-Identifier: LGPL-2.1-or-later
"""Skizzen-Werkzeug beenden: Rechteck zeichnen, dann Esc bzw. Rechtsklick -> Werkzeug ist aus (normaler Mauszeiger)."""
from harness import *


def tool():
    shape = view().viewport().cursor().shape()
    return "aktiv" if shape == QtCore.Qt.BitmapCursor else "aus (%s)" % shape


def right_click(fx, fy):
    v = view(); p = QtCore.QPoint(int(v.width() * fx), int(v.height() * fy))
    QtTest.QTest.mouseMove(v.viewport(), p)
    QtTest.QTest.mouseClick(v.viewport(), QtCore.Qt.RightButton, QtCore.Qt.NoModifier, p)


run([
    ("Create Sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick XY", lambda: Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XY_Plane")][0])),
    ("rect tool", lambda: click(button("Sketcher_CompCreateRectangles"))),
    ("p1", lambda: view_click(0.45, 0.45)), ("p2", lambda: view_click(0.55, 0.55)),
    ("after rect", lambda: L("nach Rechteck: Werkzeug %s, Geometrie %d" % (tool(), len(Gui.ActiveDocument.getInEdit().Object.Geometry)))),
    ("esc", esc),
    ("after esc", lambda: (L("nach Esc: Werkzeug %s, noch in Skizze=%s, Knopf checked=%s down=%s" % (tool(), Gui.ActiveDocument.getInEdit() is not None,
        button("Sketcher_CompCreateRectangles").isChecked(), button("Sketcher_CompCreateRectangles").isDown())), shot("esc"))),
    ("rect tool 2", lambda: click(button("Sketcher_CompCreateRectangles"))),
    ("p3", lambda: view_click(0.30, 0.30)), ("p4", lambda: view_click(0.35, 0.35)),
    ("right", lambda: right_click(0.6, 0.3)),
    ("after right", lambda: L("nach Rechtsklick: Werkzeug %s, menus=%s" % (tool(), [m.isVisible() for m in visible(QtWidgets.QMenu)]))),
])
