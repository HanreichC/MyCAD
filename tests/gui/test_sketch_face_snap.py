# SPDX-License-Identifier: LGPL-2.1-or-later
"""Skizze direkt auf einer Körperfläche: der Rand der Fläche ist projiziert (wie Fusion). Eine Linie von Kante zu Kante
fängt an beiden Rändern mit "liegt darauf" und teilt die Fläche in zwei Profile."""
from PySide6 import QtGui
from harness import *

V = App.Vector
state = {}
wait = ("wait", lambda: None)


def sketch():
    return Gui.ActiveDocument.getInEdit().Object


def profiles():
    return [o for o in doc().Objects if o.TypeId == "Design::Profiles" and o.Sketch == sketch()][0]


def setup():
    state["box"] = make_body(rect(0, 0, 40, 20), 0, 5, "Box")
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(doc().Name, state["box"].Name, top_face(state["box"]))
    Gui.runCommand("Design_CreateSketch")


def projected():
    s = sketch()
    check("the face outline is projected into the new sketch", len(s.ExternalGeometry) == 1, str(s.ExternalGeometry))
    check("the projected outline counts for profiles", len(s.Shape.Edges) == 4, str(len(s.Shape.Edges)))
    check("the whole face is one profile", len(profiles().Shape.Faces) == 1, str(len(profiles().Shape.Faces)))


def press(x, y, dx, dy):
    """Echter Klick ein paar Pixel neben dem Punkt (x, y) auf der Oberseite"""
    vp = view().viewport(); dpr = vp.devicePixelRatioF()
    px, py = Gui.ActiveDocument.ActiveView.getPointOnViewport(V(x, y, 5))
    p = QtCore.QPoint(int(px / dpr) + dx, int(vp.height() - py / dpr) + dy)
    for q in (p - QtCore.QPoint(1, 1), p):
        QtWidgets.QApplication.sendEvent(vp, QtGui.QMouseEvent(QtCore.QEvent.MouseMove, QtCore.QPointF(q), QtCore.QPointF(vp.mapToGlobal(q)), QtCore.Qt.NoButton, QtCore.Qt.NoButton, QtCore.Qt.NoModifier))
    QtTest.QTest.mouseClick(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)


def snapped():
    s = sketch()
    lines = [g for g in s.Geometry if isinstance(g, Part.LineSegment)]
    ends = [s.Placement.multVec(p) for g in lines for p in (g.StartPoint, g.EndPoint)]
    on_edge = [c for c in s.Constraints if c.Type == "PointOnObject" and c.Second <= -3]  # -1/-2 sind die Skizzenachsen
    check("both line ends land exactly on the face edges", len(lines) == 1 and sorted(round(p.y, 6) for p in ends) == [0, 20],
          str(ends))
    check("both ends are bound to the projected edges", len(on_edge) == 2, str([(c.Type, c.First, c.Second) for c in s.Constraints]))
    state["profiles"] = profiles()


def split():
    faces = state["profiles"].Shape.Faces  # Profile rechnen erst nach dem Verlassen der Skizze
    check("the line splits the face into two profiles", len(faces) == 2, str(len(faces)))


run([
    ("setup", setup), wait,
    ("fit", lambda: Gui.SendMsgToActiveView("ViewFit")), wait,
    ("projected", projected),
    ("line tool", lambda: click(button("Sketcher_CreateLine"))), wait,
    ("start", lambda: press(15, 0, 3, 4)), wait,
    ("end", lambda: press(15, 20, -3, -4)), wait,
    ("esc", lambda: QtTest.QTest.keyClick(view().viewport(), QtCore.Qt.Key_Escape)), wait,
    ("shot", lambda: shot("sketch_face_snap")),
    ("snapped", snapped),
    ("leave", lambda: Gui.ActiveDocument.resetEdit()), wait, wait,
    ("split", split),
])
