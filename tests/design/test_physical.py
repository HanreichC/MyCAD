# SPDX-License-Identifier: LGPL-2.1-or-later
"""L9 Physisches Material: Masse aus Dichte, Werkstoff aus der Appearance, eigene Wahl bleibt"""
from design import *


def uuid(name):
    return dict(Design.physicalMaterials())[name]


class Mass(DesignTest):
    def test_aluminum_cube(self):
        _, b = box(self.doc, 100, 100, 100)
        self.assertTrue(Design.setPhysicalMaterial(b, uuid("Aluminum")))
        self.assertAlmostEqual(Design.mass(b), 2.70, delta=0.027)

    def test_pla_part(self):
        _, b = box(self.doc, 50, 20, 10)
        Design.setPhysicalMaterial(b, uuid("PLA"))
        self.assertAlmostEqual(Design.mass(b), 10000 * 1.24e-6, delta=1e-4)

    def test_every_listed_material_has_a_density(self):
        _, b = box(self.doc, 10, 10, 10)
        for name, u in Design.physicalMaterials():
            self.assertTrue(Design.setPhysicalMaterial(b, u), name)
            self.assertGreater(Design.mass(b), 0, name)

    def test_unknown_uuid_is_rejected(self):
        _, b = box(self.doc, 10, 10, 10)
        self.assertFalse(Design.setPhysicalMaterial(b, "00000000-0000-0000-0000-000000000000"))

    def test_material_survives_save(self):
        _, b = box(self.doc, 100, 100, 100)
        Design.setPhysicalMaterial(b, uuid("Steel"))
        name = b.Name
        doc = save_and_reload(self.doc)
        self.assertAlmostEqual(Design.mass(doc.getObject(name)), 7.9, delta=0.2)


class FromAppearance(DesignTest):
    def test_mapping(self):
        cases = {("Anodized Blue", "Anodized"): "Aluminum", ("Brushed Aluminum", "Metal"): "Aluminum",
                 ("Stainless Steel", "Metal"): "Steel", ("Cast Iron", "Metal"): "Cast Iron",
                 ("Walnut, Oiled", "Wood"): "Wood", ("PLA Orange", "3D Print"): "PLA", ("PETG Clear", "3D Print"): "PETG",
                 ("Nylon SLS", "3D Print"): "Nylon", ("Clear Acrylic", "Glass"): "Acrylic", ("Clear Glass", "Glass"): "Glass",
                 ("Plastic Matte Black", "Plastic"): "ABS", ("Concrete", "Stone"): "Concrete"}
        for (appearance, group), name in cases.items():
            self.assertEqual(Design.physicalMaterialFor(appearance, group), uuid(name), appearance)

    def test_paint_says_nothing_about_the_material(self):
        for appearance, group in (("Lacquer Red", "Coatings"), ("Space Gray", "Colors"), ("Rubber Black", "Rubber"),
                                  ("Brass", "Metal")):
            self.assertEqual(Design.physicalMaterialFor(appearance, group), "", appearance)
