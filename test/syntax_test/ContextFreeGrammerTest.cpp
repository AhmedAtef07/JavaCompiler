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

    EXPECT_EQ(cfg->FindExistingGrammarRule("STATEMENT_LIST")->name, "STATEMENT_LIST");
    EXPECT_EQ(cfg->FindExistingGrammarRule("STATEMENT_LIST")->productions[0][0]->name, "STATEMENT");
    EXPECT_EQ(cfg->FindExistingGrammarRule("STATEMENT_LIST")->productions[1][0]->name, "STATEMENT_LIST");
    EXPECT_EQ(cfg->FindExistingGrammarRule("STATEMENT_LIST")->productions[1][1]->name, "STATEMENT");

    EXPECT_EQ(cfg->FindExistingGrammarRule("SIGN")->name, "SIGN");
    EXPECT_EQ(cfg->FindExistingGrammarRule("SIGN")->productions[0][0]->name, "+");
    EXPECT_EQ(cfg->FindExistingGrammarRule("SIGN")->productions[1][0]->name, "-");
}

TEST(ContextFreeGrammar, ParsingGrammarRuleWithEscapeChar) {
    string grammar = "     "
            "# STATEMENT_LIST  = '\\'' '\\|' | '\\|' '\\+' STATEMENT | STATEMENT_LIST STATEMENT '\\'ahmed\\''";

    ContextFreeGrammar *cfg = new ContextFreeGrammar();
    cfg->AddRulesFromString(grammar);

    EXPECT_EQ(cfg->unmodified_rules[0]->name, "STATEMENT_LIST");
    EXPECT_EQ(cfg->unmodified_rules[0]->productions[0][0]->name, "\\'");
    EXPECT_EQ(cfg->unmodified_rules[0]->productions[0][1]->name, "\\|");

    EXPECT_EQ(cfg->unmodified_rules[0]->productions[1][0]->name, "\\|");
    EXPECT_EQ(cfg->unmodified_rules[0]->productions[1][1]->name, "\\+");
    EXPECT_EQ(cfg->unmodified_rules[0]->productions[1][2]->name, "STATEMENT");

    EXPECT_EQ(cfg->unmodified_rules[0]->productions[2][0]->name, "STATEMENT_LIST");
    EXPECT_EQ(cfg->unmodified_rules[0]->productions[2][1]->name, "STATEMENT");
    EXPECT_EQ(cfg->unmodified_rules[0]->productions[2][2]->name, "\\'ahmed\\'");
}

TEST(ContextFreeGrammar, ParsingGrammarWishTailingDashes) {
    string grammar = ""
            "# STATEMENT_LIST'' = STATEMENT' | STATEMENT_LIST STATEMENT\n"
            "# SIGN = '+' | '-'";

    ContextFreeGrammar *cfg = new ContextFreeGrammar();
    cfg->AddRulesFromString(grammar);

    vector<string> grammar_tokenized = {
            "STATEMENT_LIST'' = STATEMENT' | STATEMENT_LIST STATEMENT",
            "SIGN = '+' | '-'"
    };


    EXPECT_EQ(cfg->string_rules, grammar_tokenized);
}

TEST(ContextFreeGrammar, CheckGrammarRulesReferencing) {
    string grammar = ""
            "# METHOD_BODY = STATEMENT_LIST\n"
            "# STATEMENT_LIST = STATEMENT | STATEMENT_LIST STATEMENT\n"
            "# SIGN = '*'\n"
            "# EQUATION = SIGN"
            "# STATEMENT = DECELERATION\n";

    ContextFreeGrammar *cfg = new ContextFreeGrammar();
    cfg->AddRulesFromString(grammar);

    // Comparing Names.
    EXPECT_EQ(cfg->FindExistingGrammarRule("METHOD_BODY")->productions[0][0]->name, cfg->unmodified_rules[1]->name);
    EXPECT_EQ(cfg->FindExistingGrammarRule("METHOD_BODY")->productions[0][0]->name,
              cfg->FindExistingGrammarRule("STATEMENT_LIST")->name);

    EXPECT_EQ(cfg->FindExistingGrammarRule("STATEMENT_LIST")->productions[0][0]->name,
              cfg->FindExistingGrammarRule("STATEMENT_LIST")->productions[1][1]->name);

    // Comparing References.

    // 'STATEMENT_LIST'
    EXPECT_EQ(cfg->FindExistingGrammarRule("METHOD_BODY")->productions[0][0]->grammar_rule,
              cfg->FindExistingGrammarRule("STATEMENT_LIST"));

    EXPECT_EQ(cfg->FindExistingGrammarRule("METHOD_BODY")->productions[0][0]->grammar_rule, cfg->unmodified_rules[1]);

    // 'STATEMENT'
    EXPECT_EQ(cfg->FindExistingGrammarRule("STATEMENT_LIST")->productions[0][0]->grammar_rule,
              cfg->FindExistingGrammarRule("STATEMENT_LIST")->productions[1][1]->grammar_rule);

    // 'SIGN'
    EXPECT_EQ(cfg->FindExistingGrammarRule("EQUATION")->productions[0][0]->grammar_rule,
              cfg->FindExistingGrammarRule("SIGN"));
}

