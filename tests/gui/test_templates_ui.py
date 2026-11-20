# SPDX-License-Identifier: LGPL-2.1-or-later
"""12.11 Startseite: "New from Template" zeigt die fünf Vorlagen; "Spacer" öffnet ein neues Design mit dem Körper und
der Notiz seiner Maße; eine geänderte Notiz-Zeile ändert die Länge"""
import harness
from harness import *
import Design

harness.START_PAGE = True
S = {}
W = ("wait", lambda: None)


def page():
    return [w for w in mw.findChildren(QtWidgets.QWidget, "StartPage")][0]


def choose(entry):
    """echter Klick auf den Knopf, echter Klick auf den Menüpunkt (das Menü blockiert modal: vorher einplanen)"""
    def pick():
        m = visible(QtWidgets.QMenu)[0]
        S["menu"] = [a.text() for a in m.actions() if a.text()]
        r = m.actionGeometry([a for a in m.actions() if a.text() == entry][0])
        QtTest.QTest.mouseMove(m.windowHandle(), r.center())
        QtTest.QTest.mouseClick(m.windowHandle(), QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, r.center())
    QtCore.QTimer.singleShot(600, pick)
    [b for b in page().findChildren(QtWidgets.QToolButton, "TemplateButton")][0].click()


def opened():
    d = App.ActiveDocument
    bodies = [o for o in d.Objects if o.TypeId == "Design::Body"] if d else []
    notes = [o for o in d.Objects if o.TypeId == "Design::Note"] if d else []
    S["note"], S["body"] = (notes or [None])[0], (bodies or [None])[0]
    check("Spacer opens a new design with its body and the note of its sizes",
          d is not None and d.Label == "Spacer" and len(bodies) == 1 and bool(notes) and "Length = 15 mm" in notes[0].Text
          and not page().isVisible(), "%s %s %s" % (d and d.Label, len(bodies), notes and notes[0].Text))


def longer():
    n = S["note"]
    n.Text = n.Text.replace("Length = 15 mm", "Length = 30 mm")
    Design.syncNoteParameters(n)
    doc().recompute()
    check("a note line changes the design", abs(S["body"].Shape.BoundBox.ZLength - 30) < 1e-6, str(S["body"].Shape.BoundBox))


in_order([
     ("page", lambda: check("the start page is shown", page().isVisible())),
     ("template", lambda: choose("Spacer")), W, W,
     ("menu", lambda: check("five templates in the menu", S.get("menu") == ["Box with Lid", "Wall Bracket", "PCB Enclosure",
                                                                           "Spacer", "Cable Clip"], str(S.get("menu")))),
     ("opened", opened),
     ("longer", longer),
     ("errors", lambda: check("no errors", not errors(), str(errors()))),
     ])
