# SPDX-License-Identifier: LGPL-2.1-or-later
"""Härtetest (kein CI-Test, läuft lange): baut die Skizzen eines echten Designs zufällig um (Kreis um einen Kreis, Linie
quer, Kreis um einen Eckpunkt) und prüft: kein Körper ändert sich, keine Warnung, und nach dem Zurücksetzen der Skizze
ist alles wie vorher. Hält beim ersten Fehler an.
  podman run --rm -v "$PWD:/workspace" -w /workspace -e FILE="tests/projects/ConceptKey press pull.mycad" -e SEED=1 \
      -e N=40 mycad-dev build/bin/FreeCADCmd tests/design/stress_profiles.py
Stand 2026-11-25: Seeds 1–15 je 40 Versuche grün (test_stress_profiles läuft Seed 3 im Kleinen mit)."""
import FreeCAD as App, Part, Design, random, os, sys, math
V = App.Vector
SEED = int(os.environ.get("SEED", "1")); N = int(os.environ.get("N", "40"))
rng = random.Random(SEED)
d = App.openDocument(os.environ["FILE"])
d.recompute()
bodies = [o for o in d.Objects if o.TypeId == "Design::Body"]
def state():
    return {b.Label: (round(b.Shape.Volume, 1), b.Shape.isValid()) for b in bodies}
def trouble():
    return [(o.Label, t[:90]) for o, t in Design.problems(d)] + [(o.Label, o.Warning[:90]) for o in d.Objects if getattr(o, "Warning", "")]
base, base_trouble = state(), trouble()
print("base", base, "trouble", base_trouble)
sketches = []
for o in d.Objects:
    if o.TypeId == "Design::Profiles" and o.Sketch and any(hasattr(u, "ProfileKeys") for u in o.InList):
        sketches.append(o.Sketch)
print("sketches", [s.Label for s in sketches])
fails = 0
for trial in range(N):
    sk = rng.choice(sketches)
    geo, cons = sk.Geometry, sk.Constraints
    circles = [g for g in geo if isinstance(g, Part.Circle)]
    verts = [p for g in geo if hasattr(g, "StartPoint") and not isinstance(g, Part.Circle) for p in (g.StartPoint, g.EndPoint)]
    bb = sk.Shape.BoundBox
    kind = rng.choice(["ring", "line", "vertexcircle"])
    if kind == "ring" and circles:
        c = rng.choice(circles); new = Part.Circle(c.Center, V(0, 0, 1), c.Radius * rng.uniform(1.15, 1.6))
    elif kind == "vertexcircle" and verts:
        p = rng.choice(verts); new = Part.Circle(p, V(0, 0, 1), rng.uniform(0.5, 4))
    else:
        kind = "line"
        # Skizzen-Koordinaten: Geometrie liegt lokal; bb ist global, daher aus der Geometrie selbst
        xs = [p.x for p in verts] or [0, 10]; ys = [p.y for p in verts] or [0, 10]
        x0, x1, y0, y1 = min(xs) - 5, max(xs) + 5, min(ys) - 5, max(ys) + 5
        if rng.random() < 0.5:
            x = rng.uniform(x0, x1); new = Part.LineSegment(V(x, y0, 0), V(x + rng.uniform(-3, 3), y1, 0))
        else:
            y = rng.uniform(y0, y1); new = Part.LineSegment(V(x0, y, 0), V(x1, y + rng.uniform(-3, 3), 0))
    sk.addGeometry(new)
    d.recompute()
    after, t1 = state(), trouble()
    sk.Geometry = geo; sk.Constraints = cons
    d.recompute()
    back, t2 = state(), trouble()
    ok = after == base and back == base and t1 == base_trouble and t2 == base_trouble
    if not ok:
        fails += 1
        print("FAIL trial %d %s in %s: %s" % (trial, kind, sk.Label, repr(new)[:120]))
        print("   changed:", {k: (base[k], after[k]) for k in base if after[k] != base[k]}, "trouble", t1)
        print("   after undo:", {k: (base[k], back[k]) for k in base if back[k] != base[k]}, "trouble", t2)
        break
        if back != base:  # Datei kaputt: neu laden, sonst zählen alle weiteren mit
            App.closeDocument(d.Name); d = App.openDocument(os.environ["FILE"]); d.recompute()
            bodies = [o for o in d.Objects if o.TypeId == "Design::Body"]
            sketches = [d.getObject(s.Name) for s in sketches]
print("DONE seed %d trials %d fails %d" % (SEED, N, fails))
