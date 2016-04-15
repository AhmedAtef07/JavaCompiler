//
// Created by ahmedatef on 4/15/16.
//

#ifndef STRING_PARSER_NFA_H
#define STRING_PARSER_NFA_H

#include <iostream>
#include <set>
#include "Transition.h"
#include "State.h"

class State;

class Nfa {
public:
    State* start_state;
    State* terminal_state;

    Nfa();
    Nfa(string value);

    static Nfa* Concatenate(Nfa* nfa1, Nfa* nfa2);
};


#endif //STRING_PARSER_NFA_H
