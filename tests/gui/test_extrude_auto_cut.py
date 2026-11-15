# SPDX-License-Identifier: LGPL-2.1-or-later
"""Extrude wählt Cut von selbst, sobald er durch einen Körper geht (wie Fusion), auch mit Luft zwischen Skizze und Körper
und mit Startversatz ins Material. Vorher prüfte er nur einen Punkt direkt an der Skizze und blieb bei Join/New Body.
Ein Cut geht durch alle Körper auf seinem Weg, nicht nur durch den unter der Skizze."""
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


def circle_leave():
    s = Gui.ActiveDocument.getInEdit().Object; S["top"] = s
    c = s.Placement.inverse().multVec(App.Vector(120, 10, 10))
    s.addGeometry(Part.Circle(App.Vector(c.x, c.y, 0), App.Vector(0, 0, 1), 3)); doc().recompute()
    Gui.ActiveDocument.resetEdit()


def offset_extrude():
    prof = [o for o in S["top"].InList if o.TypeId == "Design::Profiles"][0]
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(prof, "Face1"); click(button("Design_Extrude"))


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
     ("cut 2", lambda: expect("Cut", "start offset 5 mm into the plate")), ("ok 2", ok), W])
