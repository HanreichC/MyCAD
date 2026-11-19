# SPDX-License-Identifier: LGPL-2.1-or-later
"""Kontext-Leiste (Plan 12.2): die Werkzeuge, die zur Auswahl passen, schweben über ihr. Ebene Fläche → Press Pull,
Skizze, Bohrung, Shell, Aussehen; Kante → Rundung, Fase; ganzer Körper → Bewegen …; ein Klick startet das Werkzeug mit
der Auswahl, die Leiste verschwindet. Leere Auswahl, offenes Werkzeug oder Einstellung aus: keine Leiste.
Fehler stehen als FAIL im Protokoll."""
from harness import *

grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")
grp.SetBool("ContextBar", True)
state = {}


def bar():
    """Knöpfe der Kontext-Leiste, von links nach rechts"""
    found = [b for b in visible(QtWidgets.QToolButton) if b.property("contextBar")]
    return sorted(found, key=lambda b: b.mapToGlobal(QtCore.QPoint(0, 0)).x())


def commands():
    return [b.property("command") for b in bar()]


def setup():
    state["box"] = make_body(rect(0, 0, 60, 40), 0, 15, "Box")
    Gui.SendMsgToActiveView("ViewFit")


def select(sub, point):
    Gui.Selection.clearSelection()
    b = state["box"]
    Gui.Selection.addSelection(doc().Name, b.Name, sub, *point)


def face():
    select(top_face(state["box"]), (30, 20, 15))


def check_face():
    check("flat face: Press Pull, Sketch, Hole, Shell, Appearance, Search",
          commands() == ["Design_PressPull", "Design_CreateSketch", "Design_Hole", "Design_Shell", "Design_Appearance", "MyCAD_Search"],
          str(commands()))
    # nie auf dem angeklickten Punkt (sonst trifft der zweite Klick eines Doppelklicks die Leiste statt der Fläche):
    # dort darf kein Szenen-Element liegen, die Leiste aber schon zu sehen sein
    vp = view().viewport(); dpr = vp.devicePixelRatioF()
    q = Gui.ActiveDocument.ActiveView.getPointOnViewport(App.Vector(30, 20, 15))  # Coin: y von unten, Gerätepixel
    p = QtCore.QPoint(int(q[0] / dpr), int(vp.height() - q[1] / dpr))
    on_point = vp.parentWidget().itemAt(p)
    check("the bar floats near the clicked point but never on it", bool(bar()) and on_point is None,
          "item at %s: %s" % ((p.x(), p.y()), type(on_point).__name__ if on_point else None))
    for b in bar():
        check("button %s has a name and a tooltip" % b.property("command"), bool(b.accessibleName()) and bool(b.toolTip()))
    shot("face")


def edge():
    e = state["box"].Shape.Edges
    k = max(range(len(e)), key=lambda i: e[i].CenterOfMass.z)  # eine obere Kante
    state["edge"] = "Edge%d" % (k + 1)
    c = e[k].CenterOfMass
    select(state["edge"], (c.x, c.y, c.z))


def check_edge():
    check("edge: Fillet, Chamfer, Search", commands() == ["Design_Fillet", "Design_Chamfer", "MyCAD_Search"], str(commands()))


def click_fillet():
    [b for b in bar() if b.property("command") == "Design_Fillet"][0].click()


def check_fillet():
    check("clicking Fillet starts it with the edge, the bar goes away",
          Gui.Control.activeDialog() and not bar(), "dialog=%s bar=%s" % (Gui.Control.activeDialog(), commands()))
    esc()  # abbrechen wie ein Benutzer (closeDialog allein beendet den Bearbeitungsmodus nicht)


def body():
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(state["box"])


def check_body():
    check("whole body (as from the browser): Move, Mirror, Pattern, Shell, Appearance, Search",
          commands() == ["Design_Move", "Design_Mirror", "Design_Pattern", "Design_Shell", "Design_Appearance", "MyCAD_Search"],
          str(commands()))


def check_cleared():
    Gui.Selection.clearSelection()


def off():
    grp.SetBool("ContextBar", False)
    face()


in_order([
    ("setup", setup), ("wait", lambda: None),
    ("face", face), ("wait", lambda: None),
    ("check face", check_face),
    ("edge", edge), ("wait", lambda: None),
    ("check edge", check_edge),
    ("fillet", click_fillet), ("wait", lambda: None),
    ("check fillet", check_fillet), ("wait", lambda: None),
    ("body", body), ("wait", lambda: None),
    ("check body", check_body),
    ("clear", check_cleared), ("wait", lambda: None),
    ("cleared", lambda: check("nothing selected: no bar", not bar(), str(commands()))),
    ("off", off), ("wait", lambda: None),
    ("check off", lambda: check("setting off: no bar", not bar(), str(commands()))),
    ("restore", lambda: grp.SetBool("ContextBar", True)),
])
