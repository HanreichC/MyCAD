# SPDX-License-Identifier: LGPL-2.1-or-later
"""Neue Körper-Features über die echten Befehle und Dialoge: Box, Zylinder, Feder (Grundkörper), Draft, Scale,
Sweep (Kreis entlang einer Linie) und Loft (Quadrat zu Kreis). Erwartete Volumina stehen im Protokoll."""
import math
from harness import *


def sketch(geos, placement=None):
    d = doc(); root = [o for o in d.Objects if o.TypeId == "App::Part"][0]
    sk = d.addObject("Sketcher::SketchObject", "Sketch")
    if placement:
        sk.Placement = placement
    for g in geos:
        sk.addGeometry(g)
    [o for o in d.Objects if o.Label == "Sketches"][0].addObject(sk)
    prof = d.addObject("Design::Profiles", "Profiles"); prof.Sketch = sk; root.addObject(prof)
    d.recompute(); return sk, prof


def circle(r, x=0, y=0):
    return [Part.Circle(App.Vector(x, y, 0), App.Vector(0, 0, 1), r)]


def last_body():
    return [b for b in doc().Objects if b.TypeId == "Design::Body"][-1]


def vol(tag, expected):
    b = last_body()
    L("%s: body=%s volume=%.0f (erwartet ~%.0f) errors=%s" % (tag, b.Label, b.Shape.Volume, expected, errors()))


def dialog_ok():
    QtCore.QTimer.singleShot(400, ok)


state = {}
XZ = App.Placement(App.Vector(), App.Rotation(App.Vector(1, 0, 0), 90))  # Skizzen-Y = globales Z

run([
    ("box", lambda: Gui.runCommand("Design_Box")), ("ok", ok),
    ("box?", lambda: vol("box", 8000)),
    ("cylinder", lambda: Gui.runCommand("Design_Cylinder")), ("ok", ok),
    ("cylinder?", lambda: vol("cylinder", math.pi * 100 * 20)),
    ("coil", lambda: Gui.runCommand("Design_Coil")), ("coil dialog", lambda: shot("coil")), ("ok", ok),
    ("coil?", lambda: vol("coil", math.pi * 4 * 4 * math.hypot(2 * math.pi * 10, 6))),
    ("scale sel", lambda: (Gui.Selection.clearSelection(), Gui.Selection.addSelection(body("Body1")))),
    ("scale", lambda: Gui.runCommand("Design_Scale")),
    ("factor", lambda: [b.setValue(2.0) for b in visible(QtWidgets.QDoubleSpinBox)]), ("ok", ok),
    ("scale?", lambda: L("scale: Body1 volume=%.0f (erwartet 64000)" % body("Body1").Shape.Volume)),
    ("draft sel", lambda: (Gui.Selection.clearSelection(),
                           [Gui.Selection.addSelection(doc().Name, body("Body1").Name, "Face%d" % (i + 1))
                            for i, f in enumerate(body("Body1").Shape.Faces) if abs(f.normalAt(0, 0).z) < 1e-6])),
    ("draft", lambda: Gui.runCommand("Design_Draft")), ("ok", ok),
    ("draft?", lambda: L("draft: Body1 volume=%.0f (kleiner als 64000) errors=%s" % (body("Body1").Shape.Volume, errors()))),
    ("sweep sketches", lambda: state.update(profile=sketch(circle(3, 60, 0)), path=sketch([Part.LineSegment(App.Vector(60, 0, 0), App.Vector(60, 40, 0))], XZ))),
    ("sweep sel", lambda: (Gui.Selection.clearSelection(), Gui.Selection.addSelection(doc().Name, state["profile"][1].Name, "Face1"),
                           Gui.Selection.addSelection(doc().Name, state["path"][0].Name, "Edge1"))),
    ("sweep", lambda: Gui.runCommand("Design_Sweep")), ("ok", ok),
    ("sweep?", lambda: vol("sweep", math.pi * 9 * 40)),
    ("loft sketches", lambda: state.update(a=sketch(rect(90, -10, 110, 10)), b=sketch(circle(5, 100, 0), App.Placement(App.Vector(0, 0, 30), App.Rotation())))),
    ("loft sel", lambda: (Gui.Selection.clearSelection(), Gui.Selection.addSelection(doc().Name, state["a"][1].Name, "Face1"),
                          Gui.Selection.addSelection(doc().Name, state["b"][1].Name, "Face1"))),
    ("loft", lambda: Gui.runCommand("Design_Loft")), ("ok", ok),
    ("loft?", lambda: vol("loft", 30 * (400 + math.pi * 25) / 2)),
    ("timeline", lambda: L("timeline=%s" % [o.Label for o in doc().Objects if o.TypeId.startswith("Design::") and o.TypeId not in ("Design::Body", "Design::Profiles")])),
    ("shot", lambda: shot("features")),
])
