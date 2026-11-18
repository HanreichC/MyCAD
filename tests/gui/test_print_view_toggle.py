# SPDX-License-Identifier: LGPL-2.1-or-later
"""H1: Die Druckansicht zeigt, dass sie an ist. Klick auf "Print View" oben: der Knopf bleibt gedrückt, die Legende
hat einen Knopf "Exit Print View". Der schaltet sie aus, der Knopf oben ist danach nicht mehr gedrückt. Ein zweiter
Klick oben schaltet sie wie bisher aus. Fehler stehen als FAIL im Protokoll."""
from harness import *


def exit_button():
    found = [b for b in visible(QtWidgets.QPushButton) if b.objectName() == "ExitPrintView"]
    return found[0] if found else None


def legend_shown():
    return any(w.objectName() == "PrintLegend" for w in visible(QtWidgets.QWidget))


run([
    ("body", lambda: make_body(rect(0, 0, 40, 30), 0, 10, "Box")),
    ("on", lambda: click(button("Design_PrintView"))),
    ("pressed", lambda: check("H1: the Print View button stays pressed while it is on",
                              button("Design_PrintView").isChecked() and legend_shown() and exit_button() is not None,
                              "checked=%s legend=%s exit=%s" % (button("Design_PrintView").isChecked(), legend_shown(), exit_button()))),
    ("shot", lambda: shot("on")),
    ("exit", lambda: exit_button().click()),
    ("off", lambda: check("H1: Exit Print View in the legend turns it off and releases the button",
                          not button("Design_PrintView").isChecked() and not legend_shown(),
                          "checked=%s legend=%s" % (button("Design_PrintView").isChecked(), legend_shown()))),
    ("on again", lambda: click(button("Design_PrintView"))),
    ("again pressed", lambda: check("pressed again", button("Design_PrintView").isChecked())),
    ("toggle off", lambda: click(button("Design_PrintView"))),
    ("toggled off", lambda: check("a second click on the button still turns it off",
                                  not button("Design_PrintView").isChecked() and not legend_shown())),
])
