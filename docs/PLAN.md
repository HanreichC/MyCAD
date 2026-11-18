# MyCAD – Masterplan

> Stand: 2026-11-10 (Phase 10 neu) · Basis: FreeCAD 27.1-dev, Commit `e9b474306f`
> Zielplattform: **ausschließlich Linux / CachyOS** (KDE Plasma, Wayland)

---

## 1. Vision

MyCAD ist ein schlankes, parametrisches CAD-Programm für **Skizzen und Volumenkörper**.
Es arbeitet wie **Fusion 360** und sieht aus wie eine **native Apple-App mit Liquid Glass**.
Alles andere (FEM, CAM, BIM, TechDraw, Animation, Rendering, Elektronik …) lassen wir weg.

### Feste Entscheidungen

| Thema | Entscheidung |
|---|---|
| Plattform | Nur Linux (CachyOS). Systempakete statt LibPack. Kein Windows-/macOS-Code. |
| Projektmodell | Wie Fusion: **eine Design-Datei**, beliebig viele **Komponenten**. Jede Komponente hat Bodies, Sketches, Construction-Geometrie und einen eigenen Ursprung. Darüber liegt eine **globale Timeline**. |
| Anordnung | Move/Copy und Align ab sofort. **Joints erst in einer späteren Phase** (Phase 9). |
| Formate | Export: **STL, 3MF, STEP**, Skizzen als **DXF**. Import: **STEP, DXF, SVG** (in eine Skizze). Nativ: `.mycad` (ZIP, auf Basis von FCStd). |
| Theme | **Hell + Dunkel**, folgt dem KDE-Farbschema. |
| Sprache | **Englisch**, gleiche Begriffe wie Fusion. |
| UI-Technik | **Neue Oberfläche in Qt Quick / QML**. Der 3D-Viewport ist ein Item im Scene Graph, damit die Glass-Panels den Viewport-Inhalt echt weichzeichnen und brechen können. |
| Lizenz | FreeCAD steht unter LGPL-2.1+. MyCAD bleibt LGPL-2.1+, alle Lizenz-Header bleiben erhalten. |

---

## 2. Rechercheergebnisse

### 2.1 Fusion 360: Datenmodell

- **Design** (Datei) → **Root Component** → verschachtelte **Components** (Occurrences mit eigener Transformation).
- Eine **Component** enthält: Origin (3 Ebenen, 3 Achsen, Punkt), Sketches, Bodies, Construction (Ebenen, Achsen, Punkte) und Unterkomponenten.
- **Bodies** haben keine eigene Historie. Features erzeugen sie oder verändern sie.
- **Timeline**: eine lineare, globale Feature-Historie am unteren Bildschirmrand. Sie bietet:
  - Rollback-Marker (Zurückspulen und an dieser Stelle einfügen)
  - Drag & Drop zum Umsortieren (sofern Abhängigkeiten es erlauben)
  - Unterdrücken, Bearbeiten, Gruppieren
  - Fehler- und Warnmarkierung pro Feature
  - Ist eine Komponente aktiv, zeigt die Timeline nur deren Features.
- **Operation pro Feature**: `New Body | Join | Cut | Intersect | New Component`, dazu die Auswahl der betroffenen Bodies („Objects to cut“).
- **Browser** links: Document Settings, Named Views, Origin, Sketches, Bodies, Construction, Components. Jeder Eintrag hat ein Sichtbarkeits-Auge.
- **Parameters** (Change Parameters): Benutzerparameter mit Ausdrücken. Jede Bemaßung ist automatisch ein Modellparameter.

### 2.2 Fusion 360: Sketch-Funktionsumfang (Ziel: vollständig)

**Create**
- Line (mit Tangentenbogen per Drag), Centerline / Construction-Toggle
- Rectangle: 2-Point, 3-Point, Center
- Circle: Center Diameter, 2-Point, 3-Point, 2-Tangent, 3-Tangent
- Arc: 3-Point, Center Point, Tangent
- Polygon: Circumscribed, Inscribed, Edge
- Ellipse, Elliptical Arc
- Slot: Center-to-Center, Overall, Center Point, Three-Point Arc, Center Point Arc
- Spline: Fit Point (mit Krümmungsgriffen), Control Point
- Conic Curve (rho-Wert)
- Point
- Text (auch auf Pfad)
- Mirror, Circular Pattern, Rectangular Pattern
- Project / Include: Project, Intersect, Include 3D Geometry, Project to Surface, Intersection Curve
- Sketch Dimension (eine smarte Bemaßung: linear, ausgerichtet, Winkel, Radius, Durchmesser)

**Modify**
- Fillet, Chamfer (Equal Distance / Distance-Angle / Two Distances)
- Offset, Trim, Extend, Break
- Sketch Scale, Move/Copy
- Change Parameters

**Constraints** (12 + 1)
- Horizontal/Vertical, Coincident, Tangent, Equal, Parallel, Perpendicular, Fix/Unfix
- Midpoint, Concentric, Collinear, Symmetry, Curvature (G2)
- Polygon: laut einem Tutorial seit März 2026 neu, bei Autodesk nicht bestätigt; nachrangig

**Sketch Palette**
- Optionen: Look At, Sketch Grid, Snap, Slice, Show Profile, Show Points, Show Dimensions, Show Constraints, Show Projected Geometries, 3D Sketch
- Freiheitsgrade-Anzeige
- Farbcodierung: blau = unterbestimmt, schwarz/weiß = voll bestimmt, rot = überbestimmt
- Automatische Constraints während des Zeichnens, Inferenzlinien, Bemaßungseingabe per Tab direkt am Cursor (Heads-Up Display)

### 2.3 Fusion 360: Solid-Funktionsumfang (Ziel: vollständig, ohne Surface/Form/Plastic)

**Create**
- New Component, Create Sketch
- Extrude, Revolve, Sweep, Loft
- Rib, Web, Emboss
- Hole (Simple, Counterbore, Countersink, Gewinde), Thread (cosmetic / modeled)
- Box, Cylinder, Sphere, Torus, Coil, Pipe
- Pattern (Rectangular, Circular, on Path), Mirror

**Modify**
- Press Pull, Fillet (konstant, variabel, Rule Fillet), Chamfer, Shell, Draft, Scale, Combine
- Offset Face, Replace Face, Split Face, Split Body, Silhouette Split
- Move/Copy, Align, Delete
- Physical Material, Appearance, Change Parameters, Compute All

**Construct**
- Offset Plane, Plane at Angle, Tangent Plane, Midplane, Plane through Two Edges, Plane through Three Points, Plane Tangent to Face at Point, Plane along Path
- Axis: through Cylinder/Cone/Torus, Perpendicular at Point, through Two Planes, through Two Points, through Edge, Perpendicular to Face at Point
- Point: at Vertex, through Two Edges, through Three Planes, at Center of Circle/Sphere/Torus, at Edge and Plane, along Path

**Inspect**
- Measure, Interference, Section Analysis, Center of Mass, Display Component Colors

**Bewusst ausgelassen**: Surface-Workspace, Form (T-Splines), Mesh-Workspace, Plastic-Features (Boss, Snap Fit, Lip, Rest), Sheet Metal, Animation, Render, Simulation, Manufacture, Drawing, Electronics.

### 2.4 Abgleich mit FreeCAD: was es schon gibt, was neu entsteht

| Fusion | FreeCAD-Basis | Aufwand |
|---|---|---|
| Sketch-Solver | `Sketcher/App/planegcs` (sehr gut) | übernehmen |
| Line/Rect/Circle/Arc/Polygon/Ellipse/Slot/Spline/Point/Text | `DrawSketchHandler*` (Text vorhanden) | übernehmen, UI neu |
| Conic Curve | – | **neu** (rationaler B-Spline mit rho) |
| Fillet/Chamfer/Offset/Trim/Extend/Break/Scale/Move/Mirror/Patterns | `DrawSketchHandler{Fillet,Offset,Trimming,Extend,Splitting,Scale,Translate,Rotate,Symmetry}` | übernehmen, Circular Pattern ergänzen |
| Project/Intersect | External Geometry (inkl. Intersection-Modus) | übernehmen |
| Constraints | alle vorhanden außer Polygon | übernehmen |
| Extrude/Revolve/Sweep/Loft/Hole/Helix(Coil)/Primitives | `PartDesign` Pad/Pocket/Revolution/Groove/Pipe/Loft/Hole/Helix/Primitive | **Algorithmen** übernehmen, Datenmodell neu |
| Fillet/Chamfer/Shell(Thickness)/Draft/Patterns/Mirror | `PartDesign` DressUp/Transformed | Algorithmen übernehmen |
| Combine, Split Body, Split Face | `Part` Booleans, `BOPAlgo`/`BRepAlgoAPI_Splitter` | neu, auf OCCT-Basis |
| Press Pull, Offset Face, Replace Face, Delete Face | `PartDesign::Defeaturing`, OCCT `BRepOffset`, `BRepAlgoAPI_Defeaturing` | neu |
| Rib, Web, Emboss, Thread (modeled), Pipe, Scale | teils (Hole hat modellierte Gewinde) | neu |
| Construct (Ebenen/Achsen/Punkte) | `PartDesign` Datum*, `Attacher` | übernehmen, Modi auf Fusion abbilden |
| Measure | `Mod/Measure` | übernehmen, UI neu |
| STEP | `Mod/Import` (`ReaderStep`/`WriterStep`) | übernehmen |
| DXF | `Mod/Import/App/dxf` (C++) | übernehmen, Ziel: Skizze |
| SVG-Import | nur Python in Draft | **neu** (C++-Parser → Sketch-Geometrie) |
| STL/3MF | `Mod/Mesh` Exporter + `MeshPart` Tessellierung | Teilmenge übernehmen |
| Topologische Benennung | `Part::TopoShape` Element-Maps (TNP-Fix seit FreeCAD 1.0) | übernehmen, zentral |

### 2.5 Liquid Glass / Apple HIG: Designprinzipien für MyCAD

1. **Inhalt zuerst.** Der 3D-Viewport füllt das ganze Fenster. Alle Bedienelemente **schweben** als Glass-Ebene darüber, es gibt keine Docks und keine grauen Rahmen.
2. **Glass nur für die Navigations- und Steuerebene** (Toolbar, Browser, Timeline, Inspector, Popover). Inhalte selbst sind nie aus Glas.
3. **Kein Glass auf Glass.** Elemente in einem Panel nutzen Fill/Vibrancy, kein zweites Glas.
4. **Varianten**: *Regular* ist der Standard (adaptiv, Blur, Lensing). *Clear* nur über ruhigem Inhalt, mit Dimming.
5. **Konzentrische Geometrie.** Eckradien sind ineinander verschachtelt (Fenster 26 → Panel 20 → Control 12 → Chip 8). Kapsel-Formen für Buttons.
6. **Farbe sparsam.** Eine Akzentfarbe (System-Blau oder KDE-Akzent) nur für primäre Aktionen und die Auswahl. Tinting nur für das prominenteste Element.
7. **Morphing & Bewegung.** Panels gehen fließend ineinander über, z. B. wird der Toolbar-Button zum Popover. Animationen sind federbasiert (Spring). *Reduce Motion* wird respektiert.
8. **Barrierefreiheit.** *Reduce Transparency* ersetzt Glass durch opake Flächen. Kontrast mindestens WCAG AA.
9. **Typografie.** Klare Hierarchie (Large Title, Headline, Body, Caption). SF Pro darf nur auf Apple-Plattformen genutzt werden, deshalb verwenden wir **Inter** (sehr ähnlich, OFL) und **JetBrains Mono / SF-Mono-Ersatz** für Zahlenwerte.
10. **Icons.** SF Symbols dürfen außerhalb von Apple-Plattformen nicht genutzt werden. Wir bauen ein **eigenes Icon-Set im SF-Symbols-Stil** (gleichmäßige Strichstärke, auf SVG-Basis; Grundlage: Lucide/Phosphor, MIT) und ergänzen CAD-spezifische Symbole selbst.

---

## 3. Zielarchitektur

```
MyCAD/
├── CMakeLists.txt            # neu, schlank, nur Linux
├── cmake/                    # aufgeräumte Helper (nur Linux, System-Pakete)
├── src/
│   ├── 3rdParty/             # PyCXX, FastSignals, GSL, json, lru-cache, zipios++, (OndselSolver → Phase 9)
│   ├── Base/                 # aus FreeCAD (Kernel: Typen, Parameter, Quantity, Units, Python)
│   ├── App/                  # aus FreeCAD (Dokument, Properties, Expressions, Transactions)
│   ├── Gui/                  # aus FreeCAD, stark entschlackt: Selection, ViewProvider, Command, Coin-Integration
│   ├── Main/                 # neuer Einstiegspunkt `mycad`
│   ├── Mod/
│   │   ├── Material/         # Abhängigkeit von Part (Appearance/Physical Material)
│   │   ├── Part/             # OCCT-Wrapper, TopoShape, Attacher
│   │   ├── Sketcher/         # Solver + Sketch-Objekt + Edit-Mode-Logik
│   │   ├── Design/           # NEU: Fusion-Datenmodell (Component, Body, Timeline, Features)
│   │   ├── Import/           # STEP, DXF
│   │   ├── Mesh/ MeshPart/   # nur Exporter STL/3MF + Tessellierung (stark reduziert)
│   │   └── Measure/
│   └── UI/                   # NEU: komplette Qt-Quick-Oberfläche
│       ├── Viewport/         # Coin-Rendering als QQuickItem (OpenGL-RHI)
│       ├── Glass/            # Liquid-Glass-Shader, Materials, Tokens
│       ├── Components/       # QML-Controls (Button, Segmented, Field, Popover, Menu …)
│       ├── Panels/           # Toolbar, Browser, Timeline, Inspector, Sketch Palette, HUD
│       ├── Bridge/           # C++↔QML: Document-, Selection-, Command-Modelle
│       └── Resources/        # Icons, Fonts (Inter), Sounds
├── data/                     # Templates, Default-Parameter
├── tests/
├── packaging/arch/PKGBUILD   # CachyOS-Paket
└── docs/
```

