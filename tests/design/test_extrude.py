# SPDX-License-Identifier: LGPL-2.1-or-later
"""L1 Extrude: Ausdehnungen (Symmetrisch, Zwei Seiten, Bis Objekt, Alle), Verjüngung, dünne Wand"""
from design import *


def slanted_plane(doc, z0=10):
    """Fremdes Objekt mit einer schrägen Fläche z = z0 + y (für "Bis Objekt")"""
    pts = [V(-50, -50, z0 - 50), V(50, -50, z0 - 50), V(50, 50, z0 + 50), V(-50, 50, z0 + 50)]
    f = doc.addObject("Part::Feature", "Slant")
    f.Shape = Part.Face(Part.makePolygon(pts + [pts[0]]))
    doc.recompute()
    return f


def flat_plane(doc, z):
    f = doc.addObject("Part::Feature", "Flat")
    f.Shape = Part.makePlane(200, 200, V(-100, -100, z))
    doc.recompute()
    return f


def frustum(a, b, h):
    """Pyramidenstumpf mit quadratischen Flächen a² und b²"""
    return h / 3 * (a * a + b * b + a * b)


class Extents(DesignTest):
    def test_symmetric(self):
        sk = sketch(self.doc, rect(0, 0, 10, 10))
        f, body = extrude(self.doc, sk, 10, Extent="Symmetric")
        self.assertVolume(body, 1000)
        bb = body.Shape.BoundBox
        self.assertAlmostEqual(bb.ZMin, -5, places=6)
        self.assertAlmostEqual(bb.ZMax, 5, places=6)

    def test_two_sides(self):
        sk = sketch(self.doc, rect(0, 0, 10, 10))
        f, body = extrude(self.doc, sk, 10, Extent="Two Sides", Distance2=4)
        self.assertVolume(body, 1400)
        self.assertAlmostEqual(body.Shape.BoundBox.ZMin, -4, places=6)

    def test_all_cuts_through_every_body(self):
        _, low = box(self.doc, 20, 20, 5)
        sk_high = sketch(self.doc, rect(0, 0, 20, 20), App.Placement(V(0, 0, 30), App.Rotation()))
        _, high = extrude(self.doc, sk_high, 5)
        hole = sketch(self.doc, circle(10, 10, 3), App.Placement(V(0, 0, 100), App.Rotation()))
        f, _ = extrude(self.doc, hole, 1, op="Cut", bodies=[low, high], Extent="All", Reversed=True)
        self.assertNoErrors()
        for b in (low, high):
            self.assertVolume(b, 2000 - PI * 9 * 5)

    def test_all_reaches_far_bodies(self):
        _, far = box(self.doc, 20, 20, 5, at=(0, 0))
        far_sk = sketch(self.doc, rect(0, 0, 20, 20), App.Placement(V(0, 0, 3000), App.Rotation()))
        _, very_far = extrude(self.doc, far_sk, 5)
        hole = sketch(self.doc, circle(10, 10, 3), App.Placement(V(0, 0, -50), App.Rotation()))
        extrude(self.doc, hole, 1, op="Cut", bodies=[very_far], Extent="All")
        self.assertNoErrors()
        self.assertVolume(very_far, 2000 - PI * 9 * 5)


