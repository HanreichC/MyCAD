# SPDX-License-Identifier: LGPL-2.1-or-later
"""Das Material eines Körpers bleibt, wenn man ihn verändert (Christopher 27.11.: nach Teilen oder einem Extrude, das
den Körper vergrößert oder etwas hinzufügt, war das Material weg). Nussbaum über das Aussehen-Panel, dann über die
Oberfläche: Deckfläche extrudieren, eine Skizze darauf mit Verbinden extrudieren, an der XZ-Ebene teilen. Dann nur die
Deckfläche eines zweiten Körpers in Nussbaum (Aussehen mit gewählter Fläche: Material je Fläche), extrudieren, teilen."""
from harness import *

S = {}
W = ("wait", lambda: None)
V = App.Vector


def vp(obj):
    return Gui.ActiveDocument.getObject(obj.Name)


def look(obj):
    m = vp(obj).ShapeAppearance[0]
    return (tuple(round(c, 3) for c in m.DiffuseColor[:3]), round(m.Shininess, 3), len(vp(obj).ShapeAppearance))


def bodies():
    return [o for o in doc().Objects if o.TypeId == "Design::Body"]


def setup():
    S["body"] = make_body(rect(-20, -15, 20, 15), 0, 10, "Plate")  # mittig: die XZ-Ebene teilt ihn
    Gui.ActiveDocument.ActiveView.viewIsometric()
    Gui.SendMsgToActiveView("ViewFit")


def walnut():
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(S["body"])
    Gui.runCommand("Design_Appearance")


def tile(name):
    [b for b in visible(QtWidgets.QToolButton) if b.accessibleName() == name][0].click()


def remember():
    S["look"] = look(S["body"])
    S["grain"] = grain(S["body"])
    L("  look %s grain %.1f" % (S["look"], S["grain"]))


def top_face(key="body"):
    b = S[key]
    return ["Face%d" % (i + 1) for i, f in enumerate(b.Shape.Faces) if abs(f.CenterOfMass.z - b.Shape.BoundBox.ZMax) < 1e-6
            and f.Area > 100][0]


def extrude_top(key="body"):
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(doc().Name, S[key].Name, top_face(key))
    click(button("Design_Extrude"))


def face_looks(b):
    """(Material der Deckfläche, Material der übrigen Flächen) je Fläche"""
    mats = vp(b).ShapeAppearance
    top = int(top_face_of(b)[4:]) - 1
    rest = {tuple(round(c, 3) for c in m.DiffuseColor[:3]) for i, m in enumerate(mats) if i != top} if len(mats) > 1 else set()
    pick = mats[top] if len(mats) > 1 else mats[0]
    return tuple(round(c, 3) for c in pick.DiffuseColor[:3]), rest, len(mats), len(b.Shape.Faces)


def top_face_of(b):
    return ["Face%d" % (i + 1) for i, f in enumerate(b.Shape.Faces) if abs(f.CenterOfMass.z - b.Shape.BoundBox.ZMax) < 1e-6][0]


def paint_top():
    S["tile"] = make_body(rect(40, -15, 80, 15), 0, 10, "Tile")
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(doc().Name, S["tile"].Name, top_face("tile"))
    Gui.runCommand("Design_Appearance")


def remember_faces():
    S["faces"] = face_looks(S["tile"])
    L("  faces %s" % (S["faces"],))
    check("only the top face is walnut", S["faces"][2] == S["faces"][3] and S["faces"][0] not in S["faces"][1]
          and len(S["faces"][1]) == 1, str(S["faces"]))


def faces_kept(what, b=None):
    def go():
        t = b() if b else S["tile"]
        f = face_looks(t)
        check("the walnut top face stays walnut after " + what + " (" + t.Label + ")",
              f[2] == f[3] and f[0] == S["faces"][0] and f[1] == S["faces"][1], "%s -> %s" % (S["faces"], f))
    return go


def split_tile():
    plane = [o for o in doc().Objects if o.Name.startswith("XZ_Plane")][0]
    S["before"] = set(bodies())
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(S["tile"])
    Gui.Selection.addSelection(plane)
    Gui.runCommand("Design_SplitBody")


