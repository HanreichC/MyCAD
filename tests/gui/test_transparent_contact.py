# SPDX-License-Identifier: LGPL-2.1-or-later
"""Durchsichtiger Körper auf einem festen (Acrylplatte unter dem Gehäuse, ConceptKey): die Berührfläche sieht man durch
das Acryl. Beide Flächen lagen gleich tief und kämpften um die Tiefe (Streifen, Dreiecke). Durchsichtige Körper liegen
jetzt etwas weiter hinten, feste bleiben, wie sie sind; das folgt der Transparenz, wenn man sie ändert."""
from harness import *
from pivy import coin

S = {}
W = ("wait", lambda: None)


def offset(body):
    """Tiefenversatz direkt vor den Flächen des Körpers (factor, units)"""
    sa = coin.SoSearchAction(); sa.setType(coin.SoPolygonOffset.getClassTypeId()); sa.setInterest(coin.SoSearchAction.ALL)
    sa.setSearchingAll(True); sa.apply(body.ViewObject.RootNode)
    o = sa.getPaths()[sa.getPaths().getLength() - 1].getTail()
    return o.factor.getValue(), o.units.getValue()


def setup():
    S["case"] = make_body(rect(0, 0, 40, 20), 2, 10, "Case")   # z 2..12
    S["plate"] = make_body(rect(0, 0, 40, 20), 0, 2, "Plate")  # z 0..2, berührt das Gehäuse
    doc().recompute()
    S["plate"].ViewObject.Transparency = 62


def check_clear():
    check("a transparent body lies further back than a solid one it touches",
          offset(S["plate"]) > offset(S["case"]), "plate=%s case=%s" % (offset(S["plate"]), offset(S["case"])))
    S["plate"].ViewObject.Transparency = 0


def check_solid():
    check("made solid again, it lies like any solid body", offset(S["plate"]) == offset(S["case"]),
          "plate=%s case=%s" % (offset(S["plate"]), offset(S["case"])))


run([("activate", activate), ("setup", setup), W, ("clear", check_clear), W, ("solid", check_solid)])
