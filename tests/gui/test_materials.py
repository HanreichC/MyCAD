# SPDX-License-Identifier: LGPL-2.1-or-later
"""Körper-Materialien (Gui/Shell/BodyShading.cpp): eine spiegelnde Chromkugel zeigt den Raum, darin eine scharfe Linie, wo
Wand und Boden aufeinandertreffen. Mit Materialien "Sparsam" (Phong, wie früher) gibt es nur weiche Verläufe.
Fotoscans: Maßstab aus dem Bild, Hirnholz an der Stirnseite (nur bei "Hoch"). Zum Schluss ein Bild aller Effekte.
Fehler stehen als FAIL im Protokoll."""
from harness import *
import Part

saved = {}
P = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")


def material(diffuse, specular, shininess, metal, flags=0, transparency=0.0):
    m = App.Material()
    m.DiffuseColor = diffuse; m.SpecularColor = specular; m.Shininess = shininess; m.Transparency = transparency
    m.EmissiveColor = (0.0, flags / 255.0, (2 if metal else 1) / 255.0)  # Markierungen (BodyShading.h)
    return m


def fit(view_name):
    v = Gui.ActiveDocument.ActiveView
    getattr(v, view_name)(); Gui.SendMsgToActiveView("ViewFit")


def sphere():
    s = doc().addObject("Part::Sphere", "Mirror"); s.Radius = 20
    doc().recompute()
    Gui.ActiveDocument.getObject(s.Name).ShapeAppearance = [material((0.9, 0.9, 0.9), (0.9, 0.9, 0.9), 0.97, True)]
    fit("viewFront")


def lum(img, x, y):
    c = img.pixelColor(x, y)
    return 0.2126 * c.redF() + 0.7152 * c.greenF() + 0.0722 * c.blueF()


def measure(key):
    """größter Helligkeitssprung auf 6 px entlang der senkrechten Mittellinie der Kugel (Vorderansicht)"""
    img = view().viewport().grab().toImage()
    w, h = img.width(), img.height()
    line = [lum(img, w // 2, y) for y in range(int(h * 0.40), int(h * 0.72), 2)]
    saved[key] = max(abs(a - b) for a, b in zip(line, line[3:]))


def center(key):
    """mittlere Helligkeit in der Bildmitte (die sichtbare Seite des Holzklotzes)"""
    img = view().viewport().grab().toImage()
    w, h = img.width(), img.height()
    values = [lum(img, x, y) for x in range(w // 2 - 40, w // 2 + 40, 4) for y in range(h // 2 - 40, h // 2 + 40, 4)]
    saved[key] = sum(values) / len(values)


def wood():
    Gui.ActiveDocument.getObject("Mirror").Visibility = False
    make_body(rect(0, 0, 60, 40), 0, 30, "Wood")
    Gui.Selection.clearSelection(); Gui.Selection.addSelection(body("Wood"))
    Gui.runCommand("Design_Appearance")


def tile(name):
    [b.click() for b in visible(QtWidgets.QToolButton) if b.toolTip() == name]


def scale():
    """Maßstab aus dem JPEG-Kommentar der Eiche: 600 mm je Kachel (verdichtet, tools/fetch_textures.py), die Koordinaten zählen 200 mm"""
    from pivy import coin
    search = coin.SoSearchAction(); search.setType(coin.SoTexture2Transform.getClassTypeId()); search.setInterest(coin.SoSearchAction.ALL)
    search.apply(Gui.ActiveDocument.getObject(body("Wood").Name).RootNode)
    factors = [p.getTail().scaleFactor.getValue()[0] for p in search.getPaths()]
    check("Photo scan: tile size from the image (oak 600 mm)", any(abs(f - 200 / 600) < 1e-3 for f in factors), str(factors))


def showcase():
    """Holz lackiert, gebürstetes Aluminium, Carbon, Glas, PLA mit Schichten nebeneinander"""
    for i, (name, mat) in enumerate([
            ("Glass", material((0.95, 0.97, 0.97), (0.5, 0.5, 0.5), 0.98, False, 0, 0.85)),
            ("PLA", material((0.94, 0.48, 0.12), (0.3, 0.3, 0.3), 0.35, False, 8)),
            ("Anodized", material((0.25, 0.44, 0.69), (0.2, 0.3, 0.5), 0.62, True)),
            ("Lacquer", material((0.69, 0.09, 0.12), (0.4, 0.4, 0.4), 0.70, False, 1))]):
        c = doc().addObject("Part::Sphere", name); c.Radius = 15
        c.Placement.Base = App.Vector(90 + 36 * i, 20, 15)
        doc().recompute()
        Gui.ActiveDocument.getObject(c.Name).ShapeAppearance = [mat]
    Gui.ActiveDocument.ActiveView.viewIsometric(); Gui.SendMsgToActiveView("ViewFit")


in_order([
    ("high", lambda: P.SetInt("RenderQuality", 0)),
    ("sphere", sphere), ("wait", lambda: None),
    ("measure pbr", lambda: measure("pbr")),
    ("shot pbr", lambda: shot("pbr")),
    ("pbr", lambda: check("PBR: the mirror sphere reflects the room, a sharp line where wall meets floor",
                          saved["pbr"] > 0.1, "largest jump %.2f" % saved["pbr"])),
    ("low", lambda: P.SetInt("RenderQuality", 2)), ("wait", lambda: None),
    ("measure phong", lambda: measure("phong")),
    ("shot phong", lambda: shot("phong")),
    ("phong", lambda: check("Low (Phong, as before): only soft gradients, no reflected room",
                            saved["phong"] < 0.05, "largest jump %.2f" % saved["phong"])),
    ("back", lambda: P.SetInt("RenderQuality", 0)),
    ("wood", wood), ("oak", lambda: tile("Oak, Lacquered")), ("ok", ok),
    ("scale", scale),
    ("right", lambda: fit("viewRight")), ("x high", lambda: center("x high")), ("shot end grain", lambda: shot("endgrain")),
    ("front", lambda: fit("viewFront")), ("y high", lambda: center("y high")), ("shot side grain", lambda: shot("sidegrain")),
    ("balanced", lambda: P.SetInt("RenderQuality", 1)), ("wait", lambda: None),
    ("y bal", lambda: center("y bal")),
    ("right 2", lambda: fit("viewRight")), ("x bal", lambda: center("x bal")),
    ("end grain", lambda: check("High: the end face (x) shows darker end grain, Balanced plain texture",
                                saved["x high"] / saved["y high"] < 0.95 * saved["x bal"] / saved["y bal"],
                                "x/y high %.3f, balanced %.3f" % (saved["x high"] / saved["y high"], saved["x bal"] / saved["y bal"]))),
    ("back 2", lambda: P.SetInt("RenderQuality", 0)),
    ("showcase", showcase), ("wait", lambda: None), ("shot showcase", lambda: shot("showcase")),
])
