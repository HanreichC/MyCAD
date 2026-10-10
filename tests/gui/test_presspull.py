# SPDX-License-Identifier: LGPL-2.1-or-later
"""Press Pull: Oberseite herausziehen, Seitenfläche hineindrücken (Volumen nachrechenbar)."""
from harness import *


def side_face(b):  # Fläche mit kleinstem x (linke Seite)
    return "Face%d" % (1 + min(range(len(b.Shape.Faces)), key=lambda k: b.Shape.Faces[k].CenterOfMass.x))


run([
    ("setup", lambda: make_body(rect(0, 0, 60, 40), 0, 10, "Box")),
    ("pick top", lambda: Gui.Selection.addSelection(body("Box"), top_face(body("Box")))),
    ("Press Pull", lambda: click(button("Design_PressPull"))),
    ("+5", lambda: type_into(0, "5 mm")),
    ("OK", ok), ("volumes", lambda: L("%s expect 36000" % volumes())),
    ("pick side", lambda: Gui.Selection.addSelection(body("Box"), side_face(body("Box")))),
    ("Press Pull 2", lambda: click(button("Design_PressPull"))),
    ("-3", lambda: type_into(0, "-3 mm")),
    ("OK 2", ok), ("volumes", lambda: L("%s expect 34200 bb=%s" % (volumes(), body("Box").Shape.BoundBox))),
    ("errors", lambda: L("errors=%s" % errors())),
])
