cmake_minimum_required(VERSION 3.5)

project(JavaCompiler)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

add_executable(main main.cpp)

include_directories(lexical)
include_directories(syntax)

add_subdirectory(lexical)
add_subdirectory(syntax)
add_subdirectory(test)

target_link_libraries(main lexical syntax)
