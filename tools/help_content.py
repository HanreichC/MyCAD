#!/usr/bin/env python3
# Inhalt der MyCAD-Hilfe (Englisch + Deutsch). Erzeugt src/Gui/Shell/help/help.json und help.qrc:
#   python3 tools/help_content.py
# Bilder: tools/help_images.py (läuft in MyCAD) legt sie unter src/Gui/Shell/help/images/<id>.jpg ab.
# Alle Namen (Werkzeugleiste, Dropdowns, Dialogfelder) entsprechen der Oberfläche; geprüft am 14.10.2026 mit
# einem Abzug der laufenden App in beiden Sprachen. Neue Texte bitte genauso gegen die Oberfläche prüfen.
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


def pairs(items):
    """[(en, de), …] -> ([en …], [de …])"""
    return [e for e, _ in items], [d for _, d in items]


def A(id, group, icon, title, keywords, summary, steps, options=(), tips=(), see=(), commands=(), caption=None):
    """steps/tips: Liste von (Englisch, Deutsch); options: Liste von (Name en, Text en, Name de, Text de)."""
    st, tp = pairs(steps), pairs(tips)
    a = {"id": id, "group": group, "icon": icon, "commands": list(commands),
         "title": {"en": title[0], "de": title[1]}, "keywords": {"en": keywords[0], "de": keywords[1]},
         "summary": {"en": summary[0], "de": summary[1]}, "steps": {"en": st[0], "de": st[1]}, "see": list(see)}
    if options:
        a["options"] = {"en": [[o[0], o[1]] for o in options], "de": [[o[2], o[3]] for o in options]}
    if tips:
        a["tips"] = {"en": tp[0], "de": tp[1]}
    if caption:
        a["caption"] = {"en": caption[0], "de": caption[1]}
    ARTICLES.append(a)


# --- Bausteine: wo etwas liegt --------------------------------------------------------------------------------------
SEC = {"FILE": "DATEI", "CREATE": "ERSTELLEN", "MODIFY": "ÄNDERN", "CONSTRUCT": "KONSTRUIEREN", "ASSEMBLE": "ZUSAMMENFÜGEN",
       "INSPECT": "PRÜFEN", "UTILITIES": "WERKZEUGE", "CONSTRAINTS": "ABHÄNGIGKEITEN"}


def tool(section, button, variant=None, sketch=False):
    """Schritt: Werkzeug in der Leiste oben finden (button/variant: (en, de))"""
    bar_en = "sketch toolbar at the top" if sketch else "toolbar at the top"
    bar_de = "Skizzen-Werkzeugleiste oben" if sketch else "Werkzeugleiste oben"
    if not variant or variant == button:
        if variant:
            return (f"In the {bar_en}, in the {section} section, click {button[0]}. (If the button shows another tool, "
                    f"click the small arrow ▾ next to it and choose {button[0]}.)",
                    f"Klicke in der {bar_de} im Bereich {SEC[section]} auf {button[1]}. (Zeigt der Knopf ein anderes Werkzeug, "
                    f"klicke auf den kleinen Pfeil ▾ daneben und wähle {button[1]}.)")
        return (f"In the {bar_en}, in the {section} section, click {button[0]}.",
                f"Klicke in der {bar_de} im Bereich {SEC[section]} auf {button[1]}.")
    return (f"In the {bar_en}, in the {section} section, click the small arrow ▾ next to {button[0]} and choose {variant[0]}. "
            f"The button now shows {variant[0]}, so next time one click is enough.",
            f"Klicke in der {bar_de} im Bereich {SEC[section]} auf den kleinen Pfeil ▾ neben {button[1]} und wähle {variant[1]}. "
            f"Der Knopf zeigt danach {variant[1]}, beim nächsten Mal reicht also ein Klick.")


PANEL = ("A panel opens on the right; the model shows a live preview of the result.",
         "Rechts öffnet sich ein Panel; das Modell zeigt das Ergebnis gleich als Vorschau.")
OK = ("Click OK at the top of the panel. Cancel (next to it) or Esc discards the tool without changing anything.",
      "Klicke oben im Panel auf OK. Abbrechen (daneben) oder Esc verwirft das Werkzeug, ohne etwas zu ändern.")
MULTI = ("Hold Ctrl while clicking to select more than one item; click into empty space to clear the selection.",
         "Halte Strg gedrückt, um mehrere Dinge auszuwählen; ein Klick ins Leere hebt die Auswahl auf.")
OPERATION = ("Operation", "New Body creates a separate body; Join adds to an existing body, Cut removes from it, Intersect "
             "keeps only the overlap (MyCAD picks the body the sketch sits on); New Component puts the new body into its own component.",
             "Vorgang", "Neuer Körper legt einen eigenen Körper an; Verbinden fügt zu einem vorhandenen Körper hinzu, Ausschneiden "
             "zieht davon ab, Schnittmenge behält nur die Überschneidung (MyCAD nimmt den Körper, auf dem die Skizze liegt); "
             "Neue Komponente legt den neuen Körper in eine eigene Komponente.")
FLIP = ("Flip direction", "Builds towards the other side.", "Richtung umkehren", "Baut zur anderen Seite.")
EDIT_LATER = ("Everything you create appears as a step in the timeline at the bottom of the window. Double-click the step to "
              "open the same panel again and change the values later.",
              "Alles, was du erstellst, erscheint als Schritt in der Zeitleiste unten im Fenster. Doppelklick auf den Schritt "
              "öffnet dasselbe Panel wieder, dort änderst du die Werte später.")
FORMULA = ("Every number field also takes units (e.g. 1 in) and formulas or parameter names such as Width * 2.",
           "Jedes Zahlenfeld nimmt auch Einheiten (z. B. 1 in) sowie Formeln oder Parameternamen wie Breite * 2.")
PROFILE = ("Outside a sketch, its closed areas (profiles) are shown light orange. Click one to select it – it turns blue.",
           "Außerhalb einer Skizze sind ihre geschlossenen Flächen (Profile) hellorange. Ein Klick wählt eine aus – sie wird blau.")

# --- Erste Schritte ------------------------------------------------------------------------------------------------
A("start_first", "start", "Std_New", ("Your first design", "Dein erstes Design"),
  (["start", "beginner", "tutorial", "first steps", "how to", "overview"], ["Start", "Anfänger", "Anleitung", "erste Schritte", "wie", "Überblick"]),
  ("In MyCAD you draw a flat sketch, then turn its closed areas into solid bodies – just like in Fusion 360. This walkthrough builds a simple block.",
   "In MyCAD zeichnest du eine flache Skizze und machst aus ihren geschlossenen Flächen feste Körper – genau wie in Fusion 360. Diese Anleitung baut einen einfachen Block."),
  [("On the start page click the blue New Design button in the left panel. (Already in a design? In the toolbar at the top, FILE section, click New.)",
    "Klicke auf der Startseite im linken Panel auf den blauen Knopf Neues Design. (Schon in einem Design? Klicke in der Werkzeugleiste oben im Bereich DATEI auf Neu.)"),
   ("The screen now shows: the browser on the left (everything in the design), the toolbar at the top, the window buttons and the view cube at the top right, and the timeline at the bottom.",
    "Du siehst jetzt: links den Browser (alles im Design), oben die Werkzeugleiste, oben rechts die Fensterknöpfe und den ViewCube und unten die Zeitleiste."),
   tool("CREATE", ("Sketch", "Skizze")),
   ("Three planes appear in the view. Click the flat one lying on the floor (XY). The view turns so you look straight onto it and the sketch toolbar appears.",
    "In der Ansicht erscheinen drei Ebenen. Klicke die flach liegende Bodenebene (XY) an. Die Ansicht dreht sich, sodass du direkt darauf schaust, und die Skizzen-Werkzeugleiste erscheint."),
   tool("CREATE", ("Rectangle", "Rechteck"), sketch=True),
   ("Click once for the first corner, move the mouse and click again for the opposite corner. You can also type width and height into the small fields next to the cursor and press Enter.",
    "Klicke einmal für die erste Ecke, bewege die Maus und klicke erneut für die gegenüberliegende Ecke. Du kannst Breite und Höhe auch in die kleinen Felder neben dem Cursor tippen und Enter drücken."),
   ("Press Esc to put the rectangle tool away, then click the blue Finish Sketch button at the right end of the sketch toolbar.",
    "Drücke Esc, um das Rechteck-Werkzeug wegzulegen, und klicke dann ganz rechts in der Skizzen-Werkzeugleiste auf den blauen Knopf Skizze fertig stellen."),
   PROFILE,
   tool("CREATE", ("Extrude", "Extrudieren")),
   ("Drag the blue arrow upwards, or type a value into Distance in the panel on the right, e.g. 20 mm.",
    "Ziehe den blauen Pfeil nach oben oder tippe im Panel rechts bei Abstand einen Wert ein, z. B. 20 mm."),
   OK,
   ("Save with Ctrl+S (or FILE → Save). The first time you choose a name; designs in your projects folder appear on the start page.",
    "Speichere mit Strg+S (oder DATEI → Speichern). Beim ersten Mal wählst du einen Namen; Designs im Projektordner erscheinen auf der Startseite.")],
  tips=[EDIT_LATER,
        ("Hold the mouse over any tool for its name, and press F1 to open its help page.",
         "Halte die Maus über ein Werkzeug, um seinen Namen zu sehen, und drücke F1 für seine Hilfeseite."),
        ("Settings (gear button at the top right) can show the tool names under the icons: Show tool names.",
         "In den Einstellungen (Zahnrad oben rechts) kannst du die Namen unter den Symbolen einblenden: Werkzeugnamen anzeigen.")],
  see=["Design_CreateSketch", "Design_Extrude", "start_navigation", "sketch_basics"])

A("start_navigation", "start", "Nav_Rotate", ("Moving around", "Navigation"),
  (["navigate", "rotate view", "orbit", "pan", "zoom", "mouse", "trackpad", "view cube", "look from top"],
   ["navigieren", "Ansicht drehen", "Orbit", "verschieben", "zoomen", "Maus", "Trackpad", "ViewCube", "von oben ansehen"]),
  ("Rotate, pan and zoom the view with mouse, trackpad or keys. Which buttons do what depends on the navigation style in Settings; the default is Fusion 360.",
   "Drehen, verschieben und zoomen mit Maus, Trackpad oder Tasten. Welche Taste was macht, hängt vom Navigationsstil in den Einstellungen ab; Standard ist Fusion 360."),
  [("Rotate (Fusion 360 style): hold Shift and drag with the middle mouse button (the pressed scroll wheel).",
    "Drehen (Stil Fusion 360): Umschalt gedrückt halten und mit der mittleren Maustaste (dem gedrückten Mausrad) ziehen."),
   ("Pan: drag with the middle mouse button.", "Verschieben: mit der mittleren Maustaste ziehen."),
   ("Zoom: turn the scroll wheel; it zooms towards the cursor. On a trackpad, scroll with two fingers.",
    "Zoomen: Mausrad drehen; es zoomt zum Cursor hin. Auf dem Trackpad mit zwei Fingern scrollen."),
   ("View cube (top right, below the window buttons): click a face such as TOP or FRONT to look from that side, or a corner for an angled view. The small house below it shows the whole model.",
    "ViewCube (oben rechts, unter den Fensterknöpfen): Klicke eine Seite wie OBEN oder VORNE an, um von dort zu schauen, oder eine Ecke für eine Schrägansicht. Das kleine Haus darunter zeigt das ganze Modell."),
   ("Lost the model? INSPECT → Fit All (keys V, F) zooms so everything fits.",
    "Modell verloren? PRÜFEN → Alles zeigen (Tasten V, F) zoomt so, dass alles hineinpasst."),
   ("To see the exact buttons of your style: open Settings (gear button at the top right) → Navigation; the box below Style lists Rotate, Pan, Zoom and Select.",
    "Die genauen Tasten deines Stils: Einstellungen öffnen (Zahnrad oben rechts) → Navigation; der Kasten unter Stil zeigt Drehen, Verschieben, Zoomen und Auswählen.")],
  tips=[("On a laptop, Settings → Keys can turn a key such as Space into the middle mouse button.",
         "Am Laptop machst du unter Einstellungen → Tasten eine Taste wie die Leertaste zur mittleren Maustaste."),
        ("The view turns around the body under the cursor (Settings → Rotate around), so the detail you look at stays in place.",
         "Die Ansicht dreht um den Körper unter dem Cursor (Einstellungen → Drehen um), so bleibt das betrachtete Detail an seinem Platz."),
        ("Zoom in the wrong direction? Settings → Speed & Zoom → Invert zoom (mouse wheel) or Invert zoom (trackpad).",
         "Zoom in die falsche Richtung? Einstellungen → Tempo & Zoom → Zoom umkehren (Mausrad) oder Zoom umkehren (Trackpad).")],
  see=["settings", "Std_ViewFitAll"])

A("sketch_basics", "start", "Design_CreateSketch", ("Sketching basics", "Skizzen-Grundlagen"),
  (["sketch", "profile", "closed area", "constraint", "colors", "blue", "black", "construction", "fully defined"],
   ["Skizze", "Profil", "geschlossene Fläche", "Abhängigkeit", "Farben", "blau", "schwarz", "Konstruktion", "voll bestimmt"]),
  ("A sketch is a flat drawing on a plane. Every closed area of it becomes a profile that Extrude, Revolve and other tools turn into bodies.",
   "Eine Skizze ist eine flache Zeichnung auf einer Ebene. Jede geschlossene Fläche darin wird ein Profil, aus dem Extrudieren, Drehen und andere Werkzeuge Körper machen."),
  [("Start a sketch: toolbar at the top → CREATE → Sketch, then click a plane or a flat face of a body.",
    "Skizze beginnen: Werkzeugleiste oben → ERSTELLEN → Skizze, dann eine Ebene oder eine flache Körperfläche anklicken."),
   ("While sketching, the toolbar shows the sketch tools in three sections: CREATE (shapes), MODIFY (change shapes) and CONSTRAINTS (dimensions and rules). The Sketch Palette on the right holds Look At, Slice, Grid, Snap and Construction.",
    "Beim Skizzieren zeigt die Werkzeugleiste die Skizzenwerkzeuge in drei Bereichen: ERSTELLEN (Formen), ÄNDERN (Formen bearbeiten) und ABHÄNGIGKEITEN (Maße und Regeln). Die Skizzenpalette rechts enthält Senkrecht ansehen, Schnittansicht, Raster, Fangen und Konstruktion."),
   ("Draw shapes; ends and corners snap onto existing points and lines. Many tools show small input fields next to the cursor – type a value and press Tab to go to the next field, Enter to confirm.",
    "Zeichne Formen; Enden und Ecken rasten an vorhandenen Punkten und Linien ein. Viele Werkzeuge zeigen kleine Eingabefelder neben dem Cursor – Wert eintippen, mit Tab zum nächsten Feld, Enter bestätigt."),
   ("Add sizes with Dimension and rules with the constraint tools until all lines turn black (fully defined).",
    "Lege Maße mit Bemaßung und Regeln mit den Abhängigkeiten fest, bis alle Linien schwarz sind (voll bestimmt)."),
   ("Esc puts the current tool away; a second Esc (or the blue Finish Sketch button) leaves the sketch.",
    "Esc legt das aktuelle Werkzeug weg; ein zweites Esc (oder der blaue Knopf Skizze fertig stellen) verlässt die Skizze."),
   PROFILE],
  options=[("Blue lines", "Not fully defined yet: they can still move when you drag them.", "Blaue Linien", "Noch nicht voll bestimmt: sie lassen sich noch ziehen."),
           ("Black lines", "Fully defined by dimensions and constraints.", "Schwarze Linien", "Voll bestimmt durch Bemaßungen und Abhängigkeiten."),
           ("Orange dashed lines", "Construction geometry: helps drawing, never part of a profile.", "Orange gestrichelte Linien", "Konstruktionsgeometrie: hilft beim Zeichnen, gehört nie zu einem Profil."),
           ("Purple lines", "Edges projected from the model (Project).", "Lila Linien", "Aus dem Modell projizierte Kanten (Projizieren).")],
  tips=[("Two circles inside each other give two profiles: the ring and the inner disc. Click only the ring before Extrude to get a tube.",
         "Zwei Kreise ineinander ergeben zwei Profile: den Ring und die innere Scheibe. Klicke vor Extrudieren nur den Ring an, dann wird es ein Rohr."),
        ("No orange area after finishing? The outline is not closed – usually one corner is missing a Coincident constraint.",
         "Keine orange Fläche nach dem Beenden? Der Umriss ist nicht geschlossen – meist fehlt an einer Ecke Koinzident."),
        ("To change a sketch later, double-click it in the timeline at the bottom or in the browser on the left.",
         "Eine Skizze änderst du später per Doppelklick in der Zeitleiste unten oder im Browser links.")],
  see=["Design_CreateSketch", "sketch_dimension", "sketch_construction", "sketch_finish"])

