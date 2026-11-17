# SPDX-License-Identifier: LGPL-2.1-or-later
"""10.4 Idee 3: Zeilen "Name = Ausdruck" in einer Notiz sind Parameter; Formeln zeigen ihren Wert; nichts geht still
verloren; ändert sich ein Parameter am Modell, zieht die Notiz nach"""
from design import *

ARROW, WARN = "→", "⚠"


def note(doc, text, label=None):
    n = doc.addObject("Design::Note", "Note")
    if label:
        n.Label = label
    n.Text = text
    Design.syncNoteParameters(n)
    return n


def params(doc):
    return Design.parameterSet(doc, False)


def edit(n, text):
    n.Text = text
    Design.syncNoteParameters(n)


class Define(DesignTest):
    def test_lines_become_parameters(self):
        n = note(self.doc, "Gehäuse\nWand = 2 mm\nBreite = Wand * 20\n120 / 4 = 30")
        p = params(self.doc)
        self.assertAlmostEqual(p.Wand.Value, 2)
        self.assertAlmostEqual(p.Breite.Value, 40)
        lines = n.Text.split("\n")
        self.assertEqual(lines[1], "Wand = 2 mm")  # bloße Zahl: kein Hinweis
        self.assertEqual(lines[2], "Breite = Wand * 20 " + ARROW + " 40.00 mm")
        self.assertEqual(lines[3], "120 / 4 = 30")  # Rechenzeile bleibt
        self.assertEqual(sorted(n.Defines), ["Breite", "Wand"])

    def test_feature_follows_the_note(self):
        n = note(self.doc, "Hoehe = 5 mm")
        sk = sketch(self.doc, rect(0, 0, 10, 10))
        f, b = extrude(self.doc, sk, 1)
        f.setExpression("Distance", "Parameters.Hoehe")
        self.doc.recompute()
        self.assertVolume(b, 500)
        edit(n, "Hoehe = 8 mm")
        self.assertVolume(b, 800)

    def test_umlauts_and_decimal_comma(self):
        n = note(self.doc, "Wandstärke = 2,5 mm\nDoppelt = Wandstärke * 2")
        p = params(self.doc)
        self.assertAlmostEqual(p.Wandstaerke.Value, 2.5)
        self.assertAlmostEqual(p.Doppelt.Value, 5)
        self.assertEqual(p.getDocumentationOfProperty("Wandstaerke"), "Wandstärke")


class Problems(DesignTest):
    def test_bad_formula_is_marked(self):
        n = note(self.doc, "Wand = 2 mm +")
        self.assertIn(WARN, n.Text)
        self.assertFalse(hasattr(params(self.doc), "Wand"))

    def test_unknown_name_is_marked_and_does_not_stop_the_others(self):
        n = note(self.doc, "Wand = 2 mm\nFoo = abc\nBreite = Wand * 2")
        self.assertIn(WARN, n.Text.split("\n")[1])
        self.assertFalse(hasattr(params(self.doc), "Foo"))
        edit(n, "Wand = 3 mm\nFoo = abc\nBreite = Wand * 2")
        self.assertAlmostEqual(params(self.doc).Breite.Value, 6)  # ein Fehler legte vorher alle Parameter still

    def test_unit_name_is_refused(self):
        n = note(self.doc, "mm = 4 mm")
        self.assertIn(WARN, n.Text)
        self.assertFalse(hasattr(params(self.doc), "mm"))

    def test_same_name_twice_in_one_note(self):
        n = note(self.doc, "Wand = 2 mm\nWand = 3 mm")
        self.assertIn(WARN, n.Text.split("\n")[1])
        self.assertAlmostEqual(params(self.doc).Wand.Value, 2)

    def test_same_name_in_two_notes(self):
        note(self.doc, "Wand = 2 mm", "Maße")
        other = note(self.doc, "Wand = 3 mm", "Ideen")
        self.assertIn("Maße", other.Text)
        self.assertAlmostEqual(params(self.doc).Wand.Value, 2)

    def test_deleted_line_of_a_used_parameter_stays(self):
        n = note(self.doc, "Hoehe = 5 mm")
        sk = sketch(self.doc, rect(0, 0, 10, 10))
        f, b = extrude(self.doc, sk, 1)
        f.setExpression("Distance", "Parameters.Hoehe")
        self.doc.recompute()
        edit(n, "")
        self.assertTrue(hasattr(params(self.doc), "Hoehe"))  # nichts geht still verloren
        self.assertIn("still used by " + f.Label, n.Text)
        self.assertVolume(b, 500)
        f.setExpression("Distance", None)  # niemand braucht ihn mehr: jetzt darf er gehen
        edit(n, n.Text)
        self.assertFalse(hasattr(params(self.doc), "Hoehe"))
        self.assertNotIn("still used", n.Text)

    def test_deleted_unused_line_removes_the_parameter(self):
        n = note(self.doc, "Wand = 2 mm")
        edit(n, "")
        self.assertFalse(hasattr(params(self.doc), "Wand"))


