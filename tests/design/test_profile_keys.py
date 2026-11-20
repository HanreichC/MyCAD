# SPDX-License-Identifier: LGPL-2.1-or-later
"""Skizzen jederzeit ändern wie in Fusion: Schritte finden ihre Profile wieder. In ConceptKey (echter Stand,
tests/projects) liegt "Skizze" auf der PCB-Unterseite und projiziert deren Kontur und Löcher; Rahmen und Laschen sind
extrudiert, eine spätere Skizze liegt auf dem Rahmen. Bekam "Skizze" neue Elemente, verschoben sich die laufenden
Kantennummern der projizierten Kanten: Extrusion001 fand ihre Profile nicht mehr und wurde leer, die spätere Skizze
verlor ihre Fläche. Jetzt tragen projizierte Kanten feste Namen, und das ähnlichste Profil gewinnt."""
import os
from design import *

HERE = os.path.dirname(os.path.abspath(__file__))
BEFORE = os.path.join(HERE, "..", "projects", "ConceptKey before sketch edit.mycad")
AFTER = os.path.join(HERE, "..", "projects", "ConceptKey after sketch edit.mycad")


class ProfileKeys(unittest.TestCase):
    def test_editing_a_sketch_keeps_later_steps(self):
        after = App.openDocument(AFTER, True)
        geometry, constraints = after.getObject("Sketch002").Geometry, after.getObject("Sketch002").Constraints
        App.closeDocument(after.Name)
        doc = App.openDocument(BEFORE)
        try:
            doc.recompute()
            frame = doc.getObject("Extrude001")
            volume, solids = frame.Shape.Volume, len(frame.Shape.Solids)
            sketch = doc.getObject("Sketch002")
            sketch.Geometry = geometry  # die neuen Elemente der Skizze, wie im Stand danach
            sketch.Constraints = constraints
            doc.recompute()
            self.assertGreater(frame.Shape.Volume, 0.9 * volume, "the frame and its tabs are still extruded")
            self.assertEqual(len(frame.Shape.Solids), solids)
            later = doc.getObject("Sketch004")
            self.assertNotIn("Invalid", later.State, later.getStatusString())
            self.assertFalse([o.Name for o in doc.Objects if "Invalid" in o.State])
        finally:
            App.closeDocument(doc.Name)
