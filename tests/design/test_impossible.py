# SPDX-License-Identifier: LGPL-2.1-or-later
"""U4/U5: unmögliche Werte und Refine an vielen Bohrungen. In FreeCAD stürzen Rundung, Fase und Schale bei zu großen
Werten teils ab (OCCT-Segfault, nicht abfangbar: FreeCAD#33698, #23818, #25868, #29352, #22921). Erwartet: der Schritt
meldet einen Fehler (oder rechnet, wenn OCCT es doch schafft), MyCAD läuft weiter, der Körper davor bleibt heil. Bei
Gewindebohrungen nebeneinander scheitert in FreeCAD das Refine (#15353, #17802): hier rechnet der Schritt trotzdem."""
from design import *
from test_hole import hole


def survives(test, f, body, before):
    """kein Absturz (wir sind noch hier); fehlgeschlagen = rot und der Körper geht ohne den Schritt weiter (before)"""
    test.doc.recompute()
    if not f.isValid():
        test.assertTrue(f.getStatusString(), f.Name)
    test.assertGreater(body.Shape.Volume, 0)
    test.assertTrue(body.Shape.isValid() or not f.isValid())
    if not f.isValid():
        test.assertAlmostEqual(body.Shape.Volume, before, delta=1e-6 * before)


class Impossible(DesignTest):
    def block(self):
        _, b = box(self.doc, 20, 20, 10)
        return b, b.Shape.Volume

    def test_fillet_wider_than_the_face(self):
        b, v = self.block()
        f = dress(self.doc, "Design::Fillet", b, ["Edge1"], Size=15)
        survives(self, f, b, v)

    def test_fillet_all_edges_more_than_half_thickness(self):
        b, v = self.block()
        f = dress(self.doc, "Design::Fillet", b, ["Edge%d" % i for i in range(1, 13)], Size=6)
        survives(self, f, b, v)

    def test_fillet_grows_until_impossible(self):
        b, v = self.block()
        f = dress(self.doc, "Design::Fillet", b, ["Edge1", "Edge2"], Size=1)
        for size in (3, 5, 9, 14, 30):
            f.Size = size
            self.doc.recompute()
            # gescheitert: wie Fusion geht der Körper ohne die rote Rundung weiter (Phase 14; früher blieb die letzte
            # gelungene stehen, und alles danach hielt an)
            survives(self, f, b, v)

    def test_chamfer_next_to_fillet(self):
        b, v = self.block()
        f = dress(self.doc, "Design::Fillet", b, ["Edge1"], Size=4)
        self.doc.recompute()
        c = dress(self.doc, "Design::Chamfer", b, ["Edge2"], Size=12)
        survives(self, c, b, f.Shape.Volume if f.isValid() else v)

    def test_chamfer_all_edges_too_big(self):
        b, v = self.block()
        f = dress(self.doc, "Design::Chamfer", b, ["Edge%d" % i for i in range(1, 13)], Size=11)
        survives(self, f, b, v)

    def test_shell_thicker_than_the_part(self):
        b, v = self.block()
        f = dress(self.doc, "Design::Shell", b, [top_face(b)], Size=12)
        survives(self, f, b, v)

    def test_threaded_holes_side_by_side(self):
        _, b = box(self.doc, 60, 20, 10)
        v = b.Shape.Volume
        f = hole(self.doc, b, [(8 + 7 * i, 10) for i in range(7)], 10, Standard="ISO metric", Size="M5x0.8",
                 Kind="Tapped hole", Depth=8, Modeled=True)
        self.assertTrue(f.isValid(), f.getStatusString())
        self.assertLess(b.Shape.Volume, v)
        self.assertEqual(len(b.Shape.Solids), 1)
        self.assertNoErrors()
