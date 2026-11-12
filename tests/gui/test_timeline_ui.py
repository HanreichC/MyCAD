# SPDX-License-Identifier: LGPL-2.1-or-later
"""L7 in der Leiste: Eintrag ziehen, verbotenes Ziehen erklärt sich, Strg+Klick, Gruppieren per Kontextmenü, zuklappen"""
from harness import *
from harness import _pos
from PySide6 import QtGui
import Design

state = {}


def setup():
    d = doc()
    root = Design.root(d)
    sk = Design.newSketch(root)
    for g in rect(0, 0, 20, 10):
        sk.addGeometry(g)
    d.recompute()
    prof = [o for o in sk.InList if o.TypeId == "Design::Profiles"][0]
    f = d.addObject("Design::Extrude", "Extrude"); root.addObject(f); Design.addToTimeline(f)
    f.Profile = (prof, ["Face1"]); f.Distance = 5
    Design.newBody(f)
    loose = Design.newSketch(root)
    loose.addGeometry(Part.Circle(App.Vector(50, 0, 0), App.Vector(0, 0, 1), 3))
    d.recompute()
    state.update(sketch=sk, extrude=f, loose=loose)


def entries():
    """nur die Einträge (nicht Wiedergabe- oder Gruppen-Knöpfe), von links nach rechts"""
    return sorted([b for b in visible(QtWidgets.QToolButton) if b.property("timelineIndex") is not None],
                  key=lambda b: b.property("timelineIndex"))


def entry(obj):
    return [b for b in entries() if b.accessibleName() == obj.Label][0]


def drag(src, dst):
    vp, a, b = view().viewport(), _pos(src), _pos(dst)
    QtTest.QTest.mousePress(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, a)
    for k in range(1, 9):  # in Schritten, wie eine echte Hand
        p = a + (b - a) * (k / 8.0)
        ev = QtGui.QMouseEvent(QtCore.QEvent.MouseMove, QtCore.QPointF(p), QtCore.QPointF(vp.mapToGlobal(p)),
                               QtCore.Qt.NoButton, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier)
        QtWidgets.QApplication.sendEvent(vp, ev)
    QtTest.QTest.mouseRelease(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, b)


def order():
    return [o.Name for o in Design.timeline(doc())]


def close_message():
    boxes = visible(QtWidgets.QMessageBox)  # früher ein Fenster, jetzt ein Hinweis unter dem ViewCube
    state["message"] = " ".join(notices()) if not boxes else "message box instead of a hint"
    for m in boxes:
        m.accept()


def menu_action(text):
    """Nach dem Rechtsklick (das Menü blockiert) den Eintrag text wählen"""
    def pick():
        menu = QtWidgets.QApplication.activePopupWidget()
        acts = [a for a in (menu.actions() if menu else []) if a.text() == text]
        state["menu"] = [a.text() for a in menu.actions()] if menu else []
        if acts:  # wie ein Nutzer: Eintrag anwählen, Enter (trigger() allein beendet exec() nicht)
            menu.setActiveAction(acts[0])
            QtTest.QTest.keyClick(menu, QtCore.Qt.Key_Return)
        elif menu:
            menu.close()
    QtCore.QTimer.singleShot(600, pick)


def right_click(w):
    """Kontextmenü wie bei einem echten Rechtsklick (QTest erzeugt dafür kein QContextMenuEvent)"""
    QtWidgets.QApplication.sendEvent(w, QtGui.QContextMenuEvent(QtGui.QContextMenuEvent.Mouse, w.rect().center()))


def ctrl_click(w):
    QtTest.QTest.mouseClick(view().viewport(), QtCore.Qt.LeftButton, QtCore.Qt.ControlModifier, _pos(w))


def chips():
    return [b for b in visible(QtWidgets.QToolButton) if b.property("timelineGroup")]


run([
    ("activate", activate),  # Hinweise erscheinen nur bei aktivem Fenster (unter Xvfb sonst nicht)
    ("setup", setup), ("wait", lambda: None),
    ("drag loose to front", lambda: drag(entry(state["loose"]), entry(state["sketch"]))),
    ("moved", lambda: check("loose sketch moved to the front", order()[0] == state["loose"].Name, str(order()))),
    ("drag extrude to front", lambda: drag(entry(state["extrude"]), entries()[0])),
    ("message", close_message),
    ("refused", lambda: check("extrude cannot go before its sketch",
                              order().index(state["extrude"].Name) > order().index(state["sketch"].Name)
                              and "which it needs" in state.get("message", ""), state.get("message", ""))),
    ("select 1", lambda: click(entry(state["sketch"]))),
    ("select 2", lambda: ctrl_click(entry(state["extrude"]))),
    ("selected", lambda: check("ctrl+click adds to the selection", len(Gui.Selection.getSelection()) == 2,
                               str([o.Name for o in Gui.Selection.getSelection()]))),
    ("menu", lambda: (menu_action("Group Selected Steps"), right_click(entry(state["extrude"])))),
    ("grouped", lambda: check("group created", Design.timelineGroup(state["extrude"]) == "Group 1"
                              and Design.timelineGroup(state["sketch"]) == "Group 1", str(state.get("menu")))),
    ("chip", lambda: check("group button shown and open", len(chips()) == 1 and chips()[0].isChecked())),
    ("shot", lambda: shot("group")),
    ("collapse", lambda: click(chips()[0])),
    ("collapsed", lambda: check("collapsed group hides its steps", len(entries()) == 1, str([b.accessibleName() for b in entries()]))),
    ("errors", lambda: check("no errors", not errors(), str(errors()))),
])
