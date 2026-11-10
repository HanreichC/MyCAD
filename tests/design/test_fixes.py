# SPDX-License-Identifier: LGPL-2.1-or-later
"""10.2 Idee 6: Fehler schlagen einen Wert vor, der geht; verlorene Bezüge finden die passende Kante und warnen"""
from design import *


def fixes(f):
    """[(Beschriftung, Property, Wert)]"""
    out = []
    for entry in f.Fixes:
        label, prop, value = entry.split("\t")
        out.append((label, prop, float(value)))
    return out


def apply(doc, f, fix):
    _, prop, value = fix
    current = getattr(f, prop)
    setattr(f, prop, int(value) if isinstance(current, str) else value)  # Auswahllisten nehmen den Index
    doc.recompute()


def front_top(b):
    return edge_where(b, lambda p: abs(p.y) < 1e-6 and abs(p.z - 5) < 1e-6)


class Suggestions(DesignTest):
    def test_fillet_too_large_suggests_largest_radius(self):
        _, b = box(self.doc, 20, 10, 5)
        f = dress(self.doc, "Design::Fillet", b, [front_top(b)], Size=8)
        self.assertTrue(failed(f))
        (fix,) = fixes(f)
        self.assertEqual(fix[1], "Size")
        self.assertTrue(4.5 < fix[2] <= 5.0, fix)
        self.assertIn(front_top(b), f.ErrorElements)
        apply(self.doc, f, fix)
        self.assertNoErrors()
        self.assertEqual(list(f.Fixes), [])

    def test_chamfer_too_large(self):
        _, b = box(self.doc, 20, 10, 5)
        f = dress(self.doc, "Design::Chamfer", b, [front_top(b)], Size=7)
        (fix,) = fixes(f)
        apply(self.doc, f, fix)
        self.assertNoErrors()

    def test_shell_too_thick(self):
        _, b = box(self.doc, 20, 10, 5)
        f = dress(self.doc, "Design::Shell", b, [top_face(b)], Size=6)
        self.assertTrue(failed(f))
        (fix,) = fixes(f)
        self.assertLess(fix[2], 6)
        apply(self.doc, f, fix)
        self.assertNoErrors()

    def test_revolve_suggests_an_axis_beside_the_profile(self):
        sk = sketch(self.doc, rect(5, -2, 10, 2))  # die Skizzen-X-Achse geht mitten durch
        f = feature(self.doc, "Design::Revolve", Axis="Sketch X")
        f.Profile = (profiles(sk), ["Face1"])
        new_body(f)
        self.doc.recompute()
        self.assertTrue(failed(f))
        (fix,) = fixes(f)
        self.assertEqual(fix[1], "Axis")
        apply(self.doc, f, fix)
        self.assertNoErrors()


class LostReference(DesignTest):
    def test_lost_name_finds_the_matching_edge_and_warns(self):
        _, b = box(self.doc, 20, 10, 5)
        right = front_top(b)
        f = dress(self.doc, "Design::Fillet", b, [right], Size=1)
        good = b.Shape.Volume
        short = edge_where(b, lambda p: abs(p.x) < 1e-6 and abs(p.y) < 1e-6)  # senkrechte Kante, 5 mm
        # Name verloren und alte Nummer zeigt auf die falsche Kante: früher hätte MyCAD still diese gerundet
        f.Edges = [short]
        f.ElementMaps = ["lost"]
        f.touch()
        self.doc.recompute()
        self.assertNoErrors()
        self.assertAlmostEqual(b.Shape.Volume, good, delta=1e-6)
        self.assertEqual(list(f.ErrorElements), [right])
        self.assertIn("check", f.Warning)

    def test_warning_stays_until_confirmed(self):
        _, b = box(self.doc, 20, 10, 5)
        f = dress(self.doc, "Design::Fillet", b, [front_top(b)], Size=1)
        f.ElementMaps = ["lost"]
        f.touch()
        self.doc.recompute()
        self.assertTrue(f.Warning)
        f.touch()
        self.doc.recompute()
        self.assertTrue(f.Warning)  # bleibt, bis jemand bestätigt
        f.Warning = ""
        self.doc.recompute()
        self.assertEqual(f.Warning, "")
