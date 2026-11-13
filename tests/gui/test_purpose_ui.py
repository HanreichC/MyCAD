# SPDX-License-Identifier: LGPL-2.1-or-later
"""10.5 Idee 4 in der Oberfläche: Passung aus der Befehlssuche ("passung"), Bohrung und Welle gewählt, H7/g6
auswählen, das Spiel steht im Dialog; Schraube hier: Klick auf die Oberseite, M3 mit Einschmelzmutter, die Länge
folgt im Dialog"""
import os
import sys
from harness import *
import harness
import Design

sys.path.append(os.path.join(os.path.dirname(harness.__file__), "..", "design"))
import design  # noqa: E402  (Aufbau wie in den Headless-Tests)

state = {}
AXIS = Part.LineSegment(App.Vector(0, 0, -100), App.Vector(0, 0, 100)).toShape()


def radius(b):
    return min(AXIS.distToShape(f)[0] for f in b.Shape.Faces if f.Surface.TypeId != "Part::GeomPlane")


def curved_face(b):
    return "Face%d" % [i for i, f in enumerate(b.Shape.Faces, 1) if f.Surface.TypeId != "Part::GeomPlane"][0]


def setup_fit():
    _, block = design.box(doc(), 40, 40, 10, at=(-20, -20))
    design.extrude(doc(), design.sketch(doc(), design.circle(0, 0, 10)), 10, op="Cut", bodies=[block])
    pin = design.extrude(doc(), design.sketch(doc(), design.circle(0, 0, 10), App.Placement(App.Vector(0, 0, -10), App.Rotation())), 30)[1]
    state.update(block=block, pin=pin)
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(block, curved_face(block))
    Gui.Selection.addSelection(pin, curved_face(pin))


def search(text):
    activate()
    QtTest.QTest.keyClick(mw, QtCore.Qt.Key_K, QtCore.Qt.ControlModifier)
    f = [e for e in visible(QtWidgets.QLineEdit) if e.accessibleName() == "Search"][0]
    QtTest.QTest.keyClicks(f, text)
    QtTest.QTest.keyClick(f, QtCore.Qt.Key_Return)


def titled(text):
    """Überschrift des Panels: Fenstertitel der Box oder Text eines Labels"""
    return any(w.windowTitle() == text for w in visible(QtWidgets.QWidget)) or text in [l.text() for l in visible(QtWidgets.QLabel)]


def play_label():
    labels = [l.text() for l in visible(QtWidgets.QLabel)]
    return [t for t in labels if t.endswith("µm") or t.endswith(" mm")]


def setup_screw():
    for o in list(doc().Objects):
        if o.TypeId == "Design::Body":
            o.Visibility = False
    _, low = design.box(doc(), 20, 20, 10, at=(60, -10))
    sk = design.sketch(doc(), design.rect(60, -10, 80, 10), App.Placement(App.Vector(0, 0, 10), App.Rotation()))
    up = design.extrude(doc(), sk, 5)[1]
    state.update(low=low, up=up)
    Gui.Selection.clearSelection()
    top = design.top_face(up)
    Gui.Selection.addSelection(doc().Name, up.Name, top, 70, 0, 15)


def fastener():
    return [o for o in doc().Objects if o.TypeId == "Design::Fastener"][-1]


in_order([
    ("activate", activate),
    ("setup fit", setup_fit),
    ("search", lambda: search("passung")),
    ("dialog", lambda: check("the search starts the fit with both faces",
                             len([o for o in doc().Objects if o.TypeId == "Design::Fitting"]) == 1
                             and len([o for o in doc().Objects if o.TypeId == "Design::Fitting"][0].Bodies) == 2)),
    ("print default", lambda: check("3D print normal is the default, the hole grows", abs(radius(state["block"]) - 10.2) < 1e-4,
                                    str(radius(state["block"])))),
    ("title", lambda: check("the panel is called Fit", titled("Fit"))),
    ("iso", lambda: choose("H7/g6", 3)),
    ("play", lambda: check("the play of H7/g6 shows in the dialog", "+7 … +41 µm" in play_label(), str(play_label()))),
    ("clearance hidden", lambda: check("ISO hides the print clearance", not shown("Clearance"))),
    ("nominal", lambda: check("Nominal shows the hole diameter it uses (not 0.00 mm) and stays automatic",
                              abs(field("Nominal").property("rawValue") - 20) < 1e-6
                              and [o for o in doc().Objects if o.TypeId == "Design::Fitting"][-1].Nominal.Value == 0,
                              str(field("Nominal").property("rawValue")))),
    ("shot fit", lambda: shot("fit")),
    ("ok", ok),
    ("fitted", lambda: check("both diameters in their field", 20 <= 2 * radius(state["block"]) <= 20.021
                             and 19.980 <= 2 * radius(state["pin"]) <= 19.993,
                             "%.4f %.4f" % (2 * radius(state["block"]), 2 * radius(state["pin"])))),
    ("setup screw", setup_screw),
    ("screw", lambda: Gui.runCommand("Design_Fastener")),
    ("created", lambda: check("a click on the top face screws both plates", list(fastener().Bodies) == [state["up"], state["low"]])),
    ("screw title", lambda: check("the panel is called Screw Here", titled("Screw Here"))),
    ("m3", lambda: choose("M3", 2)),
    ("insert", lambda: choose("Heat-set insert", 1)),
    ("length", lambda: check("the length follows the size", abs(field("Length").property("rawValue") - 8) < 1e-9, str(field("Length").property("rawValue")))),
    ("length locked", lambda: check("the automatic length is not editable", not field("Length").isEnabled())),
    ("shot screw", lambda: shot("screw")),
    ("ok screw", ok),
    ("insert hole", lambda: check("the lower plate has the insert hole", not state["low"].Shape.isInside(App.Vector(71.9, 0, 6), 1e-6, True))),
    ("errors", lambda: check("no errors", not errors(), str(errors()))),
])
