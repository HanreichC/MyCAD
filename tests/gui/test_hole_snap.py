# SPDX-License-Identifier: LGPL-2.1-or-later
"""Phase 11.5 Bohrung per Klick zu Ende gedacht: der Klickpunkt fängt auf die Mitte der Fläche und auf Kreismitten,
sonst rundet er auf 0,5 mm; Maße zu den zwei nächsten Kanten entstehen von selbst, der Punkt ist voll bestimmt."""
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


def rounded():
    """ein Pixel ist hier gut 0,2 mm: geklickt bei (7,3 | 4,8), gemessen auf ein 0,5-mm-Raster nahe daran"""
    pt, dims, types, solved = placed()
    on_grid = all(abs(d * 2 - round(d * 2)) < 1e-9 for d in dims) and abs(pt.x - dims[1]) < 1e-9 and abs(pt.y - dims[0]) < 1e-9
    check("elsewhere it rounds to 0.5 mm, dimensioned to the two nearest edges",
          types == ["Distance", "Distance"] and on_grid and (pt - V(7.3, 4.8, 20)).Length < 0.6 and solved == 0,
          "point=%s dims=%s types=%s solve=%s" % (pt, dims, types, solved))


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
     ("ok", ok), W,
     ("hole 3", hole), W, ("pin", lambda: click_3d(V(60.6, 10.4, 20))), W, W,
     ("new", lambda: check("the next Hole waits for a click instead of reusing the hidden sketch of the last one",
                           len([o for o in doc().Objects if o.TypeId == "Design::Hole"]) == 2 and placed()[0].x > 50,
                           str(placed()))),
     ("centre", lambda: expect("on a round face it snaps onto the centre of the circle", V(60, 10, 20), [], ["Coincident"])),
     ("ok 3", ok), W,
     ("errors", lambda: check("no errors", not errors(), str(errors()))),
     ])
