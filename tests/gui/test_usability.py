# SPDX-License-Identifier: LGPL-2.1-or-later
"""Rückmeldungen: Dokument im Browser per Rechtsklick schließen; Drehen um die Mitte des Körpers unter dem Cursor."""
import os
from harness import *
from PySide6 import QtGui


def tree():
    t = [w for w in visible(QtWidgets.QTreeWidget)][0]
    return t


def doc_item(label):
    t = tree()
    for i in range(t.topLevelItemCount()):
        if t.topLevelItem(i).text(0) == label:
            return t, t.topLevelItem(i)
    raise RuntimeError("no item " + label)


def context_close():
    t, item = doc_item(App.ActiveDocument.Label)
    L("  closing %s, documents before=%s" % (item.text(0), sorted(App.listDocuments())))

    def pick():
        for m in visible(QtWidgets.QMenu):
            L("  menu=%s" % [a.text() for a in m.actions() if a.text()])
            [a for a in m.actions() if a.text() == "Close"][0].trigger(); m.close()
        QtCore.QTimer.singleShot(600, discard)

    def discard(tries=[0]):
        for box in visible(QtWidgets.QDialog):
            texts = [b.text().replace("&", "") for b in box.findChildren(QtWidgets.QAbstractButton) if b.text()]
            L("  save prompt: %s" % texts)
            for b in box.findChildren(QtWidgets.QAbstractButton):
                if b.text().replace("&", "") in ("Discard", "Don't Save", "No", "Close without saving", "Don't save"):
                    b.click(); return
        tries[0] += 1
        if tries[0] < 10:
            QtCore.QTimer.singleShot(300, discard)
    QtCore.QTimer.singleShot(500, pick)
    pos = t.visualItemRect(item).center()
    QtWidgets.QApplication.sendEvent(t.viewport(), QtGui.QContextMenuEvent(QtGui.QContextMenuEvent.Mouse, pos, t.viewport().mapToGlobal(pos)))


def screen(p):
    v = Gui.ActiveDocument.ActiveView
    return tuple(int(c) for c in v.getPointOnViewport(p))


def orbit_over(b):
    # Inventor-Stil: linke Maustaste dreht ohne Zusatztaste (das Drehzentrum gilt für alle Stile gleich)
    v = view(); vp = v.viewport()
    c = screen(b.Shape.BoundBox.Center); h = vp.height()
    start = QtCore.QPoint(c[0], h - c[1])  # Coin zählt y von unten
    QtTest.QTest.mouseMove(vp, start)
    QtTest.QTest.mousePress(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, start)
    for i in range(1, 11):
        QtTest.QTest.mouseMove(vp, start + QtCore.QPoint(12 * i, 4 * i))
    QtTest.QTest.mouseRelease(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, start + QtCore.QPoint(120, 40))


state = {}
run([
    ("new", lambda: Gui.runCommand("Std_New")),
    ("close via menu", context_close), ("wait", lambda: None), ("wait", lambda: None),
    ("closed?", lambda: (L("documents after=%s panels visible=%s" % (sorted(App.listDocuments()), len([w for w in visible(QtWidgets.QTreeWidget)]))), shot("afterclose"))),
    ("bodies", lambda: (make_body(rect(0, 0, 20, 20), 0, 20, "A"), make_body(rect(100, 0, 120, 20), 0, 20, "B"),
                        Gui.ActiveDocument.ActiveView.viewIsometric(), Gui.SendMsgToActiveView("ViewFit"))),
    ("mode", lambda: L("RotationMode=%d" % App.ParamGet("User parameter:BaseApp/Preferences/View").GetInt("RotationMode"))),
    ("before", lambda: state.update(a=screen(body("A").Shape.BoundBox.Center), b=screen(body("B").Shape.BoundBox.Center))),
    ("inventor", lambda: Gui.ActiveDocument.ActiveView.setNavigationType("Gui::InventorNavigationStyle")),
    ("orbit", lambda: orbit_over(body("B"))),
    ("after", lambda: L("Mitte B vorher %s nachher %s (gleich = dreht um B); Mitte A %s -> %s" % (
        state["b"], screen(body("B").Shape.BoundBox.Center), state["a"], screen(body("A").Shape.BoundBox.Center)))),
])