A("start_timeline", "start", "Design_Parameters", ("Timeline and changes", "Zeitleiste und Änderungen"),
  (["timeline", "history", "edit", "roll back", "suppress", "undo", "change later", "error", "red"],
   ["Zeitleiste", "Verlauf", "bearbeiten", "zurücksetzen", "unterdrücken", "rückgängig", "später ändern", "Fehler", "rot"]),
  ("Every sketch and tool you use is a step in the timeline at the bottom of the window. Change a step and everything after it updates.",
   "Jede Skizze und jedes benutzte Werkzeug ist ein Schritt in der Zeitleiste unten im Fenster. Änderst du einen Schritt, passt sich alles danach an."),
  [("Find the timeline at the bottom centre: one small icon per step, in the order you made them.",
    "Die Zeitleiste findest du unten in der Mitte: ein kleines Symbol pro Schritt, in der Reihenfolge, in der du sie gemacht hast."),
   ("Double-click a step to open its panel again; change values and click OK.",
    "Doppelklick auf einen Schritt öffnet sein Panel wieder; Werte ändern und OK klicken."),
   ("Right-click a step for Edit, Roll Back to Here, Suppress/Unsuppress and Delete.",
    "Rechtsklick auf einen Schritt bietet Bearbeiten, Bis hierher zurücksetzen, Unterdrücken/Unterdrückung aufheben und Löschen."),
   ("Roll Back to Here shows the design as it was at that step; new steps are inserted there. Use the arrows at the left of the timeline to move the marker again.",
    "Bis hierher zurücksetzen zeigt das Design so, wie es bei diesem Schritt war; neue Schritte werden dort eingefügt. Mit den Pfeilen links in der Zeitleiste verschiebst du die Markierung wieder.")],
  tips=[("A red step has a problem; hold the mouse over it to read why.", "Ein roter Schritt hat ein Problem; halte die Maus darüber, um den Grund zu lesen."),
        ("Suppress switches a step off without deleting it.", "Unterdrücken schaltet einen Schritt aus, ohne ihn zu löschen."),
        ("Undo (Ctrl+Z) reverses the last action, also deleting.", "Rückgängig (Strg+Z) nimmt die letzte Aktion zurück, auch Löschen.")],
  see=["Design_Parameters", "Design_Delete"])

# --- Datei ---------------------------------------------------------------------------------------------------------
A("file_basics", "file", "Std_Save", ("Designs and files", "Designs und Dateien"),
  (["new", "open", "save", "save as", "undo", "redo", "file", "start page", "projects folder", "rename", "close", "delete design"],
   ["neu", "öffnen", "speichern", "speichern unter", "rückgängig", "wiederherstellen", "Datei", "Startseite", "Projektordner", "umbenennen", "schließen", "Design löschen"]),
  ("Create, open and save designs and undo changes. The buttons are in the FILE section at the left end of the toolbar.",
   "Designs anlegen, öffnen und speichern und Änderungen rückgängig machen. Die Knöpfe liegen im Bereich DATEI ganz links in der Werkzeugleiste."),
  [("New (Ctrl+N) creates an empty design. Open (Ctrl+O) loads a design file. Save (Ctrl+S) stores it; the first time you choose name and folder.",
    "Neu (Strg+N) legt ein leeres Design an. Öffnen (Strg+O) lädt eine Design-Datei. Speichern (Strg+S) sichert es; beim ersten Mal wählst du Name und Ordner."),
   ("Undo (Ctrl+Z) and Redo (Ctrl+Shift+Z) step backwards and forwards through your changes.",
    "Rückgängig (Strg+Z) und Wiederherstellen (Strg+Umschalt+Z) gehen in deinen Änderungen zurück und vor."),
   ("The house button in the window buttons at the top right opens the start page: recent designs and your projects folder, with search. The arrow at the front of the same group brings you back to the design.",
    "Der Haus-Knopf bei den Fensterknöpfen oben rechts öffnet die Startseite: zuletzt verwendete Designs und dein Projektordner, mit Suche. Der Pfeil vorne in derselben Gruppe bringt dich zurück zum Design."),
   ("Right-click the design name at the top of the browser (left) for Save, Save As…, Export…, Rename, Close and Delete….",
    "Rechtsklick auf den Designnamen ganz oben im Browser (links) bietet Speichern, Speichern unter…, Exportieren…, Umbenennen, Schließen und Löschen…."),
   ("Delete… asks first. A saved file goes to the trash, so you can still get it back there.",
    "Löschen… fragt vorher nach. Eine gespeicherte Datei kommt in den Papierkorb, du holst sie dort also noch zurück.")],
  tips=[("Choose the projects folder in Settings → View → Projects folder; Save starts there.",
         "Den Projektordner wählst du in Einstellungen → Ansicht → Projektordner; Speichern beginnt dort.")],
  commands=["Std_New", "Std_Open", "Std_Save", "Std_SaveAs", "Std_Undo", "Std_Redo"], see=["Design_Export", "Design_Import"])

A("Design_Import", "file", "Design_Import", ("Insert", "Einfügen"),
  (["import", "insert", "step", "stp", "dxf", "svg", "open cad file", "drawing"], ["importieren", "einfügen", "STEP", "STP", "DXF", "SVG", "CAD-Datei öffnen", "Zeichnung"]),
  ("Brings a STEP model into the current design as bodies, or a DXF or SVG drawing as a sketch.",
   "Holt ein STEP-Modell als Körper in das aktuelle Design oder eine DXF- oder SVG-Zeichnung als Skizze."),
  [tool("FILE", ("Insert", "Einfügen")),
   ("Choose a file of type STEP (.step, .stp), DXF or SVG and click Open.", "Wähle eine Datei vom Typ STEP (.step, .stp), DXF oder SVG und klicke Öffnen."),
   ("STEP: every solid becomes a body in the Bodies folder of the browser.", "STEP: Jeder Volumenkörper wird ein Körper im Ordner Körper im Browser."),
   ("DXF and SVG: the drawing becomes a sketch on the floor plane (XY) in the Sketches folder; its closed areas are profiles right away.",
    "DXF und SVG: Die Zeichnung wird eine Skizze auf der Bodenebene (XY) im Ordner Skizzen; ihre geschlossenen Flächen sind sofort Profile.")],
  tips=[("Click a closed area of an inserted drawing and use Extrude to make a part from it.",
         "Klicke eine geschlossene Fläche einer eingefügten Zeichnung an und mache mit Extrudieren ein Teil daraus.")],
  see=["Design_Export", "Design_Extrude"])

A("Design_Export", "file", "Design_Export", ("Export", "Exportieren"),
  (["export", "3mf", "stl", "step", "3d print", "slicer", "save as stl", "save as step"], ["exportieren", "3MF", "STL", "STEP", "3D-Druck", "Slicer", "als STL speichern", "als STEP speichern"]),
  ("Saves bodies as 3MF or STL for 3D printing, or as STEP for other CAD programs.",
   "Speichert Körper als 3MF oder STL für den 3D-Druck oder als STEP für andere CAD-Programme."),
  [("Optional: select the bodies to export in the view or in the browser (Ctrl+click for several). Without a selection all visible bodies are exported.",
    "Optional: Wähle die zu exportierenden Körper in der Ansicht oder im Browser (Strg+Klick für mehrere). Ohne Auswahl werden alle sichtbaren Körper exportiert."),
   tool("FILE", ("Export", "Exportieren")),
   ("In the file dialog pick the type (3MF for 3D printing, STL, or STEP), enter a name and click Save.",
    "Wähle im Dateidialog den Typ (3MF für den 3D-Druck, STL oder STEP), gib einen Namen ein und klicke Speichern."),
   ("A message confirms how many bodies were written.", "Eine Meldung bestätigt, wie viele Körper geschrieben wurden.")],
  tips=[("3MF keeps units and is the best choice for modern slicers. STEP keeps exact curves for other CAD programs.",
         "3MF behält die Einheiten und ist für moderne Slicer die beste Wahl. STEP behält exakte Rundungen für andere CAD-Programme."),
        ("You can also right-click bodies in the browser or the design name and choose Export.",
         "Du kannst auch Körper im Browser oder den Designnamen rechts anklicken und Exportieren wählen.")],
  see=["Design_Import"])

# --- Erstellen -----------------------------------------------------------------------------------------------------
A("Design_CreateSketch", "create", "Design_CreateSketch", ("Create Sketch", "Skizze erstellen"),
  (["sketch", "draw", "2d", "plane", "face", "drawing plane"], ["Skizze", "zeichnen", "2D", "Ebene", "Fläche", "Zeichenebene"]),
  ("Starts a new sketch on an origin plane, a construction plane or a flat face of a body.",
   "Beginnt eine neue Skizze auf einer Ursprungsebene, einer Konstruktionsebene oder einer flachen Körperfläche."),
  [("In the toolbar at the top, in the CREATE section, click Sketch (key S).", "Klicke in der Werkzeugleiste oben im Bereich ERSTELLEN auf Skizze (Taste S)."),
   ("The three origin planes appear. Click one of them – XY is the floor, XZ the front, YZ the side – or click a flat face of a body.",
    "Die drei Ursprungsebenen erscheinen. Klicke eine davon an – XY ist der Boden, XZ die Vorderseite, YZ die Seite – oder eine flache Körperfläche."),
   ("The view turns to look straight at the plane and the toolbar switches to the sketch tools (CREATE, MODIFY, CONSTRAINTS).",
    "Die Ansicht dreht sich direkt auf die Ebene, und die Werkzeugleiste zeigt die Skizzenwerkzeuge (ERSTELLEN, ÄNDERN, ABHÄNGIGKEITEN)."),
   ("Draw your shapes, then click the blue Finish Sketch button at the right end of the toolbar (or press Esc twice).",
    "Zeichne deine Formen und klicke dann ganz rechts in der Werkzeugleiste auf den blauen Knopf Skizze fertig stellen (oder zweimal Esc).")],
  tips=[("Already selected a plane or face before clicking Sketch? Then the sketch starts on it immediately.",
         "Hast du vor dem Klick auf Skizze schon eine Ebene oder Fläche ausgewählt, beginnt die Skizze sofort darauf."),
        ("A sketch on a body face joins its profiles to that body by default when you extrude them.",
         "Eine Skizze auf einer Körperfläche verbindet ihre Profile beim Extrudieren standardmäßig mit diesem Körper."),
        ("To change a sketch later, double-click it in the timeline or in the Sketches folder of the browser.",
         "Eine Skizze änderst du später per Doppelklick in der Zeitleiste oder im Ordner Skizzen im Browser."),
        ("Need a plane at another height or angle? See Offset Plane and Plane at Angle.",
         "Eine Ebene auf anderer Höhe oder schräg? Siehe Versetzte Ebene und Ebene im Winkel.")],
  see=["sketch_basics", "Design_Extrude", "Design_OffsetPlane"])

A("Design_Extrude", "create", "Design_Extrude", ("Extrude", "Extrudieren"),
  (["extrude", "pull", "solid", "thickness", "block", "plate", "tube", "cut hole", "pocket"],
   ["extrudieren", "ziehen", "Volumen", "Dicke", "Block", "Platte", "Rohr", "Loch schneiden", "Tasche"]),
  ("Pulls closed areas of a sketch straight out into a body – or cuts them into one.",
   "Zieht geschlossene Flächen einer Skizze gerade heraus zu einem Körper – oder schneidet sie in einen hinein."),
  [PROFILE, ("Select one or more profiles (Ctrl+click for several).", "Wähle ein oder mehrere Profile (Strg+Klick für mehrere)."),
   ("In the toolbar at the top, in the CREATE section, click Extrude (key E).", "Klicke in der Werkzeugleiste oben im Bereich ERSTELLEN auf Extrudieren (Taste E)."),
   PANEL,
   ("Drag the blue arrow in the view, or type the length into Distance.", "Ziehe den blauen Pfeil in der Ansicht oder tippe die Länge bei Abstand ein."),
   ("Choose Direction and Operation if needed (see Options).", "Wähle bei Bedarf Richtung und Vorgang (siehe Optionen)."), OK],
  options=[("Direction", "One Side, Symmetric (half to each side) or Two Sides (Distance and Distance 2).",
            "Richtung", "Eine Seite, Symmetrisch (je zur Hälfte nach beiden Seiten) oder Zwei Seiten (Abstand und Abstand 2)."),
           ("Distance", "How far the profile is pulled; a negative value goes the other way.", "Abstand", "Wie weit das Profil gezogen wird; ein negativer Wert geht in die andere Richtung."),
           FLIP, OPERATION],
  tips=[("Two circles inside each other: click only the ring to get a tube instead of a solid cylinder.",
         "Zwei Kreise ineinander: Klicke nur den Ring an, dann entsteht ein Rohr statt eines vollen Zylinders."),
        ("To cut a pocket: sketch on the body face, extrude into the body and set Operation to Cut.",
         "Für eine Tasche: auf der Körperfläche skizzieren, in den Körper hinein extrudieren und Vorgang auf Ausschneiden stellen."),
        FORMULA, EDIT_LATER],
  see=["Design_Revolve", "Design_PressPull", "sketch_basics"])

