# SPDX-License-Identifier: LGPL-2.1-or-later
"""L2/L3 im Dialog: Bohrung nach Norm (Größe, Art, Passung, Schraube) und Gewinde mit Spiel"""
from harness import *
import Design

state = {}


def setup():
    b = make_body(rect(-15, -15, 15, 15), 0, 10, "Block")
    state["block"] = b
    root = [o for o in doc().Objects if o.TypeId == "App::Part"][0]
    sk = Design.newSketch(root)
    sk.AttachmentSupport = [Design.stableRef(b, top_face(b))]  # wie "Skizze auf Fläche": am Timeline-Zustand
    sk.MapMode = "FlatFace"
    doc().recompute()
    c = sk.getGlobalPlacement().inverse().multVec(App.Vector(0, 0, 10))  # Blockmitte in Skizzenkoordinaten
    sk.addGeometry(Part.Point(App.Vector(c.x, c.y, 0)))
    doc().recompute()
    state["sketch"] = sk


def hole():
    return [o for o in doc().Objects if o.TypeId == "Design::Hole"][-1]


def combo(label):
    return field(label)


def pick(label, text):
    box = combo(label)
    box.setCurrentIndex(box.findText(text))


run([
    ("setup", setup),
    ("start", lambda: (Gui.Selection.clearSelection(), Gui.Selection.addSelection(state["sketch"]),
                       click(button("Design_Hole")))),
    ("standard", lambda: pick("Standard", "ISO metric")),
    ("size list", lambda: check("size list filled", combo("Size").findText("M5x0.8") >= 0, str(combo("Size").count()))),
    ("size", lambda: pick("Size", "M5x0.8")),
    ("medium", lambda: check("diameter from ISO 273", abs(hole().Diameter.Value - 5.5) < 1e-6
                                and not field("Diameter").isEnabled(), str(hole().Diameter))),
    ("coarse", lambda: pick("Fit", "Coarse")),
    ("coarse set", lambda: check("coarse fit 5.8", abs(hole().Diameter.Value - 5.8) < 1e-6, str(hole().Diameter))),
    ("counterbore", lambda: pick("Type", "Counterbore")),
    ("screw shown", lambda: check("screw row for counterbore", shown("Screw")
                                     and combo("Screw").findText("ISO 4762") >= 0)),
    ("head", lambda: check("head from ISO 4762", abs(hole().HeadDiameter.Value - 10) < 1e-6
                              and not field("Head diameter").isEnabled(), str(hole().HeadDiameter))),
    ("tapped", lambda: pick("Kind", "Tapped hole")),
    ("fit hidden", lambda: check("fit hidden for tapped hole", not shown("Fit") and shown("Size"))),
    ("shot", lambda: shot("hole")),
    ("ok", ok),
    ("errors", lambda: check("no errors", not errors(), str(errors()))),
    ("thread label", lambda: check("thread designation", hole().ThreadDesignation == "M5x0.8", hole().ThreadDesignation)),
])
