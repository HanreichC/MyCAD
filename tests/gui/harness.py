# SPDX-License-Identifier: LGPL-2.1-or-later
"""Hilfen für GUI-Tests: echte Mausklicks auf Glass-Panels, Schritte mit Pause, Protokoll nach $OUT.txt."""
import os
import FreeCAD as App, FreeCADGui as Gui, Part
from PySide6 import QtCore, QtGui, QtWidgets, QtTest

# Immer gespeichert (Idee 7) stört den festen Takt der Tests: aus, test_versions_ui schaltet es gezielt ein
App.ParamGet("User parameter:BaseApp/Preferences/MyCAD").SetBool("AlwaysSave", False)
mw = Gui.getMainWindow()
mw.resize(1500, 950)
_log = open(os.environ["OUT"] + ".txt", "w")
_keep = []  # Python-Wrapper am Leben halten, sonst löscht PySide die C++-Objekte


def L(text):
    _log.write(text + "\n"); _log.flush()


def doc():
    return App.ActiveDocument


def view():
    v = [v for v in mw.findChildren(QtWidgets.QGraphicsView) if v.isVisible()][0]
    _keep.append(v); return v


def _pos(w):
    top = w
    while top.parentWidget():
        top = top.parentWidget()
    proxy = top.graphicsProxyWidget(); _keep.extend([w, top, proxy])
    return view().mapFromScene(proxy.mapToScene(QtCore.QPointF(w.mapTo(top, w.rect().center()))))


def click(w):
    p = _pos(w)
    record_click(view().viewport().mapToGlobal(p.toPoint() if hasattr(p, "toPoint") else p))
    QtTest.QTest.mouseClick(view().viewport(), QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)


# --- Aufnahme als GIF (Erklär-Clips der Hilfe, tools/help_images.py) ------------------------------------------------
_rec = {}


