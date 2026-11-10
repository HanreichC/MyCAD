# Versionen und Varianten

## Immer gespeichert

MyCAD speichert von selbst: nach jeder abgeschlossenen Aktion, sobald es 2 Sekunden ruht. Nicht mitten in einem
Werkzeug-Dialog, nicht während du ziehst, nicht während einer Kamera-Animation.

- Ein **neues Design** bekommt beim ersten Speichern einen eigenen Ordner im Projektordner:
  `Projekte/<Name>/<Name>.mycad`.
- **Schließen** fragt nie nach dem Speichern; die letzten Sekunden werden still nachgespeichert.
- **Absturz:** Öffne das Design einfach wieder – höchstens die letzten zwei Sekunden fehlen.
- **Speichern unter** eines so angelegten Designs nimmt seine Versionen mit, und der erste Ordner kommt in den Papierkorb.
- Abschalten lässt sich das über den Parameter `MyCAD/AlwaysSave` (für Tests gedacht).

## Version sichern (Strg+S)

Gibt dem jetzigen Stand einen Namen, z. B. „Vor den Bohrungen“. Benannte Versionen bleiben immer.

## Versionen

Bereich DATEI, beim Knopf **Version sichern** ▾ → **Versionen**.

- Jeder gespeicherte Stand ist eine Version mit Vorschaubild und Zeit.
- **Aufbewahrung wie Time Machine:** alles vom letzten Tag, danach eine je Stunde für eine Woche, danach eine je Tag.
  Benannte Versionen bleiben immer.
- **Kopie öffnen:** zeigt die Version als eigenes Design, ohne sie zu verändern.
- **Vergleichen:** legt die Version als Geisterbild über das Modell – **grün gepunktet** kam seitdem dazu, **rot
  schraffiert** fiel weg –, und das Panel nennt neue, entfernte und geänderte Schritte.
- **Wiederherstellen:** holt den Stand zurück. Der Stand davor bleibt als Version; Wiederherstellen löscht nie.

Versionen liegen neben der Design-Datei im Ordner `versions/<Name>/`.

## Varianten – „Was wäre wenn“

Eine Variante ist eine Kopie des Designs zum Ausprobieren.

- **Neue Variante…** (im Fenster Versionen): Name eingeben, MyCAD wechselt gleich hinein.
- **Umschalten im Browser:** Rechtsklick auf den Designnamen oben im Browser → **Varianten** → Hauptdesign oder eine
  Variante (die offene hat einen Haken).
- **Vergleichen** zeigt den Unterschied zwischen Variante und Hauptdesign wie bei Versionen.
- **Zum Hauptdesign machen:** die offene Variante wird das Hauptdesign; das alte bleibt als Version „Vor …“ erhalten.

Varianten liegen im Ordner `variants/<Name>/` neben der Design-Datei.
