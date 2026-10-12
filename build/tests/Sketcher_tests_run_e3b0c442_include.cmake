if(EXISTS "/workspace/build/tests/Sketcher_tests_run")
  if(NOT EXISTS "/workspace/build/tests/Sketcher_tests_run_e3b0c442_tests.cmake" OR
     NOT "/workspace/build/tests/Sketcher_tests_run_e3b0c442_tests.cmake" IS_NEWER_THAN "/workspace/build/tests/Sketcher_tests_run" OR
     NOT "/workspace/build/tests/Sketcher_tests_run_e3b0c442_tests.cmake" IS_NEWER_THAN "${CMAKE_CURRENT_LIST_FILE}")
    include("/workspace/build/tests/Sketcher_tests_run_e3b0c442_discovery.cmake")
  endif()
endif()
if(EXISTS "/workspace/build/tests/Sketcher_tests_run_e3b0c442_tests.cmake")
  include("/workspace/build/tests/Sketcher_tests_run_e3b0c442_tests.cmake")
else()
  add_test(Sketcher_tests_run_NOT_BUILT Sketcher_tests_run_NOT_BUILT)
endif()
