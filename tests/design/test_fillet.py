# SPDX-License-Identifier: LGPL-2.1-or-later
"""L5 Rundung und Fase: Tangentenkette, variabler Radius, zwei Abstände, Abstand und Winkel, Seite tauschen"""
from design import *


def rounded_rect(w, h, r):
    """Rechteck mit tangential angeschlossenen Viertelkreisen in den Ecken (eine Tangentenkette)"""
    g = [Part.LineSegment(V(r, 0, 0), V(w - r, 0, 0)), Part.LineSegment(V(w, r, 0), V(w, h - r, 0)),
         Part.LineSegment(V(w - r, h, 0), V(r, h, 0)), Part.LineSegment(V(0, h - r, 0), V(0, r, 0))]
    for cx, cy, a in ((w - r, r, -90), (w - r, h - r, 0), (r, h - r, 90), (r, r, 180)):
        g.append(Part.ArcOfCircle(Part.Circle(V(cx, cy, 0), V(0, 0, 1), r), math.radians(a), math.radians(a + 90)))
    return g


def front_top_edge(b):
    """Kante oben vorne (y = 0, z = Höhe) eines Quaders ab dem Ursprung"""
    zmax = b.Shape.BoundBox.ZMax
    return edge_where(b, lambda p: abs(p.y) < 1e-6 and abs(p.z - zmax) < 1e-6)


class Chain(DesignTest):
    def test_one_edge_fillets_the_tangent_chain(self):
        sk = sketch(self.doc, rounded_rect(40, 20, 5))
        _, b = extrude(self.doc, sk, 10)
        top_edges = [i for i, e in enumerate(b.Shape.Edges, 1) if abs(e.CenterOfMass.z - 10) < 1e-6]
        self.assertEqual(len(top_edges), 8)
        before_faces = len(b.Shape.Faces)
        dress(self.doc, "Design::Fillet", b, ["Edge%d" % top_edges[0]], Size=1)
        self.assertNoErrors()
        self.assertEqual(len(b.Shape.Faces), before_faces + 8)  # alle 8 Kanten der Kette gerundet


class Fillets(DesignTest):
    def test_variable_radius_between_constant_ones(self):
        volumes = []
        for variable, r1, r2 in ((False, 1, 1), (True, 1, 3), (False, 3, 3)):
            doc = new_doc("V%d" % len(volumes))
            _, b = box(doc, 40, 10, 10)
            dress(doc, "Design::Fillet", b, [front_top_edge(b)], Size=r1, Variable=variable, RadiusEnd=r2)
            self.assertEqual(errors(doc), [])
            self.assertTrue(b.Shape.isValid())
            volumes.append(b.Shape.Volume)
        self.assertGreater(volumes[0], volumes[1])
        self.assertGreater(volumes[1], volumes[2])

    def test_radius_end_only_shown_when_variable(self):
        _, b = box(self.doc, 10, 10, 10)
        f = dress(self.doc, "Design::Fillet", b, [front_top_edge(b)], Size=1)
        self.assertIn("Hidden", f.getPropertyStatus("RadiusEnd"))
        f.Variable = True
        self.assertNotIn("Hidden", f.getPropertyStatus("RadiusEnd"))


class Chamfers(DesignTest):
    def test_equal_distance(self):
        _, b = box(self.doc, 40, 10, 10)
        dress(self.doc, "Design::Chamfer", b, [front_top_edge(b)], Size=2)
        self.assertVolume(b, 4000 - 0.5 * 2 * 2 * 40)

    def test_two_distances(self):
        _, b = box(self.doc, 40, 10, 10)
        dress(self.doc, "Design::Chamfer", b, [front_top_edge(b)], Size=1, Type="Two distances", Distance2=3)
        self.assertNoErrors()
        self.assertVolume(b, 4000 - 0.5 * 1 * 3 * 40)

    def test_flip_swaps_the_faces(self):
        widths = []
        for flip in (False, True):
            doc = new_doc("F%d" % flip)
            _, b = box(doc, 40, 10, 10)
            dress(doc, "Design::Chamfer", b, [front_top_edge(b)], Size=1, Type="Two distances", Distance2=3,
                  FlipSide=flip)
            top = b.Shape.getElement(top_face(b))
            widths.append(round(top.BoundBox.YLength, 4))
        self.assertEqual(sorted(widths), [7, 9])  # einmal 1 mm, einmal 3 mm von der Oberseite weg

    def test_distance_and_angle(self):
        _, b = box(self.doc, 40, 10, 10)
        dress(self.doc, "Design::Chamfer", b, [front_top_edge(b)], Size=2, Type="Distance and angle", ChamferAngle=30)
        self.assertNoErrors()
        removed = 4000 - b.Shape.Volume
        candidates = [0.5 * 2 * 2 * math.tan(math.radians(30)) * 40, 0.5 * 2 * 2 / math.tan(math.radians(30)) * 40]
        self.assertTrue(any(abs(removed - c) < 1e-3 * c for c in candidates), removed)

    def test_bad_angle_explains(self):
        _, b = box(self.doc, 10, 10, 10)
        f = dress(self.doc, "Design::Chamfer", b, [front_top_edge(b)], Size=1, Type="Distance and angle", ChamferAngle=95)
        self.assertTrue(failed(f))
        self.assertIn("angle", f.getStatusString())

    def test_rows_follow_type(self):
        _, b = box(self.doc, 10, 10, 10)
        f = dress(self.doc, "Design::Chamfer", b, [front_top_edge(b)], Size=1)
        self.assertIn("Hidden", f.getPropertyStatus("Distance2"))
        f.Type = "Distance and angle"
        self.assertIn("Hidden", f.getPropertyStatus("Distance2"))
        self.assertNotIn("Hidden", f.getPropertyStatus("ChamferAngle"))
        self.assertNotIn("Hidden", f.getPropertyStatus("FlipSide"))


class Persistence(DesignTest):
    def test_chamfer_type_survives_save(self):
        _, b = box(self.doc, 40, 10, 10)
        f = dress(self.doc, "Design::Chamfer", b, [front_top_edge(b)], Size=1, Type="Two distances", Distance2=3)
        name, body_name, v = f.Name, b.Name, b.Shape.Volume
        doc = save_and_reload(self.doc)
        f = doc.getObject(name)
        self.assertEqual(f.Type, "Two distances")
        self.assertNotIn("Hidden", f.getPropertyStatus("Distance2"))
        f.touch()
        doc.recompute()
        self.assertAlmostEqual(doc.getObject(body_name).Shape.Volume, v, delta=1e-6 * v)
