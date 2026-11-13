# SPDX-License-Identifier: LGPL-2.1-or-later
"""Abstand 0 im Maß-Dialog: zwischen Punkt und Linie wird das Maß zu "Punkt liegt darauf" (die schwebende Kante sitzt
dann auf der Achse); bei einer Linienlänge bleibt der Dialog offen und erklärt, was stattdessen geht."""
from harness import *
import Design
import Sketcher

S = {}


def setup():
    sk = Design.newSketch(Design.root(doc()))
    Gui.ActiveDocument.setEdit(sk)
    sk.addGeometry(Part.LineSegment(App.Vector(10, 3, 0), App.Vector(30, 3, 0)))
    sk.addConstraint(Sketcher.Constraint("Horizontal", 0))
    sk.addConstraint(Sketcher.Constraint("Distance", 0, 1, -1, 3))  # schwebt 3 mm über der Achse
    sk.addConstraint(Sketcher.Constraint("Distance", 0, 20))  # Länge
    doc().recompute(); S["sk"] = sk


def edit(index):
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(doc().Name, S["sk"].Name, "Constraint%d" % (index + 1))
    QtCore.QTimer.singleShot(0, lambda: Gui.runCommand("Sketcher_ChangeDimensionConstraint"))


def type_zero():
    box = QtWidgets.QApplication.focusWidget()
    box.lineEdit().selectAll(); QtTest.QTest.keyClicks(box, "0"); QtTest.QTest.keyClick(box, QtCore.Qt.Key_Return)


def on_axis():
    c, g = S["sk"].Constraints[1], S["sk"].Geometry[0]
    check("0 between point and axis turns the dimension into point-on-object",
          c.Type == "PointOnObject" and QtWidgets.QApplication.activeModalWidget() is None and abs(g.StartPoint.y) < 1e-7
          and abs(g.EndPoint.y) < 1e-7, "%s start=%s" % (c.Type, g.StartPoint))


def length_refused():
    m = QtWidgets.QApplication.activeModalWidget()
    check("0 as a line length keeps the dialog open with a hint",
          m is not None and S["sk"].Constraints[2].Type == "Distance" and QtWidgets.QToolTip.text().startswith("0 "),
          "dialog=%s type=%s tip=%r" % (m, S["sk"].Constraints[2].Type, QtWidgets.QToolTip.text()))
    shot("hint")
    if m:
        m.reject()


run([
    ("activate", activate), ("setup", setup),
    ("edit floating", lambda: edit(1)), ("type 0", type_zero), ("on axis", on_axis),
    ("edit length", lambda: edit(2)), ("type 0 again", type_zero), ("refused", length_refused),
])
