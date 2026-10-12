# Install script for directory: /workspace/src/Mod/Show

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Mod/Show" TYPE FILE FILES
    "/workspace/src/Mod/Show/__init__.py"
    "/workspace/src/Mod/Show/Containers.py"
    "/workspace/src/Mod/Show/DepGraphTools.py"
    "/workspace/src/Mod/Show/SceneDetail.py"
    "/workspace/src/Mod/Show/mTempoVis.py"
    "/workspace/src/Mod/Show/TVObserver.py"
    "/workspace/src/Mod/Show/TVStack.py"
    "/workspace/src/Mod/Show/ShowUtils.py"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Mod/Show/SceneDetails" TYPE FILE FILES
    "/workspace/src/Mod/Show/SceneDetails/__init__.py"
    "/workspace/src/Mod/Show/SceneDetails/Camera.py"
    "/workspace/src/Mod/Show/SceneDetails/ClipPlane.py"
    "/workspace/src/Mod/Show/SceneDetails/ObjectClipPlane.py"
    "/workspace/src/Mod/Show/SceneDetails/Pickability.py"
    "/workspace/src/Mod/Show/SceneDetails/VProperty.py"
    "/workspace/src/Mod/Show/SceneDetails/Workbench.py"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/workspace/build/src/Mod/Show/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
