# SPDX-License-Identifier: LGPL-2.1-or-later
"""Maßeingabe am Cursor beim Skizzieren (On-View-Parameter): Screenshot mitten in einer Linie."""
from harness import *


def move(fx, fy):
    v = view(); QtTest.QTest.mouseMove(v.viewport(), QtCore.QPoint(int(v.width() * fx), int(v.height() * fy)))


run([
    ("Create Sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick XY", lambda: Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XY_Plane")][0])),
    ("line", lambda: click(button("Sketcher_CreateLine"))),
    ("p1", lambda: view_click(0.4, 0.55)),
    ("move", lambda: move(0.55, 0.45)), ("move2", lambda: move(0.56, 0.44)),
    ("spinboxes", lambda: L("hud=%s" % [(type(w).__name__, w.parentWidget().metaObject().className()) for w in visible(QtWidgets.QAbstractSpinBox)])),
    ("shot", lambda: shot("hud")),
    ("esc", esc), ("esc2", esc),
    ("geometry", lambda: (lambda sk: (sk.addGeometry(Part.LineSegment(App.Vector(-30, -10, 0), App.Vector(30, 15, 0))),
                                      sk.addGeometry(Part.Circle(App.Vector(0, 0, 0), App.Vector(0, 0, 1), 12), True),
                                      sk.addGeometry(rect(-40, -25, -10, -5)), App.ActiveDocument.recompute()))(Gui.ActiveDocument.getInEdit().Object)),
    ("shot colors", lambda: shot("colors")),
])
