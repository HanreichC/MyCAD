# Install script for directory: /workspace/src/Gui/PreferencePackTemplates

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/sbin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/Gui/PreferencePackTemplates" TYPE FILE FILES
    "/workspace/src/Gui/PreferencePackTemplates/Arch_Colors.cfg"
    "/workspace/src/Gui/PreferencePackTemplates/Console_Colors.cfg"
    "/workspace/src/Gui/PreferencePackTemplates/Draft_Colors.cfg"
    "/workspace/src/Gui/PreferencePackTemplates/Editor_Colors.cfg"
    "/workspace/src/Gui/PreferencePackTemplates/Editor_Font.cfg"
    "/workspace/src/Gui/PreferencePackTemplates/Main_window_layout.cfg"
    "/workspace/src/Gui/PreferencePackTemplates/Part_Colors.cfg"
    "/workspace/src/Gui/PreferencePackTemplates/Path_Colors.cfg"
    "/workspace/src/Gui/PreferencePackTemplates/Shortcuts.cfg"
    "/workspace/src/Gui/PreferencePackTemplates/Sketcher_Colors.cfg"
    "/workspace/src/Gui/PreferencePackTemplates/TechDraw_Colors.cfg"
    "/workspace/src/Gui/PreferencePackTemplates/View.cfg"
    "/workspace/src/Gui/PreferencePackTemplates/Window_Colors.cfg"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/workspace/build/src/Gui/PreferencePackTemplates/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
