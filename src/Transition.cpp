//
// Created by ahmedatef on 4/15/16.
//

#include "Transition.h"

Transition::Transition(State *next_state, const string &value) : next_state(next_state), value(value) { }