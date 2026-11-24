# SPDX-License-Identifier: LGPL-2.1-or-later
"""Phase 13.6 Szenario E: eine kleine Baugruppe, wie ein Mensch sie baut. Grundplatte mit Bohrung; ein Arm als eigene
Komponente (neue Komponente, Skizze auf ihrer XY-Ebene, Extrude) mit Bohrung an einem Ende; Gelenk Bohrung auf
Bohrung, Typ Drehen; um 90° drehen; "Kollisionen zeigen" meldet, dass der Arm in der Platte steckt; mit Versatz liegt
er an der Platte an und die Meldung ist weg; speichern, neu öffnen: Gelenk und Lage bleiben. Jede Handlung gemessen."""
import math
import os
from harness import *
import Design

S = {}
W = ("wait", lambda: None)
V = App.Vector
FILE = os.environ["OUT"] + ".assembly.mycad"


def comp():
    return [o for o in doc().Objects if o.TypeId == "App::Part" and o.Type == "Component"][0]


def arm():
    return [o for o in doc().Objects if o.TypeId == "Design::Body" and o.Label != "Base"][0]


def joint():
    return [o for o in doc().Objects if o.TypeId == "Design::Joint"][0]


def hole_face(b, cx, cy):
    """die Wand der Bohrung (in die man klickt), nicht eine Deckfläche mit demselben Schwerpunkt"""
    return ["Face%d" % i for i, f in enumerate(b.Shape.Faces, 1) if f.Surface.TypeId == "Part::GeomCylinder"
            and abs(f.Surface.Center.x - cx) < 1e-6 and abs(f.Surface.Center.y - cy) < 1e-6][0]


def placed(b):
    s = b.Shape.copy()
    s.transformShape(comp().Placement.toMatrix())
    return s


def base():
    b = make_body(rect(0, 0, 60, 40), 0, 5, "Base")
    sk = Design.newSketch([o for o in doc().Objects if o.TypeId == "App::Part"][0])
    sk.addGeometry(Part.Circle(V(30, 20, 0), V(0, 0, 1), 2))
    doc().recompute()
    prof = [o for o in sk.InList if o.TypeId == "Design::Profiles"][0]
    f = doc().addObject("Design::Extrude", "Extrude"); comp_root = [o for o in doc().Objects if o.TypeId == "App::Part"][0]
    comp_root.addObject(f); Design.addToTimeline(f)
    f.Profile = (prof, ["Face1"]); f.Distance = 5; f.Operation = "Cut"
    Design.attachToBodies(f, [b])
    sk.Visibility = False
    doc().recompute()
    Gui.ActiveDocument.ActiveView.viewIsometric(); Gui.SendMsgToActiveView("ViewFit")


def new_component():
    click(button("Design_NewComponent"))


def arm_sketch():
    click(button("Design_CreateSketch"))
    QtCore.QTimer.singleShot(200, lambda: Gui.Selection.addSelection(
        [o for o in comp().Origin.OriginFeatures if o.Role == "XY_Plane"][0]))


def arm_shape():
    s = Gui.ActiveDocument.getInEdit().Object
    for g in rect(0, 0, 50, 10):
        s.addGeometry(g)
    s.addGeometry(Part.Circle(V(5, 5, 0), V(0, 0, 1), 2))
    doc().recompute()


def arm_extrude():
    prof = [o for o in doc().Objects if o.TypeId == "Design::Profiles"][-1]
    Gui.Selection.clearSelection()
    big = max(range(len(prof.Shape.Faces)), key=lambda k: prof.Shape.Faces[k].Area)
    Gui.Selection.addSelection(prof, "Face%d" % (big + 1))  # die Fläche mit dem Loch, nicht das Loch selbst
    click(button("Design_Extrude"))


def arm_ok():
    check("arm 50 x 10 x 4 with a hole, in its own component",
          abs(arm().Shape.Volume - (500 - math.pi * 4) * 4) < 0.5 and arm() in comp().OutListRecursive and not errors(),
          "%.1f %s" % (arm().Shape.Volume, errors()))


def make_joint():
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(doc().Name, arm().Name, hole_face(arm(), 5, 5))
    Gui.Selection.addSelection(doc().Name, body("Base").Name, hole_face(body("Base"), 30, 20))
    Gui.runCommand("Design_Joint")


def pick(label, text):
    box = field(label); box.setCurrentIndex(box.findText(text))


def coaxial():
    k = placed(arm())
    hole = [f for f in k.Faces if f.Surface.TypeId == "Part::GeomCylinder"]
    axis = hole[0].Surface.Center if hole else None
    z = placed(arm()).BoundBox
    check("revolute hole on hole: the arm's hole sits on the base's hole axis, in the middle of the hole",
          hole and abs(axis.x - 30) < 1e-6 and abs(axis.y - 20) < 1e-6 and abs(z.ZMin - 0.5) < 1e-6 and not errors(),
          "%s %s %s" % (axis, z, errors()))


def status():
    return " ".join(l.text() for l in visible(QtWidgets.QLabel) if "Collision" in l.text() or "touches" in l.text())


def turned():
    c = placed(arm()).BoundBox
    check("turned 90°: the arm points along y now", abs(c.YLength - 50) < 1e-3 and abs(c.XLength - 10) < 1e-3, str(c))


def colliding():
    check("Show collisions: the arm stuck in the base is reported", "Base" in status(), status())


def free():
    k = placed(arm()).BoundBox
    overlap = placed(arm()).common(body("Base").Shape).Volume
    # die Achse einer Bohrung zeigt nach oben oder unten (wie in Fusion: sonst Vorzeichen oder Flip)
    check("with an offset of 4.5 along the axis the arm lies against the base, no collision is left",
          overlap < 1e-6 and (abs(k.ZMin - 5) < 1e-6 or abs(k.ZMax) < 1e-6) and not status().strip(),
          "%s overlap %.3f / %s" % (k, overlap, status()))
    S["arm box"] = (round(k.XMin, 3), round(k.YMin, 3), round(k.ZMin, 3))


def save_reopen():
    doc().saveAs(FILE)
    name = doc().Name
    App.closeDocument(name)
    App.openDocument(FILE)


def same():
    k = placed(arm()).BoundBox
    check("saved and reopened: the joint keeps the arm where it was",
          (round(k.XMin, 3), round(k.YMin, 3), round(k.ZMin, 3)) == S["arm box"] and not errors(),
          "%s vs %s %s" % (k, S["arm box"], errors()))


run([("activate", activate), ("base", base), W,
     timed("new component", new_component, 500), W,
     ("arm sketch", arm_sketch), W, W, ("arm shape", arm_shape),
     ("leave", lambda: Gui.ActiveDocument.resetEdit()), W,
     timed("arm extrude opens", arm_extrude, 300), W, ("arm 4", lambda: type_field("Distance", "4")), W,
     ("arm OK", ok), W, ("arm ok", arm_ok),
     timed("joint hole on hole opens", make_joint, 500), W,
     ("revolute", lambda: pick("Type", "Revolute")), W, ("coaxial", coaxial),
     timed("turn 90", lambda: type_field("Angle", "90"), 500), W, ("turned", turned),
     ("collisions on", lambda: checkbox("Show collisions").click()), W, ("colliding", colliding),
     timed("offset 4.5 above", lambda: type_field("Offset", "4.5"), 500), W, W, ("free", free),
     ("OK joint", ok), W,
     timed("save, close, reopen", save_reopen, 1500), W, W, ("same", same),
     ("errors", lambda: check("no errors", not errors(), str(errors()))),
     ])
