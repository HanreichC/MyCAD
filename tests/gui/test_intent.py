# SPDX-License-Identifier: LGPL-2.1-or-later
"""Phase 11.10 Absicht statt Befehl: Strg+K, "4 Löcher M3 in die Ecken, 5 mm vom Rand" steht als erster Treffer da;
Enter öffnet die Bohrung mit ihrem Dialog (Vorschau), vier Mitten 5 mm von den Rändern der Oberseite, ISO-Durchgangsloch
M3 durch alles; OK übernimmt, Abbrechen nimmt alles zurück. Auch "Kanten 2 mm abrunden" (gewählte Kante) und "alle
Kanten 1 mm fasen" öffnen Rundung bzw. Fase mit dem Maß."""
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


def type_sentence(text=SENTENCE):
    Gui.runCommand("MyCAD_Search")
    f = field(); f.clear(); f.insert(text)  # keyClicks kann keine Umlaute (Qt-Assert)


def dress(kind):
    return [o for o in doc().Objects if o.TypeId == "Design::" + kind][-1]


def one_edge():
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(S["box"], "Edge1")


def first_hit(want):
    r = results()
    check("understood: " + want, bool(r) and r[0] == want, str(r[:3]))


def fillet_opened():
    f = dress("Fillet")
    check("Enter opens Fillet on the selected edge with 2 mm", Gui.Control.activeDialog() and list(f.Edges) == ["Edge1"]
          and abs(f.Size.Value - 2) < 1e-9, "edges=%s size=%s" % (list(f.Edges), f.Size))


def chamfer_opened():
    c = dress("Chamfer")
    check("all edges: Chamfer on each of the 12 edges with 1 mm", Gui.Control.activeDialog() and len(c.Edges) == 12
          and abs(c.Size.Value - 1) < 1e-9, "edges=%d size=%s" % (len(c.Edges), c.Size))


def cancel():
    click([b for b in visible(QtWidgets.QPushButton) if b.text().replace("&", "") == "Cancel"][0])


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
     ("edge", one_edge), ("fillet", lambda: type_sentence("Kanten 2 mm abrunden")), W,
     ("fillet hit", lambda: first_hit("Fillet the selected edges, 2 mm")),
     ("enter f", lambda: QtTest.QTest.keyClick(field(), QtCore.Qt.Key_Return)), W, W, ("fillet opened", fillet_opened),
     ("cancel f", cancel), W,
     ("none", lambda: Gui.Selection.clearSelection()), ("chamfer", lambda: type_sentence("alle Kanten 1 mm fasen")), W,
     ("chamfer hit", lambda: first_hit("Chamfer all edges, 1 mm")),
     ("enter c", lambda: QtTest.QTest.keyClick(field(), QtCore.Qt.Key_Return)), W, W, ("chamfer opened", chamfer_opened),
     ("cancel c", cancel), W,
     ("type", type_sentence), W, ("understood", understood),
     ("enter", lambda: QtTest.QTest.keyClick(field(), QtCore.Qt.Key_Return)), W, W, ("opened", opened),
     ("OK", ok), W, ("applied", applied),
     ("errors", lambda: check("no errors", not errors(), str(errors()))),
     ])
