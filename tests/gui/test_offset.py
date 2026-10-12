# SPDX-License-Identifier: LGPL-2.1-or-later
"""Offset wie in Fusion: eine Kante anklicken genügt, die ganze zusammenhängende Kontur wird versetzt.
Kreis -> zweiter Kreis; eine Rechteckkante -> komplettes zweites Rechteck (4 Linien + 4 Eckbögen)."""
from harness import *


def sketch():
    return Gui.ActiveDocument.getInEdit().Object


def move(fx, fy):
    v = view(); QtTest.QTest.mouseMove(v.viewport(), QtCore.QPoint(int(v.width() * fx), int(v.height() * fy)))


def select(edge):
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(doc().Name, sketch().Name, edge)


def offset(fx, fy):  # Knopf wird erst kurz nach der Auswahl aktiv, daher eigener Schritt
    click(button("Sketcher_Offset"))
    QtCore.QTimer.singleShot(300, lambda: move(fx - 0.01, fy - 0.01))
    QtCore.QTimer.singleShot(600, lambda: move(fx, fy))
    QtCore.QTimer.singleShot(900, lambda: view_click(fx, fy))


def kinds():
    from collections import Counter
    return dict(Counter(g.TypeId.split("::")[1] for g in sketch().Geometry))


run([
    ("Create Sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick XY", lambda: Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XY_Plane")][0])),
    ("shapes", lambda: (sketch().addGeometry(Part.Circle(App.Vector(0, 0, 0), App.Vector(0, 0, 1), 10)),
                        sketch().addGeometry(rect(30, -10, 60, 10)), doc().recompute())),
    ("before", lambda: L("before=%s" % kinds())),
    ("select circle", lambda: select("Edge1")), ("circle", lambda: offset(0.47, 0.40)), ("wait", lambda: None),
    ("after circle", lambda: L("after circle=%s (2 Kreise erwartet)" % kinds())),
    ("select rect edge", lambda: select("Edge3")), ("rect edge", lambda: offset(0.80, 0.30)), ("wait", lambda: None),
    ("after rect", lambda: L("after one rect edge=%s (8 Linien + 4 Bögen erwartet)" % kinds())),
    ("shot", lambda: shot("offset")),
])
