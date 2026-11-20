# MyCAD auf Flathub bringen

> Ziel (Plan 12.6): MyCAD läuft auf jedem Linux, installiert über Flathub (`flatpak install flathub
> io.github.HanreichC.MyCAD`). Diese Anleitung sagt, was dafür im Repo entstehen muss, was am Code anders werden muss
> (Sandbox), wie man lokal baut und prüft, wie man einreicht und wie man danach pflegt.
> Stand: November 2026. Wo die Regeln sich schnell ändern, steht „prüfen“ dabei.

---

## 1. Die Entscheidungen vorab

| Thema | Entscheidung | Warum |
|---|---|---|
| App-ID | `io.github.HanreichC.MyCAD` | Neue Apps mit `com.github.…` nimmt Flathub nicht mehr an. Die ID muss überall exakt gleich sein (Manifest, Metainfo, Desktop-Datei, Symbol). `io.github.<Benutzer>` lässt sich über den GitHub-Account als verifiziert markieren |
| Runtime | `org.kde.Platform` / `org.kde.Sdk` in der aktuellen Qt-6-Version (prüfen: `flatpak remote-info flathub org.kde.Platform`) | bringt Qt 6 mit Wayland, SVG, Declarative, Shadertools; spart die größten Module |
| Python + PySide6 | als BaseApp `io.qt.PySide.BaseApp` derselben Qt-Version (prüfen, ob es sie für die gewählte Version gibt), sonst PySide6/Shiboken6 als eigene Module | MyCAD braucht Python und PySide6 (FreeCAD-Kern, Hilfe, Tests) |
| Bauen | alles aus den Quellen, auf den Flathub-Buildern, ohne Netz während des Baus | Flathub-Regel; Quellen werden vorher als Archive/Git-Commits mit Prüfsumme geladen |
| Version | die Tags `v1.0.N` bzw. `v1.2.0`, die unsere CI schon erzeugt | Flathub baut einen festen Tag/Commit |

---

## 2. Was im Repo entstehen muss

Alles unter `data/flatpak/` (Quellen) und per CMake installiert, damit auch AppImage und `install.sh` davon profitieren.

1. **Desktop-Datei** `io.github.HanreichC.MyCAD.desktop` (heute erzeugt `install.sh` eine eigene `mycad.desktop`):
   `Name=MyCAD`, `Exec=mycad %F`, `Icon=io.github.HanreichC.MyCAD`, `Categories=Graphics;Engineering;3DGraphics;`,
   `MimeType=application/x-mycad;model/step;model/stl;`, `StartupWMClass=` passend zur Qt-Fensterklasse.
2. **Symbol** `io.github.HanreichC.MyCAD.svg` nach `/app/share/icons/hicolor/scalable/apps/` (aus
   `tools/app_icon.py`, wie das heutige `mycad.svg`), dazu 128- und 256-px-PNGs für ältere Software-Center.
3. **Metainfo** `io.github.HanreichC.MyCAD.metainfo.xml` nach `/app/share/metainfo/`. Inhalt:
   - `<id>` exakt die App-ID, `<name>MyCAD</name>`, `<summary>` (≤ 35 Zeichen, ohne „CAD software“-Floskel, z. B.
     „Parametric CAD for 3D printing“), `<developer id="io.github.HanreichC">`.
   - `<description>`: zwei kurze Absätze und eine Liste der Hauptfunktionen (aus der neuen README, „Why MyCAD.“).
   - `<launchable type="desktop-id">io.github.HanreichC.MyCAD.desktop</launchable>`.
   - `<metadata_license>CC0-1.0</metadata_license>`, `<project_license>LGPL-2.1-or-later</project_license>`.
   - `<url type="homepage">`, `bugtracker`, `vcs-browser`, `help` (Wiki).
   - `<screenshots>`: 3–5 Bilder mit festen URLs (`raw.githubusercontent.com/HanreichC/MyCAD/<tag>/docs/images/…`),
     Standardgröße 16:9, ohne Fensterschatten, eines als `type="default"`, je mit `<caption>`. Kandidaten:
     `workspace.png`, Druckansicht, Notiz mit Parametern, Scribble, Materialien.
   - `<releases>`: je Release ein `<release version="1.0.N" date="…">` mit 2–4 Sätzen. Die CI kann das beim Taggen
     aus den Commits ergänzen.
   - `<content_rating type="oars-1.1" />` (leer = keine bedenklichen Inhalte).
   - `<branding>` mit einer hellen und einer dunklen Akzentfarbe aus den MyStyle-Tokens.
   - `<provides><mediatype>application/x-mycad</mediatype></provides>` und die MIME-Definition für `.mycad`
     (`/app/share/mime/packages/io.github.HanreichC.MyCAD.xml`, heute in `install.sh`).
   - `<requires><display_length compare="ge">1280</display_length></requires>`, `<supports><control>pointing</control>
     <control>keyboard</control><control>tablet</control></supports>`.
