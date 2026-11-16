# SPDX-License-Identifier: LGPL-2.1-or-later
"""Skizze auf dunklem Körper lesbar wie in Profi-CAD, ohne Lichthof (der machte alles dick): solange die Skizze offen ist,
tritt der Körper zur Hintergrundfarbe hin zurück; Linien bleiben dünn (neben der Linie kein heller Rand); Maße stehen
auf einem hellen Schild (wie Creos Maß-Hintergrund), auch das gerade gesetzte. Nach der Skizze ist der Körper wie vorher."""
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


def body_light():
    """Helligkeit mitten auf dem Körper (dort liegt später nichts von der Skizze)"""
    x, y =Gui.ActiveDocument.ActiveView.getPointOnViewport(App.Vector(30, 32, 10))
    img = view().viewport().grab().toImage()
    return QtGui.QColor(img.pixel(int(x), int(img.height() - y))).lightness()


def line():
    sk = Gui.ActiveDocument.getInEdit().Object
    sk.addGeometry(Part.LineSegment(App.Vector(10, 20, 0), App.Vector(50, 20, 0)))
    doc().recompute()


def faded():
    state["sketch"] = body_light()
    check("the body steps back while the sketch is open", state["sketch"] > state["before"] + 40,
          "before=%d in sketch=%d" % (state["before"], state["sketch"]))


def thin():
    sk = Gui.ActiveDocument.getInEdit().Object
    x, y = Gui.ActiveDocument.ActiveView.getPointOnViewport(sk.getGlobalPlacement().multVec(App.Vector(30, 20, 0)))
    img = view().viewport().grab().toImage()
    s = img.width() / view().viewport().width()
    px, py = int(x), int(img.height() - y)  # Coin zählt y von unten

    def light(dy):
        return QtGui.QColor(img.pixel(px, py + dy)).lightness()
    beside, away = max(light(-3 * s), light(3 * s)), light(-25 * s)
    check("no bright rim beside the line: it stays thin", abs(beside - away) < 25, "beside=%d away=%d" % (beside, away))
    state["bright"] = bright()


def bright():
    """sehr helle Pixel: auf dem zurückgetretenen Körper nur das Schild eines Maßes"""
    img = view().viewport().grab().toImage().convertToFormat(QtGui.QImage.Format_Grayscale8)
    return sum(v > 215 for v in bytes(img.constBits()))


def dimension():
    sk = Gui.ActiveDocument.getInEdit().Object
    sk.addConstraint(Sketcher.Constraint("DistanceX", 0, 1, 0, 2, 40))
    doc().recompute()


def plate():
    added = bright() - state["bright"]
    check("a dimension stands on a light plate", added > 100, "bright pixels added=%d" % added)


def back():
    after = body_light()
    check("after the sketch the body looks as before", abs(after - state["before"]) < 6, "before=%d after=%d" % (state["before"], after))


run([
    ("setup", setup), ("before", lambda: state.update(before=body_light())),
    ("Create Sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick top face", lambda: Gui.Selection.addSelection(body("Box"), top_face(body("Box")))),
    ("line", line), ("top", lambda: (Gui.ActiveDocument.ActiveView.viewTop(), Gui.SendMsgToActiveView("ViewFit"))),
    ("faded", faded), ("thin", thin), ("shot", lambda: shot("sketch")),
    ("dimension", dimension), ("plate", plate), ("shot dim", lambda: shot("dimension")),
    ("finish", lambda: click(button("Sketcher_LeaveSketch"))),
    ("top 2", lambda: (Gui.ActiveDocument.ActiveView.viewTop(), Gui.SendMsgToActiveView("ViewFit"))), ("back", back),
], delay=2000)
