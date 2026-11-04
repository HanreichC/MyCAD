# SPDX-License-Identifier: LGPL-2.1-or-later
"""Post-its: anlegen (auch in der Skizze), Rechenzeilen, Ziehen in eine Ecke, Schließen und wieder Öffnen per
Doppelklick im Browser, Tippen löst keine Skizzen-Kürzel aus, Esc und Klick in die Ansicht geben die Tastatur zurück,
Undo lässt den Text in Ruhe, Speichern und Laden. Fehler stehen als FAIL im Protokoll."""
import os
from harness import *
from harness import _pos


def notes():
    return [o for o in doc().Objects if o.TypeId == "Design::Note"]


def edits():
    return [e for e in visible(QtWidgets.QPlainTextEdit) if e.objectName() == "NoteText"]


def closers():
    return [b for b in visible(QtWidgets.QToolButton) if b.objectName() == "NoteClose"]


def keys(text):
    """wie echte Tasten: über das Fenster an den Fokus, Tastenkürzel werden dabei geprüft"""
    if QtWidgets.QApplication.focusWidget() is None:  # geht beim Skizzenstart verloren, wenn das Fenster nicht aktiv ist
        activate()
    for c in text:
        QtTest.QTest.keyClick(mw.windowHandle(), c)


def calculations():
    first = notes()[0]
    for typed, want in [("120 / 4 =", "120 / 4 = 30"), ("\r1,5 + 2 =", "1,5 + 2 = 3.5"), ("\rM8: 2 * 3 =", "M8: 2 * 3 = 6"),
                        ("\r10 mm + 1 in =", "10 mm + 1 in = 35.40 mm"), ("\rWidth / 4 =", "Width / 4 = 10.00 mm"),
                        ("\rSchraube =", "Schraube ="), ("\r6 * 7 =", "6 * 7 = 42"), (" + 1 =", "6 * 7 = 42 + 1 = 43")]:
        keys(typed)
        got = first.Text.split("\n")[-1]
        check("calc " + want, got == want, repr(got))


def add_parameter():
    s = doc().addObject("App::VarSet", "Parameters"); s.Label = "Parameters"
    s.addProperty("App::PropertyLength", "Width", "Parameters"); s.Width = "40 mm"
    [o for o in doc().Objects if o.TypeId == "App::Part"][0].addObject(s)


