# SPDX-License-Identifier: LGPL-2.1-or-later
"""Erklär-Clips Konstruieren, Zusammenfügen, Prüfen und Darstellung (läuft in tools/help_images.py, alles von dort ist da).
Auswählen mit echten Klicks in die 3D-Ansicht (Kreis im Clip), Varianten über das Menü am ▾ des Knopfs."""


# --- Klicks in der 3D-Ansicht ---------------------------------------------------------------------------------------
def ci_vp():
    """Viewport der aktiven 3D-Ansicht (view() aus harness nimmt die erste sichtbare QGraphicsView, nicht immer diese)"""
    vp = Gui.ActiveDocument.ActiveView.graphicsView().viewport()
    harness._keep.append(vp)
    return vp


def ci_at(p):
    """3D-Punkt -> Punkt im Viewport (Coin zählt y von unten)"""
    vp = ci_vp(); px, py = Gui.ActiveDocument.ActiveView.getPointOnViewport(V(*map(float, p)))
    dpr = vp.devicePixelRatioF()
    return QtCore.QPoint(int(px / dpr), int(vp.height() - py / dpr))


def ci_hit(p, ctrl=False):
    """wie von Hand: Maus hin (Vorauswahl), klicken; mit Strg kommt es zur Auswahl dazu"""
    vp = ci_vp(); q = ci_at(p)
    for r in (q - QtCore.QPoint(1, 1), q):
        QtWidgets.QApplication.sendEvent(vp, QtGui.QMouseEvent(QtCore.QEvent.MouseMove, QtCore.QPointF(r), QtCore.QPointF(vp.mapToGlobal(r)),
                                                               QtCore.Qt.NoButton, QtCore.Qt.NoButton, QtCore.Qt.NoModifier))
    record_click(vp.mapToGlobal(q))
    QtTest.QTest.mouseClick(vp, QtCore.Qt.LeftButton, QtCore.Qt.ControlModifier if ctrl else QtCore.Qt.NoModifier, q)


def ci_picks(*points):
    """erster Punkt neu wählen, weitere mit Strg dazu, je ein Schritt"""
    for i, p in enumerate(points):
        step("pick", lambda p=p, i=i: ci_hit(p, ctrl=i > 0))


def ci_fit():
    Gui.SendMsgToActiveView("ViewFit")


def ci_iso_fit():
    Gui.ActiveDocument.ActiveView.viewIsometric(); ci_fit()


def ci_ring_at(w, dx=0.0, dy=0.0):
    """Kreis auf einem Glas-Widget (dx/dy: Anteil der halben Breite/Höhe vom Mittelpunkt)"""
    p = harness._pos(w)
    p = p.toPoint() if hasattr(p, "toPoint") else p
    record_click(view().viewport().mapToGlobal(p + QtCore.QPoint(int(dx * w.width() / 2), int(dy * w.height() / 2))))


# --- Varianten-Menü (Knopf mit ▾): harness._record_frame nimmt das Menü (eigenes Fenster) mit ins Bild ---------
def ci_split(cmd):
    return [b for b in visible(QtWidgets.QToolButton)
            if b.objectName() == "GlassButton" and cmd in str(b.property("command")).split("|")][0]


