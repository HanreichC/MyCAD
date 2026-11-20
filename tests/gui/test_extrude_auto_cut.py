# SPDX-License-Identifier: LGPL-2.1-or-later
"""Extrude wählt Cut von selbst, sobald er durch einen Körper geht (wie Fusion), auch mit Luft zwischen Skizze und Körper
und mit Startversatz ins Material. Vorher prüfte er nur einen Punkt direkt an der Skizze und blieb bei Join/New Body.
Ein Cut geht durch alle Körper auf seinem Weg, nicht nur durch den unter der Skizze. Liegt die Skizze auf einem
ausgeblendeten Körper, wird er nicht Join-Ziel: das Ergebnis verschwand sonst unsichtbar in ihm (ConceptKey). Wählt man
Join auf ihn selbst, wird er nach OK eingeblendet."""
import math
from harness import *
import Design

W = ("wait", lambda: None)
S = {}


def op():
    return [o for o in doc().Objects if o.TypeId == "Design::Extrude"][-1].Operation


def gap_setup():
    S["box"] = make_body(rect(0, 0, 40, 20), 5, 10, "Floating")  # z 5..15, Luft unter ihm
    S["top"] = make_body(rect(0, 0, 40, 20), 18, 5, "Above")      # z 18..23, zweiter Körper weiter oben
    d = doc(); root = [o for o in d.Objects if o.TypeId == "App::Part"][0]
    sk = Design.newSketch(root)  # XY, z = 0
    sk.addGeometry(Part.Circle(App.Vector(20, 10, 0), App.Vector(0, 0, 1), 3)); d.recompute()
    prof = [o for o in sk.InList if o.TypeId == "Design::Profiles"][0]
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(prof, "Face1"); click(button("Design_Extrude"))


def expect(want, tag):
    check("%s: %s" % (tag, want), op() == want, op())


def offset_setup():
    b = make_body(rect(100, 0, 140, 20), 0, 10, "Plate")
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(b, top_face(b)); click(button("Design_CreateSketch"))


def circle_leave(x=120, z=10):
    s = Gui.ActiveDocument.getInEdit().Object; S["top"] = s
    c = s.Placement.inverse().multVec(App.Vector(x, 10, z))
    s.addGeometry(Part.Circle(App.Vector(c.x, c.y, 0), App.Vector(0, 0, 1), 3)); doc().recompute()
    Gui.ActiveDocument.resetEdit()


def offset_extrude():
    prof = [o for o in S["top"].InList if o.TypeId == "Design::Profiles"][0]
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(prof, "Face1"); click(button("Design_Extrude"))


def hidden_setup():
    b = make_body(rect(200, 0, 240, 20), 0, 2, "Hidden")
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(b, top_face(b)); click(button("Design_CreateSketch"))


def hidden_extrude():
    body("Hidden").Visibility = False
    body("Floating").Visibility = False  # erster Körper ausgeblendet, wie PCB in ConceptKey
    prof = [o for o in S["top"].InList if o.TypeId == "Design::Profiles"][0]
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(prof, "Face1"); click(button("Design_Extrude"))


def join_hidden():
    choose("Join", 1)
    cb = [c for c in visible(QtWidgets.QComboBox) if c.findText("Hidden") >= 0][0]
    S["preselected"] = cb.currentText()
    S["hidden_last"] = {cb.itemText(i) for i in range(cb.count() - 2, cb.count())} == {"Floating", "Hidden"}
    cb = [c for c in visible(QtWidgets.QComboBox) if c.findText("Hidden") >= 0][0]
    cb.setCurrentIndex(cb.findText("Hidden"))


def ok():
    button("Design_Extrude").setFocus(); QtTest.QTest.keyClick(view(), QtCore.Qt.Key_Return)


run([("activate", activate), ("gap", gap_setup), W,
     ("short", lambda: type_field("Distance", "3")), W, ("new", lambda: expect("New Body", "3 mm does not reach the floating body")),
     ("long", lambda: type_field("Distance", "30")), W, ("cut", lambda: expect("Cut", "30 mm goes through both bodies across the gap")),
     ("ok", ok), W, ("vol", lambda: check("the cut goes through both bodies on its way",
                                          abs(S["box"].Shape.Volume - (8000 - math.pi * 9 * 10)) < 0.05 and abs(S["top"].Shape.Volume - (4000 - math.pi * 9 * 5)) < 0.05,
                                          "%.2f %.2f" % (S["box"].Shape.Volume, S["top"].Shape.Volume))),
     ("plate", offset_setup), W, W, ("circle", circle_leave), W, ("extrude", offset_extrude), W,
     ("offset", lambda: type_field("Start offset", "-5")), W, ("dist", lambda: type_field("Distance", "2")), W,
     ("cut 2", lambda: expect("Cut", "start offset 5 mm into the plate")), ("ok 2", ok), W,
     ("hidden", hidden_setup), W, W, ("circle 2", lambda: circle_leave(220, 2)), W, ("extrude 2", hidden_extrude), W,
     ("new 2", lambda: expect("New Body", "sketch on a hidden body does not join into it")),
     ("join", join_hidden), W, ("join op", lambda: expect("Join", "join chosen by hand")),
     ("preselect", lambda: check("switching to Join preselects a visible body, hidden ones come last",
                                 S["preselected"] not in ("Floating", "Hidden") and S["hidden_last"], S["preselected"])), ("ok 3", ok), W,
     ("shown", lambda: check("a hidden body joined by hand is shown after OK", body("Hidden").Visibility
                             and abs(body("Hidden").Shape.Volume - (40 * 20 * 2 + math.pi * 9 * 10)) < 0.1,
                             "visible=%s volume=%.2f" % (body("Hidden").Visibility, body("Hidden").Shape.Volume)))])
