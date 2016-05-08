//
// Created by ahmedatef on 5/2/16.
//

#ifndef JAVACOMPILER_PARSINGFUNCTIONS_H
#define JAVACOMPILER_PARSINGFUNCTIONS_H

#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

namespace  {


    // Replaces each char from 'from' string to the 'to' char.
    // Changes the passed string.
    void replace_all_(string &s, string from, char to) {
        for(char c : from) {
            replace(s.begin(), s.end(), c, to);
        }
    }

    // Clear duplicate consecutive of 'c' char. Replace(\c+\g, 'c').
    // Changes the passed string.
    void remove_consecutive_(string &s, char c) {
        string ns;
        ns.push_back(s[0]);

        for(int i = 1, len = s.length(); i < len; ++i) {
            if(s[i] == s[i - 1] && s[i] == c) continue;
            ns.push_back(s[i]);
        }

        s = ns;
    }

    void split_(const string &s, char delimiter, vector<string> &splitted_tokens,
                bool escape_if_empty) {
        stringstream ss(s);
        string token;
        while (getline(ss, token, delimiter)) {
            // Order matters; using short circuit concept.
            if(!escape_if_empty || token.length() != 0) {
                splitted_tokens.push_back(token);
            }
        }
    }

    vector<string> split(const string &s, char delimiter, bool escape_if_empty) {
        vector<string> splitted_tokens;
        split_(s, delimiter, splitted_tokens, escape_if_empty);
        return splitted_tokens;
    }

    void trim_left_(string &s) {
        int i = 0;
        int len = s.length();
        while(i != len && s[i] == ' ') ++i;
        s = s.substr(i);
    }

    void trim_right_(string &s) {
        int i = s.length() - 1;
        while(i != -1 && s[i] == ' ') --i;
        s = s.substr(0, i + 1);
    }

    // Changes the passed string.
    void trim_(string &s) {
        trim_right_(s);
        trim_left_(s);
    }
}

#endif //JAVACOMPILER_PARSINGFUNCTIONS_H
