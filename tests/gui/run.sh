#!/usr/bin/env bash
# GUI-Test im Container: startet MyCAD mit einem Testskript (echte Klicks), Protokoll nach <out>.txt
#   tests/gui/run.sh tests/gui/test_features.py /tmp/out   → /tmp/out.txt, /tmp/out.png, /tmp/out.log
#   Läuft mit eigenem Home (build/testhome): Tests hängen nicht von deinen Einstellungen ab und ändern sie nicht.
#   MYCAD_HOME=/tmp/home tests/gui/run.sh …               → anderes Home (z. B. frisch für Sprachtests)
#   MYCAD_TIMEOUT=900 tests/gui/run.sh …                  → länger laufen lassen (Standard 180 s)
set -euo pipefail
ROOTDIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
APPHOME="${MYCAD_HOME:-$ROOTDIR/build/testhome}"
mkdir -p "$APPHOME"
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
SCRIPT="$(realpath "$1")"; OUT="$(realpath -m "$2")"
mkdir -p "$(dirname "$OUT")"
timeout "${MYCAD_TIMEOUT:-180}" podman run --rm --userns=keep-id --group-add keep-groups --device /dev/dri \
    -v "$ROOT:/workspace" -v "$APPHOME:$APPHOME" -v "$(dirname "$OUT"):$(dirname "$OUT")" -v "$(dirname "$SCRIPT"):$(dirname "$SCRIPT")" \
    -v "$XDG_RUNTIME_DIR/$WAYLAND_DISPLAY:/tmp/runtime/$WAYLAND_DISPLAY" \
    -e HOME="$APPHOME" -e XDG_RUNTIME_DIR=/tmp/runtime -e WAYLAND_DISPLAY="$WAYLAND_DISPLAY" -e QT_QPA_PLATFORM=wayland \
    -e OUT="$OUT" -e HELP_ONLY="${HELP_ONLY:-}" -e PYTHONPATH="$(dirname "$SCRIPT")" \
    mycad-dev /workspace/build/bin/FreeCAD "$SCRIPT" > "$OUT.log" 2>&1 || true
cat "$OUT.txt"
