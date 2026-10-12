# SPDX-License-Identifier: LGPL-2.1-or-later
"""Skizze nach einem Extrude weiterverwenden: Kreis extrudieren (Skizze wird ausgeblendet), Skizze wieder
bearbeiten und ein Rechteck daneben zeichnen -> das Rechteck ist anklickbar und lässt sich extrudieren.
Auch: Skizze über das Auge wieder einblenden -> ihre Profile sind wieder da."""
from harness import *


def sketch_obj():
    return [o for o in doc().Objects if o.TypeId == "Sketcher::SketchObject"][0]


def profiles():
    return [o for o in doc().Objects if o.TypeId == "Design::Profiles"][0]


def click_at(p):
    v = view(); x, y = Gui.ActiveDocument.ActiveView.getPointOnViewport(p)
    dpr = v.viewport().devicePixelRatioF()  # Coin zählt y von unten
    pt = QtCore.QPoint(int(x / dpr), int(v.viewport().height() - y / dpr))
    QtTest.QTest.mouseMove(v.viewport(), pt)
    QtTest.QTest.mouseClick(v.viewport(), QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, pt)


def state(tag):
    L("%s: sketch visible=%s profiles visible=%s selection=%s" % (
        tag, sketch_obj().Visibility, profiles().Visibility,
        [(s.Object.TypeId, s.SubElementNames) for s in Gui.Selection.getSelectionEx()]))


def add(geos):
    s = Gui.ActiveDocument.getInEdit().Object
    for g in geos:
        s.addGeometry(g)
    doc().recompute()


def fit():
    Gui.Selection.clearSelection(); Gui.ActiveDocument.ActiveView.viewIsometric(); Gui.SendMsgToActiveView("ViewFit")


run([
    ("Create Sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick XY", lambda: Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XY_Plane")][0])),
    ("circle", lambda: add([Part.Circle(App.Vector(0, 0, 0), App.Vector(0, 0, 1), 10)])),
    ("finish", lambda: click(button("Sketcher_LeaveSketch"))),
    ("extrude circle", lambda: click(button("Design_Extrude"))), ("dist", lambda: type_into(0, "10")),
    ("ok", ok), ("wait", lambda: None),
    ("after extrude", lambda: state("nach Extrude (beides aus)")),
    ("edit again", lambda: Gui.ActiveDocument.setEdit(sketch_obj().Name)),
    ("rect", lambda: add(rect(30, -10, 60, 10))),
    ("finish2", lambda: click(button("Sketcher_LeaveSketch"))),
    ("show sketch", lambda: setattr(sketch_obj(), "Visibility", True)),  # wie das Auge im Browser
    ("fit", fit),
    ("shown", lambda: state("Skizze eingeblendet (Profile müssen sichtbar sein)")),
    ("click rect", lambda: click_at(App.Vector(45, 0, 0))),
    ("sel", lambda: state("Rechteck angeklickt")), ("shot", lambda: shot("sel")),
    ("extrude rect", lambda: click(button("Design_Extrude"))), ("dist2", lambda: type_into(0, "5")),
    ("ok2", ok), ("wait2", lambda: None),
    ("volumes", lambda: L("volumes=%s (Zylinder 3141.6, Rechteck 30x20x5 = 3000)" % volumes())),
    ("hide", lambda: setattr(sketch_obj(), "Visibility", False)),
    ("hidden", lambda: state("Auge aus")),
    ("show", lambda: setattr(sketch_obj(), "Visibility", True)),
    ("again", lambda: state("Auge an")),
    ("errors", lambda: L("errors=%s" % errors())),
])
