//
// Created by Ahmed Barakat on 123 / 2 / 16.
//

#ifndef JAVACOMPILER_PARSINGTABLEGENERATOR_H
#define JAVACOMPILER_PARSINGTABLEGENERATOR_H


#include "GrammarRule.h"
#include <string>
#include <set>
#include <map>

using namespace std;

class ParsingTableGenerator {

public:
    ParsingTableGenerator(vector<GrammarRule*> rules);

private:
    vector<GrammarRule*> rules;
    vector<vector<set<string>>> firsts;
    map<string, vector<set<string>>> firsts_map;
    map<string, set<string>> follows_map;
    vector<set<string>> follows;

    bool contains_lambda(GrammarRule *rule);
    bool contains_lambda(set<string> set_of_strings);

    vector<set<string>> calculate_first(GrammarRule* rule);
    vector<vector<set<string>>> calculate_firsts();
    set<string> calculate_follow(GrammarRule* rule);
    vector<set<string>> calculate_follows();

    void remove_lambda(set<string> &set_of_strings);
    set<string> vector_to_set_strings(vector<set<string>> vector_of_strings);
};


#endif //JAVACOMPILER_PARSINGTABLEGENERATOR_H
