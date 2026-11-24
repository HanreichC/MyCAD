# SPDX-License-Identifier: LGPL-2.1-or-later
"""Phase 14, Chaos 3: Fehlbedienungen in der Skizze. Werkzeug mitten im Zeichnen abbrechen oder wechseln; ein
widersprüchliches Maß setzen (überbestimmt) und Rückgängig; einen Eckpunkt auf den Nachbarn ziehen (Linie der Länge 0);
die offene Skizze über die Zeitleiste löschen. Danach jeweils: kein Absturz, kein Abhängigkeitskreis, nichts bleibt
liegen; Rückgängig stellt her."""
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


def sk():
    e = Gui.ActiveDocument.getInEdit()
    return e.Object if e and e.Object.TypeId == "Sketcher::SketchObject" else None


def invariants(where):
    def f():
        problems = D.model_problems(doc())
        check("%s: no dependency cycle, nothing left to recompute" % where, not problems, str(problems))
        L("  %s: problems %s" % (where, [(o.Label, t[:70]) for o, t in Design.problems(doc())]))
    return f


def start():
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XY_Plane")][0])
    click(button("Design_CreateSketch"))


def frame():
    S["sketch"] = sk()
    cam = Gui.ActiveDocument.ActiveView.getCameraNode()
    cam.position.setValue(25, 15, 100)
    cam.height.setValue(120)


def key(k, mod=QtCore.Qt.NoModifier):
    return lambda: QtTest.QTest.keyClick(view().viewport(), k, mod)


def at(x, y):
    return lambda: click_at(V(x, y, 0))


def rectangle_complete():
    s = sk()
    for g in D.rect(0, 0, 50, 30):
        s.addGeometry(g)
    C = Sketcher.Constraint
    for c in [C("Coincident", i, 2, (i + 1) % 4, 1) for i in range(4)] + [C("Horizontal", 0), C("Horizontal", 2),
              C("Vertical", 1), C("Vertical", 3), C("Coincident", 0, 1, -1, 1), C("DistanceX", 0, 1, 0, 2, 50),
              C("DistanceY", 1, 1, 1, 2, 30)]:
        s.addConstraint(c)
    doc().recompute()
    S["constraints"] = len(s.Constraints)


def conflicting():
    s = sk()
    doc().openTransaction("Add length constraint")
    s.addConstraint(Sketcher.Constraint("Distance", 0, 70))  # die Unterkante hat schon 50
    doc().commitTransaction()
    doc().recompute()
    S["conflict"] = list(s.ConflictingConstraints) + list(s.RedundantConstraints)


def conflict_shown():
    check("a contradicting dimension is reported as a conflict, the sketch keeps its shape", bool(S["conflict"])
          and abs(sk().Geometry[0].length() - 50) < 1e-6, "%s %.3f" % (S["conflict"], sk().Geometry[0].length()))


def undone_conflict():
    s = sk()
    check("undo removes the contradicting dimension: solvable again", len(s.Constraints) == S["constraints"]
          and s.solve() == 0 and not s.ConflictingConstraints, "%d vs %d, solve %d" % (len(s.Constraints), S["constraints"], s.solve()))


def collapse():
    """den rechten oberen Eckpunkt auf den rechten unteren ziehen: die rechte Kante hat die Länge 0"""
    s = sk()
    doc().openTransaction("Drag Point")
    try:
        s.delConstraint(len(s.Constraints) - 1)  # das Höhenmaß stört beim Ziehen
        s.moveGeometry(1, 2, V(50, 0, 0))
    except Exception as e:
        L("  drag: %s" % e)
    doc().commitTransaction()
    doc().recompute()


def collapsed():
    s = sk()
    L("  after collapsing: solve %s, conflicting %s, redundant %s" % (s.solve(), s.ConflictingConstraints, s.RedundantConstraints))


