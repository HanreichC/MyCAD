# SPDX-License-Identifier: LGPL-2.1-or-later
"""Rollback-Marker: zurückspulen, Feature dazwischen einfügen, wieder vorspulen."""
from harness import *


def play(icon_index):  # 0 Anfang, 1 zurück, 2 vor, 3 Ende (die vier Knöpfe links in der Timeline)
    btns = sorted([b for b in timeline() if not b.toolTip()], key=lambda b: b.mapToGlobal(QtCore.QPoint(0, 0)).x())
    click(btns[icon_index])


def order():
    return [o.Name for o in [x for x in doc().Objects if x.TypeId == "App::Part"][0].Timeline]


run([
    ("setup", lambda: make_body(rect(0, 0, 60, 40), 0, 10, "Box")),
    ("pick top", lambda: Gui.Selection.addSelection(body("Box"), top_face(body("Box")))),
    ("Fillet", lambda: click(button("Design_Fillet"))), ("r2", lambda: type_into(0, "2 mm")), ("OK fillet", ok),
    ("state", lambda: L("filleted %s" % volumes())),
    ("back", lambda: play(1)),
    ("state", lambda: L("rolled back %s marker=%d" % (volumes(), [x for x in doc().Objects if x.TypeId == "App::Part"][0].RollbackMarker))),
    ("pick top 2", lambda: Gui.Selection.addSelection(body("Box"), top_face(body("Box")))),
    ("Press Pull", lambda: click(button("Design_PressPull"))), ("+5", lambda: type_into(0, "5 mm")), ("OK pp", ok),
    ("state", lambda: L("inserted %s order=%s" % (volumes(), order()))),
    ("end", lambda: play(3)),
    ("state", lambda: L("end %s zmax=%s order=%s errors=%s" % (volumes(), body("Box").Shape.BoundBox.ZMax, order(), errors()))),
    ("undo", lambda: Gui.runCommand("Std_Undo")),
    ("state", lambda: L("after undo %s" % volumes())),
])
