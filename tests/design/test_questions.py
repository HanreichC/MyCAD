# SPDX-License-Identifier: LGPL-2.1-or-later
"""12.9 Fragen ans Modell: "Warum ist das rot?" (was nicht rechnet, dann Warnungen) und "Was hängt daran?" (wer das
Gewählte benutzt)"""
from design import *


class Questions(DesignTest):
    def test_healthy_design_has_no_problems(self):
        box(self.doc, 10, 10, 10)
        self.assertEqual(Design.problems(self.doc), [])

    def test_fillet_too_big_is_named_first(self):
        _, b = box(self.doc, 10, 10, 10)
        f = dress(self.doc, "Design::Fillet", b, ["Edge1", "Edge2", "Edge3", "Edge4"], Size=50)
        self.doc.recompute()
        self.assertIn("Invalid", f.State)
        found = Design.problems(self.doc)
        self.assertGreater(len(found), 0)
        self.assertEqual(found[0][0], f)  # der kaputte Schritt zuerst, mit seinem Fehlertext
        self.assertNotEqual(found[0][1], "")

    def test_what_uses_the_sketch(self):
        sk = sketch(self.doc, rect(0, 0, 10, 10))
        f, b = extrude(self.doc, sk, 5)
        self.assertIn(f, Design.dependents(sk))
        self.assertNotIn(Design.root(self.doc), Design.dependents(sk))  # Komponenten und Ordner zählen nicht
        f2, _ = extrude(self.doc, sketch(self.doc, rect(20, 0, 30, 10)), 5)
        self.assertNotIn(f2, Design.dependents(sk))

    def test_unused_sketch_has_no_dependents(self):
        sk = sketch(self.doc, rect(0, 0, 10, 10))
        self.assertEqual(Design.dependents(sk), [])


if __name__ == "__main__":
    unittest.main()
