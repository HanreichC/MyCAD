# SPDX-License-Identifier: LGPL-2.1-or-later
"""10.3 Idee 2: Welche Maße treiben eine Fläche? Ändern rechnet neu; Parameter bleiben Parameter"""
from design import *


def dims(body, face):
    return Design.drivingDimensions(body, face)


def labels(body, face):
    return sorted(d["label"] for d in dims(body, face))


def constrained_box(doc, w=20, h=10, z=5):
    """Quader, dessen Skizze Breite und Höhe als Bemaßung hat (wie nach dem Bemaßen)"""
    sk = sketch(doc, rect(0, 0, w, h))
    for i in range(4):  # geschlossenes Rechteck: Ecken verbunden, Seiten waagrecht/senkrecht, Ursprung fest
        sk.addConstraint(Sketcher.Constraint("Coincident", i, 2, (i + 1) % 4, 1))
    sk.addConstraint(Sketcher.Constraint("Horizontal", 0)); sk.addConstraint(Sketcher.Constraint("Horizontal", 2))
    sk.addConstraint(Sketcher.Constraint("Vertical", 1)); sk.addConstraint(Sketcher.Constraint("Vertical", 3))
    sk.addConstraint(Sketcher.Constraint("Coincident", 0, 1, -1, 1))
    first = sk.addConstraint(Sketcher.Constraint("DistanceX", 0, 1, 0, 2, w))  # untere Linie: Breite
    sk.addConstraint(Sketcher.Constraint("DistanceY", 1, 1, 1, 2, h))  # rechte Linie: Höhe
    sk.renameConstraint(first, "Breite")
    doc.recompute()
    return sk, *extrude(doc, sk, z)


class Find(DesignTest):
    def test_top_face_is_the_extrude_distance(self):
        _, f, b = constrained_box(self.doc)
        (d,) = dims(b, top_face(b))
        self.assertEqual((d["owner"].Name, d["path"], d["value"]), (f.Name, "Distance", 5))

    def test_bottom_face_has_no_distance(self):
        _, f, b = constrained_box(self.doc)
        bottom = face_where(b, lambda c, fc: abs(c.z) < 1e-6)
        self.assertEqual(dims(b, bottom), [])

    def test_side_face_is_the_sketch_dimension(self):
        sk, f, b = constrained_box(self.doc)
        front = face_where(b, lambda c, fc: abs(c.y) < 1e-6)  # aus der unteren Skizzenlinie gezogen
        (d,) = dims(b, front)
        self.assertEqual((d["owner"].Name, d["path"], d["label"], d["value"]), (sk.Name, "Constraints[9]", "Breite", 20))

    def test_hole_wall_is_the_diameter(self):
        _, f, b = constrained_box(self.doc)
        pts = sketch(self.doc, [Part.Point(V(10, 5, 0))], App.Placement(V(0, 0, 5), App.Rotation()))
        h = feature(self.doc, "Design::Hole", Sketch=pts, Diameter=4, Depth=3)
        Design.attachToBodies(h, [b])
        self.doc.recompute()
        wall = face_where(b, lambda c, fc: fc.Surface.TypeId == "Part::GeomCylinder")
        self.assertEqual(labels(b, wall), ["Depth", "Diameter"])
        # die Deckfläche mit Loch gehört weiter zum Extrude
        (d,) = dims(b, top_face(b))
        self.assertEqual(d["owner"].Name, f.Name)

    def test_fillet_face_is_the_radius(self):
        _, f, b = constrained_box(self.doc)
        edge = edge_where(b, lambda p: abs(p.y) < 1e-6 and abs(p.z - 5) < 1e-6)
        dress(self.doc, "Design::Fillet", b, [edge], Size=1.5)
        round_face = face_where(b, lambda c, fc: fc.Surface.TypeId != "Part::GeomPlane")
        (d,) = dims(b, round_face)
        self.assertEqual((d["label"], d["value"]), ("Radius", 1.5))

    def test_primitive_box(self):
        f = feature(self.doc, "Design::Primitive", Type="Box", Length=10, Width=8, Height=6)
        b = new_body(f)
        self.doc.recompute()
        self.assertEqual(labels(b, top_face(b)), ["Height", "Length", "Width"])

    def test_still_found_after_inserting_a_feature_before(self):
        _, f, b = constrained_box(self.doc)
        edge = edge_where(b, lambda p: abs(p.x) < 1e-6 and abs(p.y) < 1e-6)
        dress(self.doc, "Design::Chamfer", b, [edge], Size=1)
        (d,) = dims(b, top_face(b))
        self.assertEqual(d["owner"].Name, f.Name)


class Change(DesignTest):
    def test_set_extrude_distance(self):
        _, f, b = constrained_box(self.doc)
        Design.setDrivingDimension(f, "Distance", 8)
        self.assertVolume(b, 20 * 10 * 8)

    def test_set_sketch_dimension(self):
        sk, f, b = constrained_box(self.doc)
        Design.setDrivingDimension(sk, "Constraints[9]", 30)
        self.assertVolume(b, 30 * 10 * 5)

    def test_parameter_changes_not_the_formula(self):
        _, f, b = constrained_box(self.doc)
        params = self.doc.addObject("App::VarSet", "Parameters")
        params.Label = "Parameters"
        params.addProperty("App::PropertyQuantity", "Hoehe", "Parameters")
        params.setExpression("Hoehe", "5 mm")
        f.setExpression("Distance", "Parameters.Hoehe")
        self.doc.recompute()
        (d,) = dims(b, top_face(b))
        self.assertIn("Hoehe", d["expression"])
        Design.setDrivingDimension(f, "Distance", 12)
        self.assertIn("Hoehe", f.ExpressionEngine[0][1])  # die Formel bleibt
        self.assertAlmostEqual(params.Hoehe.Value, 12, places=6)
        self.assertVolume(b, 20 * 10 * 12)

    def test_formula_explains(self):
        _, f, b = constrained_box(self.doc)
        f.setExpression("Distance", "2 mm * 3")
        self.doc.recompute()
        with self.assertRaises(ValueError) as e:
            Design.setDrivingDimension(f, "Distance", 12)
        self.assertIn("formula", str(e.exception))
