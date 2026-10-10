# SPDX-License-Identifier: LGPL-2.1-or-later
"""Hole, Pattern, Offset Plane per echter Klicks auf die Glass-Toolbar."""
from harness import *


def setup():
    make_body(rect(0, 0, 60, 40), 0, 10, "Box")
    Gui.ActiveDocument.ActiveView.viewIsometric(); Gui.SendMsgToActiveView("ViewFit")


run([
    ("setup", setup), ("volumes", lambda: L(str(volumes()))), ("shot1", lambda: shot("1-setup")),
    ("Create Sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick top face", lambda: Gui.Selection.addSelection(body("Box"), top_face(body("Box")))),
    # Punkte an feste Stellen (Skizzen-Ursprung liegt in der Ecke der Oberseite)
    ("points", lambda: [Gui.ActiveDocument.getInEdit().Object.addGeometry(Part.Point(App.Vector(x, 20, 0))) for x in (15, 45)]),
    ("finish sketch", lambda: click(button("Sketcher_LeaveSketch"))),
    ("Hole", lambda: click(button("Design_Hole"))),
    ("counterbore", lambda: choose("Counterbore", 1)),
    ("through all", lambda: checkbox("Through all").setChecked(True)),
    ("OK hole", ok), ("volumes", lambda: L(str(volumes()))), ("shot2", lambda: shot("2-hole")),
    ("select hole in timeline", lambda: click([b for b in timeline() if b.toolTip().startswith("Hole")][0])),
    ("Pattern", lambda: click(button("Design_Pattern"))),
    ("count 3", lambda: type_into(0, "3", QtWidgets.QSpinBox)),
    ("spacing 8", lambda: type_into(0, "8 mm")),
    ("OK pattern", ok), ("volumes", lambda: L(str(volumes()))), ("shot3", lambda: shot("3-pattern")),
    ("select XY", lambda: Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XY_Plane")][0])),
    ("Offset Plane", lambda: click(button("Design_OffsetPlane"))),
    ("distance 25", lambda: type_into(0, "25 mm")),
    ("OK plane", ok), ("shot4", lambda: shot("4-plane")),
    ("planes", lambda: L("planes=%s" % [(o.Name, round(o.Placement.Base.z, 3)) for o in doc().Objects if o.TypeId == "PartDesign::Plane"])),
    ("errors", lambda: L("errors=%s" % errors())),
    ("fit", lambda: (Gui.ActiveDocument.ActiveView.viewIsometric(), Gui.SendMsgToActiveView("ViewFit"))),
])
