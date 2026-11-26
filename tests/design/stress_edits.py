# SPDX-License-Identifier: LGPL-2.1-or-later
"""Härtetest 2 (kein CI-Test, läuft lange): ein Halter wie aus dem Alltag (Platte mit Maßen, Bohrungen auf der
Deckfläche, Eckrundungen, Zapfen mit Fase, Tasche in der Vorderseite, Schlitz mit Maß zur projizierten Kante) wird
zufällig bearbeitet wie von einem Menschen: Maße ändern (auch mehrere, auch drastisch bis es nicht mehr geht), in alten
Skizzen weiterzeichnen, Schritte unterdrücken, zurückrollen, löschen und rückgängig, speichern und wieder öffnen.
Geprüft wird nach jedem Schritt:
  - das bearbeitete Teil gleicht einem FRISCH gebauten Teil mit denselben Maßen (kein Bezug ist still gewandert),
  - was nichts ändern darf (Linie in alter Skizze, Unterdrücken und zurück, Zurückrollen und vor, Speichern und Laden,
    Rückgängig), ändert nichts,
  - kein Abhängigkeitskreis, nichts bleibt ungerechnet liegen.
Hält beim ersten Fehler an.
  podman run --rm -v "$PWD:/workspace" -w /workspace -e SEED=1 -e N=40 mycad-dev build/bin/FreeCADCmd tests/design/stress_edits.py
"""
import math
import os
import random
import sys
import tempfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import FreeCAD as App, Part, Sketcher, Design
import design as D

import functools
print = functools.partial(print, flush=True)  # FreeCADCmd verwirft bei sys.exit, was noch im Puffer steht
V = App.Vector
C = Sketcher.Constraint
SEED = int(os.environ.get("SEED", "1")); N = int(os.environ.get("N", "40"))
rng = random.Random(SEED)
MODEL = int(os.environ.get("MODEL") or 1)  # 2: dazu Bohrung durch den Zapfen (vor der Fase) und Drücken/Ziehen rechts
BASE = dict(W=80.0, D=50.0, H=10.0, hole=3.0, fillet=4.0, boss=8.0, boss_h=6.0, chamfer=1.0, pocket=2.0, slot=3.0)
RANGE = dict(W=(50, 140), D=(40, 90), H=(6, 20), hole=(2, 6), fillet=(1, 8), boss=(6, 11), boss_h=(3, 10),
             chamfer=(0.5, 2), pocket=(1, 4), slot=(1, 5))
if MODEL == 2:
    BASE.update(bore=2.5, pull=3.0)
    RANGE.update(bore=(1.5, 4), pull=(1, 8))


def loc(sk, p):
    return sk.getGlobalPlacement().inverse().multVec(p)


def fixed_circle(sk, center, r):
    """Kreis an globaler Stelle mit Radius- und Lagemaßen (bleibt beim Ändern des Radius, wo er ist)"""
    c = loc(sk, center)
    i = sk.addGeometry(Part.Circle(V(c.x, c.y, 0), V(0, 0, 1), r))
    sk.addConstraint(C("Radius", i, r))
    sk.addConstraint(C("DistanceX", -1, 1, i, 3, c.x))
    sk.addConstraint(C("DistanceY", -1, 1, i, 3, c.y))
    return i


