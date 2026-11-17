# SPDX-License-Identifier: LGPL-2.1-or-later
"""Klicks mitten in einer langen Neuberechnung (Absturz "Monitor Light", 2026-11-17: ein zweites Abbrechen lief in das
erste hinein, das Feature war schon gelöscht). Ein Cut mit 225 Löchern rechnet lange genug, dass der Fortschrittsbalken
Ereignisse verarbeitet; Timer klicken dann OK, Abbrechen oder drücken Esc, während noch gerechnet wird. Erwartet: kein
Absturz (sonst fehlt "step done"), danach ein stimmiger Zustand: Dialog offen mit Extrude oder Dialog zu, und Abbrechen
lässt die Platte heil. Der Log-Wächter in run.sh meldet zusätzlich verschachteltes Neuberechnen."""
from harness import *

PLATE = 200 * 200 * 4


def holes():
    d = doc(); root = [o for o in d.Objects if o.TypeId == "App::Part"][0]
    sk = d.addObject("Sketcher::SketchObject", "Sketch"); d.getObject("Sketches").addObject(sk)
    for i in range(15):
        for j in range(15):
            sk.addGeometry(Part.Circle(App.Vector(10 + 12 * i, 10 + 12 * j, 0), App.Vector(0, 0, 1), 2))
    prof = d.addObject("Design::Profiles", "Profiles"); prof.Sketch = sk; root.addObject(prof)
    d.recompute()
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(prof)


def dialog_button(text):
    return [b for b in visible(QtWidgets.QPushButton) if b.text().replace("&", "") == text][0]


def later(ms, fn):
    """fn läuft im Timer; der feuert auch mitten in einer Neuberechnung, wenn der Fortschrittsbalken Ereignisse
    verarbeitet (genau dort entstand der Absturz)"""
    def safe():
        try:
            fn()
        except Exception as e:  # Knopf schon weg: der Dialog ist zu, das ist ein erlaubter Ausgang
            L("  later: %s" % e)
    QtCore.QTimer.singleShot(ms, safe)


BEFORE = set()  # Extrudes vor dem Test (das der Platte)


def extrudes():
    return [o for o in doc().Objects if o.TypeId == "Design::Extrude" and o.Name not in BEFORE]


def consistent(name):
    open_ = bool(Gui.Control.activeDialog())
    plate = round(body("Plate").Shape.Volume)
    if open_:
        good = len(extrudes()) == 1
    else:
        good = not extrudes() and plate == PLATE  # abgebrochen: nichts übrig, Platte heil
    check(name, good, "dialog=%s extrudes=%s plate=%s errors=%s" % (open_, [e.Name for e in extrudes()], plate, errors()))


def answer_abort_question():
    w = QtWidgets.QApplication.activeModalWidget()
    if w:
        w.grab().save(os.environ["OUT"] + ".abort-question.png")  # eigenes Fenster: mw.grab() zeigt es nicht
        L("  abort question: %s" % [b.text() for b in w.findChildren(QtWidgets.QAbstractButton) if b.isVisible()])
        w.reject()  # weiterrechnen


def start():
    BEFORE.update(o.Name for o in doc().Objects if o.TypeId == "Design::Extrude")
    holes()
    click(button("Design_Extrude"))


run([
    ("plate", lambda: make_body(rect(0, 0, 200, 200), 0, 4, "Plate")),
    ("Extrude", start),
    ("timing", lambda: L("open: %s, extrudes %s" % (bool(Gui.Control.activeDialog()), [e.Name for e in extrudes()]))),
    # Abbrechen, während das Tippen eine lange Vorschau rechnet
    ("cancel while typing", lambda: (later(150, lambda: click(dialog_button("Cancel"))), type_into(0, "12 mm"))),
    ("after cancel while typing", lambda: consistent("cancel during a recompute leaves a consistent state")),
    ("reopen", lambda: None if Gui.Control.activeDialog() else start()),
    # Doppelt abbrechen: der zweite Klick kommt, während der erste noch aufräumt
    ("double cancel", lambda: (later(30, lambda: click(dialog_button("Cancel"))), click(dialog_button("Cancel")))),
    ("after double cancel", lambda: consistent("cancel twice does not crash")),
    ("reopen 2", lambda: None if Gui.Control.activeDialog() else start()),
    # OK und gleich danach Abbrechen
    ("ok then cancel", lambda: (later(30, lambda: click(dialog_button("Cancel"))), ok())),
    ("after ok then cancel", lambda: check("OK then cancel keeps one result", not Gui.Control.activeDialog()
                                           and len(extrudes()) <= 1, "extrudes=%s" % [e.Name for e in extrudes()])),
    ("undo", lambda: Gui.runCommand("Std_Undo")),
    ("reopen 3", start),
    # Esc, während eine Vorschau rechnet
    # Esc während einer Rechnung fragt "Abbrechen?" (modal); ein Mensch beantwortet sie, statt am Fenster vorbei Esc
    # an die 3D-Ansicht zu schicken (das konnte nur der Test und erzeugte verschachteltes Rechnen)
    ("esc while typing", lambda: (later(150, esc), type_into(0, "8 mm"))),
    ("abort question", answer_abort_question),
    ("after esc", lambda: consistent("Esc during a recompute leaves a consistent state")),
    ("close", lambda: Gui.Control.activeDialog() and esc()),
    ("errors", lambda: L("errors=%s volumes=%s" % (errors(), volumes()))),
])
