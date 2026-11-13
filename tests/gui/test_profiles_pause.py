# SPDX-License-Identifier: LGPL-2.1-or-later
"""Profile während der Skizzenbearbeitung: nicht bei jeder Änderung neu berechnet (große DXF-Skizzen), aber gespeichert
als noch offen (Touched), damit nach einem Absturz in der Skizze die Datei keine veralteten Profile als aktuell führt.
Beim Verlassen der Skizze passen sie wieder zur Skizze."""
import os
import re
import tempfile
import zipfile
from harness import *
import Design

V = App.Vector
state = {}


def profiles():
    return [o for o in doc().Objects if o.TypeId == "Design::Profiles"][0]


def setup():
    sk = Design.newSketch(Design.root(doc()))
    for g in rect(0, 0, 20, 10):
        sk.addGeometry(g)
    doc().recompute()
    state["sketch"] = sk
    check("one profile before editing", len(profiles().Shape.Faces) == 1, str(len(profiles().Shape.Faces)))
    Gui.ActiveDocument.setEdit(sk)


def change():
    for g in rect(30, 0, 40, 10):
        state["sketch"].addGeometry(g)
    doc().recompute()
    check("profiles wait while the sketch is edited", len(profiles().Shape.Faces) == 1, str(len(profiles().Shape.Faces)))


def save():
    path = os.path.join(tempfile.mkdtemp(), "pause.mycad")
    doc().saveAs(path)
    with zipfile.ZipFile(path) as z:
        xml = z.read("Document.xml").decode()
    tag = re.search(r'<Object type="Design::Profiles" name="%s"[^>]*>' % profiles().Name, xml)
    check("saved profiles are marked for recompute", bool(tag) and 'Touched="1"' in tag.group(0),
          tag.group(0) if tag else "no tag")


def leave():
    Gui.ActiveDocument.resetEdit()


def after():
    check("profiles match the sketch after leaving it", len(profiles().Shape.Faces) == 2, str(len(profiles().Shape.Faces)))


in_order([("setup", setup), ("change", change), ("save", save), ("leave", leave), ("after", after)], delay=600)
