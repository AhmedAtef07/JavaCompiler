cmake_minimum_required(VERSION 3.5)

add_definitions(-std=c++11)

set(SRC_FILES
        Nfa.cpp
        Nfa.h
        RegularDefinition.cpp
        RegularDefinition.h
        State.cpp
        State.h
        Transition.cpp
        Transition.h
        RegularExpression.cpp
        RegularExpression.h
        Dfa.cpp
        Dfa.h
        Token.cpp
        Token.h
        Visualiser.cpp
        Visualiser.h
        Lexical.cpp
        Lexical.h
        Symbol.h ContextFreeGrammar.cpp ContextFreeGrammar.h)

add_library(lexical STATIC ${SRC_FILES})