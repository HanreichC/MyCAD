# SPDX-License-Identifier: LGPL-2.1-or-later
"""Körper-Materialien (Gui/Shell/BodyShading.cpp): eine spiegelnde Chromkugel zeigt den Raum, darin eine scharfe Linie, wo
Wand und Boden aufeinandertreffen. Mit Materialien "Sparsam" (Phong, wie früher) gibt es nur weiche Verläufe.
Fehler stehen als FAIL im Protokoll."""
from harness import *
import Part

saved = {}
P = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")


def material(diffuse, specular, shininess, metal):
    m = App.Material()
    m.DiffuseColor = diffuse; m.SpecularColor = specular; m.Shininess = shininess
    m.EmissiveColor = (0.0, 0.0, (2 if metal else 1) / 255.0)  # Markierung: Metall ja/nein (BodyShading.h)
    return m


def sphere():
    s = doc().addObject("Part::Sphere", "Mirror"); s.Radius = 20
    doc().recompute()
    Gui.ActiveDocument.getObject(s.Name).ShapeAppearance = [material((0.9, 0.9, 0.9), (0.9, 0.9, 0.9), 0.97, True)]
    v = Gui.ActiveDocument.ActiveView
    v.viewFront(); Gui.SendMsgToActiveView("ViewFit")


def measure(key):
    """größter Helligkeitssprung auf 6 px entlang der senkrechten Mittellinie der Kugel (Vorderansicht)"""
    img = view().viewport().grab().toImage()
    w, h = img.width(), img.height()
    lum = []
    for y in range(int(h * 0.40), int(h * 0.72), 2):
        c = img.pixelColor(w // 2, y)
        lum.append(0.2126 * c.redF() + 0.7152 * c.greenF() + 0.0722 * c.blueF())
    saved[key] = max(abs(a - b) for a, b in zip(lum, lum[3:]))


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
])
