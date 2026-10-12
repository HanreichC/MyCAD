// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

/* LibraryVersions.h.  Generated from LibraryVersions.h.cmake by cmake.  */

#define HAVE_OCC_VERSION

#if defined(HAVE_OCC_VERSION)
#  include </usr/include/opencascade/Standard_Version.hxx>
#endif

/* #undef BUILD_SMESH */

#if defined(BUILD_SMESH)
#  include <SMESH_Version.h>
#endif


/* No need for Boost (version info is always included in the source) */
/* No need for Python (version info is always included in the source) */
/* No need for Qt (version info is always included in the source) */
/* No need for SMESH (version info is always included in the source) */
/* No need for zlib (version info is always included in the source) */

// No CMake version info for libarea, Zipios, or KDL

// Coin3D
constexpr const char * fcCoin3dVersion = "4.0.10";
constexpr const char * fcCoin3dSource = "external";

// Eigen3
constexpr const char * fcEigen3Version = "5.0.1";

// FreeType
constexpr const char * fcFreetypeVersion = "2.14.3";

// pcl
constexpr const char * fcPclVersion = "";

// PyCXX
constexpr const char * fcPycxxVersion = "7.1.11";

// PySide
constexpr const char * fcPysideVersion = "6.12.0";

// PyBind
constexpr const char * fcPybind11Version = "";

// Shiboken
constexpr const char * fcShibokenVersion = "6.12.0";

// vtk
constexpr const char * fcVtkVersion = "";

// Xerces-C
constexpr const char * fcXercescVersion = "3.3.0";

// Pivy
constexpr const char * fcPivyVersion = "0.6.11";
constexpr const char * fcPivySource = "external";

// Clipper2
constexpr const char * fcClipper2Version = "2.0.1";
