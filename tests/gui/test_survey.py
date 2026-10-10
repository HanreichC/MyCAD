# SPDX-License-Identifier: LGPL-2.1-or-later
"""Bestandsaufnahme der Optik: typische Fenster/Menüs öffnen und fotografieren (Screenshots <OUT>.*.png)."""
from harness import *


def open_tree():
    for t in visible(QtWidgets.QTreeWidget):
        t.expandAll()


def context_menu_shot(name, widget, pos):
    def grab():
        m = QtWidgets.QApplication.activePopupWidget()
        if m:
            m.grab().save(os.environ["OUT"] + "." + name + ".png"); L("  menu %s: %s" % (name, [a.text() for a in m.actions()]))
            m.close()
    QtCore.QTimer.singleShot(700, grab)
    QtWidgets.QApplication.postEvent(widget, QtGui.QContextMenuEvent(QtGui.QContextMenuEvent.Mouse, pos, widget.mapToGlobal(pos)))


from PySide6 import QtGui


def right_click_shot(name):
    def grab():
        m = QtWidgets.QApplication.activePopupWidget()
        if m:
            m.grab().save(os.environ["OUT"] + "." + name + ".png"); L("  menu %s: %s" % (name, [a.text() for a in m.actions()]))
            m.close()
        else:
            L("  no menu for " + name)
    QtCore.QTimer.singleShot(700, grab)
    v = view().viewport(); p = QtCore.QPoint(700, 500)
    QtTest.QTest.mousePress(v, QtCore.Qt.RightButton, QtCore.Qt.NoModifier, p)
    QtTest.QTest.mouseRelease(v, QtCore.Qt.RightButton, QtCore.Qt.NoModifier, p)
run([
    ("setup", lambda: make_body(rect(0, 0, 60, 40), 0, 15, "Box")),
    ("tree", open_tree), ("shot tree", lambda: shot("tree")),
    ("view menu", lambda: right_click_shot("viewmenu")),
    ("wait", lambda: None),
    ("select box", lambda: Gui.Selection.addSelection(body("Box"))),
    ("tree menu", lambda: context_menu_shot("treemenu", visible(QtWidgets.QTreeWidget)[0].viewport(), QtCore.QPoint(60, 30))),
    ("wait", lambda: None),
    ("Create Sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick top", lambda: Gui.Selection.addSelection(body("Box"), top_face(body("Box")))),
    ("geometry", lambda: [Gui.ActiveDocument.getInEdit().Object.addGeometry(g) for g in rect(10, 10, 30, 25)]),
    ("constraint", lambda: Gui.ActiveDocument.getInEdit().Object.addConstraint(__import__("Sketcher").Constraint("Horizontal", 0))),
    ("recompute", lambda: App.ActiveDocument.recompute()),
    ("shot sketch", lambda: shot("sketch")),
    ("finish", lambda: click(button("Sketcher_LeaveSketch"))),
    ("msg", lambda: QtCore.QTimer.singleShot(800, lambda: (QtWidgets.QApplication.activeModalWidget().grab().save(os.environ["OUT"] + ".msgbox.png"), QtWidgets.QApplication.activeModalWidget().close()))),
    ("extrude without selection", lambda: (Gui.Selection.clearSelection(), [setattr(p, "Visibility", True) for p in []], click(button("Design_Combine")))),
    ("wait", lambda: None),
])
