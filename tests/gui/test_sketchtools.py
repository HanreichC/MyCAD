# SPDX-License-Identifier: LGPL-2.1-or-later
"""Skizzen-Werkzeuge mit Varianten: Pfeil am Rechteck-Knopf öffnet das Menü, "Centered" wählen, zwei Klicks
zeichnen ein Rechteck um den Mittelpunkt. Polygon zeigt seine Optionen (Ecken) unter der Sketch Palette,
nur "Tool Parameters", keine FreeCAD-Listen. Offset erzeugt eine zweite Kontur."""
import os
import harness
from harness import *


def arrow(cmd):
    b = button(cmd); p = harness._pos(b) + QtCore.QPoint(b.width() // 2 - 5, 0)
    QtTest.QTest.mouseClick(view().viewport(), QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)


def pick(text):
    for m in visible(QtWidgets.QMenu):
        L("menu=%s" % [a.text() for a in m.actions()])
        m.grab().save(os.environ["OUT"] + ".menu.png")
        for a in m.actions():
            if text in a.text().replace("&", ""):
                m.close(); a.trigger(); return
    raise RuntimeError("no menu entry " + text)


def sketch():
    return Gui.ActiveDocument.getInEdit().Object


def report(tag):
    xs = [round(v.x, 1) for g in sketch().Geometry if g.TypeId == "Part::GeomLineSegment" for v in (g.StartPoint, g.EndPoint)]
    L("%s: geometry=%d x-range=%s" % (tag, len(sketch().Geometry), (min(xs), max(xs)) if xs else None))


def boxes(tag):
    names = sorted(set(w.metaObject().className() for w in visible(QtWidgets.QWidget)
                       if w.metaObject().className().startswith("SketcherGui::Task")))
    L("%s: sketcher boxes visible=%s" % (tag, names))


def move(fx, fy):
    v = view(); QtTest.QTest.mouseMove(v.viewport(), QtCore.QPoint(int(v.width() * fx), int(v.height() * fy)))


run([
    ("Create Sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick XY", lambda: Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XY_Plane")][0])),
    ("idle", lambda: boxes("idle")),
    ("open menu", lambda: (QtCore.QTimer.singleShot(800, lambda: pick("Centered")), arrow("Sketcher_CompCreateRectangles"))),
    ("wait", lambda: None),
    ("center", lambda: view_click(0.50, 0.50)), ("corner", lambda: view_click(0.60, 0.60)),
    ("report", lambda: report("rectangle")),
    ("polygon", lambda: click(button("Sketcher_CompCreateRegularPolygon"))),
    ("polygon boxes", lambda: boxes("polygon")), ("shot polygon", lambda: shot("polygon")),
    ("esc", esc), ("after esc", lambda: boxes("after esc")),
    ("select", lambda: [Gui.Selection.addSelection(doc().Name, sketch().Name, "Edge%d" % i) for i in range(1, 5)]),
    ("selected", lambda: L("selection=%s" % [s.SubElementNames for s in Gui.Selection.getSelectionEx()])),
    ("offset", lambda: click(button("Sketcher_Offset"))),
    ("move", lambda: move(0.66, 0.66)), ("move2", lambda: move(0.67, 0.67)), ("shot offset", lambda: shot("offset")),
    ("place", lambda: view_click(0.67, 0.67)),
    ("report2", lambda: report("after offset")),
    ("errors", lambda: L("errors=%s" % errors())),
])
