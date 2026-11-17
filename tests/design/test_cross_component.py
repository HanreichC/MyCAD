# SPDX-License-Identifier: LGPL-2.1-or-later
"""Phase 11.8 Werkzeuge über Komponentengrenzen: ein Cut aus dem Design schneidet auch Körper anderer Komponenten,
in deren eigener Lage (die Komponente kann verschoben sein). Speichern und Laden ohne Fehler, Verschieben der
Komponente rechnet richtig nach."""
from design import *

PI = 3.141592653589793


def two_blocks(doc):
    """Block 20 x 20 x 10 im Design; darüber eine Komponente, um z = 10 verschoben, mit einem gleichen Block"""
    _, low = box(doc, 20, 20, 10)
    comp = Design.newComponent(Design.root(doc))
    comp.Placement = App.Placement(V(0, 0, 10), App.Rotation())
    sk = sketch(doc, rect(0, 0, 20, 20), component=comp)
    _, high = extrude(doc, sk, 10)
    return low, comp, high


class CrossComponent(DesignTest):
    def hole_through_both(self, low, high):
        sk = sketch(self.doc, [Part.Circle(V(10, 10, 0), V(0, 0, 1), 3)], App.Placement(V(0, 0, 20), App.Rotation()))
        f, _ = extrude(self.doc, sk, 20, op="Cut", bodies=[low, high], Reversed=True)
        return f

    def test_cut_goes_through_the_body_of_another_component(self):
        low, comp, high = self.two_blocks()
        self.hole_through_both(low, high)
        hole = PI * 9 * 10
        self.assertVolume(low, 4000 - hole)
        self.assertVolume(high, 4000 - hole)
        self.assertNoErrors()

    def two_blocks(self):
        return two_blocks(self.doc)

    def test_moving_the_component_follows(self):
        low, comp, high = self.two_blocks()
        self.hole_through_both(low, high)
        comp.Placement = App.Placement(V(5, 0, 10), App.Rotation())  # Komponente 5 mm zur Seite
        self.doc.recompute()
        # die Bohrung bleibt im Design an ihrer Stelle: im verschobenen Block sitzt sie 5 mm weiter links
        bb = [f for f in high.Shape.Faces if f.Surface.TypeId == "Part::GeomCylinder"][0].BoundBox
        self.assertAlmostEqual(bb.Center.x, 5, places=6)  # x 10 im Design = x 5 in der Komponente
        self.assertVolume(high, 4000 - PI * 9 * 10)
        self.assertNoErrors()

    def test_survives_save(self):
        low, comp, high = self.two_blocks()
        self.hole_through_both(low, high)
        name = high.Name
        doc = save_and_reload(self.doc)
        self.assertAlmostEqual(doc.getObject(name).Shape.Volume, 4000 - PI * 9 * 10, places=3)
        self.assertNoErrors(doc)
