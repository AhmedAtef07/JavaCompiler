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
//    string m1 = "dsfsadf";
//    string m2 = (this->type) == RegularDefinition::kNfa ? "NFA" : "Operation";
//    string m3 = ": ";
//    string m4 = "";
    cout << GetOperation() << endl;
    if(this->type == RegularDefinition::kNfa) {
        return GetNfa()->start_state->outgoing_transitions[0]->value;
    } else {
        return GetOperation();
    }
    // return m1 + m2 + m3 + m4;
}