# SPDX-License-Identifier: LGPL-2.1-or-later
"""Maß am Maß eintippen (Phase 11.1): nach dem Bemaßen erscheint statt der Karte "Insert Length" nur ein schlankes Feld
auf dem Maß (kein Titel, keine Knöpfe, keine Abdunklung), mittig an der Stelle, an der das Maß abgesetzt wurde.
Tab übernimmt und springt zum nächsten Maß der Skizze, Enter übernimmt, Esc verwirft."""
import shiboken6
from PySide6 import QtGui
from harness import *
import Sketcher

S = {}
W = ("wait", lambda: None)
V = App.Vector


def sk():
    return Gui.ActiveDocument.getInEdit().Object


def screen(p):
    vp = view().viewport(); dpr = vp.devicePixelRatioF()
    x, y = Gui.ActiveDocument.ActiveView.getPointOnViewport(sk().getGlobalPlacement().multVec(p))
    return QtCore.QPoint(int(x / dpr), int(vp.height() - y / dpr))


def press(p):
    vp = view().viewport(); q = screen(p); S["click"] = vp.mapToGlobal(q)
    QtGui.QCursor.setPos(S["click"])  # wie beim echten Klicken steht der Zeiger dort (QTest bewegt ihn nicht)
    for r in (q - QtCore.QPoint(1, 1), q):
        QtWidgets.QApplication.sendEvent(vp, QtGui.QMouseEvent(QtCore.QEvent.MouseMove, QtCore.QPointF(r), QtCore.QPointF(vp.mapToGlobal(r)),
                                                               QtCore.Qt.NoButton, QtCore.Qt.NoButton, QtCore.Qt.NoModifier))
    QtTest.QTest.mouseClick(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, q)


def lines():
    s = sk()
    s.addGeometry(Part.LineSegment(V(0, 0, 0), V(40, 0, 0)))
    s.addGeometry(Part.LineSegment(V(0, 10, 0), V(30, 10, 0)))
    s.addConstraint(Sketcher.Constraint("Distance", 1, 30.0))  # schon bemaßt: Tab landet hier
    doc().recompute()
    Gui.SendMsgToActiveView("ViewFit")


def dimension():
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(doc().Name, sk().Name, "Edge1")
    click(button("Sketcher_Dimension"))
    QtCore.QTimer.singleShot(300, lambda: press(V(20, -8, 0)))


def field():
    m = QtWidgets.QApplication.activeModalWidget()
    box = m.findChild(QtWidgets.QAbstractSpinBox) if m else None
    while box is not None and not shiboken6.isValid(box):
        shiboken6.invalidate(box); box = m.findChild(QtWidgets.QAbstractSpinBox)
    return m, box


def inline():
    m, box = field()
    buttons = [b for b in m.findChildren(QtWidgets.QPushButton) if b.isVisible()] if m else []
    near = (m.geometry().center() - S["click"]).manhattanLength() if m else -1
    check("after dimensioning only a slim field sits on the dimension (no title, no buttons)",
          m is not None and m.objectName() == "InlineDatum" and not m.windowTitle() and not buttons and box is not None,
          "%s title=%r buttons=%s" % (m and m.objectName(), m and m.windowTitle(), [b.text() for b in buttons]))
    check("the field is centred where the dimension was placed", 0 <= near < 120, "%d px away" % near)
    scrims = [w for w in mw.children() if isinstance(w, QtWidgets.QWidget) and w.isVisible()
              and w.geometry() == mw.rect() and w.testAttribute(QtCore.Qt.WA_TransparentForMouseEvents)]
    check("the window is not dimmed: you see what you dimension", not scrims, str(scrims))


def type_into(text, key):
    m, box = field()
    box.setFocus(); box.lineEdit().selectAll()
    QtTest.QTest.keyClicks(box, text)
    QtTest.QTest.keyClick(box, key)


def tabbed():
    m, box = field()
    check("Tab applies and opens the next dimension of the sketch", m is not None and m.objectName() == "InlineDatum"
          and abs(sk().Geometry[0].length() - 25) < 1e-6, "modal=%s first line %.3f" % (m and m.objectName(), sk().Geometry[0].length()))


def done():
    check("Enter applies the next one: both lines have the typed lengths",
          QtWidgets.QApplication.activeModalWidget() is None and abs(sk().Geometry[0].length() - 25) < 1e-6
          and abs(sk().Geometry[1].length() - 12) < 1e-6,
          "%.3f %.3f" % (sk().Geometry[0].length(), sk().Geometry[1].length()))


run([("activate", activate), ("sketch", lambda: click(button("Design_CreateSketch"))),
     ("pick XY", lambda: Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XY_Plane")][0])), W, W,
     ("lines", lines), W, ("dimension", dimension), W, W, ("inline", inline),
     ("25 tab", lambda: type_into("25", QtCore.Qt.Key_Tab)), W, W, ("tabbed", tabbed),
     ("12 enter", lambda: type_into("12", QtCore.Qt.Key_Return)), W, ("done", done)], delay=1500)
