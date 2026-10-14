#!/usr/bin/env python3
# Inhalt der MyCAD-Hilfe (Englisch + Deutsch). Erzeugt src/Gui/Shell/help/help.json und help.qrc:
#   python3 tools/help_content.py
# Bilder: tools/help_images.py (läuft in MyCAD) legt sie unter src/Gui/Shell/help/images/<id>.png ab.
import json
import pathlib

HELP = pathlib.Path(__file__).resolve().parent.parent / "src/Gui/Shell/help"

GROUPS = [
    ("start", "Getting Started", "Erste Schritte"), ("file", "File", "Datei"), ("create", "Create", "Erstellen"),
    ("modify", "Modify", "Ändern"), ("construct", "Construct", "Konstruieren"), ("assemble", "Assemble", "Zusammenfügen"),
    ("inspect", "Inspect", "Prüfen"), ("utilities", "Utilities", "Werkzeuge"),
    ("sketch_create", "Sketch – Create", "Skizze – Erstellen"), ("sketch_modify", "Sketch – Modify", "Skizze – Ändern"),
    ("sketch_constraints", "Sketch – Constraints", "Skizze – Abhängigkeiten"),
]
ARTICLES = []


def A(id, group, icon, title, keywords, summary, steps, options=None, tips=None, see=(), commands=(), caption=None):
    """Jeder Text ist ein Paar (Englisch, Deutsch); Listen sind Paare von Listen."""
    a = {"id": id, "group": group, "icon": icon, "commands": list(commands),
         "title": {"en": title[0], "de": title[1]}, "keywords": {"en": keywords[0], "de": keywords[1]},
         "summary": {"en": summary[0], "de": summary[1]}, "steps": {"en": steps[0], "de": steps[1]}, "see": list(see)}
    if options:
        a["options"] = {"en": options[0], "de": options[1]}
    if tips:
        a["tips"] = {"en": tips[0], "de": tips[1]}
    if caption:
        a["caption"] = {"en": caption[0], "de": caption[1]}
    ARTICLES.append(a)


OPERATION = (["Operation", "New Body, Join, Cut, Intersect or New Component. Join and Cut ask for the body to change."],
             ["Vorgang", "Neuer Körper, Verbinden, Ausschneiden, Schnittmenge oder Neue Komponente. Bei Verbinden und Ausschneiden wählst du den Körper, der verändert wird."])

# --- Erste Schritte ------------------------------------------------------------------------------------------------
A("start_first", "start", "Std_New", ("Your first design", "Dein erstes Design"),
  (["start", "beginner", "tutorial", "first steps", "how to"], ["Start", "Anfänger", "Anleitung", "erste Schritte", "wie"]),
  ("In MyCAD you sketch a shape, then turn it into a body – just like in Fusion 360.",
   "In MyCAD skizzierst du eine Form und machst daraus einen Körper – genau wie in Fusion 360."),
  (["On the start page click New Design.", "Click Sketch and choose a plane, e.g. the floor (XY).",
    "Draw a rectangle: click two opposite corners.", "Click Finish Sketch.",
    "Click inside the rectangle, then Extrude, drag the arrow up and click OK."],
   ["Klicke auf der Startseite auf Neues Design.", "Klicke auf Skizze und wähle eine Ebene, z. B. den Boden (XY).",
    "Zeichne ein Rechteck: klicke zwei gegenüberliegende Ecken.", "Klicke auf Skizze fertig stellen.",
    "Klicke in das Rechteck, dann auf Extrudieren, ziehe den Pfeil nach oben und klicke OK."]),
  tips=(["Every step lands in the timeline at the bottom. Double-click it to change it later.",
         "Press F1 over any tool to open its help page."],
        ["Jeder Schritt landet in der Zeitleiste unten. Doppelklick darauf ändert ihn später.",
         "Drücke F1 über einem Werkzeug, um seine Hilfeseite zu öffnen."]),
  see=["Design_CreateSketch", "Design_Extrude", "start_navigation"])
A("start_navigation", "start", "Nav_Rotate", ("Moving around", "Navigation"),
  (["navigate", "rotate view", "orbit", "pan", "zoom", "mouse", "trackpad", "view cube"],
   ["navigieren", "Ansicht drehen", "Orbit", "verschieben", "zoomen", "Maus", "Trackpad", "ViewCube"]),
  ("Rotate, pan and zoom the view with mouse or trackpad. The exact buttons depend on the style in Settings.",
   "Drehen, verschieben und zoomen mit Maus oder Trackpad. Welche Tasten genau, hängt vom Stil in den Einstellungen ab."),
  (["Rotate (Fusion 360 style): hold Shift and drag with the middle mouse button.", "Pan: drag with the middle mouse button.",
    "Zoom: scroll the mouse wheel; it zooms towards the cursor.",
    "Click a face or corner of the ViewCube (top right) to look from that side; the house button shows the whole model."],
   ["Drehen (Stil Fusion 360): Umschalt halten und mit der mittleren Maustaste ziehen.",
    "Verschieben: mit der mittleren Maustaste ziehen.", "Zoomen: Mausrad drehen; es zoomt zum Cursor hin.",
    "Klicke eine Fläche oder Ecke des ViewCube (oben rechts), um von dort zu schauen; das Haus zeigt das ganze Modell."]),
  tips=(["In Settings you can turn a key, e.g. Space, into a mouse button – handy on a laptop.",
         "The view rotates around the body under the cursor, so details stay in place."],
        ["In den Einstellungen machst du eine Taste, z. B. die Leertaste, zur Maustaste – praktisch am Laptop.",
         "Die Ansicht dreht um den Körper unter dem Cursor, so bleiben Details an ihrem Platz."]),
  see=["settings"])
A("sketch_basics", "start", "Design_CreateSketch", ("Sketching basics", "Skizzen-Grundlagen"),
  (["sketch", "profile", "closed area", "constraint", "colors", "blue", "black", "construction"],
   ["Skizze", "Profil", "geschlossene Fläche", "Abhängigkeit", "Farben", "blau", "schwarz", "Konstruktion"]),
  ("A sketch is a flat drawing on a plane. Every closed area becomes a profile that you can extrude or revolve.",
   "Eine Skizze ist eine flache Zeichnung auf einer Ebene. Jede geschlossene Fläche wird ein Profil, das du extrudieren oder drehen kannst."),
  (["Draw lines, circles and other shapes; corners snap together.",
    "Add dimensions and constraints until the drawing is fully defined.",
    "Press Esc to put the current tool away, then Finish Sketch.",
    "Outside the sketch, the closed areas appear light orange; click one to select it (it turns blue)."],
   ["Zeichne Linien, Kreise und andere Formen; Ecken rasten aneinander ein.",
    "Füge Bemaßungen und Abhängigkeiten hinzu, bis die Zeichnung voll bestimmt ist.",
    "Drücke Esc, um das aktuelle Werkzeug wegzulegen, dann Skizze fertig stellen.",
    "Außerhalb der Skizze erscheinen die geschlossenen Flächen hellorange; ein Klick wählt eine aus (sie wird blau)."]),
  options=([["Blue lines", "Not fully defined yet: they can still move."], ["Black lines", "Fully defined by dimensions and constraints."],
            ["Orange dashed lines", "Construction geometry: helps drawing, never part of a profile."],
            ["Purple lines", "Projected from the model."]],
           [["Blaue Linien", "Noch nicht voll bestimmt: sie können sich noch bewegen."],
            ["Schwarze Linien", "Voll bestimmt durch Bemaßungen und Abhängigkeiten."],
            ["Orange gestrichelte Linien", "Konstruktionsgeometrie: hilft beim Zeichnen, gehört nie zu einem Profil."],
            ["Lila Linien", "Aus dem Modell projiziert."]]),
  tips=(["Two circles inside each other give two profiles: the ring and the inner disc. Click only the ring to get a tube.",
         "The Sketch Palette on the right turns grid, snap and the section view on or off."],
        ["Zwei Kreise ineinander ergeben zwei Profile: den Ring und die innere Scheibe. Klicke nur den Ring an, um ein Rohr zu bekommen.",
         "Die Skizzenpalette rechts schaltet Raster, Fangen und Schnittansicht ein oder aus."]),
  see=["Design_CreateSketch", "sketch_dimension", "sketch_construction"])
A("start_timeline", "start", "Design_Parameters", ("Timeline and changes", "Zeitleiste und Änderungen"),
  (["timeline", "history", "edit", "roll back", "suppress", "undo", "change later"],
   ["Zeitleiste", "Verlauf", "bearbeiten", "zurücksetzen", "unterdrücken", "rückgängig", "später ändern"]),
  ("Every sketch and feature is a step in the timeline at the bottom. Change any step and everything after it updates.",
   "Jede Skizze und jedes Feature ist ein Schritt in der Zeitleiste unten. Änderst du einen Schritt, passt sich alles danach an."),
  (["Double-click a step to edit it.", "Right-click a step for Edit, Roll Back to Here, Suppress or Delete.",
    "Roll Back to Here lets you insert new steps in the middle of the history."],
   ["Doppelklick auf einen Schritt bearbeitet ihn.", "Rechtsklick auf einen Schritt bietet Bearbeiten, Bis hierher zurücksetzen, Unterdrücken oder Löschen.",
    "Bis hierher zurücksetzen lässt dich neue Schritte mitten in den Verlauf einfügen."]),
  tips=(["A red step has a problem; hover it to read why.", "Suppress hides a step without deleting it."],
        ["Ein roter Schritt hat ein Problem; fahre mit der Maus darüber, um den Grund zu lesen.",
         "Unterdrücken blendet einen Schritt aus, ohne ihn zu löschen."]),
  see=["Design_Parameters"])

