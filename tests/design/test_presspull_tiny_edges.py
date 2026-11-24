# SPDX-License-Identifier: LGPL-2.1-or-later
"""Drücken/Ziehen auf einer Fläche mit Kanten kürzer als die Toleranz ihrer Ecken (Reste früherer Boolescher Schritte):
das Prisma schnitt sich selbst, Herausziehen wurde ungültig und das nächste Hineindrücken ließ den ganzen Körper
verschwinden. Echter Stand: ConceptKey (tests/projects), Rand von Basis +2,7 mm gezogen, dann -2 mm."""
import os
from design import *

FILE = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "projects", "ConceptKey press pull.mycad")


class PressPullTinyEdges(unittest.TestCase):
    def test_pull_then_push_the_rim(self):
        doc = App.openDocument(FILE)
        try:
            basis = doc.getObjectsByLabel("Basis")[0]
            self.assertFalse(basis.Shape.isValid(), "the file holds the broken result from before the fix")
            doc.recompute()  # ein ungültig gespeichertes Ergebnis rechnet von selbst neu (mustExecute)
            self.assertTrue(basis.Shape.isValid())
            sh = basis.Shape
            rim = max((i for i, f in enumerate(sh.Faces) if abs(f.BoundBox.ZMin - 6.5) < 1e-6 and f.BoundBox.ZLength < 1e-6),
                      key=lambda i: sh.Faces[i].Area)
            area, before = sh.Faces[rim].Area, sh.Volume
            push = feature(doc, "Design::PressPull", Edges=["Face%d" % (rim + 1)], Distance=-2)
            Design.attachToBodies(push, [basis])
            doc.recompute()
            self.assertTrue(basis.Shape.isValid())
            self.assertAlmostEqual(basis.Shape.Volume, before - 2 * area, delta=1.0)
        finally:
            App.closeDocument(doc.Name)
