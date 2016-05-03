//
// Created by Ahmed Barakat on 122 / 1 / 16.
//

#ifndef JAVACOMPILER_CONTEXTFREEGRAMMAR_H
#define JAVACOMPILER_CONTEXTFREEGRAMMAR_H

#include <string>
#include <vector>
#include <map>
#include "Symbol.h"
#include "GrammarRule.h"

using namespace std;

class GrammarRule;

class ContextFreeGrammar {

public:
    vector<string> string_rules;
    vector<GrammarRule*> rules;

    ContextFreeGrammar();

    vector<string> AddRulesFromFile(string file_path);
    vector<string> AddRulesFromString(string rules);
    void AddRule(string rule_string);
    void JustifyRuleString(string &rule_string);

    GrammarRule * FindExistingGrammarRule(const string &query_name);
};


#endif //JAVACOMPILER_CONTEXTFREEGRAMMAR_H
