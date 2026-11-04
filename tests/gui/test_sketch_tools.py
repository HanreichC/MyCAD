# SPDX-License-Identifier: LGPL-2.1-or-later
"""Zeichnen und Felder: Konstruktionsmodus sichtbar, Versatz einer Linie als Kopie auf der Mausseite, Fangen am Kreis,
Winkel rasten (Shift = frei), Klick ins Maßfeld wählt alles, Extrudieren einer Körperfläche, Post-it ohne Rahmen.
Fehler stehen als FAIL im Protokoll."""
import math
from PySide6 import QtGui
from harness import *

V = App.Vector
CTRL = QtCore.Qt.NoModifier
LEFT = QtCore.Qt.LeftButton
saved = {}
wait = ("wait", lambda: None)


def sketch():
    return Gui.ActiveDocument.getInEdit().Object


def screen(x, y):
    v = view(); px, py = Gui.ActiveDocument.ActiveView.getPointOnViewport(V(x, y, 0))
    dpr = v.viewport().devicePixelRatioF()
    return QtCore.QPoint(int(px / dpr), int(v.viewport().height() - py / dpr))


def hover(p, modifiers=QtCore.Qt.NoModifier):
    """Echte Mausbewegung: QTest.mouseMove ohne gedrückte Taste setzt nur den Cursor, und das geht unter Wayland nicht"""
    vp = view().viewport()
    for q in (p - QtCore.QPoint(1, 1), p):
        QtWidgets.QApplication.sendEvent(vp, QtGui.QMouseEvent(QtCore.QEvent.MouseMove, QtCore.QPointF(q), QtCore.QPointF(vp.mapToGlobal(q)), QtCore.Qt.NoButton, QtCore.Qt.NoButton, modifiers))


def move(x, y, dx=0, dy=0):
    p = screen(x, y) + QtCore.QPoint(dx, dy)
    hover(p)
    return p


def press(x, y, dx=0, dy=0, mod=CTRL):
    p = move(x, y, dx, dy)
    QtTest.QTest.mouseClick(view().viewport(), LEFT, mod, p)


def fit():
    Gui.SendMsgToActiveView("ViewFit")


def clear():
    s = sketch()
    while s.ConstraintCount:
        s.delConstraint(0)
    while s.GeometryCount:
        s.delGeometry(0)
    doc().recompute()


def palette_row():
    return [b for b in visible(QtWidgets.QToolButton) if b.objectName() == "PaletteRow" and b.text() == "Construction"][0]


def tool(name):
    return lambda: click(button(name))


def esc():
    QtTest.QTest.keyClick(view().viewport(), QtCore.Qt.Key_Escape)


def line_setup():
    clear(); sketch().addGeometry(Part.LineSegment(V(-30, 0, 0), V(30, 0, 0))); doc().recompute()
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(sketch(), "Edge1")


def offset_result(want_y):
    """Maus auf ganze Pixel gerundet: Abstand nur ungefähr, die Linie aber exakt parallel und gleich lang"""
    g = sketch().Geometry
    ok = len(g) == 2 and isinstance(g[1], Part.LineSegment) and abs(g[1].StartPoint.y - want_y) < 1 \
        and abs(g[1].EndPoint.y - g[1].StartPoint.y) < 1e-6 and abs(g[1].length() - 60) < 1e-6
    check("offset of a single line is one copy on the mouse side (y=%g)" % want_y, ok, str([type(x).__name__ + (" %s %s" % (x.StartPoint, x.EndPoint) if hasattr(x, "StartPoint") else "") for x in g]))


def chain_setup():
    clear(); sketch().addGeometry([Part.LineSegment(V(-30, 0, 0), V(30, 0, 0)), Part.LineSegment(V(30, 0, 0), V(30, 30, 0))])
    sketch().addConstraint(Sketcher.Constraint("Coincident", 0, 2, 1, 1)); doc().recompute()
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(sketch(), "Edge1"); Gui.Selection.addSelection(sketch(), "Edge2")


def chain_result():
    g = sketch().Geometry
    new = g[2:]
    ys = [p.y for x in new for p in (x.StartPoint, x.EndPoint)]
    check("offset of an open chain stays on one side", len(new) == 2 and all(isinstance(x, Part.LineSegment) for x in new) and min(ys) >= 5, str(ys))


def arc_setup():
    clear(); sketch().addGeometry(Part.ArcOfCircle(Part.Circle(V(0, 0, 0), V(0, 0, 1), 30), 0, math.pi)); doc().recompute()
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(sketch(), "Edge1")


def arc_result():
    g = sketch().Geometry
    check("offset of an arc is one larger arc on the mouse side", len(g) == 2 and isinstance(g[1], Part.ArcOfCircle) and abs(g[1].Radius - 40) < 1, str([getattr(x, "Radius", None) for x in g]))


def circle_setup():
    clear(); sketch().addGeometry(Part.Circle(V(0, 0, 0), V(0, 0, 1), 30)); doc().recompute()


