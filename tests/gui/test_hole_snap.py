# SPDX-License-Identifier: LGPL-2.1-or-later
"""Phase 11.5 Bohrung per Klick zu Ende gedacht: der Klickpunkt fängt auf die Mitte der Fläche und auf Kreismitten,
sonst rundet er auf ein Raster, das zum Zoom passt (Aufräumliste E20: ein Schritt mindestens 6 px); Maße zu den zwei nächsten Kanten entstehen von selbst, der Punkt ist voll bestimmt.
Weitere Klicks bei offenem Dialog machen weitere Bohrungen, gleicher Randabstand bindet sie zu einer Reihe."""
from harness import *

S = {}
V = App.Vector
W = ("wait", lambda: None)


def click_3d(p):
    vp = view().viewport(); dpr = vp.devicePixelRatioF()
    x, y = Gui.ActiveDocument.ActiveView.getPointOnViewport(p)
    q = QtCore.QPoint(int(x / dpr), int(vp.height() - y / dpr))
    QtTest.QTest.mouseMove(vp, q); QtTest.QTest.mouseClick(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, q)


def setup():
    S["box"] = make_body(rect(0, 0, 40, 20), 0, 20, "Box")
    S["pin"] = make_body([Part.Circle(App.Vector(60, 10, 0), App.Vector(0, 0, 1), 4)], 0, 20, "Pin")
    v = Gui.ActiveDocument.ActiveView; v.viewIsometric(); Gui.SendMsgToActiveView("ViewFit"); v.zoomOut()


def hole():
    Gui.Selection.clearSelection(); click(button("Design_Hole"))


def placed():
    """Lage (global), Maße und Deckungen der einen offenen Bohrung"""
    h = [o for o in doc().Objects if o.TypeId == "Design::Hole"][-1]
    sk = h.Sketch
    pt = [sk.Placement.multVec(V(g.X, g.Y, g.Z)) for g in sk.Geometry if g.TypeId == "Part::GeomPoint"][0]
    dims = sorted(round(c.Value, 6) for c in sk.Constraints if c.Type == "Distance")
    return pt, dims, [c.Type for c in sk.Constraints], sk.solve()


def expect(tag, at, dims, kinds=None):
    pt, got, types, solved = placed()
    check(tag, (pt - at).Length < 1e-6 and got == dims and (kinds is None or types == kinds) and solved == 0,
          "point=%s dims=%s types=%s solve=%s" % (pt, got, types, solved))


def grid(direction):
    """Raster je Richtung wie in dimensionHolePoint: der kleinste Schritt, der in der Ansicht mindestens 6 px misst"""
    v = Gui.ActiveDocument.ActiveView
    a, b = v.getPointOnViewport(V(7.3, 4.8, 20)), v.getPointOnViewport(V(7.3, 4.8, 20) + direction * 10)
    px = ((a[0] - b[0]) ** 2 + (a[1] - b[1]) ** 2) ** 0.5 / 10
    return next((g for g in (0.1, 0.2, 0.5, 1.0, 2.0, 5.0) if g * px >= 6), 10.0)


def rounded():
    """geklickt bei (7,3 | 4,8): auf das Raster des Zooms nahe daran, je Richtung eigenes Raster (schräg gesehen)"""
    pt, dims, types, solved = placed()
    gx, gy = grid(V(1, 0, 0)), grid(V(0, 1, 0))
    on = lambda d, g: abs(d / g - round(d / g)) < 1e-6
    on_grid = on(dims[1], gx) and on(dims[0], gy) and abs(pt.x - dims[1]) < 1e-9 and abs(pt.y - dims[0]) < 1e-9
    near = abs(pt.x - 7.3) <= gx / 2 + 1e-6 and abs(pt.y - 4.8) <= gy / 2 + 1e-6
    check("elsewhere it rounds to a grid that fits the zoom, dimensioned to the two nearest edges",
          types == ["Distance", "Distance"] and on_grid and near and solved == 0,
          "point=%s dims=%s grid=%s/%s types=%s solve=%s" % (pt, dims, gx, gy, types, solved))


def row():
    """zweiter Klick bei offenem Dialog: zweite Bohrung; gleicher Abstand zur vorderen Kante -> an das erste Maß gebunden"""
    h = [o for o in doc().Objects if o.TypeId == "Design::Hole"][-1]
    sk = h.Sketch
    pts = [sk.Placement.multVec(V(g.X, g.Y, g.Z)) for g in sk.Geometry if g.TypeId == "Part::GeomPoint"]
    bound = [str(e) for _, e in sk.ExpressionEngine]
    check("a second click in the open dialog adds a second hole in the same row, its edge distance bound to the first",
          len(pts) == 2 and abs(pts[0].y - pts[1].y) < 1e-9 and any("Row" in e for e in bound)
          and abs(S["box"].Shape.Volume - (16000 - 2 * 3.14159265 * 2.5 ** 2 * 8)) < 0.05,
          "points=%s expressions=%s volume=%.3f" % (pts, bound, S["box"].Shape.Volume))
    name = [c.Name for c in sk.Constraints if c.Name.startswith("Row")][0]
    sk.setDatum(name, App.Units.Quantity("6 mm")); doc().recompute()
    pts = [sk.Placement.multVec(V(g.X, g.Y, g.Z)) for g in sk.Geometry if g.TypeId == "Part::GeomPoint"]
    check("changing the first distance moves the whole row", all(abs(p.y - 6) < 1e-6 for p in pts), str(pts))


def cancel():
    click([b for b in visible(QtWidgets.QPushButton) if b.text().replace("&", "") == "Cancel"][0])


run([("activate", activate), ("setup", setup), W,
     ("hole 1", hole), W, ("near middle", lambda: click_3d(V(20.4, 9.7, 20))), W, W,
     ("middle", lambda: expect("a click near the middle of the face snaps there, with 10 and 20 mm to the edges",
                               V(20, 10, 20), [10.0, 20.0])),
     ("shot", lambda: shot("middle")),
     ("cancel 1", cancel), W,
     ("hole 2", hole), W, ("off", lambda: click_3d(V(7.3, 4.8, 20))), W, W,
     ("rounded", rounded),
     ("depth", lambda: (setattr([o for o in doc().Objects if o.TypeId == "Design::Hole"][-1], "Depth", 8), doc().recompute())), W,
     ("volume", lambda: check("the hole drills there", abs(S["box"].Shape.Volume - (16000 - 3.14159265 * 2.5 ** 2 * 8)) < 0.05,
                              "%.3f" % S["box"].Shape.Volume)),
     ("second", lambda: click_3d(V(25.3, 4.8, 20))), W, W, ("row", row),
     ("ok", ok), W,
     ("hole 3", hole), W, ("pin", lambda: click_3d(V(60.6, 10.4, 20))), W, W,
     ("new", lambda: check("the next Hole waits for a click instead of reusing the hidden sketch of the last one",
                           len([o for o in doc().Objects if o.TypeId == "Design::Hole"]) == 2 and placed()[0].x > 50,
                           str(placed()))),
     ("centre", lambda: expect("on a round face it snaps onto the centre of the circle", V(60, 10, 20), [], ["Coincident"])),
     ("ok 3", ok), W,
     ("errors", lambda: check("no errors", not errors(), str(errors()))),
     ])
