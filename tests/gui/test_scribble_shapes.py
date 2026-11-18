# SPDX-License-Identifier: LGPL-2.1-or-later
"""Aufräumliste B11: Halten begradigt auch Bögen, Ellipsen und Dreiecke; in der Skizze wird der Bogen ein echter
Kreisbogen. Fehler stehen als FAIL im Protokoll."""
import math
from harness import *
from PySide6 import QtGui


def s():
    return [o for o in doc().Objects if o.TypeId == "Design::Scribble"][0]


def send(kind, x, y, button, buttons):
    vp = view().viewport(); p = QtCore.QPointF(x, y)
    QtWidgets.QApplication.sendEvent(vp, QtGui.QMouseEvent(kind, p, vp.mapToGlobal(p), button, buttons, QtCore.Qt.NoModifier))


def draw(points):
    """gedrückt zeichnen, ohne loszulassen (der nächste Schritt hält still, dann wird losgelassen)"""
    send(QtCore.QEvent.MouseButtonPress, *points[0], QtCore.Qt.LeftButton, QtCore.Qt.LeftButton)
    for x, y in points[1:]:
        send(QtCore.QEvent.MouseMove, x, y, QtCore.Qt.NoButton, QtCore.Qt.LeftButton)
    state["end"] = points[-1]


def up():
    send(QtCore.QEvent.MouseButtonRelease, *state["end"], QtCore.Qt.LeftButton, QtCore.Qt.NoButton)


def round_path(fx, fy, rx, ry, t0, t1, n=60):
    """Punkte in Pixeln (ein Kreis bleibt rund, egal wie breit die Ansicht ist), leicht zittrig"""
    w, h = view().width(), view().height()
    return [(w * fx + rx * math.cos(t0 + (t1 - t0) * k / n) + 0.8 * math.sin(k * 2.3),
             h * fy + ry * math.sin(t0 + (t1 - t0) * k / n) + 0.8 * math.cos(k * 1.7)) for k in range(n + 1)]


def tri_path(fx, fy, size):
    w, h = view().width(), view().height()
    a, b, c = (w * fx, h * fy), (w * fx + size, h * fy), (w * fx + size / 2, h * fy - 0.8 * size)
    seg = lambda p, q: [(p[0] + (q[0] - p[0]) * k / 15, p[1] + (q[1] - p[1]) * k / 15) for k in range(15)]
    return seg(a, b) + seg(b, c) + seg(c, a) + [a]


def kinds():
    return list(s().Kinds)


state = {}
wait = ("wait", lambda: None)
hold = ("hold", lambda: None)  # Stift steht still: die Formerkennung (450 ms) schlägt zu

in_order([
    ("new", lambda: click(button("Design_Scribble"))), wait, wait,
    ("arc", lambda: draw(round_path(0.35, 0.55, 90, 90, math.pi, 2 * math.pi))), hold,
    ("arc up", up), wait,
    ("arc kind", lambda: check("a held arc becomes an arc", kinds() == [7] and s().Counts[0] == 49, str(kinds()))),
    ("ellipse", lambda: draw(round_path(0.65, 0.45, 110, 50, 0, 2.05 * math.pi, 80))), hold,
    ("ellipse up", up), wait,
    ("ellipse kind", lambda: check("a held oval becomes an ellipse", kinds()[-1] == 5 and s().Counts[-1] == 97, str(kinds()))),
    ("triangle", lambda: draw(tri_path(0.55, 0.85, 120))), hold,
    ("triangle up", up), wait,
    ("triangle kind", lambda: check("a held triangle becomes a triangle", kinds()[-1] == 4 and s().Counts[-1] == 4, str(kinds()))),
    ("shot", lambda: shot("shapes")),
    ("convert", lambda: Gui.runCommand("Design_ScribbleToSketch")), wait, wait,
    ("in sketch", lambda: (lambda types: check("the arc becomes a sketch arc, the oval a sketch ellipse",
                                               "Part::GeomArcOfCircle" in types and "Part::GeomEllipse" in types, str(types)))(
        [g.TypeId for g in Gui.ActiveDocument.getInEdit().Object.Geometry])),
    ("solved", lambda: check("that sketch solves", Gui.ActiveDocument.getInEdit().Object.solve() == 0)),
    ("leave", lambda: Gui.ActiveDocument.resetEdit()), wait,
])
