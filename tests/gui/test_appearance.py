# SPDX-License-Identifier: LGPL-2.1-or-later
"""Appearance-Panel: Kugel anklicken, Chip (Variante) anklicken, Farbfeld; Suche filtert; Favoriten und "In diesem Design"
stehen oben; mit gewählter Fläche färbt es nur diese Fläche; Material auf einen Körper ziehen; Undo stellt alles wieder
her. Fehler stehen als FAIL im Protokoll."""
from PySide6 import QtGui
from harness import *

P = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")
favs = P.GetString("MaterialFavorites", "")
state = {}


def appearance(name):
    return Gui.ActiveDocument.getObject(body(name).Name).ShapeAppearance


def color(name="Box"):
    return tuple(round(x, 2) for x in appearance(name)[0].DiffuseColor[:3])


def tile(name):
    [b for b in visible(QtWidgets.QToolButton) if b.accessibleName() == name][0].click()


def sections():
    return [l.text() for l in visible(QtWidgets.QLabel) if l.objectName() == "Section"]


def swatch(hex_):
    [b.click() for b in visible(QtWidgets.QToolButton) if b.toolTip() == hex_]


def search(text):
    e = [e for e in visible(QtWidgets.QLineEdit) if e.placeholderText() == "Search materials"][0]
    e.setText(text)


def names():
    return {b.accessibleName() for b in visible(QtWidgets.QToolButton) if b.iconSize().width() == 56}


def open_panel(*select):
    Gui.Selection.clearSelection()
    for s in select:
        Gui.Selection.addSelection(*s) if isinstance(s, tuple) else Gui.Selection.addSelection(body(s))
    Gui.runCommand("Design_Appearance")


def drop(index, name):
    """Material wie per Ziehen auf die Mitte der Oberseite des Körpers fallen lassen"""
    b = body(name); bb = b.Shape.BoundBox
    px, py = Gui.ActiveDocument.ActiveView.getPointOnViewport(App.Vector(bb.Center.x, bb.Center.y, bb.ZMax))
    gv = Gui.ActiveDocument.ActiveView.graphicsView().viewport()
    local = QtCore.QPoint(int(px / gv.devicePixelRatioF()), int(gv.height() - py / gv.devicePixelRatioF()))
    viewport = QtWidgets.QApplication.widgetAt(gv.mapToGlobal(local))  # wie beim echten Ziehen: das Widget unter der Maus
    mime = QtCore.QMimeData(); mime.setData("application/x-mycad-material", str(index).encode())
    pos = QtCore.QPointF(viewport.mapFromGlobal(gv.mapToGlobal(local)))
    # Qt gibt das Ablegen nur dem Widget, das vorher das Hereinziehen angenommen hat
    enter = QtGui.QDragEnterEvent(pos.toPoint(), QtCore.Qt.CopyAction, mime, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier)
    QtWidgets.QApplication.sendEvent(viewport, enter)
    e = QtGui.QDropEvent(pos, QtCore.Qt.CopyAction, mime, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier)
    QtWidgets.QApplication.sendEvent(viewport, e)
    L("  drop on %s, accepted=%s" % (Gui.ActiveDocument.ActiveView.getObjectInfo((int(px), int(py)))["Object"], e.isAccepted()))


run([
    ("setup", lambda: (make_body(rect(0, 0, 40, 30), 0, 15, "Box"), make_body(rect(60, 0, 100, 30), 0, 15, "Other"),
                       P.SetString("MaterialFavorites", "51"))),  # Favorit: Pulver Schwarz (Index in bodyMaterials, Shell.cpp)
    ("open", lambda: open_panel("Box")),
    ("shot", lambda: shot("panel")),
    ("sections", lambda: (L("sections=%s" % sections()),
                          check("Favorites and the library groups are listed", {"Favorites", "Metal", "Wood"} <= set(sections())),
                          check("Old FreeCAD presets are gone", not [b for b in visible(QtWidgets.QPushButton) if b.text() in ("Jade", "Ruby", "Obsidian")]))),
    ("aluminum", lambda: (tile("Aluminum"), state.update(alu=color()), check("Sphere applies the material", state["alu"] == (0.82, 0.83, 0.84), str(state["alu"])))),
    ("chip", lambda: (tile("Anodized Red"), check("Chip applies its variant", color() == (0.69, 0.23, 0.23), str(color())))),
    ("search", lambda: search("walnut")),
    ("found", lambda: (state.update(found=names()), L("found=%s" % state["found"]),
                        check("Search shows only matching materials", state["found"] and all("Walnut" in n for n in state["found"]), str(state["found"])))),
    ("shot search", lambda: shot("search")),
    ("clear", lambda: search("")),
    ("blue", lambda: (swatch("#007AFF"), check("Color swatch", color() == (0.0, 0.48, 1.0), str(color())))),
    ("ok", ok),
    ("in design", lambda: open_panel("Box")),
    ("used", lambda: check("In this design lists the material of the body", "In this design" in sections(), str(sections()))),
    ("ok 2", ok),
    # Fläche: nur die gewählte Fläche bekommt das Material
    ("face", lambda: open_panel(("Unnamed", body("Box").Name, top_face(body("Box"))))),
    ("face red", lambda: tile("Lacquer Red")),
    ("face check", lambda: (state.update(faces=[tuple(round(c, 2) for c in m.DiffuseColor[:3]) for m in appearance("Box")]),
                            L("faces=%s" % state["faces"]),
                            check("Faces: only the selected face changes",
                                  len(state["faces"]) == len(body("Box").Shape.Faces) and state["faces"].count((0.69, 0.09, 0.12)) == 1,
                                  str(state["faces"])))),
    ("ok 3", ok),
    # Ziehen: ohne Auswahl, auf den zweiten Körper
    ("drag panel", lambda: open_panel()),
    ("fit", lambda: (Gui.ActiveDocument.ActiveView.viewIsometric(), Gui.SendMsgToActiveView("ViewFit"))),
    ("drop", lambda: drop(12, "Other")),  # Eiche
    ("drop check", lambda: check("Drag onto a body applies the material", appearance("Other")[0].ImagePath == ":/mycad/textures/oak.jpg"
                                 if hasattr(appearance("Other")[0], "ImagePath") else color("Other") == (0.63, 0.49, 0.34), str(color("Other")))),
    ("shot drop", lambda: shot("drop")),
    ("ok 4", ok),
    ("undo", lambda: [Gui.runCommand("Std_Undo") for _ in range(3)]),  # Ziehen, Fläche, erstes Panel (das zweite blieb leer)
    ("after undo", lambda: check("Undo restores the look", color() == (0.36, 0.38, 0.41), str(color()))),
    ("restore", lambda: P.SetString("MaterialFavorites", favs)),
])
