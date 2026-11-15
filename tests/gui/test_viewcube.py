# SPDX-License-Identifier: LGPL-2.1-or-later
"""Eigener ViewCube: Home-Knopf und Klick auf die obere Seite drehen die Kamera. In einer Seitenansicht drehen zwei
Pfeile oben rechts die Kamera um 90° um die Blickrichtung (rechts: Bild im Uhrzeigersinn), sonst sind sie nicht da."""
from harness import *


def cube():
    """der ViewCube: ein Element der 3D-Szene mit fester Größe 120 x 150"""
    return [i for i in view().scene().items() if i.boundingRect().width() == 120 and i.boundingRect().height() == 150][0]


def cube_click(x, y):  # Koordinaten relativ zum ViewCube
    v = view(); p = v.mapFromScene(cube().mapToScene(QtCore.QPointF(x, y)))
    QtTest.QTest.mouseMove(v.viewport(), p)
    QtTest.QTest.mouseClick(v.viewport(), QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)


def direction():
    d = Gui.ActiveDocument.ActiveView.getViewDirection()
    return "(%.2f, %.2f, %.2f)" % (d.x, d.y, d.z)


def up():
    """Welt-Richtung, die im Bild nach oben zeigt"""
    from pivy import coin
    u = Gui.ActiveDocument.ActiveView.getCameraNode().orientation.getValue().multVec(coin.SbVec3f(0, 1, 0)).getValue()
    return "(%.2f, %.2f, %.2f)" % tuple(0.0 if abs(c) < 0.005 else c for c in u)


def fitted(what="Fit All"):
    """Fit All: das Modell sitzt mittig im freien Bereich rechts neben der Seitenleiste, nicht unter ihr"""
    tree = visible(QtWidgets.QTreeWidget)[0]
    top = tree
    while top.parentWidget():
        top = top.parentWidget()
    left = top.graphicsProxyWidget().sceneBoundingRect().right()  # rechter Rand der Seitenleiste
    width = view().viewport().width()
    av = Gui.ActiveDocument.ActiveView
    b = body("Box").Shape.BoundBox
    xs = [av.getPointOnViewport(App.Vector(x, y, z))[0] for x in (b.XMin, b.XMax) for y in (b.YMin, b.YMax) for z in (b.ZMin, b.ZMax)]
    detail = "model x %.0f..%.0f, free area %.0f..%d" % (min(xs), max(xs), left, width)
    check(what + " centers the model in the free area", min(xs) > left and abs((min(xs) + max(xs)) / 2 - (left + width) / 2) < 0.05 * width, detail)


run([
    ("setup", lambda: make_body(rect(0, 0, 60, 40), 0, 15, "Box")),
    ("front", lambda: Gui.ActiveDocument.ActiveView.viewFront()),
    ("dir", lambda: L("front view dir=" + direction())),
    ("home", lambda: cube_click(19, 131)), ("wait", lambda: None),
    ("dir", lambda: check("home turns to the iso view", direction() == "(-0.58, 0.58, -0.58)", direction())),
    ("top face", lambda: cube_click(60, 40)), ("wait", lambda: None),
    ("dir", lambda: check("top face looks down", direction() in ("(0.00, 0.00, -1.00)", "(-0.00, -0.00, -1.00)", "(0.00, -0.00, -1.00)", "(-0.00, 0.00, -1.00)"), direction())),
    ("up", lambda: check("top view has +Y up", up() == "(0.00, 1.00, 0.00)", up())), ("shot top", lambda: shot("arrows")),
    ("turn right", lambda: cube_click(120 - 13, 13)), ("wait", lambda: None),
    ("right", lambda: check("the right arrow turns the picture clockwise (world X now points down)", up() == "(-1.00, 0.00, 0.00)", up())),
    ("turn left", lambda: cube_click(120 - 39, 13)), ("wait", lambda: None),
    ("left", lambda: check("the left arrow turns it back", up() == "(0.00, 1.00, 0.00)", up())),
    ("zoom in", lambda: [Gui.SendMsgToActiveView("ZoomIn") for _ in range(6)]), ("wait", lambda: None),
    ("home again", lambda: cube_click(19, 131)), ("wait", lambda: None), ("shot", lambda: shot("cube")),
    ("home fits", lambda: fitted("Home")),
    ("no arrows", lambda: (cube_click(120 - 13, 13), None)), ("wait", lambda: None),
    ("iso stays", lambda: check("in the iso view there are no arrows (a click there does not turn)", direction() == "(-0.58, 0.58, -0.58)", direction())),  # Home = Iso + ganzes Modell, wie die Hilfe sagt
    ("zoom in 2", lambda: [Gui.SendMsgToActiveView("ZoomIn") for _ in range(6)]), ("wait", lambda: None),
    ("fit all", lambda: Gui.runCommand("Std_ViewFitAll")), ("wait", lambda: None),
    ("fitted", fitted),
])
