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
    Symbol *start_symbol;
    vector<Symbol *> the_stack;

    vector<Symbol *> ***table;
    map<string, int> rules_indexes;
    map<string, int> terminals_indexes;
    string outputInHtmlFormat;

    PredictiveParser(vector<Symbol *> ***table, map<string, int> rules_indexes,
                     map<string, int> terminals_indexes, Symbol *start_symbol);

    bool parse(vector<Token *> tokens);
    void initialize_the_stack();

    string StringifyStack();
    string GetStackInHtmlForm();
private:

    void print_the_stack(string current_token_name, bool new_token_passed, int index);

    void ErrorHandler(string error_msg, Token *token);

    void open_current_token_tag(const string &current_token_name, int index);

    void close_current_token_tag();

    void print_message_in_current_tag(string message);
};


#endif //JAVACOMPILER_PREDICTIVEPARSER_H
