# SPDX-License-Identifier: LGPL-2.1-or-later
"""DXF einfügen mit Rückfrage: Größe und Einheit, Ebenen an/ab, Winzlinge (Kreise mit 0,00008 mm aus Platinen-DXFs)
und doppelt gezeichnete Linien entfernen; Zähler folgen der Wahl; die Skizze bekommt genau das Gewählte."""
import os
from harness import *

DXF = os.environ["OUT"] + ".input.dxf"
state = {}


def entity(kind, layer, *codes):
    return ["0", kind, "8", layer] + [str(v) for pair in codes for v in pair]


def line(layer, x0, y0, x1, y1):
    return entity("LINE", layer, (10, x0), (20, y0), (30, 0), (11, x1), (21, y1), (31, 0))


def circle(layer, x, y, r):
    return entity("CIRCLE", layer, (10, x), (20, y), (30, 0), (40, r))


def write_dxf():
    rows = []
    outline = [(0, 0, 40, 0), (40, 0, 40, 20), (40, 20, 0, 20), (0, 20, 0, 0)]
    for seg in outline:
        rows += line("Outline", *seg)
    rows += line("Outline", 40, 0, 0, 0)  # untere Kante noch einmal, rückwärts gezeichnet
    rows += circle("Holes", 10, 10, 3) + circle("Holes", 30, 10, 3)
    for k in range(5):
        rows += circle("Holes", 5 + k, 2, 0.0000762)  # Winzlinge wie aus einem Platinen-Export
    rows += line("Text", 5, 25, 15, 25) + line("Text", 5, 28, 15, 28)
    rows += ["0", "LINE", "10", "5", "20", "15", "30", "0", "11", "15", "21", "15", "31", "0"]  # ohne Ebene (Code 8)
    with open(DXF, "w") as f:
        f.write("\n".join(["0", "SECTION", "2", "ENTITIES"] + rows + ["0", "ENDSEC", "0", "EOF"]) + "\n")


def review():
    return [d for d in visible(QtWidgets.QDialog) if d.windowTitle() == "Insert DXF"]


def insert():
    def pick():
        d = visible(QtWidgets.QFileDialog)
        name = [e for e in d[0].findChildren(QtWidgets.QLineEdit) if e.isVisible()][0]
        name.setText(DXF); d[0].accept()
    QtCore.QTimer.singleShot(800, pick)
    QtCore.QTimer.singleShot(2500, inspect)
    click(button("Design_Import"))


def texts(d):
    return [w.text() for w in d.findChildren(QtWidgets.QLabel) if w.isVisible()] + \
           [w.text() for w in d.findChildren(QtWidgets.QCheckBox) if w.isVisible()]


def inspect():
    d = review()
    check("the DXF review opens", bool(d))
    if not d:
        return
    d = d[0]
    d.grab().save(os.environ["OUT"] + ".review.png")
    t = texts(d)
    L("  review: %s" % t)
    layers = [b for b in d.findChildren(QtWidgets.QCheckBox) if b.isVisible() and " (" in b.text() and "tiny" not in b.text()
              and "duplicates" not in b.text()]
    names = [b.text() for b in layers]
    check("all layers with their counts, also entities without one",
          names == ["No layer (1)", "Holes (7)", "Outline (5)", "Text (2)"], str(names))
    check("tiny pieces and duplicates are counted",
          "Remove 5 tiny pieces (under 0.001 mm)" in t and "Merge 1 duplicates (drawn twice)" in t, str(t))
    check("summary shows what is inserted and its size", any("9 elements" in s and "40.0 × 28.0 mm" in s for s in t), str(t))
    layers[3].setChecked(False)  # Text weg
    scale = d.findChild(QtWidgets.QComboBox)
    scale.setCurrentIndex(2)  # in cm gezeichnet
    t = texts(d)
    check("without the text layer and in cm: 7 elements, ten times the size",
          any("7 elements" in s and "400.0 × 200.0 mm" in s for s in t), str(t))
    [b for b in d.findChildren(QtWidgets.QPushButton) if b.text() == "Insert"][0].click()


def result():
    sk = [o for o in doc().Objects if o.TypeId == "Sketcher::SketchObject"]
    check("one sketch inserted", len(sk) == 1)
    if not sk:
        return
    from collections import Counter
    kinds = dict(Counter(g.TypeId.split("::")[1] for g in sk[0].Geometry))
    bb = sk[0].Shape.BoundBox
    check("sketch has the outline once, the loose line and the two holes, scaled to cm",
          kinds == {"GeomLineSegment": 5, "GeomCircle": 2} and abs(bb.XLength - 400) < 1e-6 and abs(bb.YLength - 200) < 1e-6,
          "%s %.1f x %.1f" % (kinds, bb.XLength, bb.YLength))
    prof = [o for o in doc().Objects if o.TypeId == "Design::Profiles"][0]
    check("profiles: plate with two holes, and the holes", len(prof.Shape.Faces) == 3, str(len(prof.Shape.Faces)))


def cancel_case():
    """Abbrechen fügt nichts ein"""
    def pick():
        d = visible(QtWidgets.QFileDialog)
        name = [e for e in d[0].findChildren(QtWidgets.QLineEdit) if e.isVisible()][0]
        name.setText(DXF); d[0].accept()

    def cancel():
        d = review()
        if d:
            [b for b in d[0].findChildren(QtWidgets.QPushButton) if b.text() == "Cancel"][0].click()
    QtCore.QTimer.singleShot(800, pick)
    QtCore.QTimer.singleShot(2500, cancel)
    click(button("Design_Import"))


def after_cancel():
    sk = [o for o in doc().Objects if o.TypeId == "Sketcher::SketchObject"]
    check("cancel inserts nothing", len(sk) == 1, str(len(sk)))


run([("dxf", write_dxf), ("insert", insert), ("wait", lambda: None), ("wait", lambda: None), ("result", result),
     ("cancel", cancel_case), ("wait", lambda: None), ("wait", lambda: None), ("after cancel", after_cancel)], delay=1500)
