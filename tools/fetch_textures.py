#!/usr/bin/env python3
# SPDX-License-Identifier: LGPL-2.1-or-later
"""Fotoscans der Körpermaterialien laden und aufbereiten. Alle Quellen sind CC0 (Public Domain): Poly Haven und
ambientCG, Liste in src/Gui/Shell/textures/SOURCES.md.
Je Material zwei Bilder in src/Gui/Shell/textures/:
    <name>.jpg    Farbe, kachelt nahtlos
    <name>_s.jpg  Oberfläche: Rot/Grün = Normale x/y (OpenGL), Blau = Rauheit als Faktor 0..2 (128 = 1, Mittel 1)
Die Maserung (Holz, Schliff) läuft entlang der Bild-x-Achse. Die Kachelgröße in mm steht als JPEG-Kommentar "mm: <n>"
im Farbbild (BodyShading.cpp liest sie). Schreibt auch textures.qrc und nennt die mittlere Farbe (Tabelle in Shell.cpp).
    python3 tools/fetch_textures.py <leerer Ordner für die Downloads>"""
import io
import json
import pathlib
import sys
import urllib.request
import zipfile

import numpy as np
from PIL import Image

OUT = pathlib.Path(__file__).resolve().parent.parent / "src/Gui/Shell/textures"

# Name, Quelle, Kennung, Kachel in mm (Poly Haven nennt sie, bei ambientCG geschätzt), Maserung entlang x drehen,
# Zielfarbe (Mittel) für Scans, deren Holz roh oder deren Farbe unpassend ist
SOURCES = [
    ("oak", "polyhaven", "oak_veneer_01", None, True, None),
    ("walnut", "polyhaven", "american_walnut_veneer", None, True, "#5E402A"),  # roh grau, geölt dunkelbraun
    ("maple", "polyhaven", "white_maple_veneer", None, True, None),
    ("cherry", "polyhaven", "cherry_veneer", None, True, "#A86A45"),  # Kirsche dunkelt nach
    ("pine", "polyhaven", "coated_pine", None, True, "#D3AE78"),  # lackiert orange, roh hell
    ("bamboo", "polyhaven", "bamboo_veneer", None, True, None),
    ("ash", "polyhaven", "ash_veneer", None, True, None),
    ("teak", "polyhaven", "teak_veneer", None, True, None),
    ("plywood", "polyhaven", "plywood", None, True, None),
    ("concrete", "polyhaven", "concrete_wall_008", None, False, "#9A9893"),
    ("marble", "ambientcg", "Marble012", 1000, False, None),
    ("marble_black", "ambientcg", "Marble016", 1000, False, None),
    ("granite", "ambientcg", "Granite002A", 600, False, None),
    ("leather", "polyhaven", "brown_leather", None, False, None),
    ("cork", "ambientcg", "Cork002", 300, False, None),
    ("fabric", "ambientcg", "Fabric030", 150, False, None),
    ("carbon", "ambientcg", "Fabric004", 35, False, None),  # Köper mit rund 3,5 mm breiten Bündeln
    ("brushed_aluminum", "ambientcg", "Metal009", 500, True, "#C4C8CC"),  # Metallfarbe = Spiegelung
    ("brushed_steel", "ambientcg", "Metal010", 500, True, "#9DA1A6"),
]
CAP = 600  # mm je Kachel höchstens: rund 3,4 Pixel je mm
AGENT = {"User-Agent": "MyCAD-texture-fetch"}


def get(url):
    with urllib.request.urlopen(urllib.request.Request(url, headers=AGENT), timeout=120) as r:
        return r.read()


def download(cache, source, ident):
    """Farbe, Normale (OpenGL) und Rauheit als Bytes, einmal geladen bleiben sie in cache liegen"""
    folder = cache / ident
    names = ["color.jpg", "normal.jpg", "rough.jpg"]
    if not all((folder / n).exists() for n in names):
        folder.mkdir(parents=True, exist_ok=True)
        if source == "polyhaven":
            files = json.loads(get("https://api.polyhaven.com/files/" + ident))
            for n, key in zip(names, ("Diffuse", "nor_gl", "Rough")):
                (folder / n).write_bytes(get(files[key]["2k"]["jpg"]["url"]))
            info = json.loads(get("https://api.polyhaven.com/info/" + ident))
            (folder / "mm.txt").write_text(str(round(max(info["dimensions"]))))
        else:
            archive = zipfile.ZipFile(io.BytesIO(get("https://ambientcg.com/get?file=%s_2K-JPG.zip" % ident)))
            for n, suffix in zip(names, ("Color", "NormalGL", "Roughness")):
                (folder / n).write_bytes(archive.read("%s_2K-JPG_%s.jpg" % (ident, suffix)))
    mm = (folder / "mm.txt").read_text() if (folder / "mm.txt").exists() else None
    return [np.asarray(Image.open(folder / n).convert("RGB"), np.float32) / 255 for n in names], mm


