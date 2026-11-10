# Für Entwickler

## Holen und bauen

MyCAD hat ein Git-Submodul (OndselSolver, der Gelenk-Solver). Deshalb mit Submodulen klonen:

```sh
git clone --recursive https://github.com/HanreichC/MyCAD.git
# schon geklont:
git submodule update --init
```

Gebaut wird im Podman-Container (`.devcontainer/`), nichts landet auf dem System:

```sh
./install.sh   # baut MyCAD und legt den Starter `mycad` und einen Menüeintrag an
mycad
```

Das AppImage für Releases baut `tools/appimage.sh`; die CI (`.github/workflows/release.yml`) baut es nach jedem Commit,
nachdem alle Tests grün sind.

## Aufbau

| Wo | Was |
|---|---|
| `src/Gui/Shell/` | die Oberfläche: Liquid Glass, Werkzeugleiste, Zeitleiste, Notizen, Befehlssuche, Einstellungen, Startseite, Hilfe, immer gespeichert |
| `src/Mod/Design/App/` | das Modell: Körper, Features, Zeitleiste, Gelenke, Rotstift-Grammatik, Druckprüfung, Passungen |
| `src/Mod/Design/Gui/` | Befehle, Feature-Dialoge, Scribble, Handschrift, Druckansicht, Korrektur-Karten, Versionen-Fenster |
| `src/Mod/Design/DesignExport.py` | 3MF-Export, Slicer finden und starten |
| `src/Mod/Design/DesignVersions.py` | Versionen, Aufbewahrung, Vergleich, Varianten |
| `src/Mod/Design/App/AssemblySolver.*` | dünne Schnittstelle zu OndselSolver (nur diese Datei kennt den Solver) |
| `tools/help_content.py` | Quelle der eingebauten Hilfe (`python tools/help_content.py` erzeugt `help.json`) |
| `tools/make_icons.py` | erzeugt die Symbole |
| `docs/PLAN.md` | Fahrplan und Stand aller Vorhaben |
| `docs/wiki/` | dieses Wiki als Markdown im Repo |

Logik, die ohne FreeCAD auskommt, steht in kleinen Headern und hat je einen Check: `NoteParameters.h`, `Fits.h` (ISO 286),
`PrintCheck.h`, `RedPen.h`, `Gui/Shell/CommandSearch.h`, `Gui/ScribbleTidy.h`, `Gui/ScribbleShapes.h`.

## Tests

Alles auf einmal (im Container):

```sh
GUI=ci tests/run_all.sh
```

| Art | Wo | Was |
|---|---|---|
| C-Checks | `tests/*_check.cpp` | Logik ohne FreeCAD, z. B. Passungstabelle, Rotstift-Grammatik; `scribble_read_check` liest synthetische Handschrift mit dem echten Modell |
| Headless | `tests/design/test_*.py` | FreeCADCmd + unittest: Features, Volumen, Fehler und Vorschläge, Gelenke, Druckprüfung, Slicer-Suche, Versionen |
| GUI | `tests/gui/test_*.py` | klicken die App durch wie ein Mensch, mit echten Maus- und Tastatur-Ereignissen, unter Xvfb |

Einzelne Tests:

```sh
PATTERN=test_joints.py tests/design/run.sh
tests/gui/run.sh tests/gui/test_red_pen_ui.py /tmp/redpen   # Protokoll /tmp/redpen.txt, Bilder /tmp/redpen*.png
```

Die GUI-Tests in `tests/gui/ci.txt` laufen in der CI. `harness.py` schaltet „Immer gespeichert“ aus, damit der Takt der
Tests stimmt; `test_versions_ui.py` schaltet es gezielt ein. Schritte, die länger dauern können (Animation, Dialoge),
gehören in `in_order` statt `run`.

## Regeln im Projekt

Die Arbeitsweise steht in `CLAUDE.md`: vorhandenes wiederverwenden, kürzester funktionierender Diff, für nicht triviale
Logik ein ausführbarer Check, bewusste Vereinfachungen mit `ponytail:` markieren. Die Oberfläche folgt dem MyStyle-
Styleguide (nur Werte aus den Design-Tokens).
