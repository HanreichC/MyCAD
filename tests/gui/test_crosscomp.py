# SPDX-License-Identifier: LGPL-2.1-or-later
"""Über Komponentengrenzen: A in der Wurzel (x 0..20), B in einer um 10 mm verschobenen Komponente (global x 10..30).
Combine Cut A mit B -> A verliert die Überlappung; Mirror B an YZ -> Kopie global bei x -30..-10."""
from harness import *


def comp():
    return [o for o in doc().Objects if o.TypeId == "App::Part" and o.Type == "Component"][0]


def comp_plane():
    return [o for o in comp().Origin.OriginFeatures if o.Role == "XY_Plane"][0]


def bodies():
    return [o for o in doc().Objects if o.TypeId == "Design::Body"]


def global_x(b):
    k = b.Shape.BoundBox; dx = comp().Placement.Base.x if comp() in b.InListRecursive else 0
    return "x %.0f..%.0f" % (k.XMin + dx, k.XMax + dx)


def message():
    for m in visible(QtWidgets.QMessageBox):
        L("  message: %s" % m.text()); m.close()


run([
    ("A", lambda: make_body(rect(0, 0, 20, 20), 0, 10, "A")),
    ("New Component", lambda: click(button("Design_NewComponent"))),
    ("Create Sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick component XY", lambda: Gui.Selection.addSelection(comp_plane())),
    ("rect", lambda: [Gui.ActiveDocument.getInEdit().Object.addGeometry(g) for g in rect(0, 0, 20, 20)]),
    ("finish", lambda: click(button("Sketcher_LeaveSketch"))),
    ("Extrude", lambda: click(button("Design_Extrude"))), ("OK", ok),
    ("B", lambda: L("bodies=%s" % [(b.Label, round(b.Shape.Volume), global_x(b)) for b in bodies()])),
    ("select comp", lambda: (Gui.Selection.clearSelection(), Gui.Selection.addSelection(comp()))),
    ("Move comp", lambda: click(button("Design_Move"))), ("x 10", lambda: type_into(0, "10 mm")), ("OK move", ok),
    ("moved", lambda: L("component at %s, B %s" % (comp().Placement.Base, global_x(bodies()[1])))),
    ("combine sel", lambda: (Gui.Selection.clearSelection(), Gui.Selection.addSelection(body("A")), Gui.Selection.addSelection(bodies()[1]))),
    ("combine", lambda: (QtCore.QTimer.singleShot(700, message), Gui.runCommand("Design_Combine"))),
    ("cut", lambda: choose("Cut", 1)), ("OK combine", ok),
    ("combine?", lambda: L("combine: A volume=%.0f (erwartet %.0f) errors=%s" % (body("A").Shape.Volume, 4000 - 20 * 10 * 10, errors()))),
    ("mirror sel", lambda: (Gui.Selection.clearSelection(), Gui.Selection.addSelection(bodies()[1]))),
    ("mirror", lambda: (QtCore.QTimer.singleShot(700, message), Gui.runCommand("Design_Mirror"))),
    ("yz", lambda: choose("YZ plane", 2)), ("OK mirror", ok),
    ("mirror?", lambda: L("mirror: copy %s (erwartet x -30..-10) errors=%s" % (global_x(bodies()[-1]), errors()))),
])
