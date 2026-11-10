# SPDX-License-Identifier: LGPL-2.1-or-later
"""10.8 Idee 1: Rotstift. Eine gelesene Zeile an einer Stelle des Modells wird eine Korrektur am nächsten passenden
Element (Kante, Fläche, Bohrung, Feature); gleich nahe Ziele werden nicht geraten; Ausführen erzeugt normale Features"""
from design import *
import Sketcher

DOWN = V(0, 0, -1)  # von oben geschaut


def read(doc, text, at, view=DOWN):
    return Design.readCorrection(doc, text, at, view)


def apply(doc, text, at, view=DOWN, element=None):
    args = (doc, text, at, view) + ((element,) if element else ())
    return Design.applyCorrection(*args)


class Target(DesignTest):
    def setUp(self):
        super().setUp()
        self.f, self.b = box(self.doc, 20, 20, 10)

    def test_r2_beside_an_edge_rounds_the_top_one(self):
        c = read(self.doc, "R2", V(10, -2, 30))
        self.assertEqual(c["kind"], "Fillet")
        self.assertEqual(c["alternatives"], [])
        edge = self.b.Shape.getElement(c["element"])
        self.assertAlmostEqual(edge.BoundBox.ZMin, 10)  # oben (näher am Auge), nicht die untere Kante
        self.assertAlmostEqual(edge.BoundBox.YMax, 0)
        f = apply(self.doc, "R2", V(10, -2, 30))
        self.assertEqual(f.TypeId, "Design::Fillet")
        self.assertNoErrors()
        self.assertVolume(self.b, 4000 - (4 - math.pi) * 20)
        self.assertEqual(c["text"], "Fillet R2 on 1 edge")

    def test_between_edges_is_ambiguous(self):
        c = read(self.doc, "R2", V(10, 10, 30))
        self.assertGreaterEqual(len(c["alternatives"]), 2)  # vier Kanten gleich weit: fragen statt raten
        f = apply(self.doc, "R2", V(10, 10, 30), DOWN, c["alternatives"][1])
        self.assertEqual(list(f.Edges), [c["alternatives"][1]])

    def test_chamfer(self):
        apply(self.doc, "2x45", V(-2, 10, 30))
        self.assertNoErrors()
        self.assertVolume(self.b, 4000 - 2 * 20)

    def test_pull_the_face_under_the_ink(self):
        c = read(self.doc, "+5", V(10, 10, 30))
        self.assertEqual(self.b.Shape.getElement(c["element"]).BoundBox.ZMin, 10)  # Oberseite, nicht die Unterseite
        apply(self.doc, "+5", V(10, 10, 30))
        self.assertVolume(self.b, 20 * 20 * 15)

    def test_from_the_side(self):
        apply(self.doc, "-5", V(30, 10, 5), V(-1, 0, 0))  # rechte Seite eindrücken
        self.assertVolume(self.b, 15 * 20 * 10)

    def test_m5_on_a_flat_face_is_a_tapped_hole_there(self):
        c = read(self.doc, "M5", V(5, 5, 30))
        self.assertEqual(c["text"], "Tapped hole M5")
        h = apply(self.doc, "M5", V(5, 5, 30))
        self.assertEqual(h.TypeId, "Design::Hole")
        self.assertEqual((h.Size, h.Kind), ("M5x0.8", "Tapped hole"))
        self.assertNoErrors()
        self.assertFalse(self.b.Shape.isInside(V(5, 5, 5), 1e-6, True))
        self.assertTrue(self.b.Shape.isInside(V(5, 7.5, 5), 1e-6, True))  # Kernloch Ø4,2

    def test_diameter_on_a_flat_face_is_a_hole(self):
        apply(self.doc, "Ø6", V(10, 10, 30))
        self.assertVolume(self.b, 4000 - math.pi * 9 * 10)

    def test_number_sets_the_dimension_of_the_face(self):
        apply(self.doc, "12", V(10, 10, 30))
        self.assertAlmostEqual(self.f.Distance.Value, 12)
        self.assertVolume(self.b, 20 * 20 * 12)

    def test_nonsense_is_not_a_correction(self):
        self.assertEqual(read(self.doc, "Hallo", V(10, 10, 30))["error"], "Not a correction")
        with self.assertRaises(ValueError):
            apply(self.doc, "Hallo", V(10, 10, 30))


class Round(DesignTest):
    def bored(self):
        _, b = box(self.doc, 30, 30, 10, at=(-15, -15))
        sk = sketch(self.doc, circle(0, 0, 5))
        sk.addConstraint(Sketcher.Constraint("Diameter", 0, 10))
        self.doc.recompute()
        extrude(self.doc, sk, 10, op="Cut", bodies=[b])
        return b

    def test_diameter_over_a_hole_sets_its_dimension(self):
        b = self.bored()
        c = read(self.doc, "Ø12", V(0, 0, 30))
        self.assertEqual(c["text"], "Diameter 12 mm")
        apply(self.doc, "Ø12", V(0, 0, 30))
        self.assertVolume(b, 900 * 10 - math.pi * 36 * 10)

    def test_h7_on_a_hole_is_a_fit(self):
        b = self.bored()
        f = apply(self.doc, "H7", V(0, 0, 30))
        self.assertEqual((f.TypeId, f.Fit), ("Design::Fitting", "H7/g6"))
        self.assertNoErrors()

    def test_m8_on_a_pin_is_a_thread(self):
        sk = sketch(self.doc, circle(0, 0, 4))
        _, pin = extrude(self.doc, sk, 20)
        t = apply(self.doc, "M8", V(6, 0, 10), V(0, -1, 0))  # von vorn, neben dem Bolzen
        self.assertEqual((t.TypeId, t.ThreadSize), ("Design::Thread", "M8x1.25"))
        self.assertNoErrors()


class Pattern(DesignTest):
    def test_3x_beside_a_boss_repeats_it_that_way(self):
        _, b = box(self.doc, 40, 20, 5)
        sk = sketch(self.doc, circle(5, 10, 2), App.Placement(V(0, 0, 5), App.Rotation()))
        extrude(self.doc, sk, 3, op="Join", bodies=[b])
        p = apply(self.doc, "3x", V(9, 10, 30))  # rechts neben dem Zapfen geschrieben
        self.assertEqual((p.TypeId, p.Count1, p.Direction1), ("Design::Pattern", 3, "X"))
        self.assertNoErrors()
        self.assertVolume(b, 40 * 20 * 5 + 3 * math.pi * 4 * 3)
