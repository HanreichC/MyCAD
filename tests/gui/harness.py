# SPDX-License-Identifier: LGPL-2.1-or-later
"""Hilfen für GUI-Tests: echte Mausklicks auf Glass-Panels, Schritte mit Pause, Protokoll nach $OUT.txt."""
import os
import FreeCAD as App, FreeCADGui as Gui, Part
from PySide6 import QtCore, QtWidgets, QtTest

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
    QtTest.QTest.mouseClick(view().viewport(), QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, _pos(w))


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

    def tick():
        nonlocal calm, last
        now = time.monotonic()
        if now - last > 0.045:  # Timer kam zu spät dran: es lief noch Arbeit (Neuberechnung, Zeichnen, Animation)
            calm = now
        last = now
        if now - calm >= quiet or now - start >= limit:
            if now - calm < quiet:  # Hinweis, kein Fehler: zeichnet MyCAD ständig neu, kostet das Akku
                L("  busy: MyCAD kam %.0f s lang nicht zur Ruhe" % limit)
            fn()
        else:
            QtCore.QTimer.singleShot(25, tick)
    QtCore.QTimer.singleShot(25, tick)


def _sequence(steps, delay, arm_first):
    """Schritte nacheinander; jeder wartet delay und dann, bis MyCAD mit dem vorigen fertig ist. Kein fester Takt
    mehr: auf einer langsamen CI kam ein Schritt sonst dran, bevor der Dialog des vorigen offen war."""
    def next_step():
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
