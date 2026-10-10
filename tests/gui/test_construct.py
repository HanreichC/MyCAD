# SPDX-License-Identifier: LGPL-2.1-or-later
"""Konstruktion und Prüfen am Quader 60x40x15: Ebene durch drei Ecken, Achse durch zwei Ecken, Punkt auf einer Ecke,
Mittelebene zwischen Ober- und Unterseite, Messen (Fläche, Abstand, Winkel), Schnittansicht an/aus."""
from harness import *


def box():
    return body("Box")


def vertices(z):
    return ["Vertex%d" % (i + 1) for i, v in enumerate(box().Shape.Vertexes) if abs(v.Z - z) < 1e-6]


def faces(z):
    return ["Face%d" % (i + 1) for i, f in enumerate(box().Shape.Faces) if abs(f.CenterOfMass.z - z) < 1e-6]


def select(subs):
    Gui.Selection.clearSelection()
    for s in subs:
        Gui.Selection.addSelection(doc().Name, box().Name, s)


def datum(label):
    o = [o for o in doc().Objects if o.Label == label][-1]
    return o


def placement(label):
    o = datum(label); p = o.Placement
    return "%s mode=%s base=(%.1f, %.1f, %.1f) z-axis=%s" % (label, o.MapMode, p.Base.x, p.Base.y, p.Base.z,
                                                            tuple(round(c, 2) for c in p.Rotation.multVec(App.Vector(0, 0, 1))))


def measured():
    return [l.text() for l in visible(QtWidgets.QLabel) if "<table>" in l.text() or "Select a point" in l.text()]


def clipped():
    return Gui.ActiveDocument.ActiveView.hasClippingPlane()


run([
    ("setup", lambda: make_body(rect(0, 0, 60, 40), 0, 15, "Box")),
    ("3 points", lambda: select(vertices(15)[:3])), ("plane", lambda: click(button("Design_OffsetPlane|Design_Midplane|Design_Plane|Design_Axis|Design_Point")) if False else Gui.runCommand("Design_Plane")),
    ("plane?", lambda: L(placement("Plane"))),
    ("2 points", lambda: select(vertices(0)[:2])), ("axis", lambda: Gui.runCommand("Design_Axis")),
    ("axis?", lambda: L(placement("Axis"))),
    ("vertex", lambda: select(vertices(15)[:1])), ("point", lambda: Gui.runCommand("Design_Point")),
    ("point?", lambda: L(placement("Point"))),
    ("top+bottom", lambda: select(faces(15) + faces(0))), ("midplane", lambda: Gui.runCommand("Design_Midplane")),
    ("midplane?", lambda: L(placement("Midplane"))),
    ("measure", lambda: click(button("Design_Measure"))),
    ("top face", lambda: select(faces(15))), ("m1", lambda: L("measure 1: %s" % measured())),
    ("two faces", lambda: select(faces(15) + faces(0))), ("m2", lambda: L("measure 2: %s" % measured())),
    ("shot measure", lambda: shot("measure")),
    ("close", lambda: [b.click() for b in visible(QtWidgets.QPushButton) if b.text().replace("&", "") == "Close"]),
    ("section", lambda: (select(faces(15)), Gui.runCommand("Design_Section"))),
    ("clip on", lambda: (L("clipping=%s" % clipped()), shot("section"))),
    ("section off", lambda: Gui.runCommand("Design_Section")),
    ("clip off", lambda: L("clipping=%s" % clipped())),
    ("body measure", lambda: (Gui.Selection.clearSelection(), Gui.Selection.addSelection(box()), click(button("Design_Measure")))),
    ("m3", lambda: L("measure body: %s" % measured())),
    ("errors", lambda: L("errors=%s" % errors())),
])
