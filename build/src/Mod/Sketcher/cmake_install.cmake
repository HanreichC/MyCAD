# Install script for directory: /workspace/src/Mod/Sketcher

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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workspace/build/src/Mod/Sketcher/App/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workspace/build/src/Mod/Sketcher/Gui/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Mod/Sketcher" TYPE FILE FILES
    "/workspace/src/Mod/Sketcher/Init.py"
    "/workspace/src/Mod/Sketcher/SketcherExample.py"
    "/workspace/src/Mod/Sketcher/TestSketcherApp.py"
    "/workspace/src/Mod/Sketcher/Profiles.py"
    "/workspace/src/Mod/Sketcher/InitGui.py"
    "/workspace/src/Mod/Sketcher/TestSketcherGui.py"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Mod/Sketcher/ProfileLib" TYPE FILE FILES
    "/workspace/src/Mod/Sketcher/ProfileLib/Hexagon.py"
    "/workspace/src/Mod/Sketcher/ProfileLib/RegularPolygon.py"
    "/workspace/src/Mod/Sketcher/ProfileLib/__init__.py"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Mod/Sketcher/SketcherTests" TYPE FILE FILES
    "/workspace/src/Mod/Sketcher/SketcherTests/__init__.py"
    "/workspace/src/Mod/Sketcher/SketcherTests/TestSketchFillet.py"
    "/workspace/src/Mod/Sketcher/SketcherTests/TestSketcherSolver.py"
    "/workspace/src/Mod/Sketcher/SketcherTests/TestSketchExpression.py"
    "/workspace/src/Mod/Sketcher/SketcherTests/TestSketchValidateCoincidents.py"
    "/workspace/src/Mod/Sketcher/SketcherTests/TestSketchCarbonCopyReverseMapping.py"
    "/workspace/src/Mod/Sketcher/SketcherTests/TestSketchCarbonCopyReverseMapping.FCStd"
    "/workspace/src/Mod/Sketcher/SketcherTests/TestSketchInternalFaces.py"
    "/workspace/src/Mod/Sketcher/SketcherTests/TestSketcherEllipse.py"
    "/workspace/src/Mod/Sketcher/SketcherTests/TestConstraintPreselectionGui.py"
    "/workspace/src/Mod/Sketcher/SketcherTests/TestDistanceLabelExtensionGui.py"
    "/workspace/src/Mod/Sketcher/SketcherTests/TestConstraintCommandsGui.py"
    "/workspace/src/Mod/Sketcher/SketcherTests/TestCoincidentCommandGui.py"
    "/workspace/src/Mod/Sketcher/SketcherTests/GuiTestCase.py"
    "/workspace/src/Mod/Sketcher/SketcherTests/TestPlacementUpdate.py"
    "/workspace/src/Mod/Sketcher/SketcherTests/TestOnViewParameterGui.py"
    "/workspace/src/Mod/Sketcher/SketcherTests/TestExternalFacePreselection.py"
    "/workspace/src/Mod/Sketcher/SketcherTests/TestVisualLayerListGui.py"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/workspace/build/src/Mod/Sketcher/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
