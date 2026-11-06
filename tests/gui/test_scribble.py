# SPDX-License-Identifier: LGPL-2.1-or-later
"""Scribbles mit echten Mausgesten: Blatt öffnet sich, Freihand-Strich, Halten macht Linie und Rechteck, Linie rastet am
Ende einer anderen ein, Rückgängig, Radierer, Transparentpapier, Blatt an einer Linie aufstellen und darauf zeichnen,
in eine Skizze umwandeln, Speichern und Laden. Fehler stehen als FAIL im Protokoll."""
import os
from harness import *
from PySide6 import QtGui

saved = {}


def scribbles():
    return [o for o in doc().Objects if o.TypeId == "Design::Scribble"]


def s():
    return scribbles()[0]


def editing():
    e = Gui.ActiveDocument.getInEdit()
    return e is not None and e.Object.TypeId == "Design::Scribble"


def at(fx, fy):
    v = view()
    return QtCore.QPoint(int(v.width() * fx), int(v.height() * fy))


def send(kind, fx, fy, button, buttons):
    """Mausereignis direkt an die 3D-Ansicht: QTest.mouseMove versetzt unter X11 den echten Zeiger, dessen
    Bewegung später als zusätzlicher Punkt im Strich landen würde"""
    vp = view().viewport(); p = QtCore.QPointF(at(fx, fy))
    QtWidgets.QApplication.sendEvent(vp, QtGui.QMouseEvent(kind, p, vp.mapToGlobal(p), button, buttons, QtCore.Qt.NoModifier))


def press(fx, fy):
    send(QtCore.QEvent.MouseButtonPress, fx, fy, QtCore.Qt.LeftButton, QtCore.Qt.LeftButton)


def path(points):
    for fx, fy in points:
        send(QtCore.QEvent.MouseMove, fx, fy, QtCore.Qt.NoButton, QtCore.Qt.LeftButton)


def release(fx, fy):
    send(QtCore.QEvent.MouseButtonRelease, fx, fy, QtCore.Qt.LeftButton, QtCore.Qt.NoButton)


_pens = {}


def pen(kind, fx, fy, pressure, eraser=False):
    """Grafiktablett: Stift- oder Radierer-Ereignis mit Druck"""
    T = QtGui.QPointingDevice.PointerType
    key = "eraser" if eraser else "pen"
    if key not in _pens:
        _pens[key] = QtGui.QPointingDevice(key, 7 + len(_pens), QtGui.QInputDevice.DeviceType.Stylus, T.Eraser if eraser else T.Pen,
                                           QtGui.QInputDevice.Capability.Position | QtGui.QInputDevice.Capability.Pressure, 1, 3)
    vp = view().viewport(); p = QtCore.QPointF(at(fx, fy))
    down = kind != QtCore.QEvent.TabletRelease
    e = QtGui.QTabletEvent(kind, _pens[key], p, vp.mapToGlobal(p), pressure, 0, 0, 0, 0, 0, QtCore.Qt.NoModifier,
                           QtCore.Qt.LeftButton if kind != QtCore.QEvent.TabletMove else QtCore.Qt.NoButton,
                           QtCore.Qt.LeftButton if down else QtCore.Qt.NoButton)
    QtWidgets.QApplication.sendEvent(vp, e)
    return e.isAccepted()


def pen_stroke(a, b, eraser=False):
    pts = line(a, b, 20)
    accepted = pen(QtCore.QEvent.TabletPress, *pts[0], 0.05, eraser)
    for k, q in enumerate(pts[1:], 1):
        pen(QtCore.QEvent.TabletMove, *q, 0.05 + 0.95 * k / 20, eraser)
    pen(QtCore.QEvent.TabletRelease, *pts[-1], 1.0, eraser)
    saved["accepted"] = accepted


def stroke(points):
    press(*points[0]); path(points[1:]); release(*points[-1])


def line(a, b, n=30):
    return [(a[0] + (b[0] - a[0]) * k / n, a[1] + (b[1] - a[1]) * k / n) for k in range(n + 1)]


def rect_path(x0, y0, x1, y1):
    return line((x0, y0), (x1, y0), 12) + line((x1, y0), (x1, y1), 12)[1:] + line((x1, y1), (x0, y1), 12)[1:] + line((x0, y1), (x0, y0), 12)[1:]


def kinds():
    return list(s().Kinds)


