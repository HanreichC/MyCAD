# Rotstift und Scribble

## Scribble – Ideen zuerst

**Scribble** (Bereich WERKZEUGE) öffnet ein Zeichenblatt mit feinem Punktraster. Am besten mit Grafiktablett, die Maus
geht auch.

- **Stifte:** Bleistift, Fineliner, Marker, in fünf Farben; fester drücken macht die Linie dicker. Radieren mit dem
  Stift-Ende oder Taste **E** (nochmal **E** zurück zum Stift).
- **Gerade Formen:** am Ende eines Strichs kurz stillhalten – er wird zur Linie, zum Kreis oder Rechteck und rastet
  waagerecht, senkrecht und an anderen Strichenden ein.
- **Formen:** Linie, Pfeil, Rechteck, Dreieck, Sechseck, Kreis, Ellipse aufziehen. **Füllen** färbt eine Fläche.
- **Auswählen** (**V**): Striche antippen oder umranden, ziehen; eine kleine Leiste färbt um oder löscht.
- **Text** schreibt mit der Tastatur auf das Blatt.
- **Ordentliche Handschrift:** eine Sekunde nach dem Absetzen rücken deine Wörter gerade, gleich groß und gleich
  geneigt – immer noch in deiner Schrift. Strg+Z holt die rohe Fassung zurück. Einstellung: **Stift & Handschrift**.
- **Handschrift lesen** (offline, deutsches Modell): **Handschrift suchen** in der Palette springt zu jedem Wort; Maße
  bekommen die CAD-Schreibweise (o12 → Ø12, 2x45 → 2×45°, 25mm → 25 mm).
- **Transparentpapier:** das Modell scheint durch. **Nur das Blatt** (**Tab**) blendet alles andere aus.
- **Blatt umstellen:** Blatt auf eine Körperfläche legen oder entlang eines gezeichneten Strichs aufstellen – so
  skizzierst du in 3D direkt dort, wo eine Wand hin soll. **Senkrecht ansehen** (**L**) dreht die Kamera zum Blatt.
- **In Skizze umwandeln:** Linien, Kreise, Ellipsen und Formen werden eine echte Skizze, fertig zum Bemaßen. Ein
  geschriebenes `Ø12` neben einem Kreis wird seine Bemaßung.

Scribbles bleiben im Design unter **Scribbles** im Browser.

## Rotstift – die Handschrift ist der Befehl

**Rotstift** (Bereich WERKZEUGE, beim Scribble-Knopf ▾) legt ein durchsichtiges Blatt vor das Modell, quer zu deinem
Blick, mit rotem Fineliner. Du schreibst Korrekturen dorthin, wo sie hingehören, wie auf einer Zeichnung. Dann
**Korrekturen ausführen** in der Palette.

| Du schreibst | an / auf | MyCAD macht |
|---|---|---|
| `R2` | eine Kante | Rundung R2 |
| `C2` oder `2×45°` | eine Kante | Fase 2 mm |
| `+5` / `−5` | eine ebene Fläche | Fläche 5 mm herausziehen / hineindrücken |
| `M5` | eine ebene Fläche | Gewindebohrung M5 genau an der Stelle |
| `M8` | einen Bolzen | Gewinde M8 |
| `Ø8` | eine ebene Fläche | Bohrung Ø8 an der Stelle |
| `Ø12` | eine Bohrung oder einen Bolzen | Durchmesser wird 12 mm (über ihr Maß) |
| `H7` oder `Druck` | eine Bohrung | Passung H7 bzw. 3D-Druck-Spiel |
| `3×` | neben ein Feature (Zapfen, Tasche) | Muster mit 3 Stück in die Richtung, in die du schreibst |
| `12` | eine Fläche | das Maß, das die Fläche treibt, wird 12 |
| `weg` oder ein Strich quer durch | eine Fläche | Fläche entfernen (Rundung, Fase, Bohrung verschwindet) |

**Typische Lesefehler** fängt MyCAD ab: `MS` wird `M5`, `o8` wird `Ø8`, `R 2` wird `R2`, `2x45` wird `2×45°`, `3x` wird
`3×`, ein `O` in einer Zahl wird `0`. Ein einzelner senkrechter Strich bleibt eine `1`; quer durch eine Fläche heißt er
„weg“.

### Die Karten

Für jede erkannte Korrektur erscheint eine Karte rechts: `R2 → Rundung R2 an 1 Kante`.

- **Zeigen auf die Karte** hebt das Ziel im Modell hervor.
- **Zeigen** setzt das Ergebnis probehalber ins Modell, **Ausblenden** nimmt es heraus.
- **Ausführen** behält es (ein normaler Schritt in der Zeitleiste, Strg+Z nimmt ihn zurück), **Verwerfen** lässt es.
- **Alle ausführen** erledigt alle Karten.
- Sind zwei Ziele gleich nah (z. B. Tinte genau zwischen zwei Kanten), fragt die Karte **Welche?** statt zu raten.

Die Tinte bleibt im Scribble „Korrekturen“, damit du später siehst, was du warum geändert hast.
