//
// Created by ramytamer on 4/18/16.
//

#include <Nfa.h>
#include <Visualiser.h>
#include <fstream>
#include <Token.h>
#include <Dfa.h>
#include "gtest/gtest.h"

TEST(VisualiserNfaToJson, BasicConcatenation) {
    Nfa* nfa = Nfa::Solver(RegularDefinition::Tokenize("abcd"));

    // cout << Visualiser::JsonFromNfa(nfa_or_abcd) << endl;
    ofstream outjson("outjson.json");
    outjson << Visualiser::JsonFromNfa(nfa);
    outjson.close();


    cout << Visualiser::JsonFromNfa(nfa) << endl;
}

TEST(VisualiserNFAToJson, BasicStar) {
    Nfa* nfa = Nfa::Solver(RegularDefinition::Tokenize("a*"));

    // cout << Visualiser::JsonFromNfa(nfa_or_abcd) << endl;
    ofstream outjson("outjson.json");
    outjson << Visualiser::JsonFromNfa(nfa);
    outjson.close();


    cout << Visualiser::JsonFromNfa(nfa) << endl;
}

TEST(VisualiserDfaToJson, BasicStar) {
    Nfa* nfa = Nfa::Solver(RegularDefinition::Tokenize("a*"));
    Dfa* dfa = new Dfa(nfa, new Token("a*", 50));

    // cout << Visualiser::JsonFromNfa(nfa_or_abcd) << endl;
    ofstream outjson("outjson.json");
    outjson << Visualiser::JsonFromDfa(dfa);
    outjson.close();

}

TEST(VisualiserDfaToJson, BasicPlus) {
    Nfa* nfa = Nfa::Solver(RegularDefinition::Tokenize("a+"));
    Dfa* dfa = new Dfa(nfa, new Token("a+", 500));

    // cout << Visualiser::JsonFromNfa(nfa_or_abcd) << endl;
    ofstream outjson("outjson.json");
    outjson << Visualiser::JsonFromDfa(dfa);
    outjson.close();
}