# --- Datei ---------------------------------------------------------------------------------------------------------
A("file_basics", "file", "Std_Save", ("Designs and files", "Designs und Dateien"),
  (["new", "open", "save", "save as", "undo", "redo", "file", "start page", "projects folder"],
   ["neu", "öffnen", "speichern", "speichern unter", "rückgängig", "wiederholen", "Datei", "Startseite", "Projektordner"]),
  ("Create, open and save designs; undo and redo every change.", "Designs anlegen, öffnen und speichern; jede Änderung rückgängig machen und wiederholen."),
  (["New creates an empty design, Open loads a design file.", "Save (Ctrl+S) writes the design; the first time you choose a name.",
    "Undo (Ctrl+Z) and Redo (Ctrl+Y) step through your changes.",
    "The house button opens the start page with your recent designs and the projects folder."],
   ["Neu legt ein leeres Design an, Öffnen lädt eine Design-Datei.", "Speichern (Strg+S) schreibt das Design; beim ersten Mal wählst du einen Namen.",
    "Rückgängig (Strg+Z) und Wiederholen (Strg+Y) gehen durch deine Änderungen.",
    "Der Haus-Knopf öffnet die Startseite mit deinen zuletzt verwendeten Designs und dem Projektordner."]),
  tips=(["Designs saved in the projects folder (Settings) appear on the start page with a preview.",
         "Right-click a design in the browser to rename, close or delete it."],
        ["Designs im Projektordner (Einstellungen) erscheinen mit Vorschaubild auf der Startseite.",
         "Rechtsklick auf ein Design im Browser: umbenennen, schließen oder löschen."]),
  commands=["Std_New", "Std_Open", "Std_Save", "Std_SaveAs", "Std_Undo", "Std_Redo"], see=["Design_Export", "Design_Import"])
A("Design_Import", "file", "Design_Import", ("Insert", "Einfügen"),
  (["import", "step", "dxf", "svg", "insert file", "open cad"], ["importieren", "STEP", "DXF", "SVG", "Datei einfügen", "CAD öffnen"]),
  ("Brings a STEP model in as bodies, or a DXF/SVG drawing as a sketch.", "Holt ein STEP-Modell als Körper herein oder eine DXF-/SVG-Zeichnung als Skizze."),
  (["Click Insert.", "Choose a STEP, DXF or SVG file.", "STEP files become bodies; DXF and SVG become a sketch on the floor plane."],
   ["Klicke auf Einfügen.", "Wähle eine STEP-, DXF- oder SVG-Datei.", "STEP-Dateien werden Körper; DXF und SVG werden eine Skizze auf der Bodenebene."]),
  tips=(["Closed areas of an inserted DXF or SVG are profiles – extrude them right away."],
        ["Geschlossene Flächen einer eingefügten DXF oder SVG sind Profile – extrudiere sie gleich."]),
  see=["Design_Export", "Design_Extrude"])
A("Design_Export", "file", "Design_Export", ("Export", "Exportieren"),
  (["export", "3mf", "stl", "step", "3d print", "slicer", "save as stl"], ["exportieren", "3MF", "STL", "STEP", "3D-Druck", "Slicer", "als STL speichern"]),
  ("Saves bodies as 3MF or STL for 3D printing, or as STEP for other CAD programs.",
   "Speichert Körper als 3MF oder STL für den 3D-Druck oder als STEP für andere CAD-Programme."),
  (["Select the bodies to export (nothing selected = all visible bodies).", "Click Export.", "Choose the format and a file name."],
   ["Wähle die Körper zum Exportieren (nichts gewählt = alle sichtbaren Körper).", "Klicke auf Exportieren.", "Wähle Format und Dateinamen."]),
  tips=(["3MF keeps units and is the best choice for modern slicers."], ["3MF behält die Einheiten und ist für moderne Slicer die beste Wahl."]),
  see=["Design_Import"])

# --- Erstellen -----------------------------------------------------------------------------------------------------
A("Design_CreateSketch", "create", "Design_CreateSketch", ("Create Sketch", "Skizze erstellen"),
  (["sketch", "draw", "2d", "plane", "face"], ["Skizze", "zeichnen", "2D", "Ebene", "Fläche"]),
  ("Starts a new sketch on a plane or on a flat face of a body.", "Beginnt eine neue Skizze auf einer Ebene oder einer flachen Fläche eines Körpers."),
  (["Click Sketch.", "Click one of the origin planes or a flat face of a body.", "Draw with the sketch tools.", "Click Finish Sketch."],
   ["Klicke auf Skizze.", "Klicke eine der Ursprungsebenen oder eine flache Fläche eines Körpers an.", "Zeichne mit den Skizzenwerkzeugen.", "Klicke auf Skizze fertig stellen."]),
  tips=(["A sketch on a body face extrudes into that body by default (Join).",
         "Double-click a sketch in the timeline to change it later; bodies built from it update."],
        ["Eine Skizze auf einer Körperfläche wird standardmäßig mit diesem Körper verbunden.",
         "Doppelklick auf eine Skizze in der Zeitleiste ändert sie später; Körper daraus passen sich an."]),
  see=["sketch_basics", "Design_Extrude"])
A("Design_Extrude", "create", "Design_Extrude", ("Extrude", "Extrudieren"),
  (["extrude", "pull", "solid", "thickness", "block", "plate", "tube"], ["extrudieren", "ziehen", "Volumen", "Dicke", "Block", "Platte", "Rohr"]),
  ("Pulls closed areas of a sketch straight out into a body.", "Zieht geschlossene Flächen einer Skizze gerade heraus zu einem Körper."),
  (["Click one or more profiles (closed areas) of a sketch; they turn blue.", "Click Extrude.",
    "Drag the arrow or type the distance.", "Choose the operation, then click OK."],
   ["Klicke ein oder mehrere Profile (geschlossene Flächen) einer Skizze an; sie werden blau.", "Klicke auf Extrudieren.",
    "Ziehe den Pfeil oder tippe den Abstand ein.", "Wähle den Vorgang und klicke OK."]),
  options=([["Direction", "One Side, Symmetric (both sides equally) or Two Sides (two distances)."], ["Distance", "How far the profile is pulled."],
            ["Flip direction", "Pulls to the other side."], OPERATION[0]],
           [["Richtung", "Eine Seite, Symmetrisch (beidseitig gleich) oder Zwei Seiten (zwei Abstände)."], ["Abstand", "Wie weit das Profil herausgezogen wird."],
            ["Richtung umkehren", "Zieht zur anderen Seite."], OPERATION[1]]),
  tips=(["Click only the ring between two circles to get a tube instead of a solid cylinder.",
         "Type a parameter name or a formula such as Width * 2 in the distance field."],
        ["Klicke nur den Ring zwischen zwei Kreisen an, um ein Rohr statt eines vollen Zylinders zu bekommen.",
         "Tippe einen Parameternamen oder eine Formel wie Breite * 2 ins Abstandsfeld."]),
  see=["Design_Revolve", "Design_PressPull", "sketch_basics"])
A("Design_Revolve", "create", "Design_Revolve", ("Revolve", "Drehen"),
  (["revolve", "donut", "turned part", "lathe", "rotate profile", "axis", "torus", "ring", "vase"],
   ["drehen", "Donut", "Drehteil", "Drehbank", "Profil rotieren", "Achse", "Torus", "Ring", "Vase"]),
  ("Spins a cross-section around an axis – for donuts, rings, shafts and every turned part.",
   "Dreht einen Querschnitt um eine Achse – für Donuts, Ringe, Wellen und jedes Drehteil."),
  (["Create a sketch on a vertical plane, e.g. XZ.", "Draw the cross-section beside the axis, e.g. a circle 30 mm to the right of the origin.",
    "Click Finish Sketch, click the profile and then Revolve.",
    "MyCAD picks an axis that does not cross the profile; change it if needed and click OK."],
   ["Erstelle eine Skizze auf einer senkrechten Ebene, z. B. XZ.", "Zeichne den Querschnitt neben der Achse, z. B. einen Kreis 30 mm rechts vom Ursprung.",
    "Klicke auf Skizze fertig stellen, dann auf das Profil und auf Drehen.",
    "MyCAD wählt eine Achse, die das Profil nicht schneidet; ändere sie bei Bedarf und klicke OK."]),
  options=([["Axis", "Sketch X axis, Sketch Y axis or the origin axes X, Y and Z."], ["Angle", "360° for a full turn, less for a part of it."],
            ["Flip direction", "Turns the other way round."], OPERATION[0]],
           [["Achse", "X- oder Y-Achse der Skizze oder die Ursprungsachsen X, Y und Z."], ["Winkel", "360° für eine volle Umdrehung, weniger für einen Teil davon."],
            ["Richtung umkehren", "Dreht andersherum."], OPERATION[1]]),
  tips=(["The axis must not run through the profile, otherwise MyCAD says so.",
         "A half circle touching the axis gives a sphere; a rectangle touching it gives a cylinder."],
        ["Die Achse darf nicht durch das Profil laufen, sonst meldet MyCAD das.",
         "Ein Halbkreis an der Achse ergibt eine Kugel, ein Rechteck an der Achse einen Zylinder."]),
  caption=("A circle beside the axis becomes a donut.", "Ein Kreis neben der Achse wird zum Donut."),
  see=["Design_Extrude", "Design_Sweep"])
A("Design_Sweep", "create", "Design_Sweep", ("Sweep", "Sweep"),
  (["sweep", "path", "pipe", "tube", "rail", "handle", "bent"], ["Sweep", "Pfad", "Rohr", "Schlauch", "Bahn", "Griff", "gebogen"]),
  ("Moves a profile along a path – for pipes, handles and bent shapes.", "Führt ein Profil an einem Pfad entlang – für Rohre, Griffe und gebogene Formen."),
  (["Sketch the profile, e.g. a circle.", "Sketch the path on another plane: connected lines and arcs.",
    "Select the profile and the path, then click Sweep and OK."],
   ["Skizziere das Profil, z. B. einen Kreis.", "Skizziere den Pfad auf einer anderen Ebene: zusammenhängende Linien und Bögen.",
    "Wähle Profil und Pfad, klicke auf Sweep und OK."]),
  tips=(["The path must be one connected chain and must not cross itself.", "Edges of a body work as a path, too."],
        ["Der Pfad muss eine zusammenhängende Kette sein und darf sich nicht selbst kreuzen.", "Auch Kanten eines Körpers taugen als Pfad."]),
  see=["Design_Loft", "Design_Revolve"])
