# SPDX-License-Identifier: LGPL-2.1-or-later
"""Mehrere Designs auf einmal schließen (wie beim Beenden): kein Absturz, danach erscheint die Startseite.
Früher zogen die Glas-Panels verzögert in die Szene einer schon mitgeschlossenen Ansicht um (SIGSEGV)."""
from harness import *


def page():
    return [w for w in mw.findChildren(QtWidgets.QWidget, "StartPage")][0]


run([
    ("new2", lambda: Gui.runCommand("Std_New")), ("new3", lambda: Gui.runCommand("Std_New")), ("wait", lambda: None),
    ("before", lambda: L("vorher: designs=%s" % sorted(App.listDocuments()))),
    ("close all", lambda: [App.closeDocument(n) for n in list(App.listDocuments())]), ("wait", lambda: None),
    ("after", lambda: L("nachher: designs=%s start page visible=%s (kein Absturz)" % (sorted(App.listDocuments()), page().isVisible()))),
])
