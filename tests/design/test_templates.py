# SPDX-License-Identifier: LGPL-2.1-or-later
"""12.11 Vorlagen: jede baut gültige Körper ohne Fehler; die Maße stehen als Parameter in der Notiz, eine geänderte Zeile
ändert das Design; deutsche Namen in deutscher Oberfläche"""
import math

import DesignTemplates
from design import *


def bodies(doc):
    return [o for o in doc.Objects if o.TypeId == "Design::Body"]


def set_line(note, name, value):
    lines = note.Text.split("\n")
    note.Text = "\n".join("%s = %s mm" % (name, value) if l.split(" ")[0] == name else l for l in lines)
    Design.syncNoteParameters(note)


class Templates(DesignTest):
    def test_every_template_builds_clean(self):
        for key, en, de in DesignTemplates.TEMPLATES:
            doc = App.newDocument("T_" + key)
            try:
                Design.root(doc)
                DesignTemplates.build(doc, key, False)
                self.assertEqual(doc.Label, en)
                self.assertEqual(Design.problems(doc), [], key)
                found = bodies(doc)
                self.assertGreater(len(found), 0, key)
                for b in found:
                    self.assertTrue(b.Shape.isValid() and b.Shape.Volume > 0 and len(b.Shape.Solids) == 1,
                                    "%s: %s" % (key, b.Label))
            finally:
                App.closeDocument(doc.Name)

    def test_box_and_lid_sizes(self):
        DesignTemplates.build(self.doc, "box_lid", False)
        box, lid = sorted(bodies(self.doc), key=lambda b: b.Shape.BoundBox.XMin)
        self.assertAlmostEqual(box.Shape.Volume, 60 * 40 * 30 - 56 * 36 * 28, places=3)
        bb = lid.Shape.BoundBox
        self.assertAlmostEqual(bb.ZLength, 3 * 2, places=6)  # Platte Wand dick, Rand 2 Wand hoch
        # der Rand passt mit 0,2 mm Spiel je Seite in den Kasten (innen 56 x 36)
        rim = [f for f in lid.Shape.Faces if abs(f.CenterOfMass.z - 6) < 1e-6][0].BoundBox
        self.assertAlmostEqual(rim.XLength, 56 - 0.4, places=6)
        self.assertAlmostEqual(rim.YLength, 36 - 0.4, places=6)

    def test_a_note_line_changes_the_design(self):
        note = DesignTemplates.build(self.doc, "spacer", False)
        (spacer,) = bodies(self.doc)
        self.assertAlmostEqual(spacer.Shape.Volume, math.pi * (25 - 2.75 ** 2) * 15, places=3)
        set_line(note, "Length", 30)
        self.doc.recompute()
        self.assertAlmostEqual(spacer.Shape.Volume, math.pi * (25 - 2.75 ** 2) * 30, places=3)

    def test_pcb_case_has_four_standoffs_with_holes(self):
        DesignTemplates.build(self.doc, "pcb_case", False)
        (case,) = bodies(self.doc)
        holes = [f for f in case.Shape.Faces if f.Surface.TypeId == "Part::GeomCylinder" and abs(f.Surface.Radius - 1.25) < 1e-6]
        self.assertEqual(len(holes), 4)
        bb = case.Shape.BoundBox
        self.assertAlmostEqual(bb.XLength, 70 + 2 + 4, places=6)

    def test_bracket_has_two_wall_holes(self):
        DesignTemplates.build(self.doc, "wall_bracket", False)
        (bracket,) = bodies(self.doc)
        holes = [f for f in bracket.Shape.Faces if f.Surface.TypeId == "Part::GeomCylinder"]
        self.assertEqual(len(holes), 2)
        self.assertTrue(all(abs(abs(h.Surface.Axis.y) - 1) < 1e-9 for h in holes))  # quer durch die Rückwand

    def test_german_names(self):
        note = DesignTemplates.build(self.doc, "box_lid", True)
        self.assertEqual(self.doc.Label, "Box mit Deckel")
        self.assertIn("Breite = 60 mm", note.Text)
        self.assertAlmostEqual(Design.parameterSet(self.doc, False).Breite.Value, 60)


if __name__ == "__main__":
    unittest.main()
