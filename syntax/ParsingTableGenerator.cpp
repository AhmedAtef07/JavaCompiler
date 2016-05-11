//
// Created by Ahmed Barakat on 123 / 2 / 16.
//

#include "ParsingTableGenerator.h"

ParsingTableGenerator::ParsingTableGenerator(vector<GrammarRule *> rules) {
    this->rules = rules;
    this->firsts = calculate_firsts();
    this->follows = calculate_follows();
    generate_indexes();
    generate_table();
}

bool ParsingTableGenerator::contains_lambda(GrammarRule *rule) {
    for(vector<Symbol*> &v : rule->productions) {
        bool is_all_lambda = true;
        for(Symbol *symbol : v) {
            if(symbol->name != "\\L") {
                is_all_lambda = false;
            }
        }
        if(is_all_lambda) return true;
    }
    return false;
}

bool ParsingTableGenerator::contains_lambda(set<string> set_of_strings) {
    for(string s : set_of_strings) {
        if(s == "\\L") return true;
    }
    return false;
}

void ParsingTableGenerator::remove_lambda(set<string> &set_of_strings) {
    set_of_strings.erase(set_of_strings.find("\\L"));
}

set<string> ParsingTableGenerator::vector_to_set_strings(vector<set<string>> vector_of_strings) {
    set<string> set_of_strings;
    for(set<string> s : vector_of_strings) {
        set_of_strings.insert(s.begin(), s.end());
    }
    return set_of_strings;
}

vector<set<string>> ParsingTableGenerator::calculate_first(GrammarRule *rule) {
    vector<set<string>> firsts;
    for(vector<Symbol*> &v : rule->productions) {
        set<string> first;
        if(v[0]->type == Symbol::Type::kTerminal) {
            first.insert(v[0]->name);
        } else {
            bool is_all_lambda = true;
            for(int i = 0; i < v.size(); ++i) {
                if(v[i]->type == Symbol::Type::kTerminal) {
                    first.insert(v[i]->name);
                    is_all_lambda = false;
                    break;
                }
                if(v[i]->type == Symbol::Type::kNonTerminal) {
                    if(!contains_lambda(v[i]->grammar_rule)) {
                        is_all_lambda = false;
                        if(this->firsts_map.find(v[i]->grammar_rule->name) == this->firsts_map.end()) {
                            // Init the set in the map; avoiding infinite recursion.
                            this->firsts_map[v[i]->grammar_rule->name];
                            this->firsts_map[v[i]->grammar_rule->name] = calculate_first(v[i]->grammar_rule);
                        }
                        set<string> current_nonTerminal_first = vector_to_set_strings(this->firsts_map[v[i]->grammar_rule->name]);
                        first.insert(current_nonTerminal_first.begin(), current_nonTerminal_first.end());
                        break;
                    }
                }
            }
            if(is_all_lambda) {
                first.insert("\\L");
            }
        }
        firsts.push_back(first);
    }
    return firsts;
}

vector<vector<set<string>>> ParsingTableGenerator::calculate_firsts() {
    vector<vector<set<string>>> ret;
    this->terminals.insert("\\$");
    for(GrammarRule *gr : this->rules) {
        if(this->firsts_map.find(gr->name) == this->firsts_map.end()) {
            vector<set<string>> current_rule_first_vector = calculate_first(gr);
            this->firsts_map[gr->name] = current_rule_first_vector;
        }
        ret.push_back(this->firsts_map[gr->name]);
    }
    return ret;
}

