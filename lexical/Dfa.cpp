//
// Created by Ahmed Barakat on 107 / 16 / 16.
//

#include "Dfa.h"
#include "Lexical.h"
#include <map>
#include <queue>
#include <algorithm>

Dfa::Dfa(Nfa *nfa, Token *token) {

    this->token = token;
    this->current_state = 0;
    this->start_state = construct_dfa(nfa);

    this->table = construct_table();
//    print_table(this->table, this->states_count);

    this->minimized_table = minimize_table();
//    print_table(minimized_table, this->minimized_states_count);

}

string Dfa::ToString(bool minimized) {
    set<State *> visited_states;
    queue<State *> bfs;
    if(minimized) {
        bfs.push(minimized_start_state);
        visited_states.insert(minimized_start_state);
    } else {
        bfs.push(start_state);
        visited_states.insert(start_state);
    }
    string result = "";

    while(!bfs.empty()) {
        State* front_state = bfs.front();
        bfs.pop();
        string outgoing_states;
        if(front_state->is_acceptence) {
            outgoing_states += "0";
        }
        outgoing_states += to_string(front_state->id) + ": ";
        for(Transition* transition: front_state->outgoing_transitions) {
            outgoing_states += "('" + transition->value + "', ";
            outgoing_states += to_string(transition->next_state->id) + ") ";
            if(visited_states.find(transition->next_state) == visited_states.end()) {
                bfs.push(transition->next_state);
                visited_states.insert(transition->next_state);
            }
        }
//        if(front_state->is_acceptence) outgoing_states += "\t[Accepted State]";
        outgoing_states += "\n";
        result += outgoing_states;
    }
    return result;
}

