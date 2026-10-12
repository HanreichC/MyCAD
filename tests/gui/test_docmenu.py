# SPDX-License-Identifier: LGPL-2.1-or-later
"""Dokument im Browser per Rechtsklick löschen (ungespeichert und gespeichert); Toolbar bei schmalem Fenster
bricht um und überdeckt die Fensterknöpfe nicht."""
import os
from harness import *
from PySide6 import QtGui

FILE = os.environ["OUT"] + ".FCStd"


def tree():
    return [w for w in visible(QtWidgets.QTreeWidget)][0]


def context(label, entry):
    t = tree()
    item = [t.topLevelItem(i) for i in range(t.topLevelItemCount()) if t.topLevelItem(i).text(0) == label][0]

    def pick():
        for m in visible(QtWidgets.QMenu):
            L("  menu=%s" % [a.text() for a in m.actions() if a.text()])
            [a for a in m.actions() if a.text() == entry][0].trigger(); m.close()
        QtCore.QTimer.singleShot(600, confirm)

    def confirm(tries=[0]):
        for box in visible(QtWidgets.QMessageBox):
            L("  question: %s" % box.text().replace("\n", " "))
            [b for b in box.buttons() if b.text() == "Delete"][0].click(); return
        tries[0] += 1
        if tries[0] < 10:
            QtCore.QTimer.singleShot(300, confirm)
    QtCore.QTimer.singleShot(500, pick)
    pos = t.visualItemRect(item).center()
    QtWidgets.QApplication.sendEvent(t.viewport(), QtGui.QContextMenuEvent(QtGui.QContextMenuEvent.Mouse, pos, t.viewport().mapToGlobal(pos)))


def panels():
    v = view()
    rects = []
    for w in visible(QtWidgets.QToolButton):
        if w.toolTip() in ("Minimize", "Maximize", "Restore", "Close") or w.property("command") == "Std_New":
            import harness
            p = harness._pos(w)
            rects.append((w.toolTip() or w.property("command"), p.x(), p.y()))
    return rects


run([
    ("new", lambda: Gui.runCommand("Std_New")),
    ("delete unsaved", lambda: context(App.ActiveDocument.Label, "Delete…")), ("wait", lambda: None), ("wait", lambda: None),
    ("after 1", lambda: L("nach Löschen (ungespeichert): documents=%s" % sorted(App.listDocuments()))),
    ("new2", lambda: Gui.runCommand("Std_New")),
    ("save", lambda: App.ActiveDocument.saveAs(FILE)), ("wait", lambda: None),
    ("delete saved", lambda: context(App.ActiveDocument.Label, "Delete…")), ("wait", lambda: None), ("wait", lambda: None),
    ("after 2", lambda: L("nach Löschen (gespeichert): documents=%s file still there=%s" % (sorted(App.listDocuments()), os.path.exists(FILE)))),
    ("narrow", lambda: (mw.showNormal())), ("wait", lambda: None),
    ("size", lambda: mw.resize(1100, 800)), ("wait", lambda: None), ("wait", lambda: None),
    ("check", lambda: (L("schmal %s: %s" % (mw.size().toTuple(), panels())), shot("narrow"))),
    ("restore", lambda: mw.showMaximized()),
])