### 3.1 Das neue Datenmodell `Mod/Design`

- **`Design::Component`** (Grundlage: `App::Part`/`GeoFeatureGroupExtension`): Origin, Placement und Kinder. Die Root Component wird automatisch angelegt.
- **`Design::Body`**: ein leichtes Objekt mit Name, Farbe, Material und Sichtbarkeit. Seine `Shape` ist das Ergebnis des **letzten Features, das ihn verändert hat** (bis zum Rollback-Marker).
- **`Design::Feature`** (Basisklasse): `Operation` (NewBody/Join/Cut/Intersect/NewComponent), `TargetBodies`, `Previous` (globale Verkettung = Timeline), `Suppressed`, `Group` (Timeline-Gruppe).
  - Jedes Feature rechnet auf dem **Body-Zustand** seiner Komponente (`map<BodyId, TopoShape>`) und gibt den neuen Zustand aus.
  - Algorithmen stammen aus `PartDesign` (Prism, Revolution, Pipe, Loft, Hole, Fillet …) und werden in wiederverwendbare Funktionen ausgelagert.
- **`Design::Timeline`**: ein Dokument-Singleton mit geordneter Feature-Liste und Marker-Index. Er kümmert sich um Rollback (Recompute bis Marker), Umsortieren (Abhängigkeitsprüfung über DAG) und Gruppen.
- **Sketches** bleiben `Sketcher::SketchObject`, angehängt über `Attacher` an Origin-Ebenen, Construction-Ebenen oder Body-Flächen.
- **Parameters**: `App::Expression` und benannte Benutzerparameter (Dokument-Varset) ersetzen das Spreadsheet.
- **Warum nicht einfach `PartDesign::Body` pro Body?** PartDesign erzwingt eine Feature-Kette pro Body. Fusion-Operationen über mehrere Bodies (ein Extrude schneidet drei Bodies, Combine, Split Body) und die globale Timeline lassen sich darauf nur mit fragilen Hilfskonstrukten abbilden. Das eigene Modell ist sauberer und wartbarer.

### 3.2 Die neue Oberfläche `src/UI`

- **Fenster**: `QQuickWindow` mit OpenGL-RHI (Coin braucht Legacy-GL). Rahmenlos, eigene Titelleiste mit Traffic-Light-ähnlichen Fensterknöpfen links (abschaltbar → KDE-Deko). KWin-Blur über `KWindowEffects` (KF6) für Fensterbereiche ohne Viewport.
- **Viewport**: `CoinViewportItem : QQuickFramebufferObject`. Er nutzt `SoRenderManager`/`SoEventManager` aus Quarter wieder und rendert in ein FBO. Die Textur steht den Glass-Shadern zur Verfügung.
- **Liquid-Glass-Shader** (`MultiEffect` reicht nicht → eigener `ShaderEffect`/QSB):
  - Gaußscher Blur (zweistufig, downsampled), Lensing-Verzerrung an den Rändern (Normalen aus SDF der Rounded Rect), Specular-Highlight-Kante, adaptive Tönung (Hell/Dunkel abhängig von der Luminanz dahinter), leichter Schatten.
  - Fallback *Reduce Transparency*: opake Fläche.
- **Layout** (alles schwebende Glass-Panels über dem Viewport):
  - **Oben**: Kapsel-Toolbar mit Workspace-Segmenten `Sketch | Solid | Construct | Inspect`, darunter kontextabhängige Werkzeuggruppen, rechts Suche (⌘K-artige Command Palette mit `Ctrl+K`/`S`).
  - **Links**: Browser (Components, Bodies, Sketches, Construction), einklappbar.
  - **Rechts**: Inspector. Er ersetzt FreeCADs Task-Panels: Feature-Parameter, Sketch Palette, Eigenschaften der Auswahl.
  - **Unten**: Timeline als Glass-Kapsel mit Feature-Chips, Marker, Playback-Steuerung.
  - **Rechts oben**: ViewCube (neu gezeichnet, Glass) und Navigationsleiste.
  - **Am Cursor**: Heads-Up-Eingabe für Bemaßungen beim Zeichnen, Marking Menu (Radial-Menü) per Rechtsklick wie in Fusion.
- **Navigation**: Fusion-Mausbelegung als Standard (Mitte = Pan, Shift+Mitte = Orbit, Rad = Zoom zum Cursor), Alternativen umschaltbar.
- **Rendering-Look**: Modern statt CAD-Standard. Weiche Umgebungsbeleuchtung (Image-Based-artig über Matcap/Hemisphere-Licht), feine Silhouetten-Kanten, Ambient Occlusion (SSAO als Post-Pass), dezenter Bodenschatten, Hintergrund-Verlauf passend zum Theme, Auswahl-Highlight in der Akzentfarbe mit weichem Glow.
- **Bridge**: `DocumentModel` (QAbstractItemModel für Browser), `TimelineModel`, `SelectionModel`, `CommandRegistry` (wickelt `Gui::Command` ein), `InspectorModel` (Property-Schema → QML-Formulare).

---

## 4. Stand und Plan

### 4.1 Was steht (Stand 2026-11-13)

Die Phasen 0 bis 8 des ursprünglichen Plans sind erledigt, nur anders als geplant: Die Oberfläche ist kein QML-Neubau,
sondern Glass-Panels über dem vorhandenen 3D-Viewer (Entscheidung vom 2026-10-10). Die Lücken vom 2026-11-10 hat
Phase 10 geschlossen (Verweise in Klammern).

| Bereich | Stand | Noch offen |
|---|---|---|
| Fundament | Build im Container, AppImage per CI, `.mycad`, Einstellungen, Deutsch, Hilfe; Tests (C, H, G) in der CI, rot = kein Release; Container auf festem Datum gepinnt (10.0) | – |
| Oberfläche | Liquid Glass, Hell/Dunkel, Toolbar, Browser, Inspector, Timeline, ViewCube, Startseite, Notizen, Scribble, Materialien; Befehlssuche (L10); Timeline umsortieren und gruppieren (L7); Fehler mit Erklärung und Reparaturvorschlag (10.2); Maße an der Fläche ändern (10.3); Notiz als Parameterliste (10.4); Rotstift (10.8) | – |
| Datenmodell | Komponenten, Bodies, globale Timeline, Rollback, Suppress, Parameter, topologische Benennung; verlorene Bezüge werden gemeldet statt still auf alte Kantennummern zu fallen (10.2); immer gespeichert, Versionen, Varianten (10.7) | – |
| Skizze | 12 Zeichen-, 7 Ändern-Werkzeuge, 9 Constraints, Bemaßung am Cursor, Conic; große DXF-Importe (10.000 Elemente) bearbeitbar (10.9) | bei sehr großen Skizzen je neuer Linie noch ~0,3 s (2026-11-17 um 25–30 % schneller: Hüllquader für den Maßstab zwischengespeichert, kleine Diagnose-Blöcke ohne eigenen Thread, Redundanz-Prüfung bei einem Auto-Constraint an freier Geometrie übersprungen, Parameter-Tabelle als Hash). Rest: FreeCAD baut den Solver je Änderung über die ganze Skizze neu auf; schneller ginge nur ein inkrementeller Solver (großer Umbau). Profile folgen nach dem Verlassen im Hintergrund (10.9) |
| Körper | 16 Create-, 12 Modify-, 6 Construct-Werkzeuge, Measure, Section; Extrude mit allen Ausdehnungen, Verjüngung, dünnwandig (L1); Bohrung nach Norm (L2); Gewinde nach Norm, auch zum Drucken (L3); Spiegeln/Muster/Drehen an freien Bezügen und entlang Pfad (L4); Rundung variabel, Fasen-Varianten, Tangentenkette (L5); Passung, „Schraube hier“, Einschmelzmuttern (10.5) | – |
| Baugruppe | Joints Rigid/Revolute/Slider/Cylindrical, Planar, Kugel, Pin-Slot; Ketten, Grenzen, Bewegen und Animieren mit Kollisionsanzeige; geschlossene Ketten über OndselSolver (L6) | – |
| Austausch | STL, 3MF, STEP, DXF raus; STEP, DXF, SVG rein; 3MF mit Farben, Namen und Auflösung, STEP mit Farben und Komponenten (L8); Drucken öffnet den Slicer (10.6) | – |
| Prüfen | Messen mit Volumen; physisches Material, Masse und Schwerpunkt (L9); Druckansicht mit Überhang, Bett und Wanddicke (10.6) | – |

### 4.2 Phase 10: Neu gedacht

Ziel: MyCAD wird so leicht wie Papier, ohne an Präzision zu verlieren. Die Lücken aus 4.1 werden zuerst geschlossen,
danach kommen sieben neue Ideen. Notizen und Scribble waren der Anfang.

**Reihenfolge** (nach Abhängigkeiten, nicht nach Nummer):

| Etappe | Inhalt | baut auf |
|---|---|---|
| 10.0 | Test-Fundament | – |
| 10.1 | Lücken schließen | 10.0 |
| 10.2 | Idee 6: Fehler, die sich erklären und reparieren | 10.1 (alle neuen Features nutzen das Fehlermodell) |
| 10.3 | Idee 2: Fläche antippen, Zahl ändern | 10.2 |
| 10.4 | Idee 3: Die Notiz ist die Parameterliste | 10.3 (Maß am Modell ↔ Parameter ↔ Notiz) |
| 10.5 | Idee 4: Werkzeuge für den Zweck | 10.1 (Normtabellen), 10.2 |
| 10.6 | Idee 5: Der Druck gehört in den Viewport | 10.1 (3MF mit Farben) |
| 10.7 | Idee 7: Keine Angst (Speichern, Versionen, Varianten) | 10.0 |
| 10.8 | Idee 1: Handschrift ist der Befehl | 10.1, 10.3, 10.5 |
| 10.9 | Große Skizzen (DXF-Import) bearbeitbar | – |

**Testarten** (jede Funktion bekommt alle, die passen):

- **C** Logik-Check ohne FreeCAD: `tests/<name>_check.cpp`, header-only Logik, `g++ -std=c++20 -I src …` (wie die Scribble-Checks).
- **H** Headless-Test: `tests/design/test_<name>.py` mit `FreeCADCmd` und `unittest` aus der Standardbibliothek. Prüft
  Geometrie über Volumen, Flächen, Maße, Gültigkeit; deckt Speichern/Laden und Undo ab.
- **G** GUI-Test: `tests/gui/test_<name>.py`, echte Klicks wie bisher, in CI unter Xvfb.
- **Fehlerklassen statt Einzelfälle** (seit 2026-11-17, nach "Monitor Light"):
  - Jeder H-Test prüft am Ende `model_problems`: kein Abhängigkeitskreis, nach dem Neuberechnen bleibt nichts liegen.
  - `tests/design/test_fuzz.py`: zufällige, per Seed reproduzierbare Arbeitsabläufe auf den Wegen der Oberfläche,
    Invarianten nach jedem Schritt. Länger suchen: `FUZZ_SEEDS=200 FUZZ_STEPS=25`, echte Dateien: `FUZZ_FILES=a.mycad:b.mycad`,
    Fund nachstellen: `FUZZ_SEED=n`.
  - Log-Wächter in `tests/gui/run.sh`: Kreis, Endlos-Neuberechnung, Rechnen im Rechnen, Absturz, Python-Traceback im Log
    = FAIL (absichtliche: `# log-ok: <Text>` im Test).
  - `test_reentrancy`: Klicks und Esc mitten in einer langen Neuberechnung.
- Jede neue Oberfläche geht durch MyStyle § 14 (Hell, Dunkel, Kontrast, Transparenz und Bewegung reduziert, Deutsch).

**Fertig heißt** für jedes Paket: alle Tests grün (auch die alten), Hilfe-Artikel EN/DE, Übersetzungen, README-Abschnitt
wenn sichtbar für Nutzer, ein Commit auf `main`.

---

#### 10.0 Test-Fundament · erledigt (2026-11-10)

| # | Aufgabe | Umsetzung |
|---|---|---|
| 0.1 | Headless-Läufer | `tests/design/run.sh`: startet `FreeCADCmd` im Container, führt alle `test_*.py` aus, Exit-Code ≠ 0 bei Fehler |
| 0.2 | GUI-Tests ohne Desktop | `tests/gui/run.sh` nimmt ohne `WAYLAND_DISPLAY` Xvfb (`QT_QPA_PLATFORM=xcb`); `run_all.sh` sammelt `FAIL`-Zeilen |
| 0.3 | CI | `release.yml`: Unit-Tests (ctest), C-Checks, H-Tests und eine GUI-Auswahl vor dem AppImage. Rot = kein Release |
| 0.4 | Gepinnter Container | `Dockerfile` auf festes Datum aus dem Arch Linux Archive; Aktualisieren = Datum ändern, Tests laufen lassen |
| 0.5 | Grundlinie | alle vorhandenen GUI-Tests laufen lassen, Ergebnis festhalten; rote Tests vor 10.1 reparieren oder begründen. Ergebnis: Absturz bei Skizzen-Offset (ungeprüfte Geometrie) behoben, Toolbar bleibt bei eingeklappter Seitenleiste mittig, Xvfb-Displays kollidierten, vier Tests waren veraltet, Bildrate und Zwei-GPU-Test gelten nur auf passender Hardware |

