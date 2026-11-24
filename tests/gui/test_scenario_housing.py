# SPDX-License-Identifier: LGPL-2.1-or-later
"""Phase 13.3 Szenario B: ein Gehäuse mit Deckel, wie ein Mensch es baut, jede typische Handlung gemessen (timed).
Quader 60 x 40 x 30, Wandstärke 2 mit offener Deckfläche (Klick auf die Deckfläche), von oben Skizze auf den Boden
innen (Klick durch die Öffnung), Sockel 6 mm hoch (Join); Deckel als zweiter Körper in eigener Komponente, Gelenk
Deckel-Unterseite auf den Rand; Screw Here durch den Deckel in den Sockel; Druckrichtung vorschlagen; Export STEP,
wieder einlesen: alles an seinem Platz; Stückliste (Normteile). Messwerte in $OUT.perf.txt."""
import math
import os
from harness import *
import Part

S = {}
W = ("wait", lambda: None)
V = App.Vector
STEP = os.environ["OUT"] + ".housing.step"


def housing():
    return body("Housing")


def comp():
    return [o for o in doc().Objects if o.TypeId == "App::Part" and o.Type == "Component"][0]


def lid():
    return [o for o in doc().Objects if o.TypeId == "Design::Body" and o.Label not in ("Housing",) and o.Label != "Screw"
            and not o.Label.startswith("Screw")][0]


def placed(b):
    """Form im Dokument-Koordinatensystem (die Komponente kann verschoben sein)"""
    s = b.Shape.copy()
    for p in b.InListRecursive:
        if p.TypeId == "App::Part" and p.Type == "Component":
            s.transformShape(p.Placement.toMatrix())
    return s


def edit_obj():
    return Gui.ActiveDocument.getInEdit().Object


# --- Gehäuse ------------------------------------------------------------------------------------------------------------
def make_housing():
    make_body(rect(0, 0, 60, 40), 0, 30, "Housing")
    Gui.ActiveDocument.ActiveView.viewIsometric(); Gui.SendMsgToActiveView("ViewFit")


def shell():
    Gui.Selection.clearSelection()
    click_at(V(30, 20, 30))  # Deckfläche
    S["picked"] = [(s.ObjectName, s.SubElementNames) for s in Gui.Selection.getSelectionEx()]
    click(button("Design_Shell"))


def shelled():
    want = 60 * 40 * 30 - 56 * 36 * 28
    check("Shell with the clicked top face open: 2 mm walls", abs(housing().Shape.Volume - want) < 0.5 and not errors(),
          "%.1f want %.1f picked %s errors %s" % (housing().Shape.Volume, want, S["picked"], errors()))


def floor_sketch():
    Gui.ActiveDocument.ActiveView.viewTop(); Gui.SendMsgToActiveView("ViewFit")
    Gui.Selection.clearSelection()
    click_at(V(30, 20, 2))  # von oben durch die Öffnung auf den Boden innen
    S["picked"] = [(s.ObjectName, s.SubElementNames) for s in Gui.Selection.getSelectionEx()]
    click(button("Design_CreateSketch"))


def boss_circle():
    ins = Gui.ActiveDocument.getInEdit()
    check("a click through the opening picks the inner floor and opens a sketch on it", ins is not None
          and any("Face" in n for _, names in S["picked"] for n in names), str(S["picked"]))
    s = edit_obj(); S["floor"] = s
    c = s.Placement.inverse().multVec(V(8, 8, 2))
    check("the floor sketch lies on the inner floor (z = 2)", abs(s.Placement.Base.z - 2) < 1e-6, str(s.Placement))
    s.addGeometry(Part.Circle(V(c.x, c.y, 0), V(0, 0, 1), 4))
    doc().recompute()


def leave():
    Gui.ActiveDocument.resetEdit()


def extrude_boss():
    prof = [o for o in S["floor"].InList if o.TypeId == "Design::Profiles"][0]
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(prof, "Face1")
    S["vol"] = housing().Shape.Volume
    click(button("Design_Extrude"))


def boss_ok():
    added = housing().Shape.Volume - S["vol"]
    check("boss 6 mm up from the floor joins the housing", abs(added - math.pi * 16 * 6) < 0.5 and not errors(),
          "added %.2f want %.2f %s" % (added, math.pi * 16 * 6, errors()))


# --- Deckel -------------------------------------------------------------------------------------------------------------
def new_component():
    Gui.ActiveDocument.ActiveView.viewIsometric()
    click(button("Design_NewComponent"))


def lid_sketch():
    click(button("Design_CreateSketch"))
    QtCore.QTimer.singleShot(200, lambda: Gui.Selection.addSelection(
        [o for o in comp().Origin.OriginFeatures if o.Role == "XY_Plane"][0]))


def lid_rect():
    s = edit_obj()
    for g in rect(0, 0, 60, 40):
        s.addGeometry(g)
    doc().recompute()


def lid_bottom_on_rim():
    rim = face_where(housing(), lambda c: abs(c.z - 30) < 1e-6)
    low = face_where(lid(), lambda c: abs(c.z) < 1e-6)
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(doc().Name, lid().Name, low)
    Gui.Selection.addSelection(doc().Name, housing().Name, rim)
    Gui.runCommand("Design_Joint")


def lid_placed():
    k = placed(lid()).BoundBox
    check("the joint puts the lid onto the rim (x 0..60, y 0..40, z 30..32)",
          max(abs(k.XMin), abs(k.XMax - 60), abs(k.YMin), abs(k.YMax - 40), abs(k.ZMin - 30), abs(k.ZMax - 32)) < 1e-6,
          "%s errors %s" % (k, errors()))


