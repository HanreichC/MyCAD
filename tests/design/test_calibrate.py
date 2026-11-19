# SPDX-License-Identifier: LGPL-2.1-or-later
"""12.4 Druckerprofil: Testteil (Löcher mit Spiel 0,05 … 0,40, Stift, Überhänge, Wände) und was die Antworten einstellen"""
from design import *
import DesignCalibrate as C


class TestPiece(DesignTest):
    def test_three_printable_bodies_in_the_timeline(self):
        bodies = C.make(self.doc)
        self.assertEqual([b.Label for b in bodies], ["Fit Plate", "Pin", "Limits"])
        for b in bodies:
            self.assertTrue(b.Shape.isValid() and b.Shape.Volume > 0, b.Label)
            self.assertAlmostEqual(b.Shape.BoundBox.ZMin, 0, places=6)  # liegt auf dem Bett
        self.assertEqual(len(Design.timeline(self.doc)), 3)
        boxes = [b.Shape.BoundBox for b in bodies]
        for i in range(3):
            for j in range(i + 1, 3):
                self.assertFalse(boxes[i].intersect(boxes[j]), "bodies %d and %d overlap" % (i, j))

    def test_holes_grow_by_the_clearance_per_side(self):
        plate = C.shapes()[0][1]
        radii = sorted({round(f.Surface.Radius, 3) for f in plate.Faces if hasattr(f.Surface, "Radius")} - {0.8})  # 0,8: Kerbe an Loch 1 ohne Schrift
        self.assertEqual(radii, [round(C.PIN / 2 + c, 3) for c in C.CLEARANCES])
        pin = C.shapes()[1][1]
        self.assertAlmostEqual(pin.BoundBox.XLength, C.PIN, places=6)

    def test_walls_and_fins_are_there(self):
        limits = C.shapes()[2][1]
        self.assertTrue(limits.isValid())
        self.assertAlmostEqual(limits.BoundBox.ZMax, 10, places=6)  # Wände 8 hoch auf 2 mm Platte
        # die 70°-Finne steht am weitesten über: 3 + 2 + 5 * tan 70°
        fin = [f for f in limits.Faces if f.BoundBox.ZMin > 1.9 and f.BoundBox.XMax > 17]
        self.assertTrue(fin)

    def test_answers_set_the_profile(self):
        self.assertEqual(C.values(hole=4), {"PrintFitTight": 0.1, "PrintFitNormal": 0.2, "PrintFitLoose": 0.3})
        self.assertEqual(C.values(hole=1)["PrintFitTight"], 0.0)  # nie negativ
        self.assertEqual(C.values(angle=50, wall=0.6), {"OverhangAngle": 50.0, "MinWall": 0.6})
        self.assertEqual(C.values(), {})

    def test_apply_writes_what_fit_and_thread_read(self):
        grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")
        try:
            C.apply(hole=6)
            self.assertAlmostEqual(grp.GetFloat("PrintFitNormal"), 0.3)
            self.assertAlmostEqual(grp.GetFloat("PrintFitLoose"), 0.4)
        finally:
            C.apply(hole=4)  # zurück auf die Vorgaben 0,1 / 0,2 / 0,3


if __name__ == "__main__":
    unittest.main()
