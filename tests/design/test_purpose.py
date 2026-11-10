# SPDX-License-Identifier: LGPL-2.1-or-later
"""10.5 Idee 4: Werkzeuge für den Zweck. Passung (ISO 286 und 3D-Druck), Schraube hier (Durchgang mit Senkung oben;
Kernloch, Einschmelzmutter oder Mutterfalle unten; Länge nach Norm), Gewinde zum Drucken"""
from design import *

AXIS = Part.LineSegment(V(0, 0, -100), V(0, 0, 100)).toShape()


def curved(body):
    return [(i, f) for i, f in enumerate(body.Shape.Faces, 1) if f.Surface.TypeId != "Part::GeomPlane"]


def radii(body):
    """Abstände der gekrümmten Flächen von der Z-Achse, gerundet (Bohrungen und Wellen um die Achse)"""
    return sorted({round(AXIS.distToShape(f)[0], 4) for _, f in curved(body)})


def shaft(doc, r, h, z=0, component=None):
    sk = sketch(doc, circle(0, 0, r), App.Placement(V(0, 0, z), App.Rotation()), component)
    return extrude(doc, sk, h)[1]


def bored_block(doc, r, h):
    _, b = box(doc, 40, 40, h, at=(-20, -20))
    extrude(doc, sketch(doc, circle(0, 0, r)), h, op="Cut", bodies=[b])
    return b


def round_face(body):
    return "Face%d" % curved(body)[0][0]


def fitting(doc, picks, **props):
    """picks: [(body, "FaceN"), …] aus einem oder zwei Bodies"""
    bodies = []
    for b, _ in picks:
        if b not in bodies:
            bodies.append(b)
    f = feature(doc, "Design::Fitting", Design.componentOf(bodies[0]), Edges=[n for _, n in picks],
                ElementBodies=[bodies.index(b) for b, _ in picks])
    for k, v in props.items():
        setattr(f, k, v)
    Design.attachToBodies(f, bodies)
    doc.recompute()
    return f


class Fit(DesignTest):
    def test_iso_h7_g6_puts_both_in_their_field(self):
        hole = bored_block(self.doc, 10, 10)
        pin = shaft(self.doc, 10, 30, -10)
        f = fitting(self.doc, [(hole, round_face(hole)), (pin, round_face(pin))], Fit="H7/g6")
        self.assertNoErrors()
        d_hole, d_pin = 2 * radii(hole)[0], 2 * radii(pin)[0]
        self.assertTrue(20.000 <= d_hole <= 20.021, d_hole)  # H7: 0 … +21 µm
        self.assertTrue(19.980 <= d_pin <= 19.993, d_pin)    # g6: −20 … −7 µm
        self.assertAlmostEqual(d_hole, 20.0105, places=3)    # Mittelmaß
        self.assertAlmostEqual(d_pin, 19.9865, places=3)
        self.assertEqual(f.Play, "+7 … +41 µm")

    def test_interference_fit_shows_negative_play(self):
        hole = bored_block(self.doc, 10, 10)
        f = fitting(self.doc, [(hole, round_face(hole))], Fit="H7/p6")
        self.assertEqual(f.Play, "-35 … -1 µm")

    def test_print_fit_grows_the_hole_by_twice_the_play(self):
        hole = bored_block(self.doc, 5, 10)
        pin = shaft(self.doc, 5, 30, -10)
        f = fitting(self.doc, [(hole, round_face(hole)), (pin, round_face(pin))], Fit="3D print normal")
        self.assertNoErrors()
        self.assertAlmostEqual(f.Clearance.Value, 0.2)
        self.assertAlmostEqual(radii(hole)[0], 5.2, places=4)
        self.assertAlmostEqual(radii(pin)[0], 5.0, places=4)  # die Welle bleibt
        self.assertEqual(f.Play, "+0.40 mm")
        self.assertVolume(hole, 40 * 40 * 10 - math.pi * 5.2 ** 2 * 10)

    def test_print_fit_on_a_shaft_alone_shrinks_it(self):
        pin = shaft(self.doc, 5, 10)
        fitting(self.doc, [(pin, round_face(pin))], Fit="3D print loose")
        self.assertAlmostEqual(radii(pin)[0], 4.7, places=4)

    def test_print_fit_on_a_flat_face(self):
        _, b = box(self.doc, 10, 10, 10)
        fitting(self.doc, [(b, top_face(b))], Fit="3D print tight")
        self.assertAlmostEqual(b.Shape.BoundBox.ZMax, 9.9, places=6)

    def test_iso_fit_needs_round_faces(self):
        _, b = box(self.doc, 10, 10, 10)
        f = fitting(self.doc, [(b, top_face(b))], Fit="H7/h6")
        self.assertTrue(failed(f))
        self.assertIn("round faces", f.getStatusString())

    def test_works_across_components(self):
        hole = bored_block(self.doc, 10, 10)
        comp = Design.newComponent(Design.root(self.doc))
        comp.Placement = App.Placement(V(0, 0, 50), App.Rotation())
        pin = shaft(self.doc, 10, 30, -60, comp)
        fitting(self.doc, [(hole, round_face(hole)), (pin, round_face(pin))], Fit="H7/h6")
        self.assertNoErrors()
        self.assertAlmostEqual(2 * radii(pin)[0], 19.9935, places=3)  # h6: −13 … 0
        self.assertAlmostEqual(2 * radii(hole)[0], 20.0105, places=3)

    def test_survives_save(self):
        hole = bored_block(self.doc, 10, 10)
        fitting(self.doc, [(hole, round_face(hole))], Fit="H7/g6")
        doc = save_and_reload(self.doc)
        b = [o for o in doc.Objects if o.TypeId == "Design::Body"][0]
        doc.recompute()
        self.assertAlmostEqual(2 * radii(b)[0], 20.0105, places=3)


