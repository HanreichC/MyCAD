# SPDX-License-Identifier: LGPL-2.1-or-later
"""12.7 Teile-Bibliothek: Einfügen nimmt ein früheres MyCAD-Design; seine sichtbaren Körper kommen mit ihrem Namen
als Teile herein (ein Scharnier als zwei Körper), das andere Design bleibt dabei geschlossen"""
import os
from harness import *
import Design

LIB = os.environ["OUT"] + ".library.mycad"
S = {}
W = ("wait", lambda: None)


def write_library():
    work = App.ActiveDocument.Name
    lib = App.newDocument("Library", hidden=True)
    root = Design.root(lib)
    for kind, label, props in (("Box", "Bracket", dict(Length=30, Width=20, Height=5)),
                               ("Print-in-Place Hinge", "Hinge", {})):
        f = lib.addObject("Design::Primitive", "Primitive"); root.addObject(f); Design.addToTimeline(f)
        f.Type = kind
        for k, v in props.items():
            setattr(f, k, v)
        Design.newBody(f).Label = label
    lib.recompute()
    S["volume"] = sum(b.Shape.Volume for b in lib.Objects if b.TypeId == "Design::Body")
    lib.saveAs(LIB)
    App.closeDocument(lib.Name)
    App.setActiveDocument(work)


def insert():
    def pick():
        d = visible(QtWidgets.QFileDialog)
        name = [e for e in d[0].findChildren(QtWidgets.QLineEdit) if e.isVisible()][0]
        name.setText(LIB); d[0].accept()
    QtCore.QTimer.singleShot(800, pick)
    click(button("Design_Import"))


def inserted():
    found = sorted((b.Label, round(b.Shape.Volume, 3)) for b in doc().Objects if b.TypeId == "Design::Body")
    labels = [l for l, _ in found]
    check("the bracket and both hinge halves come in with their names", labels == ["Bracket", "Hinge 1", "Hinge 2"], str(found))
    check("with the same volume", abs(sum(v for _, v in found) - S["volume"]) < 1e-3, str(found))
    check("the library design stays closed", not any("Library" in d for d in App.listDocuments()),
          str(list(App.listDocuments())))


run([("activate", activate), ("library", write_library), W,
     ("insert", insert), W, W,
     ("inserted", inserted),
     ("errors", lambda: check("no errors", not errors(), str(errors()))),
     ])
