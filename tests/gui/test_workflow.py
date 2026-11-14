# SPDX-License-Identifier: LGPL-2.1-or-later
"""Arbeitsabläufe wie im echten Gebrauch (Befehle, Felder, Enter, Tastenkürzel), jeweils mit Volumen nachgerechnet:
1. Quader per Extrude, Skizze auf der Oberseite, Kreis, Extrude -5 mm wird von selbst Cut (wie Fusion; vorher vereinte ein
   Join nach innen still nichts), Grundmaß 40 -> 60, Rückgängig, Speichern und wieder Öffnen. Bohrung mit gewählter
   Seitenfläche nimmt nicht die Skizze oben (vorher bohrte sie dort), sondern wartet auf eine Skizze auf dieser Fläche.
   Noch einmal Extrude ohne Auswahl extrudiert die ausgeblendete Skizze nicht ein zweites Mal.
2. Rundung und Fase an Körperkanten (Wert tippen, Enter), Rundung nachträglich ändern, Rückgängig/Wiederholen, Fase aus der
   Mitte der Timeline löschen und das zurücknehmen.
   Bei offenem Rundungs-Dialog nimmt ein Klick auf eine Kante sie dazu, ein zweiter Klick wieder heraus (wie Fusion).
   Ebenso nimmt bei offenem Extrude ein Klick auf ein weiteres Profil der Skizze es dazu.
3. In der Skizze: Strg+Z nimmt die letzte Linie zurück, Strg+Y (wie Fusion) und Strg+Umschalt+Z holen sie wieder.
   Esc mit einer gewählten Kante hebt nur die Auswahl auf (vorher verließ es sofort die Skizze)."""
import math, os
from PySide6 import QtGui
from harness import *
import Design, Sketcher

S = {}
W = ("wait", lambda: None)
V = App.Vector


def vol():
    return sum(b.Shape.Volume for b in doc().Objects if b.TypeId == "Design::Body")


def volume(tag, want):
    check("%s: volume %.2f" % (tag, want), abs(vol() - want) < 0.05 and not errors() and not Gui.Control.activeDialog(),
          "vol=%.2f errors=%s dialog=%s" % (vol(), errors(), Gui.Control.activeDialog()))


def enter(label, value):
    """Wert tippen, Enter wie die Tastatur: an den 3D-Viewer, die Werkzeugleiste hat noch den Fokus"""
    type_field(label, value)
    button("Design_Extrude").setFocus()
    QtTest.QTest.keyClick(view(), QtCore.Qt.Key_Return)


# --- 1 ---------------------------------------------------------------------------------------------------------------
def base():
    d = doc(); root = [o for o in d.Objects if o.TypeId == "App::Part"][0]
    sk = Design.newSketch(root); S["base"] = sk
    for g in rect(0, 0, 40, 20):
        sk.addGeometry(g)
    for i in range(4):
        sk.addConstraint(Sketcher.Constraint("Coincident", i, 2, (i + 1) % 4, 1))
    for c in (("Horizontal", 0), ("Horizontal", 2), ("Vertical", 1), ("Vertical", 3), ("Coincident", 0, 1, -1, 1)):
        sk.addConstraint(Sketcher.Constraint(*c))
    S["w"] = sk.addConstraint(Sketcher.Constraint("DistanceX", 0, 1, 0, 2, 40.0))
    sk.addConstraint(Sketcher.Constraint("DistanceY", 1, 1, 1, 2, 20.0))
    d.recompute()


def extrude(sketch):
    prof = [o for o in sketch.InList if o.TypeId == "Design::Profiles"][0]
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(prof, "Face1")
    click(button("Design_Extrude"))


def body():
    return [o for o in doc().Objects if o.TypeId == "Design::Body"][0]


def extrude_again():
    Gui.Selection.clearSelection(); click(button("Design_Extrude"))


def no_second():
    n = len([o for o in doc().Objects if o.TypeId == "Design::Extrude"])
    check("Extrude again with nothing selected does not extrude the hidden sketch a second time",
          n == 1 and not Gui.Control.activeDialog(), "extrudes=%d dialog=%s" % (n, Gui.Control.activeDialog()))


