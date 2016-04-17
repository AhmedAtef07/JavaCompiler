//
// Created by ahmedatef on 4/15/16.
//

#ifndef STRING_PARSER_NFA_H
#define STRING_PARSER_NFA_H

#include <iostream>
#include <set>
#include "Transition.h"
#include "State.h"
#include "RegularDefinition.h"

class State;
class RegularDefinition;

class Nfa {
public:
    State* start_state;
    State* terminal_state;

    Nfa();
    Nfa(string value);
    Nfa(State *start_state, State *terminal_state);

    static Nfa* Concatenate(Nfa* nfa1, Nfa* nfa2);
    static Nfa* Star(Nfa *nfa);
    static Nfa* Plus(Nfa *nfa);
    static Nfa* Parallel(Nfa* nfa1, Nfa* nfa2);
    static Nfa* Parallel(vector<Nfa*> nfas);

    static Nfa* Solver(vector<RegularDefinition *> regular_definition_vector);
};


#endif //STRING_PARSER_NFA_H
