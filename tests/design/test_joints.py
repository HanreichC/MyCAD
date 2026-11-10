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

    def test_second_joint_on_same_component_is_reported(self):
        a, b_comp, b = self.base()
        joint(self.doc, b_comp, b, face(b, lambda p: abs(p.z) < 1e-6), a, face(a, lambda p: abs(p.z - 10) < 1e-6))
        j2 = self.doc.addObject("Design::Joint", "Joint")
        j2.Moving = b_comp
        j2.Origin1 = (b, [face(b, lambda p: abs(p.z) < 1e-6)])
        j2.Origin2 = (a, [face(a, lambda p: abs(p.x - 10) < 1e-6)])
        self.doc.recompute()
        self.assertTrue(failed(j2))
        self.assertIn("already follows", j2.getStatusString())

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
