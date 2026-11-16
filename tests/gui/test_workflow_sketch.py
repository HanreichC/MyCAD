# SPDX-License-Identifier: LGPL-2.1-or-later
"""Skizzieren auf einer Körperfläche wie im echten Gebrauch (Mausklicks, Felder, Enter):
1. Rechteck mit zwei Klicks auf die projizierten Ecken, Ecke abrunden (Feld: 2 mm), fertig, Extrude 5 per Enter;
   Skizze wieder öffnen, Radius 4 -> der Körper folgt.
2. Kreis, Bemaßung Mittelpunkt -> projizierte Kante (5 mm tippen): kein Konflikt, Mittelpunkt sitzt 5 mm vom Rand.
3. Versatz einer projizierten Kante versetzt den ganzen projizierten Umriss (vorher nur die eine Kante).
4. Grundskizze wird vom Rechteck zum L (zwei Linien schneiden eine Ecke ab, Flächennummern verschieben sich): die
   Skizze auf der Oberseite bleibt oben.
5. Skizze auf der Oberseite einer Rundung: Rundung löschen hängt die Skizze an dieselbe Fläche davor (vorher löste sie
   sich still). Den Schritt löschen, der die Fläche erzeugt hat: die Skizze bleibt an ihrem Platz, bekommt eine Warnung
   in der Timeline und es kommt ein Hinweis."""
import math
import shiboken6
from PySide6 import QtGui
from collections import Counter
from harness import *

S = {}
W = ("wait", lambda: None)
V = App.Vector


def sk():
    return Gui.ActiveDocument.getInEdit().Object


def vol():
    return sum(b.Shape.Volume for b in doc().Objects if b.TypeId == "Design::Body")


def screen(p):
    vp = view().viewport(); dpr = vp.devicePixelRatioF()
    x, y = Gui.ActiveDocument.ActiveView.getPointOnViewport(p)
    return QtCore.QPoint(int(x / dpr), int(vp.height() - y / dpr))


def press(p, dx=0, dy=0):
    vp = view().viewport(); q = screen(p) + QtCore.QPoint(dx, dy)
    for r in (q - QtCore.QPoint(1, 1), q):
        QtWidgets.QApplication.sendEvent(vp, QtGui.QMouseEvent(QtCore.QEvent.MouseMove, QtCore.QPointF(r), QtCore.QPointF(vp.mapToGlobal(r)),
                                                               QtCore.Qt.NoButton, QtCore.Qt.NoButton, QtCore.Qt.NoModifier))
    QtTest.QTest.mouseClick(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, q)


def keys(*ks):
    """Tasten ins Wertfeld des modalen Maß-Fensters (veraltete PySide-Hüllen verwerfen, s. test_sketch_fillet_radius)"""
    m = QtWidgets.QApplication.activeModalWidget()
    box = m.findChild(QtWidgets.QAbstractSpinBox)
    while not shiboken6.isValid(box):
        shiboken6.invalidate(box); box = m.findChild(QtWidgets.QAbstractSpinBox)
    box.setFocus(); box.lineEdit().selectAll()
    for k in ks:
        QtTest.QTest.keyClick(box, k)


def body():
    return [o for o in doc().Objects if o.TypeId == "Design::Body"][0]


def top_sketch():
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(body(), top_face(body()))
    click(button("Design_CreateSketch"))


def clean(tag):
    s = sk(); s.solve()
    check("%s: no redundant or conflicting constraints" % tag, not s.RedundantConstraints and not s.ConflictingConstraints,
          "redundant=%s conflicting=%s" % (s.RedundantConstraints, s.ConflictingConstraints))


def volume(tag, want):
    check("%s: volume %.2f" % (tag, want), abs(vol() - want) < 0.05 and not errors(), "vol=%.2f errors=%s" % (vol(), errors()))


def fresh():
    for d in list(App.listDocuments()):
        App.closeDocument(d)
    Gui.runCommand("Std_New")


# --- 1 ---------------------------------------------------------------------------------------------------------------
def leave():
    S["top"] = sk(); Gui.ActiveDocument.resetEdit()


def extrude():
    prof = [o for o in S["top"].InList if o.TypeId == "Design::Profiles"][0]
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(prof, "Face1")
    click(button("Design_Extrude"))


def enter5():
    type_field("Distance", "5"); button("Design_Extrude").setFocus(); QtTest.QTest.keyClick(view(), QtCore.Qt.Key_Return)


def radius4():
    s = sk(); i = [k for k, c in enumerate(s.Constraints) if c.Type == "Radius"][0]
    doc().openTransaction("r4"); s.setDatum(i, App.Units.Quantity("4 mm")); doc().recompute(); doc().commitTransaction()


