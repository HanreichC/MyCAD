# SPDX-License-Identifier: LGPL-2.1-or-later
"""Bilder für die Hilfe: baut für jedes Werkzeug ein kleines Beispiel in MyCAD (wie von Hand: auswählen, Werkzeug,
Werte, OK) und speichert den Bildausschnitt als src/Gui/Shell/help/images/<artikel>.png. Danach help_content.py.
    MYCAD_HOME=/tmp/helphome MYCAD_TIMEOUT=1800 tests/gui/run.sh tools/help_images.py /tmp/helpimg
    python3 tools/help_content.py
Nur einzelne Artikel: HELP_ONLY=Design_Revolve,sketch_line vor den Aufruf setzen."""
import math
import os
import sys

sys.path.insert(0, "/workspace/tests/gui")
import Sketcher
from harness import *

OUT = "/workspace/src/Gui/Shell/help/images"
ONLY = [s for s in os.environ.get("HELP_ONLY", "").split(",") if s]
steps = []
st = {}
V = App.Vector


def step(name, fn):
    steps.append((name, fn))


def wait(n=1):
    for _ in range(n):
        step("wait", lambda: None)


# --- Bausteine ------------------------------------------------------------------------------------------------------
def sketch(geos, z=0, plane="XY", construction=(), name="Sketch"):
    """Skizze (ohne Werkzeug-Dialog) mit Profilen; plane XZ: Skizzen-y zeigt nach oben"""
    d = doc(); root = [o for o in d.Objects if o.TypeId == "App::Part"][0]
    sk = d.addObject("Sketcher::SketchObject", name)
    if plane == "XZ":
        sk.Placement = App.Placement(V(0, 0, 0), App.Rotation(V(1, 0, 0), 90))
    sk.Placement.Base.z = z
    for g in geos:
        sk.addGeometry(g, False)
    for g in construction:
        sk.addGeometry(g, True)
    d.getObject("Sketches").addObject(sk)
    prof = d.addObject("Design::Profiles", "Profiles"); prof.Sketch = sk; root.addObject(prof)
    d.recompute()
    return sk, prof


def circle(x, y, r):
    return Part.Circle(V(x, y, 0), V(0, 0, 1), r)


def box(x0, y0, x1, y1, h, z=0, name="Box"):
    return make_body(rect(x0, y0, x1, y1), z, h, name)


def faces(b, pred):
    return ["Face%d" % (i + 1) for i, f in enumerate(b.Shape.Faces) if pred(f)]


def normal(f):
    u0, u1, v0, v1 = f.ParameterRange
    return f.normalAt((u0 + u1) / 2, (v0 + v1) / 2)


def top(b):
    return top_face(b)


def sides(b):
    return faces(b, lambda f: f.Surface.TypeId == "Part::GeomPlane" and abs(normal(f).z) < 1e-6)


def cylindrical(b):
    return faces(b, lambda f: f.Surface.TypeId == "Part::GeomCylinder")


def select(obj, *subs):
    Gui.Selection.clearSelection()
    for s in subs or ("",):
        Gui.Selection.addSelection(doc().Name, obj.Name, s)


def add_select(obj, *subs):
    for s in subs or ("",):
        Gui.Selection.addSelection(doc().Name, obj.Name, s)


def ring_face(prof):
    return "Face%d" % (1 + max(range(len(prof.Shape.Faces)), key=lambda i: prof.Shape.Faces[i].Area))


def combo(text):
    for c in visible(QtWidgets.QComboBox):
        i = c.findText(text)
        if i >= 0:
            c.setCurrentIndex(i)
            return


def last(type_id):
    return [o for o in doc().Objects if o.TypeId == type_id][-1]


def accept():
    """OK des Werkzeug-Dialogs direkt auslösen (ein Klick auf die Bildschirmposition kommt nicht immer an)"""
    buttons = [b for b in visible(QtWidgets.QPushButton) if b.text().replace("&", "") == "OK"]
    if buttons:
        buttons[0].click()