def record_start(path, width=880, fps=8, left=306):
    """Fenster laufend aufnehmen, bis record_stop(); Klicks (click, record_click) bekommen einen Kreis, weil das Bild
    den Mauszeiger nicht enthält. left: so viel links weglassen (die Seitenleiste gehört nicht zur Erklärung);
    880 breit = Inhaltsbreite auf GitHub, die Hilfe zeigt den Clip kleiner"""
    import time
    timer = QtCore.QTimer()
    _rec.clear()
    _rec.update(path=path, width=width, ms=1000 // fps, frames=[], clicks=[], timer=timer, clock=time.monotonic, busy=0.0, left=left)
    timer.setInterval(_rec["ms"])
    timer.timeout.connect(_record_frame)
    timer.start()
    _keep.append(timer)
    _record_frame()


def record_click(global_point):
    if _rec:
        p = mw.mapFromGlobal(global_point)
        _rec["clicks"].append((p.x(), p.y(), _rec["clock"]()))


def _record_frame():
    if QtCore.QThread.currentThread().loopLevel() > 1:
        return  # nie in einer verschachtelten Ereignisschleife: das Bild griffe mitten in einen Umbau der Szene (Absturz)
    now = _rec["clock"]()
    img = mw.grab().toImage().convertToFormat(QtGui.QImage.Format_RGB888)
    painter = QtGui.QPainter(img)
    painter.setRenderHint(QtGui.QPainter.Antialiasing)
    for x, y, t0 in _rec["clicks"]:
        age = now - t0
        if 0 <= age < 0.7:  # Klick: Kreis wächst und blendet aus
            c = QtGui.QColor(0, 136, 255)
            c.setAlphaF(0.85 * (1 - age / 0.7))
            painter.setPen(QtGui.QPen(c, 4))
            painter.setBrush(QtCore.Qt.NoBrush)
            r = 10 + 26 * age / 0.7
            painter.drawEllipse(QtCore.QPointF(x, y), r, r)
    painter.end()
    img = img.copy(_rec["left"], 0, img.width() - _rec["left"], img.height())
    _rec["frames"].append((img.scaledToWidth(_rec["width"], QtCore.Qt.SmoothTransformation), now))
    _rec["busy"] += _rec["clock"]() - now


def record_stop(hold=1.5, longest=1.2):
    """Aufnahme beenden und als GIF speichern. Gleiche Bilder hintereinander werden eins; was länger still steht (Warten
    auf den nächsten Schritt), zeigt der Clip höchstens longest Sekunden. Das letzte Bild steht hold Sekunden, dann
    beginnt der Clip von vorn. Eine Palette für alle Bilder: Unverändertes bleibt gleich, die GIF speichert nur Änderungen."""
    from PIL import Image
    _rec["timer"].stop()
    _record_frame()
    frames, times = [], []
    last = None
    for q, t in _rec["frames"]:
        raw = bytes(q.constBits())
        if raw == last:
            continue
        last = raw
        frames.append(Image.frombuffer("RGB", (q.width(), q.height()), raw, "raw", "RGB", q.bytesPerLine(), 1))
        times.append(t)
    times.append(_rec["frames"][-1][1])
    durations = [max(_rec["ms"], min(int((b - a) * 1000), int(longest * 1000))) for a, b in zip(times, times[1:])]
    durations[-1] += int(hold * 1000)
    w, h = frames[0].size
    # Palette aus bis zu 16 Bildern über den ganzen Clip: auch kurze Farben (blaue Auswahl, oranges Profil, rote
    # Schraffur) bekommen eigene Einträge, sonst werden sie grau
    picks = [frames[i * (len(frames) - 1) // 15] for i in range(16)] if len(frames) > 16 else frames
    sample = Image.new("RGB", (w // 2, h // 2 * len(picks)))
    for i, f in enumerate(picks):
        sample.paste(f.resize((w // 2, h // 2)), (0, h // 2 * i))
    palette = sample.quantize(255, method=Image.Quantize.MEDIANCUT)
    frames = [f.quantize(palette=palette, dither=Image.Dither.NONE) for f in frames]
    frames[0].save(_rec["path"], save_all=True, append_images=frames[1:], duration=durations, loop=0, optimize=False)
    L("GIF %s: %d Bilder, %.1f s, %d KB" % (os.path.basename(_rec["path"]), len(frames), sum(durations) / 1000,
                                           os.path.getsize(_rec["path"]) // 1024))
    _rec.clear()


def dclick(w):
    vp, p = view().viewport(), _pos(w)
    QtTest.QTest.mousePress(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)
    QtTest.QTest.mouseRelease(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)
    QtTest.QTest.mouseDClick(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)
    QtTest.QTest.mouseRelease(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)


def visible(cls):
    r = [w for w in QtWidgets.QApplication.allWidgets() if isinstance(w, cls) and w.isVisible()]
    _keep.extend(r); return r


def button(cmd):
    """Glass-Toolbar-Button eines Befehls"""
    for b in visible(QtWidgets.QToolButton):
        if b.objectName() in ("GlassButton", "GlassProminent") and cmd in (b.property("command"), str(b.property("command")).split("|")[0]):
            return b
    raise RuntimeError("no glass button for " + cmd)


def timeline():
    return [b for b in visible(QtWidgets.QToolButton) if b.objectName() == "GlassButton" and not b.property("command")]


def ok():
    click([b for b in visible(QtWidgets.QPushButton) if b.text().replace("&", "") == "OK"][0])


def view_click(fx, fy):
    v = view(); p = QtCore.QPoint(int(v.width() * fx), int(v.height() * fy))
    QtTest.QTest.mouseMove(v.viewport(), p)
    QtTest.QTest.mouseClick(v.viewport(), QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)


def esc():
    QtTest.QTest.keyClick(view().viewport(), QtCore.Qt.Key_Escape)


def type_into(n, text, cls=QtWidgets.QAbstractSpinBox):
    """n-tes sichtbares Eingabefeld (von oben) überschreiben"""
    box = sorted(visible(cls), key=lambda w: w.mapToGlobal(QtCore.QPoint(0, 0)).y())[n]
    box.lineEdit().selectAll(); QtTest.QTest.keyClicks(box.lineEdit(), text)


def field(label):
    """Eingabefeld rechts neben der Beschriftung label (Feature-Dialog). Über die Lage statt über das QFormLayout:
    PySide verwechselt sonst das Layout eines neuen Dialogs mit dem eines schon gelöschten."""
    kinds = (QtWidgets.QAbstractSpinBox, QtWidgets.QComboBox, QtWidgets.QPushButton, QtWidgets.QLineEdit)
    for lab in visible(QtWidgets.QLabel):
        if lab.text() != label:
            continue
        top = lab.mapToGlobal(QtCore.QPoint(0, 0)); mid = top.y() + lab.height() // 2
        cands = [w for cls in kinds for w in visible(cls) if w.parentWidget() is lab.parentWidget()
                 and w.mapToGlobal(QtCore.QPoint(0, 0)).x() > top.x()
                 and abs(w.mapToGlobal(QtCore.QPoint(0, w.height() // 2)).y() - mid) < max(lab.height(), 12)]
        if cands:
            w = min(cands, key=lambda w: w.mapToGlobal(QtCore.QPoint(0, 0)).x())
            _keep.append(w); return w
    raise RuntimeError("no field " + label)


def shown(label):
    """Ist ein Feld mit dieser Beschriftung sichtbar?"""
    try:
        return field(label).isVisible()
    except RuntimeError:
        return False


def type_field(label, text):
    box = field(label)
    edit = box.lineEdit() if hasattr(box, "lineEdit") else box
    edit.selectAll(); QtTest.QTest.keyClicks(edit, text)  # kein Enter: das bestätigt den ganzen Dialog


def choose(item_text, index):
    cb = [c for c in visible(QtWidgets.QComboBox) if c.findText(item_text) >= 0][0]
    cb.setCurrentIndex(index)


def checkbox(text):
    return [b for b in visible(QtWidgets.QCheckBox) if b.text() == text][0]


def body(label):
    return [o for o in doc().Objects if o.TypeId == "Design::Body" and o.Label == label][0]


def volumes():
    return [(b.Label, round(b.Shape.Volume, 1), b.Visibility) for b in doc().Objects if b.TypeId == "Design::Body"]


def errors():
    return [(o.Name, o.getStatusString()) for o in doc().Objects if hasattr(o, "isError") and o.isError()]


def make_body(geos, z, h, name):
    """Body per Skript (Skizze + Profil + Extrude) für schnelle Testaufbauten"""
    d = doc(); root = [o for o in d.Objects if o.TypeId == "App::Part"][0]
    sk = d.addObject("Sketcher::SketchObject", "Sketch"); sk.Placement.Base.z = z
    for g in geos:
        sk.addGeometry(g)
    d.getObject("Sketches").addObject(sk)
    prof = d.addObject("Design::Profiles", "Profiles"); prof.Sketch = sk; root.addObject(prof)
    ext = d.addObject("Design::Extrude", "Extrude"); ext.Profile = (prof, []); ext.Distance = h; root.addObject(ext)
    b = d.addObject("Design::Body", "Body"); b.Label = name; ext.Bodies = [b]; b.Tip = ext
    d.getObject("Bodies").addObject(b)
    sk.Visibility = False; prof.Visibility = False
    d.recompute(); return b


def rect(x0, y0, x1, y1):
    p = [App.Vector(x0, y0, 0), App.Vector(x1, y0, 0), App.Vector(x1, y1, 0), App.Vector(x0, y1, 0)]
    return [Part.LineSegment(p[i], p[(i + 1) % 4]) for i in range(4)]


def top_face(b):
    return "Face%d" % (1 + max(range(len(b.Shape.Faces)), key=lambda k: b.Shape.Faces[k].CenterOfMass.z))


START_PAGE = False  # True: Test beginnt auf der Startseite (ohne Design)


def _when_idle(fn, quiet=0.25, limit=10.0):
    """fn aufrufen, sobald MyCAD mit allem fertig ist: 0,25 s lang kommt jeder 25-ms-Timer pünktlich dran.
    Unter Last (CI: 8 GUI-Tests parallel mit Software-OpenGL) dauert das von selbst länger; nach 10 s geht es
    trotzdem weiter, damit eine Daueranimation den Test nicht aufhält."""
    import time
    start = calm = last = time.monotonic()

    recorded = [_rec.get("busy", 0.0)]

    def tick():
        nonlocal calm, last
        now = time.monotonic()
        own = _rec.get("busy", 0.0) - recorded[0]  # eine laufende GIF-Aufnahme (record_start) ist keine Arbeit von MyCAD
        recorded[0] = _rec.get("busy", 0.0)
        if now - last - own > 0.045:  # Timer kam zu spät dran: es lief noch Arbeit (Neuberechnung, Zeichnen, Animation)
            calm = now
        last = now
        if now - calm >= quiet or now - start >= limit:
            if now - calm < quiet:  # Hinweis, kein Fehler: zeichnet MyCAD ständig neu, kostet das Akku
                L("  busy: MyCAD kam %.0f s lang nicht zur Ruhe" % limit)
            fn()
        else:
            QtCore.QTimer.singleShot(25, tick)
    QtCore.QTimer.singleShot(25, tick)


_field_fails = set()


def _check_fields():
    """MyStyle-Textfelder überall (9.3), in jedem Zustand jedes GUI-Tests: kein sichtbares Feld in Qts Standard-Optik.
    Auf 50 % Grau gerendert bleibt ein MyStyle-Feld grau (fill.tertiary ist durchscheinend), Qts Feld ist deckend
    (weiß bzw. Verlauf); ein Zahlenfeld hat keine Pfeil-Knöpfe. Jedes Feld wird nur einmal gemeldet."""
    for w in QtWidgets.QApplication.allWidgets():
        if not isinstance(w, (QtWidgets.QLineEdit, QtWidgets.QAbstractSpinBox, QtWidgets.QComboBox)) \
                or not w.isVisible() or w.width() < 12 or w.height() < 12:
            continue
        if isinstance(w, QtWidgets.QLineEdit) and isinstance(w.parentWidget(), (QtWidgets.QAbstractSpinBox, QtWidgets.QComboBox)):
            continue  # das Eingabefeld im Zahlen-/Auswahlfeld zeichnet Qt ohne eigenen Rahmen
        img = QtGui.QImage(w.size(), QtGui.QImage.Format_ARGB32)
        img.fill(QtGui.QColor(128, 128, 128))
        w.render(img, QtCore.QPoint(), QtGui.QRegion(), QtWidgets.QWidget.RenderFlag.DrawChildren)
        why = []
        for c in (img.pixelColor(w.width() // 2, 2), img.pixelColor(w.width() // 2, w.height() - 3)):  # Rand: kein Text
            if max(abs(c.red() - 128), abs(c.green() - 128), abs(c.blue() - 128)) > 24:
                why.append("opaque %s" % c.name())
                break
        if isinstance(w, QtWidgets.QAbstractSpinBox):
            opt = QtWidgets.QStyleOptionSpinBox()
            opt.initFrom(w)
            opt.subControls = QtWidgets.QStyle.SubControl.SC_SpinBoxUp | QtWidgets.QStyle.SubControl.SC_SpinBoxDown
            opt.buttonSymbols = w.buttonSymbols()
            up = w.style().subControlRect(QtWidgets.QStyle.ComplexControl.CC_SpinBox, opt, QtWidgets.QStyle.SubControl.SC_SpinBoxUp, w)
            if up.width() > 0 and w.buttonSymbols() != QtWidgets.QAbstractSpinBox.ButtonSymbols.NoButtons:
                why.append("arrow buttons")
            edit = w.lineEdit()
            if w.width() > 30 and edit is not None and edit.width() < 10:  # Text hat keinen Platz (Stylesheet ohne subcontrol-origin)
                why.append("edit field %d px wide" % edit.width())
        key = (type(w).__name__, w.objectName(), w.accessibleName(), w.window().windowTitle())
        if why and key not in _field_fails:
            _field_fails.add(key)
            L("FAIL field not MyStyle: %s name=%r label=%r window=%r (%s)" % (key + (", ".join(why),)))


def _sequence(steps, delay, arm_first):
    """Schritte nacheinander; jeder wartet delay und dann, bis MyCAD mit dem vorigen fertig ist. Kein fester Takt
    mehr: auf einer langsamen CI kam ein Schritt sonst dran, bevor der Dialog des vorigen offen war."""
    def next_step():
        _check_fields()
        if not steps:
            L("step done"); App.saveParameter(); os._exit(0)  # "step done": run_all.sh erkennt das saubere Ende
        name, fn = steps.pop(0)
        L("step " + name)
        arm = lambda: QtCore.QTimer.singleShot(delay, lambda: _when_idle(next_step))
        if arm_first:  # run(): schon vorher, damit ein Schritt mit modalem Dialog den nächsten nicht blockiert
            arm()
        try:
            fn()
        except Exception as e:
            L("  exc %s: %s" % (type(e).__name__, e))
        if not arm_first:
            arm()
    QtCore.QTimer.singleShot(5000, lambda: _when_idle(next_step))


def run(steps, delay=1300):
    """Schritte nacheinander ausführen, Fehler protokollieren, am Ende Screenshot + Beenden"""
    start = [] if START_PAGE else [("design", lambda: App.ActiveDocument or Gui.runCommand("Std_New"))]
    _sequence(start + list(steps) + [("shot", lambda: mw.grab().save(os.environ["OUT"] + ".png"))], delay, True)


def shot(name):
    """Zwischen-Screenshot <OUT>.<name>.png und Fensterzustand ins Protokoll"""
    mw.grab().save(os.environ["OUT"] + "." + name + ".png")
    subs = mw.findChildren(QtWidgets.QMdiSubWindow)
    L("  window visible=%s minimized=%s views=%d %s" % (mw.isVisible(), mw.isMinimized(), len(subs),
                                                    [(s.isVisible(), s.isMaximized()) for s in subs]))


def check(name, ok, detail=""):
    """Prüfung fürs Protokoll; Fehler stehen als FAIL darin"""
    L("%s %s %s" % ("ok  " if ok else "FAIL", name, detail))


def activate():
    """Das Testfenster ist auf dem Desktop oft nicht aktiv; dann vergibt Qt keinen Tastaturfokus"""
    QtWidgets.QApplication.setActiveWindow(mw)
    QtWidgets.QApplication.sendEvent(view().scene(), QtCore.QEvent(QtCore.QEvent.WindowActivate))
    view().viewport().setFocus()


def in_order(steps, delay=1200):
    """Wie run(), aber der nächste Schritt wird erst nach dem Ende des vorigen gestellt (Tippen, lange Schritte)"""
    start = [] if START_PAGE else [("design", lambda: App.ActiveDocument or Gui.runCommand("Std_New"))]
    _sequence(start + list(steps) + [("shot", lambda: mw.grab().save(os.environ["OUT"] + ".png"))], delay, False)
