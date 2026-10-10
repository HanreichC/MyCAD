# SPDX-License-Identifier: LGPL-2.1-or-later
"""Meldungsfenster im MyCAD-Stil: Combine ohne Auswahl zeigt einen Hinweis."""
from harness import *


def grab():
    d = QtWidgets.QApplication.activeModalWidget()
    L("dialog=%s" % (type(d).__name__ if d else None))
    if d:
        d.grab().save(os.environ["OUT"] + ".dialog.png"); d.close()


run([
    ("combine", lambda: (QtCore.QTimer.singleShot(1500, grab), click(button("Design_Combine")))),
    ("wait", lambda: None), ("wait", lambda: None),
])
