# SPDX-License-Identifier: LGPL-2.1-or-later
"""Phase 13.7 Leistung: Skizze auf einem Körper mit vielen Flächen (Platte 120 x 80 x 10 mit 48 Bohrungen, ~150 Flächen)
öffnen, schließen und ein Extrude öffnen und verwerfen, je dreimal gemessen (timed). Dazu Szenario B: Skizze auf dem
Boden innen eines Gehäuses mit Wandstärke, von oben (dort blockierte MyCAD 1,4 s am Stück). Das war beim echten Arbeiten
ruckelig. Messwerte in $OUT.perf.txt; mit tests/gui/profile.sh unter perf."""
from harness import *
import Design

S = {}
W = ("wait", lambda: None)
V = App.Vector


def setup():
    d = doc(); root = [o for o in d.Objects if o.TypeId == "App::Part"][0]
    S["body"] = make_body(rect(0, 0, 120, 80), 0, 10, "Plate")
    sk = Design.newSketch(root)
    sk.Placement = App.Placement(V(0, 0, 10), App.Rotation())
    for i in range(8):
        for j in range(6):
            sk.addGeometry(Part.Circle(V(10 + i * 14, 10 + j * 12, 0), V(0, 0, 1), 3))
    d.recompute()
    prof = [o for o in sk.InList if o.TypeId == "Design::Profiles"][0]
    f = d.addObject("Design::Extrude", "Extrude"); root.addObject(f); Design.addToTimeline(f)
    f.Profile = (prof, ["Face%d" % (k + 1) for k in range(len(prof.Shape.Faces)) if prof.Shape.Faces[k].Area < 30])
    f.Distance = 10; f.Reversed = True; f.Operation = "Cut"
    Design.attachToBodies(f, [S["body"]])
    sk.Visibility = False
    d.recompute()
    Gui.SendMsgToActiveView("ViewFit")
    L("  plate: %d faces, volume %.0f" % (len(S["body"].Shape.Faces), S["body"].Shape.Volume))


def open_sketch():
    b = S["body"]
    top = face_where(b, lambda c: abs(c.z - 10) < 1e-6)
    Gui.Selection.clearSelection()
    click_at(V(3, 3, 10))  # Ecke der Deckfläche, neben den Bohrungen
    click(button("Design_CreateSketch"))
    S["sketch"] = Gui.ActiveDocument.getInEdit().Object if Gui.ActiveDocument.getInEdit() else None


def close_sketch():
    Gui.ActiveDocument.resetEdit()


def remove_sketch():
    s = S.get("sketch")
    if s is not None:
        doc().openTransaction("remove")
        Design.removeFromTimeline(s)
        doc().commitTransaction()
        doc().recompute()


def open_extrude():
    """eine Skizze mit Rechteck auf der Deckfläche extrudieren: Panel auf"""
    d = doc(); root = [o for o in d.Objects if o.TypeId == "App::Part"][0]
    if "rect" not in S:
        sk = Design.newSketch(root)
        sk.Placement = App.Placement(V(0, 0, 10), App.Rotation())
        for g in rect(30, 30, 50, 50):
            sk.addGeometry(g)
        d.recompute()
        S["rect"] = sk
    prof = [o for o in S["rect"].InList if o.TypeId == "Design::Profiles"][0]
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(prof, "Face1")
    click(button("Design_Extrude"))


def housing():
    """Gehäuse 60 x 40 x 30 neben der Platte, Wandstärke 2, oben offen; Blick von oben"""
    h = make_body(rect(200, 0, 260, 40), 0, 30, "Housing")
    top = face_where(h, lambda c: abs(c.z - 30) < 1e-6)
    root = [o for o in doc().Objects if o.TypeId == "App::Part"][0]
    f = doc().addObject("Design::Shell", "Shell"); root.addObject(f); Design.addToTimeline(f)
    f.Edges = [top]; f.Size = 2
    Design.attachToBodies(f, [h])
    doc().recompute()
    S["housing"] = h
    Gui.ActiveDocument.ActiveView.viewTop(); Gui.SendMsgToActiveView("ViewFit")


def open_floor_sketch():
    Gui.Selection.clearSelection()
    click_at(V(230, 20, 2))
    click(button("Design_CreateSketch"))
    S["sketch"] = Gui.ActiveDocument.getInEdit().Object if Gui.ActiveDocument.getInEdit() else None


def cancel():
    click([b for b in visible(QtWidgets.QPushButton) if b.text().replace("&", "") == "Cancel"][0])


steps = [("activate", activate), ("setup", setup), W]
for k in range(3):
    steps += [timed("sketch on body opens #%d" % (k + 1), open_sketch, 500), W,
              timed("sketch on body closes #%d" % (k + 1), close_sketch, 300), W,
              ("remove %d" % k, remove_sketch), W]
for k in range(3):
    steps += [timed("extrude on body opens #%d" % (k + 1), open_extrude, 200), W,
              timed("extrude: type 5, preview #%d" % (k + 1), lambda: type_field("Distance", "5"), 300), W,
              timed("extrude cancel #%d" % (k + 1), cancel, 300), W]
steps += [("housing", housing), W]
for k in range(2):
    steps += [timed("sketch on housing floor opens #%d" % (k + 1), open_floor_sketch, 500), W,
              timed("sketch on housing floor closes #%d" % (k + 1), close_sketch, 300), W,
              ("remove floor %d" % k, remove_sketch), W]
steps += [("errors", lambda: check("no errors", not errors(), str(errors())))]
run(steps)