def top_sketch():
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(body(), top_face(body()))
    click(button("Design_CreateSketch"))


def circle():
    s = Gui.ActiveDocument.getInEdit().Object; S["top"] = s
    c = s.Placement.inverse().multVec(V(20, 10, 10))
    s.addGeometry(Part.Circle(V(c.x, c.y, 0), V(0, 0, 1), 4))
    doc().recompute()
    Gui.ActiveDocument.resetEdit()


def auto_cut():
    e = [o for o in doc().Objects if o.TypeId == "Design::Extrude"][-1]
    check("extruding -5 mm into the body becomes Cut by itself", e.Operation == "Cut", str(e.Operation))


def side_hole():
    b = body()
    f = "Face%d" % (1 + [k for k, x in enumerate(b.Shape.Faces) if (x.normalAt(0, 0) - V(1, 0, 0)).Length < 1e-6][0])
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(b, f); click(button("Design_Hole"))


def no_hole():
    holes = [o for o in doc().Objects if o.TypeId == "Design::Hole"]
    check("Hole with a side face chosen does not drill at the sketch on top", not holes and not Gui.Control.activeDialog(),
          "holes=%s dialog=%s" % ([h.Sketch.Label for h in holes], Gui.Control.activeDialog()))


def widen():
    doc().openTransaction("Widen"); S["base"].setDatum(S["w"], App.Units.Quantity("60 mm")); doc().recompute(); doc().commitTransaction()


def reopen():
    p = os.path.join(os.path.dirname(os.environ["OUT"]), "workflow.mycad")
    doc().saveAs(p); App.closeDocument(doc().Name)
    App.openDocument(p); doc().recompute()


hole = math.pi * 16 * 5
one = [("base", base), W, ("extrude", lambda: extrude(S["base"])), W, ("10 mm", lambda: enter("Distance", "10")), W,
       ("box", lambda: volume("box 40x20x10", 8000)), ("again", extrude_again), W, ("no second", no_second),
       ("top", top_sketch), W, W, ("circle", circle), W, ("extrude 2", lambda: extrude(S["top"])), W,
       ("-5 mm", lambda: enter("Distance", "-5")), W, ("cut", auto_cut), ("hole", lambda: volume("hole r4 5 deep", 8000 - hole)),
       ("side hole", side_hole), W, ("no hole", no_hole),
       ("widen", widen), W, ("wide", lambda: volume("base 60 wide, hole follows", 12000 - hole)),
       ("undo", lambda: Gui.runCommand("Std_Undo")), W, ("narrow", lambda: volume("undo", 8000 - hole)),
       ("reopen", reopen), W, ("reopened", lambda: volume("saved and opened again", 8000 - hole)),
       ("close", lambda: App.closeDocument(doc().Name)), W, ("new", lambda: Gui.runCommand("Std_New")), W]


# --- 2 ---------------------------------------------------------------------------------------------------------------
def edge_at(x, y):
    b = S["b"]
    i = [k for k, e in enumerate(b.Shape.Edges) if abs(e.Vertexes[0].Point.z - e.Vertexes[-1].Point.z) > 9
         and abs(e.Vertexes[0].Point.x - x) < 1e-6 and abs(e.Vertexes[0].Point.y - y) < 1e-6][0]
    return "Edge%d" % (i + 1)


def dress(cmd, x, y):
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(S["b"], edge_at(x, y))
    click(button(cmd))


def delete_chamfer():
    c = [o for o in doc().Objects if o.TypeId == "Design::Chamfer"][0]
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(c)
    Gui.runCommand("Design_Delete")


def click_3d(p):
    vp = view().viewport(); dpr = vp.devicePixelRatioF()
    x, y = Gui.ActiveDocument.ActiveView.getPointOnViewport(p)
    q = QtCore.QPoint(int(x / dpr), int(vp.height() - y / dpr))
    QtTest.QTest.mouseMove(vp, q); QtTest.QTest.mouseClick(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, q)


