# SPDX-License-Identifier: LGPL-2.1-or-later
# runs: 2  (tests/run_all.sh startet ihn zweimal mit demselben Home: erst umstellen, dann prüfen)
"""Deutsche Oberfläche. Mit eigenem Home zweimal ausführen (die Sprache wirkt nach einem Neustart):
    MYCAD_HOME=/tmp/de tests/gui/run.sh tests/gui/test_german.py /tmp/de1   → stellt auf Deutsch, beendet
    MYCAD_HOME=/tmp/de tests/gui/run.sh tests/gui/test_german.py /tmp/de2   → prüft und macht Bilder
Protokolliert jeden sichtbaren Text, der noch englisch ist (Toolbar, Startseite, Einstellungen, Extrude-Dialog)."""
import os
import harness
from harness import *

harness.START_PAGE = True
general = App.ParamGet("User parameter:BaseApp/Preferences/General")
english = {"New Design", "Recent", "Projects", "Search designs", "Extrude", "Revolve", "Sketch", "Fillet", "Settings",
           "Keys", "Language", "Distance", "Operation", "New Body", "One Side", "CREATE", "MODIFY",
           "Rotate", "Pan", "Zoom", "Select", "Body material", "Show tool names", "Finish Sketch", "Line", "Rectangle"}


def texts():
    found = set()
    for w in QtWidgets.QApplication.allWidgets():
        if not w.isVisible():
            continue
        for t in (getattr(w, "text", lambda: "")() if hasattr(w, "text") and callable(getattr(w, "text")) else "",
                  w.toolTip(), str(w.property("label") or "")):
            if isinstance(t, str) and t.strip():
                found.add(t.strip())
        if isinstance(w, QtWidgets.QComboBox):
            found.update(w.itemText(i) for i in range(w.count()))
    return found


def tree_texts():
    texts = set()
    for tree in visible(QtWidgets.QTreeWidget):
        it = QtWidgets.QTreeWidgetItemIterator(tree)
        while it.value():
            texts.add(it.value().text(0)); it += 1
    return texts


def check(tag):
    left = sorted(t for t in texts() if t in english)
    L("%s: noch englisch=%s" % (tag, left))


def settings():
    def act():
        d = [w for w in visible(QtWidgets.QDialog) if w.objectName() == "Settings"][0]
        check("Einstellungen")
        d.grab().save(os.environ["OUT"] + ".settings.png")
        d.accept()
    QtCore.QTimer.singleShot(900, act)
    Gui.runCommand("MyCAD_Settings")


if general.GetString("Language", "English") != "German":
    general.SetString("Language", "German")
    App.ParamGet("User parameter:BaseApp/Preferences/MyCAD").SetBool("ToolNames", True)
    App.saveParameter()
    L("Sprache auf Deutsch gestellt, bitte erneut starten")
    os._exit(0)

run([
    ("start", lambda: (check("Startseite"), shot("start"))),
    ("new", lambda: Gui.runCommand("Std_New")), ("wait", lambda: None),
    ("main", lambda: (check("Arbeitsfläche"), shot("main"))),
    ("settings", settings), ("wait", lambda: None),
    ("body", lambda: make_body(rect(0, 0, 40, 30), 0, 10, "Box")),
    ("sketch", lambda: click(button("Design_CreateSketch"))),
    ("xy", lambda: Gui.Selection.addSelection([o for o in doc().Objects if o.Name.startswith("XY_Plane")][0])),
    ("sketchbar", lambda: (check("Skizze"), shot("sketch"))),
    ("leave", lambda: click(button("Sketcher_LeaveSketch"))), ("wait", lambda: None),
    ("extrude", lambda: (Gui.Selection.clearSelection(), Gui.Selection.addSelection(doc().Name, [o for o in doc().Objects if o.TypeId == "Design::Profiles"][0].Name, "Face1"), click(button("Design_Extrude")))),
    ("dialog", lambda: (check("Extrude-Dialog"), shot("extrude"))),
    ("komma", lambda: harness.check("Zahlen in der deutschen Oberfläche mit Komma (10,00 mm)",
                                    any("," in b.text() and "mm" in b.text() for b in visible(QtWidgets.QAbstractSpinBox)),
                                    str([b.text() for b in visible(QtWidgets.QAbstractSpinBox)]))),
    ("punkt", lambda: type_field("Abstand", "2.5")),
    ("punkt ok", lambda: harness.check("auch in der deutschen Oberfläche ist 2.5 zweieinhalb, nicht 25",
                                       abs([o for o in doc().Objects if o.TypeId == "Design::Extrude"][-1].Distance.Value - 2.5) < 1e-9,
                                       str([o for o in doc().Objects if o.TypeId == "Design::Extrude"][-1].Distance))),
    ("komma2", lambda: type_field("Abstand", "3,5")),
    ("komma2 ok", lambda: harness.check("3,5 ist dreieinhalb", abs([o for o in doc().Objects if o.TypeId == "Design::Extrude"][-1].Distance.Value - 3.5) < 1e-9,
                                        str([o for o in doc().Objects if o.TypeId == "Design::Extrude"][-1].Distance))),
    ("ok", ok), ("wait", lambda: None),
    ("labels", lambda: L("Objektnamen=%s" % sorted(o.Label for o in doc().Objects if o.TypeId not in ("App::Line", "App::Plane", "App::Point", "Design::Profiles")))),
    ("tree", lambda: harness.check("Browser: Ursprung deutsch (XZ-Ebene, X-Achse)", {"XZ-Ebene", "X-Achse"} <= tree_texts(), str(sorted(tree_texts())))),
])
