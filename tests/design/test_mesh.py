# SPDX-License-Identifier: LGPL-2.1-or-later
"""12.1 Mesh-Brücke: STL/3MF/OBJ wird ein Körper mit glatten Ebenen und echten Bohrungen"""
import os
import tempfile
import time

from design import *
import Mesh
import MeshPart
import DesignMesh as M


def block():
    """Quader 40 x 30 x 10 mit Durchgangsbohrung r 3 und Sackloch r 2, 5 tief"""
    s = Part.makeBox(40, 30, 10)
    s = s.cut(Part.makeCylinder(3, 10, V(10, 15, 0)))
    s = s.cut(Part.makeCylinder(2, 5, V(28, 15, 5)))
    return s


def mesh_of(shape, angular=0.1):
    return MeshPart.meshFromShape(Shape=shape, LinearDeflection=0.01, AngularDeflection=angular, Relative=False)


class MeshBridge(unittest.TestCase):
    def test_block_comes_back_with_flat_faces_and_real_holes(self):
        original = block()
        mesh = mesh_of(original)
        start = time.time()
        body = M.solid(mesh)
        took = time.time() - start
        print("  %d triangles -> body in %.2f s" % (mesh.CountFacets, took))
        self.assertTrue(body.isValid())
        self.assertAlmostEqual(body.Volume, original.Volume, delta=original.Volume * 0.002)
        planes = [f for f in body.Faces if f.Surface.TypeId == "Part::GeomPlane"]
        radii = sorted(round(f.Surface.Radius, 2) for f in body.Faces if f.Surface.TypeId == "Part::GeomCylinder")
        self.assertEqual(len(planes), 7)  # sechs Seiten + Boden des Sacklochs
        self.assertEqual(radii, [2.0, 3.0])
        self.assertEqual(len(body.Faces), 9)

    def test_boss_stays_faceted_but_closed(self):
        """ein Zapfen (nach außen gewölbt) wird nicht ersetzt, der Körper bleibt trotzdem richtig"""
        original = Part.makeBox(20, 20, 5).fuse(Part.makeCylinder(4, 6, V(10, 10, 5))).removeSplitter()
        body = M.solid(mesh_of(original))
        self.assertTrue(body.isValid())
        self.assertAlmostEqual(body.Volume, original.Volume, delta=original.Volume * 0.01)
        self.assertFalse([f for f in body.Faces if f.Surface.TypeId == "Part::GeomCylinder"])

    def test_inner_fillet_is_no_hole(self):
        """eine Innenrundung ist nach innen gewölbt, aber kein voller Kreis: sie bleibt (sonst fehlte ein Stück)"""
        l_shape = Part.makeBox(20, 20, 5).fuse(Part.makeBox(5, 20, 20)).removeSplitter()
        inner = [e for e in l_shape.Edges if abs(e.CenterOfMass.x - 5) < 1e-6 and abs(e.CenterOfMass.z - 5) < 1e-6]
        original = l_shape.makeFillet(3, inner)
        body = M.solid(mesh_of(original))
        self.assertTrue(body.isValid())
        self.assertAlmostEqual(body.Volume, original.Volume, delta=original.Volume * 0.002)

    def test_open_mesh_says_so(self):
        mesh = mesh_of(Part.makeBox(10, 10, 10))
        mesh.removeFacets([0])
        with self.assertRaises(M.MeshError) as e:
            M.solid(mesh)
        self.assertIn("not closed", str(e.exception))

    def test_too_many_triangles_says_so(self):
        old = M.MAX_TRIANGLES
        M.MAX_TRIANGLES = 10
        try:
            with self.assertRaises(M.MeshError) as e:
                M.solid(mesh_of(block()))
            self.assertIn("triangles", str(e.exception))
        finally:
            M.MAX_TRIANGLES = old

    def test_too_much_free_form_says_so(self):
        """eine Kuppel bleibt aus einzelnen Dreiecken: über der Grenze eine Meldung statt minutenlangem Vernähen"""
        old = M.MAX_LOOSE
        M.MAX_LOOSE = 10
        try:
            with self.assertRaises(M.MeshError) as e:
                M.solid(mesh_of(Part.makeBox(20, 20, 5).fuse(Part.makeSphere(4, V(10, 10, 5))).removeSplitter()))
            self.assertIn("free-form", str(e.exception))
            self.assertEqual(e.exception.key().split("\x1f")[2], "10")  # Werte getrennt für die Übersetzung
        finally:
            M.MAX_LOOSE = old

    def test_reads_stl_obj_and_3mf(self):
        mesh = mesh_of(block())
        folder = tempfile.mkdtemp()
        for ext in ("stl", "obj", "3mf"):
            path = os.path.join(folder, "part." + ext)
            mesh.write(path)
            back = M.read(path)
            self.assertEqual(back.CountFacets, mesh.CountFacets, ext)
        with self.assertRaises(M.MeshError):
            M.read(os.path.join(folder, "missing.stl"))


if __name__ == "__main__":
    unittest.main()