class ToObject(DesignTest):
    def test_up_to_face_of_other_body(self):
        top_sk = sketch(self.doc, rect(-5, -5, 25, 25), App.Placement(V(0, 0, 10), App.Rotation()))
        _, roof = extrude(self.doc, top_sk, 2)
        bottom = face_where(roof, lambda c, f: abs(c.z - 10) < 1e-6)
        sk = sketch(self.doc, rect(0, 0, 10, 10))
        f = feature(self.doc, "Design::Extrude", Distance=1)
        f.Profile = (profiles(sk), ["Face1"])
        f.Extent = "To Object"
        f.ToObject = Design.stableRef(roof, bottom)
        body = new_body(f)
        self.doc.recompute()
        self.assertNoErrors()
        self.assertVolume(body, 1000)

    def test_up_to_slanted_face(self):
        target = slanted_plane(self.doc, 10)
        sk = sketch(self.doc, rect(0, 0, 10, 10))
        f = feature(self.doc, "Design::Extrude", Extent="To Object")
        f.Profile = (profiles(sk), ["Face1"])
        f.ToObject = (target, ["Face1"])
        body = new_body(f)
        self.doc.recompute()
        self.assertNoErrors()
        self.assertVolume(body, 1500)  # Integral von 10 + y über das Quadrat

    def test_target_behind_profile_flips_direction(self):
        target = flat_plane(self.doc, -8)
        sk = sketch(self.doc, rect(0, 0, 10, 10))
        f = feature(self.doc, "Design::Extrude", Extent="To Object")
        f.Profile = (profiles(sk), ["Face1"])
        f.ToObject = (target, ["Face1"])
        body = new_body(f)
        self.doc.recompute()
        self.assertNoErrors()
        self.assertVolume(body, 800)
        self.assertAlmostEqual(body.Shape.BoundBox.ZMin, -8, places=6)

    def test_missing_target_explains(self):
        sk = sketch(self.doc, rect(0, 0, 10, 10))
        f = feature(self.doc, "Design::Extrude", Extent="To Object")
        f.Profile = (profiles(sk), ["Face1"])
        new_body(f)
        self.doc.recompute()
        self.assertTrue(failed(f))
        self.assertIn("face or plane", f.getStatusString())

    def test_unreachable_target_explains(self):
        wall = self.doc.addObject("Part::Feature", "Wall")  # senkrecht, parallel zur Zugrichtung, weit weg
        wall.Shape = Part.makePlane(50, 50, V(100, -25, -25), V(1, 0, 0))
        sk = sketch(self.doc, rect(0, 0, 10, 10))
        f = feature(self.doc, "Design::Extrude", Extent="To Object")
        f.Profile = (profiles(sk), ["Face1"])
        f.ToObject = (wall, ["Face1"])
        new_body(f)
        self.doc.recompute()
        self.assertTrue(failed(f))

    def test_visibility_follows_extent(self):
        sk = sketch(self.doc, rect(0, 0, 10, 10))
        f, _ = extrude(self.doc, sk, 5)
        self.assertIn("Hidden", f.getPropertyStatus("ToObject"))
        self.assertNotIn("Hidden", f.getPropertyStatus("TaperAngle"))
        f.Extent = "To Object"
        self.assertNotIn("Hidden", f.getPropertyStatus("ToObject"))
        self.assertIn("Hidden", f.getPropertyStatus("TaperAngle"))
        self.assertIn("Hidden", f.getPropertyStatus("Thickness"))
        f.Thin = True
        self.assertNotIn("Hidden", f.getPropertyStatus("Thickness"))


