//
// Created by ahmedatef on 4/15/16.
//

#include <stdexcept>
#include <stack>
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

Nfa* Nfa::Parallel(vector<Nfa*> nfas) {
    State* s_head = new State();
    State* s_tail = new State(true);

    for(Nfa* nfa: nfas) {
        nfa->terminal_state->is_acceptence = false;
        s_head->AddTransition(new Transition(nfa->start_state));
        nfa->terminal_state->AddTransition(new Transition(s_tail));
    }

    return new Nfa(s_head, s_tail);
}

Nfa* Nfa::Plus(Nfa* nfa) {
    return Concatenate(nfa, Star(nfa));
}


void print_vector_(vector<Nfa*> nfa_vector) {
    cout << "Upcoming Nfa" << endl;
    for(Nfa* nfa: nfa_vector) {
        cout << nfa->start_state->outgoing_transitions[0]->value << endl << " ";
    }
    cout << endl << endl;
}

Nfa* Nfa::Solver(vector<RegularDefinition *> regular_definition_vector) {
    stack<RegularDefinition *> solver;

    for(RegularDefinition *rd: regular_definition_vector) {
        if(rd->type == RegularDefinition::Type::kOperation){
            string operation_value = rd->GetOperation();
            if(operation_value == "(" || operation_value == "|") {
                solver.push(rd);
            } else if(operation_value == "*") {
                Nfa* stared = Nfa::Star(solver.top()->GetNfa());
                solver.pop();

                RegularDefinition* stared_rd = new RegularDefinition(RegularDefinition::Type::kNfa, stared);
                solver.push(stared_rd);
            } else if(operation_value == "+") {
                Nfa* stared = Nfa::Plus(solver.top()->GetNfa());
                solver.pop();

                RegularDefinition* stared_rd = new RegularDefinition(RegularDefinition::Type::kNfa, stared);
                solver.push(stared_rd);
            } else if(operation_value == ")") {
                cout << "Closing parenthsis" << endl;
                vector<Nfa*> parallel_nfa;
                while(solver.top()->type == RegularDefinition::kNfa || solver.top()->GetOperation() != "(") {
                    cout << "In While Loop" << endl;
                    if(solver.top()->type == RegularDefinition::kOperation) {
                        solver.pop();
                        continue;
                    }
                    parallel_nfa.push_back(solver.top()->GetNfa());
                    solver.pop();
                }
                solver.pop();
//                cout << "After Loop" << endl;
//                print_vector(parallel_nfa);
                solver.push(new RegularDefinition(RegularDefinition::Type::kNfa, Nfa::Parallel(parallel_nfa)));
            } else {
                throw std::invalid_argument("Unimplemented operation action.");
            }

        } else {
            solver.push(rd);
        }
        cout << rd->ToString() << endl;
    }
    cout << "Solver size: " << solver.size() << endl; // Must be 1 object.
    cout << "Top Type: " << solver.top()->type << endl; // 0 is Nfa.
    return solver.top()->GetNfa();
}