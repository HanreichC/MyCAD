# SPDX-License-Identifier: LGPL-2.1-or-later
"""Erklär-Clips Bereich ÄNDERN: Drücken/Ziehen, Fläche ersetzen/teilen/entfernen, Fase, Wandstärke, Formschräge,
Kombinieren, Körper teilen, Verschieben, Ausrichten, Skalieren, Löschen. Läuft in den Globals von tools/help_images.py
(step, wait, use …). Eigene Namen beginnen mit md_, damit die Clip-Dateien sich nicht gegenseitig überschreiben."""
import math


# --- Eingaben, die man im Clip sieht --------------------------------------------------------------------------------
def md_view():
    """3D-Fenster des aktiven Designs: help_images.py hat zwei Designs offen, view() aus harness liefert das erste"""
    mdi = mw.findChild(QtWidgets.QMdiArea)
    sub = mdi.activeSubWindow() if mdi else None
    vs = [v for v in (sub.findChildren(QtWidgets.QGraphicsView) if sub else []) if v.isVisible()] or [view()]
    harness._keep.extend(vs)
    return vs[0]


def md_screen(p):
    """3D-Punkt -> Qt-Punkt im Viewport (Coin zählt y von unten)"""
    v = md_view(); x, y = Gui.ActiveDocument.ActiveView.getPointOnViewport(p)
    dpr = v.viewport().devicePixelRatioF()
    return QtCore.QPoint(int(x / dpr), int(v.viewport().height() - y / dpr))


def md_ring_at(p):
    record_click(md_view().viewport().mapToGlobal(md_screen(p)))


