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


def sd_jump(x, y, z=0):
    """Maus ohne Weg dorthin setzen (kein Überfahren anderer Elemente)"""
    def go():
        sd_mouse["p"] = sd_pt(x, y, z)
        sd_hover(sd_mouse["p"])
    step("jump", go)


def sd_right_click():
    """Rechtsklick: sieht im Clip aus wie ein Klick, darum mit Schild"""
    step("right", lambda: (md_key("Right-click"), sd_press(sd_mouse.get("p") or sd_vp().rect().center(), QtCore.Qt.RightButton)))


def sd_key(label, key):
    """Taste wie von Hand (Fenster aktiv, Fokus in der Ansicht), im Clip als Schild"""
    def go():
        md_key(label)
        sc_activate()
        QtTest.QTest.keyClick(mw.windowHandle(), getattr(QtCore.Qt, "Key_" + key))
    step("key " + label, go)
    wait()


def sd_keys(text, ms=260):
    """Tippen ins Maßfeld am Cursor (es hat den Fokus); \\t = Tab, \\n = Enter, beide mit Schild"""
    def go():
        # Fenster aktiv: sonst gibt es keinen Fokus (focusWidget() ist None) und die Tasten gingen ins Leere; der Fokus
        # bleibt im Maßfeld der Szene
        QtWidgets.QApplication.setActiveWindow(mw)
        QtWidgets.QApplication.sendEvent(sd_view().scene(), QtCore.QEvent(QtCore.QEvent.WindowActivate))

        fresh = [True]  # erstes Zeichen in einem Feld ersetzt dessen ganzen Inhalt (die Maus hat ihn laufend gesetzt)

        def press(c):
            w = QtWidgets.QApplication.focusWidget() or sd_vp()
            if c in "\t\n":
                md_key("Tab" if c == "\t" else "Enter", 900)
                QtTest.QTest.keyClick(w, QtCore.Qt.Key_Tab if c == "\t" else QtCore.Qt.Key_Return)
                fresh[0] = True
                return
            if fresh[0] and hasattr(w, "selectAll"):
                w.selectAll()
            fresh[0] = False
            QtTest.QTest.keyClicks(w, c)
        for i, c in enumerate(text):
            QtCore.QTimer.singleShot(ms * (i + 1), lambda c=c: press(c))
    step("keys", go)
    wait(max(1, math.ceil(ms * (len(text) + 2) / 900)))


