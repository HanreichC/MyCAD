# SPDX-License-Identifier: LGPL-2.1-or-later
"""Phase 11.10 Absicht statt Befehl: Strg+K, "4 Löcher M3 in die Ecken, 5 mm vom Rand" steht als erster Treffer da;
Enter öffnet die Bohrung mit ihrem Dialog (Vorschau), vier Mitten 5 mm von den Rändern der Oberseite, ISO-Durchgangsloch
M3 durch alles; OK übernimmt, Abbrechen nimmt alles zurück."""
from harness import *

S = {}
W = ("wait", lambda: None)
SENTENCE = "4 Löcher M3 in die Ecken, 5 mm vom Rand"


def field():
    return [e for e in visible(QtWidgets.QLineEdit) if e.accessibleName() == "Search"][0]


def results():
    lists = [l for l in visible(QtWidgets.QListWidget) if l.accessibleName() == "Results"]
    return [lists[0].item(i).data(QtCore.Qt.AccessibleTextRole) for i in range(lists[0].count())] if lists else []


def setup():
    S["box"] = make_body(rect(0, 0, 40, 30), 0, 10, "Plate")
    Gui.ActiveDocument.ActiveView.viewIsometric(); Gui.SendMsgToActiveView("ViewFit")


def type_sentence():
    Gui.runCommand("MyCAD_Search")
    f = field(); f.clear(); f.insert(SENTENCE)  # keyClicks kann keine Umlaute (Qt-Assert)


def understood():
    r = results()
    check("the sentence is understood and comes first", bool(r) and r[0] == "Drill 4 × M3 holes in the corners, 5 mm from the edge", str(r[:3]))


def hole():
    return [o for o in doc().Objects if o.TypeId == "Design::Hole"][-1]


def opened():
    h = hole()
    pts = sorted((round(p.x, 6), round(p.y, 6)) for p in
                 [h.Sketch.Placement.multVec(App.Vector(g.X, g.Y, g.Z)) for g in h.Sketch.Geometry if g.TypeId == "Part::GeomPoint"])
    check("Enter opens the hole with its dialog: four centres 5 mm from the edges, M3 clearance, through all",
          Gui.Control.activeDialog() and pts == [(5, 5), (5, 25), (35, 5), (35, 25)] and h.Size.startswith("M3x")
          and h.Kind == "Clearance hole" and h.ThroughAll and h.Sketch.solve() == 0,
          "points=%s size=%s kind=%s through=%s" % (pts, h.Size, h.Kind, h.ThroughAll))
    shot("preview")


def applied():
    d = hole().Diameter.Value
    want = 12000 - 4 * 3.14159265 * (d / 2) ** 2 * 10
    check("OK drills the four holes", abs(S["box"].Shape.Volume - want) < 0.05 and 3 < d < 4,
          "volume=%.2f want=%.2f diameter=%.2f" % (S["box"].Shape.Volume, want, d))


run([("activate", activate), ("setup", setup), W,
     ("type", type_sentence), W, ("understood", understood),
     ("enter", lambda: QtTest.QTest.keyClick(field(), QtCore.Qt.Key_Return)), W, W, ("opened", opened),
     ("OK", ok), W, ("applied", applied),
     ("errors", lambda: check("no errors", not errors(), str(errors()))),
     ])