A("Design_Loft", "create", "Design_Loft", ("Loft", "Erhebung"),
  (["loft", "blend", "transition", "morph", "funnel"], ["Erhebung", "Übergang", "überblenden", "Trichter", "Loft"]),
  ("Builds a smooth body through two or more profiles, e.g. from a square to a circle.",
   "Baut einen glatten Körper durch zwei oder mehr Profile, z. B. vom Quadrat zum Kreis."),
  (["Sketch each profile on its own plane (use Offset Plane for parallel levels).", "Select the profiles in order.", "Click Loft and OK."],
   ["Skizziere jedes Profil auf einer eigenen Ebene (mit Versetzte Ebene für parallele Höhen).", "Wähle die Profile der Reihe nach.", "Klicke auf Erhebung und OK."]),
  options=([["Ruled", "Straight transitions instead of smooth curves."], ["Closed", "Connects the last profile back to the first."], OPERATION[0]],
           [["Regelfläche", "Gerade Übergänge statt weicher Kurven."], ["Geschlossen", "Verbindet das letzte Profil wieder mit dem ersten."], OPERATION[1]]),
  see=["Design_OffsetPlane", "Design_Sweep"])
A("Design_Rib", "create", "Design_Rib", ("Rib", "Rippe"),
  (["rib", "stiffener", "support", "gusset"], ["Rippe", "Versteifung", "Stütze", "Knotenblech"]),
  ("Adds a thin supporting wall along sketch lines between existing walls.", "Fügt entlang von Skizzenlinien eine dünne Stützwand zwischen vorhandenen Wänden ein."),
  (["Sketch the rib lines on a plane through the body; both ends must touch the body.", "Select the body and the sketch lines.",
    "Click Rib, set the thickness and click OK."],
   ["Skizziere die Rippenlinien auf einer Ebene durch den Körper; beide Enden müssen den Körper berühren.", "Wähle den Körper und die Skizzenlinien.",
    "Klicke auf Rippe, stelle die Dicke ein und klicke OK."]),
  options=([["Thickness", "Wall thickness of the rib."]], [["Dicke", "Wandstärke der Rippe."]]),
  see=["Design_Web", "Design_Shell"])
A("Design_Web", "create", "Design_Web", ("Web", "Steg"),
  (["web", "grid", "stiffeners", "honeycomb", "inner walls"], ["Steg", "Gitter", "Versteifungen", "Waben", "Innenwände"]),
  ("Like Rib, but the walls grow perpendicular to the sketch – great for a grid of stiffeners inside a shell.",
   "Wie Rippe, aber die Wände wachsen senkrecht zur Skizze – ideal für ein Gitter aus Versteifungen in einer Schale."),
  (["Sketch the lines of the web on a plane.", "Select the body and the sketch lines.", "Click Web, set the thickness and click OK."],
   ["Skizziere die Linien des Stegs auf einer Ebene.", "Wähle den Körper und die Skizzenlinien.", "Klicke auf Steg, stelle die Dicke ein und klicke OK."]),
  options=([["Thickness", "Wall thickness of each web."]], [["Dicke", "Wandstärke jedes Stegs."]]), see=["Design_Rib", "Design_Shell"])
A("Design_Emboss", "create", "Design_Emboss", ("Emboss", "Prägen"),
  (["emboss", "engrave", "text", "logo", "label", "deboss", "lettering"], ["prägen", "gravieren", "Text", "Logo", "Beschriftung", "vertiefen", "Schrift"]),
  ("Raises or engraves sketch profiles or text on a face of a body.", "Hebt Skizzenprofile oder Text auf einer Körperfläche hervor oder graviert sie ein."),
  (["Sketch the text or shapes on or near the face.", "Select the profiles and the face to emboss on.", "Click Emboss, choose raised or engraved and the depth, then OK."],
   ["Skizziere Text oder Formen auf oder nahe der Fläche.", "Wähle die Profile und die Fläche zum Prägen.", "Klicke auf Prägen, wähle erhaben oder vertieft und die Tiefe, dann OK."]),
  options=([["Type", "Emboss (raised) or Deboss (engraved)."], ["Depth", "Height or depth of the lettering."]],
           [["Typ", "Prägen (erhaben) oder Vertiefen (graviert)."], ["Tiefe", "Höhe oder Tiefe der Schrift."]]),
  see=["sketch_text"])
A("primitives", "create", "Design_Box", ("Box, Cylinder and more", "Quader, Zylinder und mehr"),
  (["box", "cube", "cylinder", "sphere", "ball", "torus", "coil", "spring", "helix", "primitive"],
   ["Quader", "Würfel", "Zylinder", "Kugel", "Ball", "Torus", "Spirale", "Feder", "Helix", "Grundkörper"]),
  ("Creates a ready-made body without a sketch.", "Erstellt einen fertigen Körper ohne Skizze."),
  (["Optionally click a plane or flat face to place it on (otherwise the floor).", "Open the dropdown next to Box and choose the shape.",
    "Type the sizes and the position, then click OK."],
   ["Klicke optional eine Ebene oder flache Fläche zum Platzieren an (sonst der Boden).", "Öffne das Dropdown neben Quader und wähle die Form.",
    "Tippe Größen und Position ein und klicke OK."]),
  options=([["Length, Width, Height", "Size of a box; height also for cylinder and coil."], ["Radius", "Radius of cylinder, sphere, torus and coil."],
            ["Tube Radius", "Thickness of torus and coil."], ["Pitch, Turns", "Height per turn and number of turns of a coil."],
            ["Position X, Y", "Where on the plane it sits."], OPERATION[0]],
           [["Länge, Breite, Höhe", "Größe des Quaders; Höhe auch bei Zylinder und Spirale."], ["Radius", "Radius von Zylinder, Kugel, Torus und Spirale."],
            ["Rohrradius", "Dicke von Torus und Spirale."], ["Steigung, Windungen", "Höhe pro Umdrehung und Anzahl der Windungen einer Spirale."],
            ["Position X, Y", "Wo auf der Ebene er sitzt."], OPERATION[1]]),
  commands=["Design_Box", "Design_Cylinder", "Design_Sphere", "Design_Torus", "Design_Coil"], see=["Design_Extrude"])
A("Design_Hole", "create", "Design_Hole", ("Hole", "Bohrung"),
  (["hole", "drill", "bore", "counterbore", "countersink", "screw", "through"], ["Bohrung", "bohren", "Loch", "Senkung", "Senkkopf", "Schraube", "durchgehend"]),
  ("Drills holes at sketch points – simple, counterbored or countersunk.", "Bohrt Löcher an Skizzenpunkten – einfach, mit zylindrischer oder kegeliger Senkung."),
  (["Create a sketch on the face where the holes start.", "Place a point for every hole and click Finish Sketch.",
    "Select the sketch and click Hole.", "Choose the type and sizes, then click OK."],
   ["Erstelle eine Skizze auf der Fläche, an der die Bohrungen beginnen.", "Setze für jede Bohrung einen Punkt und klicke Skizze fertig stellen.",
    "Wähle die Skizze und klicke auf Bohrung.", "Wähle Typ und Maße und klicke OK."]),
  options=([["Type", "Simple, Counterbore or Countersink."], ["Diameter, Depth", "Size of the hole; Through all drills all the way."],
            ["Head diameter, Head depth", "Size of the counterbore or countersink."], ["Countersink angle", "Angle of the countersink cone."]],
           [["Typ", "Einfach, Senkung zylindrisch oder Senkung kegelig."], ["Durchmesser, Tiefe", "Maß der Bohrung; Durchgehend bohrt ganz durch."],
            ["Kopfdurchmesser, Kopftiefe", "Maß der Senkung."], ["Senkwinkel", "Winkel des Senkkegels."]]),
  see=["Design_Thread", "Design_Pattern"])
A("Design_Thread", "create", "Design_Thread", ("Thread", "Gewinde"),
  (["thread", "screw", "bolt", "nut", "pitch", "m8"], ["Gewinde", "Schraube", "Bolzen", "Mutter", "Steigung", "M8"]),
  ("Cuts a real thread into a cylindrical face.", "Schneidet ein echtes Gewinde in eine zylindrische Fläche."),
  (["Click the cylindrical face of a bolt or hole.", "Click Thread.", "Set the pitch and click OK."],
   ["Klicke die zylindrische Fläche eines Bolzens oder einer Bohrung an.", "Klicke auf Gewinde.", "Stelle die Steigung ein und klicke OK."]),
  options=([["Pitch", "Distance between two threads, e.g. 1.25 mm for M8."], ["Left Handed", "Left-hand thread."]],
           [["Steigung", "Abstand zweier Gänge, z. B. 1,25 mm bei M8."], ["Linksgängig", "Linksgewinde."]]),
  see=["Design_Hole"])
A("Design_Pattern", "create", "Design_Pattern", ("Pattern", "Muster"),
  (["pattern", "array", "repeat", "copy", "rectangular", "circular", "polar"], ["Muster", "Anordnung", "wiederholen", "kopieren", "rechteckig", "kreisförmig", "polar"]),
  ("Repeats bodies or a feature in rows or around an axis.", "Wiederholt Körper oder ein Feature in Reihen oder um eine Achse."),
  (["Select bodies, or an Extrude, Revolve or Hole in the timeline.", "Click Pattern.", "Choose rectangular or circular and set count and spacing.", "Click OK."],
   ["Wähle Körper oder eine Extrusion, Drehung oder Bohrung in der Zeitleiste.", "Klicke auf Muster.", "Wähle rechteckig oder kreisförmig und stelle Anzahl und Abstand ein.", "Klicke OK."]),
  options=([["Type", "Rectangular (rows) or Circular (around an axis)."], ["Direction, Count, Spacing", "First row; Direction 2 adds a second row."],
            ["Axis, Angle", "For circular patterns: axis through the origin and total angle."]],
           [["Typ", "Rechteckig (Reihen) oder Kreisförmig (um eine Achse)."], ["Richtung, Anzahl, Abstand", "Erste Reihe; Richtung 2 fügt eine zweite Reihe hinzu."],
            ["Achse, Winkel", "Bei kreisförmigen Mustern: Achse durch den Ursprung und Gesamtwinkel."]]),
  see=["Design_Mirror", "Design_Hole"])
