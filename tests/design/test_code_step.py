# SPDX-License-Identifier: LGPL-2.1-or-later
"""12.10 Code-Schritt: Python-Code baut eine Form; läuft nur nach Freigabe auf diesem Rechner (fremde Datei: nichts
läuft); Parameter der Notiz als p.Name, eine geänderte Zeile rechnet neu; Join wie bei Grundkörpern"""
import math

import DesignCode
from design import *

PLATE = """w = p.Width
result = cut(box(w, 30, 5), cylinder(8, 5))
"""


def note(doc, text):
    n = doc.addObject("Design::Note", "Note")
    n.Text = text
    Design.syncNoteParameters(n)
    return n


class CodeStep(DesignTest):
    def setUp(self):
        super().setUp()
        App.ParamGet("User parameter:BaseApp/Preferences/MyCAD").RemGroup("ApprovedCode")

    def tearDown(self):
        App.ParamGet("User parameter:BaseApp/Preferences/MyCAD").RemGroup("ApprovedCode")
        super().tearDown()

    def step(self, code, op="New Body", bodies=()):
        f = feature(self.doc, "Design::CodeStep", Code=code)
        f.Operation = op
        if op == "New Body":
            b = new_body(f)
        else:
            Design.attachToBodies(f, list(bodies))
            b = bodies[0]
        self.doc.recompute()
        return f, b

    def test_unapproved_code_does_not_run(self):
        note(self.doc, "Width = 40 mm")
        f, b = self.step(PLATE)
        self.assertIn("Invalid", f.State)
        self.assertIn("not run on this computer", f.getStatusString())

    def test_approved_code_builds_and_follows_the_note(self):
        n = note(self.doc, "Width = 40 mm")
        DesignCode.approve(PLATE)
        f, b = self.step(PLATE)
        self.assertNotIn("Invalid", f.State)
        self.assertAlmostEqual(b.Shape.Volume, 40 * 30 * 5 - math.pi * 16 * 5, places=3)
        n.Text = "Width = 60 mm"
        Design.syncNoteParameters(n)
        self.doc.recompute()
        self.assertAlmostEqual(b.Shape.Volume, 60 * 30 * 5 - math.pi * 16 * 5, places=3)

    def test_changed_code_needs_a_new_approval(self):
        note(self.doc, "Width = 40 mm")
        DesignCode.approve(PLATE)
        f, b = self.step(PLATE)
        f.Code = PLATE.replace("30", "50")  # z. B. aus einer fremden Datei: anderer Text, keine Freigabe
        self.doc.recompute()
        self.assertIn("Invalid", f.State)

    def test_join_onto_a_body(self):
        _, base = box(self.doc, 10, 10, 10, at=(-5, -5))
        code = "result = cylinder(4, 20)"
        DesignCode.approve(code)
        f, b = self.step(code, "Join", [base])
        self.assertIs(b, base)
        self.assertAlmostEqual(base.Shape.Volume, 1000 + math.pi * 4 * 10, places=3)  # oben 10 mm heraus

    def test_errors_in_the_code_are_shown(self):
        code = "result = box(10, 10)"  # ein Maß fehlt
        DesignCode.approve(code)
        f, _ = self.step(code)
        self.assertIn("Invalid", f.State)
        self.assertIn("missing", f.getStatusString())
        code = "x = 1"
        DesignCode.approve(code)
        f, _ = self.step(code)
        self.assertIn("result to a shape", f.getStatusString())


if __name__ == "__main__":
    unittest.main()
