# SPDX-License-Identifier: LGPL-2.1-or-later
"""Drehpunkt nach dem Zentrieren (2026-11-17): Drehmodus "Mitte des Körpers unter dem Cursor". Nach dem Zentrieren
steht die Maus neben dem Körper (Wayland erlaubt nicht, sie hinzusetzen); Drehen, das im Leeren startet, drehte dann um
die Mitte aller Körper. Jetzt um den zentrierten: seine Mitte bleibt beim Drehen auf dem Bildschirm stehen."""
from harness import *

VIEW = "User parameter:BaseApp/Preferences/View"


def screen(p):
    v = view(); x, y = Gui.ActiveDocument.ActiveView.getPointOnViewport(p)
    dpr = v.viewport().devicePixelRatioF()
    return QtCore.QPointF(x / dpr, v.viewport().height() - y / dpr)


def center(label):
    return body(label).Shape.BoundBox.Center


def send(kind, pos, button, buttons, mods=QtCore.Qt.NoModifier):
    vp = view().viewport()
    ev = QtGui.QMouseEvent(kind, QtCore.QPointF(pos), vp.mapToGlobal(QtCore.QPointF(pos)), button, buttons, mods)
    QtWidgets.QApplication.sendEvent(vp, ev)


def middle_click(label):
    p = screen(center(label))
    send(QtCore.QEvent.MouseButtonPress, p, QtCore.Qt.MiddleButton, QtCore.Qt.MiddleButton)
    send(QtCore.QEvent.MouseButtonRelease, p, QtCore.Qt.MiddleButton, QtCore.Qt.NoButton)


S = {}


def orbit_in_empty_space():
    vp = view().viewport()
    start = QtCore.QPointF(vp.width() * 0.9, vp.height() * 0.15)  # oben rechts: kein Körper
    S["a"], S["b"] = screen(center("A")), screen(center("B"))
    shift, mid = QtCore.Qt.ShiftModifier, QtCore.Qt.MiddleButton
    send(QtCore.QEvent.MouseButtonPress, start, mid, mid, shift)
    for k in range(1, 13):
        send(QtCore.QEvent.MouseMove, start + QtCore.QPointF(-12 * k, 6 * k), QtCore.Qt.NoButton, mid, shift)
    send(QtCore.QEvent.MouseButtonRelease, start + QtCore.QPointF(-144, 72), mid, QtCore.Qt.NoButton, shift)


def moved(label, before):
    d = screen(center(label)) - before
    return (d.x() ** 2 + d.y() ** 2) ** 0.5


run([
    ("style", lambda: (App.ParamGet(VIEW).SetString("NavigationStyle", "Gui::RevitNavigationStyle"),
                       App.ParamGet(VIEW).SetInt("RotationMode", 3))),
    ("A", lambda: make_body(rect(0, 0, 20, 20), 0, 10, "A")),
    ("B", lambda: make_body(rect(150, 0, 170, 20), 0, 10, "B")),
    ("iso", lambda: (Gui.ActiveDocument.ActiveView.viewIsometric(), Gui.SendMsgToActiveView("ViewFit"))),
    ("center A", lambda: middle_click("A")),
    ("orbit", orbit_in_empty_space),
    ("pivot", lambda: check("orbit in empty space turns around the body centered last",
                            moved("A", S["a"]) < 4 and moved("B", S["b"]) > 20,
                            "A moved %.1f px, B moved %.1f px" % (moved("A", S["a"]), moved("B", S["b"])))),
])
