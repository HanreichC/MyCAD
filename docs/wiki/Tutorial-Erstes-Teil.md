# Tutorial: Ein Halter für den 3D-Druck

In etwa 20 Minuten baust du eine Montageplatte mit gerundeten Ecken und zwei Schraubenlöchern, steuerst sie über eine
Notiz, korrigierst sie mit dem Rotstift, prüfst sie für den Druck und schickst sie an deinen Slicer. Unterwegs lernst du
die Ideen kennen, die MyCAD besonders machen.

> Tipp: Alles, was hier ein Knopf ist, findest du auch mit **Strg+K** – einfach den Namen tippen.

---

## 1. Neues Design – und nie wieder speichern

Auf der Startseite **Neues Design** klicken. Ab jetzt speichert MyCAD von selbst: nach jedem Schritt, sobald du kurz
nichts tust. Das Design bekommt einen eigenen Ordner in deinem Projektordner (Einstellungen → Allgemein →
Projektordner). Einen Speichern-Knopf brauchst du nicht, und beim Schließen fragt MyCAD nichts.

## 2. Die Maße in eine Notiz schreiben

Klicke in der Werkzeugleiste auf **Notiz** (Bereich WERKZEUGE). Eine gelbe Notiz erscheint. Schreib:

```
Breite = 60 mm
Tiefe = 30 mm
Dicke = 4 mm
Loch = Breite - 16 mm
```

Nach jedem **Enter** werden die Zeilen zu Parametern. Hinter der Formel steht gleich ihr Wert: `Loch = Breite - 16 mm → 44.00 mm`.
Diese Namen kannst du ab jetzt in jedes Maßfeld tippen. Unter **Parameter ändern** stehen sie auch, mit dem Hinweis
„In Notiz …“.

> Rechnen geht auch: eine Zeile, die mit `=` endet, wird ausgerechnet – `Breite / 2 =` ergibt `30.00 mm`.

## 3. Skizze und Körper

1. **Skizze erstellen** (Taste **S**), dann die XY-Ebene in der Ansicht anklicken.
2. Ein **Rechteck** zeichnen, ungefähr, irgendwo um den Ursprung.
3. Mit **Bemaßung** die Breite anklicken und statt einer Zahl `Breite` tippen, für die Höhe `Tiefe`.
4. **Skizze fertigstellen**.
5. **Extrudieren** (Taste **E**), das Rechteck anklicken, als Abstand `Dicke` tippen, oben im Panel **OK**.

Du hast eine Platte 60 × 30 × 4 mm.

## 4. Fläche antippen, Zahl ändern

Klicke ohne Werkzeug auf die **Oberseite** der Platte. Neben ihr erscheint eine kleine Glaskarte mit dem Maß, das diese
Fläche erzeugt: Abstand = Dicke. Tipp `6` und **Enter** – die Platte wird dicker, und in der Notiz steht jetzt
`Dicke = 6 mm`. Andersherum geht es auch: ändere in der Notiz `Breite = 80 mm`, klick in die Ansicht, und die Platte
wird breiter. **Strg+Z** nimmt jede Änderung zurück.

## 5. Ecken runden

Die vier senkrechten Kanten anklicken (Strg+Klick), **Abrunden** (Taste **F**), Radius `3`, **OK**.

Probier ruhig einen zu großen Radius, z. B. `20`: Der Schritt in der Zeitleiste bekommt ein rotes Abzeichen, das Panel
sagt, was nicht geht, und bietet einen Radius an, der noch passt. Ein Klick auf den Vorschlag, und es stimmt wieder.

## 6. Mit dem Rotstift korrigieren

Statt Werkzeuge zu suchen, schreibst du, was du willst, direkt aufs Modell:

1. Im Bereich WERKZEUGE beim **Scribble**-Knopf den kleinen Pfeil ▾ und **Rotstift** wählen. Ein durchsichtiges Blatt
   liegt vor dem Modell, der Stift ist rot.
2. Schreib (mit Grafiktablett oder Maus) **`Ø4,5`** zweimal auf die Oberseite, dort, wo die Löcher hin sollen, und
   **`C1`** neben eine obere Längskante.
3. In der Palette **Korrekturen ausführen**. Für jede Korrektur kommt eine Karte: `Ø4,5 → Bohrung Ø4.5 mm`,
   `C1 → Fase 1 mm an 1 Kante`.
4. Zeig mit der Maus auf eine Karte: Das Ziel wird im Modell hervorgehoben. **Zeigen** setzt das Ergebnis probehalber
   ein, **Ausführen** behält es, **Alle ausführen** erledigt alles.

Die Tinte bleibt im Scribble „Korrekturen“ – später siehst du noch, was du warum geändert hast.

> Was der Rotstift noch versteht: `R2` (Rundung), `M5` (Gewindebohrung bzw. Gewinde), `+5` / `−5` (Fläche ziehen/drücken),
> `H7` oder `Druck` (Passung), `3×` (Muster), eine Zahl (das Maß der Fläche) und `weg` oder ein Strich durch eine Fläche
> (Fläche entfernen). Siehe [Rotstift und Scribble](Rotstift-und-Scribble).

## 7. Für den Druck prüfen

1. Im Bereich PRÜFEN **Druckansicht** klicken. Rot schraffiert: Überhänge, die Stützen brauchen. Grün gepunktet: was auf
   dem Bett liegt. Gelb gekreuzt: Wände dünner als 0,8 mm. Unten rechts steht die Legende.
2. Soll eine andere Seite unten liegen, die Fläche anklicken und in der Legende **Unterseite wählen**.

## 8. Einen Stand festhalten

**Strg+S** heißt in MyCAD **Version sichern**: gib dem Stand einen Namen, z. B. „Erster Druck“. Gesichert ist ohnehin
alles; der Name hilft dir, ihn wiederzufinden.

## 9. Drucken

In der Legende (oder im Bereich DATEI) **Drucken**. MyCAD findet deinen Slicer – OrcaSlicer, Bambu Studio, PrusaSlicer
oder Cura, auch als Flatpak – und öffnet die Platte dort als 3MF, mit der gewählten Unterseite nach unten. Beim ersten Mal
fragt es, welchen Slicer du nimmst, wenn mehrere da sind.

## 10. Zurückblicken

Mach die Platte breiter (in der Notiz `Breite = 100 mm`). Dann im Bereich DATEI beim Knopf **Version sichern** den Pfeil ▾,
**Versionen**: Wähle „Erster Druck“ und **Vergleichen** – was dazugekommen ist, liegt grün gepunktet über dem Modell,
was weggefallen ist rot schraffiert, und das Panel nennt die geänderten Schritte. **Wiederherstellen** holt den alten
Stand zurück, ohne den neuen zu löschen.

---

**Weiter:** [Tutorial: Baugruppe mit Gelenken](Tutorial-Baugruppe) · [Funktionsübersicht](Funktionsuebersicht)
