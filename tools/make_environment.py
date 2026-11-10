#!/usr/bin/env python3
# SPDX-License-Identifier: LGPL-2.1-or-later
"""Umgebung "Raum" für die Körper-Materialien (BodyShading.cpp): genau die RoomEnvironment von three.js (r165, aus
Googles model-viewer): ein grauer Raum mit sechs Kisten am Boden und sechs hellen Lichtflächen, die Wände von einer
Punktleuchte unter der Decke beleuchtet. Hier per Strahlverfolgung nachgerechnet, mit denselben absoluten Werten, damit
MyCAD aussieht wie die Vorschau im Browser (Belichtung 1, Tonwertkurve PBR Neutral).
Erzeugt src/Gui/Shell/environment/room.png: ein Atlas aus 6 Equirect-Bildern 512x256 untereinander (Z oben, u = atan2(y, x),
v = Winkel von oben), 16 Bit je Kanal, Wurzel-kodiert (Strahlung = Wert² * 128; ohne RGBM, das beim Filtern Stufen macht):
    0 fast scharf (Sigma 0,04 wie three.js), 1-4 Glanz für Rauheit 0,25 / 0,5 / 0,75 / 1, 5 Streulicht (Kosinus, = Bestrahlung / pi).
python3 tools/make_environment.py"""
import pathlib
import struct
import zlib

import numpy as np
from PIL import Image

OUT = pathlib.Path(__file__).resolve().parent.parent / "src/Gui/Shell/environment"
W, H = 512, 256
RANGE = 128.0  # Lichtflächen bis 100

# three.js-Koordinaten (y oben); Kisten: Mitte, Drehung um y, Maße
ROOM = ((-0.757, 13.219, 0.717), 0.0, (31.713, 28.305, 28.591))
BOXES = [((-10.906, 2.009, 1.846), -0.195, (2.328, 7.905, 4.651)),
         ((-5.607, -0.754, -0.758), 0.994, (1.970, 1.534, 3.955)),
         ((6.167, 0.857, 7.803), 0.561, (3.927, 6.285, 3.687)),
         ((-2.017, 0.018, 6.124), 0.333, (2.002, 4.566, 2.064)),
         ((2.291, -0.756, -2.621), -0.286, (1.546, 1.552, 1.496)),
         ((-2.193, -0.369, -5.547), 0.516, (3.875, 3.487, 2.986))]
LIGHTS = [((-16.116, 14.37, 8.208), (0.1, 2.428, 2.739), 50), ((-16.109, 18.021, -8.207), (0.1, 2.425, 2.751), 50),
          ((14.904, 12.198, -1.832), (0.15, 4.265, 6.331), 17), ((-0.462, 8.89, 14.520), (4.38, 5.441, 0.088), 43),
          ((3.235, 11.486, -12.541), (2.5, 2.0, 0.1), 20), ((0.0, 20.0, 0.0), (1.0, 0.1, 1.0), 100)]
POINT, POWER, CUTOFF = np.array((0.418, 16.199, 0.300)), 900.0, 28.0


def directions(w, h):
    v, u = np.mgrid[0:h, 0:w]
    theta = (v + 0.5) / h * np.pi
    phi = ((u + 0.5) / w - 0.5) * 2 * np.pi
    d = np.stack([np.sin(theta) * np.cos(phi), np.sin(theta) * np.sin(phi), np.cos(theta)], -1)
    return d, np.sin(theta)


def hit_box(d, center, angle, size, inside):
    """Strahl vom Ursprung gegen eine gedrehte Kiste: Abstand und Normale (nach außen, für inside nach innen)"""
    c, s = np.cos(angle), np.sin(angle)
    rot = np.array([[c, 0, s], [0, 1, 0], [-s, 0, c]])  # wie three.js rotation.y
    o = -rot.T @ np.array(center)
    ld = d @ rot  # = rot.T @ d
    half = np.array(size) / 2
    with np.errstate(divide="ignore", invalid="ignore"):
        t1, t2 = (-half - o) / ld, (half - o) / ld
    near, far = np.minimum(t1, t2), np.maximum(t1, t2)
    tn, tf = near.max(-1), far.min(-1)
    t = np.where(inside, tf, tn)
    ok = (tf >= tn) & (t > 1e-6)
    axis = np.where(inside, far.argmin(-1), near.argmax(-1))
    p = o + ld * t[..., None]
    n_local = np.zeros(d.shape)
    idx = np.indices(axis.shape)
    n_local[(*idx, axis)] = np.sign(p[(*idx, axis)]) * (-1 if inside else 1)
    return np.where(ok, t, np.inf), n_local @ rot.T


