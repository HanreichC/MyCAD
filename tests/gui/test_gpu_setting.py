# SPDX-License-Identifier: LGPL-2.1-or-later
"""Einstellung "Graphics card" (nur mit zwei GPUs): Umschalten speichert die Wahl und meldet den nötigen Neustart;
zurück auf die laufende Wahl braucht keine Meldung. Fehler stehen als FAIL im Protokoll."""
from harness import *

grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")
saved = {}
wait = ("wait", lambda: None)


def segment(text):
    return [b for b in visible(QtWidgets.QPushButton) if b.objectName() == "Segment" and b.text() == text]


def alerts():
    return visible(QtWidgets.QMessageBox)


def choose(text):
    saved["running"] = grp.GetInt("Gpu", 0)
    segment(text)[0].click()


def expect_restart_info():
    a = alerts()
    check("switching tells to restart MyCAD", len(a) == 1 and "restart" in (a[0].text() + a[0].informativeText()).lower(), a[0].informativeText() if a else "no message")
    check("choice is stored", grp.GetInt("Gpu", 0) != saved["running"])
    for box in a:
        box.accept()


def two_cards():
    """wie die App (Settings.cpp): mehr als eine Grafikkarte unter /sys/class/drm"""
    import glob
    return len(glob.glob("/sys/class/drm/card?") + glob.glob("/sys/class/drm/card??")) > 1


def row_or_skip():
    if not two_cards():  # z. B. CI/Xvfb: die Zeile darf es dann nicht geben, der Rest entfällt
        check("no graphics card row with a single card", not segment("Dedicated") and not segment("Processor"))
        saved["skip"] = True
        return
    check("row is there on this computer with two graphics cards", bool(segment("Dedicated")) and bool(segment("Processor")))
    saved["start"] = grp.GetInt("Gpu", 0)


def unless_skipped(fn):
    return lambda: None if saved.get("skip") else fn()


in_order([
    ("settings", lambda: QtCore.QTimer.singleShot(0, lambda: Gui.runCommand("MyCAD_Settings"))), wait,
    ("row", row_or_skip),
    ("shot", lambda: shot("settings")),
    ("to the other", unless_skipped(lambda: choose("Processor" if saved["start"] == 0 else "Dedicated"))), wait,
    ("info", unless_skipped(expect_restart_info)), wait,
    ("back", unless_skipped(lambda: choose("Dedicated" if saved["start"] == 0 else "Processor"))), wait,
    ("no info", unless_skipped(lambda: check("back to the running card needs no message",
                                             not alerts() and grp.GetInt("Gpu", 0) == saved["start"]))),
    ("close", lambda: [d.accept() for d in visible(QtWidgets.QDialog) if d.objectName() == "Settings"]),
])
