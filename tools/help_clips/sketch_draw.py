# SPDX-License-Identifier: LGPL-2.1-or-later
"""Erklär-Clips Skizze: Zeichnen und Ändern mit echten Klicks in der offenen Skizze (von oben). Der Clip beginnt in
der schon offenen Skizze; jeder Klick zeigt seinen Kreis, die Maus gleitet vorher hin, damit die Vorschau mitläuft.
Läuft in tools/help_images.py (exec in dessen Globals)."""

sd_XY = lambda: [o for o in doc().Objects if o.Name.startswith("XY_Plane")][0]


# Bausteine aus help_images.py jetzt festhalten: alle Clip-Dateien teilen sich die Globals, eine spätere könnte sie
# mit gleichem Namen überschreiben
sd_box, sd_circle, sd_closed, sd_rect_c = box, circle, closed, rect_c


def sd_view():
    """Ansicht des aktiven Designs (harness.view() nimmt die erste sichtbare, das kann die eines anderen sein)"""
    sub = mw.findChild(QtWidgets.QMdiArea).activeSubWindow()
    views = [v for v in (sub.findChildren(QtWidgets.QGraphicsView) if sub else []) if v.isVisible()] \
        or [v for v in mw.findChildren(QtWidgets.QGraphicsView) if v.isVisible()]
    v = max(views, key=lambda v: v.width() * v.height())
    harness._keep.append(v); return v


def sd_vp():
    return sd_view().viewport()


def sd_pos(w):
    """Mitte eines Glas-Widgets im Viewport (wie harness._pos, aber in der aktiven Ansicht)"""
    top = w
    while top.parentWidget():
        top = top.parentWidget()
    proxy = top.graphicsProxyWidget(); harness._keep.extend([w, top, proxy])
    p = sd_view().mapFromScene(proxy.mapToScene(QtCore.QPointF(w.mapTo(top, w.rect().center()))))
    return p.toPoint() if hasattr(p, "toPoint") else p


def sd_sk():
    return Gui.ActiveDocument.getInEdit().Object


def sd_pt(x, y, z=0):
    vp = sd_vp(); px, py = Gui.ActiveDocument.ActiveView.getPointOnViewport(V(x, y, z))
    dpr = vp.devicePixelRatioF()
    return QtCore.QPoint(int(px / dpr), int(vp.height() - py / dpr))


def sd_hover(p, mod=QtCore.Qt.NoModifier):
    """echte Mausbewegung (wie test_sketch_tools.hover)"""
    vp = sd_vp()
    QtWidgets.QApplication.sendEvent(vp, QtGui.QMouseEvent(QtCore.QEvent.MouseMove, QtCore.QPointF(p), QtCore.QPointF(vp.mapToGlobal(p)),
                                                           QtCore.Qt.NoButton, QtCore.Qt.NoButton, mod))


sd_mouse = {}


def sd_glide(target, then=None, ms=480, n=8):
    """Maus in n Schritten zum Ziel, danach then(); so läuft die Vorschau des Werkzeugs sichtbar mit"""
    start = sd_mouse.get("p") or target - QtCore.QPoint(30, -20)
    for i in range(1, n + 1):
        q = start + (target - start) * (i / n)
        QtCore.QTimer.singleShot(int(ms * i / n), lambda q=q: sd_hover(q))
    sd_mouse["p"] = target
    if then:
        QtCore.QTimer.singleShot(ms + 80, then)


def sd_press(p, btn=QtCore.Qt.LeftButton):
    sd_hover(p)
    record_click(sd_vp().mapToGlobal(p))
    QtTest.QTest.mouseClick(sd_vp(), btn, QtCore.Qt.NoModifier, p)


def sd_tap(x, y, z=0, name="click"):
    """Schritt: Maus hingleiten lassen, klicken (mit Kreis im Clip)"""
    step(name, lambda: sd_glide(sd_pt(x, y, z), lambda: sd_press(sd_pt(x, y, z))))


