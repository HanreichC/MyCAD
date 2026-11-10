#!/usr/bin/env bash
# Alle Tests im Dev-Container, Exit-Code ≠ 0 bei jedem Fehler (CI ruft das vor dem Release auf):
#   podman run --rm -v "$PWD:/workspace" -w /workspace mycad-dev tests/run_all.sh
#   GUI=all tests/run_all.sh           → alle GUI-Tests statt der Auswahl in tests/gui/ci.txt
#   GUI=none tests/run_all.sh          → ohne GUI-Tests;  UNIT=0 → ohne ctest
#   JOBS=8                             → GUI-Tests parallel (je ein eigenes Xvfb)
set -uo pipefail
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"
OUTDIR="${OUTDIR:-$ROOT/build/test-results}"
rm -rf "$OUTDIR"; mkdir -p "$OUTDIR"
failed=()

step() { echo; echo "==> $*"; }

if [ "${UNIT:-1}" != 0 ]; then
    step "Unit-Tests (ctest)"
    # --repeat: zwei MoveProperty-Tests aus FreeCAD stören sich parallel gegenseitig, einzeln laufen sie durch
    ctest --test-dir build --output-on-failure -j"${JOBS:-6}" --repeat until-pass:3 > "$OUTDIR/ctest.txt" 2>&1 || failed+=("ctest")
    tail -3 "$OUTDIR/ctest.txt"
fi

step "Logik-Checks ohne FreeCAD"
for src in tests/*_check.cpp; do
    name="$(basename "$src" .cpp)"
    if [ "$name" = scribble_read_check ]; then
        g++ -std=c++20 -fPIC -DMYCAD_HTR -I src -I src/Mod/Design/Gui $(pkg-config --cflags Qt6Gui) -I /usr/include/onnxruntime \
            "$src" src/Mod/Design/Gui/ScribbleRead.cpp $(pkg-config --libs Qt6Gui) -lonnxruntime -o "$OUTDIR/$name" \
            && QT_QPA_PLATFORM=offscreen "$OUTDIR/$name" build/src/Mod/Design/Gui/htr/model.onnx > "$OUTDIR/$name.txt" 2>&1
    else
        g++ -std=c++20 -I src "$src" -o "$OUTDIR/$name" && "$OUTDIR/$name" > "$OUTDIR/$name.txt" 2>&1
    fi
    if [ $? -eq 0 ]; then echo "ok   $name"; else echo "FAIL $name"; failed+=("$name"); fi
done

step "Hilfe aus tools/help_content.py erzeugt"
python3 tools/help_content.py --check || failed+=("help")

step "Headless-Tests (tests/design)"
tests/design/run.sh > "$OUTDIR/design.txt" 2>&1 || failed+=("design")
grep -E '^(Ran|OK|FAILED)|(ERROR|FAIL):' "$OUTDIR/design.txt"

if [ "${GUI:-ci}" != none ]; then
    step "GUI-Tests (${GUI:-ci})"
    if [ "${GUI:-ci}" = all ]; then list=(tests/gui/test_*.py); else mapfile -t list < <(grep -v '^#' tests/gui/ci.txt | sed '/^$/d; s|^|tests/gui/|'); fi
    export OUTDIR
    printf '%s\n' "${list[@]}" | xargs -P "${JOBS:-6}" -I{} sh -c \
        'n=$(basename {} .py); export MYCAD_HOME="$OUTDIR/home-$n"
         grep -q "^# runs: 2" {} && tests/gui/run.sh {} "$OUTDIR/$n-first" > /dev/null 2>&1  # z. B. erst Sprache umstellen
         tests/gui/run.sh {} "$OUTDIR/$n" > /dev/null 2>&1; true'
    for t in "${list[@]}"; do
        n="$(basename "$t" .py)"
        if [ ! -s "$OUTDIR/$n.txt" ] || grep -q '^FAIL\|exc ' "$OUTDIR/$n.txt" || ! grep -q '^step done' "$OUTDIR/$n.txt"; then
            echo "FAIL $n"; failed+=("$n")
        else
            echo "ok   $n"
        fi
    done
fi

echo
if [ ${#failed[@]} -eq 0 ]; then echo "Alle Tests grün."; exit 0; fi
echo "Fehlgeschlagen: ${failed[*]}"; exit 1
