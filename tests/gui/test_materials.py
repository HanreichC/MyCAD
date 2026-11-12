# SPDX-License-Identifier: LGPL-2.1-or-later
"""Körper-Materialien (Gui/Shell/BodyShading.cpp) und die Schalter unter Einstellungen → Materialien und Licht: eine
spiegelnde Chromkugel zeigt den Raum, darin eine scharfe Linie, wo Wand und Boden aufeinandertreffen; ohne Spiegelungen
oder ohne realistische Materialien (Phong, wie früher) nur weiche Verläufe. Fotoscans: Maßstab aus dem Bild, Hirnholz an
der Stirnseite (Relief und Hirnholz), Kontaktschatten. Zum Schluss ein Bild aller Effekte.
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


def ground(key):
    """Boden direkt vor dem Holzklotz (2 mm) und weiter weg (25 mm), von oben: Verhältnis der Helligkeit"""
    v = Gui.ActiveDocument.ActiveView
    img = view().viewport().grab().toImage()
    def at(y):
        px, py = v.getPointOnViewport(App.Vector(30, y, 0))
        x, y = int(px), int(img.height() - py)
        values = [lum(img, x + dx, y + dy) for dx in range(-6, 7, 2) for dy in range(-1, 2)]  # Rasterlinien mitteln
        return sum(values) / len(values)
    saved[key] = at(-2) / max(at(-25), 1e-3)


def scribble():
    """dicker Marker-Strich flach auf dem Boden neben dem Holzklotz: ein Scribble wirft keinen Schatten"""
    s = doc().addObject("Design::Scribble", "Scribble")
    s.Sheet = App.Placement(App.Vector(0, 0, 0.5), App.Rotation())
    s.Points = [App.Vector(x, -60, 0.5) for x in (80, 120, 160)]; s.Widths = [15.0] * 3
    s.Tools = [2]; s.Kinds = [0]; s.Colors = [(0.2, 0.2, 0.2, 0.35)]; s.Normals = [App.Vector(0, 0, 1)]
    s.Counts = [3]
    doc().recompute()


def beside_scribble():
    v = Gui.ActiveDocument.ActiveView
    img = view().viewport().grab().toImage()
    def at(y):
        px, py = v.getPointOnViewport(App.Vector(120, y, 0))
        x, y = int(px), int(img.height() - py)
        values = [lum(img, x + dx, y + dy) for dx in range(-6, 7, 2) for dy in range(-1, 2)]
        return sum(values) / len(values)
    saved["scribble"] = at(-72) / max(at(-95), 1e-3)  # 4,5 mm neben dem Strich gegen weit weg


def top():
    fit("viewTop")
    cam = Gui.ActiveDocument.ActiveView.getCameraNode()
    cam.height.setValue(cam.height.getValue() * 2)  # Boden rund um den Klotz sichtbar


def tones(key):
    """Kiste im Vorgabe-Material (Stahl), Iso-Ansicht: Helligkeit in der Mitte von Deckel, Vorder- und rechter Seite"""
    v = Gui.ActiveDocument.ActiveView
    img = view().viewport().grab().toImage()
    def at(p):
        x, y = v.getPointOnViewport(App.Vector(*p))
        return round(255 * lum(img, int(x), int(img.height() - y)))
    saved[key] = [at((20, 15, 25)), at((20, 0, 12.5)), at((40, 15, 12.5))]


def tone_box():
    b = doc().addObject("Part::Box", "Tones"); b.Length, b.Width, b.Height = 40, 30, 25
    doc().recompute()
    Gui.ActiveDocument.ActiveView.viewIsometric(); Gui.SendMsgToActiveView("ViewFit")


def flip():
    """dieselbe Kiste um 180° um x gedreht an derselben Stelle, wie ein Arm, den ein Gelenk umklappt: oben bleibt oben"""
    doc().getObject("Tones").Placement = App.Placement(App.Vector(0, 30, 25), App.Rotation(App.Vector(1, 0, 0), 180))
    doc().recompute()


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
    ("all on", lambda: [P.SetBool(k, True) for k in ("RealisticMaterials", "Reflections", "SurfaceDetail", "ContactShadow")]),
    # Studio (Vorgabe): jede Fläche ihr eigener Tonwert, sonst wirken Körper flach (im Raum waren Deckel und Vorderseite gleich)
    ("tone box", tone_box), ("wait", lambda: None), ("studio tones", lambda: tones("studio")), ("shot tones", lambda: shot("tones")),
    ("three tones", lambda: check("Studio light: the default material shows three distinct shades, top > front > right",
                                  saved["studio"][0] > saved["studio"][1] + 12 and saved["studio"][1] > saved["studio"][2] + 12,
                                  str(saved["studio"]))),
    ("room", lambda: P.SetInt("Lighting", 1)), ("wait", lambda: None), ("room tones", lambda: tones("room")),
    ("room switch", lambda: check("Lighting Room switches the environment", saved["room"] != saved["studio"],
                                  "studio %s room %s" % (saved["studio"], saved["room"]))),
    ("studio", lambda: P.SetInt("Lighting", 0)),
    ("flip", flip), ("wait", lambda: None), ("flipped tones", lambda: tones("flipped")),
    ("world light", lambda: check("A rotated body is lit in world space: its top stays the brightest, same shades as unrotated",
                                  max(abs(a - b) for a, b in zip(saved["flipped"], saved["studio"])) <= 6,
                                  "unrotated %s rotated %s" % (saved["studio"], saved["flipped"]))),
    ("hide tone box", lambda: setattr(Gui.ActiveDocument.getObject("Tones"), "Visibility", False)),
    ("sphere", sphere), ("wait", lambda: None),
    ("measure pbr", lambda: measure("pbr")),
    ("shot pbr", lambda: shot("pbr")),
    ("pbr", lambda: check("PBR: the mirror sphere reflects the room, a sharp line where wall meets floor",
                          saved["pbr"] > 0.1, "largest jump %.2f" % saved["pbr"])),
    ("no reflections", lambda: P.SetBool("Reflections", False)), ("wait", lambda: None),
    ("measure soft", lambda: measure("soft")),
    ("soft", lambda: check("Reflections off: only soft sheen, no reflected room", saved["soft"] < 0.05, "largest jump %.2f" % saved["soft"])),
    ("reflections back", lambda: P.SetBool("Reflections", True)),
    ("low", lambda: P.SetBool("RealisticMaterials", False)), ("wait", lambda: None),
    ("measure phong", lambda: measure("phong")),
    ("shot phong", lambda: shot("phong")),
    ("phong", lambda: check("Realistic materials off (Phong, as before): only soft gradients, no reflected room",
                            saved["phong"] < 0.05, "largest jump %.2f" % saved["phong"])),
    ("back", lambda: P.SetBool("RealisticMaterials", True)),
    ("wood", wood), ("oak", lambda: tile("Oak, Lacquered")), ("ok", ok),
    ("scale", scale),
    ("right", lambda: fit("viewRight")), ("x high", lambda: center("x high")), ("shot end grain", lambda: shot("endgrain")),
    ("front", lambda: fit("viewFront")), ("y high", lambda: center("y high")), ("shot side grain", lambda: shot("sidegrain")),
    ("balanced", lambda: P.SetBool("SurfaceDetail", False)), ("wait", lambda: None),
    ("y bal", lambda: center("y bal")),
    ("right 2", lambda: fit("viewRight")), ("x bal", lambda: center("x bal")),
    ("end grain", lambda: check("Relief and end grain: the end face (x) shows darker end grain, off plain texture",
                                saved["x high"] / saved["y high"] < 0.95 * saved["x bal"] / saved["y bal"],
                                "x/y high %.3f, balanced %.3f" % (saved["x high"] / saved["y high"], saved["x bal"] / saved["y bal"]))),
    ("back 2", lambda: P.SetBool("SurfaceDetail", True)),
    ("top", top), ("wait", lambda: None), ("shadow high", lambda: ground("shadow high")), ("shot shadow", lambda: shot("shadow")),
    ("balanced 2", lambda: P.SetBool("ContactShadow", False)), ("wait", lambda: None), ("shadow bal", lambda: ground("shadow bal")),
    ("shadow", lambda: check("Contact shadow darkens the ground next to the body, switched off none",
                             saved["shadow high"] < 0.93 and saved["shadow bal"] > 0.97,
                             "near/far high %.3f, balanced %.3f" % (saved["shadow high"], saved["shadow bal"]))),
    ("back 3", lambda: P.SetBool("ContactShadow", True)),
    ("scribble", scribble), ("top 2", top), ("wait", lambda: None), ("wait", lambda: None),
    ("beside scribble", beside_scribble), ("shot scribble", lambda: shot("scribble")),
    ("scribble check", lambda: check("A scribble casts no shadow", saved["scribble"] > 0.97, "near/far %.3f" % saved["scribble"])),
    ("showcase", showcase), ("wait", lambda: None), ("shot showcase", lambda: shot("showcase")),
])
