# SPDX-License-Identifier: LGPL-2.1-or-later
"""Komponenten: anlegen (aktiv), darin skizzieren und extrudieren, ganze Komponente verschieben."""
from harness import *


def comp():
    return [o for o in doc().Objects if o.TypeId == "App::Part" and o.Type == "Component"][0]


def comp_plane():
    return [o for o in comp().Origin.OriginFeatures if o.Role == "XY_Plane"][0]


def where(obj):  # Komponente, in der ein Objekt liegt
    parents = [p for p in obj.InListRecursive if p.TypeId == "App::Part"]
    return sorted(p.Label for p in parents)


run([
    ("shot start", lambda: shot("a-start")),
    ("New Component", lambda: click(button("Design_NewComponent"))),
    ("shot new comp", lambda: shot("b-newcomp")),
    ("state", lambda: L("components=%s active=%s" % ([o.Label for o in doc().Objects if o.TypeId == "App::Part"],
                                                   Gui.ActiveDocument.ActiveView.getActiveObject("part").Label))),
    ("Create Sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick component XY", lambda: Gui.Selection.addSelection(comp_plane())),
    ("rect", lambda: [Gui.ActiveDocument.getInEdit().Object.addGeometry(g) for g in rect(0, 0, 20, 10)]),
    ("shot sketch", lambda: shot("c-sketch")),
    ("finish", lambda: click(button("Sketcher_LeaveSketch"))),
    ("Extrude", lambda: click(button("Design_Extrude"))), ("OK", ok),
    ("state", lambda: L("bodies=%s body in=%s sketch in=%s" % (volumes(), where(body("Body1")),
                                                              where([o for o in doc().Objects if o.TypeId == "Sketcher::SketchObject"][0])))),
    ("shot extrude", lambda: shot("d-extrude")),
    ("select component", lambda: Gui.Selection.addSelection(comp())),
    ("Move", lambda: click(button("Design_Move"))), ("x 50", lambda: type_into(0, "50 mm")), ("OK move", ok),
    ("state", lambda: L("component at %s, body global bb=%s errors=%s" % (comp().Placement.Base, body("Body1").getGlobalPlacement().multVec(App.Vector(0, 0, 0)), errors()))),
    ("shot before fit", lambda: shot("1-before")),
    ("fit", lambda: (Gui.ActiveDocument.ActiveView.viewIsometric(), Gui.SendMsgToActiveView("ViewFit"))),
    ("wait", lambda: None), ("wait", lambda: None),
    ("shot after fit", lambda: shot("2-after")),
])
