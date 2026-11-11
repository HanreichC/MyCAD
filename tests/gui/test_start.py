# SPDX-License-Identifier: LGPL-2.1-or-later
"""Startseite: beim Start ohne Design sichtbar; "New Design" (Seitenleiste) öffnet ein Design; gespeichert und geschlossen erscheint
es unter Recent und Projects (mit Vorschaubild, im eigenen Ordner Bracket/Bracket.mycad, ohne .FCBak-Sicherung; ein
altes Legacy.FCStd im Projektordner erscheint auch); Kachel öffnet es wieder; Home zeigt die Seite, "Back" schließt sie.
Rechtsklick auf eine Kachel benennt ein Design um oder löscht es.
Projektordner für den Test im Ausgabeordner, danach wieder der des Benutzers."""
import os
import re
import shutil
import zipfile
import harness
from harness import *

harness.START_PAGE = True
grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")
old_folder = grp.GetString("ProjectsFolder", "")
FOLDER = os.environ["OUT"] + ".projects"
FILE = os.path.join(FOLDER, "Bracket", "Bracket.mycad")  # Speichern direkt in den Projektordner legt den Projektordner Bracket an
shutil.rmtree(FOLDER, ignore_errors=True)
os.makedirs(FOLDER)
grp.SetString("ProjectsFolder", FOLDER)


def page():
    return [w for w in mw.findChildren(QtWidgets.QWidget, "StartPage")][0]


def tiles():
    return [w for w in page().findChildren(QtWidgets.QWidget, "StartTile") if w.isVisible()]


def tile_names():
    return [[l.text() for l in t.findChildren(QtWidgets.QLabel, "StartName")][0] for t in tiles()]


def report(tag):
    L("%s: start page visible=%s designs=%s tiles=%s" % (tag, page().isVisible(), sorted(App.listDocuments()),
                                                         tile_names() if page().isVisible() else "-"))


def real_click(w):
    win = mw.windowHandle(); p = w.mapTo(mw, w.rect().center())
    QtTest.QTest.mouseMove(win, p)
    QtTest.QTest.mouseClick(win, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)


def tile(name, n=0):
    return [t for t in tiles() if [l.text() for l in t.findChildren(QtWidgets.QLabel, "StartName")][0] == name][n]


def save():
    make_body(rect(0, 0, 40, 30) + [Part.Circle(App.Vector(20, 15, 0), App.Vector(0, 0, 1), 8)], 0, 12, "Bracket")
    Gui.ActiveDocument.ActiveView.viewIsometric(); Gui.SendMsgToActiveView("ViewFit")


def store():
    def pick():
        d = visible(QtWidgets.QFileDialog)[0]
        [e for e in d.findChildren(QtWidgets.QLineEdit) if e.isVisible()][0].setText(os.path.join(FOLDER, "Bracket"))  # ohne Endung
        d.accept()
    QtCore.QTimer.singleShot(800, pick)
    Gui.runCommand("Std_SaveAs")  # Dialog wie beim Benutzer, Vorschaubild vom Gui-Dokument
    Gui.ActiveDocument.Document.save()  # zweites Speichern: früher entstand hier die .FCBak
    L("folder: %s, project folder: %s (only Bracket.mycad expected)" % (sorted(os.listdir(FOLDER)),
                                                                     sorted(os.listdir(os.path.dirname(FILE)))))
    with zipfile.ZipFile(FILE) as z:
        L("saved %s, thumbnail in file=%s" % (os.path.basename(FILE), "thumbnails/Thumbnail.png" in z.namelist()))
    shutil.copy(FILE, os.path.join(FOLDER, "Legacy.FCStd"))  # Design aus der Zeit vor .mycad


def recent_names():
    box = [l for l in page().findChildren(QtWidgets.QLabel) if l.text() == "Recent"][0].parentWidget()
    return [[l.text() for l in t.findChildren(QtWidgets.QLabel, "StartName")][0] for t in box.findChildren(QtWidgets.QWidget, "StartTile")]


def tile_menu(name, entry, answer):
    """Echter Rechtsklick auf die Kachel, echter Klick auf den Menüpunkt; answer füllt danach den Dialog aus"""
    def pick():
        QtCore.QTimer.singleShot(700, answer)  # vorher einplanen: der Dialog blockiert modal
        m = visible(QtWidgets.QMenu)[0]
        # das Menü öffnet beim Drücken; wie bei echter Maus geht das Loslassen an das Menü (dort noch ohne Wirkung)
        QtTest.QTest.mouseRelease(m.windowHandle(), QtCore.Qt.RightButton, QtCore.Qt.NoModifier, QtCore.QPoint(-5, -5))
        L("  menu=%s" % [a.text() for a in m.actions() if a.text()])
        r = m.actionGeometry([a for a in m.actions() if a.text() == entry][0])
        QtTest.QTest.mouseMove(m.windowHandle(), r.center())
        QtTest.QTest.mouseClick(m.windowHandle(), QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, r.center())
    QtCore.QTimer.singleShot(800, pick)
    win, p = mw.windowHandle(), tile(name).mapTo(mw, tile(name).rect().center())
    QtTest.QTest.mouseMove(win, p)
    QtTest.QTest.mousePress(win, QtCore.Qt.RightButton, QtCore.Qt.NoModifier, p)  # kehrt erst nach dem Menü zurück


