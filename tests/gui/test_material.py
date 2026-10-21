# SPDX-License-Identifier: LGPL-2.1-or-later
"""Körper-Material: neue Körper sind Space Gray; in den Einstellungen "Body material" -> Clay färbt Körper mit
Standard-Look um, ein Körper mit eigener Farbe bleibt. Am Ende wieder Space Gray (Einstellung des Benutzers)."""
from harness import *

grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")
old = grp.GetInt("BodyMaterial", 0)
state = {}


def hexcolor(b):
    c = b.ViewObject.ShapeAppearance[0].DiffuseColor
    return "#%02X%02X%02X" % tuple(round(v * 255) for v in c[:3])


def report(tag):
    L("%s: default=%s custom=%s" % (tag, hexcolor(state["a"]), hexcolor(state["b"])))


def bodies():
    state["a"] = make_body(rect(0, 0, 40, 30), 0, 10, "Default")
    state["b"] = make_body(rect(60, 0, 100, 30), 0, 10, "Custom")
    state["b"].ViewObject.ShapeAppearance = (App.Material(DiffuseColor=(1.0, 0.2, 0.2)),)


def pick(name):
    def act():
        d = [w for w in visible(QtWidgets.QDialog) if w.windowTitle() == "Settings"][0]
        combo = [c for c in d.findChildren(QtWidgets.QComboBox) if c.findText(name) >= 0][0]
        combo.setCurrentIndex(combo.findText(name))  # wie die Wahl im Pop-up
        L("  param BodyMaterial=%d" % grp.GetInt("BodyMaterial"))
        d.grab().save(os.environ["OUT"] + ".settings.png")
        d.accept()
    QtCore.QTimer.singleShot(800, act)
    Gui.runCommand("MyCAD_Settings")


import os
run([
    ("bodies", bodies),
    ("fit", lambda: (Gui.ActiveDocument.ActiveView.viewIsometric(), Gui.SendMsgToActiveView("ViewFit"))),
    ("shot gray", lambda: shot("gray")), ("start", lambda: report("start (Space Gray = #5C6169)")),
    ("clay", lambda: pick("Clay")), ("wait", lambda: None),
    ("after", lambda: report("nach Clay (#E8DED1, eigene Farbe bleibt #FF3333)")),
    ("shot", lambda: shot("clay")),
    ("titanium", lambda: pick("Natural Titanium")), ("wait", lambda: None),
    ("after titanium", lambda: report("nach Natural Titanium (#B8B2A7)")), ("shot titanium", lambda: shot("titanium")),
    ("back", lambda: pick("Space Gray")), ("wait", lambda: None),
    ("final", lambda: report("zurück")),
    ("restore", lambda: grp.SetInt("BodyMaterial", old)),
])
