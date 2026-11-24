# SPDX-License-Identifier: LGPL-2.1-or-later
"""Umbenennen im Browser mit Shift als mittlerer Maustaste: Großbuchstaben tippen darf das
Feld nicht schließen (Feld liegt im Glass-Panel, Qt meldet die 3D-Ansicht als Fokus). Erwartet: der Körper heißt
"kneu" (QTest liefert auch mit Shift den Text 'k')"""
from harness import *

grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")


def tree():
    return visible(QtWidgets.QTreeWidget)[0]


def open_editor():
    """wie Rechtsklick → Rename (Shell: tree->editItem). Über das Menü war der Test wackelig: ein simuliertes Menü
    öffnete das Feld mal, mal nicht; geprüft wird hier das Tippen, nicht das Menü"""
    t = tree(); t.expandAll()
    t.editItem(t.findItems("Box", QtCore.Qt.MatchRecursive)[0])


def old_name_hidden():
    """unter dem halbdurchsichtigen Feld darf weder der alte Name noch die Akzent-Auswahl liegen (sonst stand
    "Box" weiß auf Blau hinter dem neuen Text): Feld kurz ausblenden, die Fläche darunter ist einfarbig"""
    t = tree()
    ed = t.indexWidget(t.indexFromItem(t.findItems("Box", QtCore.Qt.MatchRecursive)[0]))
    ed.hide(); img = t.viewport().grab(ed.geometry()).toImage(); ed.show()
    img.save(os.environ["OUT"] + ".under-field.png")
    colors = {img.pixel(x, y) for x in range(img.width()) for y in range(img.height())}
    check("nothing painted under the rename field", len(colors) <= 2, "%d colors" % len(colors))


def field_usable():
    """Feld zeigt den ganzen Namen schon beim Öffnen, ein Klick setzt den Cursor statt alles auszuwählen: man kann
    den Namen ändern, statt ihn neu zu schreiben (vorher 34 px schmal, "ox" sichtbar, Klick wählte alles)"""
    t = tree()
    ed = t.indexWidget(t.indexFromItem(t.findItems("Box", QtCore.Qt.MatchRecursive)[0]))
    check("rename field fits the name when it opens",
          ed.width() >= ed.fontMetrics().horizontalAdvance(ed.text()) + 20, "%d px" % ed.width())
    QtTest.QTest.mouseClick(ed, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, QtCore.QPoint(ed.width() - 6, ed.height() // 2))
    check("a click in the rename field places the cursor", ed.selectedText() == "", repr(ed.selectedText()))
    ed.selectAll()  # wie beim Öffnen, für den Schritt "type"


def type_name():
    win = mw.windowHandle()
    vp = view().viewport(); QtTest.QTest.mouseMove(vp, vp.rect().center())  # Zeiger über dem 3D-Fenster
    QtTest.QTest.keyClick(win, QtCore.Qt.Key_A, QtCore.Qt.ControlModifier)
    QtTest.QTest.keyPress(win, QtCore.Qt.Key_Shift)
    QtTest.QTest.keyClick(win, QtCore.Qt.Key_K, QtCore.Qt.ShiftModifier)
    QtTest.QTest.keyRelease(win, QtCore.Qt.Key_Shift)
    for k in (QtCore.Qt.Key_N, QtCore.Qt.Key_E, QtCore.Qt.Key_U):
        QtTest.QTest.keyClick(win, k)


run([
    ("setup", lambda: make_body(rect(0, 0, 60, 40), 0, 15, "Box")),
    ("shift = middle", lambda: grp.SetString("MouseKeys", '[{"key":%d,"button":"middle","mode":"hold"}]' % int(QtCore.Qt.Key_Shift))),
    ("activate", activate), ("select", lambda: Gui.Selection.addSelection(doc().getObjectsByLabel("Box")[0])),
    ("rename", open_editor), ("wait", lambda: None), ("under field", old_name_hidden), ("shot", lambda: shot("editing")), ("click", field_usable),
    ("type", type_name),
    ("enter", lambda: QtTest.QTest.keyClick(mw.windowHandle(), QtCore.Qt.Key_Return)),
    ("result", lambda: check("capitals typed with shift (= middle mouse button) rename the body",
                             [b.Label for b in doc().Objects if b.TypeId == "Design::Body"] == ["kneu"],
                             str([b.Label for b in doc().Objects if b.TypeId == "Design::Body"]))),
    ("keys off", lambda: grp.SetString("MouseKeys", "[]")),
])