Tests: H `test_smoke.py` (Design anlegen, Extrude, Speichern, Laden, gleiche Volumen). Der Läufer selbst ist der Test für 0.1–0.3.

---

#### 10.1 Lücken schließen

**L1 Extrude: Ausdehnungen, Verjüngung, dünnwandig** · erledigt (2026-11-10)
- `Extent` bekommt „To Object“ (Fläche, Ebene, Body) und „All“ (durch alles, aus der Bounding Box statt 10 m).
- `TaperAngle` (beide Seiten, über `makeElementDraft` bzw. `makeElementPrismUntil`), `Thin` mit `Thickness` und Seite (innen, außen, Mitte) für offene und geschlossene Profile.
- Wiederverwendung: `TopoShape::makeElementPrismUntil`, `makeElementDraft`, `makeElementThickSolid`.
- Tests H: Volumen je Modus gegen Formel (Quader, Zylinder, Kegelstumpf bei Verjüngung); „To Object“ an schräger Fläche; „All“ durch zwei Bodies; dünnwandiges Rohr aus Kreis; Fehler bei Ziel, das nicht getroffen wird; Speichern/Laden; alte Dateien ohne neue Properties laden.
- Tests G: Extrude-Dialog stellt Modus und Ziel um, Vorschau aktualisiert sich.

**L2 Bohrung nach Norm** · erledigt (2026-11-10)
- Typen: Einfach, Durchgang (ISO 273 fein/mittel/grob), Gewinde (ISO metrisch Regel/Fein, UNC/UNF), dazu Senkung und Flachsenkung aus der Schraubennorm (ISO 4762, ISO 10642).
- Tabellen aus `PartDesign::Hole::threadDescription` und `metricHoleDiameters` (schon im Repo), nicht kopieren.
- Gewindebohrung modelliert oder kosmetisch (nur Kernloch plus Kennzeichnung im Browser).
- „Durch alles“ aus der Bounding Box der Ziel-Bodies.
- Tests H (die Tabellen kommen aus PartDesign, also mit FreeCAD): Tabellen-Lookup M5, M6, M8, 1/4 (Kernloch, Durchgang, Kopfmaße). H: Volumen der Bohrung gegen Formel; Durch alles bei 3 m großem Body; Senkung koaxial; Gewindebohrung gültiges Solid. G: Norm und Größe im Dialog wählen.

**L3 Gewinde nach Norm, auch zum Drucken** · erledigt (2026-11-10)
- ISO-Profil mit Abflachungen (H/8, H/4) statt V-Profil, Größen aus derselben Tabelle wie L2 (Auto nach Durchmesser), Links/Rechts. Läuft über die ganze Fläche und endet dort bündig (kein Auslauf).
- Gefunden beim Testen: das alte Gewinde schnitt gar nichts (Wendel mit `makeHelix` legt das Profil auf den doppelten Radius); der alte GUI-Test prüfte nur Logausgaben.
- `Clearance`: Spiel je Flanke (0 = Norm; Preset „3D-Druck“ 0,2 mm), wird in 10.5 wiederverwendet.
- Tests H: Außen- und Innengewinde M8 ineinander: mit Spiel keine Überschneidung (Common-Volumen 0), ohne Spiel und mit Übermaß Überschneidung > 0; Profiltiefe 0,6134·P ± 1 %; gültiges Solid für M3 bis M24; zu kurze Fläche gibt Fehler mit Lösung.

**L4 Freie Bezüge für Spiegeln, Muster, Drehen** · erledigt (2026-11-10)
- Neues `Reference` (LinkSub) bei Mirror, Pattern (Richtung 1/2, Achse), Move (Drehachse): Ursprungsebene/-achse, Konstruktionsebene/-achse, ebene Fläche, gerade Kante, Zylinderfläche (Achse). Ist es leer, gilt das alte Enum (alte Dateien laden unverändert).
- Muster entlang Pfad (Kante oder Skizze) als dritter Typ.
- Tests H: Spiegeln an schräger Konstruktionsebene (Schwerpunkt gespiegelt), an Körperfläche; Muster entlang Kante unter 30°; kreisförmig um Zylinderachse; entlang Bogen; alte Datei mit Enum lädt gleich.

**L5 Rundung und Fase** · erledigt (2026-11-10); die Tangentenkette macht OCCT selbst, ein Schalter entfällt
- Tangentenkette: eine Kante wählt alle tangential anschließenden (Schalter, Standard an, wie in Fusion).
- Rundung variabel: Start- und Endradius je Kante.
- Fase: „Zwei Abstände“ und „Abstand und Winkel“, Seite tauschen.
- Tests H: Kette an einem abgerundeten Rechteck-Profil (8 Kanten aus 1); variable Rundung gültig und Volumen zwischen den beiden konstanten; Fasen-Varianten gegen Formel am Quader.

**L6 Baugruppe bewegt sich** · erledigt (2026-11-10): Ketten, Grenzen, Pin-Slot/Planar/Kugel, Animieren mit Kollisionsanzeige; geschlossene Ketten (Viergelenk) über OndselSolver (FreeCAD-Fork als Submodul, mit dem Benutzer abgestimmt) hinter der dünnen Schnittstelle `AssemblySolver.h`, damit ein anderer Solver (z. B. Project Chrono) nur diese Datei ersetzt. Der erste Joint der Kette treibt, die übrigen folgen; offene Ketten rechnen wie bisher direkt. Widersprüche meldet eine Nachprüfung (der Solver selbst liefert dann einen Kompromiss); gestreckte Ketten knicken über Startversuche ±10°/±30°. Pin-Slot schließt Schleifen (Punkt auf Linie + parallele Achsen); Grenzen der folgenden Joints werden nach dem Lösen geprüft und gemeldet
- Joints werden in Abhängigkeitsreihenfolge gelöst; Konflikte (zwei Joints bewegen dieselbe Komponente gegensätzlich) melden statt still überschreiben.
- Grenzen (min/max) für Winkel und Weg; neue Typen Planar, Ball, Pin-Slot.
- Bewegen: Joint im Viewport ziehen oder „Animieren“ (Hin und Her zwischen den Grenzen), Kollision optional rot.
- Geschlossene Ketten (Viergelenk) brauchen einen echten Solver: **Entscheidung** OndselSolver aus FreeCAD übernehmen (LGPL, wie MyCAD). Erst wenn Ketten ohne Schleifen sauber laufen.
- Tests H: Kette aus drei Komponenten folgt; Grenze klemmt den Wert; Konflikt meldet Fehler; Viergelenk schließt sich (nach Solver). G: Joint ziehen dreht die Komponente, Animation läuft und stoppt mit Esc.

**L7 Timeline** · erledigt (2026-11-10)
- Ziehen zum Umsortieren, nur wenn die Abhängigkeiten es erlauben (sonst springt der Eintrag zurück, Hinweis nennt die Abhängigkeit).
- Gruppen: Einträge markieren, „Gruppieren“, auf- und zuklappen, umbenennen.
- Tests H: gültiges Umsortieren gibt dieselben Volumen; ungültiges wird abgelehnt; Gruppe übersteht Speichern/Laden; Undo stellt die Reihenfolge wieder her. G: Ziehen mit der Maus.

**L8 Austausch** · erledigt (2026-11-10); STEP-Farben über ImportGui (nur mit Oberfläche prüfbar)
- 3MF mit Farben je Body (3MF Materials-Erweiterung) und Objektnamen; Auflösung grob/normal/fein (Abweichung 0,1/0,02/0,005 mm, Winkel) im Export-Dialog und in den Einstellungen.
- STEP über `ImportGui` (Farben, Komponentenstruktur, Namen).
- Tests H: 3MF entpacken und XML prüfen (Farben, Anzahl Objekte, Dreiecke steigen mit der Auflösung); STEP exportieren und wieder einlesen: gleiche Anzahl Komponenten, Farben, Volumen.

**L9 Physisches Material und Gewicht** · erledigt (2026-11-10)
- Jeder Body hat ein physisches Material (Dichte aus `Mod/Material`); Appearance schlägt das passende vor (Walnuss → Holz, Alu eloxiert → Aluminium, PLA → PLA). Messen zeigt Masse und Schwerpunkt.
- Tests H: 10-cm-Würfel Aluminium = 2,70 kg ± 1 %; Wechsel der Appearance setzt das Material, eigene Wahl bleibt. G: Messen zeigt Masse.

**L10 Befehlssuche** · erledigt (2026-11-10); `S` ist schon „Skizze“, daher nur `Strg+K` und die Lupe in WERKZEUGE
- `S` oder `Strg+K` öffnet eine Suche (Glas-Popover): Befehle EN/DE mit Synonymen („Bohrung“, „Loch“, „hole“), zuletzt benutzte oben, Tastenkürzel daneben; Objekte im Design (Bodies, Skizzen, Parameter) als zweite Gruppe.
- Tests C: Ranking (Präfix vor Teilwort vor Synonym, Umlaute, Tippfehler um 1 Zeichen). G: Tippen „boh“, Enter startet Bohrung; Esc schließt; Tastatur und Fokusring.

**L11 Plan aktuell halten** – dieses Dokument nach jeder Etappe nachziehen.

---

#### 10.2 Idee 6: Fehler, die sich erklären und reparieren · erledigt (2026-11-10); markiert wird über die Auswahl (Akzentfarbe) statt Rot, Text und Symbol tragen die Bedeutung

- **Fehlermodell:** Features melden `Code`, Text und Vorschläge (`Fix`: Beschriftung, Property, Wert). Die Timeline zeigt sie in einem Glas-Popover am Eintrag, der Viewport hebt die betroffenen Kanten/Flächen rot hervor (mit Symbol, nie nur Farbe).
- **Vorschläge mit Rechnung:** Rundung/Fase zu groß → größter Wert, der noch geht (Bisektion, max. 12 Versuche; `ponytail:` Kosten = 12 Rundungen, reicht für einzelne Features). Shell zu dick, Gewinde zu kurz, Drehachse durch das Profil, Ziel nicht getroffen (Richtung tauschen), leeres Ergebnis bei Cut (Operation prüfen).
- **Bezüge:** Heute fällt `DressUp::elements` still auf die alte Kantennummer zurück, wenn ein Name verloren geht. Neu: Rückfall wird erkannt, das Feature bekommt eine Warnung „Bezug unsicher“ und Kandidaten (gleicher Typ, nächste Lage, ähnliche Länge). „War es diese Kante?“ zeigt sie zur Wahl.
- Tests H: je Fehlerart ein Aufbau, der den Fehler auslöst; Code und Vorschlag stimmen; Vorschlag anwenden macht das Feature gültig. Bezug: Fillet auf Kante, davor ein Feature einfügen, das die Topologie ändert → Warnung statt falscher Kante; Kandidat wählen repariert. G: Popover öffnet sich am roten Eintrag, Klick auf den Vorschlag behebt den Fehler, Undo nimmt ihn zurück.

#### 10.3 Idee 2: Fläche antippen, Zahl ändern · erledigt (2026-11-10); Erzeuger einer Fläche über die Kette der Features und die Trägerfläche statt über die Element-Map (MyCADs Formen tragen keine Objekt-Tags)

- **Treibende Maße finden** (App, ohne GUI): `Design::drivingDimensions(body, "FaceN")` liefert die Werte, die diese Fläche erzeugen: Deckfläche eines Extrudes → `Distance`; Seitenfläche → Bemaßungen der Skizzenkante, aus der sie gezogen wurde; Bohrungswand → Durchmesser; Rundungsfläche → Radius; Press-Pull-Fläche → Abstand; Grundkörper → Länge/Breite/Höhe/Radius. Weg über die Element-Map (Entstehungsgeschichte der Fläche).
- **Am Modell:** Klick auf eine Fläche ohne aktives Werkzeug zeigt die Maße als kleine Glas-Chips an der Fläche. Klick (oder Tab) öffnet das Feld, Enter rechnet neu (eine Transaktion, Undo), Esc bricht ab. Ausdrücke und Parameter-Namen gehen; ist das Maß an einen Parameter gebunden, ändert sich der Parameter (und in 10.4 die Notiz).
- Timeline bleibt für Fortgeschrittene, man muss sie nicht mehr kennen.
- Tests H: Quader aus Extrude: Deckfläche → Distance; Seitenfläche → Skizzenmaß; Bohrung → Durchmesser; Rundung → Radius; Grundkörper; Wert setzen ändert Volumen wie erwartet; nach Einfügen eines Features davor findet es noch dieselben Maße; Maß mit Parameter gibt den Parameter zurück. G: Fläche klicken, Chip erscheint, „30“ tippen, Enter, Körper ändert sich, Strg+Z stellt zurück; Tastatur-Bedienung (Tab, Esc).

#### 10.4 Idee 3: Die Notiz ist die Parameterliste · erledigt (2026-11-10); abgeglichen wird bei Enter und beim Verlassen der Notiz, nicht bei jedem Tastendruck; Werte stehen als „40.00 mm“ wie in den Rechenzeilen

