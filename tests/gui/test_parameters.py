# SPDX-License-Identifier: LGPL-2.1-or-later
"""Parameter: Width = 40 mm, Height = Width / 4; Extrude-Abstand "Height * 2" -> 20 mm.
Width auf 80 mm -> Height 20 -> Körper wird 40 mm hoch."""
import os
from harness import *


def fill_dialog():
    d = [w for w in visible(QtWidgets.QDialog) if w.windowTitle() == "Parameters"][0]
    name, expr = [e for e in d.findChildren(QtWidgets.QLineEdit) if e.isVisible() and e.placeholderText()][:2]
    add = [b for b in d.findChildren(QtWidgets.QPushButton) if b.text() == "Add"][0]
    for n, e in (("Width", "40 mm"), ("Height", "Width / 4")):
        name.setText(n); expr.setText(e); add.click()
    d.grab().save(os.environ["OUT"] + ".dialog.png")
    [b for b in d.findChildren(QtWidgets.QPushButton) if b.text().replace("&", "") == "OK"][0].click()


def params():
    s = [o for o in doc().Objects if o.TypeId == "App::VarSet"][0]
    return "Width=%s Height=%s" % (s.Width, s.Height)


def expression_distance():
    box = sorted(visible(QtWidgets.QAbstractSpinBox), key=lambda w: w.mapToGlobal(QtCore.QPoint(0, 0)).y())[0]
    edit = box.findChild(QtWidgets.QLineEdit); box.setFocus(); edit.selectAll()
    QtTest.QTest.keyClicks(edit, "Height * 2"); QtTest.QTest.keyClick(edit, QtCore.Qt.Key_Return)


def height():
    b = [o for o in doc().Objects if o.TypeId == "Design::Body"][0]
    return "%.1f (volume %.0f)" % (b.Shape.BoundBox.ZLength, b.Shape.Volume)


run([
    ("parameters", lambda: (QtCore.QTimer.singleShot(800, fill_dialog), Gui.runCommand("Design_Parameters"))),
    ("values", lambda: L("parameters: %s" % params())),
    ("Create Sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick XY", lambda: Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XY_Plane")][0])),
    ("rect", lambda: [Gui.ActiveDocument.getInEdit().Object.addGeometry(g) for g in rect(0, 0, 20, 10)]),
    ("finish", lambda: click(button("Sketcher_LeaveSketch"))),
    ("Extrude", lambda: click(button("Design_Extrude"))),
    ("expression", expression_distance),
    ("shot", lambda: shot("extrude")), ("OK", ok),
    ("height", lambda: L("height=%s (erwartet 20.0, Ausdruck=%s)" % (height(), [o.ExpressionEngine for o in doc().Objects if o.TypeId == "Design::Extrude"]))),
    ("width 80", lambda: ([o for o in doc().Objects if o.TypeId == "App::VarSet"][0].setExpression("Width", "80 mm"), doc().recompute())),
    ("height2", lambda: L("after Width=80: %s height=%s (erwartet 40.0)" % (params(), height()))),
    ("errors", lambda: L("errors=%s" % errors())),
])