A("Design_Revolve", "create", "Design_Revolve", ("Revolve", "Drehen"),
  (["revolve", "donut", "turned part", "lathe", "rotate profile", "axis", "torus", "ring", "vase", "shaft"],
   ["drehen", "Donut", "Drehteil", "Drehbank", "Profil rotieren", "Achse", "Torus", "Ring", "Vase", "Welle"]),
  ("Spins a cross-section around an axis – for donuts, rings, shafts, vases and every turned part.",
   "Dreht einen Querschnitt um eine Achse – für Donuts, Ringe, Wellen, Vasen und jedes Drehteil."),
  [("Create a sketch on an upright plane, e.g. XZ (CREATE → Sketch, then click the front plane).",
    "Erstelle eine Skizze auf einer stehenden Ebene, z. B. XZ (ERSTELLEN → Skizze, dann die vordere Ebene anklicken)."),
   ("Draw the cross-section beside the axis it should turn around – for a donut a circle 30 mm to the right of the origin. Click Finish Sketch.",
    "Zeichne den Querschnitt neben die Achse, um die er sich drehen soll – für einen Donut einen Kreis 30 mm rechts vom Ursprung. Klicke Skizze fertig stellen."),
   ("Click the orange profile so it turns blue.", "Klicke das orange Profil an, damit es blau wird."),
   tool("CREATE", ("Revolve", "Drehen")), PANEL,
   ("MyCAD already picks an axis that does not cut through the profile. Choose another one under Axis if needed and set the Angle (360° = full turn).",
    "MyCAD wählt schon eine Achse, die das Profil nicht schneidet. Wähle bei Bedarf unter Achse eine andere und stelle den Winkel ein (360° = volle Umdrehung)."),
   OK],
  options=[("Axis", "Sketch X axis, Sketch Y axis (the axes of the sketch) or the origin axes X axis, Y axis, Z axis.",
            "Achse", "Skizze X-Achse, Skizze Y-Achse (die Achsen der Skizze) oder die Ursprungsachsen X-Achse, Y-Achse, Z-Achse."),
           ("Angle", "360° for a full turn, less for part of it.", "Winkel", "360° für eine volle Umdrehung, weniger für einen Teil davon."),
           FLIP, OPERATION],
  tips=[("The axis must not run through the profile, otherwise MyCAD says so in red in the panel.",
         "Die Achse darf nicht durch das Profil laufen, sonst meldet MyCAD das rot im Panel."),
        ("A half circle touching the axis gives a sphere; a rectangle touching it gives a cylinder.",
         "Ein Halbkreis an der Achse ergibt eine Kugel, ein Rechteck an der Achse einen Zylinder."), EDIT_LATER],
  caption=("A circle beside the axis becomes a donut.", "Ein Kreis neben der Achse wird zum Donut."),
  see=["Design_Extrude", "Design_Sweep"])

A("Design_Sweep", "create", "Design_Sweep", ("Sweep", "Sweep"),
  (["sweep", "path", "pipe", "tube", "rail", "handle", "bent", "hose"], ["Sweep", "Pfad", "Rohr", "Schlauch", "Bahn", "Griff", "gebogen"]),
  ("Moves a profile along a path – for pipes, handles, cables and bent shapes.", "Führt ein Profil an einem Pfad entlang – für Rohre, Griffe, Kabel und gebogene Formen."),
  [("Sketch the profile (e.g. a circle) and finish the sketch.", "Skizziere das Profil (z. B. einen Kreis) und beende die Skizze."),
   ("Sketch the path in a second sketch on another plane: connected lines and arcs that start at the profile.",
    "Skizziere den Pfad in einer zweiten Skizze auf einer anderen Ebene: zusammenhängende Linien und Bögen, die am Profil beginnen."),
   ("Click the profile, then hold Ctrl and click the path lines (or edges of a body).", "Klicke das Profil an, dann mit gedrückter Strg-Taste die Pfadlinien (oder Kanten eines Körpers)."),
   tool("CREATE", ("Sweep", "Sweep"), ("Sweep", "Sweep")), PANEL,
   ("Choose the Operation and click OK at the top of the panel.", "Wähle den Vorgang und klicke oben im Panel auf OK.")],
  options=[OPERATION],
  tips=[("The path must be one connected chain and must not cross itself or turn too tightly for the profile.",
         "Der Pfad muss eine zusammenhängende Kette sein und darf sich nicht kreuzen oder für das Profil zu eng biegen.")],
  see=["Design_Loft", "Design_Revolve"])

A("Design_Loft", "create", "Design_Loft", ("Loft", "Erhebung"),
  (["loft", "blend", "transition", "morph", "funnel", "square to circle"], ["Erhebung", "Übergang", "überblenden", "Trichter", "Loft", "Quadrat zu Kreis"]),
  ("Builds a smooth body through two or more profiles on different planes, e.g. from a square to a circle.",
   "Baut einen glatten Körper durch zwei oder mehr Profile auf verschiedenen Ebenen, z. B. vom Quadrat zum Kreis."),
  [("Create the levels: CONSTRUCT → Offset Plane gives parallel planes at any height.", "Lege die Höhen an: KONSTRUIEREN → Versetzte Ebene ergibt parallele Ebenen in jeder Höhe."),
   ("Sketch one profile on each plane and finish each sketch.", "Skizziere auf jeder Ebene ein Profil und beende jede Skizze."),
   ("Click the profiles in order from bottom to top – Ctrl+click for the second and further.", "Klicke die Profile der Reihe nach von unten nach oben an – ab dem zweiten mit Strg+Klick."),
   tool("CREATE", ("Sweep", "Sweep"), ("Loft", "Erhebung")), PANEL, OK],
  options=[("Straight transitions", "Flat sides between the profiles instead of curved ones.", "Gerade Übergänge", "Flache Seiten zwischen den Profilen statt gewölbter."),
           ("Connect the last profile back to the first", "Closes the loft into a ring.", "Letztes Profil wieder mit dem ersten verbinden", "Schließt die Erhebung zu einem Ring."),
           OPERATION],
  see=["Design_OffsetPlane", "Design_Sweep"])

A("Design_Rib", "create", "Design_Rib", ("Rib", "Rippe"),
  (["rib", "stiffener", "support", "gusset", "brace"], ["Rippe", "Versteifung", "Stütze", "Knotenblech", "Strebe"]),
  ("Adds a thin supporting wall along sketch lines between existing walls – like the diagonal brace in an angle bracket.",
   "Fügt entlang von Skizzenlinien eine dünne Stützwand zwischen vorhandenen Wänden ein – wie die schräge Strebe in einem Winkel."),
  [("Create a sketch on a plane that cuts through the middle of the body (e.g. a Midplane).", "Erstelle eine Skizze auf einer Ebene, die mitten durch den Körper geht (z. B. eine Mittelebene)."),
   ("Draw straight lines where the ribs go; both ends of each line must touch the body. Finish the sketch.",
    "Zeichne gerade Linien, wo die Rippen hin sollen; beide Enden jeder Linie müssen den Körper berühren. Beende die Skizze."),
   ("Click the body, then Ctrl+click the rib lines (or select the whole sketch).", "Klicke den Körper an, dann mit Strg+Klick die Rippenlinien (oder die ganze Skizze)."),
   tool("CREATE", ("Sweep", "Sweep"), ("Rib", "Rippe")), PANEL,
   ("Set the Thickness and click OK at the top of the panel.", "Stelle die Dicke ein und klicke oben im Panel auf OK.")],
  options=[("Thickness", "Wall thickness of the rib, centred on the line.", "Dicke", "Wandstärke der Rippe, mittig auf der Linie.")],
  tips=[("The rib grows in the sketch plane until it meets the body. For walls perpendicular to the sketch use Web.",
         "Die Rippe wächst in der Skizzenebene, bis sie auf den Körper trifft. Für Wände senkrecht zur Skizze nimm Steg.")],
  see=["Design_Web", "Design_Shell"])

A("Design_Web", "create", "Design_Web", ("Web", "Steg"),
  (["web", "grid", "stiffeners", "honeycomb", "inner walls", "dividers", "compartments"], ["Steg", "Gitter", "Versteifungen", "Waben", "Innenwände", "Trennwände", "Fächer"]),
  ("Like Rib, but the walls grow perpendicular to the sketch – ideal for dividers or a grid of stiffeners inside a hollow part.",
   "Wie Rippe, aber die Wände wachsen senkrecht zur Skizze – ideal für Trennwände oder ein Gitter aus Versteifungen in einem hohlen Teil."),
  [("Hollow the part first, e.g. with Shell.", "Höhle das Teil zuerst aus, z. B. mit Wandstärke."),
   ("Create a sketch on the open top (or a plane above the floor) and draw straight lines from wall to wall. Lines may cross. Finish the sketch.",
    "Erstelle eine Skizze auf der offenen Oberseite (oder einer Ebene über dem Boden) und zeichne gerade Linien von Wand zu Wand. Linien dürfen sich kreuzen. Beende die Skizze."),
   ("Click the body, then Ctrl+click the lines (or select the whole sketch).", "Klicke den Körper an, dann mit Strg+Klick die Linien (oder die ganze Skizze)."),
   tool("CREATE", ("Sweep", "Sweep"), ("Web", "Steg")), PANEL,
   ("Set the Thickness and click OK at the top of the panel.", "Stelle die Dicke ein und klicke oben im Panel auf OK.")],
  options=[("Thickness", "Wall thickness of each web.", "Dicke", "Wandstärke jedes Stegs.")],
  tips=[("Each wall grows down until it meets the floor and needs walls at both ends; open ends are reported in red in the panel.",
         "Jede Wand wächst nach unten bis zum Boden und braucht an beiden Enden Wände; offene Enden meldet das Panel rot.")],
  caption=("Two crossing webs inside a shelled tray.", "Zwei sich kreuzende Stege in einer ausgehöhlten Wanne."),
  see=["Design_Rib", "Design_Shell"])

A("Design_Emboss", "create", "Design_Emboss", ("Emboss", "Prägen"),
  (["emboss", "engrave", "text", "logo", "label", "deboss", "lettering", "raised"], ["prägen", "gravieren", "Text", "Logo", "Beschriftung", "vertiefen", "Schrift", "erhaben"]),
  ("Raises (Emboss) or engraves (Deboss) sketch shapes or text on a face of a body.", "Hebt Skizzenformen oder Text auf einer Körperfläche hervor (Prägen) oder graviert sie ein (Vertiefen)."),
  [("Create a sketch on the face (or parallel to it) and draw the shapes or the text (sketch tool Text). Finish the sketch.",
    "Erstelle eine Skizze auf der Fläche (oder parallel dazu) und zeichne die Formen oder den Text (Skizzenwerkzeug Text). Beende die Skizze."),
   ("Click the profiles (Ctrl+click for several), then Ctrl+click the face of the body.", "Klicke die Profile an (Strg+Klick für mehrere), dann mit Strg+Klick die Fläche des Körpers."),
   tool("CREATE", ("Sweep", "Sweep"), ("Emboss", "Prägen")), PANEL,
   ("Choose the Type and the Depth, then click OK at the top of the panel.", "Wähle Typ und Tiefe und klicke oben im Panel auf OK.")],
  options=[("Type", "Emboss (raised) or Deboss (engraved).", "Typ", "Prägen (erhaben) oder Vertiefen (eingraviert)."),
           ("Depth", "Height of the raised shape or depth of the engraving.", "Tiefe", "Höhe der erhabenen Form oder Tiefe der Gravur.")],
  see=["sketch_text"])

A("primitives", "create", "Design_Box", ("Box, Cylinder and more", "Quader, Zylinder und mehr"),
  (["box", "cube", "cylinder", "sphere", "ball", "torus", "coil", "spring", "helix", "primitive", "basic shape"],
   ["Quader", "Würfel", "Zylinder", "Kugel", "Ball", "Torus", "Spirale", "Feder", "Helix", "Grundkörper", "Grundform"]),
  ("Creates a ready-made body without a sketch: Box, Cylinder, Sphere, Torus or Coil.", "Erstellt einen fertigen Körper ohne Skizze: Quader, Zylinder, Kugel, Torus oder Spirale."),
  [("Optional: click a plane or a flat face of a body to place the shape on it (otherwise it sits on the floor, XY).",
    "Optional: Klicke eine Ebene oder flache Körperfläche an, um die Form darauf zu setzen (sonst steht sie auf dem Boden, XY)."),
   tool("CREATE", ("Box", "Quader"), ("Box", "Quader")),
   ("Click the small arrow ▾ next to Box to choose Cylinder, Sphere, Torus or Coil instead; you can also change Type in the panel later.",
    "Über den kleinen Pfeil ▾ neben Quader wählst du stattdessen Zylinder, Kugel, Torus oder Spirale; im Panel lässt sich der Typ auch später ändern."),
   PANEL, ("Type the sizes and the position on the plane, choose the Operation.", "Tippe Größen und Position auf der Ebene ein und wähle den Vorgang."), OK],
  options=[("Type", "Box, Cylinder, Sphere, Torus or Coil.", "Typ", "Quader, Zylinder, Kugel, Torus oder Spirale."),
           ("Length, Width, Height", "Box size; Height also for Cylinder and Coil.", "Länge, Breite, Höhe", "Größe des Quaders; Höhe auch bei Zylinder und Spirale."),
           ("Radius", "Radius of Cylinder, Sphere, Torus and Coil.", "Radius", "Radius von Zylinder, Kugel, Torus und Spirale."),
           ("Tube Radius", "Thickness of Torus and Coil.", "Rohrradius", "Dicke von Torus und Spirale."),
           ("Pitch, Turns", "Height per turn and number of turns of a Coil.", "Steigung, Windungen", "Höhe pro Umdrehung und Anzahl der Windungen einer Spirale."),
           ("Position X, Position Y", "Where on the plane the shape sits.", "Position X, Position Y", "Wo auf der Ebene die Form sitzt."),
           OPERATION],
  commands=["Design_Box", "Design_Cylinder", "Design_Sphere", "Design_Torus", "Design_Coil"], see=["Design_Extrude"])

