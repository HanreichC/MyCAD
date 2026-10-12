#!/usr/bin/env bash
# MyCAD als AppImage verpacken. Läuft im Dev-Container (.devcontainer) als root, nach dem Build:
#   tools/appimage.sh 1.0.3      → MyCAD-1.0.3-x86_64.AppImage im Repo-Ordner
# Läuft nur auf Systemen mit mindestens so neuer glibc wie im (Arch-)Container, also z. B. CachyOS/Arch.
set -euo pipefail

VERSION="${1:-dev}"
ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
WORK="$ROOT/build-appimage"
APPDIR="$WORK/AppDir"
PY="python$(python3 -c 'import sys; print(f"{sys.version_info[0]}.{sys.version_info[1]}")')"
SITE="/usr/lib/$PY/site-packages"

rm -rf "$APPDIR"
mkdir -p "$APPDIR" "$WORK/tools"

echo "==> Installieren"
cmake --install "$ROOT/build" --prefix "$APPDIR/usr" >/dev/null

echo "==> Python (Standardbibliothek + benötigte Pakete)"
mkdir -p "$APPDIR/usr/lib/$PY/site-packages"
(cd "/usr/lib/$PY" && tar --exclude=site-packages --exclude=test --exclude=__pycache__ --exclude=idlelib \
    --exclude=tkinter --exclude=turtledemo --exclude='config-*' -cf - .) | tar -C "$APPDIR/usr/lib/$PY" -xf -
for pkg in PySide6 shiboken6 pivy yaml _yaml packaging freecad; do
    [ -e "$SITE/$pkg" ] && cp -a "$SITE/$pkg" "$APPDIR/usr/lib/$PY/site-packages/"
done
# nur die PySide6-Module, die MyCAD nutzt (sonst kämen Qt Quick, SQL-Treiber, 3D … mit)
KEEP=" QtCore QtGui QtWidgets QtSvg QtSvgWidgets QtOpenGL QtOpenGLWidgets QtNetwork QtPrintSupport QtUiTools QtXml QtConcurrent "
for so in "$APPDIR/usr/lib/$PY/site-packages/PySide6"/Qt*.so; do
    name="$(basename "$so")"
    name="${name%%.*}"
    [[ "$KEEP" == *" $name "* ]] || rm -f "$so" "$(dirname "$so")/$name.pyi"
done

echo "==> Schrift, Icon, Starter"
mkdir -p "$APPDIR/usr/share/fonts"
cp /usr/share/fonts/inter/Inter.ttc "$APPDIR/usr/share/fonts/"  # Familie "Inter" (die variable Datei heißt anders)
cp "$ROOT/src/Gui/Icons/mycad.svg" "$WORK/mycad.svg"
cat > "$WORK/mycad.desktop" <<EOF
[Desktop Entry]
Type=Application
Name=MyCAD
Comment=Parametric CAD
Exec=FreeCAD %F
Icon=mycad
Terminal=false
Categories=Graphics;Engineering;
StartupWMClass=mycad
X-AppImage-Version=$VERSION
EOF
cat > "$WORK/AppRun" <<EOF
#!/bin/sh
HERE="\$(dirname "\$(readlink -f "\$0")")"
# wie im Dev-Container: Oberfläche englisch, Farbschema und Sprache nicht vom Desktop übernehmen
export LC_ALL=C.UTF-8 LANG=C.UTF-8
export PYTHONHOME="\$HERE/usr"
export PYTHONPATH="\$HERE/usr/lib/$PY/site-packages\${PYTHONPATH:+:\$PYTHONPATH}"
export LD_LIBRARY_PATH="\$HERE/usr/lib\${LD_LIBRARY_PATH:+:\$LD_LIBRARY_PATH}"
exec "\$HERE/usr/bin/FreeCAD" "\$@"
EOF
chmod +x "$WORK/AppRun"

echo "==> Abhängigkeiten bündeln (linuxdeploy)"
for tool in linuxdeploy-x86_64.AppImage linuxdeploy-plugin-qt-x86_64.AppImage; do
    [ -x "$WORK/tools/$tool" ] || {
        curl -fsSL -o "$WORK/tools/$tool" \
            "https://github.com/linuxdeploy/${tool%-x86_64.AppImage}/releases/download/continuous/$tool"
        chmod +x "$WORK/tools/$tool"
    }
done
export APPIMAGE_EXTRACT_AND_RUN=1 ARCH=x86_64 PATH="$WORK/tools:$PATH"
export NO_STRIP=1  # Arch-Bibliotheken sind schon gestrippt; das strip in linuxdeploy kennt deren ELF-Format nicht
export QMAKE=/usr/lib/qt6/bin/qmake
export EXTRA_PLATFORM_PLUGINS="libqwayland.so;libqxcb.so"
export EXTRA_QT_MODULES="svg;waylandclient"
export LDAI_OUTPUT="$ROOT/MyCAD-$VERSION-x86_64.AppImage"
rm -f "$LDAI_OUTPUT"
# Wayland vollständig mitnehmen: OpenGL über wayland-egl, Fenster über xdg-shell (linuxdeploy nimmt nur einen Teil)
mkdir -p "$APPDIR/usr/plugins"
for d in wayland-graphics-integration-client wayland-shell-integration wayland-decoration-client; do
    cp -a "/usr/lib/qt6/plugins/$d" "$APPDIR/usr/plugins/"
done
deps=()
for d in "$APPDIR/usr/plugins"/*/ "$APPDIR/usr/lib" "$APPDIR/usr/lib/$PY/lib-dynload" "$APPDIR/usr/lib/$PY/site-packages"/*/ "$APPDIR/usr/Mod"/*/; do
    [ -d "$d" ] && deps+=(--deploy-deps-only "$d")
done
cd "$WORK"
# 1. Bibliotheken bündeln; dafür müssen MyCADs eigene Bibliotheken gefunden werden (setzt dabei relative RPATHs)
LD_LIBRARY_PATH="$APPDIR/usr/lib" linuxdeploy-x86_64.AppImage --appdir "$APPDIR" -e "$APPDIR/usr/bin/FreeCAD" \
    -d mycad.desktop -i mycad.svg "${deps[@]}"
# 2. Qt-Plugins, ohne den Pfad: qmake ist relokierbar und meldete sonst Pfade im AppDir
linuxdeploy-x86_64.AppImage --appdir "$APPDIR" --plugin qt --custom-apprun AppRun
# MyCAD ist immer hell: kein Desktop-Portal-Theme (das meldet ein dunkles KDE an FreeCADs Ersteinrichtung)
rm -rf "$APPDIR/usr/plugins/platformthemes"
# 3. AppImage packen
linuxdeploy-x86_64.AppImage --appdir "$APPDIR" --custom-apprun AppRun --output appimage
echo "==> Fertig: $LDAI_OUTPUT"
