include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

project(lexical_test)

add_executable(TEST_FILES
        NfaTest.cpp
        RegularExpressionTest.cpp
        DfaTest.cpp
        ParsingTest.cpp
        RegularDefinitionTest.cpp)

target_link_libraries(TEST_FILES gtest gtest_main)
target_link_libraries(TEST_FILES lexical)