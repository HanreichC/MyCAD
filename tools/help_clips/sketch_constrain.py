# SPDX-License-Identifier: LGPL-2.1-or-later
"""Erklär-Clips Skizze: Abhängigkeiten und Bemaßen mit echten Klicks in der offenen Skizze (von oben), dazu Skizze
erstellen und die Skizzen-Grundlagen. Elemente werden in der Ansicht angeklickt (Kreis im Clip), die Abhängigkeit kommt
über ihren Knopf oder ihre Taste (die Taste erscheint als Tastenkappe im Clip). Läuft in tools/help_images.py
(exec in dessen Globals); alle Namen hier beginnen mit sc_, weil alle Clip-Dateien dieselben Globals teilen."""

sc_mouse = {}
sc_cap = {}
sc_err = {}
sc_pause = {}  # done: Aufnahme ruht, bis done() wahr ist (Umbau der Oberfläche beim Betreten/Verlassen der Skizze)


def sc_safe(fn):
    """Zeitgeber-Rückrufe: Fehler ins Protokoll statt still verschluckt"""
    def go():
        try:
            fn()
        except Exception as e:
            L("  exc %s: %s" % (type(e).__name__, e))
    return go


def sc_view():
    """die 3D-Ansicht: größte sichtbare QGraphicsView (harness.view() nimmt die erste, in der Skizze ist das manchmal
    ein kleines 400x300-Fenster)"""
    return max(visible(QtWidgets.QGraphicsView), key=lambda v: v.width() * v.height())


def sc_activate():
    """wie harness.activate, aber Fokus in die 3D-Ansicht (sonst landet die Taste im kleinen Fenster und verlässt die
    Skizze)"""
    QtWidgets.QApplication.setActiveWindow(mw)
    QtWidgets.QApplication.sendEvent(sc_view().scene(), QtCore.QEvent(QtCore.QEvent.WindowActivate))
    sc_view().viewport().setFocus()


def sc_sk():
    return Gui.ActiveDocument.getInEdit().Object


def sc_pt(x, y, z=0):
    """Skizzen-/Modellpunkt -> Viewport-Pixel (Coin zählt y von unten)"""
    v = sc_view(); px, py = Gui.ActiveDocument.ActiveView.getPointOnViewport(V(x, y, z))
    dpr = v.viewport().devicePixelRatioF()
    return QtCore.QPoint(int(px / dpr), int(v.viewport().height() - py / dpr))


def sc_hover(p, buttons=QtCore.Qt.NoButton):
    vp = sc_view().viewport()
    QtWidgets.QApplication.sendEvent(vp, QtGui.QMouseEvent(QtCore.QEvent.MouseMove, QtCore.QPointF(p), QtCore.QPointF(vp.mapToGlobal(p)),
                                                           QtCore.Qt.NoButton, buttons, QtCore.Qt.NoModifier))


def sc_glide(target, then=None, ms=400, n=8, buttons=QtCore.Qt.NoButton):
    """Maus in n Schritten zum Ziel (Vorschau und Vorauswahl laufen sichtbar mit), danach then()"""
    start = sc_mouse.get("p") or target + QtCore.QPoint(40, 30)
    for i in range(1, n + 1):
        q = start + (target - start) * (i / n)
        QtCore.QTimer.singleShot(int(ms * i / n), sc_safe(lambda q=q: sc_hover(q, buttons)))
    sc_mouse["p"] = target
    if then:
        QtCore.QTimer.singleShot(ms + 80, sc_safe(then))


def sc_click_at(p):
    sc_hover(p)
    record_click(sc_view().viewport().mapToGlobal(p))
    QtTest.QTest.mouseClick(sc_view().viewport(), QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)


def sc_where(w):
    """Ort im Clip: (x, y) oder eine Funktion, die ihn erst beim Klick ausrechnet (Geometrie bewegt sich ja)"""
    return sc_pt(*(w() if callable(w) else w))


