//
// Created by Ahmed Barakat on 107 / 16 / 16.
//

#include <Nfa.h>
#include <Dfa.h>
#include <Lexical.h>
#include "gtest/gtest.h"

TEST(DfaTest, BasicCreation) {

//    Dfa *dfa = new Dfa(Nfa::Solver(RegularDefinition::Tokenize("\\+|\\-")), new Token("i", 77));

    cout << endl;
    Nfa *n = Nfa::Solver(RegularDefinition::Tokenize("(((a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z)|(A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z))|_|$)(((a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z)|(A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z))|((0|1|2|3|4|5|6|7|8|9))|_|$)*"));
//    Nfa *n = Nfa::Solver(RegularDefinition::Tokenize("int"));
//    cout << n->ToString() << endl;
//    cout << n->terminal_state->id << endl;
    Dfa *dfa = new Dfa(n, new Token("i", 77));

//    cout << endl << n->ToString() << endl;
    cout << endl << dfa->ToString(true) << endl;

//    Lexical *l = new Lexical();
//    l->AddDfa(Nfa::Solver(RegularDefinition::Tokenize("int")), new Token("i", 77));
//    l->AddDfa(Nfa::Solver(RegularDefinition::Tokenize("\\+|\\-")), new Token("i", 77));
//
//    Lexical::Output out = l->ParseInput("ahmed");
//
//    cout << endl << "TT" << out.tokens.size() << endl;
}

//TEST(DfaTest, BasicCreation) {
////    "(a|b)+bcd"
//    Nfa *nfa_a = new Nfa("a");
//    Nfa *nfa_b = new Nfa("b");
//    Nfa *nfa_b2 = new Nfa("b");
//    Nfa *nfa_c = new Nfa("c");
//    Nfa *nfa_d = new Nfa("d");
//
//    Nfa *nfa_ab = Nfa::Parallel(nfa_a, nfa_b);
//    Nfa *nfa_abab = Nfa::Plus(nfa_ab);
//    Nfa *nfa_ababb = Nfa::Concatenate(nfa_abab, nfa_b2);
//    Nfa *nfa_ababbc = Nfa::Concatenate(nfa_ababb, nfa_c);
//    Nfa *nfa_ababbcd = Nfa::Concatenate(nfa_ababbc, nfa_d);
//    Dfa *dfa = new Dfa(nfa_ababbcd, new Token("(a|b)+bcd", 1));
//
//    Dfa::table_state** minimized_table = dfa->minimized_table;
//    int int_test_table[5][4] =
//        {{4, 4, -1, -1}, {4, 1, 2, -1}, {-1, -1, -1, 3}, {-1, -1, -1, -1}, {4, 1, -1, -1}};
//    int bool_test_table[5][4] =
//            {{false, false, false, false}, {false, false, false, false}, {false, false, false, true},
//             {false, false, false, false}, {false, false, false, false}};
//    for(int i = 0; i < dfa->minimized_states_count; ++i) {
//        for(int j = 0; j < Lexical::alphabet.size(); ++j) {
//            EXPECT_EQ(minimized_table[i][j].next_state, int_test_table[i][j]);
//            EXPECT_EQ(minimized_table[i][j].is_acceptance, bool_test_table[i][j]);
//        }
//    }
//}
//
//TEST(DfaTest, Minimizing) {
////    "ab|a+b+"
//    Nfa *nfa_a = new Nfa("a");
//    Nfa *nfa_b = new Nfa("b");
//    Nfa *nfa_a1 = new Nfa("a");
//    Nfa *nfa_b1 = new Nfa("b");
//
//    Nfa *nfa_ab = Nfa::Concatenate(nfa_a, nfa_b);
//    Nfa *nfa_aa = Nfa::Plus(nfa_a1);
//    Nfa *nfa_bb = Nfa::Plus(nfa_b1);
//    Nfa *nfa_aabb = Nfa::Concatenate(nfa_aa, nfa_bb);
//    Nfa *nfa_abaabb = Nfa::Parallel(nfa_ab, nfa_aabb);
//    Dfa *dfa = new Dfa(nfa_abaabb, new Token("ab|a+b+", 2));
//
//    Dfa::table_state** minimized_table = dfa->minimized_table;
//    int int_test_table[3][4] =
//            {{2, -1, -1, -1}, {-1, 1, -1, -1}, {2, 1, -1, -1}};
//    int bool_test_table[3][4] =
//            {{false, false, false, false}, {false, true, false, false}, {false, true, false, false}};
//    for(int i = 0; i < dfa->minimized_states_count; ++i) {
//        for(int j = 0; j < Lexical::alphabet.size(); ++j) {
//            EXPECT_EQ(minimized_table[i][j].next_state, int_test_table[i][j]);
//            EXPECT_EQ(minimized_table[i][j].is_acceptance, bool_test_table[i][j]);
//        }
//    }
//}
//
//TEST(DfaTest, MinimizeWithMergingStartState) {
////    "b+|a+b+"
//    Nfa *nfa_a = new Nfa("a");
//    Nfa *nfa_b = new Nfa("b");
//    Nfa *nfa_b1 = new Nfa("b");
//
//    Nfa *nfa_aa = Nfa::Plus(nfa_a);
//    Nfa *nfa_bb = Nfa::Plus(nfa_b);
//    Nfa *nfa_bb1 = Nfa::Plus(nfa_b1);
//    Nfa *nfa_aabb = Nfa::Concatenate(nfa_aa, nfa_bb);
//    Nfa *nfa_abaabb = Nfa::Parallel(nfa_bb1, nfa_aabb);
//    Dfa *dfa = new Dfa(nfa_abaabb, new Token("b+|a+b+", 3));
//
//    Dfa::table_state** minimized_table = dfa->minimized_table;
//    int int_test_table[2][4] =
//            {{0, 1, -1, -1}, {-1, 1, -1, -1}};
//    int bool_test_table[2][4] =
//            {{false, true, false, false}, {false, true, false, false}};
//    for(int i = 0; i < dfa->minimized_states_count; ++i) {
//        for(int j = 0; j < Lexical::alphabet.size(); ++j) {
//            EXPECT_EQ(minimized_table[i][j].next_state, int_test_table[i][j]);
//            EXPECT_EQ(minimized_table[i][j].is_acceptance, bool_test_table[i][j]);
//        }
//    }
//}
//
//TEST(DfaTest, SimpleFromRegularExpression) {
//    string sample = "(a*|b)+";
//    sample = "a";
//    Nfa* nfa = Nfa::Solver(RegularDefinition::Tokenize(sample));
//
//    Dfa* dfa = new Dfa(nfa, new Token(sample, 2));
//}

TEST(DfaGeneratorFromRegularDefinition, SingleThenStar) {
    string sample = "ba*";
    Dfa* dfa = new Dfa(Nfa::Solver(RegularDefinition::Tokenize(sample)), new Token("ba*", 64531));

    cout << dfa->ToString(false) << endl;
}
