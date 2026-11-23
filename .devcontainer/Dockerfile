# Arch-Basis, damit die gebauten Binaries auch auf dem CachyOS-Host laufen.
# Fester Stand: Basis-Image und Paketquelle (Arch Linux Archive) auf ein Datum gepinnt, damit ein Update von OCCT,
# Qt oder Python den Build nicht über Nacht bricht. Aktualisieren = beide Daten anheben, Tests laufen lassen.
FROM docker.io/library/archlinux:base-devel-20261101.0.620205
RUN echo 'Server = https://archive.archlinux.org/repos/2026/11/09/$repo/os/$arch' > /etc/pacman.d/mirrorlist

# Build-Toolchain + Abhängigkeiten von Base/App/Gui/Part/Sketcher/PartDesign/Import/Mesh.
# mesa/glu: OpenGL für Coin im Container (Intel-iGPU über /dev/dri).
# xorg-server-xvfb/xorg-xauth: GUI-Tests ohne Desktop (CI), siehe tests/gui/run.sh
# heaptrack: Speicher-Profil (PLAN U8: was nach dem Schließen eines Designs liegen bleibt)
# OCCT, Coin und Pivy kommen nicht aus Arch, sondern unten aus den Quellen (PLAN U20/U21)
# Das Archiv ist manchmal minutenlang zäh ("Operation too slow"): bis zu fünf Versuche statt eines roten CI-Laufs
RUN for try in 1 2 3 4 5; do \
        pacman -Syyu --noconfirm --needed \
            cmake ninja ccache git pkgconf python gtest \
            boost eigen nlohmann-json microsoft-gsl pybind11 swig rapidjson \
            qt6-base qt6-declarative qt6-shadertools qt6-svg qt6-tools qt6-wayland onnxruntime-cpu \
            pyside6 shiboken6 xerces-c yaml-cpp fmt icu freetype2 zlib \
            python-yaml python-packaging python-matplotlib \
            mesa glu libglvnd ttf-dejavu inter-font \
            xorg-server-xvfb xorg-xauth heaptrack \
        && break; \
        [ "$try" = 5 ] && exit 1; echo "pacman: Versuch $try gescheitert, neuer Versuch in 60 s"; sleep 60; \
    done \
    && pacman -Scc --noconfirm

# U20: OCCT 8 (Arch liefert nur 7.9.3). Behebt Abstürze in Rundung/Fase an Ecken nach Booleans und an Ellipsen,
# Hänger in MakeFillet, Abstürze bei Fuse an Lofts, in PipeShell und UnifySameDomain (Refine), STEP-Import; schneller
# bei Booleans, B-Splines und STEP. Ohne Draw (Tcl-Testkonsole), sonst alle Module, die FreeCAD verlangt
# (cMake/FindOCC.cmake: Visualisierung, Datenaustausch, OCAF).
ARG OCCT_TAG=V8.0.1
RUN git clone --depth 1 --branch ${OCCT_TAG} https://github.com/Open-Cascade-SAS/OCCT.git /tmp/occt \
    && cmake -S /tmp/occt -B /tmp/occt/build -G Ninja -Wno-dev \
        -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr -DINSTALL_DIR_LAYOUT=Unix \
        -DBUILD_MODULE_Draw=OFF -DBUILD_DOC_Overview=OFF -DBUILD_SAMPLES_QT=OFF \
        -DUSE_FREETYPE=ON -DUSE_RAPIDJSON=ON -DUSE_TK=OFF -DUSE_TBB=OFF -DUSE_FREEIMAGE=OFF -DUSE_VTK=OFF \
    && cmake --build /tmp/occt/build \
    && cmake --install /tmp/occt/build \
    && rm -rf /tmp/occt

# U21: Coin 4.0.10 (Arch: 4.0.4). 4.0.6 korrigiert EGL/GLX unter Wayland, 4.0.8 umgeht einen Intel-Treiberfehler bei
# der GL-Versionsprüfung, 4.0.10 hat einen robusteren Parser. Pivy (Python-Anbindung) gegen genau diese Coin-Version.
ARG COIN_TAG=v4.0.10
ARG PIVY_TAG=0.6.11
RUN git clone --depth 1 --branch ${COIN_TAG} --recurse-submodules https://github.com/coin3d/coin.git /tmp/coin \
    && cmake -S /tmp/coin -B /tmp/coin/build -G Ninja -Wno-dev -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr \
        -DCOIN_BUILD_TESTS=OFF -DCOIN_BUILD_DOCUMENTATION=OFF \
    && cmake --build /tmp/coin/build && cmake --install /tmp/coin/build \
    && rm -rf /tmp/coin
# Pivy 0.6.11 nutzt in einigen Schnittstellen noch Python-2-Namen (PyInt_*, PyString_*); das SWIG in Arch liefert
# deren Ersatz nicht mehr mit. Ein vorab eingebundener Header ordnet sie den Python-3-Funktionen zu.
RUN printf '%s\n' '#pragma once' \
        '#define PyInt_Check PyLong_Check' '#define PyInt_AsLong PyLong_AsLong' '#define PyInt_FromLong PyLong_FromLong' \
        '#define PyString_Check PyUnicode_Check' '#define PyString_AsString PyUnicode_AsUTF8' \
        '#define PyString_FromString PyUnicode_FromString' > /tmp/py2compat.h \
    && git clone --depth 1 --branch ${PIVY_TAG} https://github.com/coin3d/pivy.git /tmp/pivy \
    && cmake -S /tmp/pivy -B /tmp/pivy/build -G Ninja -Wno-dev -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr \
        -DCMAKE_CXX_FLAGS="-include /tmp/py2compat.h" \
    && cmake --build /tmp/pivy/build && cmake --install /tmp/pivy/build \
    && rm -rf /tmp/pivy /tmp/py2compat.h
# SpaceMouse (12.14): libspnav für spacenavd; eigene Schicht am Ende, damit OCCT/Coin/Pivy aus dem Cache bleiben
RUN for try in 1 2 3 4 5; do pacman -S --noconfirm --needed libspnav && break; \
        [ "$try" = 5 ] && exit 1; sleep 60; \
    done && pacman -Scc --noconfirm
