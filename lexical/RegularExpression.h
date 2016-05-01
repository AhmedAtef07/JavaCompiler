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
    map<string, string> regular_expressions;

    map<string, string> regular_definetions_;

    RegularExpression(string lexical_file_name);

    RegularExpression();

    void addRule(string line);

    void addRulesFromFilePath(string file_path);

private:
    string evaluate(string line);
    string range_closure(char char1, char char2);

    void build_from_key(const string &line, string &line_builder, string &builder, unsigned int i, const string &key) const;

    bool is_seperator(const string &line, unsigned int i) const;

    void add_to_line_builder_left(const string &line, string &line_builder, unsigned int i, const string &value_of_key) const;

    void add_to_line_builder_right(const string &line, string &line_builder, unsigned int i, const string &value_of_key,const string &rest_of_line) const;
};


#endif //JAVACOMPILER_REGULAREXPRESSION_H
