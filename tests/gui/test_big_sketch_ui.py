# SPDX-License-Identifier: LGPL-2.1-or-later
"""Leistungsgrenzen in einer großen Skizze (10.000 Elemente wie ein Platinen-DXF): eine Mausbewegung (Vorauswahl,
ohne Zeichnen, gilt so auch unter Xvfb) und der Klick, der eine Linie anlegt. Gemessen am Desktop: 8 ms und 0,5 s;
die Grenzen haben Reserve für eine ausgelastete CI, brechen aber bei quadratischen Stellen (vorher 450 ms, 13 s)."""
import math
import os
import sys
import time
from harness import *
import harness
from PySide6 import QtGui
import Design

# relativ (CI: /workspace) und im Container des Desktops (dort ist nur tests/gui eingebunden, das Repo als /workspace)
sys.path += [os.path.join(os.path.dirname(harness.__file__), "..", "design"), "/workspace/tests/design"]
from test_big_sketch import pcb_like  # noqa: E402

state = {}


def vp():
    return view().viewport()


def move(p):
    QtWidgets.QApplication.sendEvent(vp(), QtGui.QMouseEvent(
        QtCore.QEvent.MouseMove, QtCore.QPointF(p), QtCore.QPointF(vp().mapToGlobal(p)),
        QtCore.Qt.NoButton, QtCore.Qt.NoButton, QtCore.Qt.NoModifier))


def setup():
    sk = Design.newSketch(Design.root(doc()))
    state["n"] = pcb_like(sk)
    doc().recompute()
    state["sketch"] = sk
    Gui.ActiveDocument.setEdit(sk)


def fit():
    Gui.SendMsgToActiveView("ViewFit")


def hover():
    w, h = vp().width(), vp().height()
    t = time.monotonic()
    for i in range(40):
        a = i * 0.15
        move(QtCore.QPoint(int(w * 0.5 + 80 * math.cos(a)), int(h * 0.5 + 80 * math.sin(a))))
    ms = (time.monotonic() - t) / 40 * 1000
    check("mouse move in a 10,000-element sketch under 30 ms", ms < 30, "%.1f ms" % ms)


def tool():
    Gui.runCommand("Sketcher_CreateLine")


def click(fx, fy):
    p = QtCore.QPoint(int(vp().width() * fx), int(vp().height() * fy))
    move(p)
    QtWidgets.QApplication.processEvents()
    t = time.monotonic()
    QtTest.QTest.mouseClick(vp(), QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)
    QtWidgets.QApplication.processEvents()
    return time.monotonic() - t


def first():
    click(0.45, 0.48)


def second():
    s = click(0.55, 0.52)
    added = len(state["sketch"].Geometry) - state["n"]
    check("clicking a line into a 10,000-element sketch under 1.5 s", added == 1 and s < 1.5, "%.2f s, %d added" % (s, added))


def leave():
    QtTest.QTest.keyClick(vp(), QtCore.Qt.Key_Escape)
    QtTest.QTest.keyClick(vp(), QtCore.Qt.Key_Escape)


in_order([("setup", setup), ("fit", fit), ("hover", hover), ("tool", tool), ("first", first), ("second", second),
          ("leave", leave)], delay=800)