A("Design_Mirror", "create", "Design_Mirror", ("Mirror", "Spiegeln"),
  (["mirror", "symmetric", "flip copy"], ["spiegeln", "symmetrisch", "gespiegelte Kopie"]),
  ("Creates a mirrored copy of bodies.", "Erstellt eine gespiegelte Kopie von Körpern."),
  (["Select one or more bodies.", "Click Mirror.", "Choose the mirror plane and click OK."],
   ["Wähle einen oder mehrere Körper.", "Klicke auf Spiegeln.", "Wähle die Spiegelebene und klicke OK."]),
  options=([["Mirror plane", "XY, XZ or YZ plane."]], [["Spiegelebene", "XY-, XZ- oder YZ-Ebene."]]), see=["Design_Pattern", "sketch_mirror"])

# --- Ändern --------------------------------------------------------------------------------------------------------
A("Design_PressPull", "modify", "Design_PressPull", ("Press Pull", "Drücken/Ziehen"),
  (["press pull", "push", "pull", "offset face", "thicker", "thinner"], ["drücken", "ziehen", "Fläche versetzen", "dicker", "dünner"]),
  ("Pushes or pulls flat faces of a body to make it thicker or thinner.", "Drückt oder zieht ebene Flächen eines Körpers, um ihn dicker oder dünner zu machen."),
  (["Click one or more flat faces of a body.", "Click Press Pull.", "Positive distance pulls out, negative pushes in; click OK."],
   ["Klicke eine oder mehrere ebene Flächen eines Körpers an.", "Klicke auf Drücken/Ziehen.", "Positiver Abstand zieht heraus, negativer drückt hinein; klicke OK."]),
  see=["Design_Extrude", "Design_ReplaceFace"])
A("Design_ReplaceFace", "modify", "Design_ReplaceFace", ("Replace Face", "Fläche ersetzen"),
  (["replace face", "match", "flush", "level", "extend to"], ["Fläche ersetzen", "angleichen", "bündig", "verlängern bis"]),
  ("Moves faces of a body onto a target plane or face, e.g. to make two parts flush.",
   "Verschiebt Flächen eines Körpers auf eine Zielebene oder -fläche, z. B. um zwei Teile bündig zu machen."),
  (["Select the faces to replace.", "Add the target plane or face to the selection.", "Click Replace Face and OK."],
   ["Wähle die zu ersetzenden Flächen.", "Füge die Zielebene oder -fläche zur Auswahl hinzu.", "Klicke auf Fläche ersetzen und OK."]),
  tips=(["Works with flat faces; the target must cross their direction."], ["Funktioniert mit ebenen Flächen; das Ziel muss ihre Richtung kreuzen."]),
  see=["Design_PressPull"])
A("Design_SplitFace", "modify", "Design_SplitFace", ("Split Face", "Fläche teilen"),
  (["split face", "divide face", "partition"], ["Fläche teilen", "Fläche aufteilen", "unterteilen"]),
  ("Divides faces of a body along a plane, face or sketch – for example to press-pull only a part of a face.",
   "Teilt Flächen eines Körpers entlang einer Ebene, Fläche oder Skizze – etwa um nur einen Teil einer Fläche zu drücken oder zu ziehen."),
  (["Select the faces to split.", "Add a plane, face or sketch as the cutting tool.", "Click Split Face and OK."],
   ["Wähle die zu teilenden Flächen.", "Füge eine Ebene, Fläche oder Skizze als Schneidwerkzeug hinzu.", "Klicke auf Fläche teilen und OK."]),
  see=["Design_SplitBody", "Design_PressPull"])
A("Design_Fillet", "modify", "Design_Fillet", ("Fillet", "Abrunden"),
  (["fillet", "round", "rounded edge", "radius", "smooth corner"], ["abrunden", "Rundung", "gerundete Kante", "Radius", "weiche Ecke"]),
  ("Rounds edges of a body.", "Rundet Kanten eines Körpers ab."),
  (["Click the edges to round (a face rounds all its edges).", "Click Fillet.", "Type the radius and click OK."],
   ["Klicke die zu rundenden Kanten an (eine Fläche rundet alle ihre Kanten).", "Klicke auf Abrunden.", "Tippe den Radius ein und klicke OK."]),
  options=([["Radius", "Size of the rounding."]], [["Radius", "Größe der Rundung."]]),
  tips=(["If it fails, try a smaller radius or round fewer edges at once."], ["Schlägt es fehl, versuche einen kleineren Radius oder weniger Kanten auf einmal."]),
  see=["Design_Chamfer", "sketch_fillet"])
A("Design_Chamfer", "modify", "Design_Chamfer", ("Chamfer", "Fase"),
  (["chamfer", "bevel", "cut corner", "edge break"], ["Fase", "abschrägen", "Ecke brechen", "Kante brechen"]),
  ("Cuts edges of a body at an angle.", "Schrägt Kanten eines Körpers ab."),
  (["Click the edges (or a face).", "Click Chamfer.", "Type the distance and click OK."],
   ["Klicke die Kanten (oder eine Fläche) an.", "Klicke auf Fase.", "Tippe den Abstand ein und klicke OK."]),
  options=([["Size", "Distance the edge is cut back."]], [["Größe", "Abstand, um den die Kante zurückgeschnitten wird."]]), see=["Design_Fillet"])
A("Design_Shell", "modify", "Design_Shell", ("Shell", "Wandstärke"),
  (["shell", "hollow", "wall thickness", "box", "case", "enclosure"], ["Wandstärke", "aushöhlen", "hohl", "Gehäuse", "Schale", "Box"]),
  ("Hollows out a body, leaving walls of the chosen thickness – for cases and boxes.",
   "Höhlt einen Körper aus und lässt Wände der gewählten Dicke stehen – für Gehäuse und Boxen."),
  (["Click the faces to remove, e.g. the top (or the whole body for a closed hollow).", "Click Shell.", "Set the thickness and click OK."],
   ["Klicke die zu entfernenden Flächen an, z. B. die Oberseite (oder den ganzen Körper für einen geschlossenen Hohlkörper).",
    "Klicke auf Wandstärke.", "Stelle die Dicke ein und klicke OK."]),
  options=([["Thickness", "Wall thickness."], ["Wall outside", "Adds the walls outside instead of inside."]],
           [["Dicke", "Wandstärke."], ["Wand außen", "Legt die Wände außen statt innen an."]]),
  see=["Design_Rib", "Design_Web"])
A("Design_Draft", "modify", "Design_Draft", ("Draft", "Formschräge"),
  (["draft", "taper", "slope", "mold", "angle faces"], ["Formschräge", "Konus", "Neigung", "Gussform", "Flächen neigen"]),
  ("Tilts side faces by a small angle, e.g. so a part comes out of a mold.", "Neigt Seitenflächen um einen kleinen Winkel, z. B. damit ein Teil aus der Form kommt."),
  (["Click the side faces.", "Click Draft.", "Set the angle and click OK."], ["Klicke die Seitenflächen an.", "Klicke auf Formschräge.", "Stelle den Winkel ein und klicke OK."]),
  options=([["Angle", "Tilt angle."], ["Flip direction", "Tilts the other way."]], [["Winkel", "Neigungswinkel."], ["Richtung umkehren", "Neigt in die andere Richtung."]]),
  tips=(["The faces tilt around the bottom of the body unless you pick another plane."],
        ["Die Flächen neigen sich um die Unterseite des Körpers, außer du wählst eine andere Ebene."]),
  see=["Design_Shell"])
A("Design_Combine", "modify", "Design_Combine", ("Combine", "Kombinieren"),
  (["combine", "boolean", "join", "union", "cut", "subtract", "intersect", "merge"],
   ["kombinieren", "boolesch", "verbinden", "vereinigen", "ausschneiden", "abziehen", "Schnittmenge", "zusammenführen"]),
  ("Joins bodies, cuts one out of another or keeps only where they overlap.",
   "Verbindet Körper, schneidet einen aus einem anderen aus oder behält nur die Überschneidung."),
  (["Click the target body first, then one or more tool bodies.", "Click Combine.", "Choose Join, Cut or Intersect and click OK."],
   ["Klicke zuerst den Zielkörper an, dann einen oder mehrere Werkzeugkörper.", "Klicke auf Kombinieren.", "Wähle Verbinden, Ausschneiden oder Schnittmenge und klicke OK."]),
  options=([["Operation", "Join, Cut or Intersect."], ["Keep tools", "Keeps the tool bodies visible instead of using them up."]],
           [["Vorgang", "Verbinden, Ausschneiden oder Schnittmenge."], ["Werkzeuge behalten", "Lässt die Werkzeugkörper sichtbar, statt sie zu verbrauchen."]]),
  see=["Design_SplitBody"])
A("Design_SplitBody", "modify", "Design_SplitBody", ("Split Body", "Körper teilen"),
  (["split body", "cut in half", "divide", "separate"], ["Körper teilen", "halbieren", "trennen", "zerteilen"]),
  ("Cuts a body into pieces along a plane or face.", "Schneidet einen Körper entlang einer Ebene oder Fläche in Stücke."),
  (["Select the body and a plane or face to split with.", "Click Split Body and OK."],
   ["Wähle den Körper und eine Ebene oder Fläche zum Teilen.", "Klicke auf Körper teilen und OK."]),
  tips=(["The plane or face must cut all the way through the body."], ["Die Ebene oder Fläche muss den Körper ganz durchschneiden."]),
  see=["Design_SplitFace", "Design_Combine"])
