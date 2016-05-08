//
// Created by Ahmed Barakat on 129 / 8 / 16.
//

#include <ContextFreeGrammar.h>
#include <ParsingTableGenerator.h>
#include <PredictiveParser.h>
#include <Lexical.h>
#include "gtest/gtest.h"

TEST(PredectiveParserGenerater, GeneratingObject) {
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

    cout << endl;
    cout << A_symbol->type << endl;
    cout << int_symbol->type << endl;

    vector<GrammarRule*> rules = {A, B, C};

    cout << rules[0]->productions[0][1]->grammar_rule << endl;
    cout << rules[2] << endl;
    cout << int_symbol->type << endl;
    cout << endl;

    ParsingTableGenerator* ptg = new ParsingTableGenerator(rules);

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

    cout << "follows: " << endl;
    for(set<string> s : ptg->follows) {
        for(string st : s) {
            cout << st << "  ";
        }
        cout << endl;
    }
    cout << endl;

    for(string s : ptg->terminals) {
        cout << s << endl;
    }
    cout << endl;

    PredictiveParser *pp = new PredictiveParser(ptg->table, ptg->terminals, ptg->rules_as_names);


    Token *t1 = new Token("int", 1);
    Token *t2 = new Token("id", 2);

    vector<Token*> v;
    v.push_back(t1);
    v.push_back(t2);

    if(pp->parse(v)) {
        cout << "succedded" << endl;
    }
}