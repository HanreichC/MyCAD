# SPDX-License-Identifier: LGPL-2.1-or-later
"""Bildrate: Drehen und Zeichnen in der Skizze laufen in voller Bildschirmrate statt in der halben (ein zweites Anzeigen
pro Bild, das auf den Takt wartet, halbiert sie), und der gemerkte Inhalt der Glas-Panels bleibt aktuell.
Mindestwert für 60-Hz-Bildschirme. Fehler stehen als FAIL im Protokoll."""
import math
from PySide6 import QtGui
from harness import *

MIN_FPS = 45
V = App.Vector
wait = ("wait", lambda: None)
state = {"frames": 0, "run": None, "i": 0, "angle": 0.0}


class Frames(QtCore.QObject):
    def eventFilter(self, obj, event):
        if event.type() == QtCore.QEvent.Paint:
            state["frames"] += 1
        return False


frames = Frames()


def hover(p):
    vp = view().viewport()
    QtWidgets.QApplication.sendEvent(vp, QtGui.QMouseEvent(QtCore.QEvent.MouseMove, QtCore.QPointF(p), QtCore.QPointF(vp.mapToGlobal(p)), QtCore.Qt.NoButton, QtCore.Qt.NoButton, QtCore.Qt.NoModifier))


def rotate():
    state["angle"] += 0.4
    Gui.ActiveDocument.ActiveView.setCameraOrientation(App.Rotation(V(1, 1, 1), state["angle"]).Q)


def mouse_circle():
    vp = view().viewport(); state["i"] += 1; a = state["i"] * 0.05
    hover(QtCore.QPoint(int(vp.width() * (0.5 + 0.2 * math.cos(a))), int(vp.height() * (0.5 + 0.2 * math.sin(a)))))


def measure(name, action):
    """Aktion alle 8 ms (wie eine 125-Hz-Maus), nach 3 s die Bilder pro Sekunde prüfen"""
    def tick():
        if state["run"] is action:
            action(); QtCore.QTimer.singleShot(8, tick)

    def finish():
        state["run"] = None
        fps = state["frames"] / 3
        check("%s: at least %d frames per second" % (name, MIN_FPS), fps >= MIN_FPS, "%.0f fps" % fps)
    view().viewport().installEventFilter(frames)
    state["frames"] = 0; state["run"] = action
    tick()
    QtCore.QTimer.singleShot(3000, finish)


def note_updates():
    """Text im Post-it muss auf dem Bildschirm ankommen, obwohl das Panel seinen Inhalt zwischenspeichert"""
    e = [e for e in visible(QtWidgets.QPlainTextEdit) if e.objectName() == "NoteText"][0]
    before = mw.grab().toImage()
    e.setPlainText("WWWWWWWW\nWWWWWWWW\nWWWWWWWW")

    def compare():
        check("cached panel shows new text", mw.grab().toImage() != before)
    QtCore.QTimer.singleShot(500, compare)


def geometry():
    make_body(rect(0, 0, 60, 40), 0, 15, "Box")
    Gui.ActiveDocument.ActiveView.viewIsometric(); Gui.SendMsgToActiveView("ViewFit")


in_order([
    ("activate", activate),
    ("model", geometry), wait,
    ("rotate", lambda: measure("rotating the model", rotate)), wait, wait, wait,
    ("note", lambda: click(button("Design_Note"))), wait,
    ("note text", note_updates), wait,
    ("sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick", lambda: Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XY_Plane")][0])), wait, wait,
    ("line", lambda: click(button("Sketcher_CreateLine"))), wait,
    ("first point", lambda: QtTest.QTest.mouseClick(view().viewport(), QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, QtCore.QPoint(600, 400))), wait,
    ("draw", lambda: measure("drawing a line in a sketch", mouse_circle)), wait, wait, wait,
])
