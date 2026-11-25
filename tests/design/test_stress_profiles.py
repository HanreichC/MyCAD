# SPDX-License-Identifier: LGPL-2.1-or-later
"""Härtetest im Kleinen (der ganze: tests/design/stress_profiles.py, Seeds 1–15 je 40 Versuche, Stand 25.11. alle grün):
zufällige Linien und Kreise in den Skizzen von ConceptKey dürfen keinen Körper verändern, keine Warnung auslösen, und
nach dem Zurücksetzen ist alles wie vorher. Seed 3 enthält den früheren Dominoeffekt gleich im ersten Versuch."""
import os
import runpy
from design import *

HERE = os.path.dirname(os.path.abspath(__file__))


class StressProfiles(unittest.TestCase):
    def test_random_sketch_edits_change_nothing(self):
        os.environ.update(FILE=os.path.join(HERE, "..", "projects", "ConceptKey press pull.mycad"), SEED="3", N="12")
        result = runpy.run_path(os.path.join(HERE, "stress_profiles.py"))
        for doc in list(App.listDocuments().values()):
            App.closeDocument(doc.Name)
        self.assertEqual(result["fails"], 0)