def iso_box():
    S["b"] = make_body(rect(0, 0, 40, 20), 0, 10, "Box")
    v = Gui.ActiveDocument.ActiveView; v.viewIsometric(); Gui.SendMsgToActiveView("ViewFit")
    v.zoomOut(); v.zoomOut()  # Körper weg von den Glas-Panels am Rand (Xvfb-Fenster ist kleiner)


def remove_click():
    """Klick mitten auf die Rundungsfläche der Vorschau an der Kante (0, 0)"""
    r = [o for o in doc().Objects if o.TypeId == "Design::Fillet"][0].Size.Value
    k = r * (1 - 1 / math.sqrt(2))
    click_3d(V(k, k, 5))


def two_rects():
    d = doc(); root = [o for o in d.Objects if o.TypeId == "App::Part"][0]
    sk = Design.newSketch(root)
    for g in rect(0, 0, 20, 20) + rect(40, 0, 60, 20):
        sk.addGeometry(g)
    d.recompute()
    v = Gui.ActiveDocument.ActiveView; v.viewIsometric(); Gui.SendMsgToActiveView("ViewFit"); v.zoomOut(); v.zoomOut()
    prof = [o for o in sk.InList if o.TypeId == "Design::Profiles"][0]
    left = "Face%d" % (1 + [i for i, f in enumerate(prof.Shape.Faces) if f.CenterOfMass.x < 30][0])
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(prof, left); click(button("Design_Extrude"))


def both_profiles():
    e = [o for o in doc().Objects if o.TypeId == "Design::Extrude"][0]
    check("clicking a second profile while extruding adds it", len(e.Profile[1]) == 2, str(e.Profile[1]))


def edge_count(want):
    labels = [l.text() for l in visible(QtWidgets.QLabel) if "selected" in l.text()]
    check("the fillet dialog counts %d edges" % want, labels == ["%d selected" % want], str(labels))


f3, f5, c2 = (9 - math.pi * 9 / 4) * 10, (25 - math.pi * 25 / 4) * 10, 20
two = [("box 2", lambda: S.update(b=make_body(rect(0, 0, 40, 20), 0, 10, "Box"))), W,
       ("fillet", lambda: dress("Design_Fillet", 0, 0)), W, ("r3", lambda: enter("Radius", "3")), W,
       ("filleted", lambda: volume("fillet r3", 8000 - f3)),
       ("chamfer", lambda: dress("Design_Chamfer", 40, 0)), W, ("d2", lambda: enter("Distance", "2")), W,
       ("chamfered", lambda: volume("chamfer 2", 8000 - f3 - c2)),
       ("edit", lambda: Gui.ActiveDocument.setEdit([o for o in doc().Objects if o.TypeId == "Design::Fillet"][0])), W,
       ("r5", lambda: enter("Radius", "5")), W, ("edited", lambda: volume("fillet changed to r5", 8000 - f5 - c2)),
       ("undo 2", lambda: Gui.runCommand("Std_Undo")), W, ("undone", lambda: volume("undo change", 8000 - f3 - c2)),
       ("redo 2", lambda: Gui.runCommand("Std_Redo")), W, ("redone", lambda: volume("redo change", 8000 - f5 - c2)),
       ("delete", delete_chamfer), W, W, ("deleted", lambda: volume("chamfer deleted from the middle", 8000 - f5)),
       ("undo 3", lambda: Gui.runCommand("Std_Undo")), W, ("back", lambda: volume("undo delete", 8000 - f5 - c2)),
       ("close 2", lambda: App.closeDocument(doc().Name)), W, ("new 2", lambda: Gui.runCommand("Std_New")), W,
       ("box 3", iso_box), W, ("fillet 3", lambda: dress("Design_Fillet", 40, 0)), W,
       ("add", lambda: click_3d(V(40, 20, 5))), W, ("add 2", lambda: click_3d(V(0, 0, 5))), W, ("three", lambda: edge_count(3)),
       ("remove", remove_click), W, ("two", lambda: edge_count(2)), ("r2", lambda: enter("Radius", "2")), W,
       ("two rounded", lambda: volume("two edges rounded r2 by clicking", 8000 - 2 * (4 - math.pi) * 10)),
       ("close 3", lambda: App.closeDocument(doc().Name)), W, ("new 3", lambda: Gui.runCommand("Std_New")), W,
       ("two rects", two_rects), W, ("add profile", lambda: click_3d(V(50, 10, 0))), W, ("both", both_profiles),
       ("ok both", lambda: enter("Distance", "10")), W, ("two boxes", lambda: volume("both profiles extruded", 8000)),
       ("close 4", lambda: App.closeDocument(doc().Name)), W, ("new 4", lambda: Gui.runCommand("Std_New")), W]