def build(d, P):
    """der Halter; N: Namen der Objekte (für nach dem Laden)"""
    W, Dp, H = P["W"], P["D"], P["H"]
    base = D.sketch(d, D.rect(0, 0, W, Dp))
    for c in [C("Coincident", i, 2, (i + 1) % 4, 1) for i in range(4)] + [
            C("Horizontal", 0), C("Horizontal", 2), C("Vertical", 1), C("Vertical", 3), C("Coincident", 0, 1, -1, 1),
            C("DistanceX", 0, 1, 0, 2, W), C("DistanceY", 1, 1, 1, 2, Dp)]:
        base.addConstraint(c)
    d.recompute()
    ext, b = D.extrude(d, base, H)
    top = lambda: D.face_where(b, lambda c, f: abs(c.z - H) < 1e-6 and f.Area > 100)
    holes = D.sketch(d, [], support=(b, top()))
    fixed_circle(holes, V(15, 15, H), P["hole"]); fixed_circle(holes, V(35, 15, H), P["hole"])
    d.recompute()
    cut, _ = D.extrude(d, holes, H, op="Cut", bodies=[b], Reversed=True)
    fillets = []
    for cx, cy in ((0, 0), (W, 0), (W, Dp), (0, Dp)):
        e = D.edge_where(b, lambda p, cx=cx, cy=cy: abs(p.x - cx) < 1e-6 and abs(p.y - cy) < 1e-6)
        fillets.append(D.dress(d, "Design::Fillet", b, [e], Size=P["fillet"]))
    boss = D.sketch(d, [], support=(b, top()))
    fixed_circle(boss, V(30, 28, H), P["boss"])
    d.recompute()
    join, _ = D.extrude(d, boss, P["boss_h"], op="Join", bodies=[b])
    z = H + P["boss_h"]
    bore = bcut = None
    if MODEL == 2:  # Bohrung von der Deckfläche des Zapfens durch ihn hindurch; die Fase danach verändert diese Fläche
        bore = D.sketch(d, [], support=(b, D.face_where(b, lambda c, f: abs(c.z - z) < 1e-6)))
        fixed_circle(bore, V(30, 28, z), P["bore"])
        d.recompute()
        bcut, _ = D.extrude(d, bore, P["boss_h"], op="Cut", bodies=[b], Reversed=True)
    ring = ["Edge%d" % (i + 1) for i, e in enumerate(b.Shape.Edges) if abs(e.BoundBox.ZMin - z) < 1e-6
            and abs(e.BoundBox.ZMax - z) < 1e-6 and abs(e.Length - 2 * math.pi * P["boss"]) < 1e-3][0]
    chamfer = D.dress(d, "Design::Chamfer", b, [ring], Size=P["chamfer"])
    front = D.face_where(b, lambda c, f: abs(c.y) < 1e-6 and f.Surface.TypeId == "Part::GeomPlane")
    pocket = D.sketch(d, [], support=(b, front))
    p0, p1 = loc(pocket, V(10, 0, 1.5)), loc(pocket, V(22, 0, 4.5))
    for g in D.rect(min(p0.x, p1.x), min(p0.y, p1.y), max(p0.x, p1.x), max(p0.y, p1.y)):
        pocket.addGeometry(g)
    d.recompute()
    pcut, _ = D.extrude(d, pocket, P["pocket"], op="Cut", bodies=[b], Reversed=True)
    # Schlitz an der rechten Kante: sein Abstand zur projizierten Kante ist ein Maß, er wandert also mit der Breite
    slot = D.sketch(d, [], support=(b, top()))
    edge = D.edge_where(b, lambda p: abs(p.x - W) < 1e-6 and abs(p.z - H) < 1e-6)
    slot.addExternal(b.Name, edge)
    a, c2 = loc(slot, V(W - 12, 10, H)), loc(slot, V(W - 6, 20, H))
    for g in D.rect(a.x, a.y, c2.x, c2.y):
        slot.addGeometry(g)
    for c in [C("Coincident", i, 2, (i + 1) % 4, 1) for i in range(4)] + [
            C("Horizontal", 0), C("Horizontal", 2), C("Vertical", 1), C("Vertical", 3),
            C("DistanceX", 0, 1, 0, 2, 6), C("DistanceY", 1, 1, 1, 2, 10), C("DistanceY", -1, 1, 0, 1, a.y),
            C("DistanceX", 1, 1, -3, 1, 6)]:
        slot.addConstraint(c)
    d.recompute()
    scut, _ = D.extrude(d, slot, P["slot"], op="Cut", bodies=[b], Reversed=True)
    pull = None
    if MODEL == 2:  # rechte Seitenfläche herausziehen (zwischen den Eckrundungen)
        right = D.face_where(b, lambda c, f: abs(c.x - W) < 1e-6 and f.Surface.TypeId == "Part::GeomPlane")
        pull = D.dress(d, "Design::PressPull", b, [right], Distance=P["pull"])
    for o in d.Objects:
        if o.TypeId in ("Sketcher::SketchObject", "Design::Profiles"):
            o.Visibility = False
    d.recompute()
    return dict(bore=bore and bore.Name, bcut=bcut and bcut.Name, pull=pull and pull.Name,
                base=base.Name, ext=ext.Name, body=b.Name, holes=holes.Name, cut=cut.Name, fillets=[f.Name for f in fillets],
                boss=boss.Name, join=join.Name, chamfer=chamfer.Name, pocket=pocket.Name, pcut=pcut.Name, slot=slot.Name,
                scut=scut.Name)


