#!/usr/bin/env python3
# SPDX-License-Identifier: LGPL-2.1-or-later
"""Umgebung "Raum" für die Körper-Materialien (BodyShading.cpp): ein heller Raum mit Leuchtflächen an Decke und Wänden,
selbst gerechnet und deshalb frei von fremden Lizenzen (Vorbild: three.js RoomEnvironment).
Erzeugt src/Gui/Shell/environment/room.png: ein Atlas aus 6 Equirect-Bildern 512x256 untereinander (Z oben, u = atan2(y, x),
v = Winkel von oben), in RGBM (Farbe * Alpha * 64 = Strahlung), so skaliert, dass das Streulicht im Mittel 1 ist:
    0 scharf, 1-4 Glanz für Rauheit 0,25 / 0,5 / 0,75 / 1, 5 Streulicht (Kosinus).
python3 tools/make_environment.py"""
import pathlib
import numpy as np
from PIL import Image

OUT = pathlib.Path(__file__).resolve().parent.parent / "src/Gui/Shell/environment"
W, H = 512, 256
RANGE = 64.0

# Raum (Z oben, Blick aus der Mitte): Wände, Boden und Decke matt, dazu Leuchtflächen (Strahlung > 1)
ROOM = np.array([[-6, 6], [-6, 6], [-2, 6]], float)
WALL, FLOOR, CEILING = 0.70, 0.55, 0.85  # hell wie ein Fotostudio: Metall spiegelt hell, die Lichter zeichnen sich ab
LIGHTS = [  # Achse, Seite (0/1), Bereich der beiden anderen Achsen, Strahlung
    (2, 1, (-2.2, 2.2), (-1.6, 1.6), 10.0),  # Deckenfeld
    (0, 0, (-2.4, 2.4), (0.4, 4.2), 7.0),    # linke Wand: großes Fenster
    (0, 1, (-1.2, 1.2), (1.0, 3.6), 4.0),    # rechte Wand: kleines Fenster
    (1, 1, (-4.0, 4.0), (4.4, 5.2), 6.0),    # hinten: Lichtband oben
    (1, 0, (-1.6, 1.6), (0.8, 3.0), 3.0),    # vorn: Fenster
]


def directions(w, h):
    v, u = np.mgrid[0:h, 0:w]
    theta = (v + 0.5) / h * np.pi
    phi = ((u + 0.5) / w - 0.5) * 2 * np.pi
    d = np.stack([np.sin(theta) * np.cos(phi), np.sin(theta) * np.sin(phi), np.cos(theta)], -1)
    return d, np.sin(theta)


def radiance(d):
    """Strahlung in Richtung d vom Mittelpunkt des Raums aus"""
    best = np.full(d.shape[:-1], np.inf)
    out = np.zeros(d.shape)
    for axis in range(3):
        for side in (0, 1):
            plane = ROOM[axis, side]
            with np.errstate(divide="ignore", invalid="ignore"):
                t = plane / d[..., axis]
            hit = d * t[..., None]
            ok = (t > 0) & (t < best)
            for other in range(3):
                if other != axis:
                    ok &= (hit[..., other] >= ROOM[other, 0] - 1e-6) & (hit[..., other] <= ROOM[other, 1] + 1e-6)
            base = CEILING if axis == 2 and side == 1 else FLOOR if axis == 2 else WALL
            value = np.full(d.shape[:-1], base)
            others = [o for o in range(3) if o != axis]
            for la, ls, ra, rb, k in LIGHTS:
                if la == axis and ls == side:
                    inside = (hit[..., others[0]] >= ra[0]) & (hit[..., others[0]] <= ra[1]) & \
                             (hit[..., others[1]] >= rb[0]) & (hit[..., others[1]] <= rb[1])
                    value = np.where(inside, k, value)
            best = np.where(ok, t, best)
            out = np.where(ok[..., None], value[..., None] * np.array([1.0, 1.0, 1.02]), out)
    return out


def render(w, h, ss=2):
    """Equirect mit Überabtastung (weiche Kanten der Leuchtflächen)"""
    d, _ = directions(w * ss, h * ss)
    img = radiance(d)
    return img.reshape(h, ss, w, ss, 3).mean((1, 3))


def blur(src, w, h, exponent):
    """Glanz-Keule max(N·L,0)^exponent über die Kugel gefaltet (Raumwinkel gewichtet), Ergebnis w x h"""
    sd, ssin = directions(src.shape[1], src.shape[0])
    L = sd.reshape(-1, 3)
    weight = (ssin.reshape(-1) * (np.pi / src.shape[0]) * (2 * np.pi / src.shape[1]))
    rad = src.reshape(-1, 3)
    nd, _ = directions(w, h)
    N = nd.reshape(-1, 3)
    out = np.zeros((N.shape[0], 3))
    for i in range(0, N.shape[0], 256):
        c = np.clip(N[i:i + 256] @ L.T, 0, None) ** exponent * weight
        out[i:i + 256] = (c @ rad) / c.sum(1, keepdims=True)
    return out.reshape(h, w, 3)


def upscale(img, w, h):
    return np.stack([np.asarray(Image.fromarray(img[..., c].astype(np.float32), "F").resize((w, h), Image.BILINEAR))
                     for c in range(3)], -1)


def rgbm(img):
    m = np.clip(img.max(-1, keepdims=True) / RANGE, 1 / 255, 1)
    m = np.ceil(m * 255) / 255
    rgb = np.clip(img / (m * RANGE), 0, 1)
    return (np.concatenate([rgb, m], -1) * 255 + 0.5).astype(np.uint8)


def main():
    OUT.mkdir(parents=True, exist_ok=True)
    level0 = render(W, H, ss=3)
    mid = level0.reshape(128, 2, 256, 2, 3).mean((1, 3))  # 256 x 128
    small = mid.reshape(64, 2, 128, 2, 3).mean((1, 3))    # 128 x 64
    levels = [level0]
    for r, src, size in ((0.25, mid, (128, 64)), (0.5, small, (64, 32)), (0.75, small, (64, 32)), (1.0, small, (64, 32))):
        alpha = r * r
        exponent = max(1.0, 2 / (alpha * alpha) - 2)
        levels.append(upscale(blur(src, *size, exponent), W, H))
    levels.append(upscale(blur(small, 64, 32, 1.0), W, H))  # Streulicht: Kosinus-Keule
    scale = 1.0 / levels[-1].mean()  # weiße matte Fläche: im Mittel Helligkeit 1, Belichtung im Shader bleibt einfach
    levels = [l * scale for l in levels]
    atlas = np.concatenate([rgbm(l) for l in levels], 0)
    Image.fromarray(atlas, "RGBA").save(OUT / "room.png", optimize=True)
    (OUT / "environment.qrc").write_text('<RCC>\n    <qresource prefix="/mycad/environment">\n        <file>room.png</file>\n'
                                         '    </qresource>\n</RCC>\n', newline="\n")
    for i, l in enumerate(levels):
        print("Ebene %d: Mittel %.2f, Max %.2f" % (i, l.mean(), l.max()))
    print("-> %s (%d KB)" % (OUT / "room.png", (OUT / "room.png").stat().st_size // 1024))


if __name__ == "__main__":
    main()
