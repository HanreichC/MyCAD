# SPDX-License-Identifier: LGPL-2.1-or-later
"""Werkzeug-Symbol neben der Maus: Es erscheint mit dem Werkzeug und verschwindet mit Esc oder Rechtsklick, auch wenn
die Maus zwischendurch über einem Glass-Panel war. Fehler stehen als FAIL im Protokoll."""
from PySide6 import QtGui
from harness import *
import harness

TOOL = "Sketcher_CompCreateRectangles"


def symbol():
    return view().viewport().cursor().shape() == QtCore.Qt.BitmapCursor


def hover(p):
    """Echte Mausbewegung, QTest.mouseMove setzt ohne gedrückte Taste nur den Cursor (geht unter Wayland nicht)"""
    vp = view().viewport()
    for q in (p - QtCore.QPoint(1, 1), p):
        QtWidgets.QApplication.sendEvent(vp, QtGui.QMouseEvent(QtCore.QEvent.MouseMove, QtCore.QPointF(q), QtCore.QPointF(vp.mapToGlobal(q)), QtCore.Qt.NoButton, QtCore.Qt.NoButton, QtCore.Qt.NoModifier))


def canvas(dx=0):
    v = view()
    return QtCore.QPoint(int(v.width() * 0.5) + dx, int(v.height() * 0.55))


def to_panel():
    hover(harness._pos(button(TOOL)))


def to_canvas(dx=0):
    hover(canvas(dx))


def pick_tool():
    """Wie von Hand: Maus zum Knopf, Klick, zurück auf die Zeichenfläche"""
    to_panel()
    click(button(TOOL))
    to_canvas()


def right_click():
    QtTest.QTest.mouseClick(view().viewport(), QtCore.Qt.RightButton, QtCore.Qt.NoModifier, canvas())


def expect(name, wanted):
    return ("check", lambda: check(name, symbol() == wanted))


def geometry():
    return Gui.ActiveDocument.getInEdit().Object.GeometryCount


def tool_is_off():
    """Zwei Klicks erzeugen kein Rechteck mehr. Der Cursor allein würde das nicht beweisen."""
    before = geometry()
    view_click(0.30, 0.30); view_click(0.34, 0.34)
    check("Werkzeug ist wirklich aus", geometry() == before)


in_order([
    ("Create Sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick XY", lambda: Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XY_Plane")][0])),
    ("focus", activate),

    ("tool", pick_tool), expect("Symbol erscheint sofort auf der Zeichenfläche", True),
    ("esc", esc), expect("Esc nimmt das Symbol weg", False),
    ("off", tool_is_off),

    ("tool", pick_tool),
    ("panel", to_panel), expect("über dem Panel kein Werkzeug-Symbol", False),
    ("back", to_canvas), expect("zurück auf der Fläche wieder Symbol", True),
    ("esc", esc), expect("Esc nach Panel-Ausflug nimmt das Symbol weg", False),
    ("move", lambda: to_canvas(9)), expect("und es kommt beim Bewegen nicht wieder", False),

    ("tool", pick_tool),
    ("panel", to_panel), ("back", to_canvas),
    ("right", right_click), expect("Rechtsklick nach Panel-Ausflug nimmt das Symbol weg", False),
    ("move", lambda: to_canvas(9)), expect("und es kommt beim Bewegen nicht wieder", False),

    ("tool", pick_tool),
    ("panel", to_panel),
    ("esc", esc), ("back", to_canvas), expect("Esc über dem Panel, dann zurück: kein altes Symbol", False),
    ("off", tool_is_off),

    ("tool", pick_tool), expect("nächstes Werkzeug zeigt sein Symbol", True),
    ("esc", esc), expect("und auch das geht mit Esc weg", False),
])
