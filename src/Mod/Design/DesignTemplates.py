# SPDX-License-Identifier: LGPL-2.1-or-later
"""12.11 Vorlagen: fertige Designs aus Grundkörpern, deren Maße an Parametern hängen. Die Parameter stehen als Zeilen
"Name = Wert" in einer Notiz (Idee 3): eine Zeile ändern, Enter, das Design zieht nach."""
import FreeCAD as App

# (Schlüssel, englischer Name, deutscher Name); Reihenfolge wie auf der Startseite
TEMPLATES = [
    ("box_lid", "Box with Lid", "Box mit Deckel"),
    ("wall_bracket", "Wall Bracket", "Wandhalter"),
    ("pcb_case", "PCB Enclosure", "Platinengehäuse"),
    ("spacer", "Spacer", "Distanzhülse"),
    ("cable_clip", "Cable Clip", "Kabelclip"),
]

# Parameter je Vorlage: (englisch, deutsch, Wert in mm); die Ausdrücke unten benutzen die englischen Namen als Schlüssel
PARAMS = {
    "box_lid": [("Width", "Breite", 60), ("Depth", "Tiefe", 40), ("Height", "Hoehe", 30), ("Wall", "Wand", 2),
                ("Gap", "Spiel", 0.2)],
    "wall_bracket": [("Width", "Breite", 30), ("Depth", "Tiefe", 40), ("Height", "Hoehe", 40), ("Thickness", "Dicke", 4),
                     ("Hole", "Loch", 4.5)],
    "pcb_case": [("BoardLength", "Platinenlaenge", 70), ("BoardWidth", "Platinenbreite", 50), ("Height", "Hoehe", 25),
                 ("Wall", "Wand", 2), ("Gap", "Abstand", 1), ("Standoff", "Sockel", 5), ("Hole", "Loch", 2.5)],
    "spacer": [("Outside", "Aussen", 10), ("Bore", "Bohrung", 5.5), ("Length", "Laenge", 15)],
    "cable_clip": [("Cable", "Kabel", 6), ("Wall", "Wand", 1.6), ("Width", "Breite", 8)],
}


def german():
    return App.ParamGet("User parameter:BaseApp/Preferences/General").GetString("Language", "English") == "German"


class _Builder:
    def __init__(self, doc, key, de):
        import Design
        self.Design, self.doc, self.root = Design, doc, Design.root(doc)
        self.names = {en: (de_name if de else en) for en, de_name, _ in PARAMS[key]}

    def folder(self, name):
        """Ordner der Wurzel-Komponente (Notes, Construction …), sonst die Komponente selbst"""
        found = self.doc.getObject(name)
        return found if found is not None else self.root

    def expr(self, text):
        """"Width - 2 * Wall" -> "Parameters.Breite - 2 * Parameters.Wand" """
        import re
        return re.sub(r"\b([A-Z][A-Za-z]*)\b", lambda m: "Parameters." + self.names[m.group(1)] if m.group(1) in self.names
                      else m.group(1), text)

    def level(self, z=None, turn=None, y=None):
        """Ebene in Höhe z (Ausdruck) oder gedreht (Rotation) bei y; versteckt im Ordner Construction"""
        plane = self.doc.addObject("PartDesign::Plane", "Plane")
        self.folder("Construction").addObject(plane)
        if turn is not None:
            plane.Placement = App.Placement(App.Vector(), turn)
        if z is not None:
            plane.setExpression(".Placement.Base.z", self.expr(z))
        if y is not None:
            plane.setExpression(".Placement.Base.y", self.expr(y))
        plane.Visibility = False
        return plane

    def solid(self, kind, body=None, op="New Body", plane=None, label=None, **dims):
        f = self.doc.addObject("Design::Primitive", "Primitive")
        self.root.addObject(f)
        self.Design.addToTimeline(f)
        f.Type = kind
        if plane is not None:
            f.Plane = (plane, [""])
        for prop, text in dims.items():
            f.setExpression(prop, self.expr(str(text)))
        f.Operation = op
        if op == "New Body":
            body = self.Design.newBody(f)
            if label:
                body.Label = label
        else:
            self.Design.attachToBodies(f, [body])
        return body


def build(doc, key, de=None):
    """Vorlage key in doc (ein leeres Design) bauen; de: deutsche Namen (sonst nach der Sprache der Oberfläche)"""
    import Design
    de = german() if de is None else de
    b = _Builder(doc, key, de)
    title = [t for k, *t in TEMPLATES if k == key][0][1 if de else 0]
    n = doc.addObject("Design::Note", "Note")
    b.folder("Notes").addObject(n)
    n.Label = title
    hint = "Zeile ändern, Enter: das Design zieht nach" if de else "Change a line, press Enter: the design follows"
    n.Text = "\n".join([title] + ["%s = %s mm" % (de_name if de else en, value) for en, de_name, value in PARAMS[key]]
                       + [hint])
    Design.syncNoteParameters(n)
    globals()["_" + key](b, de)
    doc.Label = title
    doc.recompute()
    return n


