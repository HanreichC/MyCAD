#!/usr/bin/env bash
# Baut MyCAD im Podman-Container und legt den Starter `mycad` + Menüeintrag an.
# Nichts wird global installiert (siehe CLAUDE.md). Nochmal ausführen = inkrementell neu bauen.
#   JOBS=6 ./install.sh     # Anzahl paralleler Compiler (Standard 6, läuft mit niedrigster Priorität)
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
JOBS="${JOBS:-6}"
IMAGE=mycad-dev
BIN="$HOME/.local/bin/mycad"
DESKTOP="$HOME/.local/share/applications/mycad.desktop"

echo "==> Container-Image bauen"
podman build -q -t "$IMAGE" "$ROOT/.devcontainer" >/dev/null

# Nach Absturz/Stromausfall bleiben leere Objektdateien liegen, an denen der Linker scheitert.
find "$ROOT/build" \( -name '*.o' -o -name '*.so' -o -name '*.a' \) -size 0 -delete 2>/dev/null || true

run() { podman run --rm --userns=keep-id -v "$ROOT:/workspace" -w /workspace \
            -e CCACHE_DIR=/workspace/.ccache "$IMAGE" "$@"; }

echo "==> Konfigurieren"
[ -f "$ROOT/build/build.ninja" ] || run cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -Wno-dev

echo "==> Bauen mit $JOBS Kernen (niedrige Priorität)"
run nice -n 19 cmake --build build -j"$JOBS"

echo "==> Starter anlegen: $BIN"
mkdir -p "$(dirname "$BIN")" "$(dirname "$DESKTOP")"
cat > "$BIN" <<EOF
#!/usr/bin/env bash
# MyCAD im Container starten: Wayland + GPU durchgereicht, Home gemountet (Dateien öffnen/speichern, Einstellungen).
exec podman run --rm --userns=keep-id --group-add keep-groups \\
    --device /dev/dri \\
    -v "$ROOT:/workspace" -v "\$HOME:\$HOME" -w "\$PWD" \\
    -v "\$XDG_RUNTIME_DIR/\$WAYLAND_DISPLAY:/tmp/runtime/\$WAYLAND_DISPLAY" \\
    -e HOME="\$HOME" -e XDG_RUNTIME_DIR=/tmp/runtime -e WAYLAND_DISPLAY="\$WAYLAND_DISPLAY" \\
    -e QT_QPA_PLATFORM=wayland \\
    $IMAGE /workspace/build/bin/FreeCAD "\$@"
EOF
chmod +x "$BIN"

ICON_DIR="$HOME/.local/share/icons/hicolor/scalable/apps"
mkdir -p "$ICON_DIR"
cp "$ROOT/src/Gui/Icons/mycad.svg" "$ICON_DIR/mycad.svg"

cat > "$DESKTOP" <<EOF
[Desktop Entry]
Type=Application
Name=MyCAD
StartupWMClass=mycad
Comment=Parametric CAD
Exec=$BIN %F
Icon=mycad
Terminal=false
Categories=Graphics;Engineering;3DGraphics;
MimeType=application/x-mycad;
EOF

# Dateityp .mycad: eigenes Symbol, Doppelklick öffnet MyCAD (Inhalt wie FreeCADs .FCStd)
MIME="$HOME/.local/share/mime"
mkdir -p "$MIME/packages"
cat > "$MIME/packages/mycad.xml" <<EOF
<?xml version="1.0" encoding="UTF-8"?>
<mime-info xmlns="http://www.freedesktop.org/standards/shared-mime-info">
  <mime-type type="application/x-mycad">
    <comment>MyCAD design</comment>
    <comment xml:lang="de">MyCAD-Design</comment>
    <icon name="mycad"/>
    <glob pattern="*.mycad"/>
  </mime-type>
</mime-info>
EOF
command -v update-mime-database >/dev/null && update-mime-database "$MIME" || true
command -v update-desktop-database >/dev/null && update-desktop-database "$(dirname "$DESKTOP")" || true
command -v xdg-mime >/dev/null && xdg-mime default mycad.desktop application/x-mycad || true

# KDE-Cache der Menüeinträge/Icons auffrischen, sonst zeigt die Taskleiste noch das alte Icon
command -v kbuildsycoca6 >/dev/null && kbuildsycoca6 >/dev/null 2>&1 || true

echo "==> Fertig. Starten mit: mycad   (oder über das App-Menü)"
case ":$PATH:" in *":$HOME/.local/bin:"*) ;; *) echo "    Hinweis: ~/.local/bin ist nicht im PATH.";; esac
