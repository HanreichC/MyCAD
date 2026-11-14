# SPDX-License-Identifier: LGPL-2.1-or-later
"""Langes Scrollen am Stück: die Kamera bleibt in den Zoom-Grenzen (0,1 mm bis 1 km). Ohne sie lief sie bis 1e-9 bzw.
1e19 mm, das Objekt änderte sich nicht mehr und nur das Raster rechnete (falsch) weiter. Orthografisch und perspektivisch."""
import math
from PySide6 import QtGui
from pivy import coin
from harness import *

W = ("wait", lambda: None)
mouse = QtGui.QPointingDevice("test mouse", 4712, QtGui.QInputDevice.DeviceType.Mouse, QtGui.QPointingDevice.PointerType.Generic,
                              QtGui.QInputDevice.Capability.Position | QtGui.QInputDevice.Capability.Scroll, 1, 3)


def camera():
    return Gui.ActiveDocument.ActiveView.getCameraNode()


def size():
    """Bildhöhe (orthografisch) bzw. Abstand zum Brennpunkt (perspektivisch), mm"""
    c = camera()
    return c.height.getValue() if c.isOfType(coin.SoOrthographicCamera.getClassTypeId()) else c.focalDistance.getValue()


def wheel(clicks, delta):
    """Mausrad neben der Bildmitte (Zoom auf den Cursor). An den Viewer: künstliche Rad-Ereignisse gibt Qt nicht vom
    Viewport an ihn weiter, echte schon"""
    v = view(); vp = v.viewport()
    p = QtCore.QPointF(vp.width() * 0.7, vp.height() * 0.4)
    for _ in range(clicks):
        QtWidgets.QApplication.sendEvent(v, QtGui.QWheelEvent(p, vp.mapToGlobal(p), QtCore.QPoint(0, 0), QtCore.QPoint(0, delta),
            QtCore.Qt.NoButton, QtCore.Qt.NoModifier, QtCore.Qt.NoScrollPhase, False, QtCore.Qt.MouseEventNotSynthesized, mouse))


def limited(kind, low, high):
    s = size(); pos = camera().position.getValue()
    ok = low <= s <= high and all(math.isfinite(x) and abs(x) < 1e7 for x in pos)
    check("%s: after long scrolling the view stays between 0.1 mm and 1 km" % kind, ok,
          "size=%.4g pos=%s" % (s, tuple(round(x, 1) for x in pos)))


def steps(kind):
    return [("%s in" % kind, lambda: wheel(150, 120)), W, ("%s min" % kind, lambda: limited(kind + " zoomed in", 0.0999, 0.11)),
            ("%s out" % kind, lambda: wheel(300, -120)), W, ("%s max" % kind, lambda: limited(kind + " zoomed out", 0.9e6, 1.0001e6)),
            ("%s back" % kind, lambda: Gui.SendMsgToActiveView("ViewFit")), W]


run([("box", lambda: (make_body(rect(0, 0, 40, 20), 0, 10, "Box"), Gui.SendMsgToActiveView("ViewFit"))), W,
     ("ortho", lambda: Gui.ActiveDocument.ActiveView.setCameraType("Orthographic")), W, *steps("orthographic"),
     ("persp", lambda: Gui.ActiveDocument.ActiveView.setCameraType("Perspective")), W, *steps("perspective"),
     ("reset", lambda: Gui.ActiveDocument.ActiveView.setCameraType("Orthographic"))])