void Dfa::print_table(Dfa::table_state **table, int rows) {
    cout << endl << "Table" << endl << "S |  ";
    for(int i = 0; i < Lexical::alphabet.size(); ++i) {
        cout << Lexical::alphabet[i] << " |  ";
    }
    cout << endl;
    for(int j = 0; j < rows; ++j) {
        cout << j << " | ";
        for(int i = 0; i < Lexical::alphabet.size(); ++i) {
            if(table[j][i].next_state != -1 && table[j][i].is_acceptance) {
                cout << "0" << table[j][i].next_state << " | ";
            }
            else if(table[j][i].next_state != -1) {
                cout << " " << table[j][i].next_state << " | ";
            }
            else {
                cout << "   | ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

string Dfa::get_sorted_ids_as_string(vector<int> ids) {
    sort(ids.begin(), ids.end());
    string ret = "";
    for(int i : ids) ret += "" + to_string(i) + ",";
    return ret;
}

vector<int> Dfa::get_ids_from_states(set<State *> states) {
    vector<int> v;
    for(State *s : states) v.push_back(s->id);
    return v;
}

set<State *> Dfa::get_closure_states(set<State *> input_states) {
    set<State *> output;
    output.insert(input_states.begin(), input_states.end());
    set<int> visited;
    queue<State *> to_visit;
    for(State *s : output) to_visit.push(s);

    output.insert(input_states.begin(), input_states.end());

    while(!to_visit.empty()) {
        State *s = to_visit.front();
        to_visit.pop();
        visited.insert(s->id);
        for(Transition *t : s->outgoing_transitions) {
            if(t->value == "" && (visited.find(t->next_state->id) == visited.end())) {
                output.insert(t->next_state);
                to_visit.push(t->next_state);
            }
        }
    }

    return output;
}

set<State *> Dfa::get_next_states(set<State *> inputState, string inputCharacter) {
    set<State *> output;
    for(State *s : inputState) {
        for(Transition *t : s->outgoing_transitions) {
            if(t->value == inputCharacter) {
                output.insert(t->next_state);
            }
        }
    }
    return get_closure_states(output);
}

bool Dfa::contains_accepted(set<State *> states) {
    for(State *s : states) {
        if(s->is_acceptence) return true;
    }
    return false;
}

int Dfa::find_alphabet_index(string s) {
    int index = 0;
    while(index < Lexical::alphabet.size() && Lexical::alphabet[index] != s) ++index;
    return index == Lexical::alphabet.size() ? -1 : index;
}

int Dfa::find_state_index(State *s, vector<State *> states) {
    vector<State *>::iterator it;
    it = find(states.begin(), states.end(), s);
    return it == states.end() ? -1 : distance(states.begin(), it);
}

Dfa::table_state** Dfa::construct_table() {
    Dfa::table_state **table = (Dfa::table_state **) malloc(this->states_count * sizeof(Dfa::table_state));
    for(int i = 0; i < this->states_count; ++i) {
        table[i] = (Dfa::table_state *) malloc(Lexical::alphabet.size() * sizeof(Dfa::table_state));
    }

    bool is_set_cell_table[this->states_count][Lexical::alphabet.size()];
    for(int i = 0; i < this->states_count * Lexical::alphabet.size(); ++i) {
        is_set_cell_table[i / Lexical::alphabet.size()][i % Lexical::alphabet.size()] = false;
    }

    for(State *s : this->states_vector) {
        int state_index = find_state_index(s, this->states_vector);
        for(Transition *t : s->outgoing_transitions) {
            Dfa::table_state *temp = (Dfa::table_state *) malloc(sizeof(Dfa::table_state));
            temp->next_state = find_state_index(t->next_state, this->states_vector);
            temp->is_acceptance = t->next_state->is_acceptence;
            int alphabet_index = find_alphabet_index(t->value);
            table[state_index][alphabet_index] = *temp;
            is_set_cell_table[state_index][alphabet_index] = true;
        }
    }

    for(int i = 0; i < this->states_count * Lexical::alphabet.size(); ++i) {
        if(!is_set_cell_table[i / Lexical::alphabet.size()][i % Lexical::alphabet.size()]) {
            Dfa::table_state *temp = (Dfa::table_state *) malloc(sizeof(Dfa::table_state));
            temp->next_state = -1;
            temp->is_acceptance = false;
            table[i / Lexical::alphabet.size()][i % Lexical::alphabet.size()] = *temp;
        }
    }
    return table;
}

Dfa::table_state** Dfa::minimize_table() {
    vector<bool> acceptence_states(this->states_count, false);

    for(State *s : this->states_vector) {
        if(s->is_acceptence) {
            acceptence_states[find_state_index(s, this->states_vector)] = true;
        }
    }

    bool minimization_table[this->states_count][this->states_count];
    for(int i = 0; i < this->states_count * this->states_count; ++i) {
        minimization_table[i / this->states_count][i % this->states_count] = true;
    }

    for(int i = 0; i < this->states_count; ++i) {
        for(int j = 0; j < this->states_count; ++j) {
            if(j >= i) break;
            if(acceptence_states[i] != acceptence_states[j]) {
                minimization_table[i][j] = false;
            }
        }
    }

    bool changed = true;
    while(changed) {
        changed = false;
        for(int i = 0; i < this->states_count; ++i) {
            for(int j = 0; j < this->states_count; ++j) {
                if(j >= i) break;
                if(!minimization_table[i][j]) continue;
                for(int k = 0; k < Lexical::alphabet.size(); ++k) {
                    int a = this->table[i][k].next_state, b = this->table[j][k].next_state;
                    if((a == -1 || b == -1) && a != b) {
                        minimization_table[i][j] = false;
                        changed = true;
                    }
                    else if(a != -1 && b != -1 && !minimization_table[a][b]) {
                        minimization_table[i][j] = false;
                        changed = true;
                    }
                }
            }
        }
    }

    vector<set<int>> to_be_minimized_states_ids;
    int new_start_ind = -1;
    changed = true;
    while(changed) {
        changed = false;
        for(int i = 0; i < this->states_count; ++i) {
            for(int j = 0; j < this->states_count; ++j) {
                if(j >= i) break;
                if(!minimization_table[i][j]) continue;
                vector<int> temp;
                set<int> v;
                v.insert(i);
                temp.push_back(i);
                v.insert(j);
                temp.push_back(j);
                if(i == 0 || j == 0) new_start_ind = to_be_minimized_states_ids.size();
                minimization_table[i][j] = false;
                while(!temp.empty()) {
                    int in = temp[0];
                    temp.erase(temp.begin());
                    for(int k = 0; k < this->states_count; ++k) {
                        if(k >= in) break;
                        if(minimization_table[in][k]) {
                            v.insert(k);
                            temp.push_back(k);
                            if(k == 0) new_start_ind = to_be_minimized_states_ids.size();
                            minimization_table[in][k] = false;
                            changed = true;
                        };
                    }
                    for(int k = this->states_count - 1; k >= 0; --k) {
                        if(in >= k) break;
                        if(minimization_table[k][in]) {
                            v.insert(k);
                            temp.push_back(k);
                            if(k == 0) new_start_ind = to_be_minimized_states_ids.size();
                            minimization_table[k][in] = false;
                            changed = true;
                        };
                    }
                }
                to_be_minimized_states_ids.push_back(v);
            }
        }
    }

    int to_remove = 0;
    for(set<int> v : to_be_minimized_states_ids) {
        to_remove += v.size() - 1;
    }

    int curr = 0, new_size = this->states_count - to_remove;
    this->minimized_states_count = new_size;


    vector<int> new_mapping(this->states_count, -1);

    if(new_start_ind != -1) {
        for(int in : to_be_minimized_states_ids[new_start_ind]) {
            new_mapping[in] = curr;
        }
        ++curr;
        to_be_minimized_states_ids.erase(to_be_minimized_states_ids.begin() + new_start_ind);
    }

    int last = new_size - 1;
    for(set<int> v : to_be_minimized_states_ids) {
        for(int in : v) {
            new_mapping[in] = last;
        }
        --last;
    }

    for(int i = 0; i < this->states_count; ++i) {
        if(new_mapping[i] == -1) new_mapping[i] = curr++;
    }


    Dfa::table_state **minimized_table = (Dfa::table_state **) malloc(new_size * sizeof(Dfa::table_state));
    for(int i = 0; i < new_size; ++i) {
        minimized_table[i] = (Dfa::table_state *) malloc(Lexical::alphabet.size() * sizeof(Dfa::table_state));
    }

    for(int i = 0; i < this->states_count; ++i) {
        for(int j = 0; j < Lexical::alphabet.size(); ++j) {
            Dfa::table_state *temp = (Dfa::table_state *) malloc(sizeof(Dfa::table_state));
            temp->next_state = -1;
            temp->is_acceptance = false;
            if(table[i][j].next_state != -1) {
                temp->next_state = new_mapping[table[i][j].next_state];
            }
            if(table[i][j].is_acceptance) {
                temp->is_acceptance = true;
            }
            int new_togo = new_mapping[i];
            minimized_table[new_togo][j] = *temp;
        }
    }

    State **minimized_states = (State **) malloc(new_size * sizeof(State));
    for(int i = 0; i < new_size; ++i) {
        minimized_states[i] = new State();
    }

    for(int i = 0; i < this->minimized_states_count; ++i) {
        for(int j = 0; j < Lexical::alphabet.size(); ++j) {
            if(minimized_table[i][j].next_state != -1) {
                int to_go_to = minimized_table[i][j].next_state;
                int is_accepted = minimized_table[i][j].is_acceptance;
                minimized_states[i]->AddTransition(new Transition(minimized_states[to_go_to], Lexical::alphabet[j]));
                if(is_accepted) {
                    minimized_states[to_go_to]->is_acceptence = true;
                }
            }
        }
    }

    this->minimized_start_state = minimized_states[0];

    return minimized_table;
}

State* Dfa::construct_dfa(Nfa *nfa) {
    map<string, State *> states_map;
    map<string, set<State *>> set_map;
    map<string, bool> bool_map;

    this->states_count = 0;
    vector<State *> states_vector;
    set<State *> s;
    State *new_start_state;
    s.insert(nfa->start_state);
    string key = Dfa::get_sorted_ids_as_string(get_ids_from_states(get_closure_states(s)));
    states_map[key] = new State();
    ++this->states_count;
    states_vector.push_back(states_map[key]);
    new_start_state = states_map[key];
    set_map[key] = get_closure_states(s);
    bool_map[key] = false;

    bool added_new = true;
    while(added_new) {
        added_new = false;
        for(map<string, bool>::iterator iterator = bool_map.begin(); iterator != bool_map.end(); iterator++) {
            if(!iterator->second) {
                for(string input : Lexical::alphabet) {
                    set<State *> next_set = get_next_states(set_map[iterator->first], input);
                    string new_state = get_sorted_ids_as_string(get_ids_from_states(next_set));
                    if(new_state == "") continue;
                    if(states_map.find(new_state) != states_map.end()) {
                        states_map[iterator->first]->AddTransition(new Transition(states_map[new_state], input));
                    } else {
                        states_map[new_state] = new State();
                        ++this->states_count;
                        states_vector.push_back(states_map[new_state]);
                        if(contains_accepted(next_set)) {
                            states_map[new_state]->is_acceptence = true;
                        }
                        set_map[new_state] = next_set;
                        bool_map[new_state] = false;
                        added_new = true;
                        states_map[iterator->first]->AddTransition(new Transition(states_map[new_state], input));
                    }
                }
                bool_map[iterator->first] = true;
            }
        }
    }

    this->states_vector = states_vector;

    return new_start_state;
}

void Dfa::initialize_current_state() {
    this->current_state = 0;
}

Token* Dfa::go_to(string input) {
    if(has_next_state(input)) {
        table_state temp = this->minimized_table[this->current_state][find_alphabet_index(input)];
        this->current_state = temp.next_state;
        if(temp.is_acceptance) {
            return this->token;
        }
    }
    return nullptr;
}

bool Dfa::has_next_state(string input) {
    return this->minimized_table[this->current_state][find_alphabet_index(input)].next_state != -1;
}

