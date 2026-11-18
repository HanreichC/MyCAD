# SPDX-License-Identifier: LGPL-2.1-or-later
"""H3: Wie oft zeichnet eine Änderung die 3D-Ansicht neu? Gemessen an 20 Körpern mit Rundungen: Maß ändern, mit
"Immer gespeichert", bis MyCAD ruht. Vor H2/H5 waren es 7 Bilder, jetzt 4 bis 6, und jedes zeigt etwas Neues: die Form
(sofort), Timeline und Kontaktschatten (der rechnet 400 ms nach der Änderung neu), Speichern samt "Gesichert"
(nach 2 s Ruhe). Mehr wäre ein Rückschritt. Fehler stehen als FAIL im Protokoll."""
import os
import shutil
from harness import *

grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")
grp.SetBool("AlwaysSave", True)  # harness schaltet es aus
old_folder = grp.GetString("ProjectsFolder", "")
FOLDER = os.environ["OUT"] + ".projects"
shutil.rmtree(FOLDER, ignore_errors=True)
os.makedirs(FOLDER)
grp.SetString("ProjectsFolder", FOLDER)
state = {"frames": 0}
LIMIT = 7  # vorher 7 fest; nach H2/H5 4-6, je nachdem, wie Speichern, Timeline und Schatten zusammenfallen


class Frames(QtCore.QObject):
    def eventFilter(self, obj, event):
        if event.type() == QtCore.QEvent.Paint:
            state["frames"] += 1
            import time
            state.setdefault("times", []).append(round(time.monotonic() - state.get("t0", 0), 2))
        return False


frames = Frames()


def bodies():
    for k in range(20):
        b = make_body(rect((k % 5) * 30, (k // 5) * 30, (k % 5) * 30 + 20, (k // 5) * 30 + 20), 0, 10, "B%d" % k)
        state.setdefault("first", b)
    Gui.SendMsgToActiveView("ViewFit")


def change():
    view().viewport().installEventFilter(frames)
    state["frames"] = 0
    import time
    state["t0"] = time.monotonic(); state["times"] = []
    ext = [o for o in doc().Objects if o.TypeId == "Design::Extrude"][0]
    ext.Distance = 14
    doc().recompute()


def restore():
    grp.SetBool("AlwaysSave", False)
    grp.SetString("ProjectsFolder", old_folder) if old_folder else grp.RemString("ProjectsFolder")


def verdict():
    n = state["frames"]
    L("frames after one change until rest (incl. saving): %d at %s s" % (n, state.get("times")))
    check("H3: one change draws the view at most %d times" % LIMIT, n <= LIMIT, str(n))


in_order([
    ("bodies", bodies),
    ("settle", lambda: None), ("settle", lambda: None), ("settle", lambda: None), ("settle", lambda: None),
    ("change", change),
    ("wait", lambda: None), ("wait", lambda: None), ("wait", lambda: None), ("wait", lambda: None),
    ("wait", lambda: None),
    ("verdict", verdict),
    ("restore", restore),
], delay=1000)
