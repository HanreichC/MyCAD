# SPDX-License-Identifier: LGPL-2.1-or-later
"""Druckbar machen (Phase 11.3) in der Druckansicht: eine Bohrung von der Seite steht als Vorschlag in der Legende,
"Ausführen" macht sie zur Tropfenform (eine Transaktion, Strg+Z nimmt sie zurück) und der Vorschlag verschwindet."""
import math
from harness import *
import Design

S = {}
W = ("wait", lambda: None)


def setup():
    d = doc()
    S["b"] = make_body(rect(0, 0, 20, 20), 0, 10, "Box")
    root = [o for o in d.Objects if o.TypeId == "App::Part"][0]
    sk = Design.newSketch(root)
    sk.addGeometry(Part.Point(App.Vector(0, 0, 0)))
    sk.Placement = App.Placement(App.Vector(20, 10, 5), App.Rotation(App.Vector(0, 1, 0), 90))
    h = d.addObject("Design::Hole", "Hole"); root.addObject(h); Design.addToTimeline(h)
    h.Sketch = sk; h.Diameter = 5; h.Depth = 10
    Design.attachToBodies(h, [S["b"]])
    d.recompute(); S["h"] = h


def rows():
    return [w for w in visible(QtWidgets.QWidget) if w.objectName() == "PrintFix"]


def listed():
    r = rows()
    check("the print view lists the sideways hole under Make printable", len(r) == 1 and "Hole" in r[0].findChild(QtWidgets.QLabel).text(),
          str([w.findChild(QtWidgets.QLabel).text() for w in r]))


def apply():
    click(rows()[0].findChild(QtWidgets.QPushButton))


def applied():
    r = 2.5
    want = 4000 - (math.pi * r * r + r * r - math.pi * r * r / 4) * 10
    check("Apply turns it into a teardrop and the suggestion goes away",
          S["h"].Teardrop and not rows() and abs(S["b"].Shape.Volume - want) < 0.05,
          "teardrop=%s rows=%d vol=%.2f want=%.2f" % (S["h"].Teardrop, len(rows()), S["b"].Shape.Volume, want))


def undone():
    check("Ctrl+Z takes it back and the suggestion returns", not S["h"].Teardrop and len(rows()) == 1,
          "teardrop=%s rows=%d" % (S["h"].Teardrop, len(rows())))


run([("activate", activate), ("setup", setup), W, ("print view", lambda: Gui.runCommand("Design_PrintView")), W, W,
     ("listed", listed), ("shot", lambda: shot("legend")), ("apply", apply), W, W, ("applied", applied),
     ("undo", lambda: Gui.runCommand("Std_Undo")), W, W, ("undone", undone),
     ("off", lambda: Gui.runCommand("Design_PrintView")), W])