A("Design_Hole", "create", "Design_Hole", ("Hole", "Bohrung"),
  (["hole", "drill", "bore", "counterbore", "countersink", "screw", "through", "bolt hole"], ["Bohrung", "bohren", "Loch", "Senkung", "Senkkopf", "Schraube", "durchgehend", "Schraubenloch"]),
  ("Drills holes at sketch points – simple, with a cylindrical counterbore or with a conical countersink.",
   "Bohrt Löcher an Skizzenpunkten – einfach, mit zylindrischer oder mit kegeliger Senkung."),
  [("Click the face of the body where the holes start, then CREATE → Sketch.", "Klicke die Körperfläche an, an der die Bohrungen beginnen, dann ERSTELLEN → Skizze."),
   ("In the sketch toolbar, CREATE section, click Point and click once for every hole centre. Add dimensions if the positions matter. Click Finish Sketch.",
    "Klicke in der Skizzen-Werkzeugleiste im Bereich ERSTELLEN auf Punkt und klicke einmal pro Bohrungsmitte. Lege bei Bedarf Maße fest. Klicke Skizze fertig stellen."),
   ("Select that sketch (click it in the timeline or in the Sketches folder of the browser).", "Wähle diese Skizze aus (in der Zeitleiste oder im Ordner Skizzen im Browser anklicken)."),
   tool("CREATE", ("Hole", "Bohrung"), ("Hole", "Bohrung")), PANEL,
   ("Choose the Type and type Diameter and Depth (or tick Through all).", "Wähle den Typ und tippe Durchmesser und Tiefe ein (oder hake Durchgehend an)."), OK],
  options=[("Type", "Simple, Counterbore (cylindrical recess for a screw head) or Countersink (cone for a countersunk screw).",
            "Typ", "Einfach, Senkung zylindrisch (Vertiefung für einen Schraubenkopf) oder Senkung kegelig (Kegel für eine Senkkopfschraube)."),
           ("Diameter, Depth", "Size of the hole.", "Durchmesser, Tiefe", "Maße der Bohrung."),
           ("Through all", "Drills through the whole body.", "Durchgehend", "Bohrt durch den ganzen Körper."),
           ("Head diameter, Head depth", "Size of the counterbore.", "Kopfdurchmesser, Kopftiefe", "Maße der zylindrischen Senkung."),
           ("Countersink angle", "Angle of the countersink cone, e.g. 90°.", "Senkwinkel", "Winkel des Senkkegels, z. B. 90°."),
           FLIP],
  tips=[("Use Pattern on the Hole step in the timeline to repeat it in rows or around a circle.",
         "Mit Muster auf den Bohrungs-Schritt in der Zeitleiste wiederholst du sie in Reihen oder im Kreis.")],
  caption=("Three counterbored holes at three sketch points.", "Drei Bohrungen mit Senkung an drei Skizzenpunkten."),
  see=["Design_Thread", "Design_Pattern", "sketch_point"])

A("Design_Thread", "create", "Design_Thread", ("Thread", "Gewinde"),
  (["thread", "screw", "bolt", "nut", "pitch", "m8", "tapped"], ["Gewinde", "Schraube", "Bolzen", "Mutter", "Steigung", "M8", "Innengewinde"]),
  ("Cuts a real, printable thread into a cylindrical face – outside on a bolt or inside a hole.",
   "Schneidet ein echtes, druckbares Gewinde in eine zylindrische Fläche – außen an einem Bolzen oder innen in einer Bohrung."),
  [("Click the round (cylindrical) face of the bolt or of the hole.", "Klicke die runde (zylindrische) Fläche des Bolzens oder der Bohrung an."),
   tool("CREATE", ("Hole", "Bohrung"), ("Thread", "Gewinde")), PANEL,
   ("Set the Pitch and click OK at the top of the panel.", "Stelle die Steigung ein und klicke oben im Panel auf OK.")],
  options=[("Pitch", "Distance from one thread to the next, e.g. 1.25 mm for M8.", "Steigung", "Abstand von Gang zu Gang, z. B. 1,25 mm bei M8."),
           ("Left-handed thread", "Turns the other way.", "Linksgewinde", "Dreht andersherum.")],
  tips=[("The face must be long enough for at least one full turn.", "Die Fläche muss für mindestens einen vollen Gang lang genug sein.")],
  see=["Design_Hole"])

A("Design_Pattern", "create", "Design_Pattern", ("Pattern", "Muster"),
  (["pattern", "array", "repeat", "copy", "rectangular", "circular", "polar", "grid of"], ["Muster", "Anordnung", "wiederholen", "kopieren", "rechteckig", "kreisförmig", "polar", "Raster aus"]),
  ("Repeats bodies, or a feature such as an Extrude, Revolve or Hole, in rows or around an axis.",
   "Wiederholt Körper oder ein Feature wie Extrusion, Drehung oder Bohrung in Reihen oder um eine Achse."),
  [("Select what to repeat: one or more bodies, or a step (Extrude, Revolve, Hole) in the timeline at the bottom.",
    "Wähle, was wiederholt wird: einen oder mehrere Körper oder einen Schritt (Extrusion, Drehung, Bohrung) in der Zeitleiste unten."),
   tool("CREATE", ("Pattern", "Muster")), PANEL,
   ("Choose the Type. Rectangular: Direction, Count and Spacing for the first row, Direction 2, Count 2 and Spacing 2 for a second row. Circular: the axis and the total angle.",
    "Wähle den Typ. Rechteckig: Richtung, Anzahl und Abstand für die erste Reihe, Richtung 2, Anzahl 2 und Abstand 2 für eine zweite. Kreisförmig: die Achse und den Gesamtwinkel."),
   OK],
  options=[("Type", "Rectangular (rows and columns) or Circular (around an axis through the origin).", "Typ", "Rechteckig (Reihen und Spalten) oder Kreisförmig (um eine Achse durch den Ursprung)."),
           ("Direction, Count, Spacing", "Axis, number of copies (the original counts) and distance of the first row.", "Richtung, Anzahl, Abstand", "Achse, Anzahl der Kopien (das Original zählt mit) und Abstand der ersten Reihe."),
           ("Direction 2, Count 2, Spacing 2", "A second row; Count 2 = 1 means no second row.", "Richtung 2, Anzahl 2, Abstand 2", "Eine zweite Reihe; Anzahl 2 = 1 heißt keine zweite Reihe.")],
  caption=("One peg repeated 4 × 2 times.", "Ein Zapfen, 4 × 2-mal wiederholt."),
  see=["Design_Mirror", "Design_Hole", "sketch_pattern"])

A("Design_Mirror", "create", "Design_Mirror", ("Mirror", "Spiegeln"),
  (["mirror", "symmetric", "flip copy", "other side"], ["spiegeln", "symmetrisch", "gespiegelte Kopie", "andere Seite"]),
  ("Creates a mirrored copy of bodies across one of the origin planes.", "Erstellt eine gespiegelte Kopie von Körpern an einer der Ursprungsebenen."),
  [("Select one or more bodies (Ctrl+click for several).", "Wähle einen oder mehrere Körper (Strg+Klick für mehrere)."),
   tool("CREATE", ("Mirror", "Spiegeln")), PANEL,
   ("Choose the Mirror plane and click OK at the top of the panel.", "Wähle die Spiegelebene und klicke oben im Panel auf OK.")],
  options=[("Mirror plane", "XY plane, XZ plane or YZ plane through the origin.", "Spiegelebene", "XY-Ebene, XZ-Ebene oder YZ-Ebene durch den Ursprung.")],
  tips=[("Build half of a symmetric part and mirror it – changes to the half update the copy.",
         "Baue die Hälfte eines symmetrischen Teils und spiegle sie – Änderungen an der Hälfte übernimmt die Kopie.")],
  see=["Design_Pattern", "sketch_mirror"])

# --- Ändern --------------------------------------------------------------------------------------------------------
A("Design_PressPull", "modify", "Design_PressPull", ("Press Pull", "Drücken/Ziehen"),
  (["press pull", "push", "pull", "offset face", "thicker", "thinner", "move face"], ["drücken", "ziehen", "Fläche versetzen", "dicker", "dünner", "Fläche verschieben"]),
  ("Pushes or pulls flat faces of a body to make it thicker or thinner – the quickest way to change a size.",
   "Drückt oder zieht ebene Flächen eines Körpers, um ihn dicker oder dünner zu machen – der schnellste Weg, ein Maß zu ändern."),
  [("Click one or more flat faces of a body (Ctrl+click for several).", "Klicke eine oder mehrere ebene Flächen eines Körpers an (Strg+Klick für mehrere)."),
   tool("MODIFY", ("Press Pull", "Drücken/Ziehen"), ("Press Pull", "Drücken/Ziehen")), PANEL,
   ("Drag the blue arrow or type the Distance: positive pulls out, negative pushes in. Faces shows how many faces are selected.",
    "Ziehe den blauen Pfeil oder tippe den Abstand ein: positiv zieht heraus, negativ drückt hinein. Flächen zeigt, wie viele Flächen gewählt sind."),
   OK],
  options=[("Distance", "How far the faces move along their normal.", "Abstand", "Wie weit sich die Flächen senkrecht verschieben.")],
  tips=[("Key Q starts Press Pull directly.", "Die Taste Q startet Drücken/Ziehen direkt.")],
  see=["Design_Extrude", "Design_ReplaceFace"])

A("Design_ReplaceFace", "modify", "Design_ReplaceFace", ("Replace Face", "Fläche ersetzen"),
  (["replace face", "match", "flush", "level", "extend to", "up to plane"], ["Fläche ersetzen", "angleichen", "bündig", "verlängern bis", "bis zur Ebene"]),
  ("Moves faces of a body exactly onto a target plane or face – e.g. to make two parts flush.",
   "Verschiebt Flächen eines Körpers genau auf eine Zielebene oder -fläche – z. B. um zwei Teile bündig zu machen."),
  [("Click the faces to move (Ctrl+click for several).", "Klicke die zu verschiebenden Flächen an (Strg+Klick für mehrere)."),
   ("Ctrl+click the target: a plane (e.g. an Offset Plane) or a face of another body.", "Klicke mit Strg die Zielebene (z. B. eine Versetzte Ebene) oder eine Fläche eines anderen Körpers an."),
   tool("MODIFY", ("Press Pull", "Drücken/Ziehen"), ("Replace Face", "Fläche ersetzen")), PANEL, OK],
  tips=[("Works with flat faces; the target must lie across their direction, not parallel beside them.",
         "Funktioniert mit ebenen Flächen; das Ziel muss quer zu ihrer Richtung liegen, nicht parallel daneben.")],
  caption=("Left: the top face was moved up to the plane. Right: the same box before.", "Links: die Oberseite wurde bis zur Ebene verschoben. Rechts: derselbe Quader vorher."),
  see=["Design_PressPull", "Design_OffsetPlane"])

A("Design_SplitFace", "modify", "Design_SplitFace", ("Split Face", "Fläche teilen"),
  (["split face", "divide face", "partition", "two areas"], ["Fläche teilen", "Fläche aufteilen", "unterteilen", "zwei Bereiche"]),
  ("Divides faces of a body along a plane, face or sketch – e.g. to Press Pull only part of a face.",
   "Teilt Flächen eines Körpers entlang einer Ebene, Fläche oder Skizze – z. B. um nur einen Teil einer Fläche zu drücken oder zu ziehen."),
  [("Click the faces to divide.", "Klicke die zu teilenden Flächen an."),
   ("Ctrl+click the cutting tool: a plane, a face or a sketch with lines across the face.", "Klicke mit Strg das Schneidwerkzeug an: eine Ebene, eine Fläche oder eine Skizze mit Linien quer über die Fläche."),
   tool("MODIFY", ("Press Pull", "Drücken/Ziehen"), ("Split Face", "Fläche teilen")), PANEL, OK],
  see=["Design_SplitBody", "Design_PressPull"])

A("Design_Fillet", "modify", "Design_Fillet", ("Fillet", "Abrunden"),
  (["fillet", "round", "rounded edge", "radius", "smooth corner", "rounded"], ["abrunden", "Rundung", "gerundete Kante", "Radius", "weiche Ecke", "rund"]),
  ("Rounds edges of a body.", "Rundet Kanten eines Körpers ab."),
  [("Click the edges to round (Ctrl+click for several). Clicking a face rounds all of its edges.",
    "Klicke die zu rundenden Kanten an (Strg+Klick für mehrere). Ein Klick auf eine Fläche rundet alle ihre Kanten."),
   ("In the toolbar at the top, in the MODIFY section, click Fillet (key F).", "Klicke in der Werkzeugleiste oben im Bereich ÄNDERN auf Abrunden (Taste F)."),
   PANEL, ("Type the Radius. Edges shows how many edges are selected.", "Tippe den Radius ein. Kanten zeigt, wie viele Kanten gewählt sind."), OK],
  options=[("Radius", "Size of the rounding.", "Radius", "Größe der Rundung.")],
  tips=[("If it fails, try a smaller radius or round fewer edges in one step.", "Schlägt es fehl, nimm einen kleineren Radius oder runde weniger Kanten in einem Schritt."), EDIT_LATER],
  see=["Design_Chamfer", "sketch_fillet"])

A("Design_Chamfer", "modify", "Design_Chamfer", ("Chamfer", "Fase"),
  (["chamfer", "bevel", "cut corner", "edge break"], ["Fase", "abschrägen", "Ecke brechen", "Kante brechen"]),
  ("Cuts edges of a body at 45°.", "Schrägt Kanten eines Körpers unter 45° ab."),
  [("Click the edges (or a face for all its edges); Ctrl+click for several.", "Klicke die Kanten an (oder eine Fläche für alle ihre Kanten); Strg+Klick für mehrere."),
   tool("MODIFY", ("Chamfer", "Fase")), PANEL, ("Type the Distance and click OK at the top of the panel.", "Tippe den Abstand ein und klicke oben im Panel auf OK.")],
  options=[("Distance", "How far the edge is cut back on both faces.", "Abstand", "Wie weit die Kante auf beiden Flächen zurückgeschnitten wird.")],
  see=["Design_Fillet"])

A("Design_Shell", "modify", "Design_Shell", ("Shell", "Wandstärke"),
  (["shell", "hollow", "wall thickness", "box", "case", "enclosure", "container"], ["Wandstärke", "aushöhlen", "hohl", "Gehäuse", "Schale", "Box", "Behälter"]),
  ("Hollows out a body and leaves walls of the chosen thickness – for cases, boxes and containers.",
   "Höhlt einen Körper aus und lässt Wände der gewählten Dicke stehen – für Gehäuse, Boxen und Behälter."),
  [("Click the faces that should be open, e.g. the top face (Ctrl+click for several). Select the whole body instead for a closed hollow part.",
    "Klicke die Flächen an, die offen sein sollen, z. B. die Oberseite (Strg+Klick für mehrere). Für ein geschlossenes Hohlteil wähle stattdessen den ganzen Körper."),
   tool("MODIFY", ("Shell", "Wandstärke")), PANEL,
   ("Set the Thickness; Open faces shows how many faces stay open.", "Stelle die Dicke ein; Offene Flächen zeigt, wie viele Flächen offen bleiben."), OK],
  options=[("Thickness", "Wall thickness.", "Dicke", "Wandstärke."),
           ("Wall outside", "Adds the walls outside the current shape instead of inside, so the inner size stays.", "Wand außen", "Legt die Wände außen um die jetzige Form statt innen, die Innenmaße bleiben also.")],
  see=["Design_Web", "Design_Rib"])

A("Design_Draft", "modify", "Design_Draft", ("Draft", "Formschräge"),
  (["draft", "taper", "slope", "mold", "angle faces", "tilt"], ["Formschräge", "Konus", "Neigung", "Gussform", "Flächen neigen", "kippen"]),
  ("Tilts side faces by a small angle – so a part comes out of a mold or a container stacks.",
   "Neigt Seitenflächen um einen kleinen Winkel – damit ein Teil aus der Form kommt oder Behälter stapelbar sind."),
  [("Click the side faces to tilt (Ctrl+click for several).", "Klicke die zu neigenden Seitenflächen an (Strg+Klick für mehrere)."),
   tool("MODIFY", ("Draft", "Formschräge")), PANEL, ("Set the Angle and click OK at the top of the panel.", "Stelle den Winkel ein und klicke oben im Panel auf OK.")],
  options=[("Angle", "Tilt angle, e.g. 3°.", "Winkel", "Neigungswinkel, z. B. 3°."), FLIP],
  tips=[("The faces tilt around the bottom of the body; Flip direction tilts them the other way.",
         "Die Flächen neigen sich um die Unterseite des Körpers; Richtung umkehren neigt sie andersherum.")],
  see=["Design_Shell"])

