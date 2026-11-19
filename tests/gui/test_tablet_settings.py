# SPDX-License-Identifier: LGPL-2.1-or-later
"""Einstellungen › Tablett (Plan T1): Huion H640P mit 6 Tasten am Tablett und 2 am Stift, Belegungsvorschlag, Änderung
bleibt beim Wiederöffnen, Vorschlag wiederherstellen, eine Stift-Taste lässt ihre Zeile aufleuchten (und tut dabei
nichts), ein unbekanntes Modell lernt seine Tasten. Außerhalb der Einstellungen dreht die untere Stift-Taste die
Ansicht (Vorschlag), solange sie gehalten ist. Die Tasten am Tablett selbst liest MyCAD per libinput: das prüft
tests/tablet_keys_check.cpp ohne Gerät, am echten Tablett von Hand. Fehler stehen als FAIL im Protokoll."""
import os
from harness import *

grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")
old_look = grp.GetInt("Appearance", 0)
old = {k: grp.GetString(k, "") for k in ("TabletModel", "TabletKeys")}
old_seen = grp.GetInt("TabletKeysSeen", 0)
grp.SetString("TabletModel", "h640p")
grp.SetString("TabletKeys", "")
grp.SetInt("TabletKeysSeen", 0)
App.ParamGet("User parameter:BaseApp/Preferences/View").SetString("NavigationStyle", "Gui::RevitNavigationStyle")
wait = ("wait", lambda: None)
_pen = []


def dialog():
    return [d for d in visible(QtWidgets.QDialog) if d.objectName() == "Settings"][0]


def open_settings():
    QtCore.QTimer.singleShot(0, lambda: Gui.runCommand("MyCAD_Settings"))


def to_tablet():
    [b for b in visible(QtWidgets.QPushButton) if b.objectName() == "Segment" and b.text() == "Tablet"][0].click()


def rows():
    return [w for w in visible(QtWidgets.QWidget) if w.objectName() == "KeyRow"]


def row(label):
    return [w for w in rows() if any(l.text() == label for l in w.findChildren(QtWidgets.QLabel))][0]


def action(label):
    return row(label).findChild(QtWidgets.QComboBox).currentData()


def check_suggestion():
    names = [l.text() for w in rows() for l in w.findChildren(QtWidgets.QLabel) if l.text().startswith(("Key ", "Lower", "Upper"))]
    check("6 keys on the tablet and 2 on the pen", len(rows()) == 8, str(names))
    got = [action("Key %d" % n) for n in range(1, 7)] + [action("Lower Button"), action("Upper Button")]
    check("suggestion: undo, eraser, select, sheet, redo, look; pen rotate, eraser while held",
          got == ["undo", "eraser", "select", "sheet", "redo", "look", "rotate", "eraserHold"], str(got))


def change_key2():
    box = row("Key 2").findChild(QtWidgets.QComboBox)
    box.setCurrentIndex(box.findData("marker"))
    check("a change is saved, only what differs from the suggestion", grp.GetString("TabletKeys", "") == "pad2=marker",
          grp.GetString("TabletKeys", ""))


def pen(target, kind, button, buttons, pos=None):
    if not _pen:
        _pen.append(QtGui.QPointingDevice("pen", 17, QtGui.QInputDevice.DeviceType.Stylus, QtGui.QPointingDevice.PointerType.Pen,
                                          QtGui.QInputDevice.Capability.Position | QtGui.QInputDevice.Capability.Pressure, 1, 3))
    p = QtCore.QPointF(pos or QtCore.QPointF(10, 10))
    e = QtGui.QTabletEvent(kind, _pen[0], p, target.mapToGlobal(p), 0, 0, 0, 0, 0, 0, QtCore.Qt.NoModifier, button, buttons)
    QtWidgets.QApplication.sendEvent(target, e)
    return e.isAccepted()


