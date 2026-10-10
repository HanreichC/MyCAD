# MyCAD – Masterplan

> Stand: 2026-10-10 · Basis: FreeCAD 27.1-dev, Commit `e9b474306f`
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
| Formate | Export: **STL, 3MF, STEP**. Import: **STEP, DXF, SVG** (in eine Skizze). Nativ: `.mycad` (ZIP, auf Basis von FCStd). |
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

## 4. Phasenplan

Jede Phase endet mit einem **lauffähigen, testbaren Stand** und einem Commit-/Tag-Meilenstein.

### Phase 0: Voraussetzungen
- [x] Nichts global installieren (CLAUDE.md): Build-Umgebung als Dev Container `.devcontainer/` (Arch base-devel, Podman). Wayland-Socket und `/dev/dri` werden durchgereicht, damit die GUI aus dem Container startet.
- [x] Image `mycad-dev` bauen. Weitere Pakete (z. B. `kwindowsystem` für KWin-Blur) kommen erst dazu, wenn eine Phase sie braucht.

### Phase 1: Fundament: kopieren, entschlacken, bauen
Ziel: `mycad` startet. Optisch ist es noch die alte FreeCAD-Oberfläche, aber nur mit Part/Sketcher/PartDesign, und alles baut aus dem MyCAD-Repo.
- [x] Kopieren: `src/{Base,App,Gui,Main,Ext,3rdParty(Teilmenge)}`, `src/Mod/{Part,Sketcher,PartDesign,Material,Import,Measure,Mesh,MeshPart}`, `cMake` → `cmake`, `data` (Teilmenge), `LICENSE`, Top-Level-`CMakeLists.txt`, `tests` (Teilmenge)
- [x] Herkunft dokumentieren: `docs/UPSTREAM.md` mit FreeCAD-Commit, Liste der übernommenen Pfade
- [~] CMake entschlacken: Modul-Optionen, LibPack, SMESH/Netgen, Designer-Plugin, Doku sind raus; Coin/Pivy kommen aus dem System. Offen: MSVC/macOS-Zweige in `cMake/FreeCAD_Helpers`.
- [ ] Nicht benötigte Teile aus `Gui` entfernen (Macro-Recorder-UI, Web, Assistant/Help, 3Dconnexion-Legacy, Designer-Plugin, Splash/Start-Seite, AddonManager-Hooks)
- [~] Rebranding: Benutzer-Konfiguration unter `~/.config/MyCAD`, `~/.local/share/MyCAD` (erledigt, damit eine installierte FreeCAD-Version nicht gestört wird). Offen: Binärname `mycad` (Starter heißt schon so). Python-Modulnamen bleiben bis Phase 8 `FreeCAD`/`FreeCADGui`.
- [x] Release-Build (Ninja, ccache, 6 Kerne, `nice`), alle 2119 Unit-Tests grün
- [x] `.gitignore`, `README.md`, `install.sh` (Build im Container + Starter `mycad` + Menüeintrag)

### Phase 2: Technik-Prototyp Liquid-Glass-Viewport *(größtes technisches Risiko zuerst)*

> **Entscheidung (2026-10-10):** Statt eines kompletten QML-Neubaus sitzen die Glass-Panels als GPU-Elemente
> direkt in der Szene des vorhandenen 3D-Viewers (`QuarterWidget` ist ein `QGraphicsView`). Coin rendert zuerst,
> danach blurrt `Gui/Shell/GlassPanel` die fertigen Pixel unter sich. Vorteil: Sketcher, Task-Dialoge, Auswahl
> und Undo von FreeCAD funktionieren unverändert weiter. Abschnitt 3.2 (QML) gilt damit nur noch als Option.

- [x] `Gui/Shell/GlassPanel`: Blur (Downsample + Gauß), Linse mit Farbaufspaltung, Glanzkante, Tönung, Schatten
- [x] `Gui/Shell/Shell`: Menüs/Toolbars/Docks/Statusleiste weg, 3D-Ansicht randlos über das ganze Fenster,
      Glass-Toolbar (wechselt im Sketch-Modus), Browser links, Inspector rechts nur bei aktivem Werkzeug,
      beim Start automatisch neues Design, Inter-Schrift, Hell/Dunkel nach System
- [ ] Offen: eigenes Icon-Set, eigener ViewCube, Timeline unten, rahmenloses Fenster, pivy-SWIG-Fehler im Container
Ziel: Ein QML-Fenster zeigt eine Coin-Szene mit Navigation, darüber ein echtes Liquid-Glass-Panel bei 60+ fps.
- [ ] `CoinViewportItem` (QQuickFramebufferObject, OpenGL-RHI), Maus/Tastatur/Touchpad → `SoEventManager`
- [ ] Glass-Shader v1: Blur, Lensing, Specular, adaptive Tönung. Vergleich mit Apple-Referenzscreenshots.
- [ ] Performance-Messung (4K, Wayland, iGPU/dGPU), Fallback-Strategie
- [ ] Prüfen, wie viel von `View3DInventorViewer` (Selektion, Highlight, Edit-Mode-Hooks des Sketchers) sich an das neue Item hängen lässt. Ergebnis: Adapter-Schicht oder Refactor.
- [ ] **Entscheidungspunkt**: Prototyp mit dir abnehmen, bevor die UI in die Breite geht

