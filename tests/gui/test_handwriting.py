# SPDX-License-Identifier: LGPL-2.1-or-later
"""Schönschrift und Handschrift lesen in Scribbles, mit echten Mausstrichen: verkrakelte Druckschrift wird nach der
Schreibpause aufgeräumt (Rückgängig holt sie roh zurück), o12 bekommt seinen Schrägstrich, die Suche in der Palette
findet Geschriebenes, ein Ø12 am Kreis wird beim Umwandeln zur Bemaßung. Fehler stehen als FAIL im Protokoll."""
import math
from harness import *
from PySide6 import QtGui

saved = {}


def s():
    return [o for o in doc().Objects if o.TypeId == "Design::Scribble"][0]


def strokes():
    """je Strich seine Punkte (Blatt = XY-Ebene, solange das Blatt nicht umgestellt ist)"""
    out, k = [], 0
    for n in s().Counts:
        out.append(s().Points[k:k + n]); k += n
    return out


def send(kind, x, y, button, buttons):
    vp = view().viewport(); p = QtCore.QPointF(x, y)
    QtWidgets.QApplication.sendEvent(vp, QtGui.QMouseEvent(kind, p, vp.mapToGlobal(p), button, buttons, QtCore.Qt.NoModifier))


def draw(points):
    send(QtCore.QEvent.MouseButtonPress, *points[0], QtCore.Qt.LeftButton, QtCore.Qt.LeftButton)
    for x, y in points[1:]:
        send(QtCore.QEvent.MouseMove, x, y, QtCore.Qt.NoButton, QtCore.Qt.LeftButton)
    send(QtCore.QEvent.MouseButtonRelease, *points[-1], QtCore.Qt.LeftButton, QtCore.Qt.NoButton)


# Einzelstrich-Druckschrift wie in tests/scribble_read_check.cpp: Einheit x-Höhe, y nach unten, Grundlinie 0
def arc(cx, cy, rx, ry, t0, t1, n=14):
    return [(cx + rx * math.cos(math.radians(t0 + (t1 - t0) * i / n)), cy + ry * math.sin(math.radians(t0 + (t1 - t0) * i / n))) for i in range(n + 1)]


def arch(x0, x1):
    return [(x0, -.55)] + arc((x0 + x1) / 2, -.55, (x1 - x0) / 2, .42, 180, 360, 10) + [(x1, 0)]


GLYPHS = {
    "o": (.85, [arc(.4, -.5, .32, .5, -80, -430, 20)]),
    "e": (.85, [[(.1, -.5), (.72, -.52)] + arc(.41, -.5, .32, .5, -5, -310, 16)]),
    "n": (.85, [[(.1, -1), (.1, 0)], arch(.1, .66)]),
    "m": (1.3, [[(.1, -1), (.1, 0)], arch(.1, .6), arch(.6, 1.1)]),
    "h": (.85, [[(.1, -1.7), (.1, 0)], arch(.1, .66)]),
    "r": (.62, [[(.1, -1), (.1, 0)], [(.1, -.5)] + arc(.38, -.55, .26, .42, 180, 290, 6)]),
    "u": (.85, [[(.1, -1)] + arc(.38, -.45, .28, .45, 180, 0, 10), [(.66, -1), (.66, 0)]]),
    "g": (.9, [arc(.4, -.5, .32, .5, -30, -370, 18), [(.74, -1), (.74, .35)] + arc(.42, .35, .32, .3, 0, 150, 8)]),
    "l": (.45, [[(.15, -1.7), (.14, -.25)] + arc(.3, -.25, .16, .25, 180, 90, 5)]),
    "B": (.85, [[(.1, -1.6), (.1, 0)], [(.1, -1.6), (.45, -1.6), (.65, -1.45), (.63, -1.02), (.4, -.86), (.12, -.86), (.5, -.84), (.74, -.6), (.72, -.2), (.5, -.02), (.1, 0)]]),
    "W": (1.15, [[(0, -1.6), (.27, 0), (.55, -1.05), (.82, 0), (1.1, -1.6)]]),
    "1": (.55, [[(.08, -1.25), (.36, -1.6), (.36, 0)]]),
    "2": (.82, [[(.1, -1.25), (.3, -1.58), (.58, -1.5), (.65, -1.1), (.1, 0), (.75, 0)]]),
    "5": (.8, [[(.68, -1.6), (.18, -1.6), (.13, -.88), (.45, -.98), (.7, -.72), (.68, -.22), (.42, 0), (.08, -.14)]]),
}


