//
// Created by ramy on 4/15/16.
//

#include "RegularExpression.h"

RegularExpression::RegularExpression(const string lexical_file_name) {
    fstream lexical_file(lexical_file_name);

    string line;

    while(getline(lexical_file, line)) {
        this->convertLine(line);
    }
}

void RegularExpression::convertLine(string line) {
    string builder = "";
    for(unsigned int i = 0 ; i < line.length() ; ++i) {
        builder.append(&line[i]);
        if(line[i] == '=' || line[i] == ':') {

            string key = builder.substr(0, builder.length() - 2);
            string rest_of_line = line.substr(i + 1, line.length() - 1);
            string value = this->evaluate(rest_of_line);
            if(line[i] == '=')
                this->regular_definetions[key] = value;
            else
                this->regular_expressions[key] = value;

            builder = "";

        }else if(line[i] == '{') {
            string keywords = line.substr(i+1, line.length()-1);
            string bldr = "";

            for (unsigned int j = 0; j < keywords.length(); ++j) {
                if (keywords[j] == ' ') {
                    this->keywords.insert(bldr);
                    bldr = "";
                } else {
                    bldr.append(&keywords[j]);
                }
            }
            break;
        } else if(line[i] == '[') {
            string puncs = line.substr(i+1, line.length()-1);
            string bldr = "";

            for (unsigned int j = 0; j < puncs.length(); ++j) {
                if (puncs[j] == ' ') {
                    this->punctuations.insert(bldr);
                    bldr = "";
                } else {
                    bldr.append(&puncs[j]);
                }
            }
            break;
        }
    }
}

string RegularExpression::evaluate(string line) {
    string line_builder, builder;
    line_builder = builder = "";

    for (unsigned int i = 0; i < line.length(); ++i) {

        line_builder.append(&line[i]);

        if(line[i] == '-') {
            string range_expr = this->range_closure(line[i-1], line[i+1]);
            line_builder.append(range_expr);
            i++;
            builder = "";
        } else if (
               line[i] == '-'
            || line[i] == '+'
            || line[i] == '*'
            || line[i] == '('
            || line[i] == ')'
            || line[i] == '|'
            || line[i] == '\\'
            || line[i] == '\n'
        ){
            string key = builder.substr(0, builder.length()-2);
            if(this->regular_definetions.count(key)) {
                string value_of_key = this->regular_definetions.at(key);
                string value;

                if(line[i] == '\\') {
                    value = "(" + value_of_key + ")" + line[i] + line[i+1];
                    line_builder.append(value);
                    i++;
                } else {
                    value = "(" + value_of_key + ")" + line[i];
                    line_builder.append(value);
                }

            } else {
                // Do nothing
            }
        }

    }

    return line_builder;

}

bool is_int(char chart) {
    return (chart >= '0' && chart <= '9') ? true : false;
}

bool is_alpha(char chart) {
    return ((chart >= 'a' && chart <= 'z') || (chart >= 'A' && chart <= 'Z')) ? true : false;
}

string RegularExpression::range_closure(char char1, char char2) {
    string expr = "";
    if(char1 < char2) {
        string s = "(";
        expr.append(s);
        expr.append(&char1);
        s = '|';
        expr.append(s);
        if(is_int(char1) && is_int(char2) || is_alpha(char1) && is_alpha(char2)) {
            for (int i = char1 + 1; i <= char2 - 1; ++i) {
                s = (char)i;
                expr.append(s);
                s = '|';
                expr.append(s);
            }
            s = char2;
            expr.append(s);
            s = ')';
            expr.append(s);
        }
    }
    return expr;
}





