# SPDX-License-Identifier: LGPL-2.1-or-later
"""Ein Schritt, dessen Profil nach einer Änderung der Skizze weggefallen ist, wird übersprungen (Warnung in der Timeline,
Körper unverändert) statt rot zu werden. Vorher hielt der Fehler "Sketch has no closed profile" alle späteren Schritte an:
auch ein neuer Extrude wurde nie berechnet (Monitor Light, Sechseck ließ sich nicht extrudieren). Und ein Schritt nimmt
nicht still ein fremdes Profil, nur weil die Kantennummern nach dem Löschen nachrutschen (Signaturen aus festen IDs).
Ein Kreis in einem benutzten Profil macht es dagegen zum Ring (verändert, nicht weg)."""
from harness import *
import Design

W = ("wait", lambda: None)
S = {}


def setup():
    d = doc(); root = [o for o in d.Objects if o.TypeId == "App::Part"][0]
    S["sk"] = Design.newSketch(root)
    for g in rect(30, 0, 50, 20) + rect(0, 0, 20, 20):  # Profil B (rechts) zuerst, dann A
        S["sk"].addGeometry(g)
    d.recompute()
    S["p"] = [o for o in S["sk"].InList if o.TypeId == "Design::Profiles"][0]


def extrude(right):
    p = S["p"]
    face = "Face%d" % (1 + [i for i, f in enumerate(p.Shape.Faces) if (f.CenterOfMass.x > 25) == right][0])
    S["sk"].Visibility = True
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(p, face); click(button("Design_Extrude"))


def enter():
    button("Design_Extrude").setFocus(); QtTest.QTest.keyClick(view(), QtCore.Qt.Key_Return)


def drop_b():
    doc().openTransaction("drop B")
    for _ in range(4):
        S["sk"].delGeometry(0)
    doc().recompute(); doc().commitTransaction()


def skipped():
    b, a = [o for o in doc().Objects if o.TypeId == "Design::Extrude"][:2]
    check("the step whose profile is gone shows a warning instead of an error", "Invalid" not in b.State and b.Warning.startswith("Profile gone"),
          "state=%s warning=%r status=%r" % (b.State, b.Warning, b.getStatusString()))
    check("later steps are still computed", a.State == ["Up-to-date"] and not errors(), "state=%s errors=%s" % (a.State, errors()))


def new_extrude():
    vols = sum(x.Shape.Volume for x in doc().Objects if x.TypeId == "Design::Body")
    check("a new extrude after the skipped step is computed", abs(vols - 2 * 4000) < 0.05, "volume=%.2f" % vols)


def ring():
    doc().openTransaction("hole"); S["sk"].addGeometry(Part.Circle(App.Vector(10, 10, 0), App.Vector(0, 0, 1), 5)); doc().recompute()
    doc().commitTransaction()


def ringed():
    vols = sum(x.Shape.Volume for x in doc().Objects if x.TypeId == "Design::Body")
    a = [o for o in doc().Objects if o.TypeId == "Design::Extrude"][1]
    check("a circle inside a used profile turns it into a ring (changed, not gone)", not a.Warning and abs(vols - 2 * (4000 - 785.398)) < 0.05,
          "volume=%.2f warning=%r" % (vols, a.Warning))


run([("activate", activate), ("setup", setup), W, ("B", lambda: extrude(True)), W, ("ok B", enter), W,
     ("A", lambda: extrude(False)), W, ("ok A", enter), W, ("drop", drop_b), W, ("skipped", skipped),
     ("A again", lambda: extrude(False)), W, ("ok", enter), W, ("new", new_extrude),
     ("ring", ring), W, ("ringed", ringed)])
