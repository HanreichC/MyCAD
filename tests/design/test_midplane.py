# SPDX-License-Identifier: LGPL-2.1-or-later
"""Aufräumliste B6: die Mittelebene bleibt in der Mitte. Zwischen Boden und Deckel eines Quaders liegt sie auf halber
Höhe; wird der Quader höher, wandert sie mit (vorher: an der ersten Fläche befestigt, Abstand beim Anlegen fest).
Auch zwischen zwei Konstruktionsebenen; übersteht Speichern und Laden."""
from design import *


def flat(body, z):
    return face_where(body, lambda c, f: abs(c.z - z) < 1e-6 and f.Surface.TypeId == "Part::GeomPlane")


def midplane(doc, refs):
    m = doc.addObject("Design::Midplane", "Midplane")
    Design.root(doc).addObject(m)
    m.Faces = refs
    doc.recompute()
    return m


class Midplane(DesignTest):
    def test_between_bottom_and_top_and_follows(self):
        f, b = box(self.doc, 20, 20, 10)
        m = midplane(self.doc, [(b, flat(b, 0)), (b, flat(b, 10))])
        self.assertAlmostEqual(m.Placement.Base.z, 5)
        f.Distance = 30  # der Quader wird höher: die Mitte wandert mit
        self.doc.recompute()
        self.assertAlmostEqual(m.Placement.Base.z, 15)
        self.assertAlmostEqual(abs(m.Placement.Rotation.multVec(V(0, 0, 1)).z), 1)  # liegt waagrecht
        self.assertNoErrors()

    def test_between_two_construction_planes(self):
        low = self.doc.addObject("PartDesign::Plane", "Low")
        high = self.doc.addObject("PartDesign::Plane", "High")
        for p, z in ((low, 2), (high, 12)):
            Design.root(self.doc).addObject(p)
            p.Placement = App.Placement(V(0, 0, z), App.Rotation())
        self.doc.recompute()
        m = midplane(self.doc, [(low, ""), (high, "")])
        self.assertAlmostEqual(m.Placement.Base.z, 7)
        high.Placement = App.Placement(V(0, 0, 22), App.Rotation())
        self.doc.recompute()
        self.assertAlmostEqual(m.Placement.Base.z, 12)

    def test_not_parallel_is_an_error(self):
        _, b = box(self.doc, 20, 20, 10)
        side = face_where(b, lambda c, f: abs(c.x) < 1e-6)
        m = midplane(self.doc, [(b, flat(b, 0)), (b, side)])
        self.assertTrue(m.isValid() is False or "Invalid" in m.State, m.State)

    def test_survives_save(self):
        f, b = box(self.doc, 20, 20, 10)
        m = midplane(self.doc, [(b, flat(b, 0)), (b, flat(b, 10))])
        name, extrude = m.Name, f.Name
        doc = save_and_reload(self.doc)
        doc.getObject(extrude).Distance = 40
        doc.recompute()
        self.assertAlmostEqual(doc.getObject(name).Placement.Base.z, 20)
