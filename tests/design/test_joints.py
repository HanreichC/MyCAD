# SPDX-License-Identifier: LGPL-2.1-or-later
"""L6 Baugruppe: Ketten folgen, Grenzen klemmen, Konflikt wird gemeldet, neue Gelenktypen, Kollisionen"""
from design import *


def component_with_box(doc, x, y, z, name):
    comp = Design.newComponent(Design.root(doc))
    comp.Label = name
    sk = sketch(doc, rect(0, 0, x, y), component=comp)
    _, b = extrude(doc, sk, z)
    b.Label = name + "Body"
    return comp, b


def face(body, pred):
    return face_where(body, lambda c, f: pred(c))


def joint(doc, moving, body1, sub1, body2, sub2, **props):
    j = doc.addObject("Design::Joint", "Joint")
    j.Moving = moving
    j.Origin1 = (body1, [sub1])
    j.Origin2 = (body2, [sub2])
    for k, v in props.items():
        setattr(j, k, v)
    doc.recompute()
    moving.setExpression("Placement", j.Name + ".Result")
    doc.recompute()
    return j


def center(body):
    """Schwerpunkt in globalen Koordinaten (mit der Lage der Komponente; die Form selbst liegt am Ursprung)"""
    return body.getGlobalPlacement().multVec(body.Shape.CenterOfMass)


def r(v):
    return (round(v.x, 4), round(v.y, 4), round(v.z, 4))


class Joints(DesignTest):
    def base(self):
        _, a = box(self.doc, 10, 10, 10)  # fest im Design
        b_comp, b = component_with_box(self.doc, 10, 10, 2, "B")
        return a, b_comp, b

    def test_planar_faces_sit_on_each_other(self):
        a, b_comp, b = self.base()
        joint(self.doc, b_comp, b, face(b, lambda c: abs(c.z) < 1e-6), a, face(a, lambda c: abs(c.z - 10) < 1e-6),
              Type="Rigid")
        self.assertNoErrors()
        self.assertEqual(r(center(b)), (5, 5, 11))

    def test_chain_follows(self):
        a, b_comp, b = self.base()
        c_comp, c = component_with_box(self.doc, 2, 2, 2, "C")
        j1 = joint(self.doc, b_comp, b, face(b, lambda p: abs(p.z) < 1e-6), a, face(a, lambda p: abs(p.z - 10) < 1e-6),
                   Type="Slider", Offset=0)
        joint(self.doc, c_comp, c, face(c, lambda p: abs(p.z) < 1e-6), b, face(b, lambda p: abs(p.z - 2) < 1e-6),
              Type="Rigid")
        z_before = center(c).z
        j1.Offset = 5
        self.doc.recompute()
        self.assertNoErrors()
        self.assertAlmostEqual(center(c).z, z_before + 5, places=6)

    def test_limits_clamp(self):
        a, b_comp, b = self.base()
        j = joint(self.doc, b_comp, b, face(b, lambda p: abs(p.z) < 1e-6), a, face(a, lambda p: abs(p.z - 10) < 1e-6),
                  Type="Slider", Limited=True, OffsetMin=0, OffsetMax=3, Offset=20)
        self.assertAlmostEqual(center(b).z, 11 + 3, places=6)
        self.assertNotIn("Hidden", j.getPropertyStatus("OffsetMax"))
        self.assertIn("Hidden", j.getPropertyStatus("AngleMax"))  # ein Schieber dreht nicht

    def test_second_joint_that_contradicts_is_reported(self):
        a, b_comp, b = self.base()
        joint(self.doc, b_comp, b, face(b, lambda p: abs(p.z) < 1e-6), a, face(a, lambda p: abs(p.z - 10) < 1e-6))
        j2 = self.doc.addObject("Design::Joint", "Joint")
        j2.Moving = b_comp
        j2.Origin1 = (b, [face(b, lambda p: abs(p.z) < 1e-6)])
        j2.Origin2 = (a, [face(a, lambda p: abs(p.x - 10) < 1e-6)])  # zwei feste Lagen zugleich: geht nicht
        self.doc.recompute()
        self.assertTrue(failed(j2))
        self.assertIn("cannot all be met", j2.getStatusString())

    def test_pin_slot_planar_ball(self):
        a, b_comp, b = self.base()
        j = joint(self.doc, b_comp, b, face(b, lambda p: abs(p.z) < 1e-6), a, face(a, lambda p: abs(p.z - 10) < 1e-6),
                  Type="Planar", Offset=3, Offset2=4)
        self.assertEqual(r(center(b)), (8, 9, 11))
        self.assertNotIn("Hidden", j.getPropertyStatus("Offset2"))
        j.Type = "Pin-Slot"; j.Offset = 3; j.Angle = 0
        self.doc.recompute()
        self.assertEqual(r(center(b)), (8, 5, 11))
        j.Type = "Ball"; j.Angle = 90
        self.doc.recompute()
        self.assertNoErrors()
        self.assertNotIn("Hidden", j.getPropertyStatus("Angle2"))

    def test_collisions(self):
        a, b_comp, b = self.base()
        j = joint(self.doc, b_comp, b, face(b, lambda p: abs(p.z) < 1e-6), a, face(a, lambda p: abs(p.z - 10) < 1e-6),
                  Type="Slider", Offset=0)
        self.assertEqual(Design.collisions(b_comp), [])  # liegt nur auf
        j.Offset = -3  # 3 mm hinein
        self.doc.recompute()
        hits = Design.collisions(b_comp)
        self.assertEqual([(x.Label, y.Label) for x, y in hits], [("BBody", a.Label)])

    def test_joint_survives_save(self):
        a, b_comp, b = self.base()
        j = joint(self.doc, b_comp, b, face(b, lambda p: abs(p.z) < 1e-6), a, face(a, lambda p: abs(p.z - 10) < 1e-6),
                  Type="Planar", Offset=3, Offset2=4, Limited=True, OffsetMax=2)
        names = j.Name, b.Name
        doc = save_and_reload(self.doc)
        doc.getObject(names[0]).touch()
        doc.recompute()
        self.assertEqual(r(center(doc.getObject(names[1]))), (7, 9, 11))  # Offset auf 2 begrenzt, Offset2 frei


