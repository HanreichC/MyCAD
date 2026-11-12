# SPDX-License-Identifier: LGPL-2.1-or-later
"""10.8 Idee 1 in der Oberfläche: Rotstift öffnet ein Korrektur-Scribble (Transparentpapier, Blatt zur Kamera);
Korrektur-Karten (wie aus der Tinte gelesen): Zeigen hebt das Ziel hervor, Ausführen legt das Feature an, bei gleich
nahen Kanten wird gewählt, Strg+Z nimmt es zurück"""
import os
import sys
from harness import *
import harness
import Design
import DesignGui

sys.path.append(os.path.join(os.path.dirname(harness.__file__), "..", "design"))
import design  # noqa: E402

state = {}
DOWN = App.Vector(0, 0, -1)
wait_step = ("wait", lambda: None)


def setup():
    _, b = design.box(doc(), 20, 20, 10)
    for o in doc().Objects:
        if o.TypeId == "Sketcher::SketchObject":
            o.Visibility = False
    state["body"] = b
    Gui.SendMsgToActiveView("ViewAxo")
    Gui.SendMsgToActiveView("ViewFit")


def cards():
    DesignGui.showCorrections(doc(), [("R2", App.Vector(10, -2, 30), DOWN), ("R1", App.Vector(10, 10, 30), DOWN),
                                      ("Hallo", App.Vector(0, 0, 30), DOWN)])


def panel_shown():
    return any(w.objectName() == "Corrections" for w in visible(QtWidgets.QWidget))


def apply_button(text):
    return [b for b in visible(QtWidgets.QPushButton) if b.accessibleName() == "Apply " + text][0]


def chamfers():
    return [o for o in doc().Objects if o.TypeId == "Design::Chamfer"]


def show_button(text):
    return [b for b in visible(QtWidgets.QPushButton) if b.accessibleName() == "Show " + text][0]


def strike_over_fillet():
    """Scribble mit einem waagerechten Strich über der Rundung an der vorderen Oberkante (von oben geschrieben)"""
    sc = doc().addObject("Design::Scribble", "Scribble")
    sc.Sheet = App.Placement(App.Vector(0, 0, 30), App.Rotation())
    pts = [App.Vector(5 + k * 0.5, 0.6, 30) for k in range(21)]
    sc.Points = pts
    sc.Widths = [0.4] * len(pts)
    sc.Tools = [1]
    sc.Kinds = [0]
    sc.Colors = [(1.0, 0.22, 0.24, 1.0)]
    sc.Normals = [App.Vector(0, 0, 1)]
    sc.Counts = [len(pts)]
    doc().recompute()
    state["scribble"] = sc
    Gui.ActiveDocument.setEdit(sc.Name)


def fillets():
    return [o for o in doc().Objects if o.TypeId == "Design::Fillet"]


def read_empty():
    """Apply Corrections ohne lesbare Tinte; ein Meldungsfenster würde den Test anhalten: merken und schließen"""
    def boxes():
        state["boxes"] = [m.text() for m in visible(QtWidgets.QMessageBox)]
        [m.close() for m in visible(QtWidgets.QMessageBox)]
    QtCore.QTimer.singleShot(1500, boxes)
    Gui.runCommand("Design_ScribbleCorrect")


def glass(w):
    """Glasfläche eines Panels in der Szene (der Proxy des Inhalts ist so groß wie das Glas)"""
    while w.parentWidget():
        w = w.parentWidget()
    return w.graphicsProxyWidget().sceneBoundingRect()


def cards_free():
    """Korrektur-Karten bei offenem Scribble: nicht über oder unter der Scribble-Palette"""
    palette = [b for b in visible(QtWidgets.QToolButton) if b.text() == "Apply Corrections"][0]
    cards = [w for w in visible(QtWidgets.QWidget) if w.objectName() == "Corrections"][0]
    return not glass(cards).intersects(glass(palette)), "cards %s palette %s" % (glass(cards).getRect(), glass(palette).getRect())


def close_cards():
    [b for b in visible(QtWidgets.QPushButton) if b.text() == "Close" and b.parentWidget().objectName() == "Corrections"][0].click()


def hover_first():
    row = apply_button("R2").parentWidget()
    QtWidgets.QApplication.sendEvent(row, QtCore.QEvent(QtCore.QEvent.Enter))


