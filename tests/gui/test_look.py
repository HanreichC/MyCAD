# SPDX-License-Identifier: LGPL-2.1-or-later
"""Optik: Screenshots von Modell- und Sketch-Modus (Icons, ViewCube, Finish Sketch)."""
from harness import *


def setup():
    make_body(rect(0, 0, 60, 40), 0, 15, "Box")
    Gui.ActiveDocument.ActiveView.viewIsometric(); Gui.SendMsgToActiveView("ViewFit")


def pixel_in_tree(tree, x, y):
    """Farbe im fertigen Fensterbild an einer Stelle des Browsers"""
    top = tree
    while top.parentWidget():
        top = top.parentWidget()
    proxy = top.graphicsProxyWidget()
    p = view().mapFromScene(proxy.mapToScene(QtCore.QPointF(tree.viewport().mapTo(top, QtCore.QPoint(x, y)))))
    return mw.grab().toImage().pixelColor(view().mapTo(mw, p))


def blue(c):
    return c.blue() > 200 and c.blue() > c.red() + 80


def select_box():
    Gui.Selection.addSelection(body("Box"))
    visible(QtWidgets.QTreeWidget)[0].expandAll()


def selected_row():
    """Auswahl im Browser färbt nur die Zeile, nicht die Einrückung links davon"""
    tree = visible(QtWidgets.QTreeWidget)[0]
    rect = tree.visualItemRect(tree.findItems("Box", QtCore.Qt.MatchExactly | QtCore.Qt.MatchRecursive)[0])
    y = rect.center().y()
    row, left = pixel_in_tree(tree, rect.left() + 72, y), pixel_in_tree(tree, rect.left() - 30, y)
    L("%s selected row only: row %s, left of it %s" % ("ok  " if blue(row) and not blue(left) else "FAIL", row.name(), left.name()))
    Gui.Selection.clearSelection()


run([
    ("setup", setup),
    ("extrude timeline entry", lambda: None),
    ("select", select_box),
    ("wait", lambda: None),
    ("selected row", selected_row),
    ("shot model", lambda: shot("model")),
    ("Create Sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick top", lambda: Gui.Selection.addSelection(body("Box"), top_face(body("Box")))),
    ("shot sketch", lambda: shot("sketch")),
    ("finish", lambda: click(button("Sketcher_LeaveSketch"))),
    ("in edit after finish", lambda: L("edit=%s" % (Gui.ActiveDocument.getInEdit() is not None))),
])
