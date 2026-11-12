# SPDX-License-Identifier: LGPL-2.1-or-later
"""Erklär-Clips: Parameter, Notiz, Rotstift, Scribble, Suche, Einstellungen, Dateien, Versionen, Einfügen, Drucken,
Exportieren, Zeitleiste, Navigation, Tastenkürzel. Läuft in den Globals von tools/help_images.py (step, wait, use …).
Eigene Namen beginnen mit ut_, damit sie die anderen Clip-Dateien nicht überschreiben."""
import math


# --- Aufnahme mit Dialogen (harness._record_frame nimmt Dialoge und Menüs mit ins Bild) ------------------------------
def ut_on_close(fn):
    """fn ausführen, sobald das Design des Clips geschlossen ist (nach der Aufnahme): Einstellungen zurück"""
    name = doc().Name

    def poll():
        if name in App.listDocuments():
            QtCore.QTimer.singleShot(300, poll)
        else:
            fn()
    QtCore.QTimer.singleShot(300, poll)


def ut_view():
    """die 3D-Ansicht: die größte sichtbare QGraphicsView (im Scribble ist noch eine kleine 400 x 300 sichtbar, die
    harness.view() sonst manchmal zuerst findet)"""
    vs = [v for v in mw.findChildren(QtWidgets.QGraphicsView) if v.isVisible()]
    v = max(vs, key=lambda v: v.width() * v.height())
    harness._keep.append(v)
    return v


def ut_grab_start():
    """Bild des Fensters; ist die Startseite offen, kommt sie obenauf: mw.grab() malte die Werkzeugleiste der 3D-Ansicht
    (dahinter) über sie, im echten Fenster liegt die Startseite darüber"""
    pix = QtWidgets.QMainWindow.grab(mw)
    start = [w for w in mw.findChildren(QtWidgets.QWidget, "StartPage") if w.isVisible()]
    if start:
        painter = QtGui.QPainter(pix)
        painter.drawPixmap(start[0].mapTo(mw, QtCore.QPoint(0, 0)), start[0].grab())
        painter.end()
    return pix


def ut_rec():
    """Aufnahme mit Dialogen; der Textcursor blinkt nicht (sonst ist jedes Bild neu und die GIF riesig)"""
    def go():
        flash = QtWidgets.QApplication.cursorFlashTime()
        QtWidgets.QApplication.setCursorFlashTime(0)
        # Kamerafahrten aus: unter Last zieht eine Drehung der Ansicht sich im Clip sonst über viele Sekunden
        grp = App.ParamGet("User parameter:BaseApp/Preferences/View")
        anim = grp.GetBool("UseNavigationAnimations", True)
        grp.SetBool("UseNavigationAnimations", False)
        g, old_view = globals(), harness.view
        harness.view = g["view"] = ut_view  # click(), _pos() und use() zielen sonst im Scribble daneben
        mw.grab = ut_grab_start  # harness._record_frame nimmt mw.grab()

        def restore():
            QtWidgets.QApplication.setCursorFlashTime(flash)
            grp.SetBool("UseNavigationAnimations", anim)
            harness.view = g["view"] = old_view
            del mw.grab
        ut_on_close(restore)
    step("dialog recorder", go)


# --- Eingaben, die man im Clip sieht --------------------------------------------------------------------------------
def ut_ring(w):
    record_click(w.mapToGlobal(w.rect().center()))


def ut_ring_scene(w):
    """Kreis auf einem Glas-Widget (liegt in der Szene der 3D-Ansicht, mapToGlobal stimmt dort nicht)"""
    p = harness._pos(w)
    record_click(ut_view().viewport().mapToGlobal(p.toPoint() if hasattr(p, "toPoint") else p))


def ut_press(w):
    """Knopf in einem Dialog: Kreis, dann auslösen"""
    ut_ring(w)
    w.click()


def ut_anim(make, n, ms=80):
    """make() liefert n Aktionen im Abstand ms (Tippen, Ziehen); danach so viele Warteschritte, dass der nächste
    Schritt erst drankommt, wenn alle durch sind"""
    step("animate", lambda: [QtCore.QTimer.singleShot(i * ms, a) for i, a in enumerate(make())])
    wait(max(0, math.ceil(n * ms / 900.0)))


def ut_type(get, text, ms=90, clear=True):
    """Text Taste für Taste in das Feld get() tippen"""
    def make():
        w = get()
        acts = []
        if clear:
            acts.append(lambda: (w.setFocus(), w.selectAll() if hasattr(w, "selectAll") else None))
        for c in text:
            if c == "\n":
                acts.append(lambda: QtTest.QTest.keyClick(w, QtCore.Qt.Key_Return))
            else:
                acts.append(lambda c=c: QtTest.QTest.keyClicks(w, c))
        return acts
    ut_anim(make, len(text) + 1, ms)


_ut_caps = []


