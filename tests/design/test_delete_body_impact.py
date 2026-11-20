# SPDX-License-Identifier: LGPL-2.1-or-later
"""Vorschau beim Löschen eines ganzen Körpers (11.2 für Körper): eigene Schritte gehen still mit; genannt wird, was
darüber hinaus geschieht. Kopien (Spiegeln) und ein Kombinieren mit ihm als einzigem Werkzeug gehen mit, eine Skizze
eines anderen Körpers auf seiner Fläche verliert sie, eine eigene Skizze zählt nicht. Danach geschieht beim Löschen
genau das."""
from design import *


def names(objs):
    return sorted(o.Name for o in objs)


class DeleteBody(DesignTest):
    def test_a_lone_body_names_nothing(self):
        _, a = box(self.doc, 20, 20, 10)
        cut = sketch(self.doc, [Part.Circle(V(10, 10, 0), V(0, 0, 1), 3)], support=(a, top_face(a)))
        extrude(self.doc, cut, -5, op="Cut", bodies=[a])  # eigene Skizze auf eigener Fläche: bleibt, nicht genannt
        self.assertEqual(Design.deletionImpact(a), {"along": [], "sketches": [], "broken": []})

    def test_sketch_of_another_body_on_its_face_loses_it(self):
        _, a = box(self.doc, 20, 20, 10)
        sk = sketch(self.doc, rect(5, 5, 15, 15), support=(a, top_face(a)))
        _, b = extrude(self.doc, sk, 5)  # neuer Körper B aus einer Skizze auf A
        impact = Design.deletionImpact(a)
        self.assertEqual(impact["sketches"], [sk.Name])
        self.assertEqual(impact["along"], [])

    def test_mirror_copy_goes_along(self):
        _, a = box(self.doc, 20, 20, 10)
        m = feature(self.doc, "Design::Mirror", Design.componentOf(a))
        copy = self.doc.addObject("Design::Body", "Body")
        self.doc.getObject("Bodies").addObject(copy)
        copy.Tip = m
        m.SourceBodies, m.SourceFeatures, m.Bodies, m.Plane = [a], [a.Tip], [copy], "YZ"
        self.doc.recompute()
        name = copy.Name
        self.assertEqual(Design.deletionImpact(a)["along"], [name])
        Design.removeFromTimeline(a)  # und so kommt es auch
        self.doc.recompute()
        self.assertIsNone(self.doc.getObject(name))

    def test_combine_with_it_as_only_tool_goes_along(self):
        _, target = box(self.doc, 20, 20, 10)
        _, tool = box(self.doc, 5, 5, 20, at=(2, 2))
        c = feature(self.doc, "Design::Combine", Design.componentOf(target), ToolBodies=[tool], ToolFeatures=[tool.Tip])
        c.Operation = "Cut"
        Design.attachToBodies(c, [target])
        self.doc.recompute()
        self.assertVolume(target, 4000 - 25 * 10)
        name = c.Name
        self.assertEqual(Design.deletionImpact(tool)["along"], [name])
        Design.removeFromTimeline(tool)
        self.doc.recompute()
        self.assertIsNone(self.doc.getObject(name))
        self.assertVolume(target, 4000)  # der Schnitt ist mit weg, wie angekündigt

    def test_reference_from_another_step_breaks(self):
        _, a = box(self.doc, 20, 20, 10)
        sk = sketch(self.doc, [Part.Circle(V(40, 10, 0), V(0, 0, 1), 3)])
        f, b = extrude(self.doc, sk, 5)
        f.Extent = "To Object"
        f.ToObject = (a, [top_face(a)])  # B wächst bis zur Oberseite von A
        self.doc.recompute()
        self.assertEqual(Design.deletionImpact(a)["broken"], [f.Name])
