//
// Created by Ahmed Barakat on 129 / 8 / 16.
//

#include "PredictiveParser.h"

PredictiveParser::PredictiveParser(vector<Symbol *> ***table, set<string> terminals, vector<string> rules_names) {
    this->table = table;
    this->terminals = terminals;
    this->rules_names = rules_names;
}


int PredictiveParser::terminal_as_index(string terminal_name) {
    if(this->terminals.find(terminal_name) == this->terminals.end()) return -1;
    return distance(this->terminals.begin(), this->terminals.find(terminal_name));
}

int PredictiveParser::rule_as_index(string rule_name) {
    for(int i = 0; i < rules_names.size(); ++i) {
        if(this->rules_names[i] == rule_name) return i;
    }
    return -1;
}

bool PredictiveParser::parse(vector<Token *> tokens) {
    vector<Symbol *> v = *this->table[0][terminal_as_index(tokens[0]->name)];
    if(v.size() == 0) {
        cout << "error" << endl;
        return false;
    } else {
        for(int i = v.size() - 1; i > -1; --i) {
            the_stack.push_back(v[i]);
            print_the_stack();
        }
    }
    for(int i = 0; i < tokens.size();) {
        Token *token = tokens[i];
        if(the_stack.size() == 0) return false;
        if(the_stack.back()->type == Symbol::Type::kTerminal) {
            if(the_stack.back()->name == token->name) {
                cout << "matched: " << token->name << " " << the_stack.back()->name << endl;
                the_stack.pop_back();
                print_the_stack();
                ++i;
            } else {
                cout << "error" << endl;
                return false;
            }
        } else {
            vector<Symbol *> v = *this->table[rule_as_index(the_stack.back()->name)][terminal_as_index(token->name)];
            if(v.size() == 0) {
                cout << "error" << endl;
                return false;
            } else {
                the_stack.pop_back();
                for(int i = v.size() - 1; i > -1; --i) {
                    the_stack.push_back(v[i]);
                    print_the_stack();
                }
            }
        }
    }

    if(the_stack.size() == 0) {
        return true;
    }
    else {
        return false;
    }
}

void PredictiveParser::print_the_stack() {
    for(Symbol *s : the_stack) {
        cout << s->name << "  ";
    }
    cout << endl;
}

