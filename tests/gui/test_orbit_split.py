# SPDX-License-Identifier: LGPL-2.1-or-later
"""Drehpunkt "Mitte des Körpers unter dem Cursor" bei einem geteilten Körper (2026-11-25): über der abgeteilten Hälfte
dreht die Ansicht um deren Mitte, nicht um die Mitte des ganzen Körpers vor dem Teilen. Auch wenn eine durchsichtige
Platte über allem liegt (Acrylglas in ConceptKey): durch sie hindurch zählt der Körper dahinter."""
import Design
from harness import *

VIEW = "User parameter:BaseApp/Preferences/View"
S = {}


def screen(p):
    v = view(); x, y = Gui.ActiveDocument.ActiveView.getPointOnViewport(p)
    dpr = v.viewport().devicePixelRatioF()
    return QtCore.QPointF(x / dpr, v.viewport().height() - y / dpr)


def send(kind, pos, button, buttons, mods=QtCore.Qt.NoModifier):
    vp = view().viewport()
    ev = QtGui.QMouseEvent(kind, QtCore.QPointF(pos), vp.mapToGlobal(QtCore.QPointF(pos)), button, buttons, mods)
    QtWidgets.QApplication.sendEvent(vp, ev)


def split():
    d = doc(); body_ = make_body(rect(0, 0, 100, 20), 0, 10, "Long")
    cut = d.addObject("PartDesign::Plane", "Cut"); Design.root(d).addObject(cut)
    cut.Placement = App.Placement(App.Vector(80, 0, 0), App.Rotation(App.Vector(0, 1, 0), 90)); cut.Visibility = False
    d.recompute()
    s = d.addObject("Design::Split", "Split"); Design.root(d).addObject(s); Design.addToTimeline(s)
    s.Tool = (cut, [""]); Design.attachToBodies(s, [body_]); d.recompute()
    p = d.addObject("Design::Body", "Body"); d.getObject("Bodies").addObject(p); p.Tip = s
    s.Bodies = [body_, p]; d.recompute()
    S["small"] = min([body_, p], key=lambda b: b.Shape.Volume)
    L("small half %s" % S["small"].Shape.BoundBox)
    glass = make_body(rect(-5, -5, 105, 25), 12, 2, "Glass")  # durchsichtige Platte über dem ganzen Körper
    glass.ViewObject.Transparency = 62


def orbit():
    c = S["small"].Shape.BoundBox.Center
    S["c"] = screen(c)
    start = screen(App.Vector(c.x, c.y, 10))  # auf die Oberseite der Hälfte, durch die Platte
    shift, mid = QtCore.Qt.ShiftModifier, QtCore.Qt.MiddleButton
    send(QtCore.QEvent.MouseButtonPress, start, mid, mid, shift)
    for k in range(1, 13):
        send(QtCore.QEvent.MouseMove, start + QtCore.QPointF(-10 * k, 5 * k), QtCore.Qt.NoButton, mid, shift)
    send(QtCore.QEvent.MouseButtonRelease, start + QtCore.QPointF(-120, 60), mid, QtCore.Qt.NoButton, shift)


def pivot():
    d = screen(S["small"].Shape.BoundBox.Center) - S["c"]
    check("orbiting over the split-off half (through a transparent plate) turns around its own center", (d.x() ** 2 + d.y() ** 2) ** 0.5 < 4,
          "its center moved %.1f px" % ((d.x() ** 2 + d.y() ** 2) ** 0.5))


run([
    ("style", lambda: (App.ParamGet(VIEW).SetString("NavigationStyle", "Gui::RevitNavigationStyle"),
                       App.ParamGet(VIEW).SetInt("RotationMode", 3))),
    ("split", split), ("iso", lambda: (Gui.ActiveDocument.ActiveView.viewIsometric(), Gui.SendMsgToActiveView("ViewFit"))),
    ("wait", lambda: None), ("orbit", orbit), ("pivot", pivot),
])
