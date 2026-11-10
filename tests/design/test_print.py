# SPDX-License-Identifier: LGPL-2.1-or-later
"""10.6 Idee 5: Druckansicht (Überhang, Bett, dünne Wände, Druckrichtung) und Drucken (Slicer finden, 3MF öffnen)"""
import os
import stat
import tempfile
import time
import zipfile

from design import *
import DesignExport


def mushroom(doc):
    """Fuß 10 x 10 x 10 auf dem Bett, darauf ein Hut 30 x 30 x 2, der rundum 10 mm übersteht"""
    _, b = box(doc, 10, 10, 10)
    sk = sketch(doc, rect(-10, -10, 20, 20), App.Placement(V(0, 0, 10), App.Rotation()))
    extrude(doc, sk, 2, op="Join", bodies=[b])
    return b


class Overhang(DesignTest):
    def test_hat_overhangs_foot_sits_on_the_bed(self):
        b = mushroom(self.doc)
        r = Design.printCheck(b)
        self.assertAlmostEqual(r["bed"], 100, places=3)
        self.assertAlmostEqual(r["overhang"], 900 - 100, places=3)  # Unterseite des Huts außerhalb des Fußes

    def test_upside_down_swaps_them(self):
        b = mushroom(self.doc)
        Design.setPrintUp(self.doc, V(0, 0, -1))
        r = Design.printCheck(b)
        self.assertAlmostEqual(r["bed"], 900, places=3)  # der Hut liegt jetzt auf, der Fuß steht nach oben
        self.assertAlmostEqual(r["overhang"], 0)
        self.assertEqual(Design.printUp(self.doc), V(0, 0, -1))

    def test_print_direction_is_saved(self):
        Design.setPrintUp(self.doc, V(1, 0, 0))
        doc = save_and_reload(self.doc)
        self.assertEqual(Design.printUp(doc), V(1, 0, 0))

    def test_lying_on_its_side(self):
        b = mushroom(self.doc)
        Design.setPrintUp(self.doc, V(1, 0, 0))  # der Hut-Rand bei x = -10 liegt auf
        r = Design.printCheck(b)
        self.assertAlmostEqual(r["bed"], 30 * 2, places=3)
        self.assertAlmostEqual(r["overhang"], 10 * 10, places=3)  # Seite des Fußes bei x = 0 hängt über dem Bett

    def test_a_plain_box_has_no_overhang(self):
        _, b = box(self.doc, 10, 10, 10)
        r = Design.printCheck(b)
        self.assertAlmostEqual(r["overhang"], 0)
        self.assertAlmostEqual(r["bed"], 100, places=3)


class Walls(DesignTest):
    def test_thin_plate_is_marked(self):
        _, b = box(self.doc, 20, 20, 0.5)
        r = Design.printCheck(b)
        self.assertAlmostEqual(r["thin"], 2 * 400, delta=1)  # Ober- und Unterseite: nur 0,5 mm dazwischen

    def test_two_mm_plate_is_fine(self):
        _, b = box(self.doc, 20, 20, 2)
        self.assertAlmostEqual(Design.printCheck(b)["thin"], 0)

    def test_own_limit(self):
        _, b = box(self.doc, 20, 20, 2)
        self.assertAlmostEqual(Design.printCheck(b, V(0, 0, 1), 45, 3)["thin"], 2 * 400, delta=1)


def fake_slicer(folder, name):
    """Programm, das seine Argumente in <folder>/args.txt schreibt"""
    path = os.path.join(folder, name)
    with open(path, "w") as f:
        f.write('#!/bin/sh\necho "$@" > "%s"\n' % os.path.join(folder, "args.txt"))
    os.chmod(path, os.stat(path).st_mode | stat.S_IEXEC)
    return path


class Slicer(DesignTest):
    def test_finds_a_slicer_in_path(self):
        with tempfile.TemporaryDirectory() as bin_dir, tempfile.TemporaryDirectory() as home:
            exe = fake_slicer(bin_dir, "prusa-slicer")
            self.assertEqual(DesignExport.find_slicers({"PATH": bin_dir}, home), [("PrusaSlicer", [exe])])

    def test_finds_an_appimage(self):
        with tempfile.TemporaryDirectory() as home:
            os.makedirs(os.path.join(home, "Applications"))
            image = fake_slicer(os.path.join(home, "Applications"), "OrcaSlicer_Linux_V2.3.0.AppImage")
            self.assertEqual(DesignExport.find_slicers({"PATH": ""}, home), [("OrcaSlicer", [image])])

    def test_nothing_installed(self):
        with tempfile.TemporaryDirectory() as home:
            self.assertEqual(DesignExport.find_slicers({"PATH": ""}, home), [])

    def test_opens_the_3mf_in_the_slicer_with_print_direction_up(self):
        _, b = box(self.doc, 30, 10, 5)
        with tempfile.TemporaryDirectory() as folder:
            exe = fake_slicer(folder, "orca-slicer")
            path = DesignExport.open_in_slicer([b], folder, [exe], up=V(1, 0, 0))
            log = os.path.join(folder, "args.txt")
            for _ in range(50):
                if os.path.exists(log):
                    break
                time.sleep(0.1)
            with open(log) as f:
                self.assertEqual(f.read().strip(), path)
            with zipfile.ZipFile(path) as z:
                model = z.read("3D/3dmodel.model").decode()
            zs = [float(part.split('"')[1]) for part in model.split(' z=')[1:]]
            self.assertAlmostEqual(max(zs) - min(zs), 30, places=3)  # x zeigte nach oben: die 30 mm stehen jetzt
