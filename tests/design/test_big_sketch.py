# SPDX-License-Identifier: LGPL-2.1-or-later
"""Große Skizzen (DXF-Import mit tausenden Elementen): Lösen bleibt schnell, Freiheitsgrade, Konflikte und
Redundanzen stimmen weiter, wenn die Diagnose in unabhängige Blöcke zerfällt"""
import time

import Sketcher
from design import *


def free_geometry(sk, n):
    """n Bögen, Linien und Kreise ohne Constraints (je Bogen zwei interne Regeln): 5 + 4 + 3 Freiheitsgrade"""
    geos = []
    for i in range(n):
        x = i * 10.0
        geos.append(Part.ArcOfCircle(Part.Circle(V(x, 0, 0), V(0, 0, 1), 2), 0, 1.5))
        geos.append(Part.LineSegment(V(x, 10, 0), V(x + 5, 12, 0)))
        geos.append(Part.Circle(V(x, 20, 0), V(0, 0, 1), 1))
    sk.addGeometry(geos)
    return 12 * n


def pcb_like(sk, n=1000):
    """Wie ein Platinen-DXF (10.000 Elemente bei n=1000): je Zelle ein Rechteck aus 4 Linien, 2 lose Linien, 3 Kreise,
    ein Bogen, ohne Constraints"""
    geos = []
    for i in range(n):
        x, y = (i % 40) * 12.0, (i // 40) * 12.0
        geos += rect(x, y, x + 8, y + 6)
        geos.append(Part.LineSegment(V(x, y + 8, 0), V(x + 9, y + 8, 0)))
        geos.append(Part.LineSegment(V(x + 10, y, 0), V(x + 10, y + 9, 0)))
        geos += [Part.Circle(V(x + 2 + k * 2, y + 3, 0), V(0, 0, 1), 0.6) for k in range(3)]
        geos.append(Part.ArcOfCircle(Part.Circle(V(x + 4, y + 10, 0), V(0, 0, 1), 1.5), 0, 2.5))
    sk.addGeometry(geos)
    return len(geos)


class BigSketch(DesignTest):
    def test_budget_10000_elements(self):
        """Leistungsgrenzen mit Reserve (gemessen: Lösen 0,16 s, Hinzufügen 0,03 s, Neuberechnen 1,6 s): quadratische
        Stellen, wie sie ein DXF-Import mit 10.000 Elementen aufdeckte, brechen sie um ein Vielfaches"""
        sk = self.doc.addObject("Sketcher::SketchObject", "Pcb")
        sk.MakeInternals = False  # wie jede MyCAD-Skizze: Flächen liefern die Profile (FreeCADs WireJoiner wäre 40 s)
        count = pcb_like(sk)
        self.assertEqual(count, 10000)

        def took(fn):
            t = time.monotonic()
            fn()
            return time.monotonic() - t
        self.assertEqual(sk.solve(), 0)
        solve = took(sk.solve)
        add = took(lambda: sk.addGeometry(Part.LineSegment(V(-5, 0, 0), V(-5, 5, 0))))
        sk.touch()
        recompute = took(self.doc.recompute)
        report = "solve %.2f s, add %.2f s, recompute %.2f s" % (solve, add, recompute)
        self.assertLess(solve, 1.0, report)
        self.assertLess(add, 0.3, report)
        self.assertLess(recompute, 6.0, report)
        self.assertFalse(sk.Shape.isNull())


    def test_many_free_arcs_solve_fast(self):
        sk = self.doc.addObject("Sketcher::SketchObject", "Big")
        dofs = free_geometry(sk, 800)
        t = time.monotonic()
        self.assertEqual(sk.solve(), 0)
        took = time.monotonic() - t
        self.assertEqual(sk.DoF, dofs)
        self.assertLess(took, 2.0, "800 free arcs took %.1f s to solve (was 11 s)" % took)

    def test_redrawn_line_gets_its_id_back(self):
        """Geometrie-Historie (beim Lösen und Hinzufügen neu aufgebaut): an derselben Stelle neu gezeichnet bekommt
        die gelöschte Linie ihre ID zurück, auch wenn ein Endpunkt minimal daneben liegt"""
        sk = self.doc.addObject("Sketcher::SketchObject", "History")
        p = [V(0, 0, 0), V(10, 0, 0), V(10, 5, 0)]
        for i in range(3):
            sk.addGeometry(Part.LineSegment(p[i], p[(i + 1) % 3]))
        ids = [sk.getGeometryId(i) for i in range(3)]
        sk.delGeometry(1)
        n = sk.addGeometry(Part.LineSegment(p[1] + V(1e-8, 0, 0), p[2]))
        self.assertEqual(sk.getGeometryId(n), ids[1])

    def test_conflict_and_redundancy_next_to_free_geometry(self):
        sk = self.doc.addObject("Sketcher::SketchObject", "Mixed")
        dofs = free_geometry(sk, 50)
        a = sk.addGeometry(Part.LineSegment(V(0, -10, 0), V(10, -10, 0)))
        b = sk.addGeometry(Part.LineSegment(V(0, -20, 0), V(10, -20, 0)))
        sk.addConstraint(Sketcher.Constraint("Horizontal", a))
        sk.addConstraint(Sketcher.Constraint("Horizontal", a))  # redundant zum vorigen (Nr. 2)
        sk.addConstraint(Sketcher.Constraint("DistanceX", b, 1, b, 2, 10))
        sk.addConstraint(Sketcher.Constraint("DistanceX", b, 1, b, 2, 12))  # widerspricht dem vorigen
        sk.solve()
        self.assertEqual(sk.RedundantConstraints, [2])
        self.assertEqual(sorted(sk.ConflictingConstraints), [3, 4])
        sk.delConstraint(3)  # zweites DistanceX
        sk.delConstraint(1)  # zweites Horizontal
        self.assertEqual(sk.solve(), 0)
        self.assertEqual(sk.DoF, dofs + 4 + 4 - 1 - 1)