def datum(sk, kind, nth, value):
    i = [k for k, c in enumerate(sk.Constraints) if c.Type == kind][nth]
    sk.setDatum(i, App.Units.Quantity("%.6f mm" % value))


def apply(d, names, P):
    """Maße P am bestehenden Teil einstellen, so wie über Maßfeld und Panels"""
    g = lambda k: d.getObject(names[k])
    datum(g("base"), "DistanceX", 0, P["W"]); datum(g("base"), "DistanceY", 0, P["D"])
    g("ext").Distance = P["H"]; g("cut").Distance = P["H"]
    for n in (0, 1):
        datum(g("holes"), "Radius", n, P["hole"])
    for f in names["fillets"]:
        d.getObject(f).Size = P["fillet"]
    datum(g("boss"), "Radius", 0, P["boss"])
    g("join").Distance = P["boss_h"]; g("chamfer").Size = P["chamfer"]
    g("pcut").Distance = P["pocket"]; g("scut").Distance = P["slot"]
    if MODEL == 2:
        datum(g("bore"), "Radius", 0, P["bore"]); g("bcut").Distance = P["boss_h"]; g("pull").Distance = P["pull"]
    d.recompute()


def shape_key(d, names):
    s = d.getObject(names["body"]).Shape
    if s.isNull():
        return None
    bb, c = s.BoundBox, s.CenterOfMass
    return (s.Volume, bb.XLength, bb.YLength, bb.ZLength, c.x, c.y, c.z, float(s.isValid()))


def same(a, b, tol=2e-4):
    if a is None or b is None:
        return a is b
    return all(abs(x - y) <= tol * max(1.0, abs(x), abs(y)) for x, y in zip(a, b))


def trouble(d):
    return sorted([(o.Label, t[:80]) for o, t in Design.problems(d)]
                  + [(o.Label, o.Warning[:80]) for o in d.Objects if getattr(o, "Warning", "")])


def fresh(P):
    """dasselbe Teil frisch gebaut: der Vergleich"""
    f = App.newDocument("Fresh"); Design.root(f)
    try:
        names = build(f, P)
        return shape_key(f, names), trouble(f)
    except Exception as e:  # mit diesen Maßen gar nicht baubar (Kante weg): kein Vergleich
        return None, [("build", str(e)[:80])]
    finally:
        App.closeDocument(f.Name)


def fail(what, **info):
    print("FAIL seed %d trial %d: %s" % (SEED, trial, what))
    for k, v in info.items():
        print("   %s: %s" % (k, v))
    print("   sizes:", ",".join("%s:%s" % kv for kv in sorted(P.items())))
    print("   log:", " | ".join(log[-8:]))
    os.environ["DEBUG"] = "1"
    debug("at the failure")
    for k in feature_keys:
        f = d.getObject(names[k])
        print("  %s %s: faces=%d edges=%d state=%s warn=%r" % (k, f.Name, len(f.Shape.Faces), len(f.Shape.Edges), f.State,
                                                           getattr(f, "Warning", "")[:60]))
    try:  # Schritt für Schritt gegen ein frisch gebautes Teil: wo beginnt der Unterschied?
        f = App.newDocument("Fresh"); Design.root(f)
        fn = build(f, P)
        keys = feature_keys[:3] + ["fillets"] + feature_keys[3:]
        vols = lambda doc, nn: [round(doc.getObject(n).Shape.Volume, 2) for k in keys for n in (nn[k] if k == "fillets" else [nn[k]])]
        print("  volumes edited:", vols(d, names))
        print("  volumes fresh: ", vols(f, fn))
    except Exception as e:
        print("  no fresh comparison:", e)
    for k in ("holes", "boss", "pocket", "slot"):
        sk = d.getObject(names[k])
        xs = [p.x for g in sk.Geometry if isinstance(g, Part.LineSegment) for p in (g.StartPoint, g.EndPoint)]
        print("  sketch %s %s: support=%s external=%s ext lines=%s x=%s place=%s warn=%r" % (
            k, sk.Name, [(o.Name, e) for o, e in sk.AttachmentSupport], [(o.Name, e) for o, e in sk.ExternalGeometry],
            [(round(g.StartPoint.x, 2), round(g.StartPoint.y, 2), round(g.EndPoint.x, 2), round(g.EndPoint.y, 2))
             for g in sk.ExternalGeo[2:] if isinstance(g, Part.LineSegment)],
            (round(min(xs), 2), round(max(xs), 2)) if xs else None, sk.Placement.Base, getattr(sk, "Warning", "")))
    sys.exit(0)


