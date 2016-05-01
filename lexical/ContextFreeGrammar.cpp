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

    for(string s : rules_as_strings) {
        cout << s << endl;
        vector<string> equal_splitted = split(s, '=');
        vector<string> or_splitted = split(equal_splitted[1], '|');
        equal_splitted[0] = trim(equal_splitted[0]);
//        cout << equal_splitted[0] << "=";
        for(int i = 0; i < or_splitted.size(); ++i) {
            or_splitted[i] = trim(or_splitted[i]);
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
