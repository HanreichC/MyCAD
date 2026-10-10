# SPDX-License-Identifier: LGPL-2.1-or-later
"""Conic Curve: drei Klicks in der Skizze erzeugen einen rationalen quadratischen B-Spline."""
from harness import *


def report():
    sk = Gui.ActiveDocument.getInEdit().Object
    curves = [g for g in sk.Geometry if g.TypeId == "Part::GeomBSplineCurve"]
    L("bsplines=%s total geometry=%d" % ([(c.Degree, c.NbPoles, [round(w, 2) for w in c.getWeights()]) for c in curves], len(sk.Geometry)))


run([
    ("Create Sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick XY", lambda: Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XY_Plane")][0])),
    ("conic", lambda: click(button("Sketcher_CreateConic"))),
    ("start", lambda: view_click(0.40, 0.60)), ("end", lambda: view_click(0.60, 0.60)), ("shoulder", lambda: view_click(0.50, 0.35)),
    ("report", report),
    ("shot", lambda: shot("conic")),
])
