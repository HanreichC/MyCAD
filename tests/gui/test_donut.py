# SPDX-License-Identifier: LGPL-2.1-or-later
"""Donut per Revolve: Querschnitt (Kreis neben der Achse) auf der XZ-Ebene skizzieren, Profil anklicken, Revolve.
Revolve wählt selbst eine Achse, die den Querschnitt nicht schneidet (hier die Y-Achse der Skizze = globale Z-Achse)
-> Torus mit Volumen 2·π²·R·r²."""
import math
from harness import *

R, r = 30, 8


def sketch():
    return Gui.ActiveDocument.getInEdit().Object


def click_at(p):
    v = view(); x, y = Gui.ActiveDocument.ActiveView.getPointOnViewport(p)
    dpr = v.viewport().devicePixelRatioF()  # Coin zählt y von unten
    pt = QtCore.QPoint(int(x / dpr), int(v.viewport().height() - y / dpr))
    QtTest.QTest.mouseMove(v.viewport(), pt)
    QtTest.QTest.mouseClick(v.viewport(), QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, pt)


def axis():
    cb = [c for c in visible(QtWidgets.QComboBox) if c.findText("Sketch Y axis") >= 0][0]
    L("vorgewählte Achse=%s (erwartet Sketch Y axis)" % cb.currentText())


def result():
    vols = [v for (_, v, _) in volumes()]
    torus = round(2 * math.pi ** 2 * R * r * r, 1)
    L("volumes=%s torus=%s -> %s" % (vols, torus, "OK" if vols and abs(vols[-1] - torus) < 1 else "FALSCH"))


run([
    ("Create Sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick XZ", lambda: Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XZ_Plane")][0])),
    ("circle", lambda: (sketch().addGeometry(Part.Circle(App.Vector(R, 0, 0), App.Vector(0, 0, 1), r)), doc().recompute())),
    ("finish", lambda: click(button("Sketcher_LeaveSketch"))),
    ("fit", lambda: (Gui.Selection.clearSelection(), Gui.ActiveDocument.ActiveView.viewIsometric(), Gui.SendMsgToActiveView("ViewFit"))),
    ("click profile", lambda: click_at(App.Vector(R, 0, 0))),
    ("sel", lambda: L("selection=%s" % [(s.Object.TypeId, s.SubElementNames) for s in Gui.Selection.getSelectionEx()])),
    ("revolve", lambda: click(button("Design_Revolve"))),
    ("axis", axis), ("wait", lambda: None),
    ("ok", ok), ("wait", lambda: None),
    ("result", result), ("errors", lambda: L("errors=%s" % errors())),
    ("view", lambda: (Gui.ActiveDocument.ActiveView.viewIsometric(), Gui.SendMsgToActiveView("ViewFit"))),
    ("shot", lambda: shot("donut")),
])
