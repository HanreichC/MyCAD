# SPDX-License-Identifier: LGPL-2.1-or-later
"""Erklär-Clips der Werkstatt-Werkzeuge aus Phase 12: Zahnrad, Scharnier, Schnapphaken samt Rastfenster, Normteil,
Stückliste, Code-Schritt, Druckertest, Vorlagen, Von Fusion umsteigen. Läuft nach create.py und utilities.py in den
Globals von tools/help_images.py und nutzt deren Helfer (cr_*, ut_*). Eigene Namen beginnen mit ws_."""


def ws_ok():
    step("ok", cr_seq(cr_ok_ring, accept, lambda: L("  ok: errors=%s volumes=%s" % (errors(), volumes()))))


def ws_command(words, title=None):
    """Befehl über Strg+K wie getippt (Stückliste und Druckertest stehen nicht in der Werkzeugleiste)"""
    step("ctrl+k", lambda: (ut_key("Ctrl + K"), ut_activate(), QtTest.QTest.keyClick(mw, QtCore.Qt.Key_K, QtCore.Qt.ControlModifier)))
    wait()
    ut_type(ut_search_field, words, ms=110)
    wait()
    step("enter", lambda: ((ut_modal(title, 160) if title else None), ut_key("Enter"),
                           QtTest.QTest.keyClick(ut_search_field(), QtCore.Qt.Key_Return)))


def ws_dialog_button(title, text):
    return lambda: ut_press(ut_text_button(ut_dialog(title), text, QtWidgets.QPushButton))


# --- Zahnrad: eins mit 24 Zähnen, ein kleines greift ein -----------------------------------------------------------
def ws_gear():
    cr_build("fit", cr_fit(-20, -20, 0, 38, 20, 6))
    cr_tool("Design_Gear", lambda: cr_type_at("Module", "1.5"), lambda: cr_type_at("Teeth", "24"),
            lambda: cr_type_at("Bore", "8"), variant=True)
    wait()
    # zweites Rad: gleiches Modul, Abstand 1,5 × (24 + 12) / 2 = 27, um einen halben Zahn gedreht (180° + 180° / 12)
    cr_tool("Design_Gear", lambda: cr_type_at("Module", "1.5"), lambda: cr_type_at("Teeth", "12"),
            lambda: cr_type_at("Position X", "27"), lambda: cr_type_at("Rotation", "195"), variant=True)
    wait(2)


# --- Scharnier ------------------------------------------------------------------------------------------------------
def ws_hinge():
    cr_build("fit", cr_fit(0, -15, 0, 50, 15, 6))
    cr_tool("Design_Hinge", lambda: cr_type_at("Length", "50"), lambda: cr_type_at("Knuckles", "7"), variant=True)
    wait(2)


# --- Schnapphaken auf einem Deckel, dann das Rastfenster in der Wand darüber ---------------------------------------
def ws_snap_hook():
    cr_build("lid", cr_fit(-25, -15, 0, 25, 15, 20), keep("lid", lambda: box(-25, -15, 25, 15, 3, name="Lid")))
    step("face", lambda: cr_sel(st["lid"], top(st["lid"]), V(-12, 0, 3)))
    cr_tool("Design_SnapHook", lambda: cr_type_at("Length", "14"), variant=True)
    wait()
    # Gegenstück: eine Wand so dick wie die Rastnase, außen am Balken (Haken: x 0 … Dicke 1,5, Nase bis 2,5)
    cr_build("wall", keep("wall", lambda: box(1.5, -6, 2.5, 14, 17, z=3, name="Wall")))
    step("hook", lambda: cr_sel([o for o in doc().Objects if o.TypeId == "Design::Primitive"][-1].Bodies[0], "", V(0.75, 4, 10)))
    wait()
    step("Design_SnapRecess", lambda: cr_use_variant("Design_SnapRecess"))
    wait(3)
    step("check", lambda: L("  snap recess: errors=%s volumes=%s" % (errors(), volumes())))


