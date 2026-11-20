#!/usr/bin/env bash
# Legt den Ordner für die Einreichung bei Flathub an (Plan 12.6, docs/FLATHUB.md § 6): das Manifest mit festem Tag und
# Commit statt des Arbeitsstands, dazu Patches und Python-Module. Den Ordner kopierst du in deinen Fork von
# github.com/flathub/flathub (Zweig new-pr) und öffnest den Pull Request selbst.
#   flatpak/submission.sh v1.0.400        # Tag muss auf GitHub liegen (die CI legt ihn beim Release an)
set -euo pipefail
TAG="${1:?Tag angeben, z. B. v1.0.400}"
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
OUT="${OUT:-$HOME/flathub-submission}"  # anderer Ort: OUT=… flatpak/submission.sh TAG
COMMIT="$(git -C "$ROOT" ls-remote https://github.com/HanreichC/MyCAD.git "refs/tags/$TAG^{}" | cut -f1)"
[ -n "$COMMIT" ] || COMMIT="$(git -C "$ROOT" ls-remote https://github.com/HanreichC/MyCAD.git "refs/tags/$TAG" | cut -f1)"
[ -n "$COMMIT" ] || { echo "Tag $TAG gibt es auf GitHub nicht." >&2; exit 1; }
rm -rf "$OUT"
mkdir -p "$OUT"
cp -r "$ROOT/flatpak/patches" "$ROOT/flatpak/python3-build-dependencies.yaml" "$OUT/"
# Quelle "dir" (Arbeitsstand) durch das Git-Repo mit Tag und Commit ersetzen; Flathub baut ohne Netz genau diesen Stand
python3 - "$ROOT/flatpak/io.github.HanreichC.MyCAD.yml" "$OUT/io.github.HanreichC.MyCAD.yml" "$TAG" "$COMMIT" <<'EOF'
import re, sys
src, dst, tag, commit = sys.argv[1:]
text = open(src, encoding="utf-8").read()
git = ("      - type: git\n        url: https://github.com/HanreichC/MyCAD.git\n"
       "        tag: %s\n        commit: %s\n" % (tag, commit))
text, n = re.subn(r"      - type: dir[^\n]*\n        path: \.\.\n", git, text)
if n != 1:
    sys.exit("Quelle 'dir' im Manifest nicht gefunden")
open(dst, "w", encoding="utf-8").write(text)
EOF
echo "Fertig: $OUT ($TAG = $COMMIT)"
