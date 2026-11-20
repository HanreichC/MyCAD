# SPDX-License-Identifier: LGPL-2.1-or-later
"""12.10 Code-Schritt: ein Timeline-Schritt aus Python-Code. Der Code setzt result auf eine Form; Maße aus der Notiz
heißen p.Name (in mm). Kleine Formfunktionen im Stil von build123d: box, cylinder, sphere, cone, torus, move, rotate,
union, cut, common, mirror.

Sicherheit: Code aus einer Datei ist fremder Code. Er läuft nur, wenn genau dieser Text auf diesem Rechner freigegeben
wurde (approve, im Panel "Run"); die Freigabe steht als Hash in den Einstellungen, nie in der Datei."""
import hashlib

import FreeCAD as App
import Part

GROUP = "User parameter:BaseApp/Preferences/MyCAD/ApprovedCode"

EXAMPLE = """# Plate with a hole. Its width from a
# note: write "Width = 40 mm" into one.
w = getattr(p, "Width", 40)
plate = box(w, 30, 5)
result = cut(plate, cylinder(8, 5))
"""


def key(code):
    return hashlib.sha256(code.encode("utf-8")).hexdigest()[:40]


def approved(code):
    return App.ParamGet(GROUP).GetBool(key(code), False)


def approve(code):
    """Freigabe dieses Textes auf diesem Rechner (der Benutzer hat ihn gesehen und "Run" geklickt)"""
    App.ParamGet(GROUP).SetBool(key(code), True)


class NotApproved(Exception):
    pass


class _Parameters:
    """p.Name: Wert eines Parameters der Notiz in mm (bzw. als Zahl); unbekannt -> AttributeError"""

    def __init__(self, doc):
        import Design
        self._set = Design.parameterSet(doc, False)

    def __getattr__(self, name):
        if self._set is None or name not in self._set.PropertiesList:
            raise AttributeError("no parameter %s in the notes" % name)
        value = getattr(self._set, name)
        return value.Value if hasattr(value, "Value") else value


def _at(shape, at):
    shape.translate(App.Vector(*at))
    return shape


def box(x, y, z, at=(0, 0, 0), center=True):
    """Quader x * y * z; center: mittig in x und y, unten auf z = 0 (wie die Grundkörper)"""
    s = Part.makeBox(x, y, z, App.Vector(-x / 2, -y / 2, 0) if center else App.Vector())
    return _at(s, at)


def cylinder(d, h, at=(0, 0, 0)):
    """Zylinder mit Durchmesser d, Höhe h, Achse z, Mitte unten bei at"""
    return _at(Part.makeCylinder(d / 2, h), at)


def cone(d1, d2, h, at=(0, 0, 0)):
    return _at(Part.makeCone(d1 / 2, d2 / 2, h), at)


def sphere(d, at=(0, 0, 0)):
    return _at(Part.makeSphere(d / 2), at)


def torus(d, tube, at=(0, 0, 0)):
    return _at(Part.makeTorus(d / 2, tube / 2), at)


def move(shape, x=0, y=0, z=0):
    s = shape.copy()
    s.translate(App.Vector(x, y, z))
    return s


def rotate(shape, angle, axis=(0, 0, 1), center=(0, 0, 0)):
    s = shape.copy()
    s.rotate(App.Vector(*center), App.Vector(*axis), angle)
    return s


def mirror(shape, normal=(1, 0, 0), base=(0, 0, 0)):
    return shape.mirror(App.Vector(*base), App.Vector(*normal))


def union(*shapes):
    result = shapes[0]
    for s in shapes[1:]:
        result = result.fuse(s)
    return result.removeSplitter()


def cut(shape, *tools):
    result = shape
    for t in tools:
        result = result.cut(t)
    return result.removeSplitter()


def common(shape, *tools):
    result = shape
    for t in tools:
        result = result.common(t)
    return result.removeSplitter()


def run(code, doc):
    """Form aus code (nur freigegebener Code läuft); wirft mit einer Meldung für den Schritt"""
    if not approved(code):
        raise NotApproved("This code has not run on this computer yet: open the step, read it and click Run")
    env = {"p": _Parameters(doc), "App": App, "Part": Part, "Vector": App.Vector, "box": box, "cylinder": cylinder,
           "cone": cone, "sphere": sphere, "torus": torus, "move": move, "rotate": rotate, "mirror": mirror,
           "union": union, "cut": cut, "common": common}
    exec(compile(code, "<code step>", "exec"), env)
    result = env.get("result")
    if not isinstance(result, Part.Shape) or result.isNull():
        raise ValueError("The code must set result to a shape")
    return result
