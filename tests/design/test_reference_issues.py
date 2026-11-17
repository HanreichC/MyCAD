# SPDX-License-Identifier: LGPL-2.1-or-later
"""Phase 11.11 Bezüge, die sich selbst prüfen: Design.referenceIssues findet an einer Stelle alles, was nicht sicher
zugeordnet ist: Warnungen der Schritte und jeden Verweis auf ein Element, das nach einer Änderung fehlt, gleich in
welcher Eigenschaft."""
from design import *


def side_face(body, x):
    return face_where(body, lambda c, f: abs(c.x - x) < 1e-6)


class References(DesignTest):
    def holder(self, body, face):
        h = self.doc.addObject("App::FeaturePython", "Holder")
        Design.root(self.doc).addObject(h)
        h.addProperty("App::PropertyLinkSub", "Ref")
        h.Ref = (body, [face])
        self.doc.recompute()
        return h

    def test_nothing_uncertain_in_a_fresh_design(self):
        _, b = box(self.doc, 20, 20, 10)
        self.holder(b, side_face(b, 20))
        self.assertEqual(Design.referenceIssues(self.doc), [])

    def test_a_reference_to_a_face_that_went_away_is_listed(self):
        f, b = box(self.doc, 20, 20, 10)
        h = self.holder(b, side_face(b, 20))
        sk = f.Profile[0].Sketch
        # Rechteck -> Dreieck ohne die Seite bei x = 20: die Fläche gibt es nicht mehr
        for i in reversed(range(sk.GeometryCount)):
            sk.delGeometry(i)
        for a, c in ((V(0, 0, 0), V(20, 0, 0)), (V(20, 0, 0), V(0, 20, 0)), (V(0, 20, 0), V(0, 0, 0))):
            sk.addGeometry(Part.LineSegment(a, c))
        self.doc.recompute()
        issues = [i for i in Design.referenceIssues(self.doc) if i[0] == h.Name]
        self.assertEqual(len(issues), 1, Design.referenceIssues(self.doc))
        name, prop, element, text, warning = issues[0]
        self.assertEqual(prop, "Ref")
        self.assertFalse(warning)
        self.assertIn("Lost reference", text)

    def test_warnings_of_steps_are_listed_and_confirming_clears_them(self):
        f, b = box(self.doc, 20, 20, 10)
        f.Warning = "The model changed under this step; check that it still uses the right edges or faces: Edge3"
        issues = Design.referenceIssues(self.doc)
        self.assertEqual([(i[0], i[4]) for i in issues], [(f.Name, True)])
        f.Warning = ""  # "Looks Right"
        self.assertEqual(Design.referenceIssues(self.doc), [])
