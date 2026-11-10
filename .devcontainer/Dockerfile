# Arch-Basis, damit die gebauten Binaries auch auf dem CachyOS-Host laufen.
# Fester Stand: Basis-Image und Paketquelle (Arch Linux Archive) auf ein Datum gepinnt, damit ein Update von OCCT,
# Qt oder Python den Build nicht über Nacht bricht. Aktualisieren = beide Daten anheben, Tests laufen lassen.
FROM docker.io/library/archlinux:base-devel-20261101.0.620205
RUN echo 'Server = https://archive.archlinux.org/repos/2026/11/09/$repo/os/$arch' > /etc/pacman.d/mirrorlist

# Build-Toolchain + Abhängigkeiten von Base/App/Gui/Part/Sketcher/PartDesign/Import/Mesh.
# mesa/glu: OpenGL für Coin im Container (Intel-iGPU über /dev/dri).
# xorg-server-xvfb/xorg-xauth: GUI-Tests ohne Desktop (CI), siehe tests/gui/run.sh
RUN pacman -Syyu --noconfirm --needed \
        cmake ninja ccache git pkgconf python gtest \
        boost eigen nlohmann-json microsoft-gsl pybind11 swig \
        qt6-base qt6-declarative qt6-shadertools qt6-svg qt6-tools qt6-wayland onnxruntime-cpu \
        pyside6 shiboken6 python-pivy coin opencascade xerces-c yaml-cpp fmt icu freetype2 zlib \
        python-yaml python-packaging python-matplotlib \
        mesa glu libglvnd ttf-dejavu inter-font \
        xorg-server-xvfb xorg-xauth \
    && pacman -Scc --noconfirm
