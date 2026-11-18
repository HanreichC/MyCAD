# SPDX-License-Identifier: LGPL-2.1-or-later
"""Aufräumliste B7: Außengewinde mit Fase an den freien Enden (45° bis zum Kern), nicht an einem Absatz. Ohne den
Schalter bleibt die Form wie bisher (alte Dateien, Skripte)."""
from design import *
from test_thread import cylinder, cyl_face, thread


def end_radius(body, z):
    """größter Abstand der Stirnfläche bei Höhe z von der Achse (Kreis-Rand der Stirn)"""
    ends = [f for f in body.Shape.Faces if f.Surface.TypeId == "Part::GeomPlane" and abs(f.CenterOfMass.z - z) < 1e-6]
    return max(max((v.Point.x ** 2 + v.Point.y ** 2) ** 0.5 for v in f.Vertexes) for f in ends)


class ThreadChamfer(DesignTest):
    def test_off_keeps_the_old_shape(self):
        b = cylinder(self.doc, 5, 20)
        t = thread(self.doc, b, cyl_face(b))  # Standard: Auto (M10x1,5), ohne Fase
        self.assertFalse(t.EndChamfer)
        self.assertAlmostEqual(end_radius(b, 20), 5, delta=0.05)  # der Gang läuft bis an den Rand

    def test_free_ends_are_chamfered_to_the_core(self):
        b = cylinder(self.doc, 5, 20)
        t = thread(self.doc, b, cyl_face(b))
        v_plain = b.Shape.Volume
        t.EndChamfer = True
        self.doc.recompute()
        core = 5 - 0.6134 * 1.5  # Kern bei M10x1,5
        self.assertAlmostEqual(end_radius(b, 20), core, delta=0.05)  # oben bis zum Kern gefast
        self.assertAlmostEqual(end_radius(b, 0), core, delta=0.05)   # unten auch (frei)
        self.assertLess(b.Shape.Volume, v_plain)
        self.assertTrue(b.Shape.isValid())
        self.assertNoErrors()

    def test_no_chamfer_at_a_shoulder(self):
        # Zapfen Ø10 auf einem Sockel Ø30: unten ein Absatz, oben frei
        _, base = box(self.doc, 30, 30, 5, at=(-15, -15))
        sk = sketch(self.doc, circle(0, 0, 5), App.Placement(V(0, 0, 5), App.Rotation()))
        extrude(self.doc, sk, 15, op="Join", bodies=[base])
        pin = [i for i, f in enumerate(base.Shape.Faces, 1) if f.Surface.TypeId != "Part::GeomPlane" and abs(f.CenterOfMass.z - 12.5) < 1e-6][0]
        t = thread(self.doc, base, "Face%d" % pin)
        top = lambda: sum(f.Area for f in base.Shape.Faces
                          if f.Surface.TypeId == "Part::GeomPlane" and abs(f.CenterOfMass.z - 5) < 0.5)
        shoulder_plain = top()
        t.EndChamfer = True
        self.doc.recompute()
        self.assertAlmostEqual(end_radius(base, 20), 5 - 0.6134 * 1.5, delta=0.05)  # freies Ende gefast
        self.assertAlmostEqual(top(), shoulder_plain, places=6)  # am Absatz: genau wie ohne Fase
        self.assertTrue(base.Shape.isValid())
        self.assertNoErrors()