- Zeilen `Name = Ausdruck` in einer Notiz (ohne `=` am Ende) legen Parameter an oder ändern sie. Rechenzeilen (`… =`) bleiben wie heute.
- Hinter einer Parameterzeile mit Formel steht der Wert grau („Breite = Wand * 20 → 40 mm“). Doppelte Namen in zwei Notizen: die zweite Zeile bekommt Fehlersymbol und Text.
- Umlaute erlaubt: „Wandstärke“ wird intern `Wandstaerke`, alle Maßfelder verstehen beide Schreibweisen.
- Zeile löschen: Parameter verschwindet, außer er wird noch benutzt; dann bleibt er, und die Notiz zeigt, wo er benutzt wird (kein stiller Datenverlust).
- Zwei Richtungen: Ändert man den Parameter im Dialog oder am Modell (10.3), ändert sich die Zeile in der Notiz. Der Parameter-Dialog zeigt die Quelle („Notiz 2“).
- Tests C: Zeilen-Parser (Definition, Rechnung, Kommentar, Dezimalkomma, Einheiten, Umlaute, ungültige Namen, Leerzeichen). H: Notiztext → Parameter; Formel zwischen Parametern; Feature folgt; Löschen eines benutzten Parameters bleibt erhalten; Konflikt; Rückweg Parameter → Notiz; Speichern/Laden. G: in Notiz tippen, Körper ändert sich; Wert am Modell ändern, Notiz zeigt den neuen Wert.

#### 10.5 Idee 4: Werkzeuge für den Zweck · erledigt (2026-11-10); Passung ist ein Feature über bis zu zwei Bodies und setzt beim Druck nur die Bohrung (sonst die Welle bzw. ebene Flächen) zurück; „Schraube hier“ nimmt einen Klick auf die Oberseite oder eine Kreiskante, das untere Teil ist der nächste Body auf der Achse; ISO 7380 als Kopftabelle ergänzt; Einschmelzmuttern M2–M8 nach gängigen Messingeinsätzen

- **Passung:** zwei Flächen (Welle/Bohrung oder zwei ebene Flächen) wählen, Passung aussuchen: ISO 286 (H7/g6, H7/h6, H7/k6, H7/p6, H8/f7) oder 3D-Druck (eng/normal/locker, Werte in den Einstellungen, Standard 0,1/0,2/0,3 mm je Seite). Ein Timeline-Feature versetzt die Fläche auf das Mittelmaß und zeigt das Spiel an.
- **Schraube hier:** Punkt oder Achse durch zwei Komponenten wählen, Schraube aussuchen (ISO 4762, ISO 10642, ISO 7380; M2 bis M12; Länge vorgeschlagen). Ein Feature macht in der oberen Komponente Durchgang plus Senkung, in der unteren Gewinde, Einschmelzmutter-Loch (3D-Druck) oder Mutterfalle.
- **Druckgewinde:** Gewinde (L3) mit Preset „3D-Druck“ und Hinweis bei zu kleiner Steigung.
- Tests C: ISO-286-Tabelle (Ø20 H7 = 0/+21 µm, g6 = −7/−20 µm, Bereichsgrenzen 3/6/10/18/30/50/80 mm). H: Passung auf Welle Ø20 → gemessener Durchmesser im Toleranzfeld; 3D-Druck-Passung vergrößert die Bohrung um 2 × Spiel; Schraube M4 ISO 4762: Bohrungen koaxial, Durchmesser laut Tabelle, Einschmelzmutter-Loch; gleiche Funktion über Komponentengrenzen. G: Werkzeug aus der Befehlssuche, zwei Flächen klicken, Passung wählen.

#### 10.6 Idee 5: Der Druck gehört in den Viewport · erledigt (2026-11-10); Überhang, Bett und Wanddicke rechnet die App je Dreieck (`Design.printCheck`), die Ansicht legt gemusterte Overlays darüber (Schraffur, Punkte, Kreuz) statt den Material-Shader umzubauen; Grenzen in den Einstellungen; der Druck-3MF liegt mit der gewählten Unterseite nach unten; Slicer: OrcaSlicer, Bambu Studio, PrusaSlicer, UltiMaker Cura, auch als Flatpak (Datei über das Dokumenten-Portal) und AppImage, gestartet ohne MyCADs Bibliothekspfade

- **Druckansicht** (Schalter in der Toolbar, wie ein Material): Überhänge über dem Grenzwinkel (Standard 45°) rot schraffiert, Flächen auf dem Bett grün, Wände unter der Mindestdicke (Standard 0,8 mm) gelb; Legende mit Text. Druckrichtung wählbar („Diese Fläche nach unten“).
- Überhang im Shader (`BodyShading`), Wanddicke auf der CPU per Strahl gegen die Normale je Tessellierungspunkt (`ponytail:` O(Punkte × Flächen); Obergrenze 50 000 Punkte, darüber ausgedünnt).
- **Drucken:** findet OrcaSlicer, Bambu Studio, PrusaSlicer (Pfad, Flatpak, AppImage in `~/Applications`), schreibt 3MF mit Farben (L8) und öffnet den Slicer damit; merkt sich die Wahl. Ohne Slicer: Export-Dialog.
- Tests C: Überhang-Klassifikation (Normale gegen Richtung, Grenzfälle 45°, waagerechte Decke). H: Wanddicke an einer 0,5-mm- und einer 2-mm-Platte; Druckrichtung drehen ändert die Überhänge. Slicer-Suche mit einem falschen Slicer im PATH, der seine Argumente protokolliert. G: Druckansicht an/aus, Screenshot hell/dunkel.

#### 10.7 Idee 7: Keine Angst · erledigt (2026-11-10, „Immer gespeichert“ mit dem Benutzer abgestimmt); Absturzschutz ist das Speichern selbst (höchstens 2 s gehen verloren), keine eigene Wiederherstellungsdatei; Versionen und Varianten im Fenster „Versionen“, Varianten auch im Browser (Rechtsklick aufs Design); „Speichern unter“ eines still angelegten Designs nimmt die Versionen mit und legt den ersten Ordner in den Papierkorb; Logik in `DesignVersions.py`

- **Immer gespeichert:** Neue Designs bekommen gleich einen Ordner im Projektordner. Nach jeder abgeschlossenen Aktion wird gespeichert, sobald MyCAD 2 s ruht. „Speichern“ heißt künftig „Version sichern…“ (mit Name).
- **Absturz:** Wiederherstellungsdatei bei jeder Aktion; beim Start bietet ein MyCAD-Hinweis die Wiederherstellung an.
- **Versionen:** Bei Änderungen eine Kopie im Ordner `versions/` (mit Vorschaubild), Aufbewahrung wie Time Machine: alle von heute, stündlich für eine Woche, täglich danach (`ponytail:` reine Dateikopien; bei sehr großen Designs Platz beobachten). Liste mit Vorschaubildern, öffnen nur zum Ansehen, „Wiederherstellen“ legt eine neue Version an, löscht nie.
- **Vergleich:** Geisterbild einer Version über dem aktuellen Stand, hinzugekommen grün, entfernt rot (mit Schraffur und Legende), dazu die Liste geänderter Features.
- **Varianten:** „Was wäre wenn“: Kopie als Variante, Umschalten im Browser, vergleichen wie oben, „Übernehmen“ macht die Variante zum Hauptstand (der alte wird Version). Kein Zusammenführen.
- Tests C: Aufbewahrungsregel (welche Versionen bleiben bei gegebenen Zeitstempeln). H: Version nur bei Änderung; Wiederherstellen ergibt dieselben Volumen; Vergleich findet hinzugefügte, entfernte und geänderte Features; Variante anlegen, ändern, umschalten, übernehmen; Wiederherstellung nach simuliertem Absturz. G: Versionsliste, Vergleich anzeigen, Variante wechseln.

#### 10.8 Idee 1: Handschrift ist der Befehl · erledigt (2026-11-10); Rotstift ist ein Scribble mit Transparentpapier, Blatt zur Kamera vor dem Modell; die Tinte zielt entlang der Blatt-Normale aufs Modell (`Design.readCorrection`); Zeigen hebt das Ziel hervor, „Zeigen“ setzt das Ergebnis probehalber ein (offene Transaktion, solange speichert MyCAD nicht); `3×` mustert entlang der nächsten Achse X/Y/Z mit 1,5 × Größe Abstand; ein gerader, eher waagerechter Strich oder „weg“ entfernt die Fläche (neues Feature „Fläche entfernen“, Defeaturing)

- **Rotstift:** Scribble direkt aufs Modell (Striche liegen auf den Flächen). Gelesene Zeilen werden zu Befehlen am nächsten Element:
  - `M5` an Punkt/Kreuz → Gewindebohrung; an Zylinder → Gewinde
  - `Ø8` an Kreis/Bohrung → Durchmesser setzen (über 10.3); an Punkt → Bohrung
  - `R2` an Kante → Rundung; `2×45°`/`C2` → Fase
  - `3×` an Feature → Muster (Richtung aus der Lage, sonst Rückfrage)
  - Zahl an einem Maß-Chip → Wert setzen (10.3); `+5`/`−5` auf Fläche → Press Pull
  - `H7` oder „Druck“ an Bohrung → Passung (10.5); durchgestrichene Fläche → Fläche entfernen
- Jede erkannte Korrektur erscheint als Karte („R2 → Rundung an 1 Kante“) mit Vorschau, Ausführen und Verwerfen, dazu „Alle ausführen“. Es entstehen normale Timeline-Features; die Tinte bleibt als Ebene „Korrekturen“.
- Mehrdeutig (zwei Kanten gleich nah): Auswahl mit Vorschau statt Raten.
- Tests C: Grammatik mit HTR-Verwechslungen (`MS`→`M5`, `R 2`, `2x45`, `o8`, `3x`/`3×`), ungültige Eingaben. C mit echtem Modell: synthetische Handschrift „M5“, „R2“, „Ø8“, „3×“ (wie `scribble_read_check`). H: Ziel-Element aus Tintenlage am Quader (Kante, Fläche, Punkt), Mehrdeutigkeit erkannt; Ausführen erzeugt die richtigen Features. G: mit simuliertem Stift „R2“ an eine Kante schreiben, Karte bestätigen, Rundung da; Undo.

#### 10.9 Große Skizzen (DXF-Import) · erledigt (2026-11-12/13)

Anlass: ein DXF-Import mit 10.102 Elementen (Platinen-Layout, keine Constraints) war nicht bearbeitbar. Ursache waren
quadratische Stellen im übernommenen FreeCAD-Code, nicht der Rechner. Gemessen an diesem Design:

| Aktion | vorher | nachher |
|---|---|---|
| Design öffnen | 26 s | ~2 s |
| Skizze lösen | 13 s | 0,16 s |
| Neuberechnen des Designs | 100 s | ~9 s |
| Mausbewegung in der Skizze | ~450 ms | 13–20 ms |
| Linie zeichnen (Klick) | 13,5 s (mit Neuberechnen) | 0,4 s |

- **Solver** (`planegcs`): Diagnose pro unabhängigem Block statt einer QR-Zerlegung über alles (Eigen SparseQR wuchs
  stark überlinear: 800 freie Bögen 11 s → 0,07 s); Parameter ohne Constraint gehen gar nicht erst hinein.
  Abhängigkeitsgruppen in einem Durchgang; Geometrie-Historie (ID-Wiederverwendung) über Hash-Raster und R-Baum per
  Bulk-Load statt einer Abfrage je Punkt; `getVertexIndexGeoPos` binär statt linear.
- **Formen:** `makeElementWires` mit Bounding-Box-Vorfilter vor `MakeWire::Add` (gleiches Ergebnis).
- **Profile:** während die Skizze bearbeitet wird (Profile ausgeblendet) erst beim Verlassen neu berechnet; Splitter parallel.
- **Anzeige (mit dem Benutzer abgestimmt):** Kurven fängt die Bildschirmsuche mit demselben Radius wie vorher der
  Strahltest (5 px, beim Zeichnen 12,5 px), bei mehreren gewinnt die nächstliegende; Punkte als geglättete
  GL-Punkte statt Bitmap-Marker (gleiche Größe, Ränder jetzt glatt). Der Lichthof um Linien, Punkte und Maße ist seit
  2026-11-16 ersetzt (wirkte dick, keine Profi-CAD macht das): bei offener Skizze treten Körper zur Hintergrundfarbe
  zurück, Maße und Symbole stehen auf einem Schild wie Creos Maß-Hintergrund (`test_sketch_contrast`).
  Flackern beim Drehen einer Skizze auf einer Körperfläche (2026-11-16): der projizierte Rand lag Linie auf Linie auf den
  Körperkanten, nur tausendstel Millimeter angehoben; aus der Ferne weniger als eine Tiefeneinheit. Alles der Skizze
  (und ihr Raster) hat jetzt einen festen Vorsprung im Tiefenpuffer (Tiefenbereich um 4e-6 verkürzt, ~60 Einheiten);
  Flächen schob ihr Polygon-Offset schon vorher zurück (`test_sketch_depth`).
- **Dabei gefunden:** Absturz, wenn die Anzeige-Ebenen der Skizze während der Bearbeitung neu gebaut werden (Knotenlisten
  zeigten auf gelöschte Knoten), und leere Skizze danach; beides behoben.
- Tests H: `test_big_sketch.py` (800 freie Bögen lösen in < 2 s, Freiheitsgrade, Konflikte und Redundanzen neben freier
  Geometrie, ID-Wiederverwendung). G: `test_sketch_layers.py`; `test_sketch_tools` prüft weiter das Fangen aus Abstand.
