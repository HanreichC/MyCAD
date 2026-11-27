# SPDX-License-Identifier: LGPL-2.1-or-later
"""F2 benennt um (Hilfe: "F2 benennt den gewählten Eintrag um"): ein Körper, im Browser oder in der Ansicht gewählt,
und eine Skizze. F2 öffnet das Namensfeld im Browser, Tippen und Enter benennt um."""
from harness import *

S = {}
W = ("wait", lambda: None)


def tree():
    return [t for t in visible(QtWidgets.QTreeWidget) if t.topLevelItemCount()][0]


def editor():
    eds = [e for e in tree().findChildren(QtWidgets.QLineEdit) if e.isVisible()]
    return eds[0] if eds else None


def setup():
    S["body"] = make_body(rect(0, 0, 40, 30), 0, 10, "Plate")
    S["sketch"] = [o for o in doc().Objects if o.TypeId == "Sketcher::SketchObject"][0]
    S["sketch"].Visibility = True
    Gui.SendMsgToActiveView("ViewFit")


def select(key):
    def go():
        Gui.Selection.clearSelection()
        Gui.Selection.addSelection(S[key])
    return go


def f2_from_view():
    """wie nach einem Klick in die Ansicht: Fokus in der 3D-Ansicht, dann F2 ans Fenster"""
    activate()
    view().viewport().setFocus()
    QtTest.QTest.keyClick(mw.windowHandle(), QtCore.Qt.Key_F2)


def f2_in_tree():
    """wie nach einem Klick in den Browser: Fokus im Browser, F2"""
    tree().setFocus()
    QtTest.QTest.keyClick(tree(), QtCore.Qt.Key_F2)


def rename_to(name):
    def go():
        e = editor()
        if e is None:
            return
        e.selectAll()
        QtTest.QTest.keyClicks(e, name)
        QtTest.QTest.keyClick(e, QtCore.Qt.Key_Return)
    return go


def opened(label):
    return lambda: check(label, editor() is not None, "no name field in the browser")


run([("activate", activate), ("setup", setup), W, W,
     # 1. Körper gewählt, Fokus in der Ansicht (wie nach einem Klick auf den Körper)
     ("select body", select("body")), W,
     ("F2 from view", f2_from_view), W,
     ("open from view", opened("F2 with the body selected in the view opens its name field")),
     ("type", rename_to("Base")), W,
     ("renamed", lambda: check("typing and Enter renames the body", S["body"].Label == "Base", S["body"].Label)),
     # 2. Skizze gewählt, Fokus im Browser
     ("select sketch", select("sketch")), W,
     ("F2 in tree", f2_in_tree), W,
     ("open in tree", opened("F2 in the browser with the sketch selected opens its name field")),
     ("type 2", rename_to("Outline")), W,
     ("renamed 2", lambda: check("the sketch is renamed", S["sketch"].Label == "Outline", S["sketch"].Label)),
     # 3. Skizze gewählt, Fokus in der Ansicht
     ("select sketch again", select("sketch")), W,
     ("F2 from view 2", f2_from_view), W,
     ("open from view 2", opened("F2 with the sketch selected in the view opens its name field")),
     ("escape", lambda: editor() and QtTest.QTest.keyClick(editor(), QtCore.Qt.Key_Escape)), W,
     ("errors", lambda: check("no errors", not errors(), str(errors()))),
     ])