A("Design_Combine", "modify", "Design_Combine", ("Combine", "Kombinieren"),
  (["combine", "boolean", "join", "union", "cut", "subtract", "intersect", "merge"], ["kombinieren", "boolesch", "verbinden", "vereinigen", "ausschneiden", "abziehen", "Schnittmenge", "zusammenführen"]),
  ("Joins bodies into one, cuts one body out of another, or keeps only where they overlap.",
   "Verbindet Körper zu einem, schneidet einen Körper aus einem anderen aus oder behält nur die Überschneidung."),
  [("Click the target body first – the one that stays and changes.", "Klicke zuerst den Zielkörper an – den, der bleibt und sich ändert."),
   ("Ctrl+click one or more tool bodies.", "Klicke mit Strg einen oder mehrere Werkzeugkörper an."),
   tool("MODIFY", ("Combine", "Kombinieren"), ("Combine", "Kombinieren")), PANEL,
   ("Choose the Operation and click OK at the top of the panel. Tools shows how many tool bodies are used.",
    "Wähle den Vorgang und klicke oben im Panel auf OK. Werkzeuge zeigt, wie viele Werkzeugkörper benutzt werden.")],
  options=[("Operation", "Join, Cut or Intersect.", "Vorgang", "Verbinden, Ausschneiden oder Schnittmenge."),
           ("Keep tools", "Keeps the tool bodies visible instead of using them up.", "Werkzeuge behalten", "Lässt die Werkzeugkörper sichtbar, statt sie zu verbrauchen.")],
  see=["Design_SplitBody"])

A("Design_SplitBody", "modify", "Design_SplitBody", ("Split Body", "Körper teilen"),
  (["split body", "cut in half", "divide", "separate", "two parts"], ["Körper teilen", "halbieren", "trennen", "zerteilen", "zwei Teile"]),
  ("Cuts a body into separate pieces along a plane or face.", "Schneidet einen Körper entlang einer Ebene oder Fläche in einzelne Stücke."),
  [("Click the body, then Ctrl+click the plane or face to split with.", "Klicke den Körper an, dann mit Strg die Ebene oder Fläche, mit der geteilt wird."),
   tool("MODIFY", ("Combine", "Kombinieren"), ("Split Body", "Körper teilen")), PANEL, OK],
  tips=[("The plane or face must cut all the way through the body. Create a suitable plane with CONSTRUCT → Offset Plane.",
         "Die Ebene oder Fläche muss den Körper ganz durchschneiden. Eine passende Ebene legst du mit KONSTRUIEREN → Versetzte Ebene an.")],
  see=["Design_SplitFace", "Design_Combine"])

A("Design_Move", "modify", "Design_Move", ("Move", "Verschieben"),
  (["move", "rotate", "translate", "position", "turn body", "shift"], ["verschieben", "drehen", "bewegen", "positionieren", "Körper drehen", "versetzen"]),
  ("Moves and rotates bodies by exact distances and angles.", "Verschiebt und dreht Körper um genaue Abstände und Winkel."),
  [("Select one or more bodies (Ctrl+click for several).", "Wähle einen oder mehrere Körper (Strg+Klick für mehrere)."),
   ("In the toolbar at the top, in the MODIFY section, click Move (key M). (If the button shows Align or Scale, use the small arrow ▾ next to it.)",
    "Klicke in der Werkzeugleiste oben im Bereich ÄNDERN auf Verschieben (Taste M). (Zeigt der Knopf Ausrichten oder Skalieren, nimm den kleinen Pfeil ▾ daneben.)"),
   PANEL, ("Type X distance, Y distance and Z distance, and if needed choose Rotate around and an Angle.", "Tippe X-Abstand, Y-Abstand und Z-Abstand ein und wähle bei Bedarf Drehen um und einen Winkel."), OK],
  options=[("X distance, Y distance, Z distance", "How far to move along each axis.", "X-Abstand, Y-Abstand, Z-Abstand", "Wie weit entlang jeder Achse verschoben wird."),
           ("Rotate around, Angle", "Axis through the body centre and the rotation angle.", "Drehen um, Winkel", "Achse durch die Körpermitte und der Drehwinkel.")],
  tips=[("To place one part exactly on another, Align is quicker.", "Um ein Teil genau an ein anderes zu setzen, ist Ausrichten schneller.")],
  see=["Design_Align", "Design_Joint"])

A("Design_Align", "modify", "Design_Align", ("Align", "Ausrichten"),
  (["align", "snap", "place on", "put together", "stack"], ["ausrichten", "andocken", "aufsetzen", "zusammensetzen", "stapeln"]),
  ("Moves a body so that one of its faces, edges or points lands exactly on a target.",
   "Verschiebt einen Körper so, dass eine seiner Flächen, Kanten oder Punkte genau auf einem Ziel landet."),
  [("Click a face, edge or point of the body you want to move.", "Klicke eine Fläche, Kante oder einen Punkt des Körpers an, den du bewegen willst."),
   ("Ctrl+click the target: a face, edge, point or plane.", "Klicke mit Strg das Ziel an: eine Fläche, Kante, einen Punkt oder eine Ebene."),
   tool("MODIFY", ("Move", "Verschieben"), ("Align", "Ausrichten")),
   ("The body jumps into place and the Move panel opens on the right: fine-tune with X/Y/Z distance and an Angle if needed.",
    "Der Körper springt an seinen Platz, und rechts öffnet sich das Panel von Verschieben: dort justierst du bei Bedarf mit X-/Y-/Z-Abstand und Winkel nach."),
   OK],
  see=["Design_Move", "Design_Joint"])

A("Design_Scale", "modify", "Design_Scale", ("Scale", "Skalieren"),
  (["scale", "resize", "bigger", "smaller", "factor", "enlarge"], ["skalieren", "Größe ändern", "größer", "kleiner", "Faktor", "vergrößern"]),
  ("Makes bodies bigger or smaller by a factor.", "Macht Körper um einen Faktor größer oder kleiner."),
  [("Select one or more bodies.", "Wähle einen oder mehrere Körper."),
   tool("MODIFY", ("Move", "Verschieben"), ("Scale", "Skalieren")), PANEL,
   ("Type the Factor (2 = double size, 0.5 = half) and choose the centre, then click OK.", "Tippe den Faktor ein (2 = doppelt so groß, 0,5 = halb so groß), wähle die Mitte und klicke OK.")],
  options=[("Factor", "Size multiplier.", "Faktor", "Vergrößerungsfaktor."),
           ("Center", "Scale around the Origin or the Body center.", "Mitte", "Um den Ursprung oder die Körpermitte skalieren.")],
  see=["Design_Move"])

A("Design_Delete", "modify", "Design_Box", ("Delete", "Löschen"),
  (["delete", "remove", "erase"], ["löschen", "entfernen"]),
  ("Removes features, sketches or bodies from the design.", "Entfernt Features, Skizzen oder Körper aus dem Design."),
  [("Select what to remove: in the view, in the browser on the left, or a step in the timeline.", "Wähle aus, was weg soll: in der Ansicht, im Browser links oder als Schritt in der Zeitleiste."),
   ("Press the Del key, or right-click and choose Delete.", "Drücke die Taste Entf oder klicke rechts und wähle Löschen.")],
  tips=[("Undo (Ctrl+Z) brings it back.", "Rückgängig (Strg+Z) holt es zurück.")], see=["start_timeline"])

# --- Konstruieren ---------------------------------------------------------------------------------------------------
CONSTRUCT_TIP = ("Construction planes, axes and points appear in the Construction folder of the browser and can be used like the origin planes – e.g. to sketch on.",
                 "Konstruktionsebenen, -achsen und -punkte erscheinen im Ordner Konstruktion im Browser und lassen sich wie die Ursprungsebenen nutzen – z. B. zum Skizzieren.")
A("Design_OffsetPlane", "construct", "Design_OffsetPlane", ("Offset Plane", "Versetzte Ebene"),
  (["offset plane", "parallel plane", "work plane", "construction plane", "plane at height"], ["versetzte Ebene", "parallele Ebene", "Arbeitsebene", "Konstruktionsebene", "Ebene in Höhe"]),
  ("Creates a plane parallel to a plane or flat face, at a distance – e.g. to sketch at another height.",
   "Erstellt eine Ebene parallel zu einer Ebene oder flachen Fläche, im Abstand – z. B. um auf anderer Höhe zu skizzieren."),
  [("Click a plane or a flat face of a body.", "Klicke eine Ebene oder eine flache Körperfläche an."),
   tool("CONSTRUCT", ("Offset Plane", "Versetzte Ebene"), ("Offset Plane", "Versetzte Ebene")), PANEL,
   ("Type the Distance (negative = other side) and click OK at the top of the panel.", "Tippe den Abstand ein (negativ = andere Seite) und klicke oben im Panel auf OK.")],
  tips=[CONSTRUCT_TIP], see=["Design_Loft", "Design_AnglePlane", "Design_CreateSketch"])

A("Design_AnglePlane", "construct", "Design_AnglePlane", ("Plane at Angle", "Ebene im Winkel"),
  (["plane at angle", "tilted plane", "rotated plane", "slanted"], ["Ebene im Winkel", "geneigte Ebene", "gedrehte Ebene", "schräg"]),
  ("Creates a plane through a straight edge or axis, tilted by an angle.", "Erstellt eine Ebene durch eine gerade Kante oder Achse, um einen Winkel geneigt."),
  [("Click a straight edge, a sketch line or an axis. Optionally Ctrl+click the plane or face the angle is measured from.",
    "Klicke eine gerade Kante, eine Skizzenlinie oder eine Achse an. Optional mit Strg die Ebene oder Fläche, von der aus der Winkel gemessen wird."),
   tool("CONSTRUCT", ("Offset Plane", "Versetzte Ebene"), ("Plane at Angle", "Ebene im Winkel")), PANEL,
   ("Type the Angle and click OK at the top of the panel.", "Tippe den Winkel ein und klicke oben im Panel auf OK.")],
  tips=[CONSTRUCT_TIP], see=["Design_OffsetPlane", "Design_Axis"])

A("Design_Midplane", "construct", "Design_Midplane", ("Midplane", "Mittelebene"),
  (["midplane", "middle", "center plane", "symmetry plane", "half way"], ["Mittelebene", "Mitte", "mittige Ebene", "Symmetrieebene", "auf halbem Weg"]),
  ("Creates a plane exactly halfway between two parallel planes or faces.", "Erstellt eine Ebene genau in der Mitte zwischen zwei parallelen Ebenen oder Flächen."),
  [("Click two parallel planes or flat faces (Ctrl+click the second), e.g. the two outer sides of a body.",
    "Klicke zwei parallele Ebenen oder flache Flächen an (die zweite mit Strg), z. B. die beiden Außenseiten eines Körpers."),
   tool("CONSTRUCT", ("Offset Plane", "Versetzte Ebene"), ("Midplane", "Mittelebene")),
   ("The plane appears immediately.", "Die Ebene erscheint sofort.")],
  tips=[CONSTRUCT_TIP], see=["Design_Mirror", "Design_Rib"])

A("Design_Plane", "construct", "Design_Plane", ("Plane", "Ebene"),
  (["plane", "three points", "work plane", "through points"], ["Ebene", "drei Punkte", "Arbeitsebene", "durch Punkte"]),
  ("Creates a plane through three points, through a face and a point, or through an edge and a point.",
   "Erstellt eine Ebene durch drei Punkte, durch eine Fläche und einen Punkt oder durch eine Kante und einen Punkt."),
  [("Select the references (Ctrl+click for each further one): three corner points, a face and a point, or an edge and a point.",
    "Wähle die Bezüge (jeden weiteren mit Strg+Klick): drei Eckpunkte, eine Fläche und einen Punkt oder eine Kante und einen Punkt."),
   tool("CONSTRUCT", ("Offset Plane", "Versetzte Ebene"), ("Plane", "Ebene")),
   ("The plane appears immediately. If the selection does not define a plane, a message says what is missing.",
    "Die Ebene erscheint sofort. Ergibt die Auswahl keine Ebene, sagt eine Meldung, was fehlt.")],
  tips=[CONSTRUCT_TIP], see=["Design_OffsetPlane"])

A("Design_Axis", "construct", "Design_Axis", ("Axis", "Achse"),
  (["axis", "center line", "rotation axis", "through hole"], ["Achse", "Mittellinie", "Drehachse", "durch Bohrung"]),
  ("Creates an axis through a cylindrical face, along a straight edge, through two points or where two planes meet.",
   "Erstellt eine Achse durch eine zylindrische Fläche, entlang einer geraden Kante, durch zwei Punkte oder wo sich zwei Ebenen schneiden."),
  [("Select the reference: a round face, a straight edge, two points or two planes (Ctrl+click for the second).",
    "Wähle den Bezug: eine runde Fläche, eine gerade Kante, zwei Punkte oder zwei Ebenen (die zweite mit Strg+Klick)."),
   tool("CONSTRUCT", ("Offset Plane", "Versetzte Ebene"), ("Axis", "Achse")), ("The axis appears immediately.", "Die Achse erscheint sofort.")],
  tips=[CONSTRUCT_TIP], see=["Design_AnglePlane"])

A("Design_Point", "construct", "Design_Point", ("Point", "Punkt"),
  (["point", "construction point", "vertex", "center", "intersection"], ["Punkt", "Konstruktionspunkt", "Eckpunkt", "Mittelpunkt", "Schnittpunkt"]),
  ("Creates a construction point at a corner, at the centre of a circular edge, where an edge passes a plane, or where three planes meet.",
   "Erstellt einen Konstruktionspunkt an einer Ecke, im Mittelpunkt einer Kreiskante, wo eine Kante eine Ebene durchstößt oder wo sich drei Ebenen treffen."),
  [("Select the reference: a corner, a circular edge, an edge and a plane, or three planes (Ctrl+click for each further one).",
    "Wähle den Bezug: eine Ecke, eine Kreiskante, eine Kante und eine Ebene oder drei Ebenen (jeden weiteren mit Strg+Klick)."),
   tool("CONSTRUCT", ("Offset Plane", "Versetzte Ebene"), ("Point", "Punkt")), ("The point appears immediately.", "Der Punkt erscheint sofort.")],
  tips=[CONSTRUCT_TIP], see=["Design_Plane", "Design_Joint"])

