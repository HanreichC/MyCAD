# SPDX-License-Identifier: LGPL-2.1-or-later
"""10.3 Idee 2 in der Oberfläche: Fläche antippen zeigt ihre Maße am Modell, Enter rechnet neu, Strg+Z nimmt es
zurück, ohne Auswahl verschwindet die Karte"""
from harness import *

state = {}


def card_fields():
    return [b for b in visible(QtWidgets.QAbstractSpinBox)
            if b.parentWidget() and b.parentWidget().objectName() == "FaceDimensions"]


def pick_top():
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(state["box"], top_face(state["box"]))


def enter_value(text):
    box = card_fields()[0]
    box.setFocus()
    box.lineEdit().selectAll(); QtTest.QTest.keyClicks(box.lineEdit(), text)
    QtTest.QTest.keyClick(box.lineEdit(), QtCore.Qt.Key_Return)


run([
    ("setup", lambda: state.update(box=make_body(rect(0, 0, 20, 10), 0, 5, "Box"))),
    ("pick", pick_top),
    ("card", lambda: check("tapping the top face shows its distance", [b.accessibleName() for b in card_fields()] == ["Distance"],
                           str([b.accessibleName() for b in card_fields()]))),
    ("shot", lambda: shot("card")),
    ("type", lambda: enter_value("12")),
    ("changed", lambda: check("enter changes the model", abs(body("Box").Shape.Volume - 2400) < 1e-6, str(body("Box").Shape.Volume))),
    ("undo", lambda: Gui.runCommand("Std_Undo")),
    ("undone", lambda: check("ctrl+z takes it back", abs(body("Box").Shape.Volume - 1000) < 1e-6, str(body("Box").Shape.Volume))),
    ("clear", lambda: Gui.Selection.clearSelection()),
    ("gone", lambda: check("without a selected face the card disappears", not card_fields())),
])
