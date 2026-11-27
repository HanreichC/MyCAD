# SPDX-License-Identifier: LGPL-2.1-or-later
"""Strg+C / Strg+V an einem Körper wie in Fusion (Christopher 27.11.): kein FreeCAD-Dialog zu Abhängigkeiten, eingefügt
wird ein fester Körper mit dem Material des Originals als Schritt in der Zeitleiste, Verschieben öffnet gleich. Die Kopie
hängt nicht am Original; Rückgängig nimmt Verschieben und Einfügen zurück."""
from harness import *
import Design

S = {"dialogs": []}
W = ("wait", lambda: None)


def vp(obj):
    return Gui.ActiveDocument.getObject(obj.Name)


def rgb(obj):
    return tuple(round(c, 3) for c in vp(obj).ShapeAppearance[0].DiffuseColor[:3])


def bodies():
    return [o for o in doc().Objects if o.TypeId == "Design::Body"]


def tile(name):
    [b for b in visible(QtWidgets.QToolButton) if b.accessibleName() == name][0].click()


def setup():
    S["body"] = make_body(rect(0, 0, 40, 30), 0, 10, "Plate")
    S["ext"] = [o for o in doc().Objects if o.TypeId == "Design::Extrude"][0]
    Design.addToTimeline([o for o in doc().Objects if o.TypeId == "Sketcher::SketchObject"][0])
    Design.addToTimeline(S["ext"])  # wie über die Oberfläche: das Design hat eine Zeitleiste
    Gui.ActiveDocument.ActiveView.viewIsometric()
    Gui.SendMsgToActiveView("ViewFit")


def select_body():
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(S["body"])


def key(k):
    def go():
        activate()
        view().viewport().setFocus()
        QtTest.QTest.keyClick(mw.windowHandle(), k, QtCore.Qt.ControlModifier)
    return go


def no_dialog():
    """ein modaler Dialog (FreeCADs Abhängigkeiten) wäre jetzt offen: merken und schließen"""
    for d in visible(QtWidgets.QDialog):
        S["dialogs"].append(d.windowTitle())
        d.reject()


def pasted():
    new = [o for o in bodies() if o != S["body"]]
    S["copy"] = new[0] if new else None
    c = S["copy"]
    check("Ctrl+C, Ctrl+V asks nothing and pastes one body", len(new) == 1 and not S["dialogs"],
          "%s dialogs %s" % ([o.Label for o in new], S["dialogs"]))
    if not c:
        return
    check("the copy is named after the original", c.Label == "Plate Copy", c.Label)
    check("it has the shape and the walnut of the original", abs(c.Shape.Volume - 12000) < 1e-6 and rgb(c) == S["walnut"],
          "%s %s" % (c.Shape.Volume, rgb(c)))
    step = [o for o in Design.timeline(doc()) if o.TypeId == "Design::Import" and c in o.Bodies]
    check("it is one step in the timeline", len(step) == 1 and step[0].TypeId == "Design::Import",
          str([(o.Label, o.TypeId) for o in Design.timeline(doc())]))
    check("no sketch or extrude was copied along",
          len([o for o in doc().Objects if o.TypeId in ("Sketcher::SketchObject", "Design::Extrude")]) == 2,
          str([o.Label for o in doc().Objects]))
    check("Move is open for the copy", Gui.Control.activeDialog(), "no panel")


def moved():
    c = S["copy"]
    check("the copy moved 60 mm, the original stayed", c and abs(c.Shape.BoundBox.XMin - 60) < 1e-6
          and abs(S["body"].Shape.BoundBox.XMin) < 1e-6, "%s %s" % (c and c.Shape.BoundBox, S["body"].Shape.BoundBox))


def longer():
    S["ext"].Distance = 20
    doc().recompute()


run([("activate", activate), ("setup", setup), W, W,
     ("select", select_body), ("appearance", lambda: Gui.runCommand("Design_Appearance")), W,
     ("walnut", lambda: tile("Walnut")), W, ("ok", ok), W, ("remember", lambda: S.__setitem__("walnut", rgb(S["body"]))),
     ("select 2", select_body), ("copy", key(QtCore.Qt.Key_C)), W, ("no dialog", no_dialog),
     ("paste", key(QtCore.Qt.Key_V)), W, W, ("no dialog 2", no_dialog), ("pasted", pasted),
     ("x 60", lambda: type_into(0, "60 mm")), W, ("ok move", ok), W, W, ("moved", moved),
     ("longer", longer), W,
     ("own", lambda: check("the copy does not follow the original", abs(S["copy"].Shape.Volume - 12000) < 1e-6
                           and abs(S["body"].Shape.Volume - 24000) < 1e-6, "%s %s" % (S["copy"].Shape.Volume, S["body"].Shape.Volume))),
     ("undo", lambda: (Gui.runCommand("Std_Undo"), Gui.runCommand("Std_Undo"), Gui.runCommand("Std_Undo"))), W, W,
     ("undone", lambda: check("Undo takes back the move and the paste", len(bodies()) == 1, str([o.Label for o in bodies()]))),
     ("errors", lambda: check("no errors", not errors(), str(errors()))),
     ])
