# SPDX-License-Identifier: LGPL-2.1-or-later
"""Dokument im Browser per Rechtsklick löschen (ungespeichert und gespeichert); Toolbar bei schmalem Fenster
bricht um und überdeckt die Fensterknöpfe nicht."""
import os
from harness import *

FILE = os.environ["OUT"] + ".FCStd"


def tree():
    return [w for w in visible(QtWidgets.QTreeWidget)][0]


def context(label, entry):
    """Echter Rechtsklick auf den Dokument-Eintrag, echter Klick auf den Menüpunkt und auf "Delete" in der Rückfrage"""
    t = tree()
    item = [t.topLevelItem(i) for i in range(t.topLevelItemCount()) if t.topLevelItem(i).text(0) == label][0]

    def pick():
        QtCore.QTimer.singleShot(600, confirm)  # vorher einplanen: der Klick öffnet die Rückfrage modal und blockiert
        for m in visible(QtWidgets.QMenu):
            L("  menu=%s" % [a.text() for a in m.actions() if a.text()])
            r = m.actionGeometry([a for a in m.actions() if a.text() == entry][0])
            QtTest.QTest.mouseMove(m.windowHandle(), r.center())  # wie eine echte Maus: erst hin, dann klicken
            QtTest.QTest.mouseClick(m.windowHandle(), QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, r.center())

    def confirm(tries=[0]):
        for box in visible(QtWidgets.QMessageBox):
            L("  question: %s" % box.text().replace("\n", " "))
            b = [b for b in box.buttons() if b.text() == "Delete"][0]
            QtTest.QTest.mouseMove(box.windowHandle(), b.mapTo(box, b.rect().center()))
            QtTest.QTest.mouseClick(box.windowHandle(), QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, b.mapTo(box, b.rect().center()))
            return
        tries[0] += 1
        if tries[0] < 10:
            QtCore.QTimer.singleShot(300, confirm)
    QtCore.QTimer.singleShot(1500, pick)
    win, p = mw.windowHandle(), t.viewport().mapTo(mw, t.visualItemRect(item).center())
    QtTest.QTest.mouseMove(win, p)
    QtTest.QTest.mousePress(win, QtCore.Qt.RightButton, QtCore.Qt.NoModifier, p)
    QtTest.QTest.mouseRelease(win, QtCore.Qt.RightButton, QtCore.Qt.NoModifier, p)


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
    ("wait", lambda: None), ("wait", lambda: None),
    ("after 1", lambda: L("nach Löschen (ungespeichert): documents=%s" % sorted(App.listDocuments()))),
    ("new2", lambda: Gui.runCommand("Std_New")),
    ("save", lambda: App.ActiveDocument.saveAs(FILE)), ("wait", lambda: None),
    ("delete saved", lambda: context(App.ActiveDocument.Label, "Delete…")), ("wait", lambda: None), ("wait", lambda: None),
    ("wait", lambda: None), ("wait", lambda: None),
    ("after 2", lambda: L("nach Löschen (gespeichert): documents=%s file still there=%s" % (sorted(App.listDocuments()), os.path.exists(FILE)))),
    ("narrow", lambda: (mw.showNormal())), ("wait", lambda: None),
    ("size", lambda: mw.resize(1100, 800)), ("wait", lambda: None), ("wait", lambda: None),
    ("check", lambda: (L("schmal %s: %s" % (mw.size().toTuple(), panels())), shot("narrow"))),
    ("restore", lambda: mw.showMaximized()),
])