def ci_variant(cmd):
    """Pfeil ▾ am Knopf anklicken, Menü zeigen, dann den Eintrag wählen (zwei Schritte wie von Hand)"""
    def open_menu():
        b = ci_split(cmd)
        ci_ring_at(b, 0, 0.8)
        p = harness._pos(b); p = p.toPoint() if hasattr(p, "toPoint") else p
        b.menu().popup(view().viewport().mapToGlobal(p + QtCore.QPoint(-b.width() // 2, b.height() // 2 + 4)))

    def choose():
        b = ci_split(cmd); m = b.menu()
        a = m.actions()[str(b.property("command")).split("|").index(cmd)]
        record_click(m.mapToGlobal(m.actionGeometry(a).center()))
        m.setActiveAction(a)
        QtCore.QTimer.singleShot(350, lambda: (m.hide(), a.trigger()))
    step("menu", open_menu)
    step(cmd, choose)


def ci_press(w):
    """Knopf im Panel: Kreis darauf und auslösen (ein Klick auf die Bildschirmstelle kommt im Panel nicht immer an)"""
    ci_ring_at(w); w.click()


def ci_ok():
    """OK oben im Panel: Kreis darauf, kurz danach auslösen (sonst ist das Panel schon weg, wenn der Kreis kommt)"""
    ci_ring_at([b for b in visible(QtWidgets.QPushButton) if b.text().replace("&", "") == "OK"][0])
    QtCore.QTimer.singleShot(300, accept)


def ci_tool(cmd, *setup):
    """wie feature(), aber Varianten über das Menü"""
    step(cmd, lambda: use(cmd))
    wait()
    for s in setup:
        step("set", s)
    wait()
    step("ok", ci_ok)
    wait()


def ci_later(fns, ms=120):
    """Teilschritte nacheinander im Abstand ms (z. B. Kamerafahrt, Ziehen) innerhalb eines Schritts"""
    for k, fn in enumerate(fns):
        QtCore.QTimer.singleShot(ms * (k + 1), fn)


# --- Kamera ---------------------------------------------------------------------------------------------------------
def ci_cam():
    from pivy import coin
    return coin, Gui.ActiveDocument.ActiveView.getCameraNode()


def ci_pan(px, py=0):
    """Ansicht um px/py Bildpunkte verschieben (Modell wandert nach rechts/oben)"""
    coin, cam = ci_cam()
    h = cam.height.getValue() / ci_vp().height()
    rot = cam.orientation.getValue()
    right, up = rot.multVec(coin.SbVec3f(1, 0, 0)), rot.multVec(coin.SbVec3f(0, 1, 0))
    p = cam.position.getValue()
    cam.position.setValue(p - right * (px * h) - up * (py * h))


def ci_zoom(f):
    coin, cam = ci_cam()
    cam.height.setValue(cam.height.getValue() * f)


def ci_look(d):
    """Kamera blickt aus Richtung d (vom Modell zur Kamera) auf das Modell, z bleibt oben"""
    z = V(*map(float, d)).normalize(); x = V(0.0, 0.0, 1.0).cross(z).normalize(); y = z.cross(x)
    m = App.Matrix(x.x, y.x, z.x, 0, x.y, y.y, z.y, 0, x.z, y.z, z.z, 0, 0, 0, 0, 1)
    Gui.ActiveDocument.ActiveView.setCameraOrientation(App.Rotation(m))


def ci_turn(a, b, n=8, ms=110):
    """Kamera in n Schritten von Richtung a nach b drehen (wie mit der Maus)"""
    ci_later([lambda t=(k + 1) / n: ci_look([a[i] + (b[i] - a[i]) * t for i in range(3)]) for k in range(n)], ms)


CI_ISO, CI_LOW = (1, -1, 1), (1, -1, -0.45)  # von schräg oben / von schräg unten


def ci_frame(scale=1.3, dx=90, d=None, dy=0):
    """Iso (oder Richtung d), einpassen, etwas Luft; dx schiebt das Modell in die Mitte des Clips (links fehlt die Seitenleiste)"""
    Gui.ActiveDocument.ActiveView.viewIsometric() if d is None else ci_look(d)
    ci_fit(); ci_zoom(scale); ci_pan(dx, dy)


def ci_final(scale=1.3, dx=90, dy=0, wait_after=1):
    step("final", lambda: (Gui.Selection.clearSelection(), ci_frame(scale, dx, None, dy)))
    wait(wait_after)


def ci_keep_selection():
    """Die Endpose von scenario() hebt die Auswahl auf; hier kommt sie gleich danach zurück (Messwerte, Hervorhebung)"""
    sel = [(x.Object, x.SubElementNames) for x in Gui.Selection.getSelectionEx()]

    class Back:
        def clearSelection(self, doc):
            Gui.Selection.removeObserver(self)
            QtCore.QTimer.singleShot(0, lambda: [Gui.Selection.addSelection(o, list(s)) if s else Gui.Selection.addSelection(o) for o, s in sel])
    obs = Back(); harness._keep.append(obs)
    Gui.Selection.addObserver(obs)


# --- Modelle --------------------------------------------------------------------------------------------------------
def ci_body_xz(pts, depth, name):
    """Körper aus einem Profil in der XZ-Ebene (x, z), nach hinten (y+) extrudiert"""
    d = doc(); root = [o for o in d.Objects if o.TypeId == "App::Part"][0]
    sk = d.addObject("Sketcher::SketchObject", "Sketch")
    sk.Placement = App.Placement(V(0, depth, 0), App.Rotation(V(1, 0, 0), 90))
    for i in range(len(pts)):
        sk.addGeometry(Part.LineSegment(V(*map(float, pts[i]), 0), V(*map(float, pts[(i + 1) % len(pts)]), 0)))
    d.getObject("Sketches").addObject(sk)
    prof = d.addObject("Design::Profiles", "Profiles"); prof.Sketch = sk; root.addObject(prof)
    ext = d.addObject("Design::Extrude", "Extrude"); ext.Profile = (prof, []); ext.Distance = depth; root.addObject(ext)
    b = d.addObject("Design::Body", "Body"); b.Label = name; ext.Bodies = [b]; b.Tip = ext
    d.getObject("Bodies").addObject(b)
    sk.Visibility = False; prof.Visibility = False
    d.recompute(); return b


def ci_design():
    sys.path.append("/workspace/tests/design")
    import design
    return design


CI_STEP = [(-30, 0), (30, 0), (30, 10), (0, 10), (0, 20), (-30, 20)]  # Stufe: oben z=20 links, z=10 rechts


def ci_model(fn, scale=1.3, dx=90, d=None):
    """Modell bauen und einpassen; der Clip beginnt erst, wenn es dasteht (kein leeres Gitter, keine halbe Skizze)"""
    step("model", lambda: (fn(), ci_frame(scale, dx, d)))
    wait()
    step("clip starts", lambda: (harness._rec["frames"].clear(), harness._record_frame()))


CI_BOX = lambda: box(-30, -20, 30, 20, 20)
CI_CYL = lambda: make_body([circle(0, 0, 12)], 0, 30, "Cylinder")
CI_C45 = (12 * math.cos(-math.pi / 4), 12 * math.sin(-math.pi / 4))  # Zylinderseite zum Betrachter (iso)


def ci_scenario(article, build, final=(1.3, 90)):
    """eigene Endpose (Seitenleiste fehlt links im Clip); scenario() hebt danach nur noch die Auswahl auf"""
    def full():
        build()
        if final:
            ci_final(*final)
    scenario(article, full, view="none", fixed=True)


# --- Konstruieren ---------------------------------------------------------------------------------------------------
def ci_offset_plane():
    ci_model(CI_BOX, 1.7)
    ci_picks((0, 0, 20))
    ci_tool("Design_OffsetPlane", lambda: type_into(0, "15"))


def ci_angle_plane():
    ci_model(CI_BOX, 1.7)
    ci_picks((0, -20, 20))
    ci_variant("Design_AnglePlane")
    wait()
    step("set", lambda: type_into(0, "-30"))
    wait()
    step("ok", ci_ok)
    wait()


def ci_midplane():
    ci_model(lambda: ci_body_xz(CI_STEP, 40, "Step"), 1.6)
    ci_picks((-15, 20, 20), (15, 20, 10))
    ci_variant("Design_Midplane")
    wait(2)


def ci_plane3():
    ci_model(CI_BOX, 1.7)
    ci_picks((-30, -20, 20), (30, 20, 20), (30, -20, 0))
    ci_variant("Design_Plane")
    wait(2)


def ci_axis():
    ci_model(CI_CYL, 1.6)
    ci_picks((CI_C45[0], CI_C45[1], 15))
    ci_variant("Design_Axis")
    wait(2)
    ci_final(1.6)
    step("show axis", lambda: (ci_hit((0, 0, -14)), ci_keep_selection()))  # die Achse ragt unten heraus: anklicken hebt sie hervor


def ci_point():
    ci_model(CI_CYL, 1.6)
    ci_picks((CI_C45[0], CI_C45[1], 30))
    ci_variant("Design_Point")
    wait(2)
    ci_final(1.1, 90, -40)
    step("show point", lambda: (ci_hit((0, 0, 30)), ci_keep_selection()))  # der Punkt ist klein: anklicken hebt ihn hervor


# --- Zusammenfügen --------------------------------------------------------------------------------------------------
def ci_comp_body(rect_xy, h, at, label):
    """Körper in einer neuen Komponente, die bei at liegt"""
    import Design
    d = doc()
    comp = Design.newComponent(Design.root(d))
    comp.Placement = App.Placement(V(*map(float, at)), App.Rotation())
    sk = Design.newSketch(comp)
    for g in rect(*rect_xy):
        sk.addGeometry(g)
    d.recompute()
    prof = [o for o in sk.InList if o.TypeId == "Design::Profiles"][0]
    f = d.addObject("Design::Extrude", "Extrude"); comp.addObject(f); Design.addToTimeline(f)
    f.Profile = (prof, ["Face1"]); f.Distance = h
    b = Design.newBody(f); b.Label = label
    sk.Visibility = False
    d.recompute()
    return b


def ci_joint():
    def build():
        box(-30, -20, 30, 20, 8, name="Base")
        ci_comp_body((-25, -5, 25, 5), 6, (80, 0, 0), "Arm")
    ci_model(build, 1.15, 110)
    ci_picks((80, 0, 6), (0, 0, 8))  # Oberseite des Arms (bewegt sich), dann wohin: Oberseite der Platte
    step("Design_Joint", lambda: use("Design_Joint"))
    wait(2)
    step("revolute", lambda: (ci_ring_at(field("Type")), field("Type").setCurrentIndex(field("Type").findText("Revolute"))))
    wait()

    def animate():
        b = [b for b in visible(QtWidgets.QPushButton) if b.text() == "Animate"][0]
        ci_ring_at(b); b.click()  # ein Klick auf die Bildschirmstelle schaltet den Knopf nicht um
        QtCore.QTimer.singleShot(2600, lambda: (ci_ring_at(b), b.click()))
    step("animate", animate)
    wait()
    step("ok", ci_ok)
    wait()


def ci_tree_item(label):
    t = [t for t in visible(QtWidgets.QTreeWidget)][0]
    its = t.findItems(label, QtCore.Qt.MatchStartsWith | QtCore.Qt.MatchRecursive)
    harness._keep.append(t)
    return t, its[-1]  # im neuen Design (das erste Design der Sitzung steht oben)


def ci_tree_show(label):
    """Teilbaum unter label im neuen Design ganz aufklappen"""
    t, it = ci_tree_item(label)
    t.expandRecursively(t.indexFromItem(it))


def ci_tree_click(label, double=False):
    t, it = ci_tree_item(label)
    vp = t.viewport(); c = t.visualItemRect(it).center()
    p = harness._pos(vp); p = p.toPoint() if hasattr(p, "toPoint") else p
    record_click(view().viewport().mapToGlobal(p + c - vp.rect().center()))
    (QtTest.QTest.mouseDClick if double else QtTest.QTest.mouseClick)(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, c)


def ci_wide():
    """ab hier mit Seitenleiste (Browser), rechts ohne den leeren Rand"""
    harness._rec["frames"].clear(); harness._rec["crop"] = (0, 1200)
    harness._record_frame()


def ci_new_component():
    step("wide", ci_wide)
    wait()
    step("Design_NewComponent", lambda: use("Design_NewComponent"))
    wait(2)
    def box_ok():  # Würfel mit den Vorgaben; das Panel rechts läge halb außerhalb des Ausschnitts, also gleich OK
        use("Design_Box")
        QtCore.QTimer.singleShot(500, ci_ok)
    step("Design_Box", box_ok)
    wait()
    step("fit", lambda: ci_frame(2.0, 100))
    step("open bodies", lambda: [ci_tree_item(n)[1].setExpanded(True) for n in ("Component", "Bodies0")])
    wait(2)
    step("double-click", lambda: ci_tree_click("Component", double=True))
    wait(2)


# --- Prüfen ---------------------------------------------------------------------------------------------------------
def ci_print_view():
    def build():
        dz = ci_design(); d = doc()
        _, b = dz.box(d, 20, 20, 20, at=(-10, -10))  # Hut: Fuß, darauf eine breite Platte (Überhang)
        dz.extrude(d, dz.sketch(d, dz.rect(-25, -25, 25, 25), App.Placement(V(0, 0, 20), App.Rotation())), 3, op="Join", bodies=[b])
        dz.extrude(d, dz.sketch(d, dz.rect(-0.3, -22, 0.3, -10)), 14, op="Join", bodies=[b])  # dünne Rippe vorn (0,6 mm)
        for o in d.Objects:
            if o.TypeId == "Sketcher::SketchObject":
                o.Visibility = False
    ci_model(build, 1.4, 40, CI_LOW)  # von unten: der Überhang ist die Unterseite der Platte
    step("Design_PrintView", lambda: use("Design_PrintView"))
    wait(3)
    step("turn up", lambda: ci_turn(CI_LOW, CI_ISO, 1))
    wait()
    ci_picks((0, 0, 23))  # die Oberseite der Platte soll aufs Bett
    step("bottom", lambda: ci_press([b for b in visible(QtWidgets.QPushButton) if b.text() == "Choose Bottom Face"][0]))
    wait(2)
    step("turn down", lambda: ci_turn(CI_ISO, CI_LOW, 1))
    wait(3)


def ci_measure():
    ci_model(lambda: ci_body_xz(CI_STEP, 40, "Step"), 1.3, -80)  # nach links: rechts öffnet sich das Panel
    step("Design_Measure", lambda: use("Design_Measure"))
    wait()
    ci_picks((-15, 20, 20))
    wait(2)
    step("pick", lambda: ci_hit((15, 20, 10), ctrl=True))
    wait(3)
    step("keep", ci_keep_selection)


def ci_section():
    def build():  # Block mit drei Bohrungen: ein Profil mit Löchern, nur die äußere Fläche extrudiert
        d = doc(); root = [o for o in d.Objects if o.TypeId == "App::Part"][0]
        _, prof = sketch(rect(-30, -20, 30, 20) + [circle(x, 0, r) for x, r in ((-16, 7), (2, 5), (17, 3))])
        ext = d.addObject("Design::Extrude", "Extrude"); ext.Profile = (prof, [ring_face(prof)]); ext.Distance = 20; root.addObject(ext)
        b = d.addObject("Design::Body", "Body"); b.Label = "Block"; ext.Bodies = [b]; b.Tip = ext
        d.getObject("Bodies").addObject(b)
        for o in d.Objects:
            if o.TypeId in ("Sketcher::SketchObject", "Design::Profiles"):
                o.Visibility = False
        d.recompute()
    ci_model(build, 1.5, 0)
    step("wide", ci_wide)  # die Ursprungsebene wählt man im Browser links
    wait()
    step("origin", lambda: ci_tree_show("Design"))
    wait()
    step("XZ", lambda: ci_tree_click("XZ"))  # XZ-Ebene: geht mitten durch die Bohrungen
    wait(2)
    step("Design_Section", lambda: use("Design_Section") if Gui.Selection.getSelection() else L("  exc: XZ not selected"))
    wait(3)


def ci_fit_all():
    ci_model(CI_BOX, 1.7, 90)

    def away():  # wie hineingezoomt und verschoben: das Modell ist halb aus dem Bild
        ci_later([lambda: (ci_zoom(0.72), ci_pan(-90, 40)) for _ in range(4)], 700)
    step("away", away)
    wait(4)

    def fit_all():  # erst der Kreis auf dem Knopf, dann springt die Ansicht
        ci_ring_at(button("Std_ViewFitAll"))
        QtCore.QTimer.singleShot(800, lambda: Gui.runCommand("Std_ViewFitAll"))
    step("Std_ViewFitAll", fit_all)
    wait(2)
    if os.environ.get("CI_KEYCHECK"):  # Prüfung der Tasten V, F (nicht im Clip gedacht)
        def keys():
            st["cam"] = Gui.ActiveDocument.ActiveView.getCamera()
            ci_zoom(0.4); ci_pan(-300)
            harness.activate()
            st["moved"] = Gui.ActiveDocument.ActiveView.getCamera()
            for k in (QtCore.Qt.Key_V, QtCore.Qt.Key_F):  # wie echte Eingabe: über das Fenster
                QtTest.QTest.keyClick(mw.windowHandle(), k)
        step("V F", keys)
        wait(2)
        step("V F?", lambda: L("  V,F: fitted=%s moved=%s dialog=%s" % (Gui.ActiveDocument.ActiveView.getCamera() == st["cam"],
                                                                         Gui.ActiveDocument.ActiveView.getCamera() != st["moved"],
                                                                         Gui.Control.activeDialog())))
        step("I", lambda: QtTest.QTest.keyClick(mw.windowHandle(), QtCore.Qt.Key_I))  # Gegenprobe: I öffnet Messen
        wait()
        step("I?", lambda: (L("  key I opens Measure: %s" % Gui.Control.activeDialog()), Gui.Control.closeDialog()))


def ci_appearance():
    def build():
        for i in range(3):
            box(i * 30 - 40, -10, i * 30 - 20, 10, 20, name="Part")
    ci_model(build, 1.3, 10)
    ci_picks((-30, 0, 20), (30, 0, 20))

    def tile(name):
        return [b for b in visible(QtWidgets.QToolButton) if b.accessibleName() == name][0]
    step("Design_Appearance", lambda: use("Design_Appearance"))
    wait(2)
    step("body", lambda: ci_press([b for b in visible(QtWidgets.QPushButton) if b.objectName() == "Segment" and b.text() == "Body"][0]))
    wait()
    step("blue", lambda: ci_press(tile("Sierra Blue")))
    wait(2)
    step("green", lambda: ci_press(tile("Alpine Green")))
    wait(2)
    step("ok", ci_ok)
    wait()


ci_scenario("Design_OffsetPlane", ci_offset_plane)
ci_scenario("Design_AnglePlane", ci_angle_plane)
ci_scenario("Design_Midplane", ci_midplane)
ci_scenario("Design_Plane", ci_plane3, final=(1.0, 90))
ci_scenario("Design_Axis", ci_axis, final=None)
ci_scenario("Design_Point", ci_point, final=None)
ci_scenario("Design_NewComponent", ci_new_component, final=None)
ci_scenario("Design_Joint", ci_joint, final=(1.7, 90))
ci_scenario("Design_PrintView", ci_print_view, final=None)
ci_scenario("Design_Measure", ci_measure, final=None)
ci_scenario("Design_Section", ci_section, final=None)
ci_scenario("Std_ViewFitAll", ci_fit_all, final=None)
ci_scenario("Design_Appearance", ci_appearance)
