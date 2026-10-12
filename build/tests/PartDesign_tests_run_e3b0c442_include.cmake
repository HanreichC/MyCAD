if(EXISTS "/workspace/build/tests/PartDesign_tests_run")
  if(NOT EXISTS "/workspace/build/tests/PartDesign_tests_run_e3b0c442_tests.cmake" OR
     NOT "/workspace/build/tests/PartDesign_tests_run_e3b0c442_tests.cmake" IS_NEWER_THAN "/workspace/build/tests/PartDesign_tests_run" OR
     NOT "/workspace/build/tests/PartDesign_tests_run_e3b0c442_tests.cmake" IS_NEWER_THAN "${CMAKE_CURRENT_LIST_FILE}")
    include("/workspace/build/tests/PartDesign_tests_run_e3b0c442_discovery.cmake")
  endif()
endif()
if(EXISTS "/workspace/build/tests/PartDesign_tests_run_e3b0c442_tests.cmake")
  include("/workspace/build/tests/PartDesign_tests_run_e3b0c442_tests.cmake")
else()
  add_test(PartDesign_tests_run_NOT_BUILT PartDesign_tests_run_NOT_BUILT)
endif()