def check_model(d, where):
    problems = D.model_problems(d)
    if problems:
        fail("model problems " + where, problems=problems)


d = App.newDocument("Edited"); Design.root(d)
d.UndoMode = 1
P = dict(BASE)
names = build(d, P)
base_key, base_trouble = shape_key(d, names), trouble(d)
print("base", base_key, base_trouble)
if base_trouble:
    print("FAIL base model has trouble"); sys.exit(0)
log, soft = [], []
feature_keys = ["ext", "cut", "join", "chamfer", "pcut", "scut"] + (["bcut", "pull"] if MODEL == 2 else [])


def features():
    return [d.getObject(names[k]) for k in feature_keys] + [d.getObject(f) for f in names["fillets"]]


def op_params(change=None):
    """ein bis drei Maße ändern, bleiben so; Vergleich mit dem frisch gebauten Teil"""
    global P
    Q = dict(P)
    for k in rng.sample(sorted(RANGE), rng.randint(1, 3)) if change is None else []:
        Q[k] = round(rng.uniform(*RANGE[k]), 2)
    Q.update(change or {})
    log.append("params %s" % {k: Q[k] for k in Q if Q[k] != P[k]})
    apply(d, names, Q)
    P = Q
    check_model(d, "after a size change")
    want, want_trouble = fresh(P)
    got, got_trouble = shape_key(d, names), trouble(d)
    if want_trouble:  # frisch gebaut geht es auch nicht: dann zählt nur, dass nichts hängt
        return
    if got_trouble or not same(got, want):
        fail("edited part differs from a freshly built one", params=P, edited=got, fresh=want, trouble=got_trouble)


def op_home():
    """zurück zu den Ausgangsmaßen: genau das Ausgangsteil"""
    global P
    log.append("home")
    P = dict(BASE)
    apply(d, names, P)
    got, t = shape_key(d, names), trouble(d)
    if t or not same(got, base_key):
        fail("back at the first sizes the part is not the first part", edited=got, first=base_key, trouble=t)


def debug(when):
    """DEBUG=1: was sich Rundungen und Fase gerade merken"""
    if os.environ.get("DEBUG"):
        e = d.getObject(names["ext"])
        print("  %s base extrude: volume %.2f faces %d keys %s subs %s" % (when, e.Shape.Volume, len(e.Shape.Faces), list(e.ProfileKeys), list(e.Profile[1])))
        sk = d.getObject(names["slot"])
        print("  %s slot at z=%.3f support=%s warn=%r" % (when, sk.Placement.Base.z, [(o.Name, e) for o, e in sk.AttachmentSupport], getattr(sk, "Warning", "")[:30]))
        print("  %s slot external=%s lines=%s state=%s" % (when, [(o.Name, e) for o, e in sk.ExternalGeometry],
              [(round(g.StartPoint.x, 2), round(g.StartPoint.y, 2), round(g.EndPoint.x, 2), round(g.EndPoint.y, 2))
               for g in sk.ExternalGeo[2:] if isinstance(g, Part.LineSegment)], sk.State))
        for n in names["fillets"] + [names["chamfer"]]:
            f = d.getObject(n)
            print("  %s %s: %s maps=%s hints=%s state=%s warn=%r" % (when, n, list(f.Edges), list(f.ElementMaps),
                  [" ".join("%.1f" % float(x) for x in h.split()) for h in f.ElementHints], f.State, f.Warning[:40]))
            if os.environ.get("DEBUG") == "2" and f.ElementMaps and f.BaseFeatures and f.BaseFeatures[0]:
                try:
                    print("     history:", f.BaseFeatures[0].Shape.getElementHistory(f.ElementMaps[0]))
                    import re
                    for hid in re.findall(r"#([0-9a-f]+)", f.ElementMaps[0]):
                        sid = d.Hasher.getID(int(hid, 16))
                        print("     #%s =" % hid, sid.Data if sid else None, getattr(sid, "Related", ""))
                except Exception as e:
                    print("     history failed:", e)


