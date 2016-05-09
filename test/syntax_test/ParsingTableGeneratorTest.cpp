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
        }
        cout << endl;
    }
    cout << endl;

    cout << "follows: " << ptg->follows.size() << endl;
    for(set<string> s : ptg->follows) {
        for(string st : s) {
            cout << st << "  ";
        }
        cout << endl;
    }
    cout << endl;
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
        }
        cout << endl;
    }
    cout << endl;

    cout << "follows: " << endl;
    for(set<string> s : ptg->follows) {
        for(string st : s) {
            cout << st << "  ";
        }
        cout << endl;
    }
    cout << endl;
}