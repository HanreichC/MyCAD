# Install script for directory: /workspace/src/3rdParty/Clipper2

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/workspace/build/src/3rdParty/Clipper2/libClipper2Z.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/clipper2" TYPE FILE FILES
    "/workspace/src/3rdParty/Clipper2/Clipper2Lib/include/clipper2/clipper.h"
    "/workspace/src/3rdParty/Clipper2/Clipper2Lib/include/clipper2/clipper.version.h"
    "/workspace/src/3rdParty/Clipper2/Clipper2Lib/include/clipper2/clipper.core.h"
    "/workspace/src/3rdParty/Clipper2/Clipper2Lib/include/clipper2/clipper.engine.h"
    "/workspace/src/3rdParty/Clipper2/Clipper2Lib/include/clipper2/clipper.export.h"
    "/workspace/src/3rdParty/Clipper2/Clipper2Lib/include/clipper2/clipper.minkowski.h"
    "/workspace/src/3rdParty/Clipper2/Clipper2Lib/include/clipper2/clipper.offset.h"
    "/workspace/src/3rdParty/Clipper2/Clipper2Lib/include/clipper2/clipper.rectclip.h"
    "/workspace/src/3rdParty/Clipper2/Clipper2Lib/include/clipper2/clipper.triangulation.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/workspace/build/src/3rdParty/Clipper2/Clipper2Z.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/workspace/build/src/3rdParty/Clipper2/libClipper2Z.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/clipper2" TYPE FILE FILES
    "/workspace/src/3rdParty/Clipper2/Clipper2Lib/include/clipper2/clipper.h"
    "/workspace/src/3rdParty/Clipper2/Clipper2Lib/include/clipper2/clipper.version.h"
    "/workspace/src/3rdParty/Clipper2/Clipper2Lib/include/clipper2/clipper.core.h"
    "/workspace/src/3rdParty/Clipper2/Clipper2Lib/include/clipper2/clipper.engine.h"
    "/workspace/src/3rdParty/Clipper2/Clipper2Lib/include/clipper2/clipper.export.h"
    "/workspace/src/3rdParty/Clipper2/Clipper2Lib/include/clipper2/clipper.minkowski.h"
    "/workspace/src/3rdParty/Clipper2/Clipper2Lib/include/clipper2/clipper.offset.h"
    "/workspace/src/3rdParty/Clipper2/Clipper2Lib/include/clipper2/clipper.rectclip.h"
    "/workspace/src/3rdParty/Clipper2/Clipper2Lib/include/clipper2/clipper.triangulation.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/clipper2" TYPE FILE FILES
    "/workspace/build/src/3rdParty/Clipper2/Clipper2Config.cmake"
    "/workspace/build/src/3rdParty/Clipper2/Clipper2ConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/clipper2/Clipper2Targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/clipper2/Clipper2Targets.cmake"
         "/workspace/build/src/3rdParty/Clipper2/CMakeFiles/Export/d8256b042a676486d1b2b19831a8c686/Clipper2Targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/clipper2/Clipper2Targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/clipper2/Clipper2Targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/clipper2" TYPE FILE FILES "/workspace/build/src/3rdParty/Clipper2/CMakeFiles/Export/d8256b042a676486d1b2b19831a8c686/Clipper2Targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/clipper2" TYPE FILE FILES "/workspace/build/src/3rdParty/Clipper2/CMakeFiles/Export/d8256b042a676486d1b2b19831a8c686/Clipper2Targets-release.cmake")
  endif()
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/workspace/build/src/3rdParty/Clipper2/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