def circle_offset_result():
    g = sketch().Geometry
    check("offset of a circle is still a circle around it", len(g) == 2 and isinstance(g[1], Part.Circle) and abs(g[1].Radius - 40) < 1, str([getattr(x, "Radius", None) for x in g]))


def on_circle(name):
    g = sketch().Geometry
    end = g[1].EndPoint if len(g) > 1 else V()
    cons = [c.Type for c in sketch().Constraints]
    check("line end lands exactly on the circle, " + name, abs(end.Length - 30) < 1e-6 and "PointOnObject" in cons, "r=%.6f %s" % (end.Length, cons))


def snap_steps():
    steps = []
    for name, x, y, dx, dy in [("from outside on the axis", 30, 0, 8, 0), ("from inside on the axis", 0, 30, 0, 8),
                               ("from outside at 45 degrees", 21.2132, 21.2132, 6, -6), ("from inside at 200 degrees", -28.19, -10.26, 7, 2)]:
        steps += [("circle " + name, circle_setup), ("line tool", tool("Sketcher_CreateLine")), wait,
                  ("start", lambda: press(5, 7)), wait,
                  ("near", lambda x=x, y=y, dx=dx, dy=dy: move(x, y, dx, dy)), wait,
                  ("end", lambda x=x, y=y, dx=dx, dy=dy: press(x, y, dx, dy)), wait,
                  ("esc", esc), wait,
                  ("check", lambda name=name: on_circle(name))]
    return steps


def free_end(deg):
    vp = view().viewport(); s = screen(0, 0) + QtCore.QPoint(40, -30); r = 200
    p = s + QtCore.QPoint(int(r * math.cos(math.radians(deg))), -int(r * math.sin(math.radians(deg))))
    hover(p, QtCore.Qt.ShiftModifier)
    QtTest.QTest.mouseClick(vp, LEFT, QtCore.Qt.ShiftModifier, p)


def angle_of(i=-1):
    g = sketch().Geometry[i]
    return math.degrees(math.atan2(g.EndPoint.y - g.StartPoint.y, g.EndPoint.x - g.StartPoint.x))


def polar(deg, r=40):
    return r * math.cos(math.radians(deg)), r * math.sin(math.radians(deg))


def draw_at(deg, mod=CTRL):
    clear()
    click(button("Sketcher_CreateLine"))
    QtWidgets.QApplication.processEvents()
    press(0, 0, 40, -30)  # Start neben dem Ursprung, damit dort nichts fängt
    saved["start"] = None


def finish_at(deg):
    g0 = view().viewport()
    s = screen(0, 0) + QtCore.QPoint(40, -30)
    r = 200
    p = s + QtCore.QPoint(int(r * math.cos(math.radians(deg))), -int(r * math.sin(math.radians(deg))))
    hover(p)
    QtTest.QTest.mouseClick(g0, LEFT, CTRL, p)


def check_angle(want, name):
    got = angle_of()
    check("%s: %.1f" % (name, want), abs(got - want) < 1e-6, "got %.4f" % got)


def fields():
    boxes = sorted(visible(QtWidgets.QAbstractSpinBox), key=lambda w: w.mapToGlobal(QtCore.QPoint(0, 0)).y())
    return boxes


def click_field():
    box = fields()[0]; saved["box"] = box
    activate()
    click(box)


def selected():
    box = saved["box"]; edit = box.findChild(QtWidgets.QLineEdit)
    check("click into a length field selects all of it", edit.selectedText() == edit.text() and edit.text() != "", repr((edit.selectedText(), edit.text())))


def type_over():
    for c in "25":
        QtTest.QTest.keyClick(mw.windowHandle(), c)
    edit = saved["box"].findChild(QtWidgets.QLineEdit)
    check("typing replaces the old value", edit.text().startswith("25") and "10" not in edit.text(), repr(edit.text()))


def setup_body():
    make_body(rect(0, 0, 60, 40), 0, 15, "Box")
    Gui.ActiveDocument.ActiveView.viewIsometric(); fit()


def pull():
    return [o for o in doc().Objects if o.TypeId == "Design::PressPull"]


def alert():
    return [w for w in visible(QtWidgets.QMessageBox)]


def close_alert():
    boxes = alert()
    check("body without a face: says what to click", len(boxes) == 1 and "flat face" in boxes[0].text() + boxes[0].informativeText(), boxes[0].informativeText() if boxes else "no message")
    for b in boxes:
        b.accept()