4. **Manifest** `io.github.HanreichC.MyCAD.yml` (kommt später ins Flathub-Repo, wird aber hier entwickelt und in der
   CI gebaut).

---

## 3. Was am Code anders werden muss (Sandbox)

Ein Flatpak sieht nur, was es per `finish-args` darf. Für MyCAD heißt das:

| Funktion | heute | im Flatpak | Änderung |
|---|---|---|---|
| Fenster, GPU | Wayland, `/dev/dri` | `--socket=wayland`, `--socket=fallback-x11`, `--share=ipc`, `--device=dri` | keine |
| Projektordner, immer speichern | beliebiger Ordner, Standard im Home | `--filesystem=xdg-documents/MyCAD:create` (Standard-Projektordner); andere Ordner über den Datei-Dialog (Portal) | Standard-Projektordner auf `~/Documents/MyCAD` legen, wenn er nicht gesetzt ist; „Projektordner wählen“ über den Portal-Dialog, Zugriff merkt sich das Dokumenten-Portal |
| Datei öffnen/importieren/exportieren | Qt-Dialog | Portal-Dialog (`xdg-desktop-portal`), Qt nutzt ihn im Flatpak von selbst | prüfen, dass kein eigener Dialog am Portal vorbei geht |
| **Drucken → Slicer** | sucht Slicer auf dem Rechner, startet sie (Flatpak-Slicer über das Dokumenten-Portal, im Container über `DesignExport.host_spawn`) | Programme auf dem Rechner zu starten bräuchte `--talk-name=org.freedesktop.Flatpak` (= `flatpak-spawn --host`, praktisch Sandbox-Ausbruch); das wird im Review kritisch gesehen und braucht eine Ausnahme | im Flatpak: 3MF schreiben und über das Portal **OpenURI** öffnen (`QDesktopServices::openUrl`); das System fragt „Öffnen mit …“ und zeigt die installierten Slicer, auch Flatpak-Slicer. Die Wahl merkt sich das System. Kein Host-Zugriff nötig |
| **Grafiktablett-Tasten** (libinput auf `/dev/input`) | udev-Regel per `pkexec` oder `install.sh` | `--device=input` (seit Flatpak 1.15.6; prüfen, ob die Flathub-Builder es inzwischen akzeptieren, früher meldeten sie „unknown device“; sonst `--device=all`, schwerer zu begründen). Die udev-Regel kann ein Flatpak nicht anlegen | die Tablett-Seite erkennt das Flatpak (`/.flatpak-info`) wie heute den Container und zeigt den Terminal-Befehl für die Regel statt „Zugriff erlauben“. Stift und Druck gehen ohne Regel |
| Touchpad selbst lesen (3-Finger-Drehen unter KWin) | libinput auf `/dev/input` | wie oben, `--device=input` | keine, außer dem Hinweis |
| Handschrift-Modell, Texturen, Hilfe | im Build | unter `/app/share/…` | Pfade schon relativ zur Installation; prüfen |
| Einstellungen, Absturzberichte | `~/.config`, `~/.local/share` | landen in `~/.var/app/io.github.HanreichC.MyCAD/` | keine; bestehende Einstellungen aus dem AppImage werden nicht übernommen (einmalig hinweisen) |
| Netz | nicht nötig | kein `--share=network` | keine |

