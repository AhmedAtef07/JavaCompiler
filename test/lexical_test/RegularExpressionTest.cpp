//
// Created by ahmedatef on 4/16/16.
//

#include "gtest/gtest.h"
#include "RegularExpression.h"


TEST(ReGernerateRegularDefinition, Creation) {
    RegularExpression * re = new RegularExpression();
    re->addRule("letter = a-z");
    EXPECT_TRUE(re->regular_definetions_.count("letter"));
}

TEST(ReGernerateRegularDefinition, GroupOfSymbols) {
    RegularExpression * re = new RegularExpression();
    re->addRule("letter = a-c");
    EXPECT_EQ(re->regular_definetions_.at("letter"), "(a|b|c)");
}

TEST(ReGernerateRegularDefinition, ConcatenatingSymbolAndGroupOfSymbols) {
    RegularExpression * re = new RegularExpression();
    re->addRule("letter = ea-c");
    EXPECT_EQ(re->regular_definetions_.at("letter"), "e(a|b|c)");
}

TEST(ReGernerateRegularDefinition, OrTwoSymbols) {
    RegularExpression * re = new RegularExpression();
    re->addRule("letter = a|b");
    EXPECT_EQ(re->regular_definetions_.at("letter"), "a|b");
}

TEST(ReGernerateRegularDefinition, OrSymbolAndGroupOfSymbols) {
    RegularExpression * re = new RegularExpression();
    re->addRule("letter = a|(a|b)");
    EXPECT_EQ(re->regular_definetions_.at("letter"), "a|(a|b)");
}

TEST(ReGernerateRegularDefinition, OrSymbolAndDefinition) {
    RegularExpression * re = new RegularExpression();
    re->addRule("digit = 0-3");
    re->addRule("digits = a|digit");
    EXPECT_EQ(re->regular_definetions_.at("digits"), "a|((0|1|2|3))");
}

TEST(ReGernerateRegularDefinition, OrDefinitionAndSymbol) {
    RegularExpression * re = new RegularExpression();
    re->addRule("digit = 0-3");
    re->addRule("digits = digit|a");
    EXPECT_EQ(re->regular_definetions_.at("digits"), "((0|1|2|3))|a");
}

TEST(ReGernerateRegularDefinition, ConcatenatingTwoOrMoreSymbols) {
    RegularExpression * re = new RegularExpression();
    re->addRule("digit = 123");
    EXPECT_EQ(re->regular_definetions_.at("digit"), "123");
}

TEST(ReGernerateRegularDefinition, ConcatenatingSymbolAndDefinition) {
    RegularExpression * re = new RegularExpression();
    re->addRule("digit = 0-3");
    re->addRule("digits = edigit");
    EXPECT_EQ(re->regular_definetions_.at("digits"), "e((0|1|2|3))");
}

TEST(ReGernerateRegularDefinition, ConcatenatingDefinitionAndSymbol) {
    RegularExpression * re = new RegularExpression();
    re->addRule("digit = 0-3");
    re->addRule("digits = digite");
    EXPECT_EQ(re->regular_definetions_.at("digits"), "((0|1|2|3))e");
}

TEST(ReGernerateRegularDefinition, EscapeCharacter) {
    RegularExpression * re = new RegularExpression();
    re->addRule("equals = \=\=");
    EXPECT_EQ(re->regular_definetions_.at("equals"), "==");
    re->addRule("mul = \*");
    EXPECT_EQ(re->regular_definetions_.at("mul"), "\*");
}

TEST(ReGernerateRegularDefinition, DefinedByAnotherRegularDefinition) {
    RegularExpression * re = new RegularExpression();
    re->addRule("digit = 0-3");
    re->addRule("digits = digit");
    EXPECT_EQ(re->regular_definetions_.at("digits"), "((0|1|2|3))");
}


TEST(ReKeywords, Creation) {
    RegularExpression * re = new RegularExpression();
    re->addRule("{for while}");
    EXPECT_EQ(*(re->keywords.find("for")), "for");
    EXPECT_EQ(*(re->keywords.find("while")), "while");
    EXPECT_EQ(re->keywords.size(), 2);
}


TEST(RePunctuations, Creation) {
    RegularExpression * re = new RegularExpression();
    re->addRule("[; , \( \) { }]");
    EXPECT_EQ(*(re->punctuations.find(";")), ";");
    EXPECT_EQ(*(re->punctuations.find("\(")), "\(");
    cout << re->punctuations.size() << endl;
    EXPECT_EQ(re->punctuations.size(), 6);
}