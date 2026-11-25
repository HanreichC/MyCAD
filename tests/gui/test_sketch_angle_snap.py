# SPDX-License-Identifier: LGPL-2.1-or-later
"""Linie zeichnen mit eingeschaltetem Raster-Fangen: nahe 30° rastet der Winkel genau auf 30° ein (2026-11-25: mit Raster
rastete gar kein Winkel, das Raster sprang vor). Weit weg von einem 15°-Schritt bestimmt weiter das Raster."""
import math
from PySide6 import QtGui
from harness import *

V = App.Vector
wait = ("wait", lambda: None)
GRP = "User parameter:BaseApp/Preferences/Mod/Sketcher/Snap"


def sketch():
    return Gui.ActiveDocument.getInEdit().Object


def press(x, y):
    vp = view().viewport(); dpr = vp.devicePixelRatioF()
    px, py = Gui.ActiveDocument.ActiveView.getPointOnViewport(V(x, y, 0))
    p = QtCore.QPoint(int(px / dpr), int(vp.height() - py / dpr))
    for q in (p - QtCore.QPoint(1, 1), p):
        QtWidgets.QApplication.sendEvent(vp, QtGui.QMouseEvent(QtCore.QEvent.MouseMove, QtCore.QPointF(q), QtCore.QPointF(vp.mapToGlobal(q)), QtCore.Qt.NoButton, QtCore.Qt.NoButton, QtCore.Qt.NoModifier))
    QtTest.QTest.mouseClick(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)


def view_area():
    sketch().addGeometry(Part.LineSegment(V(-40, -40, 0), V(-40, 40, 0)))  # Bezug für den Ausschnitt, weit weg
    sketch().addGeometry(Part.LineSegment(V(60, -40, 0), V(60, 40, 0)))
    doc().recompute(); Gui.SendMsgToActiveView("ViewFit")


def angle():
    g = sketch().Geometry[-1]
    d = g.EndPoint - g.StartPoint
    a = math.degrees(math.atan2(d.y, d.x))
    check("near 30° the line snaps to exactly 30° with grid snapping on", abs(a - 30) < 1e-6, "%.4f°" % a)


in_order([
    ("grid on", lambda: App.ParamGet(GRP).SetBool("SnapToGrid", True)),
    ("activate", activate),
    ("sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick XY", lambda: Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XY_Plane")][0])), wait, wait,
    ("area", view_area), wait,
    ("line tool", lambda: click(button("Sketcher_CreateLine"))), wait,
    ("start", lambda: press(0, 0)), wait,
    ("end", lambda: press(30 * math.cos(math.radians(31.3)), 30 * math.sin(math.radians(31.3)))), wait,
    ("esc", lambda: QtTest.QTest.keyClick(view().viewport(), QtCore.Qt.Key_Escape)), wait,
    ("angle", angle),
    ("grid off", lambda: App.ParamGet(GRP).SetBool("SnapToGrid", False)),
])
