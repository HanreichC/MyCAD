# SPDX-License-Identifier: LGPL-2.1-or-later
"""Enter bestätigt den Extrude-Dialog, auch wenn die Werkzeugleiste noch den Fokus hat (nach dem Klick auf "Extrudieren"
kam Enter dort an und verpuffte). Die Skizze verschwindet nach dem ersten Extrude wie in Fusion; blendet man sie wieder
ein und extrudiert noch einmal, bleibt sie sichtbar. Tippt man bei offenem Dialog in einem anderen Panel (Umbenennen im
Browser), gehört Enter dieser Eingabe: der Name wird übernommen, der Dialog bleibt offen."""
from harness import *
import Design

S = {}
W = ("wait", lambda: None)


def setup():
    d = doc(); root = [o for o in d.Objects if o.TypeId == "App::Part"][0]
    S["sk"] = Design.newSketch(root)
    for g in rect(0, 0, 10, 10):
        S["sk"].addGeometry(g)
    d.recompute()


def start():
    prof = [o for o in S["sk"].InList if o.TypeId == "Design::Profiles"][0]
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(prof, "Face1")
    click(button("Design_Extrude"))


def enter():
    """Fokus wie nach dem Klick in der Werkzeugleiste, Enter an den 3D-Viewer (dort landet die Tastatur)"""
    button("Design_Extrude").setFocus()
    QtTest.QTest.keyClick(view(), QtCore.Qt.Key_Return)


def extrudes():
    return len([o for o in doc().Objects if o.TypeId == "Design::Extrude"])


def first():
    check("Enter confirms the extrude dialog while the toolbar has the focus", not Gui.Control.activeDialog() and extrudes() == 1,
          "dialog=%s extrudes=%d" % (Gui.Control.activeDialog(), extrudes()))
    check("the sketch is hidden after its first extrude", not S["sk"].Visibility)


def second():
    check("Enter confirms the second extrude too", not Gui.Control.activeDialog() and extrudes() == 2,
          "dialog=%s extrudes=%d" % (Gui.Control.activeDialog(), extrudes()))
    check("a sketch shown again on purpose stays visible after the next extrude", S["sk"].Visibility)


def rename():
    t = visible(QtWidgets.QTreeWidget)[0]; t.expandAll()
    item = [i for i in t.findItems("Body", QtCore.Qt.MatchStartsWith | QtCore.Qt.MatchRecursive)][0]
    S["old"] = item.text(0); t.editItem(item, 0)


def type_name():
    ed = [w for w in QtWidgets.QApplication.allWidgets() if isinstance(w, QtWidgets.QLineEdit) and w.isVisible() and w.text() == S["old"]][0]
    ed.setFocus(); ed.selectAll(); QtTest.QTest.keyClicks(ed, "Base")


def renamed():
    labels = [b.Label for b in doc().Objects if b.TypeId == "Design::Body"]
    check("Enter while renaming in the browser renames and keeps the open dialog", "Base" in labels and Gui.Control.activeDialog(),
          "labels=%s dialog=%s" % (labels, Gui.Control.activeDialog()))


run([("activate", activate), ("setup", setup), W,
     ("start", start), W, ("enter", enter), W, ("first", first),
     ("show", lambda: setattr(S["sk"], "Visibility", True)), W,
     ("start 2", start), W, ("enter 2", enter), W, ("second", second),
     ("show again", lambda: setattr(S["sk"], "Visibility", True)), W, ("start 3", start), W,
     ("rename", rename), W, ("name", type_name), W, ("enter 3", lambda: QtTest.QTest.keyClick(view(), QtCore.Qt.Key_Return)), W,
     ("renamed", renamed)])
