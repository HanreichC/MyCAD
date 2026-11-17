# SPDX-License-Identifier: LGPL-2.1-or-later
"""Phase 11.8 in der Oberfläche: Block A im Design, darauf Block B in einer eigenen Komponente (um 10 mm hoch
verschoben). Kreis auf die Oberseite von B, Extrude 20 mm nach unten: der automatische Cut geht durch B und auch durch A
in der anderen Komponente. Ein neues Teil, das nur Körper fremder Komponenten überlappt, bleibt ein eigener Körper."""
from harness import *
import Design

S = {}
W = ("wait", lambda: None)
PI = 3.141592653589793


def setup():
    S["A"] = make_body(rect(0, 0, 20, 20), 0, 10, "A")
    comp = Design.newComponent(Design.root(doc()))
    comp.Placement = App.Placement(App.Vector(0, 0, 10), App.Rotation())
    sk = Design.newSketch(comp)
    for g in rect(0, 0, 20, 20):
        sk.addGeometry(g)
    doc().recompute()
    prof = [o for o in sk.InList if o.TypeId == "Design::Profiles"][0]
    f = doc().addObject("Design::Extrude", "Extrude"); comp.addObject(f); Design.addToTimeline(f)
    f.Profile = (prof, ["Face1"]); f.Distance = 10
    S["B"] = Design.newBody(f); S["B"].Label = "B"
    sk.Visibility = False; prof.Visibility = False
    doc().recompute()
    v = Gui.ActiveDocument.ActiveView; v.viewIsometric(); Gui.SendMsgToActiveView("ViewFit")


def circle_on_top():
    sk = Gui.ActiveDocument.getInEdit().Object
    centre = sk.getGlobalPlacement().inverse().multVec(App.Vector(10, 10, 20))  # Mitte der Oberseite von B (global)
    sk.addGeometry(Part.Circle(App.Vector(centre.x, centre.y, 0), App.Vector(0, 0, 1), 3))
    doc().recompute()


def cut_both():
    e = [o for o in doc().Objects if o.TypeId == "Design::Extrude"][-1]
    hole = PI * 9 * 10
    check("the automatic cut goes through B and also through A in the other component",
          e.Operation == "Cut" and sorted(b.Label for b in e.Bodies) == ["A", "B"]
          and abs(S["A"].Shape.Volume - (4000 - hole)) < 0.01 and abs(S["B"].Shape.Volume - (4000 - hole)) < 0.01,
          "op=%s bodies=%s A=%.2f B=%.2f" % (e.Operation, [b.Label for b in e.Bodies], S["A"].Shape.Volume, S["B"].Shape.Volume))
    shot("cut")


run([("activate", activate), ("setup", setup), W,
     ("Create Sketch", lambda: click(button("Design_CreateSketch"))), W,
     ("pick top of B", lambda: Gui.Selection.addSelection(S["B"], top_face(S["B"]))), W,
     ("circle", circle_on_top), ("finish", lambda: click(button("Sketcher_LeaveSketch"))), W,
     ("Extrude", lambda: click(button("Design_Extrude"))), W,
     ("down 20", lambda: type_field("Distance", "-20")), W, W,
     ("OK", ok), W, ("cut both", cut_both),
     ("errors", lambda: check("no errors", not errors(), str(errors()))),
     ])
