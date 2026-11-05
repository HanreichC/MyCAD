# SPDX-License-Identifier: LGPL-2.1-or-later
"""README-Bilder neu erzeugen: docs/images/workspace.png, notes.png und start.png. Läuft in MyCAD, mit eigenem Home:
    MYCAD_HOME=/tmp/readme tests/gui/run.sh tools/readme_images.py /tmp/readme/log"""
import os
import sys

sys.path.insert(0, "/workspace/tests/gui")
from harness import *

IMAGES = "/workspace/docs/images/"
PROJECTS = os.path.join(os.environ["HOME"], "Documents/MyCAD")


def plate(name, width, depth, height, holes):
    """Platte mit Bohrungen: Skizze, Profil ohne die Kreise, Extrude; als eigenes Design gespeichert"""
    Gui.runCommand("Std_New")
    QtCore.QTimer.singleShot(1500, lambda: finish_plate(name, width, depth, height, holes))


def finish_plate(name, width, depth, height, holes):
    d = doc(); d.Label = name
    root = [o for o in d.Objects if o.TypeId == "App::Part"][0]
    sk = d.addObject("Sketcher::SketchObject", "Sketch")
    for g in rect(0, 0, width, depth):
        sk.addGeometry(g)
    for x, y, r in holes:
        sk.addGeometry(Part.Circle(App.Vector(x, y, 0), App.Vector(0, 0, 1), r))
    d.getObject("Sketches").addObject(sk)
    prof = d.addObject("Design::Profiles", "Profiles"); prof.Sketch = sk; root.addObject(prof)
    d.recompute()
    faces = prof.Shape.Faces
    biggest = max(range(len(faces)), key=lambda i: faces[i].Area)
    ext = d.addObject("Design::Extrude", "Extrude"); ext.Profile = (prof, ["Face%d" % (biggest + 1)]); ext.Distance = height; root.addObject(ext)
    b = d.addObject("Design::Body", "Body"); ext.Bodies = [b]; b.Tip = ext
    d.getObject("Bodies").addObject(b)
    sk.Visibility = False; prof.Visibility = False
    d.recompute()
    Gui.ActiveDocument.ActiveView.viewIsometric(); Gui.SendMsgToActiveView("ViewFit")
    QtCore.QTimer.singleShot(800, lambda: save(name))


def save(name):
    folder = os.path.join(PROJECTS, name)
    os.makedirs(folder, exist_ok=True)
    doc().saveAs(os.path.join(folder, name + ".mycad"))


def only_bracket():
    """Nur das Bracket offen lassen und alle drei unter Recent eintragen"""
    for name, document in list(App.listDocuments().items()):
        if document.Label != "Bracket":
            App.closeDocument(name)
    recent = App.ParamGet("User parameter:BaseApp/Preferences/RecentFiles")
    for i, name in enumerate(("Bracket", "Cover", "Flange")):
        recent.SetString("MRU%d" % i, os.path.join(PROJECTS, name, name + ".mycad"))


def add_note():
    activate()
    click(button("Design_Note"))


def type_note():
    """Echt getippt: die Ergebnisse rechnet MyCAD selbst aus"""
    note = [o for o in doc().Objects if o.TypeId == "Design::Note"][0]
    note.Label = "Bracket math"
    note.OffsetX = 56; note.OffsetY = 96
    for c in "Hole spacing: 80 - 2 * 22 =\rEdge to hole: (50 - 18) / 2 =\r12 mm + 0.25 in =\rM8 or M10? Check the washer.":
        QtTest.QTest.keyClick(mw.windowHandle(), c)
    QtTest.QTest.keyClick(mw.windowHandle(), QtCore.Qt.Key_Escape)
    L("note text: %r" % note.Text)


def show_note_in_browser():
    doc().recompute()  # Umbenennen gilt als Änderung: sonst trägt die Notiz im Browser das Abzeichen "veraltet"
    [o for o in doc().Objects if o.TypeId == "Design::Note"][0].purgeTouched()
    tree = visible(QtWidgets.QTreeWidget)[0]
    for label in ("Design", "Notes"):
        tree.findItems(label, QtCore.Qt.MatchExactly | QtCore.Qt.MatchRecursive)[0].setExpanded(True)


def clear_focus():
    widget = QtWidgets.QApplication.focusWidget()
    if widget:
        widget.clearFocus()


def picture(name):
    mw.grab().save(IMAGES + name + ".png")


def home():
    [b for b in visible(QtWidgets.QToolButton) if b.toolTip() == "Home"][0].click()


wait = ("wait", lambda: None)
in_order([
    ("size", lambda: (mw.showNormal(), mw.resize(1800, 1080))), wait,
    ("flange", lambda: plate("Flange", 60, 60, 8, [(30, 30, 14), (10, 10, 3), (50, 10, 3), (10, 50, 3), (50, 50, 3)])), wait, wait, wait,
    ("cover", lambda: plate("Cover", 120, 40, 4, [(15, 20, 4), (60, 20, 10), (105, 20, 4)])), wait, wait, wait,
    ("bracket", lambda: plate("Bracket", 80, 50, 12, [(22, 25, 9), (58, 25, 9)])), wait, wait, wait,
    ("only bracket", only_bracket), wait, wait,
    ("workspace", lambda: picture("workspace")),
    ("note", add_note), wait,
    ("type", type_note), wait,
    ("browser", show_note_in_browser), wait,
    ("notes", lambda: picture("notes")),
    ("home", home), wait, wait,
    ("focus", clear_focus), wait,
    ("start", lambda: picture("start")),
], delay=1500)
