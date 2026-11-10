# Modellieren

## Der Ablauf

Wie in Fusion 360: **Skizze** auf einer Ebene oder Fläche, ein Profil anklicken, **Extrudieren** oder **Drehen**, dann
mit Werkzeugen wie Abrunden, Bohrung und Muster weiterarbeiten. Jeder Schritt landet in der **Zeitleiste**.

Ein Design besteht aus **Körpern** (Bodies) in **Komponenten**. Die Wurzel-Komponente ist das Design selbst; weitere
Komponenten brauchst du für [Baugruppen](Baugruppen).

## Skizzen

- **Skizze erstellen** (S), dann eine Ebene oder ebene Fläche anklicken. Die Kamera schaut gerade darauf.
- Jede geschlossene Region ist ein eigenes Profil. Zwei Kreise ineinander ergeben einen Ring und eine Scheibe.
- **Bemaßung** erkennt aus der Auswahl, was gemessen wird (Länge, Abstand, Radius, Winkel). In jedes Maßfeld kannst du
  Formeln und Parameternamen tippen.
- **Esc** legt das aktive Werkzeug weg, **Skizze fertigstellen** führt zurück zum Modell.
- Kanten des Modells lassen sich in die Skizze projizieren und mitbenutzen.

## Werkzeuge im Überblick

| Bereich | Werkzeuge |
|---|---|
| ERSTELLEN | Skizze erstellen · Extrudieren · Drehen · Sweep · Erhebung · Rippe · Steg · Prägen · Quader · Zylinder · Kugel · Torus · Spirale · Bohrung · Schraube hier · Gewinde · Muster · Spiegeln |
| ÄNDERN | Drücken/Ziehen · Passung · Fläche entfernen · Fläche ersetzen · Fläche teilen · Abrunden · Fase · Wandstärke · Formschräge · Kombinieren · Körper teilen · Verschieben · Ausrichten · Skalieren |
| KONSTRUIEREN | Versetzte Ebene · Ebene im Winkel · Mittelebene · Ebene · Achse · Punkt |
| ZUSAMMENFÜGEN | Neue Komponente · Gelenk |
| PRÜFEN | Messen · Schnittanalyse · Druckansicht · Alles zeigen |
| WERKZEUGE | Suchen · Parameter ändern · Darstellung · Scribble / Rotstift · Notiz |

Knöpfe mit einem kleinen Pfeil ▾ enthalten weitere Werkzeuge (z. B. Bohrung ▾ Schraube hier, Gewinde).

### Extrudieren

Richtung **Eine Seite**, **Symmetrisch**, **Zwei Seiten**, **Bis Objekt** (bis zu einer Fläche oder Ebene) oder
**Alle** (durch alles). Dazu **Verjüngungswinkel** (positiv macht schmaler) und **dünne Wand** (nur ein Rand mit
Wandstärke). Operation: neuer Körper, verbinden, abziehen, schneiden. Eine ebene Fläche eines Körpers anklicken und
extrudieren funktioniert wie Drücken/Ziehen.

### Bohrung

Punkte in einer Skizze auf der Fläche setzen, **Bohrung**. Mit **Norm** (ISO metrisch, ISO metrisch fein, UNC, UNF)
füllt MyCAD alles aus: **Durchgangsbohrung** mit Passung fein/mittel/grob oder **Gewindebohrung** (Kernloch, auf Wunsch
echtes Gewinde), Senkung passend zur Schraube. Mit **Eigene Maße** sind alle Werte frei.

### Gewinde

Zylinderfläche eines Bolzens oder einer Bohrung anklicken, **Gewinde**. Die ISO-Größe passt sich an den Durchmesser an.
**Spiel** je Seite für gedruckte Gewinde, oder gleich „Spiel für den 3D-Druck“ anhaken.

### Abrunden, Fase, Wandstärke

- **Abrunden** mit festem oder veränderlichem Radius (Anfang/Ende).
- **Fase** mit gleichem Abstand, zwei Abständen oder Abstand und Winkel; Seite umkehrbar.
- **Wandstärke** höhlt einen Körper aus; offene Flächen wählbar.

### Muster, Spiegeln, Verschieben

- **Muster** rechteckig, kreisförmig oder entlang eines Pfads (Kanten); Richtungen und Achse aus Kanten, Achsen oder
  Flächennormalen; Kopien können dem Pfad folgend mitdrehen. Geht für Features (Extrusion, Bohrung) und ganze Körper.
- **Spiegeln** an jeder Ebene oder ebenen Fläche.
- **Verschieben** um Abstände und Drehungen, auch um eine gewählte Achse.

### Fläche entfernen

Flächen anklicken, **Fläche entfernen**: die Nachbarflächen wachsen über die Lücke. So verschwinden Rundungen, Fasen,
Bohrungen oder Taschen wieder – praktisch bei importierten STEP-Teilen ohne Verlauf.

## Zeitleiste

- Unten in der Mitte, ein Eintrag je Schritt; Doppelklick öffnet ihn wieder.
- **Zurückspulen:** die Pfeile oder ein Klick setzen die Markierung zurück; spätere Schritte ruhen, bis du vorspulst.
- **Umsortieren:** einen Eintrag ziehen. Braucht er einen anderen, sagt MyCAD welchen.
- **Gruppen:** mehrere Einträge mit Strg+Klick wählen, Rechtsklick → **Gewählte Schritte gruppieren**. Gruppen klappen
  zu einem Chip zusammen, lassen sich umbenennen und auflösen.

## Fehler, die sich erklären

Geht ein Schritt nicht, bekommt er in der Zeitleiste ein Abzeichen und im Panel einen Text in Klartext. Wo es geht,
rechnet MyCAD einen **Vorschlag** aus und zeigt ihn als Knopf:

- Rundung oder Fase zu groß → der größte Wert, der noch geht
- Wandstärke zu dick, Gewinde zu kurz, Drehachse durch das Profil, Schraube zu kurz
- betroffene Kanten werden im Modell markiert

Ändert sich das Modell so, dass eine gewählte Kante nicht mehr sicher dieselbe ist, nimmt MyCAD die passendste und
markiert den Schritt orange: **Betroffene Kanten zeigen** oder **Stimmt so**.

## Maße am Modell ändern

Ohne aktives Werkzeug eine Fläche anklicken: Eine Glaskarte an der Fläche zeigt die Maße, die sie erzeugen –
Extrusionslänge der Deckfläche, das Skizzenmaß einer Seitenfläche, Bohrungsdurchmesser, Rundungsradius. Zahl oder Formel
tippen, **Enter**. Hängt das Maß an einem Parameter, ändert sich der Parameter (und die Notiz, in der er steht). Eine
Formel kann man hier nicht überschreiben; dafür den Parameter ändern.

## Befehlssuche

**Strg+K** öffnet die Suche oben in der Mitte. Sie findet Befehle, Körper und Skizzen, versteht Tippfehler, Deutsch und
Englisch und Begriffe aus anderen Programmen (z. B. „pocket“, „pad“, „gewinde“, „passung“, „slicer“). **Enter** startet
den Treffer, zuletzt benutzte stehen oben.
