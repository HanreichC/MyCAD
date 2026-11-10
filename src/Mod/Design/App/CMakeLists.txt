# SPDX-License-Identifier: LGPL-2.1-or-later

add_library(Design SHARED AppDesign.cpp Features.cpp Features.h AssemblySolver.cpp AssemblySolver.h)
target_include_directories(Design PRIVATE ${CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR}/src ${CMAKE_SOURCE_DIR}/src
                           ${CMAKE_SOURCE_DIR}/src/3rdParty/OndselSolver)
# PartDesign: Normtabellen für Bohrung und Gewinde; OndselSolver: geschlossene Gelenkketten (AssemblySolver.cpp)
target_link_libraries(Design Part PartDesign Materials Sketcher FreeCADApp OndselSolver ${OCC_LIBRARIES})
target_link_directories(Design PUBLIC ${OCC_LIBRARY_DIR})

SET_BIN_DIR(Design)
SET_PYTHON_PREFIX_SUFFIX(Design)
INSTALL(TARGETS Design DESTINATION ${CMAKE_INSTALL_LIBDIR})
