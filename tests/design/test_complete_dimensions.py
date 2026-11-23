# SPDX-License-Identifier: LGPL-2.1-or-later
"""Phase 11.6 "Was fehlt noch?": Design.completeDimensions ergänzt die fehlenden Maße nach Absicht, bis die Skizze voll
bestimmt ist. Mittig um den Ursprung -> symmetrisch, sonst Abstand zum Ursprung; Größen als Längen/Durchmesser. Die
Geometrie bleibt, wo sie war; doppelte oder widersprüchliche Maße entstehen nicht."""
import Sketcher

from design import *


def rectangle(sk, x0, y0, x1, y1):
    """Rechteck wie das Werkzeug: vier Linien, Ecken deckungsgleich, zwei waagrecht, zwei senkrecht (4 Freiheiten)"""
    pts = [V(x0, y0, 0), V(x1, y0, 0), V(x1, y1, 0), V(x0, y1, 0)]
    first = sk.GeometryCount
    for i in range(4):
        sk.addGeometry(Part.LineSegment(pts[i], pts[(i + 1) % 4]))
    for i in range(4):
        sk.addConstraint(Sketcher.Constraint("Coincident", first + i, 2, first + (i + 1) % 4, 1))
    sk.addConstraint(Sketcher.Constraint("Horizontal", first))
    sk.addConstraint(Sketcher.Constraint("Horizontal", first + 2))
    sk.addConstraint(Sketcher.Constraint("Vertical", first + 1))
    sk.addConstraint(Sketcher.Constraint("Vertical", first + 3))


def kinds(sk):
    return sorted(c.Type for c in sk.Constraints)


def corners(sk):
    return sorted((round(g.StartPoint.x, 6), round(g.StartPoint.y, 6)) for g in sk.Geometry)


class Complete(DesignTest):
    def new(self):
        return sketch(self.doc, [])

    def test_centred_rectangle_becomes_symmetric(self):
        sk = self.new()
        rectangle(sk, -10, -5, 10, 5)
        before = corners(sk)
        self.assertEqual(tuple(Design.completeDimensions(sk)), (3, 0))  # Symmetrie (2 Freiheiten), Breite, Höhe
        self.assertIn("Symmetric", kinds(sk))
        self.assertEqual(sorted(round(c.Value, 6) for c in sk.Constraints if c.Type == "Distance"), [10.0, 20.0])
        self.assertEqual(corners(sk), before)  # nichts verschoben

    def test_rectangle_elsewhere_gets_its_distance_to_the_origin(self):
        sk = self.new()
        rectangle(sk, 5, 5, 35, 25)
        before = corners(sk)
        self.assertEqual(tuple(Design.completeDimensions(sk)), (4, 0))
        self.assertNotIn("Symmetric", kinds(sk))
        self.assertEqual(sorted(round(c.Value, 6) for c in sk.Constraints if c.Type in ("DistanceX", "DistanceY")), [5.0, 5.0])
        self.assertEqual(corners(sk), before)

    def test_free_circle(self):
        sk = self.new()
        sk.addGeometry(Part.Circle(V(12, 7, 0), V(0, 0, 1), 3))
        self.assertEqual(tuple(Design.completeDimensions(sk)), (3, 0))
        self.assertIn("Diameter", kinds(sk))
        c = sk.Geometry[0]
        self.assertTrue(c.Center.isEqual(V(12, 7, 0), 1e-9) and abs(c.Radius - 3) < 1e-9)

    def test_tilted_line_ends_fully_defined(self):
        sk = self.new()
        sk.addGeometry(Part.LineSegment(V(1, 2, 0), V(9, 8, 0)))
        added, dof = Design.completeDimensions(sk)
        self.assertEqual(dof, 0)
        g = sk.Geometry[0]
        self.assertTrue(g.StartPoint.isEqual(V(1, 2, 0), 1e-9) and g.EndPoint.isEqual(V(9, 8, 0), 1e-9))

    def test_nothing_missing(self):
        sk = self.new()
        rectangle(sk, -10, -5, 10, 5)
        Design.completeDimensions(sk)
        count = len(sk.Constraints)
        self.assertEqual(tuple(Design.completeDimensions(sk)), (0, 0))
        self.assertEqual(len(sk.Constraints), count)

    def polygon(self, pts):
        """geschlossener Zug wie mit der Polylinie gezeichnet: nur die Ecken deckungsgleich"""
        sk = self.new()
        for i in range(len(pts)):
            sk.addGeometry(Part.LineSegment(pts[i], pts[(i + 1) % len(pts)]))
        for i in range(len(pts)):
            sk.addConstraint(Sketcher.Constraint("Coincident", i, 2, (i + 1) % len(pts), 1))
        return sk

    def test_tilted_rectangle_becomes_rectangular(self):
        """12.14: ein schräg gezeichnetes Rechteck bekommt rechte Winkel statt vier Winkelmaße"""
        a = math.radians(30)
        u, v = V(math.cos(a), math.sin(a), 0), V(-math.sin(a), math.cos(a), 0)
        sk = self.polygon([V(5, 5, 0), V(5, 5, 0) + u * 30, V(5, 5, 0) + u * 30 + v * 20, V(5, 5, 0) + v * 20])
        before = corners(sk)
        added, dof = Design.completeDimensions(sk)
        self.assertEqual(dof, 0)
        self.assertEqual(kinds(sk).count("Perpendicular"), 3)
        self.assertEqual(kinds(sk).count("Angle"), 1)  # nur noch die Lage des Ganzen
        self.assertEqual(corners(sk), before)

    def test_square_and_triangle_get_equal_sides(self):
        a = math.radians(15)
        u, v = V(math.cos(a), math.sin(a), 0), V(-math.sin(a), math.cos(a), 0)
        sk = self.polygon([V(0, 0, 0), u * 10, u * 10 + v * 10, v * 10])
        Design.completeDimensions(sk)
        self.assertEqual(kinds(sk).count("Equal"), 1)
        self.assertEqual(len([c for c in sk.Constraints if c.Type == "Distance"]), 1)  # eine Seite reicht
        sk = self.polygon([V(0, 0, 0), V(10, 0, 0), V(5, 10 * math.sqrt(3) / 2, 0)])
        added, dof = Design.completeDimensions(sk)
        self.assertEqual((kinds(sk).count("Equal"), dof), (2, 0))

    def test_irregular_shape_gets_no_shape_constraints(self):
        sk = self.polygon([V(0, 0, 0), V(13, 1, 0), V(17, 9, 0), V(2, 7, 0)])
        added, dof = Design.completeDimensions(sk)
        self.assertEqual(dof, 0)
        self.assertFalse({"Perpendicular", "Parallel", "Equal"} & set(kinds(sk)))

    def test_construction_lines_are_left_alone(self):
        sk = self.new()
        sk.addGeometry(Part.Circle(V(0, 0, 0), V(0, 0, 1), 4))
        sk.addGeometry(Part.LineSegment(V(-8, 0, 0), V(8, 0, 0)), True)  # Hilfslinie
        added, dof = Design.completeDimensions(sk)
        refs = {g for c in sk.Constraints for g in (c.First, c.Second) if g >= 0}
        self.assertEqual(refs, {0})  # nur der Kreis bekam Maße
        self.assertGreater(dof, 0)  # die Hilfslinie bleibt frei


if __name__ == "__main__":
    unittest.main()
