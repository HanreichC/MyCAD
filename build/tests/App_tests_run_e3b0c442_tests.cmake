add_test([=[AsyncRecomputeTest.CloseDocumentWaitsForInFlightAsyncRecompute]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=AsyncRecomputeTest.CloseDocumentWaitsForInFlightAsyncRecompute]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AsyncRecomputeTest.CloseDocumentWaitsForInFlightAsyncRecompute]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/AsyncRecompute.cpp:61]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[AsyncRecomputeTest.WorkerSafetyIsCheckedFromRequest]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=AsyncRecomputeTest.WorkerSafetyIsCheckedFromRequest]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[AsyncRecomputeTest.WorkerSafetyIsCheckedFromRequest]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/AsyncRecompute.cpp:94]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationTest.fCustomSyntaxLookup]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationTest.fCustomSyntaxLookup]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationTest.fCustomSyntaxLookup]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Application.cpp:24]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationTest.fCustomSyntaxMac]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationTest.fCustomSyntaxMac]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationTest.fCustomSyntaxMac]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Application.cpp:30]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationTest.fCustomSyntaxWidgetCount]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationTest.fCustomSyntaxWidgetCount]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationTest.fCustomSyntaxWidgetCount]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Application.cpp:36]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationTest.fCustomSyntaxNotFound]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationTest.fCustomSyntaxNotFound]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationTest.fCustomSyntaxNotFound]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Application.cpp:42]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationTest.fCustomSyntaxAmpersand]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationTest.fCustomSyntaxAmpersand]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationTest.fCustomSyntaxAmpersand]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Application.cpp:48]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationTest.fCustomSyntaxEmptyIn]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationTest.fCustomSyntaxEmptyIn]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationTest.fCustomSyntaxEmptyIn]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Application.cpp:54]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.usingCurrentVersionConfigTrueWhenDirMatchesVersion]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.usingCurrentVersionConfigTrueWhenDirMatchesVersion]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.usingCurrentVersionConfigTrueWhenDirMatchesVersion]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:125]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.usingCurrentVersionConfigFalseWhenDirDoesntMatchVersion]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.usingCurrentVersionConfigFalseWhenDirDoesntMatchVersion]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.usingCurrentVersionConfigFalseWhenDirDoesntMatchVersion]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:140]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.isVersionedPathMatchesCurrentMajorAndMinor]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.isVersionedPathMatchesCurrentMajorAndMinor]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.isVersionedPathMatchesCurrentMajorAndMinor]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:160]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.isVersionedPathMatchesLowerMinorSameMajor]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.isVersionedPathMatchesLowerMinorSameMajor]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.isVersionedPathMatchesLowerMinorSameMajor]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:168]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.isVersionedPathMatchesLowerMajorAnyMinor]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.isVersionedPathMatchesLowerMajorAnyMinor]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.isVersionedPathMatchesLowerMajorAnyMinor]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:176]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.isVersionedPathMatchesZeroMinorSameMajor]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.isVersionedPathMatchesZeroMinorSameMajor]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.isVersionedPathMatchesZeroMinorSameMajor]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:184]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.isVersionedPathDoesNotMatchHigherMinorSameMajor]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.isVersionedPathDoesNotMatchHigherMinorSameMajor]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.isVersionedPathDoesNotMatchHigherMinorSameMajor]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:192]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.isVersionedPathDoesNotMatchHigherMajorOrRandomName]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.isVersionedPathDoesNotMatchHigherMajorOrRandomName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.isVersionedPathDoesNotMatchHigherMajorOrRandomName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:200]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.mostRecentAvailReturnsExactCurrentVersionIfDirectoryExists]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.mostRecentAvailReturnsExactCurrentVersionIfDirectoryExists]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.mostRecentAvailReturnsExactCurrentVersionIfDirectoryExists]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:226]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.mostRecentAvailPrefersSameMajorAndPicksHighestLowerMinor]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.mostRecentAvailPrefersSameMajorAndPicksHighestLowerMinor]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.mostRecentAvailPrefersSameMajorAndPicksHighestLowerMinor]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:239]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.mostRecentAvailForLowerMajorPicksHighestAvailableMinor]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.mostRecentAvailForLowerMajorPicksHighestAvailableMinor]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.mostRecentAvailForLowerMajorPicksHighestAvailableMinor]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:254]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.mostRecentAvailSkipsFilesAndFallsBackToNextDirectory]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.mostRecentAvailSkipsFilesAndFallsBackToNextDirectory]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.mostRecentAvailSkipsFilesAndFallsBackToNextDirectory]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:268]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.mostRecentAvailIgnoresHigherMinorThanCurrentInSameMajor]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.mostRecentAvailIgnoresHigherMinorThanCurrentInSameMajor]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.mostRecentAvailIgnoresHigherMinorThanCurrentInSameMajor]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:282]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.mostRecentAvailReturnsEmptyStringWhenNoVersionsPresent]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.mostRecentAvailReturnsEmptyStringWhenNoVersionsPresent]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.mostRecentAvailReturnsEmptyStringWhenNoVersionsPresent]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:295]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.mostRecentConfigReturnsCurrentVersionDirectoryIfPresent]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.mostRecentConfigReturnsCurrentVersionDirectoryIfPresent]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.mostRecentConfigReturnsCurrentVersionDirectoryIfPresent]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:303]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.mostRecentConfigFallsBackToMostRecentInSameMajorWhenCurrentMissing]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.mostRecentConfigFallsBackToMostRecentInSameMajorWhenCurrentMissing]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.mostRecentConfigFallsBackToMostRecentInSameMajorWhenCurrentMissing]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:313]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.mostRecentConfigSkipsFileAtCurrentVersionAndFallsBack]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.mostRecentConfigSkipsFileAtCurrentVersionAndFallsBack]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.mostRecentConfigSkipsFileAtCurrentVersionAndFallsBack]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:327]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.mostRecentConfigFallsBackToHighestVersionInLowerMajors]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.mostRecentConfigFallsBackToHighestVersionInLowerMajors]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.mostRecentConfigFallsBackToHighestVersionInLowerMajors]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:339]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.mostRecentConfigReturnsStartingPathWhenNoVersionedConfigExists]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.mostRecentConfigReturnsStartingPathWhenNoVersionedConfigExists]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.mostRecentConfigReturnsStartingPathWhenNoVersionedConfigExists]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:356]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.usingCurrentVersionExactVersionDir]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.usingCurrentVersionExactVersionDir]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.usingCurrentVersionExactVersionDir]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:364]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.usingCurrentVersionVersionDirWithTrailingSlash]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.usingCurrentVersionVersionDirWithTrailingSlash]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.usingCurrentVersionVersionDirWithTrailingSlash]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:373]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.usingCurrentVersionFileInsideVersionDirIsFalse]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.usingCurrentVersionFileInsideVersionDirIsFalse]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.usingCurrentVersionFileInsideVersionDirIsFalse]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:383]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.usingCurrentVersionLowerVersionDirIsFalse]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.usingCurrentVersionLowerVersionDirIsFalse]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.usingCurrentVersionLowerVersionDirIsFalse]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:393]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.usingCurrentVersionHigherVersionDirIsFalse]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.usingCurrentVersionHigherVersionDirIsFalse]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.usingCurrentVersionHigherVersionDirIsFalse]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:402]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.usingCurrentVersionNonVersionDirIsFalse]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.usingCurrentVersionNonVersionDirIsFalse]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.usingCurrentVersionNonVersionDirIsFalse]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:411]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.migrateConfigCreatesDestinationAndCopiesFiles]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.migrateConfigCreatesDestinationAndCopiesFiles]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.migrateConfigCreatesDestinationAndCopiesFiles]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:433]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.migrateConfigSkipsSelfWhenNewIsSubdirectoryOfOld]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.migrateConfigSkipsSelfWhenNewIsSubdirectoryOfOld]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.migrateConfigSkipsSelfWhenNewIsSubdirectoryOfOld]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:459]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.migrateConfigEmptyOldPathJustCreatesDestination]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.migrateConfigEmptyOldPathJustCreatesDestination]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.migrateConfigEmptyOldPathJustCreatesDestination]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:481]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.migrateConfigRecursivelyCopiesDirectoriesAndFiles]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.migrateConfigRecursivelyCopiesDirectoriesAndFiles]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.migrateConfigRecursivelyCopiesDirectoriesAndFiles]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:498]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.migrateConfigNewPathSubdirRecursivelyCopiesAndSkipsSelf]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.migrateConfigNewPathSubdirRecursivelyCopiesAndSkipsSelf]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.migrateConfigNewPathSubdirRecursivelyCopiesAndSkipsSelf]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:526]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.migrateAllPathsVersionedInputChoosesParentPlusCurrent]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.migrateAllPathsVersionedInputChoosesParentPlusCurrent]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.migrateAllPathsVersionedInputChoosesParentPlusCurrent]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:548]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.migrateAllPathsNonVersionedInputAppendsCurrent]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.migrateAllPathsNonVersionedInputAppendsCurrent]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.migrateAllPathsNonVersionedInputAppendsCurrent]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:566]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.migrateAllPathsIgnoresIfDestinationAlreadyExists_NonVersioned]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.migrateAllPathsIgnoresIfDestinationAlreadyExists_NonVersioned]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.migrateAllPathsIgnoresIfDestinationAlreadyExists_NonVersioned]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:583]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.migrateConfigSkipsBrokenSymlink]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.migrateConfigSkipsBrokenSymlink]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.migrateConfigSkipsBrokenSymlink]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:598]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.migrateConfigCopiesValidSymlink]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.migrateConfigCopiesValidSymlink]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.migrateConfigCopiesValidSymlink]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:619]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.migrateAllPathsReturnsSkippedPaths]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.migrateAllPathsReturnsSkippedPaths]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.migrateAllPathsReturnsSkippedPaths]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:638]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.migrateAllPathsProcessesMultipleInputs]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.migrateAllPathsProcessesMultipleInputs]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.migrateAllPathsProcessesMultipleInputs]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:660]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.appendVecAlreadyVersionedBails]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.appendVecAlreadyVersionedBails]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.appendVecAlreadyVersionedBails]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:683]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.appendVecBaseExistsAppendsCurrentWhenPresent]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.appendVecBaseExistsAppendsCurrentWhenPresent]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.appendVecBaseExistsAppendsCurrentWhenPresent]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:700]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.appendVecPicksHighestLowerMinorInSameMajor]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.appendVecPicksHighestLowerMinorInSameMajor]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.appendVecPicksHighestLowerMinorInSameMajor]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:716]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.appendVecFallsBackToLowerMajor]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.appendVecFallsBackToLowerMajor]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.appendVecFallsBackToLowerMajor]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:734]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.appendVecNoVersionedChildrenLeavesVectorUnchanged]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.appendVecNoVersionedChildrenLeavesVectorUnchanged]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.appendVecNoVersionedChildrenLeavesVectorUnchanged]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:750]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.appendVecBaseMissingAppendsCurrentSuffix]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.appendVecBaseMissingAppendsCurrentSuffix]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.appendVecBaseMissingAppendsCurrentSuffix]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:764]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.extractVersionSucceedsWithPlainIntegers]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.extractVersionSucceedsWithPlainIntegers]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.extractVersionSucceedsWithPlainIntegers]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:778]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.extractVersionSucceedsWithWhitespace]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.extractVersionSucceedsWithWhitespace]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.extractVersionSucceedsWithWhitespace]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:788]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.extractVersionMissingMajorThrowsRuntimeError]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.extractVersionMissingMajorThrowsRuntimeError]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.extractVersionMissingMajorThrowsRuntimeError]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:801]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.extractVersionMissingMinorThrowsRuntimeError]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.extractVersionMissingMinorThrowsRuntimeError]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.extractVersionMissingMinorThrowsRuntimeError]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:809]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.extractVersionNonNumericThrowsRuntimeError]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.extractVersionNonNumericThrowsRuntimeError]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.extractVersionNonNumericThrowsRuntimeError]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:817]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.extractVersionOverflowThrowsRuntimeError]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.extractVersionOverflowThrowsRuntimeError]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.extractVersionOverflowThrowsRuntimeError]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:825]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.extractVersionNegativeNumbersPassThrough]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.extractVersionNegativeNumbersPassThrough]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.extractVersionNegativeNumbersPassThrough]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:836]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.sanitizeRemovesNullCharacterAtEnd]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.sanitizeRemovesNullCharacterAtEnd]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.sanitizeRemovesNullCharacterAtEnd]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:846]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.sanitizeReturnsUnchangedIfNoNullCharacter]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.sanitizeReturnsUnchangedIfNoNullCharacter]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.sanitizeReturnsUnchangedIfNoNullCharacter]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:855]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.appendCreateBaseExistsAppendsCurrentWhenAlreadyPresent]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.appendCreateBaseExistsAppendsCurrentWhenAlreadyPresent]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.appendCreateBaseExistsAppendsCurrentWhenAlreadyPresent]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:867]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.appendCreateBaseExistsUsesCurrentEvenWhenOlderVersionPresent]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.appendCreateBaseExistsUsesCurrentEvenWhenOlderVersionPresent]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.appendCreateBaseExistsUsesCurrentEvenWhenOlderVersionPresent]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:884]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.appendCreateBaseExistsNoVersionsAppendsAndCreatesDir]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.appendCreateBaseExistsNoVersionsAppendsAndCreatesDir]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.appendCreateBaseExistsNoVersionsAppendsAndCreatesDir]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:900]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.appendDoNotAppendBaseExistsNoVersionsLeavesUnchanged]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.appendDoNotAppendBaseExistsNoVersionsLeavesUnchanged]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.appendDoNotAppendBaseExistsNoVersionsLeavesUnchanged]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:917]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.appendCreateBaseMissingAppendsCurrentSuffix]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.appendCreateBaseMissingAppendsCurrentSuffix]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.appendCreateBaseMissingAppendsCurrentSuffix]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:933]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ApplicationDirectoriesTest.appendCreateAlreadyVersionedBails]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ApplicationDirectoriesTest.appendCreateAlreadyVersionedBails]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ApplicationDirectoriesTest.appendCreateAlreadyVersionedBails]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ApplicationDirectories.cpp:947]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BackupPolicyTest.StandardSourceDoesNotExist]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=BackupPolicyTest.StandardSourceDoesNotExist]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BackupPolicyTest.StandardSourceDoesNotExist]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/BackupPolicy.cpp:122]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BackupPolicyTest.StandardWithZeroFilesDeletesExisting]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=BackupPolicyTest.StandardWithZeroFilesDeletesExisting]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BackupPolicyTest.StandardWithZeroFilesDeletesExisting]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/BackupPolicy.cpp:131]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BackupPolicyTest.StandardWithOneFileNoPreviousBackups]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=BackupPolicyTest.StandardWithOneFileNoPreviousBackups]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BackupPolicyTest.StandardWithOneFileNoPreviousBackups]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/BackupPolicy.cpp:146]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BackupPolicyTest.StandardWithOneFileOnePreviousBackup]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=BackupPolicyTest.StandardWithOneFileOnePreviousBackup]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BackupPolicyTest.StandardWithOneFileOnePreviousBackup]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/BackupPolicy.cpp:160]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BackupPolicyTest.StandardWithTwoFilesOnePreviousBackup]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=BackupPolicyTest.StandardWithTwoFilesOnePreviousBackup]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BackupPolicyTest.StandardWithTwoFilesOnePreviousBackup]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/BackupPolicy.cpp:176]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BackupPolicyTest.StandardWithTwoFilesOnePreviousBackupUnexpectedSuffix]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=BackupPolicyTest.StandardWithTwoFilesOnePreviousBackupUnexpectedSuffix]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BackupPolicyTest.StandardWithTwoFilesOnePreviousBackupUnexpectedSuffix]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/BackupPolicy.cpp:192]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BackupPolicyTest.StandardWithTwoFilesOnePreviousBackupOutOfSequenceNumber]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=BackupPolicyTest.StandardWithTwoFilesOnePreviousBackupOutOfSequenceNumber]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BackupPolicyTest.StandardWithTwoFilesOnePreviousBackupOutOfSequenceNumber]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/BackupPolicy.cpp:210]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BackupPolicyTest.StandardWithFCBakSet]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=BackupPolicyTest.StandardWithFCBakSet]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BackupPolicyTest.StandardWithFCBakSet]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/BackupPolicy.cpp:230]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BackupPolicyTest.TimestampSourceDoesNotExist]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=BackupPolicyTest.TimestampSourceDoesNotExist]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BackupPolicyTest.TimestampSourceDoesNotExist]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/BackupPolicy.cpp:244]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BackupPolicyTest.TimestampNoSourceGiven]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=BackupPolicyTest.TimestampNoSourceGiven]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BackupPolicyTest.TimestampNoSourceGiven]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/BackupPolicy.cpp:253]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BackupPolicyTest.TimestampNoTargetGiven]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=BackupPolicyTest.TimestampNoTargetGiven]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BackupPolicyTest.TimestampNoTargetGiven]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/BackupPolicy.cpp:263]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BackupPolicyTest.TimestampWithZeroFilesDeletesExisting]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=BackupPolicyTest.TimestampWithZeroFilesDeletesExisting]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BackupPolicyTest.TimestampWithZeroFilesDeletesExisting]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/BackupPolicy.cpp:273]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BackupPolicyTest.TimestampWithOneFileAndNoneExistingNotFCBakCreatesNumberedFile]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=BackupPolicyTest.TimestampWithOneFileAndNoneExistingNotFCBakCreatesNumberedFile]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BackupPolicyTest.TimestampWithOneFileAndNoneExistingNotFCBakCreatesNumberedFile]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/BackupPolicy.cpp:288]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BackupPolicyTest.TimestampSourceHasNoExtension]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=BackupPolicyTest.TimestampSourceHasNoExtension]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BackupPolicyTest.TimestampSourceHasNoExtension]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/BackupPolicy.cpp:304]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BackupPolicyTest.TimestampTargetHasNoExtension]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=BackupPolicyTest.TimestampTargetHasNoExtension]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BackupPolicyTest.TimestampTargetHasNoExtension]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/BackupPolicy.cpp:319]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BackupPolicyTest.TimestampWithOneFileAndNoneExistingFCBakCreatesDatedFile]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=BackupPolicyTest.TimestampWithOneFileAndNoneExistingFCBakCreatesDatedFile]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BackupPolicyTest.TimestampWithOneFileAndNoneExistingFCBakCreatesDatedFile]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/BackupPolicy.cpp:334]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BackupPolicyTest.TimestampReplacesDotsWithDashes]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=BackupPolicyTest.TimestampReplacesDotsWithDashes]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BackupPolicyTest.TimestampReplacesDotsWithDashes]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/BackupPolicy.cpp:349]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BackupPolicyTest.TimestampWithInvalidFormatStringThrows]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=BackupPolicyTest.DISABLED_TimestampWithInvalidFormatStringThrows]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BackupPolicyTest.TimestampWithInvalidFormatStringThrows]=]
  PROPERTIES
    DISABLED YES
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/BackupPolicy.cpp:364]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BackupPolicyTest.TimestampWithAbsurdlyLongFormatStringThrows]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=BackupPolicyTest.DISABLED_TimestampWithAbsurdlyLongFormatStringThrows]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BackupPolicyTest.TimestampWithAbsurdlyLongFormatStringThrows]=]
  PROPERTIES
    DISABLED YES
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/BackupPolicy.cpp:378]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BackupPolicyTest.TimestampDetectsOldBackupFormat]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=BackupPolicyTest.TimestampDetectsOldBackupFormat]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BackupPolicyTest.TimestampDetectsOldBackupFormat]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/BackupPolicy.cpp:398]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BackupPolicyTest.TimestampDetectsOldBackupFormatIgnoresOther]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=BackupPolicyTest.TimestampDetectsOldBackupFormatIgnoresOther]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BackupPolicyTest.TimestampDetectsOldBackupFormatIgnoresOther]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/BackupPolicy.cpp:417]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BackupPolicyTest.TimestampDetectsAndRetainsOldBackupWhenAllowed]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=BackupPolicyTest.TimestampDetectsAndRetainsOldBackupWhenAllowed]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BackupPolicyTest.TimestampDetectsAndRetainsOldBackupWhenAllowed]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/BackupPolicy.cpp:438]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BackupPolicyTest.TimestampFormatStringEndsWithSpace]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=BackupPolicyTest.TimestampFormatStringEndsWithSpace]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BackupPolicyTest.TimestampFormatStringEndsWithSpace]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/BackupPolicy.cpp:458]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BackupPolicyTest.TimestampFormatStringEndsWithDash]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=BackupPolicyTest.TimestampFormatStringEndsWithDash]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BackupPolicyTest.TimestampFormatStringEndsWithDash]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/BackupPolicy.cpp:476]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BackupPolicyTest.TimestampFormatFileAlreadyExists]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=BackupPolicyTest.TimestampFormatFileAlreadyExists]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BackupPolicyTest.TimestampFormatFileAlreadyExists]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/BackupPolicy.cpp:494]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[BackupPolicyTest.TimestampFormatFileAlreadyExistsMultipleTimes]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=BackupPolicyTest.TimestampFormatFileAlreadyExistsMultipleTimes]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[BackupPolicyTest.TimestampFormatFileAlreadyExistsMultipleTimes]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/BackupPolicy.cpp:514]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Branding.one]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Branding.one]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Branding.one]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Branding.cpp:7]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ComplexGeoDataTest.getIndexedNameNoName]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ComplexGeoDataTest.getIndexedNameNoName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ComplexGeoDataTest.getIndexedNameNoName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ComplexGeoData.cpp:98]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ComplexGeoDataTest.getIndexedNameNoElementMap]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ComplexGeoDataTest.getIndexedNameNoElementMap]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ComplexGeoDataTest.getIndexedNameNoElementMap]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ComplexGeoData.cpp:107]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ComplexGeoDataTest.getMappedNameNoElement]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ComplexGeoDataTest.getMappedNameNoElement]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ComplexGeoDataTest.getMappedNameNoElement]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ComplexGeoData.cpp:116]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ComplexGeoDataTest.getMappedNameDisallowUnmappedNoMap]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ComplexGeoDataTest.getMappedNameDisallowUnmappedNoMap]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ComplexGeoDataTest.getMappedNameDisallowUnmappedNoMap]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ComplexGeoData.cpp:125]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ComplexGeoDataTest.getMappedNameDisallowUnmappedWithMap]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ComplexGeoDataTest.getMappedNameDisallowUnmappedWithMap]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ComplexGeoDataTest.getMappedNameDisallowUnmappedWithMap]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ComplexGeoData.cpp:134]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ComplexGeoDataTest.getMappedNameDisallowUnmappedMissingFromMap]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ComplexGeoDataTest.getMappedNameDisallowUnmappedMissingFromMap]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ComplexGeoDataTest.getMappedNameDisallowUnmappedMissingFromMap]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ComplexGeoData.cpp:151]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ComplexGeoDataTest.getMappedNameAllowUnmapped]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ComplexGeoDataTest.getMappedNameAllowUnmapped]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ComplexGeoDataTest.getMappedNameAllowUnmapped]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ComplexGeoData.cpp:164]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ComplexGeoDataTest.getElementNameGivenIndexedName]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ComplexGeoDataTest.getElementNameGivenIndexedName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ComplexGeoDataTest.getElementNameGivenIndexedName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ComplexGeoData.cpp:173]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ComplexGeoDataTest.getElementNameGivenMappedName]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ComplexGeoDataTest.getElementNameGivenMappedName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ComplexGeoDataTest.getElementNameGivenMappedName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ComplexGeoData.cpp:186]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ComplexGeoDataTest.getElementMappedNamesNoMapNoUnmapped]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ComplexGeoDataTest.getElementMappedNamesNoMapNoUnmapped]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ComplexGeoDataTest.getElementMappedNamesNoMapNoUnmapped]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ComplexGeoData.cpp:199]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ComplexGeoDataTest.getElementMappedNamesWithMapNoUnmapped]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ComplexGeoDataTest.getElementMappedNamesWithMapNoUnmapped]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ComplexGeoDataTest.getElementMappedNamesWithMapNoUnmapped]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ComplexGeoData.cpp:212]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ComplexGeoDataTest.getElementMappedNamesNoMapWithUnmapped]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ComplexGeoDataTest.getElementMappedNamesNoMapWithUnmapped]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ComplexGeoDataTest.getElementMappedNamesNoMapWithUnmapped]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ComplexGeoData.cpp:229]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ComplexGeoDataTest.getElementMappedNamesWithMapWithUnmapped]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ComplexGeoDataTest.getElementMappedNamesWithMapWithUnmapped]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ComplexGeoDataTest.getElementMappedNamesWithMapWithUnmapped]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ComplexGeoData.cpp:242]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ComplexGeoDataTest.elementTypeValidIndexName]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ComplexGeoDataTest.elementTypeValidIndexName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ComplexGeoDataTest.elementTypeValidIndexName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ComplexGeoData.cpp:258]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ComplexGeoDataTest.elementTypeInvalidIndexedName]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ComplexGeoDataTest.elementTypeInvalidIndexedName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ComplexGeoDataTest.elementTypeInvalidIndexedName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ComplexGeoData.cpp:270]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ComplexGeoDataTest.elementTypeCharEmptyName]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ComplexGeoDataTest.elementTypeCharEmptyName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ComplexGeoDataTest.elementTypeCharEmptyName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ComplexGeoData.cpp:282]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ComplexGeoDataTest.elementTypeCharIndexedName]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ComplexGeoDataTest.elementTypeCharIndexedName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ComplexGeoDataTest.elementTypeCharIndexedName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ComplexGeoData.cpp:291]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ComplexGeoDataTest.elementTypeCharMappedNameNoPrefix]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ComplexGeoDataTest.elementTypeCharMappedNameNoPrefix]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ComplexGeoDataTest.elementTypeCharMappedNameNoPrefix]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ComplexGeoData.cpp:300]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ComplexGeoDataTest.elementTypeCharMappedNameWithPrefix]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ComplexGeoDataTest.elementTypeCharMappedNameWithPrefix]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ComplexGeoDataTest.elementTypeCharMappedNameWithPrefix]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ComplexGeoData.cpp:315]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ComplexGeoDataTest.resetElementMapNoArgument]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ComplexGeoDataTest.resetElementMapNoArgument]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ComplexGeoDataTest.resetElementMapNoArgument]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ComplexGeoData.cpp:332]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ComplexGeoDataTest.resetElementMapWithArgument]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ComplexGeoDataTest.resetElementMapWithArgument]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ComplexGeoDataTest.resetElementMapWithArgument]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ComplexGeoData.cpp:341]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ComplexGeoDataTest.setAndGetElementMap]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ComplexGeoDataTest.setAndGetElementMap]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ComplexGeoDataTest.setAndGetElementMap]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ComplexGeoData.cpp:356]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ComplexGeoDataTest.getElementMapSize]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ComplexGeoDataTest.getElementMapSize]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ComplexGeoDataTest.getElementMapSize]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ComplexGeoData.cpp:379]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ComplexGeoDataTest.flushElementMap]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ComplexGeoDataTest.flushElementMap]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ComplexGeoDataTest.flushElementMap]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ComplexGeoData.cpp:395]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ComplexGeoDataTest.saveWithNoElementMap]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ComplexGeoDataTest.saveWithNoElementMap]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ComplexGeoDataTest.saveWithNoElementMap]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ComplexGeoData.cpp:400]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ComplexGeoDataTest.saveWithElementMap]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ComplexGeoDataTest.saveWithElementMap]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ComplexGeoDataTest.saveWithElementMap]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ComplexGeoData.cpp:413]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ComplexGeoDataTest.saveWithPersistenceFilename]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ComplexGeoDataTest.saveWithPersistenceFilename]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ComplexGeoDataTest.saveWithPersistenceFilename]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ComplexGeoData.cpp:429]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ComplexGeoDataTest.saveDocFileWithNoElementMap]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ComplexGeoDataTest.saveDocFileWithNoElementMap]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ComplexGeoDataTest.saveDocFileWithNoElementMap]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ComplexGeoData.cpp:444]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ComplexGeoDataTest.saveDocFileWithElementMap]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ComplexGeoDataTest.saveDocFileWithElementMap]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ComplexGeoDataTest.saveDocFileWithElementMap]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ComplexGeoData.cpp:457]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ComplexGeoDataTest.restoreStream]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ComplexGeoDataTest.restoreStream]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ComplexGeoDataTest.restoreStream]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ComplexGeoData.cpp:470]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ComplexGeoDataTest.traceElement]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ComplexGeoDataTest.traceElement]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ComplexGeoDataTest.traceElement]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ComplexGeoData.cpp:473]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DocumentTest.addStringHasherIndicatesUnwrittenWhenNew]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=DocumentTest.addStringHasherIndicatesUnwrittenWhenNew]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DocumentTest.addStringHasherIndicatesUnwrittenWhenNew]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Document.cpp:61]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DocumentTest.addStringHasherIndicatesAlreadyWritten]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=DocumentTest.addStringHasherIndicatesAlreadyWritten]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DocumentTest.addStringHasherIndicatesAlreadyWritten]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Document.cpp:74]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DocumentTest.getStringHasherGivesExpectedHasher]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=DocumentTest.getStringHasherGivesExpectedHasher]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DocumentTest.getStringHasherGivesExpectedHasher]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Document.cpp:87]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DocumentTest.importObjectsRestoresSourceStringHasher]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=DocumentTest.importObjectsRestoresSourceStringHasher]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DocumentTest.importObjectsRestoresSourceStringHasher]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Document.cpp:101]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DocumentObjectTest.getSubObjectList]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=DocumentObjectTest.getSubObjectList]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DocumentObjectTest.getSubObjectList]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/DocumentObject.cpp:44]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DocumentObserverTest.hasSubObject]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=DISABLED_DocumentObserverTest.hasSubObject]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DocumentObserverTest.hasSubObject]=]
  PROPERTIES
    DISABLED YES
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/DocumentObserver.cpp:43]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DocumentObserverTest.hasSubElement]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=DISABLED_DocumentObserverTest.hasSubElement]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DocumentObserverTest.hasSubElement]=]
  PROPERTIES
    DISABLED YES
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/DocumentObserver.cpp:86]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DocumentObserverTest.normalize]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=DISABLED_DocumentObserverTest.normalize]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DocumentObserverTest.normalize]=]
  PROPERTIES
    DISABLED YES
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/DocumentObserver.cpp:130]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[DocumentObserverTest.normalized]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=DISABLED_DocumentObserverTest.normalized]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[DocumentObserverTest.normalized]=]
  PROPERTIES
    DISABLED YES
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/DocumentObserver.cpp:313]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Expression.tokenize]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Expression.tokenize]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Expression.tokenize]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:49]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Expression.tokenizeCompletion]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Expression.tokenizeCompletion]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Expression.tokenizeCompletion]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:60]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Expression.tokenizeQuantity]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Expression.tokenizeQuantity]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Expression.tokenizeQuantity]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:69]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Expression.tokenizeFunc]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Expression.tokenizeFunc]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Expression.tokenizeFunc]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:81]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Expression.tokenizeOne]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Expression.tokenizeOne]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Expression.tokenizeOne]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:95]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Expression.tokenizeNum]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Expression.tokenizeNum]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Expression.tokenizeNum]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:104]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Expression.tokenizeID]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Expression.tokenizeID]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Expression.tokenizeID]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:113]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Expression.tokenizeUnit]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Expression.tokenizeUnit]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Expression.tokenizeUnit]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:122]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Expression.tokenizeUSUnit]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Expression.tokenizeUSUnit]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Expression.tokenizeUSUnit]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:131]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Expression.tokenizeInt]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Expression.tokenizeInt]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Expression.tokenizeInt]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:140]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Expression.tokenizePi]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Expression.tokenizePi]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Expression.tokenizePi]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:149]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Expression.tokenizeE]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Expression.tokenizeE]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Expression.tokenizeE]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:158]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Expression.tokenizeConstant]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Expression.tokenizeConstant]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Expression.tokenizeConstant]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:167]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Expression.tokenizeEqual]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Expression.tokenizeEqual]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Expression.tokenizeEqual]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:180]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Expression.tokenizeNotEqual]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Expression.tokenizeNotEqual]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Expression.tokenizeNotEqual]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:189]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Expression.tokenizeLessThan]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Expression.tokenizeLessThan]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Expression.tokenizeLessThan]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:198]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Expression.tokenizeLessThanEqual]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Expression.tokenizeLessThanEqual]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Expression.tokenizeLessThanEqual]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:207]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Expression.tokenizeGreaterThan]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Expression.tokenizeGreaterThan]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Expression.tokenizeGreaterThan]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:216]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Expression.tokenizeGreaterThanEqual]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Expression.tokenizeGreaterThanEqual]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Expression.tokenizeGreaterThanEqual]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:225]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Expression.tokenizeMinus]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Expression.tokenizeMinus]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Expression.tokenizeMinus]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:234]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Expression.tokenizeCell1]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Expression.tokenizeCell1]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Expression.tokenizeCell1]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:243]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Expression.tokenizeCell2]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Expression.tokenizeCell2]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Expression.tokenizeCell2]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:252]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Expression.tokenizeCell3]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Expression.tokenizeCell3]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Expression.tokenizeCell3]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:261]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Expression.tokenizeString]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Expression.tokenizeString]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Expression.tokenizeString]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:270]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Expression.tokenizeExponent]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Expression.tokenizeExponent]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Expression.tokenizeExponent]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:279]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Expression.tokenizeNumAndUnit]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Expression.tokenizeNumAndUnit]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Expression.tokenizeNumAndUnit]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:284]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Expression.tokenizePos]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Expression.tokenizePos]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Expression.tokenizePos]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:289]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Expression.tokenizeNeg]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Expression.tokenizeNeg]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Expression.tokenizeNeg]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:294]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Expression.tokenizePi_rad]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Expression.tokenizePi_rad]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Expression.tokenizePi_rad]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:299]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Expression.toString]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Expression.toString]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Expression.toString]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:310]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Expression.test_pi_rad]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Expression.test_pi_rad]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Expression.test_pi_rad]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:316]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Expression.test_e_rad]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Expression.test_e_rad]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Expression.test_e_rad]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:325]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Evaluate.test_evaluate_simple]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Evaluate.test_evaluate_simple]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Evaluate.test_evaluate_simple]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:364]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Evaluate.test_simplify_simple]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Evaluate.test_simplify_simple]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Evaluate.test_simplify_simple]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:372]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Evaluate.test_evaluate_function]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Evaluate.test_evaluate_function]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Evaluate.test_evaluate_function]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:380]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Evaluate.test_simplify_function]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Evaluate.test_simplify_function]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Evaluate.test_simplify_function]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:388]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Evaluate.test_evaluate_refer_to_var]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Evaluate.test_evaluate_refer_to_var]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Evaluate.test_evaluate_refer_to_var]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:396]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[Evaluate.test_simplify_refer_to_var]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=Evaluate.test_simplify_refer_to_var]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[Evaluate.test_simplify_refer_to_var]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Expression.cpp:406]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ExpressionParserTest.functionPARSEQUANT]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ExpressionParserTest.functionPARSEQUANT]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ExpressionParserTest.functionPARSEQUANT]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ExpressionParser.cpp:159]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ExpressionParserTest.isTokenAConstant]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ExpressionParserTest.isTokenAConstant]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ExpressionParserTest.isTokenAConstant]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ExpressionParser.cpp:204]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ExpressionParserTest.simpleExpressionsParse]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ExpressionParserTest.simpleExpressionsParse]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ExpressionParserTest.simpleExpressionsParse]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ExpressionParser.cpp:217]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ExpressionParserTest.expressionUserInputKeepsGroupingSeparateFromDecimals]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ExpressionParserTest.expressionUserInputKeepsGroupingSeparateFromDecimals]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ExpressionParserTest.expressionUserInputKeepsGroupingSeparateFromDecimals]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ExpressionParser.cpp:245]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ExpressionParserTest.groupedExpressionUsesLocaleGroupingPattern]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ExpressionParserTest.groupedExpressionUsesLocaleGroupingPattern]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ExpressionParserTest.groupedExpressionUsesLocaleGroupingPattern]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ExpressionParser.cpp:253]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ExpressionParserTest.localizedInputPreservesDigitsInsideIdentifiers]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ExpressionParserTest.localizedInputPreservesDigitsInsideIdentifiers]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ExpressionParserTest.localizedInputPreservesDigitsInsideIdentifiers]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ExpressionParser.cpp:263]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ExpressionParserTest.functionArgumentsTakePrecedenceOverGrouping]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ExpressionParserTest.functionArgumentsTakePrecedenceOverGrouping]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ExpressionParserTest.functionArgumentsTakePrecedenceOverGrouping]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ExpressionParser.cpp:276]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ExpressionParserTest.commaDecimalLocalesUseSemicolonsForArguments]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ExpressionParserTest.commaDecimalLocalesUseSemicolonsForArguments]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ExpressionParserTest.commaDecimalLocalesUseSemicolonsForArguments]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ExpressionParser.cpp:285]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ExpressionParserTest.groupedParenthesizedExpressionsUseTheLocalePattern]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ExpressionParserTest.groupedParenthesizedExpressionsUseTheLocalePattern]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ExpressionParserTest.groupedParenthesizedExpressionsUseTheLocalePattern]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ExpressionParser.cpp:315]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ExpressionParserTest.spaceGroupingAndSemicolonArgumentsRemainDistinct]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ExpressionParserTest.spaceGroupingAndSemicolonArgumentsRemainDistinct]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ExpressionParserTest.spaceGroupingAndSemicolonArgumentsRemainDistinct]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ExpressionParser.cpp:324]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ExpressionParserTest.commaFunctionArgumentsRemainArgumentsWithDecimalText]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ExpressionParserTest.commaFunctionArgumentsRemainArgumentsWithDecimalText]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ExpressionParserTest.commaFunctionArgumentsRemainArgumentsWithDecimalText]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ExpressionParser.cpp:332]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ExpressionParserTest.userInputPreservesOpaqueStringLiterals]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ExpressionParserTest.userInputPreservesOpaqueStringLiterals]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ExpressionParserTest.userInputPreservesOpaqueStringLiterals]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ExpressionParser.cpp:341]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ExpressionParserTest.badExpressionsDoNotParse]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ExpressionParserTest.badExpressionsDoNotParse]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ExpressionParserTest.badExpressionsDoNotParse]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ExpressionParser.cpp:353]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ExpressionParserTest.expressionsWithMultiplyDivideParse]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ExpressionParserTest.expressionsWithMultiplyDivideParse]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ExpressionParserTest.expressionsWithMultiplyDivideParse]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ExpressionParser.cpp:368]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ExpressionParserTest.expressionsWithUnitsMultipliedDontParse_LikelyBug]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ExpressionParserTest.expressionsWithUnitsMultipliedDontParse_LikelyBug]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ExpressionParserTest.expressionsWithUnitsMultipliedDontParse_LikelyBug]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ExpressionParser.cpp:382]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ExpressionParserTest.dimensionlessExpressionsParseAsLongOrDouble]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ExpressionParserTest.dimensionlessExpressionsParseAsLongOrDouble]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ExpressionParserTest.dimensionlessExpressionsParseAsLongOrDouble]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ExpressionParser.cpp:390]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ExpressionParserTest.expressionsWithFunctionsParse]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ExpressionParserTest.expressionsWithFunctionsParse]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ExpressionParserTest.expressionsWithFunctionsParse]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ExpressionParser.cpp:398]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ExpressionParserTest.expressionsParseAsPyObjectWrapper]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ExpressionParserTest.DISABLED_expressionsParseAsPyObjectWrapper]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ExpressionParserTest.expressionsParseAsPyObjectWrapper]=]
  PROPERTIES
    DISABLED YES
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ExpressionParser.cpp:414]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ExpressionParserTest.expressionsThatLookValidButDoNotParse]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ExpressionParserTest.expressionsThatLookValidButDoNotParse]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ExpressionParserTest.expressionsThatLookValidButDoNotParse]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ExpressionParser.cpp:427]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ExpressionParserTest.canParseProperties]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ExpressionParserTest.canParseProperties]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ExpressionParserTest.canParseProperties]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ExpressionParser.cpp:438]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[QuantityInput.QuantityInputUnitUsesDisplayedScaleAndSafeFallbacks]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=QuantityInput.QuantityInputUnitUsesDisplayedScaleAndSafeFallbacks]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[QuantityInput.QuantityInputUnitUsesDisplayedScaleAndSafeFallbacks]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/QuantityInput.cpp:60]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[QuantityInput.AppliesDisplayedScaleToQuantitiesAndExpressions]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=QuantityInput.AppliesDisplayedScaleToQuantitiesAndExpressions]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[QuantityInput.AppliesDisplayedScaleToQuantitiesAndExpressions]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/QuantityInput.cpp:84]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[QuantityInput.EditingAndCommitDistinguishIncompleteNumbers]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=QuantityInput.EditingAndCommitDistinguishIncompleteNumbers]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[QuantityInput.EditingAndCommitDistinguishIncompleteNumbers]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/QuantityInput.cpp:159]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[QuantityInput.TrailingGroupingSeparatorFollowsTheInputPhase]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=QuantityInput.TrailingGroupingSeparatorFollowsTheInputPhase]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[QuantityInput.TrailingGroupingSeparatorFollowsTheInputPhase]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/QuantityInput.cpp:276]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[QuantityInput.ReportsGroupingAndUnitDiagnostics]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=QuantityInput.ReportsGroupingAndUnitDiagnostics]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[QuantityInput.ReportsGroupingAndUnitDiagnostics]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/QuantityInput.cpp:308]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[QuantityInput.AcceptsGroupedQuantityAndNormalizesIt]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=QuantityInput.AcceptsGroupedQuantityAndNormalizesIt]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[QuantityInput.AcceptsGroupedQuantityAndNormalizesIt]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/QuantityInput.cpp:355]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[QuantityInput.ReportsExpressionEvaluationAndRangeDiagnostics]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=QuantityInput.ReportsExpressionEvaluationAndRangeDiagnostics]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[QuantityInput.ReportsExpressionEvaluationAndRangeDiagnostics]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/QuantityInput.cpp:374]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[QuantityInput.GrammarSelectionIsExplicit]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=QuantityInput.GrammarSelectionIsExplicit]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[QuantityInput.GrammarSelectionIsExplicit]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/QuantityInput.cpp:423]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[QuantityInput.PositiveSignsAndCompactAdditionRemainExpressionSyntax]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=QuantityInput.PositiveSignsAndCompactAdditionRemainExpressionSyntax]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[QuantityInput.PositiveSignsAndCompactAdditionRemainExpressionSyntax]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/QuantityInput.cpp:468]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[QuantityInput.DefaultUnitAppliesToBareAdditiveTerms]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=QuantityInput.DefaultUnitAppliesToBareAdditiveTerms]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[QuantityInput.DefaultUnitAppliesToBareAdditiveTerms]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/QuantityInput.cpp:583]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[QuantityInput.RejectsMalformedGroupingAfterExpressionOperand]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=QuantityInput.RejectsMalformedGroupingAfterExpressionOperand]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[QuantityInput.RejectsMalformedGroupingAfterExpressionOperand]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/QuantityInput.cpp:691]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[QuantityInput.DefaultUnitPreservesExpressionDependencies]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=QuantityInput.DefaultUnitPreservesExpressionDependencies]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[QuantityInput.DefaultUnitPreservesExpressionDependencies]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/QuantityInput.cpp:708]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[QuantityInput.DefaultUnitDoesNotRewriteNestedMultiplicativeSubexpressions]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=QuantityInput.DefaultUnitDoesNotRewriteNestedMultiplicativeSubexpressions]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[QuantityInput.DefaultUnitDoesNotRewriteNestedMultiplicativeSubexpressions]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/QuantityInput.cpp:749]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[QuantityInput.DefaultUnitExpressionsRoundTripThroughSerialization]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=QuantityInput.DefaultUnitExpressionsRoundTripThroughSerialization]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[QuantityInput.DefaultUnitExpressionsRoundTripThroughSerialization]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/QuantityInput.cpp:785]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[QuantityInput.EditingAndCommitExposeTheSameInvalidGrouping]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=QuantityInput.EditingAndCommitExposeTheSameInvalidGrouping]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[QuantityInput.EditingAndCommitExposeTheSameInvalidGrouping]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/QuantityInput.cpp:825]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[QuantityInput.SharedLocalizedInputCorpus]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=QuantityInput.SharedLocalizedInputCorpus]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[QuantityInput.SharedLocalizedInputCorpus]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/QuantityInput.cpp:845]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ElementMapTest.defaultConstruction]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ElementMapTest.defaultConstruction]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ElementMapTest.defaultConstruction]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ElementMap.cpp:72]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ElementMapTest.setElementNameDefaults]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ElementMapTest.setElementNameDefaults]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ElementMapTest.setElementNameDefaults]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ElementMap.cpp:81]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ElementMapTest.setElementNameNoOverwrite]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ElementMapTest.setElementNameNoOverwrite]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ElementMapTest.setElementNameNoOverwrite]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ElementMap.cpp:97]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ElementMapTest.setElementNameWithOverwrite]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ElementMapTest.setElementNameWithOverwrite]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ElementMapTest.setElementNameWithOverwrite]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ElementMap.cpp:120]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ElementMapTest.setElementNameWithHashing]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ElementMapTest.setElementNameWithHashing]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ElementMapTest.setElementNameWithHashing]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ElementMap.cpp:142]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ElementMapTest.eraseMappedName]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ElementMapTest.eraseMappedName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ElementMapTest.eraseMappedName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ElementMap.cpp:161]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ElementMapTest.eraseIndexedName]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ElementMapTest.eraseIndexedName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ElementMapTest.eraseIndexedName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ElementMap.cpp:198]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ElementMapTest.findMappedName]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ElementMapTest.findMappedName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ElementMapTest.findMappedName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ElementMap.cpp:241]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ElementMapTest.findIndexedName]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ElementMapTest.findIndexedName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ElementMapTest.findIndexedName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ElementMap.cpp:268]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ElementMapTest.findAll]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ElementMapTest.findAll]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ElementMapTest.findAll]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ElementMap.cpp:296]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ElementMapTest.mimicOnePart]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ElementMapTest.mimicOnePart]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ElementMapTest.mimicOnePart]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ElementMap.cpp:328]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ElementMapTest.mimicSimpleUnion]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ElementMapTest.mimicSimpleUnion]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ElementMapTest.mimicSimpleUnion]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ElementMap.cpp:359]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ElementMapTest.mimicOperationAgainstSelf]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ElementMapTest.mimicOperationAgainstSelf]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ElementMapTest.mimicOperationAgainstSelf]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ElementMap.cpp:433]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ElementMapTest.hasChildElementMapTest]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ElementMapTest.hasChildElementMapTest]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ElementMapTest.hasChildElementMapTest]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ElementMap.cpp:486]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ElementMapTest.hashChildMapsTest]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ElementMapTest.hashChildMapsTest]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ElementMapTest.hashChildMapsTest]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ElementMap.cpp:506]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ElementMapTest.addAndGetChildElementsTest]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ElementMapTest.addAndGetChildElementsTest]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ElementMapTest.addAndGetChildElementsTest]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ElementMap.cpp:533]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ElementNamingUtilsTest.findElementName]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ElementNamingUtilsTest.findElementName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ElementNamingUtilsTest.findElementName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ElementNamingUtils.cpp:40]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ElementNamingUtilsTest.indexOfElement]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ElementNamingUtilsTest.indexOfElement]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ElementNamingUtilsTest.indexOfElement]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ElementNamingUtils.cpp:63]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[IndexedNameTest.defaultConstruction]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=IndexedNameTest.defaultConstruction]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[IndexedNameTest.defaultConstruction]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:46]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[IndexedNameTest.nameOnlyConstruction]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=IndexedNameTest.nameOnlyConstruction]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[IndexedNameTest.nameOnlyConstruction]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:56]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[IndexedNameTest.nameAndIndexConstruction]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=IndexedNameTest.nameAndIndexConstruction]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[IndexedNameTest.nameAndIndexConstruction]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:66]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[IndexedNameTest.nameAndIndexConstructionWithOverride]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=IndexedNameTest.nameAndIndexConstructionWithOverride]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[IndexedNameTest.nameAndIndexConstructionWithOverride]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:79]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[IndexedNameTest.constructionInvalidCharInName]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=IndexedNameTest.constructionInvalidCharInName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[IndexedNameTest.constructionInvalidCharInName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:93]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[IndexedNameTest.constructionNumberInName]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=IndexedNameTest.constructionNumberInName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[IndexedNameTest.constructionNumberInName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:116]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[IndexedNameTest.nameAndTypeListConstructionWithoutAllowOthers]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=IndexedNameTest.nameAndTypeListConstructionWithoutAllowOthers]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[IndexedNameTest.nameAndTypeListConstructionWithoutAllowOthers]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:130]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[IndexedNameTest.nameAndTypeListConstructionWithAllowOthers]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=IndexedNameTest.nameAndTypeListConstructionWithAllowOthers]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[IndexedNameTest.nameAndTypeListConstructionWithAllowOthers]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:153]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[IndexedNameTest.nameAndTypeListConstructionReusedMemoryCheck]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=IndexedNameTest.nameAndTypeListConstructionReusedMemoryCheck]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[IndexedNameTest.nameAndTypeListConstructionReusedMemoryCheck]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:164]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[IndexedNameTest.byteArrayConstruction]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=IndexedNameTest.byteArrayConstruction]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[IndexedNameTest.byteArrayConstruction]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:174]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[IndexedNameTest.copyConstruction]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=IndexedNameTest.copyConstruction]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[IndexedNameTest.copyConstruction]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:187]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[IndexedNameTest.streamInsertionOperator]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=IndexedNameTest.streamInsertionOperator]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[IndexedNameTest.streamInsertionOperator]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:199]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[IndexedNameTest.compoundAssignmentOperator]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=IndexedNameTest.compoundAssignmentOperator]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[IndexedNameTest.compoundAssignmentOperator]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:212]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[IndexedNameTest.preincrementOperator]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=IndexedNameTest.preincrementOperator]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[IndexedNameTest.preincrementOperator]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:228]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[IndexedNameTest.predecrementOperator]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=IndexedNameTest.predecrementOperator]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[IndexedNameTest.predecrementOperator]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:240]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[IndexedNameTest.comparisonOperators]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=IndexedNameTest.comparisonOperators]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[IndexedNameTest.comparisonOperators]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:252]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[IndexedNameTest.subscriptOperator]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=IndexedNameTest.subscriptOperator]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[IndexedNameTest.subscriptOperator]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:315]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[IndexedNameTest.getType]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=IndexedNameTest.getType]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[IndexedNameTest.getType]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:327]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[IndexedNameTest.setIndex]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=IndexedNameTest.setIndex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[IndexedNameTest.setIndex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:336]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[IndexedNameTest.isNullTrue]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=IndexedNameTest.isNullTrue]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[IndexedNameTest.isNullTrue]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:349]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[IndexedNameTest.isNullFalse]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=IndexedNameTest.isNullFalse]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[IndexedNameTest.isNullFalse]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:360]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[IndexedNameTest.booleanConversionFalse]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=IndexedNameTest.booleanConversionFalse]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[IndexedNameTest.booleanConversionFalse]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:371]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[IndexedNameTest.booleanConversionTrue]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=IndexedNameTest.booleanConversionTrue]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[IndexedNameTest.booleanConversionTrue]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:388]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[IndexedNameTest.fromConst]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=IndexedNameTest.fromConst]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[IndexedNameTest.fromConst]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:399]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[IndexedNameTest.appendToStringBufferEmptyBuffer]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=IndexedNameTest.appendToStringBufferEmptyBuffer]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[IndexedNameTest.appendToStringBufferEmptyBuffer]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:412]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[IndexedNameTest.appendToStringBufferNonEmptyBuffer]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=IndexedNameTest.appendToStringBufferNonEmptyBuffer]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[IndexedNameTest.appendToStringBufferNonEmptyBuffer]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:425]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[IndexedNameTest.appendToStringBufferZeroIndex]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=IndexedNameTest.appendToStringBufferZeroIndex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[IndexedNameTest.appendToStringBufferZeroIndex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:438]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[IndexedNameTest.toString]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=IndexedNameTest.toString]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[IndexedNameTest.toString]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:451]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[IndexedNameTest.toStringNoIndex]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=IndexedNameTest.toStringNoIndex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[IndexedNameTest.toStringNoIndex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:463]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[IndexedNameTest.assignmentOperator]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=IndexedNameTest.assignmentOperator]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[IndexedNameTest.assignmentOperator]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:475]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ByteArrayTest.QByteArrayConstruction]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ByteArrayTest.QByteArrayConstruction]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ByteArrayTest.QByteArrayConstruction]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:500]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ByteArrayTest.CopyConstruction]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ByteArrayTest.CopyConstruction]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ByteArrayTest.CopyConstruction]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:512]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ByteArrayTest.MoveConstruction]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ByteArrayTest.MoveConstruction]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ByteArrayTest.MoveConstruction]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:526]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ByteArrayTest.ensureUnshared]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ByteArrayTest.ensureUnshared]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ByteArrayTest.ensureUnshared]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:541]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ByteArrayTest.equalityOperator]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ByteArrayTest.equalityOperator]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ByteArrayTest.equalityOperator]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:557]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ByteArrayTest.assignmentOperator]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ByteArrayTest.assignmentOperator]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ByteArrayTest.assignmentOperator]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:572]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ByteArrayTest.moveAssignmentOperator]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ByteArrayTest.moveAssignmentOperator]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ByteArrayTest.moveAssignmentOperator]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/IndexedName.cpp:588]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[License.isLicenseEmpty]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=License.isLicenseEmpty]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[License.isLicenseEmpty]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/License.cpp:7]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[License.isLicenseNull]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=License.isLicenseNull]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[License.isLicenseNull]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/License.cpp:12]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[License.isLicenseYesStr]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=License.isLicenseYesStr]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[License.isLicenseYesStr]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/License.cpp:17]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[License.UnknownIdentifier]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=License.UnknownIdentifier]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[License.UnknownIdentifier]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/License.cpp:22]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[License.direct]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=License.direct]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[License.direct]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/License.cpp:28]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[License.findLicenseByIdent]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=License.findLicenseByIdent]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[License.findLicenseByIdent]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/License.cpp:41]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getArrayIndexSimpleInteger]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getArrayIndexSimpleInteger]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getArrayIndexSimpleInteger]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:43]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getArrayIndexZero]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getArrayIndexZero]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getArrayIndexZero]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:48]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getArrayIndexWithDotSuffix]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getArrayIndexWithDotSuffix]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getArrayIndexWithDotSuffix]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:53]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getArrayIndexMultiDigitWithDot]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getArrayIndexMultiDigitWithDot]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getArrayIndexMultiDigitWithDot]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:58]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getArrayIndexTrailingDotOnly]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getArrayIndexTrailingDotOnly]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getArrayIndexTrailingDotOnly]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:63]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getArrayIndexReturnsMinusOneForNull]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getArrayIndexReturnsMinusOneForNull]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getArrayIndexReturnsMinusOneForNull]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:68]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getArrayIndexReturnsMinusOneForEmptyString]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getArrayIndexReturnsMinusOneForEmptyString]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getArrayIndexReturnsMinusOneForEmptyString]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:73]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getArrayIndexReturnsMinusOneForLeadingDot]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getArrayIndexReturnsMinusOneForLeadingDot]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getArrayIndexReturnsMinusOneForLeadingDot]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:78]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getArrayIndexReturnsMinusOneForAlpha]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getArrayIndexReturnsMinusOneForAlpha]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getArrayIndexReturnsMinusOneForAlpha]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:84]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getArrayIndexReturnsMinusOneForMixedAlphaDigit]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getArrayIndexReturnsMinusOneForMixedAlphaDigit]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getArrayIndexReturnsMinusOneForMixedAlphaDigit]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:89]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getArrayIndexReturnsMinusOneForAlphaThenDigit]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getArrayIndexReturnsMinusOneForAlphaThenDigit]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getArrayIndexReturnsMinusOneForAlphaThenDigit]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:94]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getArrayIndexReturnsMinusOneForMappedElement]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getArrayIndexReturnsMinusOneForMappedElement]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getArrayIndexReturnsMinusOneForMappedElement]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:99]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getArrayIndexReturnsMinusOneForMappedElementWithDigits]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getArrayIndexReturnsMinusOneForMappedElementWithDigits]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getArrayIndexReturnsMinusOneForMappedElementWithDigits]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:105]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getArrayIndexPsubnamePointsPastDot]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getArrayIndexPsubnamePointsPastDot]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getArrayIndexPsubnamePointsPastDot]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:110]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getArrayIndexPsubnameAtEndWhenNoDot]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getArrayIndexPsubnameAtEndWhenNoDot]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getArrayIndexPsubnameAtEndWhenNoDot]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:119]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getArrayIndexPsubnameEmptyAfterTrailingDot]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getArrayIndexPsubnameEmptyAfterTrailingDot]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getArrayIndexPsubnameEmptyAfterTrailingDot]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:128]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getArrayIndexPsubnameWithNestedDots]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getArrayIndexPsubnameWithNestedDots]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getArrayIndexPsubnameWithNestedDots]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:137]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getArrayIndexPsubnameUntouchedOnFailure]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getArrayIndexPsubnameUntouchedOnFailure]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getArrayIndexPsubnameUntouchedOnFailure]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:146]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getArrayIndexPsubnameUntouchedOnNull]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getArrayIndexPsubnameUntouchedOnNull]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getArrayIndexPsubnameUntouchedOnNull]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:155]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getArrayIndexLargeNumber]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getArrayIndexLargeNumber]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getArrayIndexLargeNumber]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:163]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getArrayIndexReturnsMinusOneForNegative]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getArrayIndexReturnsMinusOneForNegative]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getArrayIndexReturnsMinusOneForNegative]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:168]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getArrayIndexReturnsMinusOneForSpace]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getArrayIndexReturnsMinusOneForSpace]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getArrayIndexReturnsMinusOneForSpace]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:174]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getArrayIndexReturnsMinusOneForDigitWithSpace]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getArrayIndexReturnsMinusOneForDigitWithSpace]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getArrayIndexReturnsMinusOneForDigitWithSpace]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:179]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getScaleVectorDefaultIsUnity]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getScaleVectorDefaultIsUnity]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getScaleVectorDefaultIsUnity]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:196]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getScaleVectorReflectsUniformScale]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getScaleVectorReflectsUniformScale]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getScaleVectorReflectsUniformScale]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:205]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getScaleVectorReflectsNonUniformScale]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getScaleVectorReflectsNonUniformScale]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getScaleVectorReflectsNonUniformScale]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:218]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getTransformNoTransformDefaultIsIdentity]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getTransformNoTransformDefaultIsIdentity]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getTransformNoTransformDefaultIsIdentity]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:228]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getTransformWithTransformDefaultIsIdentity]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getTransformWithTransformDefaultIsIdentity]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getTransformWithTransformDefaultIsIdentity]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:235]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getTransformNoTransformAppliesScaleOnly]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getTransformNoTransformAppliesScaleOnly]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getTransformNoTransformAppliesScaleOnly]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:242]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getTransformNoTransformIgnoresPlacement]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getTransformNoTransformIgnoresPlacement]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getTransformNoTransformIgnoresPlacement]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:259]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getTransformWithTransformIncludesLinkPlacement]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getTransformWithTransformIncludesLinkPlacement]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getTransformWithTransformIncludesLinkPlacement]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:272]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getTransformWithTransformAndScale]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getTransformWithTransformAndScale]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getTransformWithTransformAndScale]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:286]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.getTransformUsesLinkPlacementWhenPropertyExists]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.getTransformUsesLinkPlacementWhenPropertyExists]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.getTransformUsesLinkPlacementWhenPropertyExists]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:305]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LinkTest.linkPlacementAndPlacementStayInSync]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LinkTest.linkPlacementAndPlacementStayInSync]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LinkTest.linkPlacementAndPlacementStayInSync]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Link.cpp:321]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedElementTest.constructFromNameAndIndex]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedElementTest.constructFromNameAndIndex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedElementTest.constructFromNameAndIndex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedElement.cpp:29]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedElementTest.moveConstructor]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedElementTest.moveConstructor]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedElementTest.moveConstructor]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedElement.cpp:43]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedElementTest.assignmentOperator]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedElementTest.assignmentOperator]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedElementTest.assignmentOperator]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedElement.cpp:58]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedElementTest.moveAssignmentOperator]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedElementTest.moveAssignmentOperator]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedElementTest.moveAssignmentOperator]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedElement.cpp:72]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedElementTest.equalityOperatorsWhenNotEqual]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedElementTest.equalityOperatorsWhenNotEqual]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedElementTest.equalityOperatorsWhenNotEqual]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedElement.cpp:87]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedElementTest.equalityOperatorsWhenEqual]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedElementTest.equalityOperatorsWhenEqual]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedElementTest.equalityOperatorsWhenEqual]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedElement.cpp:102]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedElementTest.lessThanOperator]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedElementTest.lessThanOperator]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedElementTest.lessThanOperator]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedElement.cpp:117]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedElementTest.comparatorBothAreZeroSize]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedElementTest.comparatorBothAreZeroSize]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedElementTest.comparatorBothAreZeroSize]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedElement.cpp:136]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedElementTest.comparatorOneIsZeroSize]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedElementTest.comparatorOneIsZeroSize]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedElementTest.comparatorOneIsZeroSize]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedElement.cpp:147]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedElementTest.comparatorBothStartWithHexDigitsThatDiffer]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedElementTest.comparatorBothStartWithHexDigitsThatDiffer]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedElementTest.comparatorBothStartWithHexDigitsThatDiffer]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedElement.cpp:158]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedElementTest.comparatorBothStartWithTheSameHexDigits]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedElementTest.comparatorBothStartWithTheSameHexDigits]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedElementTest.comparatorBothStartWithTheSameHexDigits]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedElement.cpp:169]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedElementTest.comparatorHexWithoutTerminator]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedElementTest.comparatorHexWithoutTerminator]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedElementTest.comparatorHexWithoutTerminator]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedElement.cpp:180]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedElementTest.comparatorHexWithoutTerminatorSameLength]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedElementTest.comparatorHexWithoutTerminatorSameLength]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedElementTest.comparatorHexWithoutTerminatorSameLength]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedElement.cpp:191]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedElementTest.comparatorNoHexDigitsLexicalCompare]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedElementTest.comparatorNoHexDigitsLexicalCompare]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedElementTest.comparatorNoHexDigitsLexicalCompare]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedElement.cpp:202]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedElementTest.comparatorNoHexDigitsSameStringNumericCompare]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedElementTest.comparatorNoHexDigitsSameStringNumericCompare]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedElementTest.comparatorNoHexDigitsSameStringNumericCompare]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedElement.cpp:213]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedElementTest.comparatorIntegerWithoutTerminatorIsBroken]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedElementTest.comparatorIntegerWithoutTerminatorIsBroken]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedElementTest.comparatorIntegerWithoutTerminatorIsBroken]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedElement.cpp:224]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedElementTest.comparatorThreeComplexHexNamesInMap]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedElementTest.comparatorThreeComplexHexNamesInMap]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedElementTest.comparatorThreeComplexHexNamesInMap]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedElement.cpp:235]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedElementTest.comparatorLargerWorkedExampleWithMap]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedElementTest.comparatorLargerWorkedExampleWithMap]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedElementTest.comparatorLargerWorkedExampleWithMap]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedElement.cpp:271]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.defaultConstruction]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.defaultConstruction]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.defaultConstruction]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:12]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.namedConstruction]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.namedConstruction]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.namedConstruction]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:25]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.namedConstructionWithMaxSize]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.namedConstructionWithMaxSize]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.namedConstructionWithMaxSize]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:38]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.namedConstructionDiscardPrefix]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.namedConstructionDiscardPrefix]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.namedConstructionDiscardPrefix]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:51]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.stringNamedConstruction]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.stringNamedConstruction]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.stringNamedConstruction]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:67]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.stringNamedConstructionDiscardPrefix]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.stringNamedConstructionDiscardPrefix]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.stringNamedConstructionDiscardPrefix]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:80]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.constructFromIndexedNameNoIndex]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.constructFromIndexedNameNoIndex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.constructFromIndexedNameNoIndex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:96]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.constructFromIndexedNameWithIndex]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.constructFromIndexedNameWithIndex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.constructFromIndexedNameWithIndex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:109]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.copyConstructor]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.copyConstructor]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.copyConstructor]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:123]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.copyConstructorWithPostfix]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.copyConstructorWithPostfix]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.copyConstructorWithPostfix]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:139]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.copyConstructorStartpos]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.copyConstructorStartpos]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.copyConstructorStartpos]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:165]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.copyConstructorStartposAndSize]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.copyConstructorStartposAndSize]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.copyConstructorStartposAndSize]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:181]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.moveConstructor]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.moveConstructor]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.moveConstructor]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:197]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.fromRawData]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.fromRawData]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.fromRawData]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:213]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.fromRawDataQByteArray]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.fromRawDataQByteArray]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.fromRawDataQByteArray]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:226]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.fromRawDataCopy]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.fromRawDataCopy]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.fromRawDataCopy]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:242]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.fromRawDataCopyStartposAndSize]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.fromRawDataCopyStartposAndSize]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.fromRawDataCopyStartposAndSize]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:261]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.assignmentOperator]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.assignmentOperator]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.assignmentOperator]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:280]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.assignmentOperatorString]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.assignmentOperatorString]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.assignmentOperatorString]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:296]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.assignmentOperatorConstCharPtr]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.assignmentOperatorConstCharPtr]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.assignmentOperatorConstCharPtr]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:312]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.assignmentOperatorMove]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.assignmentOperatorMove]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.assignmentOperatorMove]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:328]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.streamInsertionOperator]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.streamInsertionOperator]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.streamInsertionOperator]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:344]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.comparisonOperators]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.comparisonOperators]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.comparisonOperators]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:357]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.additionOperators]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.additionOperators]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.additionOperators]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:377]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.append]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.append]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.append]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:414]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.appendMappedNameObj]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.appendMappedNameObj]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.appendMappedNameObj]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:450]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.toString]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.toString]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.toString]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:477]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.toConstString]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.toConstString]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.toConstString]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:489]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.toRawBytes]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.toRawBytes]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.toRawBytes]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:510]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.toIndexedNameASCIIOnly]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.toIndexedNameASCIIOnly]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.toIndexedNameASCIIOnly]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:522]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.toIndexedNameInvalid]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.toIndexedNameInvalid]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.toIndexedNameInvalid]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:534]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.appendToBuffer]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.appendToBuffer]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.appendToBuffer]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:546]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.appendToBufferWithPrefix]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.appendToBufferWithPrefix]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.appendToBufferWithPrefix]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:565]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.toPrefixedString]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.toPrefixedString]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.toPrefixedString]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:593]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.toBytes]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.toBytes]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.toBytes]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:621]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.compare]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.compare]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.compare]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:630]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.subscriptOperator]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.subscriptOperator]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.subscriptOperator]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:656]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.copy]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.copy]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.copy]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:674]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.compact]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.compact]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.compact]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:686]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.boolOperator]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.boolOperator]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.boolOperator]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:702]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.clear]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.clear]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.clear]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:717]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.find]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.find]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.find]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:729]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.rfind]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.rfind]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.rfind]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:763]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.endswith]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.endswith]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.endswith]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:797]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.startsWith]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.startsWith]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.startsWith]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:817]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.findTagInElementNameHexPositiveIndexNonrecursive]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.findTagInElementNameHexPositiveIndexNonrecursive]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.findTagInElementNameHexPositiveIndexNonrecursive]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:840]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.findTagInElementNameDecPositiveIndexNonrecursive]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.findTagInElementNameDecPositiveIndexNonrecursive]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.findTagInElementNameDecPositiveIndexNonrecursive]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:866]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.findTagInElementNameHexNegativeIndexNonrecursive]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.findTagInElementNameHexNegativeIndexNonrecursive]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.findTagInElementNameHexNegativeIndexNonrecursive]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:888]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.findTagInElementNameHexExpectedNegativeIndexNonrecursive]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.findTagInElementNameHexExpectedNegativeIndexNonrecursive]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.findTagInElementNameHexExpectedNegativeIndexNonrecursive]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:910]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.findTagInElementNameRecursive]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.findTagInElementNameRecursive]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.findTagInElementNameRecursive]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:932]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MappedName.hash]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MappedName.hash]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MappedName.hash]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/MappedName.cpp:954]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ContactTest.ContactDefaultConstruction]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ContactTest.ContactDefaultConstruction]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ContactTest.ContactDefaultConstruction]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Metadata.cpp:33]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ContactTest.ContactParameterConstruction]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ContactTest.ContactParameterConstruction]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ContactTest.ContactParameterConstruction]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Metadata.cpp:40]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ContactTest.ContactNullDomNodeConstruction]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ContactTest.ContactNullDomNodeConstruction]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ContactTest.ContactNullDomNodeConstruction]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Metadata.cpp:47]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ContactTest.ContactOperatorEquality]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ContactTest.ContactOperatorEquality]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ContactTest.ContactOperatorEquality]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Metadata.cpp:54]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LicenseTest.LicenseDefaultConstruction]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LicenseTest.LicenseDefaultConstruction]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LicenseTest.LicenseDefaultConstruction]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Metadata.cpp:65]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LicenseTest.LicenseParameterConstruction]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LicenseTest.LicenseParameterConstruction]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LicenseTest.LicenseParameterConstruction]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Metadata.cpp:72]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LicenseTest.LicenseNullDomNodeConstruction]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LicenseTest.LicenseNullDomNodeConstruction]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LicenseTest.LicenseNullDomNodeConstruction]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Metadata.cpp:79]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[LicenseTest.LicenseOperatorEquality]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=LicenseTest.LicenseOperatorEquality]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[LicenseTest.LicenseOperatorEquality]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Metadata.cpp:86]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UrlTest.UrlDefaultConstruction]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=UrlTest.UrlDefaultConstruction]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UrlTest.UrlDefaultConstruction]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Metadata.cpp:97]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UrlTest.UrlParameterConstruction]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=UrlTest.UrlParameterConstruction]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UrlTest.UrlParameterConstruction]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Metadata.cpp:104]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UrlTest.UrlNullDomNodeConstruction]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=UrlTest.UrlNullDomNodeConstruction]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UrlTest.UrlNullDomNodeConstruction]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Metadata.cpp:111]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[UrlTest.UrlOperatorEquality]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=UrlTest.UrlOperatorEquality]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[UrlTest.UrlOperatorEquality]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Metadata.cpp:117]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[VersionTest.VersionDefaultConstruction]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=VersionTest.VersionDefaultConstruction]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[VersionTest.VersionDefaultConstruction]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Metadata.cpp:128]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[VersionTest.VersionParameterConstruction]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=VersionTest.VersionParameterConstruction]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[VersionTest.VersionParameterConstruction]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Metadata.cpp:137]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[VersionTest.VersionStringConstruction]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=VersionTest.VersionStringConstruction]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[VersionTest.VersionStringConstruction]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Metadata.cpp:146]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[VersionTest.VersionOperatorEqual]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=VersionTest.VersionOperatorEqual]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[VersionTest.VersionOperatorEqual]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Metadata.cpp:155]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[VersionTest.VersionOperatorComparison]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=VersionTest.VersionOperatorComparison]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[VersionTest.VersionOperatorComparison]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Metadata.cpp:168]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MetadataTest.MetadataInMemoryConstruction]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MetadataTest.MetadataInMemoryConstruction]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MetadataTest.MetadataInMemoryConstruction]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Metadata.cpp:232]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ProjectFileTest.loadInvalid]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ProjectFileTest.loadInvalid]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ProjectFileTest.loadInvalid]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ProjectFile.cpp:43]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ProjectFileTest.loadDocument]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ProjectFileTest.loadDocument]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ProjectFileTest.loadDocument]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ProjectFile.cpp:49]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ProjectFileTest.getObjects]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ProjectFileTest.getObjects]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ProjectFileTest.getObjects]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ProjectFile.cpp:55]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ProjectFileTest.getPropertyFiles]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ProjectFileTest.getPropertyFiles]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ProjectFileTest.getPropertyFiles]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ProjectFile.cpp:63]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ProjectFileTest.getMetadata]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ProjectFileTest.getMetadata]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ProjectFileTest.getMetadata]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ProjectFile.cpp:71]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ProjectFileTest.getObjectsOfType]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ProjectFileTest.getObjectsOfType]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ProjectFileTest.getObjectsOfType]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ProjectFile.cpp:89]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ProjectFileTest.restoreObject]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ProjectFileTest.restoreObject]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ProjectFileTest.restoreObject]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ProjectFile.cpp:97]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ProjectFileTest.getTypeId]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ProjectFileTest.getTypeId]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ProjectFileTest.getTypeId]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ProjectFile.cpp:106]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ProjectFileTest.getThumbnailBuffer]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ProjectFileTest.getThumbnailBuffer]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ProjectFileTest.getThumbnailBuffer]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ProjectFile.cpp:114]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[ProjectFileTest.getThumbnailFile]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=ProjectFileTest.getThumbnailFile]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ProjectFileTest.getThumbnailFile]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/ProjectFile.cpp:123]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PropertyFileIncludedTest.rejectsParentTraversalInFileAttribute]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=PropertyFileIncludedTest.rejectsParentTraversalInFileAttribute]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PropertyFileIncludedTest.rejectsParentTraversalInFileAttribute]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/PropertyFile.cpp:61]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PropertyFileIncludedTest.rejectsBackslashTraversalInFileAttribute]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=PropertyFileIncludedTest.rejectsBackslashTraversalInFileAttribute]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PropertyFileIncludedTest.rejectsBackslashTraversalInFileAttribute]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/PropertyFile.cpp:70]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PropertyFileIncludedTest.rejectsAbsolutePathInFileAttribute]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=PropertyFileIncludedTest.rejectsAbsolutePathInFileAttribute]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PropertyFileIncludedTest.rejectsAbsolutePathInFileAttribute]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/PropertyFile.cpp:79]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PropertyFileIncludedTest.rejectsSubdirectoryInFileAttribute]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=PropertyFileIncludedTest.rejectsSubdirectoryInFileAttribute]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PropertyFileIncludedTest.rejectsSubdirectoryInFileAttribute]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/PropertyFile.cpp:88]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PropertyFileIncludedTest.rejectsDotDotInFileAttribute]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=PropertyFileIncludedTest.rejectsDotDotInFileAttribute]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PropertyFileIncludedTest.rejectsDotDotInFileAttribute]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/PropertyFile.cpp:97]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PropertyFileIncludedTest.rejectsParentTraversalInDataAttribute]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=PropertyFileIncludedTest.rejectsParentTraversalInDataAttribute]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PropertyFileIncludedTest.rejectsParentTraversalInDataAttribute]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/PropertyFile.cpp:103]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PropertyFileIncludedTest.acceptsPlainBasename]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=PropertyFileIncludedTest.acceptsPlainBasename]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PropertyFileIncludedTest.acceptsPlainBasename]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/PropertyFile.cpp:112]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PropertyLink.TestSetValues]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=PropertyLink.TestSetValues]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PropertyLink.TestSetValues]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:48]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PropertyFloatTest.testWriteRead]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=PropertyFloatTest.testWriteRead]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PropertyFloatTest.testWriteRead]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:69]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[RenameProperty.simple]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=RenameProperty.simple]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RenameProperty.simple]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:96]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[RenameProperty.fromPython]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=RenameProperty.fromPython]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RenameProperty.fromPython]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:110]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[RenameProperty.chain]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=RenameProperty.chain]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RenameProperty.chain]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:125]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[RenameProperty.staticProperty]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=RenameProperty.staticProperty]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RenameProperty.staticProperty]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:149]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[RenameProperty.staticPropertyFromPython]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=RenameProperty.staticPropertyFromPython]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RenameProperty.staticPropertyFromPython]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:164]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[RenameProperty.lockedProperty]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=RenameProperty.lockedProperty]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RenameProperty.lockedProperty]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:183]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[RenameProperty.toExistingProperty]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=RenameProperty.toExistingProperty]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RenameProperty.toExistingProperty]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:199]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[RenameProperty.toInvalidProperty]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=RenameProperty.toInvalidProperty]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RenameProperty.toInvalidProperty]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:216]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[RenameProperty.updateExpressionSameContainer]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=RenameProperty.updateExpressionSameContainer]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RenameProperty.updateExpressionSameContainer]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:229]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[RenameProperty.updateExpressionDifferentContainer]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=RenameProperty.updateExpressionDifferentContainer]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RenameProperty.updateExpressionDifferentContainer]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:259]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[RenameProperty.updateExpressionDifferentDocument]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=RenameProperty.updateExpressionDifferentDocument]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RenameProperty.updateExpressionDifferentDocument]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:293]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[RenameProperty.withExpression]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=RenameProperty.withExpression]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RenameProperty.withExpression]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:333]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[RenameProperty.undo]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=RenameProperty.undo]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RenameProperty.undo]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:371]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[RenameProperty.redo]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=RenameProperty.redo]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[RenameProperty.redo]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:401]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MoveProperty.simple]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MoveProperty.simple]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MoveProperty.simple]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:482]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MoveProperty.otherDoc]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MoveProperty.otherDoc]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MoveProperty.otherDoc]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:489]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MoveProperty.staticProperty]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MoveProperty.staticProperty]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MoveProperty.staticProperty]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:496]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MoveProperty.lockedProperty]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MoveProperty.lockedProperty]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MoveProperty.lockedProperty]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:515]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MoveProperty.toExistingProperty]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MoveProperty.toExistingProperty]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MoveProperty.toExistingProperty]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:527]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MoveProperty.updateExpressionOriginatingContainer]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MoveProperty.updateExpressionOriginatingContainer]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MoveProperty.updateExpressionOriginatingContainer]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:599]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MoveProperty.updateExpressionTargetContainer]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MoveProperty.updateExpressionTargetContainer]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MoveProperty.updateExpressionTargetContainer]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:608]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MoveProperty.updateExpressionOriginatingContainerOtherDoc]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MoveProperty.updateExpressionOriginatingContainerOtherDoc]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MoveProperty.updateExpressionOriginatingContainerOtherDoc]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:617]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MoveProperty.updateExpressionTargetContainerOtherDoc]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MoveProperty.updateExpressionTargetContainerOtherDoc]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MoveProperty.updateExpressionTargetContainerOtherDoc]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:626]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MoveProperty.updateExpressionMovedProp]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MoveProperty.updateExpressionMovedProp]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MoveProperty.updateExpressionMovedProp]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:634]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MoveProperty.undo]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MoveProperty.undo]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MoveProperty.undo]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:704]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MoveProperty.undoOtherDoc]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MoveProperty.undoOtherDoc]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MoveProperty.undoOtherDoc]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:711]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MoveProperty.undoExpressionOriginatingContainer]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MoveProperty.undoExpressionOriginatingContainer]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MoveProperty.undoExpressionOriginatingContainer]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:765]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MoveProperty.undoExpressionTargetContainer]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MoveProperty.undoExpressionTargetContainer]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MoveProperty.undoExpressionTargetContainer]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:776]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MoveProperty.undoExpressionOriginatingContainerOtherDoc]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MoveProperty.undoExpressionOriginatingContainerOtherDoc]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MoveProperty.undoExpressionOriginatingContainerOtherDoc]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:787]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MoveProperty.undoExpressionTargetContainerOtherDoc]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MoveProperty.undoExpressionTargetContainerOtherDoc]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MoveProperty.undoExpressionTargetContainerOtherDoc]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:798]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MoveProperty.redoSimple]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MoveProperty.redoSimple]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MoveProperty.redoSimple]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:806]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MoveProperty.redoOtherDoc]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MoveProperty.redoOtherDoc]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MoveProperty.redoOtherDoc]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:823]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MoveProperty.redoExpressionOriginatingContainer]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MoveProperty.redoExpressionOriginatingContainer]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MoveProperty.redoExpressionOriginatingContainer]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:873]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MoveProperty.redoExpressionTargetContainer]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MoveProperty.redoExpressionTargetContainer]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MoveProperty.redoExpressionTargetContainer]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:884]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MoveProperty.redoExpressionOriginatingContainerOtherDoc]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MoveProperty.redoExpressionOriginatingContainerOtherDoc]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MoveProperty.redoExpressionOriginatingContainerOtherDoc]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:895]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[MoveProperty.redoExpressionTargetContainerOtherDoc]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=MoveProperty.redoExpressionTargetContainerOtherDoc]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[MoveProperty.redoExpressionTargetContainerOtherDoc]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/Property.cpp:906]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[PropertyExpressionEngineTest.executeCrossPropertyReference]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=PropertyExpressionEngineTest.executeCrossPropertyReference]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[PropertyExpressionEngineTest.executeCrossPropertyReference]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/PropertyExpressionEngine.cpp:61]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.stringIDManualConstructionNoFlags]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.stringIDManualConstructionNoFlags]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.stringIDManualConstructionNoFlags]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:27]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.stringIDManualConstructionWithFlag]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.stringIDManualConstructionWithFlag]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.stringIDManualConstructionWithFlag]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:42]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.stringIDDefaultConstruction]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.stringIDDefaultConstruction]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.stringIDDefaultConstruction]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:58]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.value]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.value]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.value]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:67]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.relatedIDs]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.relatedIDs]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.relatedIDs]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:88]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.isBinary]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.isBinary]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.isBinary]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:93]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.isHashed]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.isHashed]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.isHashed]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:104]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.isPostfixed]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.isPostfixed]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.isPostfixed]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:115]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.isPostfixEncoded]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.isPostfixEncoded]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.isPostfixEncoded]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:126]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.isIndexed]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.isIndexed]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.isIndexed]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:137]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.isPrefixID]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.isPrefixID]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.isPrefixID]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:148]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.isPrefixIDIndex]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.isPrefixIDIndex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.isPrefixIDIndex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:159]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.isMarked]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.isMarked]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.isMarked]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:170]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.isPersistent]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.isPersistent]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.isPersistent]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:181]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.isFromSameHasher]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.isFromSameHasher]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.isFromSameHasher]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:192]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.getHasher]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.getHasher]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.getHasher]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:197]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.data]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.data]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.data]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:202]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.postfix]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.postfix]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.postfix]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:215]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.getPyObject]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.getPyObject]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.getPyObject]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:220]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.getPyObjectWithIndex]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.getPyObjectWithIndex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.getPyObjectWithIndex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:235]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.toStringWithoutIndex]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.toStringWithoutIndex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.toStringWithoutIndex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:250]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.toStringWithIndex]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.toStringWithIndex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.toStringWithIndex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:266]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.fromStringWithEOFAndLengthGood]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.fromStringWithEOFAndLengthGood]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.fromStringWithEOFAndLengthGood]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:281]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.fromStringExtraData]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.fromStringExtraData]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.fromStringExtraData]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:295]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.fromStringLengthUnspecified]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.fromStringLengthUnspecified]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.fromStringLengthUnspecified]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:311]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.fromStringShorterLength]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.fromStringShorterLength]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.fromStringShorterLength]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:325]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.fromStringNoHashtag]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.fromStringNoHashtag]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.fromStringNoHashtag]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:340]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.fromStringNotHex]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.fromStringNotHex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.fromStringNotHex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:352]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.fromStringQByteArray]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.fromStringQByteArray]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.fromStringQByteArray]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:367]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.dataToTextHashed]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.dataToTextHashed]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.dataToTextHashed]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:380]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.dataToTextBinary]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.dataToTextBinary]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.dataToTextBinary]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:393]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.dataToTextNoIndex]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.dataToTextNoIndex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.dataToTextNoIndex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:406]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.dataToTextWithIndex]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.dataToTextWithIndex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.dataToTextWithIndex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:419]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.dataToTextWithPostfix]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.dataToTextWithPostfix]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.dataToTextWithPostfix]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:434]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.dataToBytesNoIndex]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.dataToBytesNoIndex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.dataToBytesNoIndex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:449]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.dataToBytesWithIndex]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.dataToBytesWithIndex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.dataToBytesWithIndex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:462]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.dataToBytesWithPostfix]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.dataToBytesWithPostfix]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.dataToBytesWithPostfix]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:476]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.dataToBytesWithIndexAndPostfix]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.dataToBytesWithIndexAndPostfix]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.dataToBytesWithIndexAndPostfix]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:491]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.mark]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.mark]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.mark]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:507]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.setPersistent]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.setPersistent]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.setPersistent]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:521]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.operatorLessThan]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.operatorLessThan]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.operatorLessThan]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:535]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.compare]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.compare]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.compare]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:540]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.IndexIDBooleanConversion]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.IndexIDBooleanConversion]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.IndexIDBooleanConversion]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:545]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDTest.IndexIDStreamInsertionOperator]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDTest.IndexIDStreamInsertionOperator]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDTest.IndexIDStreamInsertionOperator]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:558]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.defaultConstructor]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.defaultConstructor]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.defaultConstructor]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:592]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.constructFromNewStringID]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.constructFromNewStringID]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.constructFromNewStringID]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:601]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.constructFromStringIDAndIndex]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.constructFromStringIDAndIndex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.constructFromStringIDAndIndex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:614]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.copyConstructor]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.copyConstructor]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.copyConstructor]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:631]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.copyConstructorWithIndex]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.copyConstructorWithIndex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.copyConstructorWithIndex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:647]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.moveConstructor]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.moveConstructor]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.moveConstructor]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:664]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.destructor]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.destructor]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.destructor]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:676]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.reset]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.reset]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.reset]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:693]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.resetWithStringID]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.resetWithStringID]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.resetWithStringID]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:705]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.resetWithStringIDAndIndex]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.resetWithStringIDAndIndex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.resetWithStringIDAndIndex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:719]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.swap]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.swap]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.swap]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:734]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.assignmentFromSelf]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.assignmentFromSelf]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.assignmentFromSelf]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:755]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.assignmentToEmptyFromStringID]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.assignmentToEmptyFromStringID]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.assignmentToEmptyFromStringID]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:771]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.assignmentFromStringIDRef]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.assignmentFromStringIDRef]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.assignmentFromStringIDRef]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:785]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.moveAssignmentFromStringIDRef]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.moveAssignmentFromStringIDRef]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.moveAssignmentFromStringIDRef]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:801]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.operatorLess]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.operatorLess]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.operatorLess]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:815]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.operatorEquality]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.operatorEquality]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.operatorEquality]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:834]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.operatorInequality]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.operatorInequality]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.operatorInequality]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:850]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.booleanConversion]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.booleanConversion]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.booleanConversion]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:866]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.getRefCount]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.getRefCount]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.getRefCount]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:877]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.toString]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.toString]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.toString]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:893]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.dataToText]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.dataToText]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.dataToText]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:909]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.constData]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.constData]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.constData]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:925]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.deref]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.deref]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.deref]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:938]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.value]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.value]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.value]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:948]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.relatedIDs]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.relatedIDs]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.relatedIDs]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:963]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.isBinary]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.isBinary]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.isBinary]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:968]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.isHashed]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.isHashed]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.isHashed]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:981]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.toBytes]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.toBytes]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.toBytes]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:994]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.getPyObject]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.getPyObject]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.getPyObject]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1007]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.mark]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.mark]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.mark]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1023]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.isMarked]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.isMarked]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.isMarked]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1036]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.isFromSameHasher]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.isFromSameHasher]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.isFromSameHasher]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1047]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.getHasher]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.getHasher]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.getHasher]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1052]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringIDRefTest.setPersistent]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringIDRefTest.setPersistent]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringIDRefTest.setPersistent]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1057]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.defaultConstructor]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.defaultConstructor]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.defaultConstructor]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1120]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.getMemSize]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.getMemSize]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.getMemSize]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1132]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.Save]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.Save]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.Save]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1146]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.Restore]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.Restore]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.Restore]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1153]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.SaveDocFile]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.SaveDocFile]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.SaveDocFile]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1160]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.RestoreDocFile]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.RestoreDocFile]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.RestoreDocFile]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1167]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.setPersistenceFileName]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.setPersistenceFileName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.setPersistenceFileName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1174]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.getPersistenceFileName]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.getPersistenceFileName]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.getPersistenceFileName]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1181]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.getIDFromQByteArrayShort]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.getIDFromQByteArrayShort]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.getIDFromQByteArrayShort]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1188]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.getIDFromQByteArrayLongHashable]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.getIDFromQByteArrayLongHashable]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.getIDFromQByteArrayLongHashable]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1205]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.getIDFromQByteArrayLongUnhashable]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.getIDFromQByteArrayLongUnhashable]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.getIDFromQByteArrayLongUnhashable]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1221]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.getIDFromQByteArrayNoCopy]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.getIDFromQByteArrayNoCopy]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.getIDFromQByteArrayNoCopy]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1237]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.getIDFromQByteArrayTwoDifferentStrings]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.getIDFromQByteArrayTwoDifferentStrings]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.getIDFromQByteArrayTwoDifferentStrings]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1252]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.getIDFromQByteArrayTwoIdenticalStrings]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.getIDFromQByteArrayTwoIdenticalStrings]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.getIDFromQByteArrayTwoIdenticalStrings]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1268]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.getIDFromQByteArrayBinaryFlag]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.getIDFromQByteArrayBinaryFlag]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.getIDFromQByteArrayBinaryFlag]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1284]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.getIDFromCString]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.getIDFromCString]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.getIDFromCString]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1297]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.getIDFromMappedNameWithoutPostfixWithoutIndex]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.getIDFromMappedNameWithoutPostfixWithoutIndex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.getIDFromMappedNameWithoutPostfixWithoutIndex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1316]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.getIDFromMappedNameWithoutPostfixWithIndex]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.getIDFromMappedNameWithoutPostfixWithIndex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.getIDFromMappedNameWithoutPostfixWithIndex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1331]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.getIDFromMappedNameWithoutIndexWithPostfix]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.getIDFromMappedNameWithoutIndexWithPostfix]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.getIDFromMappedNameWithoutIndexWithPostfix]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1348]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.getIDFromMappedNameWithIndexWithPostfix]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.getIDFromMappedNameWithIndexWithPostfix]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.getIDFromMappedNameWithIndexWithPostfix]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1367]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.getIDFromMappedNameExistingNameNoIndex]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.getIDFromMappedNameExistingNameNoIndex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.getIDFromMappedNameExistingNameNoIndex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1385]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.getIDFromMappedNameExistingNameWithIndex]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.getIDFromMappedNameExistingNameWithIndex]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.getIDFromMappedNameExistingNameWithIndex]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1400]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.getIDFromMappedNameExistingNameWithIndexAndPostfix]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.getIDFromMappedNameExistingNameWithIndexAndPostfix]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.getIDFromMappedNameExistingNameWithIndexAndPostfix]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1416]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.getIDFromMappedNameDuplicateWithEncodedPostfix]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.getIDFromMappedNameDuplicateWithEncodedPostfix]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.getIDFromMappedNameDuplicateWithEncodedPostfix]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1432]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.getIDFromIntegerIDNoSuchID]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.getIDFromIntegerIDNoSuchID]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.getIDFromIntegerIDNoSuchID]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1448]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.getIDFromIntegerIDBadID]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.getIDFromIntegerIDBadID]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.getIDFromIntegerIDBadID]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1460]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.getIDMap]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.getIDMap]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.getIDMap]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1477]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.clear]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.clear]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.clear]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1489]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.size]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.size]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.size]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1501]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.count]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.count]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.count]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1513]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.getPyObject]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.getPyObject]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.getPyObject]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1525]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.setGetSaveAll]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.setGetSaveAll]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.setGetSaveAll]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1536]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.setGetThreshold]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.setGetThreshold]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.setGetThreshold]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1551]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.clearMarks]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.clearMarks]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.clearMarks]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1564]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[StringHasherTest.compact]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=StringHasherTest.compact]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[StringHasherTest.compact]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/StringHasher.cpp:1578]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[VarSet.createVarSet]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=VarSet.createVarSet]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[VarSet.createVarSet]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/VarSet.cpp:67]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[VarSet.addProperty]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=VarSet.addProperty]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[VarSet.addProperty]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/VarSet.cpp:81]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[VRMLObjectTest.loadVRMLWithTextures]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=VRMLObjectTest.loadVRMLWithTextures]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[VRMLObjectTest.loadVRMLWithTextures]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/VRMLObject.cpp:78]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[VRMLObjectSecurityTest.singleLevelTraversalDoesNotEscapeResourceSubdirectory]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=VRMLObjectSecurityTest.singleLevelTraversalDoesNotEscapeResourceSubdirectory]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[VRMLObjectSecurityTest.singleLevelTraversalDoesNotEscapeResourceSubdirectory]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/VRMLObject.cpp:183]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[VRMLObjectSecurityTest.deepTraversalIsRejected]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=VRMLObjectSecurityTest.deepTraversalIsRejected]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[VRMLObjectSecurityTest.deepTraversalIsRejected]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/VRMLObject.cpp:196]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
add_test([=[VRMLObjectSecurityTest.legitimateResourcesStillLoadAlongsideRejectedEntry]=]  /workspace/build/tests/App_tests_run [==[--gtest_filter=VRMLObjectSecurityTest.legitimateResourcesStillLoadAlongsideRejectedEntry]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[VRMLObjectSecurityTest.legitimateResourcesStillLoadAlongsideRejectedEntry]=]
  PROPERTIES
    
    DEF_SOURCE_LINE [==[/workspace/tests/src/App/VRMLObject.cpp:204]==]
    WORKING_DIRECTORY [==[/workspace/build/tests]==]
    SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==]
    
)
set(App_tests_run_TESTS [==[AsyncRecomputeTest.CloseDocumentWaitsForInFlightAsyncRecompute]==] [==[AsyncRecomputeTest.WorkerSafetyIsCheckedFromRequest]==] [==[ApplicationTest.fCustomSyntaxLookup]==] [==[ApplicationTest.fCustomSyntaxMac]==] [==[ApplicationTest.fCustomSyntaxWidgetCount]==] [==[ApplicationTest.fCustomSyntaxNotFound]==] [==[ApplicationTest.fCustomSyntaxAmpersand]==] [==[ApplicationTest.fCustomSyntaxEmptyIn]==] [==[ApplicationDirectoriesTest.usingCurrentVersionConfigTrueWhenDirMatchesVersion]==] [==[ApplicationDirectoriesTest.usingCurrentVersionConfigFalseWhenDirDoesntMatchVersion]==] [==[ApplicationDirectoriesTest.isVersionedPathMatchesCurrentMajorAndMinor]==] [==[ApplicationDirectoriesTest.isVersionedPathMatchesLowerMinorSameMajor]==] [==[ApplicationDirectoriesTest.isVersionedPathMatchesLowerMajorAnyMinor]==] [==[ApplicationDirectoriesTest.isVersionedPathMatchesZeroMinorSameMajor]==] [==[ApplicationDirectoriesTest.isVersionedPathDoesNotMatchHigherMinorSameMajor]==] [==[ApplicationDirectoriesTest.isVersionedPathDoesNotMatchHigherMajorOrRandomName]==] [==[ApplicationDirectoriesTest.mostRecentAvailReturnsExactCurrentVersionIfDirectoryExists]==] [==[ApplicationDirectoriesTest.mostRecentAvailPrefersSameMajorAndPicksHighestLowerMinor]==] [==[ApplicationDirectoriesTest.mostRecentAvailForLowerMajorPicksHighestAvailableMinor]==] [==[ApplicationDirectoriesTest.mostRecentAvailSkipsFilesAndFallsBackToNextDirectory]==] [==[ApplicationDirectoriesTest.mostRecentAvailIgnoresHigherMinorThanCurrentInSameMajor]==] [==[ApplicationDirectoriesTest.mostRecentAvailReturnsEmptyStringWhenNoVersionsPresent]==] [==[ApplicationDirectoriesTest.mostRecentConfigReturnsCurrentVersionDirectoryIfPresent]==] [==[ApplicationDirectoriesTest.mostRecentConfigFallsBackToMostRecentInSameMajorWhenCurrentMissing]==] [==[ApplicationDirectoriesTest.mostRecentConfigSkipsFileAtCurrentVersionAndFallsBack]==] [==[ApplicationDirectoriesTest.mostRecentConfigFallsBackToHighestVersionInLowerMajors]==] [==[ApplicationDirectoriesTest.mostRecentConfigReturnsStartingPathWhenNoVersionedConfigExists]==] [==[ApplicationDirectoriesTest.usingCurrentVersionExactVersionDir]==] [==[ApplicationDirectoriesTest.usingCurrentVersionVersionDirWithTrailingSlash]==] [==[ApplicationDirectoriesTest.usingCurrentVersionFileInsideVersionDirIsFalse]==] [==[ApplicationDirectoriesTest.usingCurrentVersionLowerVersionDirIsFalse]==] [==[ApplicationDirectoriesTest.usingCurrentVersionHigherVersionDirIsFalse]==] [==[ApplicationDirectoriesTest.usingCurrentVersionNonVersionDirIsFalse]==] [==[ApplicationDirectoriesTest.migrateConfigCreatesDestinationAndCopiesFiles]==] [==[ApplicationDirectoriesTest.migrateConfigSkipsSelfWhenNewIsSubdirectoryOfOld]==] [==[ApplicationDirectoriesTest.migrateConfigEmptyOldPathJustCreatesDestination]==] [==[ApplicationDirectoriesTest.migrateConfigRecursivelyCopiesDirectoriesAndFiles]==] [==[ApplicationDirectoriesTest.migrateConfigNewPathSubdirRecursivelyCopiesAndSkipsSelf]==] [==[ApplicationDirectoriesTest.migrateAllPathsVersionedInputChoosesParentPlusCurrent]==] [==[ApplicationDirectoriesTest.migrateAllPathsNonVersionedInputAppendsCurrent]==] [==[ApplicationDirectoriesTest.migrateAllPathsIgnoresIfDestinationAlreadyExists_NonVersioned]==] [==[ApplicationDirectoriesTest.migrateConfigSkipsBrokenSymlink]==] [==[ApplicationDirectoriesTest.migrateConfigCopiesValidSymlink]==] [==[ApplicationDirectoriesTest.migrateAllPathsReturnsSkippedPaths]==] [==[ApplicationDirectoriesTest.migrateAllPathsProcessesMultipleInputs]==] [==[ApplicationDirectoriesTest.appendVecAlreadyVersionedBails]==] [==[ApplicationDirectoriesTest.appendVecBaseExistsAppendsCurrentWhenPresent]==] [==[ApplicationDirectoriesTest.appendVecPicksHighestLowerMinorInSameMajor]==] [==[ApplicationDirectoriesTest.appendVecFallsBackToLowerMajor]==] [==[ApplicationDirectoriesTest.appendVecNoVersionedChildrenLeavesVectorUnchanged]==] [==[ApplicationDirectoriesTest.appendVecBaseMissingAppendsCurrentSuffix]==] [==[ApplicationDirectoriesTest.extractVersionSucceedsWithPlainIntegers]==] [==[ApplicationDirectoriesTest.extractVersionSucceedsWithWhitespace]==] [==[ApplicationDirectoriesTest.extractVersionMissingMajorThrowsRuntimeError]==] [==[ApplicationDirectoriesTest.extractVersionMissingMinorThrowsRuntimeError]==] [==[ApplicationDirectoriesTest.extractVersionNonNumericThrowsRuntimeError]==] [==[ApplicationDirectoriesTest.extractVersionOverflowThrowsRuntimeError]==] [==[ApplicationDirectoriesTest.extractVersionNegativeNumbersPassThrough]==] [==[ApplicationDirectoriesTest.sanitizeRemovesNullCharacterAtEnd]==] [==[ApplicationDirectoriesTest.sanitizeReturnsUnchangedIfNoNullCharacter]==] [==[ApplicationDirectoriesTest.appendCreateBaseExistsAppendsCurrentWhenAlreadyPresent]==] [==[ApplicationDirectoriesTest.appendCreateBaseExistsUsesCurrentEvenWhenOlderVersionPresent]==] [==[ApplicationDirectoriesTest.appendCreateBaseExistsNoVersionsAppendsAndCreatesDir]==] [==[ApplicationDirectoriesTest.appendDoNotAppendBaseExistsNoVersionsLeavesUnchanged]==] [==[ApplicationDirectoriesTest.appendCreateBaseMissingAppendsCurrentSuffix]==] [==[ApplicationDirectoriesTest.appendCreateAlreadyVersionedBails]==] [==[BackupPolicyTest.StandardSourceDoesNotExist]==] [==[BackupPolicyTest.StandardWithZeroFilesDeletesExisting]==] [==[BackupPolicyTest.StandardWithOneFileNoPreviousBackups]==] [==[BackupPolicyTest.StandardWithOneFileOnePreviousBackup]==] [==[BackupPolicyTest.StandardWithTwoFilesOnePreviousBackup]==] [==[BackupPolicyTest.StandardWithTwoFilesOnePreviousBackupUnexpectedSuffix]==] [==[BackupPolicyTest.StandardWithTwoFilesOnePreviousBackupOutOfSequenceNumber]==] [==[BackupPolicyTest.StandardWithFCBakSet]==] [==[BackupPolicyTest.TimestampSourceDoesNotExist]==] [==[BackupPolicyTest.TimestampNoSourceGiven]==] [==[BackupPolicyTest.TimestampNoTargetGiven]==] [==[BackupPolicyTest.TimestampWithZeroFilesDeletesExisting]==] [==[BackupPolicyTest.TimestampWithOneFileAndNoneExistingNotFCBakCreatesNumberedFile]==] [==[BackupPolicyTest.TimestampSourceHasNoExtension]==] [==[BackupPolicyTest.TimestampTargetHasNoExtension]==] [==[BackupPolicyTest.TimestampWithOneFileAndNoneExistingFCBakCreatesDatedFile]==] [==[BackupPolicyTest.TimestampReplacesDotsWithDashes]==] [==[BackupPolicyTest.TimestampWithInvalidFormatStringThrows]==] [==[BackupPolicyTest.TimestampWithAbsurdlyLongFormatStringThrows]==] [==[BackupPolicyTest.TimestampDetectsOldBackupFormat]==] [==[BackupPolicyTest.TimestampDetectsOldBackupFormatIgnoresOther]==] [==[BackupPolicyTest.TimestampDetectsAndRetainsOldBackupWhenAllowed]==] [==[BackupPolicyTest.TimestampFormatStringEndsWithSpace]==] [==[BackupPolicyTest.TimestampFormatStringEndsWithDash]==] [==[BackupPolicyTest.TimestampFormatFileAlreadyExists]==] [==[BackupPolicyTest.TimestampFormatFileAlreadyExistsMultipleTimes]==] [==[Branding.one]==] [==[ComplexGeoDataTest.getIndexedNameNoName]==] [==[ComplexGeoDataTest.getIndexedNameNoElementMap]==] [==[ComplexGeoDataTest.getMappedNameNoElement]==] [==[ComplexGeoDataTest.getMappedNameDisallowUnmappedNoMap]==] [==[ComplexGeoDataTest.getMappedNameDisallowUnmappedWithMap]==] [==[ComplexGeoDataTest.getMappedNameDisallowUnmappedMissingFromMap]==] [==[ComplexGeoDataTest.getMappedNameAllowUnmapped]==] [==[ComplexGeoDataTest.getElementNameGivenIndexedName]==] [==[ComplexGeoDataTest.getElementNameGivenMappedName]==] [==[ComplexGeoDataTest.getElementMappedNamesNoMapNoUnmapped]==] [==[ComplexGeoDataTest.getElementMappedNamesWithMapNoUnmapped]==] [==[ComplexGeoDataTest.getElementMappedNamesNoMapWithUnmapped]==] [==[ComplexGeoDataTest.getElementMappedNamesWithMapWithUnmapped]==] [==[ComplexGeoDataTest.elementTypeValidIndexName]==] [==[ComplexGeoDataTest.elementTypeInvalidIndexedName]==] [==[ComplexGeoDataTest.elementTypeCharEmptyName]==] [==[ComplexGeoDataTest.elementTypeCharIndexedName]==] [==[ComplexGeoDataTest.elementTypeCharMappedNameNoPrefix]==] [==[ComplexGeoDataTest.elementTypeCharMappedNameWithPrefix]==] [==[ComplexGeoDataTest.resetElementMapNoArgument]==] [==[ComplexGeoDataTest.resetElementMapWithArgument]==] [==[ComplexGeoDataTest.setAndGetElementMap]==] [==[ComplexGeoDataTest.getElementMapSize]==] [==[ComplexGeoDataTest.flushElementMap]==] [==[ComplexGeoDataTest.saveWithNoElementMap]==] [==[ComplexGeoDataTest.saveWithElementMap]==] [==[ComplexGeoDataTest.saveWithPersistenceFilename]==] [==[ComplexGeoDataTest.saveDocFileWithNoElementMap]==] [==[ComplexGeoDataTest.saveDocFileWithElementMap]==] [==[ComplexGeoDataTest.restoreStream]==] [==[ComplexGeoDataTest.traceElement]==] [==[DocumentTest.addStringHasherIndicatesUnwrittenWhenNew]==] [==[DocumentTest.addStringHasherIndicatesAlreadyWritten]==] [==[DocumentTest.getStringHasherGivesExpectedHasher]==] [==[DocumentTest.importObjectsRestoresSourceStringHasher]==] [==[DocumentObjectTest.getSubObjectList]==] [==[DocumentObserverTest.hasSubObject]==] [==[DocumentObserverTest.hasSubElement]==] [==[DocumentObserverTest.normalize]==] [==[DocumentObserverTest.normalized]==] [==[Expression.tokenize]==] [==[Expression.tokenizeCompletion]==] [==[Expression.tokenizeQuantity]==] [==[Expression.tokenizeFunc]==] [==[Expression.tokenizeOne]==] [==[Expression.tokenizeNum]==] [==[Expression.tokenizeID]==] [==[Expression.tokenizeUnit]==] [==[Expression.tokenizeUSUnit]==] [==[Expression.tokenizeInt]==] [==[Expression.tokenizePi]==] [==[Expression.tokenizeE]==] [==[Expression.tokenizeConstant]==] [==[Expression.tokenizeEqual]==] [==[Expression.tokenizeNotEqual]==] [==[Expression.tokenizeLessThan]==] [==[Expression.tokenizeLessThanEqual]==] [==[Expression.tokenizeGreaterThan]==] [==[Expression.tokenizeGreaterThanEqual]==] [==[Expression.tokenizeMinus]==] [==[Expression.tokenizeCell1]==] [==[Expression.tokenizeCell2]==] [==[Expression.tokenizeCell3]==] [==[Expression.tokenizeString]==] [==[Expression.tokenizeExponent]==] [==[Expression.tokenizeNumAndUnit]==] [==[Expression.tokenizePos]==] [==[Expression.tokenizeNeg]==] [==[Expression.tokenizePi_rad]==] [==[Expression.toString]==] [==[Expression.test_pi_rad]==] [==[Expression.test_e_rad]==] [==[Evaluate.test_evaluate_simple]==] [==[Evaluate.test_simplify_simple]==] [==[Evaluate.test_evaluate_function]==] [==[Evaluate.test_simplify_function]==] [==[Evaluate.test_evaluate_refer_to_var]==] [==[Evaluate.test_simplify_refer_to_var]==] [==[ExpressionParserTest.functionPARSEQUANT]==] [==[ExpressionParserTest.isTokenAConstant]==] [==[ExpressionParserTest.simpleExpressionsParse]==] [==[ExpressionParserTest.expressionUserInputKeepsGroupingSeparateFromDecimals]==] [==[ExpressionParserTest.groupedExpressionUsesLocaleGroupingPattern]==] [==[ExpressionParserTest.localizedInputPreservesDigitsInsideIdentifiers]==] [==[ExpressionParserTest.functionArgumentsTakePrecedenceOverGrouping]==] [==[ExpressionParserTest.commaDecimalLocalesUseSemicolonsForArguments]==] [==[ExpressionParserTest.groupedParenthesizedExpressionsUseTheLocalePattern]==] [==[ExpressionParserTest.spaceGroupingAndSemicolonArgumentsRemainDistinct]==] [==[ExpressionParserTest.commaFunctionArgumentsRemainArgumentsWithDecimalText]==] [==[ExpressionParserTest.userInputPreservesOpaqueStringLiterals]==] [==[ExpressionParserTest.badExpressionsDoNotParse]==] [==[ExpressionParserTest.expressionsWithMultiplyDivideParse]==] [==[ExpressionParserTest.expressionsWithUnitsMultipliedDontParse_LikelyBug]==] [==[ExpressionParserTest.dimensionlessExpressionsParseAsLongOrDouble]==] [==[ExpressionParserTest.expressionsWithFunctionsParse]==] [==[ExpressionParserTest.expressionsParseAsPyObjectWrapper]==] [==[ExpressionParserTest.expressionsThatLookValidButDoNotParse]==] [==[ExpressionParserTest.canParseProperties]==] [==[QuantityInput.QuantityInputUnitUsesDisplayedScaleAndSafeFallbacks]==] [==[QuantityInput.AppliesDisplayedScaleToQuantitiesAndExpressions]==] [==[QuantityInput.EditingAndCommitDistinguishIncompleteNumbers]==] [==[QuantityInput.TrailingGroupingSeparatorFollowsTheInputPhase]==] [==[QuantityInput.ReportsGroupingAndUnitDiagnostics]==] [==[QuantityInput.AcceptsGroupedQuantityAndNormalizesIt]==] [==[QuantityInput.ReportsExpressionEvaluationAndRangeDiagnostics]==] [==[QuantityInput.GrammarSelectionIsExplicit]==] [==[QuantityInput.PositiveSignsAndCompactAdditionRemainExpressionSyntax]==] [==[QuantityInput.DefaultUnitAppliesToBareAdditiveTerms]==] [==[QuantityInput.RejectsMalformedGroupingAfterExpressionOperand]==] [==[QuantityInput.DefaultUnitPreservesExpressionDependencies]==] [==[QuantityInput.DefaultUnitDoesNotRewriteNestedMultiplicativeSubexpressions]==] [==[QuantityInput.DefaultUnitExpressionsRoundTripThroughSerialization]==] [==[QuantityInput.EditingAndCommitExposeTheSameInvalidGrouping]==] [==[QuantityInput.SharedLocalizedInputCorpus]==] [==[ElementMapTest.defaultConstruction]==] [==[ElementMapTest.setElementNameDefaults]==] [==[ElementMapTest.setElementNameNoOverwrite]==] [==[ElementMapTest.setElementNameWithOverwrite]==] [==[ElementMapTest.setElementNameWithHashing]==] [==[ElementMapTest.eraseMappedName]==] [==[ElementMapTest.eraseIndexedName]==] [==[ElementMapTest.findMappedName]==] [==[ElementMapTest.findIndexedName]==] [==[ElementMapTest.findAll]==] [==[ElementMapTest.mimicOnePart]==] [==[ElementMapTest.mimicSimpleUnion]==] [==[ElementMapTest.mimicOperationAgainstSelf]==] [==[ElementMapTest.hasChildElementMapTest]==] [==[ElementMapTest.hashChildMapsTest]==] [==[ElementMapTest.addAndGetChildElementsTest]==] [==[ElementNamingUtilsTest.findElementName]==] [==[ElementNamingUtilsTest.indexOfElement]==] [==[IndexedNameTest.defaultConstruction]==] [==[IndexedNameTest.nameOnlyConstruction]==] [==[IndexedNameTest.nameAndIndexConstruction]==] [==[IndexedNameTest.nameAndIndexConstructionWithOverride]==] [==[IndexedNameTest.constructionInvalidCharInName]==] [==[IndexedNameTest.constructionNumberInName]==] [==[IndexedNameTest.nameAndTypeListConstructionWithoutAllowOthers]==] [==[IndexedNameTest.nameAndTypeListConstructionWithAllowOthers]==] [==[IndexedNameTest.nameAndTypeListConstructionReusedMemoryCheck]==] [==[IndexedNameTest.byteArrayConstruction]==] [==[IndexedNameTest.copyConstruction]==] [==[IndexedNameTest.streamInsertionOperator]==] [==[IndexedNameTest.compoundAssignmentOperator]==] [==[IndexedNameTest.preincrementOperator]==] [==[IndexedNameTest.predecrementOperator]==] [==[IndexedNameTest.comparisonOperators]==] [==[IndexedNameTest.subscriptOperator]==] [==[IndexedNameTest.getType]==] [==[IndexedNameTest.setIndex]==] [==[IndexedNameTest.isNullTrue]==] [==[IndexedNameTest.isNullFalse]==] [==[IndexedNameTest.booleanConversionFalse]==] [==[IndexedNameTest.booleanConversionTrue]==] [==[IndexedNameTest.fromConst]==] [==[IndexedNameTest.appendToStringBufferEmptyBuffer]==] [==[IndexedNameTest.appendToStringBufferNonEmptyBuffer]==] [==[IndexedNameTest.appendToStringBufferZeroIndex]==] [==[IndexedNameTest.toString]==] [==[IndexedNameTest.toStringNoIndex]==] [==[IndexedNameTest.assignmentOperator]==] [==[ByteArrayTest.QByteArrayConstruction]==] [==[ByteArrayTest.CopyConstruction]==] [==[ByteArrayTest.MoveConstruction]==] [==[ByteArrayTest.ensureUnshared]==] [==[ByteArrayTest.equalityOperator]==] [==[ByteArrayTest.assignmentOperator]==] [==[ByteArrayTest.moveAssignmentOperator]==] [==[License.isLicenseEmpty]==] [==[License.isLicenseNull]==] [==[License.isLicenseYesStr]==] [==[License.UnknownIdentifier]==] [==[License.direct]==] [==[License.findLicenseByIdent]==] [==[LinkTest.getArrayIndexSimpleInteger]==] [==[LinkTest.getArrayIndexZero]==] [==[LinkTest.getArrayIndexWithDotSuffix]==] [==[LinkTest.getArrayIndexMultiDigitWithDot]==] [==[LinkTest.getArrayIndexTrailingDotOnly]==] [==[LinkTest.getArrayIndexReturnsMinusOneForNull]==] [==[LinkTest.getArrayIndexReturnsMinusOneForEmptyString]==] [==[LinkTest.getArrayIndexReturnsMinusOneForLeadingDot]==] [==[LinkTest.getArrayIndexReturnsMinusOneForAlpha]==] [==[LinkTest.getArrayIndexReturnsMinusOneForMixedAlphaDigit]==] [==[LinkTest.getArrayIndexReturnsMinusOneForAlphaThenDigit]==] [==[LinkTest.getArrayIndexReturnsMinusOneForMappedElement]==] [==[LinkTest.getArrayIndexReturnsMinusOneForMappedElementWithDigits]==] [==[LinkTest.getArrayIndexPsubnamePointsPastDot]==] [==[LinkTest.getArrayIndexPsubnameAtEndWhenNoDot]==] [==[LinkTest.getArrayIndexPsubnameEmptyAfterTrailingDot]==] [==[LinkTest.getArrayIndexPsubnameWithNestedDots]==] [==[LinkTest.getArrayIndexPsubnameUntouchedOnFailure]==] [==[LinkTest.getArrayIndexPsubnameUntouchedOnNull]==] [==[LinkTest.getArrayIndexLargeNumber]==] [==[LinkTest.getArrayIndexReturnsMinusOneForNegative]==] [==[LinkTest.getArrayIndexReturnsMinusOneForSpace]==] [==[LinkTest.getArrayIndexReturnsMinusOneForDigitWithSpace]==] [==[LinkTest.getScaleVectorDefaultIsUnity]==] [==[LinkTest.getScaleVectorReflectsUniformScale]==] [==[LinkTest.getScaleVectorReflectsNonUniformScale]==] [==[LinkTest.getTransformNoTransformDefaultIsIdentity]==] [==[LinkTest.getTransformWithTransformDefaultIsIdentity]==] [==[LinkTest.getTransformNoTransformAppliesScaleOnly]==] [==[LinkTest.getTransformNoTransformIgnoresPlacement]==] [==[LinkTest.getTransformWithTransformIncludesLinkPlacement]==] [==[LinkTest.getTransformWithTransformAndScale]==] [==[LinkTest.getTransformUsesLinkPlacementWhenPropertyExists]==] [==[LinkTest.linkPlacementAndPlacementStayInSync]==] [==[MappedElementTest.constructFromNameAndIndex]==] [==[MappedElementTest.moveConstructor]==] [==[MappedElementTest.assignmentOperator]==] [==[MappedElementTest.moveAssignmentOperator]==] [==[MappedElementTest.equalityOperatorsWhenNotEqual]==] [==[MappedElementTest.equalityOperatorsWhenEqual]==] [==[MappedElementTest.lessThanOperator]==] [==[MappedElementTest.comparatorBothAreZeroSize]==] [==[MappedElementTest.comparatorOneIsZeroSize]==] [==[MappedElementTest.comparatorBothStartWithHexDigitsThatDiffer]==] [==[MappedElementTest.comparatorBothStartWithTheSameHexDigits]==] [==[MappedElementTest.comparatorHexWithoutTerminator]==] [==[MappedElementTest.comparatorHexWithoutTerminatorSameLength]==] [==[MappedElementTest.comparatorNoHexDigitsLexicalCompare]==] [==[MappedElementTest.comparatorNoHexDigitsSameStringNumericCompare]==] [==[MappedElementTest.comparatorIntegerWithoutTerminatorIsBroken]==] [==[MappedElementTest.comparatorThreeComplexHexNamesInMap]==] [==[MappedElementTest.comparatorLargerWorkedExampleWithMap]==] [==[MappedName.defaultConstruction]==] [==[MappedName.namedConstruction]==] [==[MappedName.namedConstructionWithMaxSize]==] [==[MappedName.namedConstructionDiscardPrefix]==] [==[MappedName.stringNamedConstruction]==] [==[MappedName.stringNamedConstructionDiscardPrefix]==] [==[MappedName.constructFromIndexedNameNoIndex]==] [==[MappedName.constructFromIndexedNameWithIndex]==] [==[MappedName.copyConstructor]==] [==[MappedName.copyConstructorWithPostfix]==] [==[MappedName.copyConstructorStartpos]==] [==[MappedName.copyConstructorStartposAndSize]==] [==[MappedName.moveConstructor]==] [==[MappedName.fromRawData]==] [==[MappedName.fromRawDataQByteArray]==] [==[MappedName.fromRawDataCopy]==] [==[MappedName.fromRawDataCopyStartposAndSize]==] [==[MappedName.assignmentOperator]==] [==[MappedName.assignmentOperatorString]==] [==[MappedName.assignmentOperatorConstCharPtr]==] [==[MappedName.assignmentOperatorMove]==] [==[MappedName.streamInsertionOperator]==] [==[MappedName.comparisonOperators]==] [==[MappedName.additionOperators]==] [==[MappedName.append]==] [==[MappedName.appendMappedNameObj]==] [==[MappedName.toString]==] [==[MappedName.toConstString]==] [==[MappedName.toRawBytes]==] [==[MappedName.toIndexedNameASCIIOnly]==] [==[MappedName.toIndexedNameInvalid]==] [==[MappedName.appendToBuffer]==] [==[MappedName.appendToBufferWithPrefix]==] [==[MappedName.toPrefixedString]==] [==[MappedName.toBytes]==] [==[MappedName.compare]==] [==[MappedName.subscriptOperator]==] [==[MappedName.copy]==] [==[MappedName.compact]==] [==[MappedName.boolOperator]==] [==[MappedName.clear]==] [==[MappedName.find]==] [==[MappedName.rfind]==] [==[MappedName.endswith]==] [==[MappedName.startsWith]==] [==[MappedName.findTagInElementNameHexPositiveIndexNonrecursive]==] [==[MappedName.findTagInElementNameDecPositiveIndexNonrecursive]==] [==[MappedName.findTagInElementNameHexNegativeIndexNonrecursive]==] [==[MappedName.findTagInElementNameHexExpectedNegativeIndexNonrecursive]==] [==[MappedName.findTagInElementNameRecursive]==] [==[MappedName.hash]==] [==[ContactTest.ContactDefaultConstruction]==] [==[ContactTest.ContactParameterConstruction]==] [==[ContactTest.ContactNullDomNodeConstruction]==] [==[ContactTest.ContactOperatorEquality]==] [==[LicenseTest.LicenseDefaultConstruction]==] [==[LicenseTest.LicenseParameterConstruction]==] [==[LicenseTest.LicenseNullDomNodeConstruction]==] [==[LicenseTest.LicenseOperatorEquality]==] [==[UrlTest.UrlDefaultConstruction]==] [==[UrlTest.UrlParameterConstruction]==] [==[UrlTest.UrlNullDomNodeConstruction]==] [==[UrlTest.UrlOperatorEquality]==] [==[VersionTest.VersionDefaultConstruction]==] [==[VersionTest.VersionParameterConstruction]==] [==[VersionTest.VersionStringConstruction]==] [==[VersionTest.VersionOperatorEqual]==] [==[VersionTest.VersionOperatorComparison]==] [==[MetadataTest.MetadataInMemoryConstruction]==] [==[ProjectFileTest.loadInvalid]==] [==[ProjectFileTest.loadDocument]==] [==[ProjectFileTest.getObjects]==] [==[ProjectFileTest.getPropertyFiles]==] [==[ProjectFileTest.getMetadata]==] [==[ProjectFileTest.getObjectsOfType]==] [==[ProjectFileTest.restoreObject]==] [==[ProjectFileTest.getTypeId]==] [==[ProjectFileTest.getThumbnailBuffer]==] [==[ProjectFileTest.getThumbnailFile]==] [==[PropertyFileIncludedTest.rejectsParentTraversalInFileAttribute]==] [==[PropertyFileIncludedTest.rejectsBackslashTraversalInFileAttribute]==] [==[PropertyFileIncludedTest.rejectsAbsolutePathInFileAttribute]==] [==[PropertyFileIncludedTest.rejectsSubdirectoryInFileAttribute]==] [==[PropertyFileIncludedTest.rejectsDotDotInFileAttribute]==] [==[PropertyFileIncludedTest.rejectsParentTraversalInDataAttribute]==] [==[PropertyFileIncludedTest.acceptsPlainBasename]==] [==[PropertyLink.TestSetValues]==] [==[PropertyFloatTest.testWriteRead]==] [==[RenameProperty.simple]==] [==[RenameProperty.fromPython]==] [==[RenameProperty.chain]==] [==[RenameProperty.staticProperty]==] [==[RenameProperty.staticPropertyFromPython]==] [==[RenameProperty.lockedProperty]==] [==[RenameProperty.toExistingProperty]==] [==[RenameProperty.toInvalidProperty]==] [==[RenameProperty.updateExpressionSameContainer]==] [==[RenameProperty.updateExpressionDifferentContainer]==] [==[RenameProperty.updateExpressionDifferentDocument]==] [==[RenameProperty.withExpression]==] [==[RenameProperty.undo]==] [==[RenameProperty.redo]==] [==[MoveProperty.simple]==] [==[MoveProperty.otherDoc]==] [==[MoveProperty.staticProperty]==] [==[MoveProperty.lockedProperty]==] [==[MoveProperty.toExistingProperty]==] [==[MoveProperty.updateExpressionOriginatingContainer]==] [==[MoveProperty.updateExpressionTargetContainer]==] [==[MoveProperty.updateExpressionOriginatingContainerOtherDoc]==] [==[MoveProperty.updateExpressionTargetContainerOtherDoc]==] [==[MoveProperty.updateExpressionMovedProp]==] [==[MoveProperty.undo]==] [==[MoveProperty.undoOtherDoc]==] [==[MoveProperty.undoExpressionOriginatingContainer]==] [==[MoveProperty.undoExpressionTargetContainer]==] [==[MoveProperty.undoExpressionOriginatingContainerOtherDoc]==] [==[MoveProperty.undoExpressionTargetContainerOtherDoc]==] [==[MoveProperty.redoSimple]==] [==[MoveProperty.redoOtherDoc]==] [==[MoveProperty.redoExpressionOriginatingContainer]==] [==[MoveProperty.redoExpressionTargetContainer]==] [==[MoveProperty.redoExpressionOriginatingContainerOtherDoc]==] [==[MoveProperty.redoExpressionTargetContainerOtherDoc]==] [==[PropertyExpressionEngineTest.executeCrossPropertyReference]==] [==[StringIDTest.stringIDManualConstructionNoFlags]==] [==[StringIDTest.stringIDManualConstructionWithFlag]==] [==[StringIDTest.stringIDDefaultConstruction]==] [==[StringIDTest.value]==] [==[StringIDTest.relatedIDs]==] [==[StringIDTest.isBinary]==] [==[StringIDTest.isHashed]==] [==[StringIDTest.isPostfixed]==] [==[StringIDTest.isPostfixEncoded]==] [==[StringIDTest.isIndexed]==] [==[StringIDTest.isPrefixID]==] [==[StringIDTest.isPrefixIDIndex]==] [==[StringIDTest.isMarked]==] [==[StringIDTest.isPersistent]==] [==[StringIDTest.isFromSameHasher]==] [==[StringIDTest.getHasher]==] [==[StringIDTest.data]==] [==[StringIDTest.postfix]==] [==[StringIDTest.getPyObject]==] [==[StringIDTest.getPyObjectWithIndex]==] [==[StringIDTest.toStringWithoutIndex]==] [==[StringIDTest.toStringWithIndex]==] [==[StringIDTest.fromStringWithEOFAndLengthGood]==] [==[StringIDTest.fromStringExtraData]==] [==[StringIDTest.fromStringLengthUnspecified]==] [==[StringIDTest.fromStringShorterLength]==] [==[StringIDTest.fromStringNoHashtag]==] [==[StringIDTest.fromStringNotHex]==] [==[StringIDTest.fromStringQByteArray]==] [==[StringIDTest.dataToTextHashed]==] [==[StringIDTest.dataToTextBinary]==] [==[StringIDTest.dataToTextNoIndex]==] [==[StringIDTest.dataToTextWithIndex]==] [==[StringIDTest.dataToTextWithPostfix]==] [==[StringIDTest.dataToBytesNoIndex]==] [==[StringIDTest.dataToBytesWithIndex]==] [==[StringIDTest.dataToBytesWithPostfix]==] [==[StringIDTest.dataToBytesWithIndexAndPostfix]==] [==[StringIDTest.mark]==] [==[StringIDTest.setPersistent]==] [==[StringIDTest.operatorLessThan]==] [==[StringIDTest.compare]==] [==[StringIDTest.IndexIDBooleanConversion]==] [==[StringIDTest.IndexIDStreamInsertionOperator]==] [==[StringIDRefTest.defaultConstructor]==] [==[StringIDRefTest.constructFromNewStringID]==] [==[StringIDRefTest.constructFromStringIDAndIndex]==] [==[StringIDRefTest.copyConstructor]==] [==[StringIDRefTest.copyConstructorWithIndex]==] [==[StringIDRefTest.moveConstructor]==] [==[StringIDRefTest.destructor]==] [==[StringIDRefTest.reset]==] [==[StringIDRefTest.resetWithStringID]==] [==[StringIDRefTest.resetWithStringIDAndIndex]==] [==[StringIDRefTest.swap]==] [==[StringIDRefTest.assignmentFromSelf]==] [==[StringIDRefTest.assignmentToEmptyFromStringID]==] [==[StringIDRefTest.assignmentFromStringIDRef]==] [==[StringIDRefTest.moveAssignmentFromStringIDRef]==] [==[StringIDRefTest.operatorLess]==] [==[StringIDRefTest.operatorEquality]==] [==[StringIDRefTest.operatorInequality]==] [==[StringIDRefTest.booleanConversion]==] [==[StringIDRefTest.getRefCount]==] [==[StringIDRefTest.toString]==] [==[StringIDRefTest.dataToText]==] [==[StringIDRefTest.constData]==] [==[StringIDRefTest.deref]==] [==[StringIDRefTest.value]==] [==[StringIDRefTest.relatedIDs]==] [==[StringIDRefTest.isBinary]==] [==[StringIDRefTest.isHashed]==] [==[StringIDRefTest.toBytes]==] [==[StringIDRefTest.getPyObject]==] [==[StringIDRefTest.mark]==] [==[StringIDRefTest.isMarked]==] [==[StringIDRefTest.isFromSameHasher]==] [==[StringIDRefTest.getHasher]==] [==[StringIDRefTest.setPersistent]==] [==[StringHasherTest.defaultConstructor]==] [==[StringHasherTest.getMemSize]==] [==[StringHasherTest.Save]==] [==[StringHasherTest.Restore]==] [==[StringHasherTest.SaveDocFile]==] [==[StringHasherTest.RestoreDocFile]==] [==[StringHasherTest.setPersistenceFileName]==] [==[StringHasherTest.getPersistenceFileName]==] [==[StringHasherTest.getIDFromQByteArrayShort]==] [==[StringHasherTest.getIDFromQByteArrayLongHashable]==] [==[StringHasherTest.getIDFromQByteArrayLongUnhashable]==] [==[StringHasherTest.getIDFromQByteArrayNoCopy]==] [==[StringHasherTest.getIDFromQByteArrayTwoDifferentStrings]==] [==[StringHasherTest.getIDFromQByteArrayTwoIdenticalStrings]==] [==[StringHasherTest.getIDFromQByteArrayBinaryFlag]==] [==[StringHasherTest.getIDFromCString]==] [==[StringHasherTest.getIDFromMappedNameWithoutPostfixWithoutIndex]==] [==[StringHasherTest.getIDFromMappedNameWithoutPostfixWithIndex]==] [==[StringHasherTest.getIDFromMappedNameWithoutIndexWithPostfix]==] [==[StringHasherTest.getIDFromMappedNameWithIndexWithPostfix]==] [==[StringHasherTest.getIDFromMappedNameExistingNameNoIndex]==] [==[StringHasherTest.getIDFromMappedNameExistingNameWithIndex]==] [==[StringHasherTest.getIDFromMappedNameExistingNameWithIndexAndPostfix]==] [==[StringHasherTest.getIDFromMappedNameDuplicateWithEncodedPostfix]==] [==[StringHasherTest.getIDFromIntegerIDNoSuchID]==] [==[StringHasherTest.getIDFromIntegerIDBadID]==] [==[StringHasherTest.getIDMap]==] [==[StringHasherTest.clear]==] [==[StringHasherTest.size]==] [==[StringHasherTest.count]==] [==[StringHasherTest.getPyObject]==] [==[StringHasherTest.setGetSaveAll]==] [==[StringHasherTest.setGetThreshold]==] [==[StringHasherTest.clearMarks]==] [==[StringHasherTest.compact]==] [==[VarSet.createVarSet]==] [==[VarSet.addProperty]==] [==[VRMLObjectTest.loadVRMLWithTextures]==] [==[VRMLObjectSecurityTest.singleLevelTraversalDoesNotEscapeResourceSubdirectory]==] [==[VRMLObjectSecurityTest.deepTraversalIsRejected]==] [==[VRMLObjectSecurityTest.legitimateResourcesStillLoadAlongsideRejectedEntry]==])
