# SPDX-License-Identifier: LGPL-2.1-or-later
"""README-Bilder neu erzeugen: docs/images/workspace.png, notes.png, scribble.png, scribble-3d.png, materials.png und start.png. Läuft in MyCAD, mit eigenem Home:
    MYCAD_HOME=/tmp/readme tests/gui/run.sh tools/readme_images.py /tmp/readme/log"""
import math
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


# Scribbles: Striche direkt in die Eigenschaften (wie sie die Werkzeuge speichern), damit das Bild genau so wird
INK, BLUE, RED, GREEN, YELLOW = (0x1D / 255, 0x1D / 255, 0x1F / 255), (0, 0x88 / 255, 1), (1, 0x38 / 255, 0x3C / 255), \
    (0x34 / 255, 0xC7 / 255, 0x59 / 255), (1, 0xCC / 255, 0)
PENCIL, PEN, MARKER = 0, 1, 2
FREE, LINE, CIRCLE, RECT, POLYGON, ELLIPSE, FILL = range(7)


def circle(cx, cy, r, n=96):
    return [(cx + r * math.cos(2 * math.pi * i / n), cy + r * math.sin(2 * math.pi * i / n)) for i in range(n + 1)]


def arrow(a, b, head=3.0):
    """wie das Pfeil-Werkzeug: Ende, Spitze, Flügel, Flügel, Spitze"""
    length = math.dist(a, b); ux, uy = (b[0] - a[0]) / length, (b[1] - a[1]) / length
    bx, by, w = b[0] - ux * head, b[1] - uy * head, head * 0.55
    return [a, b, (bx - uy * w, by + ux * w), (bx + uy * w, by - ux * w), b]


def wobble(points, amount=0.25):
    """Hand-Strich: leicht zittrig, aber gleichmäßig"""
    return [(x + amount * math.sin(i * 1.7), y + amount * math.cos(i * 1.3)) for i, (x, y) in enumerate(points)]


def draw(scribble, sheet, strokes):
    """strokes: (Punkte auf dem Blatt, Breite mm, Werkzeug, Form, Farbe)"""
    normal = sheet.Rotation.multVec(App.Vector(0, 0, 1))
    pts, widths, counts, tools, kinds, colors = [], [], [], [], [], []
    for points, width, tool, kind, color in strokes:
        pts += [sheet.multVec(App.Vector(x, y, 0)) for x, y in points]
        widths += [width] * len(points)
        counts.append(len(points)); tools.append(tool); kinds.append(kind)
        colors.append(tuple(float(c) for c in color) + ({PENCIL: 0.8, PEN: 1.0, MARKER: 0.35}[tool],))
    scribble.Sheet = sheet
    scribble.Points = pts; scribble.Widths = widths; scribble.Tools = tools; scribble.Kinds = kinds
    scribble.Colors = colors; scribble.Normals = [normal] * len(counts)
    scribble.Counts = counts  # zuletzt: erst dann passen alle Listen zusammen


def editing_scribble():
    return Gui.ActiveDocument.getInEdit().Object


def slot_idea():
    """Das Bracket von oben auf Papier skizziert (Bleistift), darüber die Ideen: Langloch, Rundungen, Kante"""
    [o for o in doc().Objects if o.TypeId == "Design::Note"][0].Visibility = False
    s = editing_scribble(); s.Label = "Slot idea"
    slot = [(30, 19), (50, 19), (50, 31), (30, 31), (30, 19)]
    draw(s, App.Placement(), [
        (wobble([(0, 0), (80, 0), (80, 50), (0, 50), (0, 0)], 0.05), 0.22, PENCIL, RECT, INK),
        (wobble(circle(22, 25, 9), 0.04), 0.22, PENCIL, FREE, INK),
        (wobble(circle(58, 25, 9), 0.04), 0.22, PENCIL, FREE, INK),
        (slot, 0, MARKER, FILL, BLUE),
        (slot, 0.3, PEN, RECT, INK),
        (circle(22, 25, 13), 0.3, PEN, CIRCLE, RED),
        (arrow((3, 46), (12.5, 34.5)), 0.3, PEN, POLYGON, INK),  # Pfeil auf das Loch
        (wobble([(80 - 10 + 10 * math.cos(t / 20 * math.pi / 2), 50 - 10 + 10 * math.sin(t / 20 * math.pi / 2)) for t in range(21)], 0.15), 0.35, PEN, FREE, GREEN),
        (wobble([(80 - 10 + 10 * math.cos(t / 20 * math.pi / 2), 10 - 10 * math.sin(t / 20 * math.pi / 2)) for t in range(21)], 0.15), 0.35, PEN, FREE, GREEN),
        (wobble([(x, 50) for x in range(4, 70, 3)], 0.1), 1.6, MARKER, FREE, YELLOW),
        ([(30, 36), (50, 36)], 0.25, PENCIL, LINE, INK),  # Maß über dem Langloch
        ([(30, 34.5), (30, 37.5)], 0.25, PENCIL, LINE, INK),
        ([(50, 34.5), (50, 37.5)], 0.25, PENCIL, LINE, INK),
    ])
    v = Gui.ActiveDocument.ActiveView
    v.viewTop(); Gui.SendMsgToActiveView("ViewFit"); Gui.runCommand("Std_ViewZoomOut")


