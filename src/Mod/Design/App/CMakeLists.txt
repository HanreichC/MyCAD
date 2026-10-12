# SPDX-License-Identifier: LGPL-2.1-or-later

add_library(Design SHARED AppDesign.cpp Features.cpp Features.h)
target_include_directories(Design PRIVATE ${CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR}/src ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(Design Part Sketcher FreeCADApp ${OCC_LIBRARIES})
target_link_directories(Design PUBLIC ${OCC_LIBRARY_DIR})

SET_BIN_DIR(Design)
SET_PYTHON_PREFIX_SUFFIX(Design)
INSTALL(TARGETS Design DESTINATION ${CMAKE_INSTALL_LIBDIR})
