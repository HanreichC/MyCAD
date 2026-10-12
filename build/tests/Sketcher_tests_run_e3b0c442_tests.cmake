add_test([=[ConstraintPointsAccess.testDefaultGeoElementIdsAreSane]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=ConstraintPointsAccess.testDefaultGeoElementIdsAreSane]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ConstraintPointsAccess.testDefaultGeoElementIdsAreSane]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/Constraint.cpp:48]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ConstraintPointsAccess.testOldWriteIsReadByNew]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=ConstraintPointsAccess.testOldWriteIsReadByNew]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ConstraintPointsAccess.testOldWriteIsReadByNew]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/Constraint.cpp:84]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ConstraintPointsAccess.testNewWriteIsReadByOld]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=ConstraintPointsAccess.testNewWriteIsReadByOld]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ConstraintPointsAccess.testNewWriteIsReadByOld]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/Constraint.cpp:112]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ConstraintPointsAccess.testThreeElementsByDefault]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=ConstraintPointsAccess.testThreeElementsByDefault]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ConstraintPointsAccess.testThreeElementsByDefault]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/Constraint.cpp:132]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ConstraintPointsAccess.testFourElementsWhenAddingOne]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=ConstraintPointsAccess.testFourElementsWhenAddingOne]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ConstraintPointsAccess.testFourElementsWhenAddingOne]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/Constraint.cpp:143]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ConstraintPointsAccess.testElementSerializationWhenAccessingOldWay]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=ConstraintPointsAccess.testElementSerializationWhenAccessingOldWay]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ConstraintPointsAccess.testElementSerializationWhenAccessingOldWay]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/Constraint.cpp:156]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ConstraintPointsAccess.testElementSerializationWhenAccessingNewWay]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=ConstraintPointsAccess.testElementSerializationWhenAccessingNewWay]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ConstraintPointsAccess.testElementSerializationWhenAccessingNewWay]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/Constraint.cpp:185]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ConstraintPointsAccess.testElementSerializationWhenMixingOldAndNew]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=ConstraintPointsAccess.testElementSerializationWhenMixingOldAndNew]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ConstraintPointsAccess.testElementSerializationWhenMixingOldAndNew]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/Constraint.cpp:211]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ConstraintPointsAccess.testElementsRestoredFromSerialization]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=ConstraintPointsAccess.testElementsRestoredFromSerialization]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ConstraintPointsAccess.testElementsRestoredFromSerialization]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/Constraint.cpp:245]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ConstraintPointsAccess.testElementsRestoredFromSerializationWithoutNewElementStorage]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=ConstraintPointsAccess.testElementsRestoredFromSerializationWithoutNewElementStorage]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ConstraintPointsAccess.testElementsRestoredFromSerializationWithoutNewElementStorage]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/Constraint.cpp:282]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ConstraintPointsAccess.testLegacyIsPreferedDuringSerializationWithoutLegacyElementStorage]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=ConstraintPointsAccess.testLegacyIsPreferedDuringSerializationWithoutLegacyElementStorage]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ConstraintPointsAccess.testLegacyIsPreferedDuringSerializationWithoutLegacyElementStorage]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/Constraint.cpp:349]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ConstraintPointsAccess.testLegacyIsPreferedDuringSerializationIfContradicting]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=ConstraintPointsAccess.testLegacyIsPreferedDuringSerializationIfContradicting]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ConstraintPointsAccess.testLegacyIsPreferedDuringSerializationIfContradicting]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/Constraint.cpp:413]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ConstraintPointsAccess.testSubstituteIndex]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=ConstraintPointsAccess.testSubstituteIndex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ConstraintPointsAccess.testSubstituteIndex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/Constraint.cpp:490]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ConstraintPointsAccess.testSubstituteIndexAndPos]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=ConstraintPointsAccess.testSubstituteIndexAndPos]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ConstraintPointsAccess.testSubstituteIndexAndPos]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/Constraint.cpp:507]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ConstraintPointsAccess.testInvolvesGeoId]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=ConstraintPointsAccess.testInvolvesGeoId]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ConstraintPointsAccess.testInvolvesGeoId]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/Constraint.cpp:524]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ConstraintPointsAccess.testInvolvesGeoIdAndPosId]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=ConstraintPointsAccess.testInvolvesGeoIdAndPosId]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ConstraintPointsAccess.testInvolvesGeoIdAndPosId]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/Constraint.cpp:537]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ConstraintPointsAccess.testLegacyWriteReflectedInInvolvesAndSubstitute]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=ConstraintPointsAccess.testLegacyWriteReflectedInInvolvesAndSubstitute]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ConstraintPointsAccess.testLegacyWriteReflectedInInvolvesAndSubstitute]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/Constraint.cpp:553]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ConstraintPointsAccess.testSubstituteUpdatesLegacyFieldsToo]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=ConstraintPointsAccess.testSubstituteUpdatesLegacyFieldsToo]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ConstraintPointsAccess.testSubstituteUpdatesLegacyFieldsToo]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/Constraint.cpp:574]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.createSketchObject]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.createSketchObject]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.createSketchObject]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:16]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testGeoIdFromShapeTypeEdge]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testGeoIdFromShapeTypeEdge]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testGeoIdFromShapeTypeEdge]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:25]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testGeoIdFromShapeTypeVertex]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testGeoIdFromShapeTypeVertex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testGeoIdFromShapeTypeVertex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:42]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testGeoIdFromShapeTypeExternalEdge]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testGeoIdFromShapeTypeExternalEdge]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testGeoIdFromShapeTypeExternalEdge]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:64]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testGeoIdFromShapeTypeHAxis]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testGeoIdFromShapeTypeHAxis]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testGeoIdFromShapeTypeHAxis]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:81]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testGeoIdFromShapeTypeVAxis]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testGeoIdFromShapeTypeVAxis]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testGeoIdFromShapeTypeVAxis]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:96]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testGeoIdFromShapeTypeRootPoint]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testGeoIdFromShapeTypeRootPoint]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testGeoIdFromShapeTypeRootPoint]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:111]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testGetPointFromGeomPoint]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testGetPointFromGeomPoint]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testGetPointFromGeomPoint]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:126]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testGetPointFromGeomLineSegment]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testGetPointFromGeomLineSegment]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testGetPointFromGeomLineSegment]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:148]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testGetPointFromGeomCircle]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testGetPointFromGeomCircle]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testGetPointFromGeomCircle]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:171]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testGetPointFromGeomEllipse]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testGetPointFromGeomEllipse]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testGetPointFromGeomEllipse]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:200]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testGetPointFromGeomArcOfCircle]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testGetPointFromGeomArcOfCircle]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testGetPointFromGeomArcOfCircle]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:231]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testGetPointFromGeomArcOfEllipse]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testGetPointFromGeomArcOfEllipse]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testGetPointFromGeomArcOfEllipse]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:259]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testGetPointFromGeomArcOfHyperbola]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testGetPointFromGeomArcOfHyperbola]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testGetPointFromGeomArcOfHyperbola]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:290]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testGetPointFromGeomArcOfParabola]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testGetPointFromGeomArcOfParabola]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testGetPointFromGeomArcOfParabola]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:323]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testGetPointFromGeomBSplineCurveNonPeriodic]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testGetPointFromGeomBSplineCurveNonPeriodic]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testGetPointFromGeomBSplineCurveNonPeriodic]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:354]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testGetPointFromGeomBSplineCurvePeriodic]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testGetPointFromGeomBSplineCurvePeriodic]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testGetPointFromGeomBSplineCurvePeriodic]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:387]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testConstraintAfterDeletingGeo]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testConstraintAfterDeletingGeo]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testConstraintAfterDeletingGeo]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:422]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testDeleteExposeInternalGeometryOfEllipse]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testDeleteExposeInternalGeometryOfEllipse]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testDeleteExposeInternalGeometryOfEllipse]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:491]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testDeleteExposeInternalGeometryOfHyperbola]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testDeleteExposeInternalGeometryOfHyperbola]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testDeleteExposeInternalGeometryOfHyperbola]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:539]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testDeleteExposeInternalGeometryOfParabola]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testDeleteExposeInternalGeometryOfParabola]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testDeleteExposeInternalGeometryOfParabola]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:586]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testDeleteExposeInternalGeometryOfBSpline]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testDeleteExposeInternalGeometryOfBSpline]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testDeleteExposeInternalGeometryOfBSpline]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:632]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testDeleteOnlyUnusedInternalGeometryOfBSpline]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testDeleteOnlyUnusedInternalGeometryOfBSpline]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testDeleteOnlyUnusedInternalGeometryOfBSpline]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:689]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionNoUnits1]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionNoUnits1]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionNoUnits1]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:735]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionNoUnits2]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionNoUnits2]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionNoUnits2]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:742]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionWithUnits1]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionWithUnits1]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionWithUnits1]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:749]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionWithUnits2]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionWithUnits2]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionWithUnits2]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:756]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionWithUnits3]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionWithUnits3]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionWithUnits3]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:763]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionWithUnits4]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionWithUnits4]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionWithUnits4]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:770]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionApplyAndReverse1]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionApplyAndReverse1]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionApplyAndReverse1]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:777]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionApplyAndReverse2]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionApplyAndReverse2]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionApplyAndReverse2]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:785]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionSimple]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionSimple]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionSimple]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:795]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionApplyAndReverse]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionApplyAndReverse]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionApplyAndReverse]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:802]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionFunction]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionFunction]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionFunction]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:810]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testGetElementName]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testGetElementName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testGetElementName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObject.cpp:820]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testAddExternalIncreasesCount]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testAddExternalIncreasesCount]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testAddExternalIncreasesCount]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:18]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testDelExternalUndef]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testDelExternalUndef]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testDelExternalUndef]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:34]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testDelExternalWhenEmpty]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testDelExternalWhenEmpty]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testDelExternalWhenEmpty]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:43]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testDelExternalWhenEmptyWithPositiveId]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testDelExternalWhenEmptyWithPositiveId]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testDelExternalWhenEmptyWithPositiveId]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:52]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testDelExternalReducesCount]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testDelExternalReducesCount]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testDelExternalReducesCount]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:61]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testReplaceGeometriesOneToOne]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testReplaceGeometriesOneToOne]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testReplaceGeometriesOneToOne]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:91]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testReplaceGeometriesTwoToOne]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testReplaceGeometriesTwoToOne]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testReplaceGeometriesTwoToOne]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:108]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testReplaceGeometriesOneToTwo]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testReplaceGeometriesOneToTwo]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testReplaceGeometriesOneToTwo]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:129]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testSplitLineSegment]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testSplitLineSegment]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testSplitLineSegment]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:160]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testSplitCircle]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testSplitCircle]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testSplitCircle]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:189]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testSplitEllipse]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testSplitEllipse]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testSplitEllipse]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:215]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testSplitArcOfCircle]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testSplitArcOfCircle]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testSplitArcOfCircle]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:242]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testSplitArcOfConic]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testSplitArcOfConic]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testSplitArcOfConic]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:271]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testSplitNonPeriodicBSpline]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testSplitNonPeriodicBSpline]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testSplitNonPeriodicBSpline]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:305]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testSplitPeriodicBSpline]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testSplitPeriodicBSpline]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testSplitPeriodicBSpline]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:337]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testTrimWithoutIntersection]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testTrimWithoutIntersection]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testTrimWithoutIntersection]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:367]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testTrimLineSegmentEnd]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testTrimLineSegmentEnd]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testTrimLineSegmentEnd]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:395]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testTrimLineSegmentMid]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testTrimLineSegmentMid]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testTrimLineSegmentMid]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:430]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testTrimCircleEnd]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testTrimCircleEnd]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testTrimCircleEnd]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:477]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testTrimCircleMid]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testTrimCircleMid]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testTrimCircleMid]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:509]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testTrimArcOfCircleEnd]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testTrimArcOfCircleEnd]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testTrimArcOfCircleEnd]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:557]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testTrimArcOfCircleMid]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testTrimArcOfCircleMid]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testTrimArcOfCircleMid]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:593]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testTrimEllipseEnd]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testTrimEllipseEnd]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testTrimEllipseEnd]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:641]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testTrimEllipseMid]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testTrimEllipseMid]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testTrimEllipseMid]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:678]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testTrimPeriodicBSplineEnd]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testTrimPeriodicBSplineEnd]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testTrimPeriodicBSplineEnd]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:734]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testTrimPeriodicBSplineMid]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testTrimPeriodicBSplineMid]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testTrimPeriodicBSplineMid]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:769]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testTrimNonPeriodicBSplineEnd]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testTrimNonPeriodicBSplineEnd]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testTrimNonPeriodicBSplineEnd]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:821]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testTrimNonPeriodicBSplineMid]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testTrimNonPeriodicBSplineMid]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testTrimNonPeriodicBSplineMid]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:862]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testTrimEffectOnConstruction]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testTrimEffectOnConstruction]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testTrimEffectOnConstruction]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:915]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testTrimEndEffectOnFullLengthConstraints]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testTrimEndEffectOnFullLengthConstraints]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testTrimEndEffectOnFullLengthConstraints]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:964]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testTrimEndEffectOnSymmetricConstraints]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testTrimEndEffectOnSymmetricConstraints]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testTrimEndEffectOnSymmetricConstraints]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:1008]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testTrimEndEffectOnUnrelatedTangent]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testTrimEndEffectOnUnrelatedTangent]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testTrimEndEffectOnUnrelatedTangent]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:1053]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testModifyKnotMultInNonPeriodicBSplineToZero]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testModifyKnotMultInNonPeriodicBSplineToZero]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testModifyKnotMultInNonPeriodicBSplineToZero]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:1108]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testModifyKnotMultInNonPeriodicBSplineToDisallowed]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testModifyKnotMultInNonPeriodicBSplineToDisallowed]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testModifyKnotMultInNonPeriodicBSplineToDisallowed]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:1127]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testModifyKnotMultInNonPeriodicBSpline]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testModifyKnotMultInNonPeriodicBSpline]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testModifyKnotMultInNonPeriodicBSpline]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:1143]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testModifyKnotMultInPeriodicBSplineToZero]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testModifyKnotMultInPeriodicBSplineToZero]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testModifyKnotMultInPeriodicBSplineToZero]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:1180]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testModifyKnotMultInPeriodicBSplineToDisallowed]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testModifyKnotMultInPeriodicBSplineToDisallowed]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testModifyKnotMultInPeriodicBSplineToDisallowed]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:1199]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testModifyKnotMultInPeriodicBSpline]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testModifyKnotMultInPeriodicBSpline]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testModifyKnotMultInPeriodicBSpline]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:1215]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testInsertKnotInNonPeriodicBSpline]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testInsertKnotInNonPeriodicBSpline]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testInsertKnotInNonPeriodicBSpline]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:1252]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testInsertKnotInPeriodicBSpline]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testInsertKnotInPeriodicBSpline]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testInsertKnotInPeriodicBSpline]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:1303]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testJoinCurves]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testJoinCurves]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testJoinCurves]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:1353]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testJoinCurvesWhenTangent]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testJoinCurvesWhenTangent]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testJoinCurvesWhenTangent]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectChanges.cpp:1384]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testAddSymmetricCopyWithoutConstraints]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testAddSymmetricCopyWithoutConstraints]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testAddSymmetricCopyWithoutConstraints]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectSymmetric.cpp:16]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testAddSymmetricWithConstraintsAddsSymmetric]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testAddSymmetricWithConstraintsAddsSymmetric]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testAddSymmetricWithConstraintsAddsSymmetric]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectSymmetric.cpp:32]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testAddSymmetricPreservesCoincidentTopology]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testAddSymmetricPreservesCoincidentTopology]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testAddSymmetricPreservesCoincidentTopology]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectSymmetric.cpp:45]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testAddSymmetricDowngradesTangentToCoincident]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testAddSymmetricDowngradesTangentToCoincident]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testAddSymmetricDowngradesTangentToCoincident]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectSymmetric.cpp:72]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testAddSymmetricOnAxisPointGetsCoincident]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testAddSymmetricOnAxisPointGetsCoincident]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testAddSymmetricOnAxisPointGetsCoincident]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectSymmetric.cpp:103]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testAddSymmetricOnAxisPointWithLineRef]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testAddSymmetricOnAxisPointWithLineRef]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testAddSymmetricOnAxisPointWithLineRef]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectSymmetric.cpp:118]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testAddSymmetricSharedVertexNoDuplicateConstraints]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testAddSymmetricSharedVertexNoDuplicateConstraints]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testAddSymmetricSharedVertexNoDuplicateConstraints]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectSymmetric.cpp:136]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testAddSymmetricPointSymmetry]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testAddSymmetricPointSymmetry]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testAddSymmetricPointSymmetry]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectSymmetric.cpp:163]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testAddSymmetricPointSymmetryOnPoint]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testAddSymmetricPointSymmetryOnPoint]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testAddSymmetricPointSymmetryOnPoint]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectSymmetric.cpp:177]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SketchObjectTest.testAddSymmetricCircleGetsCenterSymmetricAndEqual]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=SketchObjectTest.testAddSymmetricCircleGetsCenterSymmetricAndEqual]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SketchObjectTest.testAddSymmetricCircleGetsCenterSymmetricAndEqual]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/SketchObjectSymmetric.cpp:190]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[GCSTest.clearConstraints]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=GCSTest.clearConstraints]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[GCSTest.clearConstraints]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/planegcs/GCS.cpp:38]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ConstraintsTest.tangentBSplineAndArc]=]  /workspace/build/tests/Sketcher_tests_run [==[--gtest_filter=ConstraintsTest.tangentBSplineAndArc]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ConstraintsTest.tangentBSplineAndArc]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Sketcher/App/planegcs/Constraints.cpp:43]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
set(Sketcher_tests_run_TESTS [==[ConstraintPointsAccess.testDefaultGeoElementIdsAreSane]==] [==[ConstraintPointsAccess.testOldWriteIsReadByNew]==] [==[ConstraintPointsAccess.testNewWriteIsReadByOld]==] [==[ConstraintPointsAccess.testThreeElementsByDefault]==] [==[ConstraintPointsAccess.testFourElementsWhenAddingOne]==] [==[ConstraintPointsAccess.testElementSerializationWhenAccessingOldWay]==] [==[ConstraintPointsAccess.testElementSerializationWhenAccessingNewWay]==] [==[ConstraintPointsAccess.testElementSerializationWhenMixingOldAndNew]==] [==[ConstraintPointsAccess.testElementsRestoredFromSerialization]==] [==[ConstraintPointsAccess.testElementsRestoredFromSerializationWithoutNewElementStorage]==] [==[ConstraintPointsAccess.testLegacyIsPreferedDuringSerializationWithoutLegacyElementStorage]==] [==[ConstraintPointsAccess.testLegacyIsPreferedDuringSerializationIfContradicting]==] [==[ConstraintPointsAccess.testSubstituteIndex]==] [==[ConstraintPointsAccess.testSubstituteIndexAndPos]==] [==[ConstraintPointsAccess.testInvolvesGeoId]==] [==[ConstraintPointsAccess.testInvolvesGeoIdAndPosId]==] [==[ConstraintPointsAccess.testLegacyWriteReflectedInInvolvesAndSubstitute]==] [==[ConstraintPointsAccess.testSubstituteUpdatesLegacyFieldsToo]==] [==[SketchObjectTest.createSketchObject]==] [==[SketchObjectTest.testGeoIdFromShapeTypeEdge]==] [==[SketchObjectTest.testGeoIdFromShapeTypeVertex]==] [==[SketchObjectTest.testGeoIdFromShapeTypeExternalEdge]==] [==[SketchObjectTest.testGeoIdFromShapeTypeHAxis]==] [==[SketchObjectTest.testGeoIdFromShapeTypeVAxis]==] [==[SketchObjectTest.testGeoIdFromShapeTypeRootPoint]==] [==[SketchObjectTest.testGetPointFromGeomPoint]==] [==[SketchObjectTest.testGetPointFromGeomLineSegment]==] [==[SketchObjectTest.testGetPointFromGeomCircle]==] [==[SketchObjectTest.testGetPointFromGeomEllipse]==] [==[SketchObjectTest.testGetPointFromGeomArcOfCircle]==] [==[SketchObjectTest.testGetPointFromGeomArcOfEllipse]==] [==[SketchObjectTest.testGetPointFromGeomArcOfHyperbola]==] [==[SketchObjectTest.testGetPointFromGeomArcOfParabola]==] [==[SketchObjectTest.testGetPointFromGeomBSplineCurveNonPeriodic]==] [==[SketchObjectTest.testGetPointFromGeomBSplineCurvePeriodic]==] [==[SketchObjectTest.testConstraintAfterDeletingGeo]==] [==[SketchObjectTest.testDeleteExposeInternalGeometryOfEllipse]==] [==[SketchObjectTest.testDeleteExposeInternalGeometryOfHyperbola]==] [==[SketchObjectTest.testDeleteExposeInternalGeometryOfParabola]==] [==[SketchObjectTest.testDeleteExposeInternalGeometryOfBSpline]==] [==[SketchObjectTest.testDeleteOnlyUnusedInternalGeometryOfBSpline]==] [==[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionNoUnits1]==] [==[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionNoUnits2]==] [==[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionWithUnits1]==] [==[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionWithUnits2]==] [==[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionWithUnits3]==] [==[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionWithUnits4]==] [==[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionApplyAndReverse1]==] [==[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionApplyAndReverse2]==] [==[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionSimple]==] [==[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionApplyAndReverse]==] [==[SketchObjectTest.testReverseAngleConstraintToSupplementaryExpressionFunction]==] [==[SketchObjectTest.testGetElementName]==] [==[SketchObjectTest.testAddExternalIncreasesCount]==] [==[SketchObjectTest.testDelExternalUndef]==] [==[SketchObjectTest.testDelExternalWhenEmpty]==] [==[SketchObjectTest.testDelExternalWhenEmptyWithPositiveId]==] [==[SketchObjectTest.testDelExternalReducesCount]==] [==[SketchObjectTest.testReplaceGeometriesOneToOne]==] [==[SketchObjectTest.testReplaceGeometriesTwoToOne]==] [==[SketchObjectTest.testReplaceGeometriesOneToTwo]==] [==[SketchObjectTest.testSplitLineSegment]==] [==[SketchObjectTest.testSplitCircle]==] [==[SketchObjectTest.testSplitEllipse]==] [==[SketchObjectTest.testSplitArcOfCircle]==] [==[SketchObjectTest.testSplitArcOfConic]==] [==[SketchObjectTest.testSplitNonPeriodicBSpline]==] [==[SketchObjectTest.testSplitPeriodicBSpline]==] [==[SketchObjectTest.testTrimWithoutIntersection]==] [==[SketchObjectTest.testTrimLineSegmentEnd]==] [==[SketchObjectTest.testTrimLineSegmentMid]==] [==[SketchObjectTest.testTrimCircleEnd]==] [==[SketchObjectTest.testTrimCircleMid]==] [==[SketchObjectTest.testTrimArcOfCircleEnd]==] [==[SketchObjectTest.testTrimArcOfCircleMid]==] [==[SketchObjectTest.testTrimEllipseEnd]==] [==[SketchObjectTest.testTrimEllipseMid]==] [==[SketchObjectTest.testTrimPeriodicBSplineEnd]==] [==[SketchObjectTest.testTrimPeriodicBSplineMid]==] [==[SketchObjectTest.testTrimNonPeriodicBSplineEnd]==] [==[SketchObjectTest.testTrimNonPeriodicBSplineMid]==] [==[SketchObjectTest.testTrimEffectOnConstruction]==] [==[SketchObjectTest.testTrimEndEffectOnFullLengthConstraints]==] [==[SketchObjectTest.testTrimEndEffectOnSymmetricConstraints]==] [==[SketchObjectTest.testTrimEndEffectOnUnrelatedTangent]==] [==[SketchObjectTest.testModifyKnotMultInNonPeriodicBSplineToZero]==] [==[SketchObjectTest.testModifyKnotMultInNonPeriodicBSplineToDisallowed]==] [==[SketchObjectTest.testModifyKnotMultInNonPeriodicBSpline]==] [==[SketchObjectTest.testModifyKnotMultInPeriodicBSplineToZero]==] [==[SketchObjectTest.testModifyKnotMultInPeriodicBSplineToDisallowed]==] [==[SketchObjectTest.testModifyKnotMultInPeriodicBSpline]==] [==[SketchObjectTest.testInsertKnotInNonPeriodicBSpline]==] [==[SketchObjectTest.testInsertKnotInPeriodicBSpline]==] [==[SketchObjectTest.testJoinCurves]==] [==[SketchObjectTest.testJoinCurvesWhenTangent]==] [==[SketchObjectTest.testAddSymmetricCopyWithoutConstraints]==] [==[SketchObjectTest.testAddSymmetricWithConstraintsAddsSymmetric]==] [==[SketchObjectTest.testAddSymmetricPreservesCoincidentTopology]==] [==[SketchObjectTest.testAddSymmetricDowngradesTangentToCoincident]==] [==[SketchObjectTest.testAddSymmetricOnAxisPointGetsCoincident]==] [==[SketchObjectTest.testAddSymmetricOnAxisPointWithLineRef]==] [==[SketchObjectTest.testAddSymmetricSharedVertexNoDuplicateConstraints]==] [==[SketchObjectTest.testAddSymmetricPointSymmetry]==] [==[SketchObjectTest.testAddSymmetricPointSymmetryOnPoint]==] [==[SketchObjectTest.testAddSymmetricCircleGetsCenterSymmetricAndEqual]==] [==[GCSTest.clearConstraints]==] [==[ConstraintsTest.tangentBSplineAndArc]==])
