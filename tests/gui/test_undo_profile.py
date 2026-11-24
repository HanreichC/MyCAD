# SPDX-License-Identifier: LGPL-2.1-or-later
"""Phase 14 (Fund aus test_chaos_ui): in der Bohrungsskizze den Kreis aus dem Teil ziehen, Skizze verlassen, Rückgängig:
die Bohrung ist sofort wieder da (vorher blieb das Teil beim Stand ohne Bohrung, bis irgendetwas anderes neu rechnete)."""
import math
import os
import sys
from harness import *
sys.path.insert(0, os.path.join(os.path.dirname(os.environ["SCRIPT"]), "..", "design"))
import design as D
import Design

S = {}
W = ("wait", lambda: None)
V = App.Vector


def build():
    d = doc()
    _, b = D.box(d, 80, 50, 10)
    hole_sk = D.sketch(d, D.circle(60, 25, 5), support=(b, D.top_face(b)))
    D.extrude(d, hole_sk, 10, op="Cut", bodies=[b], Reversed=True)
    S.update(body=b, sketch=hole_sk, full=round(b.Shape.Volume, 2))
    L("  full %.2f" % S["full"])


def drag_out():
    s = Gui.ActiveDocument.getInEdit().Object
    c = s.Placement.inverse().multVec(V(130, 25, 10))
    doc().openTransaction("Drag Point")
    s.moveGeometry(0, 3, V(c.x, c.y, 0))
    doc().commitTransaction()
    doc().recompute()


def vol():
    return round(S["body"].Shape.Volume, 2)


def log(where):
    return lambda: L("  %s: volume %.2f, undo %s, problems %s" % (where, vol(), doc().UndoNames,
                                                               [(o.Label, t[:50]) for o, t in Design.problems(doc())]))


run([("activate", activate), ("build", build), W,
     ("edit", lambda: Gui.ActiveDocument.setEdit(S["sketch"].Name)), W, W, ("drag", drag_out), W,
     ("leave", lambda: Gui.ActiveDocument.resetEdit()), W, W, ("after leave", log("after leave")),
     ("undo", lambda: Gui.runCommand("Std_Undo")), W, W, ("after undo", log("after undo")),
     ("back", lambda: check("undo after dragging the hole out of the part: the hole is back at once",
                            vol() == S["full"], "%s vs %s" % (vol(), S["full"]))),
     ("redo", lambda: Gui.runCommand("Std_Redo")), W, W, ("after redo", log("after redo")),
     ("again", lambda: check("redo moves it out again: the cut misses and says so", vol() == 40000.0
                             and any("no longer touches" in t for o, t in Design.problems(doc())), str(vol()))),
     ("undo 2", lambda: Gui.runCommand("Std_Undo")), W, W,
     ("back 2", lambda: check("and undo once more brings it back", vol() == S["full"], str(vol()))),
     ])