def grain(b):
    """Streuung der Bildpunkte rund um die Mitte der Oberseite (Holzmaserung > 3, einfarbig ~0), wie test_texture"""
    Gui.Selection.clearSelection()
    QtWidgets.QApplication.processEvents()
    bb = b.Shape.BoundBox
    px, py = Gui.ActiveDocument.ActiveView.getPointOnViewport(App.Vector(bb.Center.x, bb.Center.y - bb.YLength / 4, bb.ZMax))
    image = view().viewport().grab().toImage()
    cx, cy = int(px), int(image.height() - py)
    colors = [image.pixelColor(cx + dx, cy + dy) for dx in range(-10, 11, 2) for dy in range(-10, 11, 2)]
    mean = [sum(getattr(c, n)() for c in colors) / len(colors) for n in ("red", "green", "blue")]
    return (sum(sum((getattr(c, n)() - mean[i]) ** 2 for i, n in enumerate(("red", "green", "blue"))) for c in colors)
            / len(colors)) ** 0.5


def kept(what):
    def go():
        check("the material stays after " + what, look(S["body"]) == S["look"],
              "%s -> %s; bodies %s" % (S["look"], look(S["body"]), [(o.Label, look(o)) for o in bodies()]))
        g = grain(S["body"])
        check("and its wood grain shows after " + what, g > 3.0, "spread %.1f (before %.1f)" % (g, S["grain"]))
    return go


def sketch_on_top():
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(doc().Name, S["body"].Name, top_face())
    click(button("Design_CreateSketch"))


def boss():
    s = Gui.ActiveDocument.getInEdit().Object
    c = s.Placement.inverse().multVec(V(8, 5, 0))
    s.addGeometry(Part.Circle(V(c.x, c.y, 0), V(0, 0, 1), 5))
    doc().recompute()
    S["sketch"] = s


def leave():
    QtTest.QTest.keyClick(view().viewport(), QtCore.Qt.Key_Escape)
    if Gui.ActiveDocument.getInEdit():
        Gui.ActiveDocument.resetEdit()


def extrude_boss():
    prof = [o for o in S["sketch"].InList if o.TypeId == "Design::Profiles"][0]
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(prof, "Face1")
    click(button("Design_Extrude"))


def split():
    plane = [o for o in doc().Objects if o.Name.startswith("XZ_Plane")][0]
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(S["body"])
    Gui.Selection.addSelection(plane)
    Gui.runCommand("Design_SplitBody")


def dump(tag):
    return lambda: L("  %s: op=%s bodies=%s" % (tag, [getattr(o, "Operation", "") for o in doc().Objects if o.TypeId == "Design::Extrude"][-1:],
                                               [(o.Label, look(o), round(o.Shape.Volume, 1)) for o in bodies()]))


run([("activate", activate), ("setup", setup), W, W,
     ("appearance", walnut), W, ("walnut", lambda: tile("Walnut")), W, ("ok", ok), W, ("remember", remember),
     # 1. Deckfläche extrudieren (vergrößert den Körper)
     ("extrude top", extrude_top), W, W, ("distance", lambda: type_field("Distance", "5")), W, ("ok 1", ok), W, W,
     ("dump 1", dump("after extruding the top face")),
     ("kept 1", kept("extruding its top face")),
     # 2. Skizze auf der Deckfläche, Kreis, mit Verbinden extrudieren (etwas hinzufügen)
     ("sketch", sketch_on_top), W, W, ("boss", boss), W, ("leave", leave), W, W,
     ("extrude boss", extrude_boss), W, W, ("height", lambda: type_field("Distance", "8")), W, ("ok 2", ok), W, W,
     ("dump 2", dump("after adding a boss")),
     ("kept 2", kept("adding a boss with Extrude")),
     # 3. Teilen an der XZ-Ebene
     ("split", split), W, W, W,
     ("dump 3", dump("after splitting")),
     ("kept 3", kept("splitting it")),
     ("pieces", lambda: check("every piece of the split body has the material",
                              all(look(o) == S["look"] for o in bodies()), str([(o.Label, look(o)) for o in bodies()]))),
     # 4. nur die Deckfläche in Nussbaum, extrudieren, teilen
     ("paint top", paint_top), W, W, ("walnut 2", lambda: tile("Walnut")), W, ("ok 4", ok), W, ("faces", remember_faces),
     ("extrude tile", lambda: extrude_top("tile")), W, W, ("distance 2", lambda: type_field("Distance", "5")), W, ("ok 5", ok), W, W,
     ("faces 1", faces_kept("extruding it")),
     ("split tile", split_tile), W, W, W,
     ("faces 2", faces_kept("splitting it")),
     ("faces 3", faces_kept("splitting it", lambda: [o for o in bodies() if o not in S["before"]][0])),
     ("errors", lambda: check("no errors", not errors(), str(errors()))),
     ])