- Nachgezogen (2026-11-13, nach Review und mit dem Benutzer abgestimmt):
  - Profile beim Verlassen einer geänderten Skizze im Hintergrund (eigener Thread, Splitter nicht-destruktiv): „Fertig“
    kehrt nach dem Neuberechnen der Skizze zurück (1,6 s statt 7–10 s), die Profile folgen; ein Werkzeug, das sie
    vorher braucht, wartet auf das Ergebnis. Profile, deren Neuberechnen beim Bearbeiten übersprungen wurde, werden als
    offen gespeichert (nach einem Absturz in der Skizze keine veralteten Profile als aktuell).
  - DXF einfügen mit Prüfung: Größe, „Gezeichnet in“ (Zoll, cm, m), Ebenen wählen, Winzlinge (< 0,001 mm) und Doppelte
    entfernen (`DxfCleanup.h`, `tests/dxf_cleanup_check.cpp`, `test_dxf_import`). Dabei drei Fehler in FreeCADs
    DXF-Leser behoben (hängende Python-Ausnahme ohne Draft, vererbte Ebene, Absturz bei Element ohne Ebene).
  - Leistungsgrenzen in den Tests: `test_big_sketch` (10.000 Elemente: Lösen < 1 s, Hinzufügen < 0,3 s, Neuberechnen
    < 6 s), `test_big_sketch_ui` (Mausbewegung < 30 ms, Linie per Klick < 1,5 s; auch in der CI-Auswahl).
  - Tests brechen ab, wenn der Build älter ist als der Code (`tests/build_stale.sh`; `ALLOW_STALE=1` übergeht das).
  - GUI-Tests am echten Bildschirm: `run.sh` lässt auf dem Desktop `spectacle` auf Anfrage fotografieren, Harness
    `screen_shot`, `screen_position`, `screen_region`, `looks_like`; erster Test `test_screen_popup`.
  - Design löschen im Browser legt den eigenen Projektordner samt Versionen in den Papierkorb (wie die Startseite).
  - Absturz-Erfassung: neben jedem Bericht des Crash-Reporters ein lesbarer Stack (`<Bericht>.txt`,
    `backtrace_symbols_fd`), beim nächsten Start ein Glas-Hinweis mit „Bericht zeigen“ (`test_crash_report`, zweimal).
    Ausgewertet: ein echter Absturz vom 12.11. 21:11 (SIGABRT beim Anlegen eines Strings in
    `Selection::getObjectList`, ausgelöst über `FaceDimensions::selectedFace`), mit einem Nachbau des damaligen Stands
    aufgelöst. Muster eines Heap-Schadens, der früher entstand; die Ursache lässt sich aus dem Bericht nicht belegen
    (Kandidat: die am 13.11. behobenen hängenden Knotenlisten der Skizzenanzeige). Gezielt geprüft und sauber:
    verzögerte Lambdas und Signal-Verbindungen im MyCAD-Code halten keine hängenden Zeiger.
  - Weitere Tests am echten Bildschirm: `test_screen_windows` (Menü, Glas-Rückfrage, Einstellungen ohne schwarze Ecken;
    Harness `screen_baseline`/`new_black` mit Selbstprüfung).
- Bleibt: ~0,4 s je neuer Linie in einer Skizze mit 10.000 Elementen (Lösen und Neuaufbau der Anzeige für alle
  Elemente); die Profile selbst brauchen dort weiterhin ~7 s, nur eben im Hintergrund.

---

### 4.4 Phase 11: CAD neu denken (beschlossen 2026-11-16)

Ziel: die beste CAD-Software überhaupt. Nicht vor allem mehr Funktionen, sondern das Bestehende schneller, klarer und
vorausschauender als Fusion. Mit dem Benutzer abgestimmt: zuerst 11.1, 11.2, 11.3, danach der Rest in dieser Reihenfolge,
ein Feature nach dem anderen (je Tests, Hilfe EN/DE, README, Wiki, ein Commit). Status je Punkt hier nachtragen.

| Nr. | Feature | Kern | Status |
|---|---|---|---|
| 11.1 | Maß am Maß eintippen | Das Schild des Maßes wird selbst zum Eingabefeld (kein Fenster „Insert Length“); Enter übernimmt, Esc verwirft, Tab springt zum nächsten Maß der Skizze. Parameter und Formeln wie bisher. | erledigt 2026-11-16: Feld mit R/⌀ und Referenz in einer Zeile, ohne Abdunklung; aus der Constraint-Liste weiter die Karte mit Name (`test_dimension_inline`) |
| 11.2 | Abhängigkeiten sichtbar, bevor es knallt | Maus über einem Timeline-Schritt hebt im Modell und in der Timeline hervor, was daran hängt. Vor dem Löschen zeigt eine Vorschau, was mitgeht oder eine Warnung bekommt (proaktiv statt „Fläche weg“ hinterher). | erledigt 2026-11-16: Hover hebt abhängige Schritte in der Timeline hervor, Tooltip „Wird gebraucht von“; Löschen fragt mit Liste (Körper gehen mit, Skizzen verlieren ihre Fläche, Schritte ihre Eingabe), Abbrechen ist Standard (`test_workflow_sketch`, `test_timeline_ui`). Im Modell keine Hervorhebung: ein Schritt hat dort keine eigene Geometrie, nur der Körper. Seit 2026-11-17 auch beim Löschen eines ganzen Körpers: Kopien, Kombinieren mit ihm als einzigem Werkzeug, Skizzen und Schritte anderer Körper auf seinen Flächen (`test_delete_body_impact`) |
| 11.3 | Druckbar machen mit einem Klick | Die Druckansicht repariert, was sie findet: Überhang → 45°-Fase, Bohrung von der Seite → Tropfenform, zu dünne Wand → Mindestwand. Als Vorschläge im Fehlermodell (Idee 6), einzeln bestätigen. | erledigt 2026-11-16: Legende der Druckansicht „Druckbar machen“ mit Ausführen je Vorschlag und „Alle ausführen“ (eine Transaktion): Bohrung quer → Tropfenform (`Teardrop`), Rundung mit überhängenden Unterkanten → dort Fase statt Rundung (`PrintChamfer`), Schale/dünne Extrusion → Mindestwand. Allgemeine Überhänge ohne Rundung bleiben ein Hinweis (keine Kante, die man sicher fasen kann). Dabei behoben: Bohrungen galten fälschlich als dünne Wand (`test_print_fixes`, `test_print_fixes_ui`, `test_print`) |
| 11.4 | Messen ohne Werkzeug | Zwei gewählte Elemente zeigen sofort Abstand/Winkel/Durchmesser klein daneben; Klick darauf macht ein Maß oder einen Parameter. | erledigt 2026-11-17: Glas-Karte unter der Mitte der kürzesten Verbindung: Abstand, bei berührenden Elementen nur der Winkel, Kreis/Zylinder allein der Durchmesser; Klick öffnet die Parameter mit dem Wert, Name + Enter legt an. Nicht bei offenem Werkzeug oder in der Skizze (dort gibt es das Maß-Werkzeug). Das Messen-Panel rechnet Abstand/Winkel jetzt mit derselben Funktion; Kante zu Fläche ist dort jetzt der Winkel zur Fläche statt zu ihrer Normalen (`test_quick_measure`, `test_quick_measure_ui`) |
| 11.5 | Bohrung per Klick zu Ende denken | Fangen auf Flächenmitte und Kantenmitten, Maße zu den zwei nächsten Kanten automatisch (heute `ponytail`), mehrere Klicks mit gleichem Randabstand werden ein Muster. | erledigt 2026-11-17: Klick fängt auf Kreismitten (deckungsgleich) und auf die Mitte der Fläche quer zu jeder Kante (12 px), sonst 0,5-mm-Raster; zwei Maße zu den nächsten nicht parallelen Kanten, Punkt voll bestimmt (`test_hole_snap`). Dabei behoben: die nächste Bohrung ohne Auswahl nahm die verborgene Skizze der letzten statt auf einen Klick zu warten. Ergänzt 2026-11-17: weitere Klicks bei offenem Dialog machen weitere Bohrungen derselben Art; gleicher Randabstand wie eine frühere rastet ein und wird an deren Maß gebunden (`Constraints.RowN`), die Reihe bewegt sich gemeinsam. Damit erledigt |
| 11.6 | „Was fehlt noch?“ in der Skizze | Je Element sichtbar, welche Freiheit fehlt; ein Klick schlägt Maße nach Absicht vor (Symmetrie, Bezug zum Ursprung). | erledigt 2026-11-17: Zeile in der Sketch Palette „4 Maße fehlen“ / „Voll bestimmt“, ein Klick ergänzt nach Absicht (mittig um den Ursprung → symmetrisch, dann Längen/Durchmesser/Radien, dann Abstand zum Ursprung, Linien waagrecht/senkrecht/Winkel); jedes Maß bleibt nur, wenn es einen Freiheitsgrad nimmt, Hilfslinien bleiben frei; eine Transaktion. „Zeigen, was sich bewegen kann“ wählt das Freie (`test_complete_dimensions`, `test_sketch_complete_ui`). Pfeile je Element nicht gebaut: Auswahl + Zähler zeigen es schon |
| 11.7 | Konfigurationen aus der Parameter-Notiz | Spalten (S/M/L …) in der Notiz schalten das Teil live um (baut auf Idee 3 und 7). | erledigt 2026-11-17: Kopfzeile `Größe: S \| M \| L`, Werte je Spalte mit `\|`, Auswahl `Größe = M` (ohne: erste); je Zeile gilt die nächste Kopfzeile darüber. Spalten als Knöpfe oben in der Notiz, ein Klick schaltet um. Maß am Modell ändert nur die aktive Spalte. ⚠ bei falscher Spaltenzahl/unbekannter Auswahl. Strg+Z dreht wie bei allen Notizen den Text nicht zurück (Note::onBeforeChange), zurück per Knopf (`note_parameters_check`, `test_note_params`, `test_note_config_ui`) |
| 11.8 | Werkzeuge über Komponentengrenzen | Cut/Bohrung durch Körper anderer Komponenten (globale Links + Transformationen, `ponytail` in `addFeature`). | erledigt 2026-11-17: ein Cut (Extrude, Bohrung, alles über `applyTool`) bringt sein Werkzeug je Körper in dessen Komponente; der automatische Cut nimmt Körper anderer Komponenten mit, sobald er an der eigenen Komponente Cut ist (ein neues Teil, das nur fremde Komponenten überlappt, bleibt eigener Körper, `test_joint`). Komponente bewegt → Schritte über Grenzen rechnen neu (AppDesign-Hook). `test_cross_component`, `test_cross_component_ui` |
| 11.9 | Foto wird Skizze | Foto auf Rasterpapier/Kalibrierkarte, Kontur maßstabsgetreu als Skizze (Ersatzteile nachbauen). | erledigt 2026-11-17 (ohne Kalibrierkarte): Einfügen nimmt auch PNG/JPG (und Strg+K „Foto zu Skizze“): Otsu-Schwelle, größte Fläche, die den Bildrand nicht berührt, Umriss und Löcher (marching squares), Douglas-Peucker 1,5 px; Maßstab aus der eingegebenen Breite. `PhotoContour.h` ohne FreeCAD geprüft (`photo_contour_check`), `test_photo_sketch`. Kreise als Kreise (Kreis-Fit, ≤ 1,5 px Abweichung) und Maßstab über Rasterpapier (Periode der Rasterlinien per Autokorrelation, über viele Kästchen verfeinert; nur die Kästchengröße wird gefragt) seit 2026-11-17. Seit 2026-11-17 auch schräge Fotos: liegt das Teil auf einem ganzen A4-Blatt (alle vier Ecken im Bild, dunklerer Tisch), findet MyCAD die Ecken, entzerrt per Homographie und kennt den Maßstab vom Blatt, ganz ohne Eingabe (schräges Testfoto: 60,4 × 40,4 mm statt 60 × 40, Loch r 9,95 statt 10). Grenzen (`ponytail`): Ecken als äußerste Punkte der Diagonalen (bis ~35° Drehung), nur A4; Raster- und glattes Papier weiter nur gerade von oben |
| 11.10 | Absicht statt Befehl | Strg+K versteht Sätze wie „4 Löcher M3 in die Ecken, 5 mm vom Rand“, zeigt eine Vorschau, Enter übernimmt (Grundlage: Handschrift-Lesen). | erledigt 2026-11-17 (erster Satz): Strg+K versteht „N Löcher M3/Ø3,4 in die Ecken, 5 mm vom Rand“ (DE/EN, Dezimalkomma, ohne Abstand 2× Nenndurchmesser) als ersten Treffer; Enter öffnet die Bohrung mit Vorschau auf der gewählten Fläche bzw. oben auf dem Körper, ISO-Durchgangsloch durch alles, Randabstände als Reihe gebunden. Parser `CommandSearch::intent` ohne FreeCAD geprüft (`command_search_check`), `test_intent`. Seit 2026-11-17 auch Rundung und Fase: „Kanten 2 mm abrunden“ / „fillet R2“ (gewählte Kanten), „alle Kanten 1 mm fasen“ (jede Kante des Körpers). Seit 2026-11-17 auch Bohrmuster: Lochkreis („6 Löcher M4 auf Lochkreis 40“ / „6 holes M4 on a 40 mm circle“, Hilfskreis mit Durchmesser) und Reihe („5 Löcher M3 in einer Reihe, 10 mm Abstand“ / „… in a row, 10 mm apart“, ohne Abstand gleichmäßig); jeder Satz DE und EN geprüft |
| 11.11 | Bezüge, die sich selbst prüfen | Jede unsichere geometrische Zuordnung wird angezeigt und per Klick repariert (systematisch statt je Fall). | erledigt 2026-11-17: `Design::referenceIssues` sammelt an einer Stelle Warnungen der Schritte (Profil weg, Skizze ohne Fläche, Kanten nach Lage wiedergefunden) und jeden Verweis, den FreeCAD als verloren markiert (`?`), in jeder Link-Eigenschaft jedes Objekts. Strg+K oder Menü eines Schritts mit Warnung → Bezüge prüfen (kein eigener Knopf: die Werkzeugleiste ist bei 1500 px voll, ein Knopf mehr bricht sie in drei Zeilen, `test_glass`): je Zeile Zeigen (Schritt + betroffene Elemente), Bearbeiten (neu wählen), bei Vermutungen Stimmt so (`test_reference_issues`, `test_references_ui`) |

