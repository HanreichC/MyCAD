# SPDX-License-Identifier: LGPL-2.1-or-later
"""Konstruktion und Prüfen am Quader 60x40x15: Ebene durch drei Ecken, Achse durch zwei Ecken, Punkt auf einer Ecke,
Mittelebene zwischen Ober- und Unterseite, Messen (Fläche, Abstand, Winkel), Schnittansicht an/aus.
Achse aus einer Zylinderfläche abseits des Ursprungs, versetzte Ebene mittig über der Fläche und so groß wie der Körper,
Abstand und Winkel per Doppelklick im Browser ändern (Abbrechen stellt wieder her)."""
from harness import *
import math


def box():
    return body("Box")


def vertices(z):
    return ["Vertex%d" % (i + 1) for i, v in enumerate(box().Shape.Vertexes) if abs(v.Z - z) < 1e-6]


def faces(z):
    return ["Face%d" % (i + 1) for i, f in enumerate(box().Shape.Faces) if abs(f.CenterOfMass.z - z) < 1e-6]


def select(subs):
    Gui.Selection.clearSelection()
    for s in subs:
        Gui.Selection.addSelection(doc().Name, box().Name, s)


def datum(label):
    o = [o for o in doc().Objects if o.Label == label][-1]
    return o


def placement(label):
    o = datum(label); p = o.Placement
    return "%s mode=%s base=(%.1f, %.1f, %.1f) z-axis=%s" % (label, o.MapMode, p.Base.x, p.Base.y, p.Base.z,
                                                            tuple(round(c, 2) for c in p.Rotation.multVec(App.Vector(0, 0, 1))))


def newest(type_id):
    return [o for o in doc().Objects if o.TypeId == type_id][-1]


def near(v, x, y, z):
    return abs(v.x - x) < 1e-6 and abs(v.y - y) < 1e-6 and abs(v.z - z) < 1e-6


def cyl_axis():
    cyl = body("Cyl")
    Gui.Selection.clearSelection()
    for i, f in enumerate(cyl.Shape.Faces):
        if f.Surface.__class__.__name__ == "Cylinder":
            Gui.Selection.addSelection(doc().Name, cyl.Name, "Face%d" % (i + 1))
    Gui.runCommand("Design_Axis")


def axis_ok():
    a = newest("PartDesign::Line"); p = a.Placement
    d = p.Rotation.multVec(App.Vector(0, 0, 1))
    check("axis of a cylindrical face runs through its centre line", a.isValid() and abs(p.Base.x - 100) < 1e-6
          and abs(p.Base.y - 20) < 1e-6 and abs(abs(d.z) - 1) < 1e-6, "%s valid=%s base=%s dir=%s" % (a.MapMode, a.isValid(), p.Base, d))
    check("axes are opaque, planes translucent", a.ViewObject.Transparency == 0 and datum("Plane").ViewObject.Transparency == 80)


def offset_ok(z):
    p = newest("PartDesign::Plane")
    check("offset plane centred over the face, sized from its body", near(p.Placement.Base, 30, 20, z) and abs(p.Length - 72) < 1e-6,
          "base=%s length=%s" % (p.Placement.Base, p.Length))


def browser_dclick(obj):
    t = visible(QtWidgets.QTreeWidget)[0]; t.expandAll()
    it = t.findItems(obj.Label, QtCore.Qt.MatchExactly | QtCore.Qt.MatchRecursive)[-1]
    t.scrollToItem(it); QtWidgets.QApplication.processEvents()
    QtTest.QTest.mouseDClick(t.viewport(), QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, t.visualItemRect(it).center())


def spin_text():
    return [b.text() for b in visible(QtWidgets.QAbstractSpinBox)]


def cancel():
    [b for b in visible(QtWidgets.QPushButton) if b.text().replace("&", "") == "Cancel"][0].click()


def measured():
    return [l.text() for l in visible(QtWidgets.QLabel) if "<table>" in l.text() or "Select a point" in l.text()]


def clipped():
    return Gui.ActiveDocument.ActiveView.hasClippingPlane()


def shadow_points():
    """Ecken des Kontaktschattens (0: kein Schatten): Viereck mit Maske (SoTexture2) und Shader in einem Separator"""
    from pivy import coin
    search = coin.SoSearchAction(); search.setType(coin.SoTexture2.getClassTypeId()); search.setInterest(coin.SoSearchAction.ALL)
    search.apply(Gui.ActiveDocument.ActiveView.getSceneGraph())
    for path in search.getPaths():
        sep = path.getNodeFromTail(1)
        kids = [sep.getChild(i) for i in range(sep.getNumChildren())]
        coords = [k for k in kids if k.isOfType(coin.SoCoordinate3.getClassTypeId())]
        if coords and any(k.isOfType(coin.SoShaderProgram.getClassTypeId()) for k in kids):
            return coords[0].point.getNum()
    return None


