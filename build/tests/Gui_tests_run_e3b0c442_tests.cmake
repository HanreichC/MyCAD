add_test([=[Assistant.first]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=Assistant.first]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Assistant.first]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/Assistant.cpp:19]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CameraPrecalculatedQuaternions.testIsometric]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=CameraPrecalculatedQuaternions.testIsometric]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CameraPrecalculatedQuaternions.testIsometric]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/Camera.cpp:199]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CameraPrecalculatedQuaternions.testDimetric]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=CameraPrecalculatedQuaternions.testDimetric]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CameraPrecalculatedQuaternions.testDimetric]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/Camera.cpp:211]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CameraPrecalculatedQuaternions.testTrimetric]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=CameraPrecalculatedQuaternions.testTrimetric]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CameraPrecalculatedQuaternions.testTrimetric]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/Camera.cpp:223]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CameraRotation.testIsometricProjection]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=CameraRotation.testIsometricProjection]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CameraRotation.testIsometricProjection]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/Camera.cpp:245]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CameraRotation.testDimetricProjection]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=CameraRotation.testDimetricProjection]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CameraRotation.testDimetricProjection]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/Camera.cpp:256]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CameraRotation.testTrimetricProjection]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=CameraRotation.testTrimetricProjection]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CameraRotation.testTrimetricProjection]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/Camera.cpp:278]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CameraFitToBox.aCubeIsFramedWithTheMargin]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=CameraFitToBox.aCubeIsFramedWithTheMargin]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CameraFitToBox.aCubeIsFramedWithTheMargin]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/Camera.cpp:307]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CameraFitToBox.noCornerIsClipped]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=CameraFitToBox.noCornerIsClipped]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CameraFitToBox.noCornerIsClipped]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/Camera.cpp:322]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CameraFitToBox.theClippingPlanesClearTheScene]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=CameraFitToBox.theClippingPlanesClearTheScene]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CameraFitToBox.theClippingPlanesClearTheScene]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/Camera.cpp:333]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CameraFitToBox.theContentReachesTheMargin]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=CameraFitToBox.theContentReachesTheMargin]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CameraFitToBox.theContentReachesTheMargin]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/Camera.cpp:345]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CameraFitToBox.aTranslatedBoxFramesIdentically]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=CameraFitToBox.aTranslatedBoxFramesIdentically]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CameraFitToBox.aTranslatedBoxFramesIdentically]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/Camera.cpp:356]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CameraFitToBox.anElongatedRodBeatsTheSphereFit]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=CameraFitToBox.anElongatedRodBeatsTheSphereFit]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CameraFitToBox.anElongatedRodBeatsTheSphereFit]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/Camera.cpp:376]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CameraFitToBox.theAspectRatioDecidesWhichExtentConstrains]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=CameraFitToBox.theAspectRatioDecidesWhichExtentConstrains]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CameraFitToBox.theAspectRatioDecidesWhichExtentConstrains]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/Camera.cpp:391]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CameraFitToBox.anEmptyBoxLeavesTheCameraAlone]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=CameraFitToBox.anEmptyBoxLeavesTheCameraAlone]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CameraFitToBox.anEmptyBoxLeavesTheCameraAlone]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/Camera.cpp:406]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CameraFitToBox.aPointBoxLeavesTheCameraAlone]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=CameraFitToBox.aPointBoxLeavesTheCameraAlone]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CameraFitToBox.aPointBoxLeavesTheCameraAlone]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/Camera.cpp:411]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ColorScaleOverlayTest.buildsGradientSnapshot]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ColorScaleOverlayTest.buildsGradientSnapshot]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ColorScaleOverlayTest.buildsGradientSnapshot]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/ColorScaleOverlayTest.cpp:14]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ColorScaleOverlayTest.usesScientificNotationWhenFixedLabelsCollide]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ColorScaleOverlayTest.usesScientificNotationWhenFixedLabelsCollide]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ColorScaleOverlayTest.usesScientificNotationWhenFixedLabelsCollide]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/ColorScaleOverlayTest.cpp:37]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ColorScaleOverlayTest.buildsGradientSnapshotForLargeRange]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ColorScaleOverlayTest.buildsGradientSnapshotForLargeRange]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ColorScaleOverlayTest.buildsGradientSnapshotForLargeRange]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/ColorScaleOverlayTest.cpp:53]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ColorScaleOverlayTest.buildsLegendSnapshotAndUsesLegendColors]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ColorScaleOverlayTest.buildsLegendSnapshotAndUsesLegendColors]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ColorScaleOverlayTest.buildsLegendSnapshotAndUsesLegendColors]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/ColorScaleOverlayTest.cpp:69]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileDialog.testNormalizeSavePath]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=FileDialog.testNormalizeSavePath]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileDialog.testNormalizeSavePath]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/FileDialog.cpp:19]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileDialog.testFilterFromFilterString]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=FileDialog.testFilterFromFilterString]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileDialog.testFilterFromFilterString]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/FileDialog.cpp:108]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FileDialog.testFilterWildcard]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=FileDialog.testFilterWildcard]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FileDialog.testFilterWildcard]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/FileDialog.cpp:128]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StyleParametersApplicationTest.ReplaceVariablesInQss]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=StyleParametersApplicationTest.ReplaceVariablesInQss]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StyleParametersApplicationTest.ReplaceVariablesInQss]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/StyleParametersApplicationTest.cpp:64]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StyleParametersApplicationTest.ReplaceVariablesInQssWithUnknownVariable]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=StyleParametersApplicationTest.ReplaceVariablesInQssWithUnknownVariable]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StyleParametersApplicationTest.ReplaceVariablesInQssWithUnknownVariable]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/StyleParametersApplicationTest.cpp:73]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StyleParametersApplicationTest.ReplaceVariablesInQssWithEmptyString]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=StyleParametersApplicationTest.ReplaceVariablesInQssWithEmptyString]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StyleParametersApplicationTest.ReplaceVariablesInQssWithEmptyString]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/StyleParametersApplicationTest.cpp:82]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StyleParametersApplicationTest.ReplaceVariablesInQssWithMultipleOccurrences]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=StyleParametersApplicationTest.ReplaceVariablesInQssWithMultipleOccurrences]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StyleParametersApplicationTest.ReplaceVariablesInQssWithMultipleOccurrences]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/StyleParametersApplicationTest.cpp:91]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ParseNumbers]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ParseNumbers]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ParseNumbers]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:83]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ParseColors]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ParseColors]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ParseColors]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:107]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ParseParameterReferences]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ParseParameterReferences]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ParseParameterReferences]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:140]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ParseArithmeticOperations]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ParseArithmeticOperations]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ParseArithmeticOperations]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:159]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ParseComplexExpressions]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ParseComplexExpressions]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ParseComplexExpressions]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:203]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ParseUnaryOperations]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ParseUnaryOperations]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ParseUnaryOperations]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:227]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ParseFunctionCalls]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ParseFunctionCalls]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ParseFunctionCalls]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:246]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ParseKeyword]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ParseKeyword]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ParseKeyword]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:274]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ParseIdentifierWithFunctionName]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ParseIdentifierWithFunctionName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ParseIdentifierWithFunctionName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:281]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ParseKeywordInsideTuple]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ParseKeywordInsideTuple]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ParseKeywordInsideTuple]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:288]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ParseKeywordSurroundedByWhitespace]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ParseKeywordSurroundedByWhitespace]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ParseKeywordSurroundedByWhitespace]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:299]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ParseErrors]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ParseErrors]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ParseErrors]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:307]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ParseWhitespace]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ParseWhitespace]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ParseWhitespace]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:338]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ParseEdgeCases]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ParseEdgeCases]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ParseEdgeCases]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:357]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ParseOperatorPrecedence]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ParseOperatorPrecedence]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ParseOperatorPrecedence]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:385]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ParseUnnamedTuple]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ParseUnnamedTuple]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ParseUnnamedTuple]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:404]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ParseNamedTuple]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ParseNamedTuple]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ParseNamedTuple]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:416]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ParseMixedTuple]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ParseMixedTuple]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ParseMixedTuple]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:428]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ParseNamedTupleWithNumericNames]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ParseNamedTupleWithNumericNames]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ParseNamedTupleWithNumericNames]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:440]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ParseSingleNamedElementIsTuple]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ParseSingleNamedElementIsTuple]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ParseSingleNamedElementIsTuple]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:452]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ParseTupleWithExpressions]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ParseTupleWithExpressions]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ParseTupleWithExpressions]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:463]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ParseTupleWithMixedTypes]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ParseTupleWithMixedTypes]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ParseTupleWithMixedTypes]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:475]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ParseNestedTuples]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ParseNestedTuples]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ParseNestedTuples]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:487]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ParseTupleWithComplexExpressions]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ParseTupleWithComplexExpressions]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ParseTupleWithComplexExpressions]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:508]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.TupleToString]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.TupleToString]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.TupleToString]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:523]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ValueHoldsAndGet]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ValueHoldsAndGet]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ValueHoldsAndGet]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:545]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.TupleAtOutOfBounds]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.TupleAtOutOfBounds]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.TupleAtOutOfBounds]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:567]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.TupleFindNonexistent]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.TupleFindNonexistent]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.TupleFindNonexistent]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:579]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.TupleMissingClosingParen]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.TupleMissingClosingParen]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.TupleMissingClosingParen]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:590]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.GroupedExpressionStillWorks]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.GroupedExpressionStillWorks]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.GroupedExpressionStillWorks]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:596]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ParseNestedParentheses]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ParseNestedParentheses]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ParseNestedParentheses]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:612]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.MemberAccessNamed]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.MemberAccessNamed]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.MemberAccessNamed]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:626]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.MemberAccessIndexed]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.MemberAccessIndexed]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.MemberAccessIndexed]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:642]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.MemberAccessInlineTuple]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.MemberAccessInlineTuple]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.MemberAccessInlineTuple]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:658]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.MemberAccessInArithmetic]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.MemberAccessInArithmetic]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.MemberAccessInArithmetic]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:672]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.MemberAccessChained]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.MemberAccessChained]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.MemberAccessChained]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:680]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.MemberAccessErrors]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.MemberAccessErrors]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.MemberAccessErrors]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:688]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.TupleElementWiseAdd]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.TupleElementWiseAdd]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.TupleElementWiseAdd]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:702]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.TupleElementWiseSubtract]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.TupleElementWiseSubtract]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.TupleElementWiseSubtract]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:714]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.TupleScalarMultiplyTupleFirst]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.TupleScalarMultiplyTupleFirst]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.TupleScalarMultiplyTupleFirst]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:726]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.TupleScalarMultiplyScalarFirst]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.TupleScalarMultiplyScalarFirst]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.TupleScalarMultiplyScalarFirst]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:739]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.TupleScalarMultiplyUnitOnScalar]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.TupleScalarMultiplyUnitOnScalar]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.TupleScalarMultiplyUnitOnScalar]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:752]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.TupleScalarDivideUnitOnTuple]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.TupleScalarDivideUnitOnTuple]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.TupleScalarDivideUnitOnTuple]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:766]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.TupleScalarDivide]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.TupleScalarDivide]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.TupleScalarDivide]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:778]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.TupleUnaryNegate]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.TupleUnaryNegate]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.TupleUnaryNegate]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:790]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.TupleAddPreservesNames]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.TupleAddPreservesNames]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.TupleAddPreservesNames]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:802]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.TupleAddMatchesByName]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.TupleAddMatchesByName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.TupleAddMatchesByName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:815]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.TupleParamArithmetic]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.TupleParamArithmetic]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.TupleParamArithmetic]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:828]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.TupleUnionMixedNamedUnnamed]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.TupleUnionMixedNamedUnnamed]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.TupleUnionMixedNamedUnnamed]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:842]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.TupleUnionNamedDifferentSizes]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.TupleUnionNamedDifferentSizes]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.TupleUnionNamedDifferentSizes]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:858]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.TupleUnionUnnamedDifferentSizes]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.TupleUnionUnnamedDifferentSizes]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.TupleUnionUnnamedDifferentSizes]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:873]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.TupleAddNumericError]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.TupleAddNumericError]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.TupleAddNumericError]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:888]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.TupleNestedScalarMultiply]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.TupleNestedScalarMultiply]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.TupleNestedScalarMultiply]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:893]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.PaddingShorthand1Arg]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.PaddingShorthand1Arg]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.PaddingShorthand1Arg]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1123]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.PaddingShorthand2Args]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.PaddingShorthand2Args]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.PaddingShorthand2Args]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1133]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.PaddingShorthand3Args]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.PaddingShorthand3Args]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.PaddingShorthand3Args]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1142]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.PaddingShorthand4Args]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.PaddingShorthand4Args]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.PaddingShorthand4Args]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1151]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.PaddingNamedVerticalHorizontal]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.PaddingNamedVerticalHorizontal]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.PaddingNamedVerticalHorizontal]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1160]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.PaddingNamedExplicitSides]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.PaddingNamedExplicitSides]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.PaddingNamedExplicitSides]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1168]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.PaddingMixedNamedOverride]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.PaddingMixedNamedOverride]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.PaddingMixedNamedOverride]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1176]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.MarginsFunction]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.MarginsFunction]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.MarginsFunction]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1185]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.InsetsConvertsTupleArgToTargetKind]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.InsetsConvertsTupleArgToTargetKind]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.InsetsConvertsTupleArgToTargetKind]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1192]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.InsetsConvertsGenericTupleArg]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.InsetsConvertsGenericTupleArg]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.InsetsConvertsGenericTupleArg]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1202]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.InsetsNamedOverrideBeatsTupleArgument]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.InsetsNamedOverrideBeatsTupleArgument]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.InsetsNamedOverrideBeatsTupleArgument]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1212]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.InsetsGroupOverrideBeatsTupleArgument]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.InsetsGroupOverrideBeatsTupleArgument]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.InsetsGroupOverrideBeatsTupleArgument]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1222]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.BorderThicknessFunction]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.BorderThicknessFunction]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.BorderThicknessFunction]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1231]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.KindPreservedThroughAdd]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.KindPreservedThroughAdd]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.KindPreservedThroughAdd]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1242]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.KindPreservedThroughScalarMultiply]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.KindPreservedThroughScalarMultiply]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.KindPreservedThroughScalarMultiply]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1250]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.KindPreservedThroughNegate]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.KindPreservedThroughNegate]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.KindPreservedThroughNegate]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1258]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.KindMismatchError]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.KindMismatchError]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.KindMismatchError]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1266]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.TypedKindPlusGenericKeepsKind]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.TypedKindPlusGenericKeepsKind]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.TypedKindPlusGenericKeepsKind]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1271]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ExtraNamedElementDropsKind]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ExtraNamedElementDropsKind]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ExtraNamedElementDropsKind]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1279]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.UnmatchedUnnamedElementsDropKind]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.UnmatchedUnnamedElementsDropKind]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.UnmatchedUnnamedElementsDropKind]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1290]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.InsetsPaddingWrapper]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.InsetsPaddingWrapper]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.InsetsPaddingWrapper]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1301]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.InsetsWrongKindCoercedFromNamedElements]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.InsetsWrongKindCoercedFromNamedElements]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.InsetsWrongKindCoercedFromNamedElements]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1315]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.BorderRadiusShorthand1Arg]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.BorderRadiusShorthand1Arg]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.BorderRadiusShorthand1Arg]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1331]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.BorderRadiusShorthand2Args]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.BorderRadiusShorthand2Args]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.BorderRadiusShorthand2Args]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1341]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.BorderRadiusShorthand3Args]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.BorderRadiusShorthand3Args]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.BorderRadiusShorthand3Args]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1351]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.BorderRadiusShorthand4Args]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.BorderRadiusShorthand4Args]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.BorderRadiusShorthand4Args]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1361]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.BorderRadiusNamedOverride]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.BorderRadiusNamedOverride]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.BorderRadiusNamedOverride]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1370]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.BorderRadiusConvertsTupleArg]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.BorderRadiusConvertsTupleArg]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.BorderRadiusConvertsTupleArg]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1378]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.BorderRadiusNamedOverrideBeatsTupleArgument]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.BorderRadiusNamedOverrideBeatsTupleArgument]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.BorderRadiusNamedOverrideBeatsTupleArgument]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1391]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.BorderRadiusKindPreservedThroughArithmetic]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.BorderRadiusKindPreservedThroughArithmetic]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.BorderRadiusKindPreservedThroughArithmetic]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1401]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.BorderRadiusKindMismatchWithInsetsThrows]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.BorderRadiusKindMismatchWithInsetsThrows]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.BorderRadiusKindMismatchWithInsetsThrows]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1409]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.CornersWrapper]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.CornersWrapper]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.CornersWrapper]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1414]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.CornersFromUnrelatedTupleDefaultsToZero]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.CornersFromUnrelatedTupleDefaultsToZero]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.CornersFromUnrelatedTupleDefaultsToZero]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1426]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ResolveTypedCorners]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ResolveTypedCorners]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ResolveTypedCorners]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1444]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.LinearGradientMinimal]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.LinearGradientMinimal]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.LinearGradientMinimal]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1475]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.LinearGradientExplicitStops]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.LinearGradientExplicitStops]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.LinearGradientExplicitStops]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1506]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.LinearGradientCustomGeometry]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.LinearGradientCustomGeometry]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.LinearGradientCustomGeometry]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1524]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.LinearGradientMixedStops]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.LinearGradientMixedStops]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.LinearGradientMixedStops]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1541]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.RadialGradientMinimal]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.RadialGradientMinimal]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.RadialGradientMinimal]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1558]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.RadialGradientCustomGeometry]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.RadialGradientCustomGeometry]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.RadialGradientCustomGeometry]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1576]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.RadialGradientExplicitFocalPoint]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.RadialGradientExplicitFocalPoint]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.RadialGradientExplicitFocalPoint]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1592]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.GradientTooFewStopsDegrades]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.GradientTooFewStopsDegrades]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.GradientTooFewStopsDegrades]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1602]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.GradientAcceptsPercentagesAsNormalizedCoordinates]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.GradientAcceptsPercentagesAsNormalizedCoordinates]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.GradientAcceptsPercentagesAsNormalizedCoordinates]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1629]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.GradientGeometryWithUnitReportsAndDefaults]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.GradientGeometryWithUnitReportsAndDefaults]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.GradientGeometryWithUnitReportsAndDefaults]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1646]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.GradientStopPositionWithUnitReportsAndDegrades]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.GradientStopPositionWithUnitReportsAndDegrades]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.GradientStopPositionWithUnitReportsAndDegrades]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1660]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.GradientWrapper]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.GradientWrapper]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.GradientWrapper]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1675]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.RadialGradientWrapper]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.RadialGradientWrapper]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.RadialGradientWrapper]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1694]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.GradientStopsAccessibleViaMemberAccess]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.GradientStopsAccessibleViaMemberAccess]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.GradientStopsAccessibleViaMemberAccess]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1712]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ResolveTypedLinearGradient]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ResolveTypedLinearGradient]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ResolveTypedLinearGradient]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1719]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.LightenGradient]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.LightenGradient]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.LightenGradient]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1770]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.DarkenGradient]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.DarkenGradient]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.DarkenGradient]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1793]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.BlendGradientWithColor]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.BlendGradientWithColor]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.BlendGradientWithColor]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1817]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.BlendColorWithGradient]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.BlendColorWithGradient]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.BlendColorWithGradient]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1836]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.BlendTwoGradientsThrows]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.BlendTwoGradientsThrows]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.BlendTwoGradientsThrows]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1855]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.CoalesceReturnsFirstDefined]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.CoalesceReturnsFirstDefined]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.CoalesceReturnsFirstDefined]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1865]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.CoalesceReturnsFirstWhenDefined]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.CoalesceReturnsFirstWhenDefined]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.CoalesceReturnsFirstWhenDefined]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1873]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.CoalesceAllUndefinedReturnsFallbackString]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.CoalesceAllUndefinedReturnsFallbackString]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.CoalesceAllUndefinedReturnsFallbackString]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1880]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.CoalesceSkipsMultipleUndefined]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.CoalesceSkipsMultipleUndefined]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.CoalesceSkipsMultipleUndefined]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1887]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ShadeBasicColor]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ShadeBasicColor]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ShadeBasicColor]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1896]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ShadeWithPercentage]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ShadeWithPercentage]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ShadeWithPercentage]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1911]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ShadeAnchorReturnsOriginal]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ShadeAnchorReturnsOriginal]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ShadeAnchorReturnsOriginal]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1922]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ShadeLighterPosition]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ShadeLighterPosition]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ShadeLighterPosition]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1933]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ShadeGradient]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ShadeGradient]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ShadeGradient]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1945]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ShadesLighterAndDarker]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ShadesLighterAndDarker]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ShadesLighterAndDarker]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1970]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ShadesAnchorExactMatch]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ShadesAnchorExactMatch]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ShadesAnchorExactMatch]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1996]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ShadesMonotonicLightness]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ShadesMonotonicLightness]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ShadesMonotonicLightness]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:2011]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ShadesPreservesHue]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ShadesPreservesHue]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ShadesPreservesHue]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:2043]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ShadesCustomRange]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ShadesCustomRange]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ShadesCustomRange]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:2063]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ShadesCustomMinMax]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ShadesCustomMinMax]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ShadesCustomMinMax]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:2084]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ContentBoxWithSizeTupleAndPadding]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ContentBoxWithSizeTupleAndPadding]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ContentBoxWithSizeTupleAndPadding]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:2102]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ContentBoxWithAsymmetricPadding]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ContentBoxWithAsymmetricPadding]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ContentBoxWithAsymmetricPadding]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:2112]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ContentBoxWithMultipleInsets]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ContentBoxWithMultipleInsets]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ContentBoxWithMultipleInsets]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:2126]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ContentBoxWithSingleNumericInset]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ContentBoxWithSingleNumericInset]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ContentBoxWithSingleNumericInset]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:2141]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ContentBoxWithTwoNumericInsets]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ContentBoxWithTwoNumericInsets]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ContentBoxWithTwoNumericInsets]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:2152]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ContentBoxWithNumericValue]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ContentBoxWithNumericValue]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ContentBoxWithNumericValue]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:2164]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ContentBoxTooFewArguments]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ContentBoxTooFewArguments]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ContentBoxTooFewArguments]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:2175]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ColorFunctionsRejectNonColorArguments]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ColorFunctionsRejectNonColorArguments]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ColorFunctionsRejectNonColorArguments]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:2180]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ColorFunctionsRejectNonNumericOrNonTupleArguments]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ColorFunctionsRejectNonNumericOrNonTupleArguments]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ColorFunctionsRejectNonNumericOrNonTupleArguments]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:2201]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.ColorFunctionTypeErrorsAreContainedByResolve]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.ColorFunctionTypeErrorsAreContainedByResolve]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.ColorFunctionTypeErrorsAreContainedByResolve]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:2223]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserTest.MalformedGradientConvertsToNoBrush]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserTest.MalformedGradientConvertsToNoBrush]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserTest.MalformedGradientConvertsToNoBrush]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:2239]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ArgumentParserTest.AllPositional]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ArgumentParserTest.AllPositional]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ArgumentParserTest.AllPositional]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:919]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ArgumentParserTest.AllNamed]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ArgumentParserTest.AllNamed]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ArgumentParserTest.AllNamed]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:931]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ArgumentParserTest.AllNamedReversedOrder]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ArgumentParserTest.AllNamedReversedOrder]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ArgumentParserTest.AllNamedReversedOrder]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:943]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ArgumentParserTest.MixedPositionalThenNamed]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ArgumentParserTest.MixedPositionalThenNamed]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ArgumentParserTest.MixedPositionalThenNamed]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:955]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ArgumentParserTest.NamedThenPositionalFillsRemainingSlot]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ArgumentParserTest.NamedThenPositionalFillsRemainingSlot]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ArgumentParserTest.NamedThenPositionalFillsRemainingSlot]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:968]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ArgumentParserTest.DefaultValueUsedWhenMissing]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ArgumentParserTest.DefaultValueUsedWhenMissing]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ArgumentParserTest.DefaultValueUsedWhenMissing]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:981]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ArgumentParserTest.DefaultValueOverriddenByPositional]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ArgumentParserTest.DefaultValueOverriddenByPositional]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ArgumentParserTest.DefaultValueOverriddenByPositional]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:995]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ArgumentParserTest.DefaultValueOverriddenByName]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ArgumentParserTest.DefaultValueOverriddenByName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ArgumentParserTest.DefaultValueOverriddenByName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1009]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ArgumentParserTest.ResolvedTupleHasCorrectOrder]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ArgumentParserTest.ResolvedTupleHasCorrectOrder]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ArgumentParserTest.ResolvedTupleHasCorrectOrder]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1023]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ArgumentParserTest.MixedTypes]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ArgumentParserTest.MixedTypes]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ArgumentParserTest.MixedTypes]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1036]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ArgumentParserTest.ErrorOnUnknownName]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ArgumentParserTest.ErrorOnUnknownName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ArgumentParserTest.ErrorOnUnknownName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1048]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ArgumentParserTest.ErrorOnDuplicateName]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ArgumentParserTest.ErrorOnDuplicateName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ArgumentParserTest.ErrorOnDuplicateName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1057]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ArgumentParserTest.ErrorOnMissingRequired]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ArgumentParserTest.ErrorOnMissingRequired]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ArgumentParserTest.ErrorOnMissingRequired]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1067]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ArgumentParserTest.ErrorOnExcessPositional]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ArgumentParserTest.ErrorOnExcessPositional]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ArgumentParserTest.ErrorOnExcessPositional]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1076]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ArgumentParserTest.TypedGetSuccess]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ArgumentParserTest.TypedGetSuccess]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ArgumentParserTest.TypedGetSuccess]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1087]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ArgumentParserTest.TypedGetWrongType]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ArgumentParserTest.TypedGetWrongType]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ArgumentParserTest.TypedGetWrongType]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1100]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ArgumentParserTest.TypedGetMissingName]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ArgumentParserTest.TypedGetMissingName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ArgumentParserTest.TypedGetMissingName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserTest.cpp:1112]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserRobustnessTest.HugeMemberIndexIsAnExpressionError]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserRobustnessTest.HugeMemberIndexIsAnExpressionError]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserRobustnessTest.HugeMemberIndexIsAnExpressionError]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserRobustnessTest.cpp:51]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserRobustnessTest.HugeColorComponentIsAParserError]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserRobustnessTest.HugeColorComponentIsAParserError]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserRobustnessTest.HugeColorComponentIsAParserError]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserRobustnessTest.cpp:60]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserRobustnessTest.OverlongNumericLiteralIsAParserError]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserRobustnessTest.OverlongNumericLiteralIsAParserError]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserRobustnessTest.OverlongNumericLiteralIsAParserError]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserRobustnessTest.cpp:72]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserRobustnessTest.NonAsciiInputDoesNotCrash]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserRobustnessTest.NonAsciiInputDoesNotCrash]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserRobustnessTest.NonAsciiInputDoesNotCrash]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserRobustnessTest.cpp:85]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserRobustnessTest.EveryFailureThroughResolveIsContained]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserRobustnessTest.EveryFailureThroughResolveIsContained]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserRobustnessTest.EveryFailureThroughResolveIsContained]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserRobustnessTest.cpp:99]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserRobustnessTest.ShortHexColorLiteralIsAParserError]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserRobustnessTest.ShortHexColorLiteralIsAParserError]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserRobustnessTest.ShortHexColorLiteralIsAParserError]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserRobustnessTest.cpp:125]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserRobustnessTest.TwoDigitHexColorLiteralIsAParserError]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserRobustnessTest.TwoDigitHexColorLiteralIsAParserError]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserRobustnessTest.TwoDigitHexColorLiteralIsAParserError]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserRobustnessTest.cpp:136]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserRobustnessTest.BareHashIsAParserError]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserRobustnessTest.BareHashIsAParserError]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserRobustnessTest.BareHashIsAParserError]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserRobustnessTest.cpp:147]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParserRobustnessTest.FullLengthHexColorLiteralStillParses]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParserRobustnessTest.FullLengthHexColorLiteralStillParses]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParserRobustnessTest.FullLengthHexColorLiteralStillParses]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParserRobustnessTest.cpp:159]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.BasicParameterResolution]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.BasicParameterResolution]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.BasicParameterResolution]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:78]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.ParameterReferences]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.ParameterReferences]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.ParameterReferences]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:100]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.Caching]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.Caching]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.Caching]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:114]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.CacheInvalidation]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.CacheInvalidation]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.CacheInvalidation]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:132]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.SourcePriority]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.SourcePriority]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.SourcePriority]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:148]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.ParameterListing]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.ParameterListing]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.ParameterListing]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:167]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.ExpressionRetrieval]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.ExpressionRetrieval]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.ExpressionRetrieval]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:188]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.ParameterRetrieval]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.ParameterRetrieval]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.ParameterRetrieval]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:209]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.SourceManagement]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.SourceManagement]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.SourceManagement]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:225]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.CircularReferenceDetection]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.CircularReferenceDetection]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.CircularReferenceDetection]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:239]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.ComplexExpressions]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.ComplexExpressions]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.ComplexExpressions]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:260]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.ErrorHandling]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.ErrorHandling]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.ErrorHandling]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:295]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.ResolveParameterDefinition]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.ResolveParameterDefinition]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.ResolveParameterDefinition]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:321]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.ResolveParameterDefinitionDefault]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.ResolveParameterDefinitionDefault]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.ResolveParameterDefinitionDefault]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:331]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.QssFormattingNumeric]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.QssFormattingNumeric]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.QssFormattingNumeric]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:340]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.QssFormattingColor]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.QssFormattingColor]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.QssFormattingColor]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:345]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.QssFormattingGenericTuple]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.QssFormattingGenericTuple]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.QssFormattingGenericTuple]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:350]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.QssFormattingInsetsTuple]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.QssFormattingInsetsTuple]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.QssFormattingInsetsTuple]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:355]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.InlineExpressionSimple]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.InlineExpressionSimple]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.InlineExpressionSimple]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:362]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.InlineExpressionFunctionCall]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.InlineExpressionFunctionCall]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.InlineExpressionFunctionCall]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:368]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.InlineExpressionWithParameterReference]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.InlineExpressionWithParameterReference]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.InlineExpressionWithParameterReference]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:374]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.InlineExpressionArithmetic]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.InlineExpressionArithmetic]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.InlineExpressionArithmetic]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:387]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.InlineExpressionMixedWithToken]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.InlineExpressionMixedWithToken]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.InlineExpressionMixedWithToken]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:393]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.InlineExpressionInvalidLogsWarning]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.InlineExpressionInvalidLogsWarning]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.InlineExpressionInvalidLogsWarning]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:399]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.InlineExpressionMultiple]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.InlineExpressionMultiple]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.InlineExpressionMultiple]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:405]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.ExistingTokenUsesToQss]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.ExistingTokenUsesToQss]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.ExistingTokenUsesToQss]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:411]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.QssFormattingLinearGradient]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.QssFormattingLinearGradient]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.QssFormattingLinearGradient]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:418]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.QssFormattingLinearGradientCustomGeometry]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.QssFormattingLinearGradientCustomGeometry]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.QssFormattingLinearGradientCustomGeometry]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:427]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.QssFormattingRadialGradient]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.QssFormattingRadialGradient]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.QssFormattingRadialGradient]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:438]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.QssFormattingKeepsStopAlpha]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.QssFormattingKeepsStopAlpha]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.QssFormattingKeepsStopAlpha]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:448]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.QssFormattingKeepsColorAlpha]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.QssFormattingKeepsColorAlpha]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.QssFormattingKeepsColorAlpha]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:460]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.QssFormattingMalformedGradientStaysTransparent]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.QssFormattingMalformedGradientStaysTransparent]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.QssFormattingMalformedGradientStaysTransparent]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:466]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.ResolvePaddingCoercesEveryEquivalentTokenShape]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.ResolvePaddingCoercesEveryEquivalentTokenShape]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.ResolvePaddingCoercesEveryEquivalentTokenShape]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:485]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.ResolveDefinitionFallsBackWhenTokenHasWrongShape]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.ResolveDefinitionFallsBackWhenTokenHasWrongShape]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.ResolveDefinitionFallsBackWhenTokenHasWrongShape]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:532]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.ResolveDefinitionOfVariantTypeStillWorks]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.ResolveDefinitionOfVariantTypeStillWorks]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.ResolveDefinitionOfVariantTypeStillWorks]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:567]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.ReloadClearsDiagnosticState]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.ReloadClearsDiagnosticState]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.ReloadClearsDiagnosticState]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:588]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.EvaluateWrapsNonBaseExceptionsAsExpressionError]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.EvaluateWrapsNonBaseExceptionsAsExpressionError]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.EvaluateWrapsNonBaseExceptionsAsExpressionError]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:600]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.ReplacePlaceholdersAbsorbsNonBaseExceptions]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.ReplacePlaceholdersAbsorbsNonBaseExceptions]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.ReplacePlaceholdersAbsorbsNonBaseExceptions]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:609]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.ReplacePlaceholdersAbsorbsThrowingParameterSource]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.ReplacePlaceholdersAbsorbsThrowingParameterSource]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.ReplacePlaceholdersAbsorbsThrowingParameterSource]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:645]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.ResolveAbsorbsThrowingParameterSource]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.ResolveAbsorbsThrowingParameterSource]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.ResolveAbsorbsThrowingParameterSource]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:659]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.ResolveDefinitionAbsorbsThrowingParameterSource]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.ResolveDefinitionAbsorbsThrowingParameterSource]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.ResolveDefinitionAbsorbsThrowingParameterSource]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:671]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.ResolveAbsorbsThrowFromCyclicFallback]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.ResolveAbsorbsThrowFromCyclicFallback]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.ResolveAbsorbsThrowFromCyclicFallback]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:724]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.ResolveReportsAreAttributedToTheToken]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.ResolveReportsAreAttributedToTheToken]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.ResolveReportsAreAttributedToTheToken]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:739]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.SameDefectInTwoTokensProducesTwoDistinctMessages]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.SameDefectInTwoTokensProducesTwoDistinctMessages]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.SameDefectInTwoTokensProducesTwoDistinctMessages]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:754]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.CircularReferenceReportsThroughDiagnostics]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.CircularReferenceReportsThroughDiagnostics]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.CircularReferenceReportsThroughDiagnostics]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:779]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.UnknownTokenIsDroppedAndNeighboursStillResolve]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.UnknownTokenIsDroppedAndNeighboursStillResolve]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.UnknownTokenIsDroppedAndNeighboursStillResolve]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:800]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.FailingInlineExpressionIsDroppedAndNeighboursStillResolve]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.FailingInlineExpressionIsDroppedAndNeighboursStillResolve]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.FailingInlineExpressionIsDroppedAndNeighboursStillResolve]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:812]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ParameterManagerTest.TokenThatFailsToEvaluateSubstitutesItsLiteralText]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ParameterManagerTest.TokenThatFailsToEvaluateSubstitutesItsLiteralText]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ParameterManagerTest.TokenThatFailsToEvaluateSubstitutesItsLiteralText]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ParameterManagerTest.cpp:823]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[YamlParameterSourceTest.ScalarStringIsLoadedAsExpression]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=YamlParameterSourceTest.ScalarStringIsLoadedAsExpression]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[YamlParameterSourceTest.ScalarStringIsLoadedAsExpression]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/YamlParameterSourceTest.cpp:71]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[YamlParameterSourceTest.ScalarColorIsLoadedAsExpression]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=YamlParameterSourceTest.ScalarColorIsLoadedAsExpression]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[YamlParameterSourceTest.ScalarColorIsLoadedAsExpression]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/YamlParameterSourceTest.cpp:80]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[YamlParameterSourceTest.SequenceBecomesUnnamedTupleExpression]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=YamlParameterSourceTest.SequenceBecomesUnnamedTupleExpression]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[YamlParameterSourceTest.SequenceBecomesUnnamedTupleExpression]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/YamlParameterSourceTest.cpp:89]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[YamlParameterSourceTest.BlockSequenceBecomesUnnamedTupleExpression]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=YamlParameterSourceTest.BlockSequenceBecomesUnnamedTupleExpression]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[YamlParameterSourceTest.BlockSequenceBecomesUnnamedTupleExpression]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/YamlParameterSourceTest.cpp:98]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[YamlParameterSourceTest.MapBecomesNamedTupleExpression]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=YamlParameterSourceTest.MapBecomesNamedTupleExpression]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[YamlParameterSourceTest.MapBecomesNamedTupleExpression]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/YamlParameterSourceTest.cpp:113]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[YamlParameterSourceTest.NestedSequenceBecomesNestedTuple]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=YamlParameterSourceTest.NestedSequenceBecomesNestedTuple]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[YamlParameterSourceTest.NestedSequenceBecomesNestedTuple]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/YamlParameterSourceTest.cpp:128]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[YamlParameterSourceTest.SequenceResolvesToTupleValue]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=YamlParameterSourceTest.SequenceResolvesToTupleValue]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[YamlParameterSourceTest.SequenceResolvesToTupleValue]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/YamlParameterSourceTest.cpp:141]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[YamlParameterSourceTest.MapResolvesToNamedTupleValue]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=YamlParameterSourceTest.MapResolvesToNamedTupleValue]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[YamlParameterSourceTest.MapResolvesToNamedTupleValue]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/YamlParameterSourceTest.cpp:157]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[YamlParameterSourceTest.MixedFileLoadsAllParameters]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=YamlParameterSourceTest.MixedFileLoadsAllParameters]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[YamlParameterSourceTest.MixedFileLoadsAllParameters]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/YamlParameterSourceTest.cpp:176]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[YamlParameterSourceTest.FlushAndReloadPreservesSequenceValue]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=YamlParameterSourceTest.FlushAndReloadPreservesSequenceValue]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[YamlParameterSourceTest.FlushAndReloadPreservesSequenceValue]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/YamlParameterSourceTest.cpp:195]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DiagnosticsTest.DeliversFormattedMessageToObserver]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=DiagnosticsTest.DeliversFormattedMessageToObserver]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DiagnosticsTest.DeliversFormattedMessageToObserver]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/DiagnosticsTest.cpp:36]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DiagnosticsTest.DropsExactRepeats]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=DiagnosticsTest.DropsExactRepeats]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DiagnosticsTest.DropsExactRepeats]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/DiagnosticsTest.cpp:45]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DiagnosticsTest.ClearAllowsMessageAgain]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=DiagnosticsTest.ClearAllowsMessageAgain]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DiagnosticsTest.ClearAllowsMessageAgain]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/DiagnosticsTest.cpp:56]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DiagnosticsTest.ObserverStopsReceivingAfterSubscriptionEnds]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=DiagnosticsTest.ObserverStopsReceivingAfterSubscriptionEnds]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DiagnosticsTest.ObserverStopsReceivingAfterSubscriptionEnds]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/DiagnosticsTest.cpp:67]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DiagnosticsTest.SupportsMultipleSimultaneousObservers]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=DiagnosticsTest.SupportsMultipleSimultaneousObservers]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DiagnosticsTest.SupportsMultipleSimultaneousObservers]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/DiagnosticsTest.cpp:84]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DiagnosticsTest.ThrowingObserverDoesNotPreventOthersFromReceiving]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=DiagnosticsTest.ThrowingObserverDoesNotPreventOthersFromReceiving]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DiagnosticsTest.ThrowingObserverDoesNotPreventOthersFromReceiving]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/DiagnosticsTest.cpp:95]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DiagnosticsTest.NoActiveResolutionScopeMeansNoPrefix]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=DiagnosticsTest.NoActiveResolutionScopeMeansNoPrefix]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DiagnosticsTest.NoActiveResolutionScopeMeansNoPrefix]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/DiagnosticsTest.cpp:110]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DiagnosticsTest.ResolutionScopePrefixesTheTokenName]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=DiagnosticsTest.ResolutionScopePrefixesTheTokenName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DiagnosticsTest.ResolutionScopePrefixesTheTokenName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/DiagnosticsTest.cpp:119]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DiagnosticsTest.SameDefectUnderTwoScopesProducesTwoDistinctMessages]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=DiagnosticsTest.SameDefectUnderTwoScopesProducesTwoDistinctMessages]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DiagnosticsTest.SameDefectUnderTwoScopesProducesTwoDistinctMessages]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/DiagnosticsTest.cpp:131]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DiagnosticsTest.NestedResolutionScopeReportsTheInnermostToken]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=DiagnosticsTest.NestedResolutionScopeReportsTheInnermostToken]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DiagnosticsTest.NestedResolutionScopeReportsTheInnermostToken]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/DiagnosticsTest.cpp:147]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ValueAccessTest.StyleDefaultsAreEmptyValues]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ValueAccessTest.StyleDefaultsAreEmptyValues]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ValueAccessTest.StyleDefaultsAreEmptyValues]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ValueAccessTest.cpp:38]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ValueAccessTest.ValueGetWrongTypeReturnsDefaultAndReports]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ValueAccessTest.ValueGetWrongTypeReturnsDefaultAndReports]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ValueAccessTest.ValueGetWrongTypeReturnsDefaultAndReports]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ValueAccessTest.cpp:47]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ValueAccessTest.ValueGetWithFallbackReturnsFallback]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ValueAccessTest.ValueGetWithFallbackReturnsFallback]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ValueAccessTest.ValueGetWithFallbackReturnsFallback]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ValueAccessTest.cpp:56]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ValueAccessTest.ValueTryGetReturnsNullOnMismatchAndReportsNothing]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ValueAccessTest.ValueTryGetReturnsNullOnMismatchAndReportsNothing]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ValueAccessTest.ValueTryGetReturnsNullOnMismatchAndReportsNothing]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ValueAccessTest.cpp:63]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ValueAccessTest.TupleGetMissingNameReturnsDefaultAndReports]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ValueAccessTest.TupleGetMissingNameReturnsDefaultAndReports]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ValueAccessTest.TupleGetMissingNameReturnsDefaultAndReports]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ValueAccessTest.cpp:73]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ValueAccessTest.TupleGetWrongTypeReturnsDefaultAndReports]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ValueAccessTest.TupleGetWrongTypeReturnsDefaultAndReports]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ValueAccessTest.TupleGetWrongTypeReturnsDefaultAndReports]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ValueAccessTest.cpp:82]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ValueAccessTest.TupleGetWithFallbackReturnsFallback]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ValueAccessTest.TupleGetWithFallbackReturnsFallback]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ValueAccessTest.TupleGetWithFallbackReturnsFallback]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ValueAccessTest.cpp:91]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ValueAccessTest.TupleAtOutOfRangeReturnsDefaultAndReports]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ValueAccessTest.TupleAtOutOfRangeReturnsDefaultAndReports]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ValueAccessTest.TupleAtOutOfRangeReturnsDefaultAndReports]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ValueAccessTest.cpp:98]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ValueAccessTest.ShadesWithNonNumericSpecIsContainedByResolve]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ValueAccessTest.ShadesWithNonNumericSpecIsContainedByResolve]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ValueAccessTest.ShadesWithNonNumericSpecIsContainedByResolve]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ValueAccessTest.cpp:110]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ValueAccessTest.BlendWithNonColorOperandIsContainedByResolve]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ValueAccessTest.BlendWithNonColorOperandIsContainedByResolve]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ValueAccessTest.BlendWithNonColorOperandIsContainedByResolve]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ValueAccessTest.cpp:131]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[EdgesTest.PaddingFromColorDegradesToZeroAndReports]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=EdgesTest.PaddingFromColorDegradesToZeroAndReports]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[EdgesTest.PaddingFromColorDegradesToZeroAndReports]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/EdgesTest.cpp:57]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[EdgesTest.PaddingTryFromColorReturnsNullopt]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=EdgesTest.PaddingTryFromColorReturnsNullopt]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[EdgesTest.PaddingTryFromColorReturnsNullopt]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/EdgesTest.cpp:69]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[EdgesTest.PaddingFromBorderColorsDegradesToZero]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=EdgesTest.PaddingFromBorderColorsDegradesToZero]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[EdgesTest.PaddingFromBorderColorsDegradesToZero]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/EdgesTest.cpp:74]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[EdgesTest.PaddingFromNumericExpandsToAllSides]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=EdgesTest.PaddingFromNumericExpandsToAllSides]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[EdgesTest.PaddingFromNumericExpandsToAllSides]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/EdgesTest.cpp:83]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[EdgesTest.BorderColorsFromColorExpandsToAllSides]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=EdgesTest.BorderColorsFromColorExpandsToAllSides]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[EdgesTest.BorderColorsFromColorExpandsToAllSides]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/EdgesTest.cpp:94]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[EdgesTest.TooManyPositionalArgumentsDegradesToZero]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=EdgesTest.TooManyPositionalArgumentsDegradesToZero]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[EdgesTest.TooManyPositionalArgumentsDegradesToZero]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/EdgesTest.cpp:104]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[EdgesTest.PaddingAcceptsAnExistingPaddingTuple]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=EdgesTest.PaddingAcceptsAnExistingPaddingTuple]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[EdgesTest.PaddingAcceptsAnExistingPaddingTuple]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/EdgesTest.cpp:122]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[EdgesTest.InsetsAcceptAnyEdgeKind]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=EdgesTest.InsetsAcceptAnyEdgeKind]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[EdgesTest.InsetsAcceptAnyEdgeKind]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/EdgesTest.cpp:131]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[EdgesTest.PaddingOfNestedBorderColorsArgumentDegradesToZero]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=EdgesTest.PaddingOfNestedBorderColorsArgumentDegradesToZero]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[EdgesTest.PaddingOfNestedBorderColorsArgumentDegradesToZero]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/EdgesTest.cpp:140]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[EdgesTest.PaddingTryFromCornersReturnsNulloptWithMessage]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=EdgesTest.PaddingTryFromCornersReturnsNulloptWithMessage]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[EdgesTest.PaddingTryFromCornersReturnsNulloptWithMessage]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/EdgesTest.cpp:160]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[EdgesTest.InsetsTryFromLinearGradientReturnsNullopt]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=EdgesTest.InsetsTryFromLinearGradientReturnsNullopt]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[EdgesTest.InsetsTryFromLinearGradientReturnsNullopt]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/EdgesTest.cpp:173]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[EdgesTest.PaddingFromCornersDegradesToZeroAndReports]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=EdgesTest.PaddingFromCornersDegradesToZeroAndReports]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[EdgesTest.PaddingFromCornersDegradesToZeroAndReports]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/EdgesTest.cpp:188]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[EdgesTest.PaddingFromMarginsTupleCoerces]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=EdgesTest.PaddingFromMarginsTupleCoerces]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[EdgesTest.PaddingFromMarginsTupleCoerces]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/EdgesTest.cpp:200]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CornersTest.FromColorDegradesToZeroAndReports]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=CornersTest.FromColorDegradesToZeroAndReports]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CornersTest.FromColorDegradesToZeroAndReports]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/CornersTest.cpp:35]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CornersTest.TryFromColorReturnsNullopt]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=CornersTest.TryFromColorReturnsNullopt]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CornersTest.TryFromColorReturnsNullopt]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/CornersTest.cpp:47]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CornersTest.DiagonalPairingForTwoValues]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=CornersTest.DiagonalPairingForTwoValues]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CornersTest.DiagonalPairingForTwoValues]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/CornersTest.cpp:52]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CornersTest.TooManyPositionalArgumentsDegradesToZero]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=CornersTest.TooManyPositionalArgumentsDegradesToZero]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CornersTest.TooManyPositionalArgumentsDegradesToZero]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/CornersTest.cpp:66]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CornersTest.RejectsAPaddingTuple]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=CornersTest.RejectsAPaddingTuple]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CornersTest.RejectsAPaddingTuple]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/CornersTest.cpp:83]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[CornersTest.RawArgumentTupleFromColorDegradesToZeroAndReports]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=CornersTest.RawArgumentTupleFromColorDegradesToZeroAndReports]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CornersTest.RawArgumentTupleFromColorDegradesToZeroAndReports]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/CornersTest.cpp:101]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[GradientTest.TooFewStopsDegradesToTransparentAndReports]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=GradientTest.TooFewStopsDegradesToTransparentAndReports]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[GradientTest.TooFewStopsDegradesToTransparentAndReports]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/GradientTest.cpp:47]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[GradientTest.TryFromTooFewStopsReturnsNullopt]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=GradientTest.TryFromTooFewStopsReturnsNullopt]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[GradientTest.TryFromTooFewStopsReturnsNullopt]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/GradientTest.cpp:62]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[GradientTest.KindMismatchDegradesAndReports]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=GradientTest.KindMismatchDegradesAndReports]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[GradientTest.KindMismatchDegradesAndReports]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/GradientTest.cpp:70]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[GradientTest.NonNumericGeometryParameterDegradesAndReports]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=GradientTest.NonNumericGeometryParameterDegradesAndReports]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[GradientTest.NonNumericGeometryParameterDegradesAndReports]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/GradientTest.cpp:91]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[GradientTest.WellFormedGradientRoundTrips]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=GradientTest.WellFormedGradientRoundTrips]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[GradientTest.WellFormedGradientRoundTrips]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/GradientTest.cpp:116]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[GradientTest.MalformedKindTaggedTupleNeverProducesIllFormedWrapperThroughAnyRoute]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=GradientTest.MalformedKindTaggedTupleNeverProducesIllFormedWrapperThroughAnyRoute]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[GradientTest.MalformedKindTaggedTupleNeverProducesIllFormedWrapperThroughAnyRoute]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/GradientTest.cpp:130]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ColorShadingTest.AnchorReturnsUnchanged]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ColorShadingTest.AnchorReturnsUnchanged]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ColorShadingTest.AnchorReturnsUnchanged]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ColorShadingTest.cpp:26]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ColorShadingTest.MonotonicDecrease]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ColorShadingTest.MonotonicDecrease]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ColorShadingTest.MonotonicDecrease]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ColorShadingTest.cpp:35]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ColorShadingTest.SymmetricRangeIsLinear]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ColorShadingTest.SymmetricRangeIsLinear]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ColorShadingTest.SymmetricRangeIsLinear]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ColorShadingTest.cpp:52]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ColorShadingTest.ClampedRangeRespectsMinMax]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ColorShadingTest.ClampedRangeRespectsMinMax]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ColorShadingTest.ClampedRangeRespectsMinMax]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ColorShadingTest.cpp:67]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ColorShadingTest.NarrowRangeProducesLessVariation]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ColorShadingTest.NarrowRangeProducesLessVariation]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ColorShadingTest.NarrowRangeProducesLessVariation]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ColorShadingTest.cpp:87]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ColorShadingTest.ExtremeLightnessIsHandled]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ColorShadingTest.ExtremeLightnessIsHandled]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ColorShadingTest.ExtremeLightnessIsHandled]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ColorShadingTest.cpp:108]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ColorShadingTest.ChromaScalesWithGamutBoundary]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ColorShadingTest.ChromaScalesWithGamutBoundary]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ColorShadingTest.ChromaScalesWithGamutBoundary]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ColorShadingTest.cpp:130]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ColorShadingTest.LighterShadesReduceChroma]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ColorShadingTest.LighterShadesReduceChroma]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ColorShadingTest.LighterShadesReduceChroma]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ColorShadingTest.cpp:145]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ColorShadingTest.BlackAnchorProducesZeroChroma]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ColorShadingTest.BlackAnchorProducesZeroChroma]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ColorShadingTest.BlackAnchorProducesZeroChroma]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ColorShadingTest.cpp:157]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ColorShadingTest.WhiteAnchorProducesZeroChroma]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ColorShadingTest.WhiteAnchorProducesZeroChroma]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ColorShadingTest.WhiteAnchorProducesZeroChroma]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ColorShadingTest.cpp:172]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ColorShadingTest.GrayStaysNeutral]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ColorShadingTest.GrayStaysNeutral]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ColorShadingTest.GrayStaysNeutral]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ColorShadingTest.cpp:187]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ColorShadingTest.HueIsPreserved]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ColorShadingTest.HueIsPreserved]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ColorShadingTest.HueIsPreserved]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ColorShadingTest.cpp:201]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ColorShadingTest.ExtremePivotsProduceFiniteShades]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ColorShadingTest.ExtremePivotsProduceFiniteShades]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ColorShadingTest.ExtremePivotsProduceFiniteShades]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ColorShadingTest.cpp:211]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ColorShadingTest.MaxLightnessAboveOneIsClamped]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ColorShadingTest.MaxLightnessAboveOneIsClamped]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ColorShadingTest.MaxLightnessAboveOneIsClamped]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ColorShadingTest.cpp:226]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ColorShadingTest.InvertedBoundsPreserveLightToDarkDirection]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ColorShadingTest.InvertedBoundsPreserveLightToDarkDirection]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ColorShadingTest.InvertedBoundsPreserveLightToDarkDirection]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ColorShadingTest.cpp:238]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ColorShadingTest.OutOfRangePositionSaturatesAtTheCurveEnds]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ColorShadingTest.OutOfRangePositionSaturatesAtTheCurveEnds]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ColorShadingTest.OutOfRangePositionSaturatesAtTheCurveEnds]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/StyleParameters/ColorShadingTest.cpp:253]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[InputHintTest.LookupHintsSimpleState]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=InputHintTest.LookupHintsSimpleState]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[InputHintTest.LookupHintsSimpleState]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/InputHintTest.cpp:44]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[InputHintTest.LookupHintsPairState]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=InputHintTest.LookupHintsPairState]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[InputHintTest.LookupHintsPairState]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/InputHintTest.cpp:64]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ViewProviderDoubleClick.LegacyCallbackRunsOnce]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ViewProviderDoubleClick.LegacyCallbackRunsOnce]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ViewProviderDoubleClick.LegacyCallbackRunsOnce]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/ViewProviderDoubleClick.cpp:65]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ViewProviderDoubleClick.LegacyRejectionIsPreserved]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ViewProviderDoubleClick.LegacyRejectionIsPreserved]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ViewProviderDoubleClick.LegacyRejectionIsPreserved]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/ViewProviderDoubleClick.cpp:72]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ViewProviderDoubleClick.ExplicitRejectionDoesNotFallBackToLegacyCallback]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ViewProviderDoubleClick.ExplicitRejectionDoesNotFallBackToLegacyCallback]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ViewProviderDoubleClick.ExplicitRejectionDoesNotFallBackToLegacyCallback]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/ViewProviderDoubleClick.cpp:80]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ViewProviderDoubleClick.UnhandledOccurrenceUsesLegacyCallbackOnce]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ViewProviderDoubleClick.UnhandledOccurrenceUsesLegacyCallbackOnce]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ViewProviderDoubleClick.UnhandledOccurrenceUsesLegacyCallbackOnce]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/ViewProviderDoubleClick.cpp:89]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ViewProviderDoubleClick.KeepsTheCallersOccurrencePath]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=ViewProviderDoubleClick.KeepsTheCallersOccurrencePath]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ViewProviderDoubleClick.KeepsTheCallersOccurrencePath]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/ViewProviderDoubleClick.cpp:98]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DefaultEditReference.UsesModelContainersInsteadOfIncomingLinks]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=DefaultEditReference.UsesModelContainersInsteadOfIncomingLinks]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DefaultEditReference.UsesModelContainersInsteadOfIncomingLinks]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/ViewProviderDoubleClick.cpp:150]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DefaultEditReference.IncludesLinkGroupContainers]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=DefaultEditReference.IncludesLinkGroupContainers]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DefaultEditReference.IncludesLinkGroupContainers]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/ViewProviderDoubleClick.cpp:168]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DefaultEditReference.IncomingLinkDoesNotReplaceTopLevelObject]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=DefaultEditReference.IncomingLinkDoesNotReplaceTopLevelObject]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DefaultEditReference.IncomingLinkDoesNotReplaceTopLevelObject]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/ViewProviderDoubleClick.cpp:182]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NativeGesturePinch.zoomWithoutBeginIsRejected]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=NativeGesturePinch.zoomWithoutBeginIsRejected]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NativeGesturePinch.zoomWithoutBeginIsRejected]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/NativeGesturePinchTest.cpp:9]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NativeGesturePinch.beginActivatesAndRecordsCenter]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=NativeGesturePinch.beginActivatesAndRecordsCenter]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NativeGesturePinch.beginActivatesAndRecordsCenter]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/NativeGesturePinchTest.cpp:17]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NativeGesturePinch.zoomKeepsTheStartCenterFromBegin]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=NativeGesturePinch.zoomKeepsTheStartCenterFromBegin]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NativeGesturePinch.zoomKeepsTheStartCenterFromBegin]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/NativeGesturePinchTest.cpp:29]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NativeGesturePinch.nonPositiveZoomValueIsClampedToNeutral]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=NativeGesturePinch.nonPositiveZoomValueIsClampedToNeutral]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NativeGesturePinch.nonPositiveZoomValueIsClampedToNeutral]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/NativeGesturePinchTest.cpp:43]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NativeGesturePinch.rotateConvertsDegreesToRadiansAndInvertsDirection]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=NativeGesturePinch.rotateConvertsDegreesToRadiansAndInvertsDirection]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NativeGesturePinch.rotateConvertsDegreesToRadiansAndInvertsDirection]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/NativeGesturePinchTest.cpp:55]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NativeGesturePinch.endDeactivatesAndFurtherUpdatesAreRejected]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=NativeGesturePinch.endDeactivatesAndFurtherUpdatesAreRejected]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NativeGesturePinch.endDeactivatesAndFurtherUpdatesAreRejected]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/NativeGesturePinchTest.cpp:67]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NativeGesturePinch.unhandledGestureTypeIsRejectedWithoutDisturbingState]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=NativeGesturePinch.unhandledGestureTypeIsRejectedWithoutDisturbingState]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NativeGesturePinch.unhandledGestureTypeIsRejectedWithoutDisturbingState]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/NativeGesturePinchTest.cpp:79]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NativeGesturePinch.aSecondGestureResetsTheStartCenter]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=NativeGesturePinch.aSecondGestureResetsTheStartCenter]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NativeGesturePinch.aSecondGestureResetsTheStartCenter]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/NativeGesturePinchTest.cpp:91]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NavigationStylePinchAction.onlyUpdateEventsMoveTheCamera]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=NavigationStylePinchAction.onlyUpdateEventsMoveTheCamera]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NavigationStylePinchAction.onlyUpdateEventsMoveTheCamera]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/NavigationStylePinchTest.cpp:26]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NavigationStylePinchAction.aRotateOnlyEventDoesNotZoom]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=NavigationStylePinchAction.aRotateOnlyEventDoesNotZoom]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NavigationStylePinchAction.aRotateOnlyEventDoesNotZoom]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/NavigationStylePinchTest.cpp:42]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NavigationStylePinchAction.aZoomOnlyEventDoesNotRotate]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=NavigationStylePinchAction.aZoomOnlyEventDoesNotRotate]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NavigationStylePinchAction.aZoomOnlyEventDoesNotRotate]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/NavigationStylePinchTest.cpp:52]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NavigationStylePinchAction.aNegativeZoomFactorIsIgnored]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=NavigationStylePinchAction.aNegativeZoomFactorIsIgnored]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NavigationStylePinchAction.aNegativeZoomFactorIsIgnored]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/NavigationStylePinchTest.cpp:62]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NavigationStylePinchAction.pinchingOutZoomsIn]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=NavigationStylePinchAction.pinchingOutZoomsIn]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NavigationStylePinchAction.pinchingOutZoomsIn]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/NavigationStylePinchTest.cpp:71]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NavigationStylePinchAction.pinchingInZoomsOutBySymmetricAmount]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=NavigationStylePinchAction.pinchingInZoomsOutBySymmetricAmount]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NavigationStylePinchAction.pinchingInZoomsOutBySymmetricAmount]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/NavigationStylePinchTest.cpp:81]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NavigationStylePinchAction.aTouchscreenPinchObeysTheTiltPreference]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=NavigationStylePinchAction.aTouchscreenPinchObeysTheTiltPreference]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NavigationStylePinchAction.aTouchscreenPinchObeysTheTiltPreference]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/NavigationStylePinchTest.cpp:92]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NavigationStylePinchAction.aTrackpadRotateIsNotBlockedByTheTouchscreenTiltPreference]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=NavigationStylePinchAction.aTrackpadRotateIsNotBlockedByTheTouchscreenTiltPreference]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NavigationStylePinchAction.aTrackpadRotateIsNotBlockedByTheTouchscreenTiltPreference]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/NavigationStylePinchTest.cpp:102]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NavigationStyleWheelAction.anOrdinaryWheelZoomsWhateverThePreferenceSays]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=NavigationStyleWheelAction.anOrdinaryWheelZoomsWhateverThePreferenceSays]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NavigationStyleWheelAction.anOrdinaryWheelZoomsWhateverThePreferenceSays]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/NavigationStyleWheelTest.cpp:22]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NavigationStyleWheelAction.aTouchpadZoomsWhenScrollPanningIsOff]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=NavigationStyleWheelAction.aTouchpadZoomsWhenScrollPanningIsOff]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NavigationStyleWheelAction.aTouchpadZoomsWhenScrollPanningIsOff]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/NavigationStyleWheelTest.cpp:28]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NavigationStyleWheelAction.aTouchpadPansWhenScrollPanningIsOn]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=NavigationStyleWheelAction.aTouchpadPansWhenScrollPanningIsOn]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NavigationStyleWheelAction.aTouchpadPansWhenScrollPanningIsOn]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/NavigationStyleWheelTest.cpp:33]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NavigationStyleWheelAction.shiftOrbitsInsteadOfPanning]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=NavigationStyleWheelAction.shiftOrbitsInsteadOfPanning]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NavigationStyleWheelAction.shiftOrbitsInsteadOfPanning]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/NavigationStyleWheelTest.cpp:38]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NavigationStyleWheelAction.ctrlZoomsEvenWhileScrollPanningIsOn]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=NavigationStyleWheelAction.ctrlZoomsEvenWhileScrollPanningIsOn]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NavigationStyleWheelAction.ctrlZoomsEvenWhileScrollPanningIsOn]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/NavigationStyleWheelTest.cpp:43]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NavigationStyleWheelAction.ctrlWinsOverShift]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=NavigationStyleWheelAction.ctrlWinsOverShift]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NavigationStyleWheelAction.ctrlWinsOverShift]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/NavigationStyleWheelTest.cpp:48]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[NavigationStyleWheelAction.modifiersNeverDivertAnOrdinaryWheelFromZooming]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=NavigationStyleWheelAction.modifiersNeverDivertAnOrdinaryWheelFromZooming]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[NavigationStyleWheelAction.modifiersNeverDivertAnOrdinaryWheelFromZooming]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/NavigationStyleWheelTest.cpp:53]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SelectionTest.testSelectionAllowsObjectsWhenNoGateIsInstalled]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=SelectionTest.testSelectionAllowsObjectsWhenNoGateIsInstalled]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SelectionTest.testSelectionAllowsObjectsWhenNoGateIsInstalled]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/SelectionTest.cpp:93]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SelectionTest.testSelectionUsesActiveGateWithoutKeepingRejectionReason]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=SelectionTest.testSelectionUsesActiveGateWithoutKeepingRejectionReason]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SelectionTest.testSelectionUsesActiveGateWithoutKeepingRejectionReason]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/SelectionTest.cpp:98]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SelectionPickPolicyTest.canFinalizeSinglePickWhenNoGateIsInstalled]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=SelectionPickPolicyTest.canFinalizeSinglePickWhenNoGateIsInstalled]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SelectionPickPolicyTest.canFinalizeSinglePickWhenNoGateIsInstalled]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/SelectionTest.cpp:113]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SelectionPickPolicyTest.continuesSinglePickWhenGateRejectedAllCurrentCandidates]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=SelectionPickPolicyTest.continuesSinglePickWhenGateRejectedAllCurrentCandidates]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SelectionPickPolicyTest.continuesSinglePickWhenGateRejectedAllCurrentCandidates]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/SelectionTest.cpp:123]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SelectionPickPolicyTest.choosesAllowedCandidateWhenPreferredPickIsRejected]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=SelectionPickPolicyTest.choosesAllowedCandidateWhenPreferredPickIsRejected]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SelectionPickPolicyTest.choosesAllowedCandidateWhenPreferredPickIsRejected]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/SelectionTest.cpp:133]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SelectionPickPolicyTest.preservesPriorityChoiceWithinFirstOwner]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=SelectionPickPolicyTest.preservesPriorityChoiceWithinFirstOwner]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SelectionPickPolicyTest.preservesPriorityChoiceWithinFirstOwner]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/SelectionTest.cpp:145]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SelectionPickPolicyTest.keepsPreferredPickWhenNoCandidatePassesGate]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=SelectionPickPolicyTest.keepsPreferredPickWhenNoCandidatePassesGate]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SelectionPickPolicyTest.keepsPreferredPickWhenNoCandidatePassesGate]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/SelectionTest.cpp:158]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SoMouseWheelEvent.toGlPixelDeltaScalesByDevicePixelRatioAndFlipsY]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=SoMouseWheelEvent.toGlPixelDeltaScalesByDevicePixelRatioAndFlipsY]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SoMouseWheelEvent.toGlPixelDeltaScalesByDevicePixelRatioAndFlipsY]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/SoMouseWheelEventTest.cpp:7]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SoMouseWheelEvent.onlyAScrollWithAPhaseAndPixelDeltaIsPrecise]=]  /workspace/build/tests/Gui_tests_run [==[--gtest_filter=SoMouseWheelEvent.onlyAScrollWithAPhaseAndPixelDeltaIsPrecise]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SoMouseWheelEvent.onlyAScrollWithAPhaseAndPixelDeltaIsPrecise]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Gui/SoMouseWheelEventTest.cpp:12]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
set(Gui_tests_run_TESTS [==[Assistant.first]==] [==[CameraPrecalculatedQuaternions.testIsometric]==] [==[CameraPrecalculatedQuaternions.testDimetric]==] [==[CameraPrecalculatedQuaternions.testTrimetric]==] [==[CameraRotation.testIsometricProjection]==] [==[CameraRotation.testDimetricProjection]==] [==[CameraRotation.testTrimetricProjection]==] [==[CameraFitToBox.aCubeIsFramedWithTheMargin]==] [==[CameraFitToBox.noCornerIsClipped]==] [==[CameraFitToBox.theClippingPlanesClearTheScene]==] [==[CameraFitToBox.theContentReachesTheMargin]==] [==[CameraFitToBox.aTranslatedBoxFramesIdentically]==] [==[CameraFitToBox.anElongatedRodBeatsTheSphereFit]==] [==[CameraFitToBox.theAspectRatioDecidesWhichExtentConstrains]==] [==[CameraFitToBox.anEmptyBoxLeavesTheCameraAlone]==] [==[CameraFitToBox.aPointBoxLeavesTheCameraAlone]==] [==[ColorScaleOverlayTest.buildsGradientSnapshot]==] [==[ColorScaleOverlayTest.usesScientificNotationWhenFixedLabelsCollide]==] [==[ColorScaleOverlayTest.buildsGradientSnapshotForLargeRange]==] [==[ColorScaleOverlayTest.buildsLegendSnapshotAndUsesLegendColors]==] [==[FileDialog.testNormalizeSavePath]==] [==[FileDialog.testFilterFromFilterString]==] [==[FileDialog.testFilterWildcard]==] [==[StyleParametersApplicationTest.ReplaceVariablesInQss]==] [==[StyleParametersApplicationTest.ReplaceVariablesInQssWithUnknownVariable]==] [==[StyleParametersApplicationTest.ReplaceVariablesInQssWithEmptyString]==] [==[StyleParametersApplicationTest.ReplaceVariablesInQssWithMultipleOccurrences]==] [==[ParserTest.ParseNumbers]==] [==[ParserTest.ParseColors]==] [==[ParserTest.ParseParameterReferences]==] [==[ParserTest.ParseArithmeticOperations]==] [==[ParserTest.ParseComplexExpressions]==] [==[ParserTest.ParseUnaryOperations]==] [==[ParserTest.ParseFunctionCalls]==] [==[ParserTest.ParseKeyword]==] [==[ParserTest.ParseIdentifierWithFunctionName]==] [==[ParserTest.ParseKeywordInsideTuple]==] [==[ParserTest.ParseKeywordSurroundedByWhitespace]==] [==[ParserTest.ParseErrors]==] [==[ParserTest.ParseWhitespace]==] [==[ParserTest.ParseEdgeCases]==] [==[ParserTest.ParseOperatorPrecedence]==] [==[ParserTest.ParseUnnamedTuple]==] [==[ParserTest.ParseNamedTuple]==] [==[ParserTest.ParseMixedTuple]==] [==[ParserTest.ParseNamedTupleWithNumericNames]==] [==[ParserTest.ParseSingleNamedElementIsTuple]==] [==[ParserTest.ParseTupleWithExpressions]==] [==[ParserTest.ParseTupleWithMixedTypes]==] [==[ParserTest.ParseNestedTuples]==] [==[ParserTest.ParseTupleWithComplexExpressions]==] [==[ParserTest.TupleToString]==] [==[ParserTest.ValueHoldsAndGet]==] [==[ParserTest.TupleAtOutOfBounds]==] [==[ParserTest.TupleFindNonexistent]==] [==[ParserTest.TupleMissingClosingParen]==] [==[ParserTest.GroupedExpressionStillWorks]==] [==[ParserTest.ParseNestedParentheses]==] [==[ParserTest.MemberAccessNamed]==] [==[ParserTest.MemberAccessIndexed]==] [==[ParserTest.MemberAccessInlineTuple]==] [==[ParserTest.MemberAccessInArithmetic]==] [==[ParserTest.MemberAccessChained]==] [==[ParserTest.MemberAccessErrors]==] [==[ParserTest.TupleElementWiseAdd]==] [==[ParserTest.TupleElementWiseSubtract]==] [==[ParserTest.TupleScalarMultiplyTupleFirst]==] [==[ParserTest.TupleScalarMultiplyScalarFirst]==] [==[ParserTest.TupleScalarMultiplyUnitOnScalar]==] [==[ParserTest.TupleScalarDivideUnitOnTuple]==] [==[ParserTest.TupleScalarDivide]==] [==[ParserTest.TupleUnaryNegate]==] [==[ParserTest.TupleAddPreservesNames]==] [==[ParserTest.TupleAddMatchesByName]==] [==[ParserTest.TupleParamArithmetic]==] [==[ParserTest.TupleUnionMixedNamedUnnamed]==] [==[ParserTest.TupleUnionNamedDifferentSizes]==] [==[ParserTest.TupleUnionUnnamedDifferentSizes]==] [==[ParserTest.TupleAddNumericError]==] [==[ParserTest.TupleNestedScalarMultiply]==] [==[ParserTest.PaddingShorthand1Arg]==] [==[ParserTest.PaddingShorthand2Args]==] [==[ParserTest.PaddingShorthand3Args]==] [==[ParserTest.PaddingShorthand4Args]==] [==[ParserTest.PaddingNamedVerticalHorizontal]==] [==[ParserTest.PaddingNamedExplicitSides]==] [==[ParserTest.PaddingMixedNamedOverride]==] [==[ParserTest.MarginsFunction]==] [==[ParserTest.InsetsConvertsTupleArgToTargetKind]==] [==[ParserTest.InsetsConvertsGenericTupleArg]==] [==[ParserTest.InsetsNamedOverrideBeatsTupleArgument]==] [==[ParserTest.InsetsGroupOverrideBeatsTupleArgument]==] [==[ParserTest.BorderThicknessFunction]==] [==[ParserTest.KindPreservedThroughAdd]==] [==[ParserTest.KindPreservedThroughScalarMultiply]==] [==[ParserTest.KindPreservedThroughNegate]==] [==[ParserTest.KindMismatchError]==] [==[ParserTest.TypedKindPlusGenericKeepsKind]==] [==[ParserTest.ExtraNamedElementDropsKind]==] [==[ParserTest.UnmatchedUnnamedElementsDropKind]==] [==[ParserTest.InsetsPaddingWrapper]==] [==[ParserTest.InsetsWrongKindCoercedFromNamedElements]==] [==[ParserTest.BorderRadiusShorthand1Arg]==] [==[ParserTest.BorderRadiusShorthand2Args]==] [==[ParserTest.BorderRadiusShorthand3Args]==] [==[ParserTest.BorderRadiusShorthand4Args]==] [==[ParserTest.BorderRadiusNamedOverride]==] [==[ParserTest.BorderRadiusConvertsTupleArg]==] [==[ParserTest.BorderRadiusNamedOverrideBeatsTupleArgument]==] [==[ParserTest.BorderRadiusKindPreservedThroughArithmetic]==] [==[ParserTest.BorderRadiusKindMismatchWithInsetsThrows]==] [==[ParserTest.CornersWrapper]==] [==[ParserTest.CornersFromUnrelatedTupleDefaultsToZero]==] [==[ParserTest.ResolveTypedCorners]==] [==[ParserTest.LinearGradientMinimal]==] [==[ParserTest.LinearGradientExplicitStops]==] [==[ParserTest.LinearGradientCustomGeometry]==] [==[ParserTest.LinearGradientMixedStops]==] [==[ParserTest.RadialGradientMinimal]==] [==[ParserTest.RadialGradientCustomGeometry]==] [==[ParserTest.RadialGradientExplicitFocalPoint]==] [==[ParserTest.GradientTooFewStopsDegrades]==] [==[ParserTest.GradientAcceptsPercentagesAsNormalizedCoordinates]==] [==[ParserTest.GradientGeometryWithUnitReportsAndDefaults]==] [==[ParserTest.GradientStopPositionWithUnitReportsAndDegrades]==] [==[ParserTest.GradientWrapper]==] [==[ParserTest.RadialGradientWrapper]==] [==[ParserTest.GradientStopsAccessibleViaMemberAccess]==] [==[ParserTest.ResolveTypedLinearGradient]==] [==[ParserTest.LightenGradient]==] [==[ParserTest.DarkenGradient]==] [==[ParserTest.BlendGradientWithColor]==] [==[ParserTest.BlendColorWithGradient]==] [==[ParserTest.BlendTwoGradientsThrows]==] [==[ParserTest.CoalesceReturnsFirstDefined]==] [==[ParserTest.CoalesceReturnsFirstWhenDefined]==] [==[ParserTest.CoalesceAllUndefinedReturnsFallbackString]==] [==[ParserTest.CoalesceSkipsMultipleUndefined]==] [==[ParserTest.ShadeBasicColor]==] [==[ParserTest.ShadeWithPercentage]==] [==[ParserTest.ShadeAnchorReturnsOriginal]==] [==[ParserTest.ShadeLighterPosition]==] [==[ParserTest.ShadeGradient]==] [==[ParserTest.ShadesLighterAndDarker]==] [==[ParserTest.ShadesAnchorExactMatch]==] [==[ParserTest.ShadesMonotonicLightness]==] [==[ParserTest.ShadesPreservesHue]==] [==[ParserTest.ShadesCustomRange]==] [==[ParserTest.ShadesCustomMinMax]==] [==[ParserTest.ContentBoxWithSizeTupleAndPadding]==] [==[ParserTest.ContentBoxWithAsymmetricPadding]==] [==[ParserTest.ContentBoxWithMultipleInsets]==] [==[ParserTest.ContentBoxWithSingleNumericInset]==] [==[ParserTest.ContentBoxWithTwoNumericInsets]==] [==[ParserTest.ContentBoxWithNumericValue]==] [==[ParserTest.ContentBoxTooFewArguments]==] [==[ParserTest.ColorFunctionsRejectNonColorArguments]==] [==[ParserTest.ColorFunctionsRejectNonNumericOrNonTupleArguments]==] [==[ParserTest.ColorFunctionTypeErrorsAreContainedByResolve]==] [==[ParserTest.MalformedGradientConvertsToNoBrush]==] [==[ArgumentParserTest.AllPositional]==] [==[ArgumentParserTest.AllNamed]==] [==[ArgumentParserTest.AllNamedReversedOrder]==] [==[ArgumentParserTest.MixedPositionalThenNamed]==] [==[ArgumentParserTest.NamedThenPositionalFillsRemainingSlot]==] [==[ArgumentParserTest.DefaultValueUsedWhenMissing]==] [==[ArgumentParserTest.DefaultValueOverriddenByPositional]==] [==[ArgumentParserTest.DefaultValueOverriddenByName]==] [==[ArgumentParserTest.ResolvedTupleHasCorrectOrder]==] [==[ArgumentParserTest.MixedTypes]==] [==[ArgumentParserTest.ErrorOnUnknownName]==] [==[ArgumentParserTest.ErrorOnDuplicateName]==] [==[ArgumentParserTest.ErrorOnMissingRequired]==] [==[ArgumentParserTest.ErrorOnExcessPositional]==] [==[ArgumentParserTest.TypedGetSuccess]==] [==[ArgumentParserTest.TypedGetWrongType]==] [==[ArgumentParserTest.TypedGetMissingName]==] [==[ParserRobustnessTest.HugeMemberIndexIsAnExpressionError]==] [==[ParserRobustnessTest.HugeColorComponentIsAParserError]==] [==[ParserRobustnessTest.OverlongNumericLiteralIsAParserError]==] [==[ParserRobustnessTest.NonAsciiInputDoesNotCrash]==] [==[ParserRobustnessTest.EveryFailureThroughResolveIsContained]==] [==[ParserRobustnessTest.ShortHexColorLiteralIsAParserError]==] [==[ParserRobustnessTest.TwoDigitHexColorLiteralIsAParserError]==] [==[ParserRobustnessTest.BareHashIsAParserError]==] [==[ParserRobustnessTest.FullLengthHexColorLiteralStillParses]==] [==[ParameterManagerTest.BasicParameterResolution]==] [==[ParameterManagerTest.ParameterReferences]==] [==[ParameterManagerTest.Caching]==] [==[ParameterManagerTest.CacheInvalidation]==] [==[ParameterManagerTest.SourcePriority]==] [==[ParameterManagerTest.ParameterListing]==] [==[ParameterManagerTest.ExpressionRetrieval]==] [==[ParameterManagerTest.ParameterRetrieval]==] [==[ParameterManagerTest.SourceManagement]==] [==[ParameterManagerTest.CircularReferenceDetection]==] [==[ParameterManagerTest.ComplexExpressions]==] [==[ParameterManagerTest.ErrorHandling]==] [==[ParameterManagerTest.ResolveParameterDefinition]==] [==[ParameterManagerTest.ResolveParameterDefinitionDefault]==] [==[ParameterManagerTest.QssFormattingNumeric]==] [==[ParameterManagerTest.QssFormattingColor]==] [==[ParameterManagerTest.QssFormattingGenericTuple]==] [==[ParameterManagerTest.QssFormattingInsetsTuple]==] [==[ParameterManagerTest.InlineExpressionSimple]==] [==[ParameterManagerTest.InlineExpressionFunctionCall]==] [==[ParameterManagerTest.InlineExpressionWithParameterReference]==] [==[ParameterManagerTest.InlineExpressionArithmetic]==] [==[ParameterManagerTest.InlineExpressionMixedWithToken]==] [==[ParameterManagerTest.InlineExpressionInvalidLogsWarning]==] [==[ParameterManagerTest.InlineExpressionMultiple]==] [==[ParameterManagerTest.ExistingTokenUsesToQss]==] [==[ParameterManagerTest.QssFormattingLinearGradient]==] [==[ParameterManagerTest.QssFormattingLinearGradientCustomGeometry]==] [==[ParameterManagerTest.QssFormattingRadialGradient]==] [==[ParameterManagerTest.QssFormattingKeepsStopAlpha]==] [==[ParameterManagerTest.QssFormattingKeepsColorAlpha]==] [==[ParameterManagerTest.QssFormattingMalformedGradientStaysTransparent]==] [==[ParameterManagerTest.ResolvePaddingCoercesEveryEquivalentTokenShape]==] [==[ParameterManagerTest.ResolveDefinitionFallsBackWhenTokenHasWrongShape]==] [==[ParameterManagerTest.ResolveDefinitionOfVariantTypeStillWorks]==] [==[ParameterManagerTest.ReloadClearsDiagnosticState]==] [==[ParameterManagerTest.EvaluateWrapsNonBaseExceptionsAsExpressionError]==] [==[ParameterManagerTest.ReplacePlaceholdersAbsorbsNonBaseExceptions]==] [==[ParameterManagerTest.ReplacePlaceholdersAbsorbsThrowingParameterSource]==] [==[ParameterManagerTest.ResolveAbsorbsThrowingParameterSource]==] [==[ParameterManagerTest.ResolveDefinitionAbsorbsThrowingParameterSource]==] [==[ParameterManagerTest.ResolveAbsorbsThrowFromCyclicFallback]==] [==[ParameterManagerTest.ResolveReportsAreAttributedToTheToken]==] [==[ParameterManagerTest.SameDefectInTwoTokensProducesTwoDistinctMessages]==] [==[ParameterManagerTest.CircularReferenceReportsThroughDiagnostics]==] [==[ParameterManagerTest.UnknownTokenIsDroppedAndNeighboursStillResolve]==] [==[ParameterManagerTest.FailingInlineExpressionIsDroppedAndNeighboursStillResolve]==] [==[ParameterManagerTest.TokenThatFailsToEvaluateSubstitutesItsLiteralText]==] [==[YamlParameterSourceTest.ScalarStringIsLoadedAsExpression]==] [==[YamlParameterSourceTest.ScalarColorIsLoadedAsExpression]==] [==[YamlParameterSourceTest.SequenceBecomesUnnamedTupleExpression]==] [==[YamlParameterSourceTest.BlockSequenceBecomesUnnamedTupleExpression]==] [==[YamlParameterSourceTest.MapBecomesNamedTupleExpression]==] [==[YamlParameterSourceTest.NestedSequenceBecomesNestedTuple]==] [==[YamlParameterSourceTest.SequenceResolvesToTupleValue]==] [==[YamlParameterSourceTest.MapResolvesToNamedTupleValue]==] [==[YamlParameterSourceTest.MixedFileLoadsAllParameters]==] [==[YamlParameterSourceTest.FlushAndReloadPreservesSequenceValue]==] [==[DiagnosticsTest.DeliversFormattedMessageToObserver]==] [==[DiagnosticsTest.DropsExactRepeats]==] [==[DiagnosticsTest.ClearAllowsMessageAgain]==] [==[DiagnosticsTest.ObserverStopsReceivingAfterSubscriptionEnds]==] [==[DiagnosticsTest.SupportsMultipleSimultaneousObservers]==] [==[DiagnosticsTest.ThrowingObserverDoesNotPreventOthersFromReceiving]==] [==[DiagnosticsTest.NoActiveResolutionScopeMeansNoPrefix]==] [==[DiagnosticsTest.ResolutionScopePrefixesTheTokenName]==] [==[DiagnosticsTest.SameDefectUnderTwoScopesProducesTwoDistinctMessages]==] [==[DiagnosticsTest.NestedResolutionScopeReportsTheInnermostToken]==] [==[ValueAccessTest.StyleDefaultsAreEmptyValues]==] [==[ValueAccessTest.ValueGetWrongTypeReturnsDefaultAndReports]==] [==[ValueAccessTest.ValueGetWithFallbackReturnsFallback]==] [==[ValueAccessTest.ValueTryGetReturnsNullOnMismatchAndReportsNothing]==] [==[ValueAccessTest.TupleGetMissingNameReturnsDefaultAndReports]==] [==[ValueAccessTest.TupleGetWrongTypeReturnsDefaultAndReports]==] [==[ValueAccessTest.TupleGetWithFallbackReturnsFallback]==] [==[ValueAccessTest.TupleAtOutOfRangeReturnsDefaultAndReports]==] [==[ValueAccessTest.ShadesWithNonNumericSpecIsContainedByResolve]==] [==[ValueAccessTest.BlendWithNonColorOperandIsContainedByResolve]==] [==[EdgesTest.PaddingFromColorDegradesToZeroAndReports]==] [==[EdgesTest.PaddingTryFromColorReturnsNullopt]==] [==[EdgesTest.PaddingFromBorderColorsDegradesToZero]==] [==[EdgesTest.PaddingFromNumericExpandsToAllSides]==] [==[EdgesTest.BorderColorsFromColorExpandsToAllSides]==] [==[EdgesTest.TooManyPositionalArgumentsDegradesToZero]==] [==[EdgesTest.PaddingAcceptsAnExistingPaddingTuple]==] [==[EdgesTest.InsetsAcceptAnyEdgeKind]==] [==[EdgesTest.PaddingOfNestedBorderColorsArgumentDegradesToZero]==] [==[EdgesTest.PaddingTryFromCornersReturnsNulloptWithMessage]==] [==[EdgesTest.InsetsTryFromLinearGradientReturnsNullopt]==] [==[EdgesTest.PaddingFromCornersDegradesToZeroAndReports]==] [==[EdgesTest.PaddingFromMarginsTupleCoerces]==] [==[CornersTest.FromColorDegradesToZeroAndReports]==] [==[CornersTest.TryFromColorReturnsNullopt]==] [==[CornersTest.DiagonalPairingForTwoValues]==] [==[CornersTest.TooManyPositionalArgumentsDegradesToZero]==] [==[CornersTest.RejectsAPaddingTuple]==] [==[CornersTest.RawArgumentTupleFromColorDegradesToZeroAndReports]==] [==[GradientTest.TooFewStopsDegradesToTransparentAndReports]==] [==[GradientTest.TryFromTooFewStopsReturnsNullopt]==] [==[GradientTest.KindMismatchDegradesAndReports]==] [==[GradientTest.NonNumericGeometryParameterDegradesAndReports]==] [==[GradientTest.WellFormedGradientRoundTrips]==] [==[GradientTest.MalformedKindTaggedTupleNeverProducesIllFormedWrapperThroughAnyRoute]==] [==[ColorShadingTest.AnchorReturnsUnchanged]==] [==[ColorShadingTest.MonotonicDecrease]==] [==[ColorShadingTest.SymmetricRangeIsLinear]==] [==[ColorShadingTest.ClampedRangeRespectsMinMax]==] [==[ColorShadingTest.NarrowRangeProducesLessVariation]==] [==[ColorShadingTest.ExtremeLightnessIsHandled]==] [==[ColorShadingTest.ChromaScalesWithGamutBoundary]==] [==[ColorShadingTest.LighterShadesReduceChroma]==] [==[ColorShadingTest.BlackAnchorProducesZeroChroma]==] [==[ColorShadingTest.WhiteAnchorProducesZeroChroma]==] [==[ColorShadingTest.GrayStaysNeutral]==] [==[ColorShadingTest.HueIsPreserved]==] [==[ColorShadingTest.ExtremePivotsProduceFiniteShades]==] [==[ColorShadingTest.MaxLightnessAboveOneIsClamped]==] [==[ColorShadingTest.InvertedBoundsPreserveLightToDarkDirection]==] [==[ColorShadingTest.OutOfRangePositionSaturatesAtTheCurveEnds]==] [==[InputHintTest.LookupHintsSimpleState]==] [==[InputHintTest.LookupHintsPairState]==] [==[ViewProviderDoubleClick.LegacyCallbackRunsOnce]==] [==[ViewProviderDoubleClick.LegacyRejectionIsPreserved]==] [==[ViewProviderDoubleClick.ExplicitRejectionDoesNotFallBackToLegacyCallback]==] [==[ViewProviderDoubleClick.UnhandledOccurrenceUsesLegacyCallbackOnce]==] [==[ViewProviderDoubleClick.KeepsTheCallersOccurrencePath]==] [==[DefaultEditReference.UsesModelContainersInsteadOfIncomingLinks]==] [==[DefaultEditReference.IncludesLinkGroupContainers]==] [==[DefaultEditReference.IncomingLinkDoesNotReplaceTopLevelObject]==] [==[NativeGesturePinch.zoomWithoutBeginIsRejected]==] [==[NativeGesturePinch.beginActivatesAndRecordsCenter]==] [==[NativeGesturePinch.zoomKeepsTheStartCenterFromBegin]==] [==[NativeGesturePinch.nonPositiveZoomValueIsClampedToNeutral]==] [==[NativeGesturePinch.rotateConvertsDegreesToRadiansAndInvertsDirection]==] [==[NativeGesturePinch.endDeactivatesAndFurtherUpdatesAreRejected]==] [==[NativeGesturePinch.unhandledGestureTypeIsRejectedWithoutDisturbingState]==] [==[NativeGesturePinch.aSecondGestureResetsTheStartCenter]==] [==[NavigationStylePinchAction.onlyUpdateEventsMoveTheCamera]==] [==[NavigationStylePinchAction.aRotateOnlyEventDoesNotZoom]==] [==[NavigationStylePinchAction.aZoomOnlyEventDoesNotRotate]==] [==[NavigationStylePinchAction.aNegativeZoomFactorIsIgnored]==] [==[NavigationStylePinchAction.pinchingOutZoomsIn]==] [==[NavigationStylePinchAction.pinchingInZoomsOutBySymmetricAmount]==] [==[NavigationStylePinchAction.aTouchscreenPinchObeysTheTiltPreference]==] [==[NavigationStylePinchAction.aTrackpadRotateIsNotBlockedByTheTouchscreenTiltPreference]==] [==[NavigationStyleWheelAction.anOrdinaryWheelZoomsWhateverThePreferenceSays]==] [==[NavigationStyleWheelAction.aTouchpadZoomsWhenScrollPanningIsOff]==] [==[NavigationStyleWheelAction.aTouchpadPansWhenScrollPanningIsOn]==] [==[NavigationStyleWheelAction.shiftOrbitsInsteadOfPanning]==] [==[NavigationStyleWheelAction.ctrlZoomsEvenWhileScrollPanningIsOn]==] [==[NavigationStyleWheelAction.ctrlWinsOverShift]==] [==[NavigationStyleWheelAction.modifiersNeverDivertAnOrdinaryWheelFromZooming]==] [==[SelectionTest.testSelectionAllowsObjectsWhenNoGateIsInstalled]==] [==[SelectionTest.testSelectionUsesActiveGateWithoutKeepingRejectionReason]==] [==[SelectionPickPolicyTest.canFinalizeSinglePickWhenNoGateIsInstalled]==] [==[SelectionPickPolicyTest.continuesSinglePickWhenGateRejectedAllCurrentCandidates]==] [==[SelectionPickPolicyTest.choosesAllowedCandidateWhenPreferredPickIsRejected]==] [==[SelectionPickPolicyTest.preservesPriorityChoiceWithinFirstOwner]==] [==[SelectionPickPolicyTest.keepsPreferredPickWhenNoCandidatePassesGate]==] [==[SoMouseWheelEvent.toGlPixelDeltaScalesByDevicePixelRatioAndFlipsY]==] [==[SoMouseWheelEvent.onlyAScrollWithAPhaseAndPixelDeltaIsPrecise]==])
