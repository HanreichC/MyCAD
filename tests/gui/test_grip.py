# SPDX-License-Identifier: LGPL-2.1-or-later
"""Fenster verschieben: die Kopfleiste geht über die ganze Fensterbreite, jede freie Stelle darin ist Griff, ein
Griff-Symbol gibt es nicht mehr. Ob Wayland das Fenster wirklich bewegt, sieht nur ein echter Mausklick; hier: die
Leiste ist so breit wie das Fenster und es bleibt genug Fläche ohne Knopf zum Anfassen."""
from harness import *


def check():
    close = [b for b in visible(QtWidgets.QToolButton) if b.toolTip() == "Close"][0]
    h = close.parentWidget().parentWidget()
    y = close.parentWidget().y() + close.y() + close.height() // 2  # Reihe der Fensterknöpfe
    free = sum(not isinstance(h.childAt(x, y), QtWidgets.QAbstractButton) for x in range(h.width()))
    L("header width=%d view=%d free=%d" % (h.width(), view().width(), free))
    assert h.width() == view().width() - 2 * 12, "Kopfleiste nicht über die ganze Breite"
    assert 100 <= free < h.width(), "zu wenig Fläche zum Anfassen (oder die Knöpfe fehlen)"
    assert "MyCAD" in [l.text() for l in h.findChildren(QtWidgets.QLabel, options=QtCore.Qt.FindDirectChildrenOnly)], "Name fehlt in der Kopfleiste"
    tool = button("Std_New")
    for tip in ("Minimize", "Maximize", "Close"):
        b = [b for b in visible(QtWidgets.QToolButton) if b.toolTip() == tip][0]
        L("%s size=%s icon=%s, tool size=%s icon=%s" % (tip, b.size().toTuple(), b.iconSize().toTuple(), tool.size().toTuple(), tool.iconSize().toTuple()))
        assert b.size() == tool.size() and b.iconSize() == tool.iconSize(), tip + " anders groß als die Toolbar-Knöpfe"
    L("OK")


run([
    ("normal", lambda: mw.showNormal()), ("wait", lambda: None),
    ("size", lambda: mw.resize(1300, 850)), ("wait", lambda: None),
    ("check", check), ("shot", lambda: shot("grip")),
    ("restore", lambda: mw.showMaximized()),
])
