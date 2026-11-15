# SPDX-License-Identifier: LGPL-2.1-or-later
"""Skizzenraster nach schnellem Zoomen in der Perspektive (Zoom auf den Cursor neben der Skizze): es deckt den sichtbaren
Bereich der Skizzenebene ab. Vorher richtete es sich nach der Fokusebene der Kamera und wurde ein kleines Feld an
falscher Stelle, sobald der Fokuspunkt vor oder hinter der Skizze lag."""
import math
from PySide6 import QtGui
from pivy import coin
from harness import *

W = ("wait", lambda: None)
mouse = QtGui.QPointingDevice("test mouse", 4712, QtGui.QInputDevice.DeviceType.Mouse, QtGui.QPointingDevice.PointerType.Generic,
                              QtGui.QInputDevice.Capability.Position | QtGui.QInputDevice.Capability.Scroll, 1, 3)


def setup():
    b = make_body(rect(300, 0, 340, 20), 0, 10, "Far")
    Gui.ActiveDocument.ActiveView.setCameraType("Perspective")
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(b, top_face(b)); click(button("Design_CreateSketch"))


def grid_on():
    sk = Gui.ActiveDocument.getInEdit()
    sk.ShowGrid = True


def wheel(clicks, delta, fx, fy):
    v = view(); vp = v.viewport()
    p = QtCore.QPointF(vp.width() * fx, vp.height() * fy)
    for _ in range(clicks):
        QtWidgets.QApplication.sendEvent(v, QtGui.QWheelEvent(p, vp.mapToGlobal(p), QtCore.QPoint(0, 0), QtCore.QPoint(0, delta),
            QtCore.Qt.NoButton, QtCore.Qt.NoModifier, QtCore.Qt.NoScrollPhase, False, QtCore.Qt.MouseEventNotSynthesized, mouse))


def grid_box():
    root = Gui.ActiveDocument.ActiveView.getViewer().getSoRenderManager().getSceneGraph()
    search = coin.SoSearchAction(); search.setName(coin.SbName("GridRoot")); search.setInterest(coin.SoSearchAction.FIRST)
    search.apply(root)
    xs, ys = [], []
    sa = coin.SoSearchAction(); sa.setType(coin.SoLineSet.getClassTypeId()); sa.setInterest(coin.SoSearchAction.ALL)
    sa.apply(search.getPath())
    for i in range(sa.getPaths().getLength()):
        ls = sa.getPaths()[i].getTail()
        vp = ls.vertexProperty.getValue()
        for k in range(vp.vertex.getNum()):
            x, y, _ = vp.vertex[k].getValue()
            if x or y:
                xs.append(x); ys.append(y)
    return (min(xs), max(xs), min(ys), max(ys)) if xs else None


def near_focus():
    """Wie nach Drehen um einen Punkt vor der Skizze: Fokuspunkt weit vor der Skizzenebene"""
    cam = Gui.ActiveDocument.ActiveView.getCameraNode()
    cam.focalDistance = cam.focalDistance.getValue() * 0.05


def covered():
    """Raster deckt den sichtbaren Bereich der Skizzenebene ab (Mitte des Bildes und mindestens 90 % seiner Breite)"""
    s = Gui.ActiveDocument.getInEdit().Object
    v = Gui.ActiveDocument.ActiveView
    cam = v.getCameraNode()
    pos = App.Vector(*cam.position.getValue().getValue())
    rot = cam.orientation.getValue()
    pl = s.getGlobalPlacement(); n = pl.Rotation.multVec(App.Vector(0, 0, 1))

    def on_plane(dx, dy):
        """Sichtstrahl durch den Bildpunkt (dx, dy in -1..1) geschnitten mit der Skizzenebene, in Skizzenkoordinaten"""
        h = cam.heightAngle.getValue() / 2
        vpw = view().viewport(); aspect = vpw.width() / vpw.height()
        d = App.Vector(*rot.multVec(coin.SbVec3f(dx * math.tan(h) * aspect, dy * math.tan(h), -1)).getValue())
        t = (pl.Base - pos).dot(n) / d.dot(n)
        return pl.inverse().multVec(pos + d * t)

    centre, left, right = on_plane(0, 0), on_plane(-1, 0), on_plane(1, 0)
    visible = abs(right.x - left.x)
    box = grid_box()
    ok = box is not None and box[0] <= centre.x <= box[1] and box[2] <= centre.y <= box[3] and (box[1] - box[0]) >= 0.9 * visible
    check("with the camera's focal point far in front of the sketch, the grid still covers the visible sketch plane", ok,
          "grid x %s..%s y %s..%s, visible width %.1f, centre (%.1f, %.1f)" % (box and round(box[0], 1), box and round(box[1], 1),
                                                                            box and round(box[2], 1), box and round(box[3], 1), visible, centre.x, centre.y))


run([("activate", activate), ("setup", setup), W, W, ("grid", grid_on), W,
     ("zoom in", lambda: wheel(25, 120, 0.85, 0.2)), W, ("zoom out", lambda: wheel(12, -120, 0.15, 0.8)), W, W,
     ("near", near_focus), W, ("step", lambda: wheel(1, 120, 0.5, 0.5)), W, W,
     ("covered", covered), ("shot", lambda: shot("grid")),
     ("ortho", lambda: Gui.ActiveDocument.ActiveView.setCameraType("Orthographic"))])
