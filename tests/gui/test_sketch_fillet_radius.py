# SPDX-License-Identifier: LGPL-2.1-or-later
"""Abrunden in der Skizze fragt wie Fusion gleich den Radius ab: Klick auf eine Ecke, Wert tippen, Enter → Bogen mit
genau diesem Radius und einem Radius-Maß. Esc im Feld nimmt das Abrunden ganz zurück."""
import os
import shiboken6
from PySide6 import QtGui
from harness import *

V = App.Vector
wait = ("wait", lambda: None)
S = {}


def sketch():
    return Gui.ActiveDocument.getInEdit().Object


def click_corner(x, y):
    """Echter Klick auf die Ecke (x, y); der Feld-Dialog ist modal, darum aus der Ereignisschleife heraus"""
    vp = view().viewport(); dpr = vp.devicePixelRatioF()
    px, py = Gui.ActiveDocument.ActiveView.getPointOnViewport(V(x, y, 0))
    p = QtCore.QPoint(int(px / dpr), int(vp.height() - py / dpr))

    def go():
        for q in (p - QtCore.QPoint(1, 1), p):
            QtWidgets.QApplication.sendEvent(vp, QtGui.QMouseEvent(QtCore.QEvent.MouseMove, QtCore.QPointF(q), QtCore.QPointF(vp.mapToGlobal(q)), QtCore.Qt.NoButton, QtCore.Qt.NoButton, QtCore.Qt.NoModifier))
        QtTest.QTest.mouseClick(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)
    QtCore.QTimer.singleShot(0, go)


def setup():
    s = sketch()
    for g in rect(0, 0, 40, 20):
        s.addGeometry(g)
    import Sketcher
    for i in range(4):
        s.addConstraint(Sketcher.Constraint("Coincident", i, 2, (i + 1) % 4, 1))
    doc().recompute()
    Gui.SendMsgToActiveView("ViewFit")


def dialog_open():
    m = QtWidgets.QApplication.activeModalWidget()
    if m and "shot" not in S:  # Bild des Felds einmal, für den Abgleich mit MyStyle
        S["shot"] = m.grab().save(os.environ["OUT"] + ".fillet_field.png")
    check("clicking a corner asks for the radius", m is not None, str(m and m.windowTitle()))


def keys(*ks):
    """Tasten an das Wertfeld des offenen Dialogs (der Wert ist vorgewählt). PySide kann für das Feld eine alte,
    gelöschte Hülle an derselben Adresse liefern (Dialog auf dem Stack, Feld-Prüfungen im Harness): verwerfen und
    neu holen."""
    m = QtWidgets.QApplication.activeModalWidget()
    box = m.findChild(QtWidgets.QAbstractSpinBox)
    while not shiboken6.isValid(box):
        shiboken6.invalidate(box)
        box = m.findChild(QtWidgets.QAbstractSpinBox)
    box.setFocus()
    for k in ks:
        QtTest.QTest.keyClick(box, k)


def type_value(text):
    keys(*text, QtCore.Qt.Key_Return)


def rounded():
    s = sketch()
    arcs = [g for g in s.Geometry if isinstance(g, Part.ArcOfCircle)]
    radius = [c.Value for c in s.Constraints if c.Type == "Radius"]
    check("the corner is rounded with exactly the typed radius and keeps a radius dimension",
          len(arcs) == 1 and abs(arcs[0].Radius - 3) < 1e-6 and radius == [3.0],
          "arcs=%s radius=%s" % ([round(a.Radius, 4) for a in arcs], radius))
    S["count"] = s.GeometryCount


def esc():
    keys(QtCore.Qt.Key_Escape)


def undone():
    s = sketch()
    check("esc in the radius field takes the whole fillet back",
          QtWidgets.QApplication.activeModalWidget() is None and s.GeometryCount == S["count"]
          and len([c for c in s.Constraints if c.Type == "Radius"]) == 1,
          "geometry %d -> %d" % (S["count"], s.GeometryCount))


def setup_slot():
    """Rechteck 40 × 10: zwei R5 an der rechten Seite fressen sie ganz auf (Halbkreis wie bei Monitor Light)"""
    s = sketch()
    while s.ConstraintCount:
        s.delConstraint(0)
    while s.GeometryCount:
        s.delGeometry(0)
    for g in rect(0, 0, 40, 10):
        s.addGeometry(g)
    import Sketcher
    for i in range(4):
        s.addConstraint(Sketcher.Constraint("Coincident", i, 2, (i + 1) % 4, 1))
    # fest wie bei Monitor Light (dort hängen die Ecken am projizierten Rand), sonst verzieht R5 das Rechteck
    for c in (("Horizontal", 0), ("Horizontal", 2), ("Vertical", 1), ("Vertical", 3), ("Coincident", 0, 1, -1, 1),
              ("Distance", 0, 40.0), ("Distance", 1, 10.0)):
        s.addConstraint(Sketcher.Constraint(*c))
    doc().recompute()


def half_circle():
    s = sketch()
    s.solve()
    lines = [g for g in s.Geometry if isinstance(g, Part.LineSegment) and g.length() < 1e-6]
    arcs = [round(g.Radius, 6) for g in s.Geometry if isinstance(g, Part.ArcOfCircle)]
    check("two R5 on a 10 mm side leave no zero-length line and no redundant constraints",
          not lines and arcs == [5, 5] and not s.RedundantConstraints and not s.ConflictingConstraints,
          "zero lines=%d arcs=%s redundant=%s" % (len(lines), arcs, s.RedundantConstraints))


def too_big():
    m = QtWidgets.QApplication.activeModalWidget()
    tips = [w.text() for w in QtWidgets.QApplication.allWidgets() if w.isVisible() and w.metaObject().className() == "QTipLabel"]
    check("a radius the sketch can't take keeps the field open and says why", m is not None and tips, "modal=%s tips=%s" % (m, tips))


def small_after_big():
    arcs = sorted(round(g.Radius, 6) for g in sketch().Geometry if isinstance(g, Part.ArcOfCircle))
    check("then a fitting radius rounds the corner", QtWidgets.QApplication.activeModalWidget() is None and arcs == [2, 5, 5], str(arcs))


in_order([
    ("activate", activate),
    ("sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick XY", lambda: Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XY_Plane")][0])), wait, wait,
    ("setup", setup), wait,
    ("fillet tool", lambda: Gui.runCommand("Sketcher_CreateFillet")), wait,
    ("corner", lambda: click_corner(40, 20)), wait, wait,
    ("dialog", dialog_open),
    ("shot", lambda: shot("fillet_dialog")),
    ("type", lambda: type_value("3")), wait,
    ("rounded", rounded),
    ("corner 2", lambda: click_corner(0, 0)), wait, wait,
    ("dialog 2", dialog_open),
    ("esc", esc), wait,
    ("undone", undone),
    ("slot", setup_slot), wait,
    ("top right", lambda: click_corner(40, 10)), wait, wait,
    ("r5", lambda: type_value("5")), wait,
    ("bottom right", lambda: click_corner(40, 0)), wait, wait,
    ("r5 again", lambda: type_value("5")), wait,
    ("half circle", half_circle),
    ("top left", lambda: click_corner(0, 10)), wait, wait,
    ("r30", lambda: type_value("30")), wait, ("too big", too_big),
    ("r2", lambda: type_value("2")), wait, ("small", small_after_big),
])
