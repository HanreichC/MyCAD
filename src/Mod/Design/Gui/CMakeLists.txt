# SPDX-License-Identifier: LGPL-2.1-or-later

add_library(DesignGui SHARED AppDesignGui.cpp Commands.cpp Scribble.cpp ScribbleRead.cpp ScribbleRead.h ScribbleShapes.h ScribbleTidy.h ViewProviders.cpp ViewProviders.h)
target_include_directories(DesignGui PRIVATE ${CMAKE_BINARY_DIR} ${CMAKE_BINARY_DIR}/src ${CMAKE_SOURCE_DIR}/src)
# qTriangulate (Scribble-Füllflächen mit Löchern) ist Qt-intern; ab Qt 6.10 ein eigenes Paket
if(Qt6_VERSION VERSION_GREATER_EQUAL "6.10.0")
    find_package(Qt6 REQUIRED COMPONENTS GuiPrivate)
endif()
target_link_libraries(DesignGui Design PartGui SketcherGui FreeCADGui Qt6::GuiPrivate ${QtSvg_LIBRARIES})

# Handschrift lesen in Scribbles (htr/README.md): onnxruntime und DE·HTR v2. Ohne beides baut MyCAD ohne Erkennung.
find_package(onnxruntime CONFIG QUIET)
if(onnxruntime_FOUND)
    set(HTR_MODEL ${CMAKE_CURRENT_BINARY_DIR}/htr/model.onnx)
    file(DOWNLOAD https://huggingface.co/naeyn/de-htr-web-v2/resolve/6241c1ff0fd42725e0dc46fcd3217469cac851bb/model.onnx
         ${HTR_MODEL} EXPECTED_HASH SHA256=b576a0a1281b9be46b2574028b75575e041b7d7cb650f063886e733467cc1499
         STATUS HTR_STATUS)
    list(GET HTR_STATUS 0 HTR_CODE)
endif()
if(onnxruntime_FOUND AND HTR_CODE EQUAL 0)
    # BIG_RESOURCES: die 10 MB gehen als Objektdatei hinein, nicht als riesige C++-Quelle
    qt_add_resources(DesignGui htr PREFIX /mycad/htr BASE ${CMAKE_CURRENT_BINARY_DIR}/htr BIG_RESOURCES FILES ${HTR_MODEL})
    target_compile_definitions(DesignGui PRIVATE MYCAD_HTR)
    target_link_libraries(DesignGui onnxruntime::onnxruntime)
    message(STATUS "Scribble: Handschrift lesen an (onnxruntime ${onnxruntime_VERSION}, DE·HTR v2)")
else()
    message(STATUS "Scribble: Handschrift lesen aus (onnxruntime oder Modell fehlt)")
endif()

SET_BIN_DIR(DesignGui)
SET_PYTHON_PREFIX_SUFFIX(DesignGui)
INSTALL(TARGETS DesignGui DESTINATION ${CMAKE_INSTALL_LIBDIR})