### Phase 3: Design-System & UI-Shell
Ziel: Die leere MyCAD-Oberfläche steht komplett, mit Dokument laden/speichern und 3D-Ansicht.
- [ ] Design-Tokens (QML-Singleton): Farben Hell/Dunkel, Akzent, Radien (konzentrisch), Abstände (8-pt-Raster), Typografie (Inter), Schatten, Animationskurven (Spring)
- [ ] Kontrollelemente-Bibliothek: Button (Glass, Prominent, Plain), Icon-Button, Segmented Control, Toggle, Slider, Text-/Zahlenfeld mit Einheiten und Ausdrücken, Stepper, Menu, Popover, Tooltip, Sheet, Alert, Search Field, List/Outline, Disclosure
- [ ] Icon-Set v1 (Werkzeuge der Phasen 4–6), Pipeline SVG → QML
- [ ] Fensterrahmen, Titelleiste, KDE-Hell/Dunkel-Erkennung, Reduce Transparency/Motion
- [ ] Panels: Toolbar, Browser, Inspector, Timeline (vorerst leer), ViewCube, Navigationsleiste, Statusmeldungen (Toasts)
- [ ] Command Palette (`S`/`Ctrl+K`), Tastenkürzel wie in Fusion (E Extrude, F Fillet, L Line, R Rectangle, C Circle, D Dimension, T Trim, X Construction, Q Press Pull …)
- [ ] Marking Menu (Rechtsklick-Radialmenü)
- [ ] Startbildschirm: zuletzt geöffnete Designs mit Vorschaubildern, „New Design“
- [ ] Viewport-Look v1: Beleuchtung, Hintergrund, Kanten, Auswahl-Glow, Grid

### Phase 4: Fusion-Datenmodell (`Mod/Design`)

> **Stand 2026-10-10 (vorgezogen vor Phase 3):** `Mod/Design` steht und ist in der Oberfläche verdrahtet.
> Root-Komponente (App::Part) mit Origin/Bodies/Sketches, Profile (alle geschlossenen Regionen einer Skizze),
> Body mit Tip, globale Timeline-Leiste (Klick wählt, Doppelklick bearbeitet, Rechtsklick Suppress/Delete).
> Features: Extrude, Revolve, Fillet, Chamfer, Shell, Combine, Move, Mirror (Bodies). Export 3MF/STL/STEP.
> Skizzen auf Körperflächen und Werkzeug-Bodies hängen am Timeline-Zustand (Feature), nicht am Body.
> Seitdem dazu: Pattern, Hole, Press Pull, Offset Plane, Komponenten (New Component, Aktivieren,
> Verschieben, Extrude -> New Component), Rollback-Marker, Suppress/Delete, topologische Benennung
> für Kanten/Flächen (Element-Maps) und Profile (Signaturen), Ziehpfeile, Conic Curve.
> Optik: eigenes Icon-Set, eigener ViewCube, rahmenloses Fenster, Fusion-Skizzenfarben, MSAA 4x.
> Offen: Operationen über Komponentengrenzen, Mirror/Pattern von Bodies, Joints (Phase 9).
Ziel: Mehrere Komponenten und Bodies in einer Datei, globale Timeline, erste Features.
- [ ] `Component`, `Body`, `Feature`-Basis, `Timeline` inkl. Rollback-Marker, Suppress, Reorder, Gruppen
- [ ] Algorithmen aus PartDesign in eine Bibliothek auslagern (`Design/Algo`)
- [ ] Erste Features: **Extrude** (alle Fusion-Optionen: One Side/Two Sides/Symmetric, Distance/To Object/All, Taper, Operation) und **Revolve**
- [ ] Aktivieren von Komponenten, „New Component“, Bodies ↔ Komponenten umwandeln
- [ ] Move/Copy (Bodies, Komponenten; frei, Punkt-zu-Punkt, Rotieren) als Timeline-Feature
- [ ] Browser- und Timeline-Modelle an QML angebunden
- [ ] Dateiformat `.mycad` (ZIP + Document.xml + BREP + Vorschaubild), Undo/Redo über Transactions
- [ ] Tests: Recompute-Kette, Rollback, Speichern/Laden, Topo-Naming-Stabilität

### Phase 5: Sketch, vollständig (Abschnitt 2.2)
- [ ] Sketch-Edit-Mode im neuen Viewport: Kamera „Look At“, Glass-Sketch-Palette, Freiheitsgrade-Anzeige, Farbcodierung
- [ ] Heads-Up-Bemaßungseingabe (Tab wechselt Felder), Inferenzlinien, Auto-Constraints, Snap
- [ ] Alle Create-Werkzeuge inkl. neu: **Conic Curve**, **Circular Pattern**, Text auf Pfad
- [ ] Alle Modify-Werkzeuge (Fillet, Chamfer-Varianten, Offset, Trim, Extend, Break, Scale, Move/Copy)
- [ ] Alle Constraints mit neuen Glyphen; Konflikte als verständliche Meldung
- [ ] Project / Include / Intersect / Project to Surface
- [ ] Profilerkennung (geschlossene Regionen, verschachtelte Profile) → Auswahl einzelner Profile für Extrude (Fusion-typisch)
- [ ] 3D-Sketch (Basis)
- [ ] Neues Rendering der Skizzengeometrie (glatte Linien, MSAA, Punkte als Kreise, Constraint-Badges)

