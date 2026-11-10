#!/usr/bin/env bash
# Headless-Tests des Design-Moduls (FreeCADCmd, ohne Oberfläche). Läuft im Dev-Container:
#   podman run --rm -v "$PWD:/workspace" -w /workspace mycad-dev tests/design/run.sh
#   PATTERN=test_extrude.py tests/design/run.sh   → nur diese Datei
set -euo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/../.." && pwd)"
HOME="$(mktemp -d)" PATTERN="${PATTERN:-}" "$ROOT/build/bin/FreeCADCmd" "$ROOT/tests/design/runner.py"
