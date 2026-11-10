# SPDX-License-Identifier: LGPL-2.1-or-later
"""L4 Freie Bezüge: Spiegeln an Ebene/Fläche, Muster entlang Kante, um beliebige Achse, entlang Pfad, Drehen um Kante"""
from design import *


def copies_of(doc, type_id, bodies, **props):
    """Spiegeln/Körper-Muster wie die Oberfläche: je Quelle ein neuer Body mit dem Ergebnis"""
    f = feature(doc, type_id, Design.componentOf(bodies[0]))
    created = []
    for b in bodies:
        c = doc.addObject("Design::Body", "Body")
        doc.getObject("Bodies").addObject(c)
        c.Tip = f
        created.append(c)
    f.SourceBodies = bodies
    f.SourceFeatures = [b.Tip for b in bodies]
    f.Bodies = created
    if type_id == "Design::Pattern":
        f.Operation = "New Body"
    for k, v in props.items():
        setattr(f, k, v)
    doc.recompute()
    return f, created


def helper(doc, shape, name="Ref"):
    """Fremdes Objekt als Bezug (Ebene, Kante, Fläche)"""
    o = doc.addObject("Part::Feature", name)
    o.Shape = shape
    doc.recompute()
    return o


def centers(shape):
    return sorted((round(s.CenterOfMass.x, 4), round(s.CenterOfMass.y, 4), round(s.CenterOfMass.z, 4)) for s in shape.Solids)


class MirrorReference(DesignTest):
    def test_mirror_at_body_face(self):
        _, b = box(self.doc, 10, 10, 10)
        face = face_where(b, lambda c, f: abs(c.x - 10) < 1e-6)
        f, (copy,) = copies_of(self.doc, "Design::Mirror", [b], PlaneReference=Design.stableRef(b, face))
        self.assertNoErrors()
        self.assertEqual(centers(copy.Shape), [(15, 5, 5)])
        self.assertIn("ReadOnly", f.getPropertyStatus("Plane"))

    def test_mirror_at_slanted_plane(self):
        _, b = box(self.doc, 10, 10, 10)
        plane = helper(self.doc, Part.makePlane(100, 100, V(0, 0, -50), V(1, 1, 0)))  # Ebene x + y = 0
        f, (copy,) = copies_of(self.doc, "Design::Mirror", [b], PlaneReference=(plane, []))
        self.assertNoErrors()
        self.assertEqual(centers(copy.Shape), [(-5, -5, 5)])

    def test_mirror_needs_a_plane(self):
        _, b = box(self.doc, 10, 10, 10)
        edge = helper(self.doc, Part.LineSegment(V(0, 0, 0), V(0, 0, 10)).toShape())
        f, _ = copies_of(self.doc, "Design::Mirror", [b], PlaneReference=(edge, []))
        self.assertTrue(failed(f))
        self.assertIn("plane", f.getStatusString())

    def test_origin_plane_still_works(self):
        _, b = box(self.doc, 10, 10, 10)
        f, (copy,) = copies_of(self.doc, "Design::Mirror", [b], Plane="YZ")
        self.assertEqual(centers(copy.Shape), [(-5, 5, 5)])


