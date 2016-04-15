//
// Created by ramy on 4/15/16.
//

#include "RegularExpression.h"

RegularExpression::RegularExpression(const string lexical_file_name) {

}

void RegularExpression::convertLine(string line) {
    string builder = "";
    for(int i = 0 ; i < line.length() ; ++i) {
        builder.append(&line[i]);
        if(line[i] == '=' || line[i] == ':') {
            string key = builder.substr(0, builder.length() - 2);
            string rest_of_line = line.substr(i + 1, line.length() - 1);
            string value = evaluate(rest_of_line);
            if(line[i] == '=')
                RegularExpression::regular_definetions[key] = value;
            else
                RegularExpression::regular_expressions[key] = value;
        }else if(line[i] == '{') {
            if(line[i] == ' ') {
                RegularExpression::keywords.insert(builder);
                builder = "";
            }
        }
    }
}

string RegularExpression::evaluate(string line) {
    return std::basic_string<char, char_traits<char>, allocator<char>>();
}

string RegularExpression::range_closure(char char1, char char2) {
    return std::basic_string<char, char_traits<char>, allocator<char>>();
}