A("Design_Move", "modify", "Design_Move", ("Move", "Verschieben"),
  (["move", "rotate", "translate", "position", "turn body"], ["verschieben", "drehen", "bewegen", "positionieren", "Körper drehen"]),
  ("Moves and rotates bodies.", "Verschiebt und dreht Körper."),
  (["Select one or more bodies.", "Click Move.", "Type the distances in X, Y, Z and, if needed, a rotation; click OK."],
   ["Wähle einen oder mehrere Körper.", "Klicke auf Verschieben.", "Tippe die Abstände in X, Y, Z und bei Bedarf eine Drehung ein; klicke OK."]),
  options=([["X, Y, Z distance", "How far to move."], ["Rotate around, Angle", "Axis through the body center and rotation angle."]],
           [["X-, Y-, Z-Abstand", "Wie weit verschoben wird."], ["Drehen um, Winkel", "Achse durch die Körpermitte und Drehwinkel."]]),
  tips=(["To move a whole component, use Move on the component or a Joint."], ["Um eine ganze Komponente zu bewegen, verwende Verschieben an der Komponente oder ein Gelenk."]),
  see=["Design_Align", "Design_Joint"])
A("Design_Align", "modify", "Design_Align", ("Align", "Ausrichten"),
  (["align", "snap", "place on", "put together"], ["ausrichten", "andocken", "aufsetzen", "zusammensetzen"]),
  ("Moves a body so that one of its faces, edges or points lands on a target.",
   "Verschiebt einen Körper so, dass eine seiner Flächen, Kanten oder Punkte auf einem Ziel landet."),
  (["Click a face, edge or point of the body to move.", "Then click the target.", "Click Align and OK."],
   ["Klicke eine Fläche, Kante oder einen Punkt des zu bewegenden Körpers an.", "Dann klicke das Ziel an.", "Klicke auf Ausrichten und OK."]),
  see=["Design_Move", "Design_Joint"])
A("Design_Scale", "modify", "Design_Scale", ("Scale", "Skalieren"),
  (["scale", "resize", "bigger", "smaller", "factor"], ["skalieren", "Größe ändern", "größer", "kleiner", "Faktor"]),
  ("Makes bodies bigger or smaller by a factor.", "Macht Körper um einen Faktor größer oder kleiner."),
  (["Select one or more bodies.", "Click Scale.", "Type the factor (2 = double size) and click OK."],
   ["Wähle einen oder mehrere Körper.", "Klicke auf Skalieren.", "Tippe den Faktor ein (2 = doppelte Größe) und klicke OK."]),
  options=([["Factor", "Size multiplier."], ["Center", "Scale around the origin or the body center."]],
           [["Faktor", "Vergrößerungsfaktor."], ["Mitte", "Um den Ursprung oder die Körpermitte skalieren."]]),
  see=["Design_Move"])
A("Design_Delete", "modify", "Design_Box", ("Delete", "Löschen"),
  (["delete", "remove", "erase"], ["löschen", "entfernen"]),
  ("Removes features, sketches or bodies from the design.", "Entfernt Features, Skizzen oder Körper aus dem Design."),
  (["Select the item in the timeline, the browser or the view.", "Right-click and choose Delete (or press Del)."],
   ["Wähle den Eintrag in der Zeitleiste, im Browser oder in der Ansicht.", "Rechtsklick und Löschen wählen (oder Entf drücken)."]),
  tips=(["Undo (Ctrl+Z) brings it back."], ["Rückgängig (Strg+Z) holt es zurück."]), see=["start_timeline"])

# --- Konstruieren ---------------------------------------------------------------------------------------------------
A("Design_OffsetPlane", "construct", "Design_OffsetPlane", ("Offset Plane", "Versetzte Ebene"),
  (["offset plane", "parallel plane", "work plane", "construction plane"], ["versetzte Ebene", "parallele Ebene", "Arbeitsebene", "Konstruktionsebene"]),
  ("Creates a plane parallel to a plane or flat face at a distance – for sketches at another height.",
   "Erstellt eine Ebene parallel zu einer Ebene oder flachen Fläche im Abstand – für Skizzen auf anderer Höhe."),
  (["Click a plane or flat face.", "Click Offset Plane.", "Type the distance and click OK."],
   ["Klicke eine Ebene oder flache Fläche an.", "Klicke auf Versetzte Ebene.", "Tippe den Abstand ein und klicke OK."]),
  see=["Design_Loft", "Design_Plane"])
A("Design_AnglePlane", "construct", "Design_AnglePlane", ("Plane at Angle", "Ebene im Winkel"),
  (["plane at angle", "tilted plane", "rotated plane"], ["Ebene im Winkel", "geneigte Ebene", "gedrehte Ebene"]),
  ("Creates a plane through a straight edge or axis, tilted by an angle.", "Erstellt eine Ebene durch eine gerade Kante oder Achse, um einen Winkel geneigt."),
  (["Click a straight edge or axis (and optionally a reference plane).", "Click Plane at Angle.", "Type the angle and click OK."],
   ["Klicke eine gerade Kante oder Achse an (optional eine Bezugsebene).", "Klicke auf Ebene im Winkel.", "Tippe den Winkel ein und klicke OK."]),
  see=["Design_OffsetPlane"])
A("Design_Midplane", "construct", "Design_Midplane", ("Midplane", "Mittelebene"),
  (["midplane", "middle", "center plane", "symmetry plane"], ["Mittelebene", "Mitte", "mittige Ebene", "Symmetrieebene"]),
  ("Creates a plane exactly between two parallel planes or faces.", "Erstellt eine Ebene genau zwischen zwei parallelen Ebenen oder Flächen."),
  (["Click two parallel planes or flat faces.", "Click Midplane."], ["Klicke zwei parallele Ebenen oder flache Flächen an.", "Klicke auf Mittelebene."]),
  see=["Design_Mirror"])
A("Design_Plane", "construct", "Design_Plane", ("Plane", "Ebene"),
  (["plane", "three points", "work plane"], ["Ebene", "drei Punkte", "Arbeitsebene"]),
  ("Creates a plane through three points, a face and a point, or an edge and a point.",
   "Erstellt eine Ebene durch drei Punkte, eine Fläche und einen Punkt oder eine Kante und einen Punkt."),
  (["Select the references.", "Click Plane."], ["Wähle die Bezüge.", "Klicke auf Ebene."]), see=["Design_OffsetPlane"])
A("Design_Axis", "construct", "Design_Axis", ("Axis", "Achse"),
  (["axis", "center line", "rotation axis"], ["Achse", "Mittellinie", "Drehachse"]),
  ("Creates an axis through a cylindrical face, along a straight edge, through two points or where two planes meet.",
   "Erstellt eine Achse durch eine zylindrische Fläche, entlang einer geraden Kante, durch zwei Punkte oder wo sich zwei Ebenen treffen."),
  (["Select the references.", "Click Axis."], ["Wähle die Bezüge.", "Klicke auf Achse."]), see=["Design_AnglePlane", "Design_Pattern"])
A("Design_Point", "construct", "Design_Point", ("Point", "Punkt"),
  (["point", "construction point", "vertex", "center"], ["Punkt", "Konstruktionspunkt", "Eckpunkt", "Mittelpunkt"]),
  ("Creates a construction point at a vertex, the center of a circle, where an edge meets a plane, or where three planes meet.",
   "Erstellt einen Konstruktionspunkt an einem Eckpunkt, im Mittelpunkt eines Kreises, wo eine Kante eine Ebene trifft oder wo sich drei Ebenen treffen."),
  (["Select the references.", "Click Point."], ["Wähle die Bezüge.", "Klicke auf Punkt."]), see=["Design_Plane"])

# --- Zusammenfügen --------------------------------------------------------------------------------------------------
A("Design_NewComponent", "assemble", "Design_NewComponent", ("New Component", "Neue Komponente"),
  (["component", "part", "assembly", "sub-assembly"], ["Komponente", "Teil", "Baugruppe", "Unterbaugruppe"]),
  ("Creates an empty part with its own origin. Components keep the parts of an assembly apart.",
   "Erstellt ein leeres Teil mit eigenem Ursprung. Komponenten halten die Teile einer Baugruppe auseinander."),
  (["Click New Component.", "Double-click it in the browser to make it active.", "New sketches and bodies now go into this component."],
   ["Klicke auf Neue Komponente.", "Doppelklicke sie im Browser, um sie zu aktivieren.", "Neue Skizzen und Körper landen jetzt in dieser Komponente."]),
  tips=(["Extrude can create a new component directly (Operation: New Component)."], ["Extrudieren kann direkt eine neue Komponente anlegen (Vorgang: Neue Komponente)."]),
  see=["Design_Joint"])
A("Design_Joint", "assemble", "Design_Joint", ("Joint", "Gelenk"),
  (["joint", "connect", "hinge", "slider", "rigid", "assembly", "mate"], ["Gelenk", "verbinden", "Scharnier", "Schieber", "starr", "Baugruppe", "zusammenbauen"]),
  ("Puts a component in place by joining a snap point on it to a point on another component.",
   "Setzt eine Komponente an ihren Platz, indem ein Fangpunkt an ihr mit einem Punkt an einer anderen Komponente verbunden wird."),
  (["Click Joint.", "Click a face, edge, hole or point on the component to move.", "Click where it should go on another component.",
    "Choose the type and, if needed, angle and offset; click OK."],
   ["Klicke auf Gelenk.", "Klicke eine Fläche, Kante, Bohrung oder einen Punkt an der zu bewegenden Komponente an.",
    "Klicke an, wo sie an einer anderen Komponente hin soll.", "Wähle den Typ und bei Bedarf Winkel und Versatz; klicke OK."]),
  options=([["Type", "Rigid, Revolute, Slider or Cylindrical."], ["Angle, Offset", "Rotation around and distance along the joint axis."],
            ["Flip", "Turns the moving component around."]],
           [["Typ", "Starr, Drehung, Schieberegler oder Zylindrisch."], ["Winkel, Versatz", "Drehung um und Abstand entlang der Gelenkachse."],
            ["Umkehren", "Dreht die bewegte Komponente um."]]),
  tips=(["The first click must be on the component that moves; the design itself stays in place."],
        ["Der erste Klick muss an der Komponente sein, die sich bewegt; das Design selbst bleibt an seinem Platz."]),
  see=["Design_NewComponent"])

