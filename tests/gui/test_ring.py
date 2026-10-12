# SPDX-License-Identifier: LGPL-2.1-or-later
"""Wie in Fusion: Skizze mit zwei Kreisen ineinander, Skizze beenden, den Ring anklicken, Extrude
-> nur der Ring wird extrudiert (Rohr mit Loch), nicht der volle Zylinder.
Ältere Dokumente (Skizze mit eigenen Innenflächen) werden beim Öffnen umgestellt."""
import math
import os
from harness import *

R, r, H = 20, 10, 10


def sketch():
    return Gui.ActiveDocument.getInEdit().Object


def circles():
    for rad in (R, r):
        sketch().addGeometry(Part.Circle(App.Vector(0, 0, 0), App.Vector(0, 0, 1), rad))
    doc().recompute()


def click_at(p):
    v = view(); x, y = Gui.ActiveDocument.ActiveView.getPointOnViewport(p)
    dpr = v.viewport().devicePixelRatioF()  # Coin zählt y von unten
    pt = QtCore.QPoint(int(x / dpr), int(v.viewport().height() - y / dpr))
    QtTest.QTest.mouseMove(v.viewport(), pt)
    QtTest.QTest.mouseClick(v.viewport(), QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, pt)


def selection():
    L("selection=%s" % [(s.Object.TypeId, s.SubElementNames) for s in Gui.Selection.getSelectionEx()])


def result():
    vols = [v for (_, v, _) in volumes()]
    ring = round(math.pi * (R * R - r * r) * H, 1)
    L("volumes=%s ring=%s full=%s -> %s" % (vols, ring, round(math.pi * R * R * H, 1),
                                           "OK" if vols and abs(vols[-1] - ring) < 1 else "FALSCH"))


def old_doc():
    for o in doc().Objects:
        if o.TypeId == "Sketcher::SketchObject":
            o.MakeInternals = True
    path = os.environ["OUT"] + ".FCStd"; doc().saveAs(path); App.closeDocument(doc().Name)


run([
    ("Create Sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick XY", lambda: Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XY_Plane")][0])),
    ("circles", circles),
    ("finish", lambda: click(button("Sketcher_LeaveSketch"))),
    ("fit", lambda: (Gui.Selection.clearSelection(), Gui.SendMsgToActiveView("ViewFit"))),
    ("shot sketch", lambda: shot("sketch")),
    ("click ring", lambda: click_at(App.Vector((R + r) / 2, 0, 0))),
    ("sel", selection), ("shot sel", lambda: shot("sel")),
    ("extrude", lambda: click(button("Design_Extrude"))),
    ("distance", lambda: type_into(0, str(H))),
    ("ok", ok), ("wait", lambda: None),
    ("result", result), ("errors", lambda: L("errors=%s" % errors())),
    ("old doc", old_doc), ("reopen", lambda: App.openDocument(os.environ["OUT"] + ".FCStd")),
    ("internals", lambda: L("internals after reopen=%s (muss False sein)" % [o.MakeInternals for o in doc().Objects if o.TypeId == "Sketcher::SketchObject"])),
])
