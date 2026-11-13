# SPDX-License-Identifier: LGPL-2.1-or-later
"""10.3 Idee 2 in der Oberfläche: ein Klick wählt die Fläche nur, ein Doppelklick zeigt ihre Maße am Modell, Enter
rechnet neu, Strg+Z nimmt es zurück, ohne Auswahl verschwindet die Karte"""
from harness import *

state = {}


def card_fields():
    return [b for b in visible(QtWidgets.QAbstractSpinBox)
            if b.parentWidget() and b.parentWidget().objectName() == "FaceDimensions"]


def top_point():
    """Mitte der Oberseite in Viewport-Koordinaten"""
    bb = state["box"].Shape.BoundBox
    p = Gui.ActiveDocument.ActiveView.getPointOnViewport(App.Vector(bb.Center.x, bb.Center.y, bb.ZMax))
    vp = view().viewport(); dpr = vp.devicePixelRatioF()
    return QtCore.QPoint(int(p[0] / dpr), int(vp.height() - p[1] / dpr))


def click_top(double):
    vp, p = view().viewport(), top_point()
    QtTest.QTest.mouseMove(vp, p)
    QtTest.QTest.mouseClick(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)
    if double:
        QtTest.QTest.mouseDClick(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)
        QtTest.QTest.mouseRelease(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)


def card_size():
    f = card_fields()
    return (f[0].parentWidget().width(), f[0].parentWidget().height()) if f else None


def selected():
    return [(s.ObjectName, n) for s in Gui.Selection.getSelectionEx() for n in s.SubElementNames]


def enter_value(text, key=QtCore.Qt.Key_Return):
    box = card_fields()[0]
    box.setFocus()
    box.lineEdit().selectAll(); QtTest.QTest.keyClicks(box.lineEdit(), text)
    QtTest.QTest.keyClick(box.lineEdit(), key)


def card_error():
    return [l.text() for l in visible(QtWidgets.QLabel) if l.parentWidget() and l.parentWidget().objectName() == "FaceDimensions"
            and l.text() and l.buddy() is None]


def broken():
    return [o.Name for o in doc().Objects if "Invalid" in o.State]


run([
    ("setup", lambda: state.update(box=make_body(rect(0, 0, 20, 10), 0, 5, "Box"))),
    ("fit", lambda: (Gui.Selection.clearSelection(), Gui.ActiveDocument.ActiveView.viewIsometric(), Gui.SendMsgToActiveView("ViewFit"))),
    ("click", lambda: click_top(False)),
    ("only selects", lambda: check("a single click selects the face but shows no card",
                                   selected() == [(state["box"].Name, top_face(state["box"]))] and not card_fields(), str(selected()))),
    ("dclick", lambda: (click_top(True), QtCore.QTimer.singleShot(0, lambda: state.update(first=card_size())))),
    ("full size at once", lambda: check("the card has its full size from the first frame (it used to grow one frame later)",
                                        state.get("first") == card_size(), "%s then %s" % (state.get("first"), card_size()))),
    ("card", lambda: check("double-clicking the top face shows its distance", [b.accessibleName() for b in card_fields()] == ["Distance"],
                           str([b.accessibleName() for b in card_fields()]))),
    ("shot", lambda: shot("card")),
    ("type", lambda: enter_value("12")),
    ("changed", lambda: check("enter changes the model", abs(body("Box").Shape.Volume - 2400) < 1e-6, str(body("Box").Shape.Volume))),
    ("undo", lambda: Gui.runCommand("Std_Undo")),
    ("undone", lambda: check("ctrl+z takes it back", abs(body("Box").Shape.Volume - 1000) < 1e-6, str(body("Box").Shape.Volume))),
    ("card undone", lambda: check("the open card shows the undone value", [b.text() for b in card_fields()] == ["5.00 mm"],
                                  str([b.text() for b in card_fields()]))),
    ("zero", lambda: enter_value("0")),
    ("rejected", lambda: check("0 is rejected: model unchanged, error in the card, no red step",
                               abs(body("Box").Shape.Volume - 1000) < 1e-6 and card_error() == ["Distance must be greater than zero"]
                               and not broken(), "%s %s %s" % (body("Box").Shape.Volume, card_error(), broken()))),
    ("esc", lambda: enter_value("33", QtCore.Qt.Key_Escape)),
    ("esc closes", lambda: check("Esc closes the card without changing the model",
                                 not card_fields() and abs(body("Box").Shape.Volume - 1000) < 1e-6, str(body("Box").Shape.Volume))),
    ("clear", lambda: Gui.Selection.clearSelection()),
    ("gone", lambda: check("without a selected face the card disappears", not card_fields())),
    # Die Karte lebt in der Szene des Designs: schließt es, stirbt sie mit (früher Absturz beim nächsten Doppelklick)
    ("dclick 2", lambda: click_top(True)), ("card 2", lambda: check("card open again", bool(card_fields()))),
    ("close", lambda: App.closeDocument(doc().Name)), ("new", lambda: Gui.runCommand("Std_New")),
    ("setup 2", lambda: state.update(box=make_body(rect(0, 0, 20, 10), 0, 5, "Box"))),
    ("fit 2", lambda: (Gui.Selection.clearSelection(), Gui.ActiveDocument.ActiveView.viewIsometric(), Gui.SendMsgToActiveView("ViewFit"))),
    ("dclick 3", lambda: click_top(True)),
    ("card 3", lambda: check("after closing a design the card works in the next one (no crash)",
                             [b.accessibleName() for b in card_fields()] == ["Distance"], str([b.accessibleName() for b in card_fields()]))),
])
