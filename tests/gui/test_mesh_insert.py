# SPDX-License-Identifier: LGPL-2.1-or-later
"""Mesh-Brücke (Plan 12.1): Einfügen nimmt eine STL; daraus wird ein Körper mit glatten Ebenen und einer echten
Bohrung, in der Timeline wie ein STEP. Ein offenes Mesh meldet, warum es kein Körper wird. Fehler stehen als FAIL im
Protokoll."""
import os
from harness import *
import Mesh
import MeshPart

STL = os.environ["OUT"] + ".input.stl"
OPEN = os.environ["OUT"] + ".open.stl"
state = {}


def write_files():
    part = Part.makeBox(40, 30, 10).cut(Part.makeCylinder(3, 10, App.Vector(12, 15, 0)))
    mesh = MeshPart.meshFromShape(Shape=part, LinearDeflection=0.01, AngularDeflection=0.1, Relative=False)
    mesh.write(STL)
    mesh.removeFacets([0])
    mesh.write(OPEN)


def insert(path):
    def pick():
        d = visible(QtWidgets.QFileDialog)
        name = [e for e in d[0].findChildren(QtWidgets.QLineEdit) if e.isVisible()][0]
        name.setText(path); d[0].accept()
    QtCore.QTimer.singleShot(800, pick)
    click(button("Design_Import"))


def bodies():
    return [o for o in doc().Objects if o.TypeId == "Design::Body"]


def check_body():
    b = [x for x in bodies() if x.Label == "test_mesh_insert.input"]
    check("the STL became a body named after the file", len(b) == 1, str([x.Label for x in bodies()]))
    if not b:
        return
    shape = b[0].Shape
    planes = sum(1 for f in shape.Faces if f.Surface.TypeId == "Part::GeomPlane")
    holes = [round(f.Surface.Radius, 2) for f in shape.Faces if f.Surface.TypeId == "Part::GeomCylinder"]
    check("flat faces are one face each, the hole is a real cylinder", planes == 6 and holes == [3.0],
          "planes %d holes %s faces %d" % (planes, holes, len(shape.Faces)))
    check("valid solid with the volume of the part", shape.isValid() and abs(shape.Volume - (12000 - 3.14159265 * 90)) < 1)
    check("one entry in the timeline", any(o.TypeId == "Design::Import" for o in Design.timeline(doc())))
    shot("body")


def check_open():
    boxes = [m for m in visible(QtWidgets.QMessageBox)]
    texts = " ".join(l.text() for m in boxes for l in m.findChildren(QtWidgets.QLabel))  # Titel und Meldung
    check("an open mesh says why", "not closed" in texts, texts)
    for m in boxes:
        m.accept()


import Design

in_order([
    ("files", write_files),
    ("setup", lambda: App.newDocument("Mesh")), ("wait", lambda: None),
    ("insert", lambda: insert(STL)), ("wait", lambda: None), ("wait", lambda: None),
    ("check body", check_body),
    ("insert open", lambda: insert(OPEN)), ("wait", lambda: None), ("wait", lambda: None),
    ("check open", check_open),
])
