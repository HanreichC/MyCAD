# Install script for directory: /workspace/src/Mod/PartDesign

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
  include("/workspace/build/src/Mod/PartDesign/App/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/workspace/build/src/Mod/PartDesign/Gui/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Mod/PartDesign" TYPE FILE FILES
    "/workspace/src/Mod/PartDesign/__init__.py"
    "/workspace/src/Mod/PartDesign/Init.py"
    "/workspace/src/Mod/PartDesign/TestPartDesignApp.py"
    "/workspace/src/Mod/PartDesign/InitGui.py"
    "/workspace/src/Mod/PartDesign/TestPartDesignGui.py"
    "/workspace/src/Mod/PartDesign/InvoluteGearFeature.py"
    "/workspace/src/Mod/PartDesign/InvoluteGearFeature.ui"
    "/workspace/src/Mod/PartDesign/SprocketFeature.py"
    "/workspace/src/Mod/PartDesign/SprocketFeature.ui"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Mod/PartDesign/Scripts" TYPE FILE FILES
    "/workspace/src/Mod/PartDesign/Scripts/__init__.py"
    "/workspace/src/Mod/PartDesign/Scripts/DistanceBolt.py"
    "/workspace/src/Mod/PartDesign/Scripts/Epitrochoid.py"
    "/workspace/src/Mod/PartDesign/Scripts/FilletArc.py"
    "/workspace/src/Mod/PartDesign/Scripts/Gear.py"
    "/workspace/src/Mod/PartDesign/Scripts/Parallelepiped.py"
    "/workspace/src/Mod/PartDesign/Scripts/RadialCopy.py"
    "/workspace/src/Mod/PartDesign/Scripts/Spring.py"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Mod/PartDesign/PartDesignTests" TYPE FILE FILES
    "/workspace/src/Mod/PartDesign/PartDesignTests/__init__.py"
    "/workspace/src/Mod/PartDesign/PartDesignTests/TestActiveObject.py"
    "/workspace/src/Mod/PartDesign/PartDesignTests/TestDatum.py"
    "/workspace/src/Mod/PartDesign/PartDesignTests/TestShapeBinder.py"
    "/workspace/src/Mod/PartDesign/PartDesignTests/TestPad.py"
    "/workspace/src/Mod/PartDesign/PartDesignTests/TestPocket.py"
    "/workspace/src/Mod/PartDesign/PartDesignTests/TestHelix.py"
    "/workspace/src/Mod/PartDesign/PartDesignTests/TestHole.py"
    "/workspace/src/Mod/PartDesign/PartDesignTests/TestRevolve.py"
    "/workspace/src/Mod/PartDesign/PartDesignTests/TestLoft.py"
    "/workspace/src/Mod/PartDesign/PartDesignTests/TestPipe.py"
    "/workspace/src/Mod/PartDesign/PartDesignTests/TestPrimitive.py"
    "/workspace/src/Mod/PartDesign/PartDesignTests/TestMirrored.py"
    "/workspace/src/Mod/PartDesign/PartDesignTests/TestLinearPattern.py"
    "/workspace/src/Mod/PartDesign/PartDesignTests/TestCircularPattern.py"
    "/workspace/src/Mod/PartDesign/PartDesignTests/TestPathPattern.py"
    "/workspace/src/Mod/PartDesign/PartDesignTests/TestPointPattern.py"
    "/workspace/src/Mod/PartDesign/PartDesignTests/TestPolarPattern.py"
    "/workspace/src/Mod/PartDesign/PartDesignTests/TestMultiTransform.py"
    "/workspace/src/Mod/PartDesign/PartDesignTests/TestBoolean.py"
    "/workspace/src/Mod/PartDesign/PartDesignTests/TestBaseFeature.py"
    "/workspace/src/Mod/PartDesign/PartDesignTests/TestFillet.py"
    "/workspace/src/Mod/PartDesign/PartDesignTests/TestChamfer.py"
    "/workspace/src/Mod/PartDesign/PartDesignTests/TestDraft.py"
    "/workspace/src/Mod/PartDesign/PartDesignTests/TestThickness.py"
    "/workspace/src/Mod/PartDesign/PartDesignTests/TestTopologicalNamingProblem.py"
    "/workspace/src/Mod/PartDesign/PartDesignTests/TestInvoluteGear.py"
    "/workspace/src/Mod/PartDesign/PartDesignTests/TestSketch.py"
    "/workspace/src/Mod/PartDesign/PartDesignTests/TestMaterial.py"
    "/workspace/src/Mod/PartDesign/PartDesignTests/TestSuppressed.py"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Mod/PartDesign/PartDesignTests/Fixtures" TYPE FILE FILES
    "/workspace/src/Mod/PartDesign/PartDesignTests/Fixtures/InvoluteGear_v0-20.FCStd"
    "/workspace/src/Mod/PartDesign/PartDesignTests/Fixtures/InternalInvoluteGear_v0-20.FCStd"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Mod/PartDesign/fcgear" TYPE FILE FILES
    "/workspace/src/Mod/PartDesign/fcgear/__init__.py"
    "/workspace/src/Mod/PartDesign/fcgear/fcgear.py"
    "/workspace/src/Mod/PartDesign/fcgear/involute.py"
    "/workspace/src/Mod/PartDesign/fcgear/svggear.py"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Mod/PartDesign/fcsprocket" TYPE FILE FILES
    "/workspace/src/Mod/PartDesign/fcsprocket/__init__.py"
    "/workspace/src/Mod/PartDesign/fcsprocket/fcsprocket.py"
    "/workspace/src/Mod/PartDesign/fcsprocket/fcsprocketdialog.py"
    "/workspace/src/Mod/PartDesign/fcsprocket/sprocket.py"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/Mod/PartDesign/Resources/Hole" TYPE FILE FILES
    "/workspace/src/Mod/PartDesign/Resources/Hole/din7984.json"
    "/workspace/src/Mod/PartDesign/Resources/Hole/iso10642.json"
    "/workspace/src/Mod/PartDesign/Resources/Hole/iso10642-fine.json"
    "/workspace/src/Mod/PartDesign/Resources/Hole/iso12474-fine.json"
    "/workspace/src/Mod/PartDesign/Resources/Hole/iso14583.json"
    "/workspace/src/Mod/PartDesign/Resources/Hole/iso14583part.json"
    "/workspace/src/Mod/PartDesign/Resources/Hole/iso2009.json"
    "/workspace/src/Mod/PartDesign/Resources/Hole/iso4762_7089.json"
    "/workspace/src/Mod/PartDesign/Resources/Hole/iso4762.json"
    "/workspace/src/Mod/PartDesign/Resources/Hole/iso4762-fine.json"
    "/workspace/src/Mod/PartDesign/Resources/Hole/iso7046.json"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/workspace/build/src/Mod/PartDesign/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