# --- Zusammenfügen --------------------------------------------------------------------------------------------------
A("Design_NewComponent", "assemble", "Design_NewComponent", ("New Component", "Neue Komponente"),
  (["component", "part", "assembly", "sub-assembly", "activate"], ["Komponente", "Teil", "Baugruppe", "Unterbaugruppe", "aktivieren"]),
  ("Creates an empty part with its own origin. Components keep the parts of an assembly apart and can be connected with joints.",
   "Erstellt ein leeres Teil mit eigenem Ursprung. Komponenten halten die Teile einer Baugruppe auseinander und lassen sich mit Gelenken verbinden."),
  [tool("ASSEMBLE", ("Component", "Komponente")),
   ("A new component (Component1, …) appears in the browser on the left.", "Im Browser links erscheint eine neue Komponente (Komponente1, …)."),
   ("Double-click it in the browser to make it active: new sketches and bodies now go into this component.", "Doppelklicke sie im Browser, um sie zu aktivieren: neue Skizzen und Körper landen jetzt in dieser Komponente."),
   ("Double-click the active component again to switch it off; new items then go into the design itself.", "Ein weiterer Doppelklick auf die aktive Komponente schaltet sie wieder aus; Neues landet dann im Design selbst.")],
  tips=[("Extrude and the other create tools can also put a new body straight into a new component: Operation → New Component.",
         "Extrudieren und die anderen Erstellen-Werkzeuge legen einen neuen Körper auch direkt in eine neue Komponente: Vorgang → Neue Komponente.")],
  see=["Design_Joint"])

A("Design_Joint", "assemble", "Design_Joint", ("Joint", "Gelenk"),
  (["joint", "connect", "hinge", "slider", "rigid", "assembly", "mate", "assemble"], ["Gelenk", "verbinden", "Scharnier", "Schieber", "starr", "Baugruppe", "zusammenbauen", "montieren"]),
  ("Puts a component in place by connecting a snap point on it to a point on another component – rigidly or so that it can turn or slide.",
   "Setzt eine Komponente an ihren Platz, indem ein Fangpunkt an ihr mit einem Punkt an einer anderen Komponente verbunden wird – starr oder so, dass sie sich drehen oder schieben lässt."),
  [("Click a face, edge, hole or point on the component that should move.", "Klicke eine Fläche, Kante, Bohrung oder einen Punkt an der Komponente an, die sich bewegen soll."),
   ("Ctrl+click where it should go on another component.", "Klicke mit Strg an, wo sie an einer anderen Komponente hin soll."),
   ("In the toolbar at the top, in the ASSEMBLE section, click Joint (key J).", "Klicke in der Werkzeugleiste oben im Bereich ZUSAMMENFÜGEN auf Gelenk (Taste J)."),
   PANEL, ("Choose the Type and, if needed, Angle and Offset; tick Flip if it is upside down.", "Wähle den Typ und bei Bedarf Winkel und Versatz; hake Umkehren an, wenn sie verkehrt herum sitzt."), OK],
  options=[("Type", "Rigid (fixed), Revolute (can turn), Slider (can slide) or Cylindrical (turn and slide).", "Typ", "Starr (fest), Drehung (dreht sich), Schieberegler (schiebt sich) oder Zylindrisch (dreht und schiebt)."),
           ("Angle, Offset", "Rotation around and distance along the joint axis.", "Winkel, Versatz", "Drehung um und Abstand entlang der Gelenkachse."),
           ("Flip", "Turns the moving component around.", "Umkehren", "Dreht die bewegte Komponente um.")],
  tips=[("The first selection must belong to the component that moves; the design itself always stays in place.",
         "Die erste Auswahl muss zur Komponente gehören, die sich bewegt; das Design selbst bleibt immer an seinem Platz."),
        ("Joints are listed in the Joints folder of the browser; double-click one to change it.", "Gelenke stehen im Ordner Gelenke im Browser; Doppelklick ändert eines.")],
  see=["Design_NewComponent", "Design_Align"])

# --- Prüfen ---------------------------------------------------------------------------------------------------------
A("Design_Measure", "inspect", "Design_Measure", ("Measure", "Messen"),
  (["measure", "distance", "length", "angle", "area", "volume", "radius", "diameter", "size"], ["messen", "Abstand", "Länge", "Winkel", "Fläche", "Volumen", "Radius", "Durchmesser", "Größe"]),
  ("Shows lengths, distances, angles, radii, areas and volumes of what you click.", "Zeigt Längen, Abstände, Winkel, Radien, Flächen und Volumen von dem, was du anklickst."),
  [("In the toolbar at the top, in the INSPECT section, click Measure (key I). The Measure panel opens on the right.",
    "Klicke in der Werkzeugleiste oben im Bereich PRÜFEN auf Messen (Taste I). Rechts öffnet sich das Panel Messen."),
   ("Click a point, edge, face or body: the panel shows its Length, Radius, Diameter, Area, Volume or Size.",
    "Klicke einen Punkt, eine Kante, Fläche oder einen Körper an: das Panel zeigt Länge, Radius, Durchmesser, Fläche, Volumen oder Größe."),
   ("Ctrl+click a second item to see the Distance and Angle between them.", "Klicke mit Strg ein zweites an, um Abstand und Winkel dazwischen zu sehen."),
   ("Close the panel with Close at the top of the panel or Esc.", "Schließe das Panel oben mit Schließen oder mit Esc.")],
  see=["Design_Section"])

A("Design_Section", "inspect", "Design_Section", ("Section Analysis", "Schnittanalyse"),
  (["section", "cut view", "inside", "cross section", "look inside"], ["Schnitt", "Schnittansicht", "innen", "Querschnitt", "hineinschauen"]),
  ("Cuts the view open at a plane so you can look inside. The model itself is not changed.",
   "Schneidet die Ansicht an einer Ebene auf, damit du hineinschauen kannst. Das Modell selbst wird nicht verändert."),
  [("Click a plane (e.g. an origin plane) or a flat face where the view should be cut.", "Klicke eine Ebene (z. B. eine Ursprungsebene) oder eine flache Fläche an, an der die Ansicht geschnitten werden soll."),
   tool("INSPECT", ("Section", "Schnitt")),
   ("Click Section again to switch the cut off.", "Klicke noch einmal auf Schnitt, um den Schnitt auszuschalten.")],
  see=["Design_Measure"])

A("Std_ViewFitAll", "inspect", "Std_ViewFitAll", ("Fit All", "Alles zeigen"),
  (["fit", "zoom all", "show everything", "lost model", "zoom extents"], ["einpassen", "alles zoomen", "alles zeigen", "Modell verloren", "Gesamtansicht"]),
  ("Zooms so that the whole model fits the window.", "Zoomt so, dass das ganze Modell ins Fenster passt."),
  [("In the toolbar at the top, in the INSPECT section, click Fit All – or press V and then F.", "Klicke in der Werkzeugleiste oben im Bereich PRÜFEN auf Alles zeigen – oder drücke V und dann F.")],
  see=["start_navigation"])

# --- Werkzeuge ------------------------------------------------------------------------------------------------------
A("Design_Parameters", "utilities", "Design_Parameters", ("Change Parameters", "Parameter ändern"),
  (["parameters", "variables", "formula", "expression", "named value", "width", "user parameter"], ["Parameter", "Variablen", "Formel", "Ausdruck", "benannter Wert", "Breite", "Benutzerparameter"]),
  ("Defines named values such as Width = 40 mm. Use them in any number field; change the value once and every part that uses it updates.",
   "Legt benannte Werte wie Breite = 40 mm an. Du nutzt sie in jedem Zahlenfeld; änderst du den Wert einmal, passt sich alles an, was ihn verwendet."),
  [tool("UTILITIES", ("Parameters", "Parameter")),
   ("The Parameters window opens with a table of Name, Expression and Value.", "Das Fenster Parameter öffnet sich mit einer Tabelle aus Name, Ausdruck und Wert."),
   ("Type a name into Name, e.g. Width, and a value into Value, e.g. 40 mm, then click Add.", "Tippe in Name einen Namen, z. B. Breite, und in Wert einen Wert, z. B. 40 mm, dann klicke Hinzufügen."),
   ("In any number field – Distance in Extrude, a sketch Dimension – type the name or a formula such as Width * 2.", "Tippe in ein beliebiges Zahlenfeld – Abstand bei Extrudieren, eine Bemaßung in der Skizze – den Namen oder eine Formel wie Breite * 2."),
   ("Change the expression in the table later and the design updates. Remove deletes a parameter.", "Änderst du später den Ausdruck in der Tabelle, aktualisiert sich das Design. Entfernen löscht einen Parameter.")],
  tips=[("Names use letters, digits and _ only, no spaces.", "Namen bestehen nur aus Buchstaben, Ziffern und _, ohne Leerzeichen.")],
  see=["sketch_dimension", "start_timeline"])

A("Design_Appearance", "utilities", "Design_Appearance", ("Appearance", "Darstellung"),
  (["appearance", "color", "colour", "material", "paint", "look"], ["Darstellung", "Farbe", "Material", "einfärben", "Aussehen"]),
  ("Gives bodies a material look such as Steel or Brass, or a colour.", "Gibt Körpern ein Material-Aussehen wie Stahl oder Messing oder eine Farbe."),
  [("Select one or more bodies (Ctrl+click for several).", "Wähle einen oder mehrere Körper (Strg+Klick für mehrere)."),
   ("In the toolbar at the top, in the UTILITIES section, click Appearance (key A). The panel opens on the right.",
    "Klicke in der Werkzeugleiste oben im Bereich WERKZEUGE auf Darstellung (Taste A). Rechts öffnet sich das Panel."),
   ("Click a button under Material (e.g. Steel, Aluminum, Brass, Plastic) or a colour dot under Color – the bodies change right away.",
    "Klicke unter Material einen Knopf (z. B. Stahl, Aluminium, Messing, Kunststoff) oder unter Farbe einen Farbpunkt – die Körper ändern sich sofort."),
   OK],
  tips=[("The default look of new bodies is set in Settings → View → Body material.", "Das Standard-Aussehen neuer Körper stellst du in Einstellungen → Ansicht → Körpermaterial ein.")],
  see=["settings"])

A("settings", "utilities", "MyCAD_Settings", ("Settings", "Einstellungen"),
  (["settings", "preferences", "language", "german", "english", "mouse", "keys", "glass", "material", "projects folder", "zoom direction"],
   ["Einstellungen", "Optionen", "Sprache", "Deutsch", "Englisch", "Maus", "Tasten", "Glas", "Material", "Projektordner", "Zoomrichtung"]),
  ("Adjusts navigation, keys, look and language. Open it with the gear button at the top right or Ctrl+,; close it with the ✕ at the top right of the window or Esc.",
   "Passt Navigation, Tasten, Aussehen und Sprache an. Öffnen mit dem Zahnrad oben rechts oder Strg+,; schließen mit dem ✕ oben rechts im Fenster oder Esc."),
  [("Navigation tab – Mouse & Trackpad: choose the Style; the box below shows which buttons Rotate, Pan, Zoom and Select.",
    "Reiter Navigation – Maus & Trackpad: Wähle den Stil; der Kasten darunter zeigt, welche Tasten Drehen, Verschieben, Zoomen und Auswählen."),
   ("View: Camera, Rotate, Rotate around, Animate view changes, Glass, Show tool names, Body material, Projects folder and Language.",
    "Ansicht: Kamera, Drehen, Drehen um, Ansichtswechsel animieren, Glas, Werkzeugnamen anzeigen, Körpermaterial, Projektordner und Sprache."),
   ("Speed & Zoom: Rotation speed, Zoom & scroll speed, Zoom towards the cursor, Invert zoom (mouse wheel) and Invert zoom (trackpad).",
    "Tempo & Zoom: Drehgeschwindigkeit, Zoom- & Scrollgeschwindigkeit, Zum Cursor hin zoomen, Zoom umkehren (Mausrad) und Zoom umkehren (Trackpad)."),
   ("Keys tab: Add Key… turns a key into a mouse button, e.g. Shift as the middle button; choose the button and whether to Hold, Click, Double-click or Toggle.",
    "Reiter Tasten: Taste hinzufügen… macht eine Taste zur Maustaste, z. B. Umschalt als mittlere Taste; wähle die Maustaste und ob Halten, Klicken, Doppelklick oder Umschalten.")],
  tips=[("A new language takes effect after restarting MyCAD.", "Eine neue Sprache wirkt nach einem Neustart von MyCAD."),
        ("Keys acting as mouse buttons stay normal keys while you type text, e.g. when renaming.", "Tasten als Maustasten bleiben beim Schreiben normale Tasten, z. B. beim Umbenennen.")],
  commands=["MyCAD_Settings"], see=["start_navigation"])

# --- Skizze: Erstellen ----------------------------------------------------------------------------------------------
INSKETCH = ("These tools are in the sketch toolbar, which appears while you edit a sketch (CREATE → Sketch, or double-click a sketch).",
            "Diese Werkzeuge liegen in der Skizzen-Werkzeugleiste, die erscheint, während du eine Skizze bearbeitest (ERSTELLEN → Skizze oder Doppelklick auf eine Skizze).")
FIELDS = ("While drawing, small fields next to the cursor show the sizes: type a value, press Tab for the next field and Enter to confirm.",
          "Beim Zeichnen zeigen kleine Felder neben dem Cursor die Maße: Wert eintippen, Tab für das nächste Feld, Enter bestätigt.")
TOOLPARAMS = ("Extra options of the active tool appear in the Tool Parameters box below the Sketch Palette on the right.",
              "Zusätzliche Optionen des aktiven Werkzeugs stehen im Bereich Werkzeugparameter unter der Skizzenpalette rechts.")
ESCTOOL = ("The tool stays active so you can draw the next shape; press Esc (or right-click) when you are done.",
           "Das Werkzeug bleibt aktiv, damit du gleich die nächste Form zeichnen kannst; drücke Esc (oder Rechtsklick), wenn du fertig bist.")
SELECT_FIRST = ("Select the geometry first (Ctrl+click for several lines or points) or a box: drag from left to right around it.",
                "Wähle zuerst die Geometrie (Strg+Klick für mehrere Linien oder Punkte) oder zieh ein Rechteck von links nach rechts darum.")
S = "sketch_create"
A("sketch_line", S, "Sketcher_CreateLine", ("Line", "Linie"), (["line", "straight", "segment", "edge"], ["Linie", "gerade", "Strecke", "Kante"]),
  ("Draws a straight line between two points.", "Zeichnet eine gerade Linie zwischen zwei Punkten."),
  [INSKETCH, tool("CREATE", ("Line", "Linie"), sketch=True),
   ("Click the start point, then the end point.", "Klicke den Startpunkt, dann den Endpunkt."), FIELDS, ESCTOOL],
  tips=[("Points snap onto existing points and lines; nearly horizontal or vertical lines get the matching constraint automatically.",
         "Punkte rasten an vorhandenen Punkten und Linien ein; fast waagrechte oder senkrechte Linien bekommen die passende Abhängigkeit automatisch."),
        ("Press M while drawing to switch how the line is defined (e.g. by length and angle).", "Drücke beim Zeichnen M, um umzuschalten, wie die Linie bestimmt wird (z. B. über Länge und Winkel).")],
  commands=["Sketcher_CreateLine", "Sketcher_CompLine"], see=["sketch_polyline", "sketch_dimension"])
