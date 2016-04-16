//
// Created by ahmedatef on 4/15/16.
//

#include "State.h"

int State::next_id = 0;

State::State() {
    this->id = next_id++;
    printf("New State has been created with id: %d, memory reference: %p\n", this->id, this);
}

void State::AddTransition(Transition* transition) {
    outgoing_transitions.push_back(transition);
}