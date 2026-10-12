<div align="center">

# MyCAD

### Profi-CAD. Federleicht.

Skizzieren. Extrudieren. Fertig.<br>
Die Arbeitsweise von Fusion 360, die Eleganz von Liquid Glass. Für Linux.

<br>

![MyCAD Arbeitsfläche](docs/images/workspace.png)

</div>

<br>

## Liquid Glass. Bis ins letzte Pixel.

Jede Fläche in MyCAD ist aus Glas. Toolbar, Browser, Fensterknöpfe und Inspector schweben über deinem Modell, und das Modell bleibt sichtbar. Ein eigener GPU-Shader zeichnet den Hintergrund weich, bricht ihn am Rand wie eine echte Linse, setzt eine feine Lichtkante und einen sanften Schatten. In Echtzeit, bei jeder Drehung.

Du willst es noch klarer? Mit **Glass: Clear** lässt das Glas noch mehr von deinem Design durch. Lieber kräftiger? **Tinted** ist für dich da.

Meldungen erscheinen als schwebende Glas-Alerts, ohne Fensterrahmen und mit klaren Kapsel-Knöpfen. Die Ecken sind konzentrisch gerundet, die Symbole einfarbig und klar. Hell und dunkel folgen automatisch deinem System.

<br>

## Skizzieren, wie du denkst.

Wähle eine Ebene und leg los. Linie, Polylinie, Rechteck, Kreis, Bogen, Langloch, Polygon, B-Spline, Kegelschnitt, Punkt, Text. Projiziere Kanten aus deinem Modell direkt in die Skizze.

Runden, trimmen, verlängern, teilen, versetzen, spiegeln, anordnen, verschieben, skalieren, alles einen Klick entfernt. Bemaße mit einem einzigen Werkzeug, das weiß, was du meinst. Lege Bedingungen fest: koinzident, horizontal, vertikal, parallel, senkrecht, tangential, gleich, symmetrisch, fixiert.

**Esc** legt das aktive Werkzeug beiseite. **Finish Sketch** bringt dich zurück zu deinem Modell.

<br>

## Klick. Und es ist ein Körper.

Jede geschlossene Fläche deiner Skizze ist ein eigenes Profil. Zwei Kreise ineinander? Klick auf den Ring, und **Extrude** macht daraus ein Rohr. Kein Umweg, kein Nachdenken. Genau wie du es von Fusion kennst.

**Erstellen:** Extrude · Revolve · Sweep · Loft · Rib · Web · Emboss · Box · Cylinder · Sphere · Torus · Coil · Hole · Thread · Pattern · Mirror

**Ändern:** Press Pull · Replace Face · Split Face · Fillet · Chamfer · Shell · Draft · Combine · Split Body · Move · Align · Scale

**Konstruieren:** Offset Plane · Plane at Angle · Midplane · Plane · Axis · Point

**Prüfen:** Measure · Section Analysis

Jeder Schritt landet in der **Timeline**. Geh zurück, ändere eine Maßzahl, und dein ganzes Design passt sich an. Mit **Change Parameters** steuerst du alles über benannte Werte und Formeln.

<br>

## Baugruppen, die zusammengehören.

Lege **Komponenten** an und verbinde sie mit **Joints**. Jede Komponente hat ihre eigenen Körper, Skizzen und ihren eigenen Ursprung, alles in einer einzigen Design-Datei.

<br>

## Alles auf einen Blick.

<div align="center">

![MyCAD Startseite](docs/images/start.png)

</div>

Die Startseite zeigt dir deine zuletzt geöffneten Designs und alles aus deinem Projektordner, jeweils mit großem Vorschaubild. Tipp ein paar Buchstaben in die Suche, und du hast dein Teil gefunden. Ein Klick, und du arbeitest weiter. Über den Home-Knopf bist du jederzeit wieder hier.

<br>

## Deine Hände. Deine Regeln.

Wähle aus zwölf Navigationsstilen, von **Fusion 360** über **SolidWorks** und **Blender** bis **Siemens NX** und **Touchpad**. MyCAD zeigt dir live, welche Taste und welche Geste dreht, schiebt, zoomt und auswählt.