Kleinigkeiten aus dem Check vom 16.11.: ~~Zeittests an der Maschinengeschwindigkeit kalibrieren~~ (erledigt 2026-11-17:
`harness.slowness()` misst eine feste Arbeit und vergrößert die Grenzen um bis zu 4×; in der CI 31–40 ms bei 30 ms
Grenze, unter lokaler Last Faktor 3,4); ~~Körper treten im Phong-Modus nicht zurück~~ (erledigt 2026-11-17: schlichter Shader nur bei offener Skizze, `test_sketch_contrast`); ~~`install.sh` auch mit
Docker statt Podman~~ (erledigt 2026-11-17: `ENGINE=docker`, ohne Podman von selbst; Docker läuft als Benutzer mit
seinen Gruppen; 2026-11-17 echt geprüft in Ubuntu 26.04 unter WSL2 mit docker.io: frischer Klon → Build → Start über Wayland mit GPU (d3d12). Dabei behoben: fehlende Untermodule holt das Skript selbst, `/dev/dri` nur wenn vorhanden (WSL: `/dev/dxg` + `/usr/lib/wsl`), Docker bekommt `/etc/passwd`/`/etc/group` (sonst „Getting HOME path from system failed“)).

---

### 4.5 Aufräumliste (beschlossen 2026-11-17)

Alles, was nach Phase 11 noch im Plan oder als `ponytail` im Code stand, mit dem Benutzer durchgegangen. Reihenfolge:
A, dann B (5, 6, 4, 9, die übrigen), dann F26, dann C und E; D (Fotos) erst mit echten Fotos des Benutzers. Je Punkt:
Tests, Hilfe/README/Wiki wo sichtbar, Status hier, ein Commit.

| Nr. | Punkt | Status |
|---|---|---|
| A1–A3 | Veraltete Notizen: PLAN zur Bohrung per Klick, Kommentar zu `addFeature` (Komponenten), `fadeBodies` (Phong) | erledigt 2026-11-17 |
| B5 | Löschen eines ganzen Körpers ohne Vorschau | erledigt 2026-11-17 (`test_delete_body_impact`) |
| B6 | Ausrichtung beim Platzieren (Commands.cpp, `ponytail` „folgt späteren Änderungen nicht“) und Abstand bei Ebenen („bleibt stehen, wenn sich die Flächen verschieben“): einmal berechnet | erledigt 2026-11-17: Mittelebene ist ein eigener Typ `Design::Midplane` (Lage aus beiden Flächen, rechnet neu, wenn eine sich bewegt); Ausrichten merkt sich beide Bezüge (`AlignFrom`/`AlignTo`) und richtet bei jeder Neuberechnung neu aus, fehlt einer, bleibt die letzte Lage mit Warnung (`test_midplane`, `test_align_follows`). Bestehende Dateien rechnen wie bisher |
| B4 | Geometrischer statt topologischer Abgleich: Skizze, die ihre Fläche verliert (nächste Fläche über den Schwerpunkt), Teilung in 3+ Teile (Teile rücken auf), Wiederfinden nach Lage bei zwei deckungsgleichen Elementen | erledigt 2026-11-18: `elementName` entscheidet bei mehreren Treffern über Identität, dann Normale bzw. Laufrichtung; `faceBefore` nimmt die Fläche mit der größten Überdeckung (Mitte eines Rahmens liegt im Loch); Teilung merkt sich gelöschte Teile (`Dropped`), die übrigen rücken nicht auf und das letzte bekommt kein fremdes Teil mehr (`test_matching`) |
| B9 | Aussehen je Fläche: nur die Farbe wechselt, Glanz/Metall/Lack kommen von der ersten Fläche | zurückgestellt 2026-11-18: FreeCAD füllt alle Materialwerte je Fläche, aber Coin wechselt bei PER_PART nur Farbe und Transparenz. Echte Abhilfe = eigene Zeichengruppen je Material im SoBrepFaceSet samt Umrechnung von Auswahl/Vorauswahl (Flächen-Index); rein optisch, Risiko für die Auswahl. Erst wenn es im Alltag stört |
| B7 | Gewinde ohne Auslauf und Fase an den Flächenenden | erledigt 2026-11-18 (Fase): Außengewinde mit 45°-Fase bis zum Kern an freien Enden, nicht an einem Absatz (Probe hinter der Stirn); neue Gewinde aus der Oberfläche mit Fase, alte Dateien unverändert (`test_thread_chamfer`). Auslauf (auslaufender Gang) bewusst nicht: andere Gewindegeometrie |
| B8 | Rippe/Steg nur aus geraden Linien | erledigt 2026-11-18 (Steg): Steg auch aus Bögen, Splines und geschlossenen Kurven (Grundfläche = Kurve um die halbe Dicke nach beiden Seiten versetzt, Kreis = Ringwand auf dem Boden); offene Kurven brauchen an beiden Enden eine Wand (`test_web_curved`). Rippe in der Skizzenebene bleibt bei geraden Linien (Versatz bis zum Körper überschlägt sich innen am Bogen) |
| B10 | Aussehen „Standard“ an Farbe/Textur erkannt: Gleichaussehendes wird mit umgefärbt | erledigt 2026-11-18: ein im Aussehen-Panel gewählter Look ist am Körper markiert (`AppearanceChosen`) und bleibt beim Wechsel des Körper-Materials, auch wenn er gleich aussieht; einzeln gefärbte Flächen bleiben, die übrigen Flächen folgen (`test_material`). Ältere Dateien und Skripte ohne Markierung: wie bisher am Look erkannt |
| B11 | Scribble: Achter-Umrisse füllen nur Teilbereiche; keine Ellipsen, Dreiecke, Bögen; Aufräumen trifft auch kleine Zeichnungen; Zeichnungen werden als Text gelesen | erledigt 2026-11-18: Füllen nach Umlaufzahl (Acht, doppelt umfahren ganz gefüllt); Halten erkennt Bogen (neue Strichart, in der Skizze ein Kreisbogen), Ellipse (auch gedreht) und Dreieck (`scribble_shapes_check`, `test_scribble_shapes`); gelesene Zeilen ab 3 Zeichen zählen nur als Schrift, wenn das Modell sicher genug ist (≥ 0,6) und die Zeile breiter als hoch ist, das gilt fürs Suchen, Maße, Rotstift und Aufräumen (`scribble_read_check`). Grenze: kleine Zeichnungen, die als 1–2 Zeichen gelesen werden, bleiben Text (eine Ziffer ist ein Maß) |
| F26 | Wackeliger Test `test_sketch_fillet_radius` (unter Last rot, allein grün): Ursache klären | erledigt 2026-11-18: Testfehler, kein MyCAD-Fehler. Der Klick öffnet den Radius-Dialog über die Ereignisschleife; unter Last kamen die Tasten vor dem Dialog an, die Rundung behielt ihren Vorschlag (0,707). Der Test wartet jetzt auf den Dialog und auf sein Schließen (fünf Kopien parallel unter Last grün) |
| F27 | Testumgebung wartet pauschal 0,1 s statt die Zeichenzeit zu messen | bleibt so (2026-11-18): gilt nur beim Aufnehmen der Hilfe-Clips, nicht für Testergebnisse; genaues Messen hieße die Zeichen-Ereignisse der 3D-Ansicht aus Python umzuleiten (Risiko für alle Tests) |
| C12 | Große Skizzen: Löser baut je Änderung die ganze Skizze neu auf (inkrementeller Löser = großer Umbau) | offen (erst wenn es im Alltag stört) |
| C13 | Baugruppen: jeder Joint löst die ganze Gruppe neu; Kollision prüft jedes Paar | teilweise 2026-11-18: die Lösung einer geschlossenen Kette wird für gleiche Eingaben (feste Teile, Joints) wiederverwendet, statt dass jeder Joint der Gruppe dasselbe löst (n → 1); Kollision rechnet Lage und Hüllquader je Körper einmal statt je Paar. Bleibt: Paare n × m mit Schnittmenge, wo sich Hüllquader überlappen (für einige hundert Körper genug) (`test_joints`) |
| C14 | Druckansicht: Wanddicke ab 50.000 Dreiecken nur stichprobenhaft | erledigt 2026-11-18: Wanddicke prüft jedes Dreieck bis 400 000 (statt 50 000), Strahlen parallel über alle Kerne, je Faden ein eigener Schnitt-Rechner (`test_print`, `test_print_ui`) |
| C15 | Versionen als ganze Dateikopien (Platz bei großen Designs) | offen |
| E20 | Bohrung per Klick: festes 0,5-mm-Raster unabhängig vom Zoom; Maßstab fürs Fangen nur in einer Richtung | erledigt 2026-11-18: Raster je Kante nach Zoom (0,1/0,2/0,5/1/2/5/10 mm, ein Schritt mindestens 6 px); der Maßstab der Ansicht gilt je Richtung (schräg gesehen kürzer), fürs Fangen wie fürs Raster (`test_hole_snap`) |
| E21 | Messkarte und Flächen-Maße folgen der Kamera per Timer statt per Ereignis | erledigt 2026-11-18: `CameraFollow` (Coin-Sensor auf der Kamera, neu angehängt bei Wechsel Perspektive/Orthografisch, Größenänderung der Ansicht) für beide Karten, Bild für Bild statt im 50-ms-Takt (`test_quick_measure_ui`: Karte folgt nach Drehen). Ob ein Werkzeug aufging, prüft die Messkarte weiter ruhig im 250-ms-Takt: FreeCAD meldet das nicht |
| E22 | Befehle ohne eigenes MyCAD-Symbol zeigen ein ausgegrautes FreeCAD-Symbol | erledigt 2026-11-18: gemessen, welche Befehle in Leisten, Menüs und Strg+K ohne eigenes Bild erscheinen; neu gezeichnet die sieben Ansichten (verdeckte Seiten: kleiner Würfel, Fläche abgesetzt), Skizze ansehen/verlassen, Sperren, Winkel, Radius, Durchmesser, Horizontal/Vertikal; Körper, Löschen, Speichern unter, neue Skizze, Raster, Fangen, Schnitt und die Maß-Varianten zeigen ein vorhandenes passendes Bild. Selten genutzte Sketcher-Befehle (B-Spline-Anzeige, Auswahl-Hilfen, Kopieren) bleiben grau |
| E23 | Scribble-Wert 0,25 ist kein MyStyle-Token | erledigt 2026-11-18: Token `opacity.markerDark` in MyStyle (Commit 76abda7, Plattform-Dateien neu gebaut), in MyCAD `Token::OpacityMarkerDark` |
| E24 | Touchpad-Gesten: feste Schwellen; unter manchen Compositors (Sway) dreht 3-Finger-Wischen doppelt | erledigt 2026-11-18 (Sway): selbst gelesenes 3-Finger-Wischen trägt ein eigenes Gerät; sobald es ankommt, verwirft der Trackpad-Filter 3-Finger-Gesten anderer Herkunft, das Doppel dreht nicht mit (`test_gestures`). Schwellen (8 % Spreizen, 12 px Weg) bleiben: an echten Gesten gemessen, ohne Touchpad hier nicht neu einzustellen |
| E25 | Kleinkram: Materialien ohne Zuordnung (Messing, Kupfer, Gummi, Stein, Lacke); Normgrößen außerhalb der Tabellen geschätzt; feste Werte für Einschmelzmuttern; Holztextur feiner als echt | erledigt 2026-11-18: Messing (Copper-443) und Kupfer aus der FreeCAD-Bibliothek, eigene Dichte-Karten für Gummi, Silikon, Granit, Marmor, Keramik (`Standard/Elastomer`, `Standard/Stone`); Lacke und Pulverlack bleiben bewusst ohne Werkstoff (`test_physical`). Durchgangsbohrung für Größen, die ISO 273 nicht nennt (M9, M11 …): Spiel zwischen den Nachbarn verteilt (`test_hole`). Bleibt so: Einschmelzmuttern mit Ruthex-Werten (üblich im 3D-Druck, andere Hersteller per Hand); Holzmaserung bis 3× feiner als echt, echte Größe bräuchte 4K-Scans (App 4× schwerer), ein Ausschnitt kachelt nicht nahtlos |
| D16–D19 | Foto zu Skizze: Blattecken nur bis ~35° Drehung, nur A4; Raster/glattes Papier nur gerade von oben; Bild auf 1000 px verkleinert; nie mit echten Handyfotos getestet | zurückgestellt, bis echte Fotos da sind |
| F28 | Echter Rechner (CachyOS, Podman, echte GPU) nur durch Nutzung abgedeckt; Tests laufen mit Software-Rendering | Hinweis |
| F29 | Ubuntu 26.04 in WSL bleibt für künftige Tests (`install.sh` mit Docker, Start über WSLg); Benutzer `tester`, Klon unter `~/MyCAD`, `docker.io` | so beschlossen |

