//
// Created by ahmedatef on 5/2/16.
//

#ifndef JAVACOMPILER_GRAMMARRULE_H
#define JAVACOMPILER_GRAMMARRULE_H

#include <string>
#include "Symbol.h"
#include "ContextFreeGrammar.h"

using namespace std;

class Symbol;
class ContextFreeGrammar;

class GrammarRule {

public:
    struct GrammarStringToken {
        string name;
        string production;
    };

    string name;
    // Outer vector is OR predication_rules x = a | b. Inner following predication_rules x = '(' 'id' ')'.
    vector<vector<Symbol*> > productions;

    GrammarRule(string name, ContextFreeGrammar* cfg);
    GrammarRule();

    void AddProductionsFromString(string rule);

    static GrammarRule::GrammarStringToken ParseGrammarString(string rule);

private:

    ContextFreeGrammar* cfg;
    vector<string> parse_or_tokens(string &s);

    vector<Symbol*> parse_following_tokens(string &s);
};


#endif //JAVACOMPILER_GRAMMARRULE_H
