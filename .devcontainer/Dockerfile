# Arch-Basis, damit die gebauten Binaries auch auf dem CachyOS-Host laufen.
FROM docker.io/library/archlinux:base-devel

# Build-Toolchain + Abhängigkeiten von Base/App/Gui/Part/Sketcher/PartDesign/Import/Mesh.
# mesa/glu: OpenGL für Coin im Container (Intel-iGPU über /dev/dri).
RUN pacman -Syu --noconfirm --needed \
        cmake ninja ccache git pkgconf python gtest \
        boost eigen nlohmann-json microsoft-gsl pybind11 swig \
        qt6-base qt6-declarative qt6-shadertools qt6-svg qt6-tools qt6-wayland \
        pyside6 shiboken6 python-pivy coin opencascade xerces-c yaml-cpp fmt icu freetype2 zlib \
        python-yaml python-packaging python-matplotlib \
        mesa glu libglvnd ttf-dejavu inter-font \
    && pacman -Scc --noconfirm
