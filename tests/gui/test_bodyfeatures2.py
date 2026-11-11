# SPDX-License-Identifier: LGPL-2.1-or-later
"""Körper-Muster, Align, Split Body und Thread über die echten Befehle."""
from harness import *


def faces(b, pred):
    return ["Face%d" % (i + 1) for i, f in enumerate(b.Shape.Faces) if pred(f)]


def select(b, subs=None):
    Gui.Selection.clearSelection()
    if subs is None:
        Gui.Selection.addSelection(b)
    for s in subs or []:
        Gui.Selection.addSelection(doc().Name, b.Name, s)


def bb(b):
    k = b.Shape.BoundBox
    return "x %.0f..%.0f y %.0f..%.0f z %.0f..%.0f" % (k.XMin, k.XMax, k.YMin, k.YMax, k.ZMin, k.ZMax)


def circle(r, x, y):
    return [Part.Circle(App.Vector(x, y, 0), App.Vector(0, 0, 1), r)]


def header():
    """Titel des Feature-Panels"""
    return [h.text() for h in visible(QtWidgets.QToolButton) if h.property("class") == "header"]


def labels():
    return {l.text() for l in visible(QtWidgets.QLabel)}


def cancel():
    click([b for b in visible(QtWidgets.QPushButton) if b.text().replace("&", "") == "Cancel"][0])


def set_pattern():
    boxes = [b for b in visible(QtWidgets.QSpinBox)]
    boxes[0].setValue(3)


run([
    ("setup", lambda: (make_body(rect(-10, -10, 10, 10), 0, 20, "A"), make_body(rect(40, -10, 60, 10), 0, 10, "B"),
                       make_body(rect(100, -10, 120, 10), 0, 10, "C"), make_body(circle(8, -60, 0), 0, 20, "D"))),
    ("pattern sel", lambda: select(body("C"))), ("pattern", lambda: Gui.runCommand("Design_Pattern")),
    ("count", set_pattern), ("ok", ok),
    ("pattern?", lambda: L("pattern: %s errors=%s" % ([(b.Label, round(b.Shape.Volume)) for b in doc().Objects if b.Label.startswith("C")], errors()))),
    ("align sel", lambda: (select(body("B"), faces(body("B"), lambda f: abs(f.CenterOfMass.z) < 1e-6)),
                           Gui.Selection.addSelection(doc().Name, body("A").Name, faces(body("A"), lambda f: abs(f.CenterOfMass.z - 20) < 1e-6)[0]))),
    ("align", lambda: Gui.runCommand("Design_Align")), ("ok", ok),
    ("align?", lambda: L("align: B %s (erwartet x -10..10 z 20..30) errors=%s" % (bb(body("B")), errors()))),
    # wie ein Klick auf den Body in der Ansicht: der wählt eine Fläche, dann Strg+Klick auf die Ebene
    ("split sel", lambda: (select(body("A"), [top_face(body("A"))]), Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XZ_Plane")][0]))),
    ("split", lambda: Gui.runCommand("Design_SplitBody")),
    ("split?", lambda: L("split: %s errors=%s" % ([(b.Label, round(b.Shape.Volume)) for b in doc().Objects if b.Label.startswith("A")], errors()))),
    ("split ok", lambda: check("a face clicked on the body selects the body to split",
                               len([b for b in doc().Objects if b.TypeId == "Design::Body" and b.Label.startswith("A")]) == 2)),
    ("thread sel", lambda: select(body("D"), faces(body("D"), lambda f: f.Surface.TypeId == "Part::GeomCylinder"))),
    ("thread", lambda: Gui.runCommand("Design_Thread")), ("wait", lambda: None), ("wait", lambda: None), ("thread dialog", lambda: shot("thread")), ("ok", ok), ("wait", lambda: None), ("wait", lambda: None),
    ("thread?", lambda: L("thread: D volume=%.0f (Zylinder %.0f, mit Gewinde kleiner) faces=%d errors=%s" % (
        body("D").Shape.Volume, 3.14159265 * 64 * 20, len(body("D").Shape.Faces), errors()))),
    ("plate", lambda: make_body(rect(-140, -20, -100, 20) + circle(6, -120, 0), 0, 15, "E")),
    ("ring only", lambda: (lambda ext: (setattr(ext, "Profile", (ext.Profile[0], ["Face%d" % (1 + max(range(len(ext.Profile[0].Shape.Faces)),
        key=lambda k: len(ext.Profile[0].Shape.Faces[k].Wires)))])), doc().recompute()))(body("E").Tip)),
    ("hole sel", lambda: select(body("E"), faces(body("E"), lambda f: f.Surface.TypeId == "Part::GeomCylinder"))),
    ("inner", lambda: Gui.runCommand("Design_Thread")), ("wait", lambda: None), ("wait", lambda: None), ("ok", ok), ("wait", lambda: None),
    ("inner?", lambda: L("inner thread: E volume=%.0f (Platte mit Bohrung %.0f, Rillen nach außen -> kleiner) errors=%s" % (
        body("E").Shape.Volume, 40 * 40 * 15 - 3.14159265 * 36 * 15, errors()))),
    ("remove sel", lambda: select(body("B"), faces(body("B"), lambda f: abs(f.CenterOfMass.x - body("B").Shape.BoundBox.XMax) < 1e-6))),
    ("remove face", lambda: Gui.runCommand("Design_RemoveFace")),
    ("remove panel", lambda: check("Remove Face panel: own title, Faces row, no Distance field",
                                   header() == ["Remove Face"] and {"Faces", "1 selected"} <= labels() and not {"Distance", "Edges"} & labels(),
                                   "%s %s" % (header(), [l.text() for l in visible(QtWidgets.QLabel)]))),
    ("remove cancel", cancel),
    ("combine sel", lambda: (select(body("B")), Gui.Selection.addSelection(body("D")))),
    ("combine", lambda: Gui.Control.activeDialog() or Gui.runCommand("Design_Combine")),
    ("one body", lambda: check("Combine panel: 1 body (singular)", "1 body" in [l.text() for l in visible(QtWidgets.QLabel)],
                               str([l.text() for l in visible(QtWidgets.QLabel)]))),
    ("combine cancel", cancel),
    ("shot", lambda: shot("features2")),
])