def rename_to(text):
    d = visible(QtWidgets.QInputDialog)[0]
    d.setTextValue(text); d.accept()


def confirm_delete():
    box = visible(QtWidgets.QMessageBox)[0]
    L("  question: %s" % box.text().replace("\n", " "))
    [b for b in box.buttons() if b.text() == "Delete"][0].click()


def save_version():
    QtCore.QTimer.singleShot(800, lambda: visible(QtWidgets.QInputDialog)[0].accept())
    Gui.runCommand("MyCAD_SaveVersion")


# in_order: jeder Schritt wartet, bis der vorige fertig ist (Kamera-Animation, Dateidialog, Materialvorschauen)
in_order([
    ("start", lambda: report("beim Start")),
    ("version", lambda: L("version shown=%s" % bool([l for l in page().findChildren(QtWidgets.QLabel, "Hint")
                                                    if re.search(r"MyCAD \d{4}\.\d\d\.\d\d · [0-9a-f]{7}", l.text())]))),
    ("shot empty", lambda: shot("empty")),
    ("new", lambda: real_click(page().findChild(QtWidgets.QPushButton, "Prominent"))), ("wait", lambda: None),
    ("after new", lambda: report("nach New Design")),
    ("body", save), ("save", store),
    # die Startseite baut ihre Kacheln nach dem Schließen auf (Vorschaubilder aus den Dateien): unter Last dauert das
    ("close", lambda: App.closeDocument(App.ActiveDocument.Name)), ("wait", lambda: None), ("wait", lambda: None), ("wait", lambda: None),
    ("closed", lambda: report("nach Schließen")), ("shot page", lambda: shot("page")),
    ("open tile", lambda: real_click(tile("Bracket"))), ("wait", lambda: None), ("wait", lambda: None),
    ("opened", lambda: report("nach Klick auf Kachel")),
    ("home", lambda: click([b for b in visible(QtWidgets.QToolButton) if b.toolTip() == "Home"][0])), ("wait", lambda: None),
    ("home shown", lambda: (report("Home"), L("  back button visible=%s" % [b for b in page().findChildren(QtWidgets.QToolButton) if b.toolTip() == "Back to Design"][0].isVisible()))),
    ("back", lambda: real_click([b for b in page().findChildren(QtWidgets.QToolButton) if b.toolTip() == "Back to Design"][0])), ("wait", lambda: None),
    ("after back", lambda: report("nach Back")),
    ("home2", lambda: click([b for b in visible(QtWidgets.QToolButton) if b.toolTip() == "Home"][0])), ("wait", lambda: None),
    ("search", lambda: QtTest.QTest.keyClicks(page().findChild(QtWidgets.QLineEdit, "StartSearch"), "xyz")),
    ("searched", lambda: report("Suche 'xyz' (keine Kachel)")),
    ("search2", lambda: (page().findChild(QtWidgets.QLineEdit, "StartSearch").setText("brack"), report("Suche 'brack'"))),
    ("shot home", lambda: shot("home")), ("back2", lambda: page().hide()),
    # ein neues Design, nur mit "Version sichern" (still in den Projektordner) gespeichert, steht auch unter Recent
    ("new2", lambda: Gui.runCommand("Std_New")), ("wait", lambda: None),
    ("body2", lambda: (setattr(App.ActiveDocument, "Label", "Clip"), make_body(rect(0, 0, 20, 20), 0, 5, "Clip"))),
    ("version", save_version),
    ("close2", lambda: App.closeDocument(App.ActiveDocument.Name)), ("wait", lambda: None),
    ("home3", lambda: click([b for b in visible(QtWidgets.QToolButton) if b.toolTip() == "Home"][0])), ("wait", lambda: None),
    ("recent", lambda: check("a design saved with Save Version is listed under Recent", "Clip" in recent_names(), str(recent_names()))),
    # Rechtsklick auf eine Kachel: umbenennen (Projektordner und Recent ziehen mit), dann löschen (Ordner in den Papierkorb)
    ("clear search", lambda: page().findChild(QtWidgets.QLineEdit, "StartSearch").clear()),
    ("rename", lambda: tile_menu("Bracket", "Rename…", lambda: rename_to("Holder"))), ("wait", lambda: None),
    ("renamed", lambda: check("rename moves the project folder and keeps the design under Recent",
                              os.path.isfile(os.path.join(FOLDER, "Holder", "Holder.mycad")) and not os.path.exists(os.path.dirname(FILE))
                              and "Holder" in recent_names() and "Holder" in tile_names() and "Bracket" not in tile_names(), str(tile_names()))),
    ("delete", lambda: tile_menu("Holder", "Delete…", confirm_delete)), ("wait", lambda: None),
    ("deleted", lambda: check("delete moves the project folder to the trash", not os.path.exists(os.path.join(FOLDER, "Holder")) and "Holder" not in tile_names(), str(tile_names()))),
    ("restore", lambda: grp.SetString("ProjectsFolder", old_folder) if old_folder else grp.RemString("ProjectsFolder")),
])
