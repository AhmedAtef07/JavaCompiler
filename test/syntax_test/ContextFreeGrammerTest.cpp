//
// Created by ahmedatef on 5/2/16.
//

#include "gtest/gtest.h"
#include "ContextFreeGrammar.h"

TEST(ContextFreeGrammar, ParsingCfgStringRulesFromStringWithExtraSpacesAndHiddenChars) {
    string grammar = ""
            "       # METHOD_BODY    =    STATEMENT_LIST\n"
            "# STATEMENT_LIST   = STATEMENT |    \t\t  STATEMENT_LIST STATEMENT\n"
            "# STATEMENT = DECLARATION\n"
            "   |    IF\n\n\n"
            "| WHILE\n\r"
            "    |   ASSIGNMENT\n"
            "# SIGN = '+' |         '-'";

    ContextFreeGrammar *cfg = new ContextFreeGrammar();
    cfg->AddRulesFromString(grammar);

    vector<string> grammar_tokenized = {
            "METHOD_BODY = STATEMENT_LIST",
            "STATEMENT_LIST = STATEMENT | STATEMENT_LIST STATEMENT",
            "STATEMENT = DECLARATION | IF | WHILE | ASSIGNMENT",
            "SIGN = '+' | '-'"
    };

    EXPECT_EQ(cfg->string_rules, grammar_tokenized);
}

TEST(ContextFreeGrammar, ParsingCfgStringRulesFromString) {
    string grammar = ""
            "# METHOD_BODY = STATEMENT_LIST\n"
            "# STATEMENT_LIST = STATEMENT | STATEMENT_LIST STATEMENT\n"
            "# STATEMENT = DECLARATION\n"
            "| IF\n"
            "| WHILE\n"
            "| ASSIGNMENT\n"
            "# DECLARATION = PRIMITIVE_TYPE 'id' ';'\n"
            "# PRIMITIVE_TYPE = 'int' | 'float'\n"
            "# IF = 'if' '(' EXPRESSION ')' '{' STATEMENT '}' 'else' '{' STATEMENT '}'\n"
            "# WHILE = 'while' '(' EXPRESSION ')' '{' STATEMENT '}'\n"
            "# ASSIGNMENT = 'id' '=' EXPRESSION ';'\n"
            "# EXPRESSION = SIMPLE_EXPRESSION\n"
            "| SIMPLE_EXPRESSION 'relop' SIMPLE_EXPRESSION\n"
            "# SIMPLE_EXPRESSION = TERM | SIGN TERM | SIMPLE_EXPRESSION 'addop' TERM\n"
            "# TERM = FACTOR | TERM 'mulop' FACTOR\n"
            "# FACTOR = 'id' | 'num' | '(' EXPRESSION ')' # SIGN = '+' | '-'";

    ContextFreeGrammar *cfg = new ContextFreeGrammar();
    cfg->AddRulesFromString(grammar);

    vector<string> grammar_tokenized = {
            "METHOD_BODY = STATEMENT_LIST",
            "STATEMENT_LIST = STATEMENT | STATEMENT_LIST STATEMENT",
            "STATEMENT = DECLARATION | IF | WHILE | ASSIGNMENT",
            "DECLARATION = PRIMITIVE_TYPE 'id' ';'",
            "PRIMITIVE_TYPE = 'int' | 'float'",
            "IF = 'if' '(' EXPRESSION ')' '{' STATEMENT '}' 'else' '{' STATEMENT '}'",
            "WHILE = 'while' '(' EXPRESSION ')' '{' STATEMENT '}'",
            "ASSIGNMENT = 'id' '=' EXPRESSION ';'",
            "EXPRESSION = SIMPLE_EXPRESSION | SIMPLE_EXPRESSION 'relop' SIMPLE_EXPRESSION",
            "SIMPLE_EXPRESSION = TERM | SIGN TERM | SIMPLE_EXPRESSION 'addop' TERM",
            "TERM = FACTOR | TERM 'mulop' FACTOR",
            "FACTOR = 'id' | 'num' | '(' EXPRESSION ')'",
            "SIGN = '+' | '-'"
    };

    EXPECT_EQ(cfg->string_rules, grammar_tokenized);
}

TEST(ContextFreeGrammar, ParsingGrammarRule) {
    string grammar = ""
            "# STATEMENT_LIST  = STATEMENT | STATEMENT_LIST STATEMENT\n"
            "# SIGN = '+' | '-'";

    ContextFreeGrammar *cfg = new ContextFreeGrammar();
    cfg->AddRulesFromString(grammar);

    EXPECT_EQ(cfg->rules[0]->name, "STATEMENT_LIST");
    EXPECT_EQ(cfg->rules[0]->productions[0][0]->name, "STATEMENT");
    EXPECT_EQ(cfg->rules[0]->productions[1][0]->name, "STATEMENT_LIST");
    EXPECT_EQ(cfg->rules[0]->productions[1][1]->name, "STATEMENT");

    EXPECT_EQ(cfg->rules[1]->name, "SIGN");
    EXPECT_EQ(cfg->rules[1]->productions[0][0]->name, "+");
    EXPECT_EQ(cfg->rules[1]->productions[1][0]->name, "-");
}
