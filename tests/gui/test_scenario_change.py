# SPDX-License-Identifier: LGPL-2.1-or-later
"""Phase 13.5 Szenario D: später ändern, wie im Alltag. Ein fertiges Teil (Platte mit Maßen, Bohrung aus einer
Skizze auf der Deckfläche, Rundung an einer senkrechten Kante, Sockel aus einer zweiten Skizze, Fase am Sockel) wird
über die Zeitleiste geändert: Rechtsklick > Bearbeiten und das Grundmaß größer; so klein, dass die Bohrung neben der
Platte liegt (muss rot werden, mit verständlichem Grund) und wieder zurück; die Bohrung mitten aus der Zeitleiste
löschen; die Rundung unterdrücken und wieder an; zurückspulen und wieder vor; alles rückgängig. Jede Handlung gemessen."""
import math
import os
import sys
from PySide6 import QtGui
from harness import *
sys.path.insert(0, os.path.join(os.path.dirname(os.environ["SCRIPT"]), "..", "design"))
import design as D
import Design
import Sketcher

S = {}
W = ("wait", lambda: None)
V = App.Vector


def body():
    return S["body"]


def vol():
    return round(body().Shape.Volume, 1)


def build():
    d = doc()
    base = D.sketch(d, D.rect(0, 0, 80, 50))
    C = Sketcher.Constraint
    for c in [C("Coincident", i, 2, (i + 1) % 4, 1) for i in range(4)] + [
            C("Horizontal", 0), C("Horizontal", 2), C("Vertical", 1), C("Vertical", 3), C("Coincident", 0, 1, -1, 1),
            C("DistanceX", 0, 1, 0, 2, 80), C("DistanceY", 1, 1, 1, 2, 50)]:
        base.addConstraint(c)
    d.recompute()
    _, b = D.extrude(d, base, 10)
    top = D.top_face(b)
    hole_sk = D.sketch(d, D.circle(65, 25, 4), support=(b, top))  # wie "Create Sketch" auf der Deckfläche
    hole = D.extrude(d, hole_sk, 10, op="Cut", bodies=[b], Reversed=True)[0]
    edge = [i for i, e in enumerate(b.Shape.Edges, 1)
            if abs(e.CenterOfMass.x) < 1e-6 and abs(e.CenterOfMass.y) < 1e-6 and abs(e.CenterOfMass.z - 5) < 1e-6][0]
    fillet = D.dress(d, "Design::Fillet", b, ["Edge%d" % edge], Size=6)
    boss_sk = D.sketch(d, D.rect(15, 15, 35, 35), support=(b, D.top_face(b)))
    boss = D.extrude(d, boss_sk, 8, op="Join", bodies=[b])[0]
    ring = [i for i, e in enumerate(b.Shape.Edges, 1) if abs(e.CenterOfMass.z - 18) < 1e-6 and abs(e.CenterOfMass.x - 25) < 1e-6
            and abs(e.CenterOfMass.y - 35) < 1e-6]
    chamfer = D.dress(d, "Design::Chamfer", b, ["Edge%d" % ring[0]], Size=1)
    for o in d.Objects:
        if o.TypeId in ("Sketcher::SketchObject", "Design::Profiles"):
            o.Visibility = False
    d.recompute()
    S.update(body=b, base=base, hole=hole, hole_sketch=hole_sk, fillet=fillet, boss=boss, chamfer=chamfer)
    S["full"] = vol(); S["hole name"] = hole.Name
    Gui.ActiveDocument.ActiveView.viewIsometric(); Gui.SendMsgToActiveView("ViewFit")
    L("  part: %d steps, volume %.1f, errors %s" % (len(Design.timeline(d)), vol(), errors()))


# --- Zeitleiste wie ein Mensch -------------------------------------------------------------------------------------------
def entries():
    return sorted([b for b in visible(QtWidgets.QToolButton) if b.property("timelineIndex") is not None],
                  key=lambda b: b.property("timelineIndex"))


def entry(obj):
    found = [b for b in entries() if b.accessibleName() == obj.Label]
    if not found:
        raise AssertionError("no timeline entry for %s in %s" % (obj.Label, [b.accessibleName() for b in entries()]))
    return found[0]


def menu(obj, text):
    """Rechtsklick auf den Eintrag, dann text im Menü wählen (das Menü blockiert: Wahl per Timer)"""
    def pick():
        m = QtWidgets.QApplication.activePopupWidget()
        acts = [a for a in (m.actions() if m else []) if a.text() == text]
        S["menu"] = [a.text() for a in m.actions()] if m else []
        if acts:
            m.setActiveAction(acts[0]); QtTest.QTest.keyClick(m, QtCore.Qt.Key_Return)
        elif m:
            m.close()
    QtCore.QTimer.singleShot(500, pick)
    w = entry(obj)
    QtWidgets.QApplication.sendEvent(w, QtGui.QContextMenuEvent(QtGui.QContextMenuEvent.Mouse, w.rect().center()))


