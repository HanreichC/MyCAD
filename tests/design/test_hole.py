# SPDX-License-Identifier: LGPL-2.1-or-later
"""L2 Bohrung nach Norm: ISO 273 Durchgang, Kernloch, UNC, Senkungen nach Schraubennorm, durch alles, modelliert"""
from design import *


def hole(doc, body, points, z, **props):
    """Bohrungen an Punkten einer Skizze in Höhe z, nach unten in body"""
    sk = sketch(doc, [Part.Point(V(x, y, 0)) for x, y in points], App.Placement(V(0, 0, z), App.Rotation()))
    f = feature(doc, "Design::Hole", Design.componentOf(body), Sketch=sk)
    for k, v in props.items():
        setattr(f, k, v)
    Design.attachToBodies(f, [body])
    doc.recompute()
    return f


def block(doc, h=10):
    return box(doc, 30, 30, h, at=(-15, -15))[1]


class Custom(DesignTest):
    def test_simple_hole_unchanged(self):
        b = block(self.doc)
        hole(self.doc, b, [(0, 0)], 10, Diameter=5, Depth=6)
        self.assertNoErrors()
        self.assertVolume(b, 9000 - PI * 2.5 ** 2 * 6)

    def test_custom_dimensions_stay_editable(self):
        b = block(self.doc)
        f = hole(self.doc, b, [(0, 0)], 10)
        self.assertNotIn("ReadOnly", f.getPropertyStatus("Diameter"))
        self.assertIn("Hidden", f.getPropertyStatus("Size"))


class Metric(DesignTest):
    def test_clearance_fits_iso_273(self):
        b = block(self.doc)
        f = hole(self.doc, b, [(0, 0)], 10, Standard="ISO metric", Size="M5x0.8", Kind="Clearance hole")
        for fit, d in (("Fine", 5.3), ("Medium", 5.5), ("Coarse", 5.8)):
            f.Fit = fit
            self.assertAlmostEqual(f.Diameter.Value, d, places=6, msg=fit)
        self.assertIn("ReadOnly", f.getPropertyStatus("Diameter"))
        self.assertEqual(f.ThreadDesignation, "")

    def test_tapped_uses_tap_drill(self):
        b = block(self.doc)
        f = hole(self.doc, b, [(0, 0)], 10, Standard="ISO metric", Size="M8x1.25", Kind="Tapped hole", Depth=8)
        self.assertAlmostEqual(f.Diameter.Value, 6.8, places=6)
        self.assertEqual(f.ThreadDesignation, "M8x1.25")
        self.assertIn("Hidden", f.getPropertyStatus("Fit"))
        self.assertNotIn("Hidden", f.getPropertyStatus("Modeled"))
        self.assertVolume(b, 9000 - PI * 3.4 ** 2 * 8)

    def test_switching_standard_keeps_nearest_size(self):
        b = block(self.doc)
        f = hole(self.doc, b, [(0, 0)], 10, Diameter=5.6)
        f.Standard = "ISO metric"
        self.assertEqual(f.Size, "M6x1.0")
        f.Standard = "Custom"
        self.assertNotIn("ReadOnly", f.getPropertyStatus("Diameter"))

    def test_fine_thread_table(self):
        b = block(self.doc)
        f = hole(self.doc, b, [(0, 0)], 10, Standard="ISO metric fine", Size="M8x1.0", Kind="Tapped hole")
        self.assertAlmostEqual(f.Diameter.Value, 7.0, places=6)


class Inch(DesignTest):
    def test_unc_quarter(self):
        b = block(self.doc)
        f = hole(self.doc, b, [(0, 0)], 10, Standard="UNC", Size="1/4", Kind="Tapped hole")
        self.assertAlmostEqual(f.Diameter.Value, 5.1, places=6)
        f.Kind = "Clearance hole"
        for fit, d in (("Fine", 6.8), ("Medium", 7.1), ("Coarse", 7.5)):
            f.Fit = fit
            self.assertAlmostEqual(f.Diameter.Value, d, places=6, msg=fit)


