//
// Created by ahmedatef on 4/15/16.
//

#include "RegularDefinition.h"

const string RegularDefinition::allowed_operations = "()*+|";

RegularDefinition::RegularDefinition(RegularDefinition::Type type, void *value) {
    this->type = type;
    this->value = value;
}

bool RegularDefinition::IsOperation(char c) {
    return allowed_operations.find(c) != string::npos;
}

string RegularDefinition::GetOperation() {
    return *static_cast<std::string*>(this->value);
    try {
        throw -1;
    } catch (int e) {
        cout << "No Operation. Exception Nr. " << e << '\n';
    }
}

Nfa* RegularDefinition::GetNfa() {
    return static_cast<Nfa*>(this->value);
}

string RegularDefinition::ToString() {
    std::string *pstr = new std::string;
    *pstr = (this->type) == RegularDefinition::kNfa ? "NFA" : "Operation";
    *pstr += ": ";
    if(this->type == RegularDefinition::kNfa) {
        return *pstr + GetNfa()->start_state->outgoing_transitions[0]->value;
    } else {
        return *pstr + GetOperation();
    }
}