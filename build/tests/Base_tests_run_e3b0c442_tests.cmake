add_test([=[Axis.TestDefault]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Axis.TestDefault]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Axis.TestDefault]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Axis.cpp:18]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Axis.TestCustom]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Axis.TestCustom]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Axis.TestCustom]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Axis.cpp:25]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Axis.TestSetter]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Axis.TestSetter]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Axis.TestSetter]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Axis.cpp:32]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Axis.TestAssign]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Axis.TestAssign]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Axis.TestAssign]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Axis.cpp:41]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Axis.TestReverse]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Axis.TestReverse]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Axis.TestReverse]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Axis.cpp:52]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Axis.TestReversed]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Axis.TestReversed]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Axis.TestReversed]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Axis.cpp:60]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Axis.TestMove]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Axis.TestMove]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Axis.TestMove]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Axis.cpp:69]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Axis.TestMult]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Axis.TestMult]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Axis.TestMult]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Axis.cpp:77]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Base64.encode]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Base64.encode]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Base64.encode]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Base64.cpp:37]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Base64.exactlyFourBytes]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Base64.exactlyFourBytes]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Base64.exactlyFourBytes]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Base64.cpp:49]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Base64.twoEqualsSignsPadding]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Base64.twoEqualsSignsPadding]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Base64.twoEqualsSignsPadding]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Base64.cpp:66]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Base64.oneEqualsSignPadding]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Base64.oneEqualsSignPadding]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Base64.oneEqualsSignPadding]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Base64.cpp:80]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BitmaskTest.toUnderlyingType]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BitmaskTest.toUnderlyingType]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BitmaskTest.toUnderlyingType]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Bitmask.cpp:21]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BoundBox.TestDefault]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BoundBox.TestDefault]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BoundBox.TestDefault]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/BoundBox.cpp:13]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BoundBox.TestVoid]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BoundBox.TestVoid]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BoundBox.TestVoid]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/BoundBox.cpp:19]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BoundBox.TestCopy]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BoundBox.TestCopy]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BoundBox.TestCopy]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/BoundBox.cpp:29]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BoundBox.TestAssign]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BoundBox.TestAssign]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BoundBox.TestAssign]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/BoundBox.cpp:44]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BoundBox.TestPoints]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BoundBox.TestPoints]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BoundBox.TestPoints]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/BoundBox.cpp:60]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BoundBox.TestDistance]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BoundBox.TestDistance]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BoundBox.TestDistance]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/BoundBox.cpp:73]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BoundBox.TestEmptySpan]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BoundBox.TestEmptySpan]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BoundBox.TestEmptySpan]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/BoundBox.cpp:90]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BoundBox.TestNonEmptySpan]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BoundBox.TestNonEmptySpan]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BoundBox.TestNonEmptySpan]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/BoundBox.cpp:96]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BoundBox.TestArray]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BoundBox.TestArray]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BoundBox.TestArray]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/BoundBox.cpp:113]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BoundBox.TestIntersect]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BoundBox.TestIntersect]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BoundBox.TestIntersect]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/BoundBox.cpp:130]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BoundBox.TestIntersect2D]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BoundBox.TestIntersect2D]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BoundBox.TestIntersect2D]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/BoundBox.cpp:153]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BoundBox.TestUnite]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BoundBox.TestUnite]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BoundBox.TestUnite]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/BoundBox.cpp:166]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BoundBox.TestAdd]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BoundBox.TestAdd]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BoundBox.TestAdd]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/BoundBox.cpp:193]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BoundBox.TestCenter]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BoundBox.TestCenter]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BoundBox.TestCenter]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/BoundBox.cpp:206]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BoundBox.TestMinimum]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BoundBox.TestMinimum]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BoundBox.TestMinimum]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/BoundBox.cpp:215]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BoundBox.TestMaximum]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BoundBox.TestMaximum]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BoundBox.TestMaximum]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/BoundBox.cpp:224]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BoundBox.TestDiagonalLength]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BoundBox.TestDiagonalLength]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BoundBox.TestDiagonalLength]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/BoundBox.cpp:233]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BoundBox.TestVolume]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BoundBox.TestVolume]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BoundBox.TestVolume]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/BoundBox.cpp:243]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BoundBox.TestDiagonalEnlarge]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BoundBox.TestDiagonalEnlarge]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BoundBox.TestDiagonalEnlarge]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/BoundBox.cpp:253]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BoundBox.TestDiagonalShrink]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BoundBox.TestDiagonalShrink]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BoundBox.TestDiagonalShrink]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/BoundBox.cpp:264]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BoundBox.TestDiagonalMove]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BoundBox.TestDiagonalMove]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BoundBox.TestDiagonalMove]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/BoundBox.cpp:276]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BoundBox.TestDiagonalScale]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BoundBox.TestDiagonalScale]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BoundBox.TestDiagonalScale]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/BoundBox.cpp:292]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Builder3D.openInventor]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Builder3D.openInventor]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Builder3D.openInventor]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Builder3D.cpp:5]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TestColor.equal]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TestColor.equal]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestColor.equal]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Color.cpp:6]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TestColor.round]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TestColor.round]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestColor.round]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Color.cpp:19]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TestColor.packedValue]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TestColor.packedValue]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestColor.packedValue]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Color.cpp:27]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TestColor.packedRGB]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TestColor.packedRGB]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestColor.packedRGB]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Color.cpp:42]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TestColor.packedARGB]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TestColor.packedARGB]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestColor.packedARGB]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Color.cpp:58]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TestColor.asPackedRGB]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TestColor.asPackedRGB]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestColor.asPackedRGB]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Color.cpp:132]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TestColor.fromPackedRGB]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TestColor.fromPackedRGB]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestColor.fromPackedRGB]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Color.cpp:145]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TestColor.asPackedRGBA]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TestColor.asPackedRGBA]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestColor.asPackedRGBA]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Color.cpp:160]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TestColor.fromPackedRGBA]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TestColor.fromPackedRGBA]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestColor.fromPackedRGBA]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Color.cpp:174]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TestColor.setValue]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TestColor.setValue]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestColor.setValue]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Color.cpp:191]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TestColor.asValue]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TestColor.asValue]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestColor.asValue]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Color.cpp:206]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TestColor.asHexString]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TestColor.asHexString]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestColor.asHexString]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Color.cpp:221]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TestColor.fromHexString]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TestColor.fromHexString]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestColor.fromHexString]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Color.cpp:232]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Console.DirectModeDeliversToObserver]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Console.DirectModeDeliversToObserver]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Console.DirectModeDeliversToObserver]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Console.cpp:77]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Console.QueuedModeFallsBackToDirectWithoutHandler]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Console.QueuedModeFallsBackToDirectWithoutHandler]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Console.QueuedModeFallsBackToDirectWithoutHandler]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Console.cpp:93]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Console.QueuedModeCallsPostEventHandlerWhenSet]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Console.QueuedModeCallsPostEventHandlerWhenSet]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Console.QueuedModeCallsPostEventHandlerWhenSet]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Console.cpp:112]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Console.RefreshCallsHandlerWhenEnabled]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Console.RefreshCallsHandlerWhenEnabled]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Console.RefreshCallsHandlerWhenEnabled]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Console.cpp:138]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CoordinateSystem.TestDefault]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CoordinateSystem.TestDefault]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CoordinateSystem.TestDefault]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CoordinateSystem.cpp:7]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CoordinateSystem.TestSetAxisFailure]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CoordinateSystem.TestSetAxisFailure]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CoordinateSystem.TestSetAxisFailure]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CoordinateSystem.cpp:16]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CoordinateSystem.TestSetAxis]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CoordinateSystem.TestSetAxis]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CoordinateSystem.TestSetAxis]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CoordinateSystem.cpp:23]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CoordinateSystem.TestSetXDir]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CoordinateSystem.TestSetXDir]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CoordinateSystem.TestSetXDir]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CoordinateSystem.cpp:37]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CoordinateSystem.TestSetYDir]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CoordinateSystem.TestSetYDir]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CoordinateSystem.TestSetYDir]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CoordinateSystem.cpp:47]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CoordinateSystem.TestSetZDir]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CoordinateSystem.TestSetZDir]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CoordinateSystem.TestSetZDir]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CoordinateSystem.cpp:57]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CoordinateSystem.TestTransformPlacement]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CoordinateSystem.TestTransformPlacement]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CoordinateSystem.TestTransformPlacement]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CoordinateSystem.cpp:67]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CoordinateSystem.TestMultTransformPlacement]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CoordinateSystem.TestMultTransformPlacement]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CoordinateSystem.TestMultTransformPlacement]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CoordinateSystem.cpp:83]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CoordinateSystem.TestTransformRotation]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CoordinateSystem.TestTransformRotation]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CoordinateSystem.TestTransformRotation]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CoordinateSystem.cpp:102]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CoordinateSystem.TestTransformPoint]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CoordinateSystem.TestTransformPoint]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CoordinateSystem.TestTransformPoint]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CoordinateSystem.cpp:116]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CoordinateSystem.TestSetPlacement]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CoordinateSystem.TestSetPlacement]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CoordinateSystem.TestSetPlacement]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CoordinateSystem.cpp:132]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.parseMissingFileThrows]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.parseMissingFileThrows]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.parseMissingFileThrows]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:238]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.parseFileTooSmall]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.parseFileTooSmall]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.parseFileTooSmall]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:244]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.parseFileTooLarge]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.parseFileTooLarge]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.parseFileTooLarge]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:255]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.parseGoodCrashReportLoads]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.parseGoodCrashReportLoads]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.parseGoodCrashReportLoads]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:268]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.parseDropsFaultAddressForCodeThatHasNone]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.parseDropsFaultAddressForCodeThatHasNone]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.parseDropsFaultAddressForCodeThatHasNone]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:306]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.parseNamesUnrecognizedFaultCodeWithItsHexValue]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.parseNamesUnrecognizedFaultCodeWithItsHexValue]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.parseNamesUnrecognizedFaultCodeWithItsHexValue]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:328]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.parseBadMagicNumber]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.parseBadMagicNumber]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.parseBadMagicNumber]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:354]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.parseBadVersionNumber]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.parseBadVersionNumber]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.parseBadVersionNumber]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:368]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.parseBadFileSize]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.parseBadFileSize]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.parseBadFileSize]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:383]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.parseBadStringTableOffset]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.parseBadStringTableOffset]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.parseBadStringTableOffset]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:397]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.parseBadFrameCount]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.parseBadFrameCount]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.parseBadFrameCount]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:414]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.parseBadFrameTableOffset]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.parseBadFrameTableOffset]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.parseBadFrameTableOffset]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:431]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.parseBadCRC]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.parseBadCRC]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.parseBadCRC]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:449]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.matchingHashAttemptsSymbolication]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.matchingHashAttemptsSymbolication]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.matchingHashAttemptsSymbolication]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:468]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.realCrashCapturesUsableFrames]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.realCrashCapturesUsableFrames]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.realCrashCapturesUsableFrames]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:564]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.DeliberateSegfaultRoundTrip]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.DISABLED_DeliberateSegfaultRoundTrip]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.DeliberateSegfaultRoundTrip]=]
  PROPERTIES
    DISABLED YES
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:620]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.trimLeadingPlumbingFramesLeavesNoPlumbingAlone]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.trimLeadingPlumbingFramesLeavesNoPlumbingAlone]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.trimLeadingPlumbingFramesLeavesNoPlumbingAlone]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:643]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.trimLeadingPlumbingFramesLeavesEmptyVectorAlone]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.trimLeadingPlumbingFramesLeavesEmptyVectorAlone]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.trimLeadingPlumbingFramesLeavesEmptyVectorAlone]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:654]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.trimLeadingPlumbingFramesRemovesSingleExpectedSymbolFromTop]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.trimLeadingPlumbingFramesRemovesSingleExpectedSymbolFromTop]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.trimLeadingPlumbingFramesRemovesSingleExpectedSymbolFromTop]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:661]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.trimLeadingPlumbingFramesRemovesAnythingAboveFirstTrampoline]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.trimLeadingPlumbingFramesRemovesAnythingAboveFirstTrampoline]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.trimLeadingPlumbingFramesRemovesAnythingAboveFirstTrampoline]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:673]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.trimLeadingPlumbingFramesKeepsUnsymbolicatedTopFrame]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.trimLeadingPlumbingFramesKeepsUnsymbolicatedTopFrame]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.trimLeadingPlumbingFramesKeepsUnsymbolicatedTopFrame]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:687]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.trimLeadingPlumbingFramesKeepsAllWhenTrampolineIsDeepest]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.trimLeadingPlumbingFramesKeepsAllWhenTrampolineIsDeepest]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.trimLeadingPlumbingFramesKeepsAllWhenTrampolineIsDeepest]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:700]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.scanDetectsAndArchivesGoodReport]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.scanDetectsAndArchivesGoodReport]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.scanDetectsAndArchivesGoodReport]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:711]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.scanDetectsAndRenamesBadReport]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.scanDetectsAndRenamesBadReport]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.scanDetectsAndRenamesBadReport]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:725]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.scanCorrectlyHandlesMixOfGoodAndBadReports]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.scanCorrectlyHandlesMixOfGoodAndBadReports]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.scanCorrectlyHandlesMixOfGoodAndBadReports]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:738]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.scanReportsIncompleteFiles]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.scanReportsIncompleteFiles]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.scanReportsIncompleteFiles]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:760]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.clearRemovesEverything]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.clearRemovesEverything]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.clearRemovesEverything]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:784]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.clearBeforeScanDoesNothing]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.clearBeforeScanDoesNothing]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.clearBeforeScanDoesNothing]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:806]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.scanSetsOSVersionWhenPresent]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.scanSetsOSVersionWhenPresent]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.scanSetsOSVersionWhenPresent]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:811]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.scanDoesNotSetOSVersionWhenNotPresent]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.scanDoesNotSetOSVersionWhenNotPresent]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.scanDoesNotSetOSVersionWhenNotPresent]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:827]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.retentionKeepsAllWhenUnderCountAndYoung]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.retentionKeepsAllWhenUnderCountAndYoung]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.retentionKeepsAllWhenUnderCountAndYoung]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:857]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.retentionDeletesOldestBeyondCount]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.retentionDeletesOldestBeyondCount]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.retentionDeletesOldestBeyondCount]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:877]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.retentionKeepsYoungBeyondCount]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.retentionKeepsYoungBeyondCount]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.retentionKeepsYoungBeyondCount]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:901]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.retentionKeepsOldWithinCount]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.retentionKeepsOldWithinCount]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.retentionKeepsOldWithinCount]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:925]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.retentionDeletesOnlyOldAndBeyondCount]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.retentionDeletesOnlyOldAndBeyondCount]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.retentionDeletesOnlyOldAndBeyondCount]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:949]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.retentionDeletesCompanionDump]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.retentionDeletesCompanionDump]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.retentionDeletesCompanionDump]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:973]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.faultAddressIsMeaningfulReturnsFalseForCodeWithoutAddress]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.faultAddressIsMeaningfulReturnsFalseForCodeWithoutAddress]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.faultAddressIsMeaningfulReturnsFalseForCodeWithoutAddress]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:994]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.faultAddressIsMeaningfulReturnsTrueForCodeWithAddress]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.faultAddressIsMeaningfulReturnsTrueForCodeWithAddress]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.faultAddressIsMeaningfulReturnsTrueForCodeWithAddress]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:999]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.describeFaultCodeGivesValidResultForValidCode]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.describeFaultCodeGivesValidResultForValidCode]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.describeFaultCodeGivesValidResultForValidCode]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:1005]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CrashReporterTests.describeFaultCodeGivesNulloptForBadCode]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=CrashReporterTests.describeFaultCodeGivesNulloptForBadCode]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CrashReporterTests.describeFaultCodeGivesNulloptForBadCode]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/CrashReporter_tests.cpp:1013]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DualNumber.TestDefault]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=DualNumber.TestDefault]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DualNumber.TestDefault]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/DualNumber.cpp:4]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DualNumber.TestNonDefault]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=DualNumber.TestNonDefault]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DualNumber.TestNonDefault]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/DualNumber.cpp:11]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DualNumber.TestNegate]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=DualNumber.TestNegate]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DualNumber.TestNegate]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/DualNumber.cpp:22]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DualNumber.TestPlus]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=DualNumber.TestPlus]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DualNumber.TestPlus]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/DualNumber.cpp:29]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DualNumber.TestMinus]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=DualNumber.TestMinus]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DualNumber.TestMinus]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/DualNumber.cpp:47]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DualNumber.TestMultiply]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=DualNumber.TestMultiply]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DualNumber.TestMultiply]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/DualNumber.cpp:65]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DualNumber.TestDivide]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=DualNumber.TestDivide]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DualNumber.TestDivide]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/DualNumber.cpp:83]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DualNumber.TestPow]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=DualNumber.TestPow]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DualNumber.TestPow]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/DualNumber.cpp:97]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DualQuaternion.TestDefault]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=DualQuaternion.TestDefault]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DualQuaternion.TestDefault]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/DualQuaternion.cpp:5]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DualQuaternion.TestFromDouble]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=DualQuaternion.TestFromDouble]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DualQuaternion.TestFromDouble]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/DualQuaternion.cpp:18]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DualQuaternion.TestFromDoubles]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=DualQuaternion.TestFromDoubles]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DualQuaternion.TestFromDoubles]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/DualQuaternion.cpp:31]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DualQuaternion.TestFromDual]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=DualQuaternion.TestFromDual]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DualQuaternion.TestFromDual]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/DualQuaternion.cpp:44]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DualQuaternion.TestIdentity]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=DualQuaternion.TestIdentity]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DualQuaternion.TestIdentity]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/DualQuaternion.cpp:58]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DualQuaternion.TestReal]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=DualQuaternion.TestReal]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DualQuaternion.TestReal]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/DualQuaternion.cpp:71]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DualQuaternion.TestDual]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=DualQuaternion.TestDual]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DualQuaternion.TestDual]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/DualQuaternion.cpp:84]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DualQuaternion.TestConjugate]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=DualQuaternion.TestConjugate]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DualQuaternion.TestConjugate]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/DualQuaternion.cpp:97]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DualQuaternion.TestVec]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=DualQuaternion.TestVec]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DualQuaternion.TestVec]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/DualQuaternion.cpp:110]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DualQuaternion.TestLength]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=DualQuaternion.TestLength]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DualQuaternion.TestLength]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/DualQuaternion.cpp:123]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DualQuaternion.TestTheta]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=DualQuaternion.TestTheta]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DualQuaternion.TestTheta]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/DualQuaternion.cpp:129]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DualQuaternion.TestDot]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=DualQuaternion.TestDot]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DualQuaternion.TestDot]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/DualQuaternion.cpp:135]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DualQuaternion.TestNegate]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=DualQuaternion.TestNegate]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DualQuaternion.TestNegate]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/DualQuaternion.cpp:143]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DualQuaternion.TestPlus]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=DualQuaternion.TestPlus]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DualQuaternion.TestPlus]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/DualQuaternion.cpp:157]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DualQuaternion.TestMinus]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=DualQuaternion.TestMinus]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DualQuaternion.TestMinus]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/DualQuaternion.cpp:172]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DualQuaternion.TestMultiplyQuat]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=DualQuaternion.TestMultiplyQuat]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DualQuaternion.TestMultiplyQuat]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/DualQuaternion.cpp:187]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DualQuaternion.TestMultiplyNumber]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=DualQuaternion.TestMultiplyNumber]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DualQuaternion.TestMultiplyNumber]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/DualQuaternion.cpp:202]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DualQuaternion.TestMultiplyScalar]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=DualQuaternion.TestMultiplyScalar]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DualQuaternion.TestMultiplyScalar]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/DualQuaternion.cpp:228]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DualQuaternion.TestPow]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=DualQuaternion.TestPow]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DualQuaternion.TestPow]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/DualQuaternion.cpp:253]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileException.TestWhatCombinesUntranslatedMessageAndPath]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileException.TestWhatCombinesUntranslatedMessageAndPath]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileException.TestWhatCombinesUntranslatedMessageAndPath]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Exception.cpp:7]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileException.TestTranslatedMessageFallsBackToSourceAndKeepsPath]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileException.TestTranslatedMessageFallsBackToSourceAndKeepsPath]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileException.TestTranslatedMessageFallsBackToSourceAndKeepsPath]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Exception.cpp:18]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileException.TestMessagesMatchTheTranslationKeys]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileException.TestMessagesMatchTheTranslationKeys]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileException.TestMessagesMatchTheTranslationKeys]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Exception.cpp:27]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileLockTest.TryLockZeroSucceedsWhenAvailable]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileLockTest.TryLockZeroSucceedsWhenAvailable]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileLockTest.TryLockZeroSucceedsWhenAvailable]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/FileLock.cpp:9]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileInfoTest.TestDirectoryPath]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileInfoTest.TestDirectoryPath]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileInfoTest.TestDirectoryPath]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/FileInfo.cpp:39]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileInfoTest.TestExistsDirectory]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileInfoTest.TestExistsDirectory]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileInfoTest.TestExistsDirectory]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/FileInfo.cpp:46]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileInfoTest.TestCreateDirectory]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileInfoTest.TestCreateDirectory]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileInfoTest.TestCreateDirectory]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/FileInfo.cpp:51]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileInfoTest.TestDirectoryContent]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileInfoTest.TestDirectoryContent]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileInfoTest.TestDirectoryContent]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/FileInfo.cpp:58]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileInfoTest.TestCheckPermission]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileInfoTest.TestCheckPermission]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileInfoTest.TestCheckPermission]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/FileInfo.cpp:66]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileInfoTest.TestCheckNoPermission]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileInfoTest.TestCheckNoPermission]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileInfoTest.TestCheckNoPermission]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/FileInfo.cpp:72]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileInfoTest.TestSetPermission]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileInfoTest.TestSetPermission]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileInfoTest.TestSetPermission]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/FileInfo.cpp:80]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileInfoTest.TestCheckFile]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileInfoTest.TestCheckFile]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileInfoTest.TestCheckFile]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/FileInfo.cpp:98]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileInfoTest.TestCheckDirectory]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileInfoTest.TestCheckDirectory]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileInfoTest.TestCheckDirectory]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/FileInfo.cpp:108]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileInfoTest.TestSize]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileInfoTest.TestSize]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileInfoTest.TestSize]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/FileInfo.cpp:118]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileInfoTest.TestLastModified]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileInfoTest.TestLastModified]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileInfoTest.TestLastModified]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/FileInfo.cpp:128]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileInfoTest.TestDeleteFile]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileInfoTest.TestDeleteFile]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileInfoTest.TestDeleteFile]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/FileInfo.cpp:137]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileInfoTest.TestRenameFile]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileInfoTest.TestRenameFile]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileInfoTest.TestRenameFile]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/FileInfo.cpp:144]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileInfoTest.TestCopyFile]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileInfoTest.TestCopyFile]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileInfoTest.TestCopyFile]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/FileInfo.cpp:152]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileInfoPathConversionTest.RoundTripAsciiPath]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileInfoPathConversionTest.RoundTripAsciiPath]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileInfoPathConversionTest.RoundTripAsciiPath]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/FileInfo.cpp:166]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileInfoPathConversionTest.RoundTripNonAsciiPath]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileInfoPathConversionTest.RoundTripNonAsciiPath]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileInfoPathConversionTest.RoundTripNonAsciiPath]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/FileInfo.cpp:174]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileInfoPathConversionTest.RoundTripChineseCharacters]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileInfoPathConversionTest.RoundTripChineseCharacters]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileInfoPathConversionTest.RoundTripChineseCharacters]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/FileInfo.cpp:183]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileInfoPathConversionTest.RoundTripAccentedCharacters]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileInfoPathConversionTest.RoundTripAccentedCharacters]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileInfoPathConversionTest.RoundTripAccentedCharacters]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/FileInfo.cpp:192]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileInfoPathConversionTest.RoundTripEmptyString]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileInfoPathConversionTest.RoundTripEmptyString]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileInfoPathConversionTest.RoundTripEmptyString]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/FileInfo.cpp:201]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileInfoPathConversionTest.PathToStringPreservesUtf8]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileInfoPathConversionTest.PathToStringPreservesUtf8]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileInfoPathConversionTest.PathToStringPreservesUtf8]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/FileInfo.cpp:209]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileInfoPathConversionTest.StringToPathProducesValidPath]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileInfoPathConversionTest.StringToPathProducesValidPath]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileInfoPathConversionTest.StringToPathProducesValidPath]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/FileInfo.cpp:220]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileInfoSafeArchiveEntryPathTest.AcceptsNamesWrittenByFreeCAD]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileInfoSafeArchiveEntryPathTest.AcceptsNamesWrittenByFreeCAD]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileInfoSafeArchiveEntryPathTest.AcceptsNamesWrittenByFreeCAD]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/FileInfo.cpp:261]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileInfoSafeArchiveEntryPathTest.RejectsParentDirectoryTraversal]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileInfoSafeArchiveEntryPathTest.RejectsParentDirectoryTraversal]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileInfoSafeArchiveEntryPathTest.RejectsParentDirectoryTraversal]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/FileInfo.cpp:274]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileInfoSafeArchiveEntryPathTest.LeadingDoubleSeparatorDoesNotEatAComponent]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileInfoSafeArchiveEntryPathTest.LeadingDoubleSeparatorDoesNotEatAComponent]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileInfoSafeArchiveEntryPathTest.LeadingDoubleSeparatorDoesNotEatAComponent]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/FileInfo.cpp:284]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileInfoSafeArchiveEntryPathTest.RejectsBackslashTraversal]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileInfoSafeArchiveEntryPathTest.RejectsBackslashTraversal]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileInfoSafeArchiveEntryPathTest.RejectsBackslashTraversal]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/FileInfo.cpp:293]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileInfoSafeArchiveEntryPathTest.RejectsColonNames]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileInfoSafeArchiveEntryPathTest.RejectsColonNames]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileInfoSafeArchiveEntryPathTest.RejectsColonNames]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/FileInfo.cpp:305]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileInfoSafeArchiveEntryPathTest.RejectsNamesThatNormalizeToNothing]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileInfoSafeArchiveEntryPathTest.RejectsNamesThatNormalizeToNothing]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileInfoSafeArchiveEntryPathTest.RejectsNamesThatNormalizeToNothing]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/FileInfo.cpp:314]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileInfoSafeArchiveEntryPathTest.NormalizesRedundantComponents]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileInfoSafeArchiveEntryPathTest.NormalizesRedundantComponents]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileInfoSafeArchiveEntryPathTest.NormalizesRedundantComponents]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/FileInfo.cpp:322]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileInfoSafeArchiveEntryPathTest.ContainedDotsAreAllowed]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileInfoSafeArchiveEntryPathTest.ContainedDotsAreAllowed]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileInfoSafeArchiveEntryPathTest.ContainedDotsAreAllowed]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/FileInfo.cpp:329]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileInfoSafeArchiveEntryPathTest.HostileNamesCannotEscapeWhenJoined]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=FileInfoSafeArchiveEntryPathTest.HostileNamesCannotEscapeWhenJoined]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileInfoSafeArchiveEntryPathTest.HostileNamesCannotEscapeWhenJoined]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/FileInfo.cpp:336]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StdInputStream.SanitizesNullAndInvalidUtf8]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=StdInputStream.SanitizesNullAndInvalidUtf8]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StdInputStream.SanitizesNullAndInvalidUtf8]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/InputSource.cpp:8]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Reference.TestNull]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Reference.TestNull]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Reference.TestNull]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Handle.cpp:19]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Reference.TestConstructor]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Reference.TestConstructor]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Reference.TestConstructor]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Handle.cpp:25]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Reference.TestCopy]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Reference.TestCopy]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Reference.TestCopy]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Handle.cpp:31]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Reference.TestAssignRaw]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Reference.TestAssignRaw]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Reference.TestAssignRaw]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Handle.cpp:44]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Reference.TestAssignRef]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Reference.TestAssignRef]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Reference.TestAssignRef]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Handle.cpp:51]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Reference.TestRefHandle]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Reference.TestRefHandle]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Reference.TestRefHandle]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Handle.cpp:65]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestShearing]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestShearing]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestShearing]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:8]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestMultLeftRight]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestMultLeftRight]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestMultLeftRight]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:15]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestNoScale]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestNoScale]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestNoScale]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:25]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestUniformScalePlusTwo]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestUniformScalePlusTwo]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestUniformScalePlusTwo]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:33]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestUniformScaleRight]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestUniformScaleRight]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestUniformScaleRight]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:41]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestNonUniformScaleRight]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestNonUniformScaleRight]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestNonUniformScaleRight]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:51]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestUniformScaleMinusOne]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestUniformScaleMinusOne]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestUniformScaleMinusOne]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:61]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestUniformScaleMinusTwo]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestUniformScaleMinusTwo]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestUniformScaleMinusTwo]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:68]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestNonUniformScaleLeftOne]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestNonUniformScaleLeftOne]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestNonUniformScaleLeftOne]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:75]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestNonUniformScaleLeftTwo]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestNonUniformScaleLeftTwo]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestNonUniformScaleLeftTwo]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:84]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestDiagonal]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestDiagonal]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestDiagonal]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:92]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestColRow]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestColRow]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestColRow]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:100]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestColRowMisc]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestColRowMisc]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestColRowMisc]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:111]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestUnity]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestUnity]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestUnity]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:125]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestNull]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestNull]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestNull]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:137]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestMultVec]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestMultVec]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestMultVec]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:146]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestMult]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestMult]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestMult]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:173]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestMultAssign]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestMultAssign]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestMultAssign]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:192]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestAdd]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestAdd]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestAdd]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:210]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestAddAssign]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestAddAssign]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestAddAssign]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:228]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestSub]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestSub]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestSub]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:246]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestSubAssign]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestSubAssign]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestSubAssign]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:264]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestHatOperator]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestHatOperator]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestHatOperator]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:282]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestHatOperatorFloat]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestHatOperatorFloat]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestHatOperatorFloat]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:297]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestDyadic]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestDyadic]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestDyadic]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:312]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestDyadicFloat]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestDyadicFloat]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestDyadicFloat]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:327]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestDecomposeScale]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestDecomposeScale]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestDecomposeScale]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:342]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestDecomposeRotation]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestDecomposeRotation]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestDecomposeRotation]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:354]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestDecomposeMove]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestDecomposeMove]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestDecomposeMove]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:368]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestDecomposeMoveFloat]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestDecomposeMoveFloat]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestDecomposeMoveFloat]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:380]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestDecompose]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestDecompose]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestDecompose]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:392]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestRotLine]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestRotLine]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestRotLine]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:412]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestRotAxisFormula]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestRotAxisFormula]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestRotAxisFormula]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:427]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestTransform]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestTransform]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestTransform]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:461]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestTransformFloat]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestTransformFloat]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestTransformFloat]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:476]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestInverseOrthogonal]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestInverseOrthogonal]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestInverseOrthogonal]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:491]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestTranspose]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestTranspose]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestTranspose]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:507]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestTrace]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestTrace]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestTrace]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:523]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestSetAndGetMatrix]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestSetAndGetMatrix]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestSetAndGetMatrix]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:533]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestSetAndGetGLMatrix]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestSetAndGetGLMatrix]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestSetAndGetGLMatrix]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:548]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Matrix.TestToAndFromString]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Matrix.TestToAndFromString]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Matrix.TestToAndFromString]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Matrix.cpp:563]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NumericFormattingTest.createsLocaleSpecificSeparators]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=NumericFormattingTest.createsLocaleSpecificSeparators]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NumericFormattingTest.createsLocaleSpecificSeparators]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/NumericFormatting.cpp:12]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NumericFormattingTest.formattedNativeDigitsRoundTripThroughScannerAndQuantity]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=NumericFormattingTest.formattedNativeDigitsRoundTripThroughScannerAndQuantity]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NumericFormattingTest.formattedNativeDigitsRoundTripThroughScannerAndQuantity]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/NumericFormatting.cpp:38]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NumericFormattingTest.formatsValuesWithEffectiveSeparators]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=NumericFormattingTest.formatsValuesWithEffectiveSeparators]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NumericFormattingTest.formatsValuesWithEffectiveSeparators]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/NumericFormatting.cpp:69]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NumericFormattingTest.cLocaleUsesDeterministicFallback]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=NumericFormattingTest.cLocaleUsesDeterministicFallback]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NumericFormattingTest.cLocaleUsesDeterministicFallback]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/NumericFormatting.cpp:86]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NumericFormattingTest.normalizesIcuLocaleIdentifiers]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=NumericFormattingTest.normalizesIcuLocaleIdentifiers]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NumericFormattingTest.normalizesIcuLocaleIdentifiers]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/NumericFormatting.cpp:92]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NumericFormattingTest.rejectsBogusIcuLocaleIdentifiers]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=NumericFormattingTest.rejectsBogusIcuLocaleIdentifiers]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NumericFormattingTest.rejectsBogusIcuLocaleIdentifiers]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/NumericFormatting.cpp:99]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NumericFormattingTest.publishedStateIsACompleteSnapshot]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=NumericFormattingTest.publishedStateIsACompleteSnapshot]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NumericFormattingTest.publishedStateIsACompleteSnapshot]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/NumericFormatting.cpp:108]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NumericFormattingTest.failedLocaleResolutionDoesNotPublishPartialState]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=NumericFormattingTest.failedLocaleResolutionDoesNotPublishPartialState]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NumericFormattingTest.failedLocaleResolutionDoesNotPublishPartialState]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/NumericFormatting.cpp:119]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NumericInputTest.canonicalAndLocalizedDecimals]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=NumericInputTest.canonicalAndLocalizedDecimals]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NumericInputTest.canonicalAndLocalizedDecimals]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/NumericInput.cpp:36]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NumericInputTest.westernGroupingAndScientificNotation]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=NumericInputTest.westernGroupingAndScientificNotation]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NumericInputTest.westernGroupingAndScientificNotation]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/NumericInput.cpp:59]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NumericInputTest.indianGroupingUsesSecondarySize]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=NumericInputTest.indianGroupingUsesSecondarySize]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NumericInputTest.indianGroupingUsesSecondarySize]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/NumericInput.cpp:76]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NumericInputTest.malformedGroupingIsInvalid]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=NumericInputTest.malformedGroupingIsInvalid]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NumericInputTest.malformedGroupingIsInvalid]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/NumericInput.cpp:87]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NumericInputTest.multipleDecimalsAndIncompleteExponentsAreDiagnosed]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=NumericInputTest.multipleDecimalsAndIncompleteExponentsAreDiagnosed]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NumericInputTest.multipleDecimalsAndIncompleteExponentsAreDiagnosed]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/NumericInput.cpp:98]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NumericInputTest.DotGroupingAndCanonicalDecimalHaveAnExplicitPolicy]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=NumericInputTest.DotGroupingAndCanonicalDecimalHaveAnExplicitPolicy]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NumericInputTest.DotGroupingAndCanonicalDecimalHaveAnExplicitPolicy]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/NumericInput.cpp:119]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NumericInputTest.negativeAndLocalizedSigns]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=NumericInputTest.negativeAndLocalizedSigns]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NumericInputTest.negativeAndLocalizedSigns]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/NumericInput.cpp:148]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NumericInputTest.InvalidUtf8IsNotALocalizedDigit]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=NumericInputTest.InvalidUtf8IsNotALocalizedDigit]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NumericInputTest.InvalidUtf8IsNotALocalizedDigit]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/NumericInput.cpp:167]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NumericInputTest.positiveSignsAreAcceptedByCanonicalConversion]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=NumericInputTest.positiveSignsAreAcceptedByCanonicalConversion]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NumericInputTest.positiveSignsAreAcceptedByCanonicalConversion]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/NumericInput.cpp:178]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NumericInputTest.OutOfRangeScientificNotationIsDiagnosed]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=NumericInputTest.OutOfRangeScientificNotationIsDiagnosed]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NumericInputTest.OutOfRangeScientificNotationIsDiagnosed]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/NumericInput.cpp:197]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NumericInputTest.exactGroupingSymbolsAreRequired]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=NumericInputTest.exactGroupingSymbolsAreRequired]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NumericInputTest.exactGroupingSymbolsAreRequired]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/NumericInput.cpp:207]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NumericInputTest.FunctionArgumentsTakePrecedenceOverCommaGrouping]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=NumericInputTest.FunctionArgumentsTakePrecedenceOverCommaGrouping]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NumericInputTest.FunctionArgumentsTakePrecedenceOverCommaGrouping]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/NumericInput.cpp:253]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NumericInputTest.GroupingPlacementMutationsFollowLocalePattern]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=NumericInputTest.GroupingPlacementMutationsFollowLocalePattern]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NumericInputTest.GroupingPlacementMutationsFollowLocalePattern]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/NumericInput.cpp:277]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OkLchTest.RoundTripBlack]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=OkLchTest.RoundTripBlack]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OkLchTest.RoundTripBlack]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/OkLch.cpp:14]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OkLchTest.RoundTripWhite]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=OkLchTest.RoundTripWhite]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OkLchTest.RoundTripWhite]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/OkLch.cpp:24]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OkLchTest.RoundTripRed]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=OkLchTest.RoundTripRed]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OkLchTest.RoundTripRed]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/OkLch.cpp:34]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OkLchTest.RoundTripGreen]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=OkLchTest.RoundTripGreen]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OkLchTest.RoundTripGreen]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/OkLch.cpp:44]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OkLchTest.RoundTripBlue]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=OkLchTest.RoundTripBlue]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OkLchTest.RoundTripBlue]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/OkLch.cpp:54]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OkLchTest.RoundTripMidGray]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=OkLchTest.RoundTripMidGray]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OkLchTest.RoundTripMidGray]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/OkLch.cpp:64]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OkLchTest.BlackHasZeroLightness]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=OkLchTest.BlackHasZeroLightness]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OkLchTest.BlackHasZeroLightness]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/OkLch.cpp:75]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OkLchTest.WhiteHasFullLightness]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=OkLchTest.WhiteHasFullLightness]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OkLchTest.WhiteHasFullLightness]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/OkLch.cpp:81]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OkLchTest.GrayHasLowChroma]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=OkLchTest.GrayHasLowChroma]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OkLchTest.GrayHasLowChroma]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/OkLch.cpp:87]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OkLchTest.GamutMappingClampsToValidSrgb]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=OkLchTest.GamutMappingClampsToValidSrgb]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OkLchTest.GamutMappingClampsToValidSrgb]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/OkLch.cpp:94]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[OkLchTest.AlphaPreserved]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=OkLchTest.AlphaPreserved]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[OkLchTest.AlphaPreserved]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/OkLch.cpp:107]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterTest.TestValid]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterTest.TestValid]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterTest.TestValid]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Parameter.cpp:98]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterTest.TestCreate]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterTest.TestCreate]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterTest.TestCreate]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Parameter.cpp:107]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterTest.TestGroup]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterTest.TestGroup]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterTest.TestGroup]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Parameter.cpp:115]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterTest.TestGroupName]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterTest.TestGroupName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterTest.TestGroupName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Parameter.cpp:131]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterTest.TestEmptyGroupName]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterTest.TestEmptyGroupName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterTest.TestEmptyGroupName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Parameter.cpp:141]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterTest.TestGroupNames]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterTest.TestGroupNames]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterTest.TestGroupNames]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Parameter.cpp:149]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterTest.TestPath]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterTest.TestPath]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterTest.TestPath]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Parameter.cpp:158]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterTest.TestBool]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterTest.TestBool]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterTest.TestBool]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Parameter.cpp:169]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterTest.TestInt]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterTest.TestInt]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterTest.TestInt]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Parameter.cpp:189]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterTest.TestUnsigned]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterTest.TestUnsigned]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterTest.TestUnsigned]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Parameter.cpp:209]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterTest.TestFloat]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterTest.TestFloat]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterTest.TestFloat]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Parameter.cpp:229]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterTest.TestString]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterTest.TestString]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterTest.TestString]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Parameter.cpp:249]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterTest.TestColor]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterTest.TestColor]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterTest.TestColor]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Parameter.cpp:269]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterTest.TestCopy]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterTest.TestCopy]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterTest.TestCopy]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Parameter.cpp:292]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterTest.TestInsert]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterTest.TestInsert]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterTest.TestInsert]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Parameter.cpp:312]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterTest.TestRevert]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterTest.TestRevert]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterTest.TestRevert]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Parameter.cpp:341]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterTest.TestRemoveGroup]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterTest.TestRemoveGroup]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterTest.TestRemoveGroup]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Parameter.cpp:361]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterTest.TestRenameGroup]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterTest.TestRenameGroup]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterTest.TestRenameGroup]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Parameter.cpp:375]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterTest.TestSaveRestoreRef]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterTest.TestSaveRestoreRef]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterTest.TestSaveRestoreRef]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Parameter.cpp:391]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterTest.TestSaveRestoreNoRef]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterTest.TestSaveRestoreNoRef]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterTest.TestSaveRestoreNoRef]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Parameter.cpp:418]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterTest.TestClear]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterTest.TestClear]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterTest.TestClear]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Parameter.cpp:438]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterTest.TestGetSetAttribute]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterTest.TestGetSetAttribute]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterTest.TestGetSetAttribute]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Parameter.cpp:460]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterTest.TestGetParameterNames]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterTest.TestGetParameterNames]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterTest.TestGetParameterNames]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Parameter.cpp:504]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterTest.TestGroupRef]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterTest.TestGroupRef]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterTest.TestGroupRef]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Parameter.cpp:519]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterTest.TestGroupNoRef]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterTest.TestGroupNoRef]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterTest.TestGroupNoRef]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Parameter.cpp:538]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterTest.TestObserverRef]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterTest.TestObserverRef]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterTest.TestObserverRef]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Parameter.cpp:557]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterTest.TestNotifyAll]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterTest.TestNotifyAll]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterTest.TestNotifyAll]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Parameter.cpp:588]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterTest.TestObserverNoRef]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterTest.TestObserverNoRef]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterTest.TestObserverNoRef]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Parameter.cpp:603]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterTest.TestLockFile]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterTest.TestLockFile]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterTest.TestLockFile]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Parameter.cpp:624]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterObserverTest.TestBool]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterObserverTest.TestBool]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterObserverTest.TestBool]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/ParameterObserver.cpp:131]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterObserverTest.TestInt]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterObserverTest.TestInt]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterObserverTest.TestInt]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/ParameterObserver.cpp:145]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterObserverTest.TestUnsigned]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterObserverTest.TestUnsigned]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterObserverTest.TestUnsigned]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/ParameterObserver.cpp:158]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterObserverTest.TestFloat]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterObserverTest.TestFloat]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterObserverTest.TestFloat]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/ParameterObserver.cpp:171]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterObserverTest.TestString]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterObserverTest.TestString]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterObserverTest.TestString]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/ParameterObserver.cpp:184]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterObserverTest.TestHashKey]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterObserverTest.TestHashKey]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterObserverTest.TestHashKey]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/ParameterObserver.cpp:197]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterObserverTest.TestUnknown]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterObserverTest.TestUnknown]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterObserverTest.TestUnknown]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/ParameterObserver.cpp:211]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterObserverTest.TestWrongType]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ParameterObserverTest.TestWrongType]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterObserverTest.TestWrongType]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/ParameterObserver.cpp:221]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Placement.TestDefault]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Placement.TestDefault]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Placement.TestDefault]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Placement.cpp:9]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Placement.TestPosRot]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Placement.TestPosRot]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Placement.TestPosRot]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Placement.cpp:17]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Placement.TestPosRotCnt]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Placement.TestPosRotCnt]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Placement.TestPosRotCnt]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Placement.cpp:26]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Placement.TestMatrix]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Placement.TestMatrix]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Placement.TestMatrix]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Placement.cpp:37]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Placement.TestIdentity]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Placement.TestIdentity]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Placement.TestIdentity]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Placement.cpp:53]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Placement.TestInvert]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Placement.TestInvert]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Placement.TestInvert]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Placement.cpp:63]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Placement.TestMove]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Placement.TestMove]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Placement.TestMove]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Placement.cpp:75]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Placement.TestSame]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Placement.TestSame]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Placement.TestSame]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Placement.cpp:85]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Placement.TestMultiply]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Placement.TestMultiply]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Placement.TestMultiply]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Placement.cpp:101]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Placement.TestMultRight]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Placement.TestMultRight]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Placement.TestMultRight]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Placement.cpp:112]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Placement.TestMultLeft]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Placement.TestMultLeft]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Placement.TestMultLeft]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Placement.cpp:127]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Placement.TestMultVec]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Placement.TestMultVec]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Placement.TestMultVec]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Placement.cpp:142]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Placement.TestDualQuat]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Placement.TestDualQuat]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Placement.TestDualQuat]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Placement.cpp:153]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Placement.TestPow]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Placement.TestPow]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Placement.TestPow]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Placement.cpp:163]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Placement.TestSlerp]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Placement.TestSlerp]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Placement.TestSlerp]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Placement.cpp:179]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Placement.TestSclerp]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Placement.TestSclerp]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Placement.TestSclerp]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Placement.cpp:198]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Persistence.ValidateXmlStringReplacesDisallowed]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Persistence.ValidateXmlStringReplacesDisallowed]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Persistence.ValidateXmlStringReplacesDisallowed]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Persistence.cpp:7]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Persistence.ValidateXmlStringPreservesValidNonBmp]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Persistence.ValidateXmlStringPreservesValidNonBmp]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Persistence.ValidateXmlStringPreservesValidNonBmp]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Persistence.cpp:19]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Persistence.ValidateXmlStringReplacesDiscouraged]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Persistence.ValidateXmlStringReplacesDiscouraged]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Persistence.ValidateXmlStringReplacesDiscouraged]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Persistence.cpp:28]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PyExceptionTest.goodCallDoesNotThrow]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=PyExceptionTest.goodCallDoesNotThrow]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PyExceptionTest.goodCallDoesNotThrow]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/PyException.cpp:46]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PyExceptionTest.pythonExceptionsPropagate]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=PyExceptionTest.pythonExceptionsPropagate]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PyExceptionTest.pythonExceptionsPropagate]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/PyException.cpp:53]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PyExceptionTest.outOfRangeMapsToIndexError]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=PyExceptionTest.outOfRangeMapsToIndexError]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PyExceptionTest.outOfRangeMapsToIndexError]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/PyException.cpp:63]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PyExceptionTest.lengthErrorMapsToIndexError]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=PyExceptionTest.lengthErrorMapsToIndexError]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PyExceptionTest.lengthErrorMapsToIndexError]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/PyException.cpp:73]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PyExceptionTest.otherLogicErrorsMapToValueError]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=PyExceptionTest.otherLogicErrorsMapToValueError]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PyExceptionTest.otherLogicErrorsMapToValueError]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/PyException.cpp:83]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PyExceptionTest.badAllocMapsToMemoryError]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=PyExceptionTest.badAllocMapsToMemoryError]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PyExceptionTest.badAllocMapsToMemoryError]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/PyException.cpp:93]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PyExceptionTest.nonExceptionTypeMapsToRuntimError]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=PyExceptionTest.nonExceptionTypeMapsToRuntimError]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PyExceptionTest.nonExceptionTypeMapsToRuntimError]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/PyException.cpp:103]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantity.TestValid]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantity.TestValid]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantity.TestValid]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:14]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantity.TestParse]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantity.TestParse]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantity.TestParse]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:24]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantity.TestLocalizedUserInput]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantity.TestLocalizedUserInput]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantity.TestLocalizedUserInput]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:32]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantity.TestLocalizedUserInputPreservesComments]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantity.TestLocalizedUserInputPreservesComments]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantity.TestLocalizedUserInputPreservesComments]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:42]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantity.TestNoDim]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantity.TestNoDim]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantity.TestNoDim]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:59]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantity.TestPowEQ1]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantity.TestPowEQ1]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantity.TestPowEQ1]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:67]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantity.TestPowEQ0]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantity.TestPowEQ0]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantity.TestPowEQ0]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:74]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantity.TestPowGT1]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantity.TestPowGT1]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantity.TestPowGT1]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:80]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantity.TestPowLT1]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantity.TestPowLT1]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantity.TestPowLT1]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:88]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantity.TestPow3DIV2]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantity.TestPow3DIV2]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantity.TestPow3DIV2]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:97]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantity.TestString]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantity.TestString]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantity.TestString]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:106]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantity.TestCopy]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantity.TestCopy]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantity.TestCopy]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:128]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantity.TestEqual]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantity.TestEqual]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantity.TestEqual]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:135]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantity.TestNotEqual]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantity.TestNotEqual]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantity.TestNotEqual]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:144]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantity.TestLessOrGreater]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantity.TestLessOrGreater]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantity.TestLessOrGreater]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:155]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantity.TestAdd]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantity.TestAdd]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantity.TestAdd]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:172]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantity.TestSub]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantity.TestSub]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantity.TestSub]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:182]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantity.TestNeg]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantity.TestNeg]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantity.TestNeg]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:192]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantity.TestMult]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantity.TestMult]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantity.TestMult]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:198]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantity.TestDiv]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantity.TestDiv]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantity.TestDiv]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:206]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantity.TestPow]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantity.TestPow]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantity.TestPow]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:214]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantityFormat.NumberOptionsAreBaseOwnedBitmask]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantityFormat.NumberOptionsAreBaseOwnedBitmask]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantityFormat.NumberOptionsAreBaseOwnedBitmask]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:116]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantityLoc.psi_parse_spaced]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantityLoc.psi_parse_spaced]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantityLoc.psi_parse_spaced]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:239]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantityLoc.psi_parse_no_space]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantityLoc.psi_parse_no_space]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantityLoc.psi_parse_no_space]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:245]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantityLoc.psi_parse_user_str]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantityLoc.psi_parse_user_str]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantityLoc.psi_parse_user_str]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:251]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantityLoc.psi_parse_safe_user_str]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantityLoc.psi_parse_safe_user_str]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantityLoc.psi_parse_safe_user_str]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:261]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantityLoc.psi_parse_unit_type]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantityLoc.psi_parse_unit_type]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantityLoc.psi_parse_unit_type]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:271]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantityLoc.psi_to_Pa]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantityLoc.psi_to_Pa]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantityLoc.psi_to_Pa]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:277]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantityLoc.psi_to_KPa]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantityLoc.psi_to_KPa]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantityLoc.psi_to_KPa]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:285]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantityLoc.psi_to_MPa]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantityLoc.psi_to_MPa]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantityLoc.psi_to_MPa]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:293]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantityLoc.voltage_unit]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantityLoc.voltage_unit]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantityLoc.voltage_unit]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:301]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantityLoc.voltage_val]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantityLoc.voltage_val]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantityLoc.voltage_val]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:308]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseQuantityLoc.voltage_val_smaller]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseQuantityLoc.voltage_val_smaller]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseQuantityLoc.voltage_val_smaller]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Quantity.cpp:315]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ReaderTest.beginCharStreamNormal]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ReaderTest.beginCharStreamNormal]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ReaderTest.beginCharStreamNormal]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Reader.cpp:95]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ReaderTest.beginCharStreamOpenClose]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ReaderTest.beginCharStreamOpenClose]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ReaderTest.beginCharStreamOpenClose]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Reader.cpp:109]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ReaderTest.beginCharStreamAlreadyBegun]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ReaderTest.beginCharStreamAlreadyBegun]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ReaderTest.beginCharStreamAlreadyBegun]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Reader.cpp:123]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ReaderTest.charStreamGood]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ReaderTest.charStreamGood]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ReaderTest.charStreamGood]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Reader.cpp:135]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ReaderTest.charStreamBad]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ReaderTest.charStreamBad]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ReaderTest.charStreamBad]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Reader.cpp:150]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ReaderTest.endCharStreamGood]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ReaderTest.endCharStreamGood]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ReaderTest.endCharStreamGood]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Reader.cpp:161]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ReaderTest.endCharStreamBad]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ReaderTest.endCharStreamBad]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ReaderTest.endCharStreamBad]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Reader.cpp:173]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ReaderTest.readDataSmallerThanBuffer]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ReaderTest.readDataSmallerThanBuffer]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ReaderTest.readDataSmallerThanBuffer]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Reader.cpp:185]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ReaderTest.readDataLargerThanBuffer]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ReaderTest.readDataLargerThanBuffer]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ReaderTest.readDataLargerThanBuffer]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Reader.cpp:204]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ReaderTest.readDataLargerThanBufferSecondRead]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ReaderTest.readDataLargerThanBufferSecondRead]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ReaderTest.readDataLargerThanBufferSecondRead]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Reader.cpp:225]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ReaderTest.readDataNotStarted]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ReaderTest.readDataNotStarted]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ReaderTest.readDataNotStarted]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Reader.cpp:247]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ReaderTest.readNextStartElement]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ReaderTest.readNextStartElement]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ReaderTest.readNextStartElement]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Reader.cpp:264]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ReaderTest.readNextStartEndElement]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ReaderTest.readNextStartEndElement]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ReaderTest.readNextStartEndElement]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Reader.cpp:296]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ReaderTest.charStreamBase64Encoded]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ReaderTest.charStreamBase64Encoded]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ReaderTest.charStreamBase64Encoded]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Reader.cpp:394]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ReaderTest.validDefaults]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ReaderTest.validDefaults]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ReaderTest.validDefaults]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Reader.cpp:413]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ReaderTest.AsciiUnchanged]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ReaderTest.AsciiUnchanged]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ReaderTest.AsciiUnchanged]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Reader.cpp:463]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ReaderTest.AllowedWhitespacePreserved]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ReaderTest.AllowedWhitespacePreserved]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ReaderTest.AllowedWhitespacePreserved]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Reader.cpp:470]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ReaderTest.DisallowedC0ControlsBecomeUnderscore]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ReaderTest.DisallowedC0ControlsBecomeUnderscore]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ReaderTest.DisallowedC0ControlsBecomeUnderscore]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Reader.cpp:477]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ReaderTest.DelAndC1ControlsBecomeUnderscore]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ReaderTest.DelAndC1ControlsBecomeUnderscore]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ReaderTest.DelAndC1ControlsBecomeUnderscore]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Reader.cpp:489]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ReaderTest.BmpBoundaryAndNoncharacters]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ReaderTest.BmpBoundaryAndNoncharacters]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ReaderTest.BmpBoundaryAndNoncharacters]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Reader.cpp:539]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ReaderTest.NonBmpEmojiPreserved]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ReaderTest.NonBmpEmojiPreserved]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ReaderTest.NonBmpEmojiPreserved]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Reader.cpp:557]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ReaderTest.ZwjSequencePreserved]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ReaderTest.ZwjSequencePreserved]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ReaderTest.ZwjSequencePreserved]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Reader.cpp:566]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ReaderTest.CombiningMarksPreserved]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ReaderTest.CombiningMarksPreserved]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ReaderTest.CombiningMarksPreserved]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Reader.cpp:574]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ReaderTest.PrivateUseAreaPreserved]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ReaderTest.PrivateUseAreaPreserved]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ReaderTest.PrivateUseAreaPreserved]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Reader.cpp:581]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ReaderTest.MixedContentSanitization]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ReaderTest.MixedContentSanitization]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ReaderTest.MixedContentSanitization]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Reader.cpp:590]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ReaderTest.validateXmlString]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ReaderTest.validateXmlString]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ReaderTest.validateXmlString]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Reader.cpp:610]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Rotation.TestNonUniformScaleLeft]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Rotation.TestNonUniformScaleLeft]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Rotation.TestNonUniformScaleLeft]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Rotation.cpp:8]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Rotation.TestNonUniformScaleRight]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Rotation.TestNonUniformScaleRight]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Rotation.TestNonUniformScaleRight]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Rotation.cpp:26]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Rotation.TestUniformScaleGT1]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Rotation.TestUniformScaleGT1]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Rotation.TestUniformScaleGT1]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Rotation.cpp:43]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Rotation.TestUniformScaleLT1]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Rotation.TestUniformScaleLT1]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Rotation.TestUniformScaleLT1]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Rotation.cpp:60]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Rotation.TestRotationDecompose]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Rotation.TestRotationDecompose]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Rotation.TestRotationDecompose]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Rotation.cpp:70]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.meter_decimal_1_mm_precision_6]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.meter_decimal_1_mm_precision_6]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.meter_decimal_1_mm_precision_6]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:108]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.meter_decimal_15_mm2_precision_6]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.meter_decimal_15_mm2_precision_6]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.meter_decimal_15_mm2_precision_6]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:116]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.meter_decimal_123456000_mm3_precision_6]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.meter_decimal_123456000_mm3_precision_6]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.meter_decimal_123456000_mm3_precision_6]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:124]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.meter_decimal_123456000_W_precision_6]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.meter_decimal_123456000_W_precision_6]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.meter_decimal_123456000_W_precision_6]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:132]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.meter_decimal_123456000_V_precision_6]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.meter_decimal_123456000_V_precision_6]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.meter_decimal_123456000_V_precision_6]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:140]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.meter_decimal_123456000_W_m2_precision_6]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.meter_decimal_123456000_W_m2_precision_6]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.meter_decimal_123456000_W_m2_precision_6]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:149]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.meter_decimal_123456000_m_s_precision_6]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.meter_decimal_123456000_m_s_precision_6]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.meter_decimal_123456000_m_s_precision_6]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:157]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.mks_1_mm_precision_6]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.mks_1_mm_precision_6]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.mks_1_mm_precision_6]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:165]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.mks_15_mm2_precision_6]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.mks_15_mm2_precision_6]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.mks_15_mm2_precision_6]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:173]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.mks_123456000_mm3_precision_6]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.mks_123456000_mm3_precision_6]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.mks_123456000_mm3_precision_6]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:181]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.mks_123456000_W_precision_6]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.mks_123456000_W_precision_6]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.mks_123456000_W_precision_6]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:189]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.mks_123456000_V_precision_6]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.mks_123456000_V_precision_6]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.mks_123456000_V_precision_6]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:197]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.mks_123456000_W_m2_precision_6]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.mks_123456000_W_m2_precision_6]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.mks_123456000_W_m2_precision_6]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:205]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.mks_123456000_m_s_precision_6]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.mks_123456000_m_s_precision_6]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.mks_123456000_m_s_precision_6]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:213]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.internal_1_mm_precision_0]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.internal_1_mm_precision_0]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.internal_1_mm_precision_0]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:221]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.schema_descriptions_use_translation_handler]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.schema_descriptions_use_translation_handler]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.schema_descriptions_use_translation_handler]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:229]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.internal_100_mm_precision_0]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.internal_100_mm_precision_0]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.internal_100_mm_precision_0]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:242]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.internal_100_mm_precision_1]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.internal_100_mm_precision_1]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.internal_100_mm_precision_1]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:250]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.internal_20000_mm_precision_2]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.internal_20000_mm_precision_2]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.internal_20000_mm_precision_2]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:258]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.internal_20nA_precision_0]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.internal_20nA_precision_0]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.internal_20nA_precision_0]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:266]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.internal_100uA_precision_0]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.internal_100uA_precision_0]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.internal_100uA_precision_0]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:274]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.internal_20nW_precision_0]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.internal_20nW_precision_0]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.internal_20nW_precision_0]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:283]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.internal_20uW_precision_0]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.internal_20uW_precision_0]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.internal_20uW_precision_0]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:291]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.internal_1mol_p_l_precision_1]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.internal_1mol_p_l_precision_1]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.internal_1mol_p_l_precision_1]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:299]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_decimal_1_mm_precision_0]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_decimal_1_mm_precision_0]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_decimal_1_mm_precision_0]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:307]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_decimal_10_mm_precision_0]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_decimal_10_mm_precision_0]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_decimal_10_mm_precision_0]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:315]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_decimal_20_mm_precision_0]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_decimal_20_mm_precision_0]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_decimal_20_mm_precision_0]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:324]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_1_mm_precision_0]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_1_mm_precision_0]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_1_mm_precision_0]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:332]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_0_mm_precision_0]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_0_mm_precision_0]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_0_mm_precision_0]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:340]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_0_mm_precision_1]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_0_mm_precision_1]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_0_mm_precision_1]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:348]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_decimal_0_mm_precision_0]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_decimal_0_mm_precision_0]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_decimal_0_mm_precision_0]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:356]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_decimal_0_mm_precision_1]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_decimal_0_mm_precision_1]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_decimal_0_mm_precision_1]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:364]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_civil_0_mm_precision_0]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_civil_0_mm_precision_0]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_civil_0_mm_precision_0]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:372]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_civil_0_mm_precision_1]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_civil_0_mm_precision_1]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_civil_0_mm_precision_1]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:380]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_building_0_mm_precision_0]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_building_0_mm_precision_0]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_building_0_mm_precision_0]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:388]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_building_0_mm_precision_1]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_building_0_mm_precision_1]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_building_0_mm_precision_1]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:396]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_decimal_1_mm_precision_1]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_decimal_1_mm_precision_1]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_decimal_1_mm_precision_1]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:404]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_decimal_100_mm_precision_0]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_decimal_100_mm_precision_0]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_decimal_100_mm_precision_0]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:412]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_decimal_100_mm_precision_1]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_decimal_100_mm_precision_1]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_decimal_100_mm_precision_1]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:420]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_decimal_100_mm_precision_2]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_decimal_100_mm_precision_2]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_decimal_100_mm_precision_2]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:428]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_decimal_1_mm_precision_2]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_decimal_1_mm_precision_2]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_decimal_1_mm_precision_2]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:436]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_decimal_1_mm_precision_4]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_decimal_1_mm_precision_4]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_decimal_1_mm_precision_4]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:444]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_safe_user_str_same]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_safe_user_str_same]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_safe_user_str_same]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:452]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_safe_user_str_more]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_safe_user_str_more]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_safe_user_str_more]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:461]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_safe_user_str_less]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_safe_user_str_less]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_safe_user_str_less]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:470]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_safe_user_str_one_inch]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_safe_user_str_one_inch]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_safe_user_str_one_inch]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:479]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_building_special_function_length_inch]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_building_special_function_length_inch]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_building_special_function_length_inch]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:488]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_building_special_function_length_foot]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_building_special_function_length_foot]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_building_special_function_length_foot]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:497]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_building_special_function_zero_length]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_building_special_function_zero_length]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_building_special_function_zero_length]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:506]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_building_special_function_length_negative_fraction_only]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_building_special_function_length_negative_fraction_only]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_building_special_function_length_negative_fraction_only]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:514]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_building_special_function_negative_inches_and_fraction]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_building_special_function_negative_inches_and_fraction]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_building_special_function_negative_inches_and_fraction]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:523]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_building_special_function_high_precision_rounding]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_building_special_function_high_precision_rounding]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_building_special_function_high_precision_rounding]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:532]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_building_special_function_length]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_building_special_function_length]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_building_special_function_length]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:541]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_building_special_function_length_neg]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_building_special_function_length_neg]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_building_special_function_length_neg]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:551]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_civil_special_function_angle_degrees]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_civil_special_function_angle_degrees]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_civil_special_function_angle_degrees]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:560]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_civil_special_function_angle_minutes]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_civil_special_function_angle_minutes]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_civil_special_function_angle_minutes]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:569]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_civil_special_function_angle_seconds]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_civil_special_function_angle_seconds]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_civil_special_function_angle_seconds]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:578]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_civil_special_function_angle_no_degrees]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_civil_special_function_angle_no_degrees]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_civil_special_function_angle_no_degrees]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:587]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.unknown_schema_name_throws]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.unknown_schema_name_throws]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.unknown_schema_name_throws]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:596]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.round_trip_test]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.round_trip_test]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.round_trip_test]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:601]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.sweep_internal]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.sweep_internal]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.sweep_internal]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:765]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.sweep_mks]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.sweep_mks]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.sweep_mks]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:1062]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.mks_negative_values_use_magnitude_for_threshold_selection]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.mks_negative_values_use_magnitude_for_threshold_selection]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.mks_negative_values_use_magnitude_for_threshold_selection]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:1249]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.sweep_imperial]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.sweep_imperial]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.sweep_imperial]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:1267]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.sweep_imperial_decimal]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.sweep_imperial_decimal]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.sweep_imperial_decimal]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:1295]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.sweep_imperial_building]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.sweep_imperial_building]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.sweep_imperial_building]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:1309]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_building_density_uses_lb_ft3]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_building_density_uses_lb_ft3]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_building_density_uses_lb_ft3]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:1322]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_building_stress_uses_psi]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_building_stress_uses_psi]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_building_stress_uses_psi]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:1334]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_density_uses_lb_in3]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_density_uses_lb_in3]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_density_uses_lb_in3]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:1342]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.imperial_civil_density_uses_lb_ft3]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.imperial_civil_density_uses_lb_ft3]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.imperial_civil_density_uses_lb_ft3]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:1350]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.sweep_imperial_civil]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.sweep_imperial_civil]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.sweep_imperial_civil]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:1358]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.sweep_centimeter]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.sweep_centimeter]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.sweep_centimeter]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:1375]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.sweep_fem]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.sweep_fem]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.sweep_fem]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:1389]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.sweep_mmmin]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.sweep_mmmin]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.sweep_mmmin]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:1399]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SchemaTest.sweep_meter_decimal]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=SchemaTest.sweep_meter_decimal]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SchemaTest.sweep_meter_decimal]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/SchemaTests.cpp:1409]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ServiceProvider.provideEmptyImplementation]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ServiceProvider.provideEmptyImplementation]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ServiceProvider.provideEmptyImplementation]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/ServiceProvider.cpp:36]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ServiceProvider.provideEmptyImplementationList]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ServiceProvider.provideEmptyImplementationList]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ServiceProvider.provideEmptyImplementationList]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/ServiceProvider.cpp:48]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ServiceProvider.provideImplementation]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ServiceProvider.provideImplementation]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ServiceProvider.provideImplementation]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/ServiceProvider.cpp:60]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ServiceProvider.provideLatestImplementation]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ServiceProvider.provideLatestImplementation]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ServiceProvider.provideLatestImplementation]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/ServiceProvider.cpp:75]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ServiceProvider.provideAllImplementations]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ServiceProvider.provideAllImplementations]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ServiceProvider.provideAllImplementations]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/ServiceProvider.cpp:91]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TextOutputStreamTest.singleLineCharStar]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TextOutputStreamTest.singleLineCharStar]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TextOutputStreamTest.singleLineCharStar]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Stream.cpp:24]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TextOutputStreamTest.multiLineCharStar]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TextOutputStreamTest.multiLineCharStar]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TextOutputStreamTest.multiLineCharStar]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Stream.cpp:38]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TextOutputStreamTest.singleLineCharStarWithCarriageReturns]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TextOutputStreamTest.singleLineCharStarWithCarriageReturns]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TextOutputStreamTest.singleLineCharStarWithCarriageReturns]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Stream.cpp:52]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TextOutputStreamTest.multiLineCharStarWithCarriageReturnsAndNewlines]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TextOutputStreamTest.multiLineCharStarWithCarriageReturnsAndNewlines]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TextOutputStreamTest.multiLineCharStarWithCarriageReturnsAndNewlines]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Stream.cpp:67]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TextStreamIntegrationTest.OutputThenInputSimpleMultiLine]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TextStreamIntegrationTest.OutputThenInputSimpleMultiLine]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TextStreamIntegrationTest.OutputThenInputSimpleMultiLine]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Stream.cpp:94]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TextStreamIntegrationTest.OutputThenInputMultiLineWithCarriageReturns]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TextStreamIntegrationTest.OutputThenInputMultiLineWithCarriageReturns]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TextStreamIntegrationTest.OutputThenInputMultiLineWithCarriageReturns]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Stream.cpp:112]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringStreambufTest.OutputOverwritesAndSeeks]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=StringStreambufTest.OutputOverwritesAndSeeks]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringStreambufTest.OutputOverwritesAndSeeks]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Stream.cpp:136]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringStreambufTest.RoundTripBinaryData]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=StringStreambufTest.RoundTripBinaryData]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringStreambufTest.RoundTripBinaryData]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Stream.cpp:150]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BufferStreambuf.emptyBufferIn]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BufferStreambuf.emptyBufferIn]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BufferStreambuf.emptyBufferIn]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Stream.cpp:178]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BufferStreambuf.emptyBufferOut]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BufferStreambuf.emptyBufferOut]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BufferStreambuf.emptyBufferOut]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Stream.cpp:209]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BufferStreambuf.bufferIn]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BufferStreambuf.bufferIn]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BufferStreambuf.bufferIn]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Stream.cpp:235]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BufferStreambuf.bufferOut]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BufferStreambuf.bufferOut]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BufferStreambuf.bufferOut]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Stream.cpp:302]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringUtils.TestTrimmed]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=StringUtils.TestTrimmed]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringUtils.TestTrimmed]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/StringUtils.cpp:10]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringUtils.TestLowercaseAscii]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=StringUtils.TestLowercaseAscii]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringUtils.TestLowercaseAscii]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/StringUtils.cpp:18]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringUtils.TestParseLong]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=StringUtils.TestParseLong]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringUtils.TestParseLong]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/StringUtils.cpp:25]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringUtils.TestParseDouble]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=StringUtils.TestParseDouble]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringUtils.TestParseDouble]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/StringUtils.cpp:39]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringUtils.TestParseBool]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=StringUtils.TestParseBool]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringUtils.TestParseBool]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/StringUtils.cpp:53]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringUtils.TestFormatDouble]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=StringUtils.TestFormatDouble]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringUtils.TestFormatDouble]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/StringUtils.cpp:70]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TimeInfo.TestDefault]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TimeInfo.TestDefault]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TimeInfo.TestDefault]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/TimeInfo.cpp:4]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TimeInfo.TestNull]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TimeInfo.TestNull]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TimeInfo.TestNull]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/TimeInfo.cpp:10]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TimeInfo.TestCompare]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TimeInfo.TestCompare]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TimeInfo.TestCompare]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/TimeInfo.cpp:16]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TimeInfo.TestDiffTime]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TimeInfo.TestDiffTime]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TimeInfo.TestDiffTime]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/TimeInfo.cpp:29]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Tools.TestIota]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Tools.TestIota]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Tools.TestIota]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Tools.cpp:9]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Tools.TestSignum]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Tools.TestSignum]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Tools.TestSignum]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Tools.cpp:18]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Tools.TestRadian]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Tools.TestRadian]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Tools.TestRadian]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Tools.cpp:29]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Tools.TestDegree]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Tools.TestDegree]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Tools.TestDegree]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Tools.cpp:37]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Tools.TestToggle]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Tools.TestToggle]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Tools.TestToggle]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Tools.cpp:45]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Tools.TestStateLocker]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Tools.TestStateLocker]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Tools.TestStateLocker]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Tools.cpp:55]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Tools.TestBitsetLocker]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Tools.TestBitsetLocker]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Tools.TestBitsetLocker]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Tools.cpp:70]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseToolsSuite.TestQuote]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseToolsSuite.TestQuote]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseToolsSuite.TestQuote]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Tools.cpp:91]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseToolsSuite.TestJoinList]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseToolsSuite.TestJoinList]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseToolsSuite.TestJoinList]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Tools.cpp:96]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseToolsSuite.TestEscapeQuotesFromString]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseToolsSuite.TestEscapeQuotesFromString]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseToolsSuite.TestEscapeQuotesFromString]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Tools.cpp:100]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseToolsSuite.TestEscapeEncodeString]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseToolsSuite.TestEscapeEncodeString]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseToolsSuite.TestEscapeEncodeString]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Tools.cpp:107]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseToolsSuite.TestEscapeEncodeFilename]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseToolsSuite.TestEscapeEncodeFilename]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseToolsSuite.TestEscapeEncodeFilename]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Tools.cpp:117]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseToolsSuite.TestCurrentDateTimeStringUtcIso]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseToolsSuite.TestCurrentDateTimeStringUtcIso]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseToolsSuite.TestCurrentDateTimeStringUtcIso]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Tools.cpp:125]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BaseToolsSuite.TestGetIdentifier]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=BaseToolsSuite.TestGetIdentifier]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BaseToolsSuite.TestGetIdentifier]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Tools.cpp:131]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Line2D.TestLength]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Line2D.TestLength]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Line2D.TestLength]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Tools2D.cpp:33]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Line2D.TestPoints]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Line2D.TestPoints]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Line2D.TestPoints]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Tools2D.cpp:39]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Line2D.TestFromPos]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Line2D.TestFromPos]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Line2D.TestFromPos]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Tools2D.cpp:46]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Line2D.TestContains]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Line2D.TestContains]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Line2D.TestContains]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Tools2D.cpp:52]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Polygon2D.TestDefault]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Polygon2D.TestDefault]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Polygon2D.TestDefault]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Tools2D.cpp:58]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Polygon2D.TestAdd]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Polygon2D.TestAdd]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Polygon2D.TestAdd]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Tools2D.cpp:64]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Polygon2D.TestRemove]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Polygon2D.TestRemove]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Polygon2D.TestRemove]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Tools2D.cpp:71]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Polygon2D.TestClear]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Polygon2D.TestClear]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Polygon2D.TestClear]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Tools2D.cpp:81]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Line3D.TestLength]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Line3D.TestLength]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Line3D.TestLength]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Tools3D.cpp:34]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Line3D.TestSqrLength]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Line3D.TestSqrLength]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Line3D.TestSqrLength]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Tools3D.cpp:40]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Line3D.TestPoints]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Line3D.TestPoints]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Line3D.TestPoints]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Tools3D.cpp:46]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Line3D.TestFromPos]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Line3D.TestFromPos]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Line3D.TestFromPos]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Tools3D.cpp:53]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Line3D.TestContains]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Line3D.TestContains]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Line3D.TestContains]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Tools3D.cpp:59]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Polygon3D.TestDefault]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Polygon3D.TestDefault]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Polygon3D.TestDefault]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Tools3D.cpp:65]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Polygon3D.TestAdd]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Polygon3D.TestAdd]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Polygon3D.TestAdd]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Tools3D.cpp:71]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Polygon3D.TestRemove]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Polygon3D.TestRemove]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Polygon3D.TestRemove]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Tools3D.cpp:78]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Polygon3D.TestClear]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Polygon3D.TestClear]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Polygon3D.TestClear]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Tools3D.cpp:88]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Translation.FallbackReturnsSource]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Translation.FallbackReturnsSource]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Translation.FallbackReturnsSource]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Translation.cpp:8]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Translation.TranslateHandlerOverrides]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Translation.TranslateHandlerOverrides]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Translation.TranslateHandlerOverrides]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Translation.cpp:14]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Translation.InstallRemoveHandlersDefaultToFalse]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Translation.InstallRemoveHandlersDefaultToFalse]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Translation.InstallRemoveHandlersDefaultToFalse]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Translation.cpp:30]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Translation.InstallRemoveHandlersCalled]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Translation.InstallRemoveHandlersCalled]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Translation.InstallRemoveHandlersCalled]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Translation.cpp:37]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TranslateModule.TranslateUsesHandlerOrFallback]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TranslateModule.TranslateUsesHandlerOrFallback]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TranslateModule.TranslateUsesHandlerOrFallback]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Translate.cpp:51]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TranslateModule.InstallAndRemoveUseHandlers]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TranslateModule.InstallAndRemoveUseHandlers]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TranslateModule.InstallAndRemoveUseHandlers]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Translate.cpp:82]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnlimitedUnsigned.Basics]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnlimitedUnsigned.Basics]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnlimitedUnsigned.Basics]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnlimitedUnsigned.cpp:25]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnlimitedUnsigned.ToString]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnlimitedUnsigned.ToString]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnlimitedUnsigned.ToString]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnlimitedUnsigned.cpp:32]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnlimitedUnsigned.TestSubtraction1]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnlimitedUnsigned.TestSubtraction1]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnlimitedUnsigned.TestSubtraction1]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnlimitedUnsigned.cpp:39]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnlimitedUnsigned.TestSubtraction2]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnlimitedUnsigned.TestSubtraction2]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnlimitedUnsigned.TestSubtraction2]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnlimitedUnsigned.cpp:48]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UniqueNameManager.NonconflictingBaseNameReturnsSameName]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UniqueNameManager.NonconflictingBaseNameReturnsSameName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UniqueNameManager.NonconflictingBaseNameReturnsSameName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UniqueNameManager.cpp:26]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UniqueNameManager.NonconflictingUniqueNameReturnsBaseName]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UniqueNameManager.NonconflictingUniqueNameReturnsBaseName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UniqueNameManager.NonconflictingUniqueNameReturnsBaseName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UniqueNameManager.cpp:33]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UniqueNameManager.ManyDigitsInModelNameIgnored]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UniqueNameManager.ManyDigitsInModelNameIgnored]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UniqueNameManager.ManyDigitsInModelNameIgnored]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UniqueNameManager.cpp:40]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UniqueNameManager.ConflictingBaseNameReturnsUniqueName]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UniqueNameManager.ConflictingBaseNameReturnsUniqueName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UniqueNameManager.ConflictingBaseNameReturnsUniqueName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UniqueNameManager.cpp:49]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UniqueNameManager.ConflictingUniqueNameReturnsNewUniqueName]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UniqueNameManager.ConflictingUniqueNameReturnsNewUniqueName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UniqueNameManager.ConflictingUniqueNameReturnsNewUniqueName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UniqueNameManager.cpp:58]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UniqueNameManager.VerifyUniqueDigitCount]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UniqueNameManager.VerifyUniqueDigitCount]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UniqueNameManager.VerifyUniqueDigitCount]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UniqueNameManager.cpp:68]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UniqueNameManager.UniqueNameLargerThanAnyName]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UniqueNameManager.UniqueNameLargerThanAnyName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UniqueNameManager.UniqueNameLargerThanAnyName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UniqueNameManager.cpp:77]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UniqueNameManager.Issue18504]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UniqueNameManager.Issue18504]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UniqueNameManager.Issue18504]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UniqueNameManager.cpp:86]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UniqueNameManager.UniqueNameWithManyDigits]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UniqueNameManager.UniqueNameWithManyDigits]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UniqueNameManager.UniqueNameWithManyDigits]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UniqueNameManager.cpp:110]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UniqueNameManager.UniqueNameWith9NDigits]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UniqueNameManager.UniqueNameWith9NDigits]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UniqueNameManager.UniqueNameWith9NDigits]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UniqueNameManager.cpp:117]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UniqueNameManager.NonAsciiNameIsHandled]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UniqueNameManager.NonAsciiNameIsHandled]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UniqueNameManager.NonAsciiNameIsHandled]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UniqueNameManager.cpp:128]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Unit.string_simple_numerator_no_denominator]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Unit.string_simple_numerator_no_denominator]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Unit.string_simple_numerator_no_denominator]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Unit.cpp:8]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Unit.string_complex_numerator_no_denominator]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Unit.string_complex_numerator_no_denominator]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Unit.string_complex_numerator_no_denominator]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Unit.cpp:13]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Unit.string_complex_single_denominator]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Unit.string_complex_single_denominator]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Unit.string_complex_single_denominator]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Unit.cpp:18]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Unit.string_no_numerator]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Unit.string_no_numerator]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Unit.string_no_numerator]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Unit.cpp:23]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Unit.string_complex_multi_denominator]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Unit.string_complex_multi_denominator]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Unit.string_complex_multi_denominator]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Unit.cpp:28]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Unit.type_string]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Unit.type_string]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Unit.type_string]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Unit.cpp:33]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Unit.TestEqual]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Unit.TestEqual]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Unit.TestEqual]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Unit.cpp:38]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Unit.TestNotEqual]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Unit.TestNotEqual]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Unit.TestNotEqual]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Unit.cpp:43]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Unit.multiply_One_is_One]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Unit.multiply_One_is_One]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Unit.multiply_One_is_One]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Unit.cpp:48]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Unit.TestMult]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Unit.TestMult]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Unit.TestMult]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Unit.cpp:53]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Unit.div]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Unit.div]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Unit.div]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Unit.cpp:59]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Unit.div_by_One_does_nothing]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Unit.div_by_One_does_nothing]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Unit.div_by_One_does_nothing]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Unit.cpp:64]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Unit.pow_0_is_One]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Unit.pow_0_is_One]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Unit.pow_0_is_One]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Unit.cpp:69]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Unit.pow_1_leaves_unit_unchanged]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Unit.pow_1_leaves_unit_unchanged]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Unit.pow_1_leaves_unit_unchanged]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Unit.cpp:74]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Unit.pow_2_is_squared]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Unit.pow_2_is_squared]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Unit.pow_2_is_squared]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Unit.cpp:79]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Unit.pow_3_is_cubed]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Unit.pow_3_is_cubed]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Unit.pow_3_is_cubed]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Unit.cpp:84]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Unit.pow_less_than_one]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Unit.pow_less_than_one]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Unit.pow_less_than_one]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Unit.cpp:89]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Unit.one_still_one_after_pow]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Unit.one_still_one_after_pow]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Unit.one_still_one_after_pow]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Unit.cpp:94]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Unit.square_root]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Unit.square_root]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Unit.square_root]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Unit.cpp:99]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Unit.cube_root]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Unit.cube_root]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Unit.cube_root]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Unit.cpp:104]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Unit.zero_root]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Unit.zero_root]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Unit.zero_root]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Unit.cpp:109]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Unit.one_root]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Unit.one_root]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Unit.one_root]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Unit.cpp:114]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Unit.TestPow3div2]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Unit.TestPow3div2]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Unit.TestPow3div2]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Unit.cpp:119]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Unit.overflow]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Unit.overflow]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Unit.overflow]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Unit.cpp:124]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Unit.underflow]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Unit.underflow]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Unit.underflow]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Unit.cpp:130]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Unit.representation_simple]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Unit.representation_simple]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Unit.representation_simple]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Unit.cpp:136]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Unit.representation_complex]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Unit.representation_complex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Unit.representation_complex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Unit.cpp:143]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Unit.representation_no_name]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Unit.representation_no_name]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Unit.representation_no_name]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Unit.cpp:150]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsApi_toUnicodeSuperscript.no_caret_unchanged]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsApi_toUnicodeSuperscript.no_caret_unchanged]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsApi_toUnicodeSuperscript.no_caret_unchanged]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsApi.cpp:6]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsApi_toUnicodeSuperscript.empty_string]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsApi_toUnicodeSuperscript.empty_string]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsApi_toUnicodeSuperscript.empty_string]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsApi.cpp:11]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsApi_toUnicodeSuperscript.digit_0]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsApi_toUnicodeSuperscript.digit_0]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsApi_toUnicodeSuperscript.digit_0]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsApi.cpp:16]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsApi_toUnicodeSuperscript.digit_1]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsApi_toUnicodeSuperscript.digit_1]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsApi_toUnicodeSuperscript.digit_1]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsApi.cpp:21]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsApi_toUnicodeSuperscript.digit_2]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsApi_toUnicodeSuperscript.digit_2]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsApi_toUnicodeSuperscript.digit_2]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsApi.cpp:26]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsApi_toUnicodeSuperscript.digit_3]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsApi_toUnicodeSuperscript.digit_3]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsApi_toUnicodeSuperscript.digit_3]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsApi.cpp:31]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsApi_toUnicodeSuperscript.digit_4]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsApi_toUnicodeSuperscript.digit_4]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsApi_toUnicodeSuperscript.digit_4]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsApi.cpp:36]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsApi_toUnicodeSuperscript.digit_5]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsApi_toUnicodeSuperscript.digit_5]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsApi_toUnicodeSuperscript.digit_5]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsApi.cpp:41]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsApi_toUnicodeSuperscript.digit_6]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsApi_toUnicodeSuperscript.digit_6]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsApi_toUnicodeSuperscript.digit_6]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsApi.cpp:46]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsApi_toUnicodeSuperscript.digit_7]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsApi_toUnicodeSuperscript.digit_7]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsApi_toUnicodeSuperscript.digit_7]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsApi.cpp:51]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsApi_toUnicodeSuperscript.digit_8]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsApi_toUnicodeSuperscript.digit_8]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsApi_toUnicodeSuperscript.digit_8]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsApi.cpp:56]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsApi_toUnicodeSuperscript.digit_9]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsApi_toUnicodeSuperscript.digit_9]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsApi_toUnicodeSuperscript.digit_9]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsApi.cpp:61]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsApi_toUnicodeSuperscript.negative_exponent_2]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsApi_toUnicodeSuperscript.negative_exponent_2]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsApi_toUnicodeSuperscript.negative_exponent_2]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsApi.cpp:66]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsApi_toUnicodeSuperscript.negative_exponent_3]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsApi_toUnicodeSuperscript.negative_exponent_3]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsApi_toUnicodeSuperscript.negative_exponent_3]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsApi.cpp:72]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsApi_toUnicodeSuperscript.area_unit_mm_squared]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsApi_toUnicodeSuperscript.area_unit_mm_squared]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsApi_toUnicodeSuperscript.area_unit_mm_squared]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsApi.cpp:78]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsApi_toUnicodeSuperscript.multiple_exponents_in_one_string]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsApi_toUnicodeSuperscript.multiple_exponents_in_one_string]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsApi_toUnicodeSuperscript.multiple_exponents_in_one_string]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsApi.cpp:83]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsApi_toUnicodeSuperscript.inverse_area_unit]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsApi_toUnicodeSuperscript.inverse_area_unit]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsApi_toUnicodeSuperscript.inverse_area_unit]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsApi.cpp:89]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsApi_toUnicodeSuperscript.complex_unit_with_negative_exponent]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsApi_toUnicodeSuperscript.complex_unit_with_negative_exponent]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsApi_toUnicodeSuperscript.complex_unit_with_negative_exponent]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsApi.cpp:95]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsApi_toUnicodeSuperscript.caret_at_end_of_string]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsApi_toUnicodeSuperscript.caret_at_end_of_string]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsApi_toUnicodeSuperscript.caret_at_end_of_string]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsApi.cpp:101]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsApi_toUnicodeSuperscript.caret_minus_at_end_of_string]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsApi_toUnicodeSuperscript.caret_minus_at_end_of_string]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsApi_toUnicodeSuperscript.caret_minus_at_end_of_string]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsApi.cpp:106]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsApi_toUnicodeSuperscript.caret_followed_by_non_digit]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsApi_toUnicodeSuperscript.caret_followed_by_non_digit]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsApi_toUnicodeSuperscript.caret_followed_by_non_digit]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsApi.cpp:111]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsApi_toUnicodeSuperscript.double_caret_before_digit]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsApi_toUnicodeSuperscript.double_caret_before_digit]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsApi_toUnicodeSuperscript.double_caret_before_digit]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsApi.cpp:116]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsApi_toUnicodeSuperscript.multi_digit]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsApi_toUnicodeSuperscript.multi_digit]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsApi_toUnicodeSuperscript.multi_digit]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsApi.cpp:121]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsApi_toUnicodeSuperscript.negative_multi_digit]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsApi_toUnicodeSuperscript.negative_multi_digit]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsApi_toUnicodeSuperscript.negative_multi_digit]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsApi.cpp:126]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsApi_toUnicodeSuperscript.minus_inside_exponent]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsApi_toUnicodeSuperscript.minus_inside_exponent]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsApi_toUnicodeSuperscript.minus_inside_exponent]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsApi.cpp:131]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsApi_toUnicodeSuperscript.minus_inside_negative_exponent]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsApi_toUnicodeSuperscript.minus_inside_negative_exponent]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsApi_toUnicodeSuperscript.minus_inside_negative_exponent]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsApi.cpp:136]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsApi_toUnicodeSuperscript.minus_inside_multi_digit_exponent]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsApi_toUnicodeSuperscript.minus_inside_multi_digit_exponent]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsApi_toUnicodeSuperscript.minus_inside_multi_digit_exponent]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsApi.cpp:141]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Uuid.CreateUuidFormatAndBits]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Uuid.CreateUuidFormatAndBits]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Uuid.CreateUuidFormatAndBits]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Uuid.cpp:9]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Uuid.SetValueAcceptsBracesAndNormalizes]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Uuid.SetValueAcceptsBracesAndNormalizes]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Uuid.SetValueAcceptsBracesAndNormalizes]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Uuid.cpp:26]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Uuid.SetValueRejectsInvalidStrings]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Uuid.SetValueRejectsInvalidStrings]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Uuid.SetValueRejectsInvalidStrings]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Uuid.cpp:36]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Uuid.CreateUuidUniquenessSmoke]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Uuid.CreateUuidUniquenessSmoke]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Uuid.CreateUuidUniquenessSmoke]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Uuid.cpp:47]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsSchemaFormatTest.fixed_uses_precision_and_trailing_zeroes]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsSchemaFormatTest.fixed_uses_precision_and_trailing_zeroes]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsSchemaFormatTest.fixed_uses_precision_and_trailing_zeroes]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsSchemaFormat.cpp:51]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsSchemaFormatTest.scientific_uses_exponent_and_precision]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsSchemaFormatTest.scientific_uses_exponent_and_precision]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsSchemaFormatTest.scientific_uses_exponent_and_precision]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsSchemaFormat.cpp:61]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsSchemaFormatTest.default_matches_qt_general_scientific_thresholds]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsSchemaFormatTest.default_matches_qt_general_scientific_thresholds]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsSchemaFormatTest.default_matches_qt_general_scientific_thresholds]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsSchemaFormat.cpp:79]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsSchemaFormatTest.omit_group_separator_option_removes_grouping]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsSchemaFormatTest.omit_group_separator_option_removes_grouping]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsSchemaFormatTest.omit_group_separator_option_removes_grouping]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsSchemaFormat.cpp:91]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsSchemaFormatTest.formatting_state_overrides_icu_default]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsSchemaFormatTest.formatting_state_overrides_icu_default]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsSchemaFormatTest.formatting_state_overrides_icu_default]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsSchemaFormat.cpp:108]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsSchemaFormatTest.default_translation_uses_current_numeric_formatting_locale]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsSchemaFormatTest.default_translation_uses_current_numeric_formatting_locale]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsSchemaFormatTest.default_translation_uses_current_numeric_formatting_locale]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsSchemaFormat.cpp:118]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsSchemaFormatTest.effective_numeric_separators_override_locale_symbols]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsSchemaFormatTest.effective_numeric_separators_override_locale_symbols]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsSchemaFormatTest.effective_numeric_separators_override_locale_symbols]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsSchemaFormat.cpp:128]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UnitsSchemaFormatTest.explicit_formatting_state_does_not_use_published_snapshot]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=UnitsSchemaFormatTest.explicit_formatting_state_does_not_use_published_snapshot]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UnitsSchemaFormatTest.explicit_formatting_state_does_not_use_published_snapshot]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/UnitsSchemaFormat.cpp:146]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestDefault]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestDefault]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestDefault]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:5]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestDefault2]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestDefault2]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestDefault2]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:13]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestCopy]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestCopy]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestCopy]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:21]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestMove]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestMove]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestMove]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:30]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestNull]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestNull]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestNull]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:39]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestEqual]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestEqual]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestEqual]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:46]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestIndex]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestIndex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestIndex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:53]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestPlus]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestPlus]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestPlus]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:63]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestPlusAssign]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestPlusAssign]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestPlusAssign]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:71]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestMinus]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestMinus]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestMinus]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:80]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestMinusAssign]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestMinusAssign]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestMinusAssign]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:88]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestNegative]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestNegative]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestNegative]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:97]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestScale]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestScale]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestScale]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:105]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestScaleAssign]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestScaleAssign]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestScaleAssign]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:114]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestDivScale]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestDivScale]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestDivScale]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:123]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestDivScaleAssign]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestDivScaleAssign]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestDivScaleAssign]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:132]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestScaleXYZ]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestScaleXYZ]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestScaleXYZ]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:141]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestMoveXYZ]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestMoveXYZ]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestMoveXYZ]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:150]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestCopyAssign]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestCopyAssign]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestCopyAssign]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:159]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestMoveAssign]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestMoveAssign]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestMoveAssign]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:169]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestScalar]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestScalar]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestScalar]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:179]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestCross]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestCross]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestCross]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:189]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestCompare]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestCompare]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestCompare]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:203]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestNormalize]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestNormalize]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestNormalize]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:211]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestCSTransform]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestCSTransform]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestCSTransform]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:218]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestLineSegment]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestLineSegment]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestLineSegment]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:231]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestDistanceLineSegment]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestDistanceLineSegment]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestDistanceLineSegment]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:237]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestProjectToPlane]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestProjectToPlane]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestProjectToPlane]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:243]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestDistanceToPlane]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestDistanceToPlane]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestDistanceToPlane]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:253]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestAngle]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestAngle]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestAngle]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:260]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestIsNormal]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestIsNormal]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestIsNormal]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:268]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestIsNormalNullVector]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestIsNormalNullVector]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestIsNormalNullVector]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:276]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestIsNormalLongVectors]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestIsNormalLongVectors]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestIsNormalLongVectors]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:282]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestIsNormalShortVectors]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestIsNormalShortVectors]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestIsNormalShortVectors]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:288]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestIsParallel]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestIsParallel]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestIsParallel]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:294]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestIsParallelNullVector]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestIsParallelNullVector]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestIsParallelNullVector]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:303]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestIsParallelLongVectors]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestIsParallelLongVectors]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestIsParallelLongVectors]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:309]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestIsParallelShortVectors]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestIsParallelShortVectors]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestIsParallelShortVectors]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:315]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Vector.TestAngleOriented]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=Vector.TestAngleOriented]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Vector.TestAngleOriented]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Vector3D.cpp:321]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ViewProj.TestViewProjMatrix]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ViewProj.TestViewProjMatrix]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ViewProj.TestViewProjMatrix]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/ViewProj.cpp:5]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ViewProj.TestViewOrthoProjMatrix]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=ViewProj.TestViewOrthoProjMatrix]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ViewProj.TestViewOrthoProjMatrix]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/ViewProj.cpp:15]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[WriterTest.insertTextSimple]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=WriterTest.insertTextSimple]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[WriterTest.insertTextSimple]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Writer.cpp:21]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[WriterTest.insertTextNeedsEscape]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=WriterTest.insertTextNeedsEscape]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[WriterTest.insertTextNeedsEscape]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Writer.cpp:36]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[WriterTest.insertNonAsciiData]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=WriterTest.insertNonAsciiData]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[WriterTest.insertNonAsciiData]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Writer.cpp:50]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[WriterTest.beginCharStream]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=WriterTest.beginCharStream]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[WriterTest.beginCharStream]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Writer.cpp:63]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[WriterTest.beginCharStreamTwice]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=WriterTest.beginCharStreamTwice]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[WriterTest.beginCharStreamTwice]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Writer.cpp:72]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[WriterTest.endCharStream]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=WriterTest.endCharStream]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[WriterTest.endCharStream]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Writer.cpp:81]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[WriterTest.endCharStreamTwice]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=WriterTest.endCharStreamTwice]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[WriterTest.endCharStreamTwice]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Writer.cpp:93]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[WriterTest.charStream]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=WriterTest.charStream]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[WriterTest.charStream]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Writer.cpp:106]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[WriterTest.charStreamBase64Encoded]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=WriterTest.charStreamBase64Encoded]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[WriterTest.charStreamBase64Encoded]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/Writer.cpp:118]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[XMLParserTest.TestLoadValidDocument]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=XMLParserTest.TestLoadValidDocument]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[XMLParserTest.TestLoadValidDocument]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/XMLParser.cpp:35]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[XMLParserTest.TestLoadInvalidDocument]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=XMLParserTest.TestLoadInvalidDocument]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[XMLParserTest.TestLoadInvalidDocument]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/XMLParser.cpp:67]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[XMLParserTest.TestLoadEmptyDocument]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=XMLParserTest.TestLoadEmptyDocument]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[XMLParserTest.TestLoadEmptyDocument]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/XMLParser.cpp:74]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[XMLParserTest.TestLoadInvalidPath]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=XMLParserTest.TestLoadInvalidPath]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[XMLParserTest.TestLoadInvalidPath]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/XMLParser.cpp:81]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[XMLParserTest.TestCheckValidFile]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=XMLParserTest.TestCheckValidFile]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[XMLParserTest.TestCheckValidFile]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/XMLParser.cpp:89]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[XMLParserTest.TestCheckInvalidFile]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=XMLParserTest.TestCheckInvalidFile]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[XMLParserTest.TestCheckInvalidFile]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/XMLParser.cpp:98]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[XMLParserTest.TestWriteValidDocument]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=XMLParserTest.TestWriteValidDocument]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[XMLParserTest.TestWriteValidDocument]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/XMLParser.cpp:110]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TestXMLTools.EscapeXmlEmptyString]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TestXMLTools.EscapeXmlEmptyString]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestXMLTools.EscapeXmlEmptyString]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/XMLTools.cpp:11]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TestXMLTools.EscapeXmlNoChangesForSafeText]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TestXMLTools.EscapeXmlNoChangesForSafeText]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestXMLTools.EscapeXmlNoChangesForSafeText]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/XMLTools.cpp:16]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TestXMLTools.EscapeXmlEscapesAmpersand]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TestXMLTools.EscapeXmlEscapesAmpersand]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestXMLTools.EscapeXmlEscapesAmpersand]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/XMLTools.cpp:23]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TestXMLTools.EscapeXmlEscapesLessThanAndGreaterThan]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TestXMLTools.EscapeXmlEscapesLessThanAndGreaterThan]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestXMLTools.EscapeXmlEscapesLessThanAndGreaterThan]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/XMLTools.cpp:29]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TestXMLTools.EscapeXmlEscapesQuotes]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TestXMLTools.EscapeXmlEscapesQuotes]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestXMLTools.EscapeXmlEscapesQuotes]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/XMLTools.cpp:38]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TestXMLTools.EscapeXmlEscapesAllFiveInOneString]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TestXMLTools.EscapeXmlEscapesAllFiveInOneString]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestXMLTools.EscapeXmlEscapesAllFiveInOneString]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/XMLTools.cpp:46]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TestXMLTools.EscapeXmlDoesNotDoubleEscapeNewlyInsertedEntities]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TestXMLTools.EscapeXmlDoesNotDoubleEscapeNewlyInsertedEntities]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestXMLTools.EscapeXmlDoesNotDoubleEscapeNewlyInsertedEntities]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/XMLTools.cpp:52]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TestXMLTools.EscapeXmlComplexMixedContent]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TestXMLTools.EscapeXmlComplexMixedContent]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestXMLTools.EscapeXmlComplexMixedContent]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/XMLTools.cpp:62]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TestXMLTools.EscapeXmlMultipleAdjacentCharacters]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TestXMLTools.EscapeXmlMultipleAdjacentCharacters]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestXMLTools.EscapeXmlMultipleAdjacentCharacters]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/XMLTools.cpp:69]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TestXMLTools.EscapeXmlPreservesWhitespaceAndControlCommonInText]=]  /workspace/build/tests/Base_tests_run [==[--gtest_filter=TestXMLTools.EscapeXmlPreservesWhitespaceAndControlCommonInText]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestXMLTools.EscapeXmlPreservesWhitespaceAndControlCommonInText]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Base/XMLTools.cpp:76]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
set(Base_tests_run_TESTS [==[Axis.TestDefault]==] [==[Axis.TestCustom]==] [==[Axis.TestSetter]==] [==[Axis.TestAssign]==] [==[Axis.TestReverse]==] [==[Axis.TestReversed]==] [==[Axis.TestMove]==] [==[Axis.TestMult]==] [==[Base64.encode]==] [==[Base64.exactlyFourBytes]==] [==[Base64.twoEqualsSignsPadding]==] [==[Base64.oneEqualsSignPadding]==] [==[BitmaskTest.toUnderlyingType]==] [==[BoundBox.TestDefault]==] [==[BoundBox.TestVoid]==] [==[BoundBox.TestCopy]==] [==[BoundBox.TestAssign]==] [==[BoundBox.TestPoints]==] [==[BoundBox.TestDistance]==] [==[BoundBox.TestEmptySpan]==] [==[BoundBox.TestNonEmptySpan]==] [==[BoundBox.TestArray]==] [==[BoundBox.TestIntersect]==] [==[BoundBox.TestIntersect2D]==] [==[BoundBox.TestUnite]==] [==[BoundBox.TestAdd]==] [==[BoundBox.TestCenter]==] [==[BoundBox.TestMinimum]==] [==[BoundBox.TestMaximum]==] [==[BoundBox.TestDiagonalLength]==] [==[BoundBox.TestVolume]==] [==[BoundBox.TestDiagonalEnlarge]==] [==[BoundBox.TestDiagonalShrink]==] [==[BoundBox.TestDiagonalMove]==] [==[BoundBox.TestDiagonalScale]==] [==[Builder3D.openInventor]==] [==[TestColor.equal]==] [==[TestColor.round]==] [==[TestColor.packedValue]==] [==[TestColor.packedRGB]==] [==[TestColor.packedARGB]==] [==[TestColor.asPackedRGB]==] [==[TestColor.fromPackedRGB]==] [==[TestColor.asPackedRGBA]==] [==[TestColor.fromPackedRGBA]==] [==[TestColor.setValue]==] [==[TestColor.asValue]==] [==[TestColor.asHexString]==] [==[TestColor.fromHexString]==] [==[Console.DirectModeDeliversToObserver]==] [==[Console.QueuedModeFallsBackToDirectWithoutHandler]==] [==[Console.QueuedModeCallsPostEventHandlerWhenSet]==] [==[Console.RefreshCallsHandlerWhenEnabled]==] [==[CoordinateSystem.TestDefault]==] [==[CoordinateSystem.TestSetAxisFailure]==] [==[CoordinateSystem.TestSetAxis]==] [==[CoordinateSystem.TestSetXDir]==] [==[CoordinateSystem.TestSetYDir]==] [==[CoordinateSystem.TestSetZDir]==] [==[CoordinateSystem.TestTransformPlacement]==] [==[CoordinateSystem.TestMultTransformPlacement]==] [==[CoordinateSystem.TestTransformRotation]==] [==[CoordinateSystem.TestTransformPoint]==] [==[CoordinateSystem.TestSetPlacement]==] [==[CrashReporterTests.parseMissingFileThrows]==] [==[CrashReporterTests.parseFileTooSmall]==] [==[CrashReporterTests.parseFileTooLarge]==] [==[CrashReporterTests.parseGoodCrashReportLoads]==] [==[CrashReporterTests.parseDropsFaultAddressForCodeThatHasNone]==] [==[CrashReporterTests.parseNamesUnrecognizedFaultCodeWithItsHexValue]==] [==[CrashReporterTests.parseBadMagicNumber]==] [==[CrashReporterTests.parseBadVersionNumber]==] [==[CrashReporterTests.parseBadFileSize]==] [==[CrashReporterTests.parseBadStringTableOffset]==] [==[CrashReporterTests.parseBadFrameCount]==] [==[CrashReporterTests.parseBadFrameTableOffset]==] [==[CrashReporterTests.parseBadCRC]==] [==[CrashReporterTests.matchingHashAttemptsSymbolication]==] [==[CrashReporterTests.realCrashCapturesUsableFrames]==] [==[CrashReporterTests.DeliberateSegfaultRoundTrip]==] [==[CrashReporterTests.trimLeadingPlumbingFramesLeavesNoPlumbingAlone]==] [==[CrashReporterTests.trimLeadingPlumbingFramesLeavesEmptyVectorAlone]==] [==[CrashReporterTests.trimLeadingPlumbingFramesRemovesSingleExpectedSymbolFromTop]==] [==[CrashReporterTests.trimLeadingPlumbingFramesRemovesAnythingAboveFirstTrampoline]==] [==[CrashReporterTests.trimLeadingPlumbingFramesKeepsUnsymbolicatedTopFrame]==] [==[CrashReporterTests.trimLeadingPlumbingFramesKeepsAllWhenTrampolineIsDeepest]==] [==[CrashReporterTests.scanDetectsAndArchivesGoodReport]==] [==[CrashReporterTests.scanDetectsAndRenamesBadReport]==] [==[CrashReporterTests.scanCorrectlyHandlesMixOfGoodAndBadReports]==] [==[CrashReporterTests.scanReportsIncompleteFiles]==] [==[CrashReporterTests.clearRemovesEverything]==] [==[CrashReporterTests.clearBeforeScanDoesNothing]==] [==[CrashReporterTests.scanSetsOSVersionWhenPresent]==] [==[CrashReporterTests.scanDoesNotSetOSVersionWhenNotPresent]==] [==[CrashReporterTests.retentionKeepsAllWhenUnderCountAndYoung]==] [==[CrashReporterTests.retentionDeletesOldestBeyondCount]==] [==[CrashReporterTests.retentionKeepsYoungBeyondCount]==] [==[CrashReporterTests.retentionKeepsOldWithinCount]==] [==[CrashReporterTests.retentionDeletesOnlyOldAndBeyondCount]==] [==[CrashReporterTests.retentionDeletesCompanionDump]==] [==[CrashReporterTests.faultAddressIsMeaningfulReturnsFalseForCodeWithoutAddress]==] [==[CrashReporterTests.faultAddressIsMeaningfulReturnsTrueForCodeWithAddress]==] [==[CrashReporterTests.describeFaultCodeGivesValidResultForValidCode]==] [==[CrashReporterTests.describeFaultCodeGivesNulloptForBadCode]==] [==[DualNumber.TestDefault]==] [==[DualNumber.TestNonDefault]==] [==[DualNumber.TestNegate]==] [==[DualNumber.TestPlus]==] [==[DualNumber.TestMinus]==] [==[DualNumber.TestMultiply]==] [==[DualNumber.TestDivide]==] [==[DualNumber.TestPow]==] [==[DualQuaternion.TestDefault]==] [==[DualQuaternion.TestFromDouble]==] [==[DualQuaternion.TestFromDoubles]==] [==[DualQuaternion.TestFromDual]==] [==[DualQuaternion.TestIdentity]==] [==[DualQuaternion.TestReal]==] [==[DualQuaternion.TestDual]==] [==[DualQuaternion.TestConjugate]==] [==[DualQuaternion.TestVec]==] [==[DualQuaternion.TestLength]==] [==[DualQuaternion.TestTheta]==] [==[DualQuaternion.TestDot]==] [==[DualQuaternion.TestNegate]==] [==[DualQuaternion.TestPlus]==] [==[DualQuaternion.TestMinus]==] [==[DualQuaternion.TestMultiplyQuat]==] [==[DualQuaternion.TestMultiplyNumber]==] [==[DualQuaternion.TestMultiplyScalar]==] [==[DualQuaternion.TestPow]==] [==[FileException.TestWhatCombinesUntranslatedMessageAndPath]==] [==[FileException.TestTranslatedMessageFallsBackToSourceAndKeepsPath]==] [==[FileException.TestMessagesMatchTheTranslationKeys]==] [==[FileLockTest.TryLockZeroSucceedsWhenAvailable]==] [==[FileInfoTest.TestDirectoryPath]==] [==[FileInfoTest.TestExistsDirectory]==] [==[FileInfoTest.TestCreateDirectory]==] [==[FileInfoTest.TestDirectoryContent]==] [==[FileInfoTest.TestCheckPermission]==] [==[FileInfoTest.TestCheckNoPermission]==] [==[FileInfoTest.TestSetPermission]==] [==[FileInfoTest.TestCheckFile]==] [==[FileInfoTest.TestCheckDirectory]==] [==[FileInfoTest.TestSize]==] [==[FileInfoTest.TestLastModified]==] [==[FileInfoTest.TestDeleteFile]==] [==[FileInfoTest.TestRenameFile]==] [==[FileInfoTest.TestCopyFile]==] [==[FileInfoPathConversionTest.RoundTripAsciiPath]==] [==[FileInfoPathConversionTest.RoundTripNonAsciiPath]==] [==[FileInfoPathConversionTest.RoundTripChineseCharacters]==] [==[FileInfoPathConversionTest.RoundTripAccentedCharacters]==] [==[FileInfoPathConversionTest.RoundTripEmptyString]==] [==[FileInfoPathConversionTest.PathToStringPreservesUtf8]==] [==[FileInfoPathConversionTest.StringToPathProducesValidPath]==] [==[FileInfoSafeArchiveEntryPathTest.AcceptsNamesWrittenByFreeCAD]==] [==[FileInfoSafeArchiveEntryPathTest.RejectsParentDirectoryTraversal]==] [==[FileInfoSafeArchiveEntryPathTest.LeadingDoubleSeparatorDoesNotEatAComponent]==] [==[FileInfoSafeArchiveEntryPathTest.RejectsBackslashTraversal]==] [==[FileInfoSafeArchiveEntryPathTest.RejectsColonNames]==] [==[FileInfoSafeArchiveEntryPathTest.RejectsNamesThatNormalizeToNothing]==] [==[FileInfoSafeArchiveEntryPathTest.NormalizesRedundantComponents]==] [==[FileInfoSafeArchiveEntryPathTest.ContainedDotsAreAllowed]==] [==[FileInfoSafeArchiveEntryPathTest.HostileNamesCannotEscapeWhenJoined]==] [==[StdInputStream.SanitizesNullAndInvalidUtf8]==] [==[Reference.TestNull]==] [==[Reference.TestConstructor]==] [==[Reference.TestCopy]==] [==[Reference.TestAssignRaw]==] [==[Reference.TestAssignRef]==] [==[Reference.TestRefHandle]==] [==[Matrix.TestShearing]==] [==[Matrix.TestMultLeftRight]==] [==[Matrix.TestNoScale]==] [==[Matrix.TestUniformScalePlusTwo]==] [==[Matrix.TestUniformScaleRight]==] [==[Matrix.TestNonUniformScaleRight]==] [==[Matrix.TestUniformScaleMinusOne]==] [==[Matrix.TestUniformScaleMinusTwo]==] [==[Matrix.TestNonUniformScaleLeftOne]==] [==[Matrix.TestNonUniformScaleLeftTwo]==] [==[Matrix.TestDiagonal]==] [==[Matrix.TestColRow]==] [==[Matrix.TestColRowMisc]==] [==[Matrix.TestUnity]==] [==[Matrix.TestNull]==] [==[Matrix.TestMultVec]==] [==[Matrix.TestMult]==] [==[Matrix.TestMultAssign]==] [==[Matrix.TestAdd]==] [==[Matrix.TestAddAssign]==] [==[Matrix.TestSub]==] [==[Matrix.TestSubAssign]==] [==[Matrix.TestHatOperator]==] [==[Matrix.TestHatOperatorFloat]==] [==[Matrix.TestDyadic]==] [==[Matrix.TestDyadicFloat]==] [==[Matrix.TestDecomposeScale]==] [==[Matrix.TestDecomposeRotation]==] [==[Matrix.TestDecomposeMove]==] [==[Matrix.TestDecomposeMoveFloat]==] [==[Matrix.TestDecompose]==] [==[Matrix.TestRotLine]==] [==[Matrix.TestRotAxisFormula]==] [==[Matrix.TestTransform]==] [==[Matrix.TestTransformFloat]==] [==[Matrix.TestInverseOrthogonal]==] [==[Matrix.TestTranspose]==] [==[Matrix.TestTrace]==] [==[Matrix.TestSetAndGetMatrix]==] [==[Matrix.TestSetAndGetGLMatrix]==] [==[Matrix.TestToAndFromString]==] [==[NumericFormattingTest.createsLocaleSpecificSeparators]==] [==[NumericFormattingTest.formattedNativeDigitsRoundTripThroughScannerAndQuantity]==] [==[NumericFormattingTest.formatsValuesWithEffectiveSeparators]==] [==[NumericFormattingTest.cLocaleUsesDeterministicFallback]==] [==[NumericFormattingTest.normalizesIcuLocaleIdentifiers]==] [==[NumericFormattingTest.rejectsBogusIcuLocaleIdentifiers]==] [==[NumericFormattingTest.publishedStateIsACompleteSnapshot]==] [==[NumericFormattingTest.failedLocaleResolutionDoesNotPublishPartialState]==] [==[NumericInputTest.canonicalAndLocalizedDecimals]==] [==[NumericInputTest.westernGroupingAndScientificNotation]==] [==[NumericInputTest.indianGroupingUsesSecondarySize]==] [==[NumericInputTest.malformedGroupingIsInvalid]==] [==[NumericInputTest.multipleDecimalsAndIncompleteExponentsAreDiagnosed]==] [==[NumericInputTest.DotGroupingAndCanonicalDecimalHaveAnExplicitPolicy]==] [==[NumericInputTest.negativeAndLocalizedSigns]==] [==[NumericInputTest.InvalidUtf8IsNotALocalizedDigit]==] [==[NumericInputTest.positiveSignsAreAcceptedByCanonicalConversion]==] [==[NumericInputTest.OutOfRangeScientificNotationIsDiagnosed]==] [==[NumericInputTest.exactGroupingSymbolsAreRequired]==] [==[NumericInputTest.FunctionArgumentsTakePrecedenceOverCommaGrouping]==] [==[NumericInputTest.GroupingPlacementMutationsFollowLocalePattern]==] [==[OkLchTest.RoundTripBlack]==] [==[OkLchTest.RoundTripWhite]==] [==[OkLchTest.RoundTripRed]==] [==[OkLchTest.RoundTripGreen]==] [==[OkLchTest.RoundTripBlue]==] [==[OkLchTest.RoundTripMidGray]==] [==[OkLchTest.BlackHasZeroLightness]==] [==[OkLchTest.WhiteHasFullLightness]==] [==[OkLchTest.GrayHasLowChroma]==] [==[OkLchTest.GamutMappingClampsToValidSrgb]==] [==[OkLchTest.AlphaPreserved]==] [==[ParameterTest.TestValid]==] [==[ParameterTest.TestCreate]==] [==[ParameterTest.TestGroup]==] [==[ParameterTest.TestGroupName]==] [==[ParameterTest.TestEmptyGroupName]==] [==[ParameterTest.TestGroupNames]==] [==[ParameterTest.TestPath]==] [==[ParameterTest.TestBool]==] [==[ParameterTest.TestInt]==] [==[ParameterTest.TestUnsigned]==] [==[ParameterTest.TestFloat]==] [==[ParameterTest.TestString]==] [==[ParameterTest.TestColor]==] [==[ParameterTest.TestCopy]==] [==[ParameterTest.TestInsert]==] [==[ParameterTest.TestRevert]==] [==[ParameterTest.TestRemoveGroup]==] [==[ParameterTest.TestRenameGroup]==] [==[ParameterTest.TestSaveRestoreRef]==] [==[ParameterTest.TestSaveRestoreNoRef]==] [==[ParameterTest.TestClear]==] [==[ParameterTest.TestGetSetAttribute]==] [==[ParameterTest.TestGetParameterNames]==] [==[ParameterTest.TestGroupRef]==] [==[ParameterTest.TestGroupNoRef]==] [==[ParameterTest.TestObserverRef]==] [==[ParameterTest.TestNotifyAll]==] [==[ParameterTest.TestObserverNoRef]==] [==[ParameterTest.TestLockFile]==] [==[ParameterObserverTest.TestBool]==] [==[ParameterObserverTest.TestInt]==] [==[ParameterObserverTest.TestUnsigned]==] [==[ParameterObserverTest.TestFloat]==] [==[ParameterObserverTest.TestString]==] [==[ParameterObserverTest.TestHashKey]==] [==[ParameterObserverTest.TestUnknown]==] [==[ParameterObserverTest.TestWrongType]==] [==[Placement.TestDefault]==] [==[Placement.TestPosRot]==] [==[Placement.TestPosRotCnt]==] [==[Placement.TestMatrix]==] [==[Placement.TestIdentity]==] [==[Placement.TestInvert]==] [==[Placement.TestMove]==] [==[Placement.TestSame]==] [==[Placement.TestMultiply]==] [==[Placement.TestMultRight]==] [==[Placement.TestMultLeft]==] [==[Placement.TestMultVec]==] [==[Placement.TestDualQuat]==] [==[Placement.TestPow]==] [==[Placement.TestSlerp]==] [==[Placement.TestSclerp]==] [==[Persistence.ValidateXmlStringReplacesDisallowed]==] [==[Persistence.ValidateXmlStringPreservesValidNonBmp]==] [==[Persistence.ValidateXmlStringReplacesDiscouraged]==] [==[PyExceptionTest.goodCallDoesNotThrow]==] [==[PyExceptionTest.pythonExceptionsPropagate]==] [==[PyExceptionTest.outOfRangeMapsToIndexError]==] [==[PyExceptionTest.lengthErrorMapsToIndexError]==] [==[PyExceptionTest.otherLogicErrorsMapToValueError]==] [==[PyExceptionTest.badAllocMapsToMemoryError]==] [==[PyExceptionTest.nonExceptionTypeMapsToRuntimError]==] [==[BaseQuantity.TestValid]==] [==[BaseQuantity.TestParse]==] [==[BaseQuantity.TestLocalizedUserInput]==] [==[BaseQuantity.TestLocalizedUserInputPreservesComments]==] [==[BaseQuantity.TestNoDim]==] [==[BaseQuantity.TestPowEQ1]==] [==[BaseQuantity.TestPowEQ0]==] [==[BaseQuantity.TestPowGT1]==] [==[BaseQuantity.TestPowLT1]==] [==[BaseQuantity.TestPow3DIV2]==] [==[BaseQuantity.TestString]==] [==[BaseQuantity.TestCopy]==] [==[BaseQuantity.TestEqual]==] [==[BaseQuantity.TestNotEqual]==] [==[BaseQuantity.TestLessOrGreater]==] [==[BaseQuantity.TestAdd]==] [==[BaseQuantity.TestSub]==] [==[BaseQuantity.TestNeg]==] [==[BaseQuantity.TestMult]==] [==[BaseQuantity.TestDiv]==] [==[BaseQuantity.TestPow]==] [==[BaseQuantityFormat.NumberOptionsAreBaseOwnedBitmask]==] [==[BaseQuantityLoc.psi_parse_spaced]==] [==[BaseQuantityLoc.psi_parse_no_space]==] [==[BaseQuantityLoc.psi_parse_user_str]==] [==[BaseQuantityLoc.psi_parse_safe_user_str]==] [==[BaseQuantityLoc.psi_parse_unit_type]==] [==[BaseQuantityLoc.psi_to_Pa]==] [==[BaseQuantityLoc.psi_to_KPa]==] [==[BaseQuantityLoc.psi_to_MPa]==] [==[BaseQuantityLoc.voltage_unit]==] [==[BaseQuantityLoc.voltage_val]==] [==[BaseQuantityLoc.voltage_val_smaller]==] [==[ReaderTest.beginCharStreamNormal]==] [==[ReaderTest.beginCharStreamOpenClose]==] [==[ReaderTest.beginCharStreamAlreadyBegun]==] [==[ReaderTest.charStreamGood]==] [==[ReaderTest.charStreamBad]==] [==[ReaderTest.endCharStreamGood]==] [==[ReaderTest.endCharStreamBad]==] [==[ReaderTest.readDataSmallerThanBuffer]==] [==[ReaderTest.readDataLargerThanBuffer]==] [==[ReaderTest.readDataLargerThanBufferSecondRead]==] [==[ReaderTest.readDataNotStarted]==] [==[ReaderTest.readNextStartElement]==] [==[ReaderTest.readNextStartEndElement]==] [==[ReaderTest.charStreamBase64Encoded]==] [==[ReaderTest.validDefaults]==] [==[ReaderTest.AsciiUnchanged]==] [==[ReaderTest.AllowedWhitespacePreserved]==] [==[ReaderTest.DisallowedC0ControlsBecomeUnderscore]==] [==[ReaderTest.DelAndC1ControlsBecomeUnderscore]==] [==[ReaderTest.BmpBoundaryAndNoncharacters]==] [==[ReaderTest.NonBmpEmojiPreserved]==] [==[ReaderTest.ZwjSequencePreserved]==] [==[ReaderTest.CombiningMarksPreserved]==] [==[ReaderTest.PrivateUseAreaPreserved]==] [==[ReaderTest.MixedContentSanitization]==] [==[ReaderTest.validateXmlString]==] [==[Rotation.TestNonUniformScaleLeft]==] [==[Rotation.TestNonUniformScaleRight]==] [==[Rotation.TestUniformScaleGT1]==] [==[Rotation.TestUniformScaleLT1]==] [==[Rotation.TestRotationDecompose]==] [==[SchemaTest.meter_decimal_1_mm_precision_6]==] [==[SchemaTest.meter_decimal_15_mm2_precision_6]==] [==[SchemaTest.meter_decimal_123456000_mm3_precision_6]==] [==[SchemaTest.meter_decimal_123456000_W_precision_6]==] [==[SchemaTest.meter_decimal_123456000_V_precision_6]==] [==[SchemaTest.meter_decimal_123456000_W_m2_precision_6]==] [==[SchemaTest.meter_decimal_123456000_m_s_precision_6]==] [==[SchemaTest.mks_1_mm_precision_6]==] [==[SchemaTest.mks_15_mm2_precision_6]==] [==[SchemaTest.mks_123456000_mm3_precision_6]==] [==[SchemaTest.mks_123456000_W_precision_6]==] [==[SchemaTest.mks_123456000_V_precision_6]==] [==[SchemaTest.mks_123456000_W_m2_precision_6]==] [==[SchemaTest.mks_123456000_m_s_precision_6]==] [==[SchemaTest.internal_1_mm_precision_0]==] [==[SchemaTest.schema_descriptions_use_translation_handler]==] [==[SchemaTest.internal_100_mm_precision_0]==] [==[SchemaTest.internal_100_mm_precision_1]==] [==[SchemaTest.internal_20000_mm_precision_2]==] [==[SchemaTest.internal_20nA_precision_0]==] [==[SchemaTest.internal_100uA_precision_0]==] [==[SchemaTest.internal_20nW_precision_0]==] [==[SchemaTest.internal_20uW_precision_0]==] [==[SchemaTest.internal_1mol_p_l_precision_1]==] [==[SchemaTest.imperial_decimal_1_mm_precision_0]==] [==[SchemaTest.imperial_decimal_10_mm_precision_0]==] [==[SchemaTest.imperial_decimal_20_mm_precision_0]==] [==[SchemaTest.imperial_1_mm_precision_0]==] [==[SchemaTest.imperial_0_mm_precision_0]==] [==[SchemaTest.imperial_0_mm_precision_1]==] [==[SchemaTest.imperial_decimal_0_mm_precision_0]==] [==[SchemaTest.imperial_decimal_0_mm_precision_1]==] [==[SchemaTest.imperial_civil_0_mm_precision_0]==] [==[SchemaTest.imperial_civil_0_mm_precision_1]==] [==[SchemaTest.imperial_building_0_mm_precision_0]==] [==[SchemaTest.imperial_building_0_mm_precision_1]==] [==[SchemaTest.imperial_decimal_1_mm_precision_1]==] [==[SchemaTest.imperial_decimal_100_mm_precision_0]==] [==[SchemaTest.imperial_decimal_100_mm_precision_1]==] [==[SchemaTest.imperial_decimal_100_mm_precision_2]==] [==[SchemaTest.imperial_decimal_1_mm_precision_2]==] [==[SchemaTest.imperial_decimal_1_mm_precision_4]==] [==[SchemaTest.imperial_safe_user_str_same]==] [==[SchemaTest.imperial_safe_user_str_more]==] [==[SchemaTest.imperial_safe_user_str_less]==] [==[SchemaTest.imperial_safe_user_str_one_inch]==] [==[SchemaTest.imperial_building_special_function_length_inch]==] [==[SchemaTest.imperial_building_special_function_length_foot]==] [==[SchemaTest.imperial_building_special_function_zero_length]==] [==[SchemaTest.imperial_building_special_function_length_negative_fraction_only]==] [==[SchemaTest.imperial_building_special_function_negative_inches_and_fraction]==] [==[SchemaTest.imperial_building_special_function_high_precision_rounding]==] [==[SchemaTest.imperial_building_special_function_length]==] [==[SchemaTest.imperial_building_special_function_length_neg]==] [==[SchemaTest.imperial_civil_special_function_angle_degrees]==] [==[SchemaTest.imperial_civil_special_function_angle_minutes]==] [==[SchemaTest.imperial_civil_special_function_angle_seconds]==] [==[SchemaTest.imperial_civil_special_function_angle_no_degrees]==] [==[SchemaTest.unknown_schema_name_throws]==] [==[SchemaTest.round_trip_test]==] [==[SchemaTest.sweep_internal]==] [==[SchemaTest.sweep_mks]==] [==[SchemaTest.mks_negative_values_use_magnitude_for_threshold_selection]==] [==[SchemaTest.sweep_imperial]==] [==[SchemaTest.sweep_imperial_decimal]==] [==[SchemaTest.sweep_imperial_building]==] [==[SchemaTest.imperial_building_density_uses_lb_ft3]==] [==[SchemaTest.imperial_building_stress_uses_psi]==] [==[SchemaTest.imperial_density_uses_lb_in3]==] [==[SchemaTest.imperial_civil_density_uses_lb_ft3]==] [==[SchemaTest.sweep_imperial_civil]==] [==[SchemaTest.sweep_centimeter]==] [==[SchemaTest.sweep_fem]==] [==[SchemaTest.sweep_mmmin]==] [==[SchemaTest.sweep_meter_decimal]==] [==[ServiceProvider.provideEmptyImplementation]==] [==[ServiceProvider.provideEmptyImplementationList]==] [==[ServiceProvider.provideImplementation]==] [==[ServiceProvider.provideLatestImplementation]==] [==[ServiceProvider.provideAllImplementations]==] [==[TextOutputStreamTest.singleLineCharStar]==] [==[TextOutputStreamTest.multiLineCharStar]==] [==[TextOutputStreamTest.singleLineCharStarWithCarriageReturns]==] [==[TextOutputStreamTest.multiLineCharStarWithCarriageReturnsAndNewlines]==] [==[TextStreamIntegrationTest.OutputThenInputSimpleMultiLine]==] [==[TextStreamIntegrationTest.OutputThenInputMultiLineWithCarriageReturns]==] [==[StringStreambufTest.OutputOverwritesAndSeeks]==] [==[StringStreambufTest.RoundTripBinaryData]==] [==[BufferStreambuf.emptyBufferIn]==] [==[BufferStreambuf.emptyBufferOut]==] [==[BufferStreambuf.bufferIn]==] [==[BufferStreambuf.bufferOut]==] [==[StringUtils.TestTrimmed]==] [==[StringUtils.TestLowercaseAscii]==] [==[StringUtils.TestParseLong]==] [==[StringUtils.TestParseDouble]==] [==[StringUtils.TestParseBool]==] [==[StringUtils.TestFormatDouble]==] [==[TimeInfo.TestDefault]==] [==[TimeInfo.TestNull]==] [==[TimeInfo.TestCompare]==] [==[TimeInfo.TestDiffTime]==] [==[Tools.TestIota]==] [==[Tools.TestSignum]==] [==[Tools.TestRadian]==] [==[Tools.TestDegree]==] [==[Tools.TestToggle]==] [==[Tools.TestStateLocker]==] [==[Tools.TestBitsetLocker]==] [==[BaseToolsSuite.TestQuote]==] [==[BaseToolsSuite.TestJoinList]==] [==[BaseToolsSuite.TestEscapeQuotesFromString]==] [==[BaseToolsSuite.TestEscapeEncodeString]==] [==[BaseToolsSuite.TestEscapeEncodeFilename]==] [==[BaseToolsSuite.TestCurrentDateTimeStringUtcIso]==] [==[BaseToolsSuite.TestGetIdentifier]==] [==[Line2D.TestLength]==] [==[Line2D.TestPoints]==] [==[Line2D.TestFromPos]==] [==[Line2D.TestContains]==] [==[Polygon2D.TestDefault]==] [==[Polygon2D.TestAdd]==] [==[Polygon2D.TestRemove]==] [==[Polygon2D.TestClear]==] [==[Line3D.TestLength]==] [==[Line3D.TestSqrLength]==] [==[Line3D.TestPoints]==] [==[Line3D.TestFromPos]==] [==[Line3D.TestContains]==] [==[Polygon3D.TestDefault]==] [==[Polygon3D.TestAdd]==] [==[Polygon3D.TestRemove]==] [==[Polygon3D.TestClear]==] [==[Translation.FallbackReturnsSource]==] [==[Translation.TranslateHandlerOverrides]==] [==[Translation.InstallRemoveHandlersDefaultToFalse]==] [==[Translation.InstallRemoveHandlersCalled]==] [==[TranslateModule.TranslateUsesHandlerOrFallback]==] [==[TranslateModule.InstallAndRemoveUseHandlers]==] [==[UnlimitedUnsigned.Basics]==] [==[UnlimitedUnsigned.ToString]==] [==[UnlimitedUnsigned.TestSubtraction1]==] [==[UnlimitedUnsigned.TestSubtraction2]==] [==[UniqueNameManager.NonconflictingBaseNameReturnsSameName]==] [==[UniqueNameManager.NonconflictingUniqueNameReturnsBaseName]==] [==[UniqueNameManager.ManyDigitsInModelNameIgnored]==] [==[UniqueNameManager.ConflictingBaseNameReturnsUniqueName]==] [==[UniqueNameManager.ConflictingUniqueNameReturnsNewUniqueName]==] [==[UniqueNameManager.VerifyUniqueDigitCount]==] [==[UniqueNameManager.UniqueNameLargerThanAnyName]==] [==[UniqueNameManager.Issue18504]==] [==[UniqueNameManager.UniqueNameWithManyDigits]==] [==[UniqueNameManager.UniqueNameWith9NDigits]==] [==[UniqueNameManager.NonAsciiNameIsHandled]==] [==[Unit.string_simple_numerator_no_denominator]==] [==[Unit.string_complex_numerator_no_denominator]==] [==[Unit.string_complex_single_denominator]==] [==[Unit.string_no_numerator]==] [==[Unit.string_complex_multi_denominator]==] [==[Unit.type_string]==] [==[Unit.TestEqual]==] [==[Unit.TestNotEqual]==] [==[Unit.multiply_One_is_One]==] [==[Unit.TestMult]==] [==[Unit.div]==] [==[Unit.div_by_One_does_nothing]==] [==[Unit.pow_0_is_One]==] [==[Unit.pow_1_leaves_unit_unchanged]==] [==[Unit.pow_2_is_squared]==] [==[Unit.pow_3_is_cubed]==] [==[Unit.pow_less_than_one]==] [==[Unit.one_still_one_after_pow]==] [==[Unit.square_root]==] [==[Unit.cube_root]==] [==[Unit.zero_root]==] [==[Unit.one_root]==] [==[Unit.TestPow3div2]==] [==[Unit.overflow]==] [==[Unit.underflow]==] [==[Unit.representation_simple]==] [==[Unit.representation_complex]==] [==[Unit.representation_no_name]==] [==[UnitsApi_toUnicodeSuperscript.no_caret_unchanged]==] [==[UnitsApi_toUnicodeSuperscript.empty_string]==] [==[UnitsApi_toUnicodeSuperscript.digit_0]==] [==[UnitsApi_toUnicodeSuperscript.digit_1]==] [==[UnitsApi_toUnicodeSuperscript.digit_2]==] [==[UnitsApi_toUnicodeSuperscript.digit_3]==] [==[UnitsApi_toUnicodeSuperscript.digit_4]==] [==[UnitsApi_toUnicodeSuperscript.digit_5]==] [==[UnitsApi_toUnicodeSuperscript.digit_6]==] [==[UnitsApi_toUnicodeSuperscript.digit_7]==] [==[UnitsApi_toUnicodeSuperscript.digit_8]==] [==[UnitsApi_toUnicodeSuperscript.digit_9]==] [==[UnitsApi_toUnicodeSuperscript.negative_exponent_2]==] [==[UnitsApi_toUnicodeSuperscript.negative_exponent_3]==] [==[UnitsApi_toUnicodeSuperscript.area_unit_mm_squared]==] [==[UnitsApi_toUnicodeSuperscript.multiple_exponents_in_one_string]==] [==[UnitsApi_toUnicodeSuperscript.inverse_area_unit]==] [==[UnitsApi_toUnicodeSuperscript.complex_unit_with_negative_exponent]==] [==[UnitsApi_toUnicodeSuperscript.caret_at_end_of_string]==] [==[UnitsApi_toUnicodeSuperscript.caret_minus_at_end_of_string]==] [==[UnitsApi_toUnicodeSuperscript.caret_followed_by_non_digit]==] [==[UnitsApi_toUnicodeSuperscript.double_caret_before_digit]==] [==[UnitsApi_toUnicodeSuperscript.multi_digit]==] [==[UnitsApi_toUnicodeSuperscript.negative_multi_digit]==] [==[UnitsApi_toUnicodeSuperscript.minus_inside_exponent]==] [==[UnitsApi_toUnicodeSuperscript.minus_inside_negative_exponent]==] [==[UnitsApi_toUnicodeSuperscript.minus_inside_multi_digit_exponent]==] [==[Uuid.CreateUuidFormatAndBits]==] [==[Uuid.SetValueAcceptsBracesAndNormalizes]==] [==[Uuid.SetValueRejectsInvalidStrings]==] [==[Uuid.CreateUuidUniquenessSmoke]==] [==[UnitsSchemaFormatTest.fixed_uses_precision_and_trailing_zeroes]==] [==[UnitsSchemaFormatTest.scientific_uses_exponent_and_precision]==] [==[UnitsSchemaFormatTest.default_matches_qt_general_scientific_thresholds]==] [==[UnitsSchemaFormatTest.omit_group_separator_option_removes_grouping]==] [==[UnitsSchemaFormatTest.formatting_state_overrides_icu_default]==] [==[UnitsSchemaFormatTest.default_translation_uses_current_numeric_formatting_locale]==] [==[UnitsSchemaFormatTest.effective_numeric_separators_override_locale_symbols]==] [==[UnitsSchemaFormatTest.explicit_formatting_state_does_not_use_published_snapshot]==] [==[Vector.TestDefault]==] [==[Vector.TestDefault2]==] [==[Vector.TestCopy]==] [==[Vector.TestMove]==] [==[Vector.TestNull]==] [==[Vector.TestEqual]==] [==[Vector.TestIndex]==] [==[Vector.TestPlus]==] [==[Vector.TestPlusAssign]==] [==[Vector.TestMinus]==] [==[Vector.TestMinusAssign]==] [==[Vector.TestNegative]==] [==[Vector.TestScale]==] [==[Vector.TestScaleAssign]==] [==[Vector.TestDivScale]==] [==[Vector.TestDivScaleAssign]==] [==[Vector.TestScaleXYZ]==] [==[Vector.TestMoveXYZ]==] [==[Vector.TestCopyAssign]==] [==[Vector.TestMoveAssign]==] [==[Vector.TestScalar]==] [==[Vector.TestCross]==] [==[Vector.TestCompare]==] [==[Vector.TestNormalize]==] [==[Vector.TestCSTransform]==] [==[Vector.TestLineSegment]==] [==[Vector.TestDistanceLineSegment]==] [==[Vector.TestProjectToPlane]==] [==[Vector.TestDistanceToPlane]==] [==[Vector.TestAngle]==] [==[Vector.TestIsNormal]==] [==[Vector.TestIsNormalNullVector]==] [==[Vector.TestIsNormalLongVectors]==] [==[Vector.TestIsNormalShortVectors]==] [==[Vector.TestIsParallel]==] [==[Vector.TestIsParallelNullVector]==] [==[Vector.TestIsParallelLongVectors]==] [==[Vector.TestIsParallelShortVectors]==] [==[Vector.TestAngleOriented]==] [==[ViewProj.TestViewProjMatrix]==] [==[ViewProj.TestViewOrthoProjMatrix]==] [==[WriterTest.insertTextSimple]==] [==[WriterTest.insertTextNeedsEscape]==] [==[WriterTest.insertNonAsciiData]==] [==[WriterTest.beginCharStream]==] [==[WriterTest.beginCharStreamTwice]==] [==[WriterTest.endCharStream]==] [==[WriterTest.endCharStreamTwice]==] [==[WriterTest.charStream]==] [==[WriterTest.charStreamBase64Encoded]==] [==[XMLParserTest.TestLoadValidDocument]==] [==[XMLParserTest.TestLoadInvalidDocument]==] [==[XMLParserTest.TestLoadEmptyDocument]==] [==[XMLParserTest.TestLoadInvalidPath]==] [==[XMLParserTest.TestCheckValidFile]==] [==[XMLParserTest.TestCheckInvalidFile]==] [==[XMLParserTest.TestWriteValidDocument]==] [==[TestXMLTools.EscapeXmlEmptyString]==] [==[TestXMLTools.EscapeXmlNoChangesForSafeText]==] [==[TestXMLTools.EscapeXmlEscapesAmpersand]==] [==[TestXMLTools.EscapeXmlEscapesLessThanAndGreaterThan]==] [==[TestXMLTools.EscapeXmlEscapesQuotes]==] [==[TestXMLTools.EscapeXmlEscapesAllFiveInOneString]==] [==[TestXMLTools.EscapeXmlDoesNotDoubleEscapeNewlyInsertedEntities]==] [==[TestXMLTools.EscapeXmlComplexMixedContent]==] [==[TestXMLTools.EscapeXmlMultipleAdjacentCharacters]==] [==[TestXMLTools.EscapeXmlPreservesWhitespaceAndControlCommonInText]==])
