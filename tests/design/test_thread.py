# SPDX-License-Identifier: LGPL-2.1-or-later
"""L3 Gewinde nach Norm: ISO-Profiltiefe, automatische Größe, Innengewinde, Spiel zum Drucken, Fehlertexte"""
from design import *


def cylinder(doc, r, h, z=0):
    sk = sketch(doc, circle(0, 0, r), App.Placement(V(0, 0, z), App.Rotation()))
    return extrude(doc, sk, h)[1]


def nut(doc, bore_r, h):
    """Block 20 x 20 x h mit Bohrung bore_r auf der Z-Achse"""
    _, b = box(doc, 20, 20, h, at=(-10, -10))
    sk = sketch(doc, circle(0, 0, bore_r))
    extrude(doc, sk, h, op="Cut", bodies=[b])
    return b


def cyl_face(body, inner=None):
    """Zylinderfläche; inner=True nimmt die kleinste (Bohrung), sonst die größte"""
    # gekrümmte Flächen (Extrusionen eines Kreises sind in Python keine Part::Cylinder, aber gekrümmt)
    faces = [(i, f) for i, f in enumerate(body.Shape.Faces, 1) if f.Surface.TypeId != "Part::GeomPlane"]
    i, _ = (min if inner else max)(faces, key=lambda x: x[1].BoundBox.XLength)
    return "Face%d" % i


def thread(doc, body, face, **props):
    return dress(doc, "Design::Thread", body, [face], **props)


def minor_radius(body):
    """kleinster Abstand der gekrümmten Flächen (Gewindegrund) von der Z-Achse; Stirnflächen enthalten die Achse"""
    axis = Part.LineSegment(V(0, 0, -50), V(0, 0, 50)).toShape()
    return min(axis.distToShape(f)[0] for f in body.Shape.Faces if f.Surface.TypeId != "Part::GeomPlane")


class Defaults(DesignTest):
    def test_new_thread_uses_iso_auto(self):
        b = cylinder(self.doc, 4, 20)
        f = thread(self.doc, b, cyl_face(b))
        self.assertEqual(f.Standard, "ISO metric")
        self.assertEqual(f.ThreadSize, "Auto")
        self.assertAlmostEqual(minor_radius(b), 4 - 0.6134 * 1.25, delta=0.01)


class External(DesignTest):
    def test_iso_profile_depth(self):
        b = cylinder(self.doc, 4, 20)
        thread(self.doc, b, cyl_face(b), Standard="ISO metric", ThreadSize="M8x1.25")
        self.assertNoErrors()
        self.assertTrue(b.Shape.isValid())
        self.assertAlmostEqual(minor_radius(b), 4 - 0.6134 * 1.25, delta=0.01)

    def test_auto_size_from_diameter(self):
        b = cylinder(self.doc, 3, 15)
        thread(self.doc, b, cyl_face(b), Standard="ISO metric")  # Auto → M6, Steigung 1.0
        self.assertNoErrors()
        self.assertAlmostEqual(minor_radius(b), 3 - 0.6134 * 1.0, delta=0.01)

    def test_custom_pitch(self):
        b = cylinder(self.doc, 5, 20)
        thread(self.doc, b, cyl_face(b), Standard="Custom", Pitch=2)
        self.assertNoErrors()
        self.assertAlmostEqual(minor_radius(b), 5 - 0.6134 * 2, delta=0.01)

    def test_standard_sizes_are_valid(self):
        for size, r in (("M3x0.5", 1.5), ("M5x0.8", 2.5), ("M12x1.75", 6), ("M24x3.0", 12)):
            b = cylinder(self.doc, r, 8 * r)
            f = thread(self.doc, b, cyl_face(b), Standard="ISO metric", ThreadSize=size)
            self.assertFalse(failed(f), size + ": " + f.getStatusString())
            self.assertTrue(b.Shape.isValid(), size)

    def test_clearance_makes_shaft_smaller(self):
        b = cylinder(self.doc, 4, 20)
        thread(self.doc, b, cyl_face(b), Standard="ISO metric", Clearance=0.2)
        self.assertNoErrors()
        self.assertLess(b.Shape.optimalBoundingBox().XMax, 4 - 0.19)
        self.assertAlmostEqual(minor_radius(b), 4 - 0.2 - 0.6134 * 1.25, delta=0.01)

    def test_pitch_hidden_for_standards(self):
        b = cylinder(self.doc, 4, 20)
        f = thread(self.doc, b, cyl_face(b), Standard="ISO metric")
        self.assertIn("Hidden", f.getPropertyStatus("Pitch"))
        self.assertIn("Auto", f.getEnumerationsOfProperty("ThreadSize"))
        f.Standard = "Custom"
        self.assertNotIn("Hidden", f.getPropertyStatus("Pitch"))


