# SPDX-License-Identifier: LGPL-2.1-or-later
"""Skizze duplizieren per Rechtsklick im Browser: genaue Kopie (Geometrie, Maße) mit eigenem Profil, in der Timeline,
sichtbar und gewählt. Original und Kopie sind danach unabhängig: Änderungen an der einen lassen die andere, wie sie ist.
Die Kopie lässt sich extrudieren."""
from harness import *
import Design
import Sketcher

S = {}
W = ("wait", lambda: None)


def setup():
    d = doc(); root = [o for o in d.Objects if o.TypeId == "App::Part"][0]
    sk = Design.newSketch(root)
    for g in rect(0, 0, 40, 20):
        sk.addGeometry(g)
    for i in range(4):
        sk.addConstraint(Sketcher.Constraint("Coincident", i, 2, (i + 1) % 4, 1))
    for i, kind in enumerate(("Horizontal", "Vertical", "Horizontal", "Vertical")):
        sk.addConstraint(Sketcher.Constraint(kind, i))
    sk.addConstraint(Sketcher.Constraint("Coincident", 0, 1, -1, 1))  # Ecke im Ursprung: das Maß verschiebt die rechte Seite
    S["dim"] = sk.addConstraint(Sketcher.Constraint("DistanceX", 0, 1, 0, 2, 40.0))
    d.recompute()
    sk.Visibility = False  # wie nach dem ersten Extrude
    S["sk"] = sk


def menu():
    """Echter Rechtsklick auf die Skizze im Browser, Menü fotografieren, echter Klick auf "Duplicate" """
    t = [w for w in visible(QtWidgets.QTreeWidget)][0]; t.expandAll()
    item = t.findItems(S["sk"].Label, QtCore.Qt.MatchExactly | QtCore.Qt.MatchRecursive)[0]
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(S["sk"])

    def pick():
        for m in visible(QtWidgets.QMenu):
            S["entries"] = [a.text() for a in m.actions() if a.text()]
            m.grab().save(os.environ["OUT"] + ".menu.png")
            r = m.actionGeometry([a for a in m.actions() if a.text() == "Duplicate"][0])
            QtTest.QTest.mouseMove(m.windowHandle(), r.center())
            QtTest.QTest.mouseClick(m.windowHandle(), QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, r.center())
    QtCore.QTimer.singleShot(800, pick)
    top = t
    while top.parentWidget():
        top = top.parentWidget()
    inner = t.viewport().mapTo(top, t.visualItemRect(item).center())
    win, p = mw.windowHandle(), view().viewport().mapTo(mw, view().mapFromScene(top.graphicsProxyWidget().mapToScene(QtCore.QPointF(inner))))
    QtTest.QTest.mouseMove(win, p)
    QtTest.QTest.mousePress(win, QtCore.Qt.RightButton, QtCore.Qt.NoModifier, p)
    QtTest.QTest.mouseRelease(win, QtCore.Qt.RightButton, QtCore.Qt.NoModifier, p)


def sketches():
    return [o for o in doc().Objects if o.TypeId == "Sketcher::SketchObject"]


def profiles(sk):
    return [o for o in sk.InList if o.TypeId == "Design::Profiles"]


def copied():
    L("menu=%s" % S.get("entries"))
    all = sketches()
    check("the browser menu offers Duplicate and it makes a second sketch", len(all) == 2, str([s.Label for s in all]))
    copy = [s for s in all if s is not S["sk"]][0]; S["copy"] = copy
    check("the copy has the same geometry and dimensions",
          len(copy.Geometry) == 4 and len(copy.Constraints) == len(S["sk"].Constraints)
          and abs(copy.Constraints[S["dim"]].Value - 40) < 1e-9, "geo=%d cons=%d" % (len(copy.Geometry), len(copy.Constraints)))
    check("the copy has its own profile with one closed area",
          len(profiles(copy)) == 1 and profiles(copy)[0] is not profiles(S["sk"])[0]
          and len(profiles(copy)[0].Shape.Faces) == 1)
    check("the copy is in the timeline, named after the original, visible and selected",
          copy in Design.timeline(doc()) and copy.Label == S["sk"].Label + " (copy)" and copy.Visibility
          and [o.Object for o in Gui.Selection.getSelectionEx()] == [copy],
          "label=%s visible=%s" % (copy.Label, copy.Visibility))


def independent():
    copy, sk = S["copy"], S["sk"]
    copy.setDatum(S["dim"], App.Units.Quantity("60 mm")); doc().recompute()
    sk.addGeometry(Part.LineSegment(App.Vector(0, 0, 0), App.Vector(40, 20, 0))); doc().recompute()
    xmax = lambda s: max(v.Point.x for v in s.Shape.Vertexes)
    check("changing the copy leaves the original as it is, and the other way round",
          abs(xmax(copy) - 60) < 1e-6 and abs(xmax(sk) - 40) < 1e-6 and len(copy.Geometry) == 4 and len(sk.Geometry) == 5,
          "copy x=%.2f geo=%d original x=%.2f geo=%d" % (xmax(copy), len(copy.Geometry), xmax(sk), len(sk.Geometry)))


def extrude():
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(profiles(S["copy"])[0], "Face1")
    click(button("Design_Extrude"))


def extruded():
    bodies = [o for o in doc().Objects if o.TypeId == "Design::Body"]
    check("the copy extrudes", len(bodies) == 1 and abs(bodies[0].Shape.Volume - 60 * 20 * 10) < 1e-6,
          str([(b.Label, b.Shape.Volume) for b in bodies]))
    check("no errors", not errors(), str(errors()))


run([("activate", activate), ("setup", setup), W, ("menu", menu), W, W, ("copied", copied),
     ("independent", independent), W, ("extrude", extrude), W, ("ok", ok), W, ("extruded", extruded)])