def md_ring(w, x=None):
    """Kreis auf einem Glass-Widget (Mitte oder x Pixel von links)"""
    top = w
    while top.parentWidget():
        top = top.parentWidget()
    pt = QtCore.QPointF(w.mapTo(top, QtCore.QPoint(w.width() // 2 if x is None else x, w.height() // 2)))
    p = md_view().mapFromScene(top.graphicsProxyWidget().mapToScene(pt))
    record_click(md_view().viewport().mapToGlobal(p))


def md_where(o, sub):
    """Stelle, die man anklickt: Flächen- oder Kantenmitte, beim ganzen Körper die Mitte der Oberseite"""
    if not sub:
        return o.Shape.getElement(top(o)).CenterOfMass if o.TypeId == "Design::Body" else o.Shape.BoundBox.Center
    e = o.Shape.getElement(sub)
    return e.CenterOfMass if sub.startswith("Face") else e.valueAt((e.FirstParameter + e.LastParameter) / 2)


def md_hover(q, mod=QtCore.Qt.NoModifier):
    """echte Mausbewegung (QTest.mouseMove ohne Taste setzt nur den Cursor)"""
    vp = md_view().viewport()
    for r in (q - QtCore.QPoint(1, 1), q):
        QtWidgets.QApplication.sendEvent(vp, QtGui.QMouseEvent(QtCore.QEvent.MouseMove, QtCore.QPointF(r), QtCore.QPointF(vp.mapToGlobal(r)),
                                                               QtCore.Qt.NoButton, QtCore.Qt.NoButton, mod))


def md_pick(get, sub=None, add=False, at=None):
    """Echter Klick in die Ansicht (add: Strg+Klick) mit Kreis: nur so zeigt MyCAD die Auswahl farbig. get/sub: Objekt
    bzw. Element oder Funktionen, die es liefern (die Objekte entstehen erst im Ablauf); at: Stelle (3D)"""
    def fn():
        o = get() if callable(get) else st[get]
        s = sub(o) if callable(sub) else (sub or "")
        p = at(o) if at else md_where(o, s)
        q = md_screen(p)
        mod = QtCore.Qt.ControlModifier if add else QtCore.Qt.NoModifier
        md_ring_at(p)
        if not add:
            Gui.Selection.clearSelection()
        md_hover(q, mod)
        QtTest.QTest.mouseClick(md_view().viewport(), QtCore.Qt.LeftButton, mod, q)
        Gui.ActiveDocument.ActiveView.redraw()
        got = [(x.ObjectName, x.SubElementNames) for x in Gui.Selection.getSelectionEx()]
        if not any(n == o.Name and (not s or s in subs) for n, subs in got):
            L("  pick missed %s %s: %s" % (o.Name, s, got))
    step("pick", fn)


def md_click(w):
    """echter Klick auf ein Glass-Widget im aktiven Fenster, mit Kreis"""
    top_ = w
    while top_.parentWidget():
        top_ = top_.parentWidget()
    pt = QtCore.QPointF(w.mapTo(top_, w.rect().center()))
    q = md_view().mapFromScene(top_.graphicsProxyWidget().mapToScene(pt))
    record_click(md_view().viewport().mapToGlobal(q))
    QtTest.QTest.mouseClick(md_view().viewport(), QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, q)


def md_tree(label, add=False):
    """Eintrag im Browser links anklicken (ganzer Körper, Ebene), mit Kreis"""
    def fn():
        tree = visible(QtWidgets.QTreeWidget)[0]
        def find():  # im aktiven Design (das letzte); nach dem Aufklappen neu suchen, der Browser baut sich dabei neu
            return tree.findItems(label, QtCore.Qt.MatchExactly | QtCore.Qt.MatchRecursive)[-1]
        parent = find().parent()
        while parent:  # nur den Weg dorthin aufklappen, der Rest bleibt wie er ist
            parent.setExpanded(True)
            parent = parent.parent()
        QtWidgets.QApplication.processEvents()
        item = find()
        rect = tree.visualItemRect(item)
        top_ = tree
        while top_.parentWidget():
            top_ = top_.parentWidget()
        proxy = top_.graphicsProxyWidget(); harness._keep.append(proxy)
        pt = tree.viewport().mapTo(top_, QtCore.QPoint(rect.left() + 40, rect.center().y()))
        q = md_view().mapFromScene(proxy.mapToScene(QtCore.QPointF(pt)))
        record_click(md_view().viewport().mapToGlobal(q))
        mod = QtCore.Qt.ControlModifier if add else QtCore.Qt.NoModifier
        QtTest.QTest.mouseClick(md_view().viewport(), QtCore.Qt.LeftButton, mod, q)
        L("  tree %s: %s" % (label, [(x.ObjectName, x.SubElementNames) for x in Gui.Selection.getSelectionEx()]))
    step("tree " + label, fn)


def md_use(cmd):
    """Werkzeug über die Toolbar; liegt es im Dropdown eines Knopfs (Drücken/Ziehen ▾ → Fläche ersetzen): Kreis auf
    dem Pfeil, danach zeigt der Knopf die gewählte Variante wie nach der Wahl im Menü"""
    def fn():
        for b in visible(QtWidgets.QToolButton):
            names = str(b.property("command")).split("|")
            if b.objectName() == "GlassButton" and cmd in names[1:] and b.menu():
                acts = b.menu().actions()
                if len(acts) == len(names):
                    # wie von Hand: Kreis auf dem Pfeil, das Menü geht auf, der Eintrag leuchtet, dann gewählt
                    md_ring(b, b.width() - 6)
                    menu, act = b.menu(), acts[names.index(cmd)]
                    menu.popup(b.mapToGlobal(QtCore.QPoint(0, b.height())))
                    QtCore.QTimer.singleShot(500, lambda: menu.setActiveAction(act))
                    QtCore.QTimer.singleShot(1300, lambda: (menu.hide(), act.trigger()))
                    return
        use(cmd)
    step(cmd, fn)
    wait(2)  # Menü, dann gleitet das Panel herein: erst dann sind seine Felder sichtbar


def md_later(make, n, ms=90):
    """make() liefert Aktionen, die im Abstand ms nacheinander laufen (Tippen, Ziehen); wartet mit, bis alle durch sind"""
    step("animate", lambda: [QtCore.QTimer.singleShot((i + 1) * ms, a) for i, a in enumerate(make())])
    wait(max(0, math.ceil(n * ms / 900.0)))


def md_box(label):
    """Eingabefeld neben label im Panel"""
    w = field(label)
    return w.lineEdit() if hasattr(w, "lineEdit") else w


def md_type(label, text, ms=110):
    """Feld anklicken (Kreis), alles markieren, Taste für Taste tippen: die Vorschau folgt"""
    def make():
        w = md_box(label)
        md_ring(field(label))
        # Cursor blinkt nicht: sonst ist jedes Bild anders und der Clip zieht sich
        acts = [lambda: (QtWidgets.QApplication.setCursorFlashTime(0), w.setFocus(), w.selectAll())]
        # zuletzt das Feld verlassen (wie Tab): es zeigt den Wert dann mit Einheit ("5.00 mm"), bevor OK kommt
        return acts + [lambda c=c: QtTest.QTest.keyClicks(w, c) for c in text] + [md_leave_field]
    md_later(make, len(text) + 2, ms)


def md_leave_field():
    w = QtWidgets.QApplication.focusWidget()
    if w:
        w.clearFocus()


def md_choose(label, text):
    """Auswahlfeld neben label auf text stellen (Kreis auf dem Feld)"""
    def fn():
        box = field(label)
        md_ring(box)
        box.setCurrentIndex(box.findText(text))
    step("choose " + text, fn)


def md_ok():
    def fn():
        vp = md_view().viewport()  # Maus weg vom Modell, wie auf dem Weg zum OK: sonst bleibt die Vorauswahl stehen
        md_hover(QtCore.QPoint(int(vp.width() * 0.35), int(vp.height() * 0.85)))
        b = [b for b in visible(QtWidgets.QPushButton) if b.text().replace("&", "") == "OK"]
        if b:
            md_ring(b[0])
        accept()
    step("ok", fn)
    wait()


_md_caps = []


def md_key(text, ms=1400):
    """Tastendruck im Clip zeigen: Schild unten in der Mitte (der Clip enthält keine Tastatur)"""
    for old in _md_caps:
        old.hide()
    lab = QtWidgets.QLabel(text, mw)
    lab.setStyleSheet("QLabel { background: rgba(29, 29, 31, 0.86); color: #FFFFFF; border-radius: 20px;"
                      " padding: 8px 20px; font-size: 22px; font-weight: 600; }")
    lab.adjustSize()
    left = 306  # so viel schneidet die Aufnahme links ab
    lab.move(left + (mw.width() - left - lab.width()) // 2, mw.height() - 170)
    lab.show()
    lab.raise_()
    _md_caps.append(lab)
    harness._keep.append(lab)
    QtCore.QTimer.singleShot(ms, lab.hide)


def md_frame(left=0.0, size=1.5, view_="iso", include=()):
    """Kamera ohne Einpass-Animation: Blick schräg von vorn rechts oben auf alle Körper, Höhe size × Diagonale, um left
    der Bildbreite nach links gerückt, damit das Panel rechts nichts verdeckt"""
    def fn():
        from pivy import coin
        bb = App.BoundBox()
        for o in doc().Objects:
            if o.TypeId == "Design::Body" and o.Visibility:
                bb.add(o.Shape.BoundBox)
        for p in include:  # Platz für das, was erst noch entsteht (Ziel einer Verschiebung, Extrusion)
            bb.add(p)
        v = Gui.ActiveDocument.ActiveView
        cam = v.getCameraNode()
        if view_ == "high":  # steiler als iso: auch die Kanten hinten und links sind zu sehen
            z = V(1, -1, 2.4).normalize(); x = V(0, 0, 1).cross(z).normalize(); y = z.cross(x)
            rot = coin.SbRotation(*App.Rotation(App.Matrix(x.x, y.x, z.x, 0, x.y, y.y, z.y, 0, x.z, y.z, z.z, 0, 0, 0, 0, 1)).Q)
        else:
            rot = {"iso": coin.SbRotation(0.424708, 0.17592, 0.339851, 0.820473), "front": coin.SbRotation(coin.SbVec3f(1, 0, 0), math.pi / 2)}[view_]
        cam.orientation.setValue(rot)
        vp = md_view().viewport()
        h = size * bb.DiagonalLength
        w = h * vp.width() / max(1, vp.height())
        c = coin.SbVec3f(bb.Center.x, bb.Center.y, bb.Center.z)
        back = rot.multVec(coin.SbVec3f(0, 0, 1))
        right = rot.multVec(coin.SbVec3f(1, 0, 0))
        cam.position.setValue(c + back * float(4 * bb.DiagonalLength) + right * float(left * w))
        cam.focalDistance.setValue(4 * bb.DiagonalLength)
        if hasattr(cam, "height"):
            cam.height.setValue(h)
    return fn


def md_final(size=1.3, view_="iso"):
    """Schlussbild: Ergebnis groß in der Mitte des Clips. ViewFit (shot in help_images) mittet im ganzen Fenster, der Clip
    lässt links die Seitenleiste weg (306 von 1500 px): dort stünde das Modell zu weit links"""
    step("final", lambda: (Gui.Selection.clearSelection(), md_frame(-0.1 * harness._rec.get("left", 306) / 306, size, view_)()))


def md_check(name):
    step("check", lambda: L("  %s: errors=%s volumes=%s" % (name, errors(), volumes())))


def md_dump(cmd):
    if os.environ.get("HELP_DUMP"):
        step("dump", lambda: dump_dialog(cmd))


def md_body(key, make, left=0.0, size=1.5, include=()):
    """Körper anlegen und Kamera einrichten in einem Schritt (der Clip beginnt mit dem fertigen Aufbau)"""
    def fn():
        r = make()
        if key:
            st[key] = r
        md_frame(left, size, include=include)()
    step("setup", fn)
    wait()
    # der Clip beginnt erst, wenn das Modell dasteht (kein leeres Gitter, kein Kamerasprung)
    step("clip starts", lambda: harness._rec and (harness._rec["frames"].clear(), harness._record_frame()))


def md_face(pred):
    """Fläche eines Körpers nach Lage: pred(Mittelpunkt, Normale)"""
    def f(b):
        for i, face in enumerate(b.Shape.Faces):
            if face.Surface.TypeId == "Part::GeomPlane" and pred(face.CenterOfMass, normal(face)):
                return "Face%d" % (i + 1)
        raise RuntimeError("no face")
    return f


FRONT = md_face(lambda c, n: n.y < -0.9)
RIGHT = md_face(lambda c, n: n.x > 0.9)


# --- Drücken/Ziehen -------------------------------------------------------------------------------------------------
def md_drag(base, direction, d0, d1, n=12, ms=110):
    """Griff des Ziehpfeils von Abstand d0 nach d1 ziehen, in kleinen Schritten wie eine Hand. Erst darüberfahren (der
    Griff leuchtet auf), dann ziehen; jeder Schritt rechnet die Vorschau neu, darum nicht zu schnell"""
    step("hover", lambda: md_hover(md_screen(base + direction * d0)))

    def make():
        vp = md_view().viewport()
        a, b = md_screen(base + direction * d0), md_screen(base + direction * d1)
        md_ring_at(base + direction * d0)

        def move(q):
            QtWidgets.QApplication.sendEvent(vp, QtGui.QMouseEvent(QtCore.QEvent.MouseMove, QtCore.QPointF(q), QtCore.QPointF(vp.mapToGlobal(q)),
                                                                   QtCore.Qt.NoButton, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier))
        acts = [lambda: md_hover(a), lambda: QtTest.QTest.mousePress(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, a)]
        acts += [lambda k=k: move(a + (b - a) * (k / n)) for k in range(1, n + 1)]
        return acts + [lambda: QtTest.QTest.mouseRelease(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, b),
                       lambda: L("  drag: distance %s" % [o.Distance for o in doc().Objects if hasattr(o, "Distance")][-1:])]
    md_later(make, n + 4, ms)


def md_fresh(left=306):
    """Aufnahme neu beginnen: der Aufbau mit echten Werkzeugen davor gehört nicht in den Clip"""
    def fn():
        harness._rec["timer"].stop()
        record_start(harness._rec["path"], left=left)
    step("fresh", fn)


def md_presspull():
    md_body("b", lambda: box(0, 0, 60, 40, 20), size=1.8)
    md_pick("b", top)
    md_use("Design_PressPull")
    md_drag(V(30, 20, 20), V(0, 0, 1), 5, 25)
    md_type("Distance", "15")
    md_dump("Design_PressPull")
    md_ok()
    md_check("Design_PressPull")


# --- Fläche ersetzen, teilen, entfernen -----------------------------------------------------------------------------
def md_replace():
    def make():  # der niedrige vorn rechts, damit seine Oberseite frei liegt
        st["t"] = box(0, 0, 40, 40, 32, name="Taller")
        st["b"] = box(50, 0, 90, 40, 20, name="Box")
    md_body(None, make, left=-0.1)
    md_pick("b", top)
    md_pick("t", top, add=True)
    md_use("Design_ReplaceFace")
    wait(2)
    md_check("Design_ReplaceFace")


def md_split_face():
    def make():
        st["b"] = box(0, 0, 60, 40, 20)
        st["l"] = sketch([Part.LineSegment(V(30, -8, 0), V(30, 48, 0))], z=20, name="SplitLine")[0]
    md_body(None, make)
    md_pick("b", top, at=lambda o: V(15, 20, 20))
    md_pick("l", "Edge1", add=True, at=lambda o: V(30, 46, 20))  # das Stück hinter dem Quader: vorn läge es über seiner Vorderseite
    md_use("Design_SplitFace")
    wait(2)
    md_check("Design_SplitFace")
    # wozu: nur die linke Hälfte herausziehen
    md_pick("b", md_face(lambda c, n: n.z > 0.9 and c.x < 30))
    md_use("Design_PressPull")
    md_type("Distance", "10")
    md_ok()


def md_remove_face():
    def make():
        b = make_body(rect(0, 0, 60, 40) + [circle(30, 20, 9)], 0, 12, "Plate")
        ext = b.Tip  # nur die Ringfläche: Platte mit Bohrung
        prof = ext.Profile[0]
        ext.Profile = (prof, ["Face%d" % (1 + max(range(len(prof.Shape.Faces)), key=lambda k: len(prof.Shape.Faces[k].Wires)))])
        doc().recompute()
        return b
    md_body("b", make, size=1.2)
    md_fresh()  # ohne den Aufbau (Platte erst ohne, dann mit Bohrung)
    wait()
    md_pick("b", lambda b: cylindrical(b)[0], at=lambda b: V(30 - 9 * math.cos(math.radians(45)), 20 + 9 * math.sin(math.radians(45)), 9))
    md_use("Design_RemoveFace")
    md_dump("Design_RemoveFace")
    md_ok()
    md_check("Design_RemoveFace")


# --- Fase, Wandstärke, Formschräge ----------------------------------------------------------------------------------
def md_dressup(cmd, faces_of, label, value, adds=()):
    md_body("b", lambda: box(0, 0, 60, 40, 20))
    md_pick("b", faces_of)
    for f in adds:
        md_pick("b", f, add=True)
    wait()
    md_use(cmd)
    md_type(label, value)
    md_dump(cmd)
    md_ok()
    md_check(cmd)


# --- Kombinieren, Körper teilen -------------------------------------------------------------------------------------
def md_combine():
    def make():
        st["a"] = box(0, 0, 60, 40, 20)
        st["c"] = make_body([circle(30, 20, 12)], -5, 30, "Cylinder")
    md_body(None, make)
    md_pick("a", top, at=lambda o: V(10, 8, 20))
    md_pick("c", lambda c: top(c), add=True)
    md_use("Design_Combine")
    md_choose("Operation", "Cut")
    md_dump("Design_Combine")
    md_ok()
    md_check("Design_Combine")


def md_split_lift():
    """nach dem Teilen: Ebene aus, oberes Stück etwas anheben, damit man die zwei Teile sieht"""
    for o in doc().Objects:
        if "Plane" in o.TypeId and o.TypeId != "App::Plane":
            o.Visibility = False
    b = max([o for o in doc().Objects if o.TypeId == "Design::Body"], key=lambda o: o.Shape.BoundBox.ZMin)
    z = b.Shape.BoundBox.ZMin
    b.Placement.Base.z += 8
    doc().recompute()
    L("  lift %s: zmin %.1f -> %.1f" % (b.Label, z, b.Shape.BoundBox.ZMin))


def md_split_body():
    """den Körper anklicken (eine Fläche reicht), dann die Ebene in der Ansicht"""
    step("setup", lambda: st.__setitem__("b", box(-30, -20, 30, 20, 20)))
    step("plane", lambda: select(st["b"], top(st["b"])))
    step("offset", lambda: Gui.runCommand("Design_OffsetPlane"))
    wait()
    step("-10", lambda: type_into(0, "-10"))
    wait()
    step("ok", accept)
    wait()
    step("frame", lambda: (Gui.Selection.clearSelection(), md_frame(0.0, 1.3)()))
    md_fresh()
    wait()
    md_pick("b")
    md_pick(lambda: [o for o in doc().Objects if "Plane" in o.TypeId and o.TypeId != "App::Plane"][-1], add=True,
            at=lambda o: V(-28, -24, 10))
    md_use("Design_SplitBody")
    wait(2)
    md_check("Design_SplitBody")
    step("lift", md_split_lift)
    wait()


# --- Verschieben, Ausrichten, Skalieren -----------------------------------------------------------------------------
def md_move():
    def make():  # Geist am Ausgangsort zum Vergleich: durchscheinend, nicht anklickbar, knapp kleiner (kein Flimmern)
        g = box(0.2, 0.2, 39.8, 19.8, 9.6, z=0.2, name="Original")
        g.ViewObject.Transparency = 75
        g.ViewObject.Selectable = False
        return box(0, 0, 40, 20, 10)
    md_body("b", make, size=1.4, include=(V(85, 45, 10),))
    md_pick("b", top)
    md_use("Design_Move")
    md_type("X distance", "40")
    md_type("Y distance", "20")
    md_choose("Rotate around", "Z axis")
    md_type("Angle", "30")
    wait()
    md_dump("Design_Move")
    md_ok()
    md_check("Design_Move")


def md_align():
    def make():
        st["a"] = box(0, 0, 60, 40, 20, name="Base")
        st["b"] = box(80, 5, 110, 35, 10, name="Lid")
    md_body(None, make)
    md_pick("b", top)
    md_pick("a", top, add=True)
    md_use("Design_Align")
    md_dump("Design_Align")
    md_ok()
    md_check("Design_Align")


def md_scale():
    def make():
        st["r"] = box(-60, 0, -40, 20, 20, name="Reference")
        st["b"] = box(0, 0, 20, 20, 20, name="Box")
    md_body(None, make, size=1.4, include=(V(40, 40, 40), V(10, 10, -10)))
    md_pick("b", top)
    md_use("Design_Scale")
    md_type("Factor", "2")
    md_choose("Center", "Origin")
    md_dump("Design_Scale")
    md_ok()
    md_check("Design_Scale")


# --- Löschen --------------------------------------------------------------------------------------------------------
def md_delete():
    """Rundung mitten in der Zeitleiste löschen: das Muster danach bleibt und rechnet ohne sie weiter"""
    def vertical(b):
        return ["Edge%d" % (i + 1) for i, e in enumerate(b.Shape.Edges) if abs(e.Vertexes[0].Point.z - e.Vertexes[1].Point.z) > 1]
    step("setup", lambda: st.__setitem__("b", box(0, 0, 20, 20, 15)))
    step("edges", lambda: select(st["b"], *vertical(st["b"])))
    step("fillet", lambda: Gui.runCommand("Design_Fillet"))
    wait()
    step("r", lambda: type_into(0, "6"))
    wait()
    step("ok", accept)
    wait()
    step("body", lambda: select(st["b"]))
    step("pattern", lambda: Gui.runCommand("Design_Pattern"))
    wait()
    step("count", lambda: (type_field("Count", "3"), type_field("Spacing", "30")))
    wait()
    step("ok", accept)
    wait()
    step("frame", lambda: (Gui.Selection.clearSelection(), md_frame(-0.1, 1.2)()))
    md_fresh()
    wait()
    step("pick step", lambda: md_click([e for e in visible(QtWidgets.QToolButton)
                                        if e.property("timelineIndex") is not None and e.accessibleName().startswith("Fillet")][0]))
    wait()
    step("Del", lambda: (md_key("Del"), Gui.runCommand("Design_Delete")))  # Taste Entf; unter Xvfb kommt die Taste nicht an
    wait(2)
    md_check("Design_Delete")


def md_extrude():
    """Rohr: nur den Ring zwischen den beiden Kreisen anklicken, Extrudieren, Länge tippen (die Vorschau wächst mit)"""
    md_body("sp", lambda: sketch([circle(0, 0, 20), circle(0, 0, 12)])[1], size=1.6, include=(V(-20, -20, 0), V(20, 20, 30)))
    md_pick("sp", ring_face, at=lambda o: V(11.3, -11.3, 0))
    md_use("Design_Extrude")
    md_type("Distance", "30")
    md_dump("Design_Extrude")
    md_ok()
    md_check("Design_Extrude")


def md_scenario(article, build, view_="iso", final=True):
    """final=False: die Kamera bleibt bis zum Schluss, wie sie ist (kein Sprung im letzten Bild)"""
    scenario(article, lambda: (build(), final and md_final(view_=view_)), view="none", fixed=True)


md_scenario("Design_Extrude", md_extrude)
md_scenario("Design_PressPull", md_presspull, final=False)
md_scenario("Design_ReplaceFace", md_replace)
md_scenario("Design_SplitFace", md_split_face)
md_scenario("Design_RemoveFace", md_remove_face)
md_scenario("Design_Fillet", lambda: md_dressup("Design_Fillet", top, "Radius", "5"), view_="high")
md_scenario("Design_Chamfer", lambda: md_dressup("Design_Chamfer", top, "Distance", "4"), view_="high")
md_scenario("Design_Shell", lambda: md_dressup("Design_Shell", top, "Thickness", "3"))
md_scenario("Design_Draft", lambda: md_dressup("Design_Draft", FRONT, "Angle", "10", adds=(RIGHT,)))
md_scenario("Design_Combine", md_combine)
md_scenario("Design_SplitBody", md_split_body)
md_scenario("Design_Move", md_move)
md_scenario("Design_Align", md_align)
md_scenario("Design_Scale", md_scale)
md_scenario("Design_Delete", md_delete)
