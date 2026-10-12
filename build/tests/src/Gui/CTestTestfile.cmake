# CMake generated Testfile for 
# Source directory: /workspace/tests/src/Gui
# Build directory: /workspace/build/tests/src/Gui
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test("ObjectSelection_Tests_run" "/workspace/build/tests/ObjectSelection_Tests_run")
set_tests_properties("ObjectSelection_Tests_run" PROPERTIES  ENVIRONMENT "QT_QPA_PLATFORM=offscreen" LABELS "Qt" _BACKTRACE_TRIPLES "/workspace/tests/CMakeLists.txt;16;add_test;/workspace/tests/src/Gui/CMakeLists.txt;36;setup_qt_test;/workspace/tests/src/Gui/CMakeLists.txt;0;")
add_test("TranslatorLocale_Tests_run" "/workspace/build/tests/TranslatorLocale_Tests_run")
set_tests_properties("TranslatorLocale_Tests_run" PROPERTIES  ENVIRONMENT "QT_QPA_PLATFORM=offscreen" LABELS "Qt" _BACKTRACE_TRIPLES "/workspace/tests/CMakeLists.txt;16;add_test;/workspace/tests/src/Gui/CMakeLists.txt;37;setup_qt_test;/workspace/tests/src/Gui/CMakeLists.txt;0;")
add_test("InputField_Tests_run" "/workspace/build/tests/InputField_Tests_run")
set_tests_properties("InputField_Tests_run" PROPERTIES  ENVIRONMENT "QT_QPA_PLATFORM=offscreen" LABELS "Qt" _BACKTRACE_TRIPLES "/workspace/tests/CMakeLists.txt;16;add_test;/workspace/tests/src/Gui/CMakeLists.txt;38;setup_qt_test;/workspace/tests/src/Gui/CMakeLists.txt;0;")
add_test("QuantitySpinBox_Tests_run" "/workspace/build/tests/QuantitySpinBox_Tests_run")
set_tests_properties("QuantitySpinBox_Tests_run" PROPERTIES  ENVIRONMENT "QT_QPA_PLATFORM=offscreen" LABELS "Qt" _BACKTRACE_TRIPLES "/workspace/tests/CMakeLists.txt;16;add_test;/workspace/tests/src/Gui/CMakeLists.txt;39;setup_qt_test;/workspace/tests/src/Gui/CMakeLists.txt;0;")
add_test("NumericLocaleConsumers_Tests_run" "/workspace/build/tests/NumericLocaleConsumers_Tests_run")
set_tests_properties("NumericLocaleConsumers_Tests_run" PROPERTIES  ENVIRONMENT "QT_QPA_PLATFORM=offscreen" LABELS "Qt" _BACKTRACE_TRIPLES "/workspace/tests/CMakeLists.txt;16;add_test;/workspace/tests/src/Gui/CMakeLists.txt;40;setup_qt_test;/workspace/tests/src/Gui/CMakeLists.txt;0;")
subdirs("Dialogs")
subdirs("propertyeditor")
