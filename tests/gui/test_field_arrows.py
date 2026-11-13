# SPDX-License-Identifier: LGPL-2.1-or-later
"""Pfeiltasten in einem Eingabefeld eines Glass-Panels bewegen den Cursor im Text, nicht die Kamera. Ohne Feld im
Fokus verschieben sie weiter die Ansicht. Die Tasten gehen wie von der Tastatur an das Fokus-Widget des Fensters (die
3D-Ansicht), nicht direkt ans Feld: genau dort fing die Kamera sie vorher ab."""
from harness import *

S = {}


def camera():
    return Gui.ActiveDocument.ActiveView.getCamera()


def press(key):
    QtTest.QTest.keyClick(QtWidgets.QApplication.focusWidget(), key)
    QtWidgets.QApplication.processEvents()


def setup():
    make_body(rect(0, 0, 40, 30), 0, 10, "Box")
    Gui.ActiveDocument.setEdit([o for o in doc().Objects if o.TypeId == "Design::Extrude"][-1])


def into_field():
    box = field("Distance"); S["edit"] = box.lineEdit() if hasattr(box, "lineEdit") else box
    click(box)


def arrows_in_field():
    e = S["edit"]; press(QtCore.Qt.Key_End)
    end, cam = e.cursorPosition(), camera()
    press(QtCore.Qt.Key_Left); press(QtCore.Qt.Key_Left)
    check("left arrow moves the cursor in the field", e.cursorPosition() == end - 2, "%d -> %d %r" % (end, e.cursorPosition(), e.text()))
    press(QtCore.Qt.Key_Right)
    check("right arrow moves the cursor back", e.cursorPosition() == end - 1, str(e.cursorPosition()))
    check("the camera stays put while typing", camera() == cam, "" if camera() == cam else "camera moved")


def leave():
    Gui.ActiveDocument.resetEdit()
    view().scene().clearFocus(); view().setFocus()


def arrows_in_view():
    cam = camera(); press(QtCore.Qt.Key_Left)
    check("without a field in focus the arrow keys still pan the view", camera() != cam, "moved" if camera() != cam else "did not move")


run([
    ("activate", activate), ("setup", setup), ("wait", lambda: None),
    ("field", into_field), ("arrows", arrows_in_field),
    ("leave", leave), ("view", arrows_in_view),
])
