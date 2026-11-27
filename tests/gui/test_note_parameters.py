# SPDX-License-Identifier: LGPL-2.1-or-later
"""10.4 Idee 3 in der Oberfläche: in die Notiz "Wand = 2 mm" tippen, Enter legt den Parameter an, Formeln zeigen
ihren Wert dahinter, die Notiz verlassen rechnet das Modell nach, doppelte Namen werden markiert, das Parameter-Fenster
zeigt, aus welcher Notiz ein Parameter kommt"""
from harness import *
from PySide6 import QtGui

state = {}


def note_obj():
    return [o for o in doc().Objects if o.TypeId == "Design::Note"][0]


def note_edit():
    return [e for e in visible(QtWidgets.QPlainTextEdit) if e.objectName() == "NoteText"][0]


def keys(text):
    for c in text:
        QtTest.QTest.keyClick(note_edit(), QtCore.Qt.Key_Return if c == "\n" else c)


def params():
    return [o for o in doc().Objects if o.TypeId == "App::VarSet" and o.Label == "Parameters"][0]


def setup():
    state["box"] = make_body(rect(0, 0, 10, 10), 0, 5, "Box")


def bind():
    ext = [o for o in doc().Objects if o.TypeId == "Design::Extrude"][0]
    ext.setExpression("Distance", "Parameters.Hoehe")
    doc().recompute()


def edit_first_line(text):
    e = note_edit()
    lines = e.toPlainText().split("\n")
    e.setPlainText("\n".join([text] + lines[1:]))


def middle_line():
    """Ende der ersten Zeile ("Hoehe = 5 mm"), "5 mm" durch "6 mm" ersetzen, Enter"""
    e = note_edit()
    state["blocks"] = e.blockCount()
    e.setFocus()
    c = e.textCursor()
    c.movePosition(QtGui.QTextCursor.Start)
    c.movePosition(QtGui.QTextCursor.EndOfBlock)
    e.setTextCursor(c)
    for _ in range(4):
        QtTest.QTest.keyClick(e, QtCore.Qt.Key_Backspace)
    keys("6 mm\n")


def dialog_source():
    def look():
        d = [w for w in visible(QtWidgets.QDialog) if w.windowTitle() == "Parameters"][0]
        state["labels"] = [l.text() for l in d.findChildren(QtWidgets.QLabel) if l.isVisible()]
        d.reject()
    QtCore.QTimer.singleShot(800, look)
    Gui.runCommand("Design_Parameters")


in_order([
    ("activate", activate),
    ("setup", setup),
    ("new note", lambda: click(button("Design_Note"))),
    ("focus", lambda: note_edit().setFocus()),
    ("type", lambda: keys("Hoehe = 5 mm\nDoppelt = Hoehe * 2\n")),
    ("defined", lambda: check("enter defines the parameters", abs(params().Hoehe.Value - 5) < 1e-9 and abs(params().Doppelt.Value - 10) < 1e-9)),
    ("hint", lambda: check("the formula shows its value in the note", "Doppelt = Hoehe * 2 → 10.00 mm" in note_edit().toPlainText(),
                           repr(note_edit().toPlainText()))),
    ("cursor", lambda: check("typing goes on in the new line", note_edit().textCursor().blockNumber() == 2,
                             str(note_edit().textCursor().blockNumber()))),
    # Maß mitten in der Liste ändern, Enter: übernimmt, keine Leerzeile, weiter auf der nächsten Zeile (wie eine Tabelle)
    ("middle", middle_line),
    ("middle applied", lambda: check("enter in the middle applies the value without an empty line",
                                     abs(params().Hoehe.Value - 6) < 1e-9 and note_edit().blockCount() == state["blocks"]
                                     and note_edit().textCursor().blockNumber() == 1,
                                     "%s blocks %d (was %d) cursor in line %d %r" % (
                                         params().Hoehe.Value, note_edit().blockCount(), state["blocks"],
                                         note_edit().textCursor().blockNumber(), note_edit().toPlainText()))),
    ("bind", bind),
    ("shot", lambda: shot("note")),
    ("change", lambda: edit_first_line("Hoehe = 8 mm")),
    ("leave", lambda: view_click(0.5, 0.8)),
    ("model", lambda: check("leaving the note updates the model", abs(state["box"].Shape.Volume - 800) < 1e-6, str(state["box"].Shape.Volume))),
    ("value", lambda: check("and the value behind the formula", "→ 16.00 mm" in note_obj().Text, repr(note_obj().Text))),
    ("twice", lambda: (note_edit().setFocus(), note_edit().moveCursor(QtGui.QTextCursor.End), keys("Hoehe = 3 mm\n"))),
    ("marked", lambda: check("a name used twice is marked", "⚠ This name is used twice" in note_obj().Text, repr(note_obj().Text))),
    ("no calc", lambda: check("typing a known name and = does not paste its value", "Hoehe = 3 mm ⚠" in note_obj().Text, repr(note_obj().Text))),
    ("kept", lambda: check("and the first line still counts", abs(params().Hoehe.Value - 8) < 1e-9)),
    ("dialog", dialog_source),
    ("source", lambda: check("the parameters window names the note", any(l.startswith("In note") for l in state.get("labels", [])),
                             str(state.get("labels")))),
    ("errors", lambda: check("no errors", not errors(), str(errors()))),
])