def feature(cmd, *setup, wait_before=1):
    """Werkzeug-Befehl mit offenem Dialog: Felder setzen, OK"""
    step(cmd, lambda: Gui.runCommand(cmd))
    wait(wait_before)
    for s in setup:
        step("set", s)
    wait()
    step("ok", accept)
    wait()


# --- Bild aufnehmen -------------------------------------------------------------------------------------------------
def shot(article, view="iso", zoom=0, fixed=False):
    def pose():
        Gui.Selection.clearSelection()
        v = Gui.ActiveDocument.ActiveView
        {"iso": v.viewIsometric, "top": v.viewTop, "front": v.viewFront, "none": lambda: None}[view]()
        if not fixed:  # Schnittanalyse: Einpassen sähe die Schnitt-Griffe als Teil des Modells
            Gui.SendMsgToActiveView("ViewFit")
        for _ in range(abs(zoom)):
            (v.zoomIn if zoom > 0 else v.zoomOut)()
    step("pose", pose)
    wait()

    def grab():
        img = mw.grab().toImage()
        w, h = img.width(), img.height()
        crop = img.copy(330, 120, w - 330 - 190, h - 120 - 80)  # ohne Browser, Toolbar, ViewCube/Palette, Zeitleiste
        crop.scaledToWidth(720, QtCore.Qt.SmoothTransformation).save(os.path.join(OUT, article + ".jpg"), "JPG", 86)
        L("Bild %s" % article)
    step("grab " + article, grab)


def scenario(article, build, view="iso", zoom=0, edit=None, fixed=False):
    if ONLY and article not in ONLY:
        return
    step("new " + article, lambda: Gui.runCommand("Std_New"))
    wait()
    build()
    if edit:  # Skizze im Bearbeiten-Modus zeigen (von oben)
        step("edit", lambda: Gui.ActiveDocument.setEdit(st[edit].Name))
        wait()
        shot(article, "none", zoom)
        step("leave", lambda: Gui.ActiveDocument.resetEdit())
    else:
        shot(article, view, zoom, fixed)
    step("close", lambda: App.closeDocument(doc().Name))
    wait()


def keep(key, fn):
    """Ergebnis eines Schritts für spätere Schritte merken"""
    return lambda: st.__setitem__(key, fn())


# --- Körper ---------------------------------------------------------------------------------------------------------
def first():
    step("body", keep("b", lambda: box(0, 0, 60, 40, 20)))


def extrude_tube():
    step("sketch", keep("sp", lambda: sketch([circle(0, 0, 20), circle(0, 0, 12)])[1]))
    step("select", lambda: select(st["sp"], ring_face(st["sp"])))
    feature("Design_Extrude", lambda: type_into(0, "30"))


def revolve():
    step("sketch", keep("sp", lambda: sketch([circle(30, 0, 8)], plane="XZ")[1]))
    step("select", lambda: select(st["sp"], "Face1"))
    feature("Design_Revolve")


def sweep():
    def build():
        _, prof = sketch([circle(0, 0, 5)])
        path, _ = sketch([Part.ArcOfCircle(Part.Circle(V(40, 0, 0), V(0, 0, 1), 40), math.pi / 2, math.pi)], plane="XZ", name="Path")
        st["prof"], st["path"] = prof, path
    step("sketches", build)
    step("select", lambda: (select(st["prof"], "Face1"), add_select(st["path"], "Edge1")))
    feature("Design_Sweep")


def loft():
    def build():
        _, p1 = sketch(rect(-20, -20, 20, 20))
        _, p2 = sketch([circle(0, 0, 12)], z=40)
        st["p1"], st["p2"] = p1, p2
    step("sketches", build)
    step("select", lambda: (select(st["p1"], "Face1"), add_select(st["p2"], "Face1")))
    feature("Design_Loft")


