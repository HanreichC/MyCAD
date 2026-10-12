add_test([=[Collection.TestValidity]=]  /workspace/build/tests/Zipios_tests_run [==[--gtest_filter=Collection.TestValidity]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Collection.TestValidity]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/zipios++/collectioncollection.cpp:8]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Collection.TestCopy]=]  /workspace/build/tests/Zipios_tests_run [==[--gtest_filter=Collection.TestCopy]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Collection.TestCopy]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/zipios++/collectioncollection.cpp:23]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Collection.TestCopyAssign]=]  /workspace/build/tests/Zipios_tests_run [==[--gtest_filter=Collection.TestCopyAssign]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Collection.TestCopyAssign]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/zipios++/collectioncollection.cpp:37]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Collection.TestClone]=]  /workspace/build/tests/Zipios_tests_run [==[--gtest_filter=Collection.TestClone]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Collection.TestClone]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/zipios++/collectioncollection.cpp:52]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Collection.TestAdd]=]  /workspace/build/tests/Zipios_tests_run [==[--gtest_filter=Collection.TestAdd]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Collection.TestAdd]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/zipios++/collectioncollection.cpp:66]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ZipFile.TestValidity]=]  /workspace/build/tests/Zipios_tests_run [==[--gtest_filter=ZipFile.TestValidity]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ZipFile.TestValidity]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/zipios++/zipfile.cpp:9]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ZipFile.TestNonExisting]=]  /workspace/build/tests/Zipios_tests_run [==[--gtest_filter=ZipFile.TestNonExisting]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ZipFile.TestNonExisting]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/zipios++/zipfile.cpp:36]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ZipFileTest.TestValid]=]  /workspace/build/tests/Zipios_tests_run [==[--gtest_filter=ZipFileTest.TestValid]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ZipFileTest.TestValid]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/zipios++/zipfile.cpp:78]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
set(Zipios_tests_run_TESTS [==[Collection.TestValidity]==] [==[Collection.TestCopy]==] [==[Collection.TestCopyAssign]==] [==[Collection.TestClone]==] [==[Collection.TestAdd]==] [==[ZipFile.TestValidity]==] [==[ZipFile.TestNonExisting]==] [==[ZipFileTest.TestValid]==])
