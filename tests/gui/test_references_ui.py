# SPDX-License-Identifier: LGPL-2.1-or-later
"""Phase 11.11 Bezüge prüfen: ohne Unsicheres sagt das Panel, dass alles sicher ist; ein Schritt mit Warnung steht als
Zeile da, Zeigen wählt die betroffenen Kanten, Stimmt so bestätigt und die Liste ist wieder leer; Bearbeiten öffnet den
Schritt."""
from harness import *

S = {}
W = ("wait", lambda: None)


def rows():
    return [w for w in visible(QtWidgets.QWidget) if w.objectName() == "ReferenceIssue"]


def panel_text():
    p = [w for w in visible(QtWidgets.QWidget) if w.objectName() == "References"]
    return " ".join(l.text() for l in p[0].findChildren(QtWidgets.QLabel)) if p else ""


def button_in_row(text):
    return [b for b in rows()[0].findChildren(QtWidgets.QPushButton) if b.text() == text][0]


def setup():
    S["b"] = make_body(rect(0, 0, 30, 20), 0, 10, "Box")
    S["f"] = S["b"].Tip


def certain():
    check("with nothing uncertain the panel says so", not rows() and "All references are certain" in panel_text(), panel_text())


def warn():
    Gui.Control.closeDialog()
    S["f"].Warning = "The model changed under this step; check that it still uses the right edges or faces: Edge3"
    S["f"].ErrorElements = ["Edge3"]


def listed():
    check("a step with a warning is listed with Show, Edit and Looks Right",
          len(rows()) == 1 and S["f"].Label in panel_text() and "right edges or faces" in panel_text(), panel_text())
    names = sorted(b.text() for b in rows()[0].findChildren(QtWidgets.QPushButton)) if rows() else []
    check("its buttons", names == ["Edit", "Looks Right", "Show"], str(names))
    shot("listed")


def shown():
    sel = [(s.ObjectName, n) for s in Gui.Selection.getSelectionEx() for n in s.SubElementNames]
    check("Show selects the edges concerned on the body", (S["b"].Name, "Edge3") in sel, str(sel))


def confirmed():
    check("Looks Right clears the warning and the list", S["f"].Warning == "" and not rows()
          and "All references are certain" in panel_text(), "warning=%r text=%s" % (S["f"].Warning, panel_text()))


def edit_opens():
    check("Edit closes the list and opens the step", Gui.Control.activeDialog() and not panel_text(),
          "dialog=%s" % Gui.Control.activeDialog())


run([("activate", activate), ("setup", setup), W,
     ("check", lambda: Gui.runCommand("Design_CheckReferences")), W, ("certain", certain),
     ("warn", warn), W, ("check again", lambda: Gui.runCommand("Design_CheckReferences")), W, ("listed", listed),
     ("show", lambda: click(button_in_row("Show"))), W, ("shown", shown),
     ("looks right", lambda: click(button_in_row("Looks Right"))), W, W, ("confirmed", confirmed),
     ("warn 2", warn), W, ("check 3", lambda: Gui.runCommand("Design_CheckReferences")), W,
     ("edit", lambda: click(button_in_row("Edit"))), W, W, ("edit opens", edit_opens),
     ("cancel", lambda: Gui.Control.closeDialog()), W,
     ])
