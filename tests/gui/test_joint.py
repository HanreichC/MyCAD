# SPDX-License-Identifier: LGPL-2.1-or-later
"""Joint: Grundplatte A (40x40x10, Wurzel), Klotz B (20x20, Komponente). Unterseite B auf Oberseite A ->
B mittig auf A. Slider +5 mm, A höher -> B folgt, Joint löschen -> B bleibt."""
from harness import *


def comp():
    return [o for o in doc().Objects if o.TypeId == "App::Part" and o.Type == "Component"][0]


def comp_plane():
    return [o for o in comp().Origin.OriginFeatures if o.Role == "XY_Plane"][0]


def B():
    return [o for o in doc().Objects if o.TypeId == "Design::Body"][1]


def face(b, z, nz):
    return ["Face%d" % (i + 1) for i, f in enumerate(b.Shape.Faces)
            if abs(f.CenterOfMass.z - z) < 1e-6 and abs(f.normalAt(0, 0).z - nz) < 1e-6][0]


def gbb():
    s = B().Shape.copy(); s.transformShape(comp().Placement.toMatrix())
    k = s.BoundBox
    return "x %.0f..%.0f y %.0f..%.0f z %.0f..%.0f" % (k.XMin, k.XMax, k.YMin, k.YMax, k.ZMin, k.ZMax)


def joint():
    return [o for o in doc().Objects if o.TypeId == "Design::Joint"][0]


run([
    ("A", lambda: make_body(rect(0, 0, 40, 40), 0, 10, "A")),
    ("New Component", lambda: click(button("Design_NewComponent"))),
    ("Create Sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick component XY", lambda: Gui.Selection.addSelection(comp_plane())),
    ("rect", lambda: [Gui.ActiveDocument.getInEdit().Object.addGeometry(g) for g in rect(0, 0, 20, 20)]),
    ("finish", lambda: click(button("Sketcher_LeaveSketch"))),
    ("Extrude", lambda: click(button("Design_Extrude"))), ("OK", ok),
    ("before", lambda: L("before: B %s folders=%s" % (gbb(), sorted(o.Label for o in comp().Group if o.TypeId == "App::DocumentObjectGroup")))),
    ("select", lambda: (Gui.Selection.clearSelection(),
                        Gui.Selection.addSelection(doc().Name, B().Name, face(B(), 0, -1)),
                        Gui.Selection.addSelection(doc().Name, body("A").Name, face(body("A"), 10, 1)))),
    ("joint", lambda: Gui.runCommand("Design_Joint")), ("shot", lambda: shot("joint")),
    ("rigid", lambda: L("rigid: B %s (erwartet x 10..30 y 10..30 z 10..20) errors=%s" % (gbb(), errors()))),
    ("slider", lambda: choose("Slider", 2)), ("offset", lambda: type_into(0, "5 mm")), ("OK joint", ok),
    ("slider?", lambda: L("slider +5: B %s (erwartet z 15..25)" % gbb())),
    ("taller A", lambda: (setattr(body("A").Tip, "Distance", 20), doc().recompute())),
    ("follow?", lambda: L("A 20 hoch: B %s (erwartet z 25..35)" % gbb())),
    ("delete", lambda: (doc().removeObject(joint().Name), doc().recompute())),
    ("deleted?", lambda: L("nach Löschen: B %s (bleibt) expr=%s errors=%s" % (gbb(), comp().ExpressionEngine, errors()))),
])
