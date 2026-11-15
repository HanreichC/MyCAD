# SPDX-License-Identifier: LGPL-2.1-or-later
"""Wie Fusion: eine Skizze auf einer Körperfläche zoomt beim Öffnen auf ihre Geometrie (ein kleiner Kreis weit weg vom
Ursprung füllt das Bild), und im Extrude-Dialog hat der Abstand gleich den Fokus: Zahl tippen, Enter."""
from harness import *
import Design

W = ("wait", lambda: None)
V = App.Vector
S = {}


def setup():
    S["b"] = make_body(rect(300, 0, 340, 20), 0, 10, "Far")
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(S["b"], top_face(S["b"])); click(button("Design_CreateSketch"))


def small_circle():
    s = Gui.ActiveDocument.getInEdit().Object; S["sk"] = s
    c = s.Placement.inverse().multVec(V(320, 10, 10))
    s.addGeometry(Part.Circle(V(c.x, c.y, 0), V(0, 0, 1), 1)); doc().recompute()
    Gui.ActiveDocument.resetEdit()


def circle_share():
    """Anteil des Kreises an der Bildbreite bzw. -höhe (größerer Wert); 1 = füllt das Bild"""
    v = Gui.ActiveDocument.ActiveView; vp = view().viewport(); dpr = vp.devicePixelRatioF()
    pts = [v.getPointOnViewport(V(x, y, 10)) for x, y in ((319, 9), (321, 9), (321, 11), (319, 11))]
    xs, ys = [p[0] / dpr for p in pts], [p[1] / dpr for p in pts]
    inside = all(0 <= x <= vp.width() and 0 <= y <= vp.height() for x, y in zip(xs, ys))
    return inside, max((max(xs) - min(xs)) / vp.width(), (max(ys) - min(ys)) / vp.height())


def fitted():
    inside, share = circle_share()
    check("re-entering a sketch on a body face zooms onto its small circle", inside and share > 0.35, "inside=%s share=%.2f" % (inside, share))
    Gui.ActiveDocument.resetEdit()


def extrude():
    prof = [o for o in S["sk"].InList if o.TypeId == "Design::Profiles"][0]
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(prof, "Face1"); click(button("Design_Extrude"))


def type_seven():
    """Tasten wie eine echte Tastatur an das Fokus-Widget (ohne vorher ins Feld zu klicken)"""
    w = QtWidgets.QApplication.focusWidget() or view()
    QtTest.QTest.keyClicks(w, "7")
    QtTest.QTest.keyClick(w, QtCore.Qt.Key_Return)


def typed():
    e = [o for o in doc().Objects if o.TypeId == "Design::Extrude"][-1]
    check("the extrude distance has the focus: typing 7 and Enter extrudes 7 mm", abs(e.Distance.Value - 7) < 1e-6 and not Gui.Control.activeDialog(),
          "distance=%s dialog=%s" % (e.Distance, Gui.Control.activeDialog()))


run([("activate", activate), ("setup", setup), W, W, ("circle", small_circle), W,
     ("away", lambda: (Gui.ActiveDocument.ActiveView.viewIsometric(), Gui.SendMsgToActiveView("ViewFit"))), W,
     ("enter", lambda: Gui.ActiveDocument.setEdit(S["sk"])), W, W, ("fitted", fitted), W,
     ("extrude", extrude), W, W, ("type", type_seven), W, ("typed", typed)])
