# SPDX-License-Identifier: LGPL-2.1-or-later
"""Design benennen: ein neues Design wird still als Unnamed/Unnamed.mycad gespeichert. Über dem Namen oben im Browser
zeigt sich ein Stift, ein Klick öffnet das Umbenennen; danach heißen Datei und Projektordner mit (vorher änderte sich
nur die Anzeige, beim nächsten Öffnen hieß es wieder "Unnamed"). Bilder <OUT>.hover.png, <OUT>.edit.png. Projektordner im Ausgabeordner."""
import os
import shutil
from harness import *

grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")
grp.SetBool("AlwaysSave", True)  # harness schaltet es aus
old_folder = grp.GetString("ProjectsFolder", "")
FOLDER = os.environ["OUT"] + ".projects"
shutil.rmtree(FOLDER, ignore_errors=True)
os.makedirs(FOLDER)
grp.SetString("ProjectsFolder", FOLDER)


def tree():
    return [w for w in visible(QtWidgets.QTreeWidget)][0]


def doc_item():
    t = tree()
    return [t.topLevelItem(i) for i in range(t.topLevelItemCount())][0]


def window_point():
    """Mitte des Designnamens im Fenster: der Baum liegt in einem Glas-Panel der 3D-Szene (wie test_docmenu)"""
    t = tree(); r = t.visualItemRect(doc_item())
    top = t
    while top.parentWidget():
        top = top.parentWidget()
    inner = t.viewport().mapTo(top, QtCore.QPoint(r.left() + 20, r.center().y()))
    return view().viewport().mapTo(mw, view().mapFromScene(top.graphicsProxyWidget().mapToScene(QtCore.QPointF(inner))))


def hover():
    QtTest.QTest.mouseMove(mw.windowHandle(), window_point())


def grab_hover():
    tree().viewport().update()
    QtWidgets.QApplication.processEvents()
    tree().viewport().grab().save(os.environ["OUT"] + ".hover.png")


def click():
    p = window_point()
    QtTest.QTest.mouseClick(mw.windowHandle(), QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)


def type_name():
    editor = next((e for e in tree().findChildren(QtWidgets.QLineEdit) if e.isVisible()), None)  # Editor im Baum
    check("a click on the design name opens the name for editing", isinstance(editor, QtWidgets.QLineEdit),
          type(editor).__name__)
    tree().viewport().grab().save(os.environ["OUT"] + ".edit.png")
    if isinstance(editor, QtWidgets.QLineEdit):
        editor.selectAll(); QtTest.QTest.keyClicks(editor, "Bracket"); QtTest.QTest.keyClick(editor, QtCore.Qt.Key_Return)


def renamed():
    d = App.ActiveDocument
    want = os.path.join(FOLDER, "Bracket", "Bracket.mycad")
    check("renaming in the browser renames the file and its project folder",
          os.path.isfile(want) and not os.path.exists(os.path.join(FOLDER, "Unnamed")) and d.FileName == want and d.Label == "Bracket",
          "files=%s FileName=%s Label=%s" % (sorted(os.listdir(FOLDER)), d.FileName, d.Label))


def restore():
    grp.SetBool("AlwaysSave", False)
    grp.SetString("ProjectsFolder", old_folder) if old_folder else grp.RemString("ProjectsFolder")


in_order([
    ("activate", activate),
    ("body", lambda: make_body(rect(0, 0, 20, 10), 0, 5, "Box")),
    ("wait", lambda: None), ("wait", lambda: None), ("wait", lambda: None),
    ("saved", lambda: check("a new design is saved quietly as Unnamed/Unnamed.mycad",
                            os.path.isfile(os.path.join(FOLDER, "Unnamed", "Unnamed.mycad")), str(os.listdir(FOLDER)))),
    ("hover", hover), ("grab", grab_hover),
    ("click", click), ("wait", lambda: None),
    ("type", type_name), ("wait", lambda: None), ("wait", lambda: None),
    ("renamed", renamed),
    ("restore", restore),
])
