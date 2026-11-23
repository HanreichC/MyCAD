# SPDX-License-Identifier: LGPL-2.1-or-later
"""12.7 Snap Recess: Haken wählen, der Befehl schneidet das passende Fenster in das Teil über der Rastnase; wird der
Haken breiter, zieht das Fenster nach"""
from harness import *
import Design

S = {}
W = ("wait", lambda: None)


def setup():
    d = doc(); root = [o for o in d.Objects if o.TypeId == "App::Part"][0]
    hook = d.addObject("Design::Primitive", "Primitive"); root.addObject(hook); Design.addToTimeline(hook)
    hook.Type = "Snap Hook"; hook.Length = 12; hook.Width = 8; hook.Thickness = 1.5; hook.Undercut = 1
    S["hook"], S["hook body"] = hook, Design.newBody(hook)
    S["wall"] = make_body(rect(0, -4, 6, 12), 8, 6, "Wall")  # Wand über der Nase: x 0..6, z 8..14
    d.recompute()
    S["volume"] = S["wall"].Shape.Volume
    Gui.SendMsgToActiveView("ViewFit")


def run_it():
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(S["hook body"])
    Gui.runCommand("Design_SnapRecess")


def cut():
    rec = [o for o in doc().Objects if o.TypeId == "Design::Primitive" and o.Type == "Snap Hook Recess"]
    S["recess"] = rec[0] if rec else None
    check("the recess is cut into the wall over the catch", S["recess"] is not None and S["recess"].Operation == "Cut"
          and list(S["recess"].Bodies) == [S["wall"]] and S["wall"].Shape.Volume < S["volume"] - 1,
          "%s %s" % (S["recess"] and S["recess"].Operation, S["wall"].Shape.Volume))


def wider():
    S["hook"].Width = 12
    doc().recompute()
    check("the recess follows the hook", abs(S["recess"].Width.Value - 12) < 1e-9, str(S["recess"].Width))


run([("activate", activate), ("setup", setup), W,
     ("run", run_it), W, ("cut", cut),
     ("wider", wider),
     ("errors", lambda: check("no errors", not errors(), str(errors()))),
     ])
