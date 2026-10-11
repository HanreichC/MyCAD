# SPDX-License-Identifier: LGPL-2.1-or-later
"""Rib: L-Winkel (Grundplatte + Wand), diagonale Linie in der Mittelebene -> dreieckige Rippe 25x25, 3 mm dick."""
from harness import *


def poly(points):
    p = [App.Vector(x, y, 0) for x, y in points]
    return [Part.LineSegment(p[i], p[(i + 1) % len(p)]) for i in range(len(p))]


state = {}


def rib_sketch():
    d = doc()
    sk = d.addObject("Sketcher::SketchObject", "RibSketch"); sk.Placement.Base.z = 10
    sk.addGeometry(Part.LineSegment(App.Vector(5, 30, 0), App.Vector(30, 5, 0)))
    [o for o in d.Objects if o.Label == "Sketches"][0].addObject(sk)
    d.recompute(); state["sk"] = sk


run([
    ("bracket", lambda: make_body(poly([(0, 0), (40, 0), (40, 5), (5, 5), (5, 40), (0, 40)]), 0, 20, "L")),
    ("before", lambda: L("before=%.1f" % body("L").Shape.Volume)),
    ("sketch", rib_sketch),
    ("select", lambda: (Gui.Selection.addSelection(body("L")), Gui.Selection.addSelection(doc().Name, state["sk"].Name, "Edge1"))),
    ("rib", lambda: Gui.runCommand("Design_Rib")), ("shot", lambda: shot("rib")), ("ok", ok),
    ("after", lambda: L("after=%.1f (zusätzlich 937.5 erwartet) solids=%d errors=%s" % (
        body("L").Shape.Volume, len(body("L").Shape.Solids), errors()))),
])
