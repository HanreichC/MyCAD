# SPDX-License-Identifier: LGPL-2.1-or-later
"""Phase 14: was kostet ein Bild? Drehen 1 s (60 Mausbewegungen) am Teil aus test_perf_session, je Einstellung
(alles an, ohne Glas-Blur, ohne realistische Materialien, ohne Achsenkreuz). Kein CI-Test, ein Messwerkzeug."""
import os
import sys
from PySide6 import QtGui
from harness import *
sys.path.insert(0, os.path.join(os.path.dirname(os.environ["SCRIPT"]), "..", "design"))
import harness

P = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")
VIEW = App.ParamGet("User parameter:BaseApp/Preferences/View")
W = ("wait", lambda: None)
S = {}
exec(open(os.path.join(os.path.dirname(os.environ["SCRIPT"]), "test_perf_session.py"), encoding="utf-8").read()
     .split("# --- Modellieren")[0].split("S = {}")[1].replace("import Sketcher", ""), globals())
import design as D
import Design
import Sketcher

def settings_switch(label):
    """in den Einstellungen den Schalter neben label umlegen, wie ein Mensch (das Theme liest ihn beim Anwenden)"""
    def open_():
        QtCore.QTimer.singleShot(0, lambda: Gui.runCommand("MyCAD_Settings"))

    def flip():
        for lab in visible(QtWidgets.QLabel):
            if lab.text() == label:
                mid = lab.mapToGlobal(QtCore.QPoint(0, lab.height() // 2)).y()
                cands = [w for w in visible(QtWidgets.QAbstractButton) if w.parentWidget() is lab.parentWidget()
                         and abs(w.mapToGlobal(QtCore.QPoint(0, w.height() // 2)).y() - mid) < 14]
                if cands:
                    cands[0].click(); L("  switched %s" % label); return
        L("  no switch %s" % label)

    def close():
        for d in visible(QtWidgets.QDialog):
            d.reject()
    return [("open settings", open_), W, ("flip " + label, flip), W, ("close settings", close), W]


def fit():
    Gui.runCommand("Std_ViewIsometric"); Gui.SendMsgToActiveView("ViewFit")


def frame_cost(label):
    """30 Bilder hintereinander, je mit etwas gedrehter Kamera: Wandzeit je Bild (gezeichnet wird in processEvents)"""
    def f():
        import time
        from pivy import coin  # noqa: F401  (getCameraNode liefert ein pivy-Objekt)
        v = Gui.ActiveDocument.ActiveView
        cam = v.getCameraNode()
        start = App.Rotation(*cam.orientation.getValue().getValue())
        QtWidgets.QApplication.processEvents()
        vp = view().viewport()
        vp.installEventFilter(harness._paints)
        harness._Paints.count = 0
        t = time.perf_counter(); cpu = time.thread_time()
        for i in range(30):
            cam.orientation.setValue(*(App.Rotation(App.Vector(0, 0, 1), 1.2 * i) * start).Q)
            v.redraw()
            QtWidgets.QApplication.processEvents()
        wall = (time.perf_counter() - t) * 1000
        S.setdefault("cost", []).append((label, wall / max(harness._Paints.count, 1),
                                         (time.thread_time() - cpu) * 1000 / max(harness._Paints.count, 1), harness._Paints.count))
    return f


def report():
    for label, ms, cpu, n in S.get("cost", []):
        L("  %-34s %5.1f ms per frame (main thread CPU %4.1f ms, %d frames)" % ("frame cost [%s]" % label, ms, cpu, n))
    for name, ms, worst, paints, budget in harness._perf:
        if ms > 0:
            L("  %-34s %5.1f frames/s  %5.0f ms per frame" % (name, paints / (ms / 1000.0), ms / max(paints, 1)))


steps = [("activate", activate), ("build", build), W, W]
steps += [("fit", fit), W, W, timed("orbit [all on]", orbit, 1200), W, ("cost all on", frame_cost("all on")), W]
steps += settings_switch("Reduce transparency") + [("fit 2", fit), W, W, timed("orbit [no glass blur]", orbit, 1200), W, ("cost no glass", frame_cost("no glass blur")), W]
steps += settings_switch("Reduce transparency") + settings_switch("Realistic materials")
steps += [("fit 3", fit), W, W, timed("orbit [no realistic materials]", orbit, 1200), W, ("cost no mat", frame_cost("no realistic materials")), W]
steps += settings_switch("Realistic materials")
steps += [("no axes", lambda: VIEW.SetBool("CornerCoordSystem", False)), ("fit 4", fit), W, W,
          timed("orbit [no corner axes]", orbit, 1200), W, ("cost no axes", frame_cost("no corner axes")), W, ("axes", lambda: VIEW.SetBool("CornerCoordSystem", True))]
steps += [("report", report)]
run(steps)
