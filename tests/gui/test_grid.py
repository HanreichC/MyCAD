# SPDX-License-Identifier: LGPL-2.1-or-later
"""Bodenraster: unter einem Körper sichtbar (Pixel ändern sich gegenüber "aus"), Schalter "Show grid" in den
Einstellungen blendet es aus und wieder ein. Screenshots: iso, perspektivisch, von oben, dunkel, Skizze (ohne Raster)."""
import os
from harness import *

grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")
viewgrp = App.ParamGet("User parameter:BaseApp/Preferences/View")
images = {}


def grab(tag):
    img = view().viewport().grab().toImage(); images[tag] = img
    img.save(os.environ["OUT"] + "." + tag + ".png")


def differing(a, b):
    """Anzahl Pixel (jedes 4. in beide Richtungen), die sich zwischen zwei Bildern unterscheiden"""
    a, b = images[a], images[b]
    return sum(a.pixel(x, y) != b.pixel(x, y) for x in range(0, a.width(), 4) for y in range(0, a.height(), 4))


def settings(action):
    def run_in_dialog():
        try:
            d = visible(QtWidgets.QDialog)[0]
            action(d); d.accept()
        except Exception as e:
            L("  exc %s: %s" % (type(e).__name__, e))
    QtCore.QTimer.singleShot(1200, run_in_dialog)
    Gui.runCommand("MyCAD_Settings")


def toggle_grid_twice(d):
    """aus, Bild, wieder an, Bild; Klick auf den Schalter am rechten Ende der Zeile (PySide liefert für den Schalter
    selbst manchmal einen veralteten Wrapper, die Zeile ist ein normales QWidget)"""
    row = [l for l in d.findChildren(QtWidgets.QLabel) if l.text() == "Show grid"][0].parentWidget()
    for tag in ("off", "on2"):
        p = row.mapTo(d, QtCore.QPoint(row.width() - 20, row.height() // 2))
        QtTest.QTest.mouseClick(d.windowHandle(), QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)  # echter Klick ins Fenster
        QtTest.QTest.qWait(500)
        L("  GroundGrid=%s" % grp.GetBool("GroundGrid", True)); grab(tag)


def segment(text):
    return lambda d: [b for b in d.findChildren(QtWidgets.QPushButton) if b.text() == text][0].click()


def iso():
    Gui.ActiveDocument.ActiveView.viewIsometric(); Gui.SendMsgToActiveView("ViewFit")


def top():
    Gui.ActiveDocument.ActiveView.viewTop(); Gui.SendMsgToActiveView("ViewFit")


run([
    ("setup", lambda: make_body(rect(0, 0, 60, 40), 0, 15, "Box")), ("iso", iso), ("grab on", lambda: grab("on")),
    ("toggle", lambda: settings(toggle_grid_twice)), ("wait", lambda: None),
    ("compare", lambda: L("grid visible: %s pixels differ on/off (> 200 expected)" % differing("on", "off"))),
    ("compare2", lambda: L("back on: %s pixels differ from first (0 expected)" % differing("on", "on2"))),
    ("perspective", lambda: (viewgrp.SetBool("Orthographic", False), iso())), ("grab persp", lambda: grab("persp")),
    ("ortho", lambda: (viewgrp.SetBool("Orthographic", True), top())), ("grab top", lambda: grab("top")),
    ("dark", lambda: (iso(), settings(segment("Dark")))), ("wait", lambda: None), ("grab dark", lambda: grab("dark")),
    ("light", lambda: settings(segment("Automatic"))), ("wait", lambda: None),
    ("sketch", lambda: Gui.ActiveDocument.setEdit(doc().getObject("Sketch"))), ("wait", lambda: None),
    ("grab sketch", lambda: grab("sketch")),
    ("leave", lambda: Gui.ActiveDocument.resetEdit()),
])
