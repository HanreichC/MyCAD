# SPDX-License-Identifier: LGPL-2.1-or-later
"""Fehler- und Hinweisfenster: Hinweis ohne Auswahl, fehlgeschlagenes Feature, Python-Fehler, Sketcher-Konflikt.
Jedes sichtbare Fenster außer dem Hauptfenster wird fotografiert."""
import os
from harness import *

n = [0]


def grab_popups(tag):
    for w in QtWidgets.QApplication.topLevelWidgets():
        if w.isVisible() and w is not mw and w.objectName() != "GlassContent":
            n[0] += 1
            L("  %s popup %s %s title=%r geo=%s main=%s" % (tag, type(w).__name__, w.objectName(), w.windowTitle(),
                                                        w.geometry().getRect(), mw.geometry().getRect()))
            w.grab().save("%s.%s%d.png" % (os.environ["OUT"], tag, n[0]))
            if isinstance(w, QtWidgets.QDialog):
                w.close()


def later(tag, fn):
    QtCore.QTimer.singleShot(1200, lambda: grab_popups(tag)); fn()


def bad_fillet():
    b = body("Box"); root = [o for o in doc().Objects if o.TypeId == "App::Part"][0]
    f = doc().addObject("Design::Fillet", "Fillet"); f.Bodies = [b]; f.Edges = ["Edge1"]; f.Size = 500; root.addObject(f)
    doc().recompute()


def conflict():
    sk = doc().addObject("Sketcher::SketchObject", "Conflict")
    sk.addGeometry(Part.LineSegment(App.Vector(0, 0, 0), App.Vector(10, 0, 0)))
    sk.addConstraint(Sketcher.Constraint("Horizontal", 0)); sk.addConstraint(Sketcher.Constraint("Vertical", 0))
    doc().recompute()


import Sketcher
run([
    ("setup", lambda: make_body(rect(0, 0, 60, 40), 0, 15, "Box")),
    ("combine hint", lambda: later("hint", lambda: click(button("Design_Combine")))),
    ("wait", lambda: None),
    ("bad fillet", lambda: later("fillet", bad_fillet)),
    ("wait", lambda: None),
    ("errors", lambda: L("errors=%s" % errors())),
    ("dclick failed", lambda: later("failed", lambda: Gui.ActiveDocument.setEdit(doc().getObject("Fillet")))),
    ("wait", lambda: None),
    ("python error", lambda: later("python", lambda: Gui.doCommand("raise RuntimeError('test error')"))),
    ("wait", lambda: None),
    ("conflict", lambda: later("conflict", conflict)),
    ("wait", lambda: None),
    ("edit conflict", lambda: later("editconflict", lambda: Gui.ActiveDocument.setEdit("Conflict"))),
    ("wait", lambda: None), ("shot", lambda: shot("main")),
])
