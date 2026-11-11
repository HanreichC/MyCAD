# SPDX-License-Identifier: LGPL-2.1-or-later
"""Jedes Fenster im MyCAD-Stil (MyStyle L3: Scrim + Glas-Karte, keine Titelleiste), hell und dunkel: Meldung (Combine
ohne Auswahl), Eingabe (Version sichern), Versionen, Parameter und Maß in der Skizze (Doppelklick auf eine Kante). Bilder <OUT>.<name>.png"""
from harness import *
import Sketcher

S = {}
grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")


def modal(name):
    """offenen Dialog prüfen, abbilden und schließen (vor dem Auslösen einplanen: der Dialog blockiert)"""
    def look(tries=[0]):
        d = QtWidgets.QApplication.activeModalWidget()
        if not d and tries[0] < 10:
            tries[0] += 1; QtCore.QTimer.singleShot(300, look); return
        tries[0] = 0
        check("%s is a glass card without title bar" % name,
              bool(d) and bool(d.windowFlags() & QtCore.Qt.FramelessWindowHint) and d.property("glass") is True,
              type(d).__name__ if d else "no dialog")
        if d:
            d.grab().save(os.environ["OUT"] + "." + name + ".png"); d.reject()
    QtCore.QTimer.singleShot(1200, look)


def theme(text):
    """Hell/Dunkel über die Einstellungen (wie der Benutzer)"""
    def pick():
        [b for b in visible(QtWidgets.QPushButton) if b.objectName() == "Segment" and b.text() == text][0].click()
        [d for d in visible(QtWidgets.QDialog) if d.objectName() == "Settings"][0].accept()
    QtCore.QTimer.singleShot(1000, pick)
    Gui.runCommand("MyCAD_Settings")


def message(name):
    modal(name); click(button("Design_Combine"))


def version(name):
    modal(name); Gui.runCommand("MyCAD_SaveVersion")


def setup():
    sk = Gui.ActiveDocument.getInEdit().Object
    sk.addGeometry(rect(10, 10, 70, 50))
    for i in range(4):
        sk.addConstraint(Sketcher.Constraint("Coincident", i, 2, (i + 1) % 4, 1))
    doc().recompute(); S["sk"] = sk
    cam = Gui.ActiveDocument.ActiveView.getCameraNode()  # ganzes Rechteck frei sichtbar
    cam.position.setValue(40, 30, cam.position.getValue()[2]); cam.height.setValue(200)


def datum(name):
    """Doppelklick auf die rechte Kante öffnet die Längeneingabe"""
    p = Gui.ActiveDocument.ActiveView.getPointOnViewport(App.Vector(70, 30, 0))
    vp = view().viewport(); dpr = vp.devicePixelRatioF(); q = QtCore.QPoint(int(p[0] / dpr), int(vp.height() - p[1] / dpr))
    modal(name)
    QtTest.QTest.mouseMove(vp, q)
    for _ in range(2):  # die Skizze erkennt den Doppelklick selbst an zwei schnellen Klicks
        QtTest.QTest.mouseClick(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, q)


run([
    ("activate", activate),
    ("light", lambda: theme("Light")), ("wait", lambda: None),
    ("message light", lambda: message("message-light")), ("wait", lambda: None),
    ("version light", lambda: version("version-light")), ("wait", lambda: None),
    ("versions light", lambda: (modal("versions-light"), Gui.runCommand("Design_Versions"))), ("wait", lambda: None),
    ("parameters light", lambda: (modal("parameters-light"), Gui.runCommand("Design_Parameters"))), ("wait", lambda: None),
    ("Create Sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick XY", lambda: Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XY_Plane")][0])),
    ("setup", setup),
    ("datum light", lambda: QtCore.QTimer.singleShot(0, lambda: datum("datum-light"))), ("wait", lambda: None),
    ("dark", lambda: theme("Dark")), ("wait", lambda: None),
    ("datum dark", lambda: QtCore.QTimer.singleShot(0, lambda: datum("datum-dark"))), ("wait", lambda: None),
    ("leave sketch", esc), ("wait", lambda: None),
    ("version dark", lambda: version("version-dark")), ("wait", lambda: None),
    ("versions dark", lambda: (modal("versions-dark"), Gui.runCommand("Design_Versions"))), ("wait", lambda: None),
    ("parameters dark", lambda: (modal("parameters-dark"), Gui.runCommand("Design_Parameters"))), ("wait", lambda: None),
    ("message dark", lambda: message("message-dark")), ("wait", lambda: None),
    ("restore", lambda: grp.SetInt("Appearance", 0)),
])
