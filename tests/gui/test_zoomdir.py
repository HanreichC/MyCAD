# SPDX-License-Identifier: LGPL-2.1-or-later
"""Zoomrichtung getrennt für Mausrad und Trackpad: dieselbe Scrollbewegung erreicht das 3D-Fenster beim Trackpad
umgekehrt, sobald dessen Einstellung von der des Mausrads abweicht (Spion am 3D-Fenster liest die Richtung mit)."""
from PySide6 import QtGui
from harness import *

grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")
pad = QtGui.QPointingDevice("test trackpad", 4711, QtGui.QInputDevice.DeviceType.TouchPad, QtGui.QPointingDevice.PointerType.Finger,
                            QtGui.QInputDevice.Capability.Position | QtGui.QInputDevice.Capability.Scroll, 2, 0)
mouse = QtGui.QPointingDevice("test mouse", 4712, QtGui.QInputDevice.DeviceType.Mouse, QtGui.QPointingDevice.PointerType.Generic,
                              QtGui.QInputDevice.Capability.Position | QtGui.QInputDevice.Capability.Scroll, 1, 3)


class Spy(QtCore.QObject):
    def eventFilter(self, obj, ev):
        if ev.type() == QtCore.QEvent.Wheel:
            seen.append(ev.angleDelta().y())
        return False


seen = []
spy = Spy()


def scroll(device, tag):
    vp = view().viewport()
    vp.installEventFilter(spy)
    seen.clear()
    p = QtCore.QPointF(vp.width() / 2, vp.height() / 2)
    ev = QtGui.QWheelEvent(p, vp.mapToGlobal(p), QtCore.QPoint(0, 0), QtCore.QPoint(0, 120), QtCore.Qt.NoButton,
                           QtCore.Qt.NoModifier, QtCore.Qt.NoScrollPhase, False, QtCore.Qt.MouseEventNotSynthesized, device)
    QtWidgets.QApplication.sendEvent(vp, ev)
    L("%s: 3D-Fenster bekommt %s" % (tag, seen))


def scroll_phase(tag):
    """Wayland: Trackpad-Scrollen kommt vom selben Gerät wie die Maus, aber mit Scrollphase und Pixel-Schritten"""
    vp = view().viewport(); seen.clear(); p = QtCore.QPointF(vp.width() / 2, vp.height() / 2)
    ev = QtGui.QWheelEvent(p, vp.mapToGlobal(p), QtCore.QPoint(0, 12), QtCore.QPoint(0, 120), QtCore.Qt.NoButton,
                           QtCore.Qt.NoModifier, QtCore.Qt.ScrollUpdate, False, QtCore.Qt.MouseEventNotSynthesized, mouse)
    QtWidgets.QApplication.sendEvent(vp, ev)
    L("%s: 3D-Fenster bekommt %s" % (tag, seen))


run([
    ("body", lambda: (make_body(rect(0, 0, 40, 30), 0, 10, "Box"), Gui.SendMsgToActiveView("ViewFit"))),
    ("same", lambda: grp.SetBool("InvertTrackpadZoom", App.ParamGet("User parameter:BaseApp/Preferences/View").GetBool("InvertZoom", True))),
    ("m1", lambda: scroll(mouse, "Mausrad")), ("t1", lambda: scroll(pad, "Trackpad (gleich eingestellt)")),
    ("flip", lambda: grp.SetBool("InvertTrackpadZoom", not App.ParamGet("User parameter:BaseApp/Preferences/View").GetBool("InvertZoom", True))),
    ("m2", lambda: scroll(mouse, "Mausrad")), ("t2", lambda: scroll(pad, "Trackpad (umgekehrt eingestellt)")),
    ("phase", lambda: scroll_phase("Trackpad über die Scrollphase erkannt (umgekehrt eingestellt)")),
    ("reset", lambda: grp.RemBool("InvertTrackpadZoom")),
])
