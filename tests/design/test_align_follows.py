# SPDX-License-Identifier: LGPL-2.1-or-later
"""Aufräumliste B6: Ausrichten folgt Änderungen. Block A mit seiner Unterseite auf die Oberseite von T: A liegt bündig
oben auf T. Wird T höher, wandert A mit (vorher: einmal berechnet, A blieb in der Luft bzw. steckte in T). Fehlt ein
Bezug, bleibt A an der letzten Lage und der Schritt warnt."""
from design import *


def flat(body, pred):
    return face_where(body, lambda c, f: f.Surface.TypeId == "Part::GeomPlane" and pred(c))


def align(doc, body, element, target, target_element):
    m = feature(doc, "Design::Move", Design.componentOf(body))
    Design.attachToBodies(m, [body])
    m.AlignFrom = element
    m.AlignTo = (target, [target_element])
    doc.recompute()
    return m


class AlignFollows(DesignTest):
    def setup_blocks(self):
        _, a = box(self.doc, 10, 10, 10)
        ft, t = box(self.doc, 20, 20, 5, at=(30, 0))
        m = align(self.doc, a, flat(a, lambda c: abs(c.z) < 1e-6), t, flat(t, lambda c: abs(c.z - 5) < 1e-6))
        return a, ft, t, m

    def test_lies_on_top_of_the_target(self):
        a, ft, t, m = self.setup_blocks()
        bb = a.Shape.BoundBox
        self.assertAlmostEqual(bb.ZMin, 5, places=6)  # bündig auf der Oberseite
        self.assertAlmostEqual(bb.Center.x, 40, places=6)  # Mitte auf Mitte
        self.assertAlmostEqual(bb.Center.y, 10, places=6)
        self.assertNoErrors()

    def test_follows_when_the_target_grows(self):
        a, ft, t, m = self.setup_blocks()
        ft.Distance = 12
        self.doc.recompute()
        self.assertAlmostEqual(a.Shape.BoundBox.ZMin, 12, places=6)
        self.assertEqual(m.Warning, "")

    def test_survives_save(self):
        a, ft, t, m = self.setup_blocks()
        names = a.Name, ft.Name
        doc = save_and_reload(self.doc)
        doc.getObject(names[1]).Distance = 8
        doc.recompute()
        self.assertAlmostEqual(doc.getObject(names[0]).Shape.BoundBox.ZMin, 8, places=6)

    def test_lost_reference_keeps_last_place_and_warns(self):
        a, ft, t, m = self.setup_blocks()
        m.AlignFrom = "Face99"  # das Element gibt es nicht mehr
        self.doc.recompute()
        self.assertIn("Align lost", m.Warning)
        self.assertAlmostEqual(a.Shape.BoundBox.ZMin, 5, places=6)  # letzte Lage (Alignment) bleibt
