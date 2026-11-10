# SPDX-License-Identifier: LGPL-2.1-or-later
"""L1 im Dialog: Extrude "Bis Objekt" (Bezugsknopf wartet von selbst), Verjüngung, dünne Wand"""
from harness import *

state = {}


def setup():
    state["roof"] = make_body(rect(-5, -5, 25, 25), 10, 2, "Roof")
    d = doc(); root = [o for o in d.Objects if o.TypeId == "App::Part"][0]
    import Design
    sk = Design.newSketch(root)
    for g in rect(0, 0, 10, 10):
        sk.addGeometry(g)
    d.recompute()
    state["sketch"] = sk


def start_extrude():
    prof = [o for o in state["sketch"].InList if o.TypeId == "Design::Profiles"][0]
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(prof, "Face1")
    click(button("Design_Extrude"))


def pick_bottom_of_roof():
    roof = state["roof"]
    face = "Face%d" % (1 + min(range(len(roof.Shape.Faces)), key=lambda k: roof.Shape.Faces[k].CenterOfMass.z))
    Gui.Selection.addSelection(roof, face)


def ref_button():
    return [b for b in visible(QtWidgets.QPushButton) if b.isCheckable()]


def check_to_object():
    f = [o for o in doc().Objects if o.TypeId == "Design::Extrude"][-1]
    state["f"] = f
    check("to object linked", f.ToObject[0] is not None, str(f.ToObject))
    body = [b for b in doc().Objects if b.TypeId == "Design::Body" and b.Tip == f]
    check("volume up to roof", body and abs(body[0].Shape.Volume - 1000) < 1, str(body and body[0].Shape.Volume))


run([
    ("setup", setup),
    ("extrude", start_extrude),
    ("to object", lambda: choose("To Object", 3)),
    ("button waits", lambda: check("reference button waits", any(b.isChecked() for b in ref_button()),
                                   str([(b.text(), b.isChecked()) for b in ref_button()]))),
    ("pick", pick_bottom_of_roof),
    ("shot", lambda: shot("toobject")),
    ("check", check_to_object),
    ("ok", ok),
    ("errors", lambda: check("no errors", not errors(), str(errors()))),
    ("edit again", lambda: check("dialog opens again", Gui.ActiveDocument.setEdit(state["f"]))),
    ("one side", lambda: choose("One Side", 0)),
    ("distance", lambda: type_field("Distance", "10")),
    ("type taper", lambda: type_field("Taper Angle", "10")),
    ("shot taper", lambda: shot("taper")),
    ("taper set", lambda: check("taper applied", abs(state["f"].TaperAngle.Value - 10) < 1e-6, str(state["f"].TaperAngle))),
    ("thin", lambda: checkbox("Thin wall").click()),
    ("thin set", lambda: check("thin wall on", state["f"].Thin, str([(c.text(), c.isChecked()) for c in visible(QtWidgets.QCheckBox)]))),
    ("thickness shown", lambda: check("thickness row shown", field("Thickness").isVisible())),
    ("ok2", ok),
    ("errors2", lambda: check("no errors after taper and thin", not errors(), str(errors()))),
])
