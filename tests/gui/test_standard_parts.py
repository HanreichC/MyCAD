# SPDX-License-Identifier: LGPL-2.1-or-later
"""Normteile (Plan 12.7): "Standard Part" öffnet das Panel mit einer Zylinderschraube; Größe und Form lassen sich dort
wählen; nach OK ist sie ein Körper. Die Stückliste zählt die Normteile und kopiert sie als Tabelle. Fehler stehen als
FAIL im Protokoll."""
from harness import *
from harness import _keep
import Design

state = {}


def primitives():
    return [o for o in doc().Objects if o.TypeId == "Design::Primitive"]


def setup():
    App.newDocument("Parts")


def start():
    Gui.runCommand("Design_StandardPart")


def check_panel():
    f = primitives()[-1]
    check("the panel starts with a socket head screw", f.Type == "Socket Head Screw" and Gui.Control.activeDialog(), f.Type)
    sizes = [c for c in visible(QtWidgets.QComboBox) if c.findText("M12") >= 0]
    check("thread sizes M2 … M12 to choose", bool(sizes))
    if sizes:
        _keep.append(sizes[0])
        sizes[0].setCurrentIndex(sizes[0].findText("M4"))
    shot("panel")


def check_screw():
    f = primitives()[-1]
    bodies = [o for o in doc().Objects if o.TypeId == "Design::Body"]
    check("OK: the screw is a body", len(bodies) == 1 and bodies[0].Shape.isValid() and not Gui.Control.activeDialog())
    check("with the size from the panel", Design.partName(f) == "ISO 4762 M4 × 20", Design.partName(f))


def second():
    """zweite gleiche Schraube und eine Mutter per Skript: die Liste fasst Gleiches zusammen"""
    for kind in ("Socket Head Screw", "Hex Nut"):
        f = doc().addObject("Design::Primitive", "Primitive")
        Design.root(doc()).addObject(f)
        Design.addToTimeline(f)
        f.Type = kind
        f.Size = "M4"
        f.Length = 20
        Design.newBody(f)
    doc().recompute()


def open_list():
    QtCore.QTimer.singleShot(0, lambda: Gui.runCommand("Design_PartsList"))


def check_list():
    dialogs = [d for d in visible(QtWidgets.QDialog) if d.windowTitle() == "Parts List"]
    check("the parts list opens", bool(dialogs))
    if not dialogs:
        return
    table = dialogs[0].findChild(QtWidgets.QTableWidget)
    _keep.extend([dialogs[0], table])
    rows = [(table.item(r, 0).text(), table.item(r, 1).text()) for r in range(table.rowCount())]
    check("same parts are counted together", rows == [("1", "ISO 4032 M4"), ("2", "ISO 4762 M4 × 20")], str(rows))
    copy = [b for b in dialogs[0].findChildren(QtWidgets.QPushButton) if b.text() == "Copy"][0]
    copy.click()
    text = QtWidgets.QApplication.clipboard().text()
    check("Copy puts a table on the clipboard", text.startswith("Qty\tPart\n1\tISO 4032 M4\n"), repr(text[:60]))
    shot("list")
    dialogs[0].reject()


in_order([
    ("setup", setup), ("wait", lambda: None),
    ("start", start), ("wait", lambda: None),
    ("check panel", check_panel), ("wait", lambda: None),
    ("ok", ok), ("wait", lambda: None),
    ("check screw", check_screw),
    ("second", second), ("wait", lambda: None),
    ("list", open_list), ("wait", lambda: None),
    ("check list", check_list),
])
