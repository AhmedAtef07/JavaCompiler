//
// Created by ahmedatef on 4/15/16.
//

#include "Nfa.h"

Nfa::Nfa(string value) {
    State* head_state = new State();
    State* tail_state = new State();

    Transition* transition = new Transition(tail_state, value);

    head_state->AddTransition(transition);

    this->start_state = head_state;
    this->terminal_state = tail_state;
}

Nfa::Nfa() {

}

Nfa* Nfa::Concatenate(Nfa* nfa1, Nfa* nfa2) {
    Nfa* nfa = new Nfa();
    nfa->start_state = nfa1->start_state;
    nfa->terminal_state = nfa2->terminal_state;

    nfa1->terminal_state->AddTransition(new Transition(nfa2->start_state, ""));

//    free(nfa1);
//    free(nfa2);

    return nfa;
}