# --- Prüfen ---------------------------------------------------------------------------------------------------------
A("Design_Measure", "inspect", "Design_Measure", ("Measure", "Messen"),
  (["measure", "distance", "length", "angle", "area", "volume", "radius", "diameter"], ["messen", "Abstand", "Länge", "Winkel", "Fläche", "Volumen", "Radius", "Durchmesser"]),
  ("Shows lengths, distances, angles, radii, areas and volumes.", "Zeigt Längen, Abstände, Winkel, Radien, Flächen und Volumen."),
  (["Click Measure.", "Click one or two points, edges, faces or bodies.", "Read the values in the panel."],
   ["Klicke auf Messen.", "Klicke einen oder zwei Punkte, Kanten, Flächen oder Körper an.", "Lies die Werte im Panel ab."]),
  see=["Design_Section"])
A("Design_Section", "inspect", "Design_Section", ("Section Analysis", "Schnittanalyse"),
  (["section", "cut view", "inside", "cross section"], ["Schnitt", "Schnittansicht", "innen", "Querschnitt"]),
  ("Cuts the view open at a plane so you can look inside. The model itself stays unchanged.",
   "Schneidet die Ansicht an einer Ebene auf, damit du hineinschauen kannst. Das Modell selbst bleibt unverändert."),
  (["Click a plane or flat face.", "Click Section Analysis.", "Click it again to turn the cut off."],
   ["Klicke eine Ebene oder flache Fläche an.", "Klicke auf Schnittanalyse.", "Klicke noch einmal darauf, um den Schnitt auszuschalten."]),
  see=["Design_Measure"])
A("Std_ViewFitAll", "inspect", "Std_ViewFitAll", ("Fit All", "Alles zeigen"),
  (["fit", "zoom all", "show everything", "lost model"], ["einpassen", "alles zoomen", "alles zeigen", "Modell verloren"]),
  ("Zooms so that the whole model fits the window.", "Zoomt so, dass das ganze Modell ins Fenster passt."),
  (["Click Fit All."], ["Klicke auf Alles zeigen."]), see=["start_navigation"])

# --- Werkzeuge ------------------------------------------------------------------------------------------------------
A("Design_Parameters", "utilities", "Design_Parameters", ("Change Parameters", "Parameter ändern"),
  (["parameters", "variables", "formula", "expression", "named value"], ["Parameter", "Variablen", "Formel", "Ausdruck", "benannter Wert"]),
  ("Defines named values such as Width = 40 mm that you can use in any dimension field.",
   "Legt benannte Werte wie Breite = 40 mm an, die du in jedem Maßfeld verwenden kannst."),
  (["Click Parameters.", "Type a name and a value and click Add.", "Type the name, or a formula like Width * 2, into any dimension field.",
    "Change the value later and everything that uses it updates."],
   ["Klicke auf Parameter.", "Tippe einen Namen und einen Wert ein und klicke Hinzufügen.",
    "Tippe den Namen oder eine Formel wie Breite * 2 in ein beliebiges Maßfeld.", "Ändere den Wert später, und alles, was ihn nutzt, passt sich an."]),
  tips=(["Names use letters, digits and _ only, no spaces."], ["Namen bestehen nur aus Buchstaben, Ziffern und _, ohne Leerzeichen."]),
  see=["sketch_dimension", "start_timeline"])
A("Design_Appearance", "utilities", "Design_Appearance", ("Appearance", "Darstellung"),
  (["appearance", "color", "colour", "material", "paint"], ["Darstellung", "Farbe", "Material", "einfärben"]),
  ("Gives bodies a material look or a color.", "Gibt Körpern ein Material-Aussehen oder eine Farbe."),
  (["Select bodies.", "Click Appearance.", "Pick a material or a color."], ["Wähle Körper.", "Klicke auf Darstellung.", "Wähle ein Material oder eine Farbe."]),
  tips=(["The default look of new bodies is set in Settings → Body material."], ["Das Standard-Aussehen neuer Körper stellst du in den Einstellungen unter Körpermaterial ein."]),
  see=["settings"])
A("settings", "utilities", "MyCAD_Settings", ("Settings", "Einstellungen"),
  (["settings", "preferences", "language", "german", "mouse", "keys", "glass", "material", "projects folder"],
   ["Einstellungen", "Optionen", "Sprache", "Deutsch", "Maus", "Tasten", "Glas", "Material", "Projektordner"]),
  ("Adjusts navigation, keys, look and language. Open it with the gear button or Ctrl+,.",
   "Passt Navigation, Tasten, Aussehen und Sprache an. Öffnen mit dem Zahnrad oder Strg+,."),
  (["Navigation: pick the mouse style; the preview shows which buttons rotate, pan and zoom.",
    "Keys: turn keys into mouse buttons, e.g. Shift as the middle button.",
    "View: camera, rotation center, tool names, body material, glass and language."],
   ["Navigation: wähle den Maus-Stil; die Vorschau zeigt, welche Tasten drehen, verschieben und zoomen.",
    "Tasten: mache Tasten zu Maustasten, z. B. Umschalt als mittlere Taste.",
    "Ansicht: Kamera, Drehmittelpunkt, Werkzeugnamen, Körpermaterial, Glas und Sprache."]),
  tips=(["A new language takes effect after restarting MyCAD."], ["Eine neue Sprache wirkt nach einem Neustart von MyCAD."]),
  commands=["MyCAD_Settings"], see=["start_navigation"])

# --- Skizze: Erstellen ----------------------------------------------------------------------------------------------
S = "sketch_create"
A("sketch_line", S, "Sketcher_CreateLine", ("Line", "Linie"), (["line", "straight", "segment"], ["Linie", "gerade", "Strecke"]),
  ("Draws a straight line between two points.", "Zeichnet eine gerade Linie zwischen zwei Punkten."),
  (["Click Line.", "Click the start point, then the end point.", "Type a length in the field next to the cursor to fix it right away."],
   ["Klicke auf Linie.", "Klicke den Startpunkt, dann den Endpunkt.", "Tippe eine Länge ins Feld neben dem Cursor, um sie gleich festzulegen."]),
  tips=(["Ends snap to existing points and lines; horizontal and vertical lines get their constraint automatically."],
        ["Enden rasten an vorhandenen Punkten und Linien ein; waagrechte und senkrechte Linien bekommen ihre Abhängigkeit automatisch."]),
  commands=["Sketcher_CreateLine", "Sketcher_CompLine"], see=["sketch_polyline", "sketch_dimension"])
A("sketch_polyline", S, "Sketcher_CreatePolyline", ("Polyline", "Polylinie"), (["polyline", "outline", "connected lines", "contour"], ["Polylinie", "Umriss", "verbundene Linien", "Kontur"]),
  ("Draws connected lines and arcs in one go – ideal for an outline.", "Zeichnet verbundene Linien und Bögen in einem Zug – ideal für einen Umriss."),
  (["Click Polyline.", "Click point after point.", "Press M to switch between line and arc segments.", "Click the start point again to close the outline, or press Esc."],
   ["Klicke auf Polylinie.", "Klicke Punkt für Punkt.", "Drücke M, um zwischen Linien- und Bogenstücken zu wechseln.",
    "Klicke den Startpunkt erneut, um den Umriss zu schließen, oder drücke Esc."]),
  see=["sketch_line"])
A("sketch_rectangle", S, "Sketcher_CreateRectangle", ("Rectangle", "Rechteck"), (["rectangle", "square", "box", "rounded rectangle", "centered"], ["Rechteck", "Quadrat", "Kasten", "abgerundetes Rechteck", "mittig"]),
  ("Draws a rectangle from two corners, around a center, or with rounded corners.", "Zeichnet ein Rechteck aus zwei Ecken, um einen Mittelpunkt oder mit abgerundeten Ecken."),
  (["Pick the variant in the dropdown next to Rectangle.", "Click the first corner (or the center).", "Click the opposite corner."],
   ["Wähle die Variante im Dropdown neben Rechteck.", "Klicke die erste Ecke (oder den Mittelpunkt).", "Klicke die gegenüberliegende Ecke."]),
  commands=["Sketcher_CompCreateRectangles", "Sketcher_CreateRectangle", "Sketcher_CreateRectangle_Center", "Sketcher_CreateOblong"], see=["sketch_dimension"])
A("sketch_circle", S, "Sketcher_CreateCircle", ("Circle and Ellipse", "Kreis und Ellipse"), (["circle", "ellipse", "round", "hole outline", "oval"], ["Kreis", "Ellipse", "rund", "Bohrungsumriss", "Oval"]),
  ("Draws a circle from its center or through three points, or an ellipse.", "Zeichnet einen Kreis vom Mittelpunkt oder durch drei Punkte, oder eine Ellipse."),
  (["Pick the variant in the dropdown next to Circle.", "Circle from center: click the center, then a point on the circle.", "Type the diameter in the field next to the cursor if you know it."],
   ["Wähle die Variante im Dropdown neben Kreis.", "Kreis vom Mittelpunkt: klicke den Mittelpunkt, dann einen Punkt auf dem Kreis.", "Tippe den Durchmesser ins Feld neben dem Cursor, wenn du ihn kennst."]),
  commands=["Sketcher_CompCreateConic", "Sketcher_CreateCircle", "Sketcher_Create3PointCircle", "Sketcher_CreateEllipseByCenter", "Sketcher_CreateEllipseBy3Points"],
  see=["Design_Revolve", "Design_Extrude"])
A("sketch_arc", S, "Sketcher_CreateArc", ("Arc", "Bogen"), (["arc", "curve", "round corner", "elliptical arc"], ["Bogen", "Kurve", "runde Ecke", "Ellipsenbogen"]),
  ("Draws a circular arc from its center or through three points, or an elliptical, hyperbolic or parabolic arc.",
   "Zeichnet einen Kreisbogen vom Mittelpunkt oder durch drei Punkte oder einen Ellipsen-, Hyperbel- oder Parabelbogen."),
  (["Pick the variant in the dropdown next to Arc.", "Arc from center: click the center, the start and the end."],
   ["Wähle die Variante im Dropdown neben Bogen.", "Bogen vom Mittelpunkt: klicke den Mittelpunkt, den Anfang und das Ende."]),
  commands=["Sketcher_CompCreateArc", "Sketcher_CreateArc", "Sketcher_Create3PointArc", "Sketcher_CreateArcOfEllipse", "Sketcher_CreateArcOfHyperbola", "Sketcher_CreateArcOfParabola"],
  see=["sketch_fillet"])
