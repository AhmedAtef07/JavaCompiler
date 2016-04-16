#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include "Nfa.h"
#include "RegularExpression.h"
#include "RegularDefinition.h"

using namespace std;

struct table_state {
    int next_state;
    bool is_acceptence;
};

void test_nfa() {
    string test = "(a*(k|l|(mn|k))*l)+";
//    test = "([a-zA-z]*(k|l|(mn|k))*l)+";
    cout << test << endl;
    cout << endl << endl;

    Nfa *nfa0 = new Nfa("a");
    Nfa *nfa1 = new Nfa("b");

    Nfa *nfa01 = Nfa::Concatenate(nfa1, nfa0);

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
    RegularDefinition *rd1 = new RegularDefinition(RegularDefinition::Type::kNfa, new Nfa(o1));
    string operation = string(1, '*');
    RegularDefinition *rd2 = new RegularDefinition(RegularDefinition::Type::kOperation, &operation);

//    cout << *static_cast<std::string*>(rd2->value) << endl;
//    cout << static_cast<Nfa*>(rd1->value)->start_state->outgoing_transitions[0]->value << endl;

    cout << rd1->ToString() << endl;
}

void test_regular_definition_array() {
    string test = "(a*(k|l|(mn|k))*l)+";
    vector<RegularDefinition *> regular_definition_vector;
    for(int i = 0; i < test.size(); ++i) {
        std::string *pstr = new std::string;
        *pstr = test[i];

        if(RegularDefinition::IsOperation(test[i])) {
            regular_definition_vector.push_back(new RegularDefinition(RegularDefinition::Type::kOperation,
                                                                      pstr));
        } else {
            regular_definition_vector.push_back(new RegularDefinition(RegularDefinition::Type::kNfa, new Nfa(*pstr)));
        }
    }


    for(RegularDefinition *rd: regular_definition_vector) {
        cout << rd->ToString() << endl;
    }
}


