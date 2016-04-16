//
// Created by ramy on 4/15/16.
//

#include "RegularExpression.h"

#include <iostream>
#include <iomanip>


RegularExpression::RegularExpression(string lexical_file_name) {
    ifstream lexical_file;
    lexical_file.open(lexical_file_name);
    string line;

    while(getline(lexical_file, line)) {
        // cout << "proccessing line: " << line << endl;
        this->convertLine(line);
    }

}

void RegularExpression::convertLine(string line) {
    string builder = "";
    for(unsigned int i = 0 ; i < line.length() ; ++i) {
        if (line[i] == ' ') continue;

        builder += line[i];

//        cout << "builder:" << builder << endl;

        if(line[i] == '=' || line[i] == ':') {
            string key = builder.substr(0, builder.length() - 1);
            string rest_of_line = line.substr(i + 1, line.length());
            // cout << "i will evaluate" << setw(20) << key << ":(" << rest_of_line << ")" << endl;
            string value = this->evaluate(rest_of_line);
            // cout << "evaluating" << key << ":" << rest_of_line << "\tvalue:" << value << endl;
            if(line[i] == '=')
                this->regular_definetions[key] = value;
            else
                this->regular_expressions[key] = value;

            builder = "";
            break;

        }else if(line[i] == '{') {
            string keywords = line.substr(i+1, line.length()-1);
            string bldr = "";

            for (unsigned int j = 0; j < keywords.length(); ++j) {
                if (keywords[j] == ' ' || keywords[j] == '}') {
                    this->keywords.insert(bldr);
                    bldr = "";
                } else {
                    bldr += keywords[j];
                }
            }
            break;
        } else if(line[i] == '[') {
            string puncs = line.substr(i+1, line.length()-1);
            string bldr = "";

            for (unsigned int j = 0; j < puncs.length(); ++j) {
                if (puncs[j] == ' ' || puncs[j] == ']') {
                    this->punctuations.insert(bldr);
                    bldr = "";
                } else {
                    bldr += puncs[j];
                }
            }
            break;
        }
    }
}

string RegularExpression::evaluate(string line) {
    string line_builder, builder;
    line_builder = "";
    builder = "";

    for (unsigned int i = 0; i < line.length(); ++i) {

        if (line[i] == ' ') continue;

        builder += line[i];

        // cout << "builder:" << builder << "\tlinebuilder:" << line_builder << "\tlastread:" << line[i] << endl;


        if(line[i] == '-' && line[i-1] != '\\') {
            string range_exp = this->range_closure(line[i-1], line[i+1]);

            // cout << "range exp:" << line[i-1] << "-" << line[i+1] << ":" << range_exp << endl;
            line_builder.append(range_exp);
            i++;
            builder = "";
            continue;
        } else if ( is_seperator(line, i) || i+1 == line.length()){
            unsigned long builder_length;

            if(i + 1 == line.length() && !is_seperator(line, i)) {
                builder_length = builder.length();
            } else {
                builder_length = builder.length() - 1;
            }


            string key = builder.substr(0, builder_length);
            // cout << "checking for key:" << key << ":" << this->regular_definetions.count(key) << endl;
            this->build_from_key(line, line_builder, builder, i, key);

            builder = "";
        }

    }

    return line_builder;

}

bool RegularExpression::is_seperator(const string &line, unsigned int i) const {
    return line[i] == '+'
           || line[i] == '*'
           || line[i] == '('
           || line[i] == ')'
           || line[i] == '|'
           || line[i] == '\\'
           || line[i] == '.';
}

void RegularExpression::build_from_key(const string &line, string &line_builder, string &builder, unsigned int i,
                                       const string &key) const {
    if(regular_definetions.count(key)) {
                string value_of_key = regular_definetions.at(key);
                // cout << "found key:" << key << ":" << value_of_key << endl;

                add_to_line_builder(line, line_builder, i, value_of_key);

    } else {
                // Do nothing
                string new_key = key;
                string old_builder = builder;
                string to_add_to_builder = "";
                do {
                    if(new_key.length() < 2) break;
                    to_add_to_builder += builder[0];
                    builder = builder.substr(1, builder.length()-1);
                    new_key = new_key.substr(1, new_key.length()-1);

                    // cout << "Trying again with new key:" << new_key << endl;

                    if (regular_definetions.count(new_key)) {
                        // cout << "found new key, new builder:" << to_add_to_builder << endl;
                        string value_of_key = regular_definetions.at(new_key);
                        line_builder.append(to_add_to_builder);
                        add_to_line_builder(line, line_builder, i, value_of_key);
                        return;
                    }
                }while(new_key.length());

                builder = old_builder;


                line_builder.append(builder);
                // cout << "add new builder:" << builder << endl;
            }
}

void RegularExpression::add_to_line_builder(const string &line, string &line_builder, unsigned int i,
                                            const string &value_of_key) const {
            string value;
            if(line[i] == '\\') {
                    value = "(" + value_of_key + ")" + line[i] + line[i+1];
                    line_builder.append(value);
                    i++;
                } else {
                    value = "(" + value_of_key + ")";
                    if (i+1 != line.length() || is_seperator(line, i)) value += line[i];
                    line_builder.append(value);
                }
}

bool is_int(char chart) {
    return chart >= '0' && chart <= '9';
}

bool is_alpha(char chart) {
    return (chart >= 'a' && chart <= 'z') || (chart >= 'A' && chart <= 'Z');
}

string RegularExpression::range_closure(char char1, char char2) {
    string expr = "";
    if(char1 < char2) {
        string s = "(";
        expr.append(s);
        expr += char1;
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







