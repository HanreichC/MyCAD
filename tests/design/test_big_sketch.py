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


class BigSketch(DesignTest):
    def test_many_free_arcs_solve_fast(self):
        sk = self.doc.addObject("Sketcher::SketchObject", "Big")
        dofs = free_geometry(sk, 800)
        t = time.monotonic()
        self.assertEqual(sk.solve(), 0)
        took = time.monotonic() - t
        self.assertEqual(sk.DoF, dofs)
        self.assertLess(took, 2.0, "800 free arcs took %.1f s to solve (was 11 s)" % took)

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