---

### 4.3 Frühere Phasen (Archiv)

Die ursprünglichen Phasen 0–9 sind durch 4.1 und 4.2 ersetzt. Joints (Phase 9) stehen in L6, Versionen und Data Panel in 10.7.

## 5. Risiken & Gegenmaßnahmen

| Risiko | Gegenmaßnahme |
|---|---|
| Coin (Legacy-OpenGL) im Qt-Quick-Scene-Graph | Phase 2 zuerst. Plan B: QOpenGLWidget plus Overlay, das das Viewport-FBO für den Blur ausliest |
| Viel FreeCAD-Gui-Code hängt an `QMainWindow`/`View3DInventorViewer` | Adapter-Schicht, schrittweiser Ersatz. Alte Oberfläche bleibt bis Phase 8 als Debug-Modus startbar |
| Eigenes Datenmodell ist groß | Algorithmen aus PartDesign wiederverwenden, nur Orchestrierung neu. Früh mit Tests absichern |
| Topologische Benennung (Referenzen brechen nach Änderungen) | Konsequent `TopoShape`-Element-Maps nutzen, Regressionstests mit typischen Edit-Szenarien |
| Kein Upstream-Merge mehr möglich (Kopie statt Fork) | Commit in `UPSTREAM.md` festhalten. Wichtige Fixes (OCCT, Solver) gezielt per Diff nachziehen |
| Lizenzen: SF Pro / SF Symbols | Inter + eigenes Icon-Set (Abschnitt 2.5) |
| Neue Features brechen alte (Phase 10 ist groß) | Etappe 10.0 zuerst: Tests in CI, rot = kein Release |
| Ständiges Speichern bremst große Designs | Speichern erst nach 2 s Ruhe; Messung in `test_performance.py`, Grenze 200 ms |
| Handschrift wird falsch gelesen und tut das Falsche | Rotstift führt nie selbst aus: jede Korrektur ist eine Karte mit Vorschau |

---

## 6. Arbeitsweise

- Etappen in der Reihenfolge aus 4.2, Pakete abhaken in dieser Datei
- Je Paket: Tests zuerst schreiben, umsetzen, alle Tests grün, Commit auf `main`
- Entscheidungen, die Verhalten für Nutzer grundlegend ändern (Speichern in 10.7, Solver in L6), stimmen wir vorher ab

## Nach der GIF-/Bug-Runde vom 12.11.2026 · geprüft am echten Bildschirm (2026-11-13), nichts offen

- Geisterbild der Suchliste beim Tippen und Ein-Bild-Glitch der Timeline-Kapsel beim Hinzufügen: am Desktop (KDE,
  Wayland) mit dem Benutzer angeschaut, 5× „bohrung“ tippen und löschen, 8 Körper nacheinander; nichts zu sehen.
  Beides waren Artefakte der Aufnahme.
- Slicer-Auswahl: der Rand war echt. Die Liste eines Auswahlfelds entsteht vor dem Glas-Stil (als Menü, 2 px schwarzer
  Rand) und übernahm ihn nur zufällig; seit 2026-11-13 bekommt sie nach dem Neu-Polieren ein StyleChange. Geprüft am
  echten Bildschirm mit `test_screen_popup` (Gegenprobe ohne Fix findet die Ränder). Eine erste Prüfung desselben Tages
  hatte den Fehler übersehen: das Prüfskript hatte die Liste dabei selbst neu gestylt.


## Bug-Runde aus dem echten Arbeiten (2026-11-14)

Beim Bauen von „Monitor Light“ fielen Fehler im Zusammenspiel auf, die einzelne Tests nicht fanden. Behoben (je mit Test):
Skizze auf Körperfläche fängt am projizierten Rand (Hilfslinien, keine Profile); Linienmitte fängt mit Dreieck; Abrunden
fragt den Radius ab, eine ganz aufgebrauchte Kante (R5 + R5 an 10 mm) fällt weg statt die Skizze redundant zu machen;
Bedingungssymbole ohne Nummern; Browser ohne „neu berechnen“-Haken, oranger Punkt statt gelbem X; Zoom-Grenzen
0,1 mm bis 1 km (langes Scrollen ließ die Kamera bis 1e19 mm laufen); Enter bestätigt Dialoge auch mit Fokus in der
Werkzeugleiste; Skizze nur beim ersten Feature ausblenden; Extrude ins Material wird von selbst Cut; Strg+Y wiederholt;
Versatz einer projizierten Kante versetzt den ganzen Umriss; unlösbarer Maßwert lässt das Feld offen; Esc mit Auswahl
hebt nur die Auswahl auf; Bohrung mit gewählter Fläche nimmt nicht die letzte Skizze irgendwo anders; Extrude ohne
Auswahl extrudiert keine ausgeblendete Skizze ein zweites Mal; Enter gehört einer Eingabe in einem anderen Panel
(Umbenennen bei offenem Dialog); bei offener Rundung/Fase nimmt ein Klick Kanten dazu oder heraus, bei offenem
Extrude/Rotieren ein Klick weitere Profile dazu (wie Fusion).

Arbeitsablauf-Tests statt Einzeltests: `test_workflow` (Teil weiterbauen, Maß ändern, Undo, Speichern, Rundung/Fase,
Tastenkürzel) und `test_workflow_sketch` (Skizzieren auf Körperflächen). Durchgespielt ohne Befund: Bemaßung zur
projizierten Kante, Seitenfläche mit Join/Cut, Verschieben, Rotieren, Komponente mit projiziertem Rand, Profil zerfällt
nach dem Extrude (Ring wie Fusion), Grundkörper nachträglich höher, Projizieren von Hand, Look-At, Esc in Dialogen.

Offene Entscheidungen, mit dem Benutzer entschieden und umgesetzt (2026-11-16, je mit Test):
- Esc verlässt die Skizze nicht mehr, auch ohne Auswahl und Werkzeug (`LeaveSketchWithEscape` jetzt standardmäßig
  aus): wie Fusion nur über „Skizze fertig stellen“. Hilfe angepasst.
- Strg+C, Strg+X, Strg+V in der Skizze gehen an die Sketcher-Befehle (Filter in der Shell; in Eingabefeldern bleiben
  die Tasten beim Text). Die Kopie verliert ihre Bezüge auf Achsen, Ursprung und projizierte Kanten (sonst klebte sie
  am Original) und hängt wie in Fusion gleich zum Verschieben am Cursor; ein Klick setzt sie ab, Esc lässt sie liegen.
- Bohrung per Klick auf eine Fläche wie Fusion: mit gewählter ebener Körperfläche an der Klickstelle (ohne Klickpunkt
  in der Mitte), ohne Auswahl wartet sie auf einen Klick. Dafür entsteht eine verborgene Skizze mit einem Punkt, in der
  Timeline vor der Bohrung; Abbrechen nimmt beides zurück. Bohren an einer Skizze mit Punkten geht weiter.
  Seit 11.5 (2026-11-17) mit Maßen zu den zwei nächsten Kanten, Fangen und Reihen; verschieben über diese Maße.
- Ein Profil, das die Vorschau eines offenen Extrude/Rotieren zudeckt: ein Klick auf die Vorschau darüber nimmt es
  heraus (Punkt im Werkzeugkörper → nächstes gewähltes Profil, beim Rotieren über seinen Kreis um die Achse).
- Feature unter einer Skizze löschen: die Skizze hängt an dieselbe Fläche im Zustand davor (eine Rundung oder Fase am
  Rand ändert die Größe der Fläche, dann genügt dieselbe Ebene). Gibt es die Fläche davor nicht, bleibt die Skizze an
  ihrem Platz, bekommt eine Warnung in der Timeline („Fläche weg“, „Stimmt so“ bestätigt) und ein Hinweis sagt es.
- Werkzeug-Hinweise unter dem ViewCube erscheinen weiter nur bei aktivem Fenster. Die Tests (eigenes Home) schalten
  das in `harness.py` ab und sehen sie so auch am Desktop ohne Fokus.

Beim vollen Testlauf danach aufgefallen, schon vor dieser Runde rot (je mit bestehendem Test):
- Der automatische Cut (ed28bd4b) prüfte Körper aller Komponenten: ein Klotz in einer neuen Komponente auf der
  Grundplatte wurde zum Cut statt zum eigenen Körper (`test_joint`). Jetzt nur Körper der eigenen Komponente.
- Seit das Hauptmaß beim Öffnen gleich den Fokus hat (ea2e3c74), setzte ein Klick hinein nur den Cursor, und Tippen
  hängte an den alten Wert an („5.00 mm25“, `test_sketch_tools`). Der erste Klick in ein so fokussiertes Feld wählt
  jetzt alles.


## FreeCAD-Erbe: Fehler, Upstream-Fixes, Abhängigkeiten (Analyse 2026-11-18)

Anlass: Die Fehler aus dem Alltag vom 17.11. lagen fast alle im übernommenen FreeCAD-Code (Abhängigkeitskreis über
externe Kanten, verschachtelter Sequencer baut die Eingabesperre ab, zweiter OK-Klick während der Neuberechnung,
Dauer-Neuzeichnen durch ignorierte SoDepthBuffer-Felder). Deshalb einmal systematisch gesucht:

- **MyCAD-Code**: was `Mod/Design` tatsächlich von FreeCAD nutzt (`Part::TopoShape` mit Fillet/Chamfer/Boolean/Refine/
  ThickSolid/Draft/Loft/Helix/Defeaturing, Sketcher mit planegcs, `PartDesign::Hole`, Attacher, Materials, STEP-Import
  über `TopoShape.read`, STEP-Export über `ImportGui.export`, STL über `Mesh.export`), dazu Speichern, Eingabesperre,
  Zeiger-Umrechnung.
- **FreeCAD-Upstream**: alle 432 Commits von unserer Basis `e9b474306f` bis `51089c6` (17.11.2026), 133 davon in
  übernommenen Pfaden. Bei jedem unten genannten Fix ist geprüft, dass die fehlerhafte Stelle bei uns noch so steht.
- **FreeCAD-Issues**: alle 3.526 offenen, gefiltert auf Fehler in Bereichen, die MyCAD nutzt (~1.100); bestätigte,
  Abstürze, Regressionen und Performance einzeln gelesen.
- **Abhängigkeiten** im Container (Arch-Archiv vom 09.11.2026): OCCT 7.9.3, Coin 4.0.4, Qt/PySide 6.12.0. FreeCAD
  selbst baut inzwischen mit OCCT 8.0.1 und Coin 4.0.10.

Vorschlag zur Reihenfolge: U1 (Datenverlust), dann U2 und U3, dann die Upstream-Fixes aus U10–U16 (klein, je ein
Commit), dann U20 (OCCT 8) mit Messung, der Rest nach Bedarf. Wie in 4.5: je Punkt Test, Status hier, ein Commit.

**In MyCAD bestätigt (Code gelesen)**

