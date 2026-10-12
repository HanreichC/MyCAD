# SPDX-License-Identifier: LGPL-2.1-or-later
"""Tasten als Maustasten (cad.helper-Funktion): Leertaste halten + Bewegung ohne Maustaste verschiebt die Ansicht.
Danach das Einstellungen-Fenster öffnen (Screenshot)."""
import os
from harness import *

grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")
old = grp.GetString("MouseKeys", "[]")
App.ParamGet("User parameter:BaseApp/Preferences/View").SetString("NavigationStyle", "Gui::RevitNavigationStyle")


def camera():
    cam = Gui.ActiveDocument.ActiveView.getCamera()
    return [l.strip() for l in cam.splitlines() if l.strip().startswith("position")][0]


def drag(key):
    vp = view().viewport(); c = vp.rect().center()
    QtTest.QTest.mouseMove(vp, c)
    QtTest.QTest.keyPress(vp, key)
    for i in range(1, 11):
        QtTest.QTest.mouseMove(vp, c + QtCore.QPoint(15 * i, 8 * i))
    QtTest.QTest.keyRelease(vp, key)


def real_middle():
    vp = view().viewport(); c = vp.rect().center()
    QtTest.QTest.mousePress(vp, QtCore.Qt.MiddleButton, QtCore.Qt.NoModifier, c)
    for i in range(1, 11):
        QtTest.QTest.mouseMove(vp, c + QtCore.QPoint(15 * i, 8 * i))
    QtTest.QTest.mouseRelease(vp, QtCore.Qt.MiddleButton, QtCore.Qt.NoModifier, c + QtCore.QPoint(150, 80))


def close_settings():
    for d in visible(QtWidgets.QDialog):
        d.grab().save(os.environ["OUT"] + ".dialog.png")
        style = [c for c in d.findChildren(QtWidgets.QComboBox) if c.findText("Blender") >= 0][0]
        style.highlighted.emit(style.findText("Blender"))  # Vorschau beim Überfahren der Liste
        d.grab().save(os.environ["OUT"] + ".hover.png")
        L("  more preferences button=%s" % any("More" in b.text() for b in d.findChildren(QtWidgets.QPushButton)))
        seg = [b for b in d.findChildren(QtWidgets.QPushButton) if b.text() == "Keys"][0]
        seg.click(); d.grab().save(os.environ["OUT"] + ".keys.png")
        d.accept()


run([
    ("setup", lambda: make_body(rect(0, 0, 60, 40), 0, 15, "Box")),
    ("map", lambda: grp.SetString("MouseKeys", '[{"key":32,"button":"middle","mode":"hold"}]')),
    ("before", lambda: L("camera before=" + camera())),
    ("perspective", lambda: App.ParamGet("User parameter:BaseApp/Preferences/View").SetBool("Orthographic", False)),
    ("type", lambda: L("camera type=" + Gui.ActiveDocument.ActiveView.getCameraType() + " (Perspective erwartet)")),
    ("ortho", lambda: App.ParamGet("User parameter:BaseApp/Preferences/View").SetBool("Orthographic", True)),
    ("real", real_middle),
    ("after real", lambda: L("camera after real middle=" + camera())),
    ("pan", lambda: drag(QtCore.Qt.Key_Space)),
    ("after", lambda: L("camera after space-pan=" + camera() + " (muss sich unterscheiden)")),
    ("open", lambda: QtCore.QTimer.singleShot(1500, lambda: close_settings())
                     or Gui.runCommand("MyCAD_Settings")),
    ("restore", lambda: grp.SetString("MouseKeys", old)),
])
