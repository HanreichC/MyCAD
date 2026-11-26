# SPDX-License-Identifier: LGPL-2.1-or-later
"""Chaotisch in alten Skizzen weiterarbeiten (ConceptKey, 2026-11-25): das Profil zweimal hintereinander teilen,
dabei Versätze (neue Inseln) hineinzeichnen; eine Skizze verliert ihre Fläche. Nichts davon darf den Körper still
verändern oder alle späteren Schritte anhalten."""
from design import *


class WildEdits(DesignTest):
    def test_split_twice_with_an_island(self):
        base = sketch(self.doc, rect(0, 0, 80, 50))
        ext, b = extrude(self.doc, base, 10)
        full = b.Shape.Volume
        base.addGeometry(Part.LineSegment(V(40, -10, 0), V(40, 60, 0)))  # erste Teilung
        self.doc.recompute()
        base.addGeometry(Part.LineSegment(V(-10, 25, 0), V(90, 25, 0)))  # die Teile noch einmal teilen
        base.addGeometry(Part.Circle(V(20, 12, 0), V(0, 0, 1), 3))       # neue Insel: wird ein Loch (wie Fusion)
        self.doc.recompute()
        self.assertNoErrors()
        self.assertEqual(ext.Warning, "")
        self.assertAlmostEqual(b.Shape.Volume, full - math.pi * 9 * 10, places=2)

    def test_a_sketch_that_loses_its_face_does_not_block(self):
        """Die Fläche gibt es in ihrer Ebene nicht mehr (Platte höher): Skizze bleibt an ihrem Platz mit Warnung, die
        Schritte danach rechnen weiter (vorher hielt der Fehler alles an)"""
        base = sketch(self.doc, rect(0, 0, 80, 50))
        ext, b = extrude(self.doc, base, 10)
        hole = sketch(self.doc, circle(20, 25, 5), support=(b, top_face(b)))
        cut, _ = extrude(self.doc, hole, 10, op="Cut", bodies=[b], Reversed=True)
        later = sketch(self.doc, circle(60, 25, 5))
        pin, _ = extrude(self.doc, later, 5, op="Join", bodies=[b])
        hole.AttachmentSupport = [(hole.AttachmentSupport[0][0], ("Face999",))]  # Name weg
        ext.Distance = 15  # und in der alten Ebene (z = 10) liegt keine Fläche mehr
        pin.Distance = 7
        self.doc.recompute()
        self.assertNotIn("Invalid", hole.State)
        self.assertTrue(hole.Warning.startswith("Face gone"), hole.Warning)
        self.assertAlmostEqual(hole.Placement.Base.z, 10, places=6)
        self.assertNotIn("Touched", pin.State, "steps after it still compute")

    def test_a_lost_face_is_found_again_by_its_position(self):
        """Flächenname weg (der Körper darunter hat sich geändert), die Fläche liegt aber noch in derselben Ebene: die
        Skizze hängt sich wieder an sie, genau an ihrem Platz, ohne Warnung (ConceptKey: Skizze001-004, Ebene)"""
        base = sketch(self.doc, rect(0, 0, 80, 50))
        ext, b = extrude(self.doc, base, 10)
        hole = sketch(self.doc, circle(20, 25, 5), support=(b, top_face(b)))
        cut, _ = extrude(self.doc, hole, 10, op="Cut", bodies=[b], Reversed=True)
        place = hole.Placement
        owner = hole.AttachmentSupport[0][0]
        hole.AttachmentSupport = [(owner, ("Face999",))]
        self.doc.recompute()
        self.assertEqual(hole.Warning if hasattr(hole, "Warning") else "", "")
        self.assertTrue(hole.Placement.isSame(place, 1e-7), (hole.Placement, place))
        sub = hole.AttachmentSupport[0][1][0]
        self.assertAlmostEqual(owner.Shape.getElement(sub).BoundBox.ZMax, 10, places=6)
        ext.Distance = 12  # folgt der Fläche wieder, wie vorher
        self.doc.recompute()
        self.assertAlmostEqual(hole.Placement.Base.z, 12, places=6)

    def test_a_join_inside_the_body_says_so(self):
        """Grundskizze liegt im Material (ConceptKey: Versatz 1 mm in "Skizze" unter dem Rand): Verbinden fügt nichts hinzu
        und sagt das, statt still nichts zu tun"""
        _, b = box(self.doc, 40, 20, 10)  # z 0..10: das Band ab z = 0 liegt ganz im Körper
        band = sketch(self.doc, rect(5, 5, 35, 6))
        join, _ = extrude(self.doc, band, 3, op="Join", bodies=[b])
        self.assertTrue(join.Warning.startswith("Adds nothing"), join.Warning)
        join.StartOffset = 10  # von der Oberseite aus
        self.doc.recompute()
        self.assertEqual(join.Warning, "")
        self.assertAlmostEqual(b.Shape.Volume, 40 * 20 * 10 + 30 * 1 * 3, places=3)

    def test_after_reopening_the_old_profile_is_still_known(self):
        """Die Flächen von vorher stehen in der Datei: nach dem Öffnen nimmt ein Kreis über den Profilrand nicht still das
        Stück außerhalb mit (ConceptKey: die erste Änderung nach dem Öffnen ließ die Grundplatte schrumpfen)"""
        import os, tempfile
        base = sketch(self.doc, rect(0, 0, 80, 50))
        base.addGeometry(Part.LineSegment(V(40, -10, 0), V(40, 60, 0)))  # einmal geteilt: die Flächen von vorher entstehen
        ext, b = extrude(self.doc, base, 10)
        self.doc.recompute()
        full = b.Shape.Volume
        path = os.path.join(tempfile.mkdtemp(), "reopen.FCStd")
        self.doc.saveAs(path)
        names = base.Name, b.Name
        App.closeDocument(self.doc.Name)
        self.doc = App.openDocument(path)
        base, b = (self.doc.getObject(n) for n in names)
        base.addGeometry(Part.Circle(V(80, 50, 0), V(0, 0, 1), 6))  # um die Ecke, ragt nach außen
        self.doc.recompute()
        self.assertAlmostEqual(b.Shape.Volume, full, places=3)