A("sketch_slot", S, "Sketcher_CreateSlot", ("Slot", "Langloch"), (["slot", "oblong hole", "groove", "arc slot"], ["Langloch", "Schlitz", "Nut", "Bogen-Langloch"]),
  ("Draws a slot: two half circles joined by straight lines, or along an arc.", "Zeichnet ein Langloch: zwei Halbkreise mit geraden Linien verbunden, oder entlang eines Bogens."),
  (["Click Slot.", "Click the first center, then the second.", "Move the mouse for the width and click."],
   ["Klicke auf Langloch.", "Klicke den ersten Mittelpunkt, dann den zweiten.", "Bewege die Maus für die Breite und klicke."]),
  commands=["Sketcher_CompSlot", "Sketcher_CreateSlot", "Sketcher_CreateArcSlot"], see=["Design_Extrude"])
A("sketch_polygon", S, "Sketcher_CreateHexagon", ("Polygon", "Polygon"), (["polygon", "hexagon", "triangle", "square", "octagon", "nut"], ["Polygon", "Sechseck", "Dreieck", "Quadrat", "Achteck", "Mutter"]),
  ("Draws a regular polygon – triangle, square, hexagon and more.", "Zeichnet ein regelmäßiges Vieleck – Dreieck, Quadrat, Sechseck und mehr."),
  (["Pick the number of corners in the dropdown.", "Click the center, then a corner."], ["Wähle die Anzahl der Ecken im Dropdown.", "Klicke den Mittelpunkt, dann eine Ecke."]),
  commands=["Sketcher_CompCreateRegularPolygon", "Sketcher_CreateTriangle", "Sketcher_CreateSquare", "Sketcher_CreatePentagon", "Sketcher_CreateHexagon",
            "Sketcher_CreateHeptagon", "Sketcher_CreateOctagon", "Sketcher_CreateRegularPolygon"], see=["sketch_rectangle"])
A("sketch_bspline", S, "Sketcher_CreateBSpline", ("B-Spline", "B-Spline"), (["spline", "free curve", "organic", "smooth curve"], ["Spline", "Freiformkurve", "organisch", "glatte Kurve"]),
  ("Draws a smooth free-form curve through control points or through points on the curve.",
   "Zeichnet eine glatte Freiformkurve über Kontrollpunkte oder durch Punkte auf der Kurve."),
  (["Pick the variant in the dropdown.", "Click point after point.", "Press Esc or right-click to finish."],
   ["Wähle die Variante im Dropdown.", "Klicke Punkt für Punkt.", "Drücke Esc oder klicke rechts zum Beenden."]),
  commands=["Sketcher_CompCreateBSpline", "Sketcher_CreateBSpline", "Sketcher_CreatePeriodicBSpline", "Sketcher_CreateBSplineByInterpolation", "Sketcher_CreatePeriodicBSplineByInterpolation"],
  see=["sketch_conic"])
A("sketch_conic", S, "Sketcher_CreateConic", ("Conic", "Kegelschnitt"), (["conic", "rho", "curve", "transition"], ["Kegelschnitt", "Rho", "Kurve", "Übergang"]),
  ("Draws a conic curve between two points whose fullness is set by a rho value.", "Zeichnet einen Kegelschnitt zwischen zwei Punkten, dessen Bauchigkeit ein Rho-Wert bestimmt."),
  (["Click Conic.", "Click start and end point, then the point that sets the tangents.", "Set the rho value and click."],
   ["Klicke auf Kegelschnitt.", "Klicke Start- und Endpunkt, dann den Punkt für die Tangenten.", "Stelle den Rho-Wert ein und klicke."]),
  commands=["Sketcher_CreateConic"], see=["sketch_bspline"])
A("sketch_point", S, "Sketcher_CreatePoint", ("Point", "Punkt"), (["point", "hole center", "marker"], ["Punkt", "Bohrungsmittelpunkt", "Markierung"]),
  ("Places a single point – for example where a hole goes.", "Setzt einen einzelnen Punkt – zum Beispiel, wo eine Bohrung hin soll."),
  (["Click Point.", "Click where the point goes."], ["Klicke auf Punkt.", "Klicke, wo der Punkt hin soll."]),
  commands=["Sketcher_CreatePoint"], see=["Design_Hole"])
A("sketch_text", S, "Sketcher_CreateText", ("Text", "Text"), (["text", "lettering", "label", "font", "engrave"], ["Text", "Schrift", "Beschriftung", "Schriftart", "gravieren"]),
  ("Writes text as outlines in the sketch – to emboss or extrude it.", "Schreibt Text als Umrisse in die Skizze – zum Prägen oder Extrudieren."),
  (["Click Text.", "Click where the text starts.", "Type the text, choose font and size, confirm."],
   ["Klicke auf Text.", "Klicke, wo der Text beginnt.", "Tippe den Text, wähle Schriftart und Größe, bestätige."]),
  commands=["Sketcher_CreateText"], see=["Design_Emboss"])
A("sketch_project", S, "Sketcher_Projection", ("Project", "Projizieren"), (["project", "include", "external", "edge of body", "intersect"], ["projizieren", "übernehmen", "extern", "Körperkante", "Schnittkante"]),
  ("Brings edges of the model into the sketch so you can draw against them.", "Holt Kanten des Modells in die Skizze, damit du an ihnen entlang zeichnen kannst."),
  (["Click Project.", "Click edges or faces of a body; they appear as purple lines.", "Press Esc when done."],
   ["Klicke auf Projizieren.", "Klicke Kanten oder Flächen eines Körpers an; sie erscheinen als lila Linien.", "Drücke Esc, wenn du fertig bist."]),
  tips=(["Projected lines follow the model when it changes."], ["Projizierte Linien folgen dem Modell, wenn es sich ändert."]),
  commands=["Sketcher_CompExternal", "Sketcher_Projection", "Sketcher_Intersection"], see=["sketch_basics"])

# --- Skizze: Ändern -------------------------------------------------------------------------------------------------
S = "sketch_modify"
A("sketch_fillet", S, "Sketcher_CreateFillet", ("Sketch Fillet and Chamfer", "Skizzen-Rundung und -Fase"), (["fillet", "round corner", "chamfer", "corner"], ["Rundung", "Ecke runden", "Fase", "Ecke"]),
  ("Rounds or bevels a corner between two lines in the sketch.", "Rundet oder schrägt eine Ecke zwischen zwei Linien in der Skizze ab."),
  (["Pick Fillet or Chamfer in the dropdown.", "Click the corner point (or both lines).", "Move the mouse for the size and click."],
   ["Wähle Rundung oder Fase im Dropdown.", "Klicke den Eckpunkt (oder beide Linien) an.", "Bewege die Maus für die Größe und klicke."]),
  commands=["Sketcher_CompCreateFillets", "Sketcher_CreateFillet", "Sketcher_CreateChamfer"], see=["Design_Fillet"])
A("sketch_trim", S, "Sketcher_Trimming", ("Trim, Extend and Split", "Stutzen, Verlängern und Teilen"), (["trim", "cut", "extend", "split", "remove part"], ["stutzen", "abschneiden", "verlängern", "teilen", "Teil entfernen"]),
  ("Trim removes a piece of a line up to the next crossing; Extend lengthens a line; Split cuts it in two.",
   "Stutzen entfernt ein Stück einer Linie bis zur nächsten Kreuzung; Verlängern verlängert eine Linie; Teilen schneidet sie in zwei."),
  (["Pick Trim, Extend or Split in the dropdown.", "Trim: click the piece to remove.", "Extend: click the line, then where it should end.", "Split: click where the line is cut."],
   ["Wähle Stutzen, Verlängern oder Teilen im Dropdown.", "Stutzen: klicke das Stück, das weg soll.", "Verlängern: klicke die Linie, dann wo sie enden soll.", "Teilen: klicke, wo die Linie geschnitten wird."]),
  commands=["Sketcher_CompCurveEdition", "Sketcher_Trimming", "Sketcher_Extend", "Sketcher_Split"], see=["sketch_fillet"])
A("sketch_offset", S, "Sketcher_Offset", ("Offset", "Versatz"), (["offset", "parallel copy", "wall", "outline inside"], ["Versatz", "parallele Kopie", "Wand", "Umriss innen"]),
  ("Draws a parallel copy of lines at a distance – e.g. for a wall.", "Zeichnet eine parallele Kopie von Linien im Abstand – z. B. für eine Wand."),
  (["Select the lines (e.g. a closed outline).", "Click Offset.", "Move the mouse or type the distance and click."],
   ["Wähle die Linien (z. B. einen geschlossenen Umriss).", "Klicke auf Versatz.", "Bewege die Maus oder tippe den Abstand ein und klicke."]),
  commands=["Sketcher_Offset"], see=["Design_Shell"])
A("sketch_mirror", S, "Sketcher_Symmetry", ("Mirror", "Spiegeln"), (["mirror", "symmetric copy", "flip"], ["spiegeln", "symmetrische Kopie", "umklappen"]),
  ("Mirrors sketch geometry across a line or point.", "Spiegelt Skizzengeometrie an einer Linie oder einem Punkt."),
  (["Select the geometry.", "Click Mirror.", "Click the mirror line or point."], ["Wähle die Geometrie.", "Klicke auf Spiegeln.", "Klicke die Spiegellinie oder den Punkt an."]),
  commands=["Sketcher_Symmetry"], see=["Design_Mirror"])
A("sketch_pattern", S, "Sketcher_RectangularArray", ("Pattern", "Muster"), (["pattern", "array", "copies", "polar", "rotate copies"], ["Muster", "Anordnung", "Kopien", "polar", "gedrehte Kopien"]),
  ("Copies sketch geometry in rows and columns, or rotated around a point.", "Kopiert Skizzengeometrie in Reihen und Spalten oder gedreht um einen Punkt."),
  (["Select the geometry.", "Pick Rectangular Array or Rotate in the dropdown.", "Set the number of copies and spacing (or angle) and click."],
   ["Wähle die Geometrie.", "Wähle Rechteckige Anordnung oder Drehen im Dropdown.", "Stelle Anzahl und Abstand (oder Winkel) ein und klicke."]),
  commands=["Sketcher_RectangularArray", "Sketcher_Rotate"], see=["Design_Pattern"])