set<string> ParsingTableGenerator::calculate_follow(GrammarRule *rule) {
    set<string> current_rule_follow;
    for(GrammarRule *gr : this->rules) {
        for(vector<Symbol*> &v : gr->productions) {
            for(int i = 0; i < v.size(); ++i) {
                if(v[i]->name == rule->name) {
                    if(i + 1 == v.size() && gr->name != rule->name) {
                        if(this->follows_map.find(gr->name) == this->follows_map.end()) {
                            // Init the set in the map; avoiding infinite recursion.
                            this->follows_map[gr->name];
                            this->follows_map[gr->name] = calculate_follow(gr);
                        }
                        current_rule_follow.insert(this->follows_map[gr->name].begin(),
                                                   this->follows_map[gr->name].end());
                        break;
                    } else if(i + 1 == v.size() && gr->name == rule->name) {
                        break;
                    } else {
                        bool is_all_lambda = true;
                        for(int j = i + 1; j < v.size(); ++j) {
                            if(v[j]->type == Symbol::Type::kTerminal) {
                                current_rule_follow.insert(v[j]->name);
                                is_all_lambda = false;
                                break;
                            } else if(contains_lambda(vector_to_set_strings(this->firsts_map[v[j]->name]))) {
                                set<string> s = vector_to_set_strings(this->firsts_map[v[j]->name]);
                                remove_lambda(s);
                                current_rule_follow.insert(s.begin(), s.end());
                            } else {
                                set<string> s = vector_to_set_strings(this->firsts_map[v[j]->name]);
                                current_rule_follow.insert(s.begin(), s.end());
                                is_all_lambda = false;
                                break;
                            }
                        }
                        if(is_all_lambda && gr->name != rule->name) {
                            if(this->follows_map.find(gr->name) == this->follows_map.end()) {
                                this->follows_map[gr->name] = calculate_follow(v[i]->grammar_rule);
                            }
                            current_rule_follow.insert(this->follows_map[gr->name].begin(), this->follows_map[gr->name].end());
                        } else {
                            break;
                        }
                    }
                }
            }
        }
    }
    return current_rule_follow;
}

vector<set<string>> ParsingTableGenerator::calculate_follows() {
    vector<set<string>> ret;
    this->follows_map[this->rules[0]->name] = calculate_follow(this->rules[0]);
    this->follows_map[this->rules[0]->name].insert("\\$");
    for(GrammarRule *gr : this->rules) {
        if(this->follows_map.find(gr->name) == this->follows_map.end()) {
            this->follows_map[gr->name] = calculate_follow(gr);
        }
        ret.push_back(this->follows_map[gr->name]);
    }
    return ret;
}

void ParsingTableGenerator::generate_table() {
    this->table = (vector<Symbol*> ***)malloc(sizeof(vector<Symbol*>) * this->rules.size());
    for(int i = 0; i < this->rules.size(); ++i) {
        this->table[i] = (vector<Symbol*> **)malloc(sizeof(vector<Symbol*>) * this->terminals.size());
    }

    for(int i = 0; i < this->rules.size(); ++i) {
        for(int j = 0; j < this->terminals.size(); ++j) {
            this->table[i][j] = new vector<Symbol*>();
        }
    }

    for(int i = 0; i < this->rules.size(); ++i) {
        for(int j = 0; j < this->firsts[i].size(); ++j) {
            for(string s : this->firsts[i][j]) {
                if(s != "\\L") {
                    int current_terminal_index = this->terminals_indexes[s];
                    vector<Symbol*> *v = this->table[i][current_terminal_index];
                    v->insert(v->end(), this->rules[i]->productions[j].begin(), this->rules[i]->productions[j].end());
                } else {
                    for(string ss : this->follows[i]) {
                        int current_terminal_index = this->terminals_indexes[ss];
                        vector<Symbol *> v = *this->table[i][current_terminal_index];
                        if(v.size() > 1 ||(v.size() == 1 && (v[0]->type != Symbol::Type::kTerminal ||
                                                             v[0]->name != "\\L"))) {
//                            cout << endl << "error while generating parsing table" << endl;
//                            vector<Symbol*> v = *this->table[i][current_terminal_index];
//                            for(int k = 0; k < v.size(); ++k) {
//                                cout << v[k]->name << " ";
//                            }
//                            cout << endl << "terminal: " << ss << " rule: " << this->rules[i]->name << endl;
                        } else {
                            this->table[i][current_terminal_index]->push_back(new Symbol("\\L"));
                        }
                    }
                }
            }
        }

        // Add synch symbols in the follow set. Only in the empty cells.
        for(string ss : this->follows[i]) {
            int current_terminal_index = this->terminals_indexes[ss];
            vector<Symbol *> v = *this->table[i][current_terminal_index];
            if(v.size() == 0) {
                this->table[i][current_terminal_index]->push_back(Symbol::GetSynchSymbol());
            }
        }
    }
}

