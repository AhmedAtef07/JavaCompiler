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

    map<string, int> rules_indexes;
    map<string, int> terminals_indexes;

    PredictiveParser(vector<Symbol *> ***table, map<string, int> rules_indexes, map<string, int> terminals_indexes);

    bool parse(vector<Token *> tokens);

private:

    void print_the_stack(string current_token_name);

};


#endif //JAVACOMPILER_PREDICTIVEPARSER_H
