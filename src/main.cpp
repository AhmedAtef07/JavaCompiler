#include <iostream>
#include "Nfa.h"

using namespace std;

/*
 * 1. Eliminate all parentheses.
 * 2.
 */
int main() {
    string test = "(a*(k|l|(mn|k))*l)+";
    cout << test << endl;
    cout << endl << endl;

    Nfa* nfa0 = new Nfa("a");
    Nfa* nfa1 = new Nfa("b");

    Nfa* nfa01 = Nfa::Concatenate(nfa0, nfa1);

    cout << nfa01->start_state->id << endl;
    cout << nfa01->start_state->outgoing_transitions[0]->value << endl;
    cout << nfa01->start_state->outgoing_transitions[0]->next_state->id << endl;
    cout << nfa01->start_state->outgoing_transitions[0]->next_state->outgoing_transitions[0]->value << endl;
    cout << nfa01->start_state->outgoing_transitions[0]->next_state->outgoing_transitions[0]->next_state->id << endl;
    cout << nfa01->start_state->outgoing_transitions[0]->next_state->outgoing_transitions[0]->next_state->
            outgoing_transitions[0]->value << endl;
    cout << nfa01->start_state->outgoing_transitions[0]->next_state->outgoing_transitions[0]->next_state->
            outgoing_transitions[0]->next_state->id << endl;

//    cout << nfa->start_state->id << endl;
//    cout << nfa->start_state->outgoing_transitions[0]->value << endl;
//    cout << nfa->start_state->outgoing_transitions[0]->next_state->id << endl;

    return 0;
}



/*
 * TODO: Nfa, State, Transition classes;
 * TODO: operations on NFAs.
 */