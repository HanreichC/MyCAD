#!/usr/bin/env bash
# Baut MyCAD im Podman- oder Docker-Container und legt den Starter `mycad` + Menüeintrag an.
# Nichts wird global installiert (siehe CLAUDE.md). Nochmal ausführen = inkrementell neu bauen.
#   JOBS=6 ./install.sh            # Anzahl paralleler Compiler (Standard 8, läuft mit niedrigster Priorität)
#   ENGINE=docker ./install.sh     # Docker statt Podman (ohne Angabe: Podman, wenn vorhanden, sonst Docker)
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
JOBS="${JOBS:-8}"
IMAGE=mycad-dev
BIN="$HOME/.local/bin/mycad"
APP_ID=io.github.HanreichC.MyCAD  # wie Flatpak und AppImage: Dateien aus src/XDGData (Plan 12.6)
DESKTOP="$HOME/.local/share/applications/$APP_ID.desktop"
ENGINE="${ENGINE:-$(command -v podman >/dev/null && echo podman || echo docker)}"
command -v "$ENGINE" >/dev/null || { echo "Weder Podman noch Docker gefunden: eins davon installieren." >&2; exit 1; }
# Dateien im Repo und im Home gehören dem Benutzer, nicht root: Podman bildet ihn ab (keep-id), Docker läuft als er,
# mit seinen Gruppen (video/render für die GPU, input für das Touchpad)
if [ "$ENGINE" = podman ]; then
    AS_USER=(--userns=keep-id)
    WITH_GROUPS="--userns=keep-id --group-add keep-groups"
else
    AS_USER=(--user "$(id -u):$(id -g)")
    # Benutzer und Gruppen des Rechners nur lesend hinein: sonst kennt der Container die Id nicht, und MyCAD scheitert
    # beim Start mit "Getting HOME path from system failed" (Podman trägt den Benutzer bei keep-id selbst ein)
    WITH_GROUPS="--user $(id -u):$(id -g)$(for g in $(id -G); do printf ' --group-add %s' "$g"; done)"
    WITH_GROUPS="$WITH_GROUPS -v /etc/passwd:/etc/passwd:ro -v /etc/group:/etc/group:ro"
fi

# Untermodule (OndselSolver, der Gelenk-Löser): fehlen sie, weil ohne --recursive geklont wurde, scheitert CMake mit
# einer unverständlichen Meldung. Hier holen statt in der Anleitung zu hoffen.
if [ -d "$ROOT/.git" ] && command -v git >/dev/null; then
    git -C "$ROOT" submodule update --init --recursive
fi

echo "==> Container-Image bauen ($ENGINE)"
"$ENGINE" build -q -t "$IMAGE" "$ROOT/.devcontainer" >/dev/null

# Nach Absturz/Stromausfall bleiben leere Objektdateien liegen, an denen der Linker scheitert.
find "$ROOT/build" \( -name '*.o' -o -name '*.so' -o -name '*.a' \) -size 0 -delete 2>/dev/null || true