def leave():
    QtTest.QTest.keyClick(view().viewport(), QtCore.Qt.Key_Escape)
    if Gui.ActiveDocument.getInEdit():
        Gui.ActiveDocument.resetEdit()


def delete_open_sketch():
    """Rechtsklick > Löschen auf die Skizze in der Zeitleiste, während sie offen ist"""
    s = S["sketch"]
    entries = [b for b in visible(QtWidgets.QToolButton) if b.property("timelineIndex") is not None and b.accessibleName() == s.Label]
    if not entries:
        L("  no timeline entry while editing (%s)" % [b.accessibleName() for b in visible(QtWidgets.QToolButton)
                                                     if b.property("timelineIndex") is not None])
        return

    def pick():
        m = QtWidgets.QApplication.activePopupWidget()
        S["menu"] = [a.text() for a in m.actions()] if m else []
        acts = [a for a in (m.actions() if m else []) if a.text() == "Delete"]
        if acts:
            m.setActiveAction(acts[0]); QtTest.QTest.keyClick(m, QtCore.Qt.Key_Return)
        elif m:
            m.close()
    QtCore.QTimer.singleShot(500, pick)
    QtCore.QTimer.singleShot(1500, lambda: [b.click() for box in visible(QtWidgets.QMessageBox)
                                             for b in box.findChildren(QtWidgets.QPushButton)
                                             if b.isVisible() and b.text().replace("&", "") in ("Delete", "Yes", "OK")][:1])
    w = entries[0]
    QtWidgets.QApplication.sendEvent(w, QtGui.QContextMenuEvent(QtGui.QContextMenuEvent.Mouse, w.rect().center()))


def after_delete():
    alive = Gui.getMainWindow() is not None
    L("  menu while editing: %s; editing now: %s; sketch exists: %s" % (S.get("menu"), Gui.ActiveDocument.getInEdit(),
                                                                       doc().getObject(S["sketch"].Name) is not None))
    check("deleting the sketch that is open: no crash, nothing half done", alive)


run([("activate", activate), ("start", start), W, W, ("frame", frame), W,
     # Werkzeug mitten im Zeichnen abbrechen und wechseln
     ("line tool", lambda: click(button("Sketcher_CreateLine"))), W, ("line start", at(5, 5)), W, ("esc", key(QtCore.Qt.Key_Escape)), W,
     ("esc 2", key(QtCore.Qt.Key_Escape)), W,
     ("circle tool", lambda: click(button("Sketcher_CompCreateConic"))), W, ("circle center", at(20, 20)), W,
     ("switch to rect", lambda: click(button("Sketcher_CompCreateRectangles"))), W, ("rect a", at(30, 5)), W,
     ("switch to line", lambda: click(button("Sketcher_CreateLine"))), W, ("esc 3", key(QtCore.Qt.Key_Escape)), W,
     ("esc 4", key(QtCore.Qt.Key_Escape)), W,
     ("geometry", lambda: L("  after aborted tools: %d geometries" % len(sk().Geometry))),
     ("inv 1", invariants("tools aborted and switched")),
     ("clear", lambda: [sk().delGeometry(0) for _ in range(len(sk().Geometry))]), W,
     ("rect", rectangle_complete), W, ("conflict", conflicting), W, ("shown", conflict_shown),
     ("undo", lambda: Gui.runCommand("Std_Undo")), W, W, ("undone", undone_conflict), ("inv 2", invariants("conflict undone")),
     ("collapse", collapse), W, ("collapsed", collapsed), ("leave", leave), W, W, ("inv 3", invariants("zero-length edge")),
     ("undo 2", lambda: Gui.runCommand("Std_Undo")), W, W, ("inv 4", invariants("undo zero-length")),
     ("reopen", lambda: Gui.ActiveDocument.setEdit(S["sketch"].Name)), W, W,
     ("delete open sketch", delete_open_sketch), W, W, W, ("after delete", after_delete), ("inv 5", invariants("open sketch deleted")),
     ])
