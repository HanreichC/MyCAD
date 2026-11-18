# SPDX-License-Identifier: LGPL-2.1-or-later
"""Aufräumliste B4: Wiederfinden nach Lage, wo es mehrdeutig ist.
- elementName: passen mehrere deckungsgleiche Elemente, entscheidet die Richtung (Normale, Lauf der Kante), nicht der
  erste Treffer.
- faceBefore: unter zwei Flächen in derselben Ebene die mit der größten Überdeckung, nicht die mit der nächsten Mitte
  (die Mitte eines Rahmens liegt im Loch).
- Teilung in drei Teile: ein Teil löschen, die anderen behalten ihre Form (vorher rückten sie auf, das übrige Teil
  hing am letzten Körper)."""
from design import *


def plane(w, h, at=V(0, 0, 0)):
    return Part.makePlane(w, h, at)


class ElementName(DesignTest):
    def test_congruent_faces_decided_by_normal(self):
        up = plane(10, 10)
        down = plane(10, 10).reversed()  # deckungsgleich, Normale nach unten
        both = Part.Compound([up, down])
        self.assertEqual(Design.elementName(both, plane(10, 10).reversed()), "Face2")
        self.assertEqual(Design.elementName(both, plane(10, 10)), "Face1")

    def test_same_face_is_found_by_identity(self):
        a, b = plane(10, 10), plane(10, 10)
        both = Part.Compound([a, b])
        self.assertEqual(Design.elementName(both, b), "Face2")  # dieselbe Fläche, auch wenn a gleich aussieht

    def test_congruent_edges_decided_by_direction(self):
        forward = Part.makeLine(V(0, 0, 0), V(10, 0, 0))
        back = Part.makeLine(V(10, 0, 0), V(0, 0, 0))
        both = Part.Compound([forward, back])
        self.assertEqual(Design.elementName(both, Part.makeLine(V(10, 0, 0), V(0, 0, 0))), "Edge2")

    def test_unique_match_and_no_match(self):
        box_ = Part.makeBox(10, 10, 10)
        i, top = [(i, f) for i, f in enumerate(box_.Faces) if abs(f.CenterOfMass.z - 10) < 1e-9][0]
        self.assertEqual(Design.elementName(box_, top), "Face%d" % (i + 1))
        self.assertEqual(Design.elementName(box_, plane(3, 3, V(50, 0, 0))), "")


class FaceBefore(DesignTest):
    def test_frame_wins_over_the_face_in_its_hole(self):
        frame = plane(50, 50).cut(plane(30, 30, V(10, 10, 0))).Faces[0]  # Rahmen, Mitte (25, 25) im Loch
        inside = plane(10, 10, V(20, 20, 0))  # liegt genau dort
        before = Part.Compound([frame, inside])
        # die Fläche des gelöschten Schritts: ein etwas dickerer Rahmen (z. B. ohne die Fase davor)
        gone = plane(50, 50).cut(plane(28, 28, V(11, 11, 0))).Faces[0]
        self.assertEqual(Design.faceBefore(before, gone), "Face1")

    def test_without_overlap_the_nearest(self):
        left, right = plane(10, 10), plane(10, 10, V(30, 0, 0))
        gone = plane(4, 4, V(18, 3, 0))  # zwischen beiden, näher an links
        self.assertEqual(Design.faceBefore(Part.Compound([left, right]), gone), "Face1")


class SplitThree(DesignTest):
    def test_deleting_one_piece_keeps_the_others(self):
        # U von oben: Steg unten (y 0..10), Schenkel links bis y 50, rechts bis y 40 (verschieden lang: ein Aufrücken
        # der Teile fiele an den Volumen auf); 10 hoch
        u = [V(0, 0, 0), V(40, 0, 0), V(40, 40, 0), V(30, 40, 0), V(30, 10, 0), V(10, 10, 0), V(10, 50, 0), V(0, 50, 0)]
        sk = sketch(self.doc, [Part.LineSegment(u[i], u[(i + 1) % 8]) for i in range(8)])
        _, body = extrude(self.doc, sk, 10)
        cut = self.doc.addObject("PartDesign::Plane", "Cut")
        Design.root(self.doc).addObject(cut)
        cut.Placement = App.Placement(V(0, 25, 0), App.Rotation(V(1, 0, 0), -90))  # Ebene y = 25 schneidet beide Schenkel
        self.doc.recompute()
        split = feature(self.doc, "Design::Split", Design.componentOf(body), Tool=(cut, [""]))
        Design.attachToBodies(split, [body])
        self.doc.recompute()
        self.assertEqual(split.Pieces, 3)
        pieces = [body]
        for i in range(2):
            p = self.doc.addObject("Design::Body", "Body")
            self.doc.getObject("Bodies").addObject(p)
            p.Tip = split
            pieces.append(p)
        split.Bodies = pieces
        self.doc.recompute()
        before = [round(p.Shape.Volume, 6) for p in pieces]
        self.assertAlmostEqual(sum(before), 40 * 10 * 10 + 10 * 40 * 10 + 10 * 30 * 10)
        self.assertEqual(len(set(before)), 3)  # drei verschiedene Teile
        keep, gone = pieces[2].Name, pieces[1].Name
        Design.removeFromTimeline(pieces[1])  # das mittlere Teil löschen
        self.doc.recompute()
        self.assertIsNone(self.doc.getObject(gone))
        self.assertAlmostEqual(body.Shape.Volume, before[0], places=6)
        self.assertAlmostEqual(self.doc.getObject(keep).Shape.Volume, before[2], places=6)  # nicht aufgerückt
        self.assertEqual(list(split.Dropped), [1])
        self.assertNoErrors()
