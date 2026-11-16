# SPDX-License-Identifier: LGPL-2.1-or-later
"""Skizze auf einer Körperfläche flackert beim Drehen nicht: ihr projizierter Rand (magenta) liegt genau auf den
Körperkanten, Linie auf Linie, und nur um tausendstel Millimeter angehoben. Aus der Ferne ist das weniger als eine
Tiefeneinheit, und je nach Blickwinkel gewann die Körperkante oder die Skizze (Flächen schiebt ihr Polygon-Offset
ohnehin zurück, Linien nicht). Darum hat alles der Skizze einen festen Vorsprung im Tiefenpuffer (verkürzter
Tiefenbereich ganz oben im EditRoot, EditModeCoinManager). Unter Xvfb flackert es nicht sichtbar; der Test legt die
Skizze eines 6 x 4 m großen Teils knapp *unter* die Fläche und vergleicht auf den Pixeln der Körperkante: mit Vorsprung
gewinnt der Rand der Skizze, mit abgeschaltetem Vorsprung (Bereich wieder 0..1) die Kante."""
from harness import *
from PySide6 import QtGui
from pivy import coin

W = ("wait", lambda: None)
S = {}
K = 100.0  # Maßstab: 6000 x 4000 x 1000 mm


def setup():
    S["b"] = make_body(rect(0, 0, 60 * K, 40 * K), 0, 10 * K, "Box")


def top():
    b = S["b"]; Gui.Selection.clearSelection(); Gui.Selection.addSelection(b, top_face(b))
    click(button("Design_CreateSketch"))


def lead_node():
    """erster Knoten im EditRoot der Skizze: der Tiefen-Vorsprung"""
    sa = coin.SoSearchAction(); sa.setName(coin.SbName("Sketch_EditRoot")); sa.setInterest(coin.SoSearchAction.FIRST)
    sa.apply(Gui.ActiveDocument.ActiveView.getSceneGraph())
    root = sa.getPath().getTail()
    return root.getChild(0)


def prepare():
    S["sk"] = Gui.ActiveDocument.getInEdit().Object
    v = Gui.ActiveDocument.ActiveView
    v.setCameraType("Perspective"); v.viewIsometric(); Gui.SendMsgToActiveView("ViewFit")
    node = lead_node()
    check("the sketch draws with a depth lead", node.isOfType(coin.SoDepthBuffer.getClassTypeId())
          and node.range.getValue()[1] < 1.0, node.getTypeId().getName().getString())
    # knapp unter die Fläche: 0,02 mm (mehr als die festen 0,007 mm Anhebung, weniger als der Vorsprung hier)
    doc().openTransaction("sink")
    S["sk"].AttachmentOffset = App.Placement(App.Vector(0, 0, -0.02), App.Rotation())
    doc().recompute(); doc().commitTransaction()


def on_edge():
    """Anteil magentafarbener Pixel genau auf der vorderen oberen Körperkante"""
    v = Gui.ActiveDocument.ActiveView
    img = view().viewport().grab().toImage()
    hits = n = 0
    for k in range(3, 98):
        x, y = v.getPointOnViewport(App.Vector(60 * K * k / 100.0, 0, 10 * K))
        c = QtGui.QColor(img.pixel(int(x), int(img.height() - y)))
        n += 1; hits += c.red() > 150 and c.blue() > 150 and c.green() < 130
    return hits / n


def with_lead():
    S["with"] = on_edge()


def without_lead():
    lead_node().range.setValue(0.0, 1.0)
    Gui.ActiveDocument.ActiveView.redraw()


def compare():
    S["without"] = on_edge()
    check("with the depth lead the sketch outline wins on the body edge, without it the edge wins",
          S["with"] > 0.3 and S["without"] < S["with"] / 2, "with %.2f, without %.2f" % (S["with"], S["without"]))


run([("activate", activate), ("setup", setup), W, ("top", top), W, W, ("prepare", prepare), W, W,
     ("with", with_lead), ("off", without_lead), W, ("compare", compare)], delay=1500)
