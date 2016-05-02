//
// Created by ahmedatef on 5/2/16.
//

#ifndef JAVACOMPILER_GRAMMARRULE_H
#define JAVACOMPILER_GRAMMARRULE_H

#include <string>
#include "Symbol.h"

using namespace std;

class Symbol;

class GrammarRule {

public:
    string name;
    vector<vector<Symbol*> > productions;

    // TODO: Pass the Context Free Grammar object, to determine if the rule is already defined or not.
    GrammarRule(string rule);

    static GrammarRule * GetNonDefinedGrammarRule(string name);

private:
    GrammarRule();
    vector<string> parse_or_tokens(string &s);
    vector<Symbol*> parse_following_tokens(string &s);

};


#endif //JAVACOMPILER_GRAMMARRULE_H