### Phase 6: Solid Create (Abschnitt 2.3)
- [ ] Sweep (Pfad, Führungsschiene, Twist), Loft (Rails, Centerline, Tangenz)
- [ ] Hole (alle Typen, Gewindetabellen ISO/UNC), Thread (cosmetic + modeled)
- [ ] Rib, Web, Emboss (Text/Profil auf Fläche prägen/gravieren)
- [ ] Primitive: Box, Cylinder, Sphere, Torus, Coil, Pipe
- [ ] Pattern (Rectangular, Circular, on Path) für Features/Bodies/Faces, Mirror
- [ ] Direkte Manipulatoren im Viewport (Glass-Pfeile und -Griffe zum Ziehen von Distanzen und Winkeln)

### Phase 7: Modify, Construct, Inspect
- [ ] Press Pull, Fillet (konstant/variabel/Rule), Chamfer, Shell, Draft, Scale, Combine
- [ ] Offset Face, Replace Face, Split Face, Split Body, Silhouette Split, Align, Delete
- [ ] Physical Material & Appearance (Material-Bibliothek, Glass-Picker, Drag & Drop auf Bodies)
- [ ] Construct: alle Ebenen-, Achsen- und Punkt-Varianten
- [ ] Inspect: Measure (Glass-HUD), Interference, Section Analysis, Center of Mass, Component Colors
- [ ] Parameters-Dialog (Benutzerparameter, Ausdrücke, Favoriten)

### Phase 8: Import/Export, Politur, Paket
- [ ] Export STL/3MF (Auflösungsvorgaben, pro Body/Komponente), STEP (AP214/AP242 mit Farben und Komponentenstruktur)
- [ ] Import STEP (als Komponenten), DXF/SVG → neue Skizze
- [ ] Performance: Recompute-Profiling, asynchrones Tessellieren, große Designs
- [ ] Animationen & Mikrointeraktionen, Feinschliff beider Themes, Barrierefreiheit
- [ ] Python-Namespace umbenennen (`FreeCAD` → `MyCAD`, Alias für Kompatibilität)
- [ ] Toten Code entfernen (alte Qt-Widgets-Oberfläche, ungenutzte Gui-Teile, PartDesign-Reste)
- [ ] `PKGBUILD` für CachyOS, `.desktop`-Datei, MIME-Typ `.mycad`, App-Icon
- [ ] Autosave & Wiederherstellung, Versionen einer Datei (lokal)

### Phase 9: Später / optional
- [ ] Joints (Rigid, Revolute, Slider, Cylindrical, Pin-Slot, Planar, Ball) mit OndselSolver, statisch
- [ ] Data Panel: lokale Projektordner mit Designs, Vorschaubildern und Versionen (wie Fusions Projektbrowser)
- [ ] Surface-Grundlagen (Thicken, Boundary Fill, Patch), falls doch gebraucht
- [ ] Ableitung (Derive) von Komponenten aus anderen Designs

---

## 5. Risiken & Gegenmaßnahmen

| Risiko | Gegenmaßnahme |
|---|---|
| Coin (Legacy-OpenGL) im Qt-Quick-Scene-Graph | Phase 2 zuerst. Plan B: QOpenGLWidget plus Overlay, das das Viewport-FBO für den Blur ausliest |
| Viel FreeCAD-Gui-Code hängt an `QMainWindow`/`View3DInventorViewer` | Adapter-Schicht, schrittweiser Ersatz. Alte Oberfläche bleibt bis Phase 8 als Debug-Modus startbar |
| Eigenes Datenmodell ist groß | Algorithmen aus PartDesign wiederverwenden, nur Orchestrierung neu. Früh mit Tests absichern |
| Topologische Benennung (Referenzen brechen nach Änderungen) | Konsequent `TopoShape`-Element-Maps nutzen, Regressionstests mit typischen Edit-Szenarien |
| Kein Upstream-Merge mehr möglich (Kopie statt Fork) | Commit in `UPSTREAM.md` festhalten. Wichtige Fixes (OCCT, Solver) gezielt per Diff nachziehen |
| Lizenzen: SF Pro / SF Symbols | Inter + eigenes Icon-Set (Abschnitt 2.5) |

---

## 6. Arbeitsweise

- Phasen der Reihe nach, Aufgaben abhaken in dieser Datei
- Nach jeder Phase: Build, Tests, kurze Demo/Screenshots, Commit + Tag (`m1` … `m8`)
- Entscheidungspunkte (Ende Phase 2, Design-Review Ende Phase 3) stimmen wir gemeinsam ab
