# SPDX-License-Identifier: LGPL-2.1-or-later
"""Phase 13.9 Zufallsabläufe über die Oberfläche: mit festem Startwert zufällige, aber gültige Bedienfolgen wie ein
Mensch, der herumprobiert (Werkzeug starten, ins Modell klicken, Wert tippen, OK oder Esc, Rückgängig, Wiederholen).
Findet Abstürze, Ausnahmen und kaputte Zustände, an die kein Szenario denkt. Nach jeder Runde: kein Abhängigkeitskreis,
nach dem Neuberechnen liegt nichts mehr an (wie test_fuzz headless). Ein Fund wird ein fester Test."""
import os
import random
import sys
from harness import *
sys.path.insert(0, os.path.join(os.path.dirname(os.environ["SCRIPT"]), "..", "design"))
import design as D
import Design

SEEDS = [1, 2, 3]
STEPS = 30
V = App.Vector
TOOLS = ["Design_Extrude", "Design_Fillet", "Design_Chamfer", "Design_Shell", "Design_PressPull", "Design_Hole",
         "Design_Move", "Design_Mirror", "Design_Pattern", "Design_Box", "Design_Cylinder", "Design_CreateSketch",
         "Design_OffsetPlane", "Design_Draft", "Design_Combine", "Design_Measure", "Design_Section"]
S = {"log": []}


def bodies():
    return [o for o in doc().Objects if o.TypeId == "Design::Body" and not o.Shape.isNull() and o.Shape.Volume > 1e-6]


def tidy():
    """Fenster, die ein Mensch wegklicken würde (Meldungen, Fragen); Aufgaben-Panels bleiben"""
    for m in visible(QtWidgets.QMessageBox):
        m.close()
    if Gui.ActiveDocument and Gui.ActiveDocument.getInEdit() and Gui.ActiveDocument.getInEdit().TypeId.startswith("SketcherGui"):
        Gui.ActiveDocument.resetEdit()  # aus einer offenen Skizze heraus (Zufallsklicks zeichneten sonst endlos)


def act(rng):
    kind = rng.choice(["tool", "tool", "click", "click", "type", "ok", "esc", "undo", "redo"])
    try:
        if kind == "tool":
            cmd = rng.choice(TOOLS)
            S["log"].append(cmd)
            Gui.runCommand(cmd)
        elif kind == "click":
            bs = bodies()
            if bs and rng.random() < 0.8:
                b = rng.choice(bs)
                f = rng.randrange(len(b.Shape.Faces))
                p = face_point(b, "Face%d" % (f + 1))
                S["log"].append("click %s Face%d" % (b.Label, f + 1))
                click_at(b.getGlobalPlacement().multVec(p) if hasattr(b, "getGlobalPlacement") else p)
            else:
                S["log"].append("click empty")
                view_click(rng.random(), rng.random())
        elif kind == "type":
            fields = [w for w in visible(QtWidgets.QAbstractSpinBox) if w.isEnabled()]
            if fields:
                w = rng.choice(fields)
                value = rng.choice(["0", "1", "5", "-3", "20", "0.5", "100"])
                S["log"].append("type %s into %s" % (value, w.objectName() or w.accessibleName()))
                w.setFocus(); w.selectAll(); QtTest.QTest.keyClicks(w, value)
                QtTest.QTest.keyClick(w, QtCore.Qt.Key_Tab)
        elif kind == "ok":
            S["log"].append("ok")
            buttons = [b for b in visible(QtWidgets.QPushButton) if b.text().replace("&", "") == "OK"]
            if buttons:
                buttons[0].click()
        elif kind == "esc":
            S["log"].append("esc")
            QtTest.QTest.keyClick(view().viewport(), QtCore.Qt.Key_Escape)
        else:
            S["log"].append(kind)
            Gui.runCommand("Std_Undo" if kind == "undo" else "Std_Redo")
    except Exception as e:  # ein Werkzeug, das gerade nicht geht, ist kein Fund; eine Ausnahme im Log schon
        S["log"].append("  -> %s: %s" % (type(e).__name__, e))
    tidy()


def round_start(seed):
    def f():
        for d in list(App.listDocuments().values()):
            App.closeDocument(d.Name)
        App.newDocument("Fuzz%d" % seed)
        Design.root(doc())
        Gui.runCommand("Std_ViewIsometric")
        _, b = D.box(doc(), 40, 30, 10)
        D.extrude(doc(), D.sketch(doc(), D.circle(10, 10, 4), App.Placement(V(0, 0, 10), App.Rotation())), 6,
                  op="Join", bodies=[b])
        Gui.SendMsgToActiveView("ViewFit")
        S["rng"] = random.Random(seed)
        S["log"] = []
    return f


def round_end(seed):
    def f():
        for b in visible(QtWidgets.QPushButton):  # ein offenes Werkzeug abbrechen
            if b.text().replace("&", "") == "Cancel":
                b.click()
        tidy()
        problems = D.model_problems(doc())
        check("seed %d: no dependency cycle, nothing left to recompute (%d steps)" % (seed, STEPS), not problems,
              "%s | steps: %s" % (problems, S["log"]))
        L("  seed %d steps: %s" % (seed, "; ".join(S["log"])))
    return f


steps = [("activate", activate)]
for seed in SEEDS:
    steps += [("seed %d" % seed, round_start(seed)), ("wait", lambda: None)]
    steps += [("act %d.%d" % (seed, i), lambda: act(S["rng"])) for i in range(STEPS)]
    steps += [("end %d" % seed, round_end(seed))]
run(steps, delay=900)
