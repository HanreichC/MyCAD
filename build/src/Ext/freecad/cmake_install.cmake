# Install script for directory: /workspace/src/Ext/freecad

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
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/lib/python3.14/site-packages/freecad/__init__.py;/usr/lib/python3.14/site-packages/freecad/deprecation.py;/usr/lib/python3.14/site-packages/freecad/freecad_doc.py;/usr/lib/python3.14/site-packages/freecad/module_io.py;/usr/lib/python3.14/site-packages/freecad/part.py;/usr/lib/python3.14/site-packages/freecad/partdesign.py;/usr/lib/python3.14/site-packages/freecad/project_utility.py;/usr/lib/python3.14/site-packages/freecad/sketcher.py;/usr/lib/python3.14/site-packages/freecad/UiTools.py;/usr/lib/python3.14/site-packages/freecad/utils.py;/usr/lib/python3.14/site-packages/freecad/utils_zip.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/lib/python3.14/site-packages/freecad" TYPE FILE FILES
    "/workspace/build/Ext/freecad/__init__.py"
    "/workspace/src/Ext/freecad/deprecation.py"
    "/workspace/src/Ext/freecad/freecad_doc.py"
    "/workspace/src/Ext/freecad/module_io.py"
    "/workspace/src/Ext/freecad/part.py"
    "/workspace/src/Ext/freecad/partdesign.py"
    "/workspace/src/Ext/freecad/project_utility.py"
    "/workspace/src/Ext/freecad/sketcher.py"
    "/workspace/src/Ext/freecad/UiTools.py"
    "/workspace/src/Ext/freecad/utils.py"
    "/workspace/src/Ext/freecad/utils_zip.py"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/workspace/build/src/Ext/freecad/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
