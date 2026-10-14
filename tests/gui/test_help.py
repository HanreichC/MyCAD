# SPDX-License-Identifier: LGPL-2.1-or-later
"""Hilfe: ?-Knopf öffnet sie; Suche "donut" findet Revolve (Enter öffnet den Artikel); Maus über Extrude + F1 öffnet
den Extrude-Artikel; Esc schließt. Prüft außerdem, dass jeder Artikel Titel, Kurztext und Schritte in beiden Sprachen hat
und jedes Bild existiert."""
import json
import os
from harness import *
import harness


def page():
    pages = [w for w in mw.findChildren(QtWidgets.QWidget, "HelpPage")]
    return pages[0] if pages else None


def article_title():
    view = page().findChild(QtWidgets.QTextBrowser, "HelpArticle")
    return view.document().toPlainText().replace("\ufffc", "").strip().split("\n")[0]


def rows():
    return [b.text() for b in page().findChildren(QtWidgets.QToolButton, "PaletteRow") if b.isVisible()]


def report(tag):
    L("%s: help visible=%s article=%s" % (tag, bool(page() and page().isVisible()), article_title() if page() else "-"))


def search(text):
    edit = page().findChild(QtWidgets.QLineEdit, "StartSearch")
    edit.setText(text)
    L("Suche %r: %s" % (text, rows()))
    QtTest.QTest.keyClick(edit, QtCore.Qt.Key_Return)


def f1_over_extrude():
    page().hide()
    b = button("Design_Extrude")
    win = mw.windowHandle(); p = view().viewport().mapTo(mw, harness._pos(b))
    QtTest.QTest.mouseMove(win, p)


def press_f1():
    QtTest.QTest.keyClick(mw.windowHandle(), QtCore.Qt.Key_F1)


def content():
    data = json.load(open("/workspace/src/Gui/Shell/help/help.json"))
    problems = []
    for a in data["articles"]:
        for field in ("title", "summary", "steps"):
            for lang in ("en", "de"):
                if not a.get(field, {}).get(lang):
                    problems.append("%s: %s/%s fehlt" % (a["id"], field, lang))
        for img in a.get("images", []):
            if not os.path.exists("/workspace/src/Gui/Shell/help/images/" + img["file"]):
                problems.append("%s: Bild %s fehlt" % (a["id"], img["file"]))
    L("Artikel=%d Probleme=%s" % (len(data["articles"]), problems[:20]))


run([
    ("content", content),
    ("help button", lambda: click([b for b in visible(QtWidgets.QToolButton) if b.toolTip().startswith("Help")][0])),
    ("wait", lambda: None), ("opened", lambda: (report("?-Knopf"), shot("help"))),
    ("search", lambda: search("donut")), ("searched", lambda: report("nach Suche + Enter")),
    ("hover", f1_over_extrude), ("wait", lambda: None), ("f1", press_f1), ("wait", lambda: None),
    ("after f1", lambda: report("F1 über Extrude")),
    ("esc", lambda: QtTest.QTest.keyClick(page(), QtCore.Qt.Key_Escape)), ("closed", lambda: report("nach Esc")),
])
