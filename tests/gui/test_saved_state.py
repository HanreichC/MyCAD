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
    ("restore", restore),
], delay=1000)