r2, r4 = 200 - (4 - math.pi), 200 - (16 - 4 * math.pi)
one = [("box", lambda: make_body(rect(0, 0, 20, 10), 0, 10, "Box")), W, ("top", top_sketch), W, W,
       ("fit", lambda: Gui.SendMsgToActiveView("ViewFit")), W,
       ("rect tool", lambda: click(button("Sketcher_CompCreateRectangles"))), W,
       ("corner 1", lambda: press(V(0, 0, 10), 3, -3)), W, ("corner 2", lambda: press(V(20, 10, 10), -3, 3)), W,
       ("esc", lambda: QtTest.QTest.keyClick(view().viewport(), QtCore.Qt.Key_Escape)), W,
       ("fillet tool", lambda: Gui.runCommand("Sketcher_CreateFillet")), W,
       ("corner", lambda: QtCore.QTimer.singleShot(0, lambda: press(V(20, 10, 10)))), W, W,
       ("2 mm", lambda: keys("2", QtCore.Qt.Key_Return)), W,
       ("esc 2", lambda: QtTest.QTest.keyClick(view().viewport(), QtCore.Qt.Key_Escape)), W, ("clean", lambda: clean("rounded rectangle")),
       ("leave", leave), W, W, ("extrude", extrude), W, ("5 mm", enter5), W,
       ("v1", lambda: volume("rounded rectangle extruded 5", 2000 + r2 * 5)),
       ("reopen", lambda: Gui.ActiveDocument.setEdit(S["top"])), W, W, ("radius 4", radius4), W,
       ("leave 2", lambda: Gui.ActiveDocument.resetEdit()), W, W, ("v2", lambda: volume("radius changed to 4", 2000 + r4 * 5))]


# --- 2 ---------------------------------------------------------------------------------------------------------------
def circle():
    s = sk(); c = s.Placement.inverse().multVec(V(12, 6, 10))
    s.addGeometry(Part.Circle(V(c.x, c.y, 0), V(0, 0, 1), 2)); doc().recompute()
    for i, g in enumerate(s.ExternalGeo[2:]):
        if hasattr(g, "StartPoint") and abs(s.Placement.multVec(g.StartPoint).y) < 1e-6 and abs(s.Placement.multVec(g.EndPoint).y) < 1e-6:
            S["edge"] = "ExternalEdge%d" % (i + 1)


def dimension():
    s = sk(); Gui.Selection.clearSelection()
    Gui.Selection.addSelection(doc().Name, s.Name, "Vertex1"); Gui.Selection.addSelection(doc().Name, s.Name, S["edge"])
    click(button("Sketcher_Dimension"))
    QtCore.QTimer.singleShot(300, lambda: press(V(16, 3, 10)))


def at_five():
    c = sk().Placement.multVec(sk().Geometry[0].Center)
    check("circle center sits 5 mm from the projected edge", abs(c.y - 5) < 1e-6, "y=%.4f" % c.y)


two = [("fresh", fresh), W, ("box 2", lambda: make_body(rect(0, 0, 40, 20), 0, 10, "Box")), W, ("top 2", top_sketch), W, W,
       ("fit 2", lambda: Gui.SendMsgToActiveView("ViewFit")), W, ("circle", circle), ("dimension", dimension), W, W,
       ("5", lambda: keys("5", QtCore.Qt.Key_Return)), W, ("at 5", at_five), ("clean 2", lambda: clean("distance to projected edge"))]


# --- 3 ---------------------------------------------------------------------------------------------------------------
def offset_outline():
    s = sk()
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(doc().Name, s.Name, "ExternalEdge1")


def offset_click():
    QtCore.QTimer.singleShot(200, lambda: press(V(20, 3, 10)))
    QtCore.QTimer.singleShot(500, lambda: press(V(20, 2, 10)))


def outline():
    kinds = dict(Counter(g.TypeId.split("::")[1] for g in sk().Geometry))  # dazu der Kreis aus Teil 2
    check("offset of one projected edge offsets the whole projected outline", kinds.get("GeomLineSegment") == 4, str(kinds))


three = [("offset", offset_outline), W, ("tool", lambda: click(button("Sketcher_Offset"))), W, ("click", offset_click), W, W, ("outline", outline),
         ("esc 3", lambda: QtTest.QTest.keyClick(view().viewport(), QtCore.Qt.Key_Escape)), W]


# --- 4 ---------------------------------------------------------------------------------------------------------------
def base_and_extrude():
    import Design
    d = doc(); root = [o for o in d.Objects if o.TypeId == "App::Part"][0]
    S["base"] = Design.newSketch(root)
    for g in rect(0, 0, 40, 20):
        S["base"].addGeometry(g)
    d.recompute()
    prof = [o for o in S["base"].InList if o.TypeId == "Design::Profiles"][0]
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(prof, "Face1")
    click(button("Design_Extrude"))