class Heads(DesignTest):
    def test_counterbore_from_screw_standard(self):
        b = block(self.doc)
        f = hole(self.doc, b, [(0, 0)], 10, Standard="ISO metric", Size="M5x0.8", HoleType="Counterbore",
                 ThroughAll=True)
        self.assertIn("ISO 4762", f.getEnumerationsOfProperty("Screw"))
        self.assertIn("DIN 7984", f.getEnumerationsOfProperty("Screw"))
        self.assertEqual(f.Screw, "ISO 4762")  # die gängigste ist vorausgewählt
        self.doc.recompute()
        self.assertAlmostEqual(f.HeadDiameter.Value, 10.0, places=6)
        self.assertAlmostEqual(f.HeadDepth.Value, 5.4, places=6)
        self.assertIn("ReadOnly", f.getPropertyStatus("HeadDepth"))
        self.assertVolume(b, 9000 - PI * 2.75 ** 2 * (10 - 5.4) - PI * 25 * 5.4)
        f.Screw = "DIN 7984"
        self.assertAlmostEqual(f.HeadDepth.Value, 4.0, places=6)

    def test_countersink_from_screw_standard(self):
        b = block(self.doc)
        f = hole(self.doc, b, [(0, 0)], 10, Standard="ISO metric", Size="M5x0.8", HoleType="Countersink")
        self.assertEqual(f.Screw, "ISO 10642")
        self.assertAlmostEqual(f.HeadDiameter.Value, 11.2, places=6)
        self.assertAlmostEqual(f.CountersinkAngle.Value, 90, places=6)
        self.assertNoErrors()

    def test_simple_hole_has_no_screw(self):
        b = block(self.doc)
        f = hole(self.doc, b, [(0, 0)], 10, Standard="ISO metric", Size="M5x0.8")
        self.assertIn("Hidden", f.getPropertyStatus("Screw"))


class Depths(DesignTest):
    def test_through_all_reaches_tall_body(self):
        sk = sketch(self.doc, rect(-15, -15, 15, 15))
        _, b = extrude(self.doc, sk, 3000)
        hole(self.doc, b, [(0, 0)], 3000, Diameter=4, ThroughAll=True)
        self.assertNoErrors()
        self.assertVolume(b, 900 * 3000 - PI * 4 * 3000)

    def test_modeled_thread_cuts_grooves(self):
        b = block(self.doc)
        f = hole(self.doc, b, [(0, 0)], 10, Standard="ISO metric", Size="M8x1.25", Kind="Tapped hole", ThroughAll=True,
                 Modeled=True)
        self.assertNoErrors()
        self.assertTrue(b.Shape.isValid())
        v = b.Shape.Volume
        self.assertLess(v, 9000 - PI * 3.4 ** 2 * 10)  # mehr weg als das Kernloch
        self.assertGreater(v, 9000 - PI * 4.0 ** 2 * 10)  # weniger als ein Loch mit Nenndurchmesser

    def test_several_points(self):
        b = block(self.doc)
        hole(self.doc, b, [(-8, -8), (8, -8), (8, 8), (-8, 8)], 10, Diameter=3, Depth=5)
        self.assertVolume(b, 9000 - 4 * PI * 1.5 ** 2 * 5)


class Persistence(DesignTest):
    def test_standard_survives_save(self):
        b = block(self.doc)
        f = hole(self.doc, b, [(0, 0)], 10, Standard="ISO metric", Size="M5x0.8", HoleType="Counterbore")
        f.Screw = "DIN 7984"
        name = f.Name
        doc = save_and_reload(self.doc)
        f = doc.getObject(name)
        self.assertEqual(f.Size, "M5x0.8")
        self.assertEqual(f.Screw, "DIN 7984")
        self.assertAlmostEqual(f.HeadDepth.Value, 4.0, places=6)
        self.assertIn("ReadOnly", f.getPropertyStatus("Diameter"))
