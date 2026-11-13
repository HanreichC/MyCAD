# SPDX-License-Identifier: LGPL-2.1-or-later
"""Am echten Bildschirm (Compositor, nur auf dem Desktop; unter Xvfb übersprungen): rahmenlose, durchscheinende Fenster
von MyCAD (Menü, Glas-Rückfrage, Einstellungen) bringen keine schwarzen Ecken, Schatten oder Ränder mit. Verglichen
wird der Bildschirm vor und mit dem Fenster; was sich ohnehin bewegt (Uhr, andere Programme), zählt nicht."""
from harness import *

state = {}


def setup():
    make_body(rect(0, 0, 60, 40), 0, 15, "Box")
    Gui.ActiveDocument.ActiveView.viewIsometric()
    Gui.SendMsgToActiveView("ViewFit")


def before(name):
    def step():
        state["base"] = screen_baseline(name)
        if state["base"] is None:
            L("  no real screen (Xvfb): %s skipped" % name)
    return step


def verify(what, name):
    def step():
        if state.get("base") is None:
            return
        count, box = new_black(state["base"], name)
        check("%s: no black corners, shadows or edges on the real screen" % what, count == 0,
              "%d black pixels in %s" % (count, box))
    return step


def black_window():
    """Selbstprüfung: ein absichtlich schwarzes Fenster über dem hellen Modell muss erkannt werden"""
    w = QtWidgets.QWidget(mw, QtCore.Qt.Tool | QtCore.Qt.FramelessWindowHint)
    w.setStyleSheet("background: black")
    w.resize(30, 30)
    v = view()
    w.move(v.viewport().mapToGlobal(QtCore.QPoint(v.width() // 3, v.height() // 3)))
    w.show()
    state["black"] = w


def check_black_seen():
    if state.get("base") is None:
        return
    count, box = new_black(state["base"], "selfcheck")
    check("self-check: a black window on the screen is seen", count >= 400, "%d black pixels in %s" % (count, box))
    state["black"].close()


def menu():
    m = QtWidgets.QMenu(mw)
    for text in ("Save Version", "Rename", "Delete…"):
        m.addAction(text)
    state["menu"] = m
    v = view()
    m.popup(v.viewport().mapToGlobal(QtCore.QPoint(v.width() // 2, v.height() // 2)))


def alert():
    box = QtWidgets.QMessageBox(QtWidgets.QMessageBox.Warning, "Delete Design", "Delete “Box”? The file is moved to the trash.",
                                QtWidgets.QMessageBox.Cancel, mw)
    box.addButton("Delete", QtWidgets.QMessageBox.DestructiveRole)
    state["alert"] = box
    box.open()


def settings():
    QtCore.QTimer.singleShot(0, lambda: Gui.runCommand("MyCAD_Settings"))  # modal: nicht im Schritt blockieren


def close_settings():
    for d in visible(QtWidgets.QDialog):
        d.reject()


run([("setup", setup),
     ("before selfcheck", before("selfcheck")), ("black", black_window), ("check selfcheck", check_black_seen),
     ("before menu", before("menu")), ("menu", menu), ("check menu", verify("menu", "menu")),
     ("close menu", lambda: state["menu"].close()),
     ("before alert", before("alert")), ("alert", alert), ("check alert", verify("glass alert", "alert")),
     ("close alert", lambda: state["alert"].reject()),
     ("before settings", before("settings")), ("settings", settings), ("check settings", verify("settings", "settings")),
     ("close settings", close_settings)], delay=1200)