def rib():
    def build():
        pts = [V(0, 0, 0), V(60, 0, 0), V(60, 6, 0), V(6, 6, 0), V(6, 50, 0), V(0, 50, 0)]
        _, prof = sketch([Part.LineSegment(pts[i], pts[(i + 1) % 6]) for i in range(6)], plane="XZ")
        select(prof, "Face1")
    step("L", build)
    feature("Design_Extrude", lambda: type_into(0, "30"))
    step("rib", keep("rib", lambda: sketch([Part.LineSegment(V(6, 40, 0), V(50, 6, 0))], plane="XZ", name="RibLine")[0]))
    step("rib y", lambda: (setattr(st["rib"].Placement.Base, "y", -15), doc().recompute()))
    step("select", lambda: (select(last("Design::Body")), add_select(st["rib"], "Edge1")))
    feature("Design_Rib", lambda: type_into(0, "4"))


def web():
    step("box", keep("b", lambda: box(0, 0, 60, 40, 20)))
    step("open", lambda: select(st["b"], top(st["b"])))
    feature("Design_Shell", lambda: type_into(0, "2"))
    step("walls", keep("w", lambda: sketch([Part.LineSegment(V(1, 20, 0), V(59, 20, 0)), Part.LineSegment(V(30, 1, 0), V(30, 39, 0))], z=10, name="WebLines")[0]))
    step("select", lambda: (select(st["b"]), add_select(st["w"], "Edge1", "Edge2")))
    feature("Design_Web", lambda: type_into(0, "3"))


def emboss():
    step("plate", keep("b", lambda: box(0, 0, 60, 40, 6)))
    step("shape", keep("sp", lambda: sketch([circle(20, 20, 8)] + rect(36, 12, 50, 28), z=6)[1]))
    step("select", lambda: (select(st["sp"], "Face1", "Face2"), add_select(st["b"], top(st["b"]))))
    feature("Design_Emboss")


def primitives():
    for i, (cmd, x) in enumerate((("Design_Box", -70), ("Design_Cylinder", -25), ("Design_Sphere", 20), ("Design_Torus", 70))):
        feature(cmd)
        step("place", lambda x=x: (setattr(last("Design::Primitive"), "PositionX", x), doc().recompute()))


def hole():
    step("plate", keep("b", lambda: box(0, 0, 70, 40, 12)))
    step("points", keep("pts", lambda: sketch([Part.Point(V(x, 20, 0)) for x in (15, 35, 55)], z=12, name="HolePoints")[0]))
    step("select", lambda: select(st["pts"]))
    feature("Design_Hole", lambda: combo("Counterbore"))


def thread():
    step("rod", lambda: make_body([circle(0, 0, 6)], 0, 30, "Rod"))
    step("select", lambda: select(last("Design::Body"), cylindrical(last("Design::Body"))[0]))
    feature("Design_Thread")


def pattern():
    step("peg", lambda: make_body([circle(0, 0, 5)], 0, 15, "Peg"))
    step("select", lambda: select(last("Design::Body")))
    feature("Design_Pattern", lambda: type_into(1, "16"), lambda: type_into(2, "4"))


def mirror():
    def build():
        pts = [V(10, 0, 0), V(50, 0, 0), V(50, 10, 0), V(20, 10, 0), V(20, 30, 0), V(10, 30, 0)]
        make_body([Part.LineSegment(pts[i], pts[(i + 1) % 6]) for i in range(6)], 0, 15, "Part")
        select(last("Design::Body"))
    step("part", build)
    feature("Design_Mirror", lambda: combo("YZ plane"))


def on_box(cmd, faces_of, *setup, h=20):
    step("box", keep("b", lambda: box(0, 0, 60, 40, h)))
    step("select", lambda: select(st["b"], *faces_of(st["b"])))
    feature(cmd, *setup)


def replace_face():
    step("box", keep("b", lambda: box(0, 0, 60, 40, 20)))
    step("plane", lambda: (select(st["b"], top(st["b"]))))
    feature("Design_OffsetPlane", lambda: type_into(0, "12"))
    step("select", lambda: (select(st["b"], top(st["b"])), add_select([o for o in doc().Objects if "Plane" in o.TypeId and o.TypeId != "App::Plane"][-1])))
    feature("Design_ReplaceFace")


