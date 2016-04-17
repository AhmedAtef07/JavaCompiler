//
// Created by ahmedatef on 4/17/16.
//

#include "Visualiser.h"
#include <queue>

string Visualiser::JsonFromNfa(Nfa * nfa) {
    set<State *> visited_states;
    queue<State *> bfs;
    bfs.push(nfa->start_state);
    visited_states.insert(nfa->start_state);
    string result = "";

    while(!bfs.empty()) {
        State* front_state = bfs.front();
        bfs.pop();
        string outgoing_states = to_string(front_state->id) + ": ";
        for(Transition* transition: front_state->outgoing_transitions) {
            outgoing_states += "('" + transition->value + "', ";
            outgoing_states += to_string(transition->next_state->id) + ") ";
            if(visited_states.find(transition->next_state) == visited_states.end()) {
                bfs.push(transition->next_state);
                visited_states.insert(transition->next_state);
            }
        }
        if(front_state->is_acceptence) outgoing_states += "\t[Accepted State]";
        outgoing_states += "\n";
        result += outgoing_states;
    }
    return result;
}