class Internal(DesignTest):
    def test_bore_gets_grooves(self):
        b = nut(self.doc, 3.4, 15)
        before = b.Shape.Volume
        thread(self.doc, b, cyl_face(b, inner=True), Standard="ISO metric")  # Auto → M8
        self.assertNoErrors()
        self.assertTrue(b.Shape.isValid())
        self.assertLess(b.Shape.Volume, before)
        self.assertGreater(b.Shape.Volume, before - PI * (4.0 ** 2 - 3.4 ** 2) * 15)


class Mating(DesignTest):
    """Welle und Mutter mit gleicher Lage: mit Spiel kein gemeinsames Volumen, mit Übermaß schon"""

    def pair(self, clearance):
        bolt = cylinder(self.doc, 4, 20)
        thread(self.doc, bolt, cyl_face(bolt), Standard="ISO metric", ThreadSize="M8x1.25", Clearance=clearance)
        d1 = 8 - 1.082532 * 1.25
        n = nut(self.doc, d1 / 2, 20)
        thread(self.doc, n, cyl_face(n, inner=True), Standard="ISO metric", ThreadSize="M8x1.25", Clearance=clearance)
        self.assertNoErrors()
        return bolt.Shape.common(n.Shape).Volume

    def test_clearance_fits(self):
        self.assertLess(self.pair(0.1), 0.01)

    def test_interference_overlaps(self):
        self.assertGreater(self.pair(-0.1), 1.0)


class Errors(DesignTest):
    def test_face_too_short(self):
        b = cylinder(self.doc, 4, 1)
        f = thread(self.doc, b, cyl_face(b), Standard="ISO metric", ThreadSize="M8x1.25")
        self.assertTrue(failed(f))
        self.assertIn("pitch", f.getStatusString())

    def test_clearance_too_large(self):
        b = cylinder(self.doc, 4, 20)
        f = thread(self.doc, b, cyl_face(b), Standard="ISO metric", ThreadSize="M8x1.25", Clearance=0.5)
        self.assertTrue(failed(f))
        self.assertIn("third of the pitch", f.getStatusString())

    def test_flat_face_rejected(self):
        b = cylinder(self.doc, 4, 20)
        f = thread(self.doc, b, top_face(b), Standard="ISO metric")
        self.assertTrue(failed(f))


class Persistence(DesignTest):
    def test_size_survives_save(self):
        b = cylinder(self.doc, 4, 20)
        f = thread(self.doc, b, cyl_face(b), Standard="ISO metric", ThreadSize="M8x1.25", Clearance=0.2)
        name, body_name, v = f.Name, b.Name, b.Shape.Volume
        doc = save_and_reload(self.doc)
        f = doc.getObject(name)
        self.assertEqual(f.ThreadSize, "M8x1.25")
        self.assertAlmostEqual(f.Clearance.Value, 0.2, places=6)
        f.touch()
        doc.recompute()
        self.assertAlmostEqual(doc.getObject(body_name).Shape.Volume, v, delta=v * 1e-6)
