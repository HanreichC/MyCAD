# Funktionsübersicht

Alles, was MyCAD kann, auf einer Seite. Die Namen sind die aus der deutschen Oberfläche, in Klammern die englischen.
Zu jedem Werkzeug gibt es in MyCAD einen Hilfeartikel (**?** unten links, oder in der Befehlssuche).

---

## Oberfläche

- **Liquid Glass** – Werkzeugleiste, Browser, Fenster-Knöpfe und Panels schweben als Glas über dem Modell. Regler von
  „Ultraklar“ bis „Getönt“ in den Einstellungen.
- **Hell, Dunkel, Automatisch**; Kontrast erhöhen, Transparenz reduzieren, Bewegung reduzieren.
- **Deutsch oder Englisch**, mit den Begriffen der deutschen Fusion-360-Version.
- **Startseite** mit zuletzt benutzten Designs und dem Projektordner, mit großen Vorschaubildern und Suche.
- **Befehlssuche** mit **Strg+K**: findet Befehle, Körper und Skizzen; versteht Tippfehler, deutsche und englische
  Begriffe und Wörter aus anderen CAD-Programmen („pad“, „pocket“, „push pull“). Zuletzt benutzte stehen oben.
- **Eingebaute Hilfe** mit 86 Artikeln, Bildern und Suche.

## Skizzieren

- Zeichnen: Linie, Polylinie, Rechteck, Kreis, Bogen, Langloch, Vieleck, B-Spline, Kegelschnitt, Punkt, Text; Kanten des
  Modells in die Skizze projizieren.
- Ändern: Abrunden, Stutzen, Verlängern, Teilen, Versatz, Spiegeln, Muster, Verschieben, Skalieren.
- Ein **Bemaßungswerkzeug**, das aus der Auswahl erkennt, was gemessen werden soll; Abhängigkeiten koinzident,
  horizontal, vertikal, parallel, senkrecht, tangential, gleich, symmetrisch, fixiert.
- Jede geschlossene Fläche ist ein eigenes Profil: zwei Kreise ineinander, den Ring anklicken, extrudieren – fertig ist
  das Rohr.

## Volumenkörper

**Erstellen:** Extrudieren · Drehen · Sweep · Erhebung · Rippe · Steg · Prägen · Quader · Zylinder · Kugel · Torus ·
Spirale · Bohrung · **Schraube hier** · Gewinde · Muster · Spiegeln

**Ändern:** Drücken/Ziehen · **Passung** · **Fläche entfernen** · Fläche ersetzen · Fläche teilen · Abrunden · Fase ·
Wandstärke · Formschräge · Kombinieren · Körper teilen · Verschieben · Ausrichten · Skalieren

**Konstruieren:** Versetzte Ebene · Ebene im Winkel · Mittelebene · Ebene · Achse · Punkt

**Prüfen:** Messen · Schnittanalyse · **Druckansicht**

Besonders erwähnenswert:

- **Extrudieren:** eine Seite, symmetrisch, zwei Seiten, bis zu einem Objekt, durch alles; mit Verjüngungswinkel und als
  dünne Wand. Eine ebene Körperfläche anklicken und extrudieren geht auch (wie Drücken/Ziehen).
- **Bohrung nach Norm:** ISO metrisch, ISO fein, UNC, UNF; Durchgangsbohrung (fein/mittel/grob) oder Gewindebohrung;
  Senkung passend zur Schraube (ISO 4762 Zylinderkopf, ISO 10642 Senkkopf, ISO 7380 Flachkopf); Gewinde auf Wunsch echt
  modelliert.
- **Gewinde:** echtes, druckbares ISO-Gewinde außen oder innen; Größe automatisch; Spiel für den 3D-Druck; Linksgewinde.
- **Abrunden** mit veränderlichem Radius; **Fase** mit gleichem Abstand, zwei Abständen oder Abstand und Winkel.
- **Muster** rechteckig, kreisförmig oder entlang eines Pfads; Richtungen und Achsen frei aus Kanten, Flächen, Achsen.
- **Spiegeln, Muster, Verschieben** an beliebigen Ebenen, Flächen, Kanten und Achsen.

## Zeitleiste

- Jeder Schritt steht in der **Zeitleiste** unten. Zurückspulen, ändern, der Rest rechnet nach.
- Schritte **per Ziehen umsortieren** (MyCAD sagt, wenn ein Schritt einen anderen braucht).
- Schritte **gruppieren** (Strg+Klick, „Gewählte Schritte gruppieren“), Gruppen zu- und aufklappen, umbenennen.
- **Fehler erklären sich**: ein rotes Abzeichen am Schritt, ein Text, der sagt, was los ist, und ein **Vorschlag, der
  geht** (z. B. „Radius 2,4 mm geht noch“) – ein Klick setzt ihn. Kanten, die nach einer Änderung nicht mehr sicher
  dieselben sind, werden orange markiert: „Betroffene Kanten zeigen“ oder „Stimmt so“.

## Maße und Parameter

- **Fläche antippen, Zahl ändern:** Klick auf eine Fläche (ohne aktives Werkzeug) zeigt am Modell die Maße, die sie
  erzeugen – Extrusionslänge, Skizzenmaß, Bohrungsdurchmesser, Radius. Zahl tippen, Enter, fertig. Strg+Z geht.
- **Parameter ändern:** benannte Werte und Formeln (`Breite = 40 mm`, `Höhe = Breite / 4`) für alle Maßfelder.
- **Notiz als Parameterliste:** `Wand = 2 mm` in einer Notiz legt den Parameter an; Formeln zeigen ihren Wert
  (`Breite = Wand * 20 → 40.00 mm`); ändert sich der Wert am Modell, ändert sich die Notiz mit.
