# SPDX-License-Identifier: LGPL-2.1-or-later
"""L10 Befehlssuche: Strg+K, Tippen findet Befehle (auch mit Tippfehler und Synonym), Körper im Design, Enter startet,
Esc schließt, zuletzt benutzte stehen oben"""
from harness import *

state = {}


def field():
    return [e for e in visible(QtWidgets.QLineEdit) if e.accessibleName() == "Search"][0]


def results():
    lists = [l for l in visible(QtWidgets.QListWidget) if l.accessibleName() == "Results"]
    return [lists[0].item(i).data(QtCore.Qt.AccessibleTextRole) for i in range(lists[0].count())] if lists else []


def typed(text):
    f = field(); f.clear(); QtTest.QTest.keyClicks(f, text)


def key(k):
    QtTest.QTest.keyClick(field(), k)


def open_search():
    activate()
    QtTest.QTest.keyClick(mw, QtCore.Qt.Key_K, QtCore.Qt.ControlModifier)


def is_open():
    return any(e.accessibleName() == "Search" for e in visible(QtWidgets.QLineEdit))


run([
    ("setup", lambda: make_body(rect(0, 0, 20, 10), 0, 5, "Bracket")),
    ("ctrl+k", open_search),
    ("opened", lambda: check("ctrl+k opens the search", is_open())),
    ("prefix", lambda: typed("meas")),
    ("first", lambda: check("prefix finds Measure first", results()[:1] == ["Measure"], str(results()))),
    ("typo", lambda: typed("mesure")),
    ("typo found", lambda: check("typo still finds Measure", "Measure" in results()[:3], str(results()))),
    ("synonym", lambda: typed("loch")),
    ("synonym found", lambda: check("German synonym finds Hole", "Hole" in results()[:3], str(results()))),
    ("object", lambda: typed("brack")),
    ("object found", lambda: check("body of the design is found", "Bracket" in results(), str(results()))),
    ("enter body", lambda: key(QtCore.Qt.Key_Return)),
    ("selected", lambda: check("enter selects the body", [o.Label for o in Gui.Selection.getSelection()] == ["Bracket"]
                              and not is_open(), str([o.Label for o in Gui.Selection.getSelection()]))),
    ("again", lambda: Gui.runCommand("MyCAD_Search")),
    ("measure", lambda: typed("meas")),
    ("run", lambda: key(QtCore.Qt.Key_Return)),
    ("measure open", lambda: check("enter runs the command", any("<table>" in l.text() or "Select a point" in l.text()
                                                                 for l in visible(QtWidgets.QLabel)))),
    ("close measure", esc),
    ("recent", lambda: Gui.runCommand("MyCAD_Search")),
    ("recent list", lambda: check("empty search shows recently used first", results()[:1] == ["Measure"], str(results()))),
    ("shot", lambda: shot("search")),
    ("esc", lambda: key(QtCore.Qt.Key_Escape)),
    ("closed", lambda: check("esc closes the search", not is_open())),
])
