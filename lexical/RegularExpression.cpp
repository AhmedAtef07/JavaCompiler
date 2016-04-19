//
// Created by ramy on 4/15/16.
//

#include "RegularExpression.h"

#include <iostream>
#include <iomanip>
#include <cstring>
#include <unistd.h>


RegularExpression::RegularExpression(string lexical_file_name) {
    ifstream lexical_file;

//    char the_path[256];
//    getcwd(the_path, 255);
//    printf("%s\n", the_path);

    string line;
    lexical_file.open(lexical_file_name);
    while(getline(lexical_file, line)) {
        this->addRule(line);
    }
}

RegularExpression::RegularExpression() {}

void RegularExpression::addRule(string line) {
    string builder = "";
    string older_line = line;
    for (int j = 0; j < line.length() ; ++j) {
        if (line[j] == ' ') continue;
        if(line[j] == 9) {
            older_line[j] = ' ';
            continue;
        }
        builder += line[j];
    }
    line = builder;
    builder = "";
    for(unsigned int i = 0 ; i < line.length() ; ++i) {

        builder += line[i];

//        cout << "builder:" << builder << endl;

        if(line[i] == '=' || line[i] == ':') {
            string key = builder.substr(0, builder.length() - 1);
            string rest_of_line = line.substr(i + 1, line.length());
            // cout << "i will evaluate" << setw(20) << key << ":(" << rest_of_line << ")" << endl;
            string value = this->evaluate(rest_of_line);
//             cout << "evaluating" << key << ":" << rest_of_line << "\tvalue:" << value << endl;
            (line[i] == '=') ? this->regular_definetions_[key] = value : this->regular_expressions[key] = value;
            break;
        }else if(line[i] == '{') {
            line = older_line;
            string keywords = line.substr(i+1, line.length()-1);
            string bldr = "";

            for (unsigned int j = 0; j < keywords.length(); ++j) {
                if ((keywords[j] == ' ' || keywords[j] == '}') && bldr != "") {
                    this->keywords.insert(bldr);
                    bldr = "";
                } else {
                    bldr += keywords[j];
                }
            }
            break;
        } else if(line[i] == '[') {
            line = older_line;
            string puncs = line.substr(i+1, line.length()-1);
            string bldr = "";

            for (unsigned int j = 0; j < puncs.length(); ++j) {
                if ((puncs[j] == ' ' || (puncs[j] == ']' && puncs[j-1] != '\\')) && bldr != "") {
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
        builder += line[i];

        if(line[i] == '-' && line[i-1] != '\\') {
            string range_exp = this->range_closure(line[i-1], line[i+1]);
            // cout << "range exp:" << line[i-1] << "-" << line[i+1] << ":" << range_exp << endl;
//            cout << line_builder.length() << endl;
            if(builder.length() > 2) {
                line_builder.append(builder.substr(0, builder.length() - 2));
            }
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
//             cout << "checking for key:" << key << ":" << this->regular_definetions_.count(key) << endl;
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
    if(regular_definetions_.count(key)) {
                string value_of_key = regular_definetions_.at(key);
//                 cout << "found key:" << key << ":" << value_of_key << endl;

                add_to_line_builder_left(line, line_builder, i, value_of_key);

    } else {
                // Do nothing
                string new_key_right = key;
                string new_key_left = key;
                string builder_right = builder.substr(0, builder.length());
                string builder_left = builder;
                string to_add_to_builder_left = "";
                string to_add_to_builder_right = "";
                do {
                    if(new_key_right.length() < 2) break;
                    to_add_to_builder_left += builder_left[0];
                    builder_left = builder_left.substr(1, builder_left.length()-1);
                    new_key_left = new_key_left.substr(1, new_key_left.length()-1);


                    if (regular_definetions_.count(new_key_left)) {
//                         cout << "found new key, new builder:" << to_add_to_builder << endl;
                        string value_of_key = regular_definetions_.at(new_key_left);
                        line_builder.append(to_add_to_builder_left);
                        add_to_line_builder_left(line, line_builder, i, value_of_key);
                        return;
                    }

                    to_add_to_builder_right += builder_right[builder_right.length() - 1];
                    builder_right = builder_right.substr(0, builder_right.length()-1);
                    new_key_right = new_key_right.substr(0, new_key_right.length()-1);

//                    cout << "Trying again with new key:" << to_add_to_builder_right << endl;
                    if (regular_definetions_.count(new_key_right)) {
                        string value_of_key = regular_definetions_.at(new_key_right);
                        cout << "found new key, new builder:" << to_add_to_builder_right << endl;
                        add_to_line_builder_right(line, line_builder, i, value_of_key, to_add_to_builder_right);
//                        line_builder.append(to_add_to_builder_right);
                        return;
                    }

                }while(new_key_right.length());

                builder = builder;

                line_builder.append(builder);
//                 cout << "add new builder:" << builder << endl;
            }
}

void RegularExpression::add_to_line_builder_left(const string &line, string &line_builder, unsigned int i,
                                            const string &value_of_key) const {
            string value;
            if(line[i] == '\\') {
                (line[i + 1] == '=') ? value = "(" + value_of_key + ")" + line[i] :
                        value = "(" + value_of_key + ")" + line[i] + line[i+1];
                line_builder.append(value);
                i++;
            } else {
                value = "(" + value_of_key + ")";
                if (i+1 != line.length() || is_seperator(line, i)) value += line[i];
                line_builder.append(value);
            }
//    cout << "line[i] : " << line[i] << endl;
}

void RegularExpression::add_to_line_builder_right(const string &line, string &line_builder, unsigned int i,
                                                 const string &value_of_key, const string &rest_of_line) const {
    string value;
    if(line[i] == '\\') {
        value = "(" + value_of_key + ")" ;
        value += rest_of_line;
        value += line[i] + line[i+1];
        line_builder.append(value);
        i++;
    } else {
        value = "(" + value_of_key + ")";
        value += rest_of_line;
        cout << "value : " << value << endl;
        if (i + 1 != line.length() || is_seperator(line, i)) value += line[i];
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


void RegularExpression::addRulesFromFilePath(string file_path) {

}