Die `finish-args` werden damit kurz und gut begründbar:

```yaml
finish-args:
  - --socket=wayland
  - --socket=fallback-x11
  - --share=ipc
  - --device=dri
  - --device=input               # Grafiktablett- und Touchpad-Tasten selbst lesen (libinput)
  - --filesystem=xdg-documents/MyCAD:create
```

---

## 4. Das Manifest

Die Module entsprechen dem, was heute `.devcontainer/Dockerfile` installiert. Was die KDE-Runtime schon hat (Qt 6,
freetype, zlib, icu, mesa), fällt weg.

```yaml
id: io.github.HanreichC.MyCAD
runtime: org.kde.Platform
runtime-version: '6.x'            # aktuelle Version eintragen
sdk: org.kde.Sdk
base: io.qt.PySide.BaseApp         # Python + PySide6/Shiboken6 (prüfen), sonst eigene Module
base-version: '6.x'
command: mycad
rename-desktop-file: false
finish-args: [ … wie oben … ]
cleanup:
  - /include
  - /lib/cmake
  - /lib/pkgconfig
  - '*.a'
modules:
  - name: boost                    # nur die Teile, die FreeCAD braucht (program_options, regex, thread, …)
  - name: eigen                    # nur Header
  - name: xerces-c
  - name: yaml-cpp
  - name: fmt
  - name: nlohmann-json
  - name: microsoft-gsl
  - name: rapidjson
  - name: pybind11
  - name: swig                     # nur zum Bauen von Pivy, danach cleanup
  - name: onnxruntime              # Handschrift; aus den Quellen schwer (siehe 7.)
  - name: occt                     # OpenCascade 8.0.1, ohne Draw/Tk/VTK (wie im Dockerfile)
  - name: coin                     # 4.0.10
  - name: pivy                     # 0.6.11 (mit dem py2compat-Header wie im Dockerfile)
  - name: python-deps              # pyyaml, packaging (matplotlib nur, wenn zur Laufzeit gebraucht)
                                   # mit flatpak-pip-generator erzeugen
  - name: mycad
    buildsystem: cmake-ninja
    config-opts: [-DCMAKE_BUILD_TYPE=Release]
    sources:
      - type: git
        url: https://github.com/HanreichC/MyCAD.git
        tag: v1.0.N
        commit: <sha>              # Flathub verlangt den festen Commit zum Tag
```

Jedes Modul mit `sources` (Archiv-URL + `sha256` oder Git-Tag + Commit) und `x-checker-data`, damit der
Flathub-Bot neue Versionen meldet. FreeCADs eigenes Flathub-Manifest (`flathub/org.freecad.FreeCAD`) baut OCCT, Coin
und Pivy schon. Dort abschauen spart Fehlersuche (Optionen, Patches).

---

## 5. Lokal bauen und prüfen

```sh
# einmalig
flatpak install flathub org.flatpak.Builder org.kde.Sdk//6.11 org.kde.Platform//6.11
# bauen und installieren aus dem Arbeitsstand (dauert beim ersten Mal wegen OCCT und PySide Stunden)
flatpak run org.flatpak.Builder --user --install --force-clean --ccache --install-deps-from=flathub \
    --repo=repo build-dir flatpak/io.github.HanreichC.MyCAD.yml
flatpak run io.github.HanreichC.MyCAD
# prüfen, wie Flathub es prüft
flatpak run --command=flatpak-builder-lint org.flatpak.Builder repo repo
```

Dasselbe macht die Action **Flatpak** (`.github/workflows/flatpak.yml`), von Hand gestartet oder bei Tags. Sie legt
`MyCAD.flatpak` als Artefakt ab.

Von Hand testen, bevor eingereicht wird: Design anlegen (landet in `~/Documents/MyCAD`), anderen Projektordner wählen,
STEP importieren, 3MF exportieren, **Drucken** (Dialog „Öffnen mit“ zeigt den Slicer), Tablett-Seite (Hinweis statt
Knopf), Hell/Dunkel, Deutsch, Hilfe mit Bildern, Handschrift lesen.

