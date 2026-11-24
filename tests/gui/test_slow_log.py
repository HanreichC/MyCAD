# SPDX-License-Identifier: LGPL-2.1-or-later
"""13.1 Ruckel-Protokoll: hängt die Oberfläche (hier 0,4 s künstlich nach "Alles einpassen"), steht in slow.log eine
Zeile mit Dauer und zuletzt ausgeführtem Befehl; mit ausgeschaltetem Schalter (Einstellungen) keine."""
import os
import time
from harness import *

P = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")
LOG = os.path.join(App.getUserAppDataDir(), "slow.log")
S = {}
W = ("wait", lambda: None)


def lines():
    try:
        with open(LOG, encoding="utf-8") as f:
            return f.read().splitlines()
    except OSError:
        return []


def hang():
    S["before"] = len(lines())
    Gui.runCommand("Std_ViewFitAll")
    time.sleep(0.4)  # die Ereignisschleife steht, wie bei einer langen Rechnung


def logged():
    new = lines()[S["before"]:]
    check("a 0.4 s hang is logged with its duration and the last command",
          len(new) == 1 and "Std_ViewFitAll" in new[0] and 350 <= int(new[0].split(" | ")[1].split()[0]) < 2000,
          str(new))


def off_hang():
    P.SetBool("SlowLog", False)
    hang()


def not_logged():
    check("switched off: nothing logged", len(lines()) == S["before"], str(lines()[S["before"]:]))
    P.SetBool("SlowLog", True)


run([("activate", activate), W, W, W, W,  # die ersten 5 s nach dem Start zählen nicht (Laden)
     ("hang", hang), W, ("logged", logged),
     ("off", off_hang), W, ("not logged", not_logged)])
