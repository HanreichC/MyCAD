# SPDX-License-Identifier: LGPL-2.1-or-later
"""Phase 14, Chaos 2: weitere Fehlbedienungen. Unsinn ins Maßfeld tippen ("abc", "1/0", 0, -5), Extrude mit 0 und
Enter doppelt; speichern, während eine Skizze offen ist; die Grundskizze mit abhängigem Extrude über die Zeitleiste
löschen; den Körper löschen, auf dessen Fläche eine Skizze liegt; das Dokument schließen, während ein Werkzeug offen
ist. Danach jeweils: kein Absturz, keine Python-Ausnahme, kein Abhängigkeitskreis, nichts bleibt liegen."""
import os
import sys
from PySide6 import QtGui
from harness import *
sys.path.insert(0, os.path.join(os.path.dirname(os.environ["SCRIPT"]), "..", "design"))
import design as D
import Design

S = {}
W = ("wait", lambda: None)
V = App.Vector
FILE = os.environ["OUT"] + ".chaos2.mycad"


def build():
    d = doc()
    S["base"] = D.sketch(d, D.rect(0, 0, 60, 40))
    S["ext"], S["body"] = D.extrude(d, S["base"], 10)
    S["top"] = D.sketch(d, D.circle(30, 20, 5), support=(S["body"], D.top_face(S["body"])))
    S["cut"] = D.extrude(d, S["top"], 10, op="Cut", bodies=[S["body"]], Reversed=True)[0]
    d.recompute()
    S["vol"] = round(S["body"].Shape.Volume, 2)
    Gui.ActiveDocument.ActiveView.viewIsometric(); Gui.SendMsgToActiveView("ViewFit")


def invariants(where):
    def f():
        problems = D.model_problems(doc()) if App.ActiveDocument else []
        check("%s: no dependency cycle, nothing left to recompute" % where, not problems, str(problems))
        if App.ActiveDocument:
            L("  %s: problems %s" % (where, [(o.Label, t[:60]) for o, t in Design.problems(doc())]))
    return f


def extrude_new():
    sk = D.sketch(doc(), D.rect(70, 0, 90, 20))
    S["new"] = sk
    prof = D.profiles(sk)
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(prof, "Face1")
    Gui.runCommand("Design_Extrude")


def typing(text):
    return lambda: type_field("Distance", text)


def enter_twice():
    w = view().viewport()
    QtTest.QTest.keyClick(w, QtCore.Qt.Key_Return)
    QtTest.QTest.keyClick(w, QtCore.Qt.Key_Return)


def tidy():
    for m in visible(QtWidgets.QMessageBox):
        L("  message: %s" % m.text()[:120]); m.close()
    for b in visible(QtWidgets.QPushButton):
        if b.text().replace("&", "") == "Cancel":
            b.click(); break


def open_sketch():
    Gui.ActiveDocument.setEdit(S["top"].Name)


def save_now():
    S["editing before save"] = Gui.ActiveDocument.getInEdit() is not None
    doc().saveAs(FILE)


def saved():
    check("saving while a sketch is open works and keeps editing",
          os.path.exists(FILE) and S["editing before save"] and Gui.ActiveDocument.getInEdit() is not None,
          "%s exists %s, editing before %s, after %s" % (FILE, os.path.exists(FILE), S["editing before save"],
                                                         Gui.ActiveDocument.getInEdit()))
    if Gui.ActiveDocument.getInEdit():
        Gui.ActiveDocument.resetEdit()


def timeline_delete(obj):
    """Rechtsklick > Löschen in der Zeitleiste; Rückfragen bestätigen wie ein eiliger Mensch"""
    def f():
        entries = [b for b in visible(QtWidgets.QToolButton) if b.property("timelineIndex") is not None
                   and b.accessibleName() == obj.Label]
        if not entries:
            L("  no timeline entry for %s" % obj.Label); return

        def pick():
            m = QtWidgets.QApplication.activePopupWidget()
            acts = [a for a in (m.actions() if m else []) if a.text() == "Delete"]
            if acts:
                m.setActiveAction(acts[0]); QtTest.QTest.keyClick(m, QtCore.Qt.Key_Return)
            elif m:
                m.close()

        def confirm():
            for box in visible(QtWidgets.QMessageBox) + visible(QtWidgets.QDialog):
                ok = [b for b in box.findChildren(QtWidgets.QPushButton) if b.isVisible()
                      and b.text().replace("&", "") in ("Delete", "Yes", "OK", "Delete All")]
                if ok:
                    L("  confirmed: %s" % ok[0].text()); ok[0].click()
        QtCore.QTimer.singleShot(500, pick)
        QtCore.QTimer.singleShot(1500, confirm)
        w = entries[0]
        QtWidgets.QApplication.sendEvent(w, QtGui.QContextMenuEvent(QtGui.QContextMenuEvent.Mouse, w.rect().center()))
    return f


def delete_body():
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(S["body"])
    QtCore.QTimer.singleShot(1200, lambda: [b.click() for box in visible(QtWidgets.QMessageBox)
                                             for b in box.findChildren(QtWidgets.QPushButton)
                                             if b.isVisible() and b.text().replace("&", "") in ("Delete", "Yes", "OK")][:1])
    Gui.runCommand("Design_Delete")


def close_with_tool():
    extrude_new_again = D.sketch(doc(), D.rect(0, 50, 10, 60))
    prof = D.profiles(extrude_new_again)
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(prof, "Face1")
    Gui.runCommand("Design_Extrude")
    QtCore.QTimer.singleShot(800, lambda: App.closeDocument(doc().Name))


def closed():
    check("closing the document with a tool open: MyCAD stays alive", Gui.getMainWindow() is not None)


run([("activate", activate), ("build", build), W, W, ("inv 0", invariants("start")),
     ("new extrude", extrude_new), W, ("abc", typing("abc")), W, ("1/0", typing("1/0")), W, ("zero", typing("0")), W,
     ("minus", typing("-5")), W, ("zero again", typing("0")), W, ("enter twice", enter_twice), W, W, ("tidy 1", tidy), W, ("tidy 1b", tidy), W,  # erst die Meldung, dann das Panel (Abbrechen)
     ("inv 1", invariants("garbage typed, enter twice")),
     ("open sketch", open_sketch), W, W, ("save in sketch", save_now), W, ("saved", saved), W, ("inv 2", invariants("saved in sketch")),
     ("delete base sketch", lambda: timeline_delete(S["base"])()), W, W, W, ("tidy 2", tidy), W,
     ("inv 3", invariants("base sketch deleted")),
     ("undo", lambda: [Gui.runCommand("Std_Undo") for _ in range(3)]), W, W, ("inv 4", invariants("undo")),
     ("delete body", delete_body), W, W, W, ("tidy 3", tidy), W, ("inv 5", invariants("body with a sketch on it deleted")),
     ("undo 2", lambda: [Gui.runCommand("Std_Undo") for _ in range(3)]), W, W, ("inv 6", invariants("undo 2")),
     ("close with tool", close_with_tool), W, W, W, ("closed", closed),
     ])