A("sketch_polyline", S, "Sketcher_CreatePolyline", ("Polyline", "Polylinie"), (["polyline", "outline", "connected lines", "contour", "shape"], ["Polylinie", "Umriss", "verbundene Linien", "Kontur", "Form"]),
  ("Draws connected lines and arcs in one go – ideal for an outline.", "Zeichnet verbundene Linien und Bögen in einem Zug – ideal für einen Umriss."),
  [INSKETCH, tool("CREATE", ("Polyline", "Polylinie"), sketch=True),
   ("Click point after point. Press M to switch the next segment between line and arc.", "Klicke Punkt für Punkt. Drücke M, um das nächste Stück zwischen Linie und Bogen umzuschalten."),
   ("Click the start point again to close the outline – it becomes a profile. Right-click or Esc ends an open line.",
    "Klicke wieder auf den Startpunkt, um den Umriss zu schließen – er wird ein Profil. Rechtsklick oder Esc beendet eine offene Linie.")],
  see=["sketch_line", "sketch_basics"])
A("sketch_rectangle", S, "Sketcher_CreateRectangle", ("Rectangle", "Rechteck"),
  (["rectangle", "square", "box", "rounded rectangle", "centered", "frame"], ["Rechteck", "Quadrat", "Kasten", "abgerundetes Rechteck", "mittig", "Rahmen"]),
  ("Draws a rectangle from two corners, around its centre, or with rounded corners.", "Zeichnet ein Rechteck aus zwei Ecken, um seinen Mittelpunkt oder mit abgerundeten Ecken."),
  [INSKETCH, tool("CREATE", ("Rectangle", "Rechteck"), ("Rectangle", "Rechteck"), sketch=True),
   ("Variants via the small arrow ▾: Rectangle (two corners), Centered Rectangle (centre, then corner), Rounded Rectangle (then set the corner radius).",
    "Varianten über den kleinen Pfeil ▾: Rechteck (zwei Ecken), Rechteck vom Mittelpunkt (Mitte, dann Ecke), Abgerundetes Rechteck (danach den Eckradius festlegen)."),
   ("Click the first corner (or the centre), move the mouse and click the opposite corner.", "Klicke die erste Ecke (oder die Mitte), bewege die Maus und klicke die gegenüberliegende Ecke."),
   FIELDS, TOOLPARAMS, ESCTOOL],
  commands=["Sketcher_CompCreateRectangles", "Sketcher_CreateRectangle", "Sketcher_CreateRectangle_Center", "Sketcher_CreateOblong"], see=["sketch_dimension", "Design_Extrude"])
A("sketch_circle", S, "Sketcher_CreateCircle", ("Circle and Ellipse", "Kreis und Ellipse"),
  (["circle", "ellipse", "round", "hole outline", "oval", "diameter"], ["Kreis", "Ellipse", "rund", "Bohrungsumriss", "Oval", "Durchmesser"]),
  ("Draws a circle from its centre or through three points, or an ellipse.", "Zeichnet einen Kreis vom Mittelpunkt oder durch drei Punkte, oder eine Ellipse."),
  [INSKETCH, tool("CREATE", ("Circle", "Kreis"), ("Circle", "Kreis"), sketch=True),
   ("Variants via the small arrow ▾: Circle From Center, Circle From 3 Points, Ellipse From Center, Ellipse From 3 Points.",
    "Varianten über den kleinen Pfeil ▾: Kreis vom Mittelpunkt, Kreis durch 3 Punkte, Ellipse vom Mittelpunkt, Ellipse durch 3 Punkte."),
   ("Circle From Center: click the centre, then a point on the circle (or type the size in the field).", "Kreis vom Mittelpunkt: klicke die Mitte, dann einen Punkt auf dem Kreis (oder tippe das Maß ins Feld)."),
   ESCTOOL],
  commands=["Sketcher_CompCreateConic", "Sketcher_CreateCircle", "Sketcher_Create3PointCircle", "Sketcher_CreateEllipseByCenter", "Sketcher_CreateEllipseBy3Points"],
  see=["Design_Revolve", "Design_Extrude"])
A("sketch_arc", S, "Sketcher_CreateArc", ("Arc", "Bogen"), (["arc", "curve", "round corner", "elliptical arc", "half circle"], ["Bogen", "Kurve", "runde Ecke", "Ellipsenbogen", "Halbkreis"]),
  ("Draws a circular arc from its centre or through three points, or an elliptical, hyperbolic or parabolic arc.",
   "Zeichnet einen Kreisbogen vom Mittelpunkt oder durch drei Punkte, oder einen Ellipsen-, Hyperbel- oder Parabelbogen."),
  [INSKETCH, tool("CREATE", ("Arc", "Bogen"), ("Arc", "Bogen"), sketch=True),
   ("Variants via the small arrow ▾: Arc From Center, Arc From 3 Points, Elliptical Arc, Hyperbolic Arc, Parabolic Arc.",
    "Varianten über den kleinen Pfeil ▾: Bogen vom Mittelpunkt, Bogen durch 3 Punkte, Ellipsenbogen, Hyperbelbogen, Parabelbogen."),
   ("Arc From Center: click the centre, then the start point, then the end point. Press M to switch between the variants while drawing.",
    "Bogen vom Mittelpunkt: klicke die Mitte, dann den Anfang, dann das Ende. Mit M schaltest du beim Zeichnen zwischen den Varianten um."),
   ESCTOOL],
  commands=["Sketcher_CompCreateArc", "Sketcher_CreateArc", "Sketcher_Create3PointArc", "Sketcher_CreateArcOfEllipse", "Sketcher_CreateArcOfHyperbola", "Sketcher_CreateArcOfParabola"],
  see=["sketch_fillet", "sketch_tangent"])
A("sketch_slot", S, "Sketcher_CreateSlot", ("Slot", "Langloch"), (["slot", "oblong hole", "groove", "arc slot", "elongated hole"], ["Langloch", "Schlitz", "Nut", "Bogen-Langloch", "längliches Loch"]),
  ("Draws a slot: two half circles joined by straight lines – or along an arc (Arc Slot).", "Zeichnet ein Langloch: zwei Halbkreise, mit geraden Linien verbunden – oder entlang eines Bogens (Bogen-Langloch)."),
  [INSKETCH, tool("CREATE", ("Slot", "Langloch"), ("Slot", "Langloch"), sketch=True),
   ("Click the start point, then the end point, then move the mouse to set the width and click.", "Klicke den Startpunkt, dann den Endpunkt, dann bewege die Maus für die Breite und klicke."),
   FIELDS, ESCTOOL],
  commands=["Sketcher_CompSlot", "Sketcher_CreateSlot", "Sketcher_CreateArcSlot"], see=["Design_Extrude"])
A("sketch_polygon", S, "Sketcher_CreateHexagon", ("Polygon", "Vieleck"), (["polygon", "hexagon", "triangle", "square", "octagon", "nut", "regular"], ["Vieleck", "Polygon", "Sechseck", "Dreieck", "Quadrat", "Achteck", "Mutter", "regelmäßig"]),
  ("Draws a regular polygon – triangle, square, pentagon, hexagon and more.", "Zeichnet ein regelmäßiges Vieleck – Dreieck, Quadrat, Fünfeck, Sechseck und mehr."),
  [INSKETCH, tool("CREATE", ("Triangle", "Dreieck"), ("Hexagon", "Sechseck"), sketch=True),
   ("The arrow ▾ offers Triangle, Square, Pentagon, Hexagon, Heptagon, Octagon and Polygon (any number of corners, set in the Tool Parameters).",
    "Der Pfeil ▾ bietet Dreieck, Quadrat, Fünfeck, Sechseck, Siebeneck, Achteck und Vieleck (beliebige Eckenzahl, in den Werkzeugparametern)."),
   ("Click the centre, then move the mouse for size and rotation and click.", "Klicke die Mitte, dann bewege die Maus für Größe und Drehung und klicke."), ESCTOOL],
  commands=["Sketcher_CompCreateRegularPolygon", "Sketcher_CreateTriangle", "Sketcher_CreateSquare", "Sketcher_CreatePentagon", "Sketcher_CreateHexagon",
            "Sketcher_CreateHeptagon", "Sketcher_CreateOctagon", "Sketcher_CreateRegularPolygon"], see=["sketch_rectangle"])
A("sketch_bspline", S, "Sketcher_CreateBSpline", ("B-Spline", "B-Spline"), (["spline", "free curve", "organic", "smooth curve", "freeform"], ["Spline", "Freiformkurve", "organisch", "glatte Kurve", "Freiform"]),
  ("Draws a smooth free-form curve, either through control points or through points on the curve itself.",
   "Zeichnet eine glatte Freiformkurve, entweder über Kontrollpunkte oder durch Punkte auf der Kurve selbst."),
  [INSKETCH, tool("CREATE", ("B-Spline", "B-Spline"), ("B-Spline", "B-Spline"), sketch=True),
   ("Variants via the arrow ▾: B-Spline (control points), Periodic B-Spline (closed), B-Spline From Knots (the curve passes through your points) and Periodic B-Spline From Knots.",
    "Varianten über den Pfeil ▾: B-Spline (Kontrollpunkte), Geschlossener B-Spline, B-Spline aus Knoten (die Kurve läuft durch deine Punkte) und Geschlossener B-Spline aus Knoten."),
   ("Click point after point; right-click to finish the curve.", "Klicke Punkt für Punkt; ein Rechtsklick beendet die Kurve.")],
  commands=["Sketcher_CompCreateBSpline", "Sketcher_CreateBSpline", "Sketcher_CreatePeriodicBSpline", "Sketcher_CreateBSplineByInterpolation", "Sketcher_CreatePeriodicBSplineByInterpolation"],
  see=["sketch_conic"])
A("sketch_conic", S, "Sketcher_CreateConic", ("Conic", "Kegelschnitt"), (["conic", "rho", "curve", "transition", "fillet curve"], ["Kegelschnitt", "Rho", "Kurve", "Übergang", "Übergangskurve"]),
  ("Draws a conic curve between two points; how full it bulges is set by the rho value.", "Zeichnet einen Kegelschnitt zwischen zwei Punkten; wie stark er sich wölbt, bestimmt der Rho-Wert."),
  [INSKETCH, tool("CREATE", ("Conic", "Kegelschnitt"), sketch=True),
   ("Click the start point and the end point, then the corner point where the two end tangents meet.", "Klicke Start- und Endpunkt, dann den Eckpunkt, in dem sich die beiden Endtangenten treffen."),
   TOOLPARAMS],
  see=["sketch_bspline", "sketch_arc"])
A("sketch_point", S, "Sketcher_CreatePoint", ("Point", "Punkt"), (["point", "hole center", "marker", "reference point"], ["Punkt", "Bohrungsmittelpunkt", "Markierung", "Bezugspunkt"]),
  ("Places a single point – for example where a hole goes.", "Setzt einen einzelnen Punkt – zum Beispiel, wo eine Bohrung hin soll."),
  [INSKETCH, tool("CREATE", ("Point", "Punkt"), sketch=True), ("Click where the point goes; repeat for more points.", "Klicke, wo der Punkt hin soll; wiederhole für weitere Punkte."), ESCTOOL],
  commands=["Sketcher_CreatePoint"], see=["Design_Hole", "sketch_dimension"])
A("sketch_text", S, "Sketcher_CreateText", ("Text", "Text"), (["text", "lettering", "label", "font", "engrave", "letters"], ["Text", "Schrift", "Beschriftung", "Schriftart", "gravieren", "Buchstaben"]),
  ("Writes text as outlines into the sketch – then emboss or extrude it.", "Schreibt Text als Umrisse in die Skizze – danach prägst oder extrudierst du ihn."),
  [INSKETCH, tool("CREATE", ("Text", "Text"), sketch=True),
   ("Type the text and choose the font in the Tool Parameters below the Sketch Palette.", "Tippe den Text ein und wähle die Schriftart in den Werkzeugparametern unter der Skizzenpalette."),
   ("Click the bottom-left point, then the bottom-right point to set length and direction.", "Klicke den Punkt unten links, dann unten rechts für Länge und Richtung.")],
  commands=["Sketcher_CreateText"], see=["Design_Emboss"])
A("sketch_project", S, "Sketcher_Projection", ("Project", "Projizieren"),
  (["project", "include", "external", "edge of body", "intersect", "reference"], ["projizieren", "übernehmen", "extern", "Körperkante", "Schnittkante", "Bezug"]),
  ("Brings edges of the model into the sketch so you can draw against them.", "Holt Kanten des Modells in die Skizze, damit du an ihnen entlang zeichnen kannst."),
  [INSKETCH, tool("CREATE", ("Project", "Projizieren"), ("Project", "Projizieren"), sketch=True),
   ("External Projection projects edges onto the sketch plane; External Intersection takes the lines where the model crosses the sketch plane (choose via the arrow ▾).",
    "Projektion übernehmen bildet Kanten auf die Skizzenebene ab; Schnittkante übernehmen nimmt die Linien, an denen das Modell die Skizzenebene schneidet (Auswahl über den Pfeil ▾)."),
   ("Click edges or faces of a body; they appear as purple lines. Press Esc when done.", "Klicke Kanten oder Flächen eines Körpers an; sie erscheinen als lila Linien. Drücke Esc, wenn du fertig bist.")],
  tips=[("Projected lines follow the model when it changes.", "Projizierte Linien folgen dem Modell, wenn es sich ändert.")],
  commands=["Sketcher_CompExternal", "Sketcher_Projection", "Sketcher_Intersection"], see=["sketch_basics"])

# --- Skizze: Ändern -------------------------------------------------------------------------------------------------
S = "sketch_modify"
A("sketch_fillet", S, "Sketcher_CreateFillet", ("Sketch Fillet and Chamfer", "Skizzen-Rundung und -Fase"), (["fillet", "round corner", "chamfer", "corner", "rounded"], ["Rundung", "Ecke runden", "Fase", "Ecke", "abgerundet"]),
  ("Rounds or bevels the corner between two lines in the sketch.", "Rundet die Ecke zwischen zwei Linien in der Skizze ab oder schrägt sie ab."),
  [INSKETCH, tool("MODIFY", ("Fillet", "Abrunden"), ("Fillet", "Abrunden"), sketch=True),
   ("Choose Fillet or Chamfer via the arrow ▾ (or press M while the tool is active).", "Wähle Abrunden oder Fase über den Pfeil ▾ (oder drücke M, während das Werkzeug aktiv ist)."),
   ("Click the corner point – or the first line and then the second line.", "Klicke den Eckpunkt an – oder die erste und dann die zweite Linie."),
   ("Move the mouse for the size or type it, and click.", "Bewege die Maus für die Größe oder tippe sie ein und klicke.")],
  commands=["Sketcher_CompCreateFillets", "Sketcher_CreateFillet", "Sketcher_CreateChamfer"], see=["Design_Fillet"])
A("sketch_trim", S, "Sketcher_Trimming", ("Trim, Extend and Split", "Stutzen, Verlängern und Teilen"),
  (["trim", "cut", "extend", "split", "remove part", "lengthen"], ["stutzen", "abschneiden", "verlängern", "teilen", "Teil entfernen", "länger machen"]),
  ("Trim removes a piece of a line up to the next crossing, Extend lengthens a line, Split cuts it in two.",
   "Stutzen entfernt ein Stück einer Linie bis zur nächsten Kreuzung, Verlängern macht eine Linie länger, Teilen schneidet sie in zwei."),
  [INSKETCH, tool("MODIFY", ("Trim", "Stutzen"), ("Trim", "Stutzen"), sketch=True),
   ("Choose via the arrow ▾: Trim Edge, Extend Edge or Split Edge.", "Wähle über den Pfeil ▾: Kante stutzen, Kante verlängern oder Kante teilen."),
   ("Trim Edge: click the piece that should go away.", "Kante stutzen: klicke das Stück an, das weg soll."),
   ("Extend Edge: click the line, then where it should end.", "Kante verlängern: klicke die Linie, dann, wo sie enden soll."),
   ("Split Edge: click the line where it should be cut.", "Kante teilen: klicke die Linie dort an, wo sie getrennt werden soll."), ESCTOOL],
  commands=["Sketcher_CompCurveEdition", "Sketcher_Trimming", "Sketcher_Extend", "Sketcher_Split"], see=["sketch_fillet"])
