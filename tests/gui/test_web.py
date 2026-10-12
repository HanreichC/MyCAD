# SPDX-License-Identifier: LGPL-2.1-or-later
"""Web: Wanne (Box 60x40x20, Shell 2 mm, oben offen), Linie quer auf z=20 -> Trennwand bis zum Boden, 56x18x3."""
from harness import *

state = {}


def tray():
    b = make_body(rect(0, 0, 60, 40), 0, 20, "Tray")
    top = top_face(b)
    s = doc().addObject("Design::Shell", "Shell"); [o for o in doc().Objects if o.TypeId == "App::Part"][0].addObject(s)
    s.Edges = [top]; s.Size = 2; s.Bodies = [b]; s.BaseFeatures = [b.Tip]; b.Tip = s
    doc().recompute()


def web_sketch():
    sk = doc().addObject("Sketcher::SketchObject", "WebSketch"); sk.Placement.Base.z = 20
    sk.addGeometry(Part.LineSegment(App.Vector(2, 20, 0), App.Vector(58, 20, 0)))
    [o for o in doc().Objects if o.Label == "Sketches"][0].addObject(sk)
    doc().recompute(); state["sk"] = sk


run([
    ("tray", tray), ("before", lambda: L("before=%.0f" % body("Tray").Shape.Volume)),
    ("sketch", web_sketch),
    ("select", lambda: (Gui.Selection.addSelection(body("Tray")), Gui.Selection.addSelection(doc().Name, state["sk"].Name, "Edge1"))),
    ("web", lambda: Gui.runCommand("Design_Web")), ("ok", ok),
    ("after", lambda: L("after=%.0f (zusätzlich 3024 erwartet) errors=%s" % (body("Tray").Shape.Volume, errors()))),
    ("shot", lambda: shot("web")),
])
