# SPDX-License-Identifier: LGPL-2.1-or-later
"""Zufalls-Workflows: zufällige, aber per Seed reproduzierbare Folgen echter Arbeitsschritte (Skizze auf Fläche, Kante
projizieren, Extrude/Cut durch mehrere Körper, Press Pull, Rundung, Löschen, Zurückrollen, Umsortieren, Speichern und
Laden), auf denselben Wegen wie die Oberfläche. Nach jedem Schritt gelten die Invarianten aus model_problems; nach
Speichern und Laden müssen alle Körper dasselbe Volumen haben. So fallen Kombinationen auf, an die beim Schreiben
gezielter Tests niemand denkt (der Abhängigkeitskreis aus "Monitor Light" entstand erst nach ~20 Schritten).

    FUZZ_SEEDS=200 FUZZ_STEPS=25 PATTERN=test_fuzz.py tests/design/run.sh      → länger suchen
    FUZZ_SEED=17 PATTERN=test_fuzz.py tests/design/run.sh                      → einen Fund nachstellen
    FUZZ_FILES=/pfad/a.mycad:/pfad/b.mycad PATTERN=test_fuzz.py …              → von echten Dateien aus (Kopie)
"""
import random
import shutil
import tempfile

from design import *

SEEDS = [int(os.environ["FUZZ_SEED"])] if os.environ.get("FUZZ_SEED") else range(int(os.environ.get("FUZZ_SEEDS", 12)))
STEPS = int(os.environ.get("FUZZ_STEPS", 14))
FILES = [f for f in os.environ.get("FUZZ_FILES", "").split(":") if f]


def bodies(doc):
    return [o for o in doc.Objects if o.TypeId == "Design::Body" and not o.Shape.isNull() and o.Shape.Volume > 1e-6]


def rolled_back(obj):
    items, marker = Design.timeline(obj.Document), Design.rollbackMarker(obj.Document)
    return 0 <= marker <= items.index(obj) if obj in items else False


def planar_faces(b):
    return ["Face%d" % i for i, f in enumerate(b.Shape.Faces, 1) if f.Surface.TypeId == "Part::GeomPlane" and f.Area > 1]


def volumes(doc):
    return {b.Name: round(b.Shape.Volume, 2) for b in bodies(doc)}