class BothWays(DesignTest):
    def test_change_on_the_model_updates_the_note(self):
        n = note(self.doc, "Hoehe = 5 mm\nDoppelt = Hoehe * 2")
        sk = sketch(self.doc, rect(0, 0, 10, 10))
        f, b = extrude(self.doc, sk, 1)
        f.setExpression("Distance", "Parameters.Hoehe")
        self.doc.recompute()
        Design.setDrivingDimension(f, "Distance", 12)  # Maß am Modell (Idee 2)
        lines = n.Text.split("\n")
        self.assertEqual(lines[0], "Hoehe = 12 mm")
        self.assertIn(ARROW + " 24.00 mm", lines[1])
        self.assertVolume(b, 1200)

    def test_survives_save(self):
        n = note(self.doc, "Wand = 2 mm\nBreite = Wand * 20")
        name = n.Name
        doc = save_and_reload(self.doc)
        n = doc.getObject(name)
        self.assertEqual(sorted(n.Defines), ["Breite", "Wand"])
        self.assertAlmostEqual(Design.parameterSet(doc, False).Breite.Value, 40)


class Configurations(DesignTest):
    """Phase 11.7: Kopfzeile "Größe: S | M | L", Werte je Spalte, "Größe = M" wählt; das Teil folgt"""
    TEXT = "Größe: S | M | L\nBreite = 20 mm | 30 mm | 40 mm\nHoehe = 5 mm"

    def part(self):
        n = note(self.doc, self.TEXT)
        sk = sketch(self.doc, rect(0, 0, 10, 10))
        f, b = extrude(self.doc, sk, 1)
        f.setExpression("Distance", "Parameters.Breite")
        self.doc.recompute()
        return n, f, b

    def choose(self, n, option):
        lines = [l for l in n.Text.split("\n") if not l.startswith("Größe =")]
        edit(n, "\n".join(lines[:1] + ["Größe = " + option] + lines[1:]))
        self.doc.recompute()

    def test_first_column_without_a_choice(self):
        n, f, b = self.part()
        self.assertAlmostEqual(params(self.doc).Breite.Value, 20)
        self.assertVolume(b, 2000)
        self.assertEqual(sorted(n.Defines), ["Breite", "Hoehe"])  # die Auswahl ist kein Parameter
        self.assertNotIn(WARN, n.Text)

    def test_choosing_a_column_switches_the_part(self):
        n, f, b = self.part()
        self.choose(n, "L")
        self.assertAlmostEqual(params(self.doc).Breite.Value, 40)
        self.assertVolume(b, 4000)
        self.assertFalse(hasattr(params(self.doc), "Groesse"))
        self.choose(n, "M")
        self.assertVolume(b, 3000)
        self.assertNotIn(WARN, n.Text)

    def test_wrong_column_count_and_unknown_choice_are_marked(self):
        n = note(self.doc, "Größe: S | M\nGröße = XL\nBreite = 1 mm | 2 mm | 3 mm\nWand = 2 mm")
        lines = n.Text.split("\n")
        self.assertIn(WARN + " Not one of the configurations", lines[1])
        self.assertIn(WARN + " Needs one value per configuration", lines[2])
        self.assertFalse(hasattr(params(self.doc), "Breite"))
        self.assertAlmostEqual(params(self.doc).Wand.Value, 2)  # der Rest geht weiter

    def test_change_on_the_model_changes_only_the_active_column(self):
        n, f, b = self.part()
        self.choose(n, "M")
        Design.setDrivingDimension(f, "Distance", 35)
        self.assertEqual(n.Text.split("\n")[2], "Breite = 20 mm | 35 mm | 40 mm")
        self.assertVolume(b, 3500)

    def test_survives_save(self):
        n, f, b = self.part()
        self.choose(n, "L")
        doc = save_and_reload(self.doc)
        self.assertAlmostEqual(Design.parameterSet(doc, False).Breite.Value, 40)
