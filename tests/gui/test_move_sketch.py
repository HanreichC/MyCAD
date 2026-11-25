# SPDX-License-Identifier: LGPL-2.1-or-later
"""Skizze im Browser wählen, Verschieben: die Skizze bewegt sich in ihrer Ebene, der Körper daraus geht mit; Abbrechen
stellt zurück. Vorher tat Verschieben an einer Skizze nichts (2026-11-25)."""
from harness import *

S = {}


def setup():
    S["b"] = make_body(rect(0, 0, 20, 10), 0, 5, "Plate")
    S["sk"] = [o for o in doc().Objects if o.TypeId == "Sketcher::SketchObject"][0]


def move():
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(S["sk"])
    Gui.runCommand("Design_Move")


def type_x():
    type_field("X distance", "15")


def moved():
    bb = S["b"].Shape.BoundBox
    check("the body made from the sketch moves with it", abs(bb.XMin - 15) < 1e-6 and abs(bb.XMax - 35) < 1e-6, str(bb))


def cancel_back():
    for b in visible(QtWidgets.QPushButton):
        if b.text().replace("&", "") == "Cancel":
            b.click(); break


def back():
    bb = S["b"].Shape.BoundBox
    check("cancel puts it back", abs(bb.XMin) < 1e-6, str(bb))


W = ("wait", lambda: None)
run([("setup", setup), ("activate", activate), ("move", move), W, ("shot", lambda: shot("dialog")), ("x", type_x), W,
     ("moved", moved), ("cancel", cancel_back), W, ("back", back)])
