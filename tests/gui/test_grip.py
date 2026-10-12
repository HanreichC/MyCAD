# SPDX-License-Identifier: LGPL-2.1-or-later
"""Fenster verschieben: Griff links im Panel der Fensterknöpfe (schmales, nicht maximiertes Fenster).
Ob Wayland das Fenster wirklich bewegt, sieht nur ein echter Mausklick; hier: Griff ist da und nimmt den Klick an."""
import os
from harness import *
import harness


def handle():
    return [w for w in visible(QtWidgets.QLabel) if w.toolTip().startswith("Drag to move")][0]


def press_handle():
    h = handle()
    p = view().viewport().mapTo(mw, harness._pos(h))
    L("handle size=%s at %s" % (h.size().toTuple(), p))
    win = mw.windowHandle()
    QtTest.QTest.mouseMove(win, p)
    QtTest.QTest.mousePress(win, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)
    QtTest.QTest.mouseRelease(win, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)


run([
    ("normal", lambda: mw.showNormal()), ("wait", lambda: None),
    ("size", lambda: mw.resize(1300, 850)), ("wait", lambda: None),
    ("press", press_handle), ("shot", lambda: shot("grip")),
    ("restore", lambda: mw.showMaximized()),
])
