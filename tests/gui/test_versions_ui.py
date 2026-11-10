# SPDX-License-Identifier: LGPL-2.1-or-later
"""10.7 Idee 7 in der Oberfläche: ein neues Design ist nach einer Aktion von selbst gespeichert (eigener Ordner im
Projektordner, Version dazu); Version sichern gibt einen Namen; Versionen vergleichen zeigt das Geisterbild mit
geändertem Schritt; Variante anlegen wechselt dorthin; Schließen fragt nicht und verliert nichts"""
import os
import sys
from harness import *
import harness

sys.path.append(os.path.join(os.path.dirname(harness.__file__), "..", "design"))
import design  # noqa: E402
import DesignVersions  # noqa: E402

state = {}
wait = ("wait", lambda: None)


def setup():
    state["f"], state["b"] = design.box(doc(), 10, 10, 10)


def answer_input(text):
    """den nächsten Eingabedialog ausfüllen und bestätigen"""
    def fill():
        dialogs = [w for w in QtWidgets.QApplication.topLevelWidgets() if isinstance(w, QtWidgets.QInputDialog) and w.isVisible()]
        if dialogs:
            dialogs[0].setTextValue(text)
            dialogs[0].accept()
        else:
            QtCore.QTimer.singleShot(200, fill)
    QtCore.QTimer.singleShot(300, fill)


def in_versions_dialog(action):
    """Versionen öffnen und action(dialog) darin ausführen"""
    def go():
        dialogs = [w for w in QtWidgets.QApplication.topLevelWidgets() if isinstance(w, QtWidgets.QDialog)
                   and w.isVisible() and w.windowTitle() == "Versions"]
        if not dialogs:
            QtCore.QTimer.singleShot(200, go)
            return
        state["dialog_rows"] = [l.count() for l in dialogs[0].findChildren(QtWidgets.QListWidget)]
        action(dialogs[0])
    QtCore.QTimer.singleShot(500, go)
    Gui.runCommand("Design_Versions")


def compare_oldest(dlg):
    versions = [l for l in dlg.findChildren(QtWidgets.QListWidget) if l.accessibleName() == "Versions"][0]
    versions.setCurrentRow(versions.count() - 1)
    [b for b in dlg.findChildren(QtWidgets.QPushButton) if b.text() == "Compare"][0].click()


def new_variant(dlg):
    answer_input("Taller")
    [b for b in dlg.findChildren(QtWidgets.QPushButton) if b.text() == "New Variant…"][0].click()


def taller():
    state["f"].Distance = 20
    doc().recompute()


def save_as(name):
    """Speichern unter: Dateidialog wie beim Benutzer, direkt in den Projektordner"""
    state["before"] = doc().FileName
    folder = os.path.dirname(os.path.dirname(doc().FileName))

    def pick():
        dialogs = visible(QtWidgets.QFileDialog)
        if not dialogs:
            QtCore.QTimer.singleShot(200, pick)
            return
        [e for e in dialogs[0].findChildren(QtWidgets.QLineEdit) if e.isVisible()][0].setText(os.path.join(folder, name))
        dialogs[0].accept()
    QtCore.QTimer.singleShot(500, pick)
    Gui.runCommand("Std_SaveAs")


def browser_variant(title):
    """Rechtsklick auf das Design im Browser, Varianten ▸ title"""
    tree = [t for t in visible(QtWidgets.QTreeWidget)][0]
    pos = tree.visualItemRect(tree.topLevelItem(0)).center()

    def pick():
        menus = [m for m in QtWidgets.QApplication.topLevelWidgets() if isinstance(m, QtWidgets.QMenu) and m.isVisible()]
        if not menus:
            QtCore.QTimer.singleShot(200, pick)
            return
        variants = [a for a in menus[0].actions() if a.text() == "Variants"][0].menu()
        state["variant_menu"] = [a.text() for a in variants.actions() if a.text()]
        [a for a in variants.actions() if a.text() == title][0].trigger()
        menus[0].close()
    QtCore.QTimer.singleShot(300, pick)
    QtTest.QTest.mouseRelease(tree.viewport(), QtCore.Qt.RightButton, QtCore.Qt.NoModifier, pos)


