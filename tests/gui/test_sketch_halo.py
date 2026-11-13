# SPDX-License-Identifier: LGPL-2.1-or-later
"""Skizzenlinien, Maße und Symbole auf dunklem Körper: heller Lichthof (Hintergrundfarbe) darum, sonst gingen sie auf
dunklem Lila unter. Prüft Pixel: knapp neben der Linie heller als der Körper weiter weg; ein Maß bringt helle Pixel mit."""
from harness import *
import Sketcher

state = {}

PURPLE = (0.20, 0.06, 0.30)


def setup():
    b = make_body(rect(0, 0, 60, 40), 0, 10, "Box")
    vo = Gui.ActiveDocument.getObject(b.Name); vo.ShapeColor = PURPLE
    m = vo.ShapeAppearance[0]; m.SpecularColor = (0.05, 0.05, 0.05, 1.0); m.EmissiveColor = (0.0, 0.0, 1 / 255, 1.0)
    vo.ShapeAppearance = [m]  # kein Metall: sonst färbt das helle Glanzlicht den Körper grau
    Gui.ActiveDocument.ActiveView.viewTop(); Gui.SendMsgToActiveView("ViewFit")


def line():
    sk = Gui.ActiveDocument.getInEdit().Object
    sk.addGeometry(Part.LineSegment(App.Vector(10, 20, 0), App.Vector(50, 20, 0)))
    doc().recompute()


def measure():
    sk = Gui.ActiveDocument.getInEdit().Object
    x, y = Gui.ActiveDocument.ActiveView.getPointOnViewport(sk.getGlobalPlacement().multVec(App.Vector(30, 20, 0)))
    img = view().viewport().grab().toImage()
    s = img.width() / view().viewport().width()
    px, py = int(x), int(img.height() - y)  # Coin zählt y von unten

    def light(dy):  # hellster Wert in ±1 px um py+dy (Linie und Rand sind antialiasiert)
        return max(QtGui.QColor(img.pixel(px, py + dy + k)).lightness() for k in (-1, 0, 1))
    beside, away = max(light(-3 * s), light(3 * s)), light(-25 * s)
    check("halo beside the line is lighter than the dark body", beside > away + 60, "beside=%d away=%d" % (beside, away))
    state["bright"] = bright()


def bright():
    """helle Pixel im Bild: Maßtext und Maßlinien selbst sind grau, nur ihr Lichthof ist so hell"""
    img = view().viewport().grab().toImage().convertToFormat(QtGui.QImage.Format_Grayscale8)
    return sum(v > 215 for v in bytes(img.constBits()))


def dimension():
    sk = Gui.ActiveDocument.getInEdit().Object
    sk.addConstraint(Sketcher.Constraint("DistanceX", 0, 1, 0, 2, 40))
    doc().recompute()


def measure_dimension():
    added = bright() - state["bright"]
    check("a dimension brings its halo along", added > 100, "bright pixels added=%d" % added)


run([
    ("setup", setup),
    ("Create Sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick top face", lambda: Gui.Selection.addSelection(body("Box"), top_face(body("Box")))),
    ("line", line), ("fit", lambda: Gui.SendMsgToActiveView("ViewFit")),
    ("measure", measure), ("shot", lambda: shot("halo")),
    ("dimension", dimension), ("measure dimension", measure_dimension), ("shot dim", lambda: shot("dimension")),
], delay=2000)
