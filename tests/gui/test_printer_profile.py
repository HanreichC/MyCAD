# SPDX-License-Identifier: LGPL-2.1-or-later
"""Druckerprofil (Plan 12.4): "Printer Test" legt ein neues Design mit Passungsplatte, Stift und Grenzen-Platte an,
dazu eine Notiz mit den Schritten. In Einstellungen › 3D Printing ein Klick auf das Loch, in das der Stift gleitet, stellt
das Spiel eng/normal/locker ein, ein Klick auf den letzten sauberen Überhang die Grenze der Druckansicht; die Felder
darunter zeigen es sofort. Fehler stehen als FAIL im Protokoll."""
from harness import *
from harness import _keep

grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")
DEFAULTS = {"PrintFitTight": 0.1, "PrintFitNormal": 0.2, "PrintFitLoose": 0.3, "OverhangAngle": 45.0, "MinWall": 0.8}
for k, v in DEFAULTS.items():
    grp.SetFloat(k, v)
state = {}


def make():
    state["docs"] = len(App.listDocuments())
    Gui.runCommand("Design_PrinterTest")


def check_piece():
    d = App.ActiveDocument
    bodies = [o for o in d.Objects if o.TypeId == "Design::Body"]
    check("a new design", len(App.listDocuments()) == state["docs"] + 1)
    check("three parts: fit plate, pin, limits", sorted(b.Label for b in bodies) == ["Fit Plate", "Limits", "Pin"],
          str([b.Label for b in bodies]))
    check("all printable solids", all(b.Shape.isValid() and b.Shape.Volume > 0 for b in bodies))
    notes = [o for o in d.Objects if o.TypeId == "Design::Note"]
    check("a note says what to do", bool(notes) and "3D Printing" in notes[0].Text, notes[0].Text if notes else "")
    shot("piece")


def dialog():
    return [d for d in visible(QtWidgets.QDialog) if d.objectName() == "Settings"][0]


def segment(label, text):
    found = [b for b in row(label).findChildren(QtWidgets.QPushButton) if b.objectName() == "Segment" and b.text() == text]
    _keep.extend(found); return found[0]


def row(label):
    """Zeile der Einstellung; Wrapper am Leben halten (sonst meldet PySide die Kinder als gelöscht)"""
    labels = [l for l in dialog().findChildren(QtWidgets.QLabel) if l.text() == label]
    r = labels[0].parentWidget(); _keep.extend(labels + [r]); return r


def field(label):
    f = row(label).findChild(QtWidgets.QDoubleSpinBox); _keep.append(f); return f


def check_marked():
    check("today's clearance is marked (hole 4 = 0.2 mm)", segment("Pin slides into hole", "4").isChecked())
    check("45° is not on the piece: nothing marked", not any(segment("Last clean overhang", "%d°" % a).isChecked()
                                                            for a in (30, 40, 50, 60, 70)))


def check_hole():
    got = [round(grp.GetFloat(k), 2) for k in ("PrintFitTight", "PrintFitNormal", "PrintFitLoose")]
    check("hole 6: clearance 0.2 / 0.3 / 0.4 mm", got == [0.2, 0.3, 0.4], str(got))
    check("the field below follows", abs(field("Clearance normal").value() - 0.3) < 1e-9, str(field("Clearance normal").value()))


def check_angle():
    check("overhang 50°: print view limit and its field", grp.GetFloat("OverhangAngle") == 50
          and field("Overhang angle").value() == 50, str(grp.GetFloat("OverhangAngle")))
    shot("settings")


def restore():
    dialog().reject()
    for k, v in DEFAULTS.items():
        grp.SetFloat(k, v)


in_order([
    ("make", make), ("wait", lambda: None),
    ("check piece", check_piece),
    ("settings", lambda: QtCore.QTimer.singleShot(0, lambda: Gui.runCommand("MyCAD_Settings"))), ("wait", lambda: None),
    ("check marked", check_marked),
    ("hole 6", lambda: segment("Pin slides into hole", "6").click()), ("wait", lambda: None),
    ("check hole", check_hole),
    ("50°", lambda: segment("Last clean overhang", "50°").click()), ("wait", lambda: None),
    ("check angle", check_angle),
    ("restore", restore),
])