**In der CI:** die eigene Action `.github/workflows/flatpak.yml` (nicht in `release.yml`, damit ein langer
Flatpak-Bau das AppImage nicht aufhält). Sie baut mit `flathub-infra/flatpak-github-actions` und lässt den Linter laufen.
So fällt ein kaputtes Manifest auf, bevor Flathub es baut.

---

## 6. Einreichen

Die Einreichung kommt von dir, unter deinem GitHub-Konto. Vorbereitet ist im Repo: das Manifest
`flatpak/io.github.HanreichC.MyCAD.yml` mit Patches und Python-Modulen und `flatpak/submission.sh`, das daraus die
Fassung für Flathub schreibt (fester Tag und Commit statt Arbeitsstand).

1. Auf GitHub `flathub/flathub` forken.
2. Klonen, vom Branch **`new-pr`** (nicht `master`) einen Branch abzweigen:
   `git clone --branch new-pr git@github.com:<du>/flathub.git && cd flathub && git checkout -b add-mycad`
3. Im MyCAD-Repo `flatpak/submission.sh v1.0.N` (N: das neueste Release, auf dem die Action Flatpak grün war),
   dann den Inhalt von `~/flathub-submission/` in den Klon kopieren:
   `cp -r ~/flathub-submission/* . && git add . && git commit -m "Add io.github.HanreichC.MyCAD" && git push -u origin add-mycad`
   Die Metainfo, Desktop-Datei und das Symbol kommen aus dem MyCAD-Repo (über den Git-Tag).
