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

    cout << endl << "grammer:" << endl;
    for(string s : cfg->string_rules) {
        cout << s << endl;
    }

    string modified_grammer = "";
    string expected_modified_grammer = "METHOD_BODY = STATEMENT_LIST\n"
            "STATEMENT_LIST = STATEMENT STATEMENT_LIST''\n"
            "STATEMENT_LIST'' = STATEMENT STATEMENT_LIST'' | \n"
            "STATEMENT = DECLARATION | IF | WHILE | ASSIGNMENT\n"
            "DECLARATION = PRIMITIVE_TYPE id ;\n"
            "IF = if ( EXPRESSION ) { STATEMENT } else { STATEMENT }\n"
            "WHILE = while ( EXPRESSION ) { STATEMENT }\n"
            "ASSIGNMENT = id = EXPRESSION ;\n"
            "PRIMITIVE_TYPE = int | float\n"
            "EXPRESSION = SIMPLE_EXPRESSION EXPRESSION'''\n"
            "SIMPLE_EXPRESSION = TERM SIMPLE_EXPRESSION'' | SIGN TERM SIMPLE_EXPRESSION''\n"
            "SIMPLE_EXPRESSION'' = addop TERM SIMPLE_EXPRESSION'' | \n"
            "TERM = FACTOR TERM''\n"
            "TERM'' = mulop FACTOR TERM'' | \n"
            "SIGN = + | -\n"
            "FACTOR = id | num | ( EXPRESSION )\n"
            "EXPRESSION''' = relop SIMPLE_EXPRESSION | \n";

    cout << endl << "modified grammer:" << endl;
    for(GrammarRule *r : cfg->rules) {
        cout << r->name << " = ";
        modified_grammer += r->name + " = ";
        for(int i = 0; i < r->productions.size(); ++i) {
            for(int j = 0; j < r->productions[i].size(); ++j) {
                cout << r->productions[i][j]->name << ((j + 1) == r->productions[i].size()? "":" ");
                modified_grammer += r->productions[i][j]->name + ((j + 1) == r->productions[i].size()? "":" ");
            }
            cout << ((i + 1) == r->productions.size()? "":" | ");
            modified_grammer += ((i + 1) == r->productions.size()? "":" | ");
        }
        cout << endl;
        modified_grammer += "\n";
    }

//    EXPECT_EQ(modified_grammer, expected_modified_grammer);
}
