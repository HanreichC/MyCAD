# SPDX-License-Identifier: LGPL-2.1-or-later
"""Startseite: beim Start ohne Design sichtbar; "New Design" (Seitenleiste) öffnet ein Design; gespeichert und geschlossen erscheint
es unter Recent und Projects (mit Vorschaubild); Kachel öffnet es wieder; Home zeigt die Seite, "Back" schließt sie.
Projektordner für den Test im Ausgabeordner, danach wieder der des Benutzers."""
import os
import zipfile
import harness
from harness import *

harness.START_PAGE = True
grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")
old_folder = grp.GetString("ProjectsFolder", "")
FOLDER = os.environ["OUT"] + ".projects"
FILE = os.path.join(FOLDER, "Bracket.FCStd")
os.makedirs(FOLDER, exist_ok=True)
for f in os.listdir(FOLDER):
    os.remove(os.path.join(FOLDER, f))
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
    Gui.ActiveDocument.Document.saveAs(FILE)  # wie Std_Save mit Vorschaubild (Gui-Dokument)
    with zipfile.ZipFile(FILE) as z:
        L("saved %s, thumbnail in file=%s" % (os.path.basename(FILE), "thumbnails/Thumbnail.png" in z.namelist()))


run([
    ("start", lambda: report("beim Start")), ("shot empty", lambda: shot("empty")),
    ("new", lambda: real_click(page().findChild(QtWidgets.QPushButton, "Prominent"))), ("wait", lambda: None),
    ("after new", lambda: report("nach New Design")),
    ("body", save), ("save", store),
    ("close", lambda: App.closeDocument(App.ActiveDocument.Name)), ("wait", lambda: None),
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
    ("restore", lambda: grp.SetString("ProjectsFolder", old_folder) if old_folder else grp.RemString("ProjectsFolder")),
])
