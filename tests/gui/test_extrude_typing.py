# SPDX-License-Identifier: LGPL-2.1-or-later
"""Abstand eines Extrudes nachträglich von 10 auf 2 mm tippen (Cursor vor die 1, Entf, 2, Entf): dazwischen steht kurz
"0.00 mm". Die Live-Vorschau zeigt den Fehler im Panel, aber keine Meldung unter dem ViewCube, die stehen bliebe,
obwohl der Wert gleich wieder stimmt ("Distance must be greater than zero")."""
from harness import *

S = {}


def setup():
    make_body(rect(0, 0, 40, 30), 0, 10, "Box")
    S["f"] = [o for o in doc().Objects if o.TypeId == "Design::Extrude"][-1]


def notes():
    return [w.text() for w in QtWidgets.QApplication.allWidgets() if isinstance(w, QtWidgets.QLabel) and w.isVisible()
            and ("zero" in w.text() or "null" in w.text())]


def edit():
    box = field("Distance"); return box.lineEdit() if hasattr(box, "lineEdit") else box


def state(tag):
    f = S["f"]
    L("  %s: field=%r Distance=%s state=%s msgs=%s" % (tag, edit().text(), f.Distance, f.State, notes()))


def keys(seq):
    e = edit()
    for k in seq:
        if k in ("HOME", "DEL", "BS", "END"):
            QtTest.QTest.keyClick(e, {"HOME": QtCore.Qt.Key_Home, "DEL": QtCore.Qt.Key_Delete, "BS": QtCore.Qt.Key_Backspace,
                                      "END": QtCore.Qt.Key_End}[k])
        else:
            QtTest.QTest.keyClicks(e, k)
        QtWidgets.QApplication.processEvents()
        state(k)


in_order([
    ("activate", activate), ("setup", setup),
    ("edit", lambda: Gui.ActiveDocument.setEdit(S["f"])), ("wait", lambda: None),
    ("start", lambda: state("start")),
    ("home del", lambda: (edit().setFocus(), keys(["HOME", "DEL", "2", "DEL"]))), ("wait", lambda: None),
    ("later", lambda: (state("1s later"), check("typing through 0 mm leaves no error notice, the value is 2 mm",
                                                abs(S["f"].Distance.Value - 2) < 1e-9 and not [m for m in notes() if "Notify_Error" in m],
                                                str(notes())))),
])