| Nr. | Punkt | Abhilfe | Status |
|---|---|---|---|
| U1 | **Speichern kann die Design-Datei verlieren.** MyCAD schaltet Sicherungsdateien ab (`CreateBackupFiles=false`, `Shell.cpp`). Dann löscht `BackupPolicy::apply` zuerst die `.mycad` und benennt erst danach die temporäre Datei um (`App/BackupPolicy.cpp`). Endet MyCAD dazwischen (Absturz, kill, Strom weg), fehlt die Datei; übrig ist nur `<name>.mycad.<UUID>`. Bei Speichern alle 2 s ist das Fenster ständig offen. Ohne `fsync` vor dem Umbenennen kann die neue Datei nach Stromausfall leer sein. Upstream ähnlich FreeCAD#33493 (offen, dort mit Sicherung) | Ohne Löschen direkt umbenennen (`rename` ersetzt unter Linux atomar), vorher Datei und Ordner `fsync`. Test: Prozess zwischen Schreiben und Umbenennen beenden, danach muss die alte oder die neue Datei vollständig da sein | erledigt 2026-11-18: ohne Sicherung wird nichts mehr gelöscht, die temporäre Datei ersetzt die Design-Datei per rename (atomar), vorher fsync der Datei, danach des Ordners; beide Wege (Zeitstempel und Standard). `test_save_atomic` sieht dem Ordner per inotify zu: die Datei wird nie gelöscht, nur ersetzt |
| U2 | **Eingabesperre mit Lücken.** Während einer Neuberechnung (`ProgressBar::eventFilter`) sind Klicks, Tasten, Kontextmenü und `NativeGesture` gesperrt, Mausrad, Touch (`TouchBegin/Update`) und Qt-Gesten (`QEvent::Gesture`) aber nicht. Zoom macht bei MyCAD einen Strahl-Pick in eine Szene, die gerade umgebaut wird. Gleiche Fehlerklasse wie der Absturz vom 17.11. und FreeCAD#30179 (Rechtsklick während des Ladens → SIGSEGV), FreeCAD#31313 (Absturz in der Gesten-Navigation) | `test_reentrancy` um Mausrad und Trackpad-Gesten erweitern; wird er rot, die Ereignisse in die Sperre aufnehmen | erledigt 2026-11-18: Mausrad, TouchBegin/Update und Qt-Gesten sind in der Sperre (Ende und Abbruch einer Berührung kommen durch, sonst bliebe sie hängen); `test_reentrancy` dreht das Mausrad mitten in einer Rechnung |
| U3 | **Zeiger trifft bei gebrochener Skalierung daneben** (KDE/Wayland 125 %, 150 % …). `InputDevice::toDevicePixelPosition` spiegelt Y in logischen Pixeln und multipliziert erst danach, der Viewport ist aber in gerundeten Gerätepixeln angelegt. Picken, Fangen und Vorauswahl liegen ein bis mehrere Gerätepixel neben dem Cursor. FreeCAD#32898, Fix als PR #32899 (offen) | PR übernehmen (erst skalieren, dann spiegeln); Test mit `QT_SCALE_FACTOR=1.5`: Pick auf eine 1-px-Kante | offen |
| U4 | **Rundung, Fase, Schale stürzen bei unmöglichen Werten ab statt Fehler zu melden.** OCCT-Segfaults lassen sich nicht abfangen. FreeCAD#33698 (unmögliche Rundung → Absturz, auch mit OCCT 8.1-dev), #23818 (Fase an Kante neben Rundung), #25868 (Radius ändern), #29352/#22921 („alle Kanten“), #20085 (Rundung friert ein), #12522 (Rundung frisst Speicher) | Testdateien aus den Tickets in `test_fuzz` aufnehmen (Rundung/Fase/Schale mit zu großen Werten); wo es knallt, vor OCCT prüfen (Radius gegen Kantenlänge und Flächenbreite, Schalendicke gegen Höhe, vgl. #25050) und als erklärten Fehler (10.2) melden | offen |
| U5 | **Refine an Bohrungen und Taschen.** MyCAD ruft `makeElementRefine` an sechs Stellen und nutzt `PartDesign::Hole`. Offen upstream: „Removing splitter failed“ bei mehreren bzw. Gewindebohrungen (FreeCAD#15353, #17802), Refine bringt Wände zurück (#22737), Rundung scheitert auf verfeinerter Form (#16654) | In `test_fuzz` mehrere Bohrungen mit Gewinde nebeneinander; scheitert Refine, ohne Refine weiterrechnen und warnen statt den Schritt rot zu machen | offen |
| U6 | **Umlaute im STEP-Export.** OCCT schreibt Namen roh als UTF-8 statt `\X2\…\X0\`; „Gehäuse“ wird in anderen CAD-Programmen zu Zeichensalat oder die Datei lässt sich nicht öffnen. FreeCAD#33914, Fix nur in OCCT (PR Open-Cascade-SAS/OCCT#1742) | Bis OCCT es kann: Namen vor dem Export selbst nach ISO 10303-21 kodieren; Test: Körper „Gehäuse“ exportieren, Datei enthält nur ASCII | offen |
| U7 | **STEP-Rundreise mit Komponenten.** FreeCAD#25150: Export lässt die Placement weg (Teile in KiCad falsch gedreht/verschoben); #20889: Rundungen kommen im STEP falsch an (OCCT, hoch priorisiert) | Test: Komponente mit Versatz und Drehung plus Rundungen exportieren, wieder einfügen, Volumen und Lage vergleichen | offen, prüfen |
| U8 | **Wird MyCAD mit der Zeit langsamer?** FreeCAD#29376 (Rechner nach 5–30 min zäh, schlimmer im Sketcher mit projizierter Geometrie, auch KDE/Wayland) und #29636 (Verzögerung wächst über Stunden). Ein Teil davon dürfte das Dauer-Neuzeichnen sein, das MyCAD am 16.11. behoben hat (db6921d4) | Dauerlauf: `test_fuzz` 30 min in einem Prozess, Bildzeit und Speicher am Anfang und Ende messen; Grenze im Test festhalten | offen |
| U9 | **Division im Maßfeld.** FreeCAD#33388 (Blocker, Regression): „10/2“ im Maßfeld ergibt „incompatible unit“, weil das Feld „10/2 mm“ liest. Betrifft „Maß am Maß eintippen“ (11.1). Fix upstream offen (PR #33728, #34068) | Test im Maßfeld: `10/2`, `10*2`, `(10+2)/2`, `10 mm/2`; wenn rot, Einheit erst nach der Rechnung anhängen | offen, prüfen |

**Upstream-Fixes nachziehen** (FreeCAD nach `e9b474306f`; Stelle bei uns unverändert geprüft; „M“ = Datei hat MyCAD
schon geändert, also von Hand einarbeiten statt `git apply`)

| Nr. | Commit | Was er behebt | Status |
|---|---|---|---|
| U10 | `ba8ded0` (`Gui/Application.cpp`, M, 2 Zeilen) | Cursor dreht nach dem Start unter Wayland lange, weil zwei Hilfs-Labels kurz als eigene Fenster aufgehen (`show()` statt `ensurePolished()`) | offen |
| U11 | `920d147` (`Gui/NotificationArea.cpp`) | Hänger: eine Qt-Warnung beim Anzeigen einer Meldung (unter Wayland „This plugin does not support raise()“) läuft in dieselbe Sperre zurück | offen |
| U12 | `33adf61` (`Gui/SoDatumLabel.cpp`, M) | Geisterlinien an Maßen (Durchmesser an Bögen): das Feld wird nie verkleinert, alte Punkte bleiben stehen | offen |
| U13 | `44a651a` (`GestureNavigationStyle`), `ec5a304` (`Gui/Tree.cpp`, M) | Absturz der Gesten-Navigation, wenn ein verzögerter Klick einen Maß-Dialog öffnet (MyCAD bietet „Gesture“ an); Absturz bei wiedereintretendem `clearSelection` | offen |
| U14 | Sketcher: `56062b6`, `c3fa28b`, `5b76ae4`, `02a1de6`, `8df06f6`, `95862d4` (meist M) | Null-Längen-Maße stabil (mit a0058bfb abgleichen); redundante Bedingungen gehen an den Entferner bzw. Benutzer statt still verworfen zu werden (vgl. FreeCAD#23189 „redundante Bedingung löschte alle Maße“); ungültiger Bedingungs-Index; Bearbeitung auf-/abbauen nur einmal; Polylinie verliert nach Rundung den letzten Punkt; Kegelschnitt teilen behält Hilfsgeometrie | offen |
| U15 | `b91dff9`, `cd97347` (`PartDesign/App/FeatureHole.cpp`, `FeatureAddSub.cpp`) | Gewindebohrung mit einem vereinigten Werkzeug (35 % schneller, Vorschau 67 %, 22 % weniger Speicher; Neuberechnen 19 % langsamer, also messen); Vorschau ohne zweite Schnittberechnung (Vorschau 30 % schneller) | offen, messen |
| U16 | `219c993` (`Gui/Quarter/EventFilter.cpp`, M) | Mausbewegungen zusammenfassen: höchstens zwei Szenendurchläufe je Schub. Hilft großen Skizzen und Szenen (vgl. FreeCAD#27319, #32971) | offen, messen |
| U17 | `b64d77b` (`Base/Reader.cpp`), `f5823b9` (`Part/App/Geometry.cpp`) | Sicherheit beim Öffnen fremder `.mycad`: XML-„Billion Laughs“ und Bezier-Kurve mit unsinniger Polzahl (Speicher) | offen |
| U18 | `80df03c`, `0cafef1`, `636365f` | Hänger bei Kamerafahrt mit Dauer 0; hängender Zeiger aus `getUserParameterTemplatePath()`; fehlendes Include für PySide 6.12 (unser Stand) | offen |
| U19 | PR FreeCAD#30919 (offen) | Lesen außerhalb des Speichers beim Öffnen einer Skizze (Achsenkreuz), gelegentliche Abstürze; FreeCAD#30914 | offen, beobachten |

Nicht übernehmen: Material-Fixes `9eb48c6`…`ede34e7` (Vergleich, Prüfung, Lizenzfelder, Fehlertexte; MyCAD holt
Materialien nur per UUID aus dem `MaterialManager`), PartDesign-DressUp/Body-Fixes `06f3dd6`, `a76e067`, `b8c7f16` (MyCAD rundet über `TopoShape`,
nicht über PartDesign-Bodies), `fffb6ee` (MyCAD ruft `ImportGui.export` direkt, Farben gehen nicht verloren).

**Abhängigkeiten**

| Nr. | Punkt | Abhilfe | Status |
|---|---|---|---|
| U20 | **OCCT 7.9.3 → 8.0.x.** Arch liefert kein OCCT 8; FreeCAD baut damit, unser Code hat die Versionsweichen schon (`OCC_VERSION_HEX >= 0x080000`). OCCT 8.0 behebt u. a. Abstürze in `ChFi3d` (Rundung/Fase an Ecken nach Booleans, an Ellipsen), Hänger in `MakeFillet::Add`, Segfault bei Fuse an Lofts, Absturz in `PipeShell`, Schalen-Regression, Absturz in `UnifySameDomain` (= Refine), STEP-Import-Abstürze und -Hänger; Booleans, B-Splines und STEP sind schneller. Risiken: Dateien mit unendlicher Geometrie lassen sich nach 8.0.1 nicht mehr öffnen (FreeCAD#33058, OCCT#1560); STEP-Import mit Torus-Buckeln bleibt (FreeCAD#34326, OCCT#1652) | OCCT 8.0.1 (oder 8.0.2) im Container selbst bauen, dazu `install.sh`/AppImage. Vorher alle Testdateien und eigene Designs laden, volle Testsuite und `test_performance` vorher/nachher | offen; **entschieden 2026-11-18**: neueste stabile OCCT-Version (Stand heute 8.0.1; 8.0.2 bzw. 8.1, sobald als Release erschienen), selbst im Container gebaut; Bauzeit und Image-Größe sind in Ordnung |
| U21 | **Coin 4.0.4 → 4.0.10.** 4.0.6 „EGL und GLX unter Wayland korrigiert“, 4.0.8 Umgehung für einen Intel-Treiberfehler bei der GL-Versionsprüfung (der Container nutzt die Intel-iGPU), 4.0.10 robusterer Parser. Arch hängt bei 4.0.4, FreeCAD bündelt 4.0.10 | Mit U20 zusammen im Container bauen; Pivy dagegen prüfen | offen; **entschieden 2026-11-18**: Coin 4.0.10, selbst im Container gebaut |

**Weitere offene FreeCAD-Fehler im Blick** (MyCAD nutzt den Bereich, aber noch nicht als Fehler gesehen; erst handeln,
wenn es im Alltag auftaucht, dann Test aus dem Ticket):

- Skizzen-Löser: Freiheitsgrade falsch gezählt (FreeCAD#15850, #8324, #11899; daran hängt der orange Punkt); Kippen
  beim Bemaßen (#10890, #23221, #33872 „Rechteck mit Rahmen“); DogLeg scheitert beim Ziehen Bogen + Linie (#32859);
  gedrehtes Rechteck mit Formel nicht lösbar (#33575) und Winkel per Formel löscht Bedingungen (#33453), beides
  wichtig für Parameter aus der Notiz (10.4); Bedingungsnamen mit Leerzeichen (#5750); große Ellipse (#30691).
- Gewinde/Helix: langsam bis Absturz bei vielen Gängen (#18367, #29949), Refine stört Gewinde (#17846).
- STEP-Import aus dem Netz: Speicher-DoS mit präparierten Dateien (#31724); importierte Teile langsam beim Drehen
  (#26148).
- Darstellung: große Koordinaten wackeln (float in Coin, #6036; betrifft DXF mit Landeskoordinaten);
  Kopieren/Einfügen unter Wayland (#15198; die Sketcher-Zwischenablage läuft über `QClipboard`).

**Zurückmelden (freiwillig):** Eigene Fixes, die FreeCAD noch fehlen und dort offene Tickets betreffen könnten:
Sequencer-Sperre bei verschachtelten Fortschritten (cf7c4f78), doppelter OK-Klick im TaskView (4d25e896),
Dauer-Neuzeichnen offener Skizzen (db6921d4, vermutlich Teil von FreeCAD#29376), Zoom-Grenzen (a3c24152, vgl. #29619).

## Hakeliges im Alltag (2026-11-18)

Was sich bei der Arbeit mit MyCAD umständlich oder träge anfühlt, gesammelt aus Rückmeldungen des Benutzers und aus
Messungen. Nichts davon ist umgesetzt; je Punkt wie in 4.5: Test, Status hier, ein Commit.

| Nr. | Punkt | Abhilfe | Status |
|---|---|---|---|
| H1 | **Druckansicht zeigt nicht, dass sie an ist** (Rückmeldung Benutzer). Ein Klick auf „Print View“ oben in der Leiste schaltet sie ein, der Knopf sieht danach aber aus wie vorher. Dass man noch einmal klicken muss, um sie zu verlassen, steht nur im Tooltip. Ursache: `Design_PrintView` ist ein einfacher Befehl ohne Umschaltzustand (`Commands.cpp`), die Leiste zeigt gedrückte Knöpfe aber schon an, wenn die Aktion umschaltbar ist (`Shell.cpp`, `setCheckable`/`setChecked`), so wie „Construction“ in der Sketch Palette | 1) Knopf bleibt gedrückt, solange die Druckansicht an ist (umschaltbare Aktion, Zustand folgt `DesignGui::printView()`, auch wenn sie anders verlassen wird). 2) In der Legende der Druckansicht unten rechts (`PrintLegend`, dort stehen schon „Choose Bottom Face“ und „Print“) ein Knopf „Druckansicht verlassen“, wie „Finish Sketch“ in der Sketch Palette. Test: Klick → Knopf gedrückt und Legende mit Verlassen-Knopf; Verlassen-Knopf → Ansicht aus, Knopf nicht mehr gedrückt | offen |
