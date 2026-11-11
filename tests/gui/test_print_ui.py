# SPDX-License-Identifier: LGPL-2.1-or-later
"""10.6 Idee 5 in der Oberfläche: Druckansicht an (Legende, rote Schraffur am Überhang), Unterseite wählen dreht die
Druckrichtung, Drucken öffnet den (falschen) Slicer mit dem 3MF, Druckansicht aus"""
import os
import stat
import sys
import tempfile
from harness import *
import harness
import Design

sys.path.append(os.path.join(os.path.dirname(harness.__file__), "..", "design"))
import design  # noqa: E402

state = {}
SLICER_DIR = tempfile.mkdtemp()


def fake_slicer():
    path = os.path.join(SLICER_DIR, "prusa-slicer")
    with open(path, "w") as f:
        f.write('#!/bin/sh\necho "$@" > "%s"\n' % os.path.join(SLICER_DIR, "args.txt"))
    os.chmod(path, os.stat(path).st_mode | stat.S_IEXEC)
    os.environ["PATH"] = SLICER_DIR + os.pathsep + os.environ.get("PATH", "")
    App.ParamGet("User parameter:BaseApp/Preferences/MyCAD").RemString("Slicer")


def setup():
    fake_slicer()
    _, b = design.box(doc(), 10, 10, 10)
    sk = design.sketch(doc(), design.rect(-10, -10, 20, 20), App.Placement(App.Vector(0, 0, 10), App.Rotation()))
    design.extrude(doc(), sk, 2, op="Join", bodies=[b])
    for o in doc().Objects:
        if o.TypeId == "Sketcher::SketchObject":
            o.Visibility = False
    state["body"] = b
    Gui.SendMsgToActiveView("ViewFit")


def red_pixels():
    img = view().viewport().grab().toImage()
    n = 0
    for y in range(0, img.height(), 3):
        for x in range(0, img.width(), 3):
            c = img.pixelColor(x, y)
            n += c.red() > 180 and c.green() < 110 and c.blue() < 110
    return n


def legend_shown():
    return any(w.objectName() == "PrintLegend" for w in visible(QtWidgets.QWidget))


def glass(w):
    """Glasfläche eines Panels in der Szene (der Proxy des Inhalts ist so groß wie das Glas)"""
    while w.parentWidget():
        w = w.parentWidget()
    return w.graphicsProxyWidget().sceneBoundingRect()


def legend_free():
    legend = [w for w in visible(QtWidgets.QWidget) if w.objectName() == "PrintLegend"][0]
    notes = [e for e in visible(QtWidgets.QPlainTextEdit) if e.objectName() == "NoteText"]
    return bool(notes) and not any(glass(legend).intersects(glass(n)) for n in notes), "legend %s notes %s" % (
        glass(legend).getRect(), [glass(n).getRect() for n in notes])


def legend_button(text):
    return [b for b in visible(QtWidgets.QPushButton) if b.text() == text][0]


def pick_hat_top():
    b = state["body"]
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(b, design.top_face(b))


in_order([
    ("activate", activate),
    ("setup", setup),
    ("before", lambda: state.update(red=red_pixels())),
    ("on", lambda: Gui.runCommand("Design_PrintView")),
    ("legend", lambda: check("the print view shows its legend", legend_shown())),
    ("red", lambda: check("the overhang of the hat is hatched red", red_pixels() > state["red"] + 50, "%d -> %d" % (state["red"], red_pixels()))),
    ("note", lambda: click(button("Design_Note"))), ("wait", lambda: None),
    ("legend free", lambda: check("a post-it (bottom right) does not cover the legend", *legend_free())),
    ("shot", lambda: shot("print")),
    ("pick top", pick_hat_top),
    ("bottom", lambda: legend_button("Choose Bottom Face").click()),
    ("turned", lambda: check("the hat top now lies on the bed", Design.printUp(doc()) == App.Vector(0, 0, -1), str(Design.printUp(doc())))),
    ("print", lambda: legend_button("Print").click()),
    ("wait", lambda: None),
    ("slicer", lambda: check("print opens the slicer with a 3MF",
                             os.path.exists(os.path.join(SLICER_DIR, "args.txt"))
                             and open(os.path.join(SLICER_DIR, "args.txt")).read().strip().endswith(".3mf"))),
    ("remembered", lambda: check("the slicer is remembered",
                                 App.ParamGet("User parameter:BaseApp/Preferences/MyCAD").GetString("Slicer") == "PrusaSlicer")),
    ("off", lambda: Gui.runCommand("Design_PrintView")),
    ("hidden", lambda: check("off again: no legend, no hatching", not legend_shown() and red_pixels() <= state["red"] + 10)),
    ("errors", lambda: check("no errors", not errors(), str(errors()))),
])
