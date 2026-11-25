# SPDX-License-Identifier: LGPL-2.1-or-later
"""Phase 14, Chaos 5: was seit dem 25.11. neu ist, über die Oberfläche gequält. Skizze auf der Deckfläche (mit dem
projizierten Rand), Bohrung daraus; die Platte mehrmals breiter und schmaler machen und die Skizze jedes Mal wieder
öffnen: der projizierte Rand wird umgeschrieben, nicht verdoppelt, und die Skizze bleibt heil. Dann eine Rundung, die
nicht passt: sie ist rot, die Bohrung danach bleibt (wie Fusion); den roten Schritt über die Zeitleiste löschen."""
import os
import sys
from PySide6 import QtGui
from harness import *
sys.path.insert(0, os.path.join(os.path.dirname(os.environ["SCRIPT"]), "..", "design"))
import design as D
import Design
import Sketcher

S = {}
W = ("wait", lambda: None)
V = App.Vector


def vol():
    return round(S["body"].Shape.Volume, 2)


def build():
    d = doc()
    base = D.sketch(d, D.rect(0, 0, 80, 50))
    C = Sketcher.Constraint
    for c in [C("Coincident", i, 2, (i + 1) % 4, 1) for i in range(4)] + [
            C("Horizontal", 0), C("Horizontal", 2), C("Vertical", 1), C("Vertical", 3), C("Coincident", 0, 1, -1, 1),
            C("DistanceX", 0, 1, 0, 2, 80), C("DistanceY", 1, 1, 1, 2, 50)]:
        base.addConstraint(c)
    d.recompute()
    _, b = D.extrude(d, base, 10)
    S.update(body=b, base=base)
    Gui.ActiveDocument.ActiveView.viewIsometric(); Gui.SendMsgToActiveView("ViewFit")


def top_sketch():
    Gui.Selection.clearSelection()
    click_at(V(20, 25, 10))
    click(button("Design_CreateSketch"))


def hole_circle():
    s = Gui.ActiveDocument.getInEdit().Object
    S["top"] = s
    c = s.Placement.inverse().multVec(V(20, 25, 10))
    doc().openTransaction("Add sketch circle")
    s.addGeometry(Part.Circle(V(c.x, c.y, 0), V(0, 0, 1), 4))
    doc().commitTransaction()
    doc().recompute()
    S["external"] = len(s.ExternalGeometry)
    S["geometry"] = len(s.Geometry)


def leave():
    QtTest.QTest.keyClick(view().viewport(), QtCore.Qt.Key_Escape)
    if Gui.ActiveDocument.getInEdit():
        Gui.ActiveDocument.resetEdit()


def cut_hole():
    prof = D.profiles(S["top"])
    faces = [i for i, f in enumerate(prof.Shape.Faces, 1) if abs(f.Area - 3.14159265 * 16) < 0.1]
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(prof, "Face%d" % faces[0])
    click(button("Design_Extrude"))


def width(value):
    def f():
        s = S["base"]
        i = [k for k, c in enumerate(s.Constraints) if c.Type == "DistanceX"][0]
        doc().openTransaction("Modify sketch constraints")
        s.setDatum(i, App.Units.Quantity("%g mm" % value))
        doc().recompute()
        doc().commitTransaction()
    return f


def reopen_top():
    Gui.ActiveDocument.setEdit(S["top"].Name)


def projection_ok(label):
    def f():
        s = Gui.ActiveDocument.getInEdit().Object if Gui.ActiveDocument.getInEdit() else S["top"]
        check("%s: the projected edge is rewritten, not doubled; the sketch stays whole" % label,
              len(s.ExternalGeometry) == S["external"] and len(s.Geometry) == S["geometry"] and "Invalid" not in s.State,
              "external %d (was %d), geometry %d (was %d), state %s" % (len(s.ExternalGeometry), S["external"],
                                                                     len(s.Geometry), S["geometry"], s.State))
    return f


def bad_fillet():
    b = S["body"]
    e = D.edge_where(b, lambda p: abs(p.x) < 1e-6 and abs(p.y) < 1e-6 and abs(p.z - 5) < 1e-6)
    S["fillet"] = D.dress(doc(), "Design::Fillet", b, [e], Size=60)  # passt nie: tiefer als die Platte (50)
    S["after fillet"] = vol()


def skipped():
    f = S["fillet"]
    hole_still = not S["body"].Shape.isInside(V(20, 25, 5), 1e-6, True)
    check("a fillet that cannot work is red, the hole and the plate go on without it (like Fusion)",
          "Invalid" in f.State and hole_still and abs(vol() - S["plate"]) < 0.5,
          "%s hole %s vol %.2f vs %.2f" % (f.State, hole_still, vol(), S["plate"]))


def delete_red():
    f = S["fillet"]
    entries = [b for b in visible(QtWidgets.QToolButton) if b.property("timelineIndex") is not None and b.accessibleName() == f.Label]
    if not entries:
        L("  no timeline entry for the red fillet"); return

    def pick():
        m = QtWidgets.QApplication.activePopupWidget()
        acts = [a for a in (m.actions() if m else []) if a.text() == "Delete"]
        if acts:
            m.setActiveAction(acts[0]); QtTest.QTest.keyClick(m, QtCore.Qt.Key_Return)
        elif m:
            m.close()
    QtCore.QTimer.singleShot(500, pick)
    QtCore.QTimer.singleShot(1500, lambda: [b.click() for box in visible(QtWidgets.QMessageBox)
                                             for b in box.findChildren(QtWidgets.QPushButton)
                                             if b.isVisible() and b.text().replace("&", "") in ("Delete", "Yes", "OK")][:1])
    w = entries[0]
    QtWidgets.QApplication.sendEvent(w, QtGui.QContextMenuEvent(QtGui.QContextMenuEvent.Mouse, w.rect().center()))


def clean():
    check("the red step deleted: nothing red, the part as before", not Design.problems(doc()) and abs(vol() - S["plate"]) < 0.5,
          "%s %.2f" % ([(o.Label, t[:60]) for o, t in Design.problems(doc())], vol()))
    problems = D.model_problems(doc())
    check("no dependency cycle, nothing left to recompute", not problems, str(problems))


steps = [("activate", activate), ("build", build), W, W, ("top sketch", top_sketch), W, W, ("circle", hole_circle), W,
         ("leave", leave), W, W, ("cut", cut_hole), W, ("depth", lambda: type_field("Distance", "-10")), W, ("ok", ok), W, W]
for k, w in enumerate((120, 60, 95, 80)):
    steps += [("width %d" % w, width(w)), W, W, ("reopen %d" % k, reopen_top), W, W,
              ("projection %d" % k, projection_ok("plate %d wide, sketch opened again" % w)), ("leave %d" % k, leave), W, W]
steps += [("plate", lambda: S.update(plate=vol())), ("bad fillet", bad_fillet), W, W, ("skipped", skipped),
          ("delete red", delete_red), W, W, W, ("clean", clean)]
run(steps)
