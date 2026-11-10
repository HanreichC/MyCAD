# Baugruppen

Ein Schritt-für-Schritt-Beispiel steht im [Tutorial: Baugruppe mit Gelenken](Tutorial-Baugruppe).

## Komponenten

**Neue Komponente** (Bereich ZUSAMMENFÜGEN) legt eine Komponente mit eigenem Ursprung, eigenen Körpern und Skizzen an.
Was du baust, landet in der aktiven Komponente. Alles bleibt in einer Datei. Das Design selbst (die Wurzel) bewegt sich
nie.

## Gelenke

**Gelenk** (Taste **J**): zuerst ein Element an der Komponente, die sich bewegt (Fläche, Kante, Bohrung, Punkt), dann
die Stelle, an die sie soll. Zwei ebene Flächen liegen aufeinander; **Umkehren** dreht das um.

| Typ | Bewegung | Werte |
|---|---|---|
| Starr | keine | Winkel, Versatz als feste Lage |
| Drehung | um die Achse | Winkel |
| Schieberegler | entlang der Achse | Versatz |
| Zylindrisch | drehen und schieben | Winkel, Versatz |
| Stift-Schlitz | drehen und im Schlitz gleiten | Winkel, Versatz |
| Planar | in der Ebene schieben und drehen | Versatz, Versatz 2, Winkel |
| Kugel | in alle Richtungen drehen | drei Winkel (Gieren, Nicken, Rollen) |

- **Winkel und Weg in Grenzen halten:** Minimum und Maximum für Winkel und Weg.
- **Animieren:** das Gelenk läuft zwischen seinen Grenzen hin und her.
- **Kollisionen zeigen:** meldet, welche Teile sich dabei berühren.

## Ketten

Ein Teil, das per Gelenk an einem bewegten Teil hängt, bewegt sich mit.

## Geschlossene Ketten

Bekommt eine Komponente ein **zweites Gelenk** (z. B. das letzte Glied eines Viergelenks zurück zum Gestell), ist die
Kette geschlossen. Dann rechnet der Solver (OndselSolver, wie in FreeCADs Assembly) alle Gelenke der Kette zusammen:

- Das **erste Gelenk** der Kette treibt mit seinem Winkel oder Weg, **starre** Gelenke bleiben starr, die übrigen folgen.
- Vor dem Schließen die Teile grob so drehen, wie die Kette sitzen soll – das wählt, wohin sie knickt. Eine ganz gestreckte
  Kette knickt MyCAD selbst.
- **Grenzen** der folgenden Gelenke werden geprüft: müsste der Mechanismus darüber hinaus, steht es am Gelenk.
- Widersprechen sich Gelenke (zwei feste Lagen für dasselbe Teil), bekommt das Gelenk eine Fehlermeldung.
- Alle Gelenktypen gehen in geschlossenen Ketten, auch Stift-Schlitz.

## Messen und Werkstoff

**Messen** zeigt für einen ganzen Körper Volumen, **Masse**, **Werkstoff** und **Schwerpunkt**. Der Werkstoff kommt aus
der **Darstellung** (Holz → Holz, gebürstetes Aluminium → Aluminium); unter Darstellung → Werkstoff kannst du ihn selbst
wählen, dann bleibt er.
