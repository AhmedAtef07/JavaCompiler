//
// Created by ahmedatef on 4/15/16.
//

#ifndef STRING_PARSER_REGULARDEFINITION_H
#define STRING_PARSER_REGULARDEFINITION_H

#include <string>
#include "Nfa.h"

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

    string GetOperation();
    Nfa * GetNfa();

    string ToString();

    static bool IsOperation(char c);
};


#endif //STRING_PARSER_REGULARDEFINITION_H
