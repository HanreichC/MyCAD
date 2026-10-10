# SPDX-License-Identifier: LGPL-2.1-or-later
"""Extrude mit Operation 'New Component': neue Komponente mit dem neuen Body."""
from harness import *


def where(obj):
    return sorted(p.Label for p in obj.InListRecursive if p.TypeId == "App::Part")


run([
    ("Create Sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick XY", lambda: Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XY_Plane")][0])),
    ("rect", lambda: [Gui.ActiveDocument.getInEdit().Object.addGeometry(g) for g in rect(0, 0, 20, 10)]),
    ("finish", lambda: click(button("Sketcher_LeaveSketch"))),
    ("Extrude", lambda: click(button("Design_Extrude"))),
    ("new component", lambda: choose("New Component", 4)),
    ("join then back", lambda: (choose("New Component", 0), choose("New Component", 4))),
    ("OK", ok),
    ("state", lambda: L("parts=%s body in=%s volumes=%s errors=%s" % (
        [o.Label for o in doc().Objects if o.TypeId == "App::Part"], where(body("Body1")), volumes(), errors()))),
    ("undo", lambda: Gui.runCommand("Std_Undo")),
    ("after undo", lambda: L("parts=%s bodies=%s" % ([o.Label for o in doc().Objects if o.TypeId == "App::Part"], volumes()))),
])
