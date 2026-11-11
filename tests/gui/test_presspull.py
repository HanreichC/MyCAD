# SPDX-License-Identifier: LGPL-2.1-or-later
"""Press Pull: Esc verwirft wie Cancel; Oberseite herausziehen, Seitenfläche hineindrücken (Volumen nachrechenbar)."""
from harness import *


def side_face(b):  # Fläche mit kleinstem x (linke Seite)
    return "Face%d" % (1 + min(range(len(b.Shape.Faces)), key=lambda k: b.Shape.Faces[k].CenterOfMass.x))


def ok_then_type():
    """Tasten, die noch ins Feld gehen, nachdem OK den Dialog geschlossen hat (er wird erst danach gelöscht)"""
    box = sorted(visible(QtWidgets.QAbstractSpinBox), key=lambda w: w.mapToGlobal(QtCore.QPoint(0, 0)).y())[0]
    ok()
    box.lineEdit().selectAll(); QtTest.QTest.keyClicks(box.lineEdit(), "8"); QtTest.QTest.keyClick(box.lineEdit(), QtCore.Qt.Key_Return)


run([
    ("setup", lambda: make_body(rect(0, 0, 60, 40), 0, 10, "Box")),
    ("pick esc", lambda: Gui.Selection.addSelection(body("Box"), top_face(body("Box")))),
    ("Press Pull esc", lambda: click(button("Design_PressPull"))),
    # Fokus nicht im Panel (etwa nach einem Klick in die Ansicht): Esc geht über das 3D-Fenster
    ("unfocus", lambda: Gui.ActiveDocument.ActiveView.graphicsView().scene().clearFocus()),
    ("esc", esc),
    ("discarded", lambda: check("Esc discards the Press Pull", not Gui.Control.activeDialog() and volumes() == [("Box", 24000.0, True)]
                                and not [o for o in doc().Objects if o.TypeId == "Design::PressPull"], str(volumes()))),
    ("clear", Gui.Selection.clearSelection),
    ("pick top", lambda: Gui.Selection.addSelection(body("Box"), top_face(body("Box")))),
    ("Press Pull", lambda: click(button("Design_PressPull"))),
    ("+5", lambda: type_into(0, "5 mm")),
    ("OK", ok_then_type), ("volumes", lambda: L("%s expect 36000" % volumes())),
    ("closed", lambda: check("keys after OK do not change the feature", volumes() == [("Box", 36000.0, True)], str(volumes()))),
    ("pick side", lambda: Gui.Selection.addSelection(body("Box"), side_face(body("Box")))),
    ("Press Pull 2", lambda: click(button("Design_PressPull"))),
    ("-3", lambda: type_into(0, "-3 mm")),
    ("OK 2", ok), ("volumes", lambda: L("%s expect 34200 bb=%s" % (volumes(), body("Box").Shape.BoundBox))),
    ("cylinder", lambda: make_body([Part.Circle(App.Vector(100, 0, 0), App.Vector(0, 0, 1), 8)], 0, 20, "Cyl")),
    ("pick mantle", lambda: (Gui.Selection.clearSelection(), Gui.Selection.addSelection(body("Cyl"), "Face%d" % (1 + [f.Surface.TypeId for f in body("Cyl").Shape.Faces].index("Part::GeomCylinder"))))),
    ("Press Pull 3", lambda: click(button("Design_PressPull"))),
    ("+2", lambda: type_into(0, "2 mm")),
    ("OK 3", ok), ("cyl", lambda: L("cylinder: %.0f expect 6283 (r 8 -> 10)" % body("Cyl").Shape.Volume)),
    ("errors", lambda: L("errors=%s" % errors())),
])