class Workflow:
    """Ein Lauf: rng wählt Schritte und Werte, log hält fest, was geschah (für die Fehlermeldung)"""

    def __init__(self, doc, rng):
        self.doc, self.rng, self.log = doc, rng, []

    def pick(self, items):
        return self.rng.choice(items) if items else None

    # --- Schritte; jeder gibt eine Beschreibung zurück oder None (nicht möglich) ---------------------------------------
    def box(self):
        x, y = self.rng.uniform(-40, 40), self.rng.uniform(-40, 40)
        w, d, h = self.rng.uniform(5, 30), self.rng.uniform(5, 30), self.rng.uniform(3, 20)
        _, b = extrude(self.doc, sketch(self.doc, rect(x, y, x + w, y + d)), h)
        return "box %s at (%.1f, %.1f) %.1f x %.1f x %.1f" % (b.Name, x, y, w, d, h)

    def sketch_on_face(self):
        b = self.pick(bodies(self.doc))
        face = self.pick(planar_faces(b)) if b else None
        if not face:
            return None
        obj, sub = Design.stableRef(b, face)  # wie "Create Sketch" auf einer Körperfläche
        sk = sketch(self.doc, [], support=(obj, sub))
        f = b.Shape.getElement(face)
        c = sk.getGlobalPlacement().inverse().multVec(f.CenterOfMass)
        r = max(0.5, math.sqrt(f.Area) / self.rng.uniform(3, 8))
        geos = rect(c.x - r, c.y - r, c.x + r, c.y + r) if self.rng.random() < 0.6 else circle(c.x, c.y, r)
        for g in geos:
            sk.addGeometry(g)
        text = "sketch %s on %s.%s" % (sk.Name, b.Name, face)
        if self.rng.random() < 0.5:  # Körperkante projizieren / Maß an Körperkante: die Oberfläche gibt den Body selbst
            edge = "Edge%d" % self.rng.randint(1, len(b.Shape.Edges))
            sk.addExternal(b.Name, edge)
            text += " + external %s.%s" % (b.Name, edge)
        self.doc.recompute()
        return text

    def extrude_last(self):
        # nur Skizzen vor dem Marker: zurückgerollte sind in der Oberfläche nicht wählbar
        sketches = [o for o in Design.timeline(self.doc) if o.TypeId == "Sketcher::SketchObject" and not rolled_back(o)]
        sk = sketches[-1] if sketches else None
        if not sk or not profiles(sk).Shape.Faces:
            return None
        d = self.rng.choice([-1, 1]) * self.rng.uniform(1, 40)
        op = self.rng.choice(["New Body", "Join", "Cut", "Cut"])
        targets = []
        if op != "New Body":
            targets = self.rng.sample(bodies(self.doc), k=min(len(bodies(self.doc)), self.rng.randint(1, 3)))
            if not targets:
                return None
        f, _ = extrude(self.doc, sk, abs(d), op=op, bodies=targets, Reversed=d < 0)
        return "extrude %s %s %.1f into %s" % (f.Name, op, d, [t.Name for t in targets])

    def press_pull(self):
        b = self.pick(bodies(self.doc))
        face = self.pick(planar_faces(b)) if b else None
        if not face:
            return None
        d = self.rng.choice([-1, 1]) * self.rng.uniform(0.5, 30)
        others = [o for o in bodies(self.doc) if o is not b] if d < 0 else []
        targets = [b] + self.rng.sample(others, k=min(len(others), self.rng.randint(0, 2)))
        pull = feature(self.doc, "Design::PressPull", Design.componentOf(b), Edges=[face], Distance=d)
        Design.attachToBodies(pull, targets)
        self.doc.recompute()
        return "press pull %s %s.%s %.1f through %s" % (pull.Name, b.Name, face, d, [t.Name for t in targets])

    def fillet(self):
        b = self.pick(bodies(self.doc))
        if not b or not b.Shape.Edges:
            return None
        edge = "Edge%d" % self.rng.randint(1, len(b.Shape.Edges))
        f = dress(self.doc, "Design::Fillet", b, [edge], Size=self.rng.uniform(0.2, 2))
        return "fillet %s %s.%s" % (f.Name, b.Name, edge)

    def delete(self):
        obj = self.pick(Design.timeline(self.doc))
        if not obj:
            return None
        name = obj.Name
        Design.removeFromTimeline(obj)
        self.doc.recompute()
        return "delete " + name

    def rollback(self):
        n = len(Design.timeline(self.doc))
        at = self.rng.choice([-1, -1, self.rng.randint(0, max(0, n - 1))])
        Design.setRollbackMarker(self.doc, at)
        return "rollback marker %d" % at

    def move(self):
        items = Design.timeline(self.doc)
        obj = self.pick(items)
        if not obj:
            return None
        to = self.rng.randint(0, len(items) - 1)
        try:
            Design.moveInTimeline(obj, to)
        except ValueError:
            return None  # nicht erlaubt (abhängig): die Oberfläche sagt das auch nur
        self.doc.recompute()
        return "move %s to %d" % (obj.Name, to)

    def edit_distance(self):
        f = self.pick([o for o in self.doc.Objects if o.TypeId in ("Design::Extrude", "Design::PressPull")])
        if not f:
            return None
        d = self.rng.uniform(0.5, 40)
        f.Distance = d if f.TypeId == "Design::Extrude" else self.rng.choice([-1, 1]) * d
        self.doc.recompute()
        return "edit %s distance %.1f" % (f.Name, f.Distance.Value)

    def save_reload(self):
        before = volumes(self.doc)
        self.doc = save_and_reload(self.doc)
        self.doc.recompute()
        after = volumes(self.doc)
        if before != after:
            raise AssertionError("save and reload changed bodies: %s -> %s" % (before, after))
        return "save and reload"

    STEPS = [(box, 3), (sketch_on_face, 4), (extrude_last, 5), (press_pull, 2), (fillet, 1), (delete, 1), (rollback, 1),
             (move, 1), (edit_distance, 2), (save_reload, 1)]

    def step(self):
        fns, weights = zip(*self.STEPS)
        fn = self.rng.choices(fns, weights)[0]
        try:
            text = fn(self)
        except (AssertionError, AttributeError, TypeError, NameError):  # Fehler im Test oder echter Befund
            raise
        except Exception as e:  # Schritt nicht möglich (FreeCAD/OCC lehnt ab): die Oberfläche zeigt dann nur einen Hinweis
            text = "%s refused: %s" % (fn.__name__, str(e).splitlines()[0][:80] if str(e) else type(e).__name__)
        if text:
            self.log.append(text)


class Fuzz(DesignTest):
    def run_seed(self, seed, start=None):
        print("fuzz seed %d%s" % (seed, " on " + start if start else ""), flush=True)  # bricht der Prozess ab: welcher
        wf = Workflow(self.doc if start is None else App.openDocument(start), random.Random(seed))
        if start is None:
            wf.box()
        for i in range(STEPS):
            wf.step()
            problems = model_problems(wf.doc)
            if problems:
                self.fail("FUZZ_SEED=%d%s, after step %d:\n  %s\nproblems:\n  %s" % (
                    seed, " FUZZ_FILES=" + start if start else "", i + 1, "\n  ".join(wf.log), "\n  ".join(problems)))

    def test_random_workflows(self):
        for seed in SEEDS:
            with self.subTest(seed=seed):
                for d in list(App.listDocuments()):
                    App.closeDocument(d)
                self.doc = new_doc("Fuzz%d" % seed)
                self.run_seed(seed)

    def test_random_workflows_on_real_files(self):
        if not FILES:
            self.skipTest("FUZZ_FILES not set")
        for path in FILES:
            for seed in SEEDS:
                with self.subTest(file=path, seed=seed):
                    for d in list(App.listDocuments()):
                        App.closeDocument(d)
                    copy = os.path.join(tempfile.mkdtemp(), "real.FCStd")
                    shutil.copy(path, copy)
                    self.run_seed(seed, copy)
