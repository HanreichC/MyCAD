# Tutorial: Baugruppe mit Gelenken

Du baust einen Hebel, der sich auf einer Grundplatte dreht, verschraubst zwei Teile mit einem Klick und schließt am Ende
eine Kette zu einem Viergelenk.

---

## 1. Grundplatte und Hebel

1. Neues Design, eine Platte 80 × 40 × 5 mm (Skizze, Extrudieren). Sie gehört zum Design selbst und bewegt sich nie.
2. **Neue Komponente** (Bereich ZUSAMMENFÜGEN). Im Browser erscheint sie; alles, was du jetzt baust, gehört zu ihr.
3. In der Komponente eine Lasche 60 × 10 × 3 mm mit einem Loch Ø6 an einem Ende bauen.

## 2. Das erste Gelenk

1. **Gelenk** (Taste **J**).
2. Zuerst etwas an der Komponente anklicken, die sich bewegen soll – die Lochfläche der Lasche.
3. Dann die Stelle, an die sie soll – z. B. eine Bohrung in der Grundplatte oder ihre Oberseite.
4. Im Panel den **Typ** wählen: **Drehung**. Mit **Winkel** drehst du den Hebel.

Typen: **Starr** (fest), **Drehung** (um die Achse), **Schieberegler** (entlang der Achse), **Zylindrisch** (beides),
**Stift-Schlitz** (drehen und im Schlitz gleiten), **Planar** (in einer Ebene), **Kugel** (in alle Richtungen).

## 3. Grenzen und Bewegung

- **Winkel und Weg in Grenzen halten** anhaken und z. B. −45° … 45° eintragen.
- **Animieren** lässt das Gelenk zwischen den Grenzen hin- und herlaufen.
- **Kollisionen zeigen** meldet, wenn Teile sich dabei berühren: „Kollision: Hebel berührt Grundplatte“.

## 4. Ketten

Bau eine zweite Komponente und verbinde sie per Gelenk mit dem Hebel statt mit der Grundplatte. Dreht sich der Hebel,
fährt sie mit.

## 5. Eine geschlossene Kette: das Viergelenk

Ein Viergelenk hat einen festen Steg, eine Kurbel, eine Koppel und eine Schwinge. Die Schwinge hängt am Ende der Koppel
**und** am Steg – die Kette ist geschlossen.

1. Kurbel per **Drehung** an den Steg, Koppel per **Drehung** an die Kurbel, Schwinge per **Drehung** an die Koppel.
2. Dreh die Teile über die Winkel der Gelenke grob so, wie das Viergelenk sitzen soll – das entscheidet, in welche
   Richtung die Kette nachher knickt.
3. Gib der Schwinge ein **zweites Gelenk** zurück zum Steg.

Jetzt rechnet ein Solver die ganze Kette zusammen. Das **erste Gelenk** der Kette (hier die Kurbel) treibt mit seinem
Winkel, die anderen folgen. Müsste ein folgendes Gelenk dabei seine Grenzen verlassen, sagt es das. Passen die Gelenke
gar nicht zusammen (zwei Gelenke wollen das Teil an verschiedene Stellen), bekommt das Gelenk eine Fehlermeldung, statt
still einen Kompromiss zu nehmen.

## 6. Zwei Teile verschrauben

1. Leg eine zweite Platte auf die erste.
2. Klick auf die Oberseite der oberen Platte, dort, wo die Schraube hin soll (oder auf die Kante einer runden Bohrung,
   um genau deren Mitte zu treffen).
3. **Schraube hier** (Bereich ERSTELLEN, beim Knopf Bohrung ▾).
4. Wähle Schraube (ISO 4762 Zylinderkopf, ISO 10642 Senkkopf, ISO 7380 Flachkopf), Größe (M2 bis M12) und was sie
   **unten** hält: Gewindebohrung (Kernloch), Einschmelzmutter oder Mutterfalle. Die passende Normlänge steht schon da.

Oben entstehen Durchgangsloch und Senkung, unten Kernloch, Loch für den Messingeinsatz oder die Sechskant-Tasche.

## 7. Passung zwischen Bolzen und Bohrung

Bohrung und Bolzen anklicken (Strg+Klick), **Passung** (Bereich ÄNDERN). Für den Drucker „3D-Druck normal“ – die Bohrung
wird je Seite 0,2 mm weiter. Für die Werkstatt z. B. **H7/g6**: beide Flächen gehen auf das Mittelmaß ihres
Toleranzfelds, das Spiel steht im Panel („+7 … +41 µm“).

## 8. Gewicht

Körper anklicken, **Messen**: Volumen, **Masse**, Werkstoff und Schwerpunkt. Der Werkstoff kommt aus der Darstellung
(Aluminium gebürstet → Aluminium); in der Darstellung kannst du ihn auch selbst wählen.

---

**Weiter:** [Baugruppen](Baugruppen) · [3D-Druck](3D-Druck) · [Funktionsübersicht](Funktionsuebersicht)
