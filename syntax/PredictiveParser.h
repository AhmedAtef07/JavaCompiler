//
// Created by Ahmed Barakat on 129 / 8 / 16.
//

#ifndef JAVACOMPILER_PREDICTIVEPARSER_H
#define JAVACOMPILER_PREDICTIVEPARSER_H

#include <set>
#include <string>
#include <Token.h>
#include "Symbol.h"

using namespace std;

class PredictiveParser {

public:
    vector<Symbol*> the_stack;
    vector<Symbol *> ***table;
    set<string> terminals;
    vector<string> rules_names;

    int terminal_as_index(string terminal_name);
    int rule_as_index(string rule_name);

    PredictiveParser(vector<Symbol *> ***table, set<string> terminals, vector<string> rules_names);

    bool parse(vector<Token *> tokens);

private:

    void print_the_stack();

};


#endif //JAVACOMPILER_PREDICTIVEPARSER_H
