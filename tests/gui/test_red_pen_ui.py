# SPDX-License-Identifier: LGPL-2.1-or-later
"""10.8 Idee 1 in der Oberfläche: Rotstift öffnet ein Korrektur-Scribble (Transparentpapier, Blatt zur Kamera);
Korrektur-Karten (wie aus der Tinte gelesen): Zeigen hebt das Ziel hervor, Ausführen legt das Feature an, bei gleich
nahen Kanten wird gewählt, Strg+Z nimmt es zurück"""
import os
import sys
from harness import *
import harness
import Design
import DesignGui

sys.path.append(os.path.join(os.path.dirname(harness.__file__), "..", "design"))
import design  # noqa: E402

state = {}
DOWN = App.Vector(0, 0, -1)


def setup():
    _, b = design.box(doc(), 20, 20, 10)
    for o in doc().Objects:
        if o.TypeId == "Sketcher::SketchObject":
            o.Visibility = False
    state["body"] = b
    Gui.SendMsgToActiveView("ViewAxo")
    Gui.SendMsgToActiveView("ViewFit")


def cards():
    DesignGui.showCorrections(doc(), [("R2", App.Vector(10, -2, 30), DOWN), ("R1", App.Vector(10, 10, 30), DOWN),
                                      ("Hallo", App.Vector(0, 0, 30), DOWN)])


def panel_shown():
    return any(w.objectName() == "Corrections" for w in visible(QtWidgets.QWidget))


def apply_button(text):
    return [b for b in visible(QtWidgets.QPushButton) if b.accessibleName() == "Apply " + text][0]


def fillets():
    return [o for o in doc().Objects if o.TypeId == "Design::Fillet"]


def hover_first():
    row = apply_button("R2").parentWidget()
    QtWidgets.QApplication.sendEvent(row, QtCore.QEvent(QtCore.QEvent.Enter))


in_order([
    ("activate", activate),
    ("setup", setup),
    ("red pen", lambda: Gui.runCommand("Design_RedPen")),
    ("scribble", lambda: check("red pen opens a tracing-paper scribble", Gui.ActiveDocument.getInEdit() is not None
                               and Gui.ActiveDocument.getInEdit().Object.TypeId == "Design::Scribble"
                               and Gui.ActiveDocument.getInEdit().Object.Tracing)),
    ("palette", lambda: check("the palette offers Apply Corrections",
                              any(b.text() == "Apply Corrections" for b in visible(QtWidgets.QToolButton)))),
    ("finish", lambda: Gui.runCommand("Design_ScribbleFinish")),
    ("cards", cards),
    ("shown", lambda: check("the cards appear", panel_shown())),
    ("only corrections", lambda: check("a word that is no correction gets no apply button",
                                       not apply_button("Hallo").isEnabled())),
    ("ambiguous", lambda: check("between four edges the card asks which one",
                                any(c.accessibleName() == "Which one?" and c.count() >= 2 for c in visible(QtWidgets.QComboBox)))),
    ("hover", hover_first),
    ("preview", lambda: check("pointing at a card highlights its edge", len(Gui.Selection.getSelectionEx()) == 1
                              and Gui.Selection.getSelectionEx()[0].SubElementNames[0].startswith("Edge"))),
    ("shot", lambda: shot("cards")),
    ("apply", lambda: apply_button("R2").click()),
    ("filleted", lambda: check("apply rounds the edge", len(fillets()) == 1 and abs(fillets()[0].Size.Value - 2) < 1e-9
                               and not state["body"].Shape.isNull() and abs(state["body"].Shape.Volume - (4000 - (4 - 3.14159265) * 20)) < 0.01,
                               str(state["body"].Shape.Volume))),
    ("choose", lambda: [c for c in visible(QtWidgets.QComboBox) if c.accessibleName() == "Which one?"][0].setCurrentIndex(1)),
    ("apply second", lambda: apply_button("R1").click()),
    ("two", lambda: check("the chosen edge gets its own fillet", len(fillets()) == 2)),
    ("undo", lambda: Gui.runCommand("Std_Undo")),
    ("undone", lambda: check("ctrl+z takes the last correction back", len(fillets()) == 1, str(len(fillets())))),
    ("errors", lambda: check("no errors", not errors(), str(errors()))),
])
