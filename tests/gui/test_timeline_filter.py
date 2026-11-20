# SPDX-License-Identifier: LGPL-2.1-or-later
"""12.13 Timeline: beim Überfahren eines Schritts leuchtet sein Körper im Modell auf (Vorauswahl); ist ein Körper
gewählt, treten die Schritte der anderen Körper zurück, ohne Auswahl zeigt die Timeline wieder alles gleich"""
from harness import *

S = {}
W = ("wait", lambda: None)


def setup():
    S["a"] = make_body(rect(0, 0, 20, 20), 0, 10, "Left")
    S["b"] = make_body(rect(40, 0, 60, 20), 0, 10, "Right")
    Gui.SendMsgToActiveView("ViewFit")


def step_of(body):
    """Timeline-Knopf der Extrusion, die body erzeugt"""
    return [b for b in timeline() if body.Name in (b.property("bodies") or []) and b.property("timelineObject") == body.Tip.Name][0]


def faded():
    return sorted(b.property("timelineObject") for b in timeline() if b.property("faded"))


def pick_left():
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(S["a"])


def filtered():
    right = [b.property("timelineObject") for b in timeline() if S["b"].Name in (b.property("bodies") or [])]
    check("with Left selected the steps of Right fade, Left's stay", sorted(right) == faded() and right
          and not step_of(S["a"]).property("faded"), "faded=%s right=%s" % (faded(), right))


def hover():
    btn = step_of(S["b"])
    QtWidgets.QApplication.sendEvent(btn, QtGui.QEnterEvent(QtCore.QPointF(5, 5), QtCore.QPointF(5, 5),
                                                            QtCore.QPointF(btn.mapToGlobal(QtCore.QPoint(5, 5)))))
    pre = Gui.Selection.getPreselection()
    check("hovering a step lights up its body in the model", pre.Object is not None and pre.Object.Name == S["b"].Name,
          str(pre.Object and pre.Object.Name))
    QtWidgets.QApplication.sendEvent(btn, QtCore.QEvent(QtCore.QEvent.Leave))
    pre = Gui.Selection.getPreselection()  # ohne Vorauswahl: leerer Name (.Object würde werfen)
    check("leaving it clears the light", not pre.ObjectName, repr(pre.ObjectName))


run([("activate", activate), ("setup", setup), W,
     ("left", pick_left), W, ("filtered", filtered),
     ("shot", lambda: shot("filter")),
     ("clear", lambda: Gui.Selection.clearSelection()), W,
     ("all", lambda: check("without a selected body nothing fades", not faded(), str(faded()))),
     ("hover", hover),
     ("errors", lambda: check("no errors", not errors(), str(errors()))),
     ])
