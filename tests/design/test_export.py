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
        points, facets = DesignExport.triangles(a.Shape, "normal")
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
