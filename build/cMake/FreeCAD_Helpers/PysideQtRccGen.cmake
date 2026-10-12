cmake_minimum_required(VERSION 3.22.0)
file(WRITE "${OUT}"
    "# Auto-generated loading code for ${RCCBIN}\n"
    "from pathlib import Path\n"
    "from PySide${PYSIDE_MAJOR_VERSION}.QtCore import QResource\n"
    "QResource.registerResource(str(Path(__file__).absolute().parent / \"${RCCBIN}\"))\n"
)
