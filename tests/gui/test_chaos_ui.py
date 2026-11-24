# SPDX-License-Identifier: LGPL-2.1-or-later
"""Phase 14: MyCAD chaotisch und "falsch" benutzen, wie Menschen es tun. Ein Teil (Platte mit Maßen, Bohrung aus einer
Skizze auf der Deckfläche, Rundung) und dann: in der Grundskizze eine Linie löschen, obwohl längst Körper daraus
entstanden sind; den Bohrungskreis aus dem Teil ziehen, ganz löschen und woanders neu zeichnen; eine Linie quer durch
das schon extrudierte Profil; ein Werkzeug offen lassen und das nächste starten; Strg+Z in der Skizze über ihren
Anfang hinaus; Rückgängig und Wiederholen durcheinander. Nach jedem Schritt: kein Abhängigkeitskreis, nichts bleibt
zum Neuberechnen liegen; Rückgängig stellt den Stand genau wieder her."""
import math
import os
import sys
from harness import *
sys.path.insert(0, os.path.join(os.path.dirname(os.environ["SCRIPT"]), "..", "design"))
import design as D
import Design
import Sketcher

S = {}
W = ("wait", lambda: None)
V = App.Vector


def vol():
    return round(S["body"].Shape.Volume, 2)


def build():
    d = doc()
    base = D.sketch(d, D.rect(0, 0, 80, 50))
    C = Sketcher.Constraint
    for c in [C("Coincident", i, 2, (i + 1) % 4, 1) for i in range(4)] + [
            C("Horizontal", 0), C("Horizontal", 2), C("Vertical", 1), C("Vertical", 3), C("Coincident", 0, 1, -1, 1),
            C("DistanceX", 0, 1, 0, 2, 80), C("DistanceY", 1, 1, 1, 2, 50)]:
        base.addConstraint(c)
    d.recompute()
    ext, b = D.extrude(d, base, 10)
    hole_sk = D.sketch(d, D.circle(60, 25, 5), support=(b, D.top_face(b)))
    hole = D.extrude(d, hole_sk, 10, op="Cut", bodies=[b], Reversed=True)[0]
    e = D.edge_where(b, lambda p: abs(p.x) < 1e-6 and abs(p.y) < 1e-6 and abs(p.z - 5) < 1e-6)
    D.dress(d, "Design::Fillet", b, [e], Size=5)
    for o in d.Objects:
        if o.TypeId in ("Sketcher::SketchObject", "Design::Profiles"):
            o.Visibility = False
    d.recompute()
    S.update(body=b, base=base, hole_sketch=hole_sk, hole=hole, extrude=ext, full=None)
    S["full"] = vol()
    Gui.ActiveDocument.ActiveView.viewIsometric(); Gui.SendMsgToActiveView("ViewFit")


def invariants(where):
    def f():
        problems = D.model_problems(doc())
        check("%s: no dependency cycle, nothing left to recompute" % where, not problems, str(problems))
        L("  %s: volume %.2f, problems %s" % (where, vol(), [(o.Label, t[:60]) for o, t in Design.problems(doc())]))
    return f


def edit(obj):
    return lambda: Gui.ActiveDocument.setEdit(obj.Name)


def leave():
    QtTest.QTest.keyClick(view().viewport(), QtCore.Qt.Key_Escape)
    if Gui.ActiveDocument.getInEdit():
        Gui.ActiveDocument.resetEdit()


def undo(n):
    def f():
        for _ in range(n):
            Gui.runCommand("Std_Undo")
    return f


def redo(n):
    def f():
        for _ in range(n):
            Gui.runCommand("Std_Redo")
    return f


# --- 1. Grundskizze: eine Linie löschen, obwohl die Platte daraus besteht --------------------------------------------------
def delete_line():
    s = Gui.ActiveDocument.getInEdit().Object
    S["vol before"] = vol()
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(doc().Name, s.Name, "Edge2")  # rechte Kante
    QtTest.QTest.keyClick(view().viewport(), QtCore.Qt.Key_Delete)


def line_gone():
    # Profil offen: die Platte darf nicht verschwinden oder kaputt sein; der Schritt sagt, warum
    warns = [t for o, t in Design.problems(doc())]
    check("deleting a line of the extruded base sketch: the step explains it, nothing crashes",
          bool(warns) and S["body"].Shape.isValid(), "%s %s" % (warns, S["body"].Shape.isValid()))


def undone_full():
    check("undo brings the whole part back", abs(vol() - S["full"]) < 0.01, "%s vs %s" % (vol(), S["full"]))


# --- 2. Bohrung: Kreis herausziehen, löschen, woanders neu ----------------------------------------------------------------
def drag_circle_out():
    s = Gui.ActiveDocument.getInEdit().Object
    c = s.Placement.inverse().multVec(V(130, 25, 10))
    doc().openTransaction("Drag Point")  # wie das Ziehen in der Skizze: eine Transaktion
    s.moveGeometry(0, 3, V(c.x, c.y, 0))
    doc().commitTransaction()
    doc().recompute()


def delete_circle():
    s = Gui.ActiveDocument.getInEdit().Object
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(doc().Name, s.Name, "Edge1")
    QtTest.QTest.keyClick(view().viewport(), QtCore.Qt.Key_Delete)


def new_circle():
    s = Gui.ActiveDocument.getInEdit().Object
    c = s.Placement.inverse().multVec(V(20, 25, 10))
    doc().openTransaction("Add sketch circle")
    s.addGeometry(Part.Circle(V(c.x, c.y, 0), V(0, 0, 1), 4))
    doc().commitTransaction()
    doc().recompute()


