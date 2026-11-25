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


class SkipFailedStep(DesignTest):
    def test_a_failing_step_is_red_and_the_later_steps_go_on(self):
        """Phase 14, wie Fusion: die Platte wird zu klein für die Rundung (R 6 an 5 x 5 mm). Die Rundung ist rot, der
        Körper geht ohne sie weiter, und der Zapfen danach kommt trotzdem (vorher hielt der Fehler alles danach an)"""
        import Sketcher
        base = sketch(self.doc, rect(0, 0, 80, 50))
        C = Sketcher.Constraint
        for c in [C("Coincident", i, 2, (i + 1) % 4, 1) for i in range(4)] + [
                C("Horizontal", 0), C("Horizontal", 2), C("Vertical", 1), C("Vertical", 3), C("Coincident", 0, 1, -1, 1),
                C("DistanceX", 0, 1, 0, 2, 80), C("DistanceY", 1, 1, 1, 2, 50)]:
            base.addConstraint(c)
        self.doc.recompute()
        _, b = extrude(self.doc, base, 10)
        corner = edge_where(b, lambda p: abs(p.x) < 1e-6 and abs(p.y) < 1e-6 and abs(p.z - 5) < 1e-6)
        f = dress(self.doc, "Design::Fillet", b, [corner], Size=6)
        boss, _ = extrude(self.doc, sketch(self.doc, circle(2.5, 2.5, 1), App.Placement(V(0, 0, 10), App.Rotation())), 5,
                          op="Join", bodies=[b])
        full = b.Shape.Volume
        dx = [i for i, c in enumerate(base.Constraints) if c.Type == "DistanceX"][0]
        dy = [i for i, c in enumerate(base.Constraints) if c.Type == "DistanceY"][0]
        base.setDatum(dx, App.Units.Quantity("5 mm"))
        base.setDatum(dy, App.Units.Quantity("5 mm"))
        self.doc.recompute()
        self.assertTrue(failed(f))
        self.assertFalse(failed(boss))
        self.assertAlmostEqual(b.Shape.Volume, 5 * 5 * 10 + math.pi * 1 * 5, places=3)
        self.assertIn(f, [o for o, t in Design.problems(self.doc)])
        base.setDatum(dx, App.Units.Quantity("80 mm"))
        base.setDatum(dy, App.Units.Quantity("50 mm"))
        self.doc.recompute()
        self.assertNoErrors()
        self.assertAlmostEqual(b.Shape.Volume, full, places=3)


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
        # 13.5: die Kante liegt unverändert da, wo sie war: dieselbe Kante, ohne Warnung (sonst warnte jedes Löschen eines
        # früheren Schritts, dessen Schnitt im Namen steckte)
        self.assertEqual(list(f.ErrorElements), [])
        self.assertEqual(f.Warning, "")

    def test_moved_edge_is_guessed_and_warns(self):
        _, b = box(self.doc, 20, 10, 5)
        right = front_top(b)
        f = dress(self.doc, "Design::Fillet", b, [right], Size=1)
        x, y, z, size = (float(v) for v in f.ElementHints[0].split())
        f.ElementMaps = ["lost"]
        f.ElementHints = ["%g %g %g %g" % (x + 0.5, y, z, size)]  # das Modell hat sich darunter verändert
        f.touch()
        self.doc.recompute()
        self.assertNoErrors()
        self.assertEqual(list(f.ErrorElements), [right])
        self.assertIn("check", f.Warning)

    def test_warning_clears_when_the_model_is_back(self):
        """Phase 14: nach einer drastischen Änderung musste geraten werden (Warnung); Rückgängig bringt das Modell genau
        zurück: die Kante liegt wieder dort, wo sie gewählt wurde, die Warnung geht von selbst"""
        _, b = box(self.doc, 20, 10, 5)
        f = dress(self.doc, "Design::Fillet", b, [front_top(b)], Size=1)
        good = list(f.ElementHints)
        x, y, z, size = (float(v) for v in good[0].split())
        f.ElementMaps = ["lost"]
        f.ElementHints = ["%g %g %g %g" % (x + 0.5, y, z, size)]
        f.touch()
        self.doc.recompute()
        self.assertIn("check", f.Warning)
        f.WarnedHints = good  # wie vor dem Raten: dort hatte der Mensch gewählt
        f.touch()
        self.doc.recompute()
        self.assertEqual(f.Warning, "")

    def test_warning_stays_until_confirmed(self):
        _, b = box(self.doc, 20, 10, 5)
        f = dress(self.doc, "Design::Fillet", b, [front_top(b)], Size=1)
        x, y, z, size = (float(v) for v in f.ElementHints[0].split())
        f.ElementMaps = ["lost"]
        f.ElementHints = ["%g %g %g %g" % (x + 0.5, y, z, size)]
        f.touch()
        self.doc.recompute()
        self.assertTrue(f.Warning)
        f.touch()
        self.doc.recompute()
        self.assertTrue(f.Warning)  # bleibt, bis jemand bestätigt
        f.Warning = ""
        self.doc.recompute()
        self.assertEqual(f.Warning, "")