def comparison_text():
    return [l.text() for l in visible(QtWidgets.QLabel) if l.parentWidget() and l.parentWidget().objectName() == "Comparison"]


def close_quickly():
    d = doc()
    ext = [o for o in d.Objects if o.TypeId == "Design::Extrude"][0]
    ext.Distance = 33
    d.recompute()
    state["closed"] = d.FileName
    Gui.runCommand("Std_CloseActiveWindow")  # sofort, vor dem Speichern nach 2 s


in_order([
    ("activate", activate),
    ("setup", setup), wait, wait, wait,
    ("saved", lambda: check("a new design saves itself into its own folder", doc().FileName.endswith(".mycad")
                            and os.path.basename(os.path.dirname(doc().FileName)) == os.path.splitext(os.path.basename(doc().FileName))[0],
                            doc().FileName)),
    ("not modified", lambda: check("and is no longer marked as changed", not Gui.ActiveDocument.Modified)),
    ("version", lambda: check("with a first version", len(DesignVersions.versions(doc().FileName)) >= 1)),
    ("change", taller), wait, wait, wait,
    ("second", lambda: check("each change becomes a version", len(DesignVersions.versions(doc().FileName)) >= 2,
                             str(len(DesignVersions.versions(doc().FileName))))),
    ("name it", lambda: (answer_input("Before holes"), Gui.runCommand("MyCAD_SaveVersion"))), wait,
    ("named", lambda: check("save version stores a named version",
                            any(v["title"] == "Before holes" for v in DesignVersions.versions(doc().FileName)))),
    ("save as", lambda: save_as("Renamed")), wait, wait,
    ("renamed", lambda: check("save as moves the design out of its first folder",
                              os.path.basename(doc().FileName) == "Renamed.mycad" and not os.path.exists(os.path.dirname(state["before"])),
                              "%s, old folder exists=%s" % (doc().FileName, os.path.exists(os.path.dirname(state["before"]))))),
    ("history", lambda: check("and takes its versions along",
                              any(v["title"] == "Before holes" for v in DesignVersions.versions(doc().FileName)))),
    ("compare", lambda: in_versions_dialog(compare_oldest)), wait, wait,
    ("rows", lambda: check("the window lists the versions", state.get("dialog_rows", [0])[0] >= 3, str(state.get("dialog_rows")))),
    ("ghost", lambda: check("compare shows what changed", any("Changed step" in t for t in comparison_text()), str(comparison_text()))),
    ("shot", lambda: shot("compare")),
    ("close compare", lambda: [b for b in visible(QtWidgets.QPushButton) if b.text() == "Close"][0].click()), wait,
    ("variant", lambda: in_versions_dialog(new_variant)), wait, wait,
    ("in variant", lambda: check("a new variant opens", DesignVersions.is_variant(doc().FileName), doc().FileName)),
    ("browser", lambda: browser_variant("Main design")), wait, wait,
    ("menu", lambda: check("the browser lists main design and variant", state.get("variant_menu", [])[:2] == ["Main design", "Taller"],
                           str(state.get("variant_menu")))),
    ("main again", lambda: check("and switches back to the main design", not DesignVersions.is_variant(doc().FileName), doc().FileName)),
    ("close", close_quickly), wait,
    ("no question", lambda: check("closing does not ask", QtWidgets.QApplication.activeModalWidget() is None)),
    ("reopen", lambda: App.openDocument(state["closed"])), wait,
    ("kept", lambda: check("the last change was saved on close",
                           abs([o for o in doc().Objects if o.TypeId == "Design::Extrude"][0].Distance.Value - 33) < 1e-9)),
])