class BackFromImpossible(DesignTest):
    """Härtetest 2 (2026-11-26): ein Maß kurz unmöglich, dann zurück. Die Eckrundungen sitzen danach wieder an den
    Ecken, an denen sie gewählt wurden, ohne Warnung."""

    def plate(self):
        import Sketcher
        C = Sketcher.Constraint
        base = sketch(self.doc, rect(0, 0, 80, 50))
        for c in [C("Coincident", i, 2, (i + 1) % 4, 1) for i in range(4)] + [
                C("Horizontal", 0), C("Horizontal", 2), C("Vertical", 1), C("Vertical", 3), C("Coincident", 0, 1, -1, 1),
                C("DistanceX", 0, 1, 0, 2, 80), C("DistanceY", 1, 1, 1, 2, 50)]:
            base.addConstraint(c)
        self.doc.recompute()
        _, b = extrude(self.doc, base, 10)
        hole = sketch(self.doc, [], support=(b, top_face(b)))
        hole.addGeometry(Part.Circle(V(15, 15, 0), V(0, 0, 1), 3))
        hole.addConstraint(C("Radius", 0, 3)); hole.addConstraint(C("DistanceX", -1, 1, 0, 3, 15))
        hole.addConstraint(C("DistanceY", -1, 1, 0, 3, 15))
        self.doc.recompute()
        extrude(self.doc, hole, 10, op="Cut", bodies=[b], Reversed=True)
        self.fillets = [dress(self.doc, "Design::Fillet", b, [edge_where(
            b, lambda p, x=x, y=y: abs(p.x - x) < 1e-6 and abs(p.y - y) < 1e-6)], Size=4)
            for x, y in ((0, 0), (80, 0), (80, 50), (0, 50))]
        return base, hole, b

    def set(self, sk, kind, value):
        i = [k for k, c in enumerate(sk.Constraints) if c.Type == kind][0]
        sk.setDatum(i, App.Units.Quantity("%g mm" % value))
        self.doc.recompute()

    def assertAsBefore(self, b, volume):
        self.assertNoErrors()
        self.assertEqual([f.Warning for f in self.fillets], [""] * 4)
        self.assertAlmostEqual(b.Shape.Volume, volume, places=3)

    def test_a_hole_that_eats_the_corner_and_back(self):
        """die Ecke war weg, die Rundung musste raten (Warnung); kommt die Ecke zurück, gilt wieder die gewählte Kante"""
        base, hole, b = self.plate()
        volume = b.Shape.Volume
        self.set(hole, "Radius", 40)
        self.set(hole, "Radius", 3)
        self.assertAsBefore(b, volume)

    def test_a_plate_as_narrow_as_the_fillet_and_back(self):
        """alle Rundungen scheitern (Platte 4 mm breit); was sie sich gemerkt haben, bleibt vom letzten guten Stand"""
        base, hole, b = self.plate()
        volume = b.Shape.Volume
        self.set(base, "DistanceX", 4)
        self.set(base, "DistanceX", 80)
        self.assertAsBefore(b, volume)


