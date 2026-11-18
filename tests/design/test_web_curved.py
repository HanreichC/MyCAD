# SPDX-License-Identifier: LGPL-2.1-or-later
"""Aufräumliste B8: eine Wand (Web) auch aus Bögen und geschlossenen Kurven. Wanne 60 x 40 x 20 mit 2 mm Wand, oben
offen: ein Bogen von Seitenwand zu Seitenwand wird eine gebogene Trennwand bis zum Boden, ein Kreis ein Ring auf dem
Boden. Ein Bogen, der frei im Raum endet, wird abgelehnt (wie bei geraden Linien)."""
import math

from design import *


def tray(doc):
    """Wanne: Boden z 0..2, Wände 2 mm, innen x 2..58, y 2..38, oben offen bei z = 20"""
    _, b = box(doc, 60, 40, 20)
    pocket = sketch(doc, rect(2, 2, 58, 38), App.Placement(V(0, 0, 20), App.Rotation()))
    extrude(doc, pocket, 18, op="Cut", bodies=[b], Reversed=True)
    return b


def web(doc, body, geos, t=2):
    sk = sketch(doc, geos, App.Placement(V(0, 0, 20), App.Rotation()))
    f = feature(doc, "Design::Rib", Design.componentOf(body), Curves=(sk, ["Edge1"]), Thickness=t, Mode="Web")
    Design.attachToBodies(f, [body])
    doc.recompute()
    return f


class CurvedWeb(DesignTest):
    def test_arc_from_wall_to_wall(self):
        b = tray(self.doc)
        before = b.Shape.Volume
        # Bogen von der linken Innenwand (x = 2) zur rechten (x = 58), Scheitel bei y = 30
        arc = Part.Arc(V(2, 20, 0), V(30, 30, 0), V(58, 20, 0))
        f = web(self.doc, b, [arc])
        self.assertTrue(f.isValid(), f.getStatusString())
        added = b.Shape.Volume - before
        length = arc.toShape().Length
        self.assertAlmostEqual(added, length * 2 * 18, delta=0.04 * length * 2 * 18)  # Bogen x 2 mm x 18 hoch
        self.assertEqual(len(b.Shape.Solids), 1)
        self.assertNoErrors()

    def test_ring_on_the_floor(self):
        b = tray(self.doc)
        before = b.Shape.Volume
        f = web(self.doc, b, [Part.Circle(V(30, 20, 0), V(0, 0, 1), 8)])
        self.assertTrue(f.isValid(), f.getStatusString())
        ring = math.pi * ((8 + 1) ** 2 - (8 - 1) ** 2) * 18  # Ring 2 mm, 18 hoch
        self.assertAlmostEqual(b.Shape.Volume - before, ring, delta=0.01 * ring)

    def test_arc_ending_in_the_air_is_refused(self):
        b = tray(self.doc)
        f = web(self.doc, b, [Part.Arc(V(20, 20, 0), V(30, 25, 0), V(40, 20, 0))])  # beide Enden mitten in der Wanne
        self.assertFalse(f.isValid())
        self.assertIn("touch a wall", f.getStatusString())
