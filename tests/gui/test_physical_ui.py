# SPDX-License-Identifier: LGPL-2.1-or-later
"""L9 in der Oberfläche: ein neuer Körper hat den Werkstoff seines Aussehens, Appearance setzt den Werkstoff mit, eigene
Wahl bleibt, Messen zeigt Masse und Schwerpunkt"""
from harness import *
import Design

state = {}


def uuid(name):
    return dict(Design.physicalMaterials())[name]


def tile(name):
    [b for b in visible(QtWidgets.QToolButton) if b.accessibleName() == name][0].click()


def search(text):
    [e for e in visible(QtWidgets.QLineEdit) if e.placeholderText() == "Search materials"][0].setText(text)


def picker():
    return [c for c in visible(QtWidgets.QComboBox) if c.accessibleName() == "Physical material"][0]


def measured():
    return " ".join(l.text() for l in visible(QtWidgets.QLabel) if "<table>" in l.text())


def look():
    return tuple(round(x, 2) for x in body("Box").ViewObject.ShapeAppearance[0].DiffuseColor[:3])


def select_box():
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(body("Box"))


# in_order: jeder Schritt wartet, bis der vorige fertig ist (Kamera-Animation, Dateidialog, Materialvorschauen)
in_order([
    ("setup", lambda: make_body(rect(0, 0, 100, 100), 0, 100, "Box")),
    # ein neuer Körper sieht aus wie Stahl (Vorgabe): Messen soll auch Stahl und eine Masse zeigen, nicht "Default"
    ("new body", lambda: check("a new body gets the material of its look", body("Box").ShapeMaterial.UUID == uuid("Steel")
                               and look() == (0.56, 0.57, 0.59), "%s %s" % (body("Box").ShapeMaterial.Name, look()))),
    ("select", select_box),
    ("appearance", lambda: click(button("Design_Appearance"))),
    ("search", lambda: search("Brushed Aluminum")),
    ("pick", lambda: tile("Brushed Aluminum")),
    ("follows", lambda: check("appearance sets aluminum", body("Box").ShapeMaterial.UUID == uuid("Aluminum"),
                              body("Box").ShapeMaterial.Name)),
    ("picker", lambda: check("picker says from appearance", picker().currentIndex() == 0)),
    ("choose", lambda: picker().setCurrentIndex(picker().findData(uuid("Steel")))),
    ("search2", lambda: search("Walnut")),
    ("pick2", lambda: tile("Walnut, Oiled")),
    ("kept", lambda: check("own choice survives a new appearance", body("Box").ShapeMaterial.UUID == uuid("Steel"),
                           body("Box").ShapeMaterial.Name)),
    ("ok", ok),
    ("measure", lambda: (select_box(), click(button("Design_Measure")))),
    ("mass", lambda: check("measure shows the mass", "Mass" in measured() and " kg" in measured()
                           and "Center of mass" in measured(), measured()[:300])),
    ("shot", lambda: shot("measure")),
    ("close", esc),
])
