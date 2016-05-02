include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

project(syntax_test)

add_executable(SYNTAX_TEST_FILE basic_test.cpp)

target_link_libraries(SYNTAX_TEST_FILE gtest gtest_main)
target_link_libraries(SYNTAX_TEST_FILE syntax)