void ParsingTableGenerator::print_firsts() {
    cout << endl << "firsts: " << endl;
    for(vector<set<string>> v : firsts) {
        for(set<string> s : v) {
            for(string st : s) {
                cout << st << "  ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void ParsingTableGenerator::print_follows() {
    cout << endl << "follows: " << follows.size() << endl;
    for(set<string> s : follows) {
        for(string st : s) {
            cout << st << "  ";
        }
        cout << endl;
    }
    cout << endl;
}

void ParsingTableGenerator::print_table() {
    cout << endl << "table:" << endl;
    cout << "#" << " | ";
    for(string s : this->terminals) {
        cout << s << " | ";
    }
    cout << endl;

    for(int i = 0; i < this->rules.size(); ++i) {
        cout << this->rules[i]->name << " | ";
        for(int j = 0; j < this->terminals.size(); ++j) {
            for(Symbol *s : *table[i][j]) {
                cout << s->name << " ";
            }
            cout << ((j + 1) == this->terminals.size()? "": " | ");
        }
        cout << endl;
    }
    cout << endl;
}

void ParsingTableGenerator::generate_indexes() {
    for(int i = 0; i < rules.size(); ++i) {
        for(vector<Symbol *> v : rules[i]->productions) {
            for(Symbol *s : v) {
                if(s->type == Symbol::Type::kTerminal) {
                    terminals.insert(s->name);
                }
            }
        }
    }

    for(int i = 0; i < this->rules.size(); ++i) {
        this->rules_indexes[this->rules[i]->name] = i;
    }

    int index = 0;
    for(string terminal : this->terminals) {
        this->terminals_indexes[terminal] = index++;
    }
}

string ParsingTableGenerator::GetParsingTableInHtmlFormat() {
    string html = ""
            "<table class=\"table table-bordered table-hover\">\n"
            "  <thead>\n"
            "    <tr>\n"
            "      <th>#</th>\n";

    for(string s : this->terminals) {
        html += "      <th>";
        html += s;
        html += "</th>\n";
    }

    html += ""
            "    </tr>\n"
            "  </thead>\n"
            "  <tbody>\n";

    for(int i = 0; i < rules.size(); ++i) {
        html += "    <tr>\n";
        html += "      <td>";
        html += rules[i]->name;
        html += "</td>\n";
        html += "      <td>";
        for(int j = 0; j < terminals.size(); ++j) {
            html += "      <td>";
            for(Symbol *s : *table[i][j]) {

                html += "<span class=\"badge\">";
                html += s->name;
                html += "</span>";

            }
            html += "</td>\n";
        }
    }

    html += ""
            "  </tbody>\n"
            "</table>";

    return html;
}

string ParsingTableGenerator::GetFirstsInHtmlFormat() {
    string html = ""
            "<table class=\"table table-bordered table-hover\">\n"
            "  <thead>\n"
            "    <tr>\n"
            "      <th width=\"200px\">Non-Terminals</th>\n"
            "      <th>Firsts</th>\n"
            "    </tr>\n"
            "  </thead>\n"
            "  <tbody>\n";

    for(int i = 0; i < rules.size(); ++i) {
        html += "    <tr>\n";
        html += "      <td>";
        html += rules[i]->name;
        html += "</td>\n";
        html += "      <td>";
        for(set<string> &ss : firsts[i]) {
            for (string s : ss) {
                html += "<span class=\"badge first-badge\">";
                html += s;
                html += "</span>";
            }
        }
        html += "</td>\n";
        html += "    </tr>\n";
    }

    html += ""
            "  </tbody>\n"
            "</table>";

    return html;
}

string ParsingTableGenerator::GetFollowsInHtmlFormat() {
    string html = ""
            "<table class=\"table table-bordered table-hover\">\n"
            "  <thead>\n"
            "    <tr>\n"
            "      <th width=\"200px\">Non-Terminals</th>\n"
            "      <th>Follows</th>\n"
            "    </tr>\n"
            "  </thead>\n"
            "  <tbody>\n";

    for(int i = 0; i < rules.size(); ++i) {
        html += "    <tr>\n";
        html += "      <td>";
        html += rules[i]->name;
        html += "</td>\n";
        html += "      <td>";
        for (string s : follows[i]) {
            html += "<span class=\"badge follow-badge\">";
            html += s;
            html += "</span>";
        }
        html += "</td>\n";
        html += "    </tr>\n";
    }

    html += ""
            "  </tbody>\n"
            "</table>";

    return html;
}
