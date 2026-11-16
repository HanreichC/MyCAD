# SPDX-License-Identifier: LGPL-2.1-or-later
"""Phase 11.3 Druckbar machen: Bohrung quer zur Druckrichtung als Tropfenform, Rundung mit gefasten Unterkanten, zu dünne
Wand auf die Mindestwand. printFixes schlägt je Schritt vor, was besser druckt; angewendet verschwindet der Vorschlag.
Volumen jeweils nachgerechnet."""
import math

from design import *

PI = math.pi
MIN_WALL = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD").GetFloat("MinWall", 0.8)


def fixes(doc):
    return [(doc.getObject(name).TypeId, prop) for name, label, prop, value in Design.printFixes(doc)]


def side_hole(doc, body, **props):
    """Bohrung von der Seite x = 20 waagrecht in den Körper, Mitte y = 10, z = 5 (Ø5, 10 tief)"""
    sk = sketch(doc, [Part.Point(V(0, 0, 0))], App.Placement(V(20, 10, 5), App.Rotation(V(0, 1, 0), 90)))
    f = feature(doc, "Design::Hole", Design.componentOf(body), Sketch=sk, Diameter=5, Depth=10)
    for k, v in props.items():
        setattr(f, k, v)
    Design.attachToBodies(f, [body])
    doc.recompute()
    return f


class Teardrop(DesignTest):
    def test_side_hole_is_suggested_and_becomes_a_teardrop(self):
        _, b = box(self.doc, 20, 20, 10)
        h = side_hole(self.doc, b)
        r = 2.5
        self.assertVolume(b, 4000 - PI * r * r * 10)
        self.assertIn(("Design::Hole", "Teardrop"), fixes(self.doc))
        h.Teardrop = True
        self.doc.recompute()
        # Kreis plus 45°-Spitze: Drachen r² ohne den Viertelkreis darin
        self.assertVolume(b, 4000 - (PI * r * r + r * r - PI * r * r / 4) * 10)
        self.assertNotIn(("Design::Hole", "Teardrop"), fixes(self.doc))
        self.assertNoErrors()

    def test_vertical_hole_needs_nothing(self):
        _, b = box(self.doc, 20, 20, 10)
        sk = sketch(self.doc, [Part.Point(V(10, 10, 0))], App.Placement(V(0, 0, 10), App.Rotation()))
        f = feature(self.doc, "Design::Hole", Design.componentOf(b), Sketch=sk, Diameter=5, Depth=5, Teardrop=True)
        Design.attachToBodies(f, [b])
        self.doc.recompute()
        self.assertVolume(b, 4000 - PI * 6.25 * 5)  # senkrecht: keine Spitze, auch wenn eingeschaltet
        self.assertEqual(fixes(self.doc), [])

    def test_print_direction_change_redraws_the_tip(self):
        _, b = box(self.doc, 20, 20, 10)
        side_hole(self.doc, b, Teardrop=True)
        Design.setPrintUp(self.doc, V(1, 0, 0))  # jetzt steht die Bohrung senkrecht
        self.doc.recompute()
        self.assertVolume(b, 4000 - PI * 6.25 * 10)


class BottomChamfer(DesignTest):
    def test_bottom_edge_becomes_chamfer_top_edge_stays_round(self):
        _, b = box(self.doc, 20, 20, 10)
        bottom = edge_where(b, lambda p: abs(p.y) < 1e-6 and abs(p.z) < 1e-6)
        top = edge_where(b, lambda p: abs(p.y) < 1e-6 and abs(p.z - 10) < 1e-6)
        f = dress(self.doc, "Design::Fillet", b, [bottom, top], Size=2)
        round_off = 4 * (1 - PI / 4) * 20  # Rundung r = 2 nimmt r² (1 - π/4) je mm weg
        self.assertVolume(b, 4000 - 2 * round_off)
        self.assertIn(("Design::Fillet", "PrintChamfer"), fixes(self.doc))
        f.PrintChamfer = True
        self.doc.recompute()
        self.assertVolume(b, 4000 - round_off - 2 * 20)  # Fase 2 × 2 nimmt r²/2 je mm weg
        self.assertEqual(fixes(self.doc), [])
        self.assertNoErrors()

    def test_top_edges_only_need_nothing(self):
        _, b = box(self.doc, 20, 20, 10)
        top = edge_where(b, lambda p: abs(p.y) < 1e-6 and abs(p.z - 10) < 1e-6)
        dress(self.doc, "Design::Fillet", b, [top], Size=2)
        self.assertEqual(fixes(self.doc), [])

    def test_saved_and_reloaded(self):
        _, b = box(self.doc, 20, 20, 10)
        bottom = edge_where(b, lambda p: abs(p.y) < 1e-6 and abs(p.z) < 1e-6)
        dress(self.doc, "Design::Fillet", b, [bottom], Size=2, PrintChamfer=True)
        doc = save_and_reload(self.doc)
        doc.recompute()
        body = [o for o in doc.Objects if o.TypeId == "Design::Body"][0]
        self.assertVolume(body, 4000 - 2 * 20)


class ThinWall(DesignTest):
    def test_shell_below_min_wall_is_raised(self):
        _, b = box(self.doc, 20, 20, 10)
        top = face_where(b, lambda c, f: abs(c.z - 10) < 1e-6)
        s = dress(self.doc, "Design::Shell", b, [top], Size=0.4)
        found = [x for x in Design.printFixes(self.doc) if x[2] == "Size"]
        self.assertEqual(len(found), 1)
        self.assertAlmostEqual(found[0][3], MIN_WALL)
        s.Size = found[0][3]
        self.doc.recompute()
        self.assertEqual(fixes(self.doc), [])
        self.assertNoErrors()
