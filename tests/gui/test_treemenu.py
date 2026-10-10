# SPDX-License-Identifier: LGPL-2.1-or-later
"""Rechtsklick im Browser zeigt das MyCAD-Menü (Show/Hide, Rename, Move, Export, Delete)."""
from harness import *
from PySide6 import QtGui


def open_menu():
    tree = visible(QtWidgets.QTreeWidget)[0]
    tree.expandAll()
    item = tree.findItems("Box", QtCore.Qt.MatchRecursive)[0]
    tree.setCurrentItem(item)
    pos = tree.visualItemRect(item).center()
    L("selection=%s" % [o.Name for o in Gui.Selection.getSelection()])

    def grab():
        m = QtWidgets.QApplication.activePopupWidget()
        L("menu=%s" % ([a.text() for a in m.actions()] if m else None))
        if m:
            m.grab().save(os.environ["OUT"] + ".menu.png"); m.close()
    QtCore.QTimer.singleShot(800, grab)
    QtWidgets.QApplication.postEvent(tree.viewport(), QtGui.QContextMenuEvent(QtGui.QContextMenuEvent.Mouse, pos, tree.viewport().mapToGlobal(pos)))


run([
    ("setup", lambda: make_body(rect(0, 0, 60, 40), 0, 15, "Box")),
    ("open", open_menu), ("wait", lambda: None),
])
