# SPDX-License-Identifier: LGPL-2.1-or-later
"""Wandstärke ohne geöffnete Fläche: ein geschlossener Hohlkörper (innen) bzw. eine geschlossene Hülle (außen)"""
from design import *


class ClosedShell(DesignTest):
    def test_inside_makes_a_closed_cavity(self):
        _, b = box(self.doc, 40, 30, 10)
        f = dress(self.doc, "Design::Shell", b, [], Size=2)
        self.doc.recompute()
        self.assertNotIn("Invalid", f.State, f.getStatusString())
        self.assertAlmostEqual(b.Shape.Volume, 40 * 30 * 10 - 36 * 26 * 6, places=3)
        self.assertEqual(len(b.Shape.Solids), 1)
        self.assertEqual(len(b.Shape.Shells), 2)  # außen und die Wand des Hohlraums

    def test_outside_makes_a_hull(self):
        _, b = box(self.doc, 40, 30, 10)
        f = dress(self.doc, "Design::Shell", b, [], Size=2, Outside=True)
        self.doc.recompute()
        self.assertNotIn("Invalid", f.State, f.getStatusString())
        self.assertAlmostEqual(b.Shape.BoundBox.XLength, 44, places=3)
        self.assertGreater(b.Shape.Volume, 0)
        self.assertLess(b.Shape.Volume, 44 * 34 * 14 - 40 * 30 * 10 + 1)


if __name__ == "__main__":
    unittest.main()
