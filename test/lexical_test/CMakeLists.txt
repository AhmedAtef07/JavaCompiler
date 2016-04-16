include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

project(lexical_test)

add_executable(TEST_FILES
        DfaTest.cpp)

target_link_libraries(TEST_FILES gtest gtest_main)
target_link_libraries(TEST_FILES lexical)