# SPDX-License-Identifier: LGPL-2.1-or-later
"""Lange Timeline: bleibt im Fenster neben der Seitenleiste, die Wiedergabe-Knöpfe bleiben stehen, die Schritte rollen
(Mausrad) und der neueste bzw. der Marker ist im Bild."""
from harness import *
import Design

PLAY = ["Go to Start", "Step Back", "Step Forward", "Go to End"]


def play_button(i):
    return [b for b in timeline() if b.accessibleName() == PLAY[i]][0]


def scroll():
    step = steps()[-1]  # findChild lieferte nach dem Neuaufbau einen schon gelöschten Wrapper
    return [a for a in visible(QtWidgets.QScrollArea) if a.isAncestorOf(step)][0]


def panel_rect():
    """Glas-Panel der Timeline in Koordinaten der 3D-Ansicht (die Panels sind Proxys in deren Szene)"""
    box = play_button(0).parentWidget()
    return QtCore.QRect(view().viewport().mapFromGlobal(box.mapToGlobal(QtCore.QPoint(0, 0))), box.size())


def in_panel(w):
    box = play_button(0).parentWidget()
    return box.rect().contains(QtCore.QRect(w.mapTo(box, QtCore.QPoint(0, 0)), w.size()))


def in_view(w):
    """liegt w ganz im sichtbaren Teil der rollenden Schritte?"""
    vp = scroll().viewport()
    return vp.rect().contains(QtCore.QRect(w.mapTo(vp, QtCore.QPoint(0, 0)), w.size()))


def wheel(steps):
    vp = scroll().viewport(); p = QtCore.QPointF(vp.rect().center())
    ev = QtGui.QWheelEvent(p, QtCore.QPointF(vp.mapToGlobal(p.toPoint())), QtCore.QPoint(), QtCore.QPoint(0, 120 * steps),
                           QtCore.Qt.NoButton, QtCore.Qt.NoModifier, QtCore.Qt.NoScrollPhase, False)
    QtWidgets.QApplication.sendEvent(vp, ev)


def arrow(name):
    """Pfeile zum Rollen neben den Schritten (ohne Mausrad)"""
    found = [b for b in timeline() if b.accessibleName() == name]
    return found[0] if found else None


def arrows_at_end():
    e, l = arrow("Earlier Steps"), arrow("Later Steps")
    check("arrows to scroll are there when the steps don't fit; at the newest step only Earlier works",
          e is not None and l is not None and e.isVisible() and l.isVisible() and e.isEnabled() and not l.isEnabled(),
          "earlier=%s later=%s" % (e and (e.isVisible(), e.isEnabled()), l and (l.isVisible(), l.isEnabled())))


def build():
    for i in range(30):
        b = make_body(rect(i * 20, 0, i * 20 + 10, 10), 0, 5, "B%d" % i)
        Design.addToTimeline(b.Tip.Profile[0].Sketch); Design.addToTimeline(b.Tip)  # mit Wiedergabe-Knöpfen wie im echten Design
    Gui.SendMsgToActiveView("ViewFit")


def steps():
    """Schritte in Timeline-Reihenfolge (allWidgets ist ungeordnet)"""
    return sorted([b for b in timeline() if b.property("timelineIndex") is not None], key=lambda b: b.property("timelineIndex"))


state = {}
run([
    ("setup", build), ("wait", lambda: None),
    ("fits", lambda: check("long timeline stays inside the window, right of the sidebar",
                           panel_rect().left() >= 12 + 290 and panel_rect().right() <= view().viewport().width(),  # Abstand + BrowserWidth
                           "%s view=%d" % (panel_rect(), view().viewport().width()))),
    ("overflows", lambda: check("the steps are wider than the timeline and scroll", scroll().horizontalScrollBar().maximum() > 0,
                                str(scroll().horizontalScrollBar().maximum()))),
    ("play visible", lambda: check("play buttons stay at the left inside the timeline",
                                   all(in_panel(play_button(i)) for i in range(4)))),
    ("newest", lambda: check("the newest step is in view", in_view(steps()[-1]))),
    ("arrows", arrows_at_end),
    ("shot end", lambda: shot("end")),
    ("arrow click", lambda: (state.update(before=scroll().horizontalScrollBar().value()), click(arrow("Earlier Steps")))),
    ("wait", lambda: None),
    ("arrow scrolled", lambda: check("the Earlier arrow scrolls the steps back, Later works again",
                                     scroll().horizontalScrollBar().value() < state["before"] and arrow("Later Steps").isEnabled(),
                                     "%d -> %d" % (state["before"], scroll().horizontalScrollBar().value()))),
    ("wheel", lambda: (state.update(before=scroll().horizontalScrollBar().value()), wheel(5))),
    ("wheeled", lambda: check("the mouse wheel scrolls the steps sideways",
                              scroll().horizontalScrollBar().value() < state["before"],
                              "%d -> %d" % (state["before"], scroll().horizontalScrollBar().value()))),
    ("shot middle", lambda: shot("middle")),
    ("start", lambda: click(play_button(0))), ("wait", lambda: None),
    ("at start", lambda: check("rolling back to the start brings the marker into view", scroll().horizontalScrollBar().value() == 0,
                               str(scroll().horizontalScrollBar().value()))),
    ("arrow at start", lambda: check("at the start the Earlier arrow is dimmed", not arrow("Earlier Steps").isEnabled())),
    ("shot start", lambda: shot("start")),
    ("end", lambda: click(play_button(3))), ("wait", lambda: None),
    ("newest again", lambda: check("going to the end shows the newest step again", in_view(steps()[-1]))),
])
