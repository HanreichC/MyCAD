# SPDX-License-Identifier: LGPL-2.1-or-later
"""Helfer für Headless-Tests: Designs per Skript aufbauen, auf demselben Weg wie die Werkzeuge der Oberfläche."""
import math
import os
import tempfile
import unittest

import FreeCAD as App
import Part
import Sketcher  # noqa: F401  (registriert Sketcher::SketchObject)
import Design

V = App.Vector


def new_doc(name="Test"):
    doc = App.newDocument(name)
    Design.root(doc)
    return doc


def rect(x0, y0, x1, y1):
    p = [V(x0, y0, 0), V(x1, y0, 0), V(x1, y1, 0), V(x0, y1, 0)]
    return [Part.LineSegment(p[i], p[(i + 1) % 4]) for i in range(4)]


def circle(cx, cy, r):
    return [Part.Circle(V(cx, cy, 0), V(0, 0, 1), r)]


def sketch(doc, geos, placement=None, component=None, support=None):
    """Skizze mit Profilen; support = (Objekt, "FaceN") hängt sie an eine Fläche"""
    sk = Design.newSketch(component or Design.root(doc))
    if placement is not None:
        sk.Placement = placement
    if support is not None:
        sk.AttachmentSupport = [support]
        sk.MapMode = "FlatFace"
    for g in geos:
        sk.addGeometry(g)
    doc.recompute()
    return sk


def profiles(sk):
    return [o for o in sk.InList if o.TypeId == "Design::Profiles"][0]


def feature(doc, type_id, component=None, **props):
    f = doc.addObject(type_id, type_id.split("::")[1])
    (component or Design.root(doc)).addObject(f)
    Design.addToTimeline(f)
    for k, v in props.items():
        setattr(f, k, v)
    return f


def new_body(f):
    """Feature erzeugt einen neuen Body (Operation New Body)"""
    return Design.newBody(f)


def extrude(doc, sk, distance, op="New Body", bodies=(), faces=None, **props):
    prof = profiles(sk)
    f = feature(doc, "Design::Extrude", Design.componentOf(sk), Distance=distance, **props)
    count = len(prof.Shape.Faces)
    f.Profile = (prof, faces or ["Face%d" % i for i in range(1, count + 1)])
    f.Operation = op
    if op == "New Body":
        body = new_body(f)
    else:
        Design.attachToBodies(f, list(bodies))
        body = bodies[0]
    doc.recompute()
    return f, body


def box(doc, x, y, z, at=(0, 0)):
    """Quader x*y*z ab (at) auf XY, als Skizze + Extrude"""
    sk = sketch(doc, rect(at[0], at[1], at[0] + x, at[1] + y))
    return extrude(doc, sk, z)


def dress(doc, type_id, body, elements, **props):
    f = feature(doc, type_id, Design.componentOf(body), Edges=list(elements), **props)
    Design.attachToBodies(f, [body])
    doc.recompute()
    return f


def edge_where(body, pred):
    """Name der ersten Kante, deren Mittelpunkt pred erfüllt"""
    for i, e in enumerate(body.Shape.Edges, 1):
        if pred(e.CenterOfMass if hasattr(e, "CenterOfMass") else e.valueAt(0.5 * (e.FirstParameter + e.LastParameter))):
            return "Edge%d" % i
    raise AssertionError("no matching edge")


def face_where(body, pred):
    for i, f in enumerate(body.Shape.Faces, 1):
        if pred(f.CenterOfMass, f):
            return "Face%d" % i
    raise AssertionError("no matching face")


def top_face(body):
    return "Face%d" % (1 + max(range(len(body.Shape.Faces)), key=lambda k: body.Shape.Faces[k].CenterOfMass.z))


def failed(obj):
    return "Invalid" in obj.State


def errors(doc):
    return [(o.Name, o.getStatusString()) for o in doc.Objects if failed(o)]


def save_and_reload(doc):
    path = os.path.join(tempfile.mkdtemp(), "t.FCStd")
    doc.saveAs(path)
    App.closeDocument(doc.Name)
    return App.openDocument(path)


class DesignTest(unittest.TestCase):
    """Jeder Test bekommt ein frisches Design; assertVolume vergleicht mit 0,1 % Toleranz"""

    def setUp(self):
        self.doc = new_doc(self.id().split(".")[-1][:40])

    def tearDown(self):
        for d in list(App.listDocuments()):
            App.closeDocument(d)

    def assertVolume(self, shape_or_body, expected, rel=1e-3):
        shape = getattr(shape_or_body, "Shape", shape_or_body)
        self.assertTrue(shape.isValid(), "shape is not valid")
        self.assertAlmostEqual(shape.Volume, expected, delta=max(abs(expected) * rel, 1e-6))

    def assertNoErrors(self, doc=None):
        self.assertEqual(errors(doc or self.doc), [])


PI = math.pi