4. Pull Request gegen **`new-pr`** öffnen, Titel „Add io.github.HanreichC.MyCAD“. Die Checkliste in der
   PR-Vorlage ausfüllen. Bei `--device=input` kurz begründen („reads graphics tablet and touchpad buttons that
   Wayland doesn't pass to apps; optional, everything else works without it“).
5. Im PR mit `bot, build` einen Testbau auf den Flathub-Buildern anstoßen. Fehler beheben, wieder `bot, build`.
6. Review: Die Prüfer kontrollieren die Anforderungen und Rechte, können Änderungen verlangen oder nach Gründen
   fragen. Rechnen mit ein bis drei Runden.
7. Nach dem Merge legt Flathub das Repo `flathub/io.github.HanreichC.MyCAD` an, du bekommst Schreibrechte. Ab dann
   gehen alle Updates dort hinein, nie wieder über `flathub/flathub`.
8. **Verifizieren:** auf flathub.org mit dem GitHub-Account anmelden und die App als verifiziert markieren (für
   `io.github.<Benutzer>` reicht der GitHub-Login). Das blaue Häkchen schafft Vertrauen.

---

## 7. Stolpersteine

- **onnxruntime aus den Quellen** ist groß und langsam zu bauen (Python, protobuf, abseil). **Stand:** Das Manifest baut
  vorerst ohne; MyCAD baut dann ohne Handschrift-Erkennung (Zeichnen, Aufräumen und Formen gehen). Später: aus den Quellen
  mit minimalen Optionen (nur CPU, ohne Tests), oder die Handschrift-Erkennung als optionale Flatpak-Erweiterung
  (`io.github.HanreichC.MyCAD.Handwriting`), damit die Haupt-App klein bleibt. Ein fertiges Binär-Archiv statt Quellen
  ist auf Flathub nur mit guter Begründung möglich.
- **Bauzeit:** OCCT + Coin + FreeCAD-Kern dauern lange. Die Flathub-Builder schaffen FreeCAD, also auch MyCAD; lokal
  `ccache` in `flatpak-builder` nutzen (`--ccache`).
- **Größe:** Texturen (Photo-Scans) und HTR-Modell machen die App schwer. Prüfen, ob Texturen in einer niedrigeren
  Auflösung reichen.
- **Nvidia:** Die Flatpak-Runtime holt den passenden GL-Treiber als Erweiterung von selbst, anders als im Container
  (`install.sh` reicht Nvidia-Bibliotheken von Hand durch).
- **Slicer über „Öffnen mit“** ist eine Änderung im Verhalten: Beim ersten Mal fragt das System. Danach merkt es
  sich die Wahl. In der Hilfe erwähnen.
- **Rechte nicht ausweiten:** keine `--filesystem=home`, kein `--talk-name=org.freedesktop.Flatpak`. Beides würde den
  Review verlängern und das Vertrauen kosten.

---

## 8. Pflege nach der Aufnahme

- Neues Release: im MyCAD-Repo taggen (CI), dann im Repo `flathub/io.github.HanreichC.MyCAD` Tag und Commit im
  Manifest erhöhen, `<release>` in der Metainfo ergänzen, PR, nach grünem Bau mergen. Der Flathub-Bot
  (`x-checker-data`) öffnet diese PRs auch selbst, wenn die Metadaten stimmen.
- Abhängigkeiten (OCCT, Coin, Runtime) zieht der Bot ebenfalls nach; nach jeder Runtime-Erhöhung einmal von Hand
  testen.
- Screenshots aktuell halten (feste URLs auf einen Tag, nicht auf `main`).

---

## 9. Reihenfolge der Arbeit (für Plan 12.6)

1. **Erledigt 2026-11-20:** Desktop-Datei, Symbol, Metainfo, MIME in `src/XDGData/` unter der App-ID, per CMake installiert;
   `install.sh` und `tools/appimage.sh` nehmen dieselben Dateien, die Wayland-App-ID ist `io.github.HanreichC.MyCAD`.
   `desktop-file-validate` und `appstreamcli validate` sind grün (Prüfung im Wegwerf-Container, Ubuntu 24.04).
2. **Erledigt 2026-11-20:** Code für die Sandbox: Standard-Projektordner war schon `~/Documents/MyCAD`; Drucken schreibt im
   Flatpak (`/.flatpak-info`) nur das 3MF und öffnet es über das OpenURI-Portal; „Zugriff erlauben“ zeigt im Flatpak den
   Terminal-Befehl für die udev-Regel.
3. **Vorbereitet 2026-11-20:** Manifest `flatpak/io.github.HanreichC.MyCAD.yml` (Module und Patches wie FreeCAD auf
   Flathub, OCCT 8.0.1, Inter; ohne onnxruntime), `flatpak/submission.sh`. Offen: erster Bau grün, von Hand testen.
4. **Angelegt 2026-11-20:** Action `.github/workflows/flatpak.yml` (von Hand und bei Tags), mit Linter.
5. Bei Flathub einreichen, Review begleiten, verifizieren.
6. README: „Install from Flathub“ ganz oben im Download-Abschnitt.

---

## Quellen

- Flathub: [Requirements](https://docs.flathub.org/docs/for-app-authors/requirements),
  [Submission](https://docs.flathub.org/docs/for-app-authors/submission),
  [MetaInfo-Richtlinien](https://docs.flathub.org/docs/for-app-authors/metainfo-guidelines),
  [Qualitätsrichtlinien](https://docs.flathub.org/docs/for-app-authors/metainfo-guidelines/quality-guidelines),
  [Linter](https://docs.flathub.org/docs/for-app-authors/linter),
  [Verifizierung](https://docs.flathub.org/docs/for-app-authors/verification),
  [Pflege](https://docs.flathub.org/docs/for-app-authors/maintenance),
  [Review](https://docs.flathub.org/docs/for-team-members/review)
- Flatpak: [Sandbox Permissions](https://docs.flatpak.org/en/latest/sandbox-permissions.html),
  [flatpak-metadata (device=input)](https://man.archlinux.org/man/flatpak-metadata.5.en.raw),
  [Support for device=input (Flathub Discourse)](https://discourse.flathub.org/t/support-for-device-input/6645),
  [flatpak-spawn](https://www.man7.org/linux/man-pages/man1/flatpak-spawn.1.html),
  [Flatpak in Flatpak starten (Discourse)](https://discourse.flathub.org/t/launching-flatpak-inside-flatpak/5708)
- FreeCAD: [Flatpak-Seite im Wiki](https://wiki.freecad.org/Flatpak), [FreeCAD auf Flathub](https://flathub.org/pl/apps/org.freecad.FreeCAD/install)
