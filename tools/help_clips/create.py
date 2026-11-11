# SPDX-License-Identifier: LGPL-2.1-or-later
# Erklär-Clips Bereich ERSTELLEN (und Passung): wird in help_images.py ausgeführt, nutzt dessen Helfer (step, wait, use …)


def cr_ring(w, x=None):
    """Kreis im Clip an Stelle x (Pixel von links im Widget, sonst Mitte) eines Glass-Widgets"""
    top = w
    while top.parentWidget():
        top = top.parentWidget()
    pt = QtCore.QPointF(w.mapTo(top, QtCore.QPoint(w.width() // 2 if x is None else x, w.height() // 2)))
    p = view().mapFromScene(top.graphicsProxyWidget().mapToScene(pt))
    record_click(view().viewport().mapToGlobal(p))


def cr_use_variant(cmd):
    """Werkzeug aus dem Dropdown eines Toolbar-Knopfs (Sweep ▾ → Loft): Kreis auf dem Pfeil, Knopf zeigt danach die
    gewählte Variante, wie nach der Wahl im Menü"""
    for b in visible(QtWidgets.QToolButton):
        names = str(b.property("command")).split("|")
        if b.objectName() == "GlassButton" and cmd in names and b.menu():
            acts = b.menu().actions()
            if len(acts) == len(names):
                cr_ring(b, b.width() - 6)
                QtCore.QTimer.singleShot(400, acts[names.index(cmd)].trigger)  # erst Kreis im Clip, dann Panel
                return
    cr_use(cmd)


def cr_use(cmd):
    """wie use(), aber erst Kreis, 0,4 s später der Befehl: sonst baut das Panel auf, bevor der Clip den Kreis zeigt"""
    try:
        cr_ring(button(cmd))
    except RuntimeError:
        pass
    QtCore.QTimer.singleShot(400, lambda: Gui.runCommand(cmd))


def cr_pick(label, text):
    """Auswahlfeld neben label auf text stellen, mit Kreis auf dem Feld"""
    box = field(label)
    cr_ring(box)
    box.setCurrentIndex(box.findText(text))


def cr_type_at(label, text):
    """Wert ins Feld neben label, als eine Eingabe (eine Neuberechnung): Tasten einzeln rechneten bei langsamen
    Vorschauen (Gewinde) so lange, dass der nächste Schritt schon OK drückte, während noch getippt wurde (Absturz)"""
    box = field(label)
    cr_ring(box)
    edit = box.lineEdit()
    edit.selectAll()
    edit.insert(text)


def cr_fit(x0, y0, z0, x1, y1, z1, top=False):
    """Ansicht (iso, sonst von oben) auf den Bereich einpassen, in dem das Ergebnis entsteht: ein Hilfsquader, nur für ViewFit"""
    def f():
        v = Gui.ActiveDocument.ActiveView
        v.viewTop() if top else v.viewIsometric()
        tmp = doc().addObject("Part::Feature", "FitBox")
        m = 0.15 * max(x1 - x0, y1 - y0, z1 - z0)  # Rand, damit nichts unter dem Panel liegt
        tmp.Shape = Part.makeBox(x1 - x0 + 2 * m, y1 - y0 + 2 * m, z1 - z0 + 2 * m, V(x0 - m, y0 - m, z0 - m))
        doc().recompute()
        Gui.SendMsgToActiveView("ViewFit")
        doc().removeObject(tmp.Name)
    return f


def cr_pause():
    """Aufnahme anhalten: der Wechsel in die Skizze und zurück zeigt sonst kurz ein dunkles Bild"""
    if harness._rec:
        harness._rec["timer"].stop()


def cr_resume():
    if harness._rec:
        harness._rec["timer"].start()


def cr_build(name, *fns):
    """Körper per Skript (oder der Hilfsquader von cr_fit) ohne Aufnahme anlegen: ein neuer Körper zeigt sonst gut 1 s
    lang einen falschen Schatten"""
    step(name, lambda: (cr_pause(), [fn() for fn in fns]))
    wait()
    step("resume", cr_resume)


def cr_quiet(cmd):
    """Kreis auf dem Knopf, 0,5 s später ohne Aufnahme auslösen (Ansichtswechsel); cr_resume() im nächsten Schritt"""
    cr_ring(button(cmd))
    QtCore.QTimer.singleShot(500, lambda: (cr_pause(), Gui.runCommand(cmd)))


def cr_fresh():
    """Aufnahme neu beginnen: was bis hier geschah (Aufbau mit echten Werkzeugen), gehört nicht in den Clip"""
    harness._rec["timer"].stop()
    record_start(harness._rec["path"])


def cr_seq(*fns, gap=400):
    """mehrere Klicks in einem Schritt, gap ms auseinander (wie schnelle Strg+Klicks): der Clip bleibt kurz"""
    def f():
        fns[0]()
        for i, fn in enumerate(fns[1:], 1):
            QtCore.QTimer.singleShot(i * gap, fn)
    return f


def cr_ok_ring():
    """Kreis auf OK; ausgelöst wird erst danach (cr_seq), damit der Clip den Kreis noch auf dem Panel zeigt"""
    b = [b for b in visible(QtWidgets.QPushButton) if b.text().replace("&", "") == "OK"]
    if b:
        cr_ring(b[0])


def cr_tool(cmd, *setup, variant=False, settle=1):
    """wie feature(), aber Werkzeug ggf. aus dem Dropdown, OK mit Kreis"""
    step(cmd, lambda: (cr_use_variant if variant else cr_use)(cmd))
    wait(settle)
    for s in setup:
        step("set", s)
    if os.environ.get("HELP_DUMP"):
        step("dump", lambda: dump_dialog(cmd))
    step("ok", cr_seq(cr_ok_ring, accept, lambda: L("  %s: errors=%s volumes=%s" % (cmd, errors(), volumes()))))


def cr_solid(prof, h, name, subs=()):
    """Körper aus einem Profil (wie make_body, aber mit Wahl der Profilflächen)"""
    d = doc(); root = [o for o in d.Objects if o.TypeId == "App::Part"][0]
    ext = d.addObject("Design::Extrude", "Extrude"); ext.Profile = (prof, list(subs)); ext.Distance = h; root.addObject(ext)
    b = d.addObject("Design::Body", "Body"); b.Label = name; ext.Bodies = [b]; b.Tip = ext
    d.getObject("Bodies").addObject(b)
    prof.Sketch.Visibility = False; prof.Visibility = False
    d.recompute()
    return b


def cr_curved(b):
    return faces(b, lambda f: f.Surface.TypeId != "Part::GeomPlane")


def cr_vp():
    """Viewport der aktiven 3D-Ansicht (view() nimmt die erste sichtbare, nach Std_New nicht immer diese)"""
    vp = Gui.ActiveDocument.ActiveView.graphicsView().viewport()
    harness._keep.append(vp)
    return vp


def cr_screen(p):
    vp = cr_vp(); px, py = Gui.ActiveDocument.ActiveView.getPointOnViewport(p)
    dpr = vp.devicePixelRatioF()
    return QtCore.QPoint(int(px / dpr), int(vp.height() - py / dpr))


def cr_press(p):
    """echter Klick an den 3D-Punkt p im Ansichtsfenster, mit Kreis im Clip"""
    q = cr_screen(p); vp = cr_vp()
    for r in (q - QtCore.QPoint(1, 1), q):
        QtWidgets.QApplication.sendEvent(vp, QtGui.QMouseEvent(QtCore.QEvent.MouseMove, QtCore.QPointF(r), QtCore.QPointF(vp.mapToGlobal(r)),
                                                                QtCore.Qt.NoButton, QtCore.Qt.NoButton, QtCore.Qt.NoModifier))
    record_click(vp.mapToGlobal(q))
    QtTest.QTest.mouseClick(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, q)


def cr_sel(obj, sub, p, add=False):
    """wie ein Klick (mit Strg bei add) auf obj/sub an der Stelle p: Auswahl samt Kreis im Clip"""
    if not add:
        Gui.Selection.clearSelection()
    record_click(cr_vp().mapToGlobal(cr_screen(p)))
    Gui.Selection.addSelection(doc().Name, obj.Name, sub, p.x, p.y, p.z)


# --- Clips ----------------------------------------------------------------------------------------------------------
def cr_revolve():
    cr_build("sketch", cr_fit(-40, -40, -8, 40, 40, 8), keep("sp", lambda: sketch([circle(30, 0, 8)], plane="XZ")[1]))
    step("select", lambda: cr_sel(st["sp"], "Face1", V(30, 0, 0)))
    cr_tool("Design_Revolve", lambda: cr_type_at("Angle", "180"), lambda: cr_type_at("Angle", "360"), variant=False)


def cr_sweep():
    def build():
        _, prof = sketch([circle(0, 0, 5)])
        path, _ = sketch([Part.ArcOfCircle(Part.Circle(V(40, 0, 0), V(0, 0, 1), 40), math.pi / 2, math.pi)], plane="XZ", name="Path")
        st["prof"], st["path"] = prof, path
    cr_build("sketches", cr_fit(-6, -6, -6, 46, 6, 46), build)
    step("select", cr_seq(lambda: cr_sel(st["prof"], "Face1", V(0, 0, 0)),
                             lambda: cr_sel(st["path"], "Edge1", V(40 - 28.28, 0, 28.28), True)))
    cr_tool("Design_Sweep", variant=True)


def cr_loft():
    def build():
        _, p1 = sketch(rect(-20, -20, 20, 20))
        _, p2 = sketch([circle(0, 0, 10)], z=30)
        _, p3 = sketch([circle(0, 0, 18)], z=60)
        st["p1"], st["p2"], st["p3"] = p1, p2, p3
    cr_build("sketches", cr_fit(-20, -20, 0, 20, 20, 60), build)
    step("select", cr_seq(lambda: cr_sel(st["p1"], "Face1", V(0, 0, 0)),
                             lambda: cr_sel(st["p2"], "Face1", V(0, 0, 30), True),
                             lambda: cr_sel(st["p3"], "Face1", V(0, 0, 60), True)))
    cr_tool("Design_Loft", variant=True)


def cr_rib():
    pts = [V(0, 0, 0), V(60, 0, 0), V(60, 6, 0), V(6, 6, 0), V(6, 50, 0), V(0, 50, 0)]
    lines = [Part.LineSegment(pts[i], pts[(i + 1) % 6]) for i in range(6)]
    cr_build("L", cr_fit(0, -30, 0, 60, 0, 50), keep("b", lambda: cr_solid(sketch(lines, plane="XZ")[1], 30, "Bracket")))
    def line():  # in der Mitte des Winkels (y = -15)
        st["rib"] = sketch([Part.LineSegment(V(6, 40, 0), V(50, 6, 0))], plane="XZ", name="RibLine")[0]
        st["rib"].Placement.Base.y = -15
        doc().recompute()
    step("rib", line)
    step("select", cr_seq(lambda: cr_sel(st["b"], "", V(40, -15, 6)),
                             lambda: cr_sel(st["rib"], "Edge1", V(28, -15, 23), True)))
    cr_tool("Design_Rib", lambda: cr_type_at("Thickness", "4"), variant=True)


def cr_web():
    cr_build("box", cr_fit(0, 0, 0, 60, 40, 20), keep("b", lambda: box(0, 0, 60, 40, 20)))
    step("open", lambda: select(st["b"], top(st["b"])))
    feature("Design_Shell", lambda: type_into(0, "2"))
    step("walls", keep("w", lambda: sketch([Part.LineSegment(V(2, 20, 0), V(58, 20, 0)), Part.LineSegment(V(30, 2, 0), V(30, 38, 0))], z=20, name="WebLines")[0]))
    step("fresh", cr_fresh)
    step("select", cr_seq(lambda: cr_sel(st["b"], "", V(1, 20, 20)),
                             lambda: cr_sel(st["w"], "Edge1", V(15, 20, 20), True),
                             lambda: cr_sel(st["w"], "Edge2", V(30, 10, 20), True)))
    cr_tool("Design_Web", lambda: cr_type_at("Thickness", "5"), variant=True)


def cr_emboss():
    cr_build("plate", cr_fit(0, 0, 0, 60, 40, 9), keep("b", lambda: box(0, 0, 60, 40, 6)))
    step("shape", keep("sp", lambda: sketch([circle(20, 20, 8)] + rect(36, 12, 50, 28), z=6)[1]))
    step("select", cr_seq(lambda: cr_sel(st["sp"], "Face1", V(20, 20, 6)),
                             lambda: cr_sel(st["sp"], "Face2", V(43, 20, 6), True),
                             lambda: cr_sel(st["b"], top(st["b"]), V(8, 8, 6), True)))
    cr_tool("Design_Emboss", lambda: cr_type_at("Depth", "3"), variant=True)


def cr_primitives():
    """ein Werkzeug, alle Grundkörper: Quader, Länge tippen, dann im Panel den Typ wechseln (Vorschau folgt)"""
    cr_build("fit", cr_fit(-30, -30, 0, 45, 30, 35))
    cr_tool("Design_Box", lambda: cr_type_at("Length", "40"),
            *[lambda t=t: cr_pick("Type", t) for t in ("Cylinder", "Sphere", "Torus", "Coil")])


def cr_hole():
    cr_build("plate", cr_fit(0, 0, 0, 70, 40, 12), keep("b", lambda: box(0, 0, 70, 40, 12)))
    step("face", lambda: cr_sel(st["b"], top(st["b"]), V(35, 20, 12)))
    step("sketch", lambda: cr_quiet("Design_CreateSketch"))
    wait()
    step("top", cr_fit(0, 0, 12, 70, 40, 12, top=True))
    wait()
    step("resume", cr_resume)
    step("point tool", lambda: cr_use("Sketcher_CreatePoint"))
    step("points", cr_seq(*[lambda x=x: cr_press(V(x, 20, 12)) for x in (15, 35, 55)]))
    step("finish", lambda: (QtTest.QTest.keyClick(cr_vp(), QtCore.Qt.Key_Escape), cr_quiet("Sketcher_LeaveSketch")))
    wait()
    step("iso", cr_fit(0, 0, 0, 70, 40, 12))
    wait()
    step("resume", cr_resume)
    step("select", lambda: cr_sel([o for o in doc().Objects if o.TypeId == "Sketcher::SketchObject"][-1], "", V(35, 20, 12)))
    cr_tool("Design_Hole", lambda: cr_pick("Standard", "ISO metric"), lambda: cr_pick("Size", "M5x0.8"), lambda: cr_pick("Type", "Counterbore"))


def cr_fastener():
    cr_build("plates", cr_fit(-35, -20, 0, 35, 20, 15), lambda: st.update(low=box(-35, -20, 35, 20, 10, name="Base"), up=box(-25, -15, 25, 15, 5, z=10, name="Lid")))
    step("face", lambda: cr_sel(st["up"], top(st["up"]), V(0, 0, 15)))
    cr_tool("Design_Fastener", lambda: cr_pick("Size", "M4"), lambda: cr_pick("Bottom", "Heat-set insert"), variant=True)


def cr_fitting():
    def build():
        prof = sketch(rect(-20, -20, 20, 20) + [circle(0, 0, 10)])[1]
        st["b"] = cr_solid(prof, 10, "Block", [ring_face(prof)])
        st["pin"] = make_body([circle(45, 0, 10)], 0, 30, "Pin")
    cr_build("parts", cr_fit(-20, -20, 0, 55, 20, 30), build)
    step("select", cr_seq(lambda: cr_sel(st["b"], cr_curved(st["b"])[0], V(-7.07, 7.07, 5)),
                             lambda: cr_sel(st["pin"], cr_curved(st["pin"])[0], V(52.07, -7.07, 15), True)))
    cr_tool("Design_Fit", lambda: cr_pick("Fit", "H7/g6"), variant=True)


def cr_thread():
    cr_build("rod", cr_fit(-10, -10, 0, 10, 10, 30), keep("r", lambda: make_body([circle(0, 0, 6)], 0, 30, "Rod")))
    step("select", lambda: cr_sel(st["r"], cylindrical(st["r"])[0], V(4.24, -4.24, 15)))
    cr_tool("Design_Thread", lambda: cr_type_at("Clearance", "0.2"), variant=True)


def cr_pattern():
    cr_build("peg", cr_fit(-5, -5, 0, 59, 29, 15), keep("p", lambda: make_body([circle(0, 0, 5)], 0, 15, "Peg")))
    step("select", lambda: cr_sel(st["p"], "", V(0, 0, 15)))
    cr_tool("Design_Pattern", lambda: cr_type_at("Count", "4"), lambda: cr_type_at("Spacing", "18"),
         lambda: cr_type_at("Count 2", "2"), lambda: cr_type_at("Spacing 2", "24"))


def cr_mirror():
    pts = [V(10, 0, 0), V(50, 0, 0), V(50, 10, 0), V(20, 10, 0), V(20, 30, 0), V(10, 30, 0)]
    cr_build("part", cr_fit(-50, -30, 0, 50, 30, 15), keep("b", lambda: make_body([Part.LineSegment(pts[i], pts[(i + 1) % 6]) for i in range(6)], 0, 15, "Part")))
    step("select", lambda: cr_sel(st["b"], "", V(30, 5, 15)))
    cr_tool("Design_Mirror", lambda: cr_pick("Mirror plane", "XZ plane"))


scenario("Design_Revolve", cr_revolve, view="none", fixed=True)
scenario("Design_Sweep", cr_sweep, view="none", fixed=True)
scenario("Design_Loft", cr_loft, view="none", fixed=True)
scenario("Design_Rib", cr_rib, view="none", fixed=True)
scenario("Design_Web", cr_web, view="none", fixed=True)
scenario("Design_Emboss", cr_emboss, view="none", fixed=True)
scenario("primitives", cr_primitives, view="none", fixed=True)
scenario("Design_Hole", cr_hole, view="none", fixed=True)
scenario("Design_Fastener", cr_fastener, view="none", fixed=True)
scenario("Design_Fit", cr_fitting, view="none", fixed=True)
scenario("Design_Thread", cr_thread, view="none", fixed=True)
scenario("Design_Pattern", cr_pattern, view="none", fixed=True)
scenario("Design_Mirror", cr_mirror, view="none", fixed=True)
