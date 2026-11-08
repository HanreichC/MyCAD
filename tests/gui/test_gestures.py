# SPDX-License-Identifier: LGPL-2.1-or-later
"""Trackpad-Gesten ohne Tasten: 3 Finger wischen dreht, 2 Finger scrollen schiebt, Spreizen zoomt."""
from harness import *
from PySide6 import QtGui

App.ParamGet("User parameter:BaseApp/Preferences/View").SetString("NavigationStyle", "Gui::RevitNavigationStyle")


def cam(key):
    c = Gui.ActiveDocument.ActiveView.getCamera()
    return [l.strip() for l in c.splitlines() if l.strip().startswith(key)][0]


def gesture(kind, fingers, value=0.0, delta=QtCore.QPointF()):
    vp = view().viewport(); p = QtCore.QPointF(vp.rect().center())
    ev = QtGui.QNativeGestureEvent(kind, QtGui.QPointingDevice.primaryPointingDevice(), fingers,
                                   p, p, QtCore.QPointF(vp.mapToGlobal(p.toPoint())), value, delta)
    QtWidgets.QApplication.sendEvent(vp, ev)


def swipe3():
    gesture(QtCore.Qt.BeginNativeGesture, 3)
    for _ in range(10):
        gesture(QtCore.Qt.PanNativeGesture, 3, delta=QtCore.QPointF(20, 5))
    gesture(QtCore.Qt.EndNativeGesture, 3)


def pinch():
    gesture(QtCore.Qt.BeginNativeGesture, 2)
    for _ in range(5):
        gesture(QtCore.Qt.ZoomNativeGesture, 2, value=0.1)
    gesture(QtCore.Qt.EndNativeGesture, 2)


def scroll2():
    # an die Ansicht selbst: echte Mausrad-Ereignisse reicht Qt vom Viewport dorthin weiter, künstliche nicht
    vp = view(); p = QtCore.QPointF(vp.rect().center()); g = QtCore.QPointF(vp.mapToGlobal(p.toPoint()))
    for phase in (QtCore.Qt.ScrollBegin, QtCore.Qt.ScrollUpdate, QtCore.Qt.ScrollUpdate, QtCore.Qt.ScrollEnd):
        d = QtCore.QPoint(0, 0) if phase in (QtCore.Qt.ScrollBegin, QtCore.Qt.ScrollEnd) else QtCore.QPoint(40, 20)
        QtWidgets.QApplication.sendEvent(vp, QtGui.QWheelEvent(p, g, d, d, QtCore.Qt.NoButton, QtCore.Qt.NoModifier, phase, False))


def check(name, key, action):
    before = cam(key); action(); after = cam(key)
    L("%s %s: %s" % ("OK  " if before != after else "FAIL", name, after))


def pan_speed():
    """Regler Schieben (2 Finger): 200 % schiebt etwa doppelt so weit wie 100 %"""
    grp = App.ParamGet("User parameter:BaseApp/Preferences/View")
    def moved():
        a = [float(v) for v in cam("position").split()[1:]]; scroll2(); b = [float(v) for v in cam("position").split()[1:]]
        return sum((x - y) ** 2 for x, y in zip(a, b)) ** 0.5
    grp.SetFloat("TrackpadPanSpeed", 1.0); one = moved()
    grp.SetFloat("TrackpadPanSpeed", 2.0); two = moved()
    grp.SetFloat("TrackpadPanSpeed", 1.0)
    L("%s Tempo Schieben: 100%% = %.2f, 200%% = %.2f" % ("OK  " if 1.8 < two / one < 2.2 else "FAIL", one, two))


run([
    ("setup", lambda: make_body(rect(0, 0, 60, 40), 0, 15, "Box")),
    ("3 Finger drehen", lambda: check("3 Finger drehen", "orientation", swipe3)),
    ("2 Finger schieben", lambda: check("2 Finger schieben", "position", scroll2)),
    ("Spreizen zoomt", lambda: check("Spreizen zoomt", "height", pinch)),
    ("Tempo Schieben", pan_speed),
])