def op_drastic(k=None):
    """ein Maß so, dass etwas scheitern muss, dann zurück: wie vorher, nichts bleibt hängen"""
    before, t0 = shape_key(d, names), trouble(d)
    Q = dict(P)
    k = k or rng.choice(["W", "D", "H", "fillet", "hole", "boss", "chamfer"])
    Q[k] = {"W": 4.0, "D": 3.0, "H": 0.6, "fillet": 60.0, "hole": 40.0, "boss": 70.0, "chamfer": 30.0}[k]
    log.append("drastic %s=%s" % (k, Q[k]))
    debug("before")
    if os.environ.get("DEBUG"):
        print("  recompute order:", [o.Name for o in d.getObject(names["slot"]).OutListRecursive if o.TypeId.startswith("Design::E")])
    try:
        apply(d, names, Q)
    except Exception as e:
        log.append("refused: %s" % str(e)[:60])
    debug("impossible")
    check_model(d, "in the impossible state")
    apply(d, names, P)
    debug("back")
    after, t1 = shape_key(d, names), trouble(d)
    if t1 != t0 or not same(after, before):
        fail("after an impossible size and back the part is not as before", before=before, after=after, trouble=t1, was=t0)


def op_scribble(fixed=None):
    """in einer alten Skizze weiterzeichnen: Linie quer oder Kreis um einen Kreis/Eckpunkt; nichts ändert sich, auch
    nicht nach dem Entfernen"""
    before, t0 = shape_key(d, names), trouble(d)
    sk = d.getObject(names[fixed[0] if fixed else rng.choice(["base", "holes", "boss", "pocket", "slot"] + (["bore"] if MODEL == 2 else []))])
    geo = sk.Geometry
    circles = [g for g in geo if isinstance(g, Part.Circle)]
    verts = [p for g in geo if isinstance(g, Part.LineSegment) for p in (g.StartPoint, g.EndPoint)]
    kind = rng.choice(["ring", "line", "vertexcircle"])
    if kind == "ring" and circles:
        c = rng.choice(circles); new = Part.Circle(c.Center, V(0, 0, 1), c.Radius * rng.uniform(1.15, 1.6))
    elif kind == "vertexcircle" and verts:
        new = Part.Circle(rng.choice(verts), V(0, 0, 1), rng.uniform(0.5, 4))
    else:
        kind = "line"
        pts = verts or [c.Center for c in circles]
        xs, ys = [p.x for p in pts], [p.y for p in pts]
        x0, x1, y0, y1 = min(xs) - 8, max(xs) + 8, min(ys) - 8, max(ys) + 8
        if rng.random() < 0.5:
            x = rng.uniform(x0, x1); new = Part.LineSegment(V(x, y0, 0), V(x + rng.uniform(-3, 3), y1, 0))
        else:
            y = rng.uniform(y0, y1); new = Part.LineSegment(V(x0, y, 0), V(x1, y + rng.uniform(-3, 3), 0))
    meanwhile = None
    if fixed:
        kind, new, meanwhile = fixed[1], fixed[2], fixed[3]
    log.append("scribble %s in %s %s" % (kind, sk.Label, repr(new)[:70]))
    i = sk.addGeometry(new)
    d.recompute()
    check_model(d, "after drawing into an old sketch")
    mid, t1 = shape_key(d, names), trouble(d)
    if t1 != t0 or not same(mid, before):
        fail("drawing into an old sketch changed the part", before=before, after=mid, trouble=t1, was=t0)
    debug("with the extra geometry")
    # mit der neuen Geometrie darin auch noch ein Maß ändern und zurück
    if meanwhile or (not fixed and rng.random() < 0.5):
        Q = dict(P); k = rng.choice(["W", "D", "H"]); Q[k] = round(rng.uniform(*RANGE[k]), 2)
        if meanwhile:
            Q = dict(P); k = meanwhile[0]; Q[k] = meanwhile[1]
        log.append("  with it %s=%s and back" % (k, Q[k]))
        apply(d, names, Q)
        debug("with it %s=%s" % (k, Q[k]))
        apply(d, names, P)
        debug("size back")
    sk.delGeometry(i)
    d.recompute()
    debug("geometry removed")
    after, t2 = shape_key(d, names), trouble(d)
    if not same(after, before) or any("check that it still uses" not in text for _, text in t2 if (_, text) not in t0):
        fail("after removing the extra geometry the part is not as before", before=before, after=after, trouble=t2, was=t0)
    if t2 != t0:  # bekannt: Teil stimmt, aber eine Warnung "Modell hat sich geändert" bleibt stehen (Zwischenstand mit
        soft.append(log[-1][:60])  # zusammengesetztem Profil und geändertem Maß); bestätigen wie ein Mensch
        for o in d.Objects:
            if getattr(o, "Warning", "").startswith("The model changed under this step"):
                o.Warning = ""
        d.recompute()


