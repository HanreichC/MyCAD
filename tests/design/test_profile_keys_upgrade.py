# SPDX-License-Identifier: LGPL-2.1-or-later
"""Ältere Dateien: Signaturen mit laufenden Nummern projizierter Kanten ("e51" für ein Loch) werden beim ersten
Neuberechnen auf feste Namen umgestellt, samt den Schlüsseln der Schritte. Ein Schritt, der nur ein solches Loch
extrudiert, findet es so auch nach der nächsten Skizzenänderung wieder (vorher fiel er auf die alte Flächennummer
zurück, die dann ein fremdes Profil trug). Echter Stand: ConceptKey (tests/projects)."""
import os
from design import *

HERE = os.path.dirname(os.path.abspath(__file__))
BEFORE = os.path.join(HERE, "..", "projects", "ConceptKey before sketch edit.mycad")
AFTER = os.path.join(HERE, "..", "projects", "ConceptKey after sketch edit.mycad")


class ProfileKeysUpgrade(unittest.TestCase):
    def test_old_hole_key_survives_a_sketch_edit(self):
        after = App.openDocument(AFTER, True)
        geometry, constraints = after.getObject("Sketch002").Geometry, after.getObject("Sketch002").Constraints
        App.closeDocument(after.Name)
        doc = App.openDocument(BEFORE)
        try:
            profiles = doc.getObject("Profiles002")
            # schon beim Laden umgestellt: die Schlüssel der Schritte passen genau zu den neuen Signaturen
            frame = doc.getObject("Extrude001")
            self.assertTrue(all(k in profiles.Signatures for k in frame.ProfileKeys), list(frame.ProfileKeys))
            self.assertTrue(any(",x" in k for k in frame.ProfileKeys), "the frame key names its projected edges")
            # ein Loch, das nur aus einer projizierten Kante besteht (früher "e<Kante>", jetzt "x<Nummer>")
            i = [k for k, s in enumerate(profiles.Signatures) if s.startswith("x") and "," not in s][0]
            hole = profiles.Shape.Faces[i].CenterOfMass
            pin = doc.addObject("Design::Extrude", "Pin"); Design.root(doc).addObject(pin); Design.addToTimeline(pin)
            pin.Profile = (profiles, ["Face%d" % (i + 1)]); pin.Distance = 5
            Design.newBody(pin)
            doc.recompute()
            self.assertTrue(pin.ProfileKeys[0].startswith("x"), pin.ProfileKeys[0])
            sketch = doc.getObject("Sketch002")
            sketch.Geometry = geometry
            sketch.Constraints = constraints
            doc.recompute()
            self.assertFalse(pin.Warning)
            center = pin.Shape.BoundBox.Center
            self.assertLess(math.hypot(center.x - hole.x, center.y - hole.y), 1e-3, "the pin stays in its hole")
        finally:
            App.closeDocument(doc.Name)
