# SPDX-License-Identifier: LGPL-2.1-or-later
"""Insert: STEP mit zwei Quadern -> Timeline-Eintrag mit zwei Bodies; DXF und SVG -> je eine Skizze mit Profilen.
Export: die DXF-Skizze wieder als DXF schreiben und einfügen -> gleiche Geometrie."""
import os
from harness import *

DATA = os.path.join(os.path.dirname(os.path.abspath(__file__)), "data")
STEP = os.environ["OUT"] + ".step"
DXF = os.path.join(os.path.dirname(os.environ["OUT"]), "plate_export.dxf")


def make_step():
    Part.makeCompound([Part.makeBox(10, 20, 30), Part.makeBox(5, 5, 5, App.Vector(50, 0, 0))]).exportStep(STEP)


def insert(path, command="Design_Import"):
    def pick():
        d = visible(QtWidgets.QFileDialog)
        L("  dialog=%s" % bool(d))
        name = [e for e in d[0].findChildren(QtWidgets.QLineEdit) if e.isVisible()][0]
        name.setText(path); d[0].accept()

    def boxes():
        for m in visible(QtWidgets.QMessageBox):
            L("  message: %s" % m.text()); m.close()
    QtCore.QTimer.singleShot(800, pick)
    QtCore.QTimer.singleShot(1200, boxes)
    click(button(command))


def sketch(label):
    return [o for o in doc().Objects if o.TypeId == "Sketcher::SketchObject" and o.Label == label][0]


def report_sketch(label):
    sk = sketch(label); bb = sk.Shape.BoundBox
    prof = [o for o in doc().Objects if o.TypeId == "Design::Profiles" and o.Sketch == sk][0]
    from collections import Counter
    L("%s: %s size=%.1f x %.1f profiles=%d" % (label, dict(Counter(g.TypeId.split("::")[1] for g in sk.Geometry)),
                                               bb.XLength, bb.YLength, len(prof.Shape.Faces)))


run([
    ("step file", make_step),
    ("insert step", lambda: insert(STEP)), ("wait", lambda: None),
    ("bodies", lambda: L("bodies=%s timeline=%s" % (volumes(), [o.Label for o in doc().Objects if o.TypeId == "Design::Import"]))),
    ("insert dxf", lambda: insert(os.path.join(DATA, "plate.dxf"))), ("wait", lambda: None),
    ("dxf", lambda: report_sketch("plate")),
    ("insert svg", lambda: insert(os.path.join(DATA, "logo.svg"))), ("wait", lambda: None),
    ("svg", lambda: report_sketch("logo")),
    ("select plate", lambda: (Gui.Selection.clearSelection(), Gui.Selection.addSelection(sketch("plate")))),
    ("export dxf", lambda: insert(DXF, "Design_Export")), ("wait", lambda: None),
    ("insert export", lambda: (Gui.Selection.clearSelection(), insert(DXF))), ("wait", lambda: None),
    ("dxf roundtrip", lambda: report_sketch("plate_export")),
    ("errors", lambda: L("errors=%s" % errors())),
    ("shot", lambda: shot("import")),
])
