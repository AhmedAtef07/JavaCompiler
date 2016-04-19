//
// Created by ahmedatef on 4/17/16.
//

#ifndef JAVACOMPILER_LEXICAL_H
#define JAVACOMPILER_LEXICAL_H

#include "Dfa.h"

class Lexical {
public:
    struct Output {
        vector<Token *> tokens;
        int errors_found;
        vector<string> errors_strings;
    };

    static const vector<string> alphabet;

    void AddDfa(Nfa* nfa, Token* token);
    Lexical::Output ParseInput(string input);

private:
    vector<Dfa *> dfas;
};


#endif //JAVACOMPILER_LEXICAL_H
