# SPDX-License-Identifier: LGPL-2.1-or-later
"""Maße in der Skizze bleiben gleich groß, wenn sich in der perspektivischen Ansicht die Fokusdistanz der Kamera ändert
(Drehen um einen Punkt weit hinter der Skizze, z. B. am anderen Ende einer 56-cm-Leiste). Vorher maß die Beschriftung
ihre Größe auf der Fokusebene und wurde riesig, bis man die Skizze neu öffnete."""
from pivy import coin
from harness import *
import Sketcher

W = ("wait", lambda: None)
V = App.Vector
S = {}


def setup():
    b = make_body(rect(500, 0, 540, 20), 0, 10, "Far")
    Gui.ActiveDocument.ActiveView.setCameraType("Perspective")
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(b, top_face(b))
    click(button("Design_CreateSketch"))


def dimension():
    s = Gui.ActiveDocument.getInEdit().Object
    a, b = s.Placement.inverse().multVec(V(505, 5, 10)), s.Placement.inverse().multVec(V(525, 5, 10))
    i = s.addGeometry(Part.LineSegment(V(a.x, a.y, 0), V(b.x, b.y, 0)))
    s.addConstraint(Sketcher.Constraint("Distance", i, 20.0))
    doc().recompute()


def label_size():
    """Ausdehnung des ersten Maß-Knotens (SoDatumLabel) in Weltkoordinaten, mit der Kamera der Ansicht berechnet"""
    root = Gui.ActiveDocument.ActiveView.getViewer().getSoRenderManager().getSceneGraph()
    search = coin.SoSearchAction(); search.setType(coin.SoType.fromName("SoDatumLabel")); search.setInterest(coin.SoSearchAction.FIRST)
    search.apply(root)
    path = search.getPath()
    vp = view().viewport()
    box = coin.SoGetBoundingBoxAction(coin.SbViewportRegion(vp.width(), vp.height()))
    box.apply(path)
    bb = box.getBoundingBox()
    lo, hi = bb.getMin().getValue(), bb.getMax().getValue()
    return max(hi[0] - lo[0], hi[1] - lo[1], hi[2] - lo[2])


def far_focus():
    S["before"] = label_size()
    cam = Gui.ActiveDocument.ActiveView.getCameraNode()
    cam.focalDistance = cam.focalDistance.getValue() * 20  # Drehpunkt weit hinter der Skizze


def same():
    after = label_size()
    check("dimension keeps its size when the camera's focal distance changes (perspective)",
          abs(after - S["before"]) < 0.05 * S["before"], "before=%.3f after=%.3f" % (S["before"], after))


run([("activate", activate), ("setup", setup), W, W, ("fit", lambda: Gui.SendMsgToActiveView("ViewFit")), W,
     ("dimension", dimension), W, ("far", far_focus), W, ("same", same),
     ("ortho", lambda: Gui.ActiveDocument.ActiveView.setCameraType("Orthographic"))])
