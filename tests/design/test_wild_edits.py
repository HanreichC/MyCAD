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