TEST(ContextFreeGrammar, ParsingOutputTokens) {
    string grammar = ""
            "# A = 'id'\n"
            "# B = A | '(' ')'";

    ContextFreeGrammar *cfg = new ContextFreeGrammar();
    cfg->AddRulesFromString(grammar);

    EXPECT_EQ(cfg->FindExistingGrammarRule("A")->name, "A");
    EXPECT_EQ(cfg->FindExistingGrammarRule("A")->productions[0][0]->name, "id");

    EXPECT_EQ(cfg->FindExistingGrammarRule("B")->name, "B");
    EXPECT_EQ(cfg->FindExistingGrammarRule("B")->productions[0][0]->name, "A");
    EXPECT_EQ(cfg->FindExistingGrammarRule("B")->productions[1][0]->name, "(");

//    for(GrammarRule *gr : cfg->unmodified_rules) {
//        cout << "# " << gr->name << " Number of productions: " <<  gr->productions.size() << endl;
//        for(vector<Symbol*> &v : gr->productions) {
//            cout << "gr.production: " << v.size() << endl;
//            for(Symbol * s : v) {
//                cout << s->type << " " << s->name << " " << s->grammar_rule << endl;
//            }
//            cout << "|" << endl;
//        }
//        cout << endl;
//    }
}

TEST(ContextFreeGrammar, LambdaFormat) {
    string grammar = ""
            "# A = 'id' \n"
            "# B = A | \\L '\\L' \n";

    ContextFreeGrammar *cfg = new ContextFreeGrammar();
    cfg->AddRulesFromString(grammar);

    EXPECT_EQ(cfg->FindExistingGrammarRule("B")->productions[1][0]->name, "\\L");
    EXPECT_EQ(cfg->FindExistingGrammarRule("B")->productions[1][0]->type, Symbol::Type::kTerminal);


    EXPECT_EQ(cfg->FindExistingGrammarRule("B")->productions[1][1]->name, "\\L");
    EXPECT_EQ(cfg->FindExistingGrammarRule("B")->productions[1][1]->type, Symbol::Type::kTerminal);
}

TEST(ContextFreeGrammar, LLGrammarTest) {
    string grammer = "# METHOD_BODY = STATEMENT_LIST\n"
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
    cfg->AddRulesFromString(grammer);

    string modified_grammer = "";
    string expected_modified_grammer = ""
            "# METHOD_BODY = STATEMENT_LIST\n"
            "# STATEMENT_LIST = STATEMENT STATEMENT_LIST''\n"
            "# STATEMENT_LIST'' = STATEMENT STATEMENT_LIST'' | '\\L'\n"
            "# STATEMENT = DECLARATION | IF | WHILE | ASSIGNMENT\n"
            "# DECLARATION = PRIMITIVE_TYPE 'id' ';'\n"
            "# IF = 'if' '(' EXPRESSION ')' '{' STATEMENT '}' 'else' '{' STATEMENT '}'\n"
            "# WHILE = 'while' '(' EXPRESSION ')' '{' STATEMENT '}'\n"
            "# ASSIGNMENT = 'id' '=' EXPRESSION ';'\n"
            "# PRIMITIVE_TYPE = 'int' | 'float'\n"
            "# EXPRESSION = SIMPLE_EXPRESSION EXPRESSION'''\n"
            "# SIMPLE_EXPRESSION = TERM SIMPLE_EXPRESSION'' | SIGN TERM SIMPLE_EXPRESSION''\n"
            "# SIMPLE_EXPRESSION'' = 'addop' TERM SIMPLE_EXPRESSION'' | '\\L'\n"
            "# TERM = FACTOR TERM''\n"
            "# TERM'' = 'mulop' FACTOR TERM'' | '\\L'\n"
            "# SIGN = '+' | '-'\n"
            "# FACTOR = 'id' | 'num' | '(' EXPRESSION ')'\n"
            "# EXPRESSION''' = 'relop' SIMPLE_EXPRESSION | '\\L'\n";

    ContextFreeGrammar *expected_cfg = new ContextFreeGrammar();
    expected_cfg->AddRulesFromString(expected_modified_grammer);

    ASSERT_EQ(cfg->rules.size(), expected_cfg->unmodified_rules.size());

    for(int i = 0, len = cfg->rules.size(); i < len; ++i) {
        ASSERT_EQ(cfg->rules[i]->productions.size(),
                 expected_cfg->FindExistingGrammarRule(cfg->rules[i]->name)->productions.size());
        for(int k = 0; k < cfg->rules[i]->productions.size(); ++k) {
            ASSERT_EQ(cfg->rules[i]->productions[k].size(),
                      expected_cfg->FindExistingGrammarRule(cfg->rules[i]->name)->productions[k].size());
            for(int j = 0; j < cfg->rules[i]->productions[k].size(); ++j) {
                EXPECT_EQ(cfg->rules[i]->productions[k][j]->name,
                          expected_cfg->FindExistingGrammarRule(cfg->rules[i]->name)->productions[k][j]->name);
                EXPECT_EQ(cfg->rules[i]->productions[k][j]->type,
                          expected_cfg->FindExistingGrammarRule(cfg->rules[i]->name)->productions[k][j]->type);
            }
        }

    }
}
