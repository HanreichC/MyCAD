# Notizen und Parameter

## Notizen

**Notiz** (Bereich WERKZEUGE) legt ein gelbes Post-it über die Ansicht. Es bleibt in der Fensterecke, in die du es
ziehst, auch wenn das Fenster kleiner wird, und bleibt offen, während du Skizzen bearbeitest. Geschlossene Notizen stehen
im Browser unter **Notizen**; ein Doppelklick öffnet sie wieder. Notizen werden im Design gespeichert.

### Rechnen

Eine Zeile, die mit `=` endet, wird ausgerechnet (auf Deutsch mit Komma, auf Englisch mit Punkt):

| Du tippst | Ergebnis |
|---|---|
| `120 / 4 =` | `120 / 4 = 30` |
| `1,5 + 2 =` | `1,5 + 2 = 3,5` |
| `10 mm + 1 in =` | `10 mm + 1 in = 35,40 mm` |
| `Breite / 4 =` | mit dem Parameter Breite |
| `M8: 2 * 3 =` | Text vor dem Doppelpunkt bleibt stehen |

### Parameter festlegen

Eine Zeile `Name = Wert oder Formel` (ohne `=` am Ende) ist ein **Parameter**. Nach **Enter** oder wenn du die Notiz
verlässt, gilt er:

```
Wand = 2 mm
Breite = Wand * 20        → 40.00 mm
Wandstärke = 2,5 mm
```

- Formeln zeigen ihren Wert hinter dem Pfeil. Den Pfeil-Teil musst du nie anfassen, MyCAD schreibt ihn neu.
- **Umlaute** gehen (`Wandstärke` heißt intern `Wandstaerke`, beide Schreibweisen funktionieren), ebenso das Dezimalkomma.
- Jedes Maßfeld versteht die Namen: Extrusionsabstand `Wand`, Skizzenmaß `Breite / 2`.
- **Beide Richtungen:** Änderst du den Wert am Modell (Fläche antippen) oder in **Parameter ändern**, ändert sich die
  Zeile in der Notiz.
- **Fehler** stehen mit ⚠ hinter der Zeile: Name doppelt, Name schon in einer anderen Notiz, kein gültiger Wert.
- **Nichts geht still verloren:** Löschst du die Zeile eines Parameters, den noch ein Maß benutzt, bleibt der Parameter,
  und die Notiz sagt `⚠ Wand wird noch gebraucht von Extrude`. Erst wenn ihn niemand mehr braucht, verschwindet er.

## Parameter ändern

Der klassische Weg (Bereich WERKZEUGE → **Parameter ändern**): eine Tabelle mit Name, Ausdruck und Wert. Neue Parameter
mit **Hinzufügen**, Ausdrücke direkt in der Tabelle ändern. Parameter aus einer Notiz zeigen „In Notiz …“ und werden dort
geändert.
