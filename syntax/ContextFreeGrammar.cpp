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

    AdjustingLambdaFormat(rule_string);

    string_rules.push_back(rule_string);

    GrammarRule::GrammarStringToken gst = GrammarRule::ParseGrammarString(rule_string);

    if (GrammarRule* matched_gr = FindExistingGrammarRule(gst.name)) { // Does Exist.
        matched_gr->AddProductionsFromString(gst.production);
    } else { // Undefined grammar rule.
        GrammarRule* gr = new GrammarRule(gst.name, this);
        gr->AddProductionsFromString(gst.production);
    };
}

string ContextFreeGrammar::many_dashes(int count) {
    string dashes = "";
    for(int i = 0; i < count; ++i) {
        dashes += "\'";
    }
    return dashes;
}

void ContextFreeGrammar::generate_ll_grammar() {
    remove_left_recursion();
    remove_left_factoring();
}

void ContextFreeGrammar::remove_left_recursion() {
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
        Symbol *new_rule_symbol = nullptr;
        if(new_nonTerminal_or_vector.size() > 0) {
            new_rule = new GrammarRule();
            new_rule->name = rule->name + many_dashes(2);
            new_rule_symbol = new Symbol(new_rule);
            Symbol *lambda = new Symbol("\\L");
            vector<Symbol*> lambda_vector = {lambda};
            for(vector<Symbol*> &concat_vector : new_nonTerminal_or_vector) {
                concat_vector.push_back(new_rule_symbol);
            }
            for(vector<Symbol*> &concat_vector : new_or_vector) {
                concat_vector.push_back(new_rule_symbol);
            }
            new_nonTerminal_or_vector.push_back(lambda_vector);
            new_rule->productions = new_nonTerminal_or_vector;
//            rules.push_back(new_rule);
        }
        if(new_or_vector.size() > 0) {
            rule_clone->productions = new_or_vector;
        } else {
            vector<vector<Symbol *>> v;
            vector<Symbol *> vv;
            vv.push_back(new_rule_symbol);
            v.push_back(vv);
            rule_clone->productions = v;
        }
        rules.push_back(rule_clone);
        if(new_rule != nullptr) {
            rules.push_back(new_rule);
        }
    }
}

void ContextFreeGrammar::remove_left_factoring() {
    for(int i = 0; i < rules.size(); ++i) {
        int dashes_count = 3;
        vector<vector<Symbol*>> &or_vector = rules[i]->productions;
        vector<vector<Symbol*>> new_or_vector;
        for(int j = 0; j < (int)or_vector.size() - 1; ++j) {
            vector<Symbol*> &current_concat_vector = or_vector[j];
            Symbol * current_first_symbol = current_concat_vector[0];
            for(int k = j + 1; k < or_vector.size();) {
                vector<Symbol*> &moving_concat_vector = or_vector[k];
                Symbol * moving_first_symbol = moving_concat_vector[0];
                if(moving_first_symbol->type == current_first_symbol->type
                   && moving_first_symbol->name == current_first_symbol->name) {
                    vector<Symbol*> new_concat_vector;
                    if(moving_concat_vector.size() > 1) {
                        new_concat_vector.insert(new_concat_vector.end(),
                                                 moving_concat_vector.begin() + 1, moving_concat_vector.end());
                    } else {
                        new_concat_vector.push_back(new Symbol("\\L"));
                    }
                    new_or_vector.push_back(new_concat_vector);
                    or_vector.erase(or_vector.begin() + k);
                } else {
                    ++k;
                }
            }
            if(new_or_vector.size() > 0) {
                vector<Symbol*> new_concat_vector;
                if(current_concat_vector.size() > 1) {
                    new_concat_vector.insert(new_concat_vector.end(),
                                             current_concat_vector.begin() + 1, current_concat_vector.end());
                } else {
                    new_concat_vector.push_back(new Symbol("\\L"));
                }
                current_concat_vector.erase(current_concat_vector.begin() + 1, current_concat_vector.end());
                GrammarRule *new_rule = new GrammarRule();
                new_rule->name = rules[i]->name + many_dashes(dashes_count++);
                Symbol *new_rule_symbol = new Symbol(new_rule);
                current_concat_vector.push_back(new_rule_symbol);
                new_or_vector.push_back(new_concat_vector);
                new_rule->productions = new_or_vector;
                rules.push_back(new_rule);
            }
        }
    }
}

void ContextFreeGrammar::AdjustingLambdaFormat(string &rule_string) {
    replace_string_(rule_string, "'\\L'", "\\L");
    replace_string_(rule_string, "\\L", "'\\L'");
}






