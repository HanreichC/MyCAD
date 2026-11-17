# SPDX-License-Identifier: LGPL-2.1-or-later
"""Phase 11.6 "Was fehlt noch?": in der Sketch Palette sagt eine Zeile, wie viele Maße fehlen; ein Klick ergänzt sie
nach Absicht (Rechteck mittig um den Ursprung -> symmetrisch, Breite, Höhe), danach steht dort "Fully defined".
"Show What Can Move" wählt, was noch frei ist."""
import Sketcher
from harness import *

S = {}
W = ("wait", lambda: None)


def rows():
    return [b for b in visible(QtWidgets.QToolButton) if b.objectName() == "PaletteRow"]


def row(word):
    r = [b for b in rows() if word in b.text()]
    return r[0] if r else None


def rectangle():
    sk = Gui.ActiveDocument.getInEdit().Object
    pts = [App.Vector(-10, -5, 0), App.Vector(10, -5, 0), App.Vector(10, 5, 0), App.Vector(-10, 5, 0)]
    for i in range(4):
        sk.addGeometry(Part.LineSegment(pts[i], pts[(i + 1) % 4]))
    for i in range(4):
        sk.addConstraint(Sketcher.Constraint("Coincident", i, 2, (i + 1) % 4, 1))
    for i, kind in enumerate(("Horizontal", "Vertical", "Horizontal", "Vertical")):
        sk.addConstraint(Sketcher.Constraint(kind, i))
    doc().recompute()
    S["sk"] = sk


def missing():
    r = row("missing")
    check("the palette says how many dimensions are missing", r is not None and r.text() == "4 dimensions missing",
          str([b.text() for b in rows()]))
    shot("missing")


def can_move():
    click(row("Move"))


def selected():
    sel = [n for s in Gui.Selection.getSelectionEx() for n in s.SubElementNames]
    check("Show What Can Move selects the free elements", len(sel) >= 4, str(sel))
    Gui.Selection.clearSelection()


def complete():
    click(row("missing"))


def done():
    sk = S["sk"]
    kinds = sorted(c.Type for c in sk.Constraints if c.Type in ("Symmetric", "Distance"))
    r = row("Fully")
    check("one click adds them by intent and the row says Fully defined",
          kinds == ["Distance", "Distance", "Symmetric"] and r is not None and r.text() == "Fully defined",
          "%s rows=%s" % (kinds, [b.text() for b in rows()]))
    shot("done")


def undone():
    check("Ctrl+Z takes the dimensions back", not [c for c in S["sk"].Constraints if c.Type in ("Symmetric", "Distance")]
          and row("missing") is not None, str([b.text() for b in rows()]))


run([("activate", activate),
     ("Create Sketch", lambda: click(button("Design_CreateSketch"))), W,
     ("pick XY", lambda: Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XY_Plane")][0])), W,
     ("rectangle", rectangle), W, W, ("missing", missing),
     ("move", can_move), W, ("selected", selected),
     ("complete", complete), W, W, ("done", done),
     ("undo", lambda: Gui.runCommand("Std_Undo")), W, W, ("undone", undone),
     ("leave", lambda: click(button("Sketcher_LeaveSketch"))), W,
     ("errors", lambda: check("no errors", not errors(), str(errors()))),
     ])