def wall_idea():
    """Zweites Blatt steht auf der Platte (Blatt umstellen): eine Wand mit Loch, im Raum gesehen"""
    [o for o in doc().Objects if o.Label == "Slot idea"][0].Visibility = False  # liegt unter der Platte
    s = editing_scribble(); s.Label = "Wall idea"
    wall = [(0, 0), (80, 0), (80, 28), (0, 28), (0, 0)]
    draw(s, App.Placement(App.Vector(0, 25, 12), App.Rotation(App.Vector(1, 0, 0), 90)), [
        (wall, 0, MARKER, FILL, GREEN),
        (wall, 0.35, PEN, RECT, INK),
        (circle(40, 15, 7), 0, MARKER, FILL, BLUE),
        (circle(40, 15, 7), 0.35, PEN, CIRCLE, INK),
    ])
    v = Gui.ActiveDocument.ActiveView
    v.viewIsometric(); Gui.SendMsgToActiveView("ViewFit"); Gui.runCommand("Std_ViewZoomOut")


def show_scribbles_in_browser():
    tree = visible(QtWidgets.QTreeWidget)[0]
    for label in ("Design", "Scribbles"):
        tree.findItems(label, QtCore.Qt.MatchExactly | QtCore.Qt.MatchRecursive)[0].setExpanded(True)


def clear_focus():
    widget = QtWidgets.QApplication.focusWidget()
    if widget:
        widget.clearFocus()


wait = ("wait", lambda: None)


def disc(x, y, r):
    return [Part.Circle(App.Vector(x, y, 0), App.Vector(0, 0, 1), r)]


# Körper und ihr Material (Name einer Kugel oder eines Chips im Panel "Darstellung")
MATERIALS = [("Tray", rect(0, 0, 70, 45), 18, "Walnut, Oiled"), ("Knob", disc(100, 22, 16), 30, "Anodized Blue"),
             ("Cap", disc(140, 22, 14), 22, "Lacquer Red"), ("Plate", rect(165, 0, 215, 45), 6, "Carbon Fiber"),
             ("Lens", disc(100, 72, 18), 12, "Clear Glass"), ("Block", rect(125, 55, 165, 85), 25, "Brushed Aluminum"),
             ("Print", disc(30, 78, 15), 35, "PLA Orange")]


def materials_design():
    Gui.runCommand("Std_New")
    QtCore.QTimer.singleShot(1500, lambda: [make_body(geo, 0, h, name) for name, geo, h, _ in MATERIALS])


def accept():
    """OK im Panel (direkt statt per Mausklick: der trifft bei dieser Fenstergröße nicht zuverlässig)"""
    [b for b in visible(QtWidgets.QPushButton) if b.text().replace("&", "") == "OK"][0].click()


def paint(name, material):
    """wie von Hand: Körper wählen, Darstellung öffnen, Material anklicken, OK (je ein Schritt)"""
    def open_panel():
        Gui.Selection.clearSelection(); Gui.Selection.addSelection(body(name))
        Gui.runCommand("Design_Appearance")
    return [(name, open_panel), wait,
            (material, lambda: [b for b in visible(QtWidgets.QToolButton) if b.accessibleName() == material][0].click()),
            ("ok", accept), wait]


def materials_view():
    v = Gui.ActiveDocument.ActiveView
    v.viewIsometric(); Gui.SendMsgToActiveView("ViewFit")
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(body("Tray"))
    Gui.runCommand("Design_Appearance")


def picture(name):
    mw.grab().save(IMAGES + name + ".png")


def home():
    [b for b in visible(QtWidgets.QToolButton) if b.toolTip() == "Home"][0].click()


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
    ("scribble", lambda: Gui.runCommand("Design_Scribble")), wait,
    ("slot idea", slot_idea), wait,
    ("scribble browser", show_scribbles_in_browser), wait,
    ("scribble picture", lambda: picture("scribble")),
    ("finish slot", lambda: Gui.runCommand("Design_ScribbleFinish")), wait,
    ("scribble 2", lambda: Gui.runCommand("Design_Scribble")), wait,
    ("wall idea", wall_idea), wait, wait,
    ("scribble 3d", lambda: picture("scribble-3d")),
    ("finish wall", lambda: Gui.runCommand("Design_ScribbleFinish")), wait,
    ("materials design", materials_design), wait, wait,
    *[s for name, _, _, material in MATERIALS for s in paint(name, material)],
    ("materials view", materials_view), wait, wait,
    ("materials", lambda: picture("materials")),
    ("close panel", accept), wait,
    ("home", home), wait, wait,
    ("focus", clear_focus), wait,
    ("start", lambda: picture("start")),
], delay=1500)
