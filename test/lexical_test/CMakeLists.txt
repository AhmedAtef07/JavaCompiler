include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

project(lexical_test)

add_executable(LEXICAL_TEST_FILES
        NfaTest.cpp
        RegularExpressionTest.cpp
        DfaTest.cpp
        ParsingTest.cpp
        RegularDefinitionTest.cpp VisualiserTest.cpp)

target_link_libraries(LEXICAL_TEST_FILES gtest gtest_main)
target_link_libraries(LEXICAL_TEST_FILES lexical)