run() { "$ENGINE" run --rm "${AS_USER[@]}" -v "$ROOT:/workspace" -w /workspace \
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
# Nvidia: im Image ist nur Mesa, und der Treiber muss exakt zum Kernelmodul passen, also den vom Rechner hineinreichen.
# AMD und Intel laufen über Mesa aus dem Image. Welche GPU genutzt wird, entscheidet MyCAD beim Start.
GPU=()
[ -e /dev/dri ] && GPU+=(--device /dev/dri)
# WSL (Linux unter Windows): die GPU heißt /dev/dxg, Mesa (d3d12) braucht Microsofts Bibliotheken aus /usr/lib/wsl
if [ -e /dev/dxg ]; then
    GPU+=(--device /dev/dxg -v /usr/lib/wsl:/usr/lib/wsl:ro -e LD_LIBRARY_PATH=/usr/lib/wsl/lib)
fi
NVIDIA=()
if [ -e /dev/nvidiactl ]; then
    for dev in /dev/nvidia0 /dev/nvidiactl /dev/nvidia-modeset /dev/nvidia-uvm; do
        [ -e "\$dev" ] && NVIDIA+=(--device "\$dev")
    done
    shopt -s nullglob
    for file in /usr/lib/lib{GLX,EGL,GLESv2,GLESv1_CM}_nvidia.so* /usr/lib/libnvidia-*.so* /usr/lib/gbm/nvidia-drm_gbm.so \\
                /usr/share/glvnd/egl_vendor.d/10_nvidia.json /usr/share/egl/egl_external_platform.d/*; do
        NVIDIA+=(-v "\$file:\$file:ro")
    done
fi
# Slicer zum Drucken: Programmordner des Rechners nur lesend unter /run/host, zum Finden; gestartet werden sie über die
# Sitzungs-D-Bus beim Flatpak-Session-Helper des Rechners (DesignExport.host_spawn). Damit kann der Container Programme
# auf dem Rechner starten (bewusst so entschieden; das Home ist ohnehin beschreibbar eingebunden)
HOST=()
for dir in /usr/bin /usr/local/bin /var/lib/flatpak/app; do
    [ -d "\$dir" ] && HOST+=(-v "\$dir:/run/host\$dir:ro")
done
# /dev/input + /run/udev: Touchpad selbst lesen (3 Finger drehen), braucht die udev-Regel aus jomaa.kb96trackpad.config
exec $ENGINE run --rm $WITH_GROUPS \\
    "\${GPU[@]}" "\${NVIDIA[@]}" "\${HOST[@]}" \\
    -v "$ROOT:/workspace" -v "\$HOME:\$HOME" -w "\$PWD" \\
    -v "\$XDG_RUNTIME_DIR/\$WAYLAND_DISPLAY:/tmp/runtime/\$WAYLAND_DISPLAY" \\
    -v "\$XDG_RUNTIME_DIR/bus:/tmp/runtime/bus" -e DBUS_SESSION_BUS_ADDRESS=unix:path=/tmp/runtime/bus \\
    -e MYCAD_HOST_ROOT=/run/host \\
    -v /dev/input:/dev/input:ro -v /run/udev:/run/udev:ro \\
    -e HOME="\$HOME" -e XDG_RUNTIME_DIR=/tmp/runtime -e WAYLAND_DISPLAY="\$WAYLAND_DISPLAY" \\
    -e QT_QPA_PLATFORM=wayland \\
    $IMAGE /workspace/build/bin/FreeCAD "\$@"
EOF
chmod +x "$BIN"

ICON_DIR="$HOME/.local/share/icons/hicolor/scalable/apps"
mkdir -p "$ICON_DIR"
cp "$ROOT/src/Gui/Icons/mycad.svg" "$ICON_DIR/$APP_ID.svg"
# Menüeintrag und Dateityp .mycad aus dem Repo; nur der Starter ist hier ein anderer
sed "s|^Exec=.*|Exec=$BIN %F|" "$ROOT/src/XDGData/$APP_ID.desktop" > "$DESKTOP"
MIME="$HOME/.local/share/mime"
mkdir -p "$MIME/packages"
cp "$ROOT/src/XDGData/$APP_ID.xml" "$MIME/packages/$APP_ID.xml"
# frühere Namen (vor Plan 12.6) weg, sonst stünde MyCAD zweimal im Menü
rm -f "$HOME/.local/share/applications/mycad.desktop" "$ICON_DIR/mycad.svg" "$MIME/packages/mycad.xml"
command -v update-mime-database >/dev/null && update-mime-database "$MIME" || true
command -v update-desktop-database >/dev/null && update-desktop-database "$(dirname "$DESKTOP")" || true
command -v xdg-mime >/dev/null && xdg-mime default "$APP_ID.desktop" application/x-mycad || true

# KDE-Cache der Menüeinträge/Icons auffrischen, sonst zeigt die Taskleiste noch das alte Icon
command -v kbuildsycoca6 >/dev/null && kbuildsycoca6 >/dev/null 2>&1 || true

# Tasten am Grafiktablett (Einstellungen › Tablett): MyCAD liest sie im Container selbst aus /dev/input. Lesbar macht sie
# eine udev-Regel wie die fürs Touchpad (uaccess für den angemeldeten Benutzer), nur für die Tasten-Geräte von
# Tabletts, nie für Tastaturen. Einmalig mit sudo, nur wenn ein Tablett angeschlossen ist und die Regel fehlt.
# Gleiche Regel wie "Zugriff erlauben" in src/Gui/Shell/Settings.cpp (dort für MyCAD außerhalb des Containers)
TABLET_RULE=/etc/udev/rules.d/70-mycad-tablet.rules
if [ ! -f "$TABLET_RULE" ] && [ -t 0 ] && command -v udevadm >/dev/null \
    && udevadm info --export-db 2>/dev/null | grep -q '^E: ID_INPUT_TABLET_PAD=1'; then
    echo "==> Grafiktablett gefunden: damit MyCAD seine Tasten lesen darf, legt sudo einmal $TABLET_RULE an"
    printf '%s\n' 'ACTION!="remove", SUBSYSTEM=="input", KERNEL=="event*", ENV{ID_INPUT_TABLET_PAD}=="1", TAG+="uaccess"' \
        | sudo tee "$TABLET_RULE" >/dev/null \
        && sudo udevadm control --reload && sudo udevadm trigger --subsystem-match=input \
        || echo "    Übersprungen. Ohne die Regel kann MyCAD die Tasten am Tablett nicht lesen (der Stift geht trotzdem)."
fi

echo "==> Fertig. Starten mit: mycad   (oder über das App-Menü)"
case ":$PATH:" in *":$HOME/.local/bin:"*) ;; *) echo "    Hinweis: ~/.local/bin ist nicht im PATH.";; esac
