//
// Created by Ahmed Barakat on 108 / 17 / 16.
//

#ifndef JAVACOMPILER_TOKEN_H
#define JAVACOMPILER_TOKEN_H

#include <string>
#include <set>

using namespace std;

class Token {

public:

    int priority;
    string name;
    string pattern;

    Token(string name, int priority);
    void delete_token();

private:

    static set<int> priorities;

};

#endif //JAVACOMPILER_TOKEN_H
