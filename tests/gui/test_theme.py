# SPDX-License-Identifier: LGPL-2.1-or-later
"""Hell/Dunkel und Liquid Glass über die Einstellungen umschalten (ohne Neustart), Screenshots aller Bereiche."""
from harness import *

grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")


def setup():
    make_body(rect(0, 0, 60, 40), 0, 15, "Box")
    Gui.ActiveDocument.ActiveView.viewIsometric(); Gui.SendMsgToActiveView("ViewFit")
    Gui.Selection.addSelection(body("Box"))


def settings():
    return [d for d in visible(QtWidgets.QDialog) if d.objectName() == "Settings"][0]


def segment(text):
    [b for b in visible(QtWidgets.QPushButton) if b.objectName() == "Segment" and b.text() == text][0].click()


def switch(label):
    """Switch in der Zeile mit diesem Label (Accessible-Name)"""
    [b for b in visible(QtWidgets.QAbstractButton) if b.accessibleName() == label][0].click()


def glass(v):
    [s for s in visible(QtWidgets.QSlider) if s.accessibleName() == "Liquid Glass"][0].setValue(v)


def bg():
    """Hintergrundfarbe oben links in der 3D-Ansicht"""
    v = view(); img = v.viewport().grab().toImage()
    return img.pixelColor(img.width() // 2, 4).name()


def state(tag):
    pal = QtWidgets.QApplication.palette()
    L("%s: window=%s text=%s 3d-top=%s appearance=%s" % (tag, pal.window().color().name(), pal.windowText().color().name(),
                                                        bg(), grp.GetInt("Appearance", 0)))


def home():
    click([b for b in visible(QtWidgets.QToolButton) if b.toolTip() == "Home"][0])


def leave_start():
    [b for b in visible(QtWidgets.QToolButton) if b.toolTip() == "Back to Design"][0].click()


def open_settings():
    QtCore.QTimer.singleShot(0, lambda: Gui.runCommand("MyCAD_Settings"))


run([
    ("setup", setup),
    ("light", lambda: (grp.SetInt("Appearance", 1), open_settings())),
    ("light segment", lambda: segment("Light")),
    ("light settings", lambda: settings().grab().save(os.environ["OUT"] + ".settings-light.png")),
    ("dark", lambda: segment("Dark")),
    ("dark settings", lambda: settings().grab().save(os.environ["OUT"] + ".settings-dark.png")),
    ("close", lambda: settings().accept()),
    ("state dark", lambda: state("dark")),
    ("shot model dark", lambda: shot("model-dark")),
    ("sketch", lambda: click(button("Design_CreateSketch"))),
    ("pick top", lambda: Gui.Selection.addSelection(body("Box"), top_face(body("Box")))),
    ("draw", lambda: Gui.ActiveDocument.getInEdit().Object.addGeometry(Part.Circle(App.Vector(30, 20, 15), App.Vector(0, 0, 1), 8))),
    ("shot sketch dark", lambda: shot("sketch-dark")),
    ("finish", lambda: click(button("Sketcher_LeaveSketch"))),
    ("home", home),
    ("shot start dark", lambda: shot("start-dark")),
    ("back", leave_start),
    ("help", lambda: QtTest.QTest.keyClick(mw, QtCore.Qt.Key_F1)),
    ("shot help dark", lambda: shot("help-dark")),
    ("help close", lambda: [w.hide() for w in visible(QtWidgets.QWidget) if w.objectName() == "HelpPage"]),
    # Glas-Stufen und Bedienungshilfen im Dunkeln
    ("settings 2", open_settings),
    ("ultra clear", lambda: glass(0)),
    ("close 2", lambda: settings().accept()),
    ("shot ultra clear", lambda: shot("glass-0-dark")),
    ("settings 3", open_settings),
    ("tinted", lambda: glass(100)),
    ("contrast", lambda: switch("Increase contrast")),
    ("close 3", lambda: settings().accept()),
    ("shot tinted contrast", lambda: shot("glass-1-contrast-dark")),
    ("settings 4", open_settings),
    ("default", lambda: glass(50)),
    ("contrast off", lambda: switch("Increase contrast")),
    ("transparency", lambda: switch("Reduce transparency")),
    ("back to light", lambda: segment("Light")),
    ("close 4", lambda: settings().accept()),
    ("state light", lambda: state("light")),
    ("shot frost light", lambda: shot("frost-light")),
    ("reset", lambda: (grp.SetBool("ReduceTransparency", False), grp.SetFloat("GlassLevel", 0.5), grp.SetInt("Appearance", 1))),
])
