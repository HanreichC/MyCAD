# SPDX-License-Identifier: LGPL-2.1-or-later
"""12.10 Code-Schritt in der Oberfläche: der Befehl öffnet das Panel mit dem Beispiel-Code; ohne "Run" rechnet nichts
(Meldung im Panel), "Run" gibt den Code frei und baut den Körper; OK übernimmt"""
from harness import *

S = {}
W = ("wait", lambda: None)
App.ParamGet("User parameter:BaseApp/Preferences/MyCAD").RemGroup("ApprovedCode")


def editor():
    return [e for e in visible(QtWidgets.QPlainTextEdit) if e.objectName() == "CodeEdit"]


def step():
    return [o for o in doc().Objects if o.TypeId == "Design::CodeStep"][-1]


def body():
    return [o for o in doc().Objects if o.TypeId == "Design::Body"][-1]


def opened():
    check("Code Step opens the panel with the example code", bool(editor()) and "result" in editor()[0].toPlainText(),
          str([e.objectName() for e in visible(QtWidgets.QPlainTextEdit)]))
    check("before Run nothing runs", "Invalid" in step().State, str(step().State))


def ran():
    s = step()
    check("Run approves and builds the plate with its hole", "Invalid" not in s.State and body().Shape.Volume > 0,
          "%s %s" % (s.State, s.getStatusString()))


run([("activate", activate),
     ("start", lambda: Gui.runCommand("Design_CodeStep")), W, W,
     ("opened", opened),
     ("run", lambda: [b for b in visible(QtWidgets.QPushButton) if b.objectName() == "RunCode"][0].click()), W,
     ("ran", ran),
     ("shot", lambda: shot("code")),
     ("ok", ok), W,
     ("kept", lambda: check("OK keeps the step", not Gui.Control.activeDialog() and "Invalid" not in step().State)),
     ("errors", lambda: check("no errors", not [e for e in errors() if "not run on this computer" not in e], str(errors()))),
     ("clean", lambda: App.ParamGet("User parameter:BaseApp/Preferences/MyCAD").RemGroup("ApprovedCode")),
     ])
