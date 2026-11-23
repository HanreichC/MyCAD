# SPDX-License-Identifier: LGPL-2.1-or-later
"""12.9 Verschieben per Satz in Strg+K: "10 mm nach oben" öffnet Verschieben mit 0, 0, 10 für den einzigen Körper,
OK hebt ihn um 10 mm"""
from harness import *

S = {}
W = ("wait", lambda: None)


def field():
    return [e for e in visible(QtWidgets.QLineEdit) if e.accessibleName() == "Search"][0]


def results():
    lists = [l for l in visible(QtWidgets.QListWidget) if l.accessibleName() == "Results"]
    return [lists[0].item(i).data(QtCore.Qt.AccessibleTextRole) for i in range(lists[0].count())] if lists else []


def say():
    Gui.Selection.clearSelection()
    Gui.runCommand("MyCAD_Search")
    f = field(); f.clear(); f.insert("10 mm nach oben")


def hit():
    r = results()
    check("understood: move up 10", bool(r) and r[0] == "Move by 0, 0, 10 mm", str(r[:3]))


def opened():
    m = [o for o in doc().Objects if o.TypeId == "Design::Move"]
    check("Enter opens Move with 0, 0, 10", Gui.Control.activeDialog() and m and m[-1].Translation == App.Vector(0, 0, 10),
          "%s notices=%s errors=%s" % (m and m[-1].Translation, notices(), errors()))


run([("activate", activate),
     ("setup", lambda: S.update(body=make_body(rect(0, 0, 20, 10), 0, 5, "Block"))), W,
     ("say", say), W, ("hit", hit),
     ("enter", lambda: QtTest.QTest.keyClick(field(), QtCore.Qt.Key_Return)), W, W,
     ("opened", opened), ("ok", ok), W,
     ("moved", lambda: check("OK lifts the block by 10 mm", abs(S["body"].Shape.BoundBox.ZMin - 10) < 1e-6,
                             str(S["body"].Shape.BoundBox))),
     ("errors", lambda: check("no errors", not errors(), str(errors()))),
     ])
