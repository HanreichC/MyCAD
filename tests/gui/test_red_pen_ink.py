# SPDX-License-Identifier: LGPL-2.1-or-later
"""Rotstift-Tinte liegt auf dem Modell, nicht auf dem Blatt davor: echter Mausstrich über die Oberseite eines Quaders
(iso), danach steht der Strich (wie gezeigt) auf dem Quader; gedreht schwebt er nicht im Raum. Bilder <OUT>.write.png
und <OUT>.turned.png"""
from harness import *
import Part
from PySide6 import QtGui

state = {}


def setup():
    state["body"] = make_body(rect(0, 0, 40, 30), 0, 10, "Box")
    for o in doc().Objects:
        if o.TypeId == "Sketcher::SketchObject":
            o.Visibility = False
    Gui.SendMsgToActiveView("ViewAxo")
    Gui.SendMsgToActiveView("ViewFit")


def send(kind, p, button, buttons):
    """Mausereignis direkt an die 3D-Ansicht (wie test_scribble)"""
    vp = view().viewport()
    QtWidgets.QApplication.sendEvent(vp, QtGui.QMouseEvent(kind, p, vp.mapToGlobal(p.toPoint()), button, buttons,
                                                           QtCore.Qt.NoModifier))


def write():
    """Strich quer über die Mitte der Oberseite (Bildschirmpunkt der Mitte, ± 30 px)"""
    pt = Gui.ActiveDocument.ActiveView.getPointOnViewport(App.Vector(20, 15, 10))
    vp = view().viewport(); dpr = vp.devicePixelRatioF()
    c = QtCore.QPointF(pt[0] / dpr, vp.height() - pt[1] / dpr)
    pts = [c + QtCore.QPointF(-30 + 3 * k, 4 * ((k % 4) - 2)) for k in range(21)]
    send(QtCore.QEvent.MouseButtonPress, pts[0], QtCore.Qt.LeftButton, QtCore.Qt.LeftButton)
    for p in pts[1:]:
        send(QtCore.QEvent.MouseMove, p, QtCore.Qt.NoButton, QtCore.Qt.LeftButton)
    send(QtCore.QEvent.MouseButtonRelease, pts[-1], QtCore.Qt.LeftButton, QtCore.Qt.NoButton)


def on_model():
    s = [o for o in doc().Objects if o.TypeId == "Design::Scribble"][-1]
    if not s.Counts:
        check("the red pen stroke lies on the model", False, "no stroke"); return
    n = s.Normals[-1]; n.normalize()
    depth = s.Depths[-1] if len(s.Depths) == len(s.Counts) else 0
    shown = [p - n * max(0, depth - 0.2) for p in s.Points[-s.Counts[-1]:]]
    gap = max(state["body"].Shape.distToShape(Part.Vertex(p))[0] for p in shown)
    sheet = max(state["body"].Shape.distToShape(Part.Vertex(p))[0] for p in s.Points[-s.Counts[-1]:])
    check("the red pen stroke lies on the model, not on the sheet in front", s.OnModel and depth > 1 and gap < 1.5,
          "depth=%.2f gap=%.2f (on the sheet it would be %.2f)" % (depth, gap, sheet))


in_order([
    ("activate", activate),
    ("setup", setup), ("wait", lambda: None),
    ("red pen", lambda: Gui.runCommand("Design_RedPen")), ("wait", lambda: None),
    ("write", write), ("wait", lambda: None),
    ("shot write", lambda: shot("write")),
    ("on model", on_model),
    ("turn", lambda: Gui.SendMsgToActiveView("ViewRight")), ("wait", lambda: None), ("wait", lambda: None),
    ("shot turned", lambda: shot("turned")),
])
