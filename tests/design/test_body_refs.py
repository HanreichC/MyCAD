# SPDX-License-Identifier: LGPL-2.1-or-later
"""Fehler aus "Monitor Light" (2026-11-17): externe Kante an einem Body bildete einen Abhängigkeitskreis (Dokument
rechnete nie fertig), Press Pull schnitt nur den eigenen Körper, ein Schritt mit gelöschter Skizze blieb rot."""
from design import *


def poly(*pts):
    p = [V(x, y, 0) for x, y in pts]
    return [Part.LineSegment(p[i], p[(i + 1) % len(p)]) for i in range(len(p))]


def body_cut_from_sketch_with_body_edge(doc):
    """Quader, Skizze auf der Oberseite mit projizierter Body-Kante, Cut aus dieser Skizze in denselben Body"""
    _, b = box(doc, 20, 20, 10)
    face = top_face(b)
    obj, sub = Design.stableRef(b, face)  # wie "Create Sketch" auf einer Körperfläche
    sk = sketch(doc, rect(5, 5, 10, 10), support=(obj, sub))
    sk.addExternal(b.Name, edge_where(b, lambda p: abs(p.z - 10) < 1e-6))  # Body direkt, wie Projizieren/Maß an Kante
    doc.recompute()
    extrude(doc, sk, 5, op="Cut", bodies=[b], Reversed=True)
    return b, sk


class BodyEdgeInSketch(DesignTest):
    def test_projected_body_edge_makes_no_cycle(self):
        b, sk = body_cut_from_sketch_with_body_edge(self.doc)
        self.assertEqual(len(sk.ExternalGeometry), 1)  # die Kante ist da, nur am Zeitleisten-Zustand statt am Body
        self.assertNotIn(b, [o for o, _ in sk.ExternalGeometry])
        self.assertNotIn(b, sk.OutListRecursive)  # Skizze hängt nicht am Body (sonst Kreis über den Cut)
        self.doc.recompute()
        self.assertEqual(errors(self.doc), [])
        self.assertTrue(all("Touched" not in o.State for o in self.doc.Objects), [(o.Name, o.State) for o in self.doc.Objects])
        self.assertAlmostEqual(b.Shape.Volume, 20 * 20 * 10 - 5 * 5 * 5, delta=1e-3)


class PressPullThrough(DesignTest):
    def test_push_cuts_every_attached_body(self):
        # L-Körper: der Arm unten endet bei x=20; seine Stirnfläche hineindrücken geht durch den Arm bis in den Quader links
        sk = sketch(self.doc, poly((0, 0), (20, 0), (20, 5), (5, 5), (5, 10), (0, 10)))
        _, l = extrude(self.doc, sk, 10)
        _, cube = box(self.doc, 10, 10, 10, at=(-15, 0))
        face = face_where(l, lambda c, f: abs(c.x - 20) < 1e-6)
        pull = feature(self.doc, "Design::PressPull", Edges=[face], Distance=-40)
        Design.attachToBodies(pull, [l, cube])
        self.doc.recompute()
        self.assertEqual(errors(self.doc), [])
        self.assertAlmostEqual(l.Shape.Volume, 5 * 5 * 10, delta=1e-3)
        self.assertAlmostEqual(cube.Shape.Volume, 10 * 5 * 10, delta=1e-3)
        pull.Distance = 3  # herausziehen: nur der eigene Körper
        self.doc.recompute()
        self.assertAlmostEqual(l.Shape.Volume, 1250 + 3 * 5 * 10, delta=1e-3)
        self.assertAlmostEqual(cube.Shape.Volume, 1000, delta=1e-3)


class DeletedSketch(DesignTest):
    def test_step_without_sketch_is_skipped_not_failed(self):
        _, b = box(self.doc, 20, 20, 10)
        sk = sketch(self.doc, rect(5, 5, 10, 10))
        cut, _ = extrude(self.doc, sk, 5, op="Cut", bodies=[b])
        prof = profiles(sk)
        cut.Profile = None  # Skizze samt Profil gelöscht
        self.doc.removeObject(prof.Name)
        self.doc.removeObject(sk.Name)
        self.doc.recompute()
        self.assertEqual(errors(self.doc), [])
        self.assertIn("Profile gone", cut.Warning)
        self.assertAlmostEqual(b.Shape.Volume, 4000, delta=1e-3)
