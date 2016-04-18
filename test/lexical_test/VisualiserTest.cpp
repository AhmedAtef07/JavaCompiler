//
// Created by ramytamer on 4/18/16.
//

#include <Nfa.h>
#include <Visualiser.h>
#include <fstream>
#include "gtest/gtest.h"

TEST(Visualiser, NFAToJson) {
    Nfa* nfa_a = new Nfa("a");
    Nfa* nfa_b = new Nfa("b");
    Nfa* nfa_c = new Nfa("c");
    Nfa* nfa_d = new Nfa("d");
    Nfa* nfa_or_abcd = Nfa::Parallel(vector<Nfa*> {nfa_a, nfa_b, nfa_c, nfa_d});

    cout << "TEST" << endl;
    // cout << Visualiser::JsonFromNfa(nfa_or_abcd) << endl;
    ofstream outjson("outjson.json");
    outjson << Visualiser::JsonFromNfa(nfa_or_abcd);
    outjson.close();


    cout << Visualiser::JsonFromNfa(nfa_or_abcd) << endl;
}