# SPDX-License-Identifier: LGPL-2.1-or-later
"""Stift in einer offenen Skizze: ein Strich wird Skizzengeometrie. Hält der Stift am Ende still, wird er zur erkannten
Form (Rechteck: vier Linien, waagerecht/senkrecht, Ecken koinzident), sonst Freihand. Ein Ende nahe an einem Skizzenpunkt
rastet ein und wird koinzident. Rückgängig nimmt den Strich zurück. Die Maus wählt wie immer (zeichnet nicht), und mit
einem laufenden Skizzenwerkzeug bekommt das Werkzeug den Stift."""
import math
from harness import *
import Design

S = {}
W = ("wait", lambda: None)
_pen = []


def tablet(kind, x, y, button, buttons):
    """Grafiktablett wie über Wayland (Stift ohne Radierer-Ende); True, wenn die Skizze es angenommen hat"""
    if not _pen:
        _pen.append(QtGui.QPointingDevice("pen", 17, QtGui.QInputDevice.DeviceType.Stylus, QtGui.QPointingDevice.PointerType.Pen,
                                          QtGui.QInputDevice.Capability.Position | QtGui.QInputDevice.Capability.Pressure, 1, 3))
    vp = view().viewport(); p = QtCore.QPointF(x, y)
    e = QtGui.QTabletEvent(kind, _pen[0], p, vp.mapToGlobal(p), .6, 0, 0, 0, 0, 0, QtCore.Qt.NoModifier, button, buttons)
    QtWidgets.QApplication.sendEvent(vp, e)
    return e.isAccepted()


def at(fx, fy):
    v = view().viewport(); return v.width() * fx, v.height() * fy


def press_and_move(points):
    L_, N = QtCore.Qt.LeftButton, QtCore.Qt.NoButton
    S["accepted"] = tablet(QtCore.QEvent.TabletPress, *points[0], L_, L_)
    for x, y in points[1:]:
        tablet(QtCore.QEvent.TabletMove, x, y, N, L_)


def release(points):
    tablet(QtCore.QEvent.TabletRelease, *points[-1], QtCore.Qt.LeftButton, QtCore.Qt.NoButton)


def stroke(points):
    press_and_move(points); release(points)


def dense(poly, n=12):
    out = [poly[0]]
    for (x0, y0), (x1, y1) in zip(poly, poly[1:]):
        out += [(x0 + (x1 - x0) * k / n, y0 + (y1 - y0) * k / n) for k in range(1, n + 1)]
    return out


def sk():
    return S["sk"]


def setup():
    d = doc(); root = [o for o in d.Objects if o.TypeId == "App::Part"][0]
    S["sk"] = Design.newSketch(root); d.recompute()
    Gui.ActiveDocument.setEdit(S["sk"])


def kinds():
    from collections import Counter
    return dict(Counter(g.TypeId.split("::")[1] for g in sk().Geometry))


def cons(kind):
    return [c for c in sk().Constraints if c.Type == kind]


def rect_hold():
    """Rechteck zeichnen, loslassen erst im nächsten Schritt: dazwischen hält der Stift still"""
    S["rect"] = dense([at(.35, .35), at(.6, .35), at(.6, .6), at(.35, .6), at(.35, .352)])
    press_and_move(S["rect"])


def rect_check():
    check("the pen starts drawing in an open sketch", S["accepted"])
    check("holding still turns the stroke into a rectangle: four lines, horizontal/vertical, corners joined",
          kinds() == {"GeomLineSegment": 4} and len(cons("Horizontal")) == 2 and len(cons("Vertical")) == 2
          and len(cons("Coincident")) == 4,
          "%s H=%d V=%d C=%d" % (kinds(), len(cons("Horizontal")), len(cons("Vertical")), len(cons("Coincident"))))
    check("the rectangle makes a closed profile", len(sk().Shape.Wires) == 1 and sk().Shape.Wires[0].isClosed())


def free():
    S["n"] = len(sk().Geometry)
    corner = view_point(sk().Geometry[0].StartPoint)  # beginnt (fast) auf einer Rechteckecke: rastet ein
    pts = [(corner[0] + 3, corner[1] + 2)] + [(corner[0] + 3 + 8 * k, corner[1] + 60 + 25 * math.sin(k / 3)) for k in range(1, 30)]
    S["coincident"] = len(cons("Coincident"))
    stroke(pts)


def view_point(p):
    """Skizzenpunkt -> Pixel im Viewport"""
    v = Gui.ActiveDocument.ActiveView; vp = view().viewport(); dpr = vp.devicePixelRatioF()
    x, y = v.getPointOnViewport(sk().getGlobalPlacement().multVec(p))
    return x / dpr, vp.height() - y / dpr


def free_check():
    added = len(sk().Geometry) - S["n"]
    check("a free stroke becomes sketch geometry (lines or splines)", added >= 1, str(kinds()))
    check("its start near a rectangle corner snaps there and is coincident",
          len(cons("Coincident")) > S["coincident"], "coincident before=%d after=%d" % (S["coincident"], len(cons("Coincident"))))


def undo():
    S["before_undo"] = len(sk().Geometry)
    Gui.runCommand("Std_Undo")


def undone():
    check("undo takes the stroke back", len(sk().Geometry) == S["n"], "%d -> %d" % (S["before_undo"], len(sk().Geometry)))


def mouse():
    S["n"] = len(sk().Geometry)
    vp = view().viewport()
    pts = [at(.2, .8), at(.3, .85), at(.4, .8)]
    def send(kind, x, y, b, bs):
        p = QtCore.QPointF(x, y)
        QtWidgets.QApplication.sendEvent(vp, QtGui.QMouseEvent(kind, p, vp.mapToGlobal(p), b, bs, QtCore.Qt.NoModifier))
    send(QtCore.QEvent.MouseButtonPress, *pts[0], QtCore.Qt.LeftButton, QtCore.Qt.LeftButton)
    for p in pts[1:]:
        send(QtCore.QEvent.MouseMove, *p, QtCore.Qt.NoButton, QtCore.Qt.LeftButton)
    send(QtCore.QEvent.MouseButtonRelease, *pts[-1], QtCore.Qt.LeftButton, QtCore.Qt.NoButton)


def tool():
    check("the mouse does not draw", len(sk().Geometry) == S["n"], str(len(sk().Geometry)))
    Gui.runCommand("Sketcher_CreateLine")


def tool_check():
    accepted = tablet(QtCore.QEvent.TabletPress, *at(.2, .2), QtCore.Qt.LeftButton, QtCore.Qt.LeftButton)
    tablet(QtCore.QEvent.TabletRelease, *at(.2, .2), QtCore.Qt.LeftButton, QtCore.Qt.NoButton)
    check("with a sketch tool running, the pen goes to the tool", not accepted)
    esc(); esc()
    check("no errors", not errors(), str(errors()))


run([("activate", activate), ("setup", setup), W, W, ("rect", rect_hold), W, ("release", lambda: release(S["rect"])), W,
     ("rect check", rect_check), ("shot", lambda: shot("rect")), ("free", free), W, ("free check", free_check),
     ("undo", undo), W, ("undone", undone), ("mouse", mouse), W, ("tool", tool), W, ("tool check", tool_check)])
