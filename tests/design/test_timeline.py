# SPDX-License-Identifier: LGPL-2.1-or-later
"""L7 Timeline: umsortieren mit Abhängigkeitsprüfung, Features auf demselben Body neu verketten, Gruppen, Undo"""
from design import *


def names(doc):
    return [o.Name for o in Design.timeline(doc)]


class Reorder(DesignTest):
    def test_independent_sketch_moves_earlier(self):
        _, b = box(self.doc, 20, 10, 5)
        loose = sketch(self.doc, rect(50, 0, 60, 10))
        Design.moveInTimeline(loose, 0)
        self.assertEqual(names(self.doc)[0], loose.Name)
        self.assertVolume(b, 1000)

    def test_feature_cannot_move_before_its_sketch(self):
        f, b = box(self.doc, 20, 10, 5)
        with self.assertRaises(ValueError) as e:
            Design.moveInTimeline(f, 0)
        self.assertIn("needs", str(e.exception))
        self.assertEqual(names(self.doc)[1], f.Name)

    def test_sketch_on_face_blocks_moving_its_feature_later(self):
        f, b = box(self.doc, 20, 10, 5)
        on_top = sketch(self.doc, circle(5, 5, 2), support=Design.stableRef(b, top_face(b)))
        with self.assertRaises(ValueError) as e:
            Design.moveInTimeline(f, len(names(self.doc)) - 1)
        self.assertIn("needed by", str(e.exception))

    def test_swap_two_features_on_one_body(self):
        f, b = box(self.doc, 40, 10, 10)
        edge = edge_where(b, lambda p: abs(p.y) < 1e-6 and abs(p.z - 10) < 1e-6)
        hole = sketch(self.doc, circle(30, 5, 2), App.Placement(V(0, 0, 10), App.Rotation()))  # vor der Rundung
        fillet = dress(self.doc, "Design::Fillet", b, [edge], Size=2)
        cut, _ = extrude(self.doc, hole, 10, op="Cut", bodies=[b], Reversed=True)
        expected = b.Shape.Volume
        Design.moveInTimeline(cut, names(self.doc).index(fillet.Name))  # Schnitt vor die Rundung
        self.assertNoErrors()
        order = names(self.doc)
        self.assertLess(order.index(cut.Name), order.index(fillet.Name))
        self.assertEqual(fillet.BaseFeatures[0].Name, cut.Name)  # die Rundung baut jetzt auf dem Schnitt auf
        self.assertEqual(b.Tip.Name, fillet.Name)
        self.assertVolume(b, expected)

    def test_move_last_feature_and_back(self):
        f, b = box(self.doc, 40, 10, 10)
        edge = edge_where(b, lambda p: abs(p.y) < 1e-6 and abs(p.z - 10) < 1e-6)
        fillet = dress(self.doc, "Design::Fillet", b, [edge], Size=2)
        chamfer = dress(self.doc, "Design::Chamfer", b, [edge_where(b, lambda p: abs(p.y - 10) < 1e-6 and abs(p.z - 10) < 1e-6)], Size=1)
        v = b.Shape.Volume
        Design.moveInTimeline(chamfer, names(self.doc).index(fillet.Name))
        Design.moveInTimeline(chamfer, len(names(self.doc)) - 1)
        self.assertNoErrors()
        self.assertVolume(b, v)
        self.assertEqual(b.Tip.Name, chamfer.Name)

    def test_undo_restores_order(self):
        _, b = box(self.doc, 20, 10, 5)
        loose = sketch(self.doc, rect(50, 0, 60, 10))
        before = names(self.doc)
        self.doc.UndoMode = 1
        self.doc.openTransaction("Move")
        Design.moveInTimeline(loose, 0)
        self.doc.commitTransaction()
        self.doc.undo()
        self.assertEqual(names(self.doc), before)


class Groups(DesignTest):
    def test_group_consecutive_entries(self):
        f, b = box(self.doc, 20, 10, 5)
        sk = Design.timeline(self.doc)[0]
        self.assertTrue(Design.setTimelineGroup([sk, f], "Base"))
        self.assertEqual(Design.timelineGroup(f), "Base")
        self.assertTrue(Design.setTimelineGroup([sk, f], ""))
        self.assertEqual(Design.timelineGroup(sk), "")

    def test_gaps_are_rejected(self):
        f, b = box(self.doc, 20, 10, 5)
        loose = sketch(self.doc, rect(50, 0, 60, 10))
        sk = Design.timeline(self.doc)[0]
        self.assertFalse(Design.setTimelineGroup([sk, loose], "Gap"))
        self.assertEqual(Design.timelineGroup(sk), "")

    def test_group_survives_save(self):
        f, b = box(self.doc, 20, 10, 5)
        Design.setTimelineGroup([f], "Base")
        name = f.Name
        doc = save_and_reload(self.doc)
        self.assertEqual(Design.timelineGroup(doc.getObject(name)), "Base")
