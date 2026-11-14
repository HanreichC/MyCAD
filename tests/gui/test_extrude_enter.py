# SPDX-License-Identifier: LGPL-2.1-or-later
"""Enter bestätigt den Extrude-Dialog, auch wenn die Werkzeugleiste noch den Fokus hat (nach dem Klick auf "Extrudieren"
kam Enter dort an und verpuffte). Die Skizze verschwindet nach dem ersten Extrude wie in Fusion; blendet man sie wieder
ein und extrudiert noch einmal, bleibt sie sichtbar."""
from harness import *
import Design

S = {}
W = ("wait", lambda: None)


def setup():
    d = doc(); root = [o for o in d.Objects if o.TypeId == "App::Part"][0]
    S["sk"] = Design.newSketch(root)
    for g in rect(0, 0, 10, 10):
        S["sk"].addGeometry(g)
    d.recompute()


def start():
    prof = [o for o in S["sk"].InList if o.TypeId == "Design::Profiles"][0]
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(prof, "Face1")
    click(button("Design_Extrude"))


def enter():
    """Fokus wie nach dem Klick in der Werkzeugleiste, Enter an den 3D-Viewer (dort landet die Tastatur)"""
    button("Design_Extrude").setFocus()
    QtTest.QTest.keyClick(view(), QtCore.Qt.Key_Return)


def extrudes():
    return len([o for o in doc().Objects if o.TypeId == "Design::Extrude"])


def first():
    check("Enter confirms the extrude dialog while the toolbar has the focus", not Gui.Control.activeDialog() and extrudes() == 1,
          "dialog=%s extrudes=%d" % (Gui.Control.activeDialog(), extrudes()))
    check("the sketch is hidden after its first extrude", not S["sk"].Visibility)


def second():
    check("Enter confirms the second extrude too", not Gui.Control.activeDialog() and extrudes() == 2,
          "dialog=%s extrudes=%d" % (Gui.Control.activeDialog(), extrudes()))
    check("a sketch shown again on purpose stays visible after the next extrude", S["sk"].Visibility)


run([("activate", activate), ("setup", setup), W,
     ("start", start), W, ("enter", enter), W, ("first", first),
     ("show", lambda: setattr(S["sk"], "Visibility", True)), W,
     ("start 2", start), W, ("enter 2", enter), W, ("second", second)])
