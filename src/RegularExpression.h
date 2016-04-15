//
// Created by ramy on 4/15/16.
//

#ifndef JAVACOMPILER_REGULAREXPRESSION_H
#define JAVACOMPILER_REGULAREXPRESSION_H


#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <map>

using namespace std;

class RegularExpression {

public:

    set<string> keywords;
    set<string> punctuations;
    map<string, string> regular_definetions;
    map<string, string> regular_expressions;

    RegularExpression(const string lexical_file_name);

private:

    void convertLine(string line);
    string evaluate(string line);
    string range_closure(char char1, char char2);

};


#endif //JAVACOMPILER_REGULAREXPRESSION_H
