# SPDX-License-Identifier: LGPL-2.1-or-later
"""Umbenennen im Browser (Rechtsklick → Rename) mit Shift als mittlerer Maustaste: Großbuchstaben tippen darf das
Feld nicht schließen (Feld liegt im Glass-Panel, Qt meldet die 3D-Ansicht als Fokus). Erwartet: bodies=['kneu']
(QTest liefert auch mit Shift den Text 'k')"""
from harness import *
from PySide6 import QtGui

grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")


def tree():
    return visible(QtWidgets.QTreeWidget)[0]


def open_menu():
    t = tree(); t.expandAll()
    item = t.findItems("Box", QtCore.Qt.MatchRecursive)[0]
    t.setCurrentItem(item)
    pos = t.visualItemRect(item).center()

    def pick():
        m = [w for w in visible(QtWidgets.QMenu)][0]
        [a for a in m.actions() if a.text() == "Rename"][0].trigger(); m.close()
    QtCore.QTimer.singleShot(800, pick)
    QtWidgets.QApplication.postEvent(t.viewport(), QtGui.QContextMenuEvent(QtGui.QContextMenuEvent.Keyboard, pos, t.viewport().mapToGlobal(pos)))


def type_name():
    win = mw.windowHandle()
    vp = view().viewport(); QtTest.QTest.mouseMove(vp, vp.rect().center())  # Zeiger über dem 3D-Fenster
    QtTest.QTest.keyClick(win, QtCore.Qt.Key_A, QtCore.Qt.ControlModifier)
    QtTest.QTest.keyPress(win, QtCore.Qt.Key_Shift)
    QtTest.QTest.keyClick(win, QtCore.Qt.Key_K, QtCore.Qt.ShiftModifier)
    QtTest.QTest.keyRelease(win, QtCore.Qt.Key_Shift)
    for k in (QtCore.Qt.Key_N, QtCore.Qt.Key_E, QtCore.Qt.Key_U):
        QtTest.QTest.keyClick(win, k)


run([
    ("setup", lambda: make_body(rect(0, 0, 60, 40), 0, 15, "Box")),
    ("shift = middle", lambda: grp.SetString("MouseKeys", '[{"key":%d,"button":"middle","mode":"hold"}]' % int(QtCore.Qt.Key_Shift))),
    ("rename", open_menu), ("wait", lambda: None),
    ("type", type_name),
    ("enter", lambda: QtTest.QTest.keyClick(mw.windowHandle(), QtCore.Qt.Key_Return)),
    ("result", lambda: L("bodies=%s" % [b.Label for b in doc().Objects if b.TypeId == "Design::Body"])),
    ("keys off", lambda: grp.SetString("MouseKeys", "[]")),
])
