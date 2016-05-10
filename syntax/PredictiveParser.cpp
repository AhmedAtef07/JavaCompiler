//
// Created by Ahmed Barakat on 129 / 8 / 16.
//

#include "PredictiveParser.h"

PredictiveParser::PredictiveParser(vector<Symbol *> ***table, map<string, int> rules_indexes, map<string, int> terminals_indexes) {
    this->table = table;
    this->rules_indexes = rules_indexes;
    this->terminals_indexes = terminals_indexes;
    initialize_the_stack();
}

void PredictiveParser::initialize_the_stack() {
    the_stack.clear();
    // TODO: Check the language will never have '\\$'.
    the_stack.push_back(new Symbol("\\$"));
}

// Just for delivering the project.
void PredictiveParser::ErrorHandler(string error_msg, Token* token) {
    cout << "@@@ error @@@: " << error_msg << endl;
    cout << "@@@ stack top @@@: " << the_stack.back()->name << endl;
    cout << "@@@ token @@@: " << token->name << endl;
}

bool PredictiveParser::parse(vector<Token *> tokens) {
    for(int i = 0; i < tokens.size(); ) {
        Token *token = tokens[i];
        if(the_stack.size() == 1 && the_stack.back()->name == "\\$" && token->name != "\\$") {
            vector<Symbol *> v = *this->table[0][terminals_indexes[tokens[0]->name]];
            if(v.size() == 0) {
                // Empty Table Cell Error.
                ErrorHandler("Empty Table Cell", token);
                ++i;
                continue;
            } else {
                for(int j = v.size() - 1; j != -1; --j) {
                    the_stack.push_back(v[j]);
                }
                print_the_stack(token->name);
            }
        }
        if(the_stack.back()->type == Symbol::Type::kTerminal) {
            if(the_stack.back()->name == "\\L") {
                the_stack.pop_back();
                continue;
            }
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
                // Mismatch Error.
                ErrorHandler("Mismatch Terminal with input token", token);
                the_stack.pop_back();
                continue;
            }
        } else {
            // Non-terminal on the top of the stack.
            vector<Symbol *> v = *this->table[rules_indexes[the_stack.back()->name]][terminals_indexes[token->name]];
            if(v.size() == 0) {
                // Empty Table Cell Error.
                ErrorHandler("Empty Table Cell", token);
                ++i;
                continue;
            } else if(v[0]->type == Symbol::Type::kSynch) {
                // Synch symbol found. Dropping from the stack.
                ErrorHandler("Synch Cell", token);
                the_stack.pop_back();
            } else {
                // Vector of symbols found in the table cell.
                the_stack.pop_back();
                for(int j = v.size() - 1; j != -1; --j) {
                    the_stack.push_back(v[j]);
                }
                print_the_stack(token->name);
            }
        }
    }

    if(the_stack.size() == 0 || (the_stack.size() == 1 && the_stack.back()->name == "\\$")) {
        return true;
    }
    return false;
}

void PredictiveParser::print_the_stack(string current_token_name) {
    cout << "Current Token: #" << current_token_name << "#\t";
    for(Symbol *s : the_stack) {
        cout << s->name << "  ";
    }
    cout << endl;
}

