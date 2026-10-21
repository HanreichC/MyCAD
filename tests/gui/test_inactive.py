# SPDX-License-Identifier: LGPL-2.1-or-later
"""Fenster verliert den Fokus (ein anderes Programm wird aktiv): Toolbar und ViewCube bleiben sichtbar.
Früher malte Qt danach nur den Fensterrand neu, Coin löschte aber das ganze Bild: alle Bedienelemente weg,
bis man wieder ins Fenster klickte. Ein kleines Fenster aus einem zweiten Prozess holt sich den Fokus."""
import os
import subprocess
from harness import *
from PySide6 import QtGui

THIEF = """
from PySide6.QtWidgets import QApplication, QLabel
from PySide6.QtCore import QTimer
a = QApplication([]); w = QLabel('MyCAD test: takes the focus'); w.resize(300, 120); w.show(); w.activateWindow()
QTimer.singleShot(8000, a.quit); a.exec()
"""


def dark_pixels(item_test):
    """dunkle Pixel (Symbole, Beschriftung) im aktuellen Bild der 3D-Ansicht, im Bereich der passenden Panels"""
    img = view().viewport().grab().toImage()
    rects = [i.sceneBoundingRect().toRect() for i in view().scene().items()
             if isinstance(i, QtWidgets.QGraphicsProxyWidget) and i.isVisible() and item_test(i.widget())]
    return sum(QtGui.QColor(img.pixel(x, y)).lightness() < 110
               for r in rects for x in range(max(r.left(), 0), min(r.right(), img.width()), 2)
               for y in range(max(r.top(), 0), min(r.bottom(), img.height()), 2))


def toolbar(w):
    return w.width() > 600 and w.height() < 150


def report(tag):
    L("%s: app inactive=%s, toolbar dark pixels=%d (> 200 expected)" % (
        tag, QtWidgets.QApplication.applicationState() != QtCore.Qt.ApplicationActive, dark_pixels(toolbar)))


run([
    ("body", lambda: make_body(rect(0, 0, 40, 30), 0, 10, "Box")),
    ("fit", lambda: (Gui.ActiveDocument.ActiveView.viewIsometric(), Gui.SendMsgToActiveView("ViewFit"))),
    ("active", lambda: report("aktiv")),
    ("thief", lambda: subprocess.Popen(["python3", "-c", THIEF])),
    ("wait", lambda: None), ("wait", lambda: None),
    ("inactive", lambda: report("inaktiv")),
])
