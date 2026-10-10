# SPDX-License-Identifier: LGPL-2.1-or-later
"""Optik: Screenshots von Modell- und Sketch-Modus (Icons, ViewCube, Finish Sketch)."""
from harness import *


def setup():
    make_body(rect(0, 0, 60, 40), 0, 15, "Box")
    Gui.ActiveDocument.ActiveView.viewIsometric(); Gui.SendMsgToActiveView("ViewFit")


run([
    ("setup", setup),
    ("extrude timeline entry", lambda: None),
    ("shot model", lambda: shot("model")),
    ("Create Sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick top", lambda: Gui.Selection.addSelection(body("Box"), top_face(body("Box")))),
    ("shot sketch", lambda: shot("sketch")),
    ("finish", lambda: click(button("Sketcher_LeaveSketch"))),
    ("in edit after finish", lambda: L("edit=%s" % (Gui.ActiveDocument.getInEdit() is not None))),
])
