#!/usr/bin/env bash
# GUI-Test: startet MyCAD mit einem Testskript (echte Klicks), Protokoll nach <out>.txt
#   tests/gui/run.sh tests/gui/test_features.py /tmp/out   → /tmp/out.txt, /tmp/out.png, /tmp/out.log
#   Läuft mit eigenem Home (build/testhome): Tests hängen nicht von deinen Einstellungen ab und ändern sie nicht.
#   MYCAD_HOME=/tmp/home tests/gui/run.sh …               → anderes Home (z. B. frisch für Sprachtests)
#   MYCAD_TIMEOUT=900 tests/gui/run.sh …                  → länger laufen lassen (Standard 180 s)
# Auf dem Desktop startet es den Dev-Container mit Wayland. Schon im Container (CI, Dev Container) läuft MyCAD direkt,
# ohne WAYLAND_DISPLAY unter Xvfb.
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
APPHOME="${MYCAD_HOME:-$ROOT/build/testhome}"
mkdir -p "$APPHOME"
SCRIPT="$(realpath "$1")"; OUT="$(realpath -m "$2")"
mkdir -p "$(dirname "$OUT")"
ENV=(HOME="$APPHOME" OUT="$OUT" LANGWANT="${LANGWANT:-}" HELP_ONLY="${HELP_ONLY:-}" HELP_DUMP="${HELP_DUMP:-}"
     PYTHONPATH="$(dirname "$SCRIPT")")
if [ -e /run/.containerenv ] || [ -e /.dockerenv ]; then
    if [ -n "${WAYLAND_DISPLAY:-}" ]; then
        env "${ENV[@]}" QT_QPA_PLATFORM=wayland timeout "${MYCAD_TIMEOUT:-180}" \
            "$ROOT/build/bin/FreeCAD" "$SCRIPT" > "$OUT.log" 2>&1 || true
    else
        env "${ENV[@]}" QT_QPA_PLATFORM=xcb LIBGL_ALWAYS_SOFTWARE=1 timeout "${MYCAD_TIMEOUT:-180}" \
            xvfb-run -n $((100 + $$)) -s "-screen 0 1600x1000x24" "$ROOT/build/bin/FreeCAD" "$SCRIPT" > "$OUT.log" 2>&1 || true
    fi
else
    PASS=(); for e in "${ENV[@]}"; do PASS+=(-e "$e"); done
    timeout "${MYCAD_TIMEOUT:-180}" podman run --rm --userns=keep-id --group-add keep-groups --device /dev/dri \
        -v "$ROOT:/workspace" -v "$APPHOME:$APPHOME" -v "$(dirname "$OUT"):$(dirname "$OUT")" -v "$(dirname "$SCRIPT"):$(dirname "$SCRIPT")" \
        -v "$XDG_RUNTIME_DIR/$WAYLAND_DISPLAY:/tmp/runtime/$WAYLAND_DISPLAY" \
        -e XDG_RUNTIME_DIR=/tmp/runtime -e WAYLAND_DISPLAY="$WAYLAND_DISPLAY" -e QT_QPA_PLATFORM=wayland \
        "${PASS[@]}" \
        mycad-dev /workspace/build/bin/FreeCAD "$SCRIPT" > "$OUT.log" 2>&1 || true
fi
cat "$OUT.txt"