def split_face():
    step("box", keep("b", lambda: box(0, 0, 60, 40, 20)))
    step("line", keep("l", lambda: sketch([Part.LineSegment(V(30, -5, 0), V(30, 45, 0))], z=20, name="SplitLine")[0]))
    step("select", lambda: (select(st["b"], top(st["b"])), add_select(st["l"])))
    feature("Design_SplitFace")


def combine():
    step("box", keep("a", lambda: box(0, 0, 60, 40, 20)))
    step("cyl", keep("c", lambda: make_body([circle(30, 20, 14)], -5, 30, "Cylinder")))
    step("select", lambda: (select(st["a"]), add_select(st["c"])))
    feature("Design_Combine", lambda: combo("Cut"))


def split_body():
    step("box", keep("b", lambda: box(0, 0, 60, 40, 20)))
    step("tool", lambda: select(doc().getObject("XY_Plane") or [o for o in doc().Objects if o.Name.startswith("XY_Plane")][0]))
    feature("Design_OffsetPlane", lambda: type_into(0, "10"))
    step("select", lambda: (select(st["b"]), add_select([o for o in doc().Objects if o.TypeId not in ("App::Plane",) and "Plane" in o.TypeId][-1])))
    feature("Design_SplitBody")


def move():
    step("box", keep("b", lambda: box(0, 0, 40, 20, 10)))
    step("ghost", lambda: box(0, 0, 40, 20, 10, name="Original"))
    step("select", lambda: select(st["b"]))
    feature("Design_Move", lambda: type_into(0, "30"), lambda: type_into(3, "30"))


def datum(cmd, refs, *setup):
    step("box", keep("b", lambda: box(0, 0, 60, 40, 20)))
    step("select", lambda: select(st["b"], *refs(st["b"])))
    feature(cmd, *setup)


def section():
    step("plate", keep("b", lambda: box(-30, -20, 30, 20, 20)))
    step("hole", keep("h", lambda: make_body([circle(0, 0, 8)], 0, 20, "Hole")))
    step("select", lambda: (select(st["b"]), add_select(st["h"])))
    feature("Design_Combine", lambda: combo("Cut"))
    step("fit", lambda: (Gui.ActiveDocument.ActiveView.viewIsometric(), Gui.SendMsgToActiveView("ViewFit")))
    step("plane", lambda: select([o for o in doc().Objects if o.Name.startswith("XZ_Plane")][0]))
    step("section", lambda: Gui.runCommand("Design_Section"))
    wait()


def appearance():
    def build():
        for i, c in enumerate(((0.95, 0.35, 0.3), (0.3, 0.6, 0.95), (0.95, 0.8, 0.3))):
            b = box(i * 30, 0, i * 30 + 20, 20, 20, name="Part")
            b.ViewObject.ShapeAppearance = (App.Material(DiffuseColor=c),)
    step("bodies", build)


# --- Skizzen --------------------------------------------------------------------------------------------------------
def sk(geos, constraints=(), construction=(), z=0, fillet=False):
    def build():
        s, _ = sketch(geos, construction=construction, z=z)
        for c in constraints:
            s.addConstraint(c)
        if fillet:  # zwei Ecken abrunden
            s.fillet(0, 1, V(25, -20, 0), V(30, -15, 0), 8)
            s.fillet(2, 3, V(-25, 20, 0), V(-30, 15, 0), 8)
        doc().recompute()
        st["sk"] = s
    step("sketch", build)


C = Sketcher.Constraint


def closed(pts):
    lines = [Part.LineSegment(pts[i], pts[(i + 1) % len(pts)]) for i in range(len(pts))]
    cons = [C("Coincident", i, 2, (i + 1) % len(pts), 1) for i in range(len(pts))]
    return lines, cons


def rect_c(x0, y0, x1, y1):
    return closed([V(x0, y0, 0), V(x1, y0, 0), V(x1, y1, 0), V(x0, y1, 0)])


