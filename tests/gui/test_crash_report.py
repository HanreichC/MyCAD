# SPDX-License-Identifier: LGPL-2.1-or-later
# runs: 2  (tests/run_all.sh startet ihn zweimal mit demselben Home: erst abstürzen, dann prüfen)
"""Absturz: der erste Lauf stürzt absichtlich ab (Nullzeiger). Der zweite sagt beim Start, dass MyCAD unerwartet beendet
wurde und die Designs gespeichert sind; im Archiv liegen der Bericht und daneben der lesbare Stack mit Funktionsnamen.
    MYCAD_HOME=/tmp/c tests/gui/run.sh tests/gui/test_crash_report.py /tmp/c1   → stürzt ab
    MYCAD_HOME=/tmp/c tests/gui/run.sh tests/gui/test_crash_report.py /tmp/c2   → prüft"""
import glob
import os
from harness import *

MARK = os.path.join(App.getUserAppDataDir(), "crash-test-done")


def crash():
    open(MARK, "w").close()
    import ctypes
    ctypes.string_at(0)  # echter Speicherzugriffsfehler: der Crash-Reporter schreibt den Bericht


def alert():
    return [b for b in visible(QtWidgets.QMessageBox) if "closed unexpectedly" in b.windowTitle()
            or "closed unexpectedly" in b.text()]


def notice():
    boxes = alert()
    check("after a crash MyCAD says so at the next start", bool(boxes), str([b.text() for b in visible(QtWidgets.QMessageBox)]))
    folder = os.path.join(App.getUserAppDataDir(), "CrashReports", "archive")
    reports = sorted(glob.glob(os.path.join(folder, "*.fcrash")))
    texts = sorted(glob.glob(os.path.join(folder, "*.fcrash.txt")))
    check("the report is archived", bool(reports), str(os.listdir(folder) if os.path.isdir(folder) else folder))
    stack = open(texts[-1]).read() if texts else ""
    check("a readable stack lies beside it, with function names", "libFreeCAD" in stack and "(" in stack,
          stack[:300].replace("\n", " | "))
    for b in boxes:
        b.accept()
    os.remove(MARK)


if not os.path.exists(MARK):
    run([("crash", crash)])
else:
    run([("notice", notice)], delay=2500)
