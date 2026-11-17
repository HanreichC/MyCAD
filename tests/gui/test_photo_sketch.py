# SPDX-License-Identifier: LGPL-2.1-or-later
"""Phase 11.9 Foto wird Skizze: ein gemaltes Foto (helles Papier, dunkle Platte 600 x 400 px mit rundem Loch r = 80 px,
1200 x 900 px, wird dabei verkleinert) mit 60 mm Breite nachgezeichnet: Skizze 60 x 40 mm, das Loch etwa Ø16 mm, ein
geschlossenes Profil mit Loch, das sich extrudieren lässt."""
import os
from harness import *
import Design
import DesignGui
from PySide6 import QtGui

S = {}
W = ("wait", lambda: None)
PI = 3.141592653589793


def photo():
    img = QtGui.QImage(1200, 900, QtGui.QImage.Format_RGB32)
    img.fill(QtGui.QColor(225, 222, 215))  # Papier
    p = QtGui.QPainter(img)
    p.setRenderHint(QtGui.QPainter.Antialiasing)
    p.setPen(QtCore.Qt.NoPen)
    p.setBrush(QtGui.QColor(60, 62, 70))  # Teil
    p.drawRect(300, 250, 600, 400)
    p.setBrush(QtGui.QColor(225, 222, 215))  # Loch: Papier scheint durch
    p.drawEllipse(QtCore.QPointF(600, 450), 80, 80)
    p.end()
    S["file"] = os.path.join(os.environ.get("TMPDIR", "/tmp"), "mycad_photo_part.png")
    img.save(S["file"])


def trace():
    S["sk"] = DesignGui.photoToSketch(S["file"], 60.0)


def traced():
    sk = S["sk"]
    wires = sk.Shape.Wires if sk else []
    bb = sk.Shape.BoundBox if sk else None
    prof = [o for o in sk.InList if o.TypeId == "Design::Profiles"][0] if sk else None
    areas = sorted(f.Area for f in prof.Shape.Faces) if prof else []
    ring, disc = 60 * 40 - PI * 8 * 8, PI * 8 * 8
    check("the photo becomes a sketch to scale: 60 x 40 mm, outline and hole closed; profiles: the plate with its hole "
          "and the disc inside (like Fusion)",
          sk is not None and len(wires) == 2 and all(w.isClosed() for w in wires) and abs(bb.XLength - 60) < 1e-6
          and abs(bb.YLength - 40) < 0.2 and len(areas) == 2 and abs(areas[1] - ring) < 0.02 * ring
          and abs(areas[0] - disc) < 0.08 * disc,
          "wires=%d bb=%s areas=%s want %.1f, %.1f" % (len(wires), bb, [round(a, 1) for a in areas], ring, disc))
    circles = [e for e in sk.Shape.Edges if e.Curve.TypeId == "Part::GeomCircle"] if sk else []
    check("the round hole becomes a real circle, about 16 mm across", len(circles) == 1 and abs(circles[0].Curve.Radius - 8) < 0.3,
          str([(e.Curve.TypeId, round(e.Length, 2)) for e in (sk.Shape.Edges if sk else [])][:6]))
    shot("traced")


def missing():
    blank = QtGui.QImage(400, 300, QtGui.QImage.Format_RGB32)
    blank.fill(QtGui.QColor(230, 230, 230))
    path = os.path.join(os.environ.get("TMPDIR", "/tmp"), "mycad_photo_blank.png")
    blank.save(path)
    before = len([o for o in doc().Objects if o.TypeId == "Sketcher::SketchObject"])
    result = DesignGui.photoToSketch(path, 50.0)
    after = len([o for o in doc().Objects if o.TypeId == "Sketcher::SketchObject"])
    check("an empty photo makes no sketch", result is None and after == before, "result=%s" % result)


def told():
    check("and says why", any("No part found" in n for n in notices()), str(notices()))


def grid_paper():
    """Rasterpapier, Kästchen 20 px (= 5 mm), hellgraue Linien; das Teil 400 x 240 px = 100 x 60 mm"""
    img = QtGui.QImage(1000, 750, QtGui.QImage.Format_RGB32)
    img.fill(QtGui.QColor(232, 232, 228))
    p = QtGui.QPainter(img)
    p.setPen(QtGui.QPen(QtGui.QColor(190, 200, 210), 1.5))
    for x in range(0, 1000, 20):
        p.drawLine(x, 0, x, 750)
    for y in range(0, 750, 20):
        p.drawLine(0, y, 1000, y)
    p.setPen(QtCore.Qt.NoPen)
    p.setBrush(QtGui.QColor(50, 52, 60))
    p.drawRect(300, 250, 400, 240)
    p.end()
    S["grid"] = os.path.join(os.environ.get("TMPDIR", "/tmp"), "mycad_photo_grid.png")
    img.save(S["grid"])


def gridded():
    period = DesignGui.photoGrid(S["grid"])
    sk = DesignGui.photoToSketch(S["grid"], 0.0, 5.0)
    bb = sk.Shape.BoundBox if sk else None
    check("on grid paper the squares set the scale: 5 mm squares make the part 100 x 60 mm",
          abs(period - 20) < 0.1 and sk is not None and abs(bb.XLength - 100) < 0.5 and abs(bb.YLength - 60) < 0.5,
          "period=%.3f bb=%s" % (period, bb))
    check("a photo without a grid says so", DesignGui.photoGrid(S["file"]) == 0, str(DesignGui.photoGrid(S["file"])))


run([("activate", activate), ("missing", missing), W, ("told", told),  # zuerst: der Hinweis "nachgezeichnet" verdeckte ihn sonst
     ("photo", photo), ("trace", trace), W, W, ("traced", traced),
     ("grid paper", grid_paper), ("gridded", gridded), W,
     ("errors", lambda: check("no errors", not errors(), str(errors()))),
     ])
