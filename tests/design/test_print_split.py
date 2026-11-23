# SPDX-License-Identifier: LGPL-2.1-or-later
"""12.8 Zu groß fürs Bett: das Teil finden, in der Mitte seiner zu langen Richtung teilen, mit Stiften (Zapfen auf der
einen Seite, Bohrung mit Spiel auf der anderen)"""
import math

from design import *


def split(doc, body, placement, **props):
    cut = doc.addObject("PartDesign::Plane", "Cut")
    Design.root(doc).addObject(cut)
    cut.Placement = placement
    doc.recompute()
    s = feature(doc, "Design::Split", Design.componentOf(body), Tool=(cut, [""]), **props)
    Design.attachToBodies(s, [body])
    doc.recompute()
    pieces = [body]
    for _ in range(1, s.Pieces):
        p = doc.addObject("Design::Body", "Body")
        doc.getObject("Bodies").addObject(p)
        p.Tip = s
        pieces.append(p)
    s.Bodies = pieces
    doc.recompute()
    return s, pieces


class PrintSplit(DesignTest):
    def setUp(self):
        super().setUp()
        self.grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")
        self.keys = ("BedWidth", "BedDepth", "BedHeight", "PrintFitNormal")
        self.old = [self.grp.GetFloat(k, d) for k, d in zip(self.keys, (220, 220, 250, 0.2))]
        for k, v in zip(self.keys, (220, 220, 250, 0.2)):
            self.grp.SetFloat(k, v)

    def tearDown(self):
        for k, v in zip(self.keys, self.old):
            self.grp.SetFloat(k, v)
        super().tearDown()

    def test_too_long_bar_is_halved_with_two_pins(self):
        _, b = box(self.doc, 300, 20, 10)
        self.assertEqual(Design.tooBigToPrint(self.doc), b)
        at = Design.printSplitPlane(b)
        self.assertAlmostEqual(at.Base.x, 150, places=6)
        self.assertAlmostEqual(abs(at.Rotation.multVec(V(0, 0, 1)).x), 1, places=6)
        s, pieces = split(self.doc, b, at, Connector="Pins")
        self.assertEqual(s.PinCount, 2)  # 20 mm breit: zwei Stifte, verdrehsicher
        self.assertAlmostEqual(s.Clearance.Value, 0.2)
        self.assertEqual(s.Warning, "")
        for p in pieces:
            self.assertTrue(p.Shape.isValid() and len(p.Shape.Solids) == 1, p.Label)
        # Platz 5 mm (halbe Höhe) -> Stift r = 5/3, 5 r lang; Bohrung r + 0,2, 0,2 tiefer
        r, c = 5 / 3, 0.2
        pegs, holes = 2 * math.pi * r * r * 5 * r, 2 * math.pi * (r + c) ** 2 * (5 * r + c)
        big, small = sorted((p.Shape.Volume for p in pieces), reverse=True)
        self.assertAlmostEqual(big, 30000 + pegs, delta=0.01)
        self.assertAlmostEqual(small, 30000 - holes, delta=0.01)
        self.assertLess(pieces[0].Shape.common(pieces[1].Shape).Volume, 1e-6)  # Zapfen stecken mit Spiel
        self.assertIsNone(Design.tooBigToPrint(self.doc))  # jede Hälfte passt jetzt

    def test_without_connector_no_pins(self):
        _, b = box(self.doc, 300, 20, 10)
        s, pieces = split(self.doc, b, Design.printSplitPlane(b))
        self.assertEqual(s.PinCount, 0)
        self.assertEqual([round(p.Shape.Volume, 6) for p in pieces], [30000, 30000])
        self.assertIn("Hidden", s.getPropertyStatus("Clearance"))

    def test_too_narrow_for_pins_warns(self):
        _, b = box(self.doc, 300, 3, 3)
        s, pieces = split(self.doc, b, Design.printSplitPlane(b), Connector="Pins")
        self.assertEqual(s.PinCount, 0)
        self.assertIn("too narrow", s.Warning)
        self.assertEqual(len(pieces), 2)  # geteilt wird trotzdem

    def test_pin_gets_shorter_in_thin_material(self):
        """Schnitt 5 mm vor dem Ende: der Stift (5 r = 8,3 mm) passt nicht, 0,75 · 0,75 davon (4,7 mm) schon"""
        _, b = box(self.doc, 10, 100, 10)
        s, pieces = split(self.doc, b, App.Placement(V(0, 95, 0), App.Rotation(V(1, 0, 0), -90)), Connector="Pins")
        self.assertEqual(s.PinCount, 1)
        r, c = 5 / 3, 0.2
        length = 5 * r * 0.75 * 0.75
        thin = min(p.Shape.Volume for p in pieces)
        self.assertAlmostEqual(thin, 500 - math.pi * (r + c) ** 2 * (length + c), delta=0.01)

    def test_three_bed_lengths_cut_off_a_third(self):
        """500 mm bei 220 mm Bett: drei gleiche Stücke nötig, der erste Schnitt trennt ein Drittel ab; der Rest
        (333 mm) wird mit dem nächsten Schnitt halbiert"""
        _, b = box(self.doc, 500, 20, 10)
        at = Design.printSplitPlane(b)
        self.assertAlmostEqual(at.Base.x, 500 / 3, places=6)
        s, pieces = split(self.doc, b, at, Connector="Pins")
        rest = [p for p in pieces if not Design.fitsPrintBed(Design.printSize(p))]
        self.assertEqual(len(rest), 1)
        self.assertAlmostEqual(Design.printSplitPlane(rest[0]).Base.x, 500 / 3 + (500 * 2 / 3) / 2, places=3)

    def test_too_tall_is_cut_across_the_height(self):
        _, b = box(self.doc, 40, 40, 300)
        at = Design.printSplitPlane(b)
        self.assertAlmostEqual(at.Base.z, 150, places=6)
        self.assertAlmostEqual(abs(at.Rotation.multVec(V(0, 0, 1)).z), 1, places=6)
        s, pieces = split(self.doc, b, at, Connector="Pins")
        self.assertEqual(s.PinCount, 2)  # 40 x 40: Platz für zwei
        self.assertTrue(all(Design.fitsPrintBed(Design.printSize(p)) for p in pieces))


if __name__ == "__main__":
    unittest.main()
