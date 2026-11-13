#!/usr/bin/env bash
# Ist der Build älter als der Code? Gibt die Quellen aus, deren Stand noch nicht gebaut ist (leer = aktuell).
# Läuft im Dev-Container (ninja). Der Versionsstempel (version_file, Version.h) gilt bei jedem Build als neu und zählt
# nicht: sonst wäre der Build nie aktuell.
#   tests/build_stale.sh            → Liste der ungebauten Quellen, Exit 0
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
[ -f "$ROOT/build/build.ninja" ] || { echo "build/ fehlt"; exit 0; }
ninja -C "$ROOT/build" -n -d explain 2>&1 \
    | sed -n 's/^ninja explain: .* older than most recent input \(.*\) ([0-9]* vs [0-9]*)$/\1/p' \
    | grep -v -e '/build/src/Build/Version' -e 'version_file' \
    | grep -v "^$ROOT/build/" \
    | sort -u
