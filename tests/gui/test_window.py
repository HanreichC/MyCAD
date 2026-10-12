# SPDX-License-Identifier: LGPL-2.1-or-later
"""Fensterknöpfe rechts oben: Maximieren/Wiederherstellen und Minimieren ändern den Fensterzustand."""
from harness import *


def btn(tip):
    return [b for b in visible(QtWidgets.QToolButton) if b.toolTip() in tip][0]


def real_click(b):
    # wie echte Eingabe: über das Fenster an die Bildschirmposition des Knopfs
    import harness
    pos = view().viewport().mapTo(mw, harness._pos(b))
    win = mw.windowHandle()
    QtTest.QTest.mouseMove(win, pos)
    QtTest.QTest.mouseClick(win, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, pos)


def state():
    return "state=%s maximized=%s size=%s normalGeometry=%s exposed=%s" % (int(mw.windowState().value), mw.isMaximized(), mw.size().toTuple(),
        mw.normalGeometry().getRect(), mw.windowHandle().isExposed())


run([
    ("normal", lambda: mw.showNormal()), ("wait", lambda: None),
    ("full size", lambda: mw.resize(mw.screen().availableGeometry().size())), ("wait", lambda: None),
    ("maximize", lambda: mw.showMaximized()), ("wait", lambda: None),
    ("start", lambda: L("start (normale Größe = ganzer Bildschirm wie bei dir): " + state())),
    ("toggle max", lambda: real_click(btn(("Maximize", "Restore")))),
    ("wait", lambda: None),
    ("after toggle", lambda: L("nach Wiederherstellen (erwartet ~75%% der Fläche): " + state())),
    ("toggle back", lambda: real_click(btn(("Maximize", "Restore")))),
    ("wait", lambda: None),
    ("after back", lambda: L("nach zweitem Klick: " + state())),
    ("minimize", lambda: click(btn(("Minimize",)))),
    ("wait", lambda: None),
    ("after min", lambda: L("nach Minimieren: " + state())),
    ("restore", lambda: mw.showMaximized()),
])
