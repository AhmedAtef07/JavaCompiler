cmake_minimum_required(VERSION 3.5)
project(JavaCompiler)

add_subdirectory(googletest)
enable_testing()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


set(SOURCE_FILES
    src/main.cpp
    src/Nfa.cpp
    src/Nfa.h
    src/RegularDefinition.cpp
    src/RegularDefinition.h
    src/State.cpp
    src/State.h
    src/Transition.cpp
    src/Transition.h
    src/RegularExpression.cpp
    src/RegularExpression.h
        unit.cpp
)

target_link_libraries(runUnitTest ${SOURCE_FILES})
target_link_libraries(runUnitTest gtest gtest_main)

add_test(NAME    runUnitTest
        COMMAND runUnitTest)