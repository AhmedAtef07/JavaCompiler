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
    vector<vector<set<string>>> firsts;
    vector<set<string>> follows;
    vector<Symbol *> ***table;

    map<string, int> terminals_indexes;
    map<string, int> rules_indexes;

    ParsingTableGenerator(vector<GrammarRule*> rules);

private:

    vector<GrammarRule*> rules;
    set<string> terminals;
    map<string, vector<set<string>>> firsts_map;

    map<string, set<string>> follows_map;

    bool contains_lambda(GrammarRule *rule);
    bool contains_lambda(set<string> set_of_strings);
    void remove_lambda(set<string> &set_of_strings);

    set<string> vector_to_set_strings(vector<set<string>> vector_of_strings);

    vector<set<string>> calculate_first(GrammarRule* rule);
    vector<vector<set<string>>> calculate_firsts();

    set<string> calculate_follow(GrammarRule* rule);
    vector<set<string>> calculate_follows();

    void generate_table();
    void generate_indexes();
    void print_table();

};


#endif //JAVACOMPILER_PARSINGTABLEGENERATOR_H