A("sketch_offset", S, "Sketcher_Offset", ("Offset", "Versatz"), (["offset", "parallel copy", "wall", "outline inside", "border"], ["Versatz", "parallele Kopie", "Wand", "Umriss innen", "Rand"]),
  ("Draws a parallel copy of lines at a distance – e.g. the inner outline of a wall.", "Zeichnet eine parallele Kopie von Linien im Abstand – z. B. den Innenumriss einer Wand."),
  [INSKETCH, SELECT_FIRST, tool("MODIFY", ("Offset", "Versatz"), sketch=True),
   ("Move the mouse or type the distance, and click.", "Bewege die Maus oder tippe den Abstand ein und klicke."), TOOLPARAMS],
  commands=["Sketcher_Offset"], see=["Design_Shell"])
A("sketch_mirror", S, "Sketcher_Symmetry", ("Mirror", "Spiegeln"), (["mirror", "symmetric copy", "flip", "other half"], ["spiegeln", "symmetrische Kopie", "umklappen", "andere Hälfte"]),
  ("Mirrors sketch geometry across a line or a point.", "Spiegelt Skizzengeometrie an einer Linie oder einem Punkt."),
  [INSKETCH, SELECT_FIRST, tool("MODIFY", ("Mirror", "Spiegeln"), sketch=True),
   ("Click the mirror line (e.g. an axis or a construction line) or a point.", "Klicke die Spiegellinie (z. B. eine Achse oder Konstruktionslinie) oder einen Punkt an."), TOOLPARAMS],
  commands=["Sketcher_Symmetry"], see=["Design_Mirror", "sketch_construction"])
A("sketch_pattern", S, "Sketcher_RectangularArray", ("Pattern", "Muster"), (["pattern", "array", "copies", "polar", "rotate copies", "grid"], ["Muster", "Anordnung", "Kopien", "polar", "gedrehte Kopien", "Raster"]),
  ("Copies sketch geometry in rows and columns, or rotated around a point.", "Kopiert Skizzengeometrie in Reihen und Spalten oder gedreht um einen Punkt."),
  [INSKETCH, SELECT_FIRST, tool("MODIFY", ("Pattern", "Muster"), ("Pattern", "Muster"), sketch=True),
   ("Choose via the arrow ▾: Rectangular Array (rows and columns) or Rotate / Polar Transform (around a point).",
    "Wähle über den Pfeil ▾: Rechteckige Anordnung (Reihen und Spalten) oder Drehen / Kreisförmig anordnen (um einen Punkt)."),
   ("Set the number of copies in the Tool Parameters, then click the reference points in the view.", "Stelle die Anzahl der Kopien in den Werkzeugparametern ein und klicke dann die Bezugspunkte in der Ansicht.")],
  commands=["Sketcher_RectangularArray", "Sketcher_Rotate"], see=["Design_Pattern"])
A("sketch_move", S, "Sketcher_Translate", ("Move and Scale", "Verschieben und Skalieren"), (["move", "translate", "copy", "scale", "resize"], ["verschieben", "bewegen", "kopieren", "skalieren", "Größe ändern"]),
  ("Moves or copies sketch geometry, or scales it around a point.", "Verschiebt oder kopiert Skizzengeometrie oder skaliert sie um einen Punkt."),
  [INSKETCH, SELECT_FIRST, tool("MODIFY", ("Move", "Verschieben"), ("Move", "Verschieben"), sketch=True),
   ("Choose via the arrow ▾: Move / Array Transform or Scale.", "Wähle über den Pfeil ▾: Verschieben / Anordnen oder Skalieren."),
   ("Move: click the reference point, then the target point. Scale: click the reference point, then set the scale factor.",
    "Verschieben: klicke den Bezugspunkt, dann den Zielpunkt. Skalieren: klicke den Bezugspunkt und lege dann den Faktor fest."),
   TOOLPARAMS],
  commands=["Sketcher_Translate", "Sketcher_Scale"], see=["sketch_pattern"])
A("sketch_construction", S, "Sketcher_ToggleConstruction", ("Construction Geometry", "Konstruktion"),
  (["construction", "helper line", "reference", "dashed", "guide"], ["Konstruktion", "Hilfslinie", "Bezug", "gestrichelt", "Führungslinie"]),
  ("Turns lines into construction geometry: orange dashed helper lines that never become part of a profile.",
   "Macht Linien zu Konstruktionsgeometrie: orange gestrichelte Hilfslinien, die nie Teil eines Profils werden."),
  [INSKETCH, SELECT_FIRST,
   ("In the sketch toolbar, in the MODIFY section, click Construction Geometry. Click it again to turn the lines back into normal geometry.",
    "Klicke in der Skizzen-Werkzeugleiste im Bereich ÄNDERN auf Konstruktion. Ein erneuter Klick macht sie wieder zu normaler Geometrie."),
   ("Without a selection, the button switches the drawing mode: new shapes are drawn as construction geometry until you click it again. The same switch is Construction in the Sketch Palette.",
    "Ohne Auswahl schaltet der Knopf den Zeichenmodus um: neue Formen werden als Konstruktion gezeichnet, bis du erneut klickst. Derselbe Schalter ist Konstruktion in der Skizzenpalette.")],
  commands=["Sketcher_ToggleConstruction"], see=["sketch_basics"])

# --- Skizze: Abhängigkeiten -----------------------------------------------------------------------------------------
S = "sketch_constraints"
EITHER = ("Either select the geometry first and then click the tool, or click the tool first and then the geometry.",
          "Entweder zuerst die Geometrie auswählen und dann das Werkzeug anklicken, oder zuerst das Werkzeug und dann die Geometrie.")
A("sketch_dimension", S, "Sketcher_Dimension", ("Dimension", "Bemaßung"),
  (["dimension", "size", "length", "distance", "radius", "diameter", "angle", "measure in sketch"], ["Bemaßung", "Maß", "Länge", "Abstand", "Radius", "Durchmesser", "Winkel", "bemaßen"]),
  ("One tool for every size: length, distance, radius, diameter and angle – it picks the right kind from what you click.",
   "Ein Werkzeug für jedes Maß: Länge, Abstand, Radius, Durchmesser und Winkel – es erkennt die Art an dem, was du anklickst."),
  [INSKETCH, tool("CONSTRAINTS", ("Dimension", "Bemaßung"), sketch=True),
   ("Click a line for its length, two points for their distance, a circle for its diameter, or two lines for the angle between them.",
    "Klicke eine Linie für ihre Länge, zwei Punkte für ihren Abstand, einen Kreis für seinen Durchmesser oder zwei Linien für den Winkel dazwischen."),
   ("Move the mouse to place the dimension, click, type the value and press Enter.", "Bewege die Maus, um das Maß zu platzieren, klicke, tippe den Wert ein und drücke Enter.")],
  tips=[("Type a parameter name or a formula such as Width / 2 instead of a number.", "Tippe statt einer Zahl einen Parameternamen oder eine Formel wie Breite / 2 ein."),
        ("Double-click an existing dimension to change its value.", "Doppelklick auf ein vorhandenes Maß ändert seinen Wert.")],
  commands=["Sketcher_Dimension", "Sketcher_CompDimensionTools", "Sketcher_ConstrainDistanceX", "Sketcher_ConstrainDistanceY", "Sketcher_ConstrainDistance",
            "Sketcher_ConstrainRadiam", "Sketcher_ConstrainRadius", "Sketcher_ConstrainDiameter", "Sketcher_ConstrainAngle", "Sketcher_ConstrainLock"],
  see=["Design_Parameters", "sketch_basics"])
A("sketch_coincident", S, "Sketcher_ConstrainCoincidentUnified", ("Coincident", "Koinzident"),
  (["coincident", "connect points", "point on line", "join", "close outline"], ["koinzident", "Punkte verbinden", "Punkt auf Linie", "zusammenfügen", "Umriss schließen"]),
  ("Puts two points on top of each other, or a point onto a line or circle.", "Legt zwei Punkte übereinander oder einen Punkt auf eine Linie oder einen Kreis."),
  [INSKETCH, EITHER, tool("CONSTRAINTS", ("Coincident", "Koinzident"), sketch=True),
   ("Click two points (or a point and a line).", "Klicke zwei Punkte an (oder einen Punkt und eine Linie).")],
  tips=[("An outline with a gap at one corner is not closed and gives no profile – Coincident closes it.",
         "Ein Umriss mit einer Lücke an einer Ecke ist nicht geschlossen und ergibt kein Profil – Koinzident schließt ihn.")],
  commands=["Sketcher_ConstrainCoincidentUnified"], see=["sketch_basics"])
A("sketch_horver", S, "Sketcher_ConstrainHorizontal", ("Horizontal and Vertical", "Horizontal und Vertikal"),
  (["horizontal", "vertical", "level", "straight up", "plumb"], ["horizontal", "vertikal", "waagrecht", "senkrecht", "lotrecht"]),
  ("Makes a line horizontal or vertical (or puts two points level).", "Macht eine Linie waagrecht oder senkrecht (oder zwei Punkte auf gleiche Höhe)."),
  [INSKETCH, EITHER, tool("CONSTRAINTS", ("Horizontal", "Horizontal"), ("Horizontal", "Horizontal"), sketch=True),
   ("For vertical choose Vertical Constraint via the arrow ▾.", "Für senkrecht wähle Vertikal-Abhängigkeit über den Pfeil ▾.")],
  commands=["Sketcher_ConstrainHorizontal", "Sketcher_ConstrainVertical", "Sketcher_ConstrainHorVer", "Sketcher_CompHorVer"], see=["sketch_parallel"])
A("sketch_parallel", S, "Sketcher_ConstrainParallel", ("Parallel and Perpendicular", "Parallel und Senkrecht"),
  (["parallel", "perpendicular", "right angle", "90 degrees", "square corner"], ["parallel", "senkrecht", "rechter Winkel", "90 Grad", "rechtwinklig"]),
  ("Makes two lines parallel or at a right angle to each other.", "Macht zwei Linien parallel oder rechtwinklig zueinander."),
  [INSKETCH, EITHER, tool("CONSTRAINTS", ("Parallel", "Parallel"), ("Parallel", "Parallel"), sketch=True),
   ("For a right angle choose Perpendicular Constraint via the arrow ▾. Click the two lines.", "Für einen rechten Winkel wähle Senkrecht-Abhängigkeit über den Pfeil ▾. Klicke die beiden Linien an.")],
  commands=["Sketcher_ConstrainParallel", "Sketcher_ConstrainPerpendicular"], see=["sketch_horver"])
A("sketch_tangent", S, "Sketcher_ConstrainTangent", ("Tangent", "Tangential"), (["tangent", "smooth transition", "touch", "blend"], ["tangential", "glatter Übergang", "berühren", "Übergang"]),
  ("Makes a line and an arc (or two curves) touch smoothly without a kink.", "Lässt eine Linie und einen Bogen (oder zwei Kurven) glatt ohne Knick ineinander übergehen."),
  [INSKETCH, EITHER, tool("CONSTRAINTS", ("Tangent", "Tangential"), sketch=True), ("Click the two curves.", "Klicke die beiden Kurven an.")],
  commands=["Sketcher_ConstrainTangent"], see=["sketch_arc"])
A("sketch_equal", S, "Sketcher_ConstrainEqual", ("Equal", "Gleich"), (["equal", "same size", "same length", "same radius"], ["gleich", "gleiche Größe", "gleiche Länge", "gleicher Radius"]),
  ("Gives lines the same length, or circles and arcs the same radius.", "Gibt Linien die gleiche Länge oder Kreisen und Bögen den gleichen Radius."),
  [INSKETCH, EITHER, tool("CONSTRAINTS", ("Equal", "Gleich"), sketch=True), ("Click two or more lines, or two or more circles.", "Klicke zwei oder mehr Linien oder zwei oder mehr Kreise an.")],
  tips=[("Dimension one of them – the others follow.", "Bemaße eines davon – die anderen folgen.")],
  commands=["Sketcher_ConstrainEqual"], see=["sketch_dimension"])
A("sketch_symmetric", S, "Sketcher_ConstrainSymmetric", ("Symmetric", "Symmetrisch"), (["symmetric", "centered", "mirror constraint", "centre"], ["symmetrisch", "mittig", "Spiegel-Abhängigkeit", "zentriert"]),
  ("Keeps two points symmetric to a line or a point – e.g. a rectangle centred on the axis.", "Hält zwei Punkte symmetrisch zu einer Linie oder einem Punkt – z. B. ein Rechteck mittig auf der Achse."),
  [INSKETCH, tool("CONSTRAINTS", ("Symmetric", "Symmetrisch"), sketch=True),
   ("Click the two points, then the symmetry line (e.g. the vertical axis) or the centre point.", "Klicke die beiden Punkte, dann die Symmetrielinie (z. B. die senkrechte Achse) oder den Mittelpunkt.")],
  commands=["Sketcher_ConstrainSymmetric"], see=["sketch_mirror"])
A("sketch_block", S, "Sketcher_ConstrainBlock", ("Block", "Fixieren"), (["fix", "block", "lock", "freeze", "pin"], ["fixieren", "blockieren", "sperren", "einfrieren", "festhalten"]),
  ("Locks geometry in place so it can no longer move.", "Hält Geometrie an ihrem Platz fest, sodass sie sich nicht mehr bewegt."),
  [INSKETCH, EITHER, tool("CONSTRAINTS", ("Block", "Fixieren"), sketch=True)],
  tips=[("Dimensions are usually the better choice: they keep the design editable.", "Bemaßungen sind meist die bessere Wahl: das Design bleibt änderbar.")],
  commands=["Sketcher_ConstrainBlock"], see=["sketch_dimension"])
A("sketch_finish", S, "Sketcher_LeaveSketch", ("Finish Sketch", "Skizze fertig stellen"),
  (["finish", "leave sketch", "close sketch", "done", "exit sketch"], ["fertig", "Skizze verlassen", "Skizze schließen", "erledigt", "Skizze beenden"]),
  ("Leaves the sketch and goes back to the model; its closed areas become profiles.", "Verlässt die Skizze und kehrt zum Modell zurück; ihre geschlossenen Flächen werden Profile."),
  [("Click the blue Finish Sketch button at the right end of the sketch toolbar – or in the Sketch Palette on the right – or press Esc twice.",
    "Klicke den blauen Knopf Skizze fertig stellen ganz rechts in der Skizzen-Werkzeugleiste – oder in der Skizzenpalette rechts – oder drücke zweimal Esc."),
   PROFILE],
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
