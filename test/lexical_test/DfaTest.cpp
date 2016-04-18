//
// Created by Ahmed Barakat on 107 / 16 / 16.
//

#include <Nfa.h>
#include <Dfa.h>
#include <Lexical.h>
#include "gtest/gtest.h"

TEST(DfaTest, BasicCreation) {
    cout << endl;
    Nfa *n = Nfa::Solver(RegularDefinition::Tokenize("(((a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z)|(A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z))|_|$)(((a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z)|(A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z))|((0|1|2|3|4|5|6|7|8|9))|_|$)*"));
//    Nfa *n = Nfa::Solver(RegularDefinition::Tokenize("int"));

    Dfa *dfa = new Dfa(n, new Token("i", 77));

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
