# SPDX-License-Identifier: LGPL-2.1-or-later
"""Das Material geht mit, wo neue Körper entstehen oder ein Körper sich ändert (Fortsetzung von test_material_kept):
Spiegeln und Muster eines Nussbaum-Körpers sind Nussbaum. Eine einzeln bemalte Deckfläche bleibt es beim Verschieben,
nach Extrudieren und Rückgängig/Wiederholen und nach Speichern und Öffnen."""
import os
from harness import *

S = {}
W = ("wait", lambda: None)
V = App.Vector


def vp(obj):
    return Gui.ActiveDocument.getObject(obj.Name)


def rgb(m):
    return tuple(round(c, 3) for c in m.DiffuseColor[:3])


def bodies():
    return [o for o in doc().Objects if o.TypeId == "Design::Body"]


def tile(name):
    [b for b in visible(QtWidgets.QToolButton) if b.accessibleName() == name][0].click()


def setup():
    S["body"] = make_body(rect(0, 0, 40, 30), 0, 10, "Plate")
    Gui.ActiveDocument.ActiveView.viewIsometric()
    Gui.SendMsgToActiveView("ViewFit")


def select_body():
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(S["body"])


def remember():
    S["walnut"] = rgb(vp(S["body"]).ShapeAppearance[0])
    S["before"] = set(bodies())
    L("  walnut %s" % (S["walnut"],))


def new_bodies_walnut(what):
    def go():
        new = [o for o in bodies() if o not in S["before"]]
        looks = [(o.Label, [rgb(m) for m in vp(o).ShapeAppearance][:2]) for o in new]
        check("the %s of a walnut body is walnut" % what,
              new and all(all(rgb(m) == S["walnut"] for m in vp(o).ShapeAppearance) for o in new), str(looks))
        S["before"] = set(bodies())
    return go


# --- einzeln bemalte Deckfläche ---
def top_index(b):
    return [i for i, f in enumerate(b.Shape.Faces) if abs(f.CenterOfMass.z - b.Shape.BoundBox.ZMax) < 1e-6][0]


def paint_top():
    S["tile"] = make_body(rect(80, 0, 120, 30), 0, 10, "Tile")
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(doc().Name, S["tile"].Name, "Face%d" % (top_index(S["tile"]) + 1))
    Gui.runCommand("Design_Appearance")


def faces(b):
    mats = vp(b).ShapeAppearance
    if len(mats) != len(b.Shape.Faces):
        return None, None
    top = top_index(b)
    return rgb(mats[top]), {rgb(m) for i, m in enumerate(mats) if i != top}


def remember_faces():
    S["faces"] = faces(S["tile"])
    L("  faces %s" % (S["faces"],))
    check("only the top face is walnut", S["faces"][0] == S["walnut"] and S["walnut"] not in S["faces"][1], str(S["faces"]))


def top_walnut(what):
    def go():
        t = [o for o in bodies() if o.Label == "Tile"][0]
        S["tile"] = t
        check("the walnut top face stays walnut " + what, faces(t) == S["faces"],
              "%s -> %s (%d colors, %d faces)" % (S["faces"], faces(t), len(vp(t).ShapeAppearance), len(t.Shape.Faces)))
    return go


def move_tile():
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(S["tile"])
    click(button("Design_Move"))


def extrude_top():
    t = S["tile"]
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(doc().Name, t.Name, "Face%d" % (top_index(t) + 1))
    click(button("Design_Extrude"))


def reopen():
    path = os.environ["OUT"] + ".FCStd"
    doc().saveAs(path)
    App.closeDocument(doc().Name)
    App.openDocument(path)


run([("activate", activate), ("setup", setup), W, W,
     ("select", select_body), ("appearance", lambda: Gui.runCommand("Design_Appearance")), W,
     ("walnut", lambda: tile("Walnut")), W, ("ok", ok), W, ("remember", remember),
     # 1. Spiegeln
     ("select 2", select_body), ("mirror", lambda: click(button("Design_Mirror"))), W, W, ("ok mirror", ok), W, W,
     ("mirrored", new_bodies_walnut("mirrored copy")),
     # 2. Muster
     ("select 3", select_body), ("pattern", lambda: click(button("Design_Pattern"))), W, W, ("ok pattern", ok), W, W,
     ("patterned", new_bodies_walnut("pattern copies")),
     # 3. nur die Deckfläche bemalt
     ("paint top", paint_top), W, W, ("walnut 2", lambda: tile("Walnut")), W, ("ok 2", ok), W, ("faces", remember_faces),
     ("move", move_tile), W, W, ("x 20", lambda: type_into(0, "20 mm")), W, ("ok move", ok), W, W,
     ("moved", top_walnut("after moving the body")),
     ("extrude", extrude_top), W, W, ("distance", lambda: type_field("Distance", "5")), W, ("ok extrude", ok), W, W,
     ("extruded", top_walnut("after extruding it")),
     ("undo", lambda: Gui.runCommand("Std_Undo")), W, W,
     ("undone", top_walnut("after undoing the extrude")),
     ("redo", lambda: Gui.runCommand("Std_Redo")), W, W,
     ("redone", top_walnut("after redoing the extrude")),
     ("reopen", reopen), W, W, W,
     ("reopened", top_walnut("after saving and opening the file")),
     ("errors", lambda: check("no errors", not errors(), str(errors()))),
     ])
