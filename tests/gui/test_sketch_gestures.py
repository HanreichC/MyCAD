# SPDX-License-Identifier: LGPL-2.1-or-later
"""12.12 Gesten mit dem Stift in einer offenen Skizze: Durchkritzeln löscht die Geometrie darunter (eine Transaktion),
ein Häkchen schließt die Skizze"""
from harness import *
import Design

S = {}
W = ("wait", lambda: None)
_pen = []


def tablet(kind, x, y, button, buttons):
    if not _pen:
        _pen.append(QtGui.QPointingDevice("pen", 18, QtGui.QInputDevice.DeviceType.Stylus, QtGui.QPointingDevice.PointerType.Pen,
                                          QtGui.QInputDevice.Capability.Position | QtGui.QInputDevice.Capability.Pressure, 1, 3))
    vp = view().viewport(); p = QtCore.QPointF(x, y)
    e = QtGui.QTabletEvent(kind, _pen[0], p, vp.mapToGlobal(p), .6, 0, 0, 0, 0, 0, QtCore.Qt.NoModifier, button, buttons)
    QtWidgets.QApplication.sendEvent(vp, e)
    return e.isAccepted()


def at(fx, fy):
    v = view().viewport(); return v.width() * fx, v.height() * fy


def dense(poly, n=12):
    out = [poly[0]]
    for (x0, y0), (x1, y1) in zip(poly, poly[1:]):
        out += [(x0 + (x1 - x0) * k / n, y0 + (y1 - y0) * k / n) for k in range(1, n + 1)]
    return out


def stroke(points):
    L_, N = QtCore.Qt.LeftButton, QtCore.Qt.NoButton
    tablet(QtCore.QEvent.TabletPress, *points[0], L_, L_)
    for x, y in points[1:]:
        tablet(QtCore.QEvent.TabletMove, x, y, N, L_)
    tablet(QtCore.QEvent.TabletRelease, *points[-1], L_, N)


def setup():
    d = doc(); root = [o for o in d.Objects if o.TypeId == "App::Part"][0]
    sk = S["sk"] = Design.newSketch(root)
    pts =[App.Vector(-20, -10, 0), App.Vector(20, -10, 0), App.Vector(20, 10, 0), App.Vector(-20, 10, 0)]
    for i in range(4):
        sk.addGeometry(Part.LineSegment(pts[i], pts[(i + 1) % 4]))
    d.recompute()
    Gui.ActiveDocument.setEdit(sk)


def view_point(p):
    """Skizzenpunkt -> Pixel im Viewport"""
    v = Gui.ActiveDocument.ActiveView; vp = view().viewport(); dpr = vp.devicePixelRatioF()
    x, y = v.getPointOnViewport(S["sk"].getGlobalPlacement().multVec(p))
    return x / dpr, vp.height() - y / dpr


def scratch():
    """hin und her über die Mitte der oberen Kante (y = 10), die Seiten bleiben außerhalb"""
    a, b = view_point(App.Vector(-8, 10, 0)), view_point(App.Vector(8, 10, 0))
    zig = [(a[0] if i % 2 == 0 else b[0], a[1] - 6 + i * 2) for i in range(7)]
    S["before"] = len(S["sk"].Geometry)
    stroke(dense(zig))


def erased():
    g = S["sk"].Geometry
    check("scratching over the top edge deletes it, the others stay",
          len(g) == S["before"] - 1 and all(abs(l.StartPoint.y - 10) > 1e-6 or abs(l.EndPoint.y - 10) > 1e-6 for l in g),
          "%d -> %d" % (S["before"], len(g)))


def tick():
    x, y = at(.25, .75)
    stroke(dense([(x, y), (x + 15, y + 18), (x + 60, y - 50)]))


run([("activate", activate), ("setup", setup), W, W,
     ("scratch", scratch), W, ("erased", erased),
     ("undo", lambda: Gui.runCommand("Std_Undo")), W,
     ("back", lambda: check("undo brings it back", len(S["sk"].Geometry) == S["before"], str(len(S["sk"].Geometry)))),
     ("tick", tick), W, W,
     ("closed", lambda: check("a tick finishes the sketch", Gui.ActiveDocument.getInEdit() is None)),
     ("errors", lambda: check("no errors", not errors(), str(errors()))),
     ])
