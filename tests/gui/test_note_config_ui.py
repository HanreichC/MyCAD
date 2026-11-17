# SPDX-License-Identifier: LGPL-2.1-or-later
"""Phase 11.7 Konfigurationen in der Notiz: "Größe: S | M | L" zeigt die Spalten als Knöpfe oben in der Notiz, die
erste ist gewählt; ein Klick auf L schreibt "Größe = L" in die Notiz und das Teil wird sofort so breit;
zurück schaltet ein Klick auf S (die Notiz bestimmt, Strg+Z dreht Notizen nicht zurück)."""
from harness import *

S = {}
W = ("wait", lambda: None)


def note_edit():
    return [e for e in visible(QtWidgets.QPlainTextEdit) if e.objectName() == "NoteText"][0]


def options():
    return sorted([b for b in visible(QtWidgets.QToolButton) if b.objectName() == "NoteConfiguration"],
                  key=lambda b: b.mapToGlobal(QtCore.QPoint(0, 0)).x())


def shown():
    return [(b.text(), b.isChecked()) for b in options()]


def setup():
    S["box"] = make_body(rect(0, 0, 10, 10), 0, 5, "Box")


def write():
    note_edit().setFocus()
    note_edit().setPlainText("Größe: S | M | L\nBreite = 20 mm | 30 mm | 40 mm")
    QtTest.QTest.keyClick(note_edit(), QtCore.Qt.Key_End, QtCore.Qt.ControlModifier)
    QtTest.QTest.keyClick(note_edit(), QtCore.Qt.Key_Return)  # Enter gleicht ab


def bind():
    ext = [o for o in doc().Objects if o.TypeId == "Design::Extrude"][0]
    ext.setExpression("Distance", "Parameters.Breite")
    doc().recompute()


def buttons():
    check("the note shows its configurations as buttons, the first one chosen",
          shown() == [("S", True), ("M", False), ("L", False)], str(shown()))
    shot("note")


def pick_l():
    click([b for b in options() if b.text() == "L"][0])


def switched():
    text = note_edit().toPlainText()
    check("clicking L writes the choice into the note and the part follows",
          "Größe = L" in text and abs(S["box"].Shape.Volume - 4000) < 1e-6 and shown()[2] == ("L", True),
          "volume=%.1f buttons=%s text=%r" % (S["box"].Shape.Volume, shown(), text))


def back_to_s():
    check("clicking S switches back", abs(S["box"].Shape.Volume - 2000) < 1e-6 and "Größe = S" in note_edit().toPlainText()
          and shown()[0] == ("S", True), "volume=%.1f buttons=%s" % (S["box"].Shape.Volume, shown()))


run([("activate", activate), ("setup", setup), W,
     ("new note", lambda: click(button("Design_Note"))), W,
     ("write", write), W, ("bind", bind), W,
     ("width S", lambda: check("without a choice the first column counts", abs(S["box"].Shape.Volume - 2000) < 1e-6,
                               "volume=%.1f" % S["box"].Shape.Volume)),
     ("buttons", buttons),
     ("L", pick_l), W, W, ("switched", switched),
     ("S", lambda: click([b for b in options() if b.text() == "S"][0])), W, W, ("back", back_to_s),
     ("errors", lambda: check("no errors", not errors(), str(errors()))),
     ])
