# SPDX-License-Identifier: LGPL-2.1-or-later
"""10.2 Idee 6 in der Oberfläche: zu großer Radius zeigt einen Knopf mit dem größten, der geht; ein Klick repariert.
Ein verlorener Bezug bekommt in der Timeline ein Warnsymbol, "Stimmt so" bestätigt."""
from harness import *
from PySide6 import QtGui

state = {}


def front_top(b):
    i = [k for k, e in enumerate(b.Shape.Edges, 1) if abs(e.CenterOfMass.y) < 1e-6 and abs(e.CenterOfMass.z - 5) < 1e-6]
    return "Edge%d" % i[0]


def fix_buttons():
    return [b for b in visible(QtWidgets.QPushButton) if b.text().startswith("Use ")]


def fillet():
    return [o for o in doc().Objects if o.TypeId == "Design::Fillet"][-1]


def menu_pick(text):
    def pick():
        menu = QtWidgets.QApplication.activePopupWidget()
        acts = [a for a in (menu.actions() if menu else []) if a.text() == text]
        state["menu"] = [a.text() for a in menu.actions()] if menu else []
        if acts:
            menu.setActiveAction(acts[0]); QtTest.QTest.keyClick(menu, QtCore.Qt.Key_Return)
        elif menu:
            menu.close()
    QtCore.QTimer.singleShot(600, pick)


def entry(obj):
    return [b for b in visible(QtWidgets.QToolButton) if b.property("timelineIndex") is not None
            and b.accessibleName() == obj.Label][0]


def lose_reference():
    f = fillet(); f.ElementMaps = ["lost"]; f.touch(); doc().recompute()


run([
    ("setup", lambda: state.update(box=make_body(rect(0, 0, 20, 10), 0, 5, "Box"))),
    ("pick edge", lambda: Gui.Selection.addSelection(state["box"], front_top(state["box"]))),
    ("fillet", lambda: click(button("Design_Fillet"))),
    ("too big", lambda: type_field("Radius", "8")),
    ("button", lambda: check("fix button offers the largest radius", len(fix_buttons()) == 1, str([b.text() for b in fix_buttons()]))),
    ("shot", lambda: shot("fix")),
    ("click fix", lambda: fix_buttons()[0].click()),
    ("fixed", lambda: check("one click repairs the fillet", not errors() and 4.5 < fillet().Size.Value <= 5, str(fillet().Size))),
    ("ok", ok),
    ("lose", lose_reference),
    ("warn", lambda: check("timeline warns about the reference", "changed" in entry(fillet()).toolTip(), entry(fillet()).toolTip())),
    ("confirm", lambda: (menu_pick("Looks Right"),
                         QtWidgets.QApplication.sendEvent(entry(fillet()), QtGui.QContextMenuEvent(QtGui.QContextMenuEvent.Mouse, QtCore.QPoint(5, 5))))),
    ("confirmed", lambda: check("looks right clears the warning", fillet().Warning == "", str(state.get("menu")))),
])
