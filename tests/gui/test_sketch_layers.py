# SPDX-License-Identifier: LGPL-2.1-or-later
"""Ebenen der Skizzenanzeige neu aufbauen, während die Skizze bearbeitet wird (VisualLayerList ändert sich): früher
Absturz, weil die Knotenlisten auf die gelöschten Knoten zeigten. Danach zeichnet, fängt und färbt die Skizze weiter."""
from harness import *
import Design

V = App.Vector


def sketch():
    return [o for o in doc().Objects if o.TypeId == "Sketcher::SketchObject"][0]


def blue_pixels():
    """Pixel der Skizzenlinien (blau: Blauanteil klar über Rot)"""
    img = view().viewport().grab().toImage()
    n = 0
    for y in range(0, img.height(), 3):
        for x in range(0, img.width(), 3):
            c = img.pixelColor(x, y)
            n += c.blue() > 150 and c.blue() - c.red() > 80
    return n


def setup():
    sk = Design.newSketch(Design.root(doc()))
    for a, b in [(V(0, 0, 0), V(20, 0, 0)), (V(20, 0, 0), V(20, 10, 0))]:
        sk.addGeometry(Part.LineSegment(a, b))
    doc().recompute()
    Gui.ActiveDocument.setEdit(sk)


def before():  # eigener Schritt nach dem Einpassen: die Kamera fährt animiert
    state["before"] = blue_pixels()


def relayer():
    vp = Gui.ActiveDocument.getInEdit()
    vp.restorePropertyContent("VisualLayerList", vp.dumpPropertyContent("VisualLayerList"))
    check("layers rebuilt while editing", True)


def draw():
    sketch().addGeometry(Part.LineSegment(V(0, 10, 0), V(0, 0, 0)))
    sketch().solve()
    doc().recompute()


def after():
    QtWidgets.QApplication.processEvents()
    n = blue_pixels()
    check("lines drawn after the rebuild", n >= state["before"] * 0.95, "%d blue pixels, before %d" % (n, state["before"]))
    state["before"] = n
    v = view()
    for i in range(20):
        QtTest.QTest.mouseMove(v.viewport(), QtCore.QPoint(v.width() // 2 + i * 5, v.height() // 2))
    check("hover after the rebuild", True)


state = {}
in_order([
    ("setup", setup), ("fit", lambda: Gui.SendMsgToActiveView("ViewFit")), ("before", before), ("relayer", relayer), ("after", after),
    ("draw", draw), ("relayer again", relayer), ("after again", after),
], delay=600)
