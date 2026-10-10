# SPDX-License-Identifier: LGPL-2.1-or-later

disable_occt8_deprecation_warnings()

add_subdirectory(App)
set(Design_Scripts Init.py)
if(BUILD_GUI)
    list(APPEND Design_Scripts InitGui.py)
    add_subdirectory(Gui)
endif(BUILD_GUI)

add_custom_target(DesignScripts ALL SOURCES ${Design_Scripts})
fc_target_copy_resource(DesignScripts ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_BINARY_DIR}/Mod/Design ${Design_Scripts})
INSTALL(FILES ${Design_Scripts} DESTINATION Mod/Design)
