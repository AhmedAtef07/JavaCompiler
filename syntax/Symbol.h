//
// Created by Ahmed Barakat on 122 / 1 / 16.
//

#ifndef JAVACOMPILER_SYMBOL_H
#define JAVACOMPILER_SYMBOL_H

#include <iostream>
#include <vector>
#include "GrammarRule.h"

using namespace std;

class GrammarRule;

class Symbol {

public:
    enum Type {
        kTerminal,
        kNonTerminal,
        kSynch
    };

    string name;
    GrammarRule* grammar_rule;
    Type type;

    Symbol(const string &name);
    Symbol(GrammarRule* grammar_rule);

    static Symbol* GetSynchSymbol();

private:
    Symbol();
};

#endif //JAVACOMPILER_SYMBOL_H
