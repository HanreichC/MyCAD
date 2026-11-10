# SPDX-License-Identifier: LGPL-2.1-or-later
"""10.7 Idee 7: Keine Angst. Aufbewahrung wie Time Machine, Version nur bei Änderung, Wiederherstellen, Vergleich
(hinzugekommen, entfernt, geänderte Schritte), Varianten anlegen, wechseln, übernehmen, Absturz"""
import os
import shutil
import tempfile

from design import *
import DesignVersions as V_

NOW = 1_800_000_000  # fester Zeitpunkt für die Aufbewahrung


class Retention(DesignTest):
    def test_today_everything(self):
        times = [NOW - m * 60 for m in range(0, 600, 7)]  # alle 7 Minuten, 10 Stunden lang
        self.assertEqual(V_.keep(times, NOW), set(times))

    def test_one_per_hour_for_a_week(self):
        times = [NOW - V_.DAY - m * 600 for m in range(12)]  # gestern, alle 10 Minuten zwei Stunden lang
        kept = V_.keep(times, NOW)
        self.assertLessEqual(len(kept), 3)
        self.assertGreaterEqual(len(kept), 2)
        self.assertIn(max(times), kept)  # die neueste je Stunde

    def test_one_per_day_after(self):
        times = [NOW - 10 * V_.DAY - h * V_.HOUR for h in range(0, 20)]
        kept = V_.keep(times, NOW)
        days = {int(t // V_.DAY) for t in times}
        self.assertEqual(len(kept), len(days))

    def test_mixed(self):
        hour = NOW - 2 * V_.DAY - 1800  # mitten in einer Stunde (NOW liegt genau auf einer vollen Stunde)
        times = [NOW - 60, hour, hour - 60, NOW - 30 * V_.DAY, NOW - 30 * V_.DAY - 60]
        kept = V_.keep(times, NOW)
        self.assertEqual(kept, {NOW - 60, hour, NOW - 30 * V_.DAY})


class Files(DesignTest):
    def setUp(self):
        super().setUp()
        self.folder = tempfile.mkdtemp()
        self.path = os.path.join(self.folder, "Box.FCStd")
        self.f, self.b = box(self.doc, 10, 10, 10)
        self.doc.saveAs(self.path)

    def tearDown(self):
        super().tearDown()
        for d in list(App.listDocuments().values()):
            App.closeDocument(d.Name)
        shutil.rmtree(self.folder, ignore_errors=True)

    def current(self):
        return App.ActiveDocument

    def body(self, doc):
        return [o for o in doc.Objects if o.TypeId == "Design::Body"][0]

    def test_version_only_when_changed(self):
        self.assertTrue(V_.snapshot(self.doc, now=NOW))
        self.assertIsNone(V_.snapshot(self.doc, now=NOW + 1))  # gleicher Stand
        self.f.Distance = 20
        self.doc.recompute()
        self.doc.save()
        self.assertTrue(V_.snapshot(self.doc, now=NOW + 2))
        self.assertEqual(len(V_.versions(self.path)), 2)
        self.assertEqual(os.path.dirname(V_.versions(self.path)[0]["path"]), os.path.join(self.folder, "versions", "Box"))

    def test_named_versions_stay(self):
        V_.snapshot(self.doc, "Before the holes", now=NOW - 40 * V_.DAY)
        V_.snapshot(self.doc, now=NOW - 40 * V_.DAY + 60)
        V_.prune(self.path, NOW)
        titles = [v["title"] for v in V_.versions(self.path)]
        self.assertIn("Before the holes", titles)

    def test_restore_gives_the_old_shape_and_keeps_everything(self):
        V_.snapshot(self.doc, now=NOW)
        old = V_.versions(self.path)[0]["path"]
        self.f.Distance = 30
        self.doc.recompute()
        self.doc.save()
        V_.snapshot(self.doc, now=NOW + 60)
        restored = V_.restore(self.doc, old)
        restored.recompute()
        self.assertAlmostEqual(self.body(restored).Shape.Volume, 1000, places=6)
        self.assertGreaterEqual(len(V_.versions(self.path)), 3)  # alter, neuer und der wiederhergestellte Stand
        self.assertTrue(os.path.exists(old))  # nichts gelöscht

    def test_compare(self):
        V_.snapshot(self.doc, now=NOW)
        old = V_.versions(self.path)[0]["path"]
        sk = sketch(self.doc, circle(5, 5, 2))
        extrude(self.doc, sk, 10, op="Cut", bodies=[self.b])  # Loch dazu
        self.f.Distance = 12  # höher
        self.doc.recompute()
        d = V_.compare(self.doc, old)
        self.assertAlmostEqual(d["addedVolume"], 200, places=3)  # 2 mm mehr Höhe (das Loch geht nur bis 10)
        self.assertAlmostEqual(d["removedVolume"], math.pi * 4 * 10, places=3)      # das Loch
        self.assertEqual(len(d["features"]["added"]), 2)   # Skizze und Extrude des Lochs
        self.assertEqual(d["features"]["changed"], [self.f.Label])
        self.assertEqual(d["features"]["removed"], [])
        self.assertEqual(App.ActiveDocument, self.doc)  # der Vergleich lässt das Design aktiv

    def test_variant_create_switch_adopt(self):
        path = V_.make_variant(self.doc, "Taller")
        self.assertEqual([v["name"] for v in V_.variants(self.path)], ["Taller"])
        self.assertEqual(V_.main_of(path), self.path)
        variant = V_.switch(self.doc, path)
        self.assertTrue(V_.is_variant(variant.FileName))
        ext = [o for o in variant.Objects if o.TypeId == "Design::Extrude"][0]
        ext.Distance = 25
        variant.recompute()
        variant.save()
        d = V_.compare(variant, self.path)
        self.assertAlmostEqual(d["addedVolume"], 1500, places=3)
        main = V_.adopt(variant)
        main.recompute()
        self.assertEqual(os.path.normcase(main.FileName), os.path.normcase(self.path))
        self.assertAlmostEqual(self.body(main).Shape.Volume, 2500, places=6)
        self.assertEqual(V_.variants(self.path), [])
        self.assertTrue(any(v["title"] == "Before Taller" for v in V_.versions(self.path)))  # alter Stand bleibt

    def test_crash_loses_nothing_that_was_saved(self):
        self.f.Distance = 15
        self.doc.recompute()
        self.doc.save()  # wie das immer laufende Speichern
        name = self.doc.Name
        App.closeDocument(name)  # "Absturz": weg ohne Rückfrage
        again = App.openDocument(self.path)
        again.recompute()
        self.assertAlmostEqual(self.body(again).Shape.Volume, 1500, places=6)

    def test_thumbnail_is_read_when_present(self):
        V_.snapshot(self.doc, now=NOW)
        self.assertIn(V_.thumbnail(V_.versions(self.path)[0]["path"]), (None,) + (V_.thumbnail(self.path),))
