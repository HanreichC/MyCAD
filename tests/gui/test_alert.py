# SPDX-License-Identifier: LGPL-2.1-or-later
"""Hinweisfenster "Ungespeichertes Dokument" beim Schließen geänderter Designs, einzeln und mit "Apply to all"
(mehrere Designs): Knopftexte passen ganz hinein, kein Text ragt hinaus, Text bündig mit den Knöpfen. Bilder
<OUT>.one.png und <OUT>.all.png. Deutsch: LANGWANT=German, zweimal mit eigenem Home ausführen wie test_german.py
(die Sprache wirkt nach einem Neustart)."""
import os
from harness import *

general = App.ParamGet("User parameter:BaseApp/Preferences/General")
if os.environ.get("LANGWANT") and general.GetString("Language", "English") != os.environ["LANGWANT"]:
    general.SetString("Language", os.environ["LANGWANT"])


def inspect(tag):
    try:
        box = visible(QtWidgets.QMessageBox)[0]
        box.grab().save(os.environ["OUT"] + "." + tag + ".png")
        short = [b.text() for b in box.findChildren(QtWidgets.QAbstractButton) if b.width() < b.sizeHint().width()]
        clipped = [l.text()[:30] for l in box.findChildren(QtWidgets.QLabel)
                   if l.isVisible() and l.text() and not l.wordWrap() and l.width() < l.sizeHint().width()]
        L("%s: buttons cut off=%s labels cut off=%s (both [] expected)" % (tag, short, clipped))
        text_x = box.findChild(QtWidgets.QLabel, "qt_msgbox_label").x()
        L("%s: text aligned with buttons=%s" % (tag, text_x == box.findChild(QtWidgets.QDialogButtonBox).x()))
        box.reject()  # Abbrechen: Designs bleiben offen
    except Exception as e:
        L("  exc %s: %s" % (type(e).__name__, e))


def close(command, tag):
    QtCore.QTimer.singleShot(1500, lambda: inspect(tag))
    Gui.runCommand(command)


run([
    ("body", lambda: make_body(rect(0, 0, 40, 30), 0, 10, "Box")),
    ("close", lambda: close("Std_CloseActiveWindow", "one")), ("wait", lambda: None),
    ("second design", lambda: Gui.runCommand("Std_New")), ("wait", lambda: None),
    ("body2", lambda: make_body(rect(0, 0, 40, 30), 0, 10, "Box2")),
    ("close all", lambda: close("Std_CloseAllWindows", "all")), ("wait", lambda: None),  # mit "Apply to all"
])
