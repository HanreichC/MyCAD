add_test([=[KDTreeTest.TestKDTreeEmpty]=]  /workspace/build/tests/Mesh_tests_run [==[--gtest_filter=KDTreeTest.TestKDTreeEmpty]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[KDTreeTest.TestKDTreeEmpty]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Mesh/App/Core/KDTree.cpp:35]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[KDTreeTest.TestKDTreeNearestEmpty]=]  /workspace/build/tests/Mesh_tests_run [==[--gtest_filter=KDTreeTest.TestKDTreeNearestEmpty]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[KDTreeTest.TestKDTreeNearestEmpty]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Mesh/App/Core/KDTree.cpp:41]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[KDTreeTest.TestKDTreeNearest]=]  /workspace/build/tests/Mesh_tests_run [==[--gtest_filter=KDTreeTest.TestKDTreeNearest]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[KDTreeTest.TestKDTreeNearest]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Mesh/App/Core/KDTree.cpp:51]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[KDTreeTest.TestKDTreeNearestMaxDist]=]  /workspace/build/tests/Mesh_tests_run [==[--gtest_filter=KDTreeTest.TestKDTreeNearestMaxDist]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[KDTreeTest.TestKDTreeNearestMaxDist]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Mesh/App/Core/KDTree.cpp:62]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[KDTreeTest.TestKDTreeFindExact]=]  /workspace/build/tests/Mesh_tests_run [==[--gtest_filter=KDTreeTest.TestKDTreeFindExact]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[KDTreeTest.TestKDTreeFindExact]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Mesh/App/Core/KDTree.cpp:76]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[KDTreeTest.TestKDTreeFindRange]=]  /workspace/build/tests/Mesh_tests_run [==[--gtest_filter=KDTreeTest.TestKDTreeFindRange]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[KDTreeTest.TestKDTreeFindRange]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Mesh/App/Core/KDTree.cpp:85]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MeshIO.LoadAsciiSTLWithoutTrailingNewline]=]  /workspace/build/tests/Mesh_tests_run [==[--gtest_filter=MeshIO.LoadAsciiSTLWithoutTrailingNewline]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MeshIO.LoadAsciiSTLWithoutTrailingNewline]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Mesh/App/Core/MeshIO.cpp:8]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ExporterTest.TestSingleMesh]=]  /workspace/build/tests/Mesh_tests_run [==[--gtest_filter=ExporterTest.TestSingleMesh]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ExporterTest.TestSingleMesh]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Mesh/App/Exporter.cpp:78]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ExporterTest.TestMultipleMeshes]=]  /workspace/build/tests/Mesh_tests_run [==[--gtest_filter=ExporterTest.TestMultipleMeshes]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ExporterTest.TestMultipleMeshes]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Mesh/App/Exporter.cpp:102]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ExporterTest.TestMeshesInPart]=]  /workspace/build/tests/Mesh_tests_run [==[--gtest_filter=ExporterTest.TestMeshesInPart]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ExporterTest.TestMeshesInPart]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Mesh/App/Exporter.cpp:127]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ImporterTest.Test3MF]=]  /workspace/build/tests/Mesh_tests_run [==[--gtest_filter=ImporterTest.Test3MF]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ImporterTest.Test3MF]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Mesh/App/Importer.cpp:20]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ImporterTest.TestOBJ]=]  /workspace/build/tests/Mesh_tests_run [==[--gtest_filter=ImporterTest.TestOBJ]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ImporterTest.TestOBJ]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Mesh/App/Importer.cpp:44]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MeshTest.TestDefault]=]  /workspace/build/tests/Mesh_tests_run [==[--gtest_filter=MeshTest.TestDefault]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MeshTest.TestDefault]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Mesh/App/Mesh.cpp:19]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MeshTest.TestGrid1OfPlanarMesh]=]  /workspace/build/tests/Mesh_tests_run [==[--gtest_filter=MeshTest.TestGrid1OfPlanarMesh]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MeshTest.TestGrid1OfPlanarMesh]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Mesh/App/Mesh.cpp:32]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MeshTest.TestGrid2OfPlanarMesh]=]  /workspace/build/tests/Mesh_tests_run [==[--gtest_filter=MeshTest.TestGrid2OfPlanarMesh]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MeshTest.TestGrid2OfPlanarMesh]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Mesh/App/Mesh.cpp:52]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MeshTest.TestGrid1OfAlmostPlanarMesh]=]  /workspace/build/tests/Mesh_tests_run [==[--gtest_filter=MeshTest.TestGrid1OfAlmostPlanarMesh]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MeshTest.TestGrid1OfAlmostPlanarMesh]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Mesh/App/Mesh.cpp:72]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MeshTest.TestGrid2OfAlmostPlanarMesh]=]  /workspace/build/tests/Mesh_tests_run [==[--gtest_filter=MeshTest.TestGrid2OfAlmostPlanarMesh]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MeshTest.TestGrid2OfAlmostPlanarMesh]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Mesh/App/Mesh.cpp:92]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MeshFeatureTest.getElementTypes]=]  /workspace/build/tests/Mesh_tests_run [==[--gtest_filter=MeshFeatureTest.getElementTypes]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MeshFeatureTest.getElementTypes]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Mesh/App/MeshFeature.cpp:23]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MeshFeatureTest.getComplexElementTypes]=]  /workspace/build/tests/Mesh_tests_run [==[--gtest_filter=MeshFeatureTest.getComplexElementTypes]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MeshFeatureTest.getComplexElementTypes]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/Mod/Mesh/App/MeshFeature.cpp:33]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
set(Mesh_tests_run_TESTS [==[KDTreeTest.TestKDTreeEmpty]==] [==[KDTreeTest.TestKDTreeNearestEmpty]==] [==[KDTreeTest.TestKDTreeNearest]==] [==[KDTreeTest.TestKDTreeNearestMaxDist]==] [==[KDTreeTest.TestKDTreeFindExact]==] [==[KDTreeTest.TestKDTreeFindRange]==] [==[MeshIO.LoadAsciiSTLWithoutTrailingNewline]==] [==[ExporterTest.TestSingleMesh]==] [==[ExporterTest.TestMultipleMeshes]==] [==[ExporterTest.TestMeshesInPart]==] [==[ImporterTest.Test3MF]==] [==[ImporterTest.TestOBJ]==] [==[MeshTest.TestDefault]==] [==[MeshTest.TestGrid1OfPlanarMesh]==] [==[MeshTest.TestGrid2OfPlanarMesh]==] [==[MeshTest.TestGrid1OfAlmostPlanarMesh]==] [==[MeshTest.TestGrid2OfAlmostPlanarMesh]==] [==[MeshFeatureTest.getElementTypes]==] [==[MeshFeatureTest.getComplexElementTypes]==])
