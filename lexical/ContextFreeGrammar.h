//
// Created by Ahmed Barakat on 122 / 1 / 16.
//

#ifndef JAVACOMPILER_CONTEXTFREEGRAMMER_H
#define JAVACOMPILER_CONTEXTFREEGRAMMER_H

#include <string>
#include <vector>
#include "Symbol.h"

using namespace std;

class ContextFreeGrammar {

public:
    vector<string> rules_as_strings;
    vector<Symbol*> rules;
    ContextFreeGrammar(string cfg_file_name);

private:
    vector<string> &split(const string &s, char delim, vector<string> &elems);
    vector<string> split(const string &s, char delim);
    string trim_right(const string& s, const string& delimiters = " \f\n\r\t\v");
    string trim_left(const string& s, const string& delimiters = " \f\n\r\t\v");
    string trim(const string& s, const string& delimiters = " \f\n\r\t\v");

};


#endif //JAVACOMPILER_CONTEXTFREEGRAMMER_H
