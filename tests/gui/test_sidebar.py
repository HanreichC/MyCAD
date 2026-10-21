# SPDX-License-Identifier: LGPL-2.1-or-later
"""Seitenleiste im Design ein-/ausklappen: Knopf in der Fensterknopf-Kapsel blendet den Browser aus, die Toolbar rückt
nach links, Tooltip wechselt; erneuter Klick zeigt ihn wieder. Startseite und Hilfe haben keinen solchen Knopf.
Am Ende wieder ausgeklappt (Einstellung MyCAD/BrowserHidden)."""
import harness
from harness import *

grp = App.ParamGet("User parameter:BaseApp/Preferences/MyCAD")
grp.SetBool("BrowserHidden", False)


def toggles(page=None):
    """Seitenleisten-Knöpfe: im Design sichtbare, sonst die auf einer Seite (StartPage, HelpPage)"""
    tips = ("Hide sidebar", "Show sidebar")
    if page:
        return [b for p in mw.findChildren(QtWidgets.QWidget, page) for b in p.findChildren(QtWidgets.QToolButton) if b.toolTip() in tips]
    return [b for b in visible(QtWidgets.QToolButton) if b.toolTip() in tips]


def browser_shown():
    """Glas-Panel mit dem Modellbaum in der 3D-Szene sichtbar"""
    return any(i.isVisible() for i in view().scene().items()
               if isinstance(i, QtWidgets.QGraphicsProxyWidget) and i.widget() and i.widget().findChildren(QtWidgets.QTreeWidget))


def toolbar_x():
    return min(harness._pos(b).x() for b in visible(QtWidgets.QToolButton) if b.objectName() == "GlassButton" and b.property("command"))


def report(tag):
    L("%s: browser shown=%s toolbar x=%d toggle=%s hidden param=%s" % (tag, browser_shown(), toolbar_x(),
                                                                      [b.toolTip() for b in toggles()], grp.GetBool("BrowserHidden")))


def real_click(w):
    win = mw.windowHandle(); p = w.mapTo(mw, w.rect().center())
    QtTest.QTest.mouseClick(win, QtCore.Qt.LeftButton, QtCore.Qt.NoModifier, p)


run([
    ("start", lambda: report("ausgeklappt")),
    ("hide", lambda: click(toggles()[0])), ("hidden", lambda: report("nach Klick (Browser weg, Toolbar weiter links)")),
    ("shot", lambda: shot("hidden")),
    ("show", lambda: click(toggles()[0])), ("shown", lambda: report("nach zweitem Klick")),
    ("home", lambda: click([b for b in visible(QtWidgets.QToolButton) if b.toolTip() == "Home"][0])), ("wait", lambda: None),
    ("start page", lambda: L("start page: sidebar toggles=%d (0 expected)" % len(toggles("StartPage")))),
    ("back", lambda: real_click([b for b in mw.findChild(QtWidgets.QWidget, "StartPage").findChildren(QtWidgets.QToolButton)
                                 if b.toolTip() == "Back to Design"][0])), ("wait", lambda: None),
    ("help", lambda: QtTest.QTest.keyClick(mw, QtCore.Qt.Key_F1)), ("wait", lambda: None),
    ("help page", lambda: L("help: sidebar toggles=%d (0 expected)" % len(toggles("HelpPage")))),
    ("restore", lambda: grp.SetBool("BrowserHidden", False)),
])
