# SPDX-License-Identifier: LGPL-2.1-or-later
"""Replace Face (Oberseite auf höhere Fläche), Split Face (an der XZ-Ebene), Emboss/Deboss (Kreis r=5, 1 mm)."""
import math
from harness import *

state = {}


def faces(b, pred):
    return ["Face%d" % (i + 1) for i, f in enumerate(b.Shape.Faces) if pred(f)]


def top(b):
    z = b.Shape.BoundBox.ZMax
    return faces(b, lambda f: abs(f.CenterOfMass.z - z) < 1e-6 and abs(abs(f.normalAt(0, 0).z) - 1) < 1e-6)[0]


def sel(*pairs):
    Gui.Selection.clearSelection()
    for obj, sub in pairs:
        if sub:
            Gui.Selection.addSelection(doc().Name, obj.Name, sub)
        else:
            Gui.Selection.addSelection(obj)


def messages():
    for m in visible(QtWidgets.QMessageBox):
        L("  message: %s" % m.text()); m.close()


def later(cmd):
    QtCore.QTimer.singleShot(700, messages); Gui.runCommand(cmd)


def emboss_sketch():
    d = doc(); root = [o for o in d.Objects if o.TypeId == "App::Part"][0]
    sk = d.addObject("Sketcher::SketchObject", "Text"); sk.Placement.Base.z = 20
    sk.addGeometry(Part.Circle(App.Vector(320, 15, 0), App.Vector(0, 0, 1), 5))
    [o for o in d.Objects if o.Label == "Sketches"][0].addObject(sk)
    prof = d.addObject("Design::Profiles", "Profiles"); prof.Sketch = sk; root.addObject(prof)
    d.recompute(); state["prof"] = prof


run([
    ("setup", lambda: (make_body(rect(0, 0, 60, 40), 0, 15, "A"), make_body(rect(100, 0, 120, 20), 0, 25, "B"),
                       make_body(rect(200, -10, 220, 10), 0, 10, "C"), make_body(rect(300, 0, 340, 30), 0, 10, "D"))),
    ("replace sel", lambda: sel((body("A"), top(body("A"))), (body("B"), top(body("B"))))),
    ("replace", lambda: later("Design_ReplaceFace")),
    ("replace?", lambda: L("replace: A volume=%.0f height=%.0f (erwartet 60000, 25) errors=%s" % (
        body("A").Shape.Volume, body("A").Shape.BoundBox.ZLength, errors()))),
    ("split sel", lambda: sel((body("C"), top(body("C"))), ([o for o in doc().Objects if o.Name.startswith("XZ_Plane")][0], None))),
    ("split", lambda: later("Design_SplitFace")),
    ("split?", lambda: L("split face: C faces=%d (erwartet 7) volume=%.0f (4000) errors=%s" % (
        len(body("C").Shape.Faces), body("C").Shape.Volume, errors()))),
    ("emboss sketch", emboss_sketch),
    ("emboss sel", lambda: sel((state["prof"], "Face1"), (body("D"), top(body("D"))))),
    ("emboss", lambda: Gui.runCommand("Design_Emboss")), ("shot", lambda: shot("emboss")), ("ok", ok),
    ("emboss?", lambda: L("emboss: D volume=%.1f (erwartet %.1f) errors=%s" % (
        body("D").Shape.Volume, 12000 + math.pi * 25, errors()))),
    ("deboss", lambda: (setattr([o for o in doc().Objects if o.TypeId == "Design::Emboss"][0], "Type", "Deboss"), doc().recompute())),
    ("deboss?", lambda: L("deboss: D volume=%.1f (erwartet %.1f) errors=%s" % (
        body("D").Shape.Volume, 12000 - math.pi * 25, errors()))),
])
