# SPDX-License-Identifier: LGPL-2.1-or-later
"""Umbenennen im Browser mit Shift als mittlerer Maustaste: Großbuchstaben tippen darf das
Feld nicht schließen (Feld liegt im Glass-Panel, Qt meldet die 3D-Ansicht als Fokus). Erwartet: der Körper heißt
"kneu" (QTest liefert auch mit Shift den Text 'k')"""
from harness import *

grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")


def tree():
    return visible(QtWidgets.QTreeWidget)[0]


def open_editor():
    """wie Rechtsklick → Rename (Shell: tree->editItem). Über das Menü war der Test wackelig: ein simuliertes Menü
    öffnete das Feld mal, mal nicht; geprüft wird hier das Tippen, nicht das Menü"""
    t = tree(); t.expandAll()
    t.editItem(t.findItems("Box", QtCore.Qt.MatchRecursive)[0])


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
    ("activate", activate), ("rename", open_editor), ("wait", lambda: None),
    ("type", type_name),
    ("enter", lambda: QtTest.QTest.keyClick(mw.windowHandle(), QtCore.Qt.Key_Return)),
    ("result", lambda: check("capitals typed with shift (= middle mouse button) rename the body",
                             [b.Label for b in doc().Objects if b.TypeId == "Design::Body"] == ["kneu"],
                             str([b.Label for b in doc().Objects if b.TypeId == "Design::Body"]))),
    ("keys off", lambda: grp.SetString("MouseKeys", "[]")),
])