def ok_enter():
    button("Design_Extrude").setFocus(); QtTest.QTest.keyClick(view(), QtCore.Qt.Key_Return)


def circle_leave():
    s = sk(); S["top"] = s; c = s.Placement.inverse().multVec(V(10, 10, 10))
    s.addGeometry(Part.Circle(V(c.x, c.y, 0), V(0, 0, 1), 3)); doc().recompute()
    Gui.ActiveDocument.resetEdit()


def make_l():
    """Rechteck 40x20 -> L: zwei Linien schneiden die rechte obere Ecke 15x10 ab (das größere Teilprofil teilt die meisten
    Kanten mit dem alten und bleibt das Profil des Extrudes)"""
    sk_ = S["base"]; doc().openTransaction("L")
    sk_.addGeometry(Part.LineSegment(V(25, 20, 0), V(25, 10, 0)))
    sk_.addGeometry(Part.LineSegment(V(25, 10, 0), V(40, 10, 0)))
    doc().recompute(); doc().commitTransaction()


def still_on_top():
    s = S["top"]; n = s.Placement.Rotation.multVec(V(0, 0, 1))
    check("the sketch on the top face stays on top when the base becomes an L", abs(s.Placement.Base.z - 10) < 1e-6
          and abs(n.z - 1) < 1e-6 and s.getStatusString() == "Valid", "z=%.2f n=%s %s on %s" % (s.Placement.Base.z, n, s.getStatusString(), s.AttachmentSupport))
    volume("L-shaped base", 6500)


four = [("fresh 4", fresh), W, ("base", base_and_extrude), W, ("ok", ok_enter), W, ("top 4", top_sketch), W, W, ("circle 4", circle_leave), W,
        ("L", make_l), W, ("on top", still_on_top)]

# --- 5 ---------------------------------------------------------------------------------------------------------------
def fillet_corner():
    b = body()
    i = [k for k, e in enumerate(b.Shape.Edges) if abs(e.Vertexes[0].Point.z - e.Vertexes[-1].Point.z) > 9
         and abs(e.Vertexes[0].Point.x - 40) < 1e-6 and abs(e.Vertexes[0].Point.y - 20) < 1e-6][0]
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(b, "Edge%d" % (i + 1)); click(button("Design_Fillet"))


def delete(type_id):
    Gui.Selection.clearSelection(); Gui.Selection.addSelection([o for o in doc().Objects if o.TypeId == type_id][0])
    Gui.runCommand("Design_Delete")


def on_base():
    s = S["top"]; sup = s.AttachmentSupport
    check("deleting the fillet under a sketch attaches it to the same face before the fillet",
          sup and sup[0][0].TypeId == "Design::Extrude" and abs(s.Placement.Base.z - 10) < 1e-6 and not getattr(s, "Warning", ""),
          "support=%s z=%.2f warning=%s" % (sup, s.Placement.Base.z, getattr(s, "Warning", "")))


def warned():
    s = S["top"]
    check("deleting the step that made the face keeps the sketch in place, with a warning in the timeline",
          not s.AttachmentSupport and abs(s.Placement.Base.z - 10) < 1e-6 and s.getStatusString() == "Valid"
          and getattr(s, "Warning", "").startswith("Face gone"),
          "support=%s z=%.2f %s warning=%s" % (s.AttachmentSupport, s.Placement.Base.z, s.getStatusString(), getattr(s, "Warning", "")))
    tips = [b.toolTip() for b in timeline() if b.toolTip().startswith(s.Label)]
    check("the timeline entry of the sketch explains the warning", any("Face gone" in t for t in tips), str(tips))
    check("a hint says that the sketch no longer lies on a face", any("no longer lies on a face" in n for n in notices()), str(notices()))


five = [("fresh 5", fresh), W, ("box 5", lambda: make_body(rect(0, 0, 40, 20), 0, 10, "Box")), W,
        ("fillet", fillet_corner), W, ("r3", lambda: type_field("Radius", "3")), ("ok 5", ok_enter), W,
        ("top 5", top_sketch), W, W, ("circle 5", circle_leave), W,
        ("on fillet", lambda: check("the sketch lies on the fillet's top face", S["top"].AttachmentSupport[0][0].TypeId == "Design::Fillet",
                                    str(S["top"].AttachmentSupport))),
        ("del fillet", lambda: delete("Design::Fillet")), W, W, ("on base", on_base),
        ("del extrude", lambda: delete("Design::Extrude")), W, W, ("warned", warned)]

run([("activate", activate), *one, *two, *three, *four, *five])
