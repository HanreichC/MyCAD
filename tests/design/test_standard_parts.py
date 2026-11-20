# SPDX-License-Identifier: LGPL-2.1-or-later
"""12.7 Normteile als echte Körper: Schrauben (ISO 4762, 10642, 7380), Mutter, Scheibe, Einschmelzmutter, Lager,
Magnete, Alu-Profil; Maße aus den Normen, Bezeichnung für die Stückliste"""
import math

from design import *


def part(doc, kind, **props):
    f = feature(doc, "Design::Primitive", Type=kind, **props)
    b = new_body(f)
    doc.recompute()
    return f, b


class StandardParts(DesignTest):
    def test_every_part_is_a_valid_solid_standing_on_the_plane(self):
        kinds = ["Socket Head Screw", "Countersunk Screw", "Button Head Screw", "Hex Nut", "Washer", "Heat-Set Insert",
                 "Ball Bearing", "Disc Magnet", "Block Magnet", "Aluminum Profile"]
        for kind in kinds:
            f, b = part(self.doc, kind)
            self.assertNotIn("Invalid", f.State, kind)
            self.assertTrue(b.Shape.isValid() and b.Shape.Volume > 0, kind)
            self.assertAlmostEqual(b.Shape.BoundBox.ZMin, 0, places=6, msg=kind)

    def test_socket_head_m3x12(self):
        f, b = part(self.doc, "Socket Head Screw", Size="M3", Length=12)
        bb = b.Shape.BoundBox
        self.assertAlmostEqual(bb.ZMax, 12 + 3, places=6)  # Länge unter dem Kopf + Kopfhöhe k = 3
        self.assertAlmostEqual(bb.XLength, 5.5, places=6)  # Kopf dk = 5,5
        self.assertEqual(Design.partName(f), "ISO 4762 M3 × 12")

    def test_countersunk_length_is_overall(self):
        f, b = part(self.doc, "Countersunk Screw", Size="M4", Length=16)
        self.assertAlmostEqual(b.Shape.BoundBox.ZMax, 16, places=6)  # Senkschraube: Nennlänge über alles
        self.assertAlmostEqual(b.Shape.BoundBox.XLength, 8, places=6)

    def test_nut_washer_insert_have_the_thread_hole(self):
        f, nut = part(self.doc, "Hex Nut", Size="M5")
        self.assertAlmostEqual(nut.Shape.BoundBox.ZLength, 4.7, places=6)  # ISO 4032 m
        holes = [round(x.Surface.Radius, 3) for x in nut.Shape.Faces if x.Surface.TypeId == "Part::GeomCylinder"]
        self.assertEqual(holes, [2.5])
        _, washer = part(self.doc, "Washer", Size="M5")
        self.assertAlmostEqual(washer.Shape.Volume, math.pi * (5 ** 2 - 2.65 ** 2) * 1, places=3)  # 10 / 5,3 / 1
        f, insert = part(self.doc, "Heat-Set Insert", Size="M3")
        self.assertAlmostEqual(insert.Shape.BoundBox.ZLength, 5.7, places=6)
        self.assertEqual(Design.partName(f), "Heat-set insert M3")

    def test_bearing_608(self):
        f, b = part(self.doc, "Ball Bearing", Bearing="608")
        bb = b.Shape.BoundBox
        self.assertAlmostEqual(bb.XLength, 22, places=6)
        self.assertAlmostEqual(bb.ZLength, 7, places=6)
        bore = min(x.Surface.Radius for x in b.Shape.Faces if x.Surface.TypeId == "Part::GeomCylinder")
        self.assertAlmostEqual(bore, 4, places=6)
        self.assertEqual(Design.partName(f), "Ball bearing 608")

    def test_profile_2040_has_six_slots_and_two_bores(self):
        f, b = part(self.doc, "Aluminum Profile", Profile="2040", Length=100)
        bb = b.Shape.BoundBox
        self.assertEqual((round(bb.XLength, 6), round(bb.YLength, 6), round(bb.ZLength, 6)), (20, 40, 100))
        bores = [x for x in b.Shape.Faces if x.Surface.TypeId == "Part::GeomCylinder"]
        self.assertEqual(len(bores), 2)
        full = 20 * 40 * 100
        self.assertLess(b.Shape.Volume, full - 6 * 6.2 * 6 * 100 * 0.99)  # sechs Nuten herausgenommen
        self.assertEqual(Design.partName(f), "Aluminum profile 2040 × 100")

    def test_magnets_and_basic_shapes_name(self):
        f, _ = part(self.doc, "Disc Magnet", Radius=5, Height=3)
        self.assertEqual(Design.partName(f), "Disc magnet 10 × 3")
        f, _ = part(self.doc, "Box")
        self.assertEqual(Design.partName(f), "")  # Grundkörper gehören nicht in die Stückliste

    def test_spur_gear_m1_z20(self):
        """Kopfkreis 22, Fußkreis 17,5; je Zahn ein echter Kreisbogen am Kopf und am Fuß, glatte Flanken"""
        f, b = part(self.doc, "Spur Gear", Module=1, Teeth=20, Height=6, Bore=5)
        s = b.Shape
        self.assertTrue(s.isValid())
        radii = [round(x.Surface.Radius, 4) for x in s.Faces if x.Surface.TypeId == "Part::GeomCylinder"]
        self.assertEqual(radii.count(11.0), 20)   # Kopf
        self.assertEqual(radii.count(8.75), 20)   # Fuß
        self.assertEqual(radii.count(2.5), 1)     # Bohrung
        self.assertAlmostEqual(s.BoundBox.ZLength, 6, places=6)
        self.assertEqual(len(s.Faces), 20 * 6 + 3)  # je Zahn 2 Flanken, Kopf, Fuß, 2 radial; oben, unten, Bohrung
        self.assertEqual(Design.partName(f), "")  # gedruckt, nicht gekauft: nicht in der Stückliste

    def test_two_gears_mesh_without_overlap(self):
        """Achsabstand m·(z1+z2)/2; das zweite Rad um einen halben Zahn gedreht, damit Zahn in Lücke greift"""
        _, a = part(self.doc, "Spur Gear", Module=2, Teeth=20, Height=5, Bore=0)
        _, b = part(self.doc, "Spur Gear", Module=2, Teeth=31, Height=5, Bore=0, PositionX=2 * (20 + 31) / 2,
                    Rotation=180 + 180 / 31)
        overlap = a.Shape.common(b.Shape).Volume
        self.assertLess(overlap, 0.05, "the gears cut into each other: %.3f mm³" % overlap)
        closer = b.Shape.copy()
        closer.translate(V(-0.3, 0, 0))  # 0,3 mm näher: jetzt müssen sie sich berühren und überlappen
        self.assertGreater(a.Shape.common(closer).Volume, 0.5)

    def test_too_few_teeth_say_so(self):
        f = feature(self.doc, "Design::Primitive", Type="Spur Gear", Module=1, Teeth=6, PressureAngle=40)
        new_body(f)
        self.doc.recompute()
        self.assertIn("Invalid", f.State)

    def test_switching_type_shows_only_its_sizes(self):
        f, _ = part(self.doc, "Ball Bearing")
        self.assertIn("Hidden", f.getPropertyStatus("Size"))
        self.assertNotIn("Hidden", f.getPropertyStatus("Bearing"))
        f.Type = "Hex Nut"
        self.assertNotIn("Hidden", f.getPropertyStatus("Size"))
        self.assertIn("Hidden", f.getPropertyStatus("Bearing"))
        self.assertIn("Hidden", f.getPropertyStatus("Length"))


if __name__ == "__main__":
    unittest.main()