def bar(doc, length, name, comp=True):
    """Lasche 2 mm dick mit Löchern Ø2 bei x = 0 und x = length (in einer eigenen Komponente oder fest im Design)"""
    owner = Design.newComponent(Design.root(doc)) if comp else None
    if owner:
        owner.Label = name
    sk = sketch(doc, rect(-4, -4, length + 4, 4), component=owner)
    _, b = extrude(doc, sk, 2)
    for x in (0, length):
        extrude(doc, sketch(doc, circle(x, 0, 1), component=owner), 2, op="Cut", bodies=[b])
    b.Label = name + "Body"
    return owner, b


def hole_at(body, x):
    """Lochfläche, deren Achse bei x (lokal) liegt"""
    for i, f in enumerate(body.Shape.Faces, 1):
        if f.Surface.TypeId != "Part::GeomPlane" and abs(f.BoundBox.Center.x - x) < 1e-6:
            return "Face%d" % i
    raise AssertionError("no hole at %s" % x)


def hole_center(comp, body, x):
    return comp.getGlobalPlacement().multVec(App.Vector(x, 0, 1)) if comp else App.Vector(x, 0, 1)


class Loops(DesignTest):
    """Viergelenk (L6, OndselSolver): Steg 40, Kurbel 10, Koppel 35, Schwinge 20; die Kurbel treibt"""

    def four_bar(self, bend=1):
        d = self.doc
        _, ground = bar(d, 40, "Ground", comp=False)
        crank_c, crank = bar(d, 10, "Crank")
        coupler_c, coupler = bar(d, 35, "Coupler")
        rocker_c, rocker = bar(d, 20, "Rocker")
        j1 = joint(d, crank_c, crank, hole_at(crank, 0), ground, hole_at(ground, 0), Type="Revolute")
        # die offene Kette grob so knicken, wie sie geschlossen sitzen soll (oberer Zweig); die Lochachsen zeigen nach -Z
        joint(d, coupler_c, coupler, hole_at(coupler, 0), crank, hole_at(crank, 10), Type="Revolute", Angle=-35 * bend)
        joint(d, rocker_c, rocker, hole_at(rocker, 0), coupler, hole_at(coupler, 35), Type="Revolute", Angle=121 * bend)
        j4 = d.addObject("Design::Joint", "Joint")  # schließt die Kette: die Schwinge hängt auch am Steg
        j4.Type = "Revolute"
        j4.Moving = rocker_c
        j4.Origin1 = (rocker, [hole_at(rocker, 20)])
        j4.Origin2 = (ground, [hole_at(ground, 40)])
        d.recompute()
        return j1, j4, (crank_c, crank), (coupler_c, coupler), (rocker_c, rocker)

    def assertClosed(self, crank, coupler, rocker):
        pairs = [(hole_center(*crank, 10), hole_center(*coupler, 0)), (hole_center(*coupler, 35), hole_center(*rocker, 0)),
                 (hole_center(*rocker, 20), App.Vector(40, 0, 1)), (hole_center(*crank, 0), App.Vector(0, 0, 1))]
        for p, q in pairs:
            self.assertLess((p - q).Length, 1e-4, "%s != %s" % (p, q))

    def test_closes_the_loop(self):
        j1, j4, crank, coupler, rocker = self.four_bar()
        self.assertFalse(failed(j4), j4.getStatusString())
        self.assertNoErrors()
        self.assertClosed(crank, coupler, rocker)
        self.assertGreater(hole_center(*rocker, 0).y, 0)  # oberer Zweig

    def test_crank_drives(self):
        j1, j4, crank, coupler, rocker = self.four_bar()
        for angle in (30, 60, 90):
            j1.Angle = angle
            self.doc.recompute()
            self.assertNoErrors()
            self.assertClosed(crank, coupler, rocker)
            tip = hole_center(*crank, 10)
            # die Lochachse zeigt nach unten (wie bei offenen Ketten): der Winkel zählt um -Z
            self.assertAlmostEqual(abs(math.degrees(math.atan2(tip.y, tip.x))), angle, places=3)

    def test_limits_of_a_following_joint_are_kept(self):
        j1, j4, crank, coupler, rocker = self.four_bar()
        j4.Limited = True
        j4.AngleMin, j4.AngleMax = -180, 180
        self.doc.recompute()
        self.assertNoErrors()
        j4.AngleMin, j4.AngleMax = -0.5, 0.5  # so eng geht das Viergelenk nicht
        self.doc.recompute()
        self.assertTrue(failed(j4))
        self.assertIn("past its limits", j4.getStatusString())

    def test_pin_slot_closes_a_loop(self):
        j1, j4, crank, coupler, rocker = self.four_bar()
        j4.Type = "Pin-Slot"  # das Ende der Schwinge gleitet im Schlitz des Stegs (entlang X)
        self.doc.recompute()
        self.assertNoErrors()
        end = hole_center(*rocker, 20)
        self.assertLess(abs(end.y), 1e-4, str(end))
        self.assertLess(abs(end.z - 1), 1e-4, str(end))

    def test_straight_chain_still_closes(self):
        j1, j4, crank, coupler, rocker = self.four_bar(bend=0)  # gestreckt: singulär, der Solver knickt selbst
        self.assertNoErrors()
        self.assertClosed(crank, coupler, rocker)

    def test_open_chains_stay_as_before(self):
        a, b_comp, b = Joints.base(self)
        j = joint(self.doc, b_comp, b, face(b, lambda p: abs(p.z) < 1e-6), a, face(a, lambda p: abs(p.z - 10) < 1e-6),
                  Type="Slider", Offset=5)
        self.assertEqual(r(center(b)), (5, 5, 16))
