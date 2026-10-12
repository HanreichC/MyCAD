# SPDX-License-Identifier: LGPL-2.1-or-later
"""Tasten als Maustasten wie im echten Gebrauch: Shift = mittlere Maustaste (halten), Tastendruck geht an das
fokussierte Widget (z. B. den Browser), Maus nur bewegt (Trackpad) -> Ansicht wird verschoben."""
from harness import *

grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")
old = grp.GetString("MouseKeys", "[]")


def camera():
    d = Gui.ActiveDocument.ActiveView.getViewDirection()
    cam = Gui.ActiveDocument.ActiveView.getCamera()
    pos = [l.strip() for l in cam.splitlines() if l.strip().startswith("position")][0]
    return "dir=(%.2f, %.2f, %.2f) %s" % (d.x, d.y, d.z, pos)


def drag(key, target):
    vp = view().viewport(); c = vp.rect().center()
    for i in range(3):
        QtTest.QTest.mouseMove(vp, c + QtCore.QPoint(i, 0))
    QtTest.QTest.keyPress(target, key)
    for i in range(1, 11):
        QtTest.QTest.mouseMove(vp, c + QtCore.QPoint(15 * i, 8 * i))
    QtTest.QTest.keyRelease(target, key)


def tree():
    return [w for w in visible(QtWidgets.QTreeWidget)][0]


def drag_window(key):
    # wie echte Eingabe: über das Fenster (QWindow), Qt stellt an das Widget unter dem Zeiger zu
    win = mw.windowHandle(); vp = view().viewport()
    c = vp.mapTo(mw, vp.rect().center())
    for i in range(3):
        QtTest.QTest.mouseMove(win, c + QtCore.QPoint(i, 0))
    QtTest.QTest.keyPress(win, key)
    for i in range(1, 11):
        QtTest.QTest.mouseMove(win, c + QtCore.QPoint(15 * i, 8 * i))
    QtTest.QTest.keyRelease(win, key)


run([
    ("setup", lambda: make_body(rect(0, 0, 60, 40), 0, 15, "Box")),
    ("map", lambda: grp.SetString("MouseKeys", '[{"key":%d,"button":"middle","mode":"hold"}]' % int(QtCore.Qt.Key_Shift))),
    ("focus tree", lambda: tree().setFocus()),
    ("before", lambda: L("before=%s focus=%s" % (camera(), QtWidgets.QApplication.focusWidget()))),
    ("shift pan", lambda: drag(QtCore.Qt.Key_Shift, QtWidgets.QApplication.focusWidget() or tree())),
    ("after", lambda: L("after shift=%s" % camera())),
    ("window path", lambda: drag_window(QtCore.Qt.Key_Shift)),
    ("after2", lambda: L("after shift (window path)=%s  (Fusion: Shift+Mitte = drehen, Richtung ändert sich)" % camera())),
    ("space", lambda: grp.SetString("MouseKeys", '[{"key":%d,"button":"middle","mode":"hold"}]' % int(QtCore.Qt.Key_Space))),
    ("window space", lambda: drag_window(QtCore.Qt.Key_Space)),
    ("after3", lambda: L("after space (window path)=%s  (Mitte = schieben, Richtung bleibt)" % camera())),
    ("restore", lambda: grp.SetString("MouseKeys", old)),
])
