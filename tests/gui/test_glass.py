# SPDX-License-Identifier: LGPL-2.1-or-later
"""Liquid Glass "Ultra Clear": das Raster scheint durch die Werkzeugleiste. Gemessen wird die Werkzeugleiste mit und
ohne Raster: scheinen die Linien durch, ändert sich der Unterschied der beiden Bilder von Pixel zu Pixel (Struktur);
ein ganz verwischtes Raster hellt nur gleichmäßig ab. Nur helles Glas zählt, Symbole und Schrift nicht.
Glas-Stufe über den Regler, Raster über den Schalter in den Einstellungen; am Ende wieder wie vorher."""
import os
from harness import *
from PySide6 import QtGui

grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")
old = grp.GetFloat("GlassLevel", 0.5)
images = {}


def settings(action):
    def act():
        try:
            d = [w for w in visible(QtWidgets.QDialog) if w.windowTitle() == "Settings"][0]
            action(d)
            d.accept()
        except Exception as e:
            L("  exc %s: %s" % (type(e).__name__, e))
    QtCore.QTimer.singleShot(1200, act)
    Gui.runCommand("MyCAD_Settings")


def ultra_clear(d):
    s = [s for s in d.findChildren(QtWidgets.QSlider) if s.accessibleName() == "Liquid Glass"][0]
    s.setValue(s.minimum())
    L("  GlassLevel=%.2f" % grp.GetFloat("GlassLevel", -1))


def toggle_grid(d):
    """echter Klick auf den Schalter am Ende der Zeile (PySide liefert für den Schalter selbst teils alte Wrapper)"""
    row = [l for l in d.findChildren(QtWidgets.QLabel) if l.text() == "Show grid"][0].parentWidget()
    p = row.mapTo(d, QtCore.QPoint(row.width() - 20, row.height() // 2))
    QtTest.QTest.mouseClick(d.windowHandle(), QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)
    QtTest.QTest.qWait(300)
    L("  GroundGrid=%s" % grp.GetBool("GroundGrid", True))


def toolbar():
    return [i.sceneBoundingRect().toRect() for i in view().scene().items()
            if isinstance(i, QtWidgets.QGraphicsProxyWidget) and i.isVisible() and i.widget().width() > 600 and i.widget().height() < 150][0]


def grab(tag):
    images[tag] = view().viewport().grab().toImage()
    images[tag].save(os.environ["OUT"] + "." + tag + ".png")


def compare():
    a, b, r = images["grid"], images["nogrid"], toolbar().adjusted(8, 8, -8, -8)  # ohne Lichtkante und Linse am Rand

    def light(img, x, y):
        return QtGui.QColor(img.pixel(x, y)).lightness()
    total = pairs = 0
    for y in range(r.top(), r.bottom(), 2):
        for x in range(r.left(), r.right()):
            la, lb, la2, lb2 = light(a, x, y), light(b, x, y), light(a, x + 1, y), light(b, x + 1, y)
            if min(la, lb, la2, lb2) > 200:
                total += abs((la2 - lb2) - (la - lb))
                pairs += 1
    L("grid structure in the Ultra Clear toolbar: %.3f (> 0.13 expected; the renderer before showed 0.08)" % (total / pairs))


run([
    ("body", lambda: make_body(rect(0, 0, 40, 30), 0, 10, "Box")),
    ("fit", lambda: (Gui.ActiveDocument.ActiveView.viewIsometric(), Gui.SendMsgToActiveView("ViewFit"))),
    ("clear", lambda: settings(ultra_clear)), ("wait", lambda: None), ("grab grid", lambda: grab("grid")),
    ("grid off", lambda: settings(toggle_grid)), ("wait", lambda: None), ("grab nogrid", lambda: grab("nogrid")),
    ("compare", compare),
    ("grid on", lambda: settings(toggle_grid)), ("wait", lambda: None),
    ("restore", lambda: grp.SetFloat("GlassLevel", old)),
])
