#include <iostream>
#include "Nfa.h"
#include "RegularDefinition.h"

using namespace std;

void test_nfa() {
    string test = "(a*(k|l|(mn|k))*l)+";
//    test = "([a-zA-z]*(k|l|(mn|k))*l)+";
    cout << test << endl;
    cout << endl << endl;

    Nfa* nfa0 = new Nfa("a");
    Nfa* nfa1 = new Nfa("b");

    Nfa* nfa01 = Nfa::Concatenate(nfa1, nfa0);

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

}

void test_regular_definition() {
    string o1 = string("a");
    RegularDefinition* rd1 = new RegularDefinition(RegularDefinition::Type::kNfa, new Nfa(o1));
    string operation = string(1, '*');
    RegularDefinition* rd2 = new RegularDefinition(RegularDefinition::Type::kOperation, &operation);

//    cout << *static_cast<std::string*>(rd2->value) << endl;
//    cout << static_cast<Nfa*>(rd1->value)->start_state->outgoing_transitions[0]->value << endl;

    cout << rd1->ToString() << endl;
}

void test_regular_definition_array() {
    string test = "(a*(k|l|(mn|k))*l)+";
    vector<RegularDefinition*> regular_definition_vector;
    for(int i = 0; i < test.size(); ++i) {
        string current_char = string(1, test[i]);
        cout << current_char << endl;

        if(RegularDefinition::IsOperation(test[i])) {
            regular_definition_vector.push_back(new RegularDefinition(RegularDefinition::Type::kOperation,
                                                                      &current_char));
        } else {
            regular_definition_vector.push_back(new RegularDefinition(RegularDefinition::Type::kNfa,
                                                                      new Nfa(current_char)));
        }
    }


    for(RegularDefinition* rd: regular_definition_vector) {
        cout << rd->ToString() << endl;
        cout << "HERERERERER" << endl;
        break;
    }
}

/*
 * 1. Eliminate all parentheses.
 * 2.
 */
int main() {

//    test_nfa();
    test_regular_definition();
//    test_regular_definition_array();
    return 0;
}



/*
 * TODO: Nfa, State, Transition classes;
 * TODO: operations on NFAs.
 */