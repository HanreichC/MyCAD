# SPDX-License-Identifier: LGPL-2.1-or-later
"""Fenster nach MyStyle § 7.3: Sidebar von oben bis unten mit dem Namen, Fensterknöpfe in eigener Kapsel mit nur drei
Knöpfen, Toolbar in der Fenstermitte auf gleicher Höhe, App-Aktionen unten in der Sidebar, freie Stelle der
Titelzeile ist Griff. Ob Wayland das Fenster wirklich bewegt, sieht nur ein echter Mausklick."""
from harness import *
import harness


def top_of(w):
    return harness._pos(w).y() - w.height() // 2


def panel_rect(w):
    """Lage des Glas-Panels eines Widgets in der Ansicht"""
    top = w
    while top.parentWidget():
        top = top.parentWidget()
    proxy = top.graphicsProxyWidget(); harness._keep.extend([top, proxy])
    return view().mapFromScene(proxy.mapToScene(QtCore.QRectF(0, 0, top.width(), top.height()))).boundingRect()


def tip(text):
    return [b for b in visible(QtWidgets.QToolButton) if b.toolTip() == text][0]


def window():
    close = tip("Close")
    capsule = panel_rect(close); tree = visible(QtWidgets.QTreeWidget)[0]; sidebar = panel_rect(tree); bar = panel_rect(button("Std_New"))
    check("sidebar from top to bottom at the inset", sidebar.top() == 12 and abs(sidebar.bottom() - (view().height() - 12)) <= 1, str(sidebar))
    check("window buttons in their own capsule at the top right", capsule.top() == 12 and abs(capsule.height() - 44) <= 1 and abs(capsule.right() - (view().width() - 12)) <= 1, str(capsule))
    buttons = [b for b in visible(QtWidgets.QToolButton) if panel_rect(b) == capsule]
    # MyCAD-Ausnahme zu MyStyle W-1/W-7: Startseite vorne in der Kapsel, dann die drei Fensterknöpfe
    order = [b.toolTip() for b in sorted(buttons, key=lambda b: harness._pos(b).x())]
    check("capsule holds Home and the three window buttons", order == ["Home", "Minimize", "Maximize", "Close"], str(order))
    check("toolbar centered in the window, same top", bar.top() == 12 and abs(bar.center().x() - view().width() / 2) <= 2, str(bar))
    check("toolbar does not reach the sidebar", bar.left() > sidebar.right(), "%d %d" % (bar.left(), sidebar.right()))
    check("toolbar does not reach the window buttons", bar.right() < capsule.left(), "%d %d" % (bar.right(), capsule.left()))
    names = [l.text() for l in visible(QtWidgets.QLabel) if panel_rect(l) == sidebar]
    check("app name in the sidebar", "MyCAD" in names)
    for t in ("Help (F1)", "Settings (Ctrl+,)"):
        check(t + " at the bottom of the sidebar", panel_rect(tip(t)) == sidebar and harness._pos(tip(t)).y() > sidebar.bottom() - 180)
    free = QtCore.QPoint(capsule.left() - 3, 20)
    check("free spot of the title row is the grip", bar.right() < free.x() and isinstance(view().itemAt(free), QtWidgets.QGraphicsRectItem), str(view().itemAt(free)))
    # gerundete Ecken gehen nur, wenn das native Fenster seinen Alphakanal von Anfang an hat (Shell::prepareWindow)
    check("window has an alpha channel", mw.windowHandle().format().alphaBufferSize() == 8)


def collapsed():
    capsule = panel_rect(tip("Show sidebar")); bar = panel_rect(button("Std_New"))
    check("collapsed: name and button as a capsule at the start of the title row", capsule.left() == 12 and capsule.top() == 12 and abs(capsule.height() - 44) <= 1, str(capsule))
    check("collapsed: toolbar stays centered", bar.left() > capsule.right() and abs(bar.center().x() - view().width() / 2) <= 2, str(bar))


wait = ("wait", lambda: None)
in_order([
    ("normal", lambda: mw.showNormal()), wait,
    ("size", lambda: mw.resize(1700, 900)), wait,
    ("window", window), ("shot", lambda: shot("window")),
    ("collapse", lambda: click(tip("Hide sidebar"))), wait,
    ("collapsed", collapsed), ("shot collapsed", lambda: shot("collapsed")),
    ("expand", lambda: click(tip("Show sidebar"))), wait,
    ("expanded", lambda: check("expanded again", bool(visible(QtWidgets.QTreeWidget)))),
    ("restore", lambda: mw.showMaximized()),
])