def press_lower_in_dialog():
    took = pen(dialog(), QtCore.QEvent.TabletPress, QtCore.Qt.MiddleButton, QtCore.Qt.MiddleButton)
    lit = row("Lower Button").property("pressed")
    label = [l for l in row("Lower Button").findChildren(QtWidgets.QLabel) if l.objectName() == "Pressed"][0]
    others = [w for w in rows() if w.property("pressed") and w is not row("Lower Button")]
    pen(dialog(), QtCore.QEvent.TabletRelease, QtCore.Qt.MiddleButton, QtCore.Qt.NoButton)
    check("lower pen button in the open settings lights its row (and says pressed), only that one",
          took and lit and label.isVisible() and not others, "accepted=%s lit=%s label=%s others=%d" % (took, lit, label.isVisible(), len(others)))
    snap("pressed")


def other_model():
    box = [c for c in dialog().findChildren(QtWidgets.QComboBox) if c.findData("other") >= 0][0]
    box.setCurrentIndex(box.findData("other"))
    empty = [l for l in visible(QtWidgets.QLabel) if l.text().startswith("No keys yet. Press each key")]
    check("unknown model: no tablet rows until a key is pressed, the pen keeps its two",
          len(rows()) == 2 and len(empty) == 1, "rows=%d hint=%d" % (len(rows()), len(empty)))
    snap("other")
    box.setCurrentIndex(box.findData("h640p"))  # neue Zeilen zeigt Qt erst in der nächsten Runde der Ereignisschleife


def scheme(text):
    """Farbschema wie auf der Seite General umschalten (der Knopf liegt dort, versteckt, klickt aber trotzdem)"""
    [b for b in dialog().findChildren(QtWidgets.QPushButton) if b.objectName() == "Segment" and b.text() == text][0].click()


def snap(name):
    """der Einstellungsdialog ist ein eigenes Fenster: shot() sähe nur das Hauptfenster"""
    dialog().grab().save(os.environ["OUT"] + "." + name + ".png")


def close():
    dialog().accept()


def restore():
    [b for b in dialog().findChildren(QtWidgets.QPushButton) if b.text() == "Restore Suggestion"][0].click()
    check("restore suggestion: nothing saved, Key 2 is the eraser again",
          grp.GetString("TabletKeys", "") == "" and action("Key 2") == "eraser", grp.GetString("TabletKeys", ""))


def camera():
    cam = Gui.ActiveDocument.ActiveView.getCamera()
    return [l.strip() for l in cam.splitlines() if l.strip().startswith("orientation")][0]


def rotate_with_pen():
    """Stift schwebt über der Ansicht, untere Taste gehalten, Stift bewegt sich: die Ansicht dreht sich"""
    vp = view().viewport(); c = QtCore.QPointF(vp.rect().center())
    before = camera()
    N, M = QtCore.Qt.NoButton, QtCore.Qt.MiddleButton
    pen(vp, QtCore.QEvent.TabletMove, N, N, c)
    pen(vp, QtCore.QEvent.TabletPress, M, M, c)
    for i in range(1, 11):
        pen(vp, QtCore.QEvent.TabletMove, N, M, c + QtCore.QPointF(15 * i, 6 * i))
    pen(vp, QtCore.QEvent.TabletRelease, M, N, c + QtCore.QPointF(150, 60))
    check("lower pen button held over the view rotates it", camera() != before, "%s -> %s" % (before, camera()))


def cleanup():
    for k, v in old.items():
        grp.SetString(k, v)
    grp.SetInt("TabletKeysSeen", old_seen)


in_order([
    ("open", open_settings), wait,
    ("tablet", to_tablet), wait,
    ("suggestion", check_suggestion),
    ("shot", lambda: snap("tablet")),
    ("dark", lambda: scheme("Dark")), wait,
    ("dark shot", lambda: snap("tablet-dark")),
    ("light", lambda: scheme(["Automatic", "Light", "Dark"][old_look])), wait,
    ("change", change_key2),
    ("pen key", press_lower_in_dialog),
    ("other model", other_model), wait,
    ("back", lambda: check("back to the H640P: its 6 rows again", len(rows()) == 8, str(len(rows())))),
    ("close", close), wait,
    ("reopen", open_settings), wait,
    ("tablet again", to_tablet), wait,
    ("kept", lambda: check("the change is still there after reopening", action("Key 2") == "marker", str(action("Key 2")))),
    ("restore", restore),
    ("close again", close), wait,
    ("body", lambda: make_body(rect(0, 0, 60, 40), 0, 15, "Box")), wait,
    ("rotate", rotate_with_pen),
    ("cleanup", cleanup),
])