def note_frame():
    e = [e for e in visible(QtWidgets.QPlainTextEdit) if e.objectName() == "NoteText"][0]
    activate(); click(e); QtWidgets.QApplication.processEvents()
    img = e.grab().toImage(); corner = img.pixelColor(img.width() // 2, 0); inner = img.pixelColor(img.width() // 2, 3)
    check("note text has no frame, also with focus", e.frameWidth() == 0 and corner == inner, "frame=%d %s %s" % (e.frameWidth(), corner.name(), inner.name()))


import Sketcher

in_order([
    ("activate", activate),
    ("sketch", tool("Design_CreateSketch")),
    ("pick XY", lambda: Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XY_Plane")][0])), wait, wait,
    # 1 Konstruktionsmodus
    ("row off", lambda: check("construction row starts off", palette_row().isCheckable() and not palette_row().isChecked())),
    ("toggle", lambda: click(palette_row())), wait,
    ("row on", lambda: check("construction row and toolbar show the mode", palette_row().isChecked() and button("Sketcher_ToggleConstruction").isChecked())),
    ("shot on", lambda: shot("construction")),
    ("toggle off", lambda: click(button("Sketcher_ToggleConstruction"))), wait,
    ("row off 2", lambda: check("both off again", not palette_row().isChecked() and not button("Sketcher_ToggleConstruction").isChecked())),
    # 2 Versatz
    ("zoom", lambda: (sketch().addGeometry(Part.Circle(V(0, 0, 0), V(0, 0, 1), 60)), doc().recompute(), fit())), wait,
    ("line", line_setup),
    ("offset", tool("Sketcher_Offset")), wait,
    ("preview", lambda: move(0, 10)), wait,
    ("shot offset", lambda: shot("offset")),
    ("click", lambda: press(0, 10)), wait,
    ("above", lambda: offset_result(10)),
    ("line 2", line_setup),
    ("offset 2", tool("Sketcher_Offset")), wait,
    ("click below", lambda: press(0, -10)), wait,
    ("below", lambda: offset_result(-10)),
    ("chain", chain_setup),
    ("offset 3", tool("Sketcher_Offset")), wait,
    ("click chain", lambda: press(0, 10)), wait,
    ("chain ok", chain_result),
    ("arc", arc_setup),
    ("offset arc", tool("Sketcher_Offset")), wait,
    ("click arc", lambda: press(0, 40)), wait,
    ("arc ok", arc_result),
    ("circle", circle_setup),
    ("select circle", lambda: (Gui.Selection.clearSelection(), Gui.Selection.addSelection(sketch(), "Edge1"))),
    ("offset 4", tool("Sketcher_Offset")), wait,
    ("click circle", lambda: press(40, 0)), wait,
    ("circle ok", circle_offset_result),
    # 3 Fangen am Kreis
    *snap_steps(),
    # 3 Winkel
    ("draw 88", lambda: draw_at(88)), wait,
    ("end 88", lambda: finish_at(88.6)), wait,
    ("esc 2", esc), wait,
    ("exact 90", lambda: check_angle(90, "near vertical snaps")),
    ("draw 44", lambda: draw_at(44)), wait,
    ("end 44", lambda: finish_at(44)), wait,
    ("esc 3", esc), wait,
    ("exact 45", lambda: check_angle(45, "near a common angle snaps")),
    ("draw 37", lambda: draw_at(37)), wait,
    ("end 37", lambda: finish_at(37.3)), wait,
    ("esc 4", esc), wait,
    ("exact 37", lambda: check_angle(37, "other angles snap to whole degrees")),
    ("draw free", lambda: draw_at(37)), wait,
    ("shift", lambda: QtTest.QTest.keyPress(mw.windowHandle(), QtCore.Qt.Key_Shift, QtCore.Qt.ShiftModifier)),
    ("end free", lambda: free_end(37.3)), wait,
    ("no shift", lambda: QtTest.QTest.keyRelease(mw.windowHandle(), QtCore.Qt.Key_Shift)),
    ("esc 5", esc), wait,
    ("free", lambda: check("Shift draws freely", abs(angle_of() - round(angle_of())) > 1e-3, "got %.4f" % angle_of())),
    ("cleanup", clear),
    ("finish", lambda: click(button("Sketcher_LeaveSketch"))), wait,
    # 5 Felder
    ("body", setup_body), wait,
    # 7 Extrude auf Körperfläche
    ("select face", lambda: (Gui.Selection.clearSelection(), Gui.Selection.addSelection(body("Box"), top_face(body("Box"))))),
    ("extrude face", lambda: click(button("Design_Extrude"))), wait, wait,
    ("pull started", lambda: check("Extrude on a body face starts pulling that face", len(pull()) == 1 and Gui.Control.activeDialog())),
    ("field", click_field),
    ("field selected", selected),
    ("type", type_over), wait,
    ("shot field", lambda: shot("field")),
    ("ok", ok), wait,
    ("volume", lambda: check("the face moved by the typed distance", abs(body("Box").Shape.Volume - 60 * 40 * 40) < 1, "%.1f" % body("Box").Shape.Volume)),
    ("only body", lambda: (Gui.Selection.clearSelection(), Gui.Selection.addSelection(body("Box")))),
    ("extrude body", lambda: click(button("Design_Extrude"))), wait,
    ("message", close_alert), wait,
    # 6 Post-it ohne Rahmen
    ("note", lambda: click(button("Design_Note"))), wait,
    ("frame", note_frame),
    ("shot note", lambda: shot("note")),
])
