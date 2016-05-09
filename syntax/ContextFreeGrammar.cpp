//
// Created by Ahmed Barakat on 122 / 1 / 16.
//

#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>
#include "ContextFreeGrammar.h"
#include "ParsingFunctions.h"

using namespace std;

ContextFreeGrammar::ContextFreeGrammar() { }

// Read the file as one string and send it to AddRulesFromString to parse it.
vector<string> ContextFreeGrammar::AddRulesFromFile(string file_path) {
    ifstream cfg_ifs(file_path);
    stringstream cfg_buffer;
    cfg_buffer << cfg_ifs.rdbuf();
    return AddRulesFromString(cfg_buffer.str());
}

// Parse the string by the '#' character as it precedes every grammar rule.
// And send it to the AddRule to parse it and make new Symbol.
vector<string> ContextFreeGrammar::AddRulesFromString(string rules_raw) {
    // TODO: Handle the case where the '#' is being used inside the grammar rule.
    vector<string> rules_raw_tokens = split(rules_raw, '#', true);

    for(string s : rules_raw_tokens) {
        AddRule(s);
    }

    generate_ll_grammar();
    return rules_raw_tokens;
}

void ContextFreeGrammar::JustifyRuleString(string &rule_string) {
    // Cleaning up.
    // TODO: Make sure this will never cause an error to the actual content of the grammar rule.
    replace_all_(rule_string, "\f\n\r\t\v", ' ');
    // Clear duplicate consecutive spaces. Replace('\s+', '\s').
    remove_consecutive_(rule_string, ' ');
    // Trimming right and left extra spaces.
    trim_(rule_string);
}

// Searches in linear time for the name in the GrammarRules in the ContextFreeGrammar.
// Returns NULL is not exists.
GrammarRule * ContextFreeGrammar::FindExistingGrammarRule(const string &query_name) {
    for (GrammarRule *gr : unmodified_rules) {
        if(gr->name == query_name) return gr;
    }
    return NULL;
}

void ContextFreeGrammar::AddRule(string rule_string) {
    JustifyRuleString(rule_string);
    if (rule_string == "") return;

    string_rules.push_back(rule_string);

    GrammarRule::GrammarStringToken gst = GrammarRule::ParseGrammarString(rule_string);

    if (GrammarRule* matched_gr = FindExistingGrammarRule(gst.name)) { // Does Exist.
        matched_gr->AddProductionsFromString(gst.production);
    } else { // Undefined grammar rule.
        GrammarRule* gr = new GrammarRule(gst.name, this);
        gr->AddProductionsFromString(gst.production);
    };
}

void ContextFreeGrammar::generate_ll_grammar() {
    for(GrammarRule *rule : unmodified_rules) {
        GrammarRule *rule_clone = new GrammarRule();
        rule_clone->name = rule->name;
        vector<vector<Symbol*>> new_or_vector;
        vector<vector<Symbol*>> new_nonTerminal_or_vector;
        for(vector<Symbol*> &concat_vector : rule->productions) {
            vector<Symbol*> new_concat_vector;
            vector<Symbol*> new_nonTerminal_concat_vector;
            if(concat_vector[0]->type == Symbol::Type::kNonTerminal && concat_vector[0]->name == rule->name) {
                new_nonTerminal_concat_vector.insert(new_nonTerminal_concat_vector.end(),
                                                     concat_vector.begin() + 1, concat_vector.end());
                new_nonTerminal_or_vector.push_back(new_nonTerminal_concat_vector);
            } else {
                new_concat_vector.insert(new_concat_vector.end(), concat_vector.begin(), concat_vector.end());
                new_or_vector.push_back(new_concat_vector);
            }
        }
        GrammarRule *new_rule = nullptr;
        if(new_nonTerminal_or_vector.size() > 0) {
            new_rule = new GrammarRule();
            new_rule->name = rule->name + "\'\'";
            Symbol *current_rule_symbol = new Symbol(new_rule);
            Symbol *lambda = new Symbol("");
            vector<Symbol*> lambda_vector = {lambda};
            for(vector<Symbol*> &concat_vector : new_nonTerminal_or_vector) {
                concat_vector.push_back(current_rule_symbol);
            }
            for(vector<Symbol*> &concat_vector : new_or_vector) {
                concat_vector.push_back(current_rule_symbol);
            }
            new_nonTerminal_or_vector.push_back(lambda_vector);
            new_rule->productions = new_nonTerminal_or_vector;
//            rules.push_back(new_rule);
        }
        rule_clone->productions = new_or_vector;
        rules.push_back(rule_clone);
        if(new_rule != nullptr) {
            rules.push_back(new_rule);
        }
    }
}