def dense(poly, step=.06):
    """gerade Stücke fein unterteilen: die Maus liefert auch nur Punkte im Pixelabstand"""
    out = [poly[0]]
    for (x0, y0), (x1, y1) in zip(poly, poly[1:]):
        n = max(1, int(math.hypot(x1 - x0, y1 - y0) / step))
        out += [(x0 + (x1 - x0) * k / n, y0 + (y1 - y0) * k / n) for k in range(1, n + 1)]
    return out


def write(text, fx, fy, u=20, tilt=3.0, messy=1.0):
    """Text in Pixeln aufs Blatt; Wörter verschieden hoch, groß und schräg, die Zeile gekippt"""
    v = view(); x0, y0 = v.width() * fx, v.height() * fy
    t = math.radians(tilt * messy); cx = 0
    for wi, word in enumerate(text.split(" ")):
        dy, scale, shear = messy * (.25, -.2, .1)[wi % 3], 1 + messy * (.0, .25, -.15)[wi % 3], .1 + messy * (.0, .2, -.1)[wi % 3]
        gx = 0
        for ch in word:
            w, polys = GLYPHS[ch]
            for poly in polys:
                pts = []
                for px, py in dense(poly):
                    px, py = (px + gx) * scale - py * scale * shear + cx, py * scale + dy
                    rx, ry = px * math.cos(t) - py * math.sin(t), px * math.sin(t) + py * math.cos(t)
                    pts.append((x0 + rx * u, y0 + ry * u))
                draw(pts)
            gx += w + .08
        cx += gx * scale + .6 + messy * .3 * (wi % 2)


def count(text):
    """so viele Striche schreibt write() für den Text"""
    return sum(len(GLYPHS[c][1]) for c in text if c != " ")