# --- 3 ---------------------------------------------------------------------------------------------------------------
def sk():
    return Gui.ActiveDocument.getInEdit().Object


def press(p):
    vp = view().viewport(); dpr = vp.devicePixelRatioF()
    x, y = Gui.ActiveDocument.ActiveView.getPointOnViewport(p)
    q = QtCore.QPoint(int(x / dpr), int(vp.height() - y / dpr))
    for r in (q - QtCore.QPoint(1, 1), q):
        QtWidgets.QApplication.sendEvent(vp, QtGui.QMouseEvent(QtCore.QEvent.MouseMove, QtCore.QPointF(r), QtCore.QPointF(vp.mapToGlobal(r)),
                                                               QtCore.Qt.NoButton, QtCore.Qt.NoButton, QtCore.Qt.NoModifier))
    QtTest.QTest.mouseClick(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, q)


def key(k, mod=QtCore.Qt.NoModifier):
    QtTest.QTest.keyClick(QtWidgets.QApplication.focusWidget() or view(), k, mod)


def lines(want, tag):
    check("%s: %d lines" % (tag, want), sk().GeometryCount == want, str(sk().GeometryCount))


def draw(a, b):
    return [("line tool", lambda: click(button("Sketcher_CreateLine"))), W, ("from", lambda: press(a)), W, ("to", lambda: press(b)), W,
            ("esc", lambda: key(QtCore.Qt.Key_Escape)), W]


def zoom():
    sk().addGeometry(Part.Circle(V(0, 0, 0), V(0, 0, 1), 60)); doc().recompute(); Gui.SendMsgToActiveView("ViewFit")
    sk().delGeometry(0); doc().recompute()


three = [("sketch", lambda: click(button("Design_CreateSketch"))),
         ("pick XY", lambda: Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XY_Plane")][0])), W, W,
         ("zoom", zoom), W, *draw(V(-30, 0, 0), V(30, 0, 0)), *draw(V(-30, 20, 0), V(30, 25, 0)), ("two", lambda: lines(2, "drawn")),
         ("ctrl z", lambda: key(QtCore.Qt.Key_Z, QtCore.Qt.ControlModifier)), W, ("one", lambda: lines(1, "Ctrl+Z")),
         ("ctrl y", lambda: key(QtCore.Qt.Key_Y, QtCore.Qt.ControlModifier)), W, ("again", lambda: lines(2, "Ctrl+Y")),
         ("ctrl z 2", lambda: key(QtCore.Qt.Key_Z, QtCore.Qt.ControlModifier)), W,
         ("ctrl shift z", lambda: key(QtCore.Qt.Key_Z, QtCore.Qt.ControlModifier | QtCore.Qt.ShiftModifier)), W,
         ("again 2", lambda: lines(2, "Ctrl+Shift+Z")),
         ("select", lambda: (Gui.Selection.clearSelection(), Gui.Selection.addSelection(doc().Name, sk().Name, "Edge1"))), W,
         ("esc sel", lambda: key(QtCore.Qt.Key_Escape)), W,
         ("still", lambda: check("Esc with a selected edge only clears the selection and stays in the sketch",
                                 Gui.ActiveDocument.getInEdit() is not None and not Gui.Selection.getSelectionEx(),
                                 "in sketch=%s selection=%s" % (Gui.ActiveDocument.getInEdit() is not None, Gui.Selection.getSelectionEx())))]

run([("activate", activate), *one, *two, *three])
