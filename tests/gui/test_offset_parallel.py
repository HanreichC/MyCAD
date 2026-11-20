# SPDX-License-Identifier: LGPL-2.1-or-later
"""Versatz wie in Fusion an das Original gebunden: Seiten parallel plus Abstandsmaß. Vorher hing die Kopie nur an
ihren Ecken; änderte man danach ein Maß des Originals, drehte der Solver ihre Seiten schief."""
from harness import *
import Sketcher

S = {}
W = ("wait", lambda: None)


def sketch():
    return Gui.ActiveDocument.getInEdit().Object


def move(fx, fy):
    v = view(); QtTest.QTest.mouseMove(v.viewport(), QtCore.QPoint(int(v.width() * fx), int(v.height() * fy)))


def shapes():
    s = sketch()
    for g in rect(-30, -15, 30, 15):
        s.addGeometry(g)
    for i in range(4):
        s.addConstraint(Sketcher.Constraint("Coincident", i, 2, (i + 1) % 4, 1))
    for i, kind in enumerate(("Horizontal", "Vertical", "Horizontal", "Vertical")):
        s.addConstraint(Sketcher.Constraint(kind, i))
    S["width"] = s.addConstraint(Sketcher.Constraint("DistanceX", 0, 1, 0, 2, 60.0))
    doc().recompute(); Gui.SendMsgToActiveView("ViewFit")


def select():
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(doc().Name, sketch().Name, "Edge1")


def offset():
    """Versatz (Knopf ist erst kurz nach der Auswahl aktiv), Klick innen zwischen Mitte und Rand"""
    click(button("Sketcher_Offset"))
    QtCore.QTimer.singleShot(300, lambda: move(0.49, 0.49))
    QtCore.QTimer.singleShot(600, lambda: move(0.5, 0.5 - 0.06))
    QtCore.QTimer.singleShot(900, lambda: view_click(0.5, 0.5 - 0.06))


def lines():
    return [(i, g) for i, g in enumerate(sketch().Geometry)
            if g.TypeId == "Part::GeomLineSegment" and i >= 4 and not sketch().getConstruction(i)]


def widen():
    S["lines"] = len(lines())
    L("constraints after offset: %s" % sorted({c.Type for c in sketch().Constraints}))
    sketch().setDatum(S["width"], App.Units.Quantity("80 mm")); doc().recompute()


def straight():
    skew = [round(min(abs(g.EndPoint.x - g.StartPoint.x), abs(g.EndPoint.y - g.StartPoint.y)), 4) for _, g in lines()]
    xs = [v for _, g in lines() for v in (g.StartPoint.x, g.EndPoint.x)]
    check("offset copy has 4 lines", S["lines"] == 4, str(S["lines"]))
    check("the offset copy stays straight and follows the original when its width changes",
          all(d < 1e-6 for d in skew) and max(xs) - min(xs) > 60, "skew=%s width=%.2f" % (skew, max(xs) - min(xs)))
    check("no errors", not errors(), str(errors()))


run([
    ("Create Sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick XY", lambda: Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XY_Plane")][0])),
    W, ("shapes", shapes), W, ("select", select), W, ("offset", offset), W, W, ("after", lambda: shot("after")), ("widen", widen), W, ("straight", straight),
    ("shot", lambda: shot("offset")),
])