def spread_of_bottoms(ss, words):
    """wie weit die Wörter einer Zeile in der Höhe auseinanderliegen (Blatt-y der Unterkanten, je Wort Median)"""
    bottoms = []
    for a, b in words:
        lows = sorted(min(p.y for p in st) for st in ss[a:b])
        bottoms.append(lows[len(lows) // 2])
    return max(bottoms) - min(bottoms)


_pen = []


def tablet(kind, x, y, pressure, button, buttons):
    """Grafiktablett wie über Wayland (Huion H640P: Stift ohne Radierer-Ende); True, wenn das Blatt es angenommen hat"""
    if not _pen:
        _pen.append(QtGui.QPointingDevice("pen", 17, QtGui.QInputDevice.DeviceType.Stylus, QtGui.QPointingDevice.PointerType.Pen,
                                          QtGui.QInputDevice.Capability.Position | QtGui.QInputDevice.Capability.Pressure, 1, 3))
    vp = view().viewport(); p = QtCore.QPointF(x, y)
    e = QtGui.QTabletEvent(kind, _pen[0], p, vp.mapToGlobal(p), pressure, 0, 0, 0, 0, 0, QtCore.Qt.NoModifier, button, buttons)
    QtWidgets.QApplication.sendEvent(vp, e)
    return e.isAccepted()


def side_button_and_tip():
    """Seitentaste (BTN_STYLUS = Mitte) gehalten, dann setzt die Spitze auf: Wayland meldet button Links, buttons Links|Mitte"""
    v = view(); x, y = v.width() * .3, v.height() * .85
    L, M, N = QtCore.Qt.LeftButton, QtCore.Qt.MiddleButton, QtCore.Qt.NoButton
    saved["n"] = len(s().Counts)
    saved["side"] = tablet(QtCore.QEvent.TabletPress, x, y, 0, M, M)
    saved["tip"] = tablet(QtCore.QEvent.TabletPress, x, y, .5, L, L | M)
    for k in range(1, 20):
        tablet(QtCore.QEvent.TabletMove, x + 4 * k, y, .5, N, L | M)
    tablet(QtCore.QEvent.TabletRelease, x + 80, y, 0, L, M)
    tablet(QtCore.QEvent.TabletRelease, x + 80, y, 0, M, N)


def hover_with_mouse_button():
    """KDE hat die Seitentaste auf eine Maustaste gelegt: der Klick kommt als echte Maus, der Stift schwebt weiter"""
    vp = view().viewport(); p = QtCore.QPoint(int(vp.width() * .5), int(vp.height() * .85))
    QtTest.QTest.mousePress(vp, QtCore.Qt.MiddleButton, QtCore.Qt.NoModifier, p)
    saved["held"] = QtWidgets.QApplication.mouseButtons() == QtCore.Qt.MiddleButton
    saved["hover"] = tablet(QtCore.QEvent.TabletMove, p.x() + 10, p.y(), 0, QtCore.Qt.NoButton, QtCore.Qt.NoButton)
    QtTest.QTest.mouseRelease(vp, QtCore.Qt.MiddleButton, QtCore.Qt.NoModifier, p)
    saved["free"] = tablet(QtCore.QEvent.TabletMove, p.x() + 20, p.y(), 0, QtCore.Qt.NoButton, QtCore.Qt.NoButton)


def find_field():
    return [w for w in visible(QtWidgets.QLineEdit) if w.placeholderText() in ("Find handwriting", "Handschrift suchen")]


def search(text):
    f = find_field()[0]; f.setFocus(); f.setText(text)
    QtTest.QTest.keyClick(f, QtCore.Qt.Key_Return)


# "Welle 25 mm": Welle = W e l l e (5 Striche), 25 = 2 Striche, mm = 6 Striche
WORDS = [(0, 5), (5, 7), (7, 13)]

in_order([
    ("new", lambda: click(button("Design_Scribble"))), ("wait", lambda: None),
    ("write", lambda: (write("Welle 25 mm", .25, .30), saved.update(raw=strokes()))),
    ("tidied", lambda: (lambda now: check("pause tidies the line: words on one baseline",
                                         spread_of_bottoms(now, WORDS) < 0.4 * spread_of_bottoms(saved["raw"], WORDS),
                                         "%.2f -> %.2f mm" % (spread_of_bottoms(saved["raw"], WORDS), spread_of_bottoms(now, WORDS))))(strokes())),
    ("same count", lambda: check("tidying keeps every stroke and point", s().Counts[:13] == [len(x) for x in saved["raw"]], str(list(s().Counts)))),
    ("undo", lambda: Gui.runCommand("Std_Undo")),
    ("raw again", lambda: check("undo brings back the raw handwriting",
                                all((a - b).Length < 1e-9 for x, y in zip(strokes(), saved["raw"]) for a, b in zip(x, y)))),
    ("redo", lambda: Gui.runCommand("Std_Redo")),
    ("tidy again", lambda: check("redo tidies again", spread_of_bottoms(strokes(), WORDS) < 0.4 * spread_of_bottoms(saved["raw"], WORDS))),

    # Grafiktablett: Seitentaste ist Navigation, auch wenn dabei die Spitze aufsetzt
    ("side button", side_button_and_tip),
    ("no stroke", lambda: check("side button held + tip down: no stroke, left to navigation",
                                len(s().Counts) == saved["n"] and not saved["side"] and not saved["tip"],
                                "strokes +%d, accepted side=%s tip=%s" % (len(s().Counts) - saved["n"], saved["side"], saved["tip"]))),
    ("hover mouse", hover_with_mouse_button),
    ("hover passes", lambda: check("pen hovering while a (remapped) mouse button is held goes on as mouse",
                                   saved["held"] and not saved["hover"] and saved["free"],
                                   "held=%s hover accepted=%s, afterwards=%s" % (saved["held"], saved["hover"], saved["free"]))),

    # Tablet-Tasten (in KDE auf Tasten gelegt): E Radierer an/aus, V Auswählen an/aus, L gerade aufs Blatt
    ("key E", lambda: (activate(), QtTest.QTest.keyClick(view().viewport(), QtCore.Qt.Key_E))),
    ("eraser", lambda: check("E switches to the eraser, no Extrude dialog",
                             button("Design_ScribbleEraser").isChecked() and not Gui.Control.activeDialog())),
    ("key E again", lambda: QtTest.QTest.keyClick(view().viewport(), QtCore.Qt.Key_E)),
    ("pen back", lambda: check("E again goes back to the pen", button("Design_ScribblePen").isChecked())),
    ("key V", lambda: QtTest.QTest.keyClick(view().viewport(), QtCore.Qt.Key_V)),
    ("select", lambda: check("V switches to Select", button("Design_ScribbleSelect").isChecked())),
    ("key V again", lambda: QtTest.QTest.keyClick(view().viewport(), QtCore.Qt.Key_V)),
    ("pen again", lambda: check("V again goes back to the pen", button("Design_ScribblePen").isChecked())),
    ("key L", lambda: QtTest.QTest.keyClick(view().viewport(), QtCore.Qt.Key_L)),

    # M: o12 ohne Schrägstrich geschrieben
    ("write o12", lambda: (saved.update(n=len(s().Counts)), write("Bohrung o12", .25, .50, messy=.4))),
    ("slashed", lambda: check("o12 gets a slash in the ink (Ø12)", len(s().Counts) == saved["n"] + count("Bohrung o12") + 1,
                              "%d strokes written, %d now" % (count("Bohrung o12"), len(s().Counts) - saved["n"]))),

    # S: Suchen in der Palette
    ("field", lambda: check("palette shows Find handwriting", len(find_field()) == 1)),
    ("not found", lambda: search("Zahnrad")),
    ("still pen", lambda: check("nothing found: the pen stays", button("Design_ScribblePen").isChecked())),
    ("find", lambda: search("25mm")),
    ("found", lambda: check("found: the line is selected (Select tool)", button("Design_ScribbleSelect").isChecked())),
    # wie eine echte Taste: an die 3D-Ansicht, die sie über die Szene ans Feld weitergibt
    ("backspace", lambda: (saved.update(n=len(s().Counts)), activate(), find_field()[0].setFocus(),
                           QtTest.QTest.keyClick(view(), QtCore.Qt.Key_Backspace))),
    ("kept", lambda: check("backspace in the find field deletes text, not strokes", len(s().Counts) == saved["n"] and find_field()[0].text() == "25m",
                           "%d strokes, field %r" % (len(s().Counts), find_field()[0].text()))),

    # T: Ø12 neben einem Kreis wird beim Umwandeln dessen Durchmesser. Die Suche hat die Ansicht verschoben: erst wieder
    # gerade aufs Blatt, sonst landen Kreis und Maß in der Zeile von "Bohrung Ø12"
    ("look", lambda: Gui.runCommand("Design_ScribbleLookAt")),
    ("circle",lambda: (Gui.runCommand("Design_ScribbleCircle"), activate(),
                        draw([(view().width() * .65, view().height() * .70), (view().width() * .70, view().height() * .70)]))),
    ("pen", lambda: Gui.runCommand("Design_ScribblePen")),
    ("label", lambda: write("o12", .73, .70, messy=.3)),
    ("written", lambda: shot("written")),
    ("convert", lambda: Gui.runCommand("Design_ScribbleToSketch")), ("wait", lambda: None), ("wait", lambda: None),
    ("dimension", lambda: (lambda sk: check("Ø12 next to the circle becomes its diameter",
                                           any(c.Type == "Diameter" and abs(c.Value - 12) < 1e-6 for c in sk.Constraints),
                                           str([(c.Type, round(c.Value, 3)) for c in sk.Constraints if c.Type in ("Diameter", "Radius", "Distance")])))(
        [o for o in doc().Objects if o.TypeId == "Sketcher::SketchObject"][-1])),
    ("shot", lambda: shot("handwriting")),
])
