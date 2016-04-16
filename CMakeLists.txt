cmake_minimum_required(VERSION 3.5)
project(JavaCompiler)

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
)
add_executable(JavaCompiler ${SOURCE_FILES})