class LooseLine(DesignTest):
    def test_a_loose_line_inside_a_profile_leaves_no_edge_on_the_body(self):
        """offene Linie mitten im Kreis eines Zapfens (berührt den Rand nicht): das Profil bleibt dasselbe, der Zapfen
        bekommt keine Phantomkante, die Fase an seinem Rand rechnet weiter (Härtetest 2, 2026-11-26)"""
        _, b = box(self.doc, 80, 50, 10)
        boss = sketch(self.doc, [], support=(b, top_face(b)))
        boss.addGeometry(Part.Circle(V(30, 28, 0), V(0, 0, 1), 8.6))
        self.doc.recompute()
        join, _ = extrude(self.doc, boss, 7, op="Join", bodies=[b])
        ring = edge_where(b, lambda p: abs(p.z - 17) < 1e-6 and abs(p.x - 30) < 1e-3)
        chamfer = dress(self.doc, "Design::Chamfer", b, [ring], Size=1.41)
        volume, edges = b.Shape.Volume, len(join.Shape.Edges)
        boss.addGeometry(Part.LineSegment(V(22, 27.54, 0), V(38, 26.6, 0)))
        self.doc.recompute()
        self.assertNoErrors()
        self.assertEqual(len(join.Shape.Edges), edges)
        self.assertEqual(chamfer.Warning, "")
        self.assertAlmostEqual(b.Shape.Volume, volume, places=3)


class ProjectedEdge(BackFromImpossible):
    @unittest.expectedFailure  # offen (PLAN 4.8): ein erster Versuch am 26.11. störte Zurückrollen und Unterdrücken
    def test_a_projected_edge_that_was_lost_for_a_moment_is_linked_again(self):
        """Schlitz mit Maß zur projizierten rechten Kante. Kreis um eine Ecke der Grundskizze, Tiefe ändern und zurück,
        Kreis weg: zwischendurch findet die Skizze die Kante nicht. Danach hängt die Linie wieder an ihr, der Schlitz
        folgt der Breite (vorher löschte die Skizze die Verknüpfung, die Linie fror für immer ein; Härtetest 2)"""
        import Sketcher
        C = Sketcher.Constraint
        base, hole, b = self.plate()
        top = face_where(b, lambda c, f: abs(c.z - 10) < 1e-6 and f.Area > 100)
        slot = sketch(self.doc, [], support=(b, top))
        slot.addExternal(b.Name, edge_where(b, lambda p: abs(p.x - 80) < 1e-6 and abs(p.z - 10) < 1e-6))
        for g in rect(68, 10, 74, 20):
            slot.addGeometry(g)
        for c in [C("Coincident", i, 2, (i + 1) % 4, 1) for i in range(4)] + [
                C("Horizontal", 0), C("Horizontal", 2), C("Vertical", 1), C("Vertical", 3),
                C("DistanceX", 0, 1, 0, 2, 6), C("DistanceY", 1, 1, 1, 2, 10), C("DistanceY", -1, 1, 0, 1, 10),
                C("DistanceX", 1, 1, -3, 1, 6)]:
            slot.addConstraint(c)
        self.doc.recompute()
        extrude(self.doc, slot, 3, op="Cut", bodies=[b], Reversed=True)
        volume = b.Shape.Volume
        i = base.addGeometry(Part.Circle(V(0, 50, 0), V(0, 0, 1), 3.8))
        self.doc.recompute()
        self.set(base, "DistanceY", 65)
        self.set(base, "DistanceY", 50)
        base.delGeometry(i)
        self.doc.recompute()
        self.assertNoErrors()  # die Rundung an dieser Ecke darf noch "bitte prüfen" melden (offen, PLAN 4.8)
        self.assertAlmostEqual(b.Shape.Volume, volume, places=3)
        self.assertEqual(len(slot.ExternalGeometry), 1)
        for f in self.fillets:
            f.Warning = ""
        self.set(base, "DistanceX", 100)  # der Schlitz wandert mit: 6 mm vom rechten Rand
        self.assertNoErrors()
        self.assertAlmostEqual(max(v.X for v in slot.Shape.Vertexes), 94, places=4)

    def test_a_line_that_crosses_the_circle_once_does_not_split_its_rim(self):
        """ein Ende im Kreis des Zapfens, eins draußen: der Kreis bleibt eine Kante (vorher zwei Bögen, die Fase am Rand
        fand nur noch einen; Härtetest 2, 2026-11-26)"""
        _, b = box(self.doc, 80, 50, 10)
        boss = sketch(self.doc, [], support=(b, top_face(b)))
        boss.addGeometry(Part.Circle(V(30, 28, 0), V(0, 0, 1), 9))
        self.doc.recompute()
        join, _ = extrude(self.doc, boss, 7, op="Join", bodies=[b])
        ring = edge_where(b, lambda p: abs(p.z - 17) < 1e-6 and abs(p.x - 30) < 1e-3)
        chamfer = dress(self.doc, "Design::Chamfer", b, [ring], Size=1.5)
        volume, edges = b.Shape.Volume, len(join.Shape.Edges)
        boss.addGeometry(Part.LineSegment(V(22, 34.54, 0), V(38, 31.8, 0)))
        self.doc.recompute()
        self.assertNoErrors()
        self.assertEqual(len(join.Shape.Edges), edges)
        self.assertEqual(chamfer.Warning, "")
        self.assertAlmostEqual(b.Shape.Volume, volume, places=3)


