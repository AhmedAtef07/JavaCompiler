//
// Created by ahmedatef on 4/15/16.
//

#ifndef STRING_PARSER_STATE_H
#define STRING_PARSER_STATE_H

#include <iostream>
#include <set>
#include <vector>
#include "Transition.h"
using namespace std;

class Transition;

class State {
public:
    int id;
    bool is_acceptence;
    // Should be changed to set for better performance.
    vector<Transition*> outgoing_transitions;

    State();
    State(bool is_acceptence);

    void AddTransition(Transition* transition);

protected:
    static int next_id;
};


#endif //STRING_PARSER_NODE_H
