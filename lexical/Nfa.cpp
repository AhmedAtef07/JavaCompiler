//
// Created by ahmedatef on 4/15/16.
//

#include <stdexcept>
#include "Nfa.h"

Nfa::Nfa() { }

Nfa::Nfa(string value) {
    State* head_state = new State();
    State* tail_state = new State();

    Transition* transition = new Transition(tail_state, value);

    head_state->AddTransition(transition);

    this->start_state = head_state;
    this->terminal_state = tail_state;
    this->terminal_state->is_acceptence = true;
}

Nfa::Nfa(State *start_state, State *terminal_state) :
        start_state(start_state), terminal_state(terminal_state) {
    if(!this->terminal_state->is_acceptence) {
        throw std::invalid_argument("terminal_state passed is not set as an acceptance state.");
    }
}

Nfa* Nfa::Concatenate(Nfa* nfa1, Nfa* nfa2) {
    nfa1->terminal_state->is_acceptence = false;

    Nfa* nfa = new Nfa(nfa1->start_state, nfa2->terminal_state);

    nfa1->terminal_state->AddTransition(new Transition(nfa2->start_state));

//    free(nfa1);
//    free(nfa2);
    return nfa;
}

Nfa* Nfa::Star(Nfa* nfa) {
    State* s_head = new State();
    State* s_tail = new State(true);

    nfa->terminal_state->is_acceptence = false;

    s_head->AddTransition(new Transition(nfa->start_state));
    s_head->AddTransition(new Transition(s_tail));
    nfa->terminal_state->AddTransition(new Transition(nfa->start_state));
    nfa->terminal_state->AddTransition(new Transition(s_tail));

    return new Nfa(s_head, s_tail);
}

Nfa* Nfa::Parallel(Nfa* nfa1, Nfa* nfa2) {
    State* s_head = new State();
    State* s_tail = new State(true);

    nfa1->terminal_state->is_acceptence = false;
    nfa2->terminal_state->is_acceptence = false;

    s_head->AddTransition(new Transition(nfa1->start_state));
    s_head->AddTransition(new Transition(nfa2->start_state));

    nfa1->terminal_state->AddTransition(new Transition(s_tail));
    nfa2->terminal_state->AddTransition(new Transition(s_tail));

    return new Nfa(s_head, s_tail);
}

Nfa* Nfa::Plus(Nfa* nfa) {
    return Concatenate(nfa, Star(nfa));
}