def ut_key(text, ms=1400):
    """Tastendruck im Clip zeigen: Schild unten in der Mitte (der Clip enthält keine Tastatur)"""
    for old in _ut_caps:
        old.hide()
    lab = QtWidgets.QLabel(text, mw)
    lab.setStyleSheet("QLabel { background: rgba(29, 29, 31, 0.86); color: #FFFFFF; border-radius: 20px;"
                      " padding: 8px 20px; font-size: 22px; font-weight: 600; }")
    lab.adjustSize()
    left = 306  # so viel schneidet die Aufnahme links ab
    lab.move(left + (mw.width() - left - lab.width()) // 2, mw.height() - 170)
    lab.show()
    lab.raise_()
    _ut_caps.append(lab)
    harness._keep.append(lab)
    QtCore.QTimer.singleShot(ms, lab.hide)


def ut_dialog(title=None):
    """oberster sichtbarer Dialog (optional mit diesem Fenstertitel)"""
    ds = [w for w in QtWidgets.QApplication.topLevelWidgets() if isinstance(w, QtWidgets.QDialog) and w.isVisible()
          and (title is None or w.windowTitle() == title)]
    harness._keep.extend(ds)
    return ds[-1]


def ut_place(title, top=110):
    """Dialog mitten über den sichtbaren Teil (rechts der Seitenleiste), unter die Werkzeugleiste, nicht höher als
    das Fenster: unter Xvfb ohne Fenstermanager landet er sonst irgendwo"""
    d = ut_dialog(title)
    room = mw.height() - top - 30
    if d.height() > room:
        d.resize(d.width(), room)
    left = 306
    d.move(mw.mapToGlobal(QtCore.QPoint(left + (mw.width() - left - d.width()) // 2, top)))


def ut_activate():
    """Fenster aktiv machen (sonst greifen Tastenkürzel nicht), ohne das Design zu wechseln: harness.activate()
    schaltet auf das erste offene Design um (hier das leere vom Start des Laufs)"""
    name = doc().Name
    activate()
    if doc().Name != name:
        mdi = mw.findChild(QtWidgets.QMdiArea)
        for sub in mdi.subWindowList():
            if sub.widget() is not None and sub.widget().windowTitle().startswith(App.getDocument(name).Label):
                mdi.setActiveSubWindow(sub)
                break
        if doc().Name != name:
            L("  ut_activate: design %s not active again (%s), windows %s" % (
                name, doc().Name, [sub.widget().windowTitle() for sub in mdi.subWindowList() if sub.widget()]))
    ut_view().viewport().setFocus()


def ut_fit():
    """Iso-Ansicht, alles einpassen und eine Stufe weiter weg: Einpassen rechnet mit der ganzen Fensterbreite, die
    Aufnahme lässt links die Seitenleiste weg, sonst ragt der Körper aus dem Bild"""
    v = Gui.ActiveDocument.ActiveView
    v.viewIsometric()
    Gui.SendMsgToActiveView("ViewFit")
    v.zoomOut()


def ut_modal(title, top=110):
    """vor einem Befehl mit Dialog aufrufen: setzt den Dialog an seinen Platz, sobald er erscheint"""
    def poll(n=0):
        try:
            ut_place(title, top)
        except IndexError:
            if n < 500:  # bis 10 s: ein Befehl aus einem Menü (▾) kommt erst nach zwei Schritten dran
                QtCore.QTimer.singleShot(20, lambda: poll(n + 1))
    QtCore.QTimer.singleShot(0, poll)


def ut_child(parent, cls, pred=lambda w: True):
    ws = [w for w in parent.findChildren(cls) if w.isVisible() and pred(w)]
    harness._keep.extend(ws)
    return ws[0]


def ut_text_button(parent, text, cls=QtWidgets.QAbstractButton):
    return ut_child(parent, cls, lambda b: b.text().replace("&", "") == text)


def ut_clip_starts():
    """der Clip beginnt erst hier: der Aufbau davor (Körper, Profil, Einpassen) gehört nicht hinein"""
    step("clip starts", lambda: harness._rec and (harness._rec["frames"].clear(), harness._record_frame()))


def ut_profile(x0, y0, x1, y1):
    """Skizze mit Rechteck, als Profil gewählt (wie nach Skizze fertig stellen)"""
    def go():
        sk, prof = sketch(rect(x0, y0, x1, y1))
        st["sp"] = prof
        ut_fit()
    step("profile", go)


# --- Parameter ändern -----------------------------------------------------------------------------------------------
def ut_parameters():
    ut_rec()
    ut_profile(0, 0, 40, 30)
    wait()
    ut_clip_starts()
    step("Design_Parameters", lambda: (ut_modal("Parameters", 200), use("Design_Parameters")))
    wait()
    ut_type(lambda: ut_child(ut_dialog("Parameters"), QtWidgets.QLineEdit, lambda e: e.placeholderText().startswith("Name")), "Height")
    ut_type(lambda: ut_child(ut_dialog("Parameters"), QtWidgets.QLineEdit, lambda e: e.placeholderText().startswith("Value")), "15 mm")
    step("add", lambda: ut_press(ut_text_button(ut_dialog("Parameters"), "Add", QtWidgets.QPushButton)))
    wait()
    step("ok", lambda: ut_press(ut_text_button(ut_dialog("Parameters"), "OK", QtWidgets.QPushButton)))
    step("select", lambda: select(st["sp"], "Face1"))
    step("Design_Extrude", lambda: use("Design_Extrude"))
    wait()
    def distance():
        return sorted(visible(QtWidgets.QAbstractSpinBox), key=lambda w: w.mapToGlobal(QtCore.QPoint(0, 0)).y())[0].lineEdit()
    ut_type(distance, "Height\n", ms=220)
    wait()
    step("ok", accept)
    wait()
    step("fit", lambda: (ut_fit()))
    wait()
    step("Design_Parameters", lambda: (ut_modal("Parameters", 200), use("Design_Parameters")))
    wait()

    def edit_cell():
        t = ut_child(ut_dialog("Parameters"), QtWidgets.QTableWidget)
        item = t.item(0, 1)
        r = t.visualItemRect(item)
        record_click(t.viewport().mapToGlobal(r.center()))
        t.editItem(item)
    step("edit", edit_cell)
    ut_type(lambda: QtWidgets.QApplication.focusWidget(), "30 mm\n")
    wait()
    step("ok", lambda: ut_press(ut_text_button(ut_dialog("Parameters"), "OK", QtWidgets.QPushButton)))
    step("check", lambda: L("  parameters: volumes=%s errors=%s" % (volumes(), errors())))
    wait()


scenario("Design_Parameters", ut_parameters, zoom=-1)


# --- Einstellungen --------------------------------------------------------------------------------------------------
def ut_settings():
    ut_rec()
    step("body", lambda: (box(0, 0, 60, 40, 20), ut_fit()))
    wait()
    step("ctrl+,", lambda: (ut_key("Ctrl + ,"), ut_modal("Settings"), ut_activate(),
                            QtTest.QTest.keyClick(mw.windowHandle(), QtCore.Qt.Key_Comma, QtCore.Qt.ControlModifier)))
    wait()
    names = lambda: ut_child(ut_dialog("Settings"), QtWidgets.QAbstractButton, lambda b: b.accessibleName() == "Show tool names")
    step("names on", lambda: ut_press(names()))
    wait(2)
    step("names off", lambda: ut_press(names()))
    wait()
    step("Navigation", lambda: ut_press(ut_text_button(ut_dialog("Settings"), "Navigation")))
    wait()
    style = lambda: ut_child(ut_dialog("Settings"), QtWidgets.QComboBox, lambda c: c.findText("Blender") >= 0)
    step("style", lambda: (ut_ring(style()), style().showPopup()))
    wait()
    step("hover Blender", lambda: style().highlighted.emit(style().findText("Blender")))
    wait(2)
    step("keep Fusion", lambda: (style().highlighted.emit(style().findText("Fusion 360")), style().hidePopup()))
    wait()
    step("Keys", lambda: ut_press(ut_text_button(ut_dialog("Settings"), "Keys")))
    wait()
    step("close", lambda: ut_press(ut_child(ut_dialog("Settings"), QtWidgets.QToolButton, lambda b: b.objectName() == "CloseSettings")))
    wait()


scenario("settings", ut_settings, zoom=-1)


# --- Maus in der 3D-Ansicht -----------------------------------------------------------------------------------------
def ut_at(fx, fy):
    v = ut_view()
    return QtCore.QPointF(v.width() * fx, v.height() * fy)


def ut_mouse(kind, p, button=QtCore.Qt.LeftButton, buttons=QtCore.Qt.LeftButton, mods=QtCore.Qt.NoModifier):
    """Mausereignis direkt an die 3D-Ansicht (p in Pixeln des Viewports)"""
    vp = ut_view().viewport()
    QtWidgets.QApplication.sendEvent(vp, QtGui.QMouseEvent(kind, p, vp.mapToGlobal(p), button, buttons, mods))


def ut_line(a, b, n):
    return [(a[0] + (b[0] - a[0]) * k / n, a[1] + (b[1] - a[1]) * k / n) for k in range(n + 1)]


def ut_stroke(points, ms=25, release=True, ring=False):
    """Strich mit der Maus, Punkt für Punkt sichtbar (points als Bruchteile der Ansicht)"""
    def make():
        pts = [ut_at(*p) for p in points]
        acts = [lambda: (ring and record_click(ut_view().viewport().mapToGlobal(pts[0].toPoint())),
                         ut_mouse(QtCore.QEvent.MouseButtonPress, pts[0]))]
        acts += [lambda p=p: ut_mouse(QtCore.QEvent.MouseMove, p, QtCore.Qt.NoButton) for p in pts[1:]]
        if release:
            acts.append(lambda: ut_mouse(QtCore.QEvent.MouseButtonRelease, pts[-1], QtCore.Qt.LeftButton, QtCore.Qt.NoButton))
        return acts
    ut_anim(make, len(points) + 1, ms)


def ut_release(fx, fy):
    step("release", lambda: ut_mouse(QtCore.QEvent.MouseButtonRelease, ut_at(fx, fy), QtCore.Qt.LeftButton, QtCore.Qt.NoButton))


def ut_tap(fx, fy):
    """kurzer Klick in die Ansicht, mit Kreis"""
    def go():
        p = ut_at(fx, fy)
        record_click(ut_view().viewport().mapToGlobal(p.toPoint()))
        ut_mouse(QtCore.QEvent.MouseButtonPress, p)
        ut_mouse(QtCore.QEvent.MouseButtonRelease, p, QtCore.Qt.LeftButton, QtCore.Qt.NoButton)
    step("tap", go)


def ut_click_view(fx, fy):
    """echter Klick in die Ansicht (mit Fokuswechsel, z. B. um eine Notiz zu verlassen)"""
    def go():
        p = ut_at(fx, fy).toPoint()
        vp = ut_view().viewport()
        record_click(vp.mapToGlobal(p))
        QtTest.QTest.mouseMove(vp, p)
        QtTest.QTest.mouseClick(vp, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)
    step("click view", go)


def ut_ring_at(p):
    """Kreis an einem 3D-Punkt (Klick auf das Modell, ausgelöst per Auswahl)"""
    fx, fy = ut_screen(p)
    record_click(ut_view().viewport().mapToGlobal(ut_at(fx, fy).toPoint()))


def ut_screen(p):
    """3D-Punkt -> Bruchteile der Ansicht (Coin zählt y von unten, in Geräte-Pixeln)"""
    v = ut_view()
    x, y = Gui.ActiveDocument.ActiveView.getPointOnViewport(p)
    dpr = v.viewport().devicePixelRatioF()
    return x / dpr / v.width(), (v.viewport().height() - y / dpr) / v.height()


def ut_glass(text, cls=QtWidgets.QAbstractButton, by="text"):
    """sichtbarer Knopf mit diesem Text (oder accessibleName), auch in Glas-Panels"""
    ws = [w for w in visible(cls) if (w.text().replace("&", "") if by == "text" else w.accessibleName()) == text]
    return ws[0]


def ut_inside(w, name):
    """liegt w in einem Widget mit diesem objectName?"""
    while w is not None:
        if w.objectName() == name:
            return True
        w = w.parentWidget()
    return False


def ut_click_glass(get):
    """Knopf in einem Glas-Panel: Kreis an der richtigen Stelle, dann auslösen"""
    def go():
        w = get()
        ut_ring_scene(w)
        w.click()
    return go


# --- Notiz ----------------------------------------------------------------------------------------------------------
def ut_note_edit():
    return [e for e in visible(QtWidgets.QPlainTextEdit) if e.objectName() == "NoteText"][0]


def ut_note_keys(text, ms=85):
    def make():
        e = ut_note_edit()
        acts = [lambda: (e.setFocus(), e.moveCursor(QtGui.QTextCursor.End))]
        for c in text:
            acts.append(lambda c=c: QtTest.QTest.keyClick(e, QtCore.Qt.Key_Return) if c == "\n" else QtTest.QTest.keyClicks(e, c))
        return acts
    ut_anim(make, len(text) + 1, ms)


def ut_note():
    ut_rec()
    ut_profile(0, 0, 40, 30)
    wait()
    ut_clip_starts()
    step("Design_Note", lambda: use("Design_Note"))
    wait()
    ut_note_keys("120 / 4 =")
    wait()
    ut_note_keys("\nWall = 2 mm\nHeight = Wall * 10\n")
    wait()
    step("select", lambda: select(st["sp"], "Face1"))
    step("Design_Extrude", lambda: use("Design_Extrude"))
    wait()
    ut_type(lambda: sorted(visible(QtWidgets.QAbstractSpinBox), key=lambda w: w.mapToGlobal(QtCore.QPoint(0, 0)).y())[0].lineEdit(), "Height\n")
    wait()
    step("ok", accept)

    wait()

    def to_wall():  # Klick ans Ende der Zeile "Wall = 2 mm"
        e = ut_note_edit()
        c = e.textCursor()
        c.movePosition(QtGui.QTextCursor.Start)
        c.movePosition(QtGui.QTextCursor.NextBlock)
        c.movePosition(QtGui.QTextCursor.EndOfBlock)
        e.setFocus()
        e.setTextCursor(c)
        r = e.cursorRect(c)
        top = e.viewport()
        p = harness._pos(e)
        off = top.mapTo(e, r.center()) - e.rect().center()
        record_click(ut_view().viewport().mapToGlobal((QtCore.QPointF(p) + QtCore.QPointF(off)).toPoint()))
    step("click line", to_wall)
    step("animate", lambda: [QtCore.QTimer.singleShot(i * 120, a) for i, a in enumerate(
        [lambda: QtTest.QTest.keyClick(ut_note_edit(), QtCore.Qt.Key_Backspace)] * 4 + [lambda c=c: QtTest.QTest.keyClicks(ut_note_edit(), c) for c in "3 mm"])])
    wait()
    ut_click_view(0.62, 0.82)
    wait(2)
    step("check", lambda: L("  note: volumes=%s errors=%s text=%r expr=%s params=%s focus=%s" % (
        volumes(), errors(), ut_note_edit().toPlainText(),
        [o.ExpressionEngine for o in doc().Objects if o.TypeId == "Design::Extrude"],
        [(o.Label, [(n, str(getattr(o, n)), o.ExpressionEngine) for n in o.PropertiesList if o.getGroupOfProperty(n) == "Parameters"])
         for o in doc().Objects if o.TypeId == "App::VarSet"], type(QtWidgets.QApplication.focusWidget()).__name__)))


scenario("Design_Note", ut_note, zoom=-1)


# --- Suche ----------------------------------------------------------------------------------------------------------
def ut_search_field():
    return [e for e in visible(QtWidgets.QLineEdit) if e.accessibleName() == "Search"][0]


def ut_search():
    ut_rec()
    def body():  # links neben dem Panel von Abrunden einpassen (es öffnet gleich und verdeckte sonst den Körper rechts)
        st["b"] = box(0, 0, 60, 40, 20, name="Bracket")
        Gui.ActiveDocument.ActiveView.viewIsometric()
        panel_fit()
        Gui.ActiveDocument.ActiveView.zoomOut()
    step("body", body)
    step("face", lambda: select(st["b"], top(st["b"])))
    wait()
    step("ctrl+k", lambda: (ut_key("Ctrl + K"), ut_activate(), QtTest.QTest.keyClick(mw, QtCore.Qt.Key_K, QtCore.Qt.ControlModifier)))
    wait()
    ut_type(ut_search_field, "loch", ms=140)
    wait()
    ut_type(ut_search_field, "filet", ms=140)
    wait()
    step("enter", lambda: (ut_key("Enter"), QtTest.QTest.keyClick(ut_search_field(), QtCore.Qt.Key_Return)))
    wait()
    step("radius", lambda: type_into(0, "6"))
    wait()
    step("ok", accept)
    step("check", lambda: L("  search: volumes=%s errors=%s" % (volumes(), errors())))


scenario("search", ut_search, zoom=-1)


# --- Scribble -------------------------------------------------------------------------------------------------------
def ut_scribble():
    ut_rec()
    step("Design_Scribble", lambda: use("Design_Scribble"))
    wait(2)
    ut_stroke([(0.36 + 0.006 * k, 0.40 + 0.05 * math.sin(k / 3.0)) for k in range(30)])  # Freihand-Welle
    wait()
    ut_stroke([(0.40, 0.55)] + [(0.40 + 0.012 * k, 0.55 + 0.0006 * k) for k in range(1, 16)], release=False)  # fast gerade
    wait()  # Stift steht still: wird zur Linie
    ut_release(0.58, 0.559)
    wait()
    rect_pts = ut_line((0.62, 0.36), (0.74, 0.36), 10) + ut_line((0.74, 0.36), (0.74, 0.52), 10)[1:] \
        + ut_line((0.74, 0.52), (0.62, 0.52), 10)[1:] + ut_line((0.62, 0.52), (0.62, 0.362), 10)[1:]
    ut_stroke([(x + 0.003 * math.sin(i), y + 0.004 * math.cos(i * 1.3)) for i, (x, y) in enumerate(rect_pts)], release=False)
    wait()  # halten: Rechteck
    ut_release(0.62, 0.362)
    wait()
    step("Design_ScribbleCircle", lambda: use("Design_ScribbleCircle"))
    ut_stroke(ut_line((0.50, 0.70), (0.55, 0.70), 12))
    wait()
    step("Design_ScribbleFill", lambda: use("Design_ScribbleFill"))
    step("Design_ScribbleBlue", lambda: use("Design_ScribbleBlue"))
    ut_tap(0.68, 0.44)
    wait()
    step("Design_ScribbleText", lambda: use("Design_ScribbleText"))
    ut_tap(0.62, 0.66)
    def typing():
        vp = ut_view().viewport()
        return [lambda c=c: QtTest.QTest.keyClicks(vp, c) for c in "Idea!"] + [lambda: QtTest.QTest.keyClick(vp, QtCore.Qt.Key_Return)]
    ut_anim(typing, 7, 150)
    wait()
    step("Design_ScribbleFinish", lambda: use("Design_ScribbleFinish"))
    wait()
    step("check", lambda: L("  scribble: kinds=%s" % [list(o.Kinds) for o in doc().Objects if o.TypeId == "Design::Scribble"]))


scenario("Design_Scribble", ut_scribble, view="top")


# --- Rotstift -------------------------------------------------------------------------------------------------------
UT_GLYPHS = {  # Einzelstrich-Druckschrift wie tests/scribble_read_check.cpp: Einheit x-Höhe, y nach unten
    "R": (.82, [[(.1, 0), (.1, -1.6)], [(.1, -1.6), (.45, -1.6), (.68, -1.42), (.66, -1.0), (.42, -.84), (.1, -.84)], [(.36, -.84), (.76, 0)]]),
    "2": (.82, [[(.1, -1.25), (.3, -1.58), (.58, -1.5), (.65, -1.1), (.1, 0), (.75, 0)]]),
}


def ut_dense(poly, d=.08):
    out = [poly[0]]
    for (x0, y0), (x1, y1) in zip(poly, poly[1:]):
        n = max(1, int(math.hypot(x1 - x0, y1 - y0) / d))
        out += [(x0 + (x1 - x0) * k / n, y0 + (y1 - y0) * k / n) for k in range(1, n + 1)]
    return out


def ut_write(text, at, u=0.016, ms=18):
    """Text mit der Maus schreiben; at() liefert die linke Grundlinie als Bruchteile der Ansicht"""
    def make():
        x0, y0 = at()
        ratio = ut_view().width() / float(ut_view().height())
        acts, gx = [], 0
        for ch in text:
            w, polys = UT_GLYPHS[ch]
            for poly in polys:
                pts = [ut_at(x0 + (px + gx) * u, y0 + py * u * ratio) for px, py in ut_dense(poly)]
                acts.append(lambda p=pts[0]: ut_mouse(QtCore.QEvent.MouseButtonPress, p))
                acts += [lambda p=p: ut_mouse(QtCore.QEvent.MouseMove, p, QtCore.Qt.NoButton) for p in pts[1:]]
                acts.append(lambda p=pts[-1]: ut_mouse(QtCore.QEvent.MouseButtonRelease, p, QtCore.Qt.LeftButton, QtCore.Qt.NoButton))
            gx += w + .12
        return acts
    n = sum(len(ut_dense(p)) + 1 for c in text for p in UT_GLYPHS[c][1])
    ut_anim(make, n, ms)


def ut_red_pen():
    ut_rec()
    step("body", lambda: (st.__setitem__("b", box(0, 0, 60, 40, 20)), ut_fit()))
    wait()
    step("Design_RedPen", lambda: use("Design_RedPen"))
    wait(2)

    def spot():  # über der Mitte der vorderen oberen Kante, etwas auf der Deckfläche
        x, y = ut_screen(App.Vector(30, 4, 20))
        return x - 0.02, y - 0.004
    ut_write("R2", spot)
    wait(2)
    step("Apply Corrections", ut_click_glass(lambda: ut_glass("Apply Corrections", QtWidgets.QToolButton)))
    wait(2)
    step("cards", lambda: L("  red pen cards: %s" % [b.accessibleName() for b in visible(QtWidgets.QPushButton) if b.accessibleName()]))
    # die Karten liegen über der Scribble-Palette: erst das Scribble fertig stellen, die Karten bleiben
    step("finish", ut_click_glass(lambda: ut_glass("Finish Scribble", QtWidgets.QAbstractButton)))
    wait()
    step("show", ut_click_glass(lambda: [b for b in visible(QtWidgets.QPushButton) if b.accessibleName().startswith("Show ")][0]))
    wait(2)
    step("apply", ut_click_glass(lambda: [b for b in visible(QtWidgets.QPushButton) if b.accessibleName().startswith("Apply ")
                                          and b.accessibleName() != "Apply All"][0]))
    wait(2)
    step("close", ut_click_glass(lambda: [b for b in visible(QtWidgets.QPushButton) if b.text() == "Close" and ut_inside(b, "Corrections")][0]))
    wait()
    step("check", lambda: L("  red pen: volumes=%s fillets=%s errors=%s" % (volumes(), [o.Name for o in doc().Objects if o.TypeId == "Design::Fillet"], errors())))


scenario("Design_RedPen", ut_red_pen, zoom=-1)


# --- Zeitleiste -----------------------------------------------------------------------------------------------------
def ut_entry(type_id):
    obj = [o for o in doc().Objects if o.TypeId == type_id][0]
    return [b for b in visible(QtWidgets.QToolButton) if b.property("timelineIndex") is not None and b.accessibleName() == obj.Label][0]


def ut_dclick_glass(w):
    """Doppelklick auf ein Glas-Widget: direkt an das Widget (über die Szene kam er bei den Zeitleisten-Einträgen nicht an)"""
    ut_ring_scene(w)
    QtTest.QTest.mouseDClick(w, QtCore.Qt.LeftButton)


def ut_menu(w, text):
    """Rechtsklick auf w, dann im Menü text wählen (das Menü blockiert: Auswahl kommt vorher in die Warteschlange)"""
    def pick():
        menu = QtWidgets.QApplication.activePopupWidget()
        acts = [a for a in (menu.actions() if menu else []) if a.text() == text]
        if acts:
            menu.setActiveAction(acts[0])
            QtCore.QTimer.singleShot(900, lambda: (record_click(menu.mapToGlobal(menu.actionGeometry(acts[0]).center())),
                                                   QtTest.QTest.keyClick(menu, QtCore.Qt.Key_Return)))
        elif menu:
            menu.close()
    p = harness._pos(w)
    p = ut_view().viewport().mapToGlobal(p.toPoint() if hasattr(p, "toPoint") else p)
    # die Zeitleiste liegt am unteren Fensterrand: das Menü soll nach oben aufgehen (wie am Bildschirmrand), sonst
    # schneidet die Aufnahme es ab
    QtGui.QCursor.setPos(p - QtCore.QPoint(0, 130))
    ut_ring_scene(w)
    QtCore.QTimer.singleShot(700, pick)
    QtWidgets.QApplication.sendEvent(w, QtGui.QContextMenuEvent(QtGui.QContextMenuEvent.Mouse, w.rect().center()))


def ut_timeline():
    ut_rec()
    step("body", lambda: (st.__setitem__("b", box(0, 0, 60, 40, 20)), ut_fit()))
    step("select", lambda: select(st["b"], top(st["b"])))
    feature("Design_Fillet", lambda: type_into(0, "3"))
    step("deselect", Gui.Selection.clearSelection)
    wait()
    step("edit extrude", lambda: ut_dclick_glass(ut_entry("Design::Extrude")))
    wait()
    step("distance", lambda: type_into(0, "40"))
    wait()
    step("ok", accept)
    wait()
    step("fit", ut_fit)
    wait()
    step("roll back", lambda: ut_menu(ut_entry("Design::Extrude"), "Roll Back to Here"))
    wait(2)
    step("to end", lambda: click([b for b in timeline() if b.accessibleName() == "Go to End"][0]))
    wait()
    step("check", lambda: L("  timeline: volumes=%s errors=%s" % (volumes(), errors())))


scenario("start_timeline", ut_timeline, zoom=-1)


# --- Designs und Dateien --------------------------------------------------------------------------------------------
def ut_shortcut(label, key, mods=QtCore.Qt.NoModifier):
    """Tastenkürzel zeigen und wie getippt auslösen (über das Fenster, wie eine echte Taste)"""
    def go():
        ut_key(label)
        ut_activate()
        QtTest.QTest.keyClick(mw.windowHandle(), key, mods)
    step(label, go)


def ut_fill_input(text):
    """offenen Eingabedialog (Version sichern) Text tippen, OK; vorher ut_modal("Save Version", 260)"""
    wait()
    ut_type(lambda: ut_child(ut_dialog(), QtWidgets.QLineEdit), text)
    wait()
    step("ok", lambda: ut_press(ut_text_button(ut_dialog(), "OK", QtWidgets.QPushButton)))
    wait()


def ut_files():
    ut_rec()
    grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")

    def setup():  # wie beim Benutzer: eigener Projektordner, jede Änderung wird gespeichert
        st["projects"] = ut_projects("files")
        grp.SetBool("AlwaysSave", True)
        ut_on_close(lambda: grp.SetBool("AlwaysSave", False))
    step("setup", setup)
    ut_full()  # mit Browser: Designname und "Gesichert" stehen dort

    def body():  # als ein Schritt, den Rückgängig zurücknimmt (wie das Werkzeug)
        doc().openTransaction("Box")
        box(0, 0, 60, 40, 20, name="Block")
        doc().commitTransaction()
    step("body", lambda: (body(), ut_fit()))
    wait()
    step("undo", lambda: (ut_key("Ctrl + Z"), ut_ring_scene(button("Std_Undo")), Gui.runCommand("Std_Undo")))
    wait(2)
    step("redo", lambda: (ut_key("Ctrl + Shift + Z"), ut_ring_scene(button("Std_Redo")), Gui.runCommand("Std_Redo")))
    wait(2)

    def name_point():  # Mitte des Designnamens oben im Browser, als Punkt im Fenster (der Baum liegt in der Szene)
        t = ut_tree()
        r = t.visualItemRect(t.topLevelItem(0))
        return mw.mapFromGlobal(ut_tree_global(QtCore.QPoint(r.left() + 20, r.center().y())))
    step("hover name", lambda: QtTest.QTest.mouseMove(mw.windowHandle(), name_point()))  # zeigt den Stift
    wait()
    step("click name", lambda: (record_click(mw.mapToGlobal(name_point())),
                                QtTest.QTest.mouseClick(mw.windowHandle(), QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, name_point())))
    wait()
    ut_type(ut_tree_editor, "Bracket\n", ms=120)
    wait(2)
    step("saved", lambda: ut_ring_scene([l for l in visible(QtWidgets.QLabel) if l.text() == "Saved"][0]))
    wait()
    step("save version", lambda: (ut_key("Ctrl + S"), ut_ring_scene(button("MyCAD_SaveVersion")), ut_modal("Save Version", 260), Gui.runCommand("MyCAD_SaveVersion")))
    ut_fill_input("First block")
    step("home", ut_click_glass(lambda: [b for b in visible(QtWidgets.QToolButton) if b.toolTip() == "Home"][0]))
    wait(3)

    def tile_menu():
        """Rechtsklick auf die Kachel: Menü mit Umbenennen… und Löschen… zeigen, nichts wählen"""
        ts = [t for t in ut_start().findChildren(QtWidgets.QWidget, "StartTile") if t.isVisible()]
        t = ([x for x in ts if "Bracket" in [l.text() for l in x.findChildren(QtWidgets.QLabel, "StartName")]] or ts)[0]
        p = t.mapTo(mw, t.rect().center())

        def show():
            m = QtWidgets.QApplication.activePopupWidget()
            if not m:
                L("  files: no tile menu")
                return
            # das Menü öffnet beim Drücken; das Loslassen geht wie bei echter Maus an das Menü
            QtTest.QTest.mouseRelease(m.windowHandle(), QtCore.Qt.RightButton, QtCore.Qt.NoModifier, QtCore.QPoint(-5, -5))
            acts = {a.text(): a for a in m.actions() if a.text()}
            L("  files: tile menu %s" % list(acts))
            for i, name in enumerate(("Rename…", "Delete…")):
                if name in acts:
                    QtCore.QTimer.singleShot(300 + 900 * i, lambda a=acts[name]: m.setActiveAction(a))
            QtCore.QTimer.singleShot(2400, m.close)
        QtCore.QTimer.singleShot(700, show)
        record_click(mw.mapToGlobal(p))
        QtTest.QTest.mouseMove(mw.windowHandle(), p)
        QtTest.QTest.mousePress(mw.windowHandle(), QtCore.Qt.RightButton, QtCore.Qt.NoModifier, p)  # kehrt erst nach dem Menü zurück
    step("right-click", tile_menu)
    wait(3)

    def back():
        b = [b for b in visible(QtWidgets.QToolButton) if b.toolTip() == "Back to Design"][0]
        ut_ring(b)
        b.click()
    step("back", back)
    wait(2)
    step("check", lambda: L("  files: file=%s label=%s folders=%s" % (doc().FileName, doc().Label, sorted(os.listdir(st["projects"])))))


scenario("file_basics", ut_files, zoom=-1)


# --- Versionen ------------------------------------------------------------------------------------------------------
def ut_versions():
    ut_rec()
    grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")

    def always():
        grp.SetBool("AlwaysSave", True)  # wie beim Benutzer: jede Änderung wird gespeichert und eine Version
        ut_on_close(lambda: grp.SetBool("AlwaysSave", False))
    step("always save", always)
    # Aufbau ohne Aufnahme (Version benennen gehört zu file_basics): Block, benannte Version, dann abgerundet
    step("body", lambda: (st.__setitem__("b", box(0, 0, 60, 40, 20, name="Block")), ut_fit()))
    wait(3)
    step("save version", lambda: (ut_modal("Save Version", 260), Gui.runCommand("MyCAD_SaveVersion")))
    wait()
    step("name", lambda: (ut_child(ut_dialog(), QtWidgets.QLineEdit).setText("Before the fillet"),
                          ut_text_button(ut_dialog(), "OK", QtWidgets.QPushButton).click()))
    wait()
    step("select", lambda: select(st["b"], top(st["b"])))
    step("Design_Fillet", lambda: Gui.runCommand("Design_Fillet"))
    wait()
    step("radius", lambda: type_into(0, "6"))
    wait()
    step("ok", accept)
    step("deselect", Gui.Selection.clearSelection)
    wait(3)
    ut_clip_starts()
    wait()
    step("place", lambda: ut_modal("Versions", 140))
    ci_variant("Design_Versions")  # ▾ neben Version sichern → Versionen, mit Menü im Bild
    wait()

    def pick():
        lst = ut_child(ut_dialog("Versions"), QtWidgets.QListWidget, lambda l: l.accessibleName() == "Versions")
        row = [i for i in range(lst.count()) if "Before the fillet" in lst.item(i).text()][0]
        r = lst.visualItemRect(lst.item(row))
        record_click(lst.viewport().mapToGlobal(r.center()))
        lst.setCurrentRow(row)
    step("pick", pick)
    wait()
    step("compare", lambda: ut_press(ut_text_button(ut_dialog("Versions"), "Compare", QtWidgets.QPushButton)))
    wait(4)
    step("check", lambda: L("  versions: file=%s labels=%s" % (doc().FileName, [l.text() for l in visible(QtWidgets.QLabel)
                                                                              if l.parentWidget() and l.parentWidget().objectName() == "Comparison"])))


scenario("Design_Versions", ut_versions, zoom=-1)


# --- Einfügen, Exportieren, Drucken ---------------------------------------------------------------------------------
UT_DATA = "/workspace/tests/gui/data"


def ut_file_dialog(folder, name, button_text):
    """Qt-Dateidialog (unter Xvfb statt des Dialogs der Arbeitsumgebung): Ordner, Name tippen, bestätigen"""
    step("dialog", lambda: visible(QtWidgets.QFileDialog)[0].setDirectory(folder))
    wait()
    ut_type(lambda: [e for e in visible(QtWidgets.QFileDialog)[0].findChildren(QtWidgets.QLineEdit) if e.isVisible()][0], name)
    wait()
    # Fenster wieder aktiv: ohne Fenstermanager (Xvfb) bleibt es das nach dem Dialog nicht, Hinweise fielen aus (test_import)
    step(button_text, lambda: (ut_press(ut_text_button(visible(QtWidgets.QFileDialog)[0], button_text, QtWidgets.QPushButton)), ut_activate()))
    wait()


def ut_import():
    ut_rec()
    step("Design_Import", lambda: (ut_modal("Insert", 150), use("Design_Import")))
    ut_file_dialog(UT_DATA, "plate.dxf", "Open")
    wait()
    step("profile", lambda: select(*(lambda p: (p, ring_face(p)))([o for o in doc().Objects if o.TypeId == "Design::Profiles"][-1])))
    step("iso", ut_fit)
    feature("Design_Extrude", lambda: type_into(0, "5"))
    step("check", lambda: L("  import: volumes=%s errors=%s" % (volumes(), errors())))


scenario("Design_Import", ut_import, zoom=-1)


def ut_export():
    ut_rec()
    step("bodies", lambda: (st.update(a=box(0, 0, 40, 30, 15, name="Base"), c=make_body([circle(20, 15, 8)], 15, 20, "Pin")),
                            ut_fit()))
    wait()
    step("select", lambda: (ut_ring_at(App.Vector(30, 25, 15)), select(st["a"])))
    step("add", lambda: (ut_ring_at(App.Vector(20, 15, 30)), add_select(st["c"])))
    wait()
    step("Design_Export", lambda: (ut_modal("Export", 150), use("Design_Export")))
    out = "/out/export" if os.path.isdir("/out") else "/tmp"

    def types():
        d = visible(QtWidgets.QFileDialog)[0]
        c = [c for c in d.findChildren(QtWidgets.QComboBox) if c.isVisible() and c.findText("STL (*.stl)") >= 0][0]
        ut_ring(c)
        c.showPopup()
    def folder():  # leerer Ordner: sonst schlägt die Namensergänzung die Datei vom letzten Lauf vor
        import shutil
        shutil.rmtree(out, ignore_errors=True)
        os.makedirs(out, exist_ok=True)
        visible(QtWidgets.QFileDialog)[0].setDirectory(out)
    step("dialog", folder)
    wait()
    step("types", types)
    wait(2)
    step("close types", lambda: [c.hidePopup() for c in visible(QtWidgets.QFileDialog)[0].findChildren(QtWidgets.QComboBox) if c.isVisible()])
    ut_type(lambda: [e for e in visible(QtWidgets.QFileDialog)[0].findChildren(QtWidgets.QLineEdit) if e.isVisible()][0], "Bracket")
    wait()
    # Fenster wieder aktiv (wie in ut_file_dialog), sonst fehlt der Hinweis "Exported 2 bodies to …"
    step("Save", lambda: (ut_press(ut_text_button(visible(QtWidgets.QFileDialog)[0], "Save", QtWidgets.QPushButton)), ut_activate()))
    wait(3)
    step("check", lambda: L("  export: files=%s" % os.listdir(out)))


scenario("Design_Export", ut_export, zoom=-1)


def ut_print():
    ut_rec()

    def slicers():  # zwei Slicer zur Wahl (Attrappen: merken sich nur die Datei)
        folder = (os.environ.get("HOME") or "/tmp") + "/fake-slicers"
        os.makedirs(folder, exist_ok=True)
        for name in ("prusa-slicer", "orca-slicer"):
            path = os.path.join(folder, name)
            with open(path, "w") as f:
                f.write('#!/bin/sh\necho "$@" > "%s.args"\n' % path)
            os.chmod(path, 0o755)
        if folder not in os.environ.get("PATH", ""):
            os.environ["PATH"] = folder + os.pathsep + os.environ.get("PATH", "")
        App.ParamGet("User parameter:BaseApp/Preferences/MyCAD").RemString("Slicer")
        st["slicers"] = folder
    step("slicers", slicers)
    step("bodies", lambda: (st.update(a=box(0, 0, 40, 30, 15, name="Base"), c=make_body([circle(20, 15, 8)], 15, 20, "Pin")),
                            ut_fit()))
    wait()
    step("Design_Print", lambda: (ut_modal("Print", 260), use("Design_Print")))
    wait()

    def choose():
        c = ut_child(ut_dialog(), QtWidgets.QComboBox)
        ut_ring(c)
        c.showPopup()
    step("open list", choose)
    wait()
    step("prusa", lambda: (lambda c: (c.setCurrentIndex(c.findText("PrusaSlicer")), c.hidePopup()))(ut_child(ut_dialog(), QtWidgets.QComboBox)))
    wait()
    step("ok", lambda: ut_press(ut_text_button(ut_dialog(), "OK", QtWidgets.QPushButton)))
    step("opened", lambda: ut_key("PrusaSlicer opens with the 3MF", 2500))
    wait(2)
    step("check", lambda: L("  print: %s" % [open(os.path.join(st["slicers"], f)).read() for f in os.listdir(st["slicers"]) if f.endswith(".args")]))


scenario("Design_Print", ut_print, zoom=-1)


# --- Navigation -----------------------------------------------------------------------------------------------------
def ut_drag(a, b, button, mods, n=24, ms=40):
    def make():
        pa, pb = ut_at(*a), ut_at(*b)
        pts = [pa + (pb - pa) * (k / float(n)) for k in range(n + 1)]
        acts = [lambda: (record_click(ut_view().viewport().mapToGlobal(pa.toPoint())),
                         ut_mouse(QtCore.QEvent.MouseButtonPress, pa, button, button, mods))]
        acts += [lambda p=p: ut_mouse(QtCore.QEvent.MouseMove, p, QtCore.Qt.NoButton, button, mods) for p in pts[1:]]
        acts.append(lambda: ut_mouse(QtCore.QEvent.MouseButtonRelease, pb, button, QtCore.Qt.NoButton, mods))
        return acts
    ut_anim(make, n + 2, ms)


def ut_wheel(fx, fy, clicks, ms=120):
    def make():
        vp = ut_view().viewport()
        p = ut_at(fx, fy)

        def one(d):
            ev = QtGui.QWheelEvent(p, vp.mapToGlobal(p), QtCore.QPoint(0, 0), QtCore.QPoint(0, d), QtCore.Qt.NoButton,
                                   QtCore.Qt.NoModifier, QtCore.Qt.NoScrollPhase, False)
            QtWidgets.QApplication.sendEvent(ut_view(), ev)  # an den Viewport kam es nicht an (nicht spontan: kein Zoom)
        return [lambda: one(120 if clicks > 0 else -120) for _ in range(abs(clicks))]
    ut_anim(make, abs(clicks), ms)


def ut_cube_click(x, y):
    def go():
        cube = [i for i in ut_view().scene().items() if i.boundingRect().width() == 120 and i.boundingRect().height() == 150][0]
        v = ut_view()
        p = v.mapFromScene(cube.mapToScene(QtCore.QPointF(x, y)))
        record_click(v.viewport().mapToGlobal(p))
        QtTest.QTest.mouseMove(v.viewport(), p)
        QtTest.QTest.mouseClick(v.viewport(), QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)
    step("cube", go)


def ut_navigation():
    ut_rec()
    step("model", lambda: (box(-30, -20, 30, 20, 15, name="Base"), make_body([circle(0, 0, 10)], 15, 25, "Pin"),
                           ut_fit()))
    wait()
    step("cam", lambda: L("  nav before: %s" % Gui.ActiveDocument.ActiveView.getViewDirection()))
    step("rotate label", lambda: ut_key("Shift + middle drag: rotate", 6000))
    ut_drag((0.55, 0.55), (0.63, 0.53), QtCore.Qt.MiddleButton, QtCore.Qt.ShiftModifier, n=12, ms=140)
    wait()
    step("cam", lambda: L("  nav after rotate: %s" % Gui.ActiveDocument.ActiveView.getViewDirection()))
    step("pan label", lambda: ut_key("Middle drag: pan", 6000))
    ut_drag((0.62, 0.48), (0.45, 0.62), QtCore.Qt.MiddleButton, QtCore.Qt.NoModifier, n=12, ms=140)
    wait()
    step("zoom label", lambda: ut_key("Scroll wheel: zoom", 6000))
    ut_wheel(0.55, 0.5, 3, ms=400)
    wait()
    step("cam", lambda: L("  nav after pan/zoom: %s" % Gui.ActiveDocument.ActiveView.getCamera().splitlines()[1:4]))
    step("top label", lambda: ut_key("View cube: TOP", 2500))
    ut_cube_click(60, 40)
    wait(2)
    step("home label", lambda: ut_key("Home: whole model", 2500))
    ut_cube_click(19, 131)
    wait(2)


scenario("start_navigation", ut_navigation, view="none")


# --- Tastenkürzel ---------------------------------------------------------------------------------------------------
def ut_esc():
    step("esc", lambda: (ut_key("Esc", 900), ut_activate(), QtTest.QTest.keyClick(mw.windowHandle(), QtCore.Qt.Key_Escape)))
    wait()


def ut_report(label):
    step("report " + label, lambda: L("  key %s: dialog=%s edit=%s search=%s" % (
        label, bool(Gui.Control.activeDialog()), Gui.ActiveDocument.getInEdit() is not None,
        any(e.accessibleName() == "Search" for e in visible(QtWidgets.QLineEdit)))))


def ut_shortcuts():
    """Kürzel mit sichtbarer Wirkung. Esc ist hier kein Abbrechen: Esc schließt Drücken/Ziehen und Abrunden, behält aber
    das Ergebnis, und schließt Darstellung gar nicht; deshalb immer mit OK"""
    ut_rec()
    # Maus in die Mitte: sie stand noch auf Home am ViewCube (voriger Clip), das leuchtete den ganzen Clip lang
    step("mouse", lambda: ut_mouse(QtCore.QEvent.MouseMove, ut_at(0.5, 0.5), QtCore.Qt.NoButton, QtCore.Qt.NoButton))
    step("body", lambda: (st.__setitem__("b", box(0, 0, 60, 40, 20, name="Block")), ut_fit()))
    top_face = lambda: (ut_ring_at(App.Vector(30, 20, st["b"].Shape.BoundBox.ZMax)), select(st["b"], top(st["b"])))
    step("select", top_face)
    wait()
    ut_shortcut("Q", QtCore.Qt.Key_Q)
    wait()
    ut_report("Q")
    step("distance", lambda: type_into(0, "10"))
    wait()
    step("ok", ut_click_glass(lambda: [b for b in visible(QtWidgets.QPushButton) if b.text().replace("&", "") == "OK"][0]))
    wait()
    step("select", top_face)
    wait()
    ut_shortcut("F", QtCore.Qt.Key_F)
    wait()
    ut_report("F")
    step("radius", lambda: type_into(0, "4"))
    wait()
    step("ok", ut_click_glass(lambda: [b for b in visible(QtWidgets.QPushButton) if b.text().replace("&", "") == "OK"][0]))
    wait()
    step("select body", lambda: (ut_ring_at(App.Vector(30, 0, 10)), select(st["b"])))
    ut_shortcut("A", QtCore.Qt.Key_A)
    wait()
    ut_report("A")
    step("blue", ut_click_glass(lambda: ut_glass("Sierra Blue", QtWidgets.QToolButton, by="name")))
    wait()
    step("ok", ut_click_glass(lambda: [b for b in visible(QtWidgets.QPushButton) if b.text().replace("&", "") == "OK"][0]))
    wait()
    step("deselect", Gui.Selection.clearSelection)
    ut_shortcut("Ctrl + K", QtCore.Qt.Key_K, QtCore.Qt.ControlModifier)
    wait()
    ut_report("Ctrl+K")
    ut_type(ut_search_field, "measure", ms=120)
    wait()
    ut_esc()
    step("check", lambda: L("  shortcuts: volumes=%s errors=%s" % (volumes(), errors())))


scenario("start_shortcuts", ut_shortcuts, zoom=-1)


# --- Ganzes Fenster: Startseite, Browser, Zahlen, Hilfe ---------------------------------------------------------------
def ut_full():
    """ab hier das ganze Fenster aufnehmen: Browser und die Seitenleisten von Start- und Hilfeseite gehören zur Erklärung
    (record_start lässt links 306 px weg); die Bilder davor (schmaler) fallen weg"""
    def go():
        if harness._rec:
            harness._rec["left"] = 0
            del harness._rec["frames"][:]
    step("whole window", go)


def ut_projects(name):
    """eigener, leerer Projektordner für den Clip; danach wieder der alte"""
    import shutil
    grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")
    old = grp.GetString("ProjectsFolder", "")
    folder = "/tmp/clip-" + name
    shutil.rmtree(folder, ignore_errors=True)
    os.makedirs(folder)
    grp.SetString("ProjectsFolder", folder)
    ut_on_close(lambda: grp.SetString("ProjectsFolder", old) if old else grp.RemString("ProjectsFolder"))
    return folder


def ut_tree():
    t = [t for t in visible(QtWidgets.QTreeWidget) if t.topLevelItemCount()][0]
    harness._keep.append(t)
    return t


def ut_tree_global(p):
    """Punkt im Browser-Baum (Viewport-Koordinaten) als Bildschirmpunkt: der Baum liegt in einem Glas-Panel der Szene"""
    t = ut_tree()
    top = t
    while top.parentWidget():
        top = top.parentWidget()
    inner = t.viewport().mapTo(top, p)
    v = ut_view()
    return v.viewport().mapToGlobal(v.mapFromScene(top.graphicsProxyWidget().mapToScene(QtCore.QPointF(inner))))


def ut_tree_item(text):
    t = ut_tree()
    return t.findItems(text, QtCore.Qt.MatchRecursive)[0]


def ut_tree_click(point, button=QtCore.Qt.LeftButton):
    """echter Klick in den Baum (point() liefert Viewport-Koordinaten), im Clip mit Kreis"""
    def go():
        p = point()
        record_click(ut_tree_global(p))
        QtTest.QTest.mouseClick(ut_tree().viewport(), button, QtCore.Qt.NoModifier, p)
    return go


def ut_eye(text):
    """Auge vor dem Eintrag (FreeCADs Sichtbarkeits-Symbol, das erste Symbol der Zeile)"""
    t = ut_tree()
    r = t.visualItemRect(ut_tree_item(text))
    return QtCore.QPoint(r.left() + t.style().pixelMetric(QtWidgets.QStyle.PM_FocusFrameHMargin) + 1 + t.iconSize().height() // 2, r.center().y())


def ut_item_text(text):
    r = ut_tree().visualItemRect(ut_tree_item(text))
    return QtCore.QPoint(r.left() + 60, r.center().y())


def ut_pick_menu(text, after=900):
    """im nächsten aufgehenden Menü text wählen (das Menü blockiert: vorher einplanen); ohne text nur zeigen und schließen"""
    def pick():
        menu = QtWidgets.QApplication.activePopupWidget()
        acts = [a for a in (menu.actions() if menu else []) if text and a.text() == text]
        if menu:
            L("  menu: %s" % [a.text() for a in menu.actions() if a.text()])
        if acts:
            menu.setActiveAction(acts[0])
            QtCore.QTimer.singleShot(700, lambda: (record_click(menu.mapToGlobal(menu.actionGeometry(acts[0]).center())),
                                                   QtTest.QTest.keyClick(menu, QtCore.Qt.Key_Return)))
        elif menu:
            QtCore.QTimer.singleShot(1500, menu.close)
    QtCore.QTimer.singleShot(after, pick)


def ut_cover(hide):
    """Design-Ansicht unter Start- oder Hilfeseite aus- bzw. wieder einblenden: in der Aufnahme (mw.grab) zeichnen sich
    Werkzeugleiste und Browser des Designs sonst über die Seite (auch in file_basics.gif zu sehen)"""
    step("cover", lambda: mw.findChild(QtWidgets.QMdiArea).setVisible(not hide))


def ut_doc_item():
    """Eintrag des Designs im Browser; andere offene Designs (das leere vom Start des Laufs) blendet der Clip aus,
    Ursprung klappt er zu"""
    t = ut_tree()
    item = None
    for i in range(t.topLevelItemCount()):
        it = t.topLevelItem(i)
        it.setHidden(it.text(0) != doc().Label)
        if it.text(0) == doc().Label:
            item = it
    for o in t.findItems("Origin", QtCore.Qt.MatchRecursive):
        o.setExpanded(False)
    return item


def ut_tree_editor():
    return [e for e in ut_tree().findChildren(QtWidgets.QLineEdit) if e.isVisible()][0]


# --- Startseite -----------------------------------------------------------------------------------------------------
def ut_start():
    return [w for w in mw.findChildren(QtWidgets.QWidget, "StartPage")][0]


def ut_tile(name):
    return [t for t in ut_start().findChildren(QtWidgets.QWidget, "StartTile") if t.isVisible()
            and [l.text() for l in t.findChildren(QtWidgets.QLabel, "StartName")][0] == name][0]


def ut_start_page():
    ut_rec()

    def designs():
        """drei Designs im Projektordner des Clips; das offene heißt Bracket, zwei davon unter Recent"""
        folder = ut_projects("start")
        b = box(0, 0, 60, 40, 8, name="Plate")
        files = []
        for name, change in (("Lid", lambda: setattr(b.Tip, "Distance", 3)),
                             ("Hinge", lambda: make_body([circle(30, 20, 8)], 8, 20, "Pin")),
                             ("Bracket", lambda: setattr(b.Tip, "Distance", 12))):
            change()
            doc().recompute()
            ut_fit()
            path = os.path.join(folder, name, name + ".mycad")
            os.makedirs(os.path.dirname(path))
            if name == "Bracket":
                doc().saveAs(path)
            else:
                doc().saveCopy(path)
            files.append(path)
        mru = App.ParamGet("User parameter:BaseApp/Preferences/RecentFiles")
        old = {k: mru.GetString(k) for k in ("MRU0", "MRU1")}
        mru.SetString("MRU0", files[2])
        mru.SetString("MRU1", files[1])
        ut_on_close(lambda: [mru.SetString(k, v) if v else mru.RemString(k) for k, v in old.items()])
        st["projects"] = folder
    step("designs", designs)
    ut_full()
    wait()
    step("home", ut_click_glass(lambda: [b for b in visible(QtWidgets.QToolButton) if b.toolTip() == "Home"][0]))
    ut_cover(True)
    wait(3)

    def row(text):
        return [b for b in ut_start().findChildren(QtWidgets.QToolButton, "PaletteRow") if b.text() == text][0]
    step("recent", lambda: ut_press(row("Recent")))
    wait(2)
    step("projects", lambda: ut_press(row("Projects")))
    wait(2)
    step("all", lambda: ut_press(row("All Designs")))
    wait()

    def search():
        return ut_start().findChild(QtWidgets.QLineEdit, "StartSearch")
    step("search", lambda: ut_ring(search()))
    ut_type(search, "hin", ms=200)
    wait(2)
    step("clear", lambda: search().clear())
    wait()

    def rename():
        t = ut_tile("Hinge")
        p = t.mapTo(mw, t.rect().center())

        def pick():
            m = QtWidgets.QApplication.activePopupWidget()
            if not m:
                L("  start page: no menu")
                return
            ut_modal("Rename Design", 260)
            # das Menü öffnet beim Drücken; das Loslassen geht wie bei echter Maus an das Menü
            QtTest.QTest.mouseRelease(m.windowHandle(), QtCore.Qt.RightButton, QtCore.Qt.NoModifier, QtCore.QPoint(-5, -5))
            a = [a for a in m.actions() if a.text() == "Rename…"][0]
            m.setActiveAction(a)
            QtCore.QTimer.singleShot(700, lambda: (record_click(m.mapToGlobal(m.actionGeometry(a).center())),
                                                   QtTest.QTest.keyClick(m, QtCore.Qt.Key_Return)))
        QtCore.QTimer.singleShot(700, pick)
        record_click(mw.mapToGlobal(p))
        QtTest.QTest.mouseMove(mw.windowHandle(), p)
        QtTest.QTest.mousePress(mw.windowHandle(), QtCore.Qt.RightButton, QtCore.Qt.NoModifier, p)  # kehrt erst nach dem Menü zurück
    step("right-click", rename)
    wait(2)
    ut_type(lambda: ut_child(ut_dialog("Rename Design"), QtWidgets.QLineEdit), "Door hinge", ms=110)
    wait()
    step("ok", lambda: ut_press(ut_text_button(ut_dialog("Rename Design"), "OK", QtWidgets.QPushButton)))
    wait(3)
    step("check", lambda: L("  start page: folders=%s tiles=%s" % (sorted(os.listdir(st["projects"])), sorted(
        [l.text() for l in ut_start().findChildren(QtWidgets.QLabel, "StartName") if l.isVisible()]))))
    ut_cover(False)
    step("back", lambda: ut_press([b for b in ut_start().findChildren(QtWidgets.QToolButton)
                                   if b.isVisible() and b.toolTip() == "Back to Design"][0]))
    wait(2)


scenario("file_start_page", ut_start_page, zoom=-1)


# --- Browser --------------------------------------------------------------------------------------------------------
def ut_browser():
    ut_rec()
    grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")

    def setup():
        ut_projects("browser")
        grp.SetBool("AlwaysSave", True)  # wie beim Benutzer: still gespeichert, unten steht dann "Gesichert"
        ut_on_close(lambda: grp.SetBool("AlwaysSave", False))
        box(0, 0, 60, 40, 10, name="Base")
        make_body([circle(30, 20, 8)], 10, 20, "Pin")
        ut_fit()
        ut_tree().expandAll()
        ut_doc_item()
    step("setup", setup)
    ut_full()
    wait(3)

    def saved():
        w = [w for w in visible(QtWidgets.QWidget) if w.objectName() == "SavedState"]
        L("  browser: saved shown=%s file=%s" % (bool(w), doc().FileName))
        if w:
            ut_ring_scene(w[0])
            ut_key("Saved", 1800)
    step("saved", saved)
    wait(2)
    step("hide pin", ut_tree_click(lambda: ut_eye("Pin")))
    wait(2)
    step("show pin", ut_tree_click(lambda: ut_eye("Pin")))
    wait()

    def rename_pin():
        Gui.Selection.clearSelection()
        Gui.Selection.addSelection(doc().Name, [o for o in doc().Objects if o.Label == "Pin"][0].Name)
        ut_pick_menu("Rename")
        ut_tree_click(lambda: ut_item_text("Pin"), QtCore.Qt.RightButton)()
    step("rename pin", rename_pin)
    wait(2)
    ut_type(ut_tree_editor, "Shaft\n", ms=120)
    wait(2)
    step("name", ut_tree_click(lambda: (lambda r: QtCore.QPoint(r.left() + 40, r.center().y()))(ut_tree().visualItemRect(ut_doc_item()))))
    wait()
    ut_type(ut_tree_editor, "Bracket\n", ms=120)
    wait(3)
    step("check", lambda: L("  browser: label=%s file=%s bodies=%s" % (
        doc().Label, doc().FileName, [o.Label for o in doc().Objects if o.TypeId == "Design::Body"])))

    def view_menu():
        Gui.Selection.clearSelection()
        vp = ut_view().viewport()
        p = QtCore.QPoint(int(vp.width() * 0.75), int(vp.height() * 0.3))
        record_click(vp.mapToGlobal(p))
        ut_pick_menu(None)
        QtTest.QTest.mousePress(vp, QtCore.Qt.RightButton, QtCore.Qt.NoModifier, p)
        QtTest.QTest.mouseRelease(vp, QtCore.Qt.RightButton, QtCore.Qt.NoModifier, p)
    step("view menu", view_menu)
    wait(3)


scenario("browser", ut_browser, zoom=-1)


# --- Zahlen eingeben ------------------------------------------------------------------------------------------------
def ut_numbers():
    ut_rec()
    ut_profile(0, 0, 40, 30)
    step("select", lambda: select(st["sp"], "Face1"))
    step("Design_Extrude", lambda: use("Design_Extrude"))
    wait()

    def distance():
        return sorted(visible(QtWidgets.QAbstractSpinBox), key=lambda w: w.mapToGlobal(QtCore.QPoint(0, 0)).y())[0].lineEdit()

    def show(label):
        f = [o for o in doc().Objects if o.TypeId == "Design::Extrude"][-1]
        L("  numbers: %r -> %s" % (distance().text(), f.Distance))
        ut_key(label, 2200)
    for text, label in (("12,5", "12,5 = 12.5 mm"), ("1 in", "1 in = 25.4 mm"), ("2 * 7,5", "2 * 7,5 = 15 mm")):
        step("field", lambda: ut_ring_scene(distance().parentWidget()))
        ut_type(distance, text, ms=200)
        wait()
        step("show", lambda label=label: show(label))
        wait(2)
    step("ok", accept)
    wait()
    step("check", lambda: L("  numbers: volumes=%s errors=%s" % (volumes(), errors())))


scenario("numbers", ut_numbers, zoom=-1)


# --- Hilfe ----------------------------------------------------------------------------------------------------------
def ut_help_page():
    return [w for w in mw.findChildren(QtWidgets.QWidget, "HelpPage")][0]


def ut_still():
    """Clips im Hilfeartikel anhalten: jedes Bild wäre sonst neu, der Clip liefe in Echtzeit (unter Last minutenlang)"""
    step("still", lambda: [m.setPaused(True) for m in ut_help_page().findChildren(QtGui.QMovie)])


def ut_help():
    ut_rec()
    step("body", lambda: (box(0, 0, 60, 40, 20, name="Block"), ut_fit()))
    ut_full()
    wait()

    def hover():
        q = harness._pos(button("Design_Fillet"))
        p = ut_view().viewport().mapTo(mw, q.toPoint() if hasattr(q, "toPoint") else q)
        record_click(mw.mapToGlobal(p))
        QtTest.QTest.mouseMove(mw.windowHandle(), p)
    step("point at fillet", hover)
    wait(2)
    step("F1", lambda: (ut_key("F1"), QtTest.QTest.keyClick(mw.windowHandle(), QtCore.Qt.Key_F1)))
    ut_cover(True)
    ut_still()
    wait(3)

    def search():
        return ut_help_page().findChild(QtWidgets.QLineEdit, "StartSearch")
    step("search", lambda: ut_ring(search()))
    ut_type(search, "donut", ms=180)
    wait(2)
    step("enter", lambda: (ut_key("Enter"), QtTest.QTest.keyClick(search(), QtCore.Qt.Key_Return)))
    ut_still()
    wait(3)
    step("check", lambda: L("  help: article=%s" % ut_help_page().findChild(QtWidgets.QTextBrowser, "HelpArticle")
                            .document().toPlainText().replace("￼", "").strip().split("\n")[0]))
    ut_cover(False)
    step("back", lambda: ut_press([b for b in ut_help_page().findChildren(QtWidgets.QToolButton)
                                   if b.isVisible() and b.toolTip() == "Back"][0]))
    wait(2)


scenario("help", ut_help, zoom=-1)
