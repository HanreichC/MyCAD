# SPDX-License-Identifier: LGPL-2.1-or-later
"""Reinzoomen kommt immer bis an den Körper unter dem Cursor (perspektivisch). Vorher zoomte die Kamera nur auf ihren
Brennpunkt zu und kam ihm nie ganz nahe: lag er (nach Drehen, Schieben, Zoomen woanders) vor dem Körper, blieb der Zoom
in der Luft stehen. Der Punkt unter dem Cursor bleibt dabei unter dem Cursor, der Körper wird nicht weggeschnitten."""
import math
from PySide6 import QtGui
from pivy import coin
from harness import *

W = ("wait", lambda: None)
mouse = QtGui.QPointingDevice("test mouse", 4713, QtGui.QInputDevice.DeviceType.Mouse, QtGui.QPointingDevice.PointerType.Generic,
                              QtGui.QInputDevice.Capability.Position | QtGui.QInputDevice.Capability.Scroll, 1, 3)
FX, FY = 0.62, 0.45  # Cursor neben der Bildmitte
seen = {}


def camera():
    return Gui.ActiveDocument.ActiveView.getCameraNode()


def cursor():
    vp = view().viewport()
    return QtCore.QPointF(vp.width() * FX, vp.height() * FY)


def wheel(clicks, delta):
    v = view(); vp = v.viewport(); p = cursor()
    for _ in range(clicks):
        QtWidgets.QApplication.sendEvent(v, QtGui.QWheelEvent(p, vp.mapToGlobal(p), QtCore.QPoint(0, 0), QtCore.QPoint(0, delta),
            QtCore.Qt.NoButton, QtCore.Qt.NoModifier, QtCore.Qt.NoScrollPhase, False, QtCore.Qt.MouseEventNotSynthesized, mouse))


def under_cursor():
    p = cursor(); vp = view().viewport()
    info = Gui.ActiveDocument.ActiveView.getObjectInfo((int(p.x()), int(vp.height() - p.y())))
    return App.Vector(info["x"], info["y"], info["z"]) if info else None


def color_at_cursor():
    p = cursor(); img = view().viewport().grab().toImage()
    return img.pixelColor(int(p.x() * img.width() / view().viewport().width()), int(p.y() * img.height() / view().viewport().height()))


def setup():
    Gui.ActiveDocument.ActiveView.setCameraType("Perspective")
    c = camera()
    c.orientation.setValue(coin.SbRotation())  # von oben, ohne Animation
    c.position.setValue(coin.SbVec3f(15, 12, 120))
    c.focalDistance.setValue(60)  # Brennpunkt bei z = 60, weit über dem Körper (Oberseite z = 10)


def before():
    seen["point"] = under_cursor(); seen["color"] = color_at_cursor()
    check("the box is under the cursor", seen["point"] is not None and abs(seen["point"].z - 10) < 0.01, str(seen["point"]))


def close():
    z = camera().position.getValue()[2]
    check("zooming in reaches the box (camera less than 1 mm above its top)", 10 < z < 11, "camera z=%.3f" % z)
    p = under_cursor()
    check("the point under the cursor stays under the cursor", p is not None and (p - seen["point"]).Length < 0.5,
          "%s -> %s" % (seen["point"], p))
    a, b = seen["color"], color_at_cursor()
    check("the box is still drawn at the cursor (not cut away)", abs(a.red() - b.red()) + abs(a.green() - b.green()) + abs(a.blue() - b.blue()) < 40,
          "%s -> %s" % (a.name(), b.name()))


def far():
    z = camera().position.getValue()[2]
    check("zooming out again works", z > 100, "camera z=%.1f" % z)


run([("box", lambda: (make_body(rect(0, 0, 40, 20), 0, 10, "Box"), Gui.SendMsgToActiveView("ViewFit"))), W,
     ("setup", setup), W, ("s1", lambda: shot("setup")), ("before", before),
     ("in", lambda: wheel(120, 120)), W, ("s2", lambda: shot("close")), ("close", close),
     ("out", lambda: wheel(40, -120)), W, ("far", far),
     ("reset", lambda: Gui.ActiveDocument.ActiveView.setCameraType("Orthographic"))])
