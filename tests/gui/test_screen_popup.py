# SPDX-License-Identifier: LGPL-2.1-or-later
"""Am echten Bildschirm (Compositor, nur auf dem Desktop; unter Xvfb übersprungen): Drucken, welcher Slicer? Dialog und
aufgeklappte Liste erscheinen so, wie Qt sie zeichnet, ohne dunkle Ränder (die sah nur der Compositor)."""
import os
import tempfile
from harness import *
import harness
import sys

sys.path += [os.path.join(os.path.dirname(harness.__file__), "..", "design"), "/workspace/tests/design"]
import design  # noqa: E402

state = {}


def setup():
    folder = tempfile.mkdtemp()
    for name in ("prusa-slicer", "orca-slicer"):  # zwei Slicer: dann fragt Drucken, welcher
        path = os.path.join(folder, name)
        with open(path, "w") as f:
            f.write("#!/bin/sh\nexit 0\n")
        os.chmod(path, 0o755)
    os.environ["PATH"] = folder + os.pathsep + os.environ.get("PATH", "")
    App.ParamGet("User parameter:BaseApp/Preferences/MyCAD").RemString("Slicer")
    design.box(doc(), 10, 10, 10)
    Gui.SendMsgToActiveView("ViewFit")


def chooser():
    d = [w for w in QtWidgets.QApplication.topLevelWidgets() if isinstance(w, QtWidgets.QInputDialog) and w.isVisible()]
    return d[0] if d else None


def dark_rows(img):
    """Zeilen, die im mittleren Drittel fast schwarz sind"""
    rows = []
    for y in range(img.height()):
        xs = range(img.width() // 3, 2 * img.width() // 3)
        if all(max(img.pixelColor(x, y).red(), img.pixelColor(x, y).green(), img.pixelColor(x, y).blue()) < 40 for x in xs):
            rows.append(y)
    return rows


def popup():
    d = chooser()
    check("print asks which slicer", d is not None)
    if not d:
        return
    ok = [b for b in d.findChildren(QtWidgets.QPushButton) if b.text() == "OK"][0]  # deckend: Anker für das Glas
    at = screen_position(ok, "anchor")  # vor dem Aufklappen: die Liste verdeckt den Knopf
    if at is None:
        L("  no real screen (Xvfb): screen checks skipped")
        d.reject()
        return
    check("the dialog appears on the real screen as Qt draws it (OK button found)", at is not False)
    combo = d.findChild(QtWidgets.QComboBox)
    combo.showPopup()  # ohne Fensterwechsel: ein Popup schließt sich, sobald ein anderes Fenster aktiv wird
    for _ in range(20):
        QtWidgets.QApplication.processEvents()
    container = combo.view().window()
    real = screen_region(container, ok, at, "popup")
    if real:
        real.save(os.environ["OUT"] + ".popup-real.png")
        share = looks_like(real, container)
        check("the open list appears on screen as Qt draws it", share > 0.95, "%.0f %% alike" % (share * 100))
        check("no dark lines at the open list", not dark_rows(real), str(dark_rows(real)))
    combo.hidePopup()
    d.reject()


run([("setup", setup), ("print", lambda: Gui.runCommand("Design_Print")), ("popup", popup)], delay=1500)
