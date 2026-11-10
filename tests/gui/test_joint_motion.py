# SPDX-License-Identifier: LGPL-2.1-or-later
"""L6 im Dialog: Gelenktyp mit passenden Feldern, Grenzen, Animieren bleibt in den Grenzen, Kollision als Text"""
from harness import *
import Design

state = {}


def setup():
    d = doc()
    a = make_body(rect(0, 0, 10, 10), 0, 10, "Base")
    comp = Design.newComponent(Design.root(d))
    sk = Design.newSketch(comp)
    for g in rect(0, 0, 10, 10):
        sk.addGeometry(g)
    d.recompute()
    prof = [o for o in sk.InList if o.TypeId == "Design::Profiles"][0]
    f = d.addObject("Design::Extrude", "Extrude"); comp.addObject(f); Design.addToTimeline(f)
    f.Profile = (prof, ["Face1"]); f.Distance = 2
    b = Design.newBody(f); b.Label = "Slider"
    d.recompute()
    bottom = "Face%d" % (1 + min(range(len(b.Shape.Faces)), key=lambda k: b.Shape.Faces[k].CenterOfMass.z))
    j = d.addObject("Design::Joint", "Joint")
    j.Moving = comp; j.Origin1 = (b, [bottom]); j.Origin2 = (a, [top_face(a)])
    d.recompute()
    comp.setExpression("Placement", j.Name + ".Result")
    d.recompute()
    state.update(joint=j, comp=comp)


def pick(label, text):
    box = field(label); box.setCurrentIndex(box.findText(text))


def status():
    return " ".join(l.text() for l in visible(QtWidgets.QLabel) if "Collision" in l.text() or "touches" in l.text())


run([
    ("setup", setup),
    ("edit", lambda: Gui.ActiveDocument.setEdit(state["joint"])),
    ("slider", lambda: pick("Type", "Slider")),
    ("rows", lambda: check("slider shows offset, not angle", shown("Offset") and not shown("Angle"))),
    ("limits on", lambda: checkbox("Keep angle and distance within limits").click()),
    ("limit rows", lambda: check("offset limits appear", shown("Offset min") and shown("Offset max") and not shown("Angle max"))),
    ("max", lambda: type_field("Offset max", "4")),
    ("animate", lambda: [b for b in visible(QtWidgets.QPushButton) if b.text() == "Animate"][0].click()),
    # mehrere Stichproben: unter Last kann eine einzelne genau auf der unteren Grenze 0 liegen
    ("sample 1", lambda: state.setdefault("samples", []).append(state["joint"].Offset.Value)),
    ("sample 2", lambda: state["samples"].append(state["joint"].Offset.Value)),
    ("sample 3", lambda: state["samples"].append(state["joint"].Offset.Value)),
    ("moving", lambda: check("animation moves within the limits",
                             max(state["samples"]) > 0 and all(0 <= v <= 4 + 1e-9 for v in state["samples"]),
                             str(state["samples"]))),
    ("stop", lambda: [b for b in visible(QtWidgets.QPushButton) if b.text() == "Stop"][0].click()),
    ("collisions on", lambda: checkbox("Show collisions").click()),
    ("min", lambda: type_field("Offset min", "-3")),
    ("into base", lambda: type_field("Offset", "-3")),
    ("collision", lambda: check("collision is reported by name", "Slider" in status() and "Base" in status(), status())),
    ("planar", lambda: pick("Type", "Planar")),
    ("planar rows", lambda: check("planar shows offset 2 and angle", shown("Offset 2") and shown("Angle"))),
    ("shot", lambda: shot("joint")),
    ("ok", ok),
])