in_order([
    ("activate", activate),
    ("setup", setup),
    ("red pen", lambda: Gui.runCommand("Design_RedPen")),
    ("scribble", lambda: check("red pen opens a tracing-paper scribble", Gui.ActiveDocument.getInEdit() is not None
                               and Gui.ActiveDocument.getInEdit().Object.TypeId == "Design::Scribble"
                               and Gui.ActiveDocument.getInEdit().Object.Tracing)),
    ("palette", lambda: check("the palette offers Apply Corrections",
                              any(b.text() == "Apply Corrections" for b in visible(QtWidgets.QToolButton)))),
    ("empty", read_empty), wait_step,
    ("no alert", lambda: check("nothing to read: a notice instead of a message box",
                               not state.get("boxes") and any("No corrections found" in t for t in notices()),
                               "%s %s" % (state.get("boxes"), notices()))),
    ("cards in scribble", cards), wait_step,
    ("cards free", lambda: check("cards next to an open scribble keep clear of its palette", *cards_free())),
    ("close cards", close_cards),
    ("finish", lambda: Gui.runCommand("Design_ScribbleFinish")),
    ("cards", cards),
    ("shown", lambda: check("the cards appear", panel_shown())),
    ("only corrections", lambda: check("a word that is no correction gets no apply button",
                                       not apply_button("Hallo").isEnabled())),
    ("ambiguous", lambda: check("between four edges the card asks which one",
                                any(c.accessibleName() == "Which one?" and c.count() >= 2 for c in visible(QtWidgets.QComboBox)))),
    ("hover", hover_first),
    ("preview", lambda: check("pointing at a card highlights its edge", len(Gui.Selection.getSelectionEx()) == 1
                              and Gui.Selection.getSelectionEx()[0].SubElementNames[0].startswith("Edge"))),
    ("shot", lambda: shot("cards")),
    ("apply", lambda: apply_button("R2").click()),
    ("filleted", lambda: check("apply rounds the edge", len(fillets()) == 1 and abs(fillets()[0].Size.Value - 2) < 1e-9
                               and not state["body"].Shape.isNull() and abs(state["body"].Shape.Volume - (4000 - (4 - 3.14159265) * 20)) < 0.01,
                               str(state["body"].Shape.Volume))),
    ("choose", lambda: [c for c in visible(QtWidgets.QComboBox) if c.accessibleName() == "Which one?"][0].setCurrentIndex(1)),
    ("apply second", lambda: apply_button("R1").click()),
    ("two", lambda: check("the chosen edge gets its own fillet", len(fillets()) == 2)),
    wait_step,
    ("done rows", lambda: check("done rows drop their buttons and the card grows with its status lines",
                                not any(b.accessibleName() in ("Apply R2", "Apply R1") for b in visible(QtWidgets.QPushButton))
                                and all(w.height() >= w.sizeHint().height() for w in visible(QtWidgets.QWidget) if w.objectName() == "Corrections"),
                                str([(w.height(), w.sizeHint().height()) for w in visible(QtWidgets.QWidget) if w.objectName() == "Corrections"]))),
    ("undo", lambda: Gui.runCommand("Std_Undo")),
    ("undone", lambda: check("ctrl+z takes the last correction back", len(fillets()) == 1, str(len(fillets())))),
    ("preview cards", lambda: DesignGui.showCorrections(doc(), [("C1", App.Vector(-2, 10, 30), DOWN)])),
    ("show", lambda: show_button("C1").click()),
    ("shown", lambda: check("show puts the chamfer into the model on trial", len(chamfers()) == 1 and doc().HasPendingTransaction)),
    ("hide", lambda: show_button("C1").click()),
    ("hidden", lambda: check("hide takes it out again", len(chamfers()) == 0 and not doc().HasPendingTransaction)),
    ("show again", lambda: show_button("C1").click()),
    ("keep", lambda: apply_button("C1").click()),
    ("kept", lambda: check("apply keeps what was shown", len(chamfers()) == 1 and not doc().HasPendingTransaction)),
    ("volume", lambda: state.update({"before strike": state["body"].Shape.Volume})),
    ("strike", strike_over_fillet), wait_step,
    ("read ink", lambda: Gui.runCommand("Design_ScribbleCorrect")), wait_step,
    ("struck", lambda: check("a line through the fillet reads as remove", any(b.accessibleName() == "Apply weg" for b in visible(QtWidgets.QPushButton)),
                             str([b.accessibleName() for b in visible(QtWidgets.QPushButton)]))),
    ("remove", lambda: apply_button("weg").click()),
    ("removed", lambda: check("and takes the fillet away (the body grows back)",
                              any(o.TypeId == "Design::RemoveFace" for o in doc().Objects)
                              and state["body"].Shape.Volume > state["before strike"] + 10, "%.2f -> %.2f" % (state["before strike"], state["body"].Shape.Volume))),
    ("finish", lambda: Gui.runCommand("Design_ScribbleFinish")),
    ("errors", lambda: check("no errors", not errors(), str(errors()))),
])