# --- Normteile: Typ wechseln, Vorschau folgt ------------------------------------------------------------------------
def ws_standard_part():
    cr_build("fit", cr_fit(-25, -25, 0, 25, 25, 25))
    cr_tool("Design_StandardPart", *[lambda t=t: cr_pick("Type", t) for t in
                                     ("Hex Nut", "Washer", "Heat-Set Insert", "Ball Bearing", "Socket Head Screw")],
            lambda: cr_pick("Size", "M5"), lambda: cr_type_at("Length", "20"), variant=True)
    wait(2)


# --- Stückliste: Platte mit vier Schrauben und einem Lager ----------------------------------------------------------
def ws_parts_list():
    ut_rec()  # Dialog im Bild, Textcursor ohne Blinken

    def build():
        import Design
        st["b"] = plate = box(-30, -20, 30, 20, 5, name="Plate")
        face = top(plate)
        for kind, x, y, extra in [("Socket Head Screw", sx * 22, sy * 12, {"Size": "M3", "Length": 12})
                                  for sx in (-1, 1) for sy in (-1, 1)] + [("Ball Bearing", 0, 0, {"Bearing": "608"})]:
            f = doc().addObject("Design::Primitive", "Primitive")
            Design.root(doc()).addObject(f)
            Design.addToTimeline(f)
            f.Type = kind
            f.Plane = (plate, [face])
            f.PositionX, f.PositionY = x, y
            for k, v in extra.items():
                setattr(f, k, v)
            Design.newBody(f)
        doc().recompute()
    cr_build("parts", cr_fit(-30, -20, 0, 30, 20, 17), build)
    ws_command("parts list", "Parts List")
    wait(3)
    step("copy", ws_dialog_button("Parts List", "Copy"))
    wait()
    step("check", lambda: L("  parts list: %r" % QtWidgets.QApplication.clipboard().text()))
    step("close", ws_dialog_button("Parts List", "Close"))
    wait()


# --- Code-Schritt: zweites Loch dazuschreiben, Ausführen ------------------------------------------------------------
def ws_code_edit():
    return [e for e in visible(QtWidgets.QPlainTextEdit) if e.objectName() == "CodeEdit"][0]


def ws_code_keys(text, ms=70):
    def make():
        e = ws_code_edit()
        acts = [lambda: (e.setFocus(), e.moveCursor(QtGui.QTextCursor.End))]
        for c in text:
            acts.append(lambda c=c: QtTest.QTest.keyClick(e, QtCore.Qt.Key_Return) if c == "\n" else QtTest.QTest.keyClicks(e, c))
        return acts
    ut_anim(make, len(text) + 1, ms)


def ws_code_step():
    ut_rec()  # Textcursor im Code ohne Blinken (sonst ist jedes Bild neu)
    cr_build("fit", cr_fit(-22, -15, 0, 22, 15, 5))
    step("Design_CodeStep", lambda: cr_use_variant("Design_CodeStep"))
    wait(2)
    ws_code_keys("result = cut(result, cylinder(4, 5, at=(13, 0, 0)))\n")
    wait()
    step("run", ut_click_glass(lambda: [b for b in visible(QtWidgets.QPushButton) if b.objectName() == "RunCode"][0]))
    wait(2)
    ws_ok()
    wait(2)


# --- Druckertest ----------------------------------------------------------------------------------------------------
def ws_printer_test():
    ut_rec()
    ws_command("printer test")
    wait(3)
    step("fit", ut_fit)
    wait(3)
    step("check", lambda: L("  printer test: %s errors=%s volumes=%s" % (doc().Label, errors(), volumes())))