class PatternReference(DesignTest):
    def test_rectangular_along_slanted_edge(self):
        _, b = box(self.doc, 4, 4, 4)
        a = math.radians(30)
        edge = helper(self.doc, Part.LineSegment(V(0, 0, 0), V(math.cos(a), math.sin(a), 0)).toShape())
        f, (copy,) = copies_of(self.doc, "Design::Pattern", [b], Direction1Reference=(edge, []), Count1=3, Spacing1=20)
        self.assertNoErrors()
        expected = sorted((round(2 + 20 * k * math.cos(a), 4), round(2 + 20 * k * math.sin(a), 4), 2.0) for k in (1, 2))
        self.assertEqual(centers(copy.Shape), expected)
        self.assertIn("ReadOnly", f.getPropertyStatus("Direction1"))

    def test_direction_from_face_normal(self):
        _, b = box(self.doc, 4, 4, 4)
        top = Design.stableRef(b, top_face(b))
        f, (copy,) = copies_of(self.doc, "Design::Pattern", [b], Direction1Reference=top, Count1=2, Spacing1=10)
        self.assertEqual(centers(copy.Shape), [(2, 2, 12)])

    def test_circular_around_off_origin_cylinder(self):
        _, b = box(self.doc, 4, 4, 4, at=(38, -2))
        cyl = helper(self.doc, Part.makeCylinder(2, 10, V(30, 0, 0)))
        face = [i for i, fc in enumerate(cyl.Shape.Faces, 1) if fc.Surface.TypeId == "Part::GeomCylinder"][0]
        f, (copy,) = copies_of(self.doc, "Design::Pattern", [b], Type="Circular", AxisReference=(cyl, ["Face%d" % face]),
                               Count1=4, Angle=360)
        self.assertNoErrors()
        self.assertEqual(centers(copy.Shape), sorted([(30, 10, 2), (20, 0, 2), (30, -10, 2)]))

    def test_along_straight_path(self):
        _, b = box(self.doc, 2, 2, 2, at=(-1, -1))
        path = helper(self.doc, Part.LineSegment(V(0, 0, 0), V(0, 50, 0)).toShape())
        f, (copy,) = copies_of(self.doc, "Design::Pattern", [b], Type="Path", Path=(path, []), Count1=4, Spacing1=10)
        self.assertNoErrors()
        self.assertEqual(centers(copy.Shape), [(0, 10, 1), (0, 20, 1), (0, 30, 1)])

    def test_along_arc_follows_path(self):
        _, b = box(self.doc, 2, 0.5, 1, at=(19, -0.25))  # schmaler Stab quer zur Bahn bei (20, 0)
        arc = helper(self.doc, Part.ArcOfCircle(Part.Circle(V(0, 0, 0), V(0, 0, 1), 20), 0, math.pi / 2).toShape())
        quarter = 20 * math.pi / 2
        f, (copy,) = copies_of(self.doc, "Design::Pattern", [b], Type="Path", Path=(arc, []), Count1=2,
                               Spacing1=quarter, FollowPath=True)
        self.assertNoErrors()
        (cx, cy, _), = centers(copy.Shape)
        self.assertAlmostEqual(cx, 0, places=3)
        self.assertAlmostEqual(cy, 20, places=3)
        bb = copy.Shape.BoundBox  # mitgedreht: jetzt entlang Y lang, nicht mehr entlang X
        self.assertAlmostEqual(bb.YLength, 2, places=3)
        self.assertAlmostEqual(bb.XLength, 0.5, places=3)

    def test_path_too_short_explains(self):
        _, b = box(self.doc, 2, 2, 2)
        path = helper(self.doc, Part.LineSegment(V(0, 0, 0), V(0, 15, 0)).toShape())
        f, _ = copies_of(self.doc, "Design::Pattern", [b], Type="Path", Path=(path, []), Count1=4, Spacing1=10)
        self.assertTrue(failed(f))
        self.assertIn("do not fit", f.getStatusString())

    def test_visibility_follows_type(self):
        _, b = box(self.doc, 2, 2, 2)
        f, _ = copies_of(self.doc, "Design::Pattern", [b], Count1=2)
        self.assertNotIn("Hidden", f.getPropertyStatus("Direction1Reference"))
        self.assertIn("Hidden", f.getPropertyStatus("Path"))
        f.Type = "Path"
        self.assertIn("Hidden", f.getPropertyStatus("Direction1Reference"))
        self.assertNotIn("Hidden", f.getPropertyStatus("Path"))

    def test_feature_pattern_with_reference(self):
        _, b = box(self.doc, 40, 10, 5)
        hole = sketch(self.doc, circle(5, 5, 2), App.Placement(V(0, 0, 5), App.Rotation()))
        cut, _ = extrude(self.doc, hole, 5, op="Cut", bodies=[b], Reversed=True)
        edge = helper(self.doc, Part.LineSegment(V(0, 0, 0), V(1, 0, 0)).toShape())
        f = feature(self.doc, "Design::Pattern", Source=cut, Direction1Reference=(edge, []), Count1=3, Spacing1=12)
        f.Operation = "Cut"
        Design.attachToBodies(f, [b])
        self.doc.recompute()
        self.assertNoErrors()
        self.assertVolume(b, 40 * 10 * 5 - 3 * PI * 4 * 5)


class MoveReference(DesignTest):
    def test_rotate_around_body_edge(self):
        _, b = box(self.doc, 10, 4, 2)
        edge = helper(self.doc, Part.LineSegment(V(0, 0, 0), V(0, 0, 1)).toShape())  # Z-Achse durch die Ecke
        f = feature(self.doc, "Design::Move", AxisReference=(edge, []), Angle=90)
        Design.attachToBodies(f, [b])
        self.doc.recompute()
        self.assertNoErrors()
        self.assertEqual(centers(b.Shape), [(-2, 5, 1)])


class Persistence(DesignTest):
    def test_references_survive_save(self):
        _, b = box(self.doc, 4, 4, 4)
        edge = helper(self.doc, Part.LineSegment(V(0, 0, 0), V(0, 1, 0)).toShape(), "Edge")
        f, (copy,) = copies_of(self.doc, "Design::Pattern", [b], Direction1Reference=(edge, []), Count1=2, Spacing1=10)
        name, copy_name = f.Name, copy.Name
        doc = save_and_reload(self.doc)
        f = doc.getObject(name)
        self.assertEqual(f.Direction1Reference[0].Name, "Edge")
        self.assertIn("ReadOnly", f.getPropertyStatus("Direction1"))
        f.touch()
        doc.recompute()
        self.assertEqual(centers(doc.getObject(copy_name).Shape), [(2, 12, 2)])
