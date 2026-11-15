# SPDX-License-Identifier: LGPL-2.1-or-later
"""Skizze öffnen zoomt auf die Skizze: sie füllt den freien Teil der Ansicht (wie Fusion), auch wenn sie klein auf
einer großen Körperfläche liegt. Eine leere Skizze auf einer Fläche zeigt die Fläche. Orthografisch und perspektivisch."""
from harness import *

V = App.Vector
state = {}
W = ("wait", lambda: None)


def setup():
    state["box"] = make_body(rect(0, 0, 200, 100), 0, 5, "Box")
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(doc().Name, state["box"].Name, top_face(state["box"]))
    Gui.runCommand("Design_CreateSketch")


def draw():
    s = Gui.ActiveDocument.getInEdit().Object; state["sketch"] = s
    for g in rect(150, 60, 162, 66):
        s.addGeometry(g)
    doc().recompute()


def reopen(kind):
    Gui.ActiveDocument.resetEdit()
    Gui.ActiveDocument.ActiveView.setCameraType(kind)
    Gui.SendMsgToActiveView("ViewFit")
    QtCore.QTimer.singleShot(600, lambda: Gui.ActiveDocument.setEdit(state["sketch"].Name))


def extent(points):
    """Ausdehnung der Punkte in Anteilen des freien Teils der Ansicht (Breite, Höhe) und ob alle darin liegen"""
    v = Gui.ActiveDocument.ActiveView; vp = view().viewport(); dpr = vp.devicePixelRatioF(); free = view().property("freeArea")
    px = [v.getPointOnViewport(p) for p in points]
    xs = [(p[0] / dpr / vp.width() - free.x()) / free.width() for p in px]
    ys = [(1 - p[1] / dpr / vp.height() - free.y()) / free.height() for p in px]
    inside = all(-0.001 <= x <= 1.001 for x in xs) and all(-0.001 <= y <= 1.001 for y in ys)
    return max(xs) - min(xs), max(ys) - min(ys), inside


def fills(kind):
    s = state["sketch"]
    w, h, inside = extent([s.Placement.multVec(V(x, y, 0)) for x in (150, 162) for y in (60, 66)])
    check("%s: the opened sketch fills the free part of the view" % kind, inside and max(w, h) > 0.9, "w=%.2f h=%.2f inside=%s" % (w, h, inside))
    shot("open_fit_" + kind.lower())


def empty():
    Gui.ActiveDocument.resetEdit()
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(doc().Name, state["box"].Name, top_face(state["box"]))
    Gui.runCommand("Design_CreateSketch")


def face_shown():
    w, h, inside = extent([V(x, y, 5) for x in (0, 200) for y in (0, 100)])
    check("an empty sketch on a face shows the whole face", inside and max(w, h) > 0.9, "w=%.2f h=%.2f inside=%s" % (w, h, inside))


run([("setup", setup), W, ("draw", draw), W,
     ("ortho", lambda: reopen("Orthographic")), W, W, ("ortho fills", lambda: fills("Orthographic")),
     ("persp", lambda: reopen("Perspective")), W, W, ("persp fills", lambda: fills("Perspective")),
     ("empty", empty), W, W, ("face", face_shown),
     ("leave", lambda: (Gui.ActiveDocument.resetEdit(), Gui.ActiveDocument.ActiveView.setCameraType("Orthographic")))])
