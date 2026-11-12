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


def blue_pixels():
    """Pixel in der Auswahlfarbe (Akzentblau) in der Ansicht"""
    img = view().viewport().grab().toImage()
    n = 0
    for y in range(0, img.height(), 3):
        for x in range(0, img.width(), 3):
            c = img.pixelColor(x, y)
            n += c.blue() > 150 and c.blue() > c.red() + 60
    return n


def open_search():
    activate()
    QtTest.QTest.keyClick(mw, QtCore.Qt.Key_K, QtCore.Qt.ControlModifier)


def is_open():
    return any(e.accessibleName() == "Search" for e in visible(QtWidgets.QLineEdit))


def window_keys(text):
    """wie echtes Tippen: über das Fenster, nicht direkt ins Feld (in der Skizze schluckte die 3D-Ansicht die Tasten)"""
    for c in text:
        QtTest.QTest.keyClick(mw.windowHandle(), c)


def in_sketch_typed():
    r = results()
    check("typing reaches the search field in a sketch", field().text() == "slot", repr(field().text()))
    check("no duplicate hits in a sketch (group commands skipped)", r and len(r) == len(set(r)), str(r))


def german_in_sketch():
    typed("kreis")
    check("German name finds Circle in the English UI", any("Circle" in t for t in results()[:3]), str(results()))


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
    ("highlighted", lambda: check("the body found by search is highlighted in the view", blue_pixels() > 500, str(blue_pixels()))),
    ("again", lambda: Gui.runCommand("MyCAD_Search")),
    ("measure", lambda: typed("meas")),
    ("run", lambda: key(QtCore.Qt.Key_Return)),
    ("measure open", lambda: check("enter runs the command", any("<table>" in l.text() or "Select a point" in l.text()
                                                                 for l in visible(QtWidgets.QLabel)))),
    ("close measure", esc),
    ("recent", lambda: Gui.runCommand("MyCAD_Search")),
    ("recent list", lambda: check("empty search shows recently used first", results()[:1] == ["Measure"], str(results()))),
    ("shot", lambda: shot("search")),
    ("recent body", lambda: check("empty search shows the body used last too", "Bracket" in results(), str(results()))),
    ("esc", lambda: key(QtCore.Qt.Key_Escape)),
    ("closed", lambda: check("esc closes the search", not is_open())),
    ("bohrung", lambda: (Gui.runCommand("MyCAD_Search"), typed("bohrung"))),
    ("hole first", lambda: check("German label ranks Hole first in the English UI", results()[:1] == ["Hole"], str(results()))),
    ("esc0", lambda: key(QtCore.Qt.Key_Escape)),
    ("sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick XY", lambda: Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XY_Plane")][0])),
    ("ctrl+k sketch", open_search),
    ("type sketch", lambda: window_keys("slot")),
    ("typed sketch", in_sketch_typed),
    ("kreis", german_in_sketch),
    ("esc sketch", lambda: QtTest.QTest.keyClick(mw.windowHandle(), QtCore.Qt.Key_Escape)),
    ("esc only search", lambda: check("esc in a sketch closes only the search", not is_open()
                                      and Gui.ActiveDocument.getInEdit() is not None)),
    ("leave sketch", lambda: Gui.runCommand("Sketcher_LeaveSketch")),
    ("close design", lambda: App.closeDocument(doc().Name)),
    ("new design", lambda: Gui.runCommand("Std_New")),
    ("search again", lambda: Gui.runCommand("MyCAD_Search")),
    ("alive", lambda: check("search works after closing the design it was shown in", is_open())),
])
