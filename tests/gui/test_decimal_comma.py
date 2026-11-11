# SPDX-License-Identifier: LGPL-2.1-or-later
"""Dezimalkomma überall: "2,5" in einem Maßfeld (Extrude-Abstand, QuantitySpinBox) ist 2,5 mm wie "2.5" (vorher wurde
das Komma still verworfen, der Wert blieb alt); in einem einfachen Zahlenfeld der Einstellungen (QDoubleSpinBox) ebenso. Wo ein Komma
Tausender trennt (en_US), bleibt es dabei: das prüfen FreeCADs Unit-Tests (QuantityInput, QuantitySpinBox)."""
from harness import *

S = {}
grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")


def setup():
    make_body(rect(0, 0, 40, 30), 0, 10, "Box")
    S["f"] = [o for o in doc().Objects if o.TypeId == "Design::Extrude"][-1]
    S["tight"] = grp.GetFloat("PrintFitTight", 0.1)


def distance(text, want):
    type_field("Distance", text)
    QtWidgets.QApplication.processEvents()
    check("typing %s in the Distance field gives %s mm" % (text, want), abs(S["f"].Distance.Value - want) < 1e-9,
          "Distance=%s" % S["f"].Distance)


def settings_field():
    """Spiel eng in den Einstellungen: "0,15" mit echten Tasten"""
    def act():
        d = [w for w in visible(QtWidgets.QDialog) if w.objectName() == "Settings"][0]
        box = [b for b in d.findChildren(QtWidgets.QDoubleSpinBox) if b.accessibleName() == "Clearance tight"][0]
        box.setFocus(); box.lineEdit().selectAll()
        for ch in "0,15":
            QtTest.QTest.keyClicks(box.lineEdit(), ch)
        S["typed"] = box.value()
        d.accept()
    QtCore.QTimer.singleShot(900, act)
    Gui.runCommand("MyCAD_Settings")


in_order([
    ("activate", activate), ("setup", setup),
    ("edit", lambda: Gui.ActiveDocument.setEdit(S["f"])), ("wait", lambda: None),
    ("comma", lambda: distance("2,5", 2.5)),
    ("dot", lambda: distance("3.5", 3.5)),
    ("comma with unit", lambda: distance("4,25 mm", 4.25)),
    ("enter", lambda: (type_field("Distance", "5,5"), QtTest.QTest.keyClick(field("Distance").lineEdit(), QtCore.Qt.Key_Return))),
    ("wait", lambda: None),
    ("entered", lambda: check("5,5 and Enter applies 5.5 mm (no 'unknown parameter')", abs(S["f"].Distance.Value - 5.5) < 1e-9
                              and not [t for t in (w.text() for w in visible(QtWidgets.QLabel)) if "invalid expression" in t],
                              "Distance=%s" % S["f"].Distance)),
    ("close", lambda: Gui.ActiveDocument.getInEdit() and Gui.ActiveDocument.resetEdit()), ("wait", lambda: None),
    ("settings", settings_field), ("wait", lambda: None),
    ("settings comma", lambda: check("a plain number field takes 0,15", abs(S.get("typed", 0) - 0.15) < 1e-9,
                                     "value=%s" % S.get("typed"))),
    ("restore", lambda: grp.SetFloat("PrintFitTight", S["tight"])),
])
