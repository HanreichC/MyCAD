# SPDX-License-Identifier: LGPL-2.1-or-later

add_library(DesignGui SHARED AppDesignGui.cpp Commands.cpp ViewProviders.cpp ViewProviders.h)
target_include_directories(DesignGui PRIVATE ${CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR}/src ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(DesignGui Design PartGui SketcherGui FreeCADGui)

SET_BIN_DIR(DesignGui)
SET_PYTHON_PREFIX_SUFFIX(DesignGui)
INSTALL(TARGETS DesignGui DESTINATION ${CMAKE_INSTALL_LIBDIR})
