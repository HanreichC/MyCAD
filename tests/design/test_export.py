# SPDX-License-Identifier: LGPL-2.1-or-later
"""L8 Austausch: 3MF mit Namen, Farben und wählbarer Auflösung; STEP hin und zurück mit gleichem Volumen"""
import os
import tempfile
import xml.etree.ElementTree as ET
import zipfile

import DesignExport
from design import *

NS = {"m": "http://schemas.microsoft.com/3dmanufacturing/core/2015/02"}


def read_model(path):
    with zipfile.ZipFile(path) as z:
        names = z.namelist()
        root = ET.fromstring(z.read("3D/3dmodel.model"))
    return names, root


def tmp(name):
    return os.path.join(tempfile.mkdtemp(), name)


class ThreeMF(DesignTest):
    def bodies(self):
        _, a = box(self.doc, 20, 10, 5)
        a.Label = "Base"
        sk = sketch(self.doc, circle(40, 5, 5))
        _, b = extrude(self.doc, sk, 10)
        b.Label = "Knob & Co"
        return a, b

    def test_objects_names_colors(self):
        a, b = self.bodies()
        path = tmp("t.3mf")
        DesignExport.write_3mf(path, [a, b], colors={a.Name: (1, 0, 0), b.Name: (0, 0, 1)})
        names, root = read_model(path)
        self.assertIn("[Content_Types].xml", names)
        self.assertIn("_rels/.rels", names)
        objects = root.findall("m:resources/m:object", NS)
        self.assertEqual([o.get("name") for o in objects], ["Base", "Knob & Co"])
        colors = [m.get("displaycolor") for m in root.findall("m:resources/m:basematerials/m:base", NS)]
        self.assertEqual(colors, ["#FF0000", "#0000FF"])
        self.assertEqual([o.get("pindex") for o in objects], ["0", "1"])
        self.assertEqual(len(root.findall("m:build/m:item", NS)), 2)

    def test_same_color_shares_one_material(self):
        a, b = self.bodies()
        path = tmp("t.3mf")
        DesignExport.write_3mf(path, [a, b], colors={a.Name: (0.5, 0.5, 0.5), b.Name: (0.5, 0.5, 0.5)})
        _, root = read_model(path)
        self.assertEqual(len(root.findall("m:resources/m:basematerials/m:base", NS)), 1)

    def test_each_face_keeps_its_color(self):
        """12.8: eine farbige Fläche (Appearance je Fläche) kommt als Farbe ihrer Dreiecke an, der Rest in Körperfarbe"""
        a, _ = self.bodies()
        top = max(range(len(a.Shape.Faces)), key=lambda i: a.Shape.Faces[i].CenterOfMass.z)
        look = [(0.5, 0.5, 0.5)] * len(a.Shape.Faces)
        look[top] = (1, 0, 0)
        old = DesignExport.face_colors
        DesignExport.face_colors = lambda body: look if body == a else []
        try:
            path = tmp("f.3mf")
            DesignExport.write_3mf(path, [a])
        finally:
            DesignExport.face_colors = old
        _, root = read_model(path)
        colors = [m.get("displaycolor") for m in root.findall("m:resources/m:basematerials/m:base", NS)]
        self.assertEqual(colors, ["#808080", "#FF0000"])
        obj = root.find("m:resources/m:object", NS)
        self.assertEqual(obj.get("pindex"), "0")
        points = [(float(v.get("x")), float(v.get("y")), float(v.get("z"))) for v in obj.findall(".//m:vertex", NS)]
        red = [t for t in obj.findall(".//m:triangle", NS) if t.get("p1") == "1"]
        self.assertEqual(len(red), 2)  # die Deckfläche 20 x 10: zwei Dreiecke
        for t in red:
            self.assertTrue(all(points[int(t.get(k))][2] == 5 for k in ("v1", "v2", "v3")))
        self.assertEqual(len(obj.findall(".//m:triangle", NS)), 12)

    def test_triangles_know_their_face(self):
        sk = sketch(self.doc, circle(0, 0, 10))
        _, cyl = extrude(self.doc, sk, 10)
        points, facets, face = DesignExport.triangles(cyl.Shape, "normal")
        self.assertEqual(sorted(set(face)), list(range(len(cyl.Shape.Faces))))
        for t, f in zip(facets, face):
            center = (points[t[0]] + points[t[1]] + points[t[2]]) * (1 / 3)
            self.assertLess(cyl.Shape.Faces[f].distToShape(Part.Vertex(center))[0], 0.1)

    def test_resolution_changes_triangle_count(self):
        sk = sketch(self.doc, circle(0, 0, 20))
        _, cyl = extrude(self.doc, sk, 10)
        counts = []
        for quality in ("coarse", "normal", "fine"):
            path = tmp(quality + ".3mf")
            DesignExport.write_3mf(path, [cyl], quality)
            _, root = read_model(path)
            counts.append(len(root.findall(".//m:triangle", NS)))
        self.assertLess(counts[0], counts[1])
        self.assertLess(counts[1], counts[2])

    def test_mesh_is_closed_and_matches_volume(self):
        a, _ = self.bodies()
        points, facets, _ = DesignExport.triangles(a.Shape, "normal")
        import Mesh
        m = Mesh.Mesh((points, facets))
        self.assertTrue(m.isSolid())
        self.assertAlmostEqual(m.Volume, 1000, delta=1)

    def test_component_placement_is_applied(self):
        comp = Design.newComponent(Design.root(self.doc))
        comp.Placement = App.Placement(V(100, 0, 0), App.Rotation())
        sk = sketch(self.doc, rect(0, 0, 10, 10), component=comp)
        _, b = extrude(self.doc, sk, 5)
        path = tmp("c.3mf")
        DesignExport.write_3mf(path, [b])
        _, root = read_model(path)
        xs = [float(v.get("x")) for v in root.findall(".//m:vertex", NS)]
        self.assertAlmostEqual(min(xs), 100, places=4)


