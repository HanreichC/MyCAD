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
# Nicht still alten Code testen: ist eine Quelle neuer als der Build, abbrechen (ALLOW_STALE=1 übergeht das)
if [ -z "${ALLOW_STALE:-}" ]; then
    if [ -e /run/.containerenv ] || [ -e /.dockerenv ]; then stale="$("$ROOT/tests/build_stale.sh")"
    else stale="$(podman run --rm -v "$ROOT:/workspace" -w /workspace mycad-dev tests/build_stale.sh)"; fi
    if [ -n "$stale" ]; then
        { echo "FAIL build is not up to date, build first (or ALLOW_STALE=1). Newer than the build:"; echo "$stale" | head -10; } > "$OUT.txt"
        cat "$OUT.txt"; exit 1
    fi
fi
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
    # Bildschirmfotos vom echten Bildschirm (Compositor) auf Anfrage des Tests (harness.screen_shot): legt er
    # <OUT>.screen-<Name>.request an, entsteht <OUT>.screen-<Name>.png. Unter Xvfb gibt es das nicht.
    WATCH=""
    if command -v spectacle > /dev/null && [ -z "${NO_SCREEN:-}" ]; then
        PASS+=(-e MYCAD_SCREEN=1)
        ( while :; do
              for r in "$OUT".screen-*.request; do
                  [ -e "$r" ] || continue
                  b="${r%.request}"; rm -f "$r"
                  spectacle -b -n -f -o "$b.part.png" > /dev/null 2>&1; mv -f "$b.part.png" "$b.png" 2> /dev/null
              done
              sleep 0.05
          done ) &
        WATCH=$!
    fi
    timeout "${MYCAD_TIMEOUT:-180}" podman run --rm --userns=keep-id --group-add keep-groups --device /dev/dri \
        -v "$ROOT:/workspace" -v "$APPHOME:$APPHOME" -v "$(dirname "$OUT"):$(dirname "$OUT")" -v "$(dirname "$SCRIPT"):$(dirname "$SCRIPT")" \
        -v "$XDG_RUNTIME_DIR/$WAYLAND_DISPLAY:/tmp/runtime/$WAYLAND_DISPLAY" \
        -e XDG_RUNTIME_DIR=/tmp/runtime -e WAYLAND_DISPLAY="$WAYLAND_DISPLAY" -e QT_QPA_PLATFORM=wayland \
        "${PASS[@]}" \
        mycad-dev /workspace/build/bin/FreeCAD "$SCRIPT" > "$OUT.log" 2>&1 || true
    [ -n "$WATCH" ] && kill "$WATCH" 2> /dev/null
fi
# Log-Wächter: Meldungen, hinter denen Fehlerklassen stecken (Abhängigkeitskreis, Endlos-Neuberechnung, Rechnen im
# Rechnen, Absturz, Python-Fehler), standen sonst nur im Log; so blieb der Kreis aus "Monitor Light" unbemerkt.
# Ein Test, der eine davon absichtlich auslöst, nennt sie in einer Zeile "# log-ok: <Text>".
LOG_BAD='graph must be a DAG|still touched after recompute|Recursive calling of recompute|Program received signal|Unhandled .* caught|ActiveDialog was null|^Traceback'
grep -E "$LOG_BAD" "$OUT.log" 2> /dev/null | { ok="$(sed -n 's/^# log-ok: //p' "$SCRIPT")"; if [ -n "$ok" ]; then grep -v -F "$ok"; else cat; fi; } \
    | sort | uniq -c | sed 's/^ *\([0-9]*\) /FAIL log (\1x): /' >> "$OUT.txt" || true
cat "$OUT.txt"
