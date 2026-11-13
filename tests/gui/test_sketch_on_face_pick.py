# SPDX-License-Identifier: LGPL-2.1-or-later
"""Skizze auf einer Körperfläche liegt genau in deren Ebene: ein Klick ins Profil wählt das Profil (wie Fusion), nicht
zufällig die Fläche darunter. Daneben bleibt es die Körperfläche."""
from harness import *
import Design

state = {}


def selected():
    return [(s.ObjectName, n) for s in Gui.Selection.getSelectionEx() for n in s.SubElementNames]


def setup():
    state["box"] = make_body(rect(0, 0, 40, 20), 0, 5, "Box")
    sk = Design.newSketch(Design.root(doc()))
    sk.Placement.Base.z = 5  # genau auf der Oberseite
    for g in rect(5, 5, 15, 15):
        sk.addGeometry(g)
    doc().recompute()
    state["profiles"] = [o for o in doc().Objects if o.TypeId == "Design::Profiles" and o.Sketch == sk][0]


def click_at(x, y):
    Gui.Selection.clearSelection()
    p = Gui.ActiveDocument.ActiveView.getPointOnViewport(App.Vector(x, y, 5))
    vp = view().viewport(); dpr = vp.devicePixelRatioF()
    q = QtCore.QPoint(int(p[0] / dpr), int(vp.height() - p[1] / dpr))
    QtTest.QTest.mouseMove(vp, q)
    QtTest.QTest.mouseClick(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, q)
    return selected()


def inside():
    hits = [click_at(x, y) for x, y in [(10, 10), (7, 8), (13, 12), (9, 13), (12, 6)]]
    check("clicks inside the profile select the profile, not the face below",
          all(h == [(state["profiles"].Name, "Face1")] for h in hits), str(hits))


def outside():
    hit = click_at(30, 10)
    check("a click next to the profile still selects the body face", hit == [(state["box"].Name, top_face(state["box"]))], str(hit))


run([
    ("setup", setup),
    ("fit", lambda: (Gui.ActiveDocument.ActiveView.viewTop(), Gui.SendMsgToActiveView("ViewFit"))),
    ("inside", inside),
    ("outside", outside),
])
