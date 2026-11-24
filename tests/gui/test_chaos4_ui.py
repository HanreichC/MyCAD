# SPDX-License-Identifier: LGPL-2.1-or-later
"""Phase 14, Chaos 4: die Grundskizze drastisch ändern, wenn längst Schritte darauf aufbauen. Alles löschen und einen
Kreis zeichnen (als Befehl und in der offenen Skizze); die Platte auf 5 x 5 mm schrumpfen (die Rundung mit 6 mm passt
nicht mehr); die Grundskizze drehen.
Erwartet: verständliche Warnungen oder Fehler statt Absturz, kein Abhängigkeitskreis, und Rückgängig stellt genau
wieder her."""
import os
import sys
from harness import *
sys.path.insert(0, os.path.join(os.path.dirname(os.environ["SCRIPT"]), "..", "design"))
import design as D
import Design
import Sketcher

S = {}
W = ("wait", lambda: None)
V = App.Vector


def vol():
    return round(S["body"].Shape.Volume, 2) if not S["body"].Shape.isNull() else 0


def build():
    d = doc()
    base = D.sketch(d, D.rect(0, 0, 80, 50))
    C = Sketcher.Constraint
    for c in [C("Coincident", i, 2, (i + 1) % 4, 1) for i in range(4)] + [
            C("Horizontal", 0), C("Horizontal", 2), C("Vertical", 1), C("Vertical", 3), C("Coincident", 0, 1, -1, 1),
            C("DistanceX", 0, 1, 0, 2, 80), C("DistanceY", 1, 1, 1, 2, 50)]:
        base.addConstraint(c)
    d.recompute()
    _, b = D.extrude(d, base, 10)
    e = D.edge_where(b, lambda p: abs(p.x) < 1e-6 and abs(p.y) < 1e-6 and abs(p.z - 5) < 1e-6)
    D.dress(d, "Design::Fillet", b, [e], Size=6)
    top = D.edge_where(b, lambda p: abs(p.y - 50) < 1e-6 and abs(p.z - 10) < 1e-6)
    D.dress(d, "Design::Chamfer", b, [top], Size=1)
    hole = D.sketch(d, D.circle(60, 25, 5), support=(b, D.top_face(b)))
    D.extrude(d, hole, 10, op="Cut", bodies=[b], Reversed=True)
    for o in d.Objects:
        if o.TypeId in ("Sketcher::SketchObject", "Design::Profiles"):
            o.Visibility = False
    d.recompute()
    S.update(body=b, base=base, full=None)
    S["full"] = vol()
    Gui.ActiveDocument.ActiveView.viewIsometric(); Gui.SendMsgToActiveView("ViewFit")


def state(where):
    def f():
        problems = D.model_problems(doc())
        check("%s: no dependency cycle, nothing left to recompute" % where, not problems, str(problems))
        L("  %s: volume %.2f, problems %s" % (where, vol(), [(o.Label, t[:70]) for o, t in Design.problems(doc())]))
    return f


def change(name, fn):
    def f():
        doc().openTransaction(name)  # wie ein Befehl: ändern und neu rechnen in der Transaktion
        fn(S["base"])
        doc().recompute()
        doc().commitTransaction()
    return f


def to_circle(s):
    s.deleteAllGeometry()
    s.addGeometry(Part.Circle(V(40, 25, 0), V(0, 0, 1), 20))


def tiny(s):
    i = [k for k, c in enumerate(s.Constraints) if c.Type == "DistanceX"][0]
    j = [k for k, c in enumerate(s.Constraints) if c.Type == "DistanceY"][0]
    s.setDatum(i, App.Units.Quantity("5 mm"))
    s.setDatum(j, App.Units.Quantity("5 mm"))


def turn(s):
    s.Placement = App.Placement(V(0, 0, 0), App.Rotation(V(0, 0, 1), 30))


def undo_back(where):
    def f():
        Gui.runCommand("Std_Undo")
    return f


def restored(where):
    def f():
        check("%s, then undo: the part as built, nothing red" % where, abs(vol() - S["full"]) < 0.01 and not Design.problems(doc()),
              "%s vs %s %s" % (vol(), S["full"], [(o.Label, t[:60]) for o, t in Design.problems(doc())]))
    return f


steps = [("activate", activate), ("build", build), W, W, ("start", state("start"))]
for name, fn in (("rectangle replaced by a circle", to_circle), ("plate 5 x 5 (fillet 6 no longer fits)", tiny),
                 ("base sketch turned 30 degrees", turn)):
    steps += [(name, change(name, fn)), W, W, ("state " + name, state(name)),
              ("undo " + name, undo_back(name)), W, W, ("restored " + name, restored(name))]


def in_sketch_to_circle():
    s = Gui.ActiveDocument.getInEdit().Object
    doc().openTransaction("Delete")  # wie Entf und das Kreis-Werkzeug: je eine Transaktion
    s.deleteAllGeometry()
    doc().commitTransaction()
    doc().openTransaction("Add sketch circle")
    s.addGeometry(Part.Circle(V(40, 25, 0), V(0, 0, 1), 20))
    doc().commitTransaction()
    doc().recompute()


def undo_n(n):
    return lambda: [Gui.runCommand("Std_Undo") for _ in range(n)]


steps += [("edit base", lambda: Gui.ActiveDocument.setEdit(S["base"].Name)), W, W, ("in sketch", in_sketch_to_circle), W,
          ("leave", lambda: Gui.ActiveDocument.resetEdit()), W, W, W, ("state ui", state("in the sketch: rectangle -> circle")),
          ("undo ui", undo_n(3)),
          W, W, ("restored ui", restored("in the sketch: rectangle -> circle"))]
run(steps)