def op_suppress():
    before, t0 = shape_key(d, names), trouble(d)
    f = rng.choice(features())
    log.append("suppress %s and back" % f.Label)
    f.Suppressed = True
    d.recompute()
    check_model(d, "with a suppressed step")
    if rng.random() < 0.4:
        Q = dict(P); k = rng.choice(["W", "D", "H"]); Q[k] = round(rng.uniform(*RANGE[k]), 2)
        log.append("  meanwhile %s=%s and back" % (k, Q[k]))
        apply(d, names, Q); apply(d, names, P)
    f.Suppressed = False
    d.recompute()
    after, t1 = shape_key(d, names), trouble(d)
    if t1 != t0 or not same(after, before):
        fail("suppress and unsuppress changed the part", step=f.Label, before=before, after=after, trouble=t1, was=t0)


def op_rollback(fixed=None):
    before, t0 = shape_key(d, names), trouble(d)
    n = len(Design.timeline(d))
    at = fixed or rng.randint(1, n - 1)
    log.append("roll back to %d and forward" % at)
    debug("before rolling back")
    Design.setRollbackMarker(d, at)
    d.recompute()
    debug("rolled back to %d" % at)
    check_model(d, "rolled back")
    if not fixed and rng.random() < 0.4:
        Q = dict(P); k = rng.choice(["W", "D", "H"]); Q[k] = round(rng.uniform(*RANGE[k]), 2)
        log.append("  meanwhile %s=%s and back" % (k, Q[k]))
        try:
            apply(d, names, Q); apply(d, names, P)
        except Exception as e:
            log.append("  refused: %s" % str(e)[:60])
    Design.setRollbackMarker(d, -1)
    d.recompute()
    after, t1 = shape_key(d, names), trouble(d)
    if t1 != t0 or not same(after, before):
        fail("roll back and forward changed the part", at=at, before=before, after=after, trouble=t1, was=t0)


def op_reload():
    global d
    before, t0 = shape_key(d, names), trouble(d)
    log.append("save and reload")
    path = os.path.join(tempfile.mkdtemp(), "edited.FCStd")
    d.saveAs(path)
    App.closeDocument(d.Name)
    d = App.openDocument(path)
    d.UndoMode = 1
    d.recompute()
    after, t1 = shape_key(d, names), trouble(d)
    if t1 != t0 or not same(after, before):
        fail("save and reload changed the part", before=before, after=after, trouble=t1, was=t0)
    check_model(d, "after reload")


def op_undo(delete=None):
    """eine Änderung (Maß oder Schritt löschen) in einer Transaktion, dann Rückgängig: wie vorher"""
    before, t0 = shape_key(d, names), trouble(d)
    what = "delete" if delete else rng.choice(["size", "delete"])
    d.openTransaction("change")
    if what == "size":
        Q = dict(P); k = rng.choice(sorted(RANGE)); Q[k] = round(rng.uniform(*RANGE[k]), 2)
        log.append("undo of %s=%s" % (k, Q[k]))
        apply(d, names, Q)
    else:
        f = d.getObject(names[delete]) if delete else rng.choice(features())
        log.append("undo of deleting %s" % f.Label)
        Design.removeFromTimeline(f)
        d.recompute()
    d.commitTransaction()
    check_model(d, "after the change that gets undone")
    d.undo()
    d.recompute()
    after, t1 = shape_key(d, names), trouble(d)
    if t1 != t0 or not same(after, before):
        fail("undo did not bring the part back", what=what, before=before, after=after, trouble=t1, was=t0)
    check_model(d, "after undo")


