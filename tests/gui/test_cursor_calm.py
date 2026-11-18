# SPDX-License-Identifier: LGPL-2.1-or-later
"""H2: Hat ein Feld in einem Glas-Panel den Fokus (Maß im Extrude-Dialog, Notiz), zeichnet die 3D-Ansicht in Ruhe
nicht neu. Vorher 2 Bilder je Sekunde im Takt des blinkenden Cursors. Gemessen: 3 s Ruhe, höchstens ein Bild.
Fehler stehen als FAIL im Protokoll."""
from harness import *

state = {"frames": 0}


class Frames(QtCore.QObject):
    def eventFilter(self, obj, event):
        if event.type() == QtCore.QEvent.Paint:
            state["frames"] += 1
        return False


frames = Frames()


def focus_field():
    """das Textfeld der Notiz (ein Glas-Panel über der Ansicht) bekommt den Fokus"""
    fields = [e for kind in (QtWidgets.QPlainTextEdit, QtWidgets.QTextEdit, QtWidgets.QLineEdit)
              for e in visible(kind) if e.isEnabled()]
    state["field"] = fields[0] if fields else None
    if state["field"]:
        # wie ein Klick hinein: Fokus auf das Proxy-Element in der Szene der Ansicht und dort auf das Feld
        top = state["field"].window()
        proxy = top.graphicsProxyWidget()
        view().setFocus()
        if proxy:
            proxy.setFocus()
        state["field"].setFocus()


def start_count():
    view().viewport().installEventFilter(frames)
    state["frames"] = 0


run([
    ("body", lambda: make_body(rect(0, 0, 40, 30), 0, 10, "Box")),
    ("note", lambda: Gui.runCommand("Design_Note")),
    ("focus", focus_field),
    ("has field", lambda: check("the note has a text field", state.get("field") is not None, str(state.get("field")))),
    ("no blink", lambda: check("H2: the text cursor does not blink (each blink redrew the 3D view)",
                               QtWidgets.QApplication.cursorFlashTime() == 0, str(QtWidgets.QApplication.cursorFlashTime()))),
    ("count", start_count),
    ("wait 1", lambda: None), ("wait 2", lambda: None),
    ("frames", lambda: check("H2: a focused field does not redraw the 3D view while nothing happens",
                             state["frames"] <= 1, "%d frames in ~3 s" % state["frames"])),
])
