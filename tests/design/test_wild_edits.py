# SPDX-License-Identifier: LGPL-2.1-or-later
"""Chaotisch in alten Skizzen weiterarbeiten (ConceptKey, 2026-11-25): das Profil zweimal hintereinander teilen,
dabei Versätze (neue Inseln) hineinzeichnen; eine Skizze verliert ihre Fläche. Nichts davon darf den Körper still
verändern oder alle späteren Schritte anhalten."""
from design import *


class WildEdits(DesignTest):
    def test_split_twice_with_an_island(self):
        base = sketch(self.doc, rect(0, 0, 80, 50))
        ext, b = extrude(self.doc, base, 10)
        full = b.Shape.Volume
        base.addGeometry(Part.LineSegment(V(40, -10, 0), V(40, 60, 0)))  # erste Teilung
        self.doc.recompute()
        base.addGeometry(Part.LineSegment(V(-10, 25, 0), V(90, 25, 0)))  # die Teile noch einmal teilen
        base.addGeometry(Part.Circle(V(20, 12, 0), V(0, 0, 1), 3))       # neue Insel: wird ein Loch (wie Fusion)
        self.doc.recompute()
        self.assertNoErrors()
        self.assertEqual(ext.Warning, "")
        self.assertAlmostEqual(b.Shape.Volume, full - math.pi * 9 * 10, places=2)

    def test_a_sketch_that_loses_its_face_does_not_block(self):
        base = sketch(self.doc, rect(0, 0, 80, 50))
        ext, b = extrude(self.doc, base, 10)
        hole = sketch(self.doc, circle(20, 25, 5), support=(b, top_face(b)))
        cut, _ = extrude(self.doc, hole, 10, op="Cut", bodies=[b], Reversed=True)
        later = sketch(self.doc, circle(60, 25, 5))
        pin, _ = extrude(self.doc, later, 5, op="Join", bodies=[b])
        hole.AttachmentSupport = [(hole.AttachmentSupport[0][0], ("Face999",))]  # Fläche gibt es nicht (mehr)
        pin.Distance = 7
        self.doc.recompute()
        self.assertNotIn("Invalid", hole.State)
        self.assertTrue(hole.Warning.startswith("Face gone"), hole.Warning)
        self.assertNotIn("Touched", pin.State, "steps after it still compute")

    def test_a_join_inside_the_body_says_so(self):
        """Grundskizze liegt im Material (ConceptKey: Versatz 1 mm in "Skizze" unter dem Rand): Verbinden fügt nichts hinzu
        und sagt das, statt still nichts zu tun"""
        _, b = box(self.doc, 40, 20, 10)  # z 0..10: das Band ab z = 0 liegt ganz im Körper
        band = sketch(self.doc, rect(5, 5, 35, 6))
        join, _ = extrude(self.doc, band, 3, op="Join", bodies=[b])
        self.assertTrue(join.Warning.startswith("Adds nothing"), join.Warning)
        join.StartOffset = 10  # von der Oberseite aus
        self.doc.recompute()
        self.assertEqual(join.Warning, "")
        self.assertAlmostEqual(b.Shape.Volume, 40 * 20 * 10 + 30 * 1 * 3, places=3)
