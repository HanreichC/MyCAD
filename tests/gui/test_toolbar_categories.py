# SPDX-License-Identifier: LGPL-2.1-or-later
"""Kompakte Werkzeugleiste (Plan 12.3): eine Zeile mit Datei, den häufigsten Werkzeugen und Kategorie-Knöpfen. Ein
Klick auf eine Kategorie öffnet ein Glas-Popover mit allen ihren Werkzeugen im Raster mit Namen; ein Werkzeug darin
startet und schließt das Popover; zweiter Klick, Klick daneben oder Esc schließen es. Einstellung "All Tools" zeigt die
alte Leiste. Fehler stehen als FAIL im Protokoll."""
from harness import *
from harness import _pos

grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")
grp.SetBool("ToolbarFull", False)
ORDER = ["FILE", "CREATE", "MODIFY", "CONSTRUCT", "ASSEMBLE", "INSPECT", "PRINT", "UTILITIES"]
state = {}


def cats():
    found = [b for b in visible(QtWidgets.QToolButton) if b.objectName() == "CategoryButton"]
    return sorted(found, key=lambda b: _pos(b).x())


def cat(key):
    return [b for b in cats() if b.property("category") == key][0]


def on_bar(cmd):
    return [b for b in visible(QtWidgets.QToolButton) if b.objectName() == "GlassButton" and b.property("command") == cmd]


def setup():
    mw.resize(1600, 950)  # ein 1600 breites Fenster mit offener Seitenleiste: eine Reihe (schmaler bricht sie um)
    App.newDocument("Categories")


def check_compact():
    check("eight categories in order", [b.property("category") for b in cats()] == ORDER,
          str([b.property("category") for b in cats()]))
    check("frequent tools stay direct", all(on_bar(c) for c in ("Design_CreateSketch", "Design_Extrude", "Design_Hole",
                                                                "Design_Fillet", "Design_PressPull", "Design_Measure")))
    check("the rest waits in the categories", not on_bar("Design_Revolve") and not on_bar("Design_Chamfer"))
    # eine Reihe wie bei Fusion: Symbole oben, die Kategorien als Überschriften darunter, nichts umgebrochen
    ys = {round(_pos(b).y()) for b in cats()}
    tools = {round(_pos(on_bar(c)[0]).y()) for c in ("Std_Undo", "Design_Extrude", "Design_Measure", "MyCAD_Search")}
    check("one row", max(ys) - min(ys) <= 2 and max(tools) - min(tools) <= 2 and max(tools) < min(ys),
          "captions %s tools %s" % (sorted(ys), sorted(tools)))
    check("categories have a name", all(b.accessibleName() for b in cats()))
    shot("compact")


def check_create():
    tools = on_bar("Design_Revolve")
    check("CREATE opens its tools", bool(tools) and bool(on_bar("Design_Coil")), str(len(tools)))
    if tools:
        b = tools[0]
        check("tools in the popover show their names", b.toolButtonStyle() == QtCore.Qt.ToolButtonTextUnderIcon and bool(b.text()),
              repr(b.text()))
        check("popover below its button", _pos(b).y() > _pos(cat("CREATE")).y() + 20)
        first = max(on_bar("Design_CreateSketch"), key=lambda t: _pos(t).y())  # im Popover, nicht in der Toolbar
        p = _pos(first)
        beside = QtCore.QPoint(int(p.x() - first.width() / 2 - 4), int(p.y()))
        check("the glass reaches around the tools", view().itemAt(beside) is not None, str((beside.x(), beside.y())))
    check("its button looks open", cat("CREATE").isChecked())
    shot("create")


def check_switched():
    check("MODIFY replaces CREATE", bool(on_bar("Design_Chamfer")) and not on_bar("Design_Revolve"))
    check("only the open category looks open", cat("MODIFY").isChecked() and not cat("CREATE").isChecked())


def closed(why):
    return lambda: check(why, not on_bar("Design_Revolve") and not on_bar("Design_Chamfer") and not on_bar("Design_AnglePlane")
                         and not any(b.isChecked() for b in cats()))


def new_from_file():
    state["docs"] = len(App.listDocuments())
    click(on_bar("Std_New")[0])


def check_new():
    check("a tool in the popover runs and closes it", len(App.listDocuments()) == state["docs"] + 1 and not on_bar("Std_Open"),
          "%d -> %d" % (state["docs"], len(App.listDocuments())))


def full():
    grp.SetBool("ToolbarFull", True)
    mw.resize(1501, 950)  # layout() liest die Einstellung (in der App schaltet setFullToolbar sofort um)


in_order([
    ("setup", setup), ("wait", lambda: None),
    ("check compact", check_compact),
    ("create", lambda: click(cat("CREATE"))), ("wait", lambda: None),
    ("check create", check_create),
    ("again", lambda: click(cat("CREATE"))), ("wait", lambda: None),
    ("closed by second click", closed("second click closes")),
    ("create", lambda: click(cat("CREATE"))), ("wait", lambda: None),
    ("modify", lambda: click(cat("MODIFY"))), ("wait", lambda: None),
    ("check switched", check_switched),
    ("esc", esc), ("wait", lambda: None),
    ("closed by esc", closed("Esc closes")),
    ("construct", lambda: click(cat("CONSTRUCT"))), ("wait", lambda: None),
    ("outside", lambda: view_click(0.5, 0.6)), ("wait", lambda: None),
    ("closed by outside", closed("a click beside it closes")),
    ("file", lambda: click(cat("FILE"))), ("wait", lambda: None),
    ("new", new_from_file), ("wait", lambda: None),
    ("check new", check_new),
    ("full", full), ("wait", lambda: None),
    ("check full", lambda: check("setting All Tools: every tool, no categories", bool(on_bar("Design_Revolve")) and not cats())),
])