def along_x(color):
    """Läuft die Maserung senkrecht? Entlang der Fasern ändert sich die Farbe kaum."""
    g = color.mean(-1)
    return np.abs(np.diff(g, axis=1)).mean() < np.abs(np.diff(g, axis=0)).mean()


def tint(color, target):
    """Auf die Zielfarbe im Mittel bringen. Halb entsättigt, damit kein Kanal mit Faktor 10 das Rauschen aufbläst."""
    lum = (color @ np.array([0.2126, 0.7152, 0.0722], np.float32))[..., None]
    src = (color + lum) / 2
    goal = np.array([int(target[i:i + 2], 16) for i in (1, 3, 5)], np.float32) / 255
    return src * goal / src.mean((0, 1))


def resize(img, size):
    return np.stack([np.asarray(Image.fromarray(img[..., c], "F").resize((size, size), Image.LANCZOS))
                     for c in range(img.shape[-1])], -1)


def save(img, path, comment=None):
    pixels = (np.clip(img, 0, 1) * 255 + 0.5).astype(np.uint8)
    extra = {"comment": comment.encode()} if comment else {}
    Image.fromarray(pixels, "RGB").save(path, quality=87, optimize=True, **extra)


def main():
    if len(sys.argv) != 2:
        sys.exit(__doc__)
    cache = pathlib.Path(sys.argv[1])
    OUT.mkdir(parents=True, exist_ok=True)
    files = []
    for name, source, ident, mm, grain, target in SOURCES:
        (color, normal, rough), known = download(cache, source, ident)
        mm = mm or int(known)
        if grain and not along_x(color):
            # 90° gegen den Uhrzeigersinn, die Normale dreht mit: (x, y) -> (-y, x)
            color, normal, rough = (np.rot90(i).copy() for i in (color, normal, rough))
            n = normal * 2 - 1
            normal = np.stack([-n[..., 1], n[..., 0], n[..., 2]], -1) * 0.5 + 0.5
        if target:
            color = tint(color, target)
        # Große Scans (Furnierblatt 1-2 m) verdichten: Auf Teilen von 20-300 mm wäre die Maserung sonst unscharf und grob.
        # ponytail: Maserung dann bis 3x feiner als echt; wer es genau will, braucht 4K-Scans (4x so groß)
        size = 2048 if grain and mm >= 500 else 1024  # Stein und Stoff sind fleckig, da reicht weniger
        mm = min(mm, CAP)
        r = rough.mean(-1)
        factor = np.clip(r / max(r.mean(), 1e-3), 0, 2) / 2  # Rauheit relativ zum Mittel: das Material bestimmt den Glanz
        surface = np.concatenate([normal[..., :2], factor[..., None]], -1)
        save(resize(color, size), OUT / (name + ".jpg"), "mm: %d" % mm)
        save(resize(surface, size // 2), OUT / (name + "_s.jpg"))
        files += [name + ".jpg", name + "_s.jpg"]
        mean = (resize(color, 64).mean((0, 1)) * 255 + 0.5).astype(int)
        print("%-17s %4d mm  mittlere Farbe 0x%02X%02X%02XFF" % (name, mm, *mean))
    (OUT / "textures.qrc").write_text('<RCC>\n    <qresource prefix="/mycad/textures">\n'
                                      + "".join("        <file>%s</file>\n" % f for f in sorted(files))
                                      + "    </qresource>\n</RCC>\n", newline="\n")
    total = sum((OUT / f).stat().st_size for f in files)
    print("-> %s (%.1f MB)" % (OUT, total / 1e6))


if __name__ == "__main__":
    main()
