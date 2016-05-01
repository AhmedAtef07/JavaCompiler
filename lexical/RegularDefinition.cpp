//
// Created by ahmedatef on 4/15/16.
//

#include "RegularDefinition.h"

const string RegularDefinition::allowed_operations = "()*+|\\";

RegularDefinition::RegularDefinition(RegularDefinition::Type type, void *value) {
    this->type = type;
    this->value = value;
}

bool RegularDefinition::IsOperation(char c) {
    return allowed_operations.find(c) != string::npos;
}

string RegularDefinition::GetOperation() const {
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

bool inline RegularDefinition::operator==(const RegularDefinition& rd) {
    cout << "hey" << endl;
    if(rd.type == RegularDefinition::kNfa || this->type == RegularDefinition::kNfa) return false;
    return this->GetOperation() == rd.GetOperation();
}

// Accepts regular expression and tokenize it.
vector<RegularDefinition *> RegularDefinition::Tokenize(string re) {
    vector<RegularDefinition *> regular_definition_vector;
    for(int i = 0; i < re.size(); ++i) {
        std::string *pstr = new std::string;
        *pstr = re[i];

        if(RegularDefinition::IsOperation(re[i])) {
            if(re[i] == '\\') {
                if(re[i + 1] == 'L') {
                    regular_definition_vector.push_back(new RegularDefinition(RegularDefinition::kNfa, new Nfa("")));
                } else {
                    *pstr = re[i + 1];
                    regular_definition_vector.push_back(new RegularDefinition(RegularDefinition::kNfa, new Nfa(*pstr)));
                }
                ++i; // Escape next character because it is resolved.
            } else {
                regular_definition_vector.push_back(new RegularDefinition(RegularDefinition::kOperation, pstr));
            }
        } else {
            regular_definition_vector.push_back(new RegularDefinition(RegularDefinition::kNfa, new Nfa(*pstr)));
        }
    }
    return regular_definition_vector;
}