def radiance(d3):
    """Strahlung in Richtung d3 (three.js-Koordinaten) aus der Mitte des Raums"""
    best, normal = hit_box(d3, *ROOM, inside=True)
    emit = np.full(best.shape, -1.0)
    for center, angle, size in BOXES:
        t, n = hit_box(d3, center, angle, size, inside=False)
        closer = t < best
        best, normal = np.where(closer, t, best), np.where(closer[..., None], n, normal)
    for center, size, k in LIGHTS:
        t, _ = hit_box(d3, center, 0.0, size, inside=False)
        closer = t < best
        best, emit = np.where(closer, t, best), np.where(closer, k, emit)
    # weiße matte Fläche (MeshStandardMaterial): Lambert, Punktleuchte mit Abfall wie three.js, ohne Schatten
    p = d3 * best[..., None]
    to = POINT - p
    dist = np.linalg.norm(to, axis=-1)
    fall = 1 / np.maximum(dist ** 2, 0.01) * np.clip(1 - (dist / CUTOFF) ** 4, 0, 1) ** 2
    lit = POWER * fall * np.clip((normal * to).sum(-1) / dist, 0, None) / np.pi
    value = np.where(emit >= 0, emit, lit)
    return np.repeat(value[..., None], 3, -1)


def render(w, h, ss=3):
    """Equirect mit Überabtastung; Z oben: three.js (x, y, z) = (x, z, -y)"""
    d, _ = directions(w * ss, h * ss)
    d3 = np.stack([d[..., 0], d[..., 2], -d[..., 1]], -1)
    return radiance(d3).reshape(h, ss, w, ss, 3).mean((1, 3))


def blur(src, w, h, exponent):
    """Glanz-Keule max(N·L,0)^exponent über die Kugel gefaltet (Raumwinkel gewichtet), Ergebnis w x h"""
    sd, ssin = directions(src.shape[1], src.shape[0])
    L = sd.reshape(-1, 3)
    weight = (ssin.reshape(-1) * (np.pi / src.shape[0]) * (2 * np.pi / src.shape[1]))
    rad = src.reshape(-1, 3)
    nd, _ = directions(w, h)
    N = nd.reshape(-1, 3)
    out = np.zeros((N.shape[0], 3))
    L32, w32 = L.astype(np.float32), weight.astype(np.float32)
    for i in range(0, N.shape[0], 256):
        c = np.clip(N[i:i + 256].astype(np.float32) @ L32.T, 0, None) ** exponent * w32
        out[i:i + 256] = (c @ rad) / c.sum(1, keepdims=True)
    return out.reshape(h, w, 3)


def upscale(img, w, h):
    return np.stack([np.asarray(Image.fromarray(img[..., c].astype(np.float32), "F").resize((w, h), Image.BILINEAR))
                     for c in range(3)], -1)


def encode(img):
    return (np.sqrt(np.clip(img / RANGE, 0, 1)) * 65535 + 0.5).astype(">u2")


def save_png16(path, rgb):
    """RGB mit 16 Bit je Kanal (Pillow schreibt das nicht)"""
    rgb = rgb.astype(">u2")  # PNG speichert Big-Endian; concatenate liefert die eigene Byte-Reihenfolge
    h, w, _ = rgb.shape
    raw = b"".join(bytes(1) + rgb[y].tobytes() for y in range(h))  # je Zeile Filter 0
    chunk = lambda kind, data: struct.pack(">I", len(data)) + kind + data + struct.pack(">I", zlib.crc32(kind + data))
    path.write_bytes(bytes([137, 80, 78, 71, 13, 10, 26, 10]) + chunk(b"IHDR", struct.pack(">IIBBBBB", w, h, 16, 2, 0, 0, 0))
                     + chunk(b"IDAT", zlib.compress(raw, 9)) + chunk(b"IEND", b""))


def main():
    OUT.mkdir(parents=True, exist_ok=True)
    sharp = render(W, H, ss=4)
    mid = sharp.reshape(128, 2, 256, 2, 3).mean((1, 3))  # 256 x 128
    small = mid.reshape(64, 2, 128, 2, 3).mean((1, 3))   # 128 x 64
    # wie PMREMGenerator.fromScene(scene, 0.04): leicht weich (Sigma 0,04 rad, Keule cos^625), auch gegen Kanten am Pol
    levels = [upscale(blur(mid, 256, 128, 1 / 0.04 ** 2), W, H)]
    for r, src, size in ((0.25, mid, (256, 128)), (0.5, mid, (128, 64)), (0.75, small, (64, 32)), (1.0, small, (64, 32))):
        # GGX-Rauheit -> Phong-Keule (2/α² - 2) um die Halbvektor-Normale; die Spiegelrichtung streut doppelt so weit,
        # die Keule um sie ist also viermal flacher
        alpha = r * r
        exponent = max(1.0, (2 / (alpha * alpha) - 2) / 4)
        levels.append(upscale(blur(src, *size, exponent), W, H))
    levels.append(upscale(blur(small, 64, 32, 1.0), W, H))  # Streulicht: Kosinus-Keule
    save_png16(OUT / "room.png", np.concatenate([encode(l) for l in levels], 0))
    (OUT / "environment.qrc").write_text('<RCC>\n    <qresource prefix="/mycad/environment">\n        <file>room.png</file>\n'
                                         '    </qresource>\n</RCC>\n', newline="\n")
    for i, l in enumerate(levels):
        print("Ebene %d: Mittel %.2f, Max %.2f" % (i, l.mean(), l.max()))
    s = levels[-1]
    print("Streulicht oben %.2f, Seite %.2f, unten %.2f" % (s[0].mean(), s[H // 2].mean(), s[-1].mean()))
    print("-> %s (%d KB)" % (OUT / "room.png", (OUT / "room.png").stat().st_size // 1024))


if __name__ == "__main__":
    main()
