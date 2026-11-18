# SPDX-License-Identifier: LGPL-2.1-or-later
"""Körper-Material: neue Körper sind Stahl (Vorgabe); in den Einstellungen "Body material" -> Clay färbt Körper mit
Standard-Look um, ein Körper mit eigener Farbe bleibt. Aufräumliste B10: ein im Aussehen-Panel gewählter Stahl bleibt
Stahl, obwohl er wie der Standard aussieht; bei einer einzeln gefärbten Fläche folgen nur die übrigen Flächen. Am Ende
wieder Stahl (Einstellung des Benutzers)."""
from harness import *

grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")
old = grp.GetInt("BodyMaterial", 29)  # Vorgabe Stahl (Shell.h DefaultBodyMaterial)
state = {}


def hexcolor(b, i=0):
    c = b.ViewObject.ShapeAppearance[i].DiffuseColor
    return "#%02X%02X%02X" % tuple(round(v * 255) for v in c[:3])


def faces(b):
    return {hexcolor(b, i) for i in range(len(b.ViewObject.ShapeAppearance))}


def panel(*sel):
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(*sel)
    Gui.runCommand("Design_Appearance")


def tile(name):
    [b for b in visible(QtWidgets.QToolButton) if b.accessibleName() == name][0].click()


def report(tag):
    L("%s: default=%s custom=%s" % (tag, hexcolor(state["a"]), hexcolor(state["b"])))


def bodies():
    state["a"] = make_body(rect(0, 0, 40, 30), 0, 10, "Default")
    state["b"] = make_body(rect(60, 0, 100, 30), 0, 10, "Custom")
    state["b"].ViewObject.ShapeAppearance = (App.Material(DiffuseColor=(1.0, 0.2, 0.2)),)
    state["c"] = make_body(rect(0, 50, 40, 80), 0, 10, "Chosen")
    state["d"] = make_body(rect(60, 50, 100, 80), 0, 10, "Faces")


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
    ("steel panel", lambda: panel(state["c"])), ("steel", lambda: tile("Steel")), ("ok steel", ok),
    ("face panel", lambda: panel(state["c"].Document.Name, state["d"].Name, top_face(state["d"]))),
    ("red face", lambda: tile("Lacquer Red")), ("ok face", ok),
    ("fit", lambda: (Gui.ActiveDocument.ActiveView.viewIsometric(), Gui.SendMsgToActiveView("ViewFit"))),
    ("shot gray", lambda: shot("gray")), ("start", lambda: report("start (Steel = #8F9296)")),
    ("clay", lambda: pick("Clay")), ("wait", lambda: None),
    ("after", lambda: report("nach Clay (#E8DED1, eigene Farbe bleibt #FF3333)")),
    ("shot", lambda: shot("clay")),
    ("chosen", lambda: (check("A look picked in the panel stays, even if it equals the standard", hexcolor(state["c"]) == "#8F9296", hexcolor(state["c"])),
                        check("Colour by hand stays", hexcolor(state["b"]) == "#FF3333", hexcolor(state["b"])),
                        check("Standard look follows the default", hexcolor(state["a"]) == "#E8DED1", hexcolor(state["a"])),
                        check("Single red face stays, the other faces follow", faces(state["d"]) == {"#E8DED1", "#B0161E"}, str(faces(state["d"]))))),
    ("titanium", lambda: pick("Natural Titanium")), ("wait", lambda: None),
    ("after titanium", lambda: report("nach Natural Titanium (#B8B2A7)")), ("shot titanium", lambda: shot("titanium")),
    ("back", lambda: pick("Steel")), ("wait", lambda: None),
    ("final", lambda: report("zurück")),
    ("restore", lambda: grp.SetInt("BodyMaterial", old)),
])