def hole_state():
    warns = [(o.Label, t[:70]) for o, t in Design.problems(doc())]
    L("  after redrawing the hole: volume %.2f, warns %s" % (vol(), warns))
    # wie Fusion: das Profil ist weg (der Schritt sagt es) oder die neue Bohrung wird genommen; nie still falsch
    plain = 80 * 50 * 10 - (25 - math.pi * 25 / 4) * 10
    new_hole = plain - math.pi * 16 * 10
    check("a hole sketch redrawn elsewhere: either the new hole is cut or the step says its profile is gone",
          abs(vol() - new_hole) < 0.5 or (abs(vol() - plain) < 0.5 and warns), "%s %s" % (vol(), warns))


# --- 3. Linie quer durch das extrudierte Profil der Grundskizze -----------------------------------------------------------
def line_across():
    s = Gui.ActiveDocument.getInEdit().Object
    doc().openTransaction("Add sketch line")
    s.addGeometry(Part.LineSegment(V(40, -10, 0), V(40, 60, 0)))
    doc().commitTransaction()
    doc().recompute()


def across_state():
    warns = [(o.Label, t[:70]) for o, t in Design.problems(doc())]
    L("  after a line across the base: volume %.2f, warns %s" % (vol(), warns))
    check("a line across the extruded base profile: the plate stays whole or the step explains why not",
          abs(vol() - S["vol before across"]) < 0.5 or warns, "%s vs %s %s" % (vol(), S["vol before across"], warns))


# --- 4. Werkzeuge durcheinander -------------------------------------------------------------------------------------------
def extrude_then_fillet():
    prof = [o for o in S["base"].InList if o.TypeId == "Design::Profiles"][0]
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(prof, "Face1")
    Gui.runCommand("Design_Extrude")
    QtCore.QTimer.singleShot(400, lambda: Gui.runCommand("Design_Fillet"))  # das nächste Werkzeug, ohne OK/Abbrechen


def close_tools():
    for _ in range(3):
        for b in visible(QtWidgets.QPushButton):
            if b.text().replace("&", "") == "Cancel":
                b.click(); break
        for m in visible(QtWidgets.QMessageBox):
            m.close()


def tools_state():
    check("starting a tool while another is open leaves no stray step", abs(vol() - S["full"]) < 0.01
          and not any(o.TypeId in ("Design::Fillet", "Design::Extrude") and "Invalid" in o.State for o in doc().Objects),
          "%s %s" % (vol(), [(o.Label, o.State) for o in doc().Objects if "Invalid" in o.State]))


# --- 5. Strg+Z in der Skizze über ihren Anfang hinaus ---------------------------------------------------------------------
def scribble_in_sketch():
    s = Gui.ActiveDocument.getInEdit().Object
    for k in range(3):
        doc().openTransaction("line %d" % k)
        s.addGeometry(Part.LineSegment(V(5 + k * 5, 5, 0), V(5 + k * 5, 15, 0)))
        doc().commitTransaction()
    doc().recompute()


def ctrl_z(n):
    def f():
        for _ in range(n):
            QtTest.QTest.keyClick(view().viewport(), QtCore.Qt.Key_Z, QtCore.Qt.ControlModifier)
    return f


def after_ctrl_z():
    check("Ctrl+Z past the start of the sketch session: no crash, still editing or cleanly left",
          S["body"].Shape.isValid(), "%s" % S["body"].Shape.isValid())


steps = [("activate", activate), ("build", build), W, W, ("start", invariants("start")),
         ("edit base", edit(S.get("base") or None) if False else lambda: edit(S["base"])()), W, W,
         ("delete line", delete_line), W, ("leave 1", leave), W, W, ("line gone", line_gone), ("inv 1", invariants("line deleted")),
         ("undo 1", undo(3)), W, W, ("undone 1", undone_full), ("inv 1b", invariants("undo")),
         ("edit hole", lambda: edit(S["hole_sketch"])()), W, W, ("drag out", drag_circle_out), W,
         ("delete circle", delete_circle), W, ("new circle", new_circle), W, ("leave 2", leave), W, W,
         ("hole state", hole_state), ("inv 2", invariants("hole redrawn")),
         ("undo 2", undo(6)), W, W, ("undone 2", undone_full),
         ("remember", lambda: S.update({"vol before across": vol()})),
         ("edit base 2", lambda: edit(S["base"])()), W, W, ("line across", line_across), W, ("leave 3", leave), W, W,
         ("across", across_state), ("inv 3", invariants("line across")),
         ("undo 3", undo(3)), W, W, ("undone 3", undone_full),
         ("tools", extrude_then_fillet), W, W, ("close tools", close_tools), W, W, ("tools ok", tools_state),
         ("inv 4", invariants("tools mixed")),
         ("edit hole 2", lambda: edit(S["hole_sketch"])()), W, W, ("scribble", scribble_in_sketch), W,
         ("ctrl z", ctrl_z(8)), W, W, ("after ctrl z", after_ctrl_z), ("leave 4", leave), W, W,
         ("inv 5", invariants("ctrl+z in sketch")),
         ("redo mix", redo(4)), W, ("undo mix", undo(2)), W, ("redo mix 2", redo(1)), W, ("inv 6", invariants("undo/redo mixed")),
         ("undo all", undo(40)), W, W, ("redo all", redo(40)), W, W, ("inv 7", invariants("undo all, redo all")),
         ("errors", lambda: L("  errors at the end: %s" % errors()))]
run(steps)
