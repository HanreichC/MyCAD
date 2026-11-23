# SPDX-License-Identifier: LGPL-2.1-or-later
"""12.9 Sätze für Grundkörper und Wand in Strg+K: "Quader 40 x 30 x 10" öffnet den Quader mit diesen Maßen, OK legt
ihn an; "Wand 2 mm" höhlt den einzigen Körper mit 2 mm Wand aus; "Zylinder Ø20 x 30" öffnet den Zylinder"""
from harness import *

S = {}
W = ("wait", lambda: None)


def field():
    return [e for e in visible(QtWidgets.QLineEdit) if e.accessibleName() == "Search"][0]


def results():
    lists = [l for l in visible(QtWidgets.QListWidget) if l.accessibleName() == "Results"]
    return [lists[0].item(i).data(QtCore.Qt.AccessibleTextRole) for i in range(lists[0].count())] if lists else []


def say(text):
    Gui.runCommand("MyCAD_Search")
    f = field(); f.clear(); f.insert(text)  # keyClicks kann keine Umlaute


def first_hit(want):
    r = results()
    check("understood: " + want, bool(r) and r[0] == want, str(r[:3]))


def enter():
    QtTest.QTest.keyClick(field(), QtCore.Qt.Key_Return)


def last(type_id):
    found = [o for o in doc().Objects if o.TypeId == type_id]
    return found[-1] if found else None


def box_opened():
    p = last("Design::Primitive")
    check("Enter opens the box with 40 × 30 × 10", Gui.Control.activeDialog() and p is not None and p.Type == "Box"
          and (p.Length.Value, p.Width.Value, p.Height.Value) == (40, 30, 10), str(p and (p.Length, p.Width, p.Height)))


def box_made():
    b = last("Design::Body")
    S["body"] = b
    check("OK makes the box", b is not None and abs(b.Shape.Volume - 12000) < 1e-6, str(b and b.Shape.Volume))


def shelled():
    s = last("Design::Shell")
    check("Shell 2 mm opens with 2 mm", Gui.Control.activeDialog() and s is not None and abs(s.Size.Value - 2) < 1e-9,
          str(s and s.Size))


def hollow():
    check("OK hollows the box (closed, 2 mm walls)", abs(S["body"].Shape.Volume - (12000 - 36 * 26 * 6)) < 1e-3,
          str(S["body"].Shape.Volume))


def cylinder_opened():
    p = last("Design::Primitive")
    check("the cylinder opens with Ø20 and 30 high", Gui.Control.activeDialog() and p.Type == "Cylinder"
          and (p.Radius.Value, p.Height.Value) == (10, 30), str((p.Type, p.Radius, p.Height)))


run([("activate", activate),
     ("box", lambda: say("Quader 40 x 30 x 10")), W, ("box hit", lambda: first_hit("Box 40 × 30 × 10 mm")),
     ("enter b", enter), W, W, ("box opened", box_opened), ("ok b", ok), W, ("box made", box_made),
     ("none", lambda: Gui.Selection.clearSelection()),
     ("shell", lambda: say("Wand 2 mm")), W, ("shell hit", lambda: first_hit("Shell with 2 mm walls")),
     ("enter s", enter), W, W, ("shelled", shelled), ("ok s", ok), W, ("hollow", hollow),
     ("cyl", lambda: say("Zylinder Ø20 x 30")), W, ("cyl hit", lambda: first_hit("Cylinder ⌀ 20 mm, 30 mm high")),
     ("enter c", enter), W, W, ("cyl opened", cylinder_opened),
     ("errors", lambda: check("no errors", not errors(), str(errors()))),
     ])
