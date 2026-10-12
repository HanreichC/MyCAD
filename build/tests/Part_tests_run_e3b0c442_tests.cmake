add_test([=[AttacherTest.TestSetReferences]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=AttacherTest.TestSetReferences]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AttacherTest.TestSetReferences]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/Attacher.cpp:53]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[AttacherTest.TestSuggestMapModes]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=AttacherTest.TestSuggestMapModes]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AttacherTest.TestSuggestMapModes]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/Attacher.cpp:59]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[AttacherTest.TestGetShapeType]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=AttacherTest.TestGetShapeType]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AttacherTest.TestGetShapeType]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/Attacher.cpp:71]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[AttacherTest.TestGetInertialPropsOfShape]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=AttacherTest.TestGetInertialPropsOfShape]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AttacherTest.TestGetInertialPropsOfShape]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/Attacher.cpp:79]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[AttacherTest.TestGetRefObjects]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=AttacherTest.TestGetRefObjects]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AttacherTest.TestGetRefObjects]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/Attacher.cpp:90]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[AttacherTest.TestCalculateAttachedPlacement]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=AttacherTest.TestCalculateAttachedPlacement]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AttacherTest.TestCalculateAttachedPlacement]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/Attacher.cpp:98]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[AttacherTest.TestAllStringModesValid]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=AttacherTest.TestAllStringModesValid]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AttacherTest.TestAllStringModesValid]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/Attacher.cpp:111]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[AttacherTest.TestAllModesBoundaries]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=AttacherTest.TestAllModesBoundaries]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AttacherTest.TestAllModesBoundaries]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/Attacher.cpp:187]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[AttachExtensionTest.testPlanePlane]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=AttachExtensionTest.testPlanePlane]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AttachExtensionTest.testPlanePlane]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/AttachExtension.cpp:93]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[AttachExtensionTest.testMidPlane]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=AttachExtensionTest.testMidPlane]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AttachExtensionTest.testMidPlane]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/AttachExtension.cpp:112]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[AttachExtensionTest.testMidPlaneBisectsFaceAngle]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=AttachExtensionTest.testMidPlaneBisectsFaceAngle]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AttachExtensionTest.testMidPlaneBisectsFaceAngle]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/AttachExtension.cpp:147]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[AttachExtensionTest.testMidPlaneBisectsConnectedFaces]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=AttachExtensionTest.testMidPlaneBisectsConnectedFaces]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AttachExtensionTest.testMidPlaneBisectsConnectedFaces]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/AttachExtension.cpp:189]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[AttachExtensionTest.testMidPlaneBisectsObliqueFaceAngle]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=AttachExtensionTest.testMidPlaneBisectsObliqueFaceAngle]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AttachExtensionTest.testMidPlaneBisectsObliqueFaceAngle]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/AttachExtension.cpp:222]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[AttachExtensionTest.testAttacherEngineType]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=AttachExtensionTest.testAttacherEngineType]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AttachExtensionTest.testAttacherEngineType]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/AttachExtension.cpp:259]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[AttachExtensionTest.testAttacherTypeEngine]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=AttachExtensionTest.testAttacherTypeEngine]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AttachExtensionTest.testAttacherTypeEngine]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/AttachExtension.cpp:278]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[AttachExtensionTest.testEmptyLegacySupportDoesNotClearAttachmentSupport]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=AttachExtensionTest.testEmptyLegacySupportDoesNotClearAttachmentSupport]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AttachExtensionTest.testEmptyLegacySupportDoesNotClearAttachmentSupport]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/AttachExtension.cpp:301]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[AttachExtensionTest.testNonEmptyLegacySupportReplacesAttachmentSupport]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=AttachExtensionTest.testNonEmptyLegacySupportReplacesAttachmentSupport]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AttachExtensionTest.testNonEmptyLegacySupportReplacesAttachmentSupport]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/AttachExtension.cpp:321]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BRepMeshTest.testNoDomains]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=BRepMeshTest.testNoDomains]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BRepMeshTest.testNoDomains]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/BRepMesh.cpp:133]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BRepMeshTest.testEmptyDomains]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=BRepMeshTest.testEmptyDomains]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BRepMeshTest.testEmptyDomains]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/BRepMesh.cpp:144]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BRepMeshTest.testConnectedDomains]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=BRepMeshTest.testConnectedDomains]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BRepMeshTest.testConnectedDomains]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/BRepMesh.cpp:155]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BRepMeshTest.testUnconnectedDomains]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=BRepMeshTest.testUnconnectedDomains]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BRepMeshTest.testUnconnectedDomains]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/BRepMesh.cpp:166]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FaceMakerBullseyeTest.getWireDirectionCCWRectangle]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FaceMakerBullseyeTest.getWireDirectionCCWRectangle]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FaceMakerBullseyeTest.getWireDirectionCCWRectangle]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FaceMakerBullseye.cpp:99]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FaceMakerBullseyeTest.getWireDirectionCWRectangle]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FaceMakerBullseyeTest.getWireDirectionCWRectangle]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FaceMakerBullseyeTest.getWireDirectionCWRectangle]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FaceMakerBullseye.cpp:107]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FaceMakerBullseyeTest.getWireDirectionCCWCircle]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FaceMakerBullseyeTest.getWireDirectionCCWCircle]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FaceMakerBullseyeTest.getWireDirectionCCWCircle]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FaceMakerBullseye.cpp:116]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FaceMakerBullseyeTest.getWireDirectionCWCircle]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FaceMakerBullseyeTest.getWireDirectionCWCircle]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FaceMakerBullseyeTest.getWireDirectionCWCircle]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FaceMakerBullseye.cpp:124]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FaceMakerBullseyeTest.getWireDirectionFlippedPlane]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FaceMakerBullseyeTest.getWireDirectionFlippedPlane]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FaceMakerBullseyeTest.getWireDirectionFlippedPlane]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FaceMakerBullseye.cpp:133]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FaceMakerBullseyeTest.getWireDirectionTiltedPlane]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FaceMakerBullseyeTest.getWireDirectionTiltedPlane]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FaceMakerBullseyeTest.getWireDirectionTiltedPlane]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FaceMakerBullseye.cpp:143]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FaceMakerBullseyeTest.faceDrillerSimpleRectangle]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FaceMakerBullseyeTest.faceDrillerSimpleRectangle]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FaceMakerBullseyeTest.faceDrillerSimpleRectangle]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FaceMakerBullseye.cpp:175]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FaceMakerBullseyeTest.faceDrillerWithOneHole]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FaceMakerBullseyeTest.faceDrillerWithOneHole]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FaceMakerBullseyeTest.faceDrillerWithOneHole]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FaceMakerBullseye.cpp:186]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FaceMakerBullseyeTest.faceDrillerReversedOuterWire]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FaceMakerBullseyeTest.faceDrillerReversedOuterWire]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FaceMakerBullseyeTest.faceDrillerReversedOuterWire]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FaceMakerBullseye.cpp:199]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FaceMakerBullseyeTest.faceDrillerReversedHoleWire]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FaceMakerBullseyeTest.faceDrillerReversedHoleWire]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FaceMakerBullseyeTest.faceDrillerReversedHoleWire]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FaceMakerBullseye.cpp:211]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FaceMakerBullseyeTest.faceDrillerFlippedPlane]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FaceMakerBullseyeTest.faceDrillerFlippedPlane]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FaceMakerBullseyeTest.faceDrillerFlippedPlane]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FaceMakerBullseye.cpp:226]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FaceMakerBullseyeTest.faceDrillerMultipleHoles]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FaceMakerBullseyeTest.faceDrillerMultipleHoles]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FaceMakerBullseyeTest.faceDrillerMultipleHoles]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FaceMakerBullseye.cpp:239]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FaceMakerBullseyeTest.buildEssenceOuterWithHole]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FaceMakerBullseyeTest.buildEssenceOuterWithHole]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FaceMakerBullseyeTest.buildEssenceOuterWithHole]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FaceMakerBullseye.cpp:254]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FaceMakerBullseyeTest.buildEssenceNestedIslands]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FaceMakerBullseyeTest.buildEssenceNestedIslands]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FaceMakerBullseyeTest.buildEssenceNestedIslands]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FaceMakerBullseye.cpp:271]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FaceMakerBullseyeTest.buildEssenceTiltedPlane]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FaceMakerBullseyeTest.buildEssenceTiltedPlane]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FaceMakerBullseyeTest.buildEssenceTiltedPlane]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FaceMakerBullseye.cpp:292]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FaceMakerBullseyeTest.buildEssenceManyWires]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FaceMakerBullseyeTest.buildEssenceManyWires]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FaceMakerBullseyeTest.buildEssenceManyWires]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FaceMakerBullseye.cpp:322]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FaceMakerUnifiedTest.singleRectangleNaming]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FaceMakerUnifiedTest.singleRectangleNaming]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FaceMakerUnifiedTest.singleRectangleNaming]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FaceMakerUnified.cpp:173]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FaceMakerUnifiedTest.subdivisionNaming]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FaceMakerUnifiedTest.subdivisionNaming]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FaceMakerUnifiedTest.subdivisionNaming]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FaceMakerUnified.cpp:182]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FaceMakerUnifiedTest.overlappingRectsNaming]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FaceMakerUnifiedTest.overlappingRectsNaming]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FaceMakerUnifiedTest.overlappingRectsNaming]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FaceMakerUnified.cpp:191]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FaceMakerUnifiedTest.selfIntersectingBSplineNaming]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FaceMakerUnifiedTest.selfIntersectingBSplineNaming]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FaceMakerUnifiedTest.selfIntersectingBSplineNaming]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FaceMakerUnified.cpp:200]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FaceMakerUnifiedTest.singleRectangleStable]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FaceMakerUnifiedTest.singleRectangleStable]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FaceMakerUnifiedTest.singleRectangleStable]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FaceMakerUnified.cpp:209]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FaceMakerUnifiedTest.subdivisionStable]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FaceMakerUnifiedTest.subdivisionStable]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FaceMakerUnifiedTest.subdivisionStable]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FaceMakerUnified.cpp:214]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FaceMakerUnifiedTest.overlappingRectsStable]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FaceMakerUnifiedTest.overlappingRectsStable]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FaceMakerUnifiedTest.overlappingRectsStable]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FaceMakerUnified.cpp:219]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FaceMakerUnifiedTest.selfIntersectingBSplineStable]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FaceMakerUnifiedTest.selfIntersectingBSplineStable]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FaceMakerUnifiedTest.selfIntersectingBSplineStable]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FaceMakerUnified.cpp:224]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureChamferTest.testOther]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureChamferTest.testOther]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureChamferTest.testOther]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureChamfer.cpp:58]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureChamferTest.testMost]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureChamferTest.testMost]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureChamferTest.testMost]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureChamfer.cpp:92]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureChamferTest.testMustExecute]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureChamferTest.testMustExecute]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureChamferTest.testMustExecute]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureChamfer.cpp:116]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureChamferTest.testGetProviderName]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureChamferTest.testGetProviderName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureChamferTest.testGetProviderName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureChamfer.cpp:134]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureCompoundTest.testIntersecting]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureCompoundTest.testIntersecting]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureCompoundTest.testIntersecting]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureCompound.cpp:34]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureCompoundTest.testNonIntersecting]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureCompoundTest.testNonIntersecting]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureCompoundTest.testNonIntersecting]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureCompound.cpp:49]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureCompoundTest.xlinkFromOpenDocumentKeepsMappedNameWhenTargetReopens]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureCompoundTest.xlinkFromOpenDocumentKeepsMappedNameWhenTargetReopens]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureCompoundTest.xlinkFromOpenDocumentKeepsMappedNameWhenTargetReopens]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureCompound.cpp:64]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureCompoundTest.xlinkKeepsMappedNameWhenOpenedWithTarget]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureCompoundTest.xlinkKeepsMappedNameWhenOpenedWithTarget]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureCompoundTest.xlinkKeepsMappedNameWhenOpenedWithTarget]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureCompound.cpp:88]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureExtrusionTest.testMustExecute]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureExtrusionTest.testMustExecute]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureExtrusionTest.testMustExecute]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureExtrusion.cpp:42]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureExtrusionTest.testGetProviderName]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureExtrusionTest.testGetProviderName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureExtrusionTest.testGetProviderName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureExtrusion.cpp:68]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureExtrusionTest.testFetchAxisLink]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureExtrusionTest.testFetchAxisLink]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureExtrusionTest.testFetchAxisLink]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureExtrusion.cpp:79]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureExtrusionTest.testExtrudeShape]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureExtrusionTest.testExtrudeShape]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureExtrusionTest.testExtrudeShape]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureExtrusion.cpp:90]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureExtrusionTest.testComputeFinalParameters]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureExtrusionTest.testComputeFinalParameters]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureExtrusionTest.testComputeFinalParameters]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureExtrusion.cpp:95]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureExtrusionTest.testExecuteSimple]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureExtrusionTest.testExecuteSimple]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureExtrusionTest.testExecuteSimple]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureExtrusion.cpp:100]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureExtrusionTest.testExecuteSimpleRev]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureExtrusionTest.testExecuteSimpleRev]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureExtrusionTest.testExecuteSimpleRev]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureExtrusion.cpp:113]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureExtrusionTest.testExecuteSolid]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureExtrusionTest.testExecuteSolid]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureExtrusionTest.testExecuteSolid]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureExtrusion.cpp:129]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureExtrusionTest.testExecuteReverse]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureExtrusionTest.testExecuteReverse]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureExtrusionTest.testExecuteReverse]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureExtrusion.cpp:143]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureExtrusionTest.testExecuteSymmetric]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureExtrusionTest.testExecuteSymmetric]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureExtrusionTest.testExecuteSymmetric]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureExtrusion.cpp:157]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureExtrusionTest.testExecuteAngled]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureExtrusionTest.testExecuteAngled]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureExtrusionTest.testExecuteAngled]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureExtrusion.cpp:171]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureExtrusionTest.testExecuteAngledRev]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureExtrusionTest.testExecuteAngledRev]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureExtrusionTest.testExecuteAngledRev]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureExtrusion.cpp:206]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureExtrusionTest.testExecuteEdge]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureExtrusionTest.testExecuteEdge]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureExtrusionTest.testExecuteEdge]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureExtrusion.cpp:252]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureExtrusionTest.testExecuteDir]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureExtrusionTest.testExecuteDir]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureExtrusionTest.testExecuteDir]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureExtrusion.cpp:277]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureExtrusionTest.testExecuteFaceMaker]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureExtrusionTest.testExecuteFaceMaker]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureExtrusionTest.testExecuteFaceMaker]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureExtrusion.cpp:295]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureExtrusionTest.testFaceWithHoles]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureExtrusionTest.testFaceWithHoles]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureExtrusionTest.testFaceWithHoles]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureExtrusion.cpp:309]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureFilletTest.testOtherEdges]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureFilletTest.testOtherEdges]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureFilletTest.testOtherEdges]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureFillet.cpp:52]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureFilletTest.testMostEdges]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureFilletTest.testMostEdges]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureFilletTest.testMostEdges]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureFillet.cpp:85]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureFilletTest.testMustExecute]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureFilletTest.testMustExecute]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureFilletTest.testMustExecute]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureFillet.cpp:108]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureFilletTest.testGetProviderName]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureFilletTest.testGetProviderName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureFilletTest.testGetProviderName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureFillet.cpp:126]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureMirroringTest.testXMirror]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureMirroringTest.testXMirror]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureMirroringTest.testXMirror]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureMirroring.cpp:36]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureMirroringTest.testYMirrorWithExistingElementMap]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureMirroringTest.testYMirrorWithExistingElementMap]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureMirroringTest.testYMirrorWithExistingElementMap]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureMirroring.cpp:61]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureOffsetTest.testOffset3D]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureOffsetTest.testOffset3D]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureOffsetTest.testOffset3D]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureOffset.cpp:37]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureOffsetTest.testOffset3DWithExistingElementMap]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureOffsetTest.testOffset3DWithExistingElementMap]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureOffsetTest.testOffset3DWithExistingElementMap]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureOffset.cpp:51]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureOffsetTest.testOffset2D]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureOffsetTest.testOffset2D]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureOffsetTest.testOffset2D]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureOffset.cpp:76]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartCommonTest.testIntersecting]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartCommonTest.testIntersecting]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartCommonTest.testIntersecting]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeaturePartCommon.cpp:31]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartCommonTest.testNonIntersecting]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartCommonTest.testNonIntersecting]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartCommonTest.testNonIntersecting]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeaturePartCommon.cpp:54]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartCommonTest.testTouching]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartCommonTest.testTouching]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartCommonTest.testTouching]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeaturePartCommon.cpp:71]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartCommonTest.testAlmostTouching]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartCommonTest.testAlmostTouching]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartCommonTest.testAlmostTouching]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeaturePartCommon.cpp:88]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartCommonTest.testBarelyIntersecting]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartCommonTest.testBarelyIntersecting]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartCommonTest.testBarelyIntersecting]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeaturePartCommon.cpp:105]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartCommonTest.testMustExecute]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartCommonTest.testMustExecute]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartCommonTest.testMustExecute]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeaturePartCommon.cpp:132]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartCommonTest.testGetProviderName]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartCommonTest.testGetProviderName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartCommonTest.testGetProviderName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeaturePartCommon.cpp:150]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartCommonTest.testHistory]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartCommonTest.testHistory]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartCommonTest.testHistory]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeaturePartCommon.cpp:159]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartCommonTest.testMapping]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartCommonTest.testMapping]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartCommonTest.testMapping]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeaturePartCommon.cpp:198]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartCutTest.testIntersecting]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartCutTest.testIntersecting]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartCutTest.testIntersecting]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeaturePartCut.cpp:30]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartCutTest.testNonIntersecting]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartCutTest.testNonIntersecting]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartCutTest.testNonIntersecting]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeaturePartCut.cpp:53]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartCutTest.testTouching]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartCutTest.testTouching]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartCutTest.testTouching]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeaturePartCut.cpp:76]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartCutTest.testAlmostTouching]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartCutTest.testAlmostTouching]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartCutTest.testAlmostTouching]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeaturePartCut.cpp:99]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartCutTest.testBarelyIntersecting]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartCutTest.testBarelyIntersecting]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartCutTest.testBarelyIntersecting]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeaturePartCut.cpp:122]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartCutTest.testMustExecute]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartCutTest.testMustExecute]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartCutTest.testMustExecute]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeaturePartCut.cpp:149]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartCutTest.testGetProviderName]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartCutTest.testGetProviderName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartCutTest.testGetProviderName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeaturePartCut.cpp:167]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartCutTest.testMapping]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartCutTest.testMapping]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartCutTest.testMapping]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeaturePartCut.cpp:176]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartFuseTest.testIntersecting]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartFuseTest.testIntersecting]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartFuseTest.testIntersecting]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeaturePartFuse.cpp:34]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartFuseTest.testCompound]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartFuseTest.testCompound]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartFuseTest.testCompound]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeaturePartFuse.cpp:57]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartFuseTest.testRecursiveCompound]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartFuseTest.testRecursiveCompound]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartFuseTest.testRecursiveCompound]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeaturePartFuse.cpp:82]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartFuseTest.testNonIntersecting]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartFuseTest.testNonIntersecting]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartFuseTest.testNonIntersecting]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeaturePartFuse.cpp:115]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartFuseTest.testTouching]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartFuseTest.testTouching]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartFuseTest.testTouching]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeaturePartFuse.cpp:138]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartFuseTest.testAlmostTouching]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartFuseTest.testAlmostTouching]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartFuseTest.testAlmostTouching]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeaturePartFuse.cpp:161]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartFuseTest.testBarelyIntersecting]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartFuseTest.testBarelyIntersecting]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartFuseTest.testBarelyIntersecting]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeaturePartFuse.cpp:184]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartFuseTest.testMustExecute]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartFuseTest.testMustExecute]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartFuseTest.testMustExecute]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeaturePartFuse.cpp:211]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartFuseTest.testGetProviderName]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartFuseTest.testGetProviderName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartFuseTest.testGetProviderName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeaturePartFuse.cpp:229]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartFuseTest.testRefine]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartFuseTest.testRefine]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartFuseTest.testRefine]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeaturePartFuse.cpp:238]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureRevolutionTest.testExecute]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureRevolutionTest.testExecute]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureRevolutionTest.testExecute]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureRevolution.cpp:46]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureRevolutionTest.testExecuteBase]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureRevolutionTest.testExecuteBase]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureRevolutionTest.testExecuteBase]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureRevolution.cpp:60]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureRevolutionTest.testAxis]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureRevolutionTest.testAxis]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureRevolutionTest.testAxis]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureRevolution.cpp:79]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureRevolutionTest.testAxisLink]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureRevolutionTest.testAxisLink]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureRevolutionTest.testAxisLink]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureRevolution.cpp:94]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureRevolutionTest.testSymmetric]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureRevolutionTest.testSymmetric]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureRevolutionTest.testSymmetric]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureRevolution.cpp:115]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureRevolutionTest.testAngle]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureRevolutionTest.testAngle]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureRevolutionTest.testAngle]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureRevolution.cpp:130]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureRevolutionTest.testMustExecute]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureRevolutionTest.testMustExecute]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureRevolutionTest.testMustExecute]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureRevolution.cpp:145]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeatureRevolutionTest.testGetProviderName]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeatureRevolutionTest.testGetProviderName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeatureRevolutionTest.testGetProviderName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FeatureRevolution.cpp:176]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FuzzyBooleanTest.testLoadedCorrectly]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FuzzyBooleanTest.testLoadedCorrectly]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FuzzyBooleanTest.testLoadedCorrectly]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FuzzyBoolean.cpp:48]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FuzzyBooleanTest.testDefaultFuzzy]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FuzzyBooleanTest.testDefaultFuzzy]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FuzzyBooleanTest.testDefaultFuzzy]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FuzzyBoolean.cpp:55]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FuzzyBooleanTest.testGoodFuzzy]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FuzzyBooleanTest.testGoodFuzzy]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FuzzyBooleanTest.testGoodFuzzy]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FuzzyBoolean.cpp:82]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FuzzyBooleanTest.testFailsTooSmallFuzzy]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FuzzyBooleanTest.testFailsTooSmallFuzzy]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FuzzyBooleanTest.testFailsTooSmallFuzzy]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FuzzyBoolean.cpp:114]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FuzzyBooleanTest.testCompletelyFailsTooBigFuzzy]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FuzzyBooleanTest.testCompletelyFailsTooBigFuzzy]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FuzzyBooleanTest.testCompletelyFailsTooBigFuzzy]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/FuzzyBoolean.cpp:142]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[GeometryTest.testTrimBSpline]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=GeometryTest.testTrimBSpline]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[GeometryTest.testTrimBSpline]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/Geometry.cpp:32]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkArrayPolarTest.objectAxes]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=LinkArrayPolarTest.objectAxes]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkArrayPolarTest.objectAxes]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/LinkArrayPolar.cpp:42]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkArrayPolarTest.showElementDefaultsToExpandedAndEditable]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=LinkArrayPolarTest.showElementDefaultsToExpandedAndEditable]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkArrayPolarTest.showElementDefaultsToExpandedAndEditable]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/LinkArrayPolar.cpp:56]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkArrayPolarTest.expandedElementsFollowPatternPlacementChanges]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=LinkArrayPolarTest.expandedElementsFollowPatternPlacementChanges]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkArrayPolarTest.expandedElementsFollowPatternPlacementChanges]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/LinkArrayPolar.cpp:65]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkArrayPolarTest.suppressedExpandedElementIsOmittedFromSubObjects]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=LinkArrayPolarTest.suppressedExpandedElementIsOmittedFromSubObjects]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkArrayPolarTest.suppressedExpandedElementIsOmittedFromSubObjects]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/LinkArrayPolar.cpp:91]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ModelRefineTest.testRefineKeepsASolidValidWhenAVertexSplitsASeam]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=ModelRefineTest.testRefineKeepsASolidValidWhenAVertexSplitsASeam]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ModelRefineTest.testRefineKeepsASolidValidWhenAVertexSplitsASeam]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/ModelRefine.cpp:76]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ModelRefineTest.testRefinePreservesVolumeWhenAVertexSplitsASeam]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=ModelRefineTest.testRefinePreservesVolumeWhenAVertexSplitsASeam]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ModelRefineTest.testRefinePreservesVolumeWhenAVertexSplitsASeam]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/ModelRefine.cpp:91]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ModelRefineTest.testRefineLeavesNoEmptyFaceWhenAVertexSplitsASeam]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=ModelRefineTest.testRefineLeavesNoEmptyFaceWhenAVertexSplitsASeam]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ModelRefineTest.testRefineLeavesNoEmptyFaceWhenAVertexSplitsASeam]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/ModelRefine.cpp:100]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ModelRefineTest.testRefineIsUnharmedByAVertexOffTheSeam]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=ModelRefineTest.testRefineIsUnharmedByAVertexOffTheSeam]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ModelRefineTest.testRefineIsUnharmedByAVertexOffTheSeam]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/ModelRefine.cpp:112]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartTest.testGetElementName]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartTest.testGetElementName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartTest.testGetElementName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/PartFeature.cpp:37]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartTest.create]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartTest.create]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartTest.create]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/PartFeature.cpp:61]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartTest.getElementHistory]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartTest.getElementHistory]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartTest.getElementHistory]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/PartFeature.cpp:130]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartTest.getRelatedElements]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartTest.getRelatedElements]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartTest.getRelatedElements]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/PartFeature.cpp:146]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartTest.getElementFromSource]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartTest.getElementFromSource]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartTest.getElementFromSource]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/PartFeature.cpp:178]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartTest.getSubObject]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartTest.getSubObject]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartTest.getSubObject]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/PartFeature.cpp:204]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartTest.getElementTypes]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartTest.getElementTypes]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartTest.getElementTypes]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/PartFeature.cpp:220]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartTest.getComplexElementTypes]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartTest.getComplexElementTypes]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartTest.getComplexElementTypes]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/PartFeature.cpp:231]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PartFeaturesTest.testRuledSurface]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=PartFeaturesTest.testRuledSurface]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PartFeaturesTest.testRuledSurface]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/PartFeatures.cpp:30]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PartFeaturesTest.testLoft]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=PartFeaturesTest.testLoft]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PartFeaturesTest.testLoft]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/PartFeatures.cpp:65]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PartFeaturesTest.testSweep]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=PartFeaturesTest.testSweep]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PartFeaturesTest.testSweep]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/PartFeatures.cpp:93]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PartFeaturesTest.testThickness]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=PartFeaturesTest.testThickness]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PartFeaturesTest.testThickness]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/PartFeatures.cpp:125]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PartFeaturesTest.testRefine]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=PartFeaturesTest.testRefine]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PartFeaturesTest.testRefine]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/PartFeatures.cpp:147]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PartFeaturesTest.testReverse]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=PartFeaturesTest.testReverse]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PartFeaturesTest.testReverse]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/PartFeatures.cpp:177]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PreviewExtensionTest.previewShapeIsOutputTransientAndHidden]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=PreviewExtensionTest.previewShapeIsOutputTransientAndHidden]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PreviewExtensionTest.previewShapeIsOutputTransientAndHidden]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/PreviewExtension.cpp:118]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PreviewExtensionTest.updatePreviewRecomputesOnceThenMarksFresh]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=PreviewExtensionTest.updatePreviewRecomputesOnceThenMarksFresh]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PreviewExtensionTest.updatePreviewRecomputesOnceThenMarksFresh]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/PreviewExtension.cpp:127]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PreviewExtensionTest.updatePreviewIsNoOpWhileFresh]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=PreviewExtensionTest.updatePreviewIsNoOpWhileFresh]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PreviewExtensionTest.updatePreviewIsNoOpWhileFresh]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/PreviewExtension.cpp:138]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PreviewExtensionTest.changingInputPropertyInvalidates]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=PreviewExtensionTest.changingInputPropertyInvalidates]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PreviewExtensionTest.changingInputPropertyInvalidates]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/PreviewExtension.cpp:149]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PreviewExtensionTest.changingPreviewShapeDoesNotInvalidate]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=PreviewExtensionTest.changingPreviewShapeDoesNotInvalidate]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PreviewExtensionTest.changingPreviewShapeDoesNotInvalidate]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/PreviewExtension.cpp:160]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PreviewExtensionTest.changingOutputPropertyDoesNotInvalidate]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=PreviewExtensionTest.changingOutputPropertyDoesNotInvalidate]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PreviewExtensionTest.changingOutputPropertyDoesNotInvalidate]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/PreviewExtension.cpp:171]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PreviewExtensionTest.changingTypeOnlyOutputPropertyDoesNotInvalidate]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=PreviewExtensionTest.changingTypeOnlyOutputPropertyDoesNotInvalidate]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PreviewExtensionTest.changingTypeOnlyOutputPropertyDoesNotInvalidate]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/PreviewExtension.cpp:183]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PreviewExtensionTest.invalidatePreviewForcesRecompute]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=PreviewExtensionTest.invalidatePreviewForcesRecompute]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PreviewExtensionTest.invalidatePreviewForcesRecompute]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/PreviewExtension.cpp:195]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PreviewExtensionTest.mustRecomputePreviewFollowsMustRecompute]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=PreviewExtensionTest.mustRecomputePreviewFollowsMustRecompute]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PreviewExtensionTest.mustRecomputePreviewFollowsMustRecompute]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/PreviewExtension.cpp:207]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PreviewExtensionTest.decliningRecomputeKeepsPreviewFreshOnInputChange]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=PreviewExtensionTest.decliningRecomputeKeepsPreviewFreshOnInputChange]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PreviewExtensionTest.decliningRecomputeKeepsPreviewFreshOnInputChange]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/PreviewExtension.cpp:220]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PropertyTopoShapeTest.testPropertyPartShapeTopoShape]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=PropertyTopoShapeTest.testPropertyPartShapeTopoShape]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PropertyTopoShapeTest.testPropertyPartShapeTopoShape]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/PropertyTopoShape.cpp:107]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PropertyTopoShapeTest.testPropertyPartShapeTopoDSShape]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=PropertyTopoShapeTest.testPropertyPartShapeTopoDSShape]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PropertyTopoShapeTest.testPropertyPartShapeTopoDSShape]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/PropertyTopoShape.cpp:124]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PropertyTopoShapeTest.testPropertyPartShapeGetPyObject]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=PropertyTopoShapeTest.testPropertyPartShapeGetPyObject]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PropertyTopoShapeTest.testPropertyPartShapeGetPyObject]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/PropertyTopoShape.cpp:144]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PropertyTopoShapeTest.testShapeHistory]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=PropertyTopoShapeTest.testShapeHistory]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PropertyTopoShapeTest.testShapeHistory]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/PropertyTopoShape.cpp:179]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PropertyTopoShapeTest.testPropertyShapeHistory]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=PropertyTopoShapeTest.testPropertyShapeHistory]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PropertyTopoShapeTest.testPropertyShapeHistory]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/PropertyTopoShape.cpp:204]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PropertyTopoShapeTest.testPropertyShapeCache]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=PropertyTopoShapeTest.testPropertyShapeCache]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PropertyTopoShapeTest.testPropertyShapeCache]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/PropertyTopoShape.cpp:209]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PropertyTopoShapeTest.testPropertyShapeCachePyObj]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=PropertyTopoShapeTest.testPropertyShapeCachePyObj]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PropertyTopoShapeTest.testPropertyShapeCachePyObj]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/PropertyTopoShape.cpp:228]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PropertyTopoShapeTest.testRestore]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=PropertyTopoShapeTest.testRestore]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PropertyTopoShapeTest.testRestore]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/PropertyTopoShape.cpp:255]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TestTopoDS_Shape.TestCastEdgeToVertex]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TestTopoDS_Shape.TestCastEdgeToVertex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestTopoDS_Shape.TestCastEdgeToVertex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoDS_Shape.cpp:25]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TestTopoDS_Shape.TestCastNullVertex]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TestTopoDS_Shape.TestCastNullVertex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestTopoDS_Shape.TestCastNullVertex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoDS_Shape.cpp:34]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TestTopoDS_Shape.TestCastNullEdge]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TestTopoDS_Shape.TestCastNullEdge]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestTopoDS_Shape.TestCastNullEdge]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoDS_Shape.cpp:42]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TestTopoDS_Shape.TestExploreNullShape]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TestTopoDS_Shape.TestExploreNullShape]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TestTopoDS_Shape.TestExploreNullShape]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoDS_Shape.cpp:50]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeTest.TestElementTypeFace1]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeTest.TestElementTypeFace1]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeTest.TestElementTypeFace1]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShape.cpp:39]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeTest.TestElementTypeEdge12]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeTest.TestElementTypeEdge12]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeTest.TestElementTypeEdge12]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShape.cpp:45]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeTest.TestElementTypeVertex3]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeTest.TestElementTypeVertex3]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeTest.TestElementTypeVertex3]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShape.cpp:51]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeTest.TestElementTypeFacer]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeTest.TestElementTypeFacer]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeTest.TestElementTypeFacer]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShape.cpp:57]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeTest.TestElementTypeVertex]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeTest.TestElementTypeVertex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeTest.TestElementTypeVertex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShape.cpp:63]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeTest.TestElementTypeEmpty]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeTest.TestElementTypeEmpty]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeTest.TestElementTypeEmpty]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShape.cpp:69]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeTest.TestElementTypeNull]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeTest.TestElementTypeNull]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeTest.TestElementTypeNull]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShape.cpp:75]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeTest.TestElementTypeWithHash]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeTest.TestElementTypeWithHash]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeTest.TestElementTypeWithHash]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShape.cpp:81]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeTest.TestElementTypeWithSubelements]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeTest.TestElementTypeWithSubelements]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeTest.TestElementTypeWithSubelements]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShape.cpp:87]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeTest.TestElementTypeNonMatching]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeTest.TestElementTypeNonMatching]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeTest.TestElementTypeNonMatching]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShape.cpp:93]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeTest.TestTypeFace1]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeTest.TestTypeFace1]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeTest.TestTypeFace1]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShape.cpp:102]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeTest.TestTypeEdge12]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeTest.TestTypeEdge12]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeTest.TestTypeEdge12]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShape.cpp:108]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeTest.TestTypeVertex3]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeTest.TestTypeVertex3]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeTest.TestTypeVertex3]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShape.cpp:114]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeTest.TestTypeFacer]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeTest.TestTypeFacer]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeTest.TestTypeFacer]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShape.cpp:120]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeTest.TestTypeVertex]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeTest.TestTypeVertex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeTest.TestTypeVertex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShape.cpp:126]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeTest.TestTypeEmpty]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeTest.TestTypeEmpty]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeTest.TestTypeEmpty]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShape.cpp:132]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeTest.TestTypeNull]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeTest.TestTypeNull]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeTest.TestTypeNull]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShape.cpp:138]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeTest.TestGetSubshape]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeTest.TestGetSubshape]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeTest.TestGetSubshape]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShape.cpp:144]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ShapeRelationKey.HistoryTraceTypeComparison]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=ShapeRelationKey.HistoryTraceTypeComparison]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ShapeRelationKey.HistoryTraceTypeComparison]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeCache.cpp:27]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeCacheTest.ConstructionFromTopoDS_Shape]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeCacheTest.ConstructionFromTopoDS_Shape]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeCacheTest.ConstructionFromTopoDS_Shape]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeCache.cpp:72]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeCacheTest.InsertRelationIntoEmptyTableCompacts]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeCacheTest.InsertRelationIntoEmptyTableCompacts]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeCacheTest.InsertRelationIntoEmptyTableCompacts]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeCache.cpp:89]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeCacheTest.InsertAlreadyExistsUpdatesExisting]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeCacheTest.InsertAlreadyExistsUpdatesExisting]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeCacheTest.InsertAlreadyExistsUpdatesExisting]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeCache.cpp:110]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeCacheTest.IsTouchedNotPartners]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeCacheTest.IsTouchedNotPartners]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeCacheTest.IsTouchedNotPartners]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeCache.cpp:130]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeCacheTest.IsTouchedArePartners]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeCacheTest.IsTouchedArePartners]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeCacheTest.IsTouchedArePartners]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeCache.cpp:150]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeCacheTest.GetAncestrySHAPE]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeCacheTest.GetAncestrySHAPE]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeCacheTest.GetAncestrySHAPE]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeCache.cpp:176]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeCacheTest.GetAncestryEDGE]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeCacheTest.GetAncestryEDGE]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeCacheTest.GetAncestryEDGE]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeCache.cpp:189]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeCacheTest.GetAncestryFACE]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeCacheTest.GetAncestryFACE]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeCacheTest.GetAncestryFACE]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeCache.cpp:202]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeCacheTest.CountShape]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeCacheTest.CountShape]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeCacheTest.CountShape]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeCache.cpp:215]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeCacheTest.FindShapeGivenSubshape]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeCacheTest.FindShapeGivenSubshape]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeCacheTest.FindShapeGivenSubshape]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeCache.cpp:232]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeCacheTest.FindShapeGivenTypeAndIndex]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeCacheTest.FindShapeGivenTypeAndIndex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeCacheTest.FindShapeGivenTypeAndIndex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeCache.cpp:247]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeCacheTest.FindAncestor]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeCacheTest.FindAncestor]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeCacheTest.FindAncestor]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeCache.cpp:279]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementCompoundOneShapeReturnsShape]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementCompoundOneShapeReturnsShape]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementCompoundOneShapeReturnsShape]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:81]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementCompoundOneShapeForceReturnsCompound]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementCompoundOneShapeForceReturnsCompound]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementCompoundOneShapeForceReturnsCompound]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:95]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementCompoundTwoShapesReturnsCompound]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementCompoundTwoShapesReturnsCompound]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementCompoundTwoShapesReturnsCompound]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:113]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementCompoundEmptyShapesReturnsEmptyCompound]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementCompoundEmptyShapesReturnsEmptyCompound]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementCompoundEmptyShapesReturnsEmptyCompound]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:128]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementCompoundTwoShapesGeneratesMap]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementCompoundTwoShapesGeneratesMap]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementCompoundTwoShapesGeneratesMap]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:144]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementCompoundTwoCubes]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementCompoundTwoCubes]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementCompoundTwoCubes]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:169]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.MapperMakerModified]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.MapperMakerModified]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.MapperMakerModified]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:218]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.MapperMakerGenerated]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.MapperMakerGenerated]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.MapperMakerGenerated]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:279]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.MapperHistoryModified]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.MapperHistoryModified]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.MapperHistoryModified]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:322]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.MapperHistoryGenerated]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.MapperHistoryGenerated]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.MapperHistoryGenerated]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:378]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.resetElementMapTest]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.resetElementMapTest]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.resetElementMapTest]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:425]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.flushElementMapTest]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.flushElementMapTest]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.flushElementMapTest]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:486]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.cacheRelatedElements]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.cacheRelatedElements]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.cacheRelatedElements]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:537]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementWiresCombinesAdjacent]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementWiresCombinesAdjacent]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementWiresCombinesAdjacent]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:569]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementWiresCombinesWires]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementWiresCombinesWires]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementWiresCombinesWires]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:584]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementFaceNull]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementFaceNull]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementFaceNull]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:622]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementFaceSimple]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementFaceSimple]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementFaceSimple]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:643]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementFaceParams]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementFaceParams]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementFaceParams]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:667]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementFaceFromFace]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementFaceFromFace]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementFaceFromFace]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:691]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementFaceOpenWire]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementFaceOpenWire]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementFaceOpenWire]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:716]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementFaceClosedWire]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementFaceClosedWire]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementFaceClosedWire]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:741]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.setElementComboNameNothing]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.setElementComboNameNothing]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.setElementComboNameNothing]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:772]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.setElementComboNameSimple]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.setElementComboNameSimple]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.setElementComboNameSimple]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:783]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.setElementComboName]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.setElementComboName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.setElementComboName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:800]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.setElementComboNameCompound]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.setElementComboNameCompound]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.setElementComboNameCompound]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:821]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.splitWires]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.splitWires]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.splitWires]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:849]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.getSubShapes]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.getSubShapes]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.getSubShapes]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:876]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.getSubTopoShapes]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.getSubTopoShapes]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.getSubTopoShapes]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:890]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.getOrderedEdges]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.getOrderedEdges]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.getOrderedEdges]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:904]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.getOrderedVertexes]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.getOrderedVertexes]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.getOrderedVertexes]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:917]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.getSubTopoShapeByEnum]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.getSubTopoShapeByEnum]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.getSubTopoShapeByEnum]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:928]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.getSubTopoShapeByStringDefaults]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.getSubTopoShapeByStringDefaults]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.getSubTopoShapeByStringDefaults]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:947]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.getSubTopoShapeByStringNames]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.getSubTopoShapeByStringNames]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.getSubTopoShapeByStringNames]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:973]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.mapSubElementInvalidParm]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.mapSubElementInvalidParm]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.mapSubElementInvalidParm]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:993]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.mapSubElementFindShapeByNames]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.mapSubElementFindShapeByNames]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.mapSubElementFindShapeByNames]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:1010]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.mapSubElementFindShapeByType]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.mapSubElementFindShapeByType]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.mapSubElementFindShapeByType]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:1043]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.mapSubElementFindAncestor]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.mapSubElementFindAncestor]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.mapSubElementFindAncestor]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:1065]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.mapSubElementFindAncestors]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.mapSubElementFindAncestors]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.mapSubElementFindAncestors]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:1087]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.findSubShapesWithSharedVertexEverything]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.findSubShapesWithSharedVertexEverything]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.findSubShapesWithSharedVertexEverything]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:1147]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.findSubShapesWithSharedVertexMid]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.findSubShapesWithSharedVertexMid]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.findSubShapesWithSharedVertexMid]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:1201]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.findSubShapesWithSharedVertexClose]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.findSubShapesWithSharedVertexClose]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.findSubShapesWithSharedVertexClose]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:1249]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementShellInvalid]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementShellInvalid]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementShellInvalid]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:1297]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementShellSingle]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementShellSingle]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementShellSingle]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:1305]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementShellOpen]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementShellOpen]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementShellOpen]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:1322]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementShellClosed]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementShellClosed]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementShellClosed]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:1348]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementShellIntersecting]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementShellIntersecting]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementShellIntersecting]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:1369]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementShellFromWires]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementShellFromWires]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementShellFromWires]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:1392]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementBooleanImpossibleCommon]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementBooleanImpossibleCommon]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementBooleanImpossibleCommon]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:1413]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementBooleanCommon]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementBooleanCommon]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementBooleanCommon]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:1428]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementBooleanCommonWithCompoundTool]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementBooleanCommonWithCompoundTool]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementBooleanCommonWithCompoundTool]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:1448]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementBooleanCut]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementBooleanCut]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementBooleanCut]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:1471]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementBooleanFuse]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementBooleanFuse]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementBooleanFuse]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:1533]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementBooleanAcceptsShapeRejectedByAnalyzer]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementBooleanAcceptsShapeRejectedByAnalyzer]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementBooleanAcceptsShapeRejectedByAnalyzer]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:1628]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementDraft]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementDraft]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementDraft]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:1687]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementDraftTopoShapes]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementDraftTopoShapes]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementDraftTopoShapes]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:1708]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.linearizeEdge]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.linearizeEdge]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.linearizeEdge]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:1748]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.linearizeFace]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.linearizeFace]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.linearizeFace]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:1768]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementRuledSurfaceEdges]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementRuledSurfaceEdges]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementRuledSurfaceEdges]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:1789]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementRuledSurfaceWires]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementRuledSurfaceWires]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementRuledSurfaceWires]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:1823]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementLoft]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementLoft]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementLoft]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:1872]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementLoftAllowsDistinctProfilesWithSameCenter]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementLoftAllowsDistinctProfilesWithSameCenter]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementLoftAllowsDistinctProfilesWithSameCenter]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:1923]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementLoftRejectsCoincidentProfiles]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementLoftRejectsCoincidentProfiles]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementLoftRejectsCoincidentProfiles]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:1951]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementPipeShell]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementPipeShell]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementPipeShell]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:1971]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementThickSolid]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementThickSolid]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementThickSolid]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:1996]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementGeneralFuse]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementGeneralFuse]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementGeneralFuse]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:2027]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementFuse]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementFuse]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementFuse]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:2125]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementCut]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementCut]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementCut]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:2215]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementChamfer]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementChamfer]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementChamfer]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:2279]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementFillet]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementFillet]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementFillet]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:2399]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementSlice]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementSlice]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementSlice]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:2526]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementSlices]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementSlices]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementSlices]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:2556]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementMirror]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementMirror]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementMirror]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:2611]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementTransformWithoutMap]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementTransformWithoutMap]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementTransformWithoutMap]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:2643]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementTransformWithMap]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementTransformWithMap]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementTransformWithMap]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:2661]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementGTransformWithoutMap]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementGTransformWithoutMap]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementGTransformWithoutMap]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:2754]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementGTransformWithMap]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementGTransformWithMap]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementGTransformWithMap]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:2772]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementSolid]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementSolid]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementSolid]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:2868]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementRevolve]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementRevolve]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementRevolve]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:2912]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementPrism]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementPrism]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementPrism]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:2959]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementPrismUntil]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementPrismUntil]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementPrismUntil]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:3006]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementFilledFace]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementFilledFace]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementFilledFace]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:3033]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementFilledFaceFromLooseEdges]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementFilledFaceFromLooseEdges]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementFilledFaceFromLooseEdges]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:3069]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementFilledFaceExplicitBoundaryRange]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementFilledFaceExplicitBoundaryRange]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementFilledFaceExplicitBoundaryRange]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:3099]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementBSplineFace]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementBSplineFace]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementBSplineFace]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:3127]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.replaceElementShape]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.replaceElementShape]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.replaceElementShape]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:3176]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.removeElementShape]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.removeElementShape]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.removeElementShape]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:3210]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementEvolve]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementEvolve]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementEvolve]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:3241]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.traceElement]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.traceElement]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.traceElement]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:3277]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementOffset]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementOffset]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementOffset]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:3358]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementOffsetFace]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementOffsetFace]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementOffsetFace]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:3491]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeExpansionTest.makeElementOffset2D]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeExpansionTest.makeElementOffset2D]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeExpansionTest.makeElementOffset2D]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeExpansion.cpp:3535]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[FeaturePartMakeElementRefineTest.makeElementRefineBoxes]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=FeaturePartMakeElementRefineTest.makeElementRefineBoxes]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[FeaturePartMakeElementRefineTest.makeElementRefineBoxes]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeMakeElementRefine.cpp:28]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeMakeShapeWithElementMapTests.nullShapeThrows]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeMakeShapeWithElementMapTests.nullShapeThrows]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeMakeShapeWithElementMapTests.nullShapeThrows]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeMakeShapeWithElementMap.cpp:65]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeMakeShapeWithElementMapTests.mapCompoundCount]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeMakeShapeWithElementMapTests.mapCompoundCount]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeMakeShapeWithElementMapTests.mapCompoundCount]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeMakeShapeWithElementMap.cpp:131]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeMakeShapeWithElementMapTests.emptySourceShapes]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeMakeShapeWithElementMapTests.emptySourceShapes]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeMakeShapeWithElementMapTests.emptySourceShapes]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeMakeShapeWithElementMap.cpp:161]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeMakeShapeWithElementMapTests.nonMappableSources]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeMakeShapeWithElementMapTests.nonMappableSources]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeMakeShapeWithElementMapTests.nonMappableSources]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeMakeShapeWithElementMap.cpp:180]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeMakeShapeWithElementMapTests.findSourceShapesInShape]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeMakeShapeWithElementMapTests.findSourceShapesInShape]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeMakeShapeWithElementMapTests.findSourceShapesInShape]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeMakeShapeWithElementMap.cpp:233]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeMakeShapeWithElementMapTests.findSourceSubShapesInElementMap]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeMakeShapeWithElementMapTests.findSourceSubShapesInElementMap]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeMakeShapeWithElementMapTests.findSourceSubShapesInElementMap]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeMakeShapeWithElementMap.cpp:317]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeMakeShapeWithElementMapTests.findMakerOpInElementMap]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeMakeShapeWithElementMapTests.findMakerOpInElementMap]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeMakeShapeWithElementMapTests.findMakerOpInElementMap]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeMakeShapeWithElementMap.cpp:334]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeMapperTest.shapeHasherSingle]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeMapperTest.shapeHasherSingle]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeMapperTest.shapeHasherSingle]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeMapper.cpp:41]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeMapperTest.shapeHasherDual]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeMapperTest.shapeHasherDual]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeMapperTest.shapeHasherDual]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeMapper.cpp:62]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeMapperTest.shapeHasherPair]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeMapperTest.shapeHasherPair]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeMapperTest.shapeHasherPair]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeMapper.cpp:84]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeMapperTest.shapeHasherPairs]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeMapperTest.shapeHasherPairs]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeMapperTest.shapeHasherPairs]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeMapper.cpp:109]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeMapperTest.shapeMapperTests]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeMapperTest.shapeMapperTests]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeMapperTest.shapeMapperTests]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeMapper.cpp:136]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeMakeShapeTests.nullShapeThrows]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeMakeShapeTests.nullShapeThrows]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeMakeShapeTests.nullShapeThrows]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeMakeShape.cpp:54]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeMakeShapeTests.shapeVertex]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeMakeShapeTests.shapeVertex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeMakeShapeTests.shapeVertex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeMakeShape.cpp:68]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeMakeShapeTests.thruSections]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeMakeShapeTests.thruSections]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeMakeShapeTests.thruSections]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeMakeShape.cpp:82]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[TopoShapeMakeShapeTests.sewing]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=TopoShapeMakeShapeTests.sewing]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TopoShapeMakeShapeTests.sewing]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/TopoShapeMakeShape.cpp:119]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[WireJoinerTest.addShape]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=WireJoinerTest.addShape]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[WireJoinerTest.addShape]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/WireJoiner.cpp:45]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[WireJoinerTest.setOutline]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=WireJoinerTest.setOutline]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[WireJoinerTest.setOutline]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/WireJoiner.cpp:129]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[WireJoinerTest.setTightBound]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=WireJoinerTest.setTightBound]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[WireJoinerTest.setTightBound]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/WireJoiner.cpp:241]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[WireJoinerTest.setSplitEdges]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=WireJoinerTest.setSplitEdges]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[WireJoinerTest.setSplitEdges]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/WireJoiner.cpp:311]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[WireJoinerTest.setMergeEdges]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=WireJoinerTest.setMergeEdges]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[WireJoinerTest.setMergeEdges]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/WireJoiner.cpp:385]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[WireJoinerTest.setTolerance]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=WireJoinerTest.setTolerance]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[WireJoinerTest.setTolerance]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/WireJoiner.cpp:464]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[WireJoinerTest.getOpenWires]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=WireJoinerTest.getOpenWires]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[WireJoinerTest.getOpenWires]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/WireJoiner.cpp:593]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[WireJoinerTest.getResultWires]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=WireJoinerTest.getResultWires]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[WireJoinerTest.getResultWires]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/WireJoiner.cpp:699]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[WireJoinerTest.Build]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=WireJoinerTest.Build]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[WireJoinerTest.Build]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/WireJoiner.cpp:777]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[WireJoinerTest.Modified]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=WireJoinerTest.Modified]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[WireJoinerTest.Modified]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/WireJoiner.cpp:812]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[WireJoinerTest.Generated]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=WireJoinerTest.Generated]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[WireJoinerTest.Generated]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/WireJoiner.cpp:856]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[WireJoinerTest.IsDeleted]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=WireJoinerTest.IsDeleted]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[WireJoinerTest.IsDeleted]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/App/WireJoiner.cpp:892]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SoBrepEdgeSetMappingTest.sparseMapping]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=SoBrepEdgeSetMappingTest.sparseMapping]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SoBrepEdgeSetMappingTest.sparseMapping]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/Gui/SoBrepEdgeSet.cpp:35]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SoBrepEdgeSetMappingTest.skippedEdgeHasNoRenderedLine]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=SoBrepEdgeSetMappingTest.skippedEdgeHasNoRenderedLine]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SoBrepEdgeSetMappingTest.skippedEdgeHasNoRenderedLine]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/Gui/SoBrepEdgeSet.cpp:50]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SoBrepEdgeSetMappingTest.emptyMappingHasNoRenderedEdges]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=SoBrepEdgeSetMappingTest.emptyMappingHasNoRenderedEdges]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SoBrepEdgeSetMappingTest.emptyMappingHasNoRenderedEdges]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/Gui/SoBrepEdgeSet.cpp:59]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SoBrepEdgeSetMappingTest.edgeBeyondMappingHasNoRenderedLine]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=SoBrepEdgeSetMappingTest.edgeBeyondMappingHasNoRenderedLine]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SoBrepEdgeSetMappingTest.edgeBeyondMappingHasNoRenderedLine]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/Gui/SoBrepEdgeSet.cpp:66]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SoBrepEdgeSetMappingTest.lineBeyondMappingHasNoEdge]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=SoBrepEdgeSetMappingTest.lineBeyondMappingHasNoEdge]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SoBrepEdgeSetMappingTest.lineBeyondMappingHasNoEdge]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/Gui/SoBrepEdgeSet.cpp:75]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SoBrepEdgeSetMappingTest.withoutMappingFallsBackToOneLinePerEdge]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=SoBrepEdgeSetMappingTest.withoutMappingFallsBackToOneLinePerEdge]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SoBrepEdgeSetMappingTest.withoutMappingFallsBackToOneLinePerEdge]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/Gui/SoBrepEdgeSet.cpp:83]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SoBrepEdgeSetMappingTest.mappingRoundTrips]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=SoBrepEdgeSetMappingTest.mappingRoundTrips]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SoBrepEdgeSetMappingTest.mappingRoundTrips]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/Gui/SoBrepEdgeSet.cpp:93]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[SoBrepEdgeSetMappingTest.remappingReplacesThePreviousMapping]=]  /workspace/build/tests/Part_tests_run [==[--gtest_filter=SoBrepEdgeSetMappingTest.remappingReplacesThePreviousMapping]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[SoBrepEdgeSetMappingTest.remappingReplacesThePreviousMapping]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Part/Gui/SoBrepEdgeSet.cpp:105]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
set(Part_tests_run_TESTS [==[AttacherTest.TestSetReferences]==] [==[AttacherTest.TestSuggestMapModes]==] [==[AttacherTest.TestGetShapeType]==] [==[AttacherTest.TestGetInertialPropsOfShape]==] [==[AttacherTest.TestGetRefObjects]==] [==[AttacherTest.TestCalculateAttachedPlacement]==] [==[AttacherTest.TestAllStringModesValid]==] [==[AttacherTest.TestAllModesBoundaries]==] [==[AttachExtensionTest.testPlanePlane]==] [==[AttachExtensionTest.testMidPlane]==] [==[AttachExtensionTest.testMidPlaneBisectsFaceAngle]==] [==[AttachExtensionTest.testMidPlaneBisectsConnectedFaces]==] [==[AttachExtensionTest.testMidPlaneBisectsObliqueFaceAngle]==] [==[AttachExtensionTest.testAttacherEngineType]==] [==[AttachExtensionTest.testAttacherTypeEngine]==] [==[AttachExtensionTest.testEmptyLegacySupportDoesNotClearAttachmentSupport]==] [==[AttachExtensionTest.testNonEmptyLegacySupportReplacesAttachmentSupport]==] [==[BRepMeshTest.testNoDomains]==] [==[BRepMeshTest.testEmptyDomains]==] [==[BRepMeshTest.testConnectedDomains]==] [==[BRepMeshTest.testUnconnectedDomains]==] [==[FaceMakerBullseyeTest.getWireDirectionCCWRectangle]==] [==[FaceMakerBullseyeTest.getWireDirectionCWRectangle]==] [==[FaceMakerBullseyeTest.getWireDirectionCCWCircle]==] [==[FaceMakerBullseyeTest.getWireDirectionCWCircle]==] [==[FaceMakerBullseyeTest.getWireDirectionFlippedPlane]==] [==[FaceMakerBullseyeTest.getWireDirectionTiltedPlane]==] [==[FaceMakerBullseyeTest.faceDrillerSimpleRectangle]==] [==[FaceMakerBullseyeTest.faceDrillerWithOneHole]==] [==[FaceMakerBullseyeTest.faceDrillerReversedOuterWire]==] [==[FaceMakerBullseyeTest.faceDrillerReversedHoleWire]==] [==[FaceMakerBullseyeTest.faceDrillerFlippedPlane]==] [==[FaceMakerBullseyeTest.faceDrillerMultipleHoles]==] [==[FaceMakerBullseyeTest.buildEssenceOuterWithHole]==] [==[FaceMakerBullseyeTest.buildEssenceNestedIslands]==] [==[FaceMakerBullseyeTest.buildEssenceTiltedPlane]==] [==[FaceMakerBullseyeTest.buildEssenceManyWires]==] [==[FaceMakerUnifiedTest.singleRectangleNaming]==] [==[FaceMakerUnifiedTest.subdivisionNaming]==] [==[FaceMakerUnifiedTest.overlappingRectsNaming]==] [==[FaceMakerUnifiedTest.selfIntersectingBSplineNaming]==] [==[FaceMakerUnifiedTest.singleRectangleStable]==] [==[FaceMakerUnifiedTest.subdivisionStable]==] [==[FaceMakerUnifiedTest.overlappingRectsStable]==] [==[FaceMakerUnifiedTest.selfIntersectingBSplineStable]==] [==[FeatureChamferTest.testOther]==] [==[FeatureChamferTest.testMost]==] [==[FeatureChamferTest.testMustExecute]==] [==[FeatureChamferTest.testGetProviderName]==] [==[FeatureCompoundTest.testIntersecting]==] [==[FeatureCompoundTest.testNonIntersecting]==] [==[FeatureCompoundTest.xlinkFromOpenDocumentKeepsMappedNameWhenTargetReopens]==] [==[FeatureCompoundTest.xlinkKeepsMappedNameWhenOpenedWithTarget]==] [==[FeatureExtrusionTest.testMustExecute]==] [==[FeatureExtrusionTest.testGetProviderName]==] [==[FeatureExtrusionTest.testFetchAxisLink]==] [==[FeatureExtrusionTest.testExtrudeShape]==] [==[FeatureExtrusionTest.testComputeFinalParameters]==] [==[FeatureExtrusionTest.testExecuteSimple]==] [==[FeatureExtrusionTest.testExecuteSimpleRev]==] [==[FeatureExtrusionTest.testExecuteSolid]==] [==[FeatureExtrusionTest.testExecuteReverse]==] [==[FeatureExtrusionTest.testExecuteSymmetric]==] [==[FeatureExtrusionTest.testExecuteAngled]==] [==[FeatureExtrusionTest.testExecuteAngledRev]==] [==[FeatureExtrusionTest.testExecuteEdge]==] [==[FeatureExtrusionTest.testExecuteDir]==] [==[FeatureExtrusionTest.testExecuteFaceMaker]==] [==[FeatureExtrusionTest.testFaceWithHoles]==] [==[FeatureFilletTest.testOtherEdges]==] [==[FeatureFilletTest.testMostEdges]==] [==[FeatureFilletTest.testMustExecute]==] [==[FeatureFilletTest.testGetProviderName]==] [==[FeatureMirroringTest.testXMirror]==] [==[FeatureMirroringTest.testYMirrorWithExistingElementMap]==] [==[FeatureOffsetTest.testOffset3D]==] [==[FeatureOffsetTest.testOffset3DWithExistingElementMap]==] [==[FeatureOffsetTest.testOffset2D]==] [==[FeaturePartCommonTest.testIntersecting]==] [==[FeaturePartCommonTest.testNonIntersecting]==] [==[FeaturePartCommonTest.testTouching]==] [==[FeaturePartCommonTest.testAlmostTouching]==] [==[FeaturePartCommonTest.testBarelyIntersecting]==] [==[FeaturePartCommonTest.testMustExecute]==] [==[FeaturePartCommonTest.testGetProviderName]==] [==[FeaturePartCommonTest.testHistory]==] [==[FeaturePartCommonTest.testMapping]==] [==[FeaturePartCutTest.testIntersecting]==] [==[FeaturePartCutTest.testNonIntersecting]==] [==[FeaturePartCutTest.testTouching]==] [==[FeaturePartCutTest.testAlmostTouching]==] [==[FeaturePartCutTest.testBarelyIntersecting]==] [==[FeaturePartCutTest.testMustExecute]==] [==[FeaturePartCutTest.testGetProviderName]==] [==[FeaturePartCutTest.testMapping]==] [==[FeaturePartFuseTest.testIntersecting]==] [==[FeaturePartFuseTest.testCompound]==] [==[FeaturePartFuseTest.testRecursiveCompound]==] [==[FeaturePartFuseTest.testNonIntersecting]==] [==[FeaturePartFuseTest.testTouching]==] [==[FeaturePartFuseTest.testAlmostTouching]==] [==[FeaturePartFuseTest.testBarelyIntersecting]==] [==[FeaturePartFuseTest.testMustExecute]==] [==[FeaturePartFuseTest.testGetProviderName]==] [==[FeaturePartFuseTest.testRefine]==] [==[FeatureRevolutionTest.testExecute]==] [==[FeatureRevolutionTest.testExecuteBase]==] [==[FeatureRevolutionTest.testAxis]==] [==[FeatureRevolutionTest.testAxisLink]==] [==[FeatureRevolutionTest.testSymmetric]==] [==[FeatureRevolutionTest.testAngle]==] [==[FeatureRevolutionTest.testMustExecute]==] [==[FeatureRevolutionTest.testGetProviderName]==] [==[FuzzyBooleanTest.testLoadedCorrectly]==] [==[FuzzyBooleanTest.testDefaultFuzzy]==] [==[FuzzyBooleanTest.testGoodFuzzy]==] [==[FuzzyBooleanTest.testFailsTooSmallFuzzy]==] [==[FuzzyBooleanTest.testCompletelyFailsTooBigFuzzy]==] [==[GeometryTest.testTrimBSpline]==] [==[LinkArrayPolarTest.objectAxes]==] [==[LinkArrayPolarTest.showElementDefaultsToExpandedAndEditable]==] [==[LinkArrayPolarTest.expandedElementsFollowPatternPlacementChanges]==] [==[LinkArrayPolarTest.suppressedExpandedElementIsOmittedFromSubObjects]==] [==[ModelRefineTest.testRefineKeepsASolidValidWhenAVertexSplitsASeam]==] [==[ModelRefineTest.testRefinePreservesVolumeWhenAVertexSplitsASeam]==] [==[ModelRefineTest.testRefineLeavesNoEmptyFaceWhenAVertexSplitsASeam]==] [==[ModelRefineTest.testRefineIsUnharmedByAVertexOffTheSeam]==] [==[FeaturePartTest.testGetElementName]==] [==[FeaturePartTest.create]==] [==[FeaturePartTest.getElementHistory]==] [==[FeaturePartTest.getRelatedElements]==] [==[FeaturePartTest.getElementFromSource]==] [==[FeaturePartTest.getSubObject]==] [==[FeaturePartTest.getElementTypes]==] [==[FeaturePartTest.getComplexElementTypes]==] [==[PartFeaturesTest.testRuledSurface]==] [==[PartFeaturesTest.testLoft]==] [==[PartFeaturesTest.testSweep]==] [==[PartFeaturesTest.testThickness]==] [==[PartFeaturesTest.testRefine]==] [==[PartFeaturesTest.testReverse]==] [==[PreviewExtensionTest.previewShapeIsOutputTransientAndHidden]==] [==[PreviewExtensionTest.updatePreviewRecomputesOnceThenMarksFresh]==] [==[PreviewExtensionTest.updatePreviewIsNoOpWhileFresh]==] [==[PreviewExtensionTest.changingInputPropertyInvalidates]==] [==[PreviewExtensionTest.changingPreviewShapeDoesNotInvalidate]==] [==[PreviewExtensionTest.changingOutputPropertyDoesNotInvalidate]==] [==[PreviewExtensionTest.changingTypeOnlyOutputPropertyDoesNotInvalidate]==] [==[PreviewExtensionTest.invalidatePreviewForcesRecompute]==] [==[PreviewExtensionTest.mustRecomputePreviewFollowsMustRecompute]==] [==[PreviewExtensionTest.decliningRecomputeKeepsPreviewFreshOnInputChange]==] [==[PropertyTopoShapeTest.testPropertyPartShapeTopoShape]==] [==[PropertyTopoShapeTest.testPropertyPartShapeTopoDSShape]==] [==[PropertyTopoShapeTest.testPropertyPartShapeGetPyObject]==] [==[PropertyTopoShapeTest.testShapeHistory]==] [==[PropertyTopoShapeTest.testPropertyShapeHistory]==] [==[PropertyTopoShapeTest.testPropertyShapeCache]==] [==[PropertyTopoShapeTest.testPropertyShapeCachePyObj]==] [==[PropertyTopoShapeTest.testRestore]==] [==[TestTopoDS_Shape.TestCastEdgeToVertex]==] [==[TestTopoDS_Shape.TestCastNullVertex]==] [==[TestTopoDS_Shape.TestCastNullEdge]==] [==[TestTopoDS_Shape.TestExploreNullShape]==] [==[TopoShapeTest.TestElementTypeFace1]==] [==[TopoShapeTest.TestElementTypeEdge12]==] [==[TopoShapeTest.TestElementTypeVertex3]==] [==[TopoShapeTest.TestElementTypeFacer]==] [==[TopoShapeTest.TestElementTypeVertex]==] [==[TopoShapeTest.TestElementTypeEmpty]==] [==[TopoShapeTest.TestElementTypeNull]==] [==[TopoShapeTest.TestElementTypeWithHash]==] [==[TopoShapeTest.TestElementTypeWithSubelements]==] [==[TopoShapeTest.TestElementTypeNonMatching]==] [==[TopoShapeTest.TestTypeFace1]==] [==[TopoShapeTest.TestTypeEdge12]==] [==[TopoShapeTest.TestTypeVertex3]==] [==[TopoShapeTest.TestTypeFacer]==] [==[TopoShapeTest.TestTypeVertex]==] [==[TopoShapeTest.TestTypeEmpty]==] [==[TopoShapeTest.TestTypeNull]==] [==[TopoShapeTest.TestGetSubshape]==] [==[ShapeRelationKey.HistoryTraceTypeComparison]==] [==[TopoShapeCacheTest.ConstructionFromTopoDS_Shape]==] [==[TopoShapeCacheTest.InsertRelationIntoEmptyTableCompacts]==] [==[TopoShapeCacheTest.InsertAlreadyExistsUpdatesExisting]==] [==[TopoShapeCacheTest.IsTouchedNotPartners]==] [==[TopoShapeCacheTest.IsTouchedArePartners]==] [==[TopoShapeCacheTest.GetAncestrySHAPE]==] [==[TopoShapeCacheTest.GetAncestryEDGE]==] [==[TopoShapeCacheTest.GetAncestryFACE]==] [==[TopoShapeCacheTest.CountShape]==] [==[TopoShapeCacheTest.FindShapeGivenSubshape]==] [==[TopoShapeCacheTest.FindShapeGivenTypeAndIndex]==] [==[TopoShapeCacheTest.FindAncestor]==] [==[TopoShapeExpansionTest.makeElementCompoundOneShapeReturnsShape]==] [==[TopoShapeExpansionTest.makeElementCompoundOneShapeForceReturnsCompound]==] [==[TopoShapeExpansionTest.makeElementCompoundTwoShapesReturnsCompound]==] [==[TopoShapeExpansionTest.makeElementCompoundEmptyShapesReturnsEmptyCompound]==] [==[TopoShapeExpansionTest.makeElementCompoundTwoShapesGeneratesMap]==] [==[TopoShapeExpansionTest.makeElementCompoundTwoCubes]==] [==[TopoShapeExpansionTest.MapperMakerModified]==] [==[TopoShapeExpansionTest.MapperMakerGenerated]==] [==[TopoShapeExpansionTest.MapperHistoryModified]==] [==[TopoShapeExpansionTest.MapperHistoryGenerated]==] [==[TopoShapeExpansionTest.resetElementMapTest]==] [==[TopoShapeExpansionTest.flushElementMapTest]==] [==[TopoShapeExpansionTest.cacheRelatedElements]==] [==[TopoShapeExpansionTest.makeElementWiresCombinesAdjacent]==] [==[TopoShapeExpansionTest.makeElementWiresCombinesWires]==] [==[TopoShapeExpansionTest.makeElementFaceNull]==] [==[TopoShapeExpansionTest.makeElementFaceSimple]==] [==[TopoShapeExpansionTest.makeElementFaceParams]==] [==[TopoShapeExpansionTest.makeElementFaceFromFace]==] [==[TopoShapeExpansionTest.makeElementFaceOpenWire]==] [==[TopoShapeExpansionTest.makeElementFaceClosedWire]==] [==[TopoShapeExpansionTest.setElementComboNameNothing]==] [==[TopoShapeExpansionTest.setElementComboNameSimple]==] [==[TopoShapeExpansionTest.setElementComboName]==] [==[TopoShapeExpansionTest.setElementComboNameCompound]==] [==[TopoShapeExpansionTest.splitWires]==] [==[TopoShapeExpansionTest.getSubShapes]==] [==[TopoShapeExpansionTest.getSubTopoShapes]==] [==[TopoShapeExpansionTest.getOrderedEdges]==] [==[TopoShapeExpansionTest.getOrderedVertexes]==] [==[TopoShapeExpansionTest.getSubTopoShapeByEnum]==] [==[TopoShapeExpansionTest.getSubTopoShapeByStringDefaults]==] [==[TopoShapeExpansionTest.getSubTopoShapeByStringNames]==] [==[TopoShapeExpansionTest.mapSubElementInvalidParm]==] [==[TopoShapeExpansionTest.mapSubElementFindShapeByNames]==] [==[TopoShapeExpansionTest.mapSubElementFindShapeByType]==] [==[TopoShapeExpansionTest.mapSubElementFindAncestor]==] [==[TopoShapeExpansionTest.mapSubElementFindAncestors]==] [==[TopoShapeExpansionTest.findSubShapesWithSharedVertexEverything]==] [==[TopoShapeExpansionTest.findSubShapesWithSharedVertexMid]==] [==[TopoShapeExpansionTest.findSubShapesWithSharedVertexClose]==] [==[TopoShapeExpansionTest.makeElementShellInvalid]==] [==[TopoShapeExpansionTest.makeElementShellSingle]==] [==[TopoShapeExpansionTest.makeElementShellOpen]==] [==[TopoShapeExpansionTest.makeElementShellClosed]==] [==[TopoShapeExpansionTest.makeElementShellIntersecting]==] [==[TopoShapeExpansionTest.makeElementShellFromWires]==] [==[TopoShapeExpansionTest.makeElementBooleanImpossibleCommon]==] [==[TopoShapeExpansionTest.makeElementBooleanCommon]==] [==[TopoShapeExpansionTest.makeElementBooleanCommonWithCompoundTool]==] [==[TopoShapeExpansionTest.makeElementBooleanCut]==] [==[TopoShapeExpansionTest.makeElementBooleanFuse]==] [==[TopoShapeExpansionTest.makeElementBooleanAcceptsShapeRejectedByAnalyzer]==] [==[TopoShapeExpansionTest.makeElementDraft]==] [==[TopoShapeExpansionTest.makeElementDraftTopoShapes]==] [==[TopoShapeExpansionTest.linearizeEdge]==] [==[TopoShapeExpansionTest.linearizeFace]==] [==[TopoShapeExpansionTest.makeElementRuledSurfaceEdges]==] [==[TopoShapeExpansionTest.makeElementRuledSurfaceWires]==] [==[TopoShapeExpansionTest.makeElementLoft]==] [==[TopoShapeExpansionTest.makeElementLoftAllowsDistinctProfilesWithSameCenter]==] [==[TopoShapeExpansionTest.makeElementLoftRejectsCoincidentProfiles]==] [==[TopoShapeExpansionTest.makeElementPipeShell]==] [==[TopoShapeExpansionTest.makeElementThickSolid]==] [==[TopoShapeExpansionTest.makeElementGeneralFuse]==] [==[TopoShapeExpansionTest.makeElementFuse]==] [==[TopoShapeExpansionTest.makeElementCut]==] [==[TopoShapeExpansionTest.makeElementChamfer]==] [==[TopoShapeExpansionTest.makeElementFillet]==] [==[TopoShapeExpansionTest.makeElementSlice]==] [==[TopoShapeExpansionTest.makeElementSlices]==] [==[TopoShapeExpansionTest.makeElementMirror]==] [==[TopoShapeExpansionTest.makeElementTransformWithoutMap]==] [==[TopoShapeExpansionTest.makeElementTransformWithMap]==] [==[TopoShapeExpansionTest.makeElementGTransformWithoutMap]==] [==[TopoShapeExpansionTest.makeElementGTransformWithMap]==] [==[TopoShapeExpansionTest.makeElementSolid]==] [==[TopoShapeExpansionTest.makeElementRevolve]==] [==[TopoShapeExpansionTest.makeElementPrism]==] [==[TopoShapeExpansionTest.makeElementPrismUntil]==] [==[TopoShapeExpansionTest.makeElementFilledFace]==] [==[TopoShapeExpansionTest.makeElementFilledFaceFromLooseEdges]==] [==[TopoShapeExpansionTest.makeElementFilledFaceExplicitBoundaryRange]==] [==[TopoShapeExpansionTest.makeElementBSplineFace]==] [==[TopoShapeExpansionTest.replaceElementShape]==] [==[TopoShapeExpansionTest.removeElementShape]==] [==[TopoShapeExpansionTest.makeElementEvolve]==] [==[TopoShapeExpansionTest.traceElement]==] [==[TopoShapeExpansionTest.makeElementOffset]==] [==[TopoShapeExpansionTest.makeElementOffsetFace]==] [==[TopoShapeExpansionTest.makeElementOffset2D]==] [==[FeaturePartMakeElementRefineTest.makeElementRefineBoxes]==] [==[TopoShapeMakeShapeWithElementMapTests.nullShapeThrows]==] [==[TopoShapeMakeShapeWithElementMapTests.mapCompoundCount]==] [==[TopoShapeMakeShapeWithElementMapTests.emptySourceShapes]==] [==[TopoShapeMakeShapeWithElementMapTests.nonMappableSources]==] [==[TopoShapeMakeShapeWithElementMapTests.findSourceShapesInShape]==] [==[TopoShapeMakeShapeWithElementMapTests.findSourceSubShapesInElementMap]==] [==[TopoShapeMakeShapeWithElementMapTests.findMakerOpInElementMap]==] [==[TopoShapeMapperTest.shapeHasherSingle]==] [==[TopoShapeMapperTest.shapeHasherDual]==] [==[TopoShapeMapperTest.shapeHasherPair]==] [==[TopoShapeMapperTest.shapeHasherPairs]==] [==[TopoShapeMapperTest.shapeMapperTests]==] [==[TopoShapeMakeShapeTests.nullShapeThrows]==] [==[TopoShapeMakeShapeTests.shapeVertex]==] [==[TopoShapeMakeShapeTests.thruSections]==] [==[TopoShapeMakeShapeTests.sewing]==] [==[WireJoinerTest.addShape]==] [==[WireJoinerTest.setOutline]==] [==[WireJoinerTest.setTightBound]==] [==[WireJoinerTest.setSplitEdges]==] [==[WireJoinerTest.setMergeEdges]==] [==[WireJoinerTest.setTolerance]==] [==[WireJoinerTest.getOpenWires]==] [==[WireJoinerTest.getResultWires]==] [==[WireJoinerTest.Build]==] [==[WireJoinerTest.Modified]==] [==[WireJoinerTest.Generated]==] [==[WireJoinerTest.IsDeleted]==] [==[SoBrepEdgeSetMappingTest.sparseMapping]==] [==[SoBrepEdgeSetMappingTest.skippedEdgeHasNoRenderedLine]==] [==[SoBrepEdgeSetMappingTest.emptyMappingHasNoRenderedEdges]==] [==[SoBrepEdgeSetMappingTest.edgeBeyondMappingHasNoRenderedLine]==] [==[SoBrepEdgeSetMappingTest.lineBeyondMappingHasNoEdge]==] [==[SoBrepEdgeSetMappingTest.withoutMappingFallsBackToOneLinePerEdge]==] [==[SoBrepEdgeSetMappingTest.mappingRoundTrips]==] [==[SoBrepEdgeSetMappingTest.remappingReplacesThePreviousMapping]==])