def hexagon(cx, cy, r):
    return closed([V(cx + r * math.cos(a * math.pi / 3), cy + r * math.sin(a * math.pi / 3), 0) for a in range(6)])


R = rect_c(-30, -20, 30, 20)
SKETCHES = {
    "Design_CreateSketch": (R[0], R[1]),
    "sketch_basics": (R[0] + [circle(0, 0, 10)], R[1] + [C("Horizontal", 0), C("Vertical", 1), C("DistanceX", 0, 1, 0, 2, 60)]),
    "sketch_line": ([Part.LineSegment(V(-30, -10, 0), V(20, 15, 0)), Part.LineSegment(V(-20, 20, 0), V(30, 20, 0))], [C("Horizontal", 1)]),
    "sketch_polyline": closed([V(-30, -20, 0), V(30, -20, 0), V(30, 0, 0), V(0, 20, 0), V(-30, 20, 0)]),
    "sketch_rectangle": (R[0], R[1] + [C("Horizontal", 0), C("Horizontal", 2), C("Vertical", 1), C("Vertical", 3)]),
    "sketch_circle": ([circle(-18, 0, 14), Part.Ellipse(V(28, 0, 0), 14, 8)], []),
    "sketch_arc": ([Part.ArcOfCircle(circle(-15, 0, 15), 0, math.pi), Part.ArcOfCircle(circle(20, -5, 12), -math.pi / 2, math.pi / 2)], []),
    "sketch_slot": ([Part.ArcOfCircle(circle(-20, 0, 8), math.pi / 2, 3 * math.pi / 2), Part.ArcOfCircle(circle(20, 0, 8), -math.pi / 2, math.pi / 2),
                     Part.LineSegment(V(-20, -8, 0), V(20, -8, 0)), Part.LineSegment(V(-20, 8, 0), V(20, 8, 0))], []),
    "sketch_polygon": hexagon(0, 0, 25),
    "sketch_bspline": ([Part.BSplineCurve([V(-30, 0, 0), V(-15, 18, 0), V(0, -5, 0), V(15, 20, 0), V(30, 0, 0)])], []),
    "sketch_conic": ([Part.ArcOfEllipse(Part.Ellipse(V(0, -10, 0), 28, 18), 0, math.pi)], []),
    "sketch_point": ([Part.Point(V(x, y, 0)) for x in (-20, 0, 20) for y in (-10, 10)], []),
    "sketch_fillet": (R[0], R[1]),
    "sketch_trim": ([Part.LineSegment(V(-30, 0, 0), V(30, 0, 0)), Part.LineSegment(V(0, -20, 0), V(0, 20, 0)), circle(0, 0, 12)], []),
    "sketch_offset": (rect_c(-30, -20, 30, 20)[0] + rect_c(-25, -15, 25, 15)[0], []),
    "sketch_mirror": (closed([V(5, -15, 0), V(30, -15, 0), V(30, 15, 0), V(5, 5, 0)])[0] + closed([V(-5, -15, 0), V(-30, -15, 0), V(-30, 15, 0), V(-5, 5, 0)])[0], []),
    "sketch_pattern": ([circle(x, y, 5) for x in (-20, 0, 20) for y in (-10, 10)], []),
    "sketch_move": ([circle(-15, 0, 10), circle(15, 0, 10)], []),
    "sketch_construction": (R[0], R[1]),
    "sketch_dimension": (R[0], R[1] + [C("DistanceX", 0, 1, 0, 2, 60), C("DistanceY", 1, 1, 1, 2, 40)]),
    "sketch_coincident": (R[0], R[1]),
    "sketch_horver": (R[0], R[1] + [C("Horizontal", 0), C("Horizontal", 2), C("Vertical", 1), C("Vertical", 3)]),
    "sketch_parallel": ([Part.LineSegment(V(-30, -15, 0), V(25, -5, 0)), Part.LineSegment(V(-30, 5, 0), V(25, 15, 0)), Part.LineSegment(V(-20, -30, 0), V(-16, 25, 0))],
                        [C("Parallel", 0, 1), C("Perpendicular", 0, 2)]),
    "sketch_tangent": ([Part.LineSegment(V(-30, 10, 0), V(0, 10, 0)), Part.ArcOfCircle(circle(0, 0, 10), -math.pi / 2, math.pi / 2)], [C("Tangent", 0, 2, 1, 2)]),
    "sketch_equal": ([circle(-18, 0, 10), circle(18, 0, 10)], [C("Equal", 0, 1)]),
    "sketch_symmetric": ([Part.LineSegment(V(-25, 10, 0), V(25, 10, 0)), Part.LineSegment(V(-25, -15, 0), V(25, -15, 0))],
                         [C("Symmetric", 0, 1, 0, 2, -2), C("Symmetric", 1, 1, 1, 2, -2)]),
    "sketch_block": (R[0], R[1] + [C("Block", 0)]),
}
CONSTRUCTION = {"sketch_construction": [Part.LineSegment(V(-30, -20, 0), V(30, 20, 0)), Part.LineSegment(V(-30, 20, 0), V(30, -20, 0))],
                "sketch_mirror": [Part.LineSegment(V(0, -25, 0), V(0, 25, 0))]}


