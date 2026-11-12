# SPDX-License-Identifier: LGPL-2.1-or-later
"""Shift = mittlere Maustaste stört beim Umbenennen nicht (Kamera bleibt); Namen unter den Symbolen ein-/ausblenden."""
import os
from harness import *

grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")
old = grp.GetString("MouseKeys", "[]")
old_names = grp.GetBool("ToolNames", False)


def camera():
    d = Gui.ActiveDocument.ActiveView.getViewDirection()
    cam = Gui.ActiveDocument.ActiveView.getCamera()
    return "dir=(%.2f, %.2f, %.2f) %s" % (d.x, d.y, d.z, [l.strip() for l in cam.splitlines() if "position" in l][0])


def tree():
    return [w for w in visible(QtWidgets.QTreeWidget)][0]


def rename_with_shift():
    t = tree()
    item = t.topLevelItem(0)
    t.editItem(item)
    edit = QtWidgets.QApplication.focusWidget()
    L("  editing in %s" % (type(edit).__name__ if edit else None))
    win = mw.windowHandle(); vp = view().viewport()
    c = vp.mapTo(mw, vp.rect().center())
    QtTest.QTest.mouseMove(win, c)
    QtTest.QTest.keyPress(win, QtCore.Qt.Key_Shift)
    for i in range(1, 8):
        QtTest.QTest.mouseMove(win, c + QtCore.QPoint(15 * i, 8 * i))
    QtTest.QTest.keyRelease(win, QtCore.Qt.Key_Shift)
    QtTest.QTest.keyClick(edit or t, QtCore.Qt.Key_Escape)


def toggle_names():
    def flip():
        d = [w for w in visible(QtWidgets.QDialog) if w.windowTitle() == "Settings"][0]
        row = [w for w in d.findChildren(QtWidgets.QLabel) if w.text() == "Show tool names"][0].parentWidget()
        # Schalter rechts in der Zeile, wie ein echter Mausklick über das Dialogfenster
        pos = row.mapTo(d, QtCore.QPoint(row.width() - 22, row.height() // 2))
        QtTest.QTest.mouseClick(d.windowHandle(), QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, pos)
        L("  tool names param=%s" % grp.GetBool("ToolNames"))
        d.accept()
    QtCore.QTimer.singleShot(800, flip)
    Gui.runCommand("MyCAD_Settings")


bar_h = []


def bar_ok(tag):
    """Toolbar nach dem Umschalten: keine Knöpfe/Beschriftungen übereinander, alles in der Toolbar, aus = wieder so hoch wie
    am Anfang (früher blieben die Abschnitte mit alten Größen stehen: "Open" über "Save", 3 Reihen auf hoher Glasfläche)"""
    bar = button("Std_New").parentWidget().parentWidget().parentWidget()
    items = [w for w in bar.findChildren(QtWidgets.QWidget) if w.isVisible()
             and (w.objectName() == "GlassButton" or isinstance(w, QtWidgets.QLabel))]
    rects = [(w, QtCore.QRect(w.mapTo(bar, QtCore.QPoint(0, 0)), w.size())) for w in items]
    bad = ["%s/%s" % (a.text().replace(chr(10), " "), b.text().replace(chr(10), " ")) for i, (a, ra) in enumerate(rects)
           for b, rb in rects[i + 1:] if ra.intersects(rb)]
    out = [w.text() for w, r in rects if not bar.rect().contains(r)]
    head = bar.parentWidget()
    L("  %s: bar %dx%d header %dx%d names=%s" % (tag, bar.width(), bar.height(), head.width(), head.height(), grp.GetBool("ToolNames")))
    check("%s no overlap" % tag, not bad, str(bad[:5]))
    check("%s inside bar" % tag, not out, str(out[:5]))
    check("%s header fits bar" % tag, head.height() - bar.height() <= 16, "%d vs %d" % (head.height(), bar.height()))
    if not grp.GetBool("ToolNames"):
        bar_h.append(bar.height())
        check("%s off = start height" % tag, bar_h[-1] == bar_h[0], str(bar_h))


run([
    ("setup", lambda: make_body(rect(0, 0, 60, 40), 0, 15, "Box")),
    ("map shift", lambda: grp.SetString("MouseKeys", '[{"key":%d,"button":"middle","mode":"hold"}]' % int(QtCore.Qt.Key_Shift))),
    ("before", lambda: L("before   %s" % camera())),
    ("rename", rename_with_shift),
    ("after", lambda: L("umbenennen mit Shift: %s (muss gleich bleiben)" % camera())),
    ("restore keys", lambda: grp.SetString("MouseKeys", old)),
    ("shot plain", lambda: (L("  names at start=%s" % grp.GetBool("ToolNames")), shot("plain"))),
    ("check plain", lambda: bar_ok("start")),
    ("names on", toggle_names), ("wait", lambda: None),
    ("shot names", lambda: (shot("names"), bar_ok("on1"))),
    ("names off", toggle_names), ("wait2", lambda: None), ("check off1", lambda: (shot("off1"), bar_ok("off1"))),
    ("names on2", toggle_names), ("wait3", lambda: None), ("check on2", lambda: bar_ok("on2")),
    ("names off2", toggle_names), ("wait4", lambda: None), ("check off2", lambda: (shot("off2"), bar_ok("off2"))),
    ("names on3", toggle_names), ("wait5", lambda: None),
    ("sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick XY", lambda: Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XY_Plane")][0])),
    ("shot sketch", lambda: shot("sketchnames")),
    ("names back", lambda: grp.SetBool("ToolNames", old_names)),  # Einstellung des Benutzers nicht verändert lassen
])