Leg eine Taste als Maustaste fest, zum Beispiel **Shift** als mittlere Maustaste, und navigiere mit einer Hand. Beim Schreiben bleibt Shift natürlich Shift. MyCAD dreht um den Körper unter deinem Cursor, nicht irgendwo in den Raum. Und wer lieber Namen statt Symbole sieht, schaltet einfach **Show tool names** ein.

<br>

## Materialien mit Charakter.

Neue Körper erscheinen in **Space Gray**, satiniert und edel. Lieber **Clay**, **Sierra Blue** oder **Ceramic**? Eine Einstellung genügt, und deine Körper wechseln sofort ihr Kleid. Mit **Appearance** gibst du jedem Körper seine eigene Farbe.

<br>

## Spricht jede Sprache.

**Exportiere** nach STL und 3MF für deinen 3D-Drucker oder nach STEP für jedes andere CAD-Programm. **Importiere** STEP-Modelle sowie DXF- und SVG-Zeichnungen direkt in eine Skizze.

<br>

## Technische Daten

| | |
|---|---|
| **Plattform** | Linux, entwickelt und getestet auf CachyOS mit KDE Plasma (Wayland) |
| **Oberfläche** | Liquid Glass mit GPU-Glas-Shader, hell und dunkel nach Systemeinstellung, Sprache Englisch |
| **Modell** | Parametrisch, mit globaler Timeline, Komponenten und Joints |
| **Skizze** | 12 Zeichenwerkzeuge, 7 Änderungswerkzeuge, 9 Bedingungen, eine smarte Bemaßung |
| **Volumen** | 16 Erstell-, 12 Änderungs- und 6 Konstruktionswerkzeuge |
| **Export** | STL · 3MF · STEP |
| **Import** | STEP · DXF · SVG |
| **Dateiformat** | FCStd (ZIP mit Vorschaubild) |
| **Navigation** | 12 Stile, Tasten als Maustasten, Drehen um den Körper unter dem Cursor |
| **Materialien** | Space Gray · Clay · Sierra Blue · Ceramic |
| **Kern** | FreeCAD mit OpenCascade |
| **Lizenz** | LGPL-2.1-or-later |

<br>

## In zwei Befehlen bereit.

```sh
./install.sh   # baut MyCAD im Podman-Container und legt den Starter `mycad` samt Menüeintrag an
mycad          # los geht's
```

Nichts landet global auf deinem System. MyCAD baut in einem Podman-Container (`.devcontainer/`). Erneutes Ausführen baut nur, was sich geändert hat. Mit `JOBS=8 ./install.sh` legst du fest, wie viele Kerne mitarbeiten (Standard 6, mit niedrigster Priorität).

**Du brauchst:** Linux mit Wayland, Podman und eine GPU mit OpenGL.

<br>

## Für Entwickler.

Der Kern der Oberfläche liegt in [`src/Gui/Shell/`](src/Gui/Shell), die Fusion-Werkzeuge in [`src/Mod/Design/`](src/Mod/Design). Die Symbole erzeugt [`tools/make_icons.py`](tools/make_icons.py).

Die GUI-Tests klicken wie ein Mensch, mit echten Maus- und Tastatur-Events:

```sh
tests/gui/run.sh tests/gui/test_ring.py /tmp/ring   # Protokoll in /tmp/ring.txt, Screenshot in /tmp/ring.png
```

Der Fahrplan steht in [`docs/PLAN.md`](docs/PLAN.md).

<br>

## Herkunft und Lizenz.

MyCAD baut auf [FreeCAD](https://www.freecad.org) auf, dem freien parametrischen CAD-Programm. Danke an alle, die es möglich machen. Mehr dazu in [`docs/UPSTREAM.md`](docs/UPSTREAM.md).

MyCAD steht wie FreeCAD unter der [LGPL-2.1-or-later](LICENSE).

<sub>MyCAD ist ein unabhängiges Projekt und steht in keiner Verbindung zu Apple Inc. oder Autodesk, Inc. Liquid Glass ist eine Designsprache von Apple, Fusion 360 ist eine Marke von Autodesk. Beide Namen dienen hier nur zur Beschreibung von Stil und Arbeitsweise.</sub>
