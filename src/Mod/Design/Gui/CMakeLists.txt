# SPDX-License-Identifier: LGPL-2.1-or-later

add_library(DesignGui SHARED AppDesignGui.cpp Commands.cpp Scribble.cpp ScribbleShapes.h ScribbleTidy.h ViewProviders.cpp ViewProviders.h)
target_include_directories(DesignGui PRIVATE ${CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR}/src ${CMAKE_SOURCE_DIR}/src)
# qTriangulate (Scribble-Füllflächen mit Löchern) ist Qt-intern; ab Qt 6.10 ein eigenes Paket
if(Qt6_VERSION VERSION_GREATER_EQUAL "6.10.0")
    find_package(Qt6 REQUIRED COMPONENTS GuiPrivate)
endif()
target_link_libraries(DesignGui Design PartGui SketcherGui FreeCADGui Qt6::GuiPrivate ${QtSvg_LIBRARIES})

SET_BIN_DIR(DesignGui)
SET_PYTHON_PREFIX_SUFFIX(DesignGui)
INSTALL(TARGETS DesignGui DESTINATION ${CMAKE_INSTALL_LIBDIR})