class Taper(DesignTest):
    def test_positive_taper_narrows(self):
        sk = sketch(self.doc, rect(0, 0, 10, 10))
        f, body = extrude(self.doc, sk, 10, TaperAngle=10)
        self.assertNoErrors()
        top = 10 - 2 * 10 * math.tan(math.radians(10))
        self.assertVolume(body, frustum(10, top, 10))
        top_area = body.Shape.getElement(top_face(body)).Area
        self.assertAlmostEqual(top_area, top * top, delta=1e-3)

    def test_negative_taper_widens(self):
        sk = sketch(self.doc, rect(0, 0, 10, 10))
        f, body = extrude(self.doc, sk, 10, TaperAngle=-10)
        top = 10 + 2 * 10 * math.tan(math.radians(10))
        self.assertVolume(body, frustum(10, top, 10))

    def test_taper_on_circle_is_cone_frustum(self):
        sk = sketch(self.doc, circle(0, 0, 10))
        f, body = extrude(self.doc, sk, 10, TaperAngle=20)
        r = 10 - 10 * math.tan(math.radians(20))
        self.assertVolume(body, PI * 10 / 3 * (100 + 10 * r + r * r), rel=2e-3)

    def test_symmetric_taper_narrows_both_ways(self):
        sk = sketch(self.doc, rect(0, 0, 10, 10))
        f, body = extrude(self.doc, sk, 10, Extent="Symmetric", TaperAngle=5)
        end = 10 - 2 * 5 * math.tan(math.radians(5))
        self.assertVolume(body, 2 * frustum(10, end, 5))

    def test_taper_hole_widens(self):
        """Loch im Profil öffnet sich, wenn der Körper schmaler wird (Entformung)"""
        sk = sketch(self.doc, rect(0, 0, 20, 20) + circle(10, 10, 3))
        f, body = extrude(self.doc, sk, 5, TaperAngle=5)
        self.assertNoErrors()
        top = body.Shape.getElement(top_face(body))
        inner = [e for e in top.Edges if e.Curve.TypeId == "Part::GeomCircle"]
        self.assertTrue(inner and inner[0].Curve.Radius > 3)

    def test_too_steep_explains(self):
        sk = sketch(self.doc, rect(0, 0, 10, 10))
        f, _ = extrude(self.doc, sk, 10, TaperAngle=89.5)
        self.assertTrue(failed(f))
        self.assertIn("89", f.getStatusString())


class Thin(DesignTest):
    def tube(self, side, expected_outer, expected_inner):
        sk = sketch(self.doc, circle(0, 0, 10))
        f, body = extrude(self.doc, sk, 10, Thin=True, Thickness=2, ThinSide=side)
        self.assertNoErrors()
        self.assertVolume(body, PI * (expected_outer ** 2 - expected_inner ** 2) * 10)

    def test_inside(self):
        self.tube("Inside", 10, 8)

    def test_outside(self):
        self.tube("Outside", 12, 10)

    def test_center(self):
        self.tube("Center", 11, 9)

    def test_profile_with_hole_gets_wall_on_both_loops(self):
        sk = sketch(self.doc, rect(0, 0, 20, 20) + circle(10, 10, 5))
        faces = profiles(sk).Shape.Faces
        ring = "Face%d" % (1 + max(range(len(faces)), key=lambda i: faces[i].Area))  # nicht die Kreisscheibe
        f, body = extrude(self.doc, sk, 10, faces=[ring], Thin=True, Thickness=1, ThinSide="Inside")
        self.assertNoErrors()
        outer_wall = 400 - 18 * 18
        hole_wall = PI * (6 ** 2 - 5 ** 2)
        self.assertVolume(body, (outer_wall + hole_wall) * 10, rel=5e-3)

    def test_thin_with_taper(self):
        sk = sketch(self.doc, circle(0, 0, 10))
        f, body = extrude(self.doc, sk, 10, Thin=True, Thickness=2, TaperAngle=5)
        self.assertNoErrors()
        self.assertTrue(body.Shape.isValid())
        self.assertLess(body.Shape.Volume, PI * (100 - 64) * 10)

    def test_zero_thickness_explains(self):
        sk = sketch(self.doc, circle(0, 0, 10))
        f, _ = extrude(self.doc, sk, 10, Thin=True, Thickness=0)
        self.assertTrue(failed(f))


class Persistence(DesignTest):
    def test_new_options_survive_save(self):
        sk = sketch(self.doc, circle(0, 0, 10))
        f, body = extrude(self.doc, sk, 10, Thin=True, Thickness=2, TaperAngle=5, Extent="Symmetric")
        before, f_name, body_name = body.Shape.Volume, f.Name, body.Name
        doc = save_and_reload(self.doc)
        f = doc.getObject(f_name)
        self.assertTrue(f.Thin)
        self.assertEqual(f.Extent, "Symmetric")
        self.assertIn("Hidden", f.getPropertyStatus("ToObject"))
        f.touch()
        doc.recompute()
        self.assertAlmostEqual(doc.getObject(body_name).Shape.Volume, before, delta=before * 1e-6)
