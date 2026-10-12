# Install script for directory: /workspace/src/Mod/Part

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
  include("/workspace/build/src/Mod/Part/App/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workspace/build/src/Mod/Part/Gui/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Mod/Part" TYPE FILE FILES
    "/workspace/src/Mod/Part/Init.py"
    "/workspace/src/Mod/Part/JoinFeatures.py"
    "/workspace/src/Mod/Part/MakeBottle.py"
    "/workspace/src/Mod/Part/PartEnums.py"
    "/workspace/src/Mod/Part/TestPartApp.py"
    "/workspace/src/Mod/Part/InitGui.py"
    "/workspace/src/Mod/Part/TestPartGui.py"
    "/workspace/src/Mod/Part/TestPartPreview.py"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Mod/Part/AttachmentEditor" TYPE FILE FILES
    "/workspace/src/Mod/Part/AttachmentEditor/__init__.py"
    "/workspace/src/Mod/Part/AttachmentEditor/Commands.py"
    "/workspace/src/Mod/Part/AttachmentEditor/FrozenClass.py"
    "/workspace/src/Mod/Part/AttachmentEditor/TaskAttachmentEditor.py"
    "/workspace/src/Mod/Part/AttachmentEditor/TaskAttachmentEditor.ui"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Mod/Part/BasicShapes" TYPE FILE FILES
    "/workspace/src/Mod/Part/BasicShapes/__init__.py"
    "/workspace/src/Mod/Part/BasicShapes/Shapes.py"
    "/workspace/src/Mod/Part/BasicShapes/Utils.py"
    "/workspace/src/Mod/Part/BasicShapes/ShapeContent.py"
    "/workspace/src/Mod/Part/BasicShapes/CommandShapes.py"
    "/workspace/src/Mod/Part/BasicShapes/ViewProviderShapes.py"
    "/workspace/src/Mod/Part/BasicShapes/TaskTube.ui"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Mod/Part/BOPTools" TYPE FILE FILES
    "/workspace/src/Mod/Part/BOPTools/__init__.py"
    "/workspace/src/Mod/Part/BOPTools/BOPFeatures.py"
    "/workspace/src/Mod/Part/BOPTools/GeneralFuseResult.py"
    "/workspace/src/Mod/Part/BOPTools/JoinAPI.py"
    "/workspace/src/Mod/Part/BOPTools/JoinFeatures.py"
    "/workspace/src/Mod/Part/BOPTools/ShapeMerge.py"
    "/workspace/src/Mod/Part/BOPTools/SplitAPI.py"
    "/workspace/src/Mod/Part/BOPTools/SplitFeatures.py"
    "/workspace/src/Mod/Part/BOPTools/ToleranceFeatures.py"
    "/workspace/src/Mod/Part/BOPTools/Utils.py"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Mod/Part/CompoundTools" TYPE FILE FILES
    "/workspace/src/Mod/Part/CompoundTools/__init__.py"
    "/workspace/src/Mod/Part/CompoundTools/_CommandCompoundFilter.py"
    "/workspace/src/Mod/Part/CompoundTools/_CommandExplodeCompound.py"
    "/workspace/src/Mod/Part/CompoundTools/CompoundFilter.py"
    "/workspace/src/Mod/Part/CompoundTools/Explode.py"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Mod/Part/parttests" TYPE FILE FILES
    "/workspace/src/Mod/Part/parttests/__init__.py"
    "/workspace/src/Mod/Part/parttests/BRep_tests.py"
    "/workspace/src/Mod/Part/parttests/Geom2d_tests.py"
    "/workspace/src/Mod/Part/parttests/part_test_objects.py"
    "/workspace/src/Mod/Part/parttests/regression_tests.py"
    "/workspace/src/Mod/Part/parttests/TopoShapeListTest.py"
    "/workspace/src/Mod/Part/parttests/ColorPerFaceTest.py"
    "/workspace/src/Mod/Part/parttests/ColorTransparencyTest.py"
    "/workspace/src/Mod/Part/parttests/TaskFaceAppearancesTest.py"
    "/workspace/src/Mod/Part/parttests/TopoShapeTest.py"
    "/workspace/src/Mod/Part/parttests/TestTangentMode3-0.21.FCStd"
    "/workspace/src/Mod/Part/parttests/TestLinkArrayCircular.py"
    "/workspace/src/Mod/Part/parttests/TestLinkArrayLinear.py"
    "/workspace/src/Mod/Part/parttests/TestLinkArrayPath.py"
    "/workspace/src/Mod/Part/parttests/TestLinkArrayPoint.py"
    "/workspace/src/Mod/Part/parttests/TestPartMirror.py"
    "/workspace/src/Mod/Part/parttests/TestFaceMakerUnifiedPlanar.py"
    "/workspace/src/Mod/Part/parttests/TestFaceMakerUnifiedNonPlanar.py"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/workspace/build/src/Mod/Part/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