void test_lex_to_re() {
    RegularExpression *re = new RegularExpression(
            "/home/ramytamer/kolia/plt/project/phase-1/JavaCompiler/src/lexical_input.txt");


    /*for (set<string>::iterator i = re->keywords.begin(); i != re->keywords.end(); i++) {
        string element = *i;
        cout << "element: " << element << endl;
    }*/

    /*cout << "\nDefinetions:" << endl;
    for(map<string, string>::const_iterator it = re->regular_definetions.begin(); it != re->regular_definetions.end(); ++it)
    {
        cout << "'" << it->first << "'" << setw(20) << "'" << it->second << "'" << endl;
    }

    cout << "\nEXPRESSIONS:" << endl;
    for(map<string, string>::const_iterator it = re->regular_expressions.begin(); it != re->regular_expressions.end(); ++it)
    {
        cout << "'" << it->first << "'" << setw(20) << "'" << it->second << "'" << endl;
    }*/

    cout << "\n\nTESTING:" << endl;
    cout << "\nRegular Definetions:" << endl;
    cout << setw(35) << "isset letter:" << setw(35) << (re->regular_definetions.count("letter") ? "TRUE" : "FALSE") <<
    endl;
    cout << setw(35) << "isset digit:" << setw(35) << (re->regular_definetions.count("digit") ? "TRUE" : "FALSE") <<
    endl;
    cout << setw(35) << "isset digits:" << setw(35) << (re->regular_definetions.count("digits") ? "TRUE" : "FALSE") <<
    endl;
    cout << setw(35) << "isset equals:" << setw(35) << (re->regular_definetions.count("equals") ? "TRUE" : "FALSE") <<
    endl;
    cout << setw(35) << "isset notequals:" << setw(35) <<
    (re->regular_definetions.count("notequals") ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "isset larger:" << setw(35) << (re->regular_definetions.count("larger") ? "TRUE" : "FALSE") <<
    endl;
    cout << setw(35) << "isset smaller:" << setw(35) << (re->regular_definetions.count("smaller") ? "TRUE" : "FALSE") <<
    endl;

    cout << endl;
    cout << setw(35) << "Assert Definetions of letter:" << setw(35) << (re->regular_definetions.at("letter") ==
                                                                        "(a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z)|(A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z)"
                                                                        ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "Assert Definetions of digits:" << setw(35) << (re->regular_definetions.at("digit")
                                                                        == "(0|1|2|3|4|5|6|7|8|9)" ? "TRUE"
                                                                                                   : "FALSE") << endl;
    cout << setw(35) << "Assert Definetions of digits:" << setw(35) << (re->regular_definetions.at("digits")
                                                                        == "((0|1|2|3|4|5|6|7|8|9))+" ? "TRUE"
                                                                                                      : "FALSE") <<
    endl;
    cout << setw(35) << "Assert Definetions of equals:" << setw(35) << (re->regular_definetions.at("equals")
                                                                        == "\\=\\=" ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "Assert Definetions of notequals:" << setw(35) << (re->regular_definetions.at("notequals")
                                                                           == "!\\=" ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "Assert Definetions of larger:" << setw(35) << (re->regular_definetions.at("larger")
                                                                        == ">|>\\=" ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "Assert Definetions of smaller:" << setw(35) << (re->regular_definetions.at("smaller")
                                                                         == "<|<\\=" ? "TRUE" : "FALSE") << endl;

    cout << "\nRegular Expressions:" << endl;
    cout << setw(35) << "isset num: " << setw(35) << (re->regular_expressions.count("num") ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "isset id: " << setw(35) << (re->regular_expressions.count("id") ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "isset relop: " << setw(35) << (re->regular_expressions.count("relop") ? "TRUE" : "FALSE") <<
    endl;
    cout << setw(35) << "isset assign: " << setw(35) << (re->regular_expressions.count("assign") ? "TRUE" : "FALSE") <<
    endl;
    cout << setw(35) << "isset addop: " << setw(35) << (re->regular_expressions.count("addop") ? "TRUE" : "FALSE") <<
    endl;
    cout << setw(35) << "isset mulop: " << setw(35) << (re->regular_expressions.count("mulop") ? "TRUE" : "FALSE") <<
    endl;

    cout << endl;

    cout << setw(35) << "Assert Expression of num: " << setw(35) << (re->regular_expressions.at("num")
                                                                     ==
                                                                     "((0|1|2|3|4|5|6|7|8|9))+|((0|1|2|3|4|5|6|7|8|9))+.(((0|1|2|3|4|5|6|7|8|9))+)(\\L|E(((0|1|2|3|4|5|6|7|8|9))+))"
                                                                     ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "Assert Expression of id: " << setw(35) << (re->regular_expressions.at("id")
                                                                    ==
                                                                    "(((a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z)|(A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z))|_"
                                                                            "|$)(((a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z)|(A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z))"
                                                                            "|((0|1|2|3|4|5|6|7|8|9))|_|$)*" ? "TRUE"
                                                                                                             : "FALSE") <<
    endl;
    cout << setw(35) << "Assert Expression of relop: " << setw(35) <<
    (re->regular_expressions.at("relop") == "(\\=\\=)|(!\\=)|(>|>\\=)|(<|<\\=)" ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "Assert Expression of assign: " << setw(35) <<
    (re->regular_expressions.at("assign") == "\\=" ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "Assert Expression of addop: " << setw(35) <<
    (re->regular_expressions.at("addop") == "\\+|\\-" ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "Assert Expression of mulop: " << setw(35) <<
    (re->regular_expressions.at("mulop") == "\\*|/" ? "TRUE" : "FALSE") << endl;

    cout << endl;
    cout << "\nKeywords:" << endl;
    cout << setw(35) << "Assert Keywords size(49): " << setw(35) << (re->keywords.size() == 49 ? "TRUE" : "FALSE") <<
    endl;


    cout << endl;
    cout << "\nPuncituations:" << endl;
    cout << setw(35) << "Assert Puncituations size(6): " << setw(35) <<
    (re->punctuations.size() == 6 ? "TRUE" : "FALSE") << endl;

}

void print_transitions(State *state, bool *v) {
    if(v[state->id]) return;
    cout << "--------------" << endl;
    if(state->is_acceptence)
        cout << "0";
    cout << state->id << endl;
    for(Transition *s : state->outgoing_transitions) {
        cout << "->" + s->value + "| " << s->next_state->id << endl;
    }
    v[state->id] = true;
    for(Transition *s : state->outgoing_transitions) {
        print_transitions(s->next_state, v);
    }
}

string sorted(vector<int> ids) {
    sort(ids.begin(), ids.end());
    string ret = "";
    for(int i : ids) ret += "" + to_string(i) + ",";
    return ret;
}

vector<int> get_ids(set<State *> states) {
    vector<int> v;
    for(State *s : states) v.push_back(s->id);
    return v;
}

set<State *> get_neighbors(State *s, bool *v) {
    set<State *> ret;
    ret.insert(s);
    for(Transition *t : s->outgoing_transitions) {
        if(!v[t->next_state->id]) {
            ret.insert(t->next_state);
            v[t->next_state->id] = true;
            set<State *> n = get_neighbors(t->next_state, v);
            ret.insert(begin(n), end(n));
        }
    }
    return ret;
}

set<State *> get_states(Nfa *n, bool *v) {
    return get_neighbors(n->start_state, v);
}

set<State *> Closure(set<State *> input_states) {
    set<State *> output;
    output.insert(begin(input_states), end(input_states));
    set<State *> n;
    for(State *s : input_states) {
        for(Transition *t : s->outgoing_transitions) {
            if(t->value == "") {
                output.insert(t->next_state);
                n.insert(t->next_state);
            }
        }
    }
    if(!n.empty()) {
        set<State *> n_closure = Closure(n);
        output.insert(begin(n_closure), end(n_closure));
    }
    return output;
}

set<State *> Goto(set<State *> inputState, string inputCharacter) {
    set<State *> output;
    for(State *s : inputState) {
        for(Transition *t : s->outgoing_transitions) {
            if(t->value == inputCharacter) {
                output.insert(t->next_state);
            }
        }
    }
    return Closure(output);
}

void test_DFA1() {
    Nfa *nfa_a = new Nfa("a");
    Nfa *nfa_b = new Nfa("b");

    Nfa *nfa_ab = Nfa::Parallel(nfa_a, nfa_b);
    Nfa *nfa_abab = Nfa::Plus(nfa_ab);
    Nfa *nfa_b2 = new Nfa("b");
    Nfa *nfa_ababb = Nfa::Concatenate(nfa_abab, nfa_b2);
    Nfa *nfa_c = new Nfa("c");
    Nfa *nfa_d = new Nfa("d");
    Nfa *nfa_ababbc = Nfa::Concatenate(nfa_ababb, nfa_c);
    Nfa *nfa_ababbcd = Nfa::Concatenate(nfa_ababbc, nfa_d);
    bool visited[13];
//    for (int i = 0; i < 13; ++i) visited[i] = false;
    fill(visited, visited + sizeof(visited), false);

//    cout << "T: " << nfa_ababbcd->terminal_state->id << endl;
//    for (int i = 0; i < 13; ++i) visited[i] = false;
//    print_transitions(nfa_ababbcd->start_state, visited);
//    for (int i = 0; i < 13; ++i) visited[i] = false;

//    set<State*> all_states = get_states(nfa_ababbcd, visited);
//    for(State *s : all_states) {
//        cout << s->id << endl;
//    }

//    set<State*> n;
//    n.insert(nfa_ababbcd->start_state);
//    n.insert(nfa_ababbcd->start_state->outgoing_transitions[0]->next_state);
//    n.insert(nfa_ababbcd->start_state->outgoing_transitions[0]->next_state->outgoing_transitions[0]->next_state);
//    set<State*> closure = Closure(n);
//    cout << "S " << closure.size() << endl;
//    for(State *s : closure) {
//        cout << s->id << endl;
//    }

//    set<State*> n;
//    n.insert(nfa_ababbcd->start_state);
//    n.insert(nfa_ababbcd->start_state->outgoing_transitions[0]->next_state);
//    n.insert(nfa_ababbcd->start_state->outgoing_transitions[0]->next_state->outgoing_transitions[0]->next_state);

//    vector<State*> all_states = get_states(nfa_ababbcd, visited);
//    for(State* ss : all_states) {
//        if(ss->id == 8) {
//            n.insert(ss);
//            set<State *> next = Goto(Closure(n), "b");
//            cout << "S " << next.size() << endl;
//            for (State *s : next) {
//                cout << s->id << endl;
//            }
//        }
//    }
//    State *a = new State();
//    State *b = new State();
//    a->AddTransition(new Transition(b, "a"));
//    Nfa *sss = new Nfa(a, b);
//    set<State*> all_states = get_states(sss, visited);
//    for(State *s : all_states) {
//        cout << s->id << endl;
//    }
}

bool contais_accepted(set<State *> states) {
    for(State *s : states) {
        if(s->is_acceptence) return true;
    }
    return false;
}

static string alphapet[4] = {"a", "b", "c", "d"};
static int alphapet_size = 4;

int find_alphapet_index(string s) {
    int index = 0;
    while(index < alphapet_size && alphapet[index] != s) ++index;
    return index == alphapet_size ? -1 : index;
}

int find_state_index(State *s, vector<State *> states) {
    vector<State *>::iterator it;
    it = find(states.begin(), states.end(), s);
    return it == states.end() ? -1 : distance(states.begin(), it);
}


table_state **construct_table(vector<State *> states) {
    int states_size = states.size();
    table_state **table = (table_state **) malloc(states_size * sizeof(table_state));
    for(int i = 0; i < states_size; ++i) {
        table[i] = (table_state *) malloc(alphapet_size * sizeof(table_state));
    }
    bool set_table[states_size][alphapet_size];
    for(int i = 0; i < states_size * alphapet_size; ++i) {
        set_table[i / alphapet_size][i % alphapet_size] = false;
    }

    for(State *s : states) {
        int state_index = find_state_index(s, states);
        for(Transition *t : s->outgoing_transitions) {
            table_state *temp = (table_state *) malloc(sizeof(table_state));
            temp->next_state = find_state_index(t->next_state, states);
            temp->is_acceptence = t->next_state->is_acceptence;
//            cout << t->next_state->id << " " << t->next_state->is_acceptence << endl;
            int alphabet_index = find_alphapet_index(t->value);
            table[state_index][alphabet_index] = *temp;
            set_table[state_index][alphabet_index] = true;
        }
    }

    for(int i = 0; i < states_size * alphapet_size; ++i) {
        if(!set_table[i / alphapet_size][i % alphapet_size]) {
            table_state *temp = (table_state *) malloc(sizeof(table_state));
            temp->next_state = -1;
            temp->is_acceptence = false;
            table[i / alphapet_size][i % alphapet_size] = *temp;
        }
    }
    return table;
}

table_state **minimize_table(vector<State *> states, table_state **table) {

    int states_size = states.size();
    bool acceptence_states[states_size];
    for(int i = 0; i < states_size; ++i) acceptence_states[i] = false;
    for(State *s : states) {
        if(s->is_acceptence) {
            acceptence_states[find_state_index(s, states)] = true;
//            cout << find_state_index(s, states) << endl;
        }
    }
    bool minimization_table[states_size][states_size];
    for(int i = 0; i < states_size * states_size; ++i) minimization_table[i / states_size][i % states_size] = true;

    for(int i = 0; i < states_size; ++i) {
        for(int j = 0; j < states_size; ++j) {
            if(j >= i) break;
            if(acceptence_states[i] != acceptence_states[j]) {
                minimization_table[i][j] = false;
            }
        }
    }

    bool changed = true;
    while(changed) {
        changed = false;
        for(int i = 0; i < states_size; ++i) {
            for(int j = 0; j < states_size; ++j) {
                if(j >= i) break;
                if(!minimization_table[i][j]) continue;
                for(int k = 0; k < alphapet_size; ++k) {
                    int a = table[i][k].next_state, b = table[j][k].next_state;
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

//    minimization_table[3][0] = true;

    cout << endl;
    for(int i = 0; i < states_size; ++i) {
        cout << i << "| ";
        for(int j = 0; j < states_size; ++j) {
            if(j >= i) break;
            cout << minimization_table[i][j] << " | ";
        }
        cout << endl;
    }
    cout << endl << " | ";
    for(int i = 0; i < states_size; ++i) {
        cout << i << " | ";
    }
    cout << endl;

    vector<vector<int>> minimized_states;
    int to_remove = 0, new_start_ind = -1;
    changed = true;
    while(changed) {
        changed = false;
        for(int i = 0; i < states_size; ++i) {
            for(int j = 0; j < states_size; ++j) {
                if(j >= i) break;
                if(!minimization_table[i][j]) continue;
                vector<int> v, temp;
                v.push_back(i);
                temp.push_back(i);
                v.push_back(j);
                temp.push_back(j);
                if(i == 0 || j == 0) new_start_ind = minimized_states.size();
                ++to_remove;
                minimization_table[i][j] = false;
                while(!temp.empty()) {
                    int in = temp[0];
                    temp.erase(temp.begin());
                    for(int k = 0; k < states_size; ++k) {
                        if(k >= in) break;
                        if(minimization_table[in][k]) {
                            v.push_back(k);
                            temp.push_back(k);
                            if(k == 0) new_start_ind = minimized_states.size();
                            minimization_table[in][k] = false;
                            changed = true;
                            ++to_remove;
                        };
                    }
                    for(int k = states_size - 1; k >= 0; --k) {
                        if(in >= k) break;
                        if(minimization_table[k][in]) {
                            v.push_back(k);
                            temp.push_back(k);
                            if(k == 0) new_start_ind = minimized_states.size();
                            minimization_table[k][in] = false;
                            changed = true;
                            ++to_remove;
                        };
                    }
                }
                minimized_states.push_back(v);
            }
        }
    }

    int new_states = minimized_states.size(), curr = 0, new_size = states_size - to_remove;
    cout << endl << "to remove: " << to_remove << "  " << "new: " << new_states << " | " << new_start_ind << endl <<
    endl;
//    for(vector<int> v : minimized_states) {
//        for(int i : v) {
//            cout << i << "  " << endl;
//        }
//        cout << endl;
//    }

    vector<int> new_mapping(states_size, -1);

    if(new_start_ind != -1) {
        for(int in : minimized_states[new_start_ind]) {
            new_mapping[in] = curr;
        }
        ++curr;
        minimized_states.erase(minimized_states.begin() + new_start_ind);
    }
    int last = new_size - 1;
    for(vector<int> v : minimized_states) {
        for(int in : v) {
            new_mapping[in] = last;
        }
        --last;
    }

    for(int i = 0; i < states_size; ++i) {
        if(new_mapping[i] == -1) new_mapping[i] = curr++;
    }

    table_state **minimized_table = (table_state **) malloc(new_size * sizeof(table_state));
    for(int i = 0; i < new_size; ++i) {
        minimized_table[i] = (table_state *) malloc(alphapet_size * sizeof(table_state));
    }

    for(int i = 0; i < states_size; ++i) {
        for(int j = 0; j < alphapet_size; ++j) {
            table_state *temp = (table_state *) malloc(sizeof(table_state));
            temp->next_state = -1;
            temp->is_acceptence = false;
            if(table[i][j].next_state != -1) {
                temp->next_state = new_mapping[table[i][j].next_state];
            }
            if(table[i][j].is_acceptence) {
                temp->is_acceptence = true;
            }
            minimized_table[new_mapping[i]][j] = *temp;
        }
    }

    return minimized_table;
}

Nfa *construct_Dfa(Nfa *nfa) {
    map<string, State *> states_map;
    map<string, set<State *>> set_map;
    map<string, bool> bool_map;

    int states_size = 0;
    vector<State *> states_vector;
    set<State *> s;
    State *new_start;
    s.insert(nfa->start_state);
    string key = sorted(get_ids(Closure(s)));
    states_map[key] = new State();
    ++states_size;
    states_vector.push_back(states_map[key]);
    new_start = states_map[key];
    set_map[key] = Closure(s);
    bool_map[key] = false;


    bool added_new = true;
    while(added_new) {
        added_new = false;
        for(map<string, bool>::iterator iterator = bool_map.begin(); iterator != bool_map.end(); iterator++) {
            if(!iterator->second) {
                for(string input : alphapet) {
                    set<State *> next_set = Goto(set_map[iterator->first], input);
                    string new_state = sorted(get_ids(next_set));
                    if(new_state == "") continue;
                    if(states_map.find(new_state) != states_map.end()) {
                        states_map[iterator->first]->AddTransition(new Transition(states_map[new_state], input));
                    } else {
                        states_map[new_state] = new State();
                        ++states_size;
                        states_vector.push_back(states_map[new_state]);
//                        if(contais_accepted(next_set) || states_map[new_state]->id == 19) { // to be fixed
//                        if(contais_accepted(next_set) || states_map[new_state]->id == 17 || states_map[new_state]->id == 18) { // to be fixed
//                        if(contais_accepted(next_set) || states_map[new_state]->id == 16 ||
//                           states_map[new_state]->id == 17) { // to be fixed
                        if(contais_accepted(next_set)) {
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

    bool visited[50];
//    for (int i = 0; i < 50; ++i) visited[i] = false;
    cout << endl << "DFA" << endl;
    fill(visited, visited + sizeof(visited), false);
    print_transitions(new_start, visited);
    cout << endl;

//    cout << endl;
//    for(map<string, bool>::iterator iterator = bool_map.begin(); iterator != bool_map.end(); iterator++) {
//        cout << iterator->first <<  "||" << iterator->second << endl;
//    }
//    cout << endl;
//    for(map<string, State*>::iterator iterator = states_map.begin(); iterator != states_map.end(); iterator++) {
//        cout << iterator->first <<  "||" << iterator->second->id << endl;
//    }

    cout << endl << "new states nums" << endl;
    for(State *s : states_vector) cout << s->id << " ";
    cout << endl;


    table_state **table = construct_table(states_vector);
    cout << endl << "Table" << endl << "S | ";
    for(int i = 0; i < alphapet_size; ++i) {
        cout << alphapet[i] << " | ";
    }
    cout << endl;
    for(int j = 0; j < states_size; ++j) {
        cout << j << " | ";
        for(int i = 0; i < alphapet_size; ++i) {
            if(table[j][i].next_state != -1 && table[j][i].is_acceptence) {
                cout << "0" << table[j][i].next_state << " | ";
            }
            else if(table[j][i].next_state != -1) {
                cout << table[j][i].next_state << " | ";
            }
            else {
                cout << "  | ";
            }
        }
        cout << endl;
    }


    table_state **minimized_table = minimize_table(states_vector, table);

    cout << endl << "Min Table" << endl << "S | ";
    for(int i = 0; i < alphapet_size; ++i) {
        cout << alphapet[i] << " | ";
    }
    cout << endl;
    for(int j = 0; j < states_size; ++j) {
        cout << j << " | ";
        for(int i = 0; i < alphapet_size; ++i) {
            if(minimized_table[j][i].next_state != -1 && minimized_table[j][i].is_acceptence) {
                cout << "0" << minimized_table[j][i].next_state << " | ";
            }
            else if(minimized_table[j][i].next_state != -1) {
                cout << minimized_table[j][i].next_state << " | ";
            }
            else {
                cout << "  | ";
            }
        }
        cout << endl;
    }

}


void test_DFA2() {

////    "(a|b)+bcd"
//    Nfa *nfa_a = new Nfa("a");
//    Nfa *nfa_b = new Nfa("b");
//    Nfa *nfa_b2 = new Nfa("b");
//    Nfa *nfa_c = new Nfa("c");
//    Nfa *nfa_d = new Nfa("d");
//
//    Nfa *nfa_ab = Nfa::Parallel(nfa_a, nfa_b);
//    Nfa *nfa_abab = Nfa::Plus(nfa_ab);
//    Nfa *nfa_ababb = Nfa::Concatenate(nfa_abab, nfa_b2);
//    Nfa *nfa_ababbc = Nfa::Concatenate(nfa_ababb, nfa_c);
//    Nfa *nfa_ababbcd = Nfa::Concatenate(nfa_ababbc, nfa_d);
//    bool visited[50];
//    fill(visited, visited + sizeof(visited), false);
//    cout << endl << "NFA" << endl;
//    print_transitions(nfa_ababbcd->start_state, visited);
//    cout << endl;
//    construct_Dfa(nfa_ababbcd);


////    "ab|a+b+"
//    Nfa *nfa_a = new Nfa("a");
//    Nfa *nfa_b = new Nfa("b");
//    Nfa *nfa_a1 = new Nfa("a");
//    Nfa *nfa_b1 = new Nfa("b");
//
//    Nfa *nfa_ab = Nfa::Concatenate(nfa_a, nfa_b);
//    Nfa *nfa_aa = Nfa::Plus(nfa_a1);
//    Nfa *nfa_bb = Nfa::Plus(nfa_b1);
//    Nfa *nfa_aabb = Nfa::Concatenate(nfa_aa, nfa_bb);
//    Nfa *nfa_abaabb = Nfa::Parallel(nfa_ab, nfa_aabb);
//    bool visited[50];
//    fill(visited, visited + sizeof(visited), false);
//    cout << endl << "NFA" << endl;
//    print_transitions(nfa_abaabb->start_state, visited);
//    cout << endl;
//    construct_Dfa(nfa_abaabb);

//
////    "b+|a+b+"
//    Nfa *nfa_a = new Nfa("a");
//    Nfa *nfa_b = new Nfa("b");
//    Nfa *nfa_b1 = new Nfa("b");
//
//    Nfa *nfa_aa = Nfa::Plus(nfa_a);
//    Nfa *nfa_bb = Nfa::Plus(nfa_b);
//    Nfa *nfa_bb1 = Nfa::Plus(nfa_b1);
//    Nfa *nfa_aabb = Nfa::Concatenate(nfa_aa, nfa_bb);
//    Nfa *nfa_abaabb = Nfa::Parallel(nfa_bb1, nfa_aabb);
//    bool visited[50];
//    fill(visited, visited + sizeof(visited), false);
//    cout << endl << "NFA" << endl;
//    print_transitions(nfa_abaabb->start_state, visited);
//    cout << endl;
//    construct_Dfa(nfa_abaabb);


//    set<State*> s;
//    s.insert(nfa_ababbcd->start_state);
//    cout << sorted(get_ids(Closure(s))) << endl;
//
//    map<string, State*> m;
//    m[sorted(get_ids(Closure(s)))] = new State();
//    m["123"] = new State();
//    cout << endl;
//    if (m.find("02") != m.end()) {
//        cout << m[sorted(get_ids(Closure(s)))]->id << endl;
//    } else {
//        cout << "Not" << endl;
//    }
//    cout << endl;
//    for(map<string, State*>::iterator iterator = m.begin(); iterator != m.end(); iterator++) {
//        cout << iterator->second->id << endl;
//    }
}


/*
 * 1. Eliminate all parentheses.
 * 2.
 */
int main() {

//    test_nfa();
//    test_regular_definition();
//    test_regular_definition_array();

//    test_lex_to_re();

//    test_DFA1();
    test_DFA2();

//    table_state *a = (table_state*)malloc(sizeof(table_state));
//    a->next_state = 1;
//    a->is_acceptence = true;
//    cout << a->is_acceptence << endl;

    return 0;
}



/*
 * TODO: Nfa, State, Transition classes;
 * TODO: operations on NFAs.
 */