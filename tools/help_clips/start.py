# SPDX-License-Identifier: LGPL-2.1-or-later
"""Erklär-Clips der Gruppe Erste Schritte (start_*): läuft in den Globals von tools/help_images.py"""


def _start_clips():
    """alle Helfer lokal: die Clip-Dateien teilen sich die Globals von help_images.py, gleiche Namen anderer Dateien
    überschrieben sich sonst gegenseitig"""
    from PySide6 import QtGui

    LEFT, NOMOD = QtCore.Qt.LeftButton, QtCore.Qt.NoModifier

    def gview():
        """die Ansicht des aktiven Designs (harness.view() nimmt die erste sichtbare, das kann die eines anderen Designs sein)"""
        v = max((v for v in mw.findChildren(QtWidgets.QGraphicsView) if v.isVisible()), key=lambda v: v.width() * v.height())
        harness._keep.append(v); return v

    def gpos(w):
        """Mitte eines Widgets auf einem Glas-Panel im Viewport (wie harness._pos, aber in gview())"""
        top = w
        while top.parentWidget():
            top = top.parentWidget()
        proxy = top.graphicsProxyWidget(); harness._keep.extend([w, top, proxy])
        return gview().mapFromScene(proxy.mapToScene(QtCore.QPointF(w.mapTo(top, w.rect().center()))))

    def gclick(w):
        """echter Klick auf ein Glas-Widget, im Clip mit Kreis"""
        p = gpos(w); vp = gview().viewport()
        record_click(vp.mapToGlobal(p))
        QtTest.QTest.mouseClick(vp, LEFT, NOMOD, p)

    def ring(w):
        """nur der Kreis auf einem Widget (ausgelöst wird anders)"""
        try:
            record_click(gview().viewport().mapToGlobal(gpos(w)))
        except Exception:
            pass

    def at(p):
        """Bildschirmpunkt (Viewport) eines 3D-Punkts"""
        vp = gview().viewport(); x, y = Gui.ActiveDocument.ActiveView.getPointOnViewport(p)
        dpr = vp.devicePixelRatioF()
        return QtCore.QPoint(int(x / dpr), int(vp.height() - y / dpr))

    def hover(q, mod=NOMOD):
        """echte Mausbewegung (Vorauswahl), wie tests/gui/test_sketch_tools.py"""
        vp = gview().viewport()
        for r in (q - QtCore.QPoint(1, 1), q):
            QtWidgets.QApplication.sendEvent(vp, QtGui.QMouseEvent(QtCore.QEvent.MouseMove, QtCore.QPointF(r), QtCore.QPointF(vp.mapToGlobal(r)),
                                                                   QtCore.Qt.NoButton, QtCore.Qt.NoButton, mod))

    def tap(p, mod=NOMOD):
        """echter Klick auf einen 3D-Punkt, im Clip mit Kreis"""
        q = at(p) if isinstance(p, App.Vector) else p
        hover(q, mod)
        record_click(gview().viewport().mapToGlobal(q))
        QtTest.QTest.mouseClick(gview().viewport(), LEFT, mod, q)

    def dtap(p):
        """Doppelklick auf einen 3D-Punkt (Maße am Modell), wie tests/gui/test_face_dims.py; im Clip ein Kreis"""
        q = at(p); vp = gview().viewport()
        hover(q)
        record_click(vp.mapToGlobal(q))
        QtTest.QTest.mouseClick(vp, LEFT, NOMOD, q)
        QtTest.QTest.mouseDClick(vp, LEFT, NOMOD, q)
        QtTest.QTest.mouseRelease(vp, LEFT, NOMOD, q)

    def field_click(box):
        """Zahlenfeld anklicken (Kreis) und Fokus hineinsetzen"""
        ring(box)
        box.setFocus()
        box.lineEdit().selectAll()

    def keys(w, text, enter=True):
        QtTest.QTest.keyClicks(w, text)
        if enter:
            QtTest.QTest.keyClick(w, QtCore.Qt.Key_Return)

    def card_fields():
        return [b for b in visible(QtWidgets.QAbstractSpinBox) if b.parentWidget() and b.parentWidget().objectName() == "FaceDimensions"]

    def clip(article, build, zoom=-1, still=1.2):
        """wie scenario(); vorweg hört der Textcursor auf zu blinken: sonst ändert sich das Bild ständig und der Clip
        kürzt kein Warten (jedes blinkende Feld hielte ihn auf voller Länge)"""
        def build_calm():
            step("calm", lambda: (QtGui.QGuiApplication.styleHints().setCursorFlashTime(0), skip_flicker(still)))
            build()
        scenario(article, build_calm, zoom=zoom)

    def skip_flicker(still=1.2):
        """Aufnahme im festen Takt statt nach der Uhr, und ohne Flackern:
        - jedes Bild zählt 1/8 s, wie lange MyCAD auch dafür brauchte (unter Last kommt der Takt nur alle ~1 s: sonst stünde
          jeder Zwischenschritt eines Klick-Kreises über 1 s und der Clip würde doppelt so lang)
        - Bilder, die sich vom letzten behaltenen nur in ein paar Pixeln unterscheiden (blinkender Textcursor im
          Skizzen-Maßfeld, der sich nicht abstellen lässt), fallen weg.
        ponytail: Schwelle 60 Pixelwerte; ein einzelnes getipptes Zeichen kann darunter liegen, es erscheint dann mit der
        nächsten größeren Änderung
        - still: so lange steht ein unverändertes Bild höchstens (record_stop kappt selbst erst bei 1,2 s)"""
        import numpy
        timer = harness._rec.get("timer") if harness._rec else None
        if not timer:
            return
        clock = [None, None]  # Takt, Zeitpunkt der letzten Änderung

        def tick():
            frames = harness._rec.get("frames") if harness._rec else None
            if frames is None:
                return
            n = len(frames)
            harness._record_frame()
            if len(frames) != n + 1:
                return
            changed = 1
            if n >= 1 and frames[-1][0].size() == frames[-2][0].size():
                x = numpy.frombuffer(bytes(frames[-1][0].constBits()), numpy.uint8)
                y = numpy.frombuffer(bytes(frames[-2][0].constBits()), numpy.uint8)
                changed = int((numpy.abs(x.astype(numpy.int16) - y) > 24).sum())
            if clock[0] is None:
                clock[0] = clock[1] = frames[-1][1]
            elif changed >= 60 or clock[0] - clock[1] < still:
                clock[0] += harness._rec["ms"] / 1000
            if changed >= 60:
                clock[1] = clock[0]
            frames[-1] = (frames[-1][0], clock[0])
            if n >= 2 and changed < 60:
                frames.pop()  # gleich oder nur Geflacker: das vorige Bild steht einfach länger
        timer.timeout.disconnect()
        timer.timeout.connect(tick)
        st["tick"] = tick

    def iso_fit(zoom=0):
        v = Gui.ActiveDocument.ActiveView
        v.viewIsometric(); Gui.SendMsgToActiveView("ViewFit")
        for _ in range(abs(zoom)):
            (v.zoomIn if zoom > 0 else v.zoomOut)()

    def center(b, face):
        return b.Shape.getElement(face).CenterOfMass

    # --- start_dimensions ------------------------------------------------------------------------------------------------
    def dim_box():
        """Block aus einer bemaßten Skizze (60 x 40, Rechteck mit Maßen), 20 hoch"""
        lines, cons = rect_c(0, 0, 60, 40)
        sk = dz.sketch(doc(), lines)
        for c in cons + [C("Horizontal", 0), C("Horizontal", 2), C("Vertical", 1), C("Vertical", 3),
                         C("DistanceX", 0, 1, 0, 2, 60), C("DistanceY", 1, 1, 1, 2, 40)]:
            sk.addConstraint(c)
        doc().recompute()
        _, b = dz.extrude(doc(), sk, 20)
        sk.Visibility = False; dz.profiles(sk).Visibility = False
        b.Label = "Block"
        doc().recompute()
        return b

    def front(b):
        return [f for f in sides(b) if normal(b.Shape.getElement(f)).y < -0.5][0]

    def dimensions():
        step("box", lambda: (look(V(30, 20, 10), 120), st.update(b=dim_box())))
        step("dclick top", lambda: dtap(center(st["b"], top(st["b"]))))
        wait()
        step("field", lambda: field_click(card_fields()[0]))
        step("type", lambda: keys(card_fields()[0].lineEdit(), "35"))
        wait()
        step("dclick side", lambda: dtap(center(st["b"], front(st["b"]))))
        wait()
        step("field", lambda: field_click(card_fields()[0]))
        step("type", lambda: keys(card_fields()[0].lineEdit(), "80"))
        wait()
        step("check", lambda: L("  volumes=%s errors=%s" % (volumes(), errors())))

    clip("start_dimensions", dimensions, still=1.0)

    # --- start_first -----------------------------------------------------------------------------------------------------
    def tool(cmd, run=None):
        """Werkzeug über seinen Knopf (Kreis darauf); ausgelöst direkt, wie use() in help_images.py. run: Befehl, wenn der
        Knopf eine Gruppe ist (Gui.runCommand einer Gruppe startet kein Werkzeug)"""
        tool_ring(cmd)
        Gui.runCommand(run or cmd)

    def press_ok():
        b = [b for b in visible(QtWidgets.QPushButton) if b.text().replace("&", "") == "OK"][0]
        ring(b); b.click()

    def drag_to(a, b, n=6):
        """Maus ohne Taste von a nach b (Gummiband des Werkzeugs sichtbar)"""
        for k in range(1, n + 1):
            hover(a + (b - a) * k / n)

    def xy_pixel():
        """auf die Bodenebene (XY) klicken: mitten in die Pixel, die die Ebene treffen (die anderen Ebenen verdecken Teile)"""
        v = Gui.ActiveDocument.ActiveView; vp = gview().viewport(); dpr = vp.devicePixelRatioF()
        o = at(V(0, 0, 0)); hits = []
        for dx in range(-150, 151, 6):
            for dy in range(-150, 151, 6):
                q = o + QtCore.QPoint(dx, dy)
                info = v.getObjectInfo((q.x() * dpr, (vp.height() - q.y()) * dpr))
                if info and str(info.get("Object", "")).startswith("XY_Plane"):
                    hits.append(q)
        cx = sum(q.x() for q in hits) / len(hits); cy = sum(q.y() for q in hits) / len(hits)
        return min(hits, key=lambda q: (q.x() - cx) ** 2 + (q.y() - cy) ** 2)

    def look(c, h):
        """Iso-Ansicht auf den Punkt c, h mm hoch im Bild (orthografische Kamera wie in MyCAD)"""
        from pivy import coin
        cam = Gui.ActiveDocument.ActiveView.getCameraNode()
        cam.orientation.setValue(coin.SbRotation(0.424708, 0.17592, 0.339851, 0.820473))  # Iso wie Gui/Camera.cpp, ohne Animation
        d = cam.orientation.getValue().multVec(coin.SbVec3f(0, 0, -1))
        dist = max(cam.focalDistance.getValue(), 500)
        # der Clip schneidet links die Seitenleiste ab (record_start left=306): c in die Mitte des Clips, nicht des Fensters
        right = cam.orientation.getValue().multVec(coin.SbVec3f(1, 0, 0))
        shift = 153 * h / gview().viewport().height()
        cam.position.setValue(coin.SbVec3f(c.x, c.y, c.z) - d * dist - right * shift); cam.focalDistance.setValue(dist)
        cam.height.setValue(h)

    def pause():
        """Aufnahme anhalten: der Wechsel in die Skizze und zurück zeigt kurz ein leeres blaues Bild und die alte Leiste"""
        if harness._rec:
            harness._rec["timer"].stop()

    def resume():
        if harness._rec:
            harness._rec["timer"].start()

    def enter_sketch():
        """Skizze, Ebenen erscheinen, Klick auf die Bodenebene. Den Wechsel in die Skizze nimmt der Clip nicht auf: er zeigt
        sonst kurz die alte Leiste mit Aufgaben-Panel und ein leeres Bild. Kreis zuerst, Klick und Pause 0,5 s später"""
        step("sketch", lambda: (look(V(0, 0, 0), 160), tool("Design_CreateSketch")))

        def plane():
            q = xy_pixel()
            record_click(gview().viewport().mapToGlobal(q))
            QtCore.QTimer.singleShot(500, lambda: (pause(), tap_silent(q)))
        step("plane", plane)
        step("resume", resume)

    def leave_sketch():
        step("finish", lambda: (tool_ring("Sketcher_LeaveSketch"),
                                QtCore.QTimer.singleShot(500, lambda: (pause(), Gui.runCommand("Sketcher_LeaveSketch")))))
        step("iso", lambda: (look(V(0, 0, 5), 110), resume()))

    def tap_silent(q, mod=NOMOD):
        hover(q, mod)
        QtTest.QTest.mouseClick(gview().viewport(), LEFT, mod, q)

    def first_design():
        enter_sketch()
        step("rect", lambda: tool("Sketcher_CompCreateRectangles", "Sketcher_CreateRectangle"))
        step("p1", lambda: (st.update(p1=at(V(-30, -20, 0)), p2=at(V(30, 20, 0))), tap(st["p1"])))
        step("move", lambda: drag_to(st["p1"], st["p2"]))
        step("w", lambda: keys(QtWidgets.QApplication.focusWidget(), "60"))
        step("h", lambda: keys(QtWidgets.QApplication.focusWidget(), "40"))
        step("esc", esc_key)
        leave_sketch()
        step("profile", lambda: tap(V(0, 0, 0)))
        step("extrude", lambda: tool("Design_Extrude"))
        step("dist", lambda: (ring(sorted(visible(QtWidgets.QAbstractSpinBox), key=lambda w: w.mapToGlobal(QtCore.QPoint(0, 0)).y())[0]), type_into(0, "20")))
        wait()
        step("ok", lambda: (press_ok(), L("  first: sketch=%s" % [round(g.length(), 2) for o in doc().Objects if o.TypeId == "Sketcher::SketchObject" for g in o.Geometry])))
        step("check", lambda: L("  volumes=%s errors=%s" % (volumes(), errors())))

    clip("start_first", first_design, still=1.0)

    # --- Handschrift für den Rotstift (Glyphen wie tests/scribble_read_check.cpp, Einheit x-Höhe, y nach unten) ----------
    def _arc(cx, cy, rx, ry, t0, t1, n=14):
        return [(cx + rx * math.cos(math.radians(t0 + (t1 - t0) * i / n)), cy + ry * math.sin(math.radians(t0 + (t1 - t0) * i / n))) for i in range(n + 1)]

    GLYPHS = {
        "Ø": (1.05, [_arc(.5, -.8, .38, .8, -90, -450, 24), [(.05, .12), (.95, -1.72)]]),
        "C": (.85, [_arc(.45, -.8, .38, .8, -40, -320, 20)]),
        "R": (.82, [[(.1, 0), (.1, -1.6)], [(.1, -1.6), (.45, -1.6), (.68, -1.42), (.66, -1.0), (.42, -.84), (.1, -.84)], [(.36, -.84), (.76, 0)]]),
        "1": (.55, [[(.08, -1.25), (.36, -1.6), (.36, 0)]]),
        "2": (.82, [[(.1, -1.25), (.3, -1.58), (.58, -1.5), (.65, -1.1), (.1, 0), (.75, 0)]]),
        "4": (.9, [[(.58, 0), (.58, -1.6), (.05, -.5), (.82, -.5)]]),
        "5": (.8, [[(.68, -1.6), (.18, -1.6), (.13, -.88), (.45, -.98), (.7, -.72), (.68, -.22), (.42, 0), (.08, -.14)]]),
        ".": (.3, [[(.1, -.08), (.15, -.02), (.1, 0)]]),
        ",": (.3, [[(.14, -.1), (.12, .05), (.06, .25)]]),
    }

    def _dense(poly, stepw=.06):
        out = [poly[0]]
        for (x0, y0), (x1, y1) in zip(poly, poly[1:]):
            n = max(1, int(math.hypot(x1 - x0, y1 - y0) / stepw))
            out += [(x0 + (x1 - x0) * k / n, y0 + (y1 - y0) * k / n) for k in range(1, n + 1)]
        return out

    def _stroke(points):
        vp = gview().viewport()

        def send(kind, x, y, button, buttons):
            p = QtCore.QPointF(x, y)
            QtWidgets.QApplication.sendEvent(vp, QtGui.QMouseEvent(kind, p, vp.mapToGlobal(p), button, buttons, NOMOD))
        send(QtCore.QEvent.MouseButtonPress, *points[0], LEFT, LEFT)
        for x, y in points[1:]:
            send(QtCore.QEvent.MouseMove, x, y, QtCore.Qt.NoButton, LEFT)
        send(QtCore.QEvent.MouseButtonRelease, *points[-1], LEFT, QtCore.Qt.NoButton)

    def handwrite(text, p, u=14):
        """text mit der Maus schreiben, mittig auf den 3D-Punkt p (u: x-Höhe in Pixeln)"""
        q = at(p)
        width = sum(GLYPHS[c][0] + .08 for c in text)
        x0, y0 = q.x() - width * u / 2, q.y() + .8 * u
        gx = 0
        for c in text:
            w, polys = GLYPHS[c]
            for poly in polys:
                _stroke([(x0 + (px + gx) * u, y0 + py * u) for px, py in _dense(poly)])
            gx += w + .08

    # --- start_tutorial_print --------------------------------------------------------------------------------------------
    def note_edit():
        return [e for e in visible(QtWidgets.QPlainTextEdit) if e.objectName() == "NoteText"][0]

    def note_line(text):
        e = note_edit(); e.setFocus()
        for c in text:
            QtTest.QTest.keyClick(e, c)
        QtTest.QTest.keyClick(e, QtCore.Qt.Key_Return)

    def sketch_obj():
        return Gui.ActiveDocument.getInEdit().Object

    def esc_key():
        QtTest.QTest.keyClick(gview().viewport(), QtCore.Qt.Key_Escape)

    def dimension(edge, edge_point, place, value):
        """Kante wählen, Bemaßung, Maß ablegen, Wert tippen (wie tests/gui/test_dimension.py: echter Klick auf den Knopf,
        Ablegen 0,3 s danach). Den Wert fragt ein eigenes Fenster ab: das zeigt der Clip nicht, nur das Ergebnis"""
        def start():
            ring_at(edge_point)
            Gui.Selection.clearSelection(); Gui.Selection.addSelection(doc().Name, sketch_obj().Name, edge)
            gclick(button("Sketcher_Dimension"))

            def put():
                vp = gview().viewport(); q = at(place)
                record_click(vp.mapToGlobal(q))
                QtTest.QTest.mouseMove(vp, q)
                QtTest.QTest.mouseClick(vp, LEFT, NOMOD, q)
            QtCore.QTimer.singleShot(300, put)
        step("dimension", start)
        step("value", lambda: keys(QtWidgets.QApplication.focusWidget(), value))
        step("esc", esc_key)

    def draw_rect(a, b):
        step("rect", lambda: tool("Sketcher_CompCreateRectangles", "Sketcher_CreateRectangle"))
        step("p1", lambda: (st.update(p1=at(a), p2=at(b)), tap(st["p1"])))
        step("move", lambda: drag_to(st["p1"], st["p2"]))
        step("p2", lambda: tap(st["p2"]))
        step("esc", esc_key)

    def sketch_on_xy():
        enter_sketch()

    def fake_slicer():
        """Drucken öffnet einen Slicer: im Container gibt es keinen, ein Skript nimmt die Datei an"""
        import stat
        d = "/out/home/slicer"; os.makedirs(d, exist_ok=True)
        path = os.path.join(d, "prusa-slicer")
        with open(path, "w") as f:
            f.write("#!/bin/sh\nexit 0\n")
        os.chmod(path, os.stat(path).st_mode | stat.S_IEXEC)
        os.environ["PATH"] = d + os.pathsep + os.environ.get("PATH", "")
        App.ParamGet("User parameter:BaseApp/Preferences/MyCAD").RemString("Slicer")

    def vertical_edges(b):
        return ["Edge%d" % i for i, e in enumerate(b.Shape.Edges, 1)
                if e.Curve.TypeId == "Part::GeomLine" and abs(e.Vertexes[0].Point.z - e.Vertexes[-1].Point.z) > 1]

    def type_expression(n, text):
        """Parameter ins n-te Zahlenfeld des Dialogs: Enter übernimmt den Ausdruck (bei einer Zahl wäre es OK)"""
        box = sorted(visible(QtWidgets.QAbstractSpinBox), key=lambda w: w.mapToGlobal(QtCore.QPoint(0, 0)).y())[n]
        ring(box); box.setFocus(); box.lineEdit().selectAll()
        keys(box.lineEdit(), text)

    def plate():
        return last("Design::Body")

    def read_corrections():
        """Korrekturen ausführen. ponytail: die Erkennung liest die mit der Maus geschriebenen Ø4.5 und C1 nicht (R2 schon,
        s. Bericht); deshalb kommen die Karten direkt über showCorrections, mit dem, was dort steht. Der Kreis zeigt den Knopf"""
        import DesignGui
        ring([b for b in visible(QtWidgets.QToolButton) if b.text() == "Apply Corrections"][0])
        d = Gui.ActiveDocument.ActiveView.getViewDirection()
        DesignGui.showCorrections(doc(), [("Ø4.5", V(-18, 0, 6), d), ("Ø4.5", V(18, 0, 6), d), ("C1", V(0, -20, 6), d)])

    def card_state():
        card = [(b.accessibleName(), b.text(), b.toolTip()) for b in card_fields()]
        params = [o for o in doc().Objects if o.TypeId == "App::VarSet"]
        return "card=%s params=%s note=%r errors=%s" % (card, params and params[0].ExpressionEngine,
                                                        [o.Text for o in doc().Objects if o.TypeId == "Design::Note"], errors())

    def tutorial_print():
        # 1. Maße in eine Notiz
        step("note", lambda: tool("Design_Note"))
        step("lines", lambda: [note_line(t) for t in ("Width = 60 mm", "Depth = 30 mm", "Thickness = 4 mm")])
        # 2. Skizze und Körper
        step("leave note", esc_key)
        sketch_on_xy()
        step("rect", lambda: (tool("Sketcher_CompCreateRectangles", "Sketcher_CreateRectangle"),
                              st.update(p1=at(V(-28, -14, 0)), p2=at(V(28, 14, 0))), tap(st["p1"])))
        step("p2", lambda: (drag_to(st["p1"], st["p2"]), tap(st["p2"])))
        step("esc", esc_key)
        dimension("Edge1", V(10, -14, 0), V(10, -7, 0), "60")
        dimension("Edge2", V(28, 5, 0), V(20, 5, 0), "30")
        leave_sketch()
        step("profile", lambda: (L("  sketch=%s" % [round(g.length(), 2) for o in doc().Objects if o.TypeId == "Sketcher::SketchObject" for g in o.Geometry]),
                                 tap(V(0, 0, 0))))
        step("extrude", lambda: tool("Design_Extrude"))
        step("dist", lambda: type_expression(0, "Thickness"))
        step("ok", press_ok)
        # 3. Fläche antippen, Zahl ändern
        step("dclick top", lambda: dtap(center(plate(), top(plate()))))
        step("field", lambda: (L("  before: " + card_state()), field_click(card_fields()[0])))
        step("type", lambda: keys(card_fields()[0].lineEdit(), "6"))
        # 4. Ecken runden
        def pick_edges():
            L("  after: " + card_state())
            Gui.Selection.clearSelection()
            for e in vertical_edges(plate()):
                ring_at(plate().Shape.getElement(e).CenterOfMass)
                Gui.Selection.addSelection(plate(), e)
        step("edges", pick_edges)
        step("fillet", lambda: tool("Design_Fillet"))
        step("r big", lambda: type_field("Radius", "20"))
        wait()
        step("r 3", lambda: type_field("Radius", "3"))
        step("ok", press_ok)
        # 5. Rotstift: näher heran, damit die Schrift lesbar ist
        step("red pen", lambda: (Gui.Selection.clearSelection(), tool("Design_RedPen")))
        step("holes", lambda: (handwrite("Ø4.5", V(-18, 0, 6), 16), handwrite("Ø4.5", V(18, 0, 6), 16)))
        step("chamfer", lambda: handwrite("C1", V(0, -20, 6), 16))
        wait()
        step("apply", read_corrections)
        step("apply all", lambda: (L("  cards=%s" % [b.accessibleName() for b in visible(QtWidgets.QPushButton) if b.accessibleName().startswith("Apply ")]),
                                   gclick([b for b in visible(QtWidgets.QPushButton) if b.text() == "Apply All"][0])))
        step("close", lambda: ([(ring(b), b.click()) for b in visible(QtWidgets.QPushButton) if b.text() == "Close"][:1],
                               Gui.runCommand("Design_ScribbleFinish")))
        # 6. Prüfen, drucken (die Notiz legt sich sonst über die Legende)
        step("print view", lambda: (L("  after red pen=%s errors=%s" % (volumes(), errors())), fake_slicer(),
                                    [b.click() for b in visible(QtWidgets.QToolButton) if b.objectName() == "NoteClose"],
                                    tool("Design_PrintView")))
        step("print", lambda: gclick([b for b in visible(QtWidgets.QPushButton) if b.text() == "Print"][0]))

    def ring_at(p):
        record_click(gview().viewport().mapToGlobal(at(p)))

    clip("start_tutorial_print", tutorial_print, still=0.8)

    # --- start_tutorial_assembly -----------------------------------------------------------------------------------------
    sys.path.append("/workspace/tests/design")
    import Design
    import design as dz  # Aufbau wie in den Headless-Tests (tests/design/design.py)

    def cyl_face(b, x, y):
        """Zylinderfläche (Bohrung oder Bolzen) mit der Achse bei x, y"""
        for i, f in enumerate(b.Shape.Faces, 1):
            if f.Surface.TypeId == "Part::GeomCylinder" and abs(f.Surface.Center.x - x) < 1e-6 and abs(f.Surface.Center.y - y) < 1e-6:
                return "Face%d" % i
        raise RuntimeError("no cylinder at %s %s" % (x, y))

    def gplace(b, p):
        return b.getGlobalPlacement().multVec(p)

    def combo_pick(label, text):
        try:
            box = field(label)
        except RuntimeError:
            box = [c for c in visible(QtWidgets.QComboBox) if c.findText(text) >= 0][0]
        ring(box); box.setCurrentIndex(box.findText(text))

    def push(text):
        gclick([b for b in visible(QtWidgets.QPushButton) if b.text() == text][0])

    def check_box(text):
        gclick([b for b in visible(QtWidgets.QCheckBox) if b.text() == text][0])

    def select_with_ring(pairs):
        Gui.Selection.clearSelection()
        for b, sub, p in pairs:
            ring_at(p); Gui.Selection.addSelection(b, sub)

    def asm_base():
        _, base = dz.box(doc(), 80, 40, 5)
        dz.extrude(doc(), dz.sketch(doc(), dz.circle(20, 20, 4), App.Placement(V(0, 0, 5), App.Rotation())), 10, op="Join", bodies=[base])
        base.Label = "Base"
        st["base"] = base
        hide_sketches()
        iso_fit(-1)

    def asm_lever():
        comp = [o for o in doc().Objects if o.TypeId == "App::Part" and o.Type == "Component"][-1]
        sk = dz.sketch(doc(), dz.rect(-7, 63, 50, 77), component=comp)
        _, lever = dz.extrude(doc(), sk, 4)
        dz.extrude(doc(), dz.sketch(doc(), dz.circle(0, 70, 4.2), component=comp), 4, op="Cut", bodies=[lever])
        lever.Label = "Lever"
        st.update(lever=lever, lever_comp=comp)
        hide_sketches()
        Gui.SendMsgToActiveView("ViewFit")

    def asm_plate():
        sk = dz.sketch(doc(), dz.rect(52, 6, 76, 34), App.Placement(V(0, 0, 5), App.Rotation()))
        _, p = dz.extrude(doc(), sk, 5)
        p.Label = "Cover"
        st["cover"] = p

    def bar(length, name, y):
        """Lasche 3 mm dick mit Löchern Ø4 bei x = 0 und x = length, in einer eigenen Komponente (wie tests/design/test_joints.py)"""
        comp = Design.newComponent(Design.root(doc())) if name != "Ground" else None
        if comp:
            comp.Label = name
        _, b = dz.extrude(doc(), dz.sketch(doc(), dz.rect(-5, y - 5, length + 5, y + 5), component=comp), 3)
        for x in (0, length):
            dz.extrude(doc(), dz.sketch(doc(), dz.circle(x, y, 2), component=comp), 3, op="Cut", bodies=[b])
        b.Label = name
        return comp, b

    def link(moving, b1, x1, y1, b2, x2, y2, **props):
        j = doc().addObject("Design::Joint", "Joint")
        j.Type = "Revolute"; j.Moving = moving
        j.Origin1 = (b1, [cyl_face(b1, x1, y1)]); j.Origin2 = (b2, [cyl_face(b2, x2, y2)])
        for k, v in props.items():
            setattr(j, k, v)
        doc().recompute()
        if not [e for e in moving.ExpressionEngine if e[0] == "Placement"]:  # die Lage folgt dem ersten Gelenk
            moving.setExpression("Placement", j.Name + ".Result")
        doc().recompute()
        return j

    def fourbar_build():
        Y = -80  # neben der ersten Baugruppe; die Kamera schaut nur hierhin
        st["fb"] = {"ground": bar(60, "Ground", Y), "crank": bar(15, "Crank", Y - 30), "coupler": bar(50, "Coupler", Y - 50),
                    "rocker": bar(30, "Rocker", Y - 70), "Y": Y}
        hide_sketches()
        Gui.SendMsgToActiveView("ViewFit")

    def hide_sketches():
        """Skizzen (und damit ihre Profile) aus, wie nach einem Extrudieren von Hand"""
        for o in doc().Objects:
            if o.TypeId == "Sketcher::SketchObject":
                o.Visibility = False

    def fourbar_joint(name):
        f = st["fb"]; Y = f["Y"]
        (gc, g), (cc, c), (kc, k), (rc, r) = f["ground"], f["crank"], f["coupler"], f["rocker"]
        if name == "crank":
            st["j1"] = link(cc, c, 0, Y - 30, g, 0, Y)
        elif name == "coupler":
            link(kc, k, 0, Y - 50, c, 15, Y - 30, Angle=-35)
        elif name == "rocker":
            link(rc, r, 0, Y - 70, k, 50, Y - 50, Angle=121)
        else:  # zurück zur Grundplatte: schließt die Kette
            link(rc, r, 30, Y - 70, g, 60, Y)
        Gui.SendMsgToActiveView("ViewFit")

    def drive(angles):
        """das erste Gelenk dreht, die Kette folgt (wie Animieren, hier in festen Schritten, je Schritt ein Bild im Clip)"""
        for a in angles:
            st["j1"].Angle = a; doc().recompute()
            QtWidgets.QApplication.processEvents()
            if st.get("tick"):
                st["tick"]()

    def tutorial_assembly():
        # 1. Grundplatte und Hebel
        step("base", asm_base)
        step("new component", lambda: tool("Design_NewComponent"))
        step("lever", asm_lever)
        # 2. Gelenk: Bohrung des Hebels, dann der Bolzen der Grundplatte, Gelenk
        step("pick", lambda: select_with_ring([(st["lever"], cyl_face(st["lever"], 0, 70), gplace(st["lever"], V(-4.2, 70, 4))),
                                               (st["base"], cyl_face(st["base"], 20, 20), V(20, 16, 15))]))
        step("joint", lambda: tool("Design_Joint"))
        wait()
        step("revolute", lambda: combo_pick("Type", "Revolute"))
        step("angle", lambda: (ring(field("Angle")), type_field("Angle", "60")))
        step("limits", lambda: check_box("Keep angle and distance within limits"))
        step("max", lambda: type_field("Angle max", "90"))
        step("animate", lambda: (push("Animate"), QtCore.QTimer.singleShot(1500, lambda: push("Stop"))))
        step("park", lambda: type_field("Angle", "135"))  # vom Platz der zweiten Platte weg
        step("ok", lambda: (press_ok(), Gui.SendMsgToActiveView("ViewFit")))
        # 3. Zwei Teile verschrauben
        step("cover", lambda: (asm_plate(), hide_sketches(), Gui.SendMsgToActiveView("ViewFit")))
        step("top", lambda: tap(V(66, 20, 10)))
        step("screw", lambda: (L("  screw at: %s" % [(x.ObjectName, x.SubElementNames) for x in Gui.Selection.getSelectionEx()]),
                               tool("Design_Fastener")))
        step("m3", lambda: combo_pick("Size", "M3"))
        step("insert", lambda: combo_pick("Holds", "Heat-set insert"))
        step("ok", lambda: (press_ok(), QtCore.QTimer.singleShot(1500, lambda: L("  fastener: %s bodies=%d errors=%s" % (
            [o.Label for o in doc().Objects if "Fastener" in o.TypeId], len([o for o in doc().Objects if o.TypeId == "Design::Body"]), errors())))))
        # 4. Eine geschlossene Kette
        step("bars", fourbar_build)
        for name in ("crank", "coupler", "rocker", "close"):  # je Gelenk: Kreis auf Gelenk, die Teile rücken zusammen
            step(name, lambda name=name: (tool_ring("Design_Joint"), fourbar_joint(name)))
        step("drive", lambda: drive(list(range(0, 361, 30))))
        # 5. Passung und Gewicht
        step("back", lambda: look(V(40, 40, 5), 120))
        step("pick", lambda: select_with_ring([(st["lever"], cyl_face(st["lever"], 0, 70), gplace(st["lever"], V(0, 66, 4))),
                                               (st["base"], cyl_face(st["base"], 20, 20), V(20, 16, 15))]))
        step("fit", lambda: tool("Design_Fit"))
        step("h7", lambda: combo_pick("Fit", "H7/g6"))
        step("ok", press_ok)
        step("body", lambda: (Gui.Selection.clearSelection(), ring_at(V(70, 30, 2.5)), Gui.Selection.addSelection(st["base"])))
        step("measure", lambda: tool("Design_Measure"))
        wait()
        step("close", lambda: (L("  assembly errors=%s" % errors()), push("Close")))

    def tool_ring(cmd):
        """Kreis auf dem Knopf; liegt das Werkzeug unter einem anderen (▾-Menü), auf diesem Knopf"""
        try:
            ring(button(cmd))
        except RuntimeError:
            group = [b for b in visible(QtWidgets.QToolButton) if b.objectName() in ("GlassButton", "GlassProminent")
                     and cmd in str(b.property("command")).split("|")]
            if group:
                ring(group[0])
            else:
                L("  no button for " + cmd)

    clip("start_tutorial_assembly", tutorial_assembly, still=0.8)

    # --- start_overview: Skizze → Körper → Abrunden → Material → Notiz → Druckansicht --------------------------------------
    def overview():
        """Rundgang: Skizze → Körper → Abrunden → Material → Notiz, die rechnet"""
        sketch_on_xy()
        draw_rect(V(-30, -20, 0), V(30, 20, 0))
        leave_sketch()
        step("profile", lambda: tap(V(0, 0, 0)))
        step("extrude", lambda: tool("Design_Extrude"))
        step("dist", lambda: type_into(0, "20"))
        step("ok", press_ok)
        step("top", lambda: tap(center(plate(), top(plate()))))
        step("fillet", lambda: tool("Design_Fillet"))
        step("r", lambda: type_field("Radius", "5"))
        step("ok", press_ok)
        step("body", lambda: (Gui.Selection.clearSelection(), ring_at(center(plate(), top(plate()))), Gui.Selection.addSelection(plate())))
        step("appearance", lambda: tool("Design_Appearance"))
        wait()
        step("search", lambda: [e for e in visible(QtWidgets.QLineEdit) if e.placeholderText() == "Search materials"][0].setText("Walnut"))
        step("tile", lambda: gclick([b for b in visible(QtWidgets.QToolButton) if b.accessibleName().startswith("Walnut")][0]))
        step("ok", press_ok)
        step("note", lambda: tool("Design_Note"))
        step("lines", lambda: (note_line("Wall = 2 mm"), note_line("120 / 4 =")))
        step("leave", esc_key)

    clip("start_overview", overview, still=0.6)


_start_clips()
