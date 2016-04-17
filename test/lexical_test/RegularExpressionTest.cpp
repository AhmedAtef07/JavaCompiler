//
// Created by ahmedatef on 4/16/16.
//

#include "gtest/gtest.h"
#include "RegularExpression.h"


TEST(generate_regular_definition, created) {
    RegularExpression * re = new RegularExpression();
    re->addRule("letter = a-z");
    EXPECT_TRUE(re->regular_definetions_.count("letter"));
}

TEST(generate_regular_definition, group_of_symbols) {
    RegularExpression * re = new RegularExpression();
    re->addRule("letter = a-c");
    EXPECT_EQ(re->regular_definetions_.at("letter"), "(a|b|c)");
}

TEST(generate_regular_definition, concatenating_symbol_andgroup_of_symbols) {
    RegularExpression * re = new RegularExpression();
    re->addRule("letter = ea-c");
    EXPECT_EQ(re->regular_definetions_.at("letter"), "e(a|b|c)");
}

TEST(generate_regular_definition, or_two_symbols) {
    RegularExpression * re = new RegularExpression();
    re->addRule("letter = a|b");
    EXPECT_EQ(re->regular_definetions_.at("letter"), "a|b");
}

TEST(generate_regular_definition, or_symbol_and_group_of_symbols) {
    RegularExpression * re = new RegularExpression();
    re->addRule("letter = a|(a|b)");
    EXPECT_EQ(re->regular_definetions_.at("letter"), "a|(a|b)");
}

TEST(generate_regular_definition, or_symbol_and_definition) {
    RegularExpression * re = new RegularExpression();
    re->addRule("digit = 0-3");
    re->addRule("digits = a|digit");
    EXPECT_EQ(re->regular_definetions_.at("digits"), "a|((0|1|2|3))");
}

TEST(generate_regular_definition, or_definition_and_symbol) {
    RegularExpression * re = new RegularExpression();
    re->addRule("digit = 0-3");
    re->addRule("digits = digit|a");
    EXPECT_EQ(re->regular_definetions_.at("digits"), "((0|1|2|3))|a");
}

TEST(generate_regular_definition, concatenating_two_or_more_symbols) {
    RegularExpression * re = new RegularExpression();
    re->addRule("digit = 123");
    EXPECT_EQ(re->regular_definetions_.at("digit"), "123");
}

TEST(generate_regular_definition, concatenating_symbol_and_definition) {
    RegularExpression * re = new RegularExpression();
    re->addRule("digit = 0-3");
    re->addRule("digits = edigit");
    EXPECT_EQ(re->regular_definetions_.at("digits"), "e((0|1|2|3))");
}

TEST(generate_regular_definition, concatenating_definition_and_symbol) {
    RegularExpression * re = new RegularExpression();
    re->addRule("digit = 0-3");
    re->addRule("digits = digite");
    EXPECT_EQ(re->regular_definetions_.at("digits"), "((0|1|2|3))e");
}

TEST(generate_regular_definition, escape_character) {
    RegularExpression * re = new RegularExpression();
    re->addRule("equals = \=\=");
    EXPECT_EQ(re->regular_definetions_.at("equals"), "==");
    re->addRule("mul = \*");
    EXPECT_EQ(re->regular_definetions_.at("mul"), "\*");
}

TEST(generate_regular_definition, defined_by_another_regular_definition) {
    RegularExpression * re = new RegularExpression();
    re->addRule("digit = 0-3");
    re->addRule("digits = digit");
    EXPECT_EQ(re->regular_definetions_.at("digits"), "((0|1|2|3))");
}


TEST(keywords, keyword_generation) {
    RegularExpression * re = new RegularExpression();
    re->addRule("{for while}");
    EXPECT_EQ(*(re->keywords.find("for")), "for");
    EXPECT_EQ(*(re->keywords.find("while")), "while");
    EXPECT_EQ(re->keywords.size(), 2);
}


TEST(punctuations, punctuations_generation) {
    RegularExpression * re = new RegularExpression();
    re->addRule("[; , \( \) { }]");
    EXPECT_EQ(*(re->punctuations.find(";")), ";");
    EXPECT_EQ(*(re->punctuations.find("\(")), "\(");
    cout << re->punctuations.size() << endl;
    EXPECT_EQ(re->punctuations.size(), 6);
}