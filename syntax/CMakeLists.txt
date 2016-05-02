cmake_minimum_required(VERSION 3.5)

add_definitions(-std=c++11)

set(SRC_FILES
        Symbol.cpp
        Symbol.h
        ContextFreeGrammar.cpp
        ContextFreeGrammar.h
        GrammarRule.cpp
        GrammarRule.h
        ParsingFunctions.h)

add_library(syntax STATIC ${SRC_FILES})