def _box_lid(b, de):
    # Kasten: außen Width x Depth x Height, innen ab Boden (Wall) ausgeräumt
    box = b.solid("Box", label="Box", Length="Width", Width="Depth", Height="Height")
    b.solid("Box", box, "Cut", b.level(z="Wall"), Length="Width - 2 * Wall", Width="Depth - 2 * Wall", Height="Height")
    # Deckel daneben: Platte Wall dick, darunter (gedreht gedruckt: oben) ein Rand, der mit Gap Spiel in den Kasten passt
    lid = b.solid("Box", label="Deckel" if de else "Lid", Length="Width", Width="Depth", Height="Wall",
                  PositionX="Width + 10 mm")
    b.solid("Box", lid, "Join", b.level(z="Wall"), Length="Width - 2 * Wall - 2 * Gap",
            Width="Depth - 2 * Wall - 2 * Gap", Height="2 * Wall", PositionX="Width + 10 mm")
    b.solid("Box", lid, "Cut", b.level(z="Wall"), Length="Width - 4 * Wall - 2 * Gap",
            Width="Depth - 4 * Wall - 2 * Gap", Height="2 * Wall", PositionX="Width + 10 mm")


def _wall_bracket(b, de):
    # Winkel: Rückwand (an der Wand, y 0 … Thickness) und Arm nach vorn (y 0 … Depth), beide Width breit
    body = b.solid("Box", label="Wandhalter" if de else "Bracket", Length="Width", Width="Thickness", Height="Height",
                   PositionY="Thickness / 2")
    b.solid("Box", body, "Join", Length="Width", Width="Depth", Height="Thickness", PositionY="Depth / 2")
    # zwei Schraublöcher durch die Rückwand: Ebene senkrecht zu y auf der Vorderseite der Wand, Zylinder nach -y
    wall = b.level(turn=App.Rotation(App.Vector(1, 0, 0), 90), y="Thickness")
    for side in ("-", ""):
        b.solid("Cylinder", body, "Cut", wall, Radius="Hole / 2", Height="Thickness",
                PositionX=side + "Width / 4", PositionY="Height * 0.7")


def _pcb_case(b, de):
    # Gehäuse: Platine + Abstand rundum + Wand; innen ab Boden ausgeräumt; vier Sockel mit Loch für M3-Schrauben
    outer_l, outer_w = "BoardLength + 2 * Gap + 2 * Wall", "BoardWidth + 2 * Gap + 2 * Wall"
    body = b.solid("Box", label="Gehäuse" if de else "Enclosure", Length=outer_l, Width=outer_w, Height="Height")
    floor = b.level(z="Wall")
    b.solid("Box", body, "Cut", floor, Length="BoardLength + 2 * Gap", Width="BoardWidth + 2 * Gap", Height="Height")
    for sx in ("-", ""):
        for sy in ("-", ""):
            at = dict(PositionX=sx + "(BoardLength / 2 - 3.5 mm)", PositionY=sy + "(BoardWidth / 2 - 3.5 mm)")
            b.solid("Cylinder", body, "Join", floor, Radius="3 mm", Height="Standoff", **at)
            b.solid("Cylinder", body, "Cut", floor, Radius="Hole / 2", Height="Standoff", **at)


def _spacer(b, de):
    body = b.solid("Cylinder", label="Distanzhülse" if de else "Spacer", Radius="Outside / 2", Height="Length")
    b.solid("Cylinder", body, "Cut", Radius="Bore / 2", Height="Length")


def _cable_clip(b, de):
    # Ring um das Kabel (Achse senkrecht: druckt ohne Stützen), oben offen zum Einschnappen, unten eine Lasche
    body = b.solid("Cylinder", label="Kabelclip" if de else "Clip", Radius="Cable / 2 + Wall", Height="Width")
    b.solid("Cylinder", body, "Cut", Radius="Cable / 2", Height="Width")
    b.solid("Box", body, "Cut", Length="Cable * 0.75", Width="Cable", Height="Width", PositionY="Cable / 2 + Wall")
    b.solid("Box", body, "Join", Length="Cable + 2 * Wall + 12 mm", Width="Wall", Height="Width",
            PositionY="-(Cable / 2 + Wall)")
