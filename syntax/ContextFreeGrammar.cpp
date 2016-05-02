//
// Created by Ahmed Barakat on 122 / 1 / 16.
//

#include <sstream>
#include <fstream>
#include <iostream>
#include <map>
#include "ContextFreeGrammar.h"

using namespace std;

ContextFreeGrammar::ContextFreeGrammar(string cfg_file_name) {
    ifstream cfg(cfg_file_name);
    string rule, current_line;
    rules_as_strings.clear();
    while(getline(cfg, current_line)) {
        if(current_line[0] == '#') {
            if(rule.length() > 1) {
                rules_as_strings.push_back(rule);
            }
            rule = "";
            rule += current_line;
        } else {
            rule += current_line;
        }
    }

    map<string, Symbol*> created_symbols;
    map<string, bool> created_symbols_bools;

    for(string s : rules_as_strings) {
        cout << s << endl;
        s.erase(s.begin(), s.begin() + 1);
        vector<string> equal_splitted = split(s, '=');
        equal_splitted[0] = trim(equal_splitted[0]);
        vector<string> or_splitted = split(equal_splitted[1], '|');
        if(created_symbols_bools.find(equal_splitted[0]) != created_symbols_bools.end()) {
            cout << endl;
        } else {
            created_symbols_bools[equal_splitted[0]] = true;
            created_symbols[equal_splitted[0]] = new Symbol(equal_splitted[0]);
        }
        for(int i = 0; i < or_splitted.size(); ++i) {
            or_splitted[i] = trim(or_splitted[i]);
//            cout << "ss|" << or_splitted[i] << "|ss" << endl;
            vector<string> concats_splitted = split(or_splitted[i], ' ');
            vector<Symbol*> concats;
            concats.clear();
            for(int j = 0; j < concats_splitted.size(); ++j) {
                if(concats_splitted[j].length() < 1) continue;
                concats_splitted[j] = trim(concats_splitted[j]);
//                cout << "sss|" << concats_splitted[j] << "|sss" << endl;
                if(created_symbols_bools.find(concats_splitted[j]) == created_symbols_bools.end()) {
                    created_symbols_bools[concats_splitted[j]] = true;
                    created_symbols[concats_splitted[j]] = new Symbol(concats_splitted[j]);
                }
                concats.push_back(created_symbols[concats_splitted[j]]);
            }
            created_symbols[equal_splitted[0]]->productions.push_back(concats);
        }
        this->rules.push_back(created_symbols[equal_splitted[0]]);
        cout << endl;
    }

    for(Symbol *symbol : rules) {
        cout << symbol->name << " = ";
        for(int i = 0; i < symbol->productions.size(); ++i) {
            for(int j = 0; j < symbol->productions[i].size(); ++j) {
                cout << symbol->productions[i][j]->name << ((j+1) < symbol->productions[i].size()? "+":"");
            }
            cout << ((i+1) < symbol->productions.size()? " | ":"");
        }
        cout << endl;
    }
}

vector<string> &ContextFreeGrammar::split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

vector<string> ContextFreeGrammar::split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

string ContextFreeGrammar::trim_right(const string& s, const string& delimiters) {
    return s.substr( 0, s.find_last_not_of( delimiters ) + 1 );
}

string ContextFreeGrammar::trim_left(const string& s, const string& delimiters) {
    return s.substr( s.find_first_not_of( delimiters ) );
}

string ContextFreeGrammar::trim(const string& s, const string& delimiters) {
    return trim_left(trim_right(s, delimiters), delimiters);
}
