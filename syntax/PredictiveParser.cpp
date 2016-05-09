//
// Created by Ahmed Barakat on 129 / 8 / 16.
//

#include "PredictiveParser.h"

PredictiveParser::PredictiveParser(vector<Symbol *> ***table, map<string, int> rules_indexes, map<string, int> terminals_indexes) {
    this->table = table;
    this->rules_indexes = rules_indexes;
    this->terminals_indexes = terminals_indexes;
}

bool PredictiveParser::parse(vector<Token *> tokens) {
    for(int i = 0; i < tokens.size();) {
        Token *token = tokens[i];
        if(the_stack.size() == 0) {
            vector<Symbol *> v = *this->table[0][terminals_indexes[tokens[0]->name]];
            if(v.size() == 0) {
                cout << "error" << endl;
                return false;
            } else {
                for(int j = v.size() - 1; j > -1; --j) {
                    the_stack.push_back(v[j]);
                    print_the_stack(token->name);
                }
            }
        }
        if(the_stack.back()->type == Symbol::Type::kTerminal) {
            if(the_stack.back()->name == token->name) {
                cout << "matched: " << token->name << " " << the_stack.back()->name << endl;
                the_stack.pop_back();
                if(i + 1 < tokens.size()) {
                    print_the_stack(tokens[i + 1]->name);
                } else {
                    print_the_stack("");
                }
                ++i;
            } else {
                cout << "error" << endl;
                cout << "waiting: " << the_stack.back()->name << " found: " << token->name << endl;
                return false;
            }
        } else {
            vector<Symbol *> v = *this->table[rules_indexes[the_stack.back()->name]][terminals_indexes[token->name]];
            if(v.size() == 0) {
                cout << "error" << endl;
                return false;
            } else {
                the_stack.pop_back();
                for(int j = v.size() - 1; j > -1; --j) {
                    the_stack.push_back(v[j]);
                    print_the_stack(token->name);
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

void PredictiveParser::print_the_stack(string current_token_name) {
    for(Symbol *s : the_stack) {
        cout << s->name << "  ";
    }
    cout << "   current token: " << current_token_name << endl;
}