def sd_hover_to(x, y, z=0):
    step("move", lambda: sd_glide(sd_pt(x, y, z)))


def sd_right_click():
    step("right", lambda: sd_press(sd_mouse.get("p") or sd_vp().rect().center(), QtCore.Qt.RightButton))


def sd_tool(cmd, ring=None):
    """Werkzeug wie von Hand: Kreis auf seinem Knopf (bei Gruppen der Gruppenknopf ring), Befehl auslösen"""
    def go():
        try:
            record_click(sd_vp().mapToGlobal(sd_pos(button(ring or cmd))))
        except RuntimeError:
            L("  no button " + (ring or cmd))
        Gui.runCommand(cmd)
    step(cmd, go)
    wait()
    if os.environ.get("HELP_DUMP"):
        step("dump", lambda: sd_dump(cmd))


def sd_dump(cmd):
    """Werkzeugparameter des aktiven Werkzeugs ins Protokoll (für die Hilfe-Texte)"""
    for w in QtWidgets.QApplication.allWidgets():
        if w.isVisible() and w.metaObject().className().startswith("SketcherGui::SketcherToolDefaultWidget"):
            items = []
            for c in w.findChildren(QtWidgets.QWidget):
                if not c.isVisible():
                    continue
                if isinstance(c, QtWidgets.QComboBox):
                    items.append("combo[%s]" % "/".join(c.itemText(i) for i in range(c.count())))
                elif isinstance(c, QtWidgets.QCheckBox):
                    items.append("check[%s]" % c.text())
                elif isinstance(c, QtWidgets.QLabel) and c.text().strip():
                    items.append("label[%s]" % c.text())
                elif isinstance(c, QtWidgets.QLineEdit) and not isinstance(c.parentWidget(), (QtWidgets.QAbstractSpinBox, QtWidgets.QComboBox)):
                    items.append("edit[%s]" % c.text())
                elif isinstance(c, QtWidgets.QAbstractSpinBox):
                    items.append("spin[%s]" % c.text())
            L("  DUMP %s: %s" % (cmd, " ".join(items)))


def sd_camera():
    """von oben, Ursprung in der Mitte, 110 mm hoch im Bild: die Formen sind groß genug, nichts liegt unter der Palette"""
    c = Gui.ActiveDocument.ActiveView.getCameraNode()
    c.position.setValue(0, 0, c.position.getValue()[2]); c.height.setValue(110)


def sd_restart():
    """Aufnahme neu beginnen: der Clip startet in der offenen Skizze, nicht beim Anlegen"""
    if GIF and harness._rec:
        path = harness._rec["path"]
        harness._rec["timer"].stop()
        sd_mouse.clear()
        record_start(path)


def sd_open_sketch(geos=(), cons=()):
    """neue Skizze auf XY (wie von Hand: Skizze, Ebene wählen), Ausgangsgeometrie, von oben; der Clip beginnt hier"""
    step("create sketch", lambda: Gui.runCommand("Design_CreateSketch"))
    wait()
    step("sd_XY", lambda: Gui.Selection.addSelection(sd_XY()))
    wait(2)

    def setup():
        s = sd_sk()
        for g in geos:
            s.addGeometry(g, False)
        for c in cons:
            s.addConstraint(c)
        doc().recompute()
        Gui.Selection.clearSelection()
        sd_camera()
        st["sk"] = s
    step("setup", setup)
    wait()
    step("sd_restart", sd_restart)
    wait()


def sd_esc_step():
    def go():
        if sd_vp().cursor().shape() != QtCore.Qt.BitmapCursor:
            return  # Werkzeug hat schon von selbst aufgehört: Esc verließe sonst die Skizze
        QtTest.QTest.keyClick(sd_vp(), QtCore.Qt.Key_Escape)
        w = QtWidgets.QApplication.focusWidget()
        if w:  # sonst zeigt ein Knopf der Palette den Tastatur-Fokusrahmen
            w.clearFocus()
    step("esc", go)
    wait()


