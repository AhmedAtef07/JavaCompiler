//
// Created by Ahmed Barakat on 107 / 16 / 16.
//

#include <Nfa.h>
#include <Dfa.h>
#include "gtest/gtest.h"

TEST(creation_test, basic_creation) {
//    "(a|b)+bcd"
    Nfa *nfa_a = new Nfa("a");
    Nfa *nfa_b = new Nfa("b");
    Nfa *nfa_b2 = new Nfa("b");
    Nfa *nfa_c = new Nfa("c");
    Nfa *nfa_d = new Nfa("d");

    Nfa *nfa_ab = Nfa::Parallel(nfa_a, nfa_b);
    Nfa *nfa_abab = Nfa::Plus(nfa_ab);
    Nfa *nfa_ababb = Nfa::Concatenate(nfa_abab, nfa_b2);
    Nfa *nfa_ababbc = Nfa::Concatenate(nfa_ababb, nfa_c);
    Nfa *nfa_ababbcd = Nfa::Concatenate(nfa_ababbc, nfa_d);
    Dfa *dfa = new Dfa(nfa_ababbcd);

    Dfa::table_state** minimized_table = dfa->minimized_table;
    int int_test_table[5][4] =
        {{4, 4, -1, -1}, {4, 1, 2, -1}, {-1, -1, -1, 3}, {-1, -1, -1, -1}, {4, 1, -1, -1}};
    int bool_test_table[5][4] =
            {{false, false, false, false}, {false, false, false, false}, {false, false, false, true},
             {false, false, false, false}, {false, false, false, false}};
    for(int i = 0; i < dfa->minimized_states_count; ++i) {
        for(int j = 0; j < alphapet_size; ++j) {
            EXPECT_EQ(minimized_table[i][j].next_state, int_test_table[i][j]);
            EXPECT_EQ(minimized_table[i][j].is_acceptence, bool_test_table[i][j]);
        }
    }
}

TEST(minimizing_test, minimize_test) {
//    "ab|a+b+"
    Nfa *nfa_a = new Nfa("a");
    Nfa *nfa_b = new Nfa("b");
    Nfa *nfa_a1 = new Nfa("a");
    Nfa *nfa_b1 = new Nfa("b");

    Nfa *nfa_ab = Nfa::Concatenate(nfa_a, nfa_b);
    Nfa *nfa_aa = Nfa::Plus(nfa_a1);
    Nfa *nfa_bb = Nfa::Plus(nfa_b1);
    Nfa *nfa_aabb = Nfa::Concatenate(nfa_aa, nfa_bb);
    Nfa *nfa_abaabb = Nfa::Parallel(nfa_ab, nfa_aabb);
    Dfa *dfa = new Dfa(nfa_abaabb);

    Dfa::table_state** minimized_table = dfa->minimized_table;
    int int_test_table[3][4] =
            {{2, -1, -1, -1}, {-1, 1, -1, -1}, {2, 1, -1, -1}};
    int bool_test_table[3][4] =
            {{false, false, false, false}, {false, true, false, false}, {false, true, false, false}};
    for(int i = 0; i < dfa->minimized_states_count; ++i) {
        for(int j = 0; j < alphapet_size; ++j) {
            EXPECT_EQ(minimized_table[i][j].next_state, int_test_table[i][j]);
            EXPECT_EQ(minimized_table[i][j].is_acceptence, bool_test_table[i][j]);
        }
    }
}

TEST(minimizng_test, minimize_test_with_start_merge) {
//    "b+|a+b+"
    Nfa *nfa_a = new Nfa("a");
    Nfa *nfa_b = new Nfa("b");
    Nfa *nfa_b1 = new Nfa("b");

    Nfa *nfa_aa = Nfa::Plus(nfa_a);
    Nfa *nfa_bb = Nfa::Plus(nfa_b);
    Nfa *nfa_bb1 = Nfa::Plus(nfa_b1);
    Nfa *nfa_aabb = Nfa::Concatenate(nfa_aa, nfa_bb);
    Nfa *nfa_abaabb = Nfa::Parallel(nfa_bb1, nfa_aabb);
    Dfa *dfa = new Dfa(nfa_abaabb);

    Dfa::table_state** minimized_table = dfa->minimized_table;
    int int_test_table[2][4] =
            {{0, 1, -1, -1}, {-1, 1, -1, -1}};
    int bool_test_table[2][4] =
            {{false, true, false, false}, {false, true, false, false}};
    for(int i = 0; i < dfa->minimized_states_count; ++i) {
        for(int j = 0; j < alphapet_size; ++j) {
            EXPECT_EQ(minimized_table[i][j].next_state, int_test_table[i][j]);
            EXPECT_EQ(minimized_table[i][j].is_acceptence, bool_test_table[i][j]);
        }
    }
}