def sc_tap(w, name="click"):
    """Schritt: Maus hingleiten, klicken (Kreis im Clip). In der Skizze kommt jeder angeklickte Teil zur Auswahl dazu."""
    step(name, lambda: sc_glide(sc_where(w), lambda: sc_click_at(sc_where(w))))


def sc_taps(*ws, esc=False):
    """Ein Schritt, mehrere Klicks nacheinander (Zeichnen): zwischen den Schritten wartet der Ablauf auf Ruhe, und die
    blinkenden Eingabefelder am Cursor lassen MyCAD nie zur Ruhe kommen (jeder Schritt dauerte dann 10 s)"""
    def go():
        rest = list(ws)

        def nxt():
            if not rest and esc:  # Werkzeug gleich weglegen: sonst blinken seine Felder bis zum nächsten Schritt
                sc_press("Esc", "Escape")
            if rest:
                w = rest.pop(0)
                sc_glide(sc_where(w), lambda: (sc_click_at(sc_where(w)), QtCore.QTimer.singleShot(600, sc_safe(nxt))))
        nxt()
    step("taps", go)


def sc_move(w):
    step("move", lambda: sc_glide(sc_where(w)))


def sc_on(i, t=0.5):
    """Punkt auf Skizzenelement i (t: Anteil des Parameterbereichs, 0,5 = Mitte)"""
    def f():
        g = sc_sk().Geometry[i]
        p = g.value(g.FirstParameter + t * (g.LastParameter - g.FirstParameter))
        return p.x, p.y
    return f


def sc_end(i, which):
    """Endpunkt (1 Anfang, 2 Ende) oder Mittelpunkt (3) von Skizzenelement i"""
    def f():
        g = sc_sk().Geometry[i]
        p = {1: lambda: g.StartPoint, 2: lambda: g.EndPoint, 3: lambda: g.Center}[which]()
        return p.x, p.y
    return f


def sc_drag(a, b):
    """Schritte: hingleiten, mit gedrückter Taste nach b ziehen (ohne Kreis: es ist kein Klick)"""
    sc_move(a)

    def go():
        vp = sc_view().viewport(); p, q = sc_where(a), sc_where(b)
        QtTest.QTest.mousePress(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)
        sc_mouse["p"] = p
        sc_glide(q, lambda: QtTest.QTest.mouseRelease(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, q), ms=900, n=12,
                 buttons=QtCore.Qt.LeftButton)
    step("drag", go)
    wait()


def sc_ring(w):
    """Kreis auf einem Glas-Knopf (wie harness._pos, aber über sc_view)"""
    top = w
    while top.parentWidget():
        top = top.parentWidget()
    proxy = top.graphicsProxyWidget()
    if proxy:
        g = sc_view().viewport().mapToGlobal(sc_view().mapFromScene(proxy.mapToScene(QtCore.QPointF(w.mapTo(top, w.rect().center())))))
    else:  # eigenes Fenster (z. B. die Skizzenpalette)
        g = w.mapToGlobal(w.rect().center())
    record_click(g)


def sc_tool(cmd, ring=None):
    """Schritt: Werkzeug über seinen Knopf (Kreis auf dem Knopf; bei Gruppen der Gruppenknopf ring)"""
    def go():
        try:
            sc_ring(button(ring or cmd))
        except RuntimeError:
            L("  no button " + (ring or cmd))
        Gui.runCommand(cmd)
    step(cmd, go)
    wait()


