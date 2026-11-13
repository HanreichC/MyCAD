#!/usr/bin/env bash
# Headless-Tests des Design-Moduls (FreeCADCmd, ohne Oberfläche). Läuft im Dev-Container:
#   podman run --rm -v "$PWD:/workspace" -w /workspace mycad-dev tests/design/run.sh
#   PATTERN=test_extrude.py tests/design/run.sh   → nur diese Datei
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
# Nicht still alten Code testen: ist eine Quelle neuer als der Build, abbrechen (ALLOW_STALE=1 übergeht das)
stale="$("$ROOT/tests/build_stale.sh")"
if [ -n "$stale" ] && [ -z "${ALLOW_STALE:-}" ]; then
    echo "FAIL build is not up to date, build first (or ALLOW_STALE=1). Newer than the build:"; echo "$stale" | head -10
    exit 1
fi
HOME="$(mktemp -d)" PATTERN="${PATTERN:-}" "$ROOT/build/bin/FreeCADCmd" "$ROOT/tests/design/runner.py"
