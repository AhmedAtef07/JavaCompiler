//
// Created by ahmedatef on 5/3/16.
//

#include <ContextFreeGrammar.h>
#include <ParsingTableGenerator.h>
#include <Token.h>
#include "gtest/gtest.h"

TEST(ParsingTableCalculatingFirsts, SimpleFirst) {
    string grammar = ""
            "# A = 'id'\n"
            "# B = A | '(' ')'";

    ContextFreeGrammar *cfg = new ContextFreeGrammar();
    cfg->AddRulesFromString(grammar);

    ParsingTableGenerator* ptg = new ParsingTableGenerator(cfg->unmodified_rules);

    cout << endl;

    cout << "firsts: " << endl;
    for(vector<set<string>> v : ptg->firsts) {
        for(set<string> s : v) {
            for(string st : s) {
                cout << st << "  ";
            }
            cout << " '|' ";
        }
        cout << endl;
    }
    cout << endl;
    set<string> s1, s2, s3;
    s1.insert("id");
    s2.insert("id");
    s3.insert("(");
    vector<set<string>> v1 = {s1};
    vector<set<string>> v2 = {s2, s3};
    vector<vector<set<string>>> v3 = {v1, v2};
    EXPECT_EQ(v3, ptg->firsts);

    cout << "follows: " << ptg->follows.size() << endl;
    for(set<string> s : ptg->follows) {
        for(string st : s) {
            cout << st << "  ";
        }
        cout << endl;
    }
    cout << endl;
    set<string> s4;
    s4.insert("\\$");
    set<string> s5;
    vector<set<string>> v4 = {s4, s5};
    EXPECT_EQ(v4, ptg->follows);
}

TEST(ParsingTableCalculatingFirstsAndTable, SimpleFirst) {
    string grammar = ""
            "# A = B C\n"
            "# B = 'int' | 'float'\n"
            "# C = 'id'";

    GrammarRule *A = new GrammarRule();
    A->name = "A";
    Symbol *A_symbol = new Symbol(A);

    GrammarRule *B = new GrammarRule();
    B->name = "B";
    Symbol *B_symbol = new Symbol(B);

    GrammarRule *C = new GrammarRule();
    C->name = "C";
    Symbol *C_symbol = new Symbol(C);

    Symbol *id_symbol = new Symbol("id");
    Symbol *int_symbol = new Symbol("int");
    Symbol *float_symbol = new Symbol("float");
    vector<Symbol*> temp_1 = {B_symbol, C_symbol};
    vector<Symbol*> temp_11 = {C_symbol, B_symbol};
    vector<Symbol*> temp_2 = {int_symbol};
    vector<Symbol*> temp_3 = {float_symbol};
    vector<Symbol*> temp_4 = {id_symbol};
    A->productions.push_back(temp_1);
//    A->productions.push_back(temp_11);
    B->productions.push_back(temp_2);
    B->productions.push_back(temp_3);
    C->productions.push_back(temp_4);

    vector<GrammarRule*> rules = {A, B, C};

    ParsingTableGenerator* ptg = new ParsingTableGenerator(rules);

    cout << "firsts: " << endl;
    for(vector<set<string>> &v : ptg->firsts) {
        for(set<string> s : v) {
            for(string st : s) {
                cout << st << "  ";
            }
            cout << " '|' ";
        }
        cout << endl;
    }
    cout << endl;
    set<string> s1, s2, s3, s4;
    s1.insert("float");
    s1.insert("int");
    s2.insert("int");
    s3.insert("float");
    s4.insert("id");
    vector<set<string>> v1 = {s1};
    vector<set<string>> v2 = {s2, s3};
    vector<set<string>> v3 = {s4};
    vector<vector<set<string>>> v4 = {v1, v2, v3};
    EXPECT_EQ(v4, ptg->firsts);

    cout << "follows: " << endl;
    for(set<string> s : ptg->follows) {
        for(string st : s) {
            cout << st << "  ";
        }
        cout << endl;
    }
    cout << endl;
    set<string> s5, s6;
    s5.insert("\\$");
    s6.insert("id");
    vector<set<string>> v5 = {s5, s6, s5};
    EXPECT_EQ(v5, ptg->follows);
}