A("sketch_move", S, "Sketcher_Translate", ("Move and Scale", "Verschieben und Skalieren"), (["move", "translate", "copy", "scale", "resize"], ["verschieben", "bewegen", "kopieren", "skalieren", "Größe ändern"]),
  ("Moves or copies sketch geometry, or scales it around a point.", "Verschiebt oder kopiert Skizzengeometrie oder skaliert sie um einen Punkt."),
  (["Select the geometry.", "Pick Move or Scale in the dropdown.", "Click the base point, then the target point (or the scale factor)."],
   ["Wähle die Geometrie.", "Wähle Verschieben oder Skalieren im Dropdown.", "Klicke den Basispunkt, dann den Zielpunkt (oder den Skalierfaktor)."]),
  commands=["Sketcher_Translate", "Sketcher_Scale"], see=["sketch_pattern"])
A("sketch_construction", S, "Sketcher_ToggleConstruction", ("Construction", "Konstruktion"), (["construction", "helper line", "reference", "dashed"], ["Konstruktion", "Hilfslinie", "Bezug", "gestrichelt"]),
  ("Turns lines into construction geometry: orange dashed helper lines that are never part of a profile.",
   "Macht Linien zu Konstruktionsgeometrie: orange gestrichelte Hilfslinien, die nie zu einem Profil gehören."),
  (["Select lines.", "Click Construction. Click again to turn it back into normal geometry."],
   ["Wähle Linien.", "Klicke auf Konstruktion. Ein weiterer Klick macht sie wieder zu normaler Geometrie."]),
  commands=["Sketcher_ToggleConstruction"], see=["sketch_basics"])

# --- Skizze: Abhängigkeiten -----------------------------------------------------------------------------------------
S = "sketch_constraints"
A("sketch_dimension", S, "Sketcher_Dimension", ("Dimension", "Bemaßung"), (["dimension", "size", "length", "distance", "radius", "diameter", "angle"], ["Bemaßung", "Maß", "Länge", "Abstand", "Radius", "Durchmesser", "Winkel"]),
  ("One tool for every size: length, distance, radius, diameter and angle.", "Ein Werkzeug für jedes Maß: Länge, Abstand, Radius, Durchmesser und Winkel."),
  (["Click Dimension.", "Click a line (length), two points (distance), a circle (diameter) or two lines (angle).", "Place the dimension and type the value."],
   ["Klicke auf Bemaßung.", "Klicke eine Linie (Länge), zwei Punkte (Abstand), einen Kreis (Durchmesser) oder zwei Linien (Winkel) an.", "Platziere das Maß und tippe den Wert ein."]),
  tips=(["Type a parameter name or a formula instead of a number.", "Double-click a dimension to change it."],
        ["Tippe statt einer Zahl einen Parameternamen oder eine Formel ein.", "Doppelklick auf ein Maß ändert es."]),
  commands=["Sketcher_Dimension", "Sketcher_CompDimensionTools", "Sketcher_ConstrainDistanceX", "Sketcher_ConstrainDistanceY", "Sketcher_ConstrainDistance",
            "Sketcher_ConstrainRadiam", "Sketcher_ConstrainRadius", "Sketcher_ConstrainDiameter", "Sketcher_ConstrainAngle", "Sketcher_ConstrainLock"],
  see=["Design_Parameters", "sketch_basics"])
A("sketch_coincident", S, "Sketcher_ConstrainCoincidentUnified", ("Coincident", "Koinzident"), (["coincident", "connect points", "point on line", "join"], ["koinzident", "Punkte verbinden", "Punkt auf Linie", "zusammenfügen"]),
  ("Puts two points on top of each other, or a point onto a line.", "Legt zwei Punkte übereinander oder einen Punkt auf eine Linie."),
  (["Select two points (or a point and a line).", "Click Coincident."], ["Wähle zwei Punkte (oder einen Punkt und eine Linie).", "Klicke auf Koinzident."]),
  tips=(["Open outlines often just miss a coincident corner – then there is no profile to extrude."],
        ["Offenen Umrissen fehlt oft nur eine koinzidente Ecke – dann gibt es kein Profil zum Extrudieren."]),
  commands=["Sketcher_ConstrainCoincidentUnified"], see=["sketch_basics"])
A("sketch_horver", S, "Sketcher_ConstrainHorizontal", ("Horizontal and Vertical", "Horizontal und Vertikal"), (["horizontal", "vertical", "level", "straight up"], ["horizontal", "vertikal", "waagrecht", "senkrecht"]),
  ("Makes a line horizontal or vertical.", "Macht eine Linie waagrecht oder senkrecht."),
  (["Select a line (or two points).", "Pick Horizontal or Vertical in the dropdown."], ["Wähle eine Linie (oder zwei Punkte).", "Wähle Horizontal oder Vertikal im Dropdown."]),
  commands=["Sketcher_ConstrainHorizontal", "Sketcher_ConstrainVertical", "Sketcher_ConstrainHorVer", "Sketcher_CompHorVer"], see=["sketch_parallel"])
A("sketch_parallel", S, "Sketcher_ConstrainParallel", ("Parallel and Perpendicular", "Parallel und Senkrecht"), (["parallel", "perpendicular", "right angle", "90 degrees"], ["parallel", "senkrecht", "rechter Winkel", "90 Grad"]),
  ("Makes two lines parallel or at a right angle.", "Macht zwei Linien parallel oder rechtwinklig zueinander."),
  (["Select two lines.", "Pick Parallel or Perpendicular in the dropdown."], ["Wähle zwei Linien.", "Wähle Parallel oder Senkrecht im Dropdown."]),
  commands=["Sketcher_ConstrainParallel", "Sketcher_ConstrainPerpendicular"], see=["sketch_horver"])
A("sketch_tangent", S, "Sketcher_ConstrainTangent", ("Tangent", "Tangential"), (["tangent", "smooth transition", "touch"], ["tangential", "glatter Übergang", "berühren"]),
  ("Makes a line and an arc (or two curves) touch smoothly.", "Lässt eine Linie und einen Bogen (oder zwei Kurven) glatt ineinander übergehen."),
  (["Select the two curves.", "Click Tangent."], ["Wähle die beiden Kurven.", "Klicke auf Tangential."]), commands=["Sketcher_ConstrainTangent"], see=["sketch_arc"])
A("sketch_equal", S, "Sketcher_ConstrainEqual", ("Equal", "Gleich"), (["equal", "same size", "same length", "same radius"], ["gleich", "gleiche Größe", "gleiche Länge", "gleicher Radius"]),
  ("Gives lines the same length, or circles the same radius.", "Gibt Linien die gleiche Länge oder Kreisen den gleichen Radius."),
  (["Select two or more lines or circles.", "Click Equal."], ["Wähle zwei oder mehr Linien oder Kreise.", "Klicke auf Gleich."]), commands=["Sketcher_ConstrainEqual"], see=["sketch_dimension"])
A("sketch_symmetric", S, "Sketcher_ConstrainSymmetric", ("Symmetric", "Symmetrisch"), (["symmetric", "centered", "mirror constraint"], ["symmetrisch", "mittig", "Spiegel-Abhängigkeit"]),
  ("Keeps two points symmetric to a line or point – e.g. a part centered on an axis.", "Hält zwei Punkte symmetrisch zu einer Linie oder einem Punkt – z. B. ein Teil mittig auf einer Achse."),
  (["Select two points and then the symmetry line or point.", "Click Symmetric."], ["Wähle zwei Punkte und dann die Symmetrielinie oder den Punkt.", "Klicke auf Symmetrisch."]),
  commands=["Sketcher_ConstrainSymmetric"], see=["sketch_mirror"])
A("sketch_block", S, "Sketcher_ConstrainBlock", ("Fix", "Fixieren"), (["fix", "block", "lock", "freeze"], ["fixieren", "blockieren", "sperren", "einfrieren"]),
  ("Locks geometry in place so it can no longer move.", "Fixiert Geometrie an ihrem Platz, so dass sie sich nicht mehr bewegt."),
  (["Select the geometry.", "Click Fix."], ["Wähle die Geometrie.", "Klicke auf Fixieren."]), commands=["Sketcher_ConstrainBlock"], see=["sketch_dimension"])
A("sketch_finish", S, "Sketcher_LeaveSketch", ("Finish Sketch", "Skizze fertig stellen"), (["finish", "leave sketch", "close sketch", "done"], ["fertig", "Skizze verlassen", "Skizze schließen", "erledigt"]),
  ("Leaves the sketch and goes back to the model; the closed areas become profiles.", "Verlässt die Skizze und kehrt zum Modell zurück; die geschlossenen Flächen werden Profile."),
  (["Click Finish Sketch (blue button), or press Esc twice."], ["Klicke auf Skizze fertig stellen (blauer Knopf) oder drücke zweimal Esc."]),
  commands=["Sketcher_LeaveSketch"], see=["Design_Extrude", "sketch_basics"])


def main():
    images = HELP / "images"
    data = {"groups": [{"id": g, "title": {"en": en, "de": de}} for g, en, de in GROUPS], "articles": []}
    for a in ARTICLES:
        a = dict(a)
        caption = a.pop("caption", None)
        if (images / (a["id"] + ".jpg")).exists():  # Bild von tools/help_images.py
            a["images"] = [{"file": a["id"] + ".jpg", "caption": caption or {"en": "", "de": ""}}]
        data["articles"].append(a)
    (HELP / "help.json").write_text(json.dumps(data, ensure_ascii=False, indent=1) + "\n")
    files = ["help.json"] + sorted("images/" + p.name for p in images.glob("*.jpg"))
    (HELP / "help.qrc").write_text('<RCC>\n    <qresource prefix="/mycad/help">\n'
                                   + "".join("        <file>%s</file>\n" % f for f in files) + "    </qresource>\n</RCC>\n")
    print("%d Artikel, %d Bilder" % (len(ARTICLES), len(files) - 1))


if __name__ == "__main__":
    main()
