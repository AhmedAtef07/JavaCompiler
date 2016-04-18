//
// Created by Ahmed Barakat on 107 / 16 / 16.
//

#ifndef JAVACOMPILER_DFA_H
#define JAVACOMPILER_DFA_H


#include "Nfa.h"
#include "Token.h"

class Dfa {

public:

    struct table_state {
        int next_state;
        bool is_acceptance;
    };

    State *start_state, *minimized_start_state;

    Token *token;
    int current_state;
    int states_count;
    int minimized_states_count;
    table_state** table;
    table_state** minimized_table;

    Dfa(Nfa *nfa, Token *token);
    void initialize_current_state();
    Token* go_to(string input);
    bool has_next_state(string input);
    string ToString(bool minimized);

private:

    State* construct_dfa(Nfa *nfa);
    vector<State *> states_vector;
    void print_transitions(State *state, bool *v);
    void print_table(table_state **table, int rows);

    vector<int> get_ids_from_states(set<State *> states);
    string get_sorted_ids_as_string(vector<int> ids);
    set<State *> get_closure_states(set<State *> input_states);
    set<State *> get_next_states(set<State *> inputState, string inputCharacter);
    bool contains_accepted(set<State *> states);
    int find_alphabet_index(string s);
    int find_state_index(State *s, vector<State *> states);

    table_state** construct_table();
    table_state** minimize_table();

};


#endif //JAVACOMPILER_DFA_H