def drag_to_top_left():
    vp = view().viewport(); close = _pos(closers()[0])
    start = QtCore.QPoint(close.x() - 60, close.y()); target = QtCore.QPoint(400, 300)
    QtTest.QTest.mouseMove(vp, start)
    QtTest.QTest.mousePress(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, start)
    for k in range(1, 9):
        QtTest.QTest.mouseMove(vp, QtCore.QPoint(start.x() + (target.x() - start.x()) * k // 8, start.y() + (target.y() - start.y()) * k // 8))
    QtTest.QTest.mouseRelease(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, target)
    close = _pos(closers()[0])
    check("drag follows the mouse", abs(close.x() - 460) < 3 and abs(close.y() - 300) < 3, str(close))
    check("drag: stored for the top left corner", notes()[0].Corner == 0)


def keep_corner():
    """Fenster kleiner: oben links bleibt, wo es ist; ein Post-it unten rechts wandert mit der Ecke"""
    y = _pos(closers()[0]).y()
    mw.resize(mw.width(), mw.height() - 150)
    saved["y"] = y


def tree_item(tree, label):
    items = tree.findItems(label, QtCore.Qt.MatchExactly | QtCore.Qt.MatchRecursive)
    _keep_items.extend(items)
    return items[0]


_keep_items = []


def browser_tree():
    return [t for t in visible(QtWidgets.QTreeWidget)][0]


def dclick_in_browser():
    tree = browser_tree(); tree.expandAll()
    QtWidgets.QApplication.processEvents()
    item = tree_item(tree, notes()[0].Label)
    rect = tree.visualItemRect(item)
    top = tree
    while top.parentWidget():
        top = top.parentWidget()
    proxy = top.graphicsProxyWidget(); _keep_items.append(proxy)
    point = tree.viewport().mapTo(top, QtCore.QPoint(rect.left() + 50, rect.center().y()))
    p = view().mapFromScene(proxy.mapToScene(QtCore.QPointF(point)))
    vp = view().viewport()
    QtTest.QTest.mouseMove(vp, p)
    QtTest.QTest.mouseClick(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)
    QtTest.QTest.mouseDClick(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)
    QtTest.QTest.mouseRelease(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)


def in_sketch():
    return Gui.ActiveDocument.getInEdit() is not None


def reopen_file():
    path = os.environ["OUT"] + ".FCStd"
    doc().saveAs(path)
    App.closeDocument(doc().Name)
    App.openDocument(path)


saved = {}
wait = ("wait", lambda: None)

in_order([
    ("activate", activate),
    ("param", add_parameter),
    ("new note", lambda: click(button("Design_Note"))), wait,
    ("created", lambda: check("one note in folder Notes, panel shown", len(notes()) == 1 and "Notes" in [o.Name for o in notes()[0].InList] and len(edits()) == 1)),
    ("shot empty", lambda: shot("empty")),
    ("calc", calculations),
    ("modified", lambda: check("design counts as modified", Gui.ActiveDocument.Modified)),
    ("shot calc", lambda: shot("calc")),
    ("drag", drag_to_top_left), wait,
    ("smaller window", keep_corner), wait,
    ("corner kept", lambda: check("top left note ignores a smaller window", abs(_pos(closers()[0]).y() - saved["y"]) < 3)),
    ("shot dragged", lambda: shot("dragged")),
    ("window back", lambda: mw.resize(1500, 950)), wait,
    ("close", lambda: click(closers()[0])), wait,
    ("closed", lambda: check("closed but still in the design", edits() == [] and len(notes()) == 1 and not notes()[0].Visibility)),
    ("eye closed", lambda: check("browser eye shows it closed", not Gui.ActiveDocument.getObject(notes()[0].Name).isVisible())),
    ("reopen", dclick_in_browser), wait,
    ("reopened", lambda: check("double-click in browser reopens it with its text", len(edits()) == 1 and "= 30" in edits()[0].toPlainText())),
    ("eye open", lambda: check("browser eye shows it open", Gui.ActiveDocument.getObject(notes()[0].Name).isVisible())),
    ("sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick XY", lambda: Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XY_Plane")][0])), wait, wait,
    ("stays", lambda: check("note stays open in the sketch", in_sketch() and len(edits()) == 1)),
    ("button", lambda: check("note button enabled in the sketch", button("Design_Note").isEnabled())),
    ("second note", lambda: click(button("Design_Note"))), wait,
    ("two", lambda: check("second note from the sketch", len(notes()) == 2 and len(edits()) == 2 and in_sketch())),
    ("typing", lambda: keys("lgm")), wait,
    ("no shortcut", lambda: check("typing fills the new note, no sketch shortcut", notes()[1].Text == "lgm" and Gui.ActiveDocument.getInEdit().Object.GeometryCount == 0, repr(notes()[1].Text))),
    ("esc", lambda: (activate(), QtTest.QTest.keyClick(mw.windowHandle(), QtCore.Qt.Key_Escape))), wait,
    ("after esc", lambda: check("Esc in the note keeps the sketch open", in_sketch())),
    ("key after esc", lambda: keys("#")), wait,
    ("esc freed keys", lambda: check("after Esc keys no longer go to the note", notes()[1].Text == "lgm", repr(notes()[1].Text))),
    ("shot sketch", lambda: shot("sketch")),
    ("into note", lambda: click(edits()[0])),
    ("type in sketch", lambda: keys("7")), wait,
    ("typed", lambda: check("click into a note in the sketch, then type", "7" in notes()[0].Text + notes()[1].Text and in_sketch())),
    ("into view", lambda: view_click(0.5, 0.6)), wait,
    ("key after view", lambda: keys("#")), wait,
    ("view freed keys", lambda: check("click into the view frees the keys", "#" not in notes()[0].Text + notes()[1].Text)),
    ("finish", lambda: click(button("Sketcher_LeaveSketch"))), wait,
    ("left", lambda: check("notes stay open after the sketch", not in_sketch() and len(edits()) == 2)),
    ("timeline", lambda: check("notes are not on the timeline", not set(notes()) & set(doc().getObject("Root").Timeline))),
    ("text before undo", lambda: saved.update(text=notes()[0].Text)),
    ("undo", lambda: Gui.runCommand("Std_Undo")), wait,
    ("undo text", lambda: check("undo does not touch the note text", notes()[0].Text == saved["text"])),
    ("redo", lambda: Gui.runCommand("Std_Redo")), wait,
    ("save", reopen_file), wait, wait,
    ("loaded", lambda: check("after reload: text, corner, open state", len(notes()) == 2 and notes()[0].Corner == 0 and "= 30" in notes()[0].Text and len(edits()) == 2, "%d notes, %d open" % (len(notes()), len(edits())))),
    ("delete", lambda: doc().removeObject(notes()[1].Name)), wait,
    ("deleted", lambda: check("deleted note is gone", len(notes()) == 1 and len(edits()) == 1)),
    ("shot end", lambda: shot("end")),
])
