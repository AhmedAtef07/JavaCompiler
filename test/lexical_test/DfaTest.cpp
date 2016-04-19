//
// Created by Ahmed Barakat on 107 / 16 / 16.
//

#include <Nfa.h>
#include <Dfa.h>
#include <Lexical.h>
#include "gtest/gtest.h"

TEST(DfaTest, BasicCreation) {
    cout << endl;
    Nfa *n = Nfa::Solver(RegularDefinition::Tokenize("int"));
//    Nfa *n = Nfa::Solver(RegularDefinition::Tokenize("int"));

//    Dfa *dfa = new Dfa(n, new Token("i", 77));
//
//    cout << n->ToString() << endl;
//    cout << dfa->ToString(false) << endl;

    //    "b+|a+b+"
//    Nfa *nfa_a3 = new Nfa("a");
//    Nfa *nfa_b4 = new Nfa("b");
//    Nfa *nfa_b5 = new Nfa("b");
//
//    Nfa *nfa_aa3 = Nfa::Plus(nfa_a3);
//    Nfa *nfa_bb3 = Nfa::Plus(nfa_b4);
//    Nfa *nfa_bb5 = Nfa::Plus(nfa_b5);
//    Nfa *nfa_aabb2 = Nfa::Concatenate(nfa_aa3, nfa_bb3);
//    Nfa *nfa_abaabb2 = Nfa::Parallel(nfa_bb5, nfa_aabb2);
//    Dfa *dfa3 = new Dfa(nfa_abaabb2, new Token("b+|a+b+", 72));
//
//    cout << nfa_abaabb2->ToString() << endl;
//    cout << dfa3->ToString(true) << endl;

//    cout << endl << n->ToString() << endl;
//    cout << endl << dfa->ToString(true) << endl;

//    Lexical *l = new Lexical();
//    l->AddDfa(Nfa::Solver(RegularDefinition::Tokenize("int")), new Token("i", 77));
//    l->AddDfa(Nfa::Solver(RegularDefinition::Tokenize("\\+|\\-")), new Token("i", 77));
//    Lexical::Output out = l->ParseInput("ahmed");
//    cout << endl << "TT" << out.tokens.size() << endl;
}


TEST(DfaGeneratorFromRegularDefinition, SingleThenStar) {
    string sample = "ba*";
    Dfa* dfa = new Dfa(Nfa::Solver(RegularDefinition::Tokenize(sample)), new Token("ba*", 64531));
//    cout << dfa->ToString(false) << endl;
}
