#!/usr/bin/env python3
# SPDX-License-Identifier: LGPL-2.1-or-later
"""Texturen der Körpermaterialien, rein prozedural und deshalb frei von fremden Lizenzen.
Alle kacheln nahtlos (Rauschen aus der FFT ist periodisch), eine Kachel entspricht 200 mm auf dem Körper
(TEXTURE_TILE_MM in ViewProviderExt.cpp), die Maserung läuft entlang der Bild-x-Achse.
Erzeugt src/Gui/Shell/textures/<name>.jpg und textures.qrc und nennt die mittlere Farbe jeder Textur (für die Tabelle
bodyMaterials in Shell.cpp).   python3 tools/make_textures.py"""
import pathlib
import numpy as np
from PIL import Image

OUT = pathlib.Path(__file__).resolve().parent.parent / "src/Gui/Shell/textures"
N = 1024
rng = np.random.default_rng(7)  # fest: gleiche Bilder bei jedem Lauf
y, x = np.mgrid[0:N, 0:N] / N


def noise(sx, sy, falloff=2.0, angle=0):
    """Periodisches Rauschen, Mittel 0, Streuung 1. sx/sy: Strukturen pro Kachel in x/y (kleiner = länger gezogen),
    angle dreht die Richtung (Grad)"""
    fy, fx = np.fft.fftfreq(N, 1 / N)[:, None], np.fft.fftfreq(N, 1 / N)[None, :]
    c, s = np.cos(np.radians(angle)), np.sin(np.radians(angle))
    filt = (1 + ((c * fx + s * fy) / sx) ** 2 + ((c * fy - s * fx) / sy) ** 2) ** (-falloff / 2)
    n = np.fft.ifft2(np.fft.fft2(rng.standard_normal((N, N))) * filt).real
    return (n - n.mean()) / n.std()


def hexrgb(h):
    return np.array([int(h[i:i + 2], 16) for i in (1, 3, 5)], float) / 255


def mix(a, b, t):
    """Farbe a bei t=0 bis b bei t=1"""
    t = np.clip(t, 0, 1)[..., None]
    return hexrgb(a) * (1 - t) + hexrgb(b) * t


def wood(light, dark, rings, warp, pores, contrast=1.0):
    """Fladerschnitt: Jahresringe laufen als lange Wellen entlang x und weiten sich zu Bögen. Die Verzerrung bleibt
    in y flacher als der Ringabstand, sonst reißen die Ringe zu Inseln ab."""
    f = rings * y + warp * (noise(0.7, 1.1, 4) + 0.1 * noise(1.5, 5, 3))  # rings ganzzahlig: bleibt periodisch
    ring = f % 1
    band = np.minimum(ring ** 2.2, (1 - ring) * 9)  # langsam dunkler, am Ringende schnell zurück
    tone = rng.random(rings)[np.floor(f).astype(int) % rings]  # jeder Ring eigener Ton, an der Kachelkante gleich
    fibers = noise(5, 420, 1.3)
    streaks = noise(1.2, 40, 2)
    pore = np.clip(noise(26, 620, 1.1) - 1.35, 0, 1)
    t = 0.2 + contrast * (0.32 * band + 0.14 * tone + 0.075 * fibers + 0.09 * streaks) + pores * pore
    return mix(light, dark, t)


def brushed(base, amount):
    """Gebürstetes Metall: sehr lange, sehr feine Streifen"""
    s = 0.7 * noise(5, 800, 1.1) + 0.3 * noise(1.5, 90, 1.5)
    return hexrgb(base) * (1 + amount * s + 0.012 * noise(3, 4, 2))[..., None]


def bamboo():
    t = wood("#E0C78F", "#B4935A", 64, 1.0, 0.35, 0.6)
    node = np.exp(-(((x * 3) % 1 - 0.5 + 0.0025 * noise(1.5, 1.5, 3)) / 0.006) ** 2)  # Knoten quer zur Faser
    return t * (1 - 0.22 * node)[..., None]


def carbon():
    """2x2-Köper: 64 Bündel pro Kachel, also rund 3 mm. Abwechselnd liegt ein Bündel in x- oder y-Richtung oben."""
    tows = 64
    u, v = x * tows, y * tows
    over = ((np.floor(u) + np.floor(v)) % 4) < 2
    across = np.where(over, v % 1, u % 1)  # Position quer zum obenliegenden Bündel
    fine = np.where(over, noise(25, 900, 0.9), noise(900, 25, 0.9))
    level = np.where(over, 0.21, 0.125) * (0.68 + 0.32 * np.sin(np.pi * across) ** 0.7) + 0.012 * fine
    return level[..., None] * hexrgb("#F2F3F7")