def op_reorder():
    """einen Schritt in der Zeitleiste verschieben (wenn MyCAD es erlaubt) und zurück: wie vorher"""
    before, t0 = shape_key(d, names), trouble(d)
    items = Design.timeline(d)
    f = rng.choice(features())
    was, to = items.index(f), rng.randint(0, len(items) - 1)
    d.openTransaction("move")
    try:
        Design.moveInTimeline(f, to)
    except ValueError:
        d.abortTransaction()
        return  # hängt von etwas ab, das dann später käme: die Oberfläche sagt das auch nur
    d.commitTransaction()
    log.append("move %s from %d to %d and back" % (f.Label, was, to))
    d.recompute()
    check_model(d, "after moving a step")
    try:
        Design.moveInTimeline(f, was)
    except ValueError:
        # zurück geht nicht immer (eine Skizze hängt an einem Zustand, in dessen Kette der Schritt jetzt steckt): dann
        # wie ein Mensch mit Rückgängig
        log.append("  back by undo")
        d.undo()
    d.recompute()
    after, t1 = shape_key(d, names), trouble(d)
    if t1 != t0 or not same(after, before):
        fail("moving a step and back changed the part", step=f.Label, to=to, before=before, after=after, trouble=t1, was=t0)


def op_redo():
    """Maß ändern, Rückgängig, Wiederholen: wie nach der Änderung; das Maß bleibt"""
    global P
    Q = dict(P); k = rng.choice(sorted(RANGE)); Q[k] = round(rng.uniform(*RANGE[k]), 2)
    log.append("undo and redo of %s=%s" % (k, Q[k]))
    d.openTransaction("change")
    apply(d, names, Q)
    d.commitTransaction()
    changed, t0 = shape_key(d, names), trouble(d)
    d.undo(); d.recompute()
    d.redo(); d.recompute()
    P = Q
    after, t1 = shape_key(d, names), trouble(d)
    if t1 != t0 or not same(after, changed):
        fail("redo did not bring the change back", what=k, changed=changed, after=after, trouble=t1, was=t0)
    check_model(d, "after redo")


OPS = [(op_reorder, 2), (op_redo, 2), (op_params, 6), (op_home, 1), (op_drastic, 2), (op_scribble, 4), (op_suppress, 2), (op_rollback, 2), (op_reload, 1),
       (op_undo, 2)]
# REPLAY="reload;drastic=hole;params=W:120,H:8;line=boss:22,27.5,38,26.6;home": einen Fund ohne Zufall nachstellen
for trial, item in enumerate([i for i in os.environ.get("REPLAY", "").replace("+", ";").split(";") if i]):
    kind, _, arg = item.partition("=")
    if kind == "params":
        op_params({k: float(v) for k, v in (kv.split(":") for kv in arg.split(","))})
    elif kind == "drastic":
        op_drastic(arg)
    elif kind == "rollback" and arg:
        op_rollback(int(arg))
    elif kind == "undodelete":
        op_undo(arg)
    elif kind in ("line", "circle"):  # line=boss:22,27.5,38,26.6 / circle=base:0,50,3.8 (Skizzenkoordinaten), dahinter
        key, _, rest = arg.partition(":")  # optional ein Maß, das währenddessen geändert und zurückgestellt wird: ,D:75
        parts = rest.split(",")
        meanwhile = None
        if ":" in parts[-1]:
            k, v = parts.pop().split(":"); meanwhile = (k, float(v))
        n = [float(v) for v in parts]
        geo = Part.LineSegment(V(n[0], n[1], 0), V(n[2], n[3], 0)) if kind == "line" else Part.Circle(V(n[0], n[1], 0), V(0, 0, 1), n[2])
        op_scribble([key, kind, geo, meanwhile])
    else:
        {"reload": op_reload, "home": op_home, "scribble": op_scribble, "suppress": op_suppress, "rollback": op_rollback,
         "undo": op_undo}[kind]()
    if not d.getObject(names["slot"]).ExternalGeometry:
        fail("the slot sketch lost its link to the projected edge")
if os.environ.get("REPLAY"):
    print("done replay: ok"); sys.exit(0)
for trial in range(N):
    fn = rng.choices([o for o, _ in OPS], [w for _, w in OPS])[0]
    fn()
    if not d.getObject(names["slot"]).ExternalGeometry:
        fail("the slot sketch lost its link to the projected edge")
trial = N
op_home()
print("done seed %d: %d trials ok, %d stale warnings %s" % (SEED, N, len(soft), soft[:2]))