def sd_pick(*edges):
    """Skizzenelemente per Klick wählen (Strg für weitere): edges = (x, y) Punkte auf den Linien"""
    for i, (x, y) in enumerate(edges):
        if i == 0:
            sd_tap(x, y, name="sd_pick")
        else:
            def go(x=x, y=y):
                def press():
                    p = sd_pt(x, y); sd_hover(p, QtCore.Qt.ControlModifier)
                    record_click(sd_vp().mapToGlobal(p))
                    QtTest.QTest.mouseClick(sd_vp(), QtCore.Qt.LeftButton, QtCore.Qt.ControlModifier, p)
                sd_glide(sd_pt(x, y), press)
            step("sd_pick+", go)


def sd_squash():
    """Bilder, die sich vom vorigen nur in ein paar Punkten unterscheiden (die blinkende Schreibmarke des Maßfelds
    am Cursor), zählen als dasselbe Bild: record_stop fasst sie dann zusammen, und eine Pause bleibt kurz"""
    frames = harness._rec.get("frames")
    if not frames:
        return
    from PIL import Image, ImageChops

    def pil(q):
        return Image.frombuffer("RGB", (q.width(), q.height()), bytes(q.constBits()), "raw", "RGB", q.bytesPerLine(), 1)
    kept, ref = frames[0][0], pil(frames[0][0])
    for i, (q, t) in enumerate(frames):
        p = pil(q)
        changed = ImageChops.difference(ref, p).convert("L").point(lambda v: 255 if v > 24 else 0).histogram()[255]
        if changed > 60:  # mehr als die Schreibmarken (je etwa 2 x 7 Punkte, manchmal zwei Felder zugleich)
            kept, ref = q, p
        frames[i] = (kept, t)


def sd_sketch_clip(article, build, **kw):
    def run_build():
        build()
        step("squash", sd_squash)
    scenario(article, run_build, **(kw or dict(view="none", fixed=True)))


# --- Zeichnen -------------------------------------------------------------------------------------------------------
def line():
    sd_open_sketch()
    sd_tool("Sketcher_CreateLine")
    sd_tap(-35, -20); sd_tap(10, 15)
    sd_tap(-35, 25); sd_tap(35, 25)  # fast waagrecht: rastet waagrecht ein
    sd_esc_step()


def rectangle():
    sd_open_sketch()
    sd_tool("Sketcher_CreateRectangle", "Sketcher_CompCreateRectangles")
    sd_tap(-30, -20); sd_tap(30, 20)
    sd_esc_step()


def polyline():
    sd_open_sketch()
    sd_tool("Sketcher_CreatePolyline")
    for x, y in ((-35, -20), (35, -20), (20, 20), (-20, 20), (-35, -20)):  # zurück zum Start: geschlossen
        sd_tap(x, y)
    wait()


def circle_ellipse():
    sd_open_sketch()
    sd_tool("Sketcher_CreateCircle", "Sketcher_CompCreateConic")
    sd_tap(-20, 0); sd_tap(-6, 0)
    sd_esc_step()
    sd_tool("Sketcher_CreateEllipseByCenter", "Sketcher_CompCreateConic")
    sd_tap(25, 0); sd_tap(40, 0); sd_tap(25, 9)
    sd_esc_step()


def arc():
    sd_open_sketch()
    sd_tool("Sketcher_CreateArc", "Sketcher_CompCreateArc")
    sd_tap(0, -12); sd_tap(25, -12)
    sd_hover_to(0, 13)  # über oben: der Bogen folgt der Maus
    sd_tap(-25, -12)
    sd_esc_step()


def slot():
    sd_open_sketch()
    sd_tool("Sketcher_CreateSlot", "Sketcher_CompSlot")
    sd_tap(-25, 0); sd_tap(25, 0); sd_tap(25, 10)
    sd_esc_step()


def polygon():
    sd_open_sketch()
    sd_tool("Sketcher_CreateHexagon", "Sketcher_CompCreateRegularPolygon")
    sd_tap(0, 0); sd_tap(28, 8)
    sd_esc_step()


