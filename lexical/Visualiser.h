//
// Created by ahmedatef on 4/17/16.
//

#ifndef JAVACOMPILER_VISUALISER_H
#define JAVACOMPILER_VISUALISER_H


#include <map>
#include "Nfa.h"
#include "State.h"
#include "Dfa.h"

class Visualiser {

public:
    static string JsonFromNfa(Nfa *);
    static string JsonFromDfa(Dfa *);
    static string JsonFromState(State *);
    static void set_index_of_node(std::map<int, int> &node_indexat, int &node_index, const State *front_state);
    static string is_epsilon(string v);
};


#endif //JAVACOMPILER_VISUALISER_H