def width(value):
    def f():
        s = S["base"]
        i = [k for k, c in enumerate(s.Constraints) if c.Type == "DistanceX"][0]
        s.setDatum(i, App.Units.Quantity("%g mm" % value))
        Gui.ActiveDocument.resetEdit()  # "Fertig": rechnet alles neu
    return f


def problems():
    return [(o.Label, t) for o, t in Design.problems(doc())]


def is_red(obj):
    return any(o == obj.Label for o, _ in problems())


# --- Prüfungen -----------------------------------------------------------------------------------------------------------
def wider_ok():
    k = body().Shape.BoundBox
    check("base 80 -> 100 via the timeline: every later step still works", abs(k.XLength - 100) < 1e-6 and not problems()
          and body().Shape.isValid(), "%s %s" % (k, problems()))
    S["wider"] = vol()


def too_small_ok():  # ein Schnitt, der nichts mehr trifft: Warnung (der Körper bleibt gültig)
    p = problems()
    check("base 50 wide: the hole at x = 65 lies outside; that step is red with a reason, the steps after it still work",
          is_red(S["hole"]) and not is_red(S["chamfer"]) and not is_red(S["fillet"]),
          str(p))
    S["reason"] = [t for o, t in p if o == S["hole"].Label]
    L("  why red: %s" % S["reason"])


def back_ok():
    check("back to 80: the same part as before, nothing red", vol() == S["full"] and not problems(),
          "%s vs %s %s" % (vol(), S["full"], problems()))


def deleted_ok():
    want = S["full"] + round(math.pi * 16 * 10, 1)
    check("delete the hole from the middle of the timeline: the hole is gone, the later steps still work",
          abs(vol() - want) < 0.5 and not problems() and doc().getObject(S["hole name"]) is None,
          "%s want %s %s" % (vol(), want, problems()))
    S["no hole"] = vol()


def suppressed_ok():
    check("suppress the fillet: the corner is sharp again", vol() > S["no hole"] and not problems(),
          "%s vs %s %s" % (vol(), S["no hole"], problems()))
    S["sharp"] = vol()


def unsuppressed_ok():
    check("unsuppress: the fillet is back", vol() == S["no hole"] and not problems(), "%s %s" % (vol(), problems()))


def rolled_ok():
    k = body().Shape.BoundBox
    check("roll back to the fillet: no boss yet (10 high)", abs(k.ZLength - 10) < 1e-6, str(k))


def forward():
    Design.setRollbackMarker(doc(), -1)
    doc().recompute()


def forward_ok():
    check("roll forward: everything back", vol() == S["no hole"] and not problems(), "%s %s" % (vol(), problems()))


def undo_all():
    for _ in range(30):
        Gui.runCommand("Std_Undo")


def undone_ok():
    check("undo all the way: the part as built, nothing red", vol() == S["full"] and not problems(),
          "%s vs %s %s" % (vol(), S["full"], problems()))


run([("activate", activate), ("build", build), W, W,
     timed("edit base sketch (right-click)", lambda: menu(S["base"], "Edit"), 800), W, W,
     timed("base 80 -> 100, done", width(100), 1500), W, ("wider", wider_ok),
     ("edit again", lambda: menu(S["base"], "Edit")), W, W,
     timed("base 100 -> 50, done", width(50), 1500), W, ("too small", too_small_ok),
     ("edit 3", lambda: menu(S["base"], "Edit")), W, W,
     timed("base 50 -> 80, done", width(80), 1500), W, ("back", back_ok),
     timed("delete the hole (right-click)", lambda: menu(S["hole"], "Delete"), 1500), W, W, ("deleted", deleted_ok),
     timed("suppress the fillet", lambda: menu(S["fillet"], "Suppress"), 1000), W, W, ("suppressed", suppressed_ok),
     timed("unsuppress the fillet", lambda: menu(S["fillet"], "Unsuppress"), 1000), W, W, ("unsuppressed", unsuppressed_ok),
     timed("roll back to the fillet", lambda: menu(S["fillet"], "Roll Back to Here"), 1000), W, W, ("rolled", rolled_ok),
     timed("roll forward", forward, 1000), W, ("forward", forward_ok),
     timed("undo all", undo_all, 3000), W, W, ("undone", undone_ok),
     ("errors", lambda: check("no errors", not errors(), str(errors()))),
     ])
