# CMake generated Testfile for 
# Source directory: /workspace/tests/src/Gui/propertyeditor
# Build directory: /workspace/build/tests/src/Gui/propertyeditor
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test("PropertyItem_Tests_run" "/workspace/build/tests/PropertyItem_Tests_run")
set_tests_properties("PropertyItem_Tests_run" PROPERTIES  ENVIRONMENT "QT_QPA_PLATFORM=offscreen" LABELS "Qt" _BACKTRACE_TRIPLES "/workspace/tests/CMakeLists.txt;16;add_test;/workspace/tests/src/Gui/propertyeditor/CMakeLists.txt;1;setup_qt_test;/workspace/tests/src/Gui/propertyeditor/CMakeLists.txt;0;")
add_test("PropertyEditorFocus_Tests_run" "/workspace/build/tests/PropertyEditorFocus_Tests_run")
set_tests_properties("PropertyEditorFocus_Tests_run" PROPERTIES  ENVIRONMENT "QT_QPA_PLATFORM=offscreen" LABELS "Qt" _BACKTRACE_TRIPLES "/workspace/tests/CMakeLists.txt;16;add_test;/workspace/tests/src/Gui/propertyeditor/CMakeLists.txt;2;setup_qt_test;/workspace/tests/src/Gui/propertyeditor/CMakeLists.txt;0;")
