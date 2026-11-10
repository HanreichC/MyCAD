# SPDX-License-Identifier: LGPL-2.1-or-later
"""Grundlage: Design anlegen, Extrude, Join/Cut, Fillet, Rollback, Löschen, Speichern und Laden"""
from design import *


class Smoke(DesignTest):
    def test_extrude_new_body(self):
        _, body = box(self.doc, 20, 10, 5)
        self.assertVolume(body, 1000)
        self.assertNoErrors()

    def test_join_and_cut(self):
        _, body = box(self.doc, 20, 10, 5)
        top = sketch(self.doc, rect(0, 0, 10, 10), App.Placement(V(0, 0, 5), App.Rotation()))
        extrude(self.doc, top, 5, op="Join", bodies=[body])
        self.assertVolume(body, 1500)
        hole = sketch(self.doc, circle(15, 5, 2), App.Placement(V(0, 0, 5), App.Rotation()))
        extrude(self.doc, hole, 5, op="Cut", bodies=[body], Reversed=True)
        self.assertVolume(body, 1500 - PI * 4 * 5)
        self.assertNoErrors()

    def test_fillet_rollback_delete(self):
        _, body = box(self.doc, 20, 10, 5)
        edge = edge_where(body, lambda p: abs(p.x - 20) < 1e-6 and abs(p.y - 10) < 1e-6)
        fillet = dress(self.doc, "Design::Fillet", body, [edge], Size=2)
        filleted = 1000 - (4 - PI) * 5  # Quadrat 2x2 minus Viertelkreis, über die Höhe
        self.assertVolume(body, filleted)
        Design.setRollbackMarker(self.doc, 2)  # Skizze + Extrude aktiv
        self.assertVolume(body, 1000)
        Design.setRollbackMarker(self.doc, -1)
        self.assertVolume(body, filleted)
        Design.removeFromTimeline(fillet)
        self.doc.recompute()
        self.assertVolume(body, 1000)
        self.assertEqual(len(Design.timeline(self.doc)), 2)

    def test_save_and_reload(self):
        _, body = box(self.doc, 20, 10, 5)
        dress(self.doc, "Design::Chamfer", body, [top_face(body)], Size=1)
        before = body.Shape.Volume
        doc = save_and_reload(self.doc)
        body = [o for o in doc.Objects if o.TypeId == "Design::Body"][0]
        doc.recompute()
        self.assertVolume(body, before)
        self.assertNoErrors(doc)
