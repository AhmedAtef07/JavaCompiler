//
// Created by Ahmed Barakat on 122 / 1 / 16.
//

#ifndef JAVACOMPILER_SYMBOL_H
#define JAVACOMPILER_SYMBOL_H

#include <iostream>
#include <vector>
using namespace std;

class Symbol {

public:
    enum Type {
        terminal,
        nonTerminal,
    };
    vector<vector<Symbol*>> productions;
    string name;

    Symbol(string name);

};

#endif //JAVACOMPILER_SYMBOL_H
