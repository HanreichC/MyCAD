# SPDX-License-Identifier: LGPL-2.1-or-later
"""Phase 11.4 Messen ohne Werkzeug: zwei gewählte Flächen zeigen sofort ihren Abstand als kleine Karte daneben, zwei
sich berührende ihren Winkel, ein Zylinder seinen Durchmesser. Ein drittes Element, ein offenes Werkzeug oder eine
leere Auswahl schließen die Karte. Ein Klick auf den Wert öffnet die Parameter mit dem Wert, Name tippen, Enter legt an."""
from harness import *

S = {}
W = ("wait", lambda: None)


def face(pred):
    b = S["b"]
    return "Face%d" % (1 + next(i for i, f in enumerate(b.Shape.Faces) if pred(f.CenterOfMass, f)))


def pick(*names):
    Gui.Selection.clearSelection()
    for n in names:
        Gui.Selection.addSelection(S["b"], n)


def values():
    return [b.text() for b in visible(QtWidgets.QPushButton) if b.objectName() == "QuickMeasureValue"]


def setup():
    S["b"] = make_body(rect(0, 0, 20, 10), 0, 5, "Box")
    S["top"] = face(lambda c, f: abs(c.z - 5) < 1e-6)
    S["bottom"] = face(lambda c, f: abs(c.z) < 1e-6)
    S["front"] = face(lambda c, f: abs(c.y) < 1e-6)
    S["cyl"] = make_body([Part.Circle(App.Vector(40, 5, 0), App.Vector(0, 0, 1), 3)], 0, 5, "Pin")
    Gui.SendMsgToActiveView("ViewFit")


def distance():
    v = values()
    check("two parallel faces show their distance right away", v == ["5.00 mm"] or v == ["5 mm"], str(v))
    shot("distance")


def card_near():
    """die Karte steht unter der Mitte der kürzesten Verbindung (2,5 mm über dem Boden, mittig im Quader)"""
    w = [b for b in visible(QtWidgets.QPushButton) if b.objectName() == "QuickMeasureValue"][0]
    vp = view().viewport()
    p = Gui.ActiveDocument.ActiveView.getPointOnViewport(App.Vector(10, 5, 2.5))
    anchor = QtCore.QPoint(int(p[0] / vp.devicePixelRatioF()), int(vp.height() - p[1] / vp.devicePixelRatioF()))
    card = vp.mapFromGlobal(w.mapToGlobal(w.rect().center()))
    check("the card sits just below the measured spot", 0 < card.y() - anchor.y() < 80 and abs(card.x() - anchor.x()) < 80,
          "card=%s anchor=%s" % (card, anchor))


def angle():
    v = values()
    check("two touching faces show only their angle", v == ["∠ 90.00°"], str(v))


def diameter():
    Gui.Selection.clearSelection()
    side = 1 + next(i for i, f in enumerate(S["cyl"].Shape.Faces) if f.Surface.TypeId == "Part::GeomCylinder")
    Gui.Selection.addSelection(S["cyl"], "Face%d" % side)


def fill():
    d = [w for w in visible(QtWidgets.QDialog) if w.windowTitle() == "Parameters"]
    if not d:
        S["dialog"] = "no dialog"; return
    d = d[0]
    name, expr = [e for e in d.findChildren(QtWidgets.QLineEdit) if e.isVisible() and e.placeholderText()][:2]
    S["dialog"] = "value=%r name focused=%s" % (expr.text(), name.hasFocus())
    QtTest.QTest.keyClicks(name, "Thickness")
    QtTest.QTest.keyClick(name, QtCore.Qt.Key_Return)  # Enter legt an (Add ist Standard)
    S["added"] = [d.findChild(QtWidgets.QTableWidget).item(r, 0).text() for r in range(d.findChild(QtWidgets.QTableWidget).rowCount())]
    [b for b in d.findChildren(QtWidgets.QPushButton) if b.text().replace("&", "") == "OK"][0].click()


def use():
    QtCore.QTimer.singleShot(800, fill)
    [b for b in visible(QtWidgets.QPushButton) if b.objectName() == "QuickMeasureValue"][0].click()


def parameter():
    s = [o for o in doc().Objects if o.TypeId == "App::VarSet"]
    got = s and getattr(s[0], "Thickness", None)
    check("clicking the value opens Parameters with it filled in; a name and Enter add it",
          S.get("dialog") == "value='5 mm' name focused=True" and got is not None and abs(got.Value - 5) < 1e-9,
          "%s added=%s Thickness=%s" % (S.get("dialog"), S.get("added"), got))


run([("activate", activate), ("setup", setup), W,
     ("two faces", lambda: pick(S["top"], S["bottom"])), W, ("distance", distance), ("near", card_near),
     ("three faces", lambda: pick(S["top"], S["bottom"], S["front"])), W,
     ("three: none", lambda: check("a third element closes the card", values() == [], str(values()))),
     ("touching", lambda: pick(S["top"], S["front"])), W, ("angle", angle),
     ("one flat face", lambda: pick(S["top"])), W,
     ("flat: none", lambda: check("a single flat face shows nothing", values() == [], str(values()))),
     ("cylinder", diameter), W,
     ("diameter", lambda: check("a cylinder alone shows its diameter", values() in (["⌀ 6.00 mm"], ["⌀ 6 mm"]), str(values()))),
     ("tool", lambda: (pick(S["top"], S["bottom"]), Gui.runCommand("Design_Measure"))), W, W,
     ("tool: none", lambda: check("an open tool closes the card", values() == [], str(values()))),
     ("close tool", lambda: Gui.Control.closeDialog()), W,
     ("again", lambda: pick(S["top"], S["bottom"])), W,
     ("use", use), W, W, ("parameter", parameter),
     ("clear", lambda: Gui.Selection.clearSelection()), W,
     ("cleared", lambda: check("an empty selection closes the card", values() == [], str(values()))),
     ("errors", lambda: L("errors=%s" % errors())),
     ])
