#include <iostream>
#include <fstream>
#include "Nfa.h"
#include "RegularExpression.h"

#include <iomanip>

using namespace std;

/*
 * 1. Eliminate all parentheses.
 * 2.
 */
int main() {
    /*
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

     */

    RegularExpression * re = new RegularExpression("/home/ramy/kolia/plt/project/phase-1/JavaCompiler/src/lexical_input.txt");


    /*for (set<string>::iterator i = re->keywords.begin(); i != re->keywords.end(); i++) {
        string element = *i;
        cout << "element: " << element << endl;
    }*/

    cout << "\nDefinetions:" << endl;
    for(map<string, string>::const_iterator it = re->regular_definetions.begin(); it != re->regular_definetions.end(); ++it)
    {
        cout << "'" << it->first << "'" << setw(20) << "'" << it->second << "'" << endl;
    }

    cout << "\nEXPRESSIONS:" << endl;
    for(map<string, string>::const_iterator it = re->regular_expressions.begin(); it != re->regular_expressions.end(); ++it)
    {
        cout << "'" << it->first << "'" << setw(20) << "'" << it->second << "'" << endl;
    }
    return 0;
}



/*
 * TODO: Nfa, State, Transition classes;
 * TODO: operations on NFAs.
 */