def sc_frame():
    """Ein Bild der Aufnahme wie harness._record_frame, dazu: eigene Fenster (Maßeingabe, Meldungen) ins Bild gemalt,
    auch während deren modaler Schleife (harness lässt verschachtelte Schleifen aus, wegen des Skizzen-Umbaus); die
    zuletzt gedrückte Taste als Kappe; keine Bilder, solange sc_pause gilt, und keine einfarbigen Zwischenbilder"""
    rec = harness._rec
    try:
        modal = isinstance(QtWidgets.QApplication.activeModalWidget(), QtWidgets.QDialog)
        if QtCore.QThread.currentThread().loopLevel() > 1 and not modal:
            return
        if sc_pause:
            if "at" not in sc_pause and sc_pause["done"]():
                sc_pause["at"] = rec["clock"]() + 0.4
            if "at" not in sc_pause or rec["clock"]() < sc_pause["at"]:
                return
            sc_pause.clear()
        now = rec["clock"]()
        img = mw.grab().toImage().convertToFormat(QtGui.QImage.Format_RGB888)
        p = QtGui.QPainter(img)
        p.setRenderHint(QtGui.QPainter.Antialiasing)
        p.setRenderHint(QtGui.QPainter.SmoothPixmapTransform)
        for w in QtWidgets.QApplication.topLevelWidgets():
            # nur kleine Fenster: ein fensterfüllendes durchscheinendes Abdunkeln ergäbe per grab() nur Rauschen
            if w is not mw and w.isVisible() and isinstance(w, (QtWidgets.QDialog, QtWidgets.QMenu)) \
                    and w.width() * w.height() < mw.width() * mw.height() / 4:
                p.drawPixmap(mw.mapFromGlobal(w.mapToGlobal(QtCore.QPoint(0, 0))), w.grab())
        for x, y, t0 in rec["clicks"]:
            age = now - t0
            if 0 <= age < 0.7:
                c = QtGui.QColor(0, 136, 255)
                c.setAlphaF(0.85 * (1 - age / 0.7))
                p.setPen(QtGui.QPen(c, 4))
                p.setBrush(QtCore.Qt.NoBrush)
                r = 10 + 26 * age / 0.7
                p.drawEllipse(QtCore.QPointF(x, y), r, r)
        p.end()
        img = img.copy(rec["left"], 0, img.width() - rec["left"], img.height()).scaledToWidth(rec["width"], QtCore.Qt.SmoothTransformation)
        probe = {img.pixel(x, y) for x in (40, img.width() // 2, img.width() - 40) for y in (120, img.height() // 2, img.height() - 120)}
        if len(probe) > 1:  # einfarbig (grau): Zwischenbild beim Umschalten der Ansicht
            if "t" in sc_cap and now - sc_cap["t"] < 1.4:
                sc_keycap(img)
            rec["frames"].append((img, now))
        rec["busy"] += rec["clock"]() - now
    except Exception as e:
        if not sc_err:
            L("  exc sc_frame %s: %s" % (type(e).__name__, e))
        sc_err["once"] = True


def sc_keycap(img):
    p = QtGui.QPainter(img)
    p.setRenderHint(QtGui.QPainter.Antialiasing)
    f = p.font(); f.setPixelSize(30); f.setBold(True); p.setFont(f)
    w = max(64, p.fontMetrics().horizontalAdvance(sc_cap["text"]) + 36)
    r = QtCore.QRectF((img.width() - w) / 2, sc_cap.get("y", img.height() - 170), w, 64)
    p.setPen(QtGui.QPen(QtGui.QColor(0, 136, 255), 3))
    p.setBrush(QtGui.QColor(255, 255, 255, 235))
    p.drawRoundedRect(r, 12, 12)
    p.setPen(QtGui.QColor(29, 29, 31))
    p.drawText(r, QtCore.Qt.AlignCenter, sc_cap["text"])
    p.end()


def sc_press(label, *keys, y=None):
    """Tasten wie von Hand (Fenster aktiv, Fokus in der Ansicht); im Clip erscheint label als Tastenkappe (y: Höhe im
    Clip statt unten, wenn dort etwas Wichtiges steht)"""
    if harness._rec:
        sc_cap.clear()
        sc_cap.update(text=label, t=harness._rec["clock"]())
        if y is not None:
            sc_cap["y"] = y
    sc_activate()
    for k in keys:
        QtTest.QTest.keyClick(mw.windowHandle(), getattr(QtCore.Qt, "Key_" + k))


def sc_key(label, *keys, y=None):
    step("key " + label, lambda: sc_press(label, *keys, y=y))
    wait()


def sc_type(text):
    """Schritt: Wert ins Eingabefeld mit dem Fokus tippen (Maßeingabe), nächster Schritt: Enter"""
    def go():
        box = QtWidgets.QApplication.focusWidget()
        edit = box.lineEdit() if hasattr(box, "lineEdit") and box.lineEdit() else box
        edit.selectAll()
        QtTest.QTest.keyClicks(edit, text)
    step("type " + text, go)
    wait()
    step("enter", lambda: QtTest.QTest.keyClick(QtWidgets.QApplication.focusWidget(), QtCore.Qt.Key_Return))
    wait()


def sc_camera(cx=0, cy=0, h=110):
    import pivy.coin  # getCameraNode braucht pivy
    c = Gui.ActiveDocument.ActiveView.getCameraNode()
    c.position.setValue(cx, cy, c.position.getValue()[2]); c.height.setValue(h)


def sc_restart():
    """Aufnahme neu beginnen (der Clip startet in der offenen Skizze) und die Tastenkappe einhängen"""
    sc_mouse.clear(); sc_cap.clear()
    QtWidgets.QApplication.setCursorFlashTime(0)  # blinkende Schreibmarke: jedes Bild anders, der Clip würde lang
    if GIF and harness._rec:
        path = harness._rec["path"]
        harness._rec["timer"].stop()
        record_start(path)
        t = harness._rec["timer"]
        t.timeout.disconnect()
        t.timeout.connect(sc_frame)


def sc_xy():
    return [o for o in doc().Objects if o.Name.startswith("XY_Plane")][0]


def sc_open(geos=(), cons=(), cx=0, cy=0, h=110):
    """Skizze auf XY mit lose gezeichneter Geometrie öffnen; der Clip beginnt danach"""
    step("create sketch", lambda: Gui.runCommand("Design_CreateSketch"))
    wait()
    step("XY", lambda: Gui.Selection.addSelection(sc_xy()))
    wait(2)

    def setup():
        s = sc_sk()
        for g in geos:
            s.addGeometry(g, False)
        for c in cons:
            s.addConstraint(c)
        doc().recompute()
        Gui.Selection.clearSelection()
        sc_camera(cx, cy, h)
        st["sk"] = s
    step("setup", setup)
    wait()
    step("restart", sc_restart)
    wait()


def sc_log(tag):
    """Prüfung fürs Protokoll: welche Abhängigkeiten die Skizze am Ende hat"""
    step("log", lambda: L("  %s: cons=%s" % (tag, [c.Type for c in sc_sk().Constraints])))


def sc_clip(article, build):
    scenario(article, build, view="none", fixed=True)


def sc_closed(pts):
    lines = [Part.LineSegment(pts[i], pts[(i + 1) % len(pts)]) for i in range(len(pts))]
    return lines, [C("Coincident", i, 2, (i + 1) % len(pts), 1) for i in range(len(pts))]


# --- Abhängigkeiten -------------------------------------------------------------------------------------------------
def sc_rect(x0, y0, x1, y1):
    """Rechteck wie vom Rechteck-Werkzeug: Ecken verbunden, waagrecht/senkrecht, ohne Maße"""
    lines, cons = sc_closed([V(x0, y0, 0), V(x1, y0, 0), V(x1, y1, 0), V(x0, y1, 0)])
    return lines, cons + [C("Horizontal", 0), C("Horizontal", 2), C("Vertical", 1), C("Vertical", 3)]


def sc_coincident():
    """Umriss mit Lücke an der Ecke oben rechts: beide Enden anklicken, Koinzident schließt sie"""
    pts = [V(-30, -20, 0), V(30, -20, 0), V(30, 12, 0), V(22, 20, 0), V(-30, 20, 0)]
    lines = [Part.LineSegment(pts[0], pts[1]), Part.LineSegment(pts[1], pts[2]), Part.LineSegment(pts[3], pts[4]),
             Part.LineSegment(pts[4], pts[0])]
    cons = [C("Coincident", 0, 2, 1, 1), C("Coincident", 2, 2, 3, 1), C("Coincident", 3, 2, 0, 1),
            C("Horizontal", 0), C("Horizontal", 2), C("Vertical", 1), C("Vertical", 3)]  # sonst kippt die obere Kante
    sc_open(lines, cons, -3, 0, 85)
    sc_tap(sc_end(1, 2)); sc_tap(sc_end(2, 1))
    sc_tool("Sketcher_ConstrainCoincidentUnified")
    sc_log("coincident")
    wait()


def sc_horver():
    """schief gezeichnetes Viereck: untere Kante + Horizontal (Knopf), linke Kante + Taste V"""
    lines, cons = sc_closed([V(-28, -16, 0), V(30, -23, 0), V(25, 20, 0), V(-22, 16, 0)])
    sc_open(lines, cons, -3, 0, 85)
    sc_tap(sc_on(0)); sc_tool("Sketcher_ConstrainHorizontal")
    sc_tap(sc_on(3, 0.3)); sc_key("V", "V")  # Mitte läge auf der roten X-Achse
    sc_log("horver")
    wait()


def sc_parallel():
    """zwei Linien parallel (Knopf), dann eine dritte rechtwinklig dazu (Taste N)"""
    lines = [Part.LineSegment(V(-30, -14, 0), V(22, -6, 0)), Part.LineSegment(V(-28, 8, 0), V(24, 22, 0)),
             Part.LineSegment(V(34, -22, 0), V(40, 22, 0))]
    sc_open(lines, (), 1, 0, 85)
    sc_tap(sc_on(0)); sc_tap(sc_on(1)); sc_tool("Sketcher_ConstrainParallel")
    sc_tap(sc_on(1, 0.3)); sc_tap(sc_on(2, 0.3)); sc_key("N", "N")  # Mitte läge auf der roten X-Achse
    sc_log("parallel")
    wait()


def sc_tangent():
    """Linie trifft den Bogen mit Knick: Linie und Bogen anklicken, Tangential macht den Übergang glatt"""
    arc = Part.ArcOfCircle(Part.Circle(V(12, 0, 0), V(0, 0, 1), 16), -math.pi / 2, math.pi / 2)
    lines = [Part.LineSegment(V(-30, -16, 0), V(12, -16, 0)), arc, Part.LineSegment(V(12, 16, 0), V(-30, 4, 0))]
    cons = [C("Tangent", 0, 2, 1, 1), C("Coincident", 1, 2, 2, 1)]  # Tangente am Endpunkt schließt Koinzident ein
    sc_open(lines, cons, -3, 0, 85)
    sc_tap(sc_on(2)); sc_tap(sc_on(1, 0.3)); sc_tool("Sketcher_ConstrainTangent")
    sc_log("tangent")
    wait()


def sc_equal():
    """zwei Kreise gleich groß machen, dann einen bemaßen: der andere folgt"""
    # Abstand der Mitten schon bemaßt: sonst wäre das Kreismaß das erste der Skizze, und das erste Maß skaliert die
    # ganze Skizze samt Ansicht (FreeCAD AutoScale) - im Bild änderte sich dann nichts
    sc_open([circle(-20, 0, 7), circle(16, 0, 14)], [C("DistanceX", 0, 3, 1, 3, 36)], -3, 0, 85)
    sc_tap(sc_on(0, 0.125)); sc_tap(sc_on(1, 0.125)); sc_tool("Sketcher_ConstrainEqual")
    sc_tool("Sketcher_Dimension")
    sc_tap(sc_on(1, 0.125)); sc_tap(lambda: (30, 12))
    sc_type("20")
    sc_key("Esc", "Escape")
    sc_log("equal")
    wait()


def sc_symmetric():
    """Rechteck abseits der Mitte: zwei gegenüberliegende Ecken und den Ursprung anklicken, Symmetrisch rückt es mittig.
    (Zwei Ecken einer waagrechten Kante zur senkrechten Achse wären doppelt bestimmt: das Rechteck ist schon waagrecht.)"""
    lines, cons = sc_rect(8, -6, 42, 18)
    # Breite und Höhe bemaßt: sonst verzieht der Löser das Rechteck, statt es nur zu verschieben
    sc_open(lines, cons + [C("DistanceX", 0, 1, 0, 2, 34), C("DistanceY", 1, 1, 1, 2, 24)], 1, 0, 85)
    sc_tap(sc_end(0, 1)); sc_tap(sc_end(1, 2)); sc_tap((0, 0))
    sc_tool("Sketcher_ConstrainSymmetric")
    sc_log("symmetric")
    wait()


def sc_block():
    """Kreis lässt sich ziehen; nach Fixieren bleibt er, wo er ist"""
    sc_open([circle(-10, 0, 12)], (), -3, 0, 85)
    sc_drag(sc_end(0, 3), (8, 6))
    sc_tap(sc_on(0, 0.125)); sc_tool("Sketcher_ConstrainBlock")
    sc_drag(sc_end(0, 3), (-14, -10))
    sc_log("block")
    wait()


def sc_dimension():
    """Rechteck und Kreis ohne Maße: Länge der unteren Kante und Durchmesser des Kreises eintippen"""
    lines, cons = sc_rect(-24, -14, 22, 16)
    # Höhe schon bemaßt, sonst skaliert das erste Maß die ganze Skizze samt Ansicht (siehe sc_equal)
    sc_open(lines + [circle(0, 1, 6)], cons + [C("DistanceY", 1, 1, 1, 2, 30)], -3, 0, 85)
    sc_tool("Sketcher_Dimension")
    sc_tap(sc_on(0)); sc_tap(lambda: (sc_on(0)()[0] + 4, -26))
    sc_type("60")
    sc_tap(sc_on(4, 0.125)); sc_tap(lambda: (16, 9))
    sc_type("20")
    sc_key("Esc", "Escape", y=110)  # unten stünde die Kappe auf dem Maß 60 mm
    sc_log("dimension")
    wait()


sc_clip("sketch_coincident", sc_coincident)
sc_clip("sketch_horver", sc_horver)
sc_clip("sketch_parallel", sc_parallel)
sc_clip("sketch_tangent", sc_tangent)
sc_clip("sketch_equal", sc_equal)
sc_clip("sketch_symmetric", sc_symmetric)
sc_clip("sketch_block", sc_block)
sc_clip("sketch_dimension", sc_dimension)


# --- Skizze erstellen, Grundlagen -----------------------------------------------------------------------------------
def sc_plane_point():
    """Mitte des sichtbaren Teils der XY-Ebene (die anderen Ebenen stehen davor oder dahinter): ein Raster auf z=0
    abtasten, was dort unter dem Cursor liegt"""
    v = Gui.ActiveDocument.ActiveView
    hits = []
    for r in (40, 8):  # grob, dann fein (die Ebenen sind je nach Zoom unterschiedlich groß)
        for i in range(-10, 11):
            for j in range(-10, 11):
                x, y = r * i / 10, r * j / 10
                px, py = v.getPointOnViewport(V(x, y, 0))
                if "XY_Plane" in str(v.getObjectInfo((int(px), int(py))) or {}):
                    hits.append((x, y))
        if len(hits) > 3:
            break
    if not hits:
        L("  XY plane not found under the cursor")
        return 5, -5
    return sum(h[0] for h in hits) / len(hits), sum(h[1] for h in hits) / len(hits)


def sc_look_iso(h=45):
    """Schräg von oben, Ursprung in der Mitte, so nah, dass die Ursprungsebenen groß genug zum Anklicken sind"""
    import pivy.coin  # getCameraNode braucht pivy
    v = Gui.ActiveDocument.ActiveView
    v.viewIsometric()
    c = v.getCameraNode(); d = v.getViewDirection(); dist = c.focalDistance.getValue()
    c.position.setValue(-d.x * dist, -d.y * dist, -d.z * dist)
    c.height.setValue(h)


def sc_new_sketch(cx=0, cy=0, h=80):
    """Skizze wie von Hand: Knopf Skizze, dann die Bodenebene XY in der Ansicht anklicken; der Clip beginnt davor.
    Bis die Skizze steht, ruht die Aufnahme; dann Ansicht auf (cx, cy) mit h mm Höhe."""
    step("look", sc_look_iso)
    wait()
    step("restart", sc_restart)
    wait()
    sc_tool("Design_CreateSketch")
    wait()
    entered = {}

    def ready():
        if Gui.ActiveDocument.getInEdit() is None:
            return False
        t = entered.setdefault("t", harness._rec["clock"]())
        if harness._rec["clock"]() - t < 1.2:  # Kamera dreht noch auf die Ebene
            return False
        sc_camera(cx, cy, h)
        return True

    def click():  # Kreis zuerst, Klick etwas später: während des Umbaus ruht die Aufnahme, sonst sähe man den Kreis nicht
        p = sc_where(sc_plane_point)
        sc_hover(p)
        record_click(sc_view().viewport().mapToGlobal(p))

        def press():
            sc_pause["done"] = ready
            QtTest.QTest.mouseClick(sc_view().viewport(), QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)
        QtCore.QTimer.singleShot(500, sc_safe(press))
    step("XY", lambda: sc_glide(sc_where(sc_plane_point), click))
    wait(2)
    step("in sketch", lambda: L("  in sketch: %s" % Gui.ActiveDocument.getInEdit()))


def sc_finish():
    """Skizze fertig stellen über den blauen Knopf; die Aufnahme ruht, bis das Modell wieder steht"""
    def go():
        sc_ring(button("Sketcher_LeaveSketch"))

        def leave():  # erst Kreis zeigen, dann ruht die Aufnahme bis zum Modell
            sc_pause["done"] = lambda: Gui.ActiveDocument.getInEdit() is None
            Gui.runCommand("Sketcher_LeaveSketch")
        QtCore.QTimer.singleShot(500, sc_safe(leave))
    step("finish", go)
    wait(2)


def sc_create_sketch():
    sc_new_sketch()
    sc_tool("Sketcher_CreateCircle", "Sketcher_CompCreateConic")
    sc_taps((0, 0), (20, 0), esc=True)
    sc_finish()


def sc_basics():
    """Ablauf: Skizze auf XY, Rechteck ab dem Ursprung, zwei Maße -> voll bestimmt, Skizze fertig -> Profil"""
    sc_new_sketch(28, 18, 110)
    sc_tool("Sketcher_CreateRectangle", "Sketcher_CompCreateRectangles")
    # 60 breit: das erste Maß skaliert sonst die ganze Skizze samt Ansicht (siehe sc_equal). Kein Esc danach: das
    # Rechteck-Werkzeug endet nach einem Rechteck, Esc verließe die Skizze
    sc_taps((0, 0), (60, 28))
    sc_tool("Sketcher_Dimension")
    sc_tap(sc_on(0)); sc_tap(lambda: (sc_on(0)()[0] + 3, -10))
    sc_type("60")
    sc_tap(sc_on(1)); sc_tap(lambda: (sc_on(1)()[0] + 10, sc_on(1)()[1] + 3))
    sc_type("40")
    sc_key("Esc", "Escape")
    step("dof", lambda: L("  basics: fully constrained=%s" % sc_sk().FullyConstrained))
    sc_finish()


scenario("Design_CreateSketch", sc_create_sketch, view="iso")
scenario("sketch_basics", sc_basics, view="iso")
