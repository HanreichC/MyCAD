# SPDX-License-Identifier: LGPL-2.1-or-later
"""H5: Inspector und Druck-Legende folgen dem Öffnen und Schließen eines Werkzeugs per Signal (dialogChanged), nicht
im 250-ms-Takt. 60 ms nach dem Öffnen ist der Inspector da, 60 ms nach dem Schließen weg (mit dem Takt meist noch
nicht). Fehler stehen als FAIL im Protokoll."""
from harness import *

state = {}


def taskview_visible():
    return any(w.metaObject().className() == "Gui::TaskView::TaskView" and w.isVisible()
               for w in QtWidgets.QApplication.allWidgets())


def soon(key):
    QtCore.QTimer.singleShot(60, lambda: state.update({key: taskview_visible()}))


run([
    ("body", lambda: make_body(rect(0, 0, 40, 30), 0, 10, "Box")),
    ("before", lambda: check("no tool, no inspector", not taskview_visible())),
    ("open", lambda: (Gui.runCommand("Design_Measure"), soon("open"))),
    ("opened", lambda: check("H5: the inspector is there 60 ms after a tool opens", state.get("open") is True, str(state))),
    ("close", lambda: (Gui.Control.closeDialog(), soon("closed"))),
    ("closed", lambda: check("H5: and gone 60 ms after it closes", state.get("closed") is False, str(state))),
])
