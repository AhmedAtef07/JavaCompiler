//
// Created by ahmedatef on 4/16/16.
//

#include "gtest/gtest.h"
#include "RegularExpression.h"
#include "RegularDefinition.h"

TEST(Magdy, Atef) {
    EXPECT_EQ(7, 7);
}

TEST(RegularExpression, TestName) {
    RegularExpression * re = new RegularExpression("/home/ahmedatef/ClionProjects/JavaCompiler/lexical/lexical_input.txt");
    EXPECT_EQ(re->regular_definetions.at("letter"),
              "(a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z)|"
                      "(A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z)");
}

TEST(RegularDefinition, _1) {
    string o1 = string("a");
    RegularDefinition* rd1 = new RegularDefinition(RegularDefinition::Type::kNfa, new Nfa(o1));
    cout << rd1->value << endl;
}