# SPDX-License-Identifier: LGPL-2.1-or-later
"""Texturen auf Körpern: Kachel im Panel gibt dem Körper Maserung, ein einfarbiges Material nimmt sie wieder weg,
Abbrechen stellt sie zurück, Speichern und Öffnen behält sie. In den Einstellungen gewählt bekommen auch neue Körper
die Textur, ein Körper mit eigenem Material bleibt. Fehler stehen als FAIL im Protokoll, Bilder in <OUT>.*.png."""
import os
import tempfile
from PySide6 import QtGui
from harness import *

grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")
old = grp.GetInt("BodyMaterial", 29)  # Vorgabe Stahl (Shell.h DefaultBodyMaterial)
state = {}
FILE = os.path.join(tempfile.mkdtemp(), "texture.FCStd")


def cylinder(x, y, r, h, name):
    return make_body([Part.Circle(App.Vector(x, y, 0), App.Vector(0, 0, 1), r)], 0, h, name)


def fit():
    Gui.ActiveDocument.ActiveView.viewIsometric()
    Gui.SendMsgToActiveView("ViewFit")


def patch(b, z=None):
    """Mittelwert und Streuung der Bildpunkte rund um die Mitte der Oberseite des Körpers"""
    bb = b.Shape.BoundBox
    point = App.Vector(bb.Center.x, bb.Center.y, bb.ZMax if z is None else z)
    px, py = Gui.ActiveDocument.ActiveView.getPointOnViewport(point)
    v = view().viewport()
    image = v.grab().toImage()
    ratio = image.width() / v.width()
    cx, cy = int(px), int(image.height() - py)
    colors = [image.pixelColor(cx + dx, cy + dy) for dx in range(-14, 15, 2) for dy in range(-14, 15, 2)]
    mean = [sum(getattr(c, n)() for c in colors) / len(colors) for n in ("red", "green", "blue")]
    spread = (sum(sum((getattr(c, n)() - mean[i]) ** 2 for i, n in enumerate(("red", "green", "blue"))) for c in colors) / len(colors)) ** 0.5
    return mean, spread


def textured(b):
    return patch(b)[1] > 3.0  # einfarbig bleibt praktisch 0


def tile(name):
    [b for b in visible(QtWidgets.QToolButton) if b.accessibleName() == name][0].click()


def setup():
    state["box"] = make_body(rect(0, 0, 90, 60), 0, 30, "Box")
    state["cyl"] = cylinder(150, 30, 30, 50, "Cylinder")
    state["own"] = make_body(rect(-90, 0, -20, 60), 0, 30, "Own")


def select(*names):
    Gui.Selection.clearSelection()
    for n in names:
        Gui.Selection.addSelection(body(n))


def appearance(*names):
    select(*names)
    Gui.runCommand("Design_Appearance")


def report(tag, b):
    mean, spread = patch(b)
    L("  %s: rgb=(%d,%d,%d) Streuung=%.1f" % (tag, *mean, spread))


def woody(b):
    r, g, bl = patch(b)[0]
    return r > g > bl


def pick_default(name):
    def act():
        d = [w for w in visible(QtWidgets.QDialog) if w.windowTitle() == "Settings"][0]
        combo = [c for c in d.findChildren(QtWidgets.QComboBox) if c.findText(name) >= 0][0]
        combo.setCurrentIndex(combo.findText(name))
        d.accept()
    QtCore.QTimer.singleShot(800, act)
    Gui.runCommand("MyCAD_Settings")


def reopen():
    Gui.Selection.clearSelection()
    doc().saveAs(FILE)
    App.closeDocument(doc().Name)
    App.openDocument(FILE)


def after_reopen():
    state["box"] = body("Box")
    state["cyl"] = body("Cylinder")
    fit()


in_order([
    ("setup", setup),
    ("fit", fit),
    ("plain", lambda: (report("vorher", state["box"]), check("neuer Körper ohne Textur einfarbig", not textured(state["box"])))),

    ("panel", lambda: appearance("Box", "Cylinder")),
    ("panel shot", lambda: shot("panel")),
    ("oak", lambda: tile("Oak")),
    ("deselect", Gui.Selection.clearSelection),
    ("oak check", lambda: (report("Eiche", state["box"]), check("Eiche zeigt Maserung", textured(state["box"])), check("Eiche ist holzfarben", woody(state["box"])), shot("oak"))),

    ("select", lambda: select("Box", "Cylinder")),
    ("steel", lambda: tile("Steel")),
    ("deselect", Gui.Selection.clearSelection),
    ("steel check", lambda: (report("Stahl", state["box"]), check("Stahl nimmt die Textur weg", not textured(state["box"])))),

    ("select", lambda: select("Box", "Cylinder")),
    ("carbon", lambda: tile("Carbon Fiber")),
    ("deselect", Gui.Selection.clearSelection),
    ("carbon check", lambda: (report("Carbon", state["box"]), check("Carbon zeigt Gewebe", textured(state["box"])), shot("carbon"))),
    ("select", lambda: select("Box", "Cylinder")),
    ("walnut", lambda: tile("Walnut")),
    ("ok", ok),
    ("deselect", Gui.Selection.clearSelection),
    ("walnut check", lambda: (report("Nussbaum", state["box"]), check("Nussbaum nach OK", textured(state["box"])), check("Zylinder hat Textur", patch(state["cyl"])[1] > 3.0), shot("walnut"))),

    ("own panel", lambda: appearance("Box")),
    ("marble", lambda: tile("Marble")),
    ("cancel", lambda: [b for b in visible(QtWidgets.QPushButton) if b.text().replace("&", "") == "Cancel"][0].click()),
    ("deselect", Gui.Selection.clearSelection),
    ("cancel check", lambda: (report("nach Abbrechen", state["box"]), check("Abbrechen stellt Nussbaum wieder her", woody(state["box"]) and sum(patch(state["box"])[0]) < 360))),

    ("reopen", reopen),
    ("after", after_reopen),
    ("reopen check", lambda: (report("nach Öffnen", state["box"]), check("Textur übersteht Speichern und Öffnen", textured(state["box"])), shot("reopened"))),

    # Vorgabe in den Einstellungen: bestehender Körper mit eigener Textur bleibt, neuer Körper bekommt Eiche (deutliche
    # Maserung; der Ahorn-Scan ist fast gleichmäßig hell wie echter Ahorn)
    ("default", lambda: pick_default("Oak")), ("wait", lambda: None), ("wait", lambda: None),
    ("new", lambda: state.update(new=make_body(rect(0, 100, 90, 160), 0, 30, "New"))),
    ("fit", fit),
    ("default check", lambda: (report("neu mit Vorgabe Eiche", state["new"]), report("eigene Textur", state["box"]),
                               check("neuer Körper bekommt die Vorgabe-Textur", textured(state["new"]) and sum(patch(state["new"])[0]) > 400),
                               check("eigene Textur bleibt beim Wechsel", textured(state["box"]) and sum(patch(state["box"])[0]) < 360),
                               shot("default"))),
    ("back", lambda: pick_default("Steel")), ("wait", lambda: None), ("wait", lambda: None),
    ("back check", lambda: (report("zurück auf Stahl", state["new"]), check("Vorgabe zurück nimmt die Textur vom Standard-Körper", not textured(state["new"])),
                            check("eigene Textur bleibt auch dann", textured(state["box"])))),
    ("restore", lambda: grp.SetInt("BodyMaterial", old)),
], delay=1500)
