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

### 4.1 Was steht (Stand 2026-11-10)

Die Phasen 0 bis 8 des ursprünglichen Plans sind zum großen Teil erledigt, nur anders als geplant: Die Oberfläche ist
kein QML-Neubau, sondern Glass-Panels über dem vorhandenen 3D-Viewer (Entscheidung vom 2026-10-10).

| Bereich | Erledigt | Offen (wandert in Phase 10) |
|---|---|---|
| Fundament | Build im Container, AppImage per CI, `.mycad`, Einstellungen, Deutsch, Hilfe | Tests laufen nicht in CI; Dev-Container auf ungepinntem Arch |
| Oberfläche | Liquid Glass, Hell/Dunkel, Toolbar, Browser, Inspector, Timeline, ViewCube, Startseite, Notizen, Scribble, Materialien | Befehlssuche, Timeline umsortieren und gruppieren |
| Datenmodell | Komponenten, Bodies, globale Timeline, Rollback, Suppress, Parameter, topologische Benennung | stille Rückfalle auf alte Kantennummern (siehe 10.2) |
| Skizze | 12 Zeichen-, 7 Ändern-Werkzeuge, 9 Constraints, Bemaßung am Cursor, Conic | – |
| Körper | 16 Create-, 12 Modify-, 6 Construct-Werkzeuge, Measure, Section | Extrude nur „Abstand“; Bohrung ohne Normen; Gewinde vereinfacht; Spiegeln/Muster/Drehen nur an Ursprungs-Achsen und -Ebenen; Fillet nur konstant, Fase nur gleichschenklig, keine Tangentenkette |
| Baugruppe | Joints Rigid/Revolute/Slider/Cylindrical | kein Solver, keine Bewegung, keine Grenzen |
| Austausch | STL, 3MF, STEP, DXF raus; STEP, DXF, SVG rein | 3MF ohne Farben und ohne Auflösung; STEP-Farben und Komponenten ungeprüft |
| Prüfen | Messen mit Volumen | kein physisches Material, kein Gewicht |

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
  Strahltest (5 px, beim Zeichnen 12,5 px), bei mehreren gewinnt die nächstliegende; Punkte und Lichthof als geglättete
  GL-Punkte statt Bitmap-Marker (gleiche Größe, Ränder jetzt glatt).
- **Dabei gefunden:** Absturz, wenn die Anzeige-Ebenen der Skizze während der Bearbeitung neu gebaut werden (Knotenlisten
  zeigten auf gelöschte Knoten), und leere Skizze danach; beides behoben.
- Tests H: `test_big_sketch.py` (800 freie Bögen lösen in < 2 s, Freiheitsgrade, Konflikte und Redundanzen neben freier
  Geometrie, ID-Wiederverwendung). G: `test_sketch_layers.py`; `test_sketch_tools` prüft weiter das Fangen aus Abstand.
- Bleibt langsam: Verlassen der Skizze einmalig ~7 s (OpenCascade schneidet die Profile aus 24.000 Kanten), 0,4 s je
  neuer Linie (Lösen und Neuaufbau der Anzeige für alle Elemente).

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

## Offen nach der GIF-/Bug-Runde vom 12.11.2026

- Nur in Aufnahmen gesehen, am echten Bildschirm prüfen: Geisterbild der Suchliste beim Tippen; Ein-Bild-Glitch der
  Timeline-Kapsel beim Hinzufügen (Probe: Inhalt hat sofort die richtige Größe);
  Slicer-Auswahl: unter Xvfb noch eine dunkle 2-px-Linie zwischen Feld und Liste (am echten Bildschirm prüfen). 


