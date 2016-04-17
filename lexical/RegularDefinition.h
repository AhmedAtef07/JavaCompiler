//
// Created by ahmedatef on 4/15/16.
//

#ifndef STRING_PARSER_REGULARDEFINITION_H
#define STRING_PARSER_REGULARDEFINITION_H

#include <string>
#include "Nfa.h"

class Nfa;

using namespace std;

class RegularDefinition {
public:
    enum Type {
        kNfa,
        kOperation,
    };

    const static string allowed_operations;

    Type type;
    void* value;

    RegularDefinition(Type type, void *value);

    string GetOperation() const;
    Nfa * GetNfa();

    string ToString();

    bool inline operator==(const RegularDefinition& rd);

    static bool IsOperation(char c);

    static vector<RegularDefinition *> Tokenize(string re);
};


#endif //STRING_PARSER_REGULARDEFINITION_H
