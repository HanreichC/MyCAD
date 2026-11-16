# SPDX-License-Identifier: LGPL-2.1-or-later
"""Phase 11.4 Messen ohne Werkzeug: Design.quickMeasure misst zwei Elemente zueinander (Abstand, Winkel) oder einen Kreis
allein (Durchmesser). Fehlende Werte fehlen im Ergebnis; anchor ist der Punkt, an dem die Anzeige steht."""
from design import *

BOX = Part.makeBox(20, 10, 5)


def face(pred):
    return next(f for f in BOX.Faces if pred(f.CenterOfMass, f))


def edge(pred):
    return next(e for e in BOX.Edges if pred(e.CenterOfMass, e))


TOP = face(lambda c, f: abs(c.z - 5) < 1e-9)
BOTTOM = face(lambda c, f: abs(c.z) < 1e-9)
FRONT = face(lambda c, f: abs(c.y) < 1e-9)
X_EDGE = edge(lambda c, e: abs(c.y) < 1e-9 and abs(c.z) < 1e-9)  # entlang x bei y = 0, z = 0
Y_EDGE_TOP = edge(lambda c, e: abs(c.x - 20) < 1e-9 and abs(c.z - 5) < 1e-9)  # entlang y bei x = 20, z = 5
Z_EDGE = edge(lambda c, e: abs(c.x) < 1e-9 and abs(c.y) < 1e-9)  # senkrecht bei x = 0, y = 0


class QuickMeasure(unittest.TestCase):
    def test_parallel_faces(self):
        m = Design.quickMeasure(TOP, BOTTOM)
        self.assertAlmostEqual(m["distance"], 5)
        self.assertAlmostEqual(m["angle"], 0)
        self.assertNotIn("diameter", m)
        self.assertTrue(m["anchor"].isEqual(V(10, 5, 2.5), 1e-6), m["anchor"])  # Mitte, nicht eine der Ecken

    def test_touching_faces_have_an_angle(self):
        m = Design.quickMeasure(TOP, FRONT)
        self.assertAlmostEqual(m["distance"], 0)
        self.assertAlmostEqual(m["angle"], 90)

    def test_skew_edges(self):
        m = Design.quickMeasure(X_EDGE, Y_EDGE_TOP)
        self.assertAlmostEqual(m["distance"], 5)  # von (20, 0, 0) nach (20, 0, 5)
        self.assertAlmostEqual(m["angle"], 90)
        self.assertTrue(m["anchor"].isEqual(V(20, 0, 2.5), 1e-6), m["anchor"])

    def test_edge_to_face_is_the_angle_to_the_face(self):
        self.assertAlmostEqual(Design.quickMeasure(Z_EDGE, TOP)["angle"], 90)  # senkrecht auf der Fläche
        self.assertAlmostEqual(Design.quickMeasure(X_EDGE, TOP)["angle"], 0)  # liegt parallel zur Fläche
        self.assertAlmostEqual(Design.quickMeasure(TOP, X_EDGE)["angle"], 0)  # Reihenfolge egal
        tilted = Part.makeLine(V(0, 0, 0), V(10, 0, 10))
        self.assertAlmostEqual(Design.quickMeasure(tilted, BOTTOM)["angle"], 45)

    def test_points(self):
        m = Design.quickMeasure(Part.Vertex(V(0, 0, 0)), Part.Vertex(V(3, 4, 0)))
        self.assertAlmostEqual(m["distance"], 5)
        self.assertNotIn("angle", m)

    def test_circle_alone_gives_its_diameter(self):
        cyl = Part.makeCylinder(3, 10)
        side = next(f for f in cyl.Faces if f.Surface.TypeId == "Part::GeomCylinder")
        rim = next(e for e in cyl.Edges if e.Curve.TypeId == "Part::GeomCircle")
        for element in (side, rim):
            m = Design.quickMeasure(element)
            self.assertAlmostEqual(m["diameter"], 6)
            self.assertAlmostEqual(cyl.distToShape(Part.Vertex(m["anchor"]))[0], 0, places=6)  # Anzeige am Kreis

    def test_nothing_to_show(self):
        for args in ((X_EDGE,), (TOP,), (TOP, BOTTOM, FRONT), ()):
            self.assertEqual(set(Design.quickMeasure(*args)), {"anchor"}, args)

    def test_only_shapes(self):
        with self.assertRaises(TypeError):
            Design.quickMeasure("Face1")


if __name__ == "__main__":
    unittest.main()