# --- Vorlagen: Box mit Deckel von der Startseite, Breite in der Notiz ändern ---------------------------------------
def ws_templates():
    ut_rec()
    ut_full()
    wait()
    step("home", ut_click_glass(lambda: [b for b in visible(QtWidgets.QToolButton) if b.toolTip() == "Home"][0]))
    ut_cover(True)
    wait(3)

    def template():
        b = ut_start().findChild(QtWidgets.QToolButton, "TemplateButton")
        ut_pick_menu("Box with Lid")
        ut_ring(b)
        b.click()  # kehrt erst nach dem Menü zurück, dann steht die Vorlage schon da
        mw.findChild(QtWidgets.QMdiArea).setVisible(True)  # gleich wieder zeigen, sonst ein leeres Bild im Clip
    step("template", template)
    wait()
    step("fit", lambda: (ut_fit(), Gui.ActiveDocument.ActiveView.zoomOut()))
    wait(2)

    def to_width():  # ans Ende der Zeile "Width = 60 mm" (Zeile 2, nach dem Titel)
        e = ut_note_edit()
        c = e.textCursor()
        c.movePosition(QtGui.QTextCursor.Start)
        c.movePosition(QtGui.QTextCursor.NextBlock)
        c.movePosition(QtGui.QTextCursor.EndOfBlock)
        e.setFocus()
        e.setTextCursor(c)
        off = e.viewport().mapTo(e, e.cursorRect(c).center()) - e.rect().center()
        record_click(ut_view().viewport().mapToGlobal((QtCore.QPointF(harness._pos(e)) + QtCore.QPointF(off)).toPoint()))
    step("click line", to_width)
    step("animate", lambda: harness.record_motion(
        [lambda: QtTest.QTest.keyClick(ut_note_edit(), QtCore.Qt.Key_Backspace)] * 5
        + [lambda c=c: QtTest.QTest.keyClicks(ut_note_edit(), c) for c in "90 mm"]
        + [lambda: (ut_key("Enter"), QtTest.QTest.keyClick(ut_note_edit(), QtCore.Qt.Key_Return))], 120))
    wait(4)
    step("check", lambda: L("  template: %s volumes=%s errors=%s text=%r" % (doc().Label, volumes(), errors(),
                                                                          ut_note_edit().toPlainText())))


# --- Von Fusion umsteigen: Strg+K kennt die Fusion-Wörter -----------------------------------------------------------
def ws_from_fusion():
    ut_rec()
    step("body", lambda: (st.__setitem__("b", box(0, 0, 60, 40, 15, name="Block")), ut_fit()))
    wait()
    ut_clip_starts()
    step("face", lambda: (ut_ring_at(App.Vector(30, 20, 15)), select(st["b"], top(st["b"]))))
    wait()
    ws_command("offset face")
    wait()
    step("distance", lambda: type_into(0, "10"))
    wait()
    step("ok", ut_click_glass(lambda: [b for b in visible(QtWidgets.QPushButton) if b.text().replace("&", "") == "OK"][0]))
    wait()
    step("deselect", Gui.Selection.clearSelection)
    step("ctrl+k", lambda: (ut_key("Ctrl + K"), ut_activate(), QtTest.QTest.keyClick(mw, QtCore.Qt.Key_K, QtCore.Qt.ControlModifier)))
    wait()
    ut_type(ut_search_field, "change parameters", ms=110)
    wait(2)
    ut_esc()
    step("check", lambda: L("  from fusion: volumes=%s errors=%s" % (volumes(), errors())))


scenario("Design_Gear", ws_gear, view="none", fixed=True)
scenario("Design_Hinge", ws_hinge, view="none", fixed=True)
scenario("Design_SnapHook", ws_snap_hook, view="none", fixed=True)
scenario("Design_StandardPart", ws_standard_part, view="none", fixed=True)
scenario("Design_PartsList", ws_parts_list, view="none", fixed=True)
scenario("Design_CodeStep", ws_code_step, view="none", fixed=True)
scenario("Design_PrinterTest", ws_printer_test, view="none", fixed=True)
scenario("start_templates", ws_templates, view="none", fixed=True)
scenario("start_from_fusion", ws_from_fusion, zoom=-1)