def concrete():
    t = 0.5 + 0.05 * noise(5, 5, 2.4) + 0.05 * noise(60, 60, 1.6) + 0.03 * noise(400, 400, 1)
    img = mix("#6E6E6A", "#B8B7B1", t)
    pores = np.clip((noise(110, 110, 1.4) - 2.6) * 2, 0, 1)
    return img * (1 - 0.65 * pores)[..., None]


def marble():
    """Adern sind Nulllinien von Rauschen, schräg gestreckt: laufen durch, statt Ringe zu bilden"""
    a = noise(1.1, 4, 3.4, 35) + 0.18 * noise(8, 8, 2.4)
    b = noise(1.4, 6, 3.2, 20) + 0.14 * noise(14, 14, 2.2)
    strength = 0.55 + 0.45 * np.tanh(noise(2, 2, 3))
    vein = np.exp(-(a / 0.035) ** 2) * strength + 0.35 * np.exp(-(b / 0.02) ** 2) + 0.14 * np.exp(-(a / 0.22) ** 2)
    return mix("#F2F0EB", "#5F636B", 0.08 + 0.05 * noise(4, 4, 2.4) + 0.85 * vein)


def granite():
    img = mix("#8E8B88", "#B6B1AC", 0.5 + 0.3 * noise(90, 90, 1.4))
    img = np.where((noise(120, 120, 1.8) > 0.75)[..., None], hexrgb("#26252A"), img)
    img = np.where((noise(100, 100, 1.8) > 1.15)[..., None], hexrgb("#B78B7E"), img)
    img = np.where((noise(180, 180, 1.4) > 2.1)[..., None], hexrgb("#E4E1DC"), img)
    return img


def leather():
    """Falten als Nulllinien von Rauschen, dazwischen gewölbte Narben"""
    a, b = noise(34, 34, 2.6), noise(42, 42, 2.6)
    crease = np.exp(-(a / 0.16) ** 2) + np.exp(-(b / 0.16) ** 2)
    return mix("#7A4A2D", "#2E1A0F", 0.2 + 0.07 * noise(4, 4, 2.4) + 0.42 * crease + 0.05 * noise(300, 300, 1))


def cork():
    img = mix("#C49A6C", "#946A41", 0.5 + 0.28 * noise(70, 70, 1.8) + 0.1 * noise(9, 9, 2))
    img = np.where((noise(55, 55, 2.2) > 1.1)[..., None], hexrgb("#6B4628"), img)
    img = np.where((noise(45, 45, 2.2) > 1.5)[..., None], hexrgb("#DDBB8E"), img)
    return img


TEXTURES = {
    "oak": lambda: wood("#D6B27C", "#7A522B", 26, 1.7, 0.5),
    "walnut": lambda: wood("#80593B", "#26170F", 30, 2.0, 0.35),
    "maple": lambda: wood("#EFDBB5", "#BE9A68", 34, 1.2, 0.1, 0.75),
    "cherry": lambda: wood("#C5825A", "#6B361C", 30, 1.5, 0.12),
    "pine": lambda: wood("#F0D8A8", "#A16C2E", 18, 1.6, 0.04, 1.3),
    "bamboo": bamboo,
    "brushed_aluminum": lambda: brushed("#C6C9CC", 0.05),
    "brushed_steel": lambda: brushed("#8D9094", 0.08),
    "carbon": carbon,
    "concrete": concrete,
    "marble": marble,
    "granite": granite,
    "leather": leather,
    "cork": cork,
}

if __name__ == "__main__":
    OUT.mkdir(exist_ok=True)
    for name, make in TEXTURES.items():
        img = (np.clip(make(), 0, 1) * 255 + 0.5).astype(np.uint8)
        Image.fromarray(img).save(OUT / (name + ".jpg"), quality=84, optimize=True)
        print("%-18s #%02X%02X%02X  %4d KB" % (name, *img.mean((0, 1)).round().astype(int), (OUT / (name + ".jpg")).stat().st_size // 1024))
    (OUT / "textures.qrc").write_text('<RCC>\n    <qresource prefix="/mycad/textures">\n'
                                      + "".join("        <file>%s.jpg</file>\n" % n for n in TEXTURES)
                                      + "    </qresource>\n</RCC>\n")