def plates(doc, bottom=10, top=5):
    """unten 20 x 20 x bottom ab z = 0, oben 20 x 20 x top darauf"""
    _, low = box(doc, 20, 20, bottom, at=(-10, -10))
    sk = sketch(doc, rect(-10, -10, 10, 10), App.Placement(V(0, 0, bottom), App.Rotation()))
    _, up = extrude(doc, sk, top)
    return up, low


def m4(up, at=V(0, 0, 15)):
    f = Design.fastenerAt(up, at, V(0, 0, -1))
    f.Size = "M4"
    up.Document.recompute()
    return f


def solid_at(body, x, y, z):
    return body.Shape.isInside(V(x, y, z), 1e-6, True)


class Fastener(DesignTest):
    def test_m4_socket_head_into_a_tapped_hole(self):
        up, low = plates(self.doc)
        f = m4(up)
        self.assertNoErrors()
        self.assertEqual(list(f.Bodies), [up, low])
        self.assertEqual(radii(up), [2.25, 4.0])  # ISO 273 mittel 4,5; Senkung ISO 4762 Ø8
        self.assertEqual(radii(low), [1.65])      # Kernloch M4: 3,3
        # Senkung 4,4 tief, darunter 0,6 Klemmlänge; 1,5 × d Gewinde → 6,6 → Normlänge 8
        self.assertAlmostEqual(f.Length.Value, 8)
        self.assertFalse(solid_at(up, 3.5, 0, 15 - 4.3))   # in der Senkung
        self.assertTrue(solid_at(up, 3.5, 0, 15 - 4.5))    # darunter wieder Material
        tip = 15 - 4.4 - 8
        self.assertFalse(solid_at(low, 0, 0, tip - 0.9))   # Kernloch reicht 1 mm über die Spitze
        self.assertTrue(solid_at(low, 0, 0, tip - 1.1))

    def test_countersunk_head_sits_flush(self):
        up, low = plates(self.doc)
        f = m4(up)
        f.Screw = "ISO 10642"
        self.doc.recompute()
        self.assertNoErrors()
        self.assertFalse(solid_at(up, 4.4, 0, 14.99))  # Senkung Ø9 an der Oberfläche
        self.assertTrue(solid_at(up, 4.4, 0, 14.0))     # Kegel: tiefer wird es enger
        # Senkkopf zählt mit: 5 mm oben + 6 mm Gewinde → 12
        self.assertAlmostEqual(f.Length.Value, 12)

    def test_new_screw_is_m3_socket_head(self):
        up, low = plates(self.doc)
        f = Design.fastenerAt(up, V(0, 0, 15), V(0, 0, -1))
        self.assertEqual((f.Screw, f.Size, f.Bottom), ("ISO 4762", "M3", "Tapped hole"))
        self.assertEqual(radii(low), [1.25])  # Kernloch M3: 2,5

    def test_heat_set_insert(self):
        up, low = plates(self.doc)
        f = Design.fastenerAt(up, V(0, 0, 15), V(0, 0, -1))
        f.Size = "M3"
        f.Bottom = "Heat-set insert"
        self.doc.recompute()
        self.assertNoErrors()
        self.assertEqual(radii(low), [2.0])            # Einschmelzmutter M3: Ø4
        self.assertFalse(solid_at(low, 1.9, 0, 10 - 5.6))  # mindestens so tief wie die Mutter lang ist

    def test_nut_trap_at_the_bottom(self):
        up, low = plates(self.doc)
        f = Design.fastenerAt(up, V(0, 0, 15), V(0, 0, -1))
        f.Size = "M3"
        f.Bottom = "Nut trap"
        self.doc.recompute()
        self.assertNoErrors()
        self.assertFalse(solid_at(low, 2.8, 0, 1.0))   # Sechskant (Schlüsselweite 5,5 + Spiel) an der Unterseite
        self.assertTrue(solid_at(low, 2.8, 0, 5.0))    # darüber nur der Durchgang Ø3,4
        self.assertFalse(solid_at(low, 1.6, 0, 5.0))
        self.assertTrue(f.Length.Value >= 15 - 3.4 - 0.5)

    def test_across_components(self):
        _, low = box(self.doc, 20, 20, 10, at=(-10, -10))
        comp = Design.newComponent(Design.root(self.doc))
        comp.Placement = App.Placement(V(0, 0, 10), App.Rotation())
        sk = sketch(self.doc, rect(-10, -10, 10, 10), None, comp)
        _, up = extrude(self.doc, sk, 5)
        f = m4(up)
        self.assertNoErrors()
        self.assertEqual(list(f.Bodies), [up, low])
        self.assertEqual(radii(low), [1.65])
        self.assertEqual(radii(up), [2.25, 4.0])  # die obere Form liegt lokal bei z = 0 … 5, Achse dieselbe

    def test_nothing_below(self):
        _, b = box(self.doc, 20, 20, 10, at=(-10, -10))
        with self.assertRaises(ValueError):
            Design.fastenerAt(b, V(0, 0, 10), V(0, 0, -1))

    def test_too_short_by_hand_offers_a_longer_screw(self):
        up, low = plates(self.doc)
        f = Design.fastenerAt(up, V(0, 0, 15), V(0, 0, -1))
        f.AutoLength = False
        f.Length = 3
        self.doc.recompute()
        self.assertTrue(failed(f))
        self.assertTrue(any("\tLength\t" in fix for fix in f.Fixes), list(f.Fixes))


def cylinder(doc, r, h):
    return shaft(doc, r, h)


class PrintThread(DesignTest):
    def thread(self, r, **props):
        b = cylinder(self.doc, r, 20)
        return dress(self.doc, "Design::Thread", b, [round_face(b)], **props), b

    def test_print_preset_adds_clearance(self):
        _, plain = self.thread(4)
        minor_plain = radii(plain)[0]
        f, printed = self.thread(4, ForPrinting=True)
        self.assertNoErrors()
        self.assertEqual(f.Warning, "")  # M8: 1,25 mm Steigung druckt gut
        self.assertAlmostEqual(minor_plain - radii(printed)[0], 0.15, places=3)

    def test_fine_pitch_warns_and_still_works(self):
        f, _ = self.thread(1.5, ForPrinting=True)  # M3, 0,5 mm Steigung
        self.assertNoErrors()
        self.assertIn("pitch below 1 mm", f.Warning)
        f.Warning = ""  # "Sieht richtig aus"
        self.doc.recompute()
        self.assertEqual(f.Warning, "")  # kommt nicht wieder