def bspline():
    sd_open_sketch()
    sd_tool("Sketcher_CreateBSpline", "Sketcher_CompCreateBSpline")
    for x, y in ((-36, -10), (-12, 22), (12, -18), (36, 10)):
        sd_tap(x, y)
    sd_right_click()
    wait()
    sd_esc_step()


def conic():
    sd_open_sketch()
    sd_tool("Sketcher_CreateConic")
    sd_tap(-30, -15); sd_tap(30, -15); sd_tap(0, 25)
    sd_esc_step()


def point():
    sd_open_sketch(*sd_rect_c(-35, -20, 35, 20))
    sd_tool("Sketcher_CreatePoint")
    for x, y in ((-20, 9), (20, 9), (0, -9)):  # neben den Achsen: dort rastete der Punkt auf der Achse ein
        sd_tap(x, y)
    sd_esc_step()


def text():
    sd_open_sketch()
    sd_tool("Sketcher_CreateText")

    def type_text():  # Feld "Text" der Werkzeugparameter
        e = [e for e in visible(QtWidgets.QLineEdit) if e.text() == "Text"][0]
        record_click(sd_vp().mapToGlobal(sd_pos(e)))
        e.selectAll(); QtTest.QTest.keyClicks(e, "MyCAD")
    step("type", type_text)
    wait()
    sd_tap(-35, -8); sd_tap(35, -8)
    sd_esc_step()


def project():
    """Körper knapp unter der Skizzenebene: seine Kanten (z=-5) liegen nicht in der Ebene, die übernommenen Linien
    flimmern nicht mit der Körperfläche (auf einer Körperfläche waren sie mal sichtbar, mal verdeckt)"""
    step("box", lambda: sd_box(-30, -20, 30, 20, 10, z=-15))
    sd_open_sketch()
    sd_tool("Sketcher_Projection", "Sketcher_CompExternal")
    for x, y in ((0, -20), (30, 0), (0, 20), (-30, 0)):
        sd_tap(x, y, -5)
    sd_esc_step()
    sd_leave()  # das Design mit offener Skizze und übernommenen Kanten zu schließen, brachte das nächste zum Absturz


# --- Ändern ---------------------------------------------------------------------------------------------------------
def fillet():
    sd_open_sketch(*sd_rect_c(-30, -20, 30, 20))
    sd_tool("Sketcher_CreateFillet", "Sketcher_CompCreateFillets")
    sd_tap(30, 20); sd_tap(-30, -20)
    sd_esc_step()


def trim():
    """zwei waagrechte, zwei senkrechte Linien mit Überstand: die Überstände wegklicken, übrig bleibt ein Rechteck"""
    L_ = lambda x0, y0, x1, y1: Part.LineSegment(V(x0, y0, 0), V(x1, y1, 0))
    sd_open_sketch([L_(-20, -12, 34, -12), L_(-20, 12, 34, 12), L_(-20, -12, -20, 26), L_(20, -12, 20, 26)])
    sd_tool("Sketcher_Trimming")
    sd_tap(28, 12); sd_tap(28, -12); sd_tap(20, 20); sd_tap(-20, 20)
    sd_esc_step()


def offset():
    sd_open_sketch(*sd_rect_c(-25, -15, 25, 15))
    sd_tap(0, -15, name="pick edge")
    sd_tool("Sketcher_Offset")
    sd_hover_to(0, -20)
    sd_tap(0, -22)
    wait()


def mirror():
    lines, cons = sd_closed([V(8, -15, 0), V(32, -15, 0), V(32, 15, 0), V(8, 5, 0)])
    sd_open_sketch(lines, cons)
    sd_pick((20, -15), (32, 0), (20, 10), (8, -5))
    sd_tool("Sketcher_Symmetry")
    sd_tap(0, 22)  # die senkrechte Achse ist die Spiegellinie
    wait()


