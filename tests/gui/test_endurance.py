# SPDX-License-Identifier: LGPL-2.1-or-later
"""U8: Wird MyCAD mit der Zeit langsamer? (FreeCAD#29376, #29636) Dieselbe Standard-Szene wird am Anfang und am Ende
gemessen (Zeit je Bild beim Drehen, Speicher); dazwischen laufen Arbeitszyklen in einem Prozess: neues Design, Körper,
Rundung, Schnitt, Drehen, Rückgängig, Schließen. Was liegen bleibt (Speicher, Szenenknoten, Beobachter), zeigt sich
am Ende als langsameres Bild oder mehr Speicher.
    ENDURANCE_MINUTES=30 MYCAD_TIMEOUT=2400 tests/gui/run.sh tests/gui/test_endurance.py /tmp/endurance
In der Suite eine Minute; die Grenzen gelten für beide."""
import math
import os
import time
from harness import *
import Design

MINUTES = float(os.environ.get("ENDURANCE_MINUTES", "1"))
V = App.Vector
state = {}


def rss_mb():
    """belegter Speicher; vorher gibt glibc Freigegebenes ans System zurück, sonst sähe Wiederverwendbares wie ein Leck aus"""
    import ctypes
    import gc
    gc.collect()
    try:
        ctypes.CDLL("libc.so.6").malloc_trim(0)
    except OSError:
        pass
    for line in open("/proc/self/status"):
        if line.startswith("VmRSS:"):
            return int(line.split()[1]) / 1024
    return 0


def fresh():
    """neues Design wie per Knopf, danach das alte schließen (alle zu schließen ließ die Oberfläche ohne Design)"""
    old = App.ActiveDocument
    Gui.runCommand("Std_New")
    for _ in range(5):
        QtWidgets.QApplication.processEvents()
    if old and old.Name in App.listDocuments():
        App.closeDocument(old.Name)
    for _ in range(5):
        QtWidgets.QApplication.processEvents()


def scene():
    """immer dieselbe Szene: drei Körper, einer gerundet"""
    fresh()
    a = make_body(rect(0, 0, 60, 40), 0, 20, "A")
    make_body(rect(80, 0, 120, 40), 0, 30, "B")
    make_body([Part.Circle(V(30, 80, 0), V(0, 0, 1), 15)], 0, 25, "C")
    edges = [i for i, e in enumerate(a.Shape.Edges, 1) if abs(e.CenterOfMass.z - 20) < 1e-6]
    f = doc().addObject("Design::Fillet", "Fillet")
    Design.componentOf(a).addObject(f)
    Design.addToTimeline(f)
    f.Edges = ["Edge%d" % i for i in edges]
    f.Size = 2
    Design.attachToBodies(f, [a])
    doc().recompute()
    Gui.ActiveDocument.ActiveView.viewIsometric(); Gui.SendMsgToActiveView("ViewFit")
    QtWidgets.QApplication.processEvents()


def frame_ms():
    """mittlere Zeit für ein Bild beim Drehen: grab() rendert die Ansicht wirklich (repaint() nur angefordert)"""
    vp = view().viewport()
    for _ in range(3):
        vp.grab()
    t = time.monotonic()
    for i in range(20):
        Gui.ActiveDocument.ActiveView.setCameraOrientation(App.Rotation(V(1, 1, 1), 0.3 + 0.05 * i).Q)
        vp.grab()
    return (time.monotonic() - t) / 20 * 1000


def logged(fn):
    """vollständiger Traceback ins Protokoll (der Harness nennt nur die Ausnahme)"""
    def run_logged():
        import traceback
        try:
            fn()
        except Exception:
            L(traceback.format_exc())
            raise
    return run_logged


def measure(tag):
    scene()
    ms = min(frame_ms() for _ in range(3))
    mb = rss_mb()
    state[tag] = (ms, mb)
    L("%s: %.2f ms per frame, %.0f MB" % (tag, ms, mb))


def churn():
    """Arbeitszyklen bis MINUTES um sind; zwischen den Schritten darf die Oberfläche zeichnen"""
    end = time.monotonic() + MINUTES * 60
    cycles = 0
    while time.monotonic() < end:
        fresh()
        for k in range(4):
            b = make_body(rect(k * 50, 0, k * 50 + 40, 30), 0, 10 + k * 5, "Part%d" % k)
            QtWidgets.QApplication.processEvents()
        sk = doc().addObject("Sketcher::SketchObject", "Cut")
        doc().getObject("Sketches").addObject(sk)
        sk.Placement = App.Placement(V(0, 0, 40), App.Rotation())
        for k in range(4):
            sk.addGeometry(Part.Circle(V(k * 50 + 20, 15, 0), V(0, 0, 1), 5))
        doc().recompute()
        for i in range(10):
            Gui.ActiveDocument.ActiveView.setCameraOrientation(App.Rotation(V(0, 0, 1), 0.2 * i).Q)
            QtWidgets.QApplication.processEvents()
        Gui.Selection.addSelection(doc().Name, b.Name)
        Gui.Selection.clearSelection()
        cycles += 1
    state["cycles"] = cycles
    L("churn: %d cycles in %.1f min" % (cycles, MINUTES))


def verdict():
    (ms0, mb0), (ms1, mb1) = state["start"], state["end"]
    L("frame %.2f -> %.2f ms, memory %.0f -> %.0f MB after %d cycles" % (ms0, ms1, mb0, mb1, state["cycles"]))
    # Grenzen: ein Bild höchstens 50 % (plus 2 ms Messrauschen) langsamer. Speicher: 150 MB für alles, was beim ersten
    # Mal angelegt wird, dazu höchstens 3 MB je geschlossenem Design. Gemessen 1,35 MB (PLAN U8: Rest in Qts
    # Framebuffern je Ansicht); vorher 9 MB, weil Texturen und die Szene des Kontaktschattens liegen blieben
    per = (mb1 - mb0) / max(1, state["cycles"])
    L("memory per closed design: %.2f MB" % per)
    check("U8: the same scene is not slower after working", ms1 <= ms0 * 1.5 + 2, "%.2f -> %.2f ms" % (ms0, ms1))
    check("U8: memory does not keep growing", mb1 - mb0 <= 150 + 3 * state["cycles"],
          "%.0f -> %.0f MB (%.2f MB per design)" % (mb0, mb1, per))


in_order([
    ("start", logged(lambda: measure("start"))),
    ("churn", logged(churn)),
    ("end", logged(lambda: measure("end"))),
    ("verdict", verdict),
])
