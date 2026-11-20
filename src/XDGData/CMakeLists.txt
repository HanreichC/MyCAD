include(GNUInstallDirs)

# Desktop-Datei, Symbol, Metainfo und Dateityp unter der App-ID (Plan 12.6, docs/FLATHUB.md). Flatpak, AppImage und
# install.sh nehmen dieselben Dateien. Version und Datum: CI übergibt -DMYCAD_RELEASE=1.0.N, sonst der letzte Tag
set(MYCAD_APP_ID io.github.HanreichC.MyCAD)
if(NOT DEFINED MYCAD_RELEASE AND EXISTS "${CMAKE_SOURCE_DIR}/.git")
    execute_process(COMMAND git describe --tags --abbrev=0 --match "v*"
        OUTPUT_VARIABLE MYCAD_RELEASE
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET)
    string(REGEX REPLACE "^v" "" MYCAD_RELEASE "${MYCAD_RELEASE}")
endif()
if(NOT MYCAD_RELEASE)
    set(MYCAD_RELEASE "1.0.0")
endif()
if(NOT DEFINED APPDATA_RELEASE_DATE)
    if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
        execute_process(COMMAND git log -1 --pretty=%cd --date=short
            OUTPUT_VARIABLE APPDATA_RELEASE_DATE
            WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
            OUTPUT_STRIP_TRAILING_WHITESPACE)
    endif()
    if(NOT APPDATA_RELEASE_DATE)  # ohne .git oder wenn git nicht darf (Container, fremder Eigentümer)
        string(TIMESTAMP APPDATA_RELEASE_DATE "%Y-%m-%d")
    endif()
endif()

configure_file(${MYCAD_APP_ID}.metainfo.xml.in ${CMAKE_BINARY_DIR}/${MYCAD_APP_ID}.metainfo.xml @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/${MYCAD_APP_ID}.metainfo.xml DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/metainfo)
install(FILES ${MYCAD_APP_ID}.desktop DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/applications)
install(FILES ${MYCAD_APP_ID}.xml DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/mime/packages)
install(FILES ${CMAKE_SOURCE_DIR}/src/Gui/Icons/mycad.svg
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/icons/hicolor/scalable/apps
    RENAME ${MYCAD_APP_ID}.svg)

configure_file(
    FreeCAD.thumbnailer.in
    ${CMAKE_BINARY_DIR}/FreeCAD.thumbnailer
)
install(
    FILES ${CMAKE_BINARY_DIR}/FreeCAD.thumbnailer
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/thumbnailers
)

configure_file(
    ${CMAKE_SOURCE_DIR}/src/Tools/freecad-thumbnailer.in
    ${CMAKE_BINARY_DIR}/freecad-thumbnailer
)
install(
    PROGRAMS ${CMAKE_BINARY_DIR}/freecad-thumbnailer
    TYPE BIN
)