run([
    ("setup", lambda: make_body(rect(0, 0, 60, 40), 0, 15, "Box")),
    ("3 points", lambda: select(vertices(15)[:3])), ("plane", lambda: click(button("Design_OffsetPlane|Design_Midplane|Design_Plane|Design_Axis|Design_Point")) if False else Gui.runCommand("Design_Plane")),
    ("plane?", lambda: L(placement("Plane"))),
    ("2 points", lambda: select(vertices(0)[:2])), ("axis", lambda: Gui.runCommand("Design_Axis")),
    ("axis?", lambda: L(placement("Axis"))),
    ("vertex", lambda: select(vertices(15)[:1])), ("point", lambda: Gui.runCommand("Design_Point")),
    ("point?", lambda: L(placement("Point"))),
    ("top+bottom", lambda: select(faces(15) + faces(0))), ("midplane", lambda: Gui.runCommand("Design_Midplane")),
    ("midplane?", lambda: L(placement("Midplane"))),
    ("edge", lambda: select(["Edge%d" % (i + 1) for i, e in enumerate(box().Shape.Edges)
                             if abs(e.CenterOfMass.z - 15) < 1e-6 and abs(e.CenterOfMass.y) < 1e-6
                             and abs(e.Vertexes[0].Y - e.Vertexes[1].Y) < 1e-6])),
    ("angle plane", lambda: Gui.runCommand("Design_AnglePlane")), ("ok angle", ok),
    ("angle?", lambda: L(placement("Plane001") + " (Normale ~(0, ±0.71, 0.71), durch y=0 z=15)")),
    ("angle centred", lambda: check("plane at angle centred on the edge", near(datum("Plane001").Placement.Base, 30, 0, 15),
                                    str(datum("Plane001").Placement.Base))),
    ("cylinder", lambda: make_body([Part.Circle(App.Vector(100, 20, 0), App.Vector(0, 0, 1), 10)], 0, 30, "Cyl")),
    ("cyl axis", cyl_axis), ("cyl axis?", axis_ok),
    ("top", lambda: select(faces(15))), ("offset", lambda: Gui.runCommand("Design_OffsetPlane")), ("ok offset", ok),
    ("offset?", lambda: offset_ok(25)),
    ("edit offset", lambda: browser_dclick(newest("PartDesign::Plane"))),
    ("edit open", lambda: check("double-click reopens Offset Plane with its distance", "10.00 mm" in spin_text(), str(spin_text()))),
    ("type 5", lambda: type_into(0, "5")), ("ok edit", ok), ("edited", lambda: offset_ok(20)),
    ("edit again", lambda: browser_dclick(newest("PartDesign::Plane"))), ("type 7", lambda: type_into(0, "7")),
    ("cancel edit", cancel), ("restored", lambda: offset_ok(20)),
    ("edit angle", lambda: browser_dclick(datum("Plane001"))),
    ("angle open", lambda: check("double-click reopens Plane at Angle with its angle", any(t.startswith("45") for t in spin_text()),
                                 str(spin_text()))),
    ("type 30", lambda: type_into(0, "30")), ("cancel angle", cancel),
    ("angle restored", lambda: check("cancel restores the angle", abs(datum("Plane001").AttachmentOffset.Rotation.Angle - math.pi / 4) < 1e-6,
                                     str(datum("Plane001").AttachmentOffset))),
    ("measure", lambda: click(button("Design_Measure"))),
    ("top face", lambda: select(faces(15))), ("m1", lambda: L("measure 1: %s" % measured())),
    ("two faces", lambda: select(faces(15) + faces(0))), ("m2", lambda: L("measure 2: %s" % measured())),
    ("shot measure", lambda: shot("measure")),
    ("close", lambda: [b.click() for b in visible(QtWidgets.QPushButton) if b.text().replace("&", "") == "Close"]),
    ("section", lambda: (select(faces(15)), Gui.runCommand("Design_Section"))),
    ("clip on", lambda: (L("clipping=%s" % clipped()), shot("section"))),
    ("section off", lambda: Gui.runCommand("Design_Section")),
    ("clip off", lambda: L("clipping=%s" % clipped())),
    ("body measure", lambda: (Gui.Selection.clearSelection(), Gui.Selection.addSelection(box()), click(button("Design_Measure")))),
    ("m3", lambda: L("measure body: %s" % measured())),
    ("errors", lambda: L("errors=%s" % errors())),
    ("only datums", lambda: (Gui.Control.closeDialog(), setattr(box(), "Visibility", False))), ("wait", lambda: None),
    ("no datum shadow", lambda: check("planes, axes and points cast no contact shadow", shadow_points() == 0, str(shadow_points()))),
])
