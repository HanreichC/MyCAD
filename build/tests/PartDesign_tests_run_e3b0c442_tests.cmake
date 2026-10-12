add_test([=[BackwardCompatibilityTest.TestOpenV021Model]=]  /workspace/build/tests/PartDesign_tests_run [==[--gtest_filter=BackwardCompatibilityTest.TestOpenV021Model]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BackwardCompatibilityTest.TestOpenV021Model]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/PartDesign/App/BackwardCompatibility.cpp:56]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BackwardCompatibilityTest.TestTwoLengthsPadWithExpression]=]  /workspace/build/tests/PartDesign_tests_run [==[--gtest_filter=BackwardCompatibilityTest.TestTwoLengthsPadWithExpression]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BackwardCompatibilityTest.TestTwoLengthsPadWithExpression]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/PartDesign/App/BackwardCompatibility.cpp:132]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BackwardCompatibilityTest.TestTwoLengthsPadCyclicExpression]=]  /workspace/build/tests/PartDesign_tests_run [==[--gtest_filter=BackwardCompatibilityTest.TestTwoLengthsPadCyclicExpression]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BackwardCompatibilityTest.TestTwoLengthsPadCyclicExpression]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/PartDesign/App/BackwardCompatibility.cpp:163]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BackwardCompatibilityTest.TestTwoLengthsPadCrossObjectRefExpression]=]  /workspace/build/tests/PartDesign_tests_run [==[--gtest_filter=BackwardCompatibilityTest.TestTwoLengthsPadCrossObjectRefExpression]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BackwardCompatibilityTest.TestTwoLengthsPadCrossObjectRefExpression]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/PartDesign/App/BackwardCompatibility.cpp:193]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DatumPlaneTest.attachDatumPlane]=]  /workspace/build/tests/PartDesign_tests_run [==[--gtest_filter=DatumPlaneTest.attachDatumPlane]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DatumPlaneTest.attachDatumPlane]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/PartDesign/App/DatumPlane.cpp:49]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ShapeBinderTest.shapeBinderExists]=]  /workspace/build/tests/PartDesign_tests_run [==[--gtest_filter=ShapeBinderTest.shapeBinderExists]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ShapeBinderTest.shapeBinderExists]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/PartDesign/App/ShapeBinder.cpp:61]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ShapeBinderTest.subShapeBinderExists]=]  /workspace/build/tests/PartDesign_tests_run [==[--gtest_filter=ShapeBinderTest.subShapeBinderExists]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ShapeBinderTest.subShapeBinderExists]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/PartDesign/App/ShapeBinder.cpp:71]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PadTest.TestMidPlaneTwoLength]=]  /workspace/build/tests/PartDesign_tests_run [==[--gtest_filter=PadTest.TestMidPlaneTwoLength]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PadTest.TestMidPlaneTwoLength]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/PartDesign/App/Pad.cpp:63]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePipeTest.SketchProfileSketchSpine]=]  /workspace/build/tests/PartDesign_tests_run [==[--gtest_filter=FeaturePipeTest.SketchProfileSketchSpine]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePipeTest.SketchProfileSketchSpine]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/PartDesign/App/Pipe.cpp:183]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePipeTest.SketchProfileBinderSpine]=]  /workspace/build/tests/PartDesign_tests_run [==[--gtest_filter=FeaturePipeTest.SketchProfileBinderSpine]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePipeTest.SketchProfileBinderSpine]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/PartDesign/App/Pipe.cpp:203]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePipeTest.BinderProfileSketchSpine]=]  /workspace/build/tests/PartDesign_tests_run [==[--gtest_filter=FeaturePipeTest.BinderProfileSketchSpine]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePipeTest.BinderProfileSketchSpine]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/PartDesign/App/Pipe.cpp:227]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePipeTest.BinderProfileBinderSpine]=]  /workspace/build/tests/PartDesign_tests_run [==[--gtest_filter=FeaturePipeTest.BinderProfileBinderSpine]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePipeTest.BinderProfileBinderSpine]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/PartDesign/App/Pipe.cpp:250]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[RevolutionTest.TwoSidesAngles]=]  /workspace/build/tests/PartDesign_tests_run [==[--gtest_filter=RevolutionTest.TwoSidesAngles]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RevolutionTest.TwoSidesAngles]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/PartDesign/App/Revolution.cpp:168]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[RevolutionTest.TwoSidesSignedAngles]=]  /workspace/build/tests/PartDesign_tests_run [==[--gtest_filter=RevolutionTest.TwoSidesSignedAngles]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RevolutionTest.TwoSidesSignedAngles]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/PartDesign/App/Revolution.cpp:193]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[RevolutionTest.TwoSidesOverlappingAngles]=]  /workspace/build/tests/PartDesign_tests_run [==[--gtest_filter=RevolutionTest.TwoSidesOverlappingAngles]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RevolutionTest.TwoSidesOverlappingAngles]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/PartDesign/App/Revolution.cpp:212]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[RevolutionTest.SymmetricAngle]=]  /workspace/build/tests/PartDesign_tests_run [==[--gtest_filter=RevolutionTest.SymmetricAngle]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RevolutionTest.SymmetricAngle]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/PartDesign/App/Revolution.cpp:230]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[RevolutionTest.MidplaneMapsToSideType]=]  /workspace/build/tests/PartDesign_tests_run [==[--gtest_filter=RevolutionTest.MidplaneMapsToSideType]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RevolutionTest.MidplaneMapsToSideType]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/PartDesign/App/Revolution.cpp:250]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[RevolutionTest.GrooveTwoSidesThroughAll]=]  /workspace/build/tests/PartDesign_tests_run [==[--gtest_filter=RevolutionTest.GrooveTwoSidesThroughAll]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RevolutionTest.GrooveTwoSidesThroughAll]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/PartDesign/App/Revolution.cpp:264]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[RevolutionTest.GrooveStartOffset]=]  /workspace/build/tests/PartDesign_tests_run [==[--gtest_filter=RevolutionTest.GrooveStartOffset]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RevolutionTest.GrooveStartOffset]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/PartDesign/App/Revolution.cpp:293]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[RevolutionTest.SecondSideUpToFaceWithoutTargetIsAnError]=]  /workspace/build/tests/PartDesign_tests_run [==[--gtest_filter=RevolutionTest.SecondSideUpToFaceWithoutTargetIsAnError]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RevolutionTest.SecondSideUpToFaceWithoutTargetIsAnError]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/PartDesign/App/Revolution.cpp:315]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[RevolutionTest.ProjectOffsetAxisAndRestoreOriginalAxis]=]  /workspace/build/tests/PartDesign_tests_run [==[--gtest_filter=RevolutionTest.ProjectOffsetAxisAndRestoreOriginalAxis]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RevolutionTest.ProjectOffsetAxisAndRestoreOriginalAxis]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/PartDesign/App/Revolution.cpp:327]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[RevolutionTest.ProjectAxisRespectsNestedBodyPlacements]=]  /workspace/build/tests/PartDesign_tests_run [==[--gtest_filter=RevolutionTest.ProjectAxisRespectsNestedBodyPlacements]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RevolutionTest.ProjectAxisRespectsNestedBodyPlacements]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/PartDesign/App/Revolution.cpp:350]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[RevolutionTest.ProjectTiltedAxisOntoRotatedProfile]=]  /workspace/build/tests/PartDesign_tests_run [==[--gtest_filter=RevolutionTest.ProjectTiltedAxisOntoRotatedProfile]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RevolutionTest.ProjectTiltedAxisOntoRotatedProfile]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/PartDesign/App/Revolution.cpp:374]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[RevolutionTest.ProjectAxisOntoSelectedFacePlane]=]  /workspace/build/tests/PartDesign_tests_run [==[--gtest_filter=RevolutionTest.ProjectAxisOntoSelectedFacePlane]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RevolutionTest.ProjectAxisOntoSelectedFacePlane]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/PartDesign/App/Revolution.cpp:401]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[RevolutionTest.ProjectPerpendicularAxisIsAnError]=]  /workspace/build/tests/PartDesign_tests_run [==[--gtest_filter=RevolutionTest.ProjectPerpendicularAxisIsAnError]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RevolutionTest.ProjectPerpendicularAxisIsAnError]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/PartDesign/App/Revolution.cpp:419]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[RevolutionTest.GrooveProjectAxis]=]  /workspace/build/tests/PartDesign_tests_run [==[--gtest_filter=RevolutionTest.GrooveProjectAxis]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RevolutionTest.GrooveProjectAxis]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/PartDesign/App/Revolution.cpp:435]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[GeoFeatureGroupTest.testDocumentObjectGroupAcceptsBoolean]=]  /workspace/build/tests/PartDesign_tests_run [==[--gtest_filter=GeoFeatureGroupTest.testDocumentObjectGroupAcceptsBoolean]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[GeoFeatureGroupTest.testDocumentObjectGroupAcceptsBoolean]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/PartDesign/App/GeoFeatureGroupExtension.cpp:116]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[GeoFeatureGroupTest.testIsLinkValidCrossFailure]=]  /workspace/build/tests/PartDesign_tests_run [==[--gtest_filter=GeoFeatureGroupTest.testIsLinkValidCrossFailure]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[GeoFeatureGroupTest.testIsLinkValidCrossFailure]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/PartDesign/App/GeoFeatureGroupExtension.cpp:161]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
set(PartDesign_tests_run_TESTS [==[BackwardCompatibilityTest.TestOpenV021Model]==] [==[BackwardCompatibilityTest.TestTwoLengthsPadWithExpression]==] [==[BackwardCompatibilityTest.TestTwoLengthsPadCyclicExpression]==] [==[BackwardCompatibilityTest.TestTwoLengthsPadCrossObjectRefExpression]==] [==[DatumPlaneTest.attachDatumPlane]==] [==[ShapeBinderTest.shapeBinderExists]==] [==[ShapeBinderTest.subShapeBinderExists]==] [==[PadTest.TestMidPlaneTwoLength]==] [==[FeaturePipeTest.SketchProfileSketchSpine]==] [==[FeaturePipeTest.SketchProfileBinderSpine]==] [==[FeaturePipeTest.BinderProfileSketchSpine]==] [==[FeaturePipeTest.BinderProfileBinderSpine]==] [==[RevolutionTest.TwoSidesAngles]==] [==[RevolutionTest.TwoSidesSignedAngles]==] [==[RevolutionTest.TwoSidesOverlappingAngles]==] [==[RevolutionTest.SymmetricAngle]==] [==[RevolutionTest.MidplaneMapsToSideType]==] [==[RevolutionTest.GrooveTwoSidesThroughAll]==] [==[RevolutionTest.GrooveStartOffset]==] [==[RevolutionTest.SecondSideUpToFaceWithoutTargetIsAnError]==] [==[RevolutionTest.ProjectOffsetAxisAndRestoreOriginalAxis]==] [==[RevolutionTest.ProjectAxisRespectsNestedBodyPlacements]==] [==[RevolutionTest.ProjectTiltedAxisOntoRotatedProfile]==] [==[RevolutionTest.ProjectAxisOntoSelectedFacePlane]==] [==[RevolutionTest.ProjectPerpendicularAxisIsAnError]==] [==[RevolutionTest.GrooveProjectAxis]==] [==[GeoFeatureGroupTest.testDocumentObjectGroupAcceptsBoolean]==] [==[GeoFeatureGroupTest.testIsLinkValidCrossFailure]==])