def ends(i):
    """Anfang und Ende von Strich i"""
    start = sum(s().Counts[:i])
    pts = s().Points[start:start + s().Counts[i]]
    return pts[0], pts[-1]


def dump(tag):
    """Striche ins Protokoll: Punktzahl, Form, Anfang und Ende"""
    L("  %s counts=%s kinds=%s ends=%s" % (tag, list(s().Counts), kinds(), [tuple(round(c, 2) for c in (e.x, e.y, e.z)) for i in range(len(s().Counts)) for e in ends(i)]))


def normal():
    return s().Sheet.Rotation.multVec(App.Vector(0, 0, 1))


def reopen_file():
    path_ = os.environ["OUT"] + ".mycad"
    doc().saveAs(path_)
    App.closeDocument(doc().Name)
    App.openDocument(path_)


wait = ("wait", lambda: None)
hold = ("hold", lambda: None)  # Stift steht still: die Formerkennung (450 ms) schlägt zu

in_order([
    ("note first", lambda: Gui.runCommand("Design_Note")), wait,
    ("new", lambda: click(button("Design_Scribble"))), wait, wait,
    ("opened", lambda: check("scribble opens its sheet", len(scribbles()) == 1 and editing())),
    ("toolbar", lambda: check("scribble toolbar with pens", button("Design_ScribblePen").isVisible() and button("Design_ScribbleEraser").isVisible())),
    ("pen checked", lambda: check("fineliner is the active tool", button("Design_ScribblePen").isChecked())),
    ("folder order", lambda: check("browser: Scribbles before Notes", [o.Name.rstrip("0123456789") for o in doc().getObject("Root").Group if o.TypeId == "App::DocumentObjectGroup"][-2:] == ["Scribbles", "Notes"],
                                   str([o.Name for o in doc().getObject("Root").Group]))),
    ("shot empty", lambda: shot("empty")),

    ("free", lambda: stroke([(0.40 + 0.01 * k, 0.62 + 0.03 * ((-1) ** k)) for k in range(16)])), wait,
    ("free kept", lambda: check("zigzag stays a free stroke", kinds() == [0], str(kinds()))),
    ("free on sheet", lambda: check("points lie on the XY sheet", all(abs(p.z) < 1e-6 for p in s().Points))),
    ("width", lambda: check("stroke has a width", all(w > 0 for w in s().Widths))),

    ("line down", lambda: (press(0.40, 0.40), path(line((0.40, 0.40), (0.56, 0.412))))), hold,
    ("line up", lambda: release(0.56, 0.412)), wait, ("dump", lambda: dump("line")),
    ("line", lambda: check("held stroke becomes a line", kinds() == [0, 1] and s().Counts[1] == 2, str(kinds()))),
    ("level", lambda: check("almost level line snaps level", abs(ends(1)[0].y - ends(1)[1].y) < 1e-6, str(ends(1)))),

    ("snap line", lambda: (press(0.562, 0.405), path(line((0.562, 0.405), (0.565, 0.52))))), hold,
    ("snap up", lambda: release(0.565, 0.52)), wait,
    ("snapped", lambda: check("new line starts exactly at the end of the old one", kinds()[-1] == 1 and (ends(2)[0] - ends(1)[1]).Length < 1e-9, str(ends(2)[0]))),
    ("vertical", lambda: check("almost vertical line snaps vertical", abs(ends(2)[0].x - ends(2)[1].x) < 1e-6)),

    ("rect down", lambda: (press(0.62, 0.40), path(rect_path(0.62, 0.40, 0.70, 0.50)[1:]))), hold,
    ("rect up", lambda: release(0.62, 0.40)), wait,
    ("rect", lambda: check("held closed stroke becomes a rectangle", kinds()[-1] == 3 and s().Counts[-1] == 5, str(kinds()))),
    ("shot drawn", lambda: shot("drawn")),

    ("undo", lambda: Gui.runCommand("Std_Undo")), wait,
    ("undone", lambda: check("undo takes the last stroke back", len(kinds()) == 3)),
    ("redo", lambda: Gui.runCommand("Std_Redo")), wait,
    ("redone", lambda: check("redo brings it back", len(kinds()) == 4)),

    ("tablet", lambda: pen_stroke((0.40, 0.76), (0.55, 0.80))), wait,
    ("tablet stroke", lambda: check("pen tablet draws (press accepted, no mouse fallback)", saved["accepted"] and len(kinds()) == 5)),
    ("pressure", lambda: check("pressing harder makes the line thicker", s().Widths[-1] > 2 * s().Widths[sum(s().Counts[:-1])],
                               "%.3f -> %.3f" % (s().Widths[sum(s().Counts[:-1])], s().Widths[-1]))),
    ("pen eraser", lambda: pen_stroke((0.47, 0.72), (0.48, 0.84), eraser=True)), wait,
    ("pen erased", lambda: check("back of the pen erases", kinds() == [0, 1, 1, 3], str(kinds()))),
    ("still pen", lambda: check("erasing with the pen keeps the fineliner selected", button("Design_ScribblePen").isChecked())),
    ("eraser", lambda: click(button("Design_ScribbleEraser"))), wait,
    ("wipe", lambda: stroke(line((0.42, 0.55), (0.42, 0.70), 20))), wait,
    ("erased", lambda: check("eraser removes the free stroke only", kinds() == [1, 1, 3], str(kinds()))),
    ("undo erase", lambda: Gui.runCommand("Std_Undo")), wait,
    ("erase undone", lambda: check("undo brings an erased stroke back", kinds() == [0, 1, 1, 3], str(kinds()))),

    ("tracing", lambda: Gui.runCommand("Design_ScribbleTracing")), wait,
    ("traced", lambda: check("tracing paper on", s().Tracing)),
    ("tracing off", lambda: Gui.runCommand("Design_ScribbleTracing")),

    ("sheet tool", lambda: click(button("Design_ScribbleSheet"))), wait,
    ("tap line", lambda: stroke([(0.48, 0.405)])), wait,
    ("stood up", lambda: check("tapping a line stands the sheet up along it", abs(normal().z) < 1e-6 and abs(normal().x) < 1e-6, str(normal()))),
    ("back to pen", lambda: check("after moving the sheet the pen is back", button("Design_ScribblePen").isChecked())),
    ("look", lambda: Gui.runCommand("Design_ScribbleLookAt")), wait, wait,
    ("3d", lambda: stroke(line((0.45, 0.45), (0.52, 0.30), 20))), wait,
    ("3d stroke", lambda: check("stroke on the upright sheet", abs(s().Normals[-1].z) < 1e-6 and len(kinds()) == 5)),
    ("shot 3d", lambda: shot("3d")),
    ("iso", lambda: Gui.ActiveDocument.ActiveView.viewIsometric()), wait,
    ("shot iso", lambda: shot("iso")),

    ("back to XY", lambda: setattr(s(), "Sheet", App.Placement())), wait,
    ("convert", lambda: Gui.runCommand("Design_ScribbleToSketch")), wait, wait,
    ("sketch", lambda: check("convert opens a sketch", Gui.ActiveDocument.getInEdit() is not None and Gui.ActiveDocument.getInEdit().Object.TypeId == "Sketcher::SketchObject")),
    ("geometry", lambda: saved.update(sk=Gui.ActiveDocument.getInEdit().Object)),
    ("lines", lambda: check("zigzag (15 lines), two lines and a rectangle become 21 lines", saved["sk"].GeometryCount == 21
                            and all(g.TypeId == "Part::GeomLineSegment" for g in saved["sk"].Geometry), str([g.TypeId for g in saved["sk"].Geometry]))),
    ("coincident", lambda: check("touching ends are joined", sum(1 for c in saved["sk"].Constraints if c.Type == "Coincident") >= 19, str([c.Type for c in saved["sk"].Constraints]))),
    ("solved", lambda: check("the sketch solves", saved["sk"].solve() == 0)),
    ("hidden", lambda: check("scribble is hidden after converting", not s().Visibility)),
    ("leave", lambda: Gui.ActiveDocument.resetEdit()), wait,

    ("save", reopen_file), wait, wait,
    ("loaded", lambda: check("after reload: strokes, kinds and sheet", kinds() == [0, 1, 1, 3, 0] and len(s().Points) == sum(s().Counts))),
    ("reopen", lambda: (setattr(s(), "Visibility", True), Gui.ActiveDocument.setEdit(s().Name))), wait,
    ("reopened", lambda: check("double-click/setEdit reopens the sheet", editing())),
    ("esc", lambda: (activate(), QtTest.QTest.keyClick(view().viewport(), QtCore.Qt.Key_Escape))), wait,
    ("closed", lambda: check("Esc finishes the scribble", not editing())),
    ("shot end", lambda: shot("end")),
])
