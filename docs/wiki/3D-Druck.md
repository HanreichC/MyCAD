# 3D-Druck

MyCAD ist für Leute gemacht, die drucken. Alles Wichtige ist eingebaut, vom Spiel bis zum Slicer.

## Druckansicht

**Druckansicht** (Bereich PRÜFEN) zeigt direkt am Modell, was der Drucker schwer findet. Muster statt nur Farbe, damit
es auch ohne Farbsehen klar ist:

| Muster | Bedeutung |
|---|---|
| rot schraffiert | Überhang flacher als der Grenzwinkel (Standard 45°) – braucht Stützen |
| grün gepunktet | liegt auf dem Druckbett |
| gelb gekreuzt | Wand dünner als die kleinste Wand (Standard 0,8 mm) |

- **Unterseite wählen:** die Fläche anklicken, die auf dem Bett liegen soll, dann in der Legende **Unterseite wählen**.
  Die Druckrichtung wird im Design gespeichert und von **Drucken** benutzt.
- Grenzwinkel und kleinste Wand stehen in den **Einstellungen**.
- Nochmal **Druckansicht** blendet sie aus.

## Drucken

**Drucken** (Bereich DATEI oder in der Legende) öffnet die sichtbaren (oder gewählten) Körper in deinem Slicer: als 3MF
mit Namen und Farben, die gewählte Unterseite nach unten.

MyCAD findet:

| Slicer | als Programm | Flatpak | AppImage in `~/Applications` |
|---|---|---|---|
| OrcaSlicer | `orca-slicer` | `io.github.softfever.OrcaSlicer` | `OrcaSlicer*.AppImage` |
| Bambu Studio | `bambu-studio` | `com.bambulab.BambuStudio` | `Bambu_Studio*.AppImage` |
| PrusaSlicer | `prusa-slicer` | `com.prusa3d.PrusaSlicer` | `PrusaSlicer*.AppImage` |
| UltiMaker Cura | `cura`, `UltiMaker-Cura` | `com.ultimaker.cura` | `UltiMaker-Cura*.AppImage` |

- Sind mehrere installiert, fragt MyCAD einmal und merkt sich die Wahl.
- **Flatpak:** Die Datei wird über das Dokumenten-Portal an den Slicer gereicht (`flatpak run --file-forwarding … @@ Datei @@`),
  damit er sie in seiner Sandbox sieht.
- Der Slicer startet ohne MyCADs eigene Bibliothekspfade und in der Sprache deines Desktops.
- Ohne Slicer bietet **Drucken** an, eine 3MF-Datei zu speichern.
- Wie fein Rundungen werden, bestimmt **Export-Auflösung** (grob/normal/fein) in den Einstellungen.

## Passung

Bohrung und Welle (oder ebene Flächen) wählen, **Passung** (Bereich ÄNDERN):

- **3D-Druck eng / normal / locker:** die Bohrung wird je Seite um das Spiel weiter (Standard 0,1 / 0,2 / 0,3 mm,
  einstellbar unter Einstellungen → Spiel beim 3D-Druck). Ohne Bohrung wird die Welle dünner, ebene Flächen gehen zurück.
- **ISO 286:** H7/g6 (gleitet), H7/h6 (enge Gleitpassung), H7/k6 (Übergang), H7/p6 (Presssitz), H8/f7 (läuft frei).
  Beide Flächen gehen auf das Mittelmaß ihres Toleranzfelds; das Spiel steht im Panel, z. B. `+7 … +41 µm`.
- Bohrung und Welle dürfen in zwei verschiedenen Körpern liegen.

## Schraube hier

Auf die Oberseite des oberen Teils klicken (oder auf die Kante einer runden Bohrung), **Schraube hier** (beim Knopf
Bohrung ▾). Das untere Teil ist der nächste Körper hinter dem Punkt, auch in einer anderen Komponente.

- **Schraube:** ISO 4762 (Zylinderkopf, versenkt), ISO 10642 (Senkkopf, bündig), ISO 7380 (Flachkopf); M2 bis M12.
- **Unten:** Gewindebohrung, **Einschmelzmutter** (Loch für Messingeinsätze, z. B. M3: Ø4 × 5,7 mm) oder
  **Mutterfalle** (Sechskant-Tasche an der Unterseite).
- **Länge:** die kürzeste Normlänge, die hält; zu kurz von Hand gewählt, schlägt MyCAD eine längere vor.

## Gewinde zum Drucken

Beim **Gewinde** „Spiel für den 3D-Druck“ anhaken: Das Spiel kommt von selbst (begrenzt auf ein Viertel der Steigung),
und unter 1 mm Steigung (kleiner als M8) warnt MyCAD, dass es mit einer 0,4-mm-Düse schlecht druckt.

## Export

**Exportieren** als **3MF** (je Körper ein Objekt mit Namen und Farbe), **STL**, **STEP** (mit Farben und Struktur) und
**DXF** (Skizzen, z. B. für Laser und CNC).
