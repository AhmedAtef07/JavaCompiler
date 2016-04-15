cmake_minimum_required(VERSION 3.5)
project(string_parser)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main.cpp src/Nfa.cpp src/Nfa.h src/State.cpp src/State.h src/Transition.cpp src/Transition.h src/RegularDefinition.cpp src/RegularDefinition.h)
add_executable(string_parser ${SOURCE_FILES})