class MoveSteps(DesignTest):
    """Umsortieren in der Zeitleiste (Härtetest 2, 2026-11-26): die Kette der Körperzustände wird neu verbunden und
    zählte deshalb nicht als Abhängigkeit. Ein Schritt braucht trotzdem seinen Körper und die Kanten, an denen er sitzt."""

    def part(self):
        _, b = box(self.doc, 80, 50, 10)
        hole = sketch(self.doc, circle(15, 15, 3), support=(b, top_face(b)))
        cut, _ = extrude(self.doc, hole, 10, op="Cut", bodies=[b], Reversed=True)
        fillet = dress(self.doc, "Design::Fillet", b, [edge_where(b, lambda p: abs(p.x) < 1e-6 and abs(p.y) < 1e-6)], Size=4)
        boss = sketch(self.doc, circle(50, 25, 8), support=(b, face_where(b, lambda c, f: abs(c.z - 10) < 1e-6 and f.Area > 100)))
        join, _ = extrude(self.doc, boss, 6, op="Join", bodies=[b])
        ring = edge_where(b, lambda p: abs(p.z - 16) < 1e-6 and abs(p.x - 50) < 1e-3)
        chamfer = dress(self.doc, "Design::Chamfer", b, [ring], Size=1)
        return b, cut, fillet, join, chamfer

    def at(self, f):
        return Design.timeline(self.doc).index(f)

    def test_a_fillet_cannot_go_before_the_first_step_of_its_body(self):
        b, cut, fillet, join, chamfer = self.part()
        volume = b.Shape.Volume
        with self.assertRaisesRegex(ValueError, "It needs"):
            Design.moveInTimeline(fillet, 0)
        self.assertAlmostEqual(b.Shape.Volume, volume, places=6)

    def test_a_chamfer_cannot_go_before_the_boss_it_sits_on(self):
        b, cut, fillet, join, chamfer = self.part()
        with self.assertRaisesRegex(ValueError, "It needs " + join.Label):
            Design.moveInTimeline(chamfer, self.at(fillet))

    def test_the_boss_cannot_go_behind_the_chamfer_on_its_rim(self):
        b, cut, fillet, join, chamfer = self.part()
        with self.assertRaisesRegex(ValueError, "It is needed by " + chamfer.Label):
            Design.moveInTimeline(join, self.at(chamfer))

    def test_a_fillet_may_go_before_a_hole_that_leaves_its_edge_alone(self):
        b, cut, fillet, join, chamfer = self.part()
        volume = b.Shape.Volume
        Design.moveInTimeline(fillet, self.at(cut))
        self.doc.recompute()
        self.assertNoErrors()
        self.assertLess(self.at(fillet), self.at(cut))
        self.assertAlmostEqual(b.Shape.Volume, volume, places=3)