class Step(DesignTest):
    def test_round_trip_keeps_volume(self):
        import Import
        _, a = box(self.doc, 20, 10, 5)
        sk = sketch(self.doc, circle(40, 5, 5))
        _, b = extrude(self.doc, sk, 10)
        path = tmp("t.step")
        Import.export([a, b], path)
        shape = Part.read(path)
        self.assertEqual(len(shape.Solids), 2)
        self.assertAlmostEqual(shape.Volume, 1000 + PI * 25 * 10, delta=0.01)

    def test_names_are_ascii(self):
        # U6: OCCT schreibt Namen roh als UTF-8; andere CAD-Programme brauchen ISO 10303-21 (\X2\…\X0\)
        self.assertEqual(DesignExport.step_ascii("Gehäuse Ø12"), "Geh\\X2\\00E4\\X0\\use \\X2\\00D8\\X0\\12")
        self.assertEqual(DesignExport.step_ascii("Größe"), "Gr\\X2\\00F600DF\\X0\\e")  # eine Folge, ein Block
        _, a = box(self.doc, 20, 10, 5)
        a.Label = "Gehäuse"
        path = tmp("u.step")
        DesignExport.write_step(path, [a])
        data = open(path, "rb").read()
        self.assertTrue(data.isascii())
        self.assertIn(b"Geh\\X2\\00E4\\X0\\use", data)
        self.assertAlmostEqual(Part.read(path).Volume, 1000, delta=0.01)  # die Datei bleibt lesbar

    def test_component_round_trip(self):
        # U7: Komponente mit Versatz und Drehung, Körper mit Rundungen: Lage und Volumen kommen so an (FreeCAD#25150)
        comp = Design.newComponent(Design.root(self.doc))
        comp.Placement = App.Placement(V(100, 20, 5), App.Rotation(V(0, 0, 1), 30))
        sk = sketch(self.doc, rect(0, 0, 30, 20), component=comp)
        _, b = extrude(self.doc, sk, 10)
        dress(self.doc, "Design::Fillet", b, ["Edge%d" % i for i in range(1, 5)], Size=2)
        self.doc.recompute()
        expected = b.Shape.copy()
        expected.Placement = comp.Placement.multiply(expected.Placement)
        path = tmp("c.step")
        DesignExport.write_step(path, [b])
        shape = Part.read(path)
        self.assertAlmostEqual(shape.Volume, b.Shape.Volume, delta=0.01 * b.Shape.Volume)
        self.assertLess((shape.BoundBox.Center - expected.BoundBox.Center).Length, 0.01)
        self.assertGreater(len([f for f in shape.Faces if "Cylinder" in f.Surface.TypeId or "BSpline" in f.Surface.TypeId]), 0)
        self.assertNotIn("StepExport", [o.Name[:10] for o in self.doc.Objects])  # die Kopie ist wieder weg
        b.Label = "Gehäuse"
        DesignExport.write_step(path, [b])
        self.assertIn(b"Geh\\X2\\00E4\\X0\\use'", open(path, "rb").read())  # Name des Originals, ohne 001
