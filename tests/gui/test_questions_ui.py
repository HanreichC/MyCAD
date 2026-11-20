# SPDX-License-Identifier: LGPL-2.1-or-later
"""12.9 Fragen ans Modell in Strg+K: "Was hängt daran?" mit gewählter Skizze nennt und wählt die Extrusion;
"Warum ist das rot?" nennt die Rundung, die nicht rechnet, und wählt sie; ohne Fehler: "Nichts ist rot\""""
import Design
from harness import *

S = {}
W = ("wait", lambda: None)


def field():
    return [e for e in visible(QtWidgets.QLineEdit) if e.accessibleName() == "Search"][0]


def results():
    lists = [l for l in visible(QtWidgets.QListWidget) if l.accessibleName() == "Results"]
    return [lists[0].item(i).data(QtCore.Qt.AccessibleTextRole) for i in range(lists[0].count())] if lists else []


def ask(text):
    Gui.runCommand("MyCAD_Search")
    f = field(); f.clear(); f.insert(text)  # keyClicks kann keine Umlaute


def first_hit(want):
    r = results()
    check("understood: " + want, bool(r) and r[0] == want, str(r[:3]))


def enter():
    QtTest.QTest.keyClick(field(), QtCore.Qt.Key_Return)


def setup():
    S["body"] = make_body(rect(0, 0, 40, 30), 0, 10, "Plate")
    S["sketch"] = [o for o in doc().Objects if o.TypeId == "Sketcher::SketchObject"][0]
    S["extrude"] = [o for o in doc().Objects if o.TypeId == "Design::Extrude"][0]
    Gui.SendMsgToActiveView("ViewFit")


def pick_sketch():
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(S["sketch"])


def break_it():
    """Rundung R50 an einer 10 mm hohen Platte: rechnet nicht"""
    f = doc().addObject("Design::Fillet", "Fillet")
    Design.componentOf(S["body"]).addObject(f)
    Design.addToTimeline(f)
    f.Edges = ["Edge1"]
    f.Size = 50
    Design.attachToBodies(f, [S["body"]])
    doc().recompute()
    S["fillet"] = f
    Gui.Selection.clearSelection()


def selected():
    return [s.Object for s in Gui.Selection.getSelectionEx()]


run([("activate", activate), ("setup", setup), W,
     ("nothing", lambda: (Gui.Selection.clearSelection(), ask("Warum ist das rot?"))), W,
     ("why hit", lambda: first_hit("Explain what is red or wrong")),
     ("enter 1", enter), W, W,
     ("healthy", lambda: check("a healthy design: nothing is red", any("Nothing is red" in n for n in notices()), str(notices()))),
     ("sketch", pick_sketch), ("depends", lambda: ask("Was hängt daran?")), W,
     ("depends hit", lambda: first_hit("Show what uses the selection")),
     ("enter 2", enter), W, W,
     ("users", lambda: check("the extrude uses the sketch: named and selected",
                             S["extrude"] in selected() and any("is used by" in n and S["extrude"].Label in n for n in notices()),
                             "%s %s" % ([o.Name for o in selected()], notices()))),
     ("break", break_it), W,
     ("why", lambda: ask("why is this red?")), W,
     ("enter 3", enter), W, W,
     ("named", lambda: check("the fillet that does not compute is named and selected",
                             S["fillet"] in selected() and any(S["fillet"].Label in n for n in notices()),
                             "%s %s" % ([o.Name for o in selected()], notices()))),
     ("errors", lambda: check("no errors", not [e for e in errors() if "Fillet" not in e], str(errors()))),
     ])
