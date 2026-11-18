# SPDX-License-Identifier: LGPL-2.1-or-later
"""Unten im Browser "Saved" (wie MyNotes): nur wenn der Stand des Designs gespeichert ist. Neues Design: nicht
gesichert; nach dem stillen Speichern (immer speichern, 2 s Ruhe): gesichert; nach einer Änderung wieder nicht,
dann wieder gesichert. Projektordner im Ausgabeordner."""
import os
import shutil
from harness import *

grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")
grp.SetBool("AlwaysSave", True)  # harness schaltet es aus
old_folder = grp.GetString("ProjectsFolder", "")
FOLDER = os.environ["OUT"] + ".projects"
shutil.rmtree(FOLDER, ignore_errors=True)
os.makedirs(FOLDER)
grp.SetString("ProjectsFolder", FOLDER)


def mark():
    return [w for w in QtWidgets.QApplication.allWidgets() if w.objectName() == "SavedState"][0]


def state(expect, why):
    m = mark()
    check(why, m.isVisible() == expect, "visible=%s tip=%s" % (m.isVisible(), m.toolTip()))


def keep_wheeling(seconds=4.0):
    """H3: Mausrad in kleinen Schritten, wie beim Zoomen, alle 200 ms; währenddessen speichert MyCAD nicht"""
    from PySide6 import QtGui
    vp = view().viewport(); p = QtCore.QPointF(vp.rect().center())
    for k in range(int(seconds / 0.2)):
        def turn(k=k):
            ev = QtGui.QWheelEvent(p, QtCore.QPointF(vp.mapToGlobal(p.toPoint())), QtCore.QPoint(),
                                   QtCore.QPoint(0, 15 if k % 2 else -15), QtCore.Qt.NoButton, QtCore.Qt.NoModifier,
                                   QtCore.Qt.NoScrollPhase, False)
            QtWidgets.QApplication.sendEvent(vp, ev)
        QtCore.QTimer.singleShot(int(k * 200), turn)


def restore():
    grp.SetBool("AlwaysSave", False)
    grp.SetString("ProjectsFolder", old_folder) if old_folder else grp.RemString("ProjectsFolder")


in_order([
    ("fresh", lambda: state(False, "a new design that was never saved shows no Saved mark")),
    ("body", lambda: make_body(rect(0, 0, 20, 10), 0, 5, "Box")),
    ("wait", lambda: None), ("wait", lambda: None), ("wait", lambda: None), ("wait", lambda: None),
    ("saved", lambda: state(True, "after saving quietly the browser shows Saved")),
    ("shot", lambda: shot("saved")),
    ("change", lambda: (setattr(body("Box"), "Label", "Bar"), Gui.ActiveDocument.Document.recompute())),
    ("unsaved", lambda: state(False, "a change hides the Saved mark until it is saved")),
    ("wait", lambda: None), ("wait", lambda: None), ("wait", lambda: None), ("wait", lambda: None),
    ("saved again", lambda: state(True, "saved again after the change")),
    ("change 2", lambda: (setattr(body("Bar"), "Label", "Baz"), Gui.ActiveDocument.Document.recompute(), keep_wheeling())),
    ("wait", lambda: None), ("wait", lambda: None),
    ("not while wheeling", lambda: state(False, "H3: no saving while the mouse wheel is still turning")),
    ("wait", lambda: None), ("wait", lambda: None), ("wait", lambda: None), ("wait", lambda: None),
    ("saved after", lambda: state(True, "saved once the wheel rests")),
    ("restore", restore),
], delay=1000)