def project():
    step("box", keep("b", lambda: box(-30, -20, 30, 20, 15)))
    sk([circle(0, 0, 8)], z=15)
    step("external", lambda: ([st["sk"].addExternal(st["b"].Name, e) for e in ("Edge1", "Edge2", "Edge3", "Edge4", "Edge5", "Edge6", "Edge7", "Edge8", "Edge9", "Edge10", "Edge11", "Edge12")], doc().recompute()))


# --- Ablauf ---------------------------------------------------------------------------------------------------------
scenario("start_first", first)
scenario("Design_Extrude", extrude_tube)
scenario("Design_Revolve", revolve)
scenario("Design_Sweep", sweep)
scenario("Design_Loft", loft)
scenario("Design_Rib", rib)
scenario("Design_Emboss", emboss)
scenario("primitives", primitives)
scenario("Design_Thread", thread)
scenario("Design_Mirror", mirror)
scenario("Design_PressPull", lambda: on_box("Design_PressPull", lambda b: [top(b)], lambda: type_into(0, "15")))
# ponytail: Bohrung, Muster, Fläche ersetzen und Steg brauchen ein passenderes Beispiel, bis dahin ohne Bild
scenario("Design_SplitFace", split_face)
scenario("Design_Fillet", lambda: on_box("Design_Fillet", lambda b: [top(b)], lambda: type_into(0, "5")))
scenario("Design_Chamfer", lambda: on_box("Design_Chamfer", lambda b: [top(b)], lambda: type_into(0, "4")))
scenario("Design_Shell", lambda: on_box("Design_Shell", lambda b: [top(b)], lambda: type_into(0, "2")))
scenario("Design_Draft", lambda: on_box("Design_Draft", sides, lambda: type_into(0, "8")))
scenario("Design_Combine", combine)
scenario("Design_SplitBody", split_body)
scenario("Design_Move", move)
scenario("Design_OffsetPlane", lambda: datum("Design_OffsetPlane", lambda b: [top(b)], lambda: type_into(0, "15")))
scenario("Design_Midplane", lambda: datum("Design_Midplane", lambda b: [f for f in sides(b) if abs(normal(b.Shape.getElement(f)).x) > 0.5]))
scenario("Design_Axis", lambda: (step("cyl", lambda: make_body([circle(0, 0, 12)], 0, 30, "Cylinder")),
                                 step("select", lambda: select(last("Design::Body"), cylindrical(last("Design::Body"))[0])),
                                 feature("Design_Axis")))
scenario("Design_Section", section, fixed=True)
scenario("Design_Appearance", appearance)
scenario("sketch_project", project, edit="sk")
for article, (geos, cons) in SKETCHES.items():
    scenario(article, lambda g=geos, c=cons, a=article: sk(g, c, CONSTRUCTION.get(a, ()), fillet=a == "sketch_fillet"), edit="sk")

run(steps, delay=900)
