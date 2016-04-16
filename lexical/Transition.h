//
// Created by ahmedatef on 4/15/16.
//

#ifndef STRING_PARSER_TRANSITION_H
#define STRING_PARSER_TRANSITION_H

#include <iostream>
#include <string>
#include "State.h"
using namespace std;

class State;

class Transition {
public:
    State* next_state;
    string value;

    Transition(State *next_state, string value = "");
};


#endif //STRING_PARSER_TRANSITION_H