def sd_variant(group, text):
    """Werkzeug aus dem Menü am ▾ eines Knopfs, wie von Hand: Kreis auf dem Pfeil, Menü zeigen, Eintrag anklicken
    (die Aufnahme malt das Menü mit ins Bild); der Knopf zeigt danach die gewählte Variante"""
    def btn():
        return [b for b in visible(QtWidgets.QToolButton) if b.objectName() == "GlassButton" and b.property("command") == group][0]

    def open_menu():
        b = btn(); p = sd_pos(b)
        record_click(sd_vp().mapToGlobal(p + QtCore.QPoint(b.width() // 2 - 6, 0)))
        b.menu().popup(sd_vp().mapToGlobal(p + QtCore.QPoint(-b.width() // 2, b.height() // 2 + 4)))

    def choose():
        m = btn().menu()
        a = [a for a in m.actions() if a.text() == text][0]
        record_click(m.mapToGlobal(m.actionGeometry(a).center()))
        m.setActiveAction(a)
        QtCore.QTimer.singleShot(400, lambda: (m.hide(), a.trigger()))
    step("menu", open_menu)
    step(text, choose)
    wait()


def sd_tool(cmd, ring=None):
    """Werkzeug wie von Hand: Kreis auf seinem Knopf (bei Gruppen der Gruppenknopf ring), 0,4 s später der Befehl:
    sonst steht sein Panel schon im Bild, bevor der Kreis kommt"""
    def go():
        try:
            record_click(sd_vp().mapToGlobal(sd_pos(button(ring or cmd))))
        except RuntimeError:
            L("  no button " + (ring or cmd))
        QtCore.QTimer.singleShot(400, lambda: Gui.runCommand(cmd))
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


def sd_camera(h=110):
    """von oben, Ursprung in der Mitte, 110 mm hoch im Bild: die Formen sind groß genug, nichts liegt unter der Palette"""
    c = Gui.ActiveDocument.ActiveView.getCameraNode()
    c.position.setValue(0, 0, c.position.getValue()[2]); c.height.setValue(h)


def sd_restart():
    """Aufnahme neu beginnen: der Clip startet in der offenen Skizze, nicht beim Anlegen"""
    if GIF and harness._rec:
        path = harness._rec["path"]
        harness._rec["timer"].stop()
        sd_mouse.clear()
        record_start(path)


def sd_open_sketch(geos=(), cons=(), h=110):
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
        sd_camera(h)
        st["sk"] = s
    step("setup", setup)
    wait()
    step("sd_restart", sd_restart)
    wait()


def sd_esc_step():
    def go():
        if sd_vp().cursor().shape() != QtCore.Qt.BitmapCursor:
            return  # Werkzeug hat schon von selbst aufgehört: Esc verließe sonst die Skizze
        md_key("Esc")
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
    sd_tap(-35, 25)
    sd_hover_to(0, 32)  # die zweite Linie per Maßfeld: Länge 70, Tab, Winkel 0, Enter
    sd_keys("70\t0\n")
    sd_esc_step()


def rectangle():
    """Varianten am ▾ zeigen, ein Rechteck; dann eins mit runden Ecken (Taste U in den Werkzeugparametern)"""
    sd_open_sketch()
    sd_variant("Sketcher_CompCreateRectangles", "Rectangle")
    sd_tap(-40, -15); sd_tap(-5, 15)
    sd_esc_step()
    sd_tool("Sketcher_CreateRectangle", "Sketcher_CompCreateRectangles")
    sd_key("U", "U")
    sd_tap(5, -15); sd_tap(40, 15)
    sd_keys("5\n")  # dann der Eckenradius: tippen und Enter
    sd_esc_step()


def polyline():
    sd_open_sketch()
    sd_tool("Sketcher_CreatePolyline")
    for x, y in ((-35, -20), (35, -20), (35, 5)):
        sd_tap(x, y)
    sd_key("M", "M")  # nächstes Stück als Bogen
    sd_hover_to(26, 22)
    sd_tap(5, 18)
    sd_key("M", "M")  # wieder Linie
    sd_tap(-35, 18)
    step("mode", lambda: L("  polyline: %s" % [type(g).__name__ for g in sd_sk().Geometry]))
    sd_tap(-35, -20)  # zurück zum Start: geschlossen
    sd_esc_step()


def circle_ellipse():
    sd_open_sketch()
    sd_tool("Sketcher_CreateCircle", "Sketcher_CompCreateConic")
    sd_tap(-20, 0); sd_tap(-6, 0)
    sd_esc_step()
    sd_variant("Sketcher_CompCreateConic", "Ellipse From Center")
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
    sd_variant("Sketcher_CompCreateRegularPolygon", "Hexagon")
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
    for x, y in ((-20, 9), (20, 9), (6, -9)):  # neben den Achsen: dort rastete der Punkt auf der Achse ein
        sd_tap(x, y)
    sd_esc_step()


def text():
    sd_open_sketch()
    sd_tool("Sketcher_CreateText")
    sd_hover_to(-30, -12)  # Maus in die Ansicht: sonst steht das Koordinatenfeld beim Tippen am Ursprung

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
    step("turn", lambda: (Gui.ActiveDocument.ActiveView.viewIsometric(), Gui.SendMsgToActiveView("ViewFit")))
    wait(2)
    sd_tool("Sketcher_Projection", "Sketcher_CompExternal")
    # jede Kante von außen her entlang der Kante anfahren (Sprung dorthin, die Maus sieht man im Clip nicht): quer über
    # den Körper leuchteten Ober- und Seitenflächen bei jedem Weg auf
    for x, y, ox, oy in ((0, -20, -45, -20), (30, 0, 30, 35), (0, 20, 45, 20), (-30, 0, -30, 35)):
        sd_jump(ox, oy, -5)
        sd_tap(x, y, -5)
    sd_jump(-30, 45, -5)
    sd_esc_step()
    sd_leave()  # das Design mit offener Skizze und übernommenen Kanten zu schließen, brachte das nächste zum Absturz


# --- Ändern ---------------------------------------------------------------------------------------------------------
def fillet():
    """erst die eine, dann die andere Linie anklicken: die Größe richtet sich nach den Klickstellen (ein Klick auf den
    Eckpunkt gäbe nur 1/5 der kürzeren Linie, auf 60 x 40 kaum 6 mm)"""
    sd_open_sketch(*sd_rect_c(-30, -20, 30, 20))
    sd_tool("Sketcher_CreateFillet", "Sketcher_CompCreateFillets")
    sd_tap(16, 20); sd_tap(30, 6)
    sd_key("M", "M")  # Fase statt Rundung
    sd_tap(-16, -20); sd_tap(-30, -6)
    sd_esc_step()
    step("radii", lambda: L("  fillet: %s" % [round(g.Radius, 1) for g in sd_sk().Geometry if hasattr(g, "Radius")]))


def trim():
    """zwei waagrechte, zwei senkrechte Linien mit Überstand: die Überstände wegklicken, übrig bleibt ein Rechteck"""
    L_ = lambda x0, y0, x1, y1: Part.LineSegment(V(x0, y0, 0), V(x1, y1, 0))
    sd_open_sketch([L_(-20, -12, 34, -12), L_(-20, 12, 34, 12), L_(-20, -12, -20, 26), L_(20, -12, 20, 26), L_(6, -12, 6, 2)])
    sd_tool("Sketcher_Trimming")
    sd_tap(28, 12); sd_tap(28, -12); sd_tap(20, 20); sd_tap(-20, 20)
    sd_esc_step()
    # Verlängern: die kurze Linie (neben der grünen Y-Achse) bis an die obere Kante
    sd_variant("Sketcher_Trimming|Sketcher_Extend|Sketcher_Split", "Extend Edge")
    sd_tap(6, -4); sd_tap(6, 12)
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
    sd_variant("Sketcher_RectangularArray|Sketcher_Rotate", "Rotate / Polar Transform")
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
    # ohne Auswahl: Konstruktion in der Palette schaltet das Zeichnen um, die neue Linie wird gestrichelt
    sd_palette_row("Construction")
    sd_tool("Sketcher_CreateLine")
    sd_tap(-30, -28); sd_tap(30, -28)
    sd_esc_step()
    sd_palette_row("Construction")


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
    step("keep", ci_keep_selection)  # das Schlussbild hebt die Auswahl auf: das Profil bleibt blau
    wait()


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
sd_sketch_clip("sketch_finish", finish)  # ohne Schlussbild-Pose: kein Sprung am Ende


# --- Skizzenpalette -------------------------------------------------------------------------------------------------
def sd_palette_row(text):
    """Zeile der Skizzenpalette: Kreis, dann auslösen"""
    def go():
        b = [b for b in visible(QtWidgets.QToolButton) if b.objectName() == "PaletteRow" and b.text() == text][0]
        record_click(sd_vp().mapToGlobal(sd_pos(b)))
        b.click()
    step(text, go)
    wait(2)


def sd_palette():
    """Platte unter der Skizzenebene, ein Bolzen durch sie hindurch: Schnittansicht schneidet seinen oberen Teil weg"""
    step("bodies", lambda: (sd_box(-35, -25, 35, 25, 8, z=-10), make_body([sd_circle(15, 0, 8)], -2, 16, "Pin")))
    sd_open_sketch([sd_circle(-15, 0, 10)])
    step("turn", lambda: Gui.ActiveDocument.ActiveView.viewIsometric())
    wait(2)
    sd_palette_row("Slice")
    sd_palette_row("Look At")
    sd_palette_row("Grid")
    sd_palette_row("Grid")
    sd_palette_row("Snap")
    sd_palette_row("Snap")
    sd_leave()


sd_sketch_clip("sketch_palette", sd_palette)
