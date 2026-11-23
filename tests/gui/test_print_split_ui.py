# SPDX-License-Identifier: LGPL-2.1-or-later
"""12.8 Zum Drucken teilen: eine Leiste, die dreimal so lang ist wie das Bett breit, wird mit einem Klick in drei
gleich lange Stücke geteilt, die alle aufs Bett passen"""
from harness import *
import Design

S = {}
W = ("wait", lambda: None)
grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")
old = [grp.GetFloat(k, d) for k, d in (("BedWidth", 220), ("BedDepth", 220), ("BedHeight", 250))]


def setup():
    for k in ("BedWidth", "BedDepth", "BedHeight"):
        grp.SetFloat(k, 25)
    S["bar"] = make_body(rect(0, 0, 60, 8), 0, 8, "Bar")
    Gui.SendMsgToActiveView("ViewFit")


def bodies():
    return [o for o in doc().Objects if o.TypeId == "Design::Body"]


def split():
    Gui.Selection.clearSelection()
    Gui.runCommand("Design_PrintSplit")


def pieces():
    found = bodies()
    lengths = sorted(round(Design.printSize(b).x, 1) for b in found)
    check("one click cuts the bar into three pieces that all fit the bed",
          len(found) == 3 and Design.tooBigToPrint(doc()) is None, "%d bodies, x sizes %s" % (len(found), lengths))


def restore():
    for k, v in zip(("BedWidth", "BedDepth", "BedHeight"), old):
        grp.SetFloat(k, v)


run([("activate", activate), ("setup", setup), W,
     ("split", split), W, W,
     ("pieces", pieces),
     ("restore", restore),
     ("errors", lambda: check("no errors", not errors(), str(errors()))),
     ])
