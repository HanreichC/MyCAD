# SPDX-License-Identifier: LGPL-2.1-or-later
"""Appearance: Körper wählen, Material-Vorlage und Farbe anklicken, OK; Undo stellt das Aussehen wieder her."""
from harness import *


def color():
    c = Gui.ActiveDocument.getObject(body("Box").Name).ShapeAppearance[0].DiffuseColor
    return tuple(round(x, 2) for x in c[:3])


def press(text):
    [b.click() for b in visible(QtWidgets.QPushButton) if b.text() == text]


def swatch(hex_):
    [b.click() for b in visible(QtWidgets.QToolButton) if b.toolTip() == hex_]


run([
    ("setup", lambda: make_body(rect(0, 0, 40, 30), 0, 15, "Box")),
    ("before", lambda: L("before=%s" % (color(),))),
    ("select", lambda: Gui.Selection.addSelection(body("Box"))),
    ("appearance", lambda: Gui.runCommand("Design_Appearance")),
    ("aluminum", lambda: (press("Aluminum"), L("aluminum=%s" % (color(),)))),
    ("blue", lambda: (swatch("#007AFF"), L("blue=%s (erwartet (0.0, 0.48, 1.0))" % (color(),)))),
    ("shot", lambda: shot("appearance")), ("ok", ok),
    ("undo", lambda: Gui.runCommand("Std_Undo")),
    ("after undo", lambda: L("after undo=%s" % (color(),))),
])