def screw_here():
    top = face_where(lid(), lambda c: abs(c.z - 2) < 1e-6)  # Deckel-Oberseite (lokal z = 2)
    Gui.Selection.clearSelection()
    Gui.Selection.addSelection(doc().Name, lid().Name, top, 8, 8, 32)  # Klickpunkt global, über dem Sockel
    S["boss vol"] = housing().Shape.Volume
    Gui.runCommand("Design_Fastener")


def screwed():
    f = [o for o in doc().Objects if o.TypeId == "Design::Fastener"]
    names = [b.Label for b in f[0].Bodies] if f else []
    check("Screw Here at the boss: lid and housing are screwed, the screw comes along",
          len(f) == 1 and lid().Label in names and "Housing" in names and len(names) == 3, str(names))
    h = housing().Shape
    check("the boss got a hole for the screw", not h.isInside(V(8, 8, 6), 1e-6, True) and h.Volume < S["boss vol"] - 1,
          "vol %.1f before %.1f" % (h.Volume, S["boss vol"]))
    check("the lid got a through hole", not placed(lid()).isInside(V(8, 8, 31), 1e-6, True))
    S["bodies"] = sorted((b.Label, round(placed(b).Volume, 1)) for b in doc().Objects if b.TypeId == "Design::Body")


# --- Drucken, Export, Stückliste ----------------------------------------------------------------------------------------
def suggest():
    Gui.Selection.clearSelection()
    Gui.runCommand("Design_PrintSuggest")


def suggested():
    check("print suggestion runs without errors", not errors(), str(errors()))
    Gui.runCommand("Design_PrintView")  # Druckansicht wieder aus


def export_step():
    def pick():
        d = visible(QtWidgets.QFileDialog)
        if not d:
            L("  no file dialog"); return
        [e for e in d[0].findChildren(QtWidgets.QLineEdit) if e.isVisible()][0].setText(STEP)
        d[0].accept()
        activate()
    Gui.Selection.clearSelection()
    QtCore.QTimer.singleShot(600, pick)
    Gui.runCommand("Design_Export")


def step_ok():
    ok_file = os.path.exists(STEP)
    vols = []
    if ok_file:
        s = Part.Shape(); s.read(STEP)
        vols = sorted(round(x.Volume, 1) for x in s.Solids)
        S["step bb"] = s.BoundBox
    want = sorted(v for _, v in S["bodies"])
    check("STEP export: one solid per body with the same volumes", ok_file and vols == want, "%s vs %s" % (vols, want))
    k = S.get("step bb")
    check("STEP export: the lid sits on the housing there too (z up to 32 plus screw head)",
          k is not None and abs(k.ZMin) < 1e-3 and 32 - 1e-3 <= k.ZMax < 40, str(k))


def parts_list():
    QtCore.QTimer.singleShot(0, lambda: Gui.runCommand("Design_PartsList"))


def parts_ok():
    texts = []
    for d in visible(QtWidgets.QDialog):
        for t in d.findChildren(QtWidgets.QTableWidget) + d.findChildren(QtWidgets.QTreeWidget):
            if isinstance(t, QtWidgets.QTableWidget):
                texts += [t.item(r, c).text() for r in range(t.rowCount()) for c in range(t.columnCount()) if t.item(r, c)]
            else:
                it = QtWidgets.QTreeWidgetItemIterator(t)
                while it.value():
                    texts += [it.value().text(c) for c in range(t.columnCount())]; it += 1
        for l in d.findChildren(QtWidgets.QLabel):
            texts.append(l.text())
    joined = " | ".join(texts)
    L("  parts list: %s" % joined[:400])
    check("parts list: the standard parts to buy, here the one screw (M3 x 30 reaches into the boss)",
          "ISO 4762 M3 × 30" in joined, joined[:300])
    for d in visible(QtWidgets.QDialog):
        d.close()


run([("activate", activate), ("housing", make_housing), W,
     timed("shell opens (click top face)", shell, 300), W,
     timed("shell: type 2, preview", lambda: type_field("Thickness", "2"), 500), W,
     timed("shell OK", ok, 500), W, ("shelled", shelled),
     timed("sketch on inner floor opens", floor_sketch, 500), W, ("circle", boss_circle),
     timed("finish floor sketch", leave, 300), W,
     timed("extrude boss opens", extrude_boss, 300), W,
     timed("boss: type 6, preview", lambda: type_field("Distance", "6"), 300), W,
     timed("boss OK", ok, 300), W, ("boss ok", boss_ok),
     ("component", new_component), W,
     ("lid sketch", lid_sketch), W, W, ("lid rect", lid_rect),
     ("lid leave", leave), W,
     ("lid extrude", lambda: click(button("Design_Extrude"))), W,
     ("lid 2", lambda: type_field("Distance", "2")), W, ("lid OK", ok), W,
     timed("joint lid on rim", lid_bottom_on_rim, 500), W, ("joint OK", ok), W, ("lid placed", lid_placed),
     timed("screw here opens", screw_here, 500), W,
     ("M3", lambda: choose("M3", 2)), W, timed("screw OK", ok, 800), W, ("screwed", screwed),
     timed("suggest print orientation", suggest, 800), W, ("suggested", suggested), W,
     ("export", export_step), W, W, ("step ok", step_ok),
     ("parts", parts_list), W, ("parts ok", parts_ok),
     ("errors", lambda: check("no errors", not errors(), str(errors()))),
     ])