- **Notizen rechnen:** `120 / 4 =` ergibt `30`, mit Einheiten (`10 mm + 1 in = 35.40 mm`) und Parameternamen.

## Ideen und Handschrift

- **Scribble:** Zeichenblatt mit Stift-Druck, Bleistift, Fineliner, Marker, Radierer; Formen (Linie, Pfeil, Rechteck,
  Dreieck, Sechseck, Kreis, Ellipse), Füllen, Text, Auswählen und Verschieben.
- Gerade Linien, Kreise und Rechtecke durch kurzes Stillhalten; Handschrift wird von selbst ordentlich.
- **Handschrift lesen** (offline): Suche in der Handschrift, CAD-Schreibweise (o12 → Ø12, 2x45 → 2×45°).
- **Blatt umstellen** auf jede Fläche oder senkrecht entlang eines Strichs: in 3D skizzieren.
- **In Skizze umwandeln:** Striche werden eine echte Skizze, geschriebene Maße (`Ø12` neben einem Kreis) werden Bemaßungen.
- **Rotstift:** Korrekturen direkt aufs Modell schreiben – `R2`, `C2`, `2×45°`, `+5`, `−5`, `M5`, `Ø8`, `H7`, `Druck`,
  `3×`, eine Zahl, `weg` oder ein Strich durch eine Fläche. Jede wird eine Karte mit Zeigen, Ausführen und Verwerfen.

## 3D-Druck

- **Druckansicht:** Überhänge (rot schraffiert), Flächen auf dem Bett (grün gepunktet), zu dünne Wände (gelb gekreuzt);
  **Unterseite wählen** legt die Druckrichtung fest. Grenzwinkel und kleinste Wand in den Einstellungen.
- **Drucken:** öffnet das Design als 3MF mit Farben im Slicer – **OrcaSlicer, Bambu Studio, PrusaSlicer, UltiMaker
  Cura**, als Programm, **Flatpak** oder AppImage. Merkt sich deinen Slicer.
- **Passung:** Bohrung und Welle nach ISO 286 (H7/g6, H7/h6, H7/k6, H7/p6, H8/f7) oder mit Druckspiel (eng/normal/locker,
  einstellbar). Das Spiel steht im Panel.
- **Schraube hier:** ein Klick verschraubt zwei Teile: oben Durchgang mit Senkung, unten Gewindebohrung, Einschmelzmutter oder
  Mutterfalle; die Schraubenlänge wird nach Norm vorgeschlagen.
- **Gewinde zum Drucken:** Spiel kommt von selbst, Hinweis bei zu feiner Steigung.
- **Export** als 3MF (Farben, Namen), STL, STEP (mit Farben), DXF (Skizzen); Auflösung grob/normal/fein.

## Speichern und Versionen

- **Immer gespeichert:** nach jeder Aktion, sobald MyCAD 2 Sekunden ruht. Neue Designs bekommen einen eigenen Ordner im
  Projektordner. Beim Schließen keine Rückfrage. Absturz: höchstens 2 Sekunden fehlen.
- **Version sichern** (Strg+S) gibt dem Stand einen Namen.
- **Versionen:** jeder Stand bleibt, aufbewahrt wie bei Time Machine. Mit Vorschaubild ansehen, **vergleichen** (Geisterbild:
  grün dazugekommen, rot entfernt, dazu die geänderten Schritte) und **wiederherstellen** (löscht nie etwas).
- **Varianten:** „Was wäre wenn“ als Kopie ausprobieren, im Browser umschalten, vergleichen, zum Hauptdesign machen.

## Baugruppen

- **Komponenten** mit eigenen Körpern, Skizzen und Ursprung, alles in einer Datei.
- **Gelenke:** Starr, Drehung, Schieberegler, Zylindrisch, Stift-Schlitz, Planar, Kugel; Winkel und Weg mit Grenzen.
- **Ketten:** ein Teil an einem bewegten Teil bewegt sich mit.
- **Geschlossene Ketten** (z. B. Viergelenk) über den Solver; das erste Gelenk treibt, die anderen folgen.
- **Animieren** mit **Kollisionsanzeige**.

## Prüfen

- **Messen:** Abstände, Winkel, Flächen, Volumen – für einen ganzen Körper auch **Masse, Werkstoff und Schwerpunkt**.
- **Darstellung** setzt den passenden **Werkstoff** (Dichte) mit; eigene Wahl bleibt erhalten.
- **Schnittanalyse**, **Druckansicht**.

## Darstellung und Materialien

- 119 Materialien (Metalle, eloxiert, Lacke, Kunststoffe, PLA mit Druckschichten, Gummi, Glas, Holz, Stein, Leder,
  Carbon …), viele als echte Fotoscans mit Relief und Hirnholz.
- Spiegelungen eines Studioraums, Klarlack, Kontaktschatten – alles einzeln abschaltbar.
- Ziehen einer Materialkugel auf einen Körper; einzelne Flächen färben.

## Bedienung

- 12 Navigationsstile (u. a. Fusion 360, SolidWorks, Blender, Touchpad); Tasten als Maustasten.
- Grafiktablett mit Druck und Schwebe unter Wayland; Seitentasten navigieren.
- Tastenkürzel: siehe [Bedienung und Einstellungen](Bedienung-und-Einstellungen).

## Dateien

- Eigenes Format `.mycad` (ZIP mit Vorschaubild, gleicher Inhalt wie FreeCADs `.FCStd`); `.FCStd` öffnet auch.
- Import: STEP (je Solid ein Körper), DXF und SVG in eine Skizze.
