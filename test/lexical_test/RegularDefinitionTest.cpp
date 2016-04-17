//
// Created by ahmedatef on 4/16/16.
//

#include <RegularDefinition.h>
#include <stack>
#include "gtest/gtest.h"

string* make_str_pointer_(string s) {
    std::string *pstr = new std::string;
    *pstr = s;
    return pstr;
}

TEST(RegularDefinition, Creation) {
    string test = "(a*(k|l|(mn|k))*l)+";
    vector<RegularDefinition *> regular_definition_vector;
    for(int i = 0; i < test.size(); ++i) {
        std::string *pstr = new std::string;
        *pstr = test[i];

        if(RegularDefinition::IsOperation(test[i])) {
            regular_definition_vector.push_back(new RegularDefinition(RegularDefinition::Type::kOperation,
                                                                      pstr));
        } else {
            regular_definition_vector.push_back(new RegularDefinition(RegularDefinition::Type::kNfa, new Nfa(*pstr)));
        }
    }


    for(RegularDefinition *rd: regular_definition_vector) {
        cout << rd->ToString() << endl;
    }
}

TEST(RegularDefinition, EqualOperator) {
    // The overriding operator is not passing.
    RegularDefinition* rd_open_1 = new RegularDefinition(RegularDefinition::kOperation, make_str_pointer_("("));

    RegularDefinition* rd_open_2 = new RegularDefinition(RegularDefinition::kOperation, make_str_pointer_("("));
    cout << endl << endl << rd_open_1->GetOperation() << " hhhhhhhhhhhhhhhhhhhhhhhh " <<
            rd_open_2->GetOperation() << " " << (rd_open_1->GetOperation() == rd_open_2->GetOperation()) << endl;
    EXPECT_TRUE(rd_open_1==rd_open_2);

    RegularDefinition* rd_close_1 = new RegularDefinition(RegularDefinition::kOperation, make_str_pointer_(")"));
    EXPECT_FALSE(rd_open_1 == rd_close_1);

    RegularDefinition* rd_nfa = new RegularDefinition(RegularDefinition::kNfa, NULL);
    EXPECT_FALSE(rd_close_1 == rd_nfa);
    
}