def sd_param(text):
    """erstes Zahlenfeld der Werkzeugparameter überschreiben (mit Kreis auf dem Feld)"""
    def go():
        for w in QtWidgets.QApplication.allWidgets():
            if w.isVisible() and w.metaObject().className().startswith("SketcherGui::SketcherToolDefaultWidget"):
                spin = [c for c in w.findChildren(QtWidgets.QAbstractSpinBox) if c.isVisible()][0]
                record_click(sd_vp().mapToGlobal(sd_pos(spin)))
                spin.lineEdit().selectAll(); QtTest.QTest.keyClicks(spin.lineEdit(), text)
                return
    step("param " + text, go)
    wait()


def pattern():
    sd_open_sketch([sd_circle(25, 0, 5)])
    sd_pick((30, 0))
    sd_tool("Sketcher_Rotate", "Sketcher_RectangularArray")
    sd_param("4")  # Elements: das Original und drei Kopien
    sd_tap(0, 0); sd_tap(25, 0)
    sd_hover_to(0, 25)  # der Winkel folgt der Maus um die Mitte herum
    sd_tap(-25, 0)
    sd_esc_step()


def move():
    sd_open_sketch([sd_circle(-20, 0, 10)])
    sd_pick((-10, 0))
    sd_tool("Sketcher_Translate")
    sd_tap(-20, 0); sd_tap(20, 0)
    sd_esc_step()


def construction():
    lines, cons = sd_rect_c(-30, -20, 30, 20)
    sd_open_sketch(lines + [Part.LineSegment(V(-30, -20, 0), V(30, 20, 0)), Part.LineSegment(V(-30, 20, 0), V(30, -20, 0))], cons)
    sd_pick((-15, -10), (-15, 10))
    sd_tool("Sketcher_ToggleConstruction")
    step("clear", lambda: Gui.Selection.clearSelection())
    wait()


def sd_leave():
    """Skizze fertig stellen wie von Hand. Kreis zeigen, dann die Aufnahme kurz anhalten: ein Bild mitten im Abbau der
    Skizzen-Ansicht ist dunkelgrau (oder bringt MyCAD zum Absturz)"""
    def leave():
        p = sd_pos(button("Sketcher_LeaveSketch"))
        record_click(sd_vp().mapToGlobal(p))

        def press():
            if harness._rec:
                harness._rec["timer"].stop()
                QtCore.QTimer.singleShot(1800, harness._rec["timer"].start)
            QtTest.QTest.mouseClick(sd_vp(), QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)
        QtCore.QTimer.singleShot(450, press)  # erst den Kreis zeigen
    step("finish", leave)
    wait(3)  # Kamera fertig gedreht


def finish():
    sd_open_sketch(*sd_rect_c(-30, -20, 30, 20))
    sd_leave()
    sd_tap(0, 0, name="select profile")
    wait()
    feature("Design_Extrude", lambda: type_into(0, "20"))


sd_sketch_clip("sketch_line", line)
sd_sketch_clip("sketch_polyline", polyline)
sd_sketch_clip("sketch_rectangle", rectangle)
sd_sketch_clip("sketch_circle", circle_ellipse)
sd_sketch_clip("sketch_arc", arc)
sd_sketch_clip("sketch_slot", slot)
sd_sketch_clip("sketch_polygon", polygon)
sd_sketch_clip("sketch_bspline", bspline)
sd_sketch_clip("sketch_conic", conic)
sd_sketch_clip("sketch_point", point)
sd_sketch_clip("sketch_text", text)
sd_sketch_clip("sketch_project", project, view="iso")
sd_sketch_clip("sketch_fillet", fillet)
sd_sketch_clip("sketch_trim", trim)
sd_sketch_clip("sketch_offset", offset)
sd_sketch_clip("sketch_mirror", mirror)
sd_sketch_clip("sketch_pattern", pattern)
sd_sketch_clip("sketch_move", move)
sd_sketch_clip("sketch_construction", construction)
sd_sketch_clip("sketch_finish", finish, view="iso")
