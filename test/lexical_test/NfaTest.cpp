//
// Created by ahmedatef on 4/16/16.
//

#include "Nfa.h"
#include "gtest/gtest.h"

class NfaTest : public ::testing::Test, public State {

protected:
    int next_id_cached;

    virtual void SetUp() {
        // Save the protected static int generator from State class, for states ids in next_id_cached and set it to 0.
        this->next_id_cached = this->next_id;
        this->next_id = 0;
    }

    virtual void TearDown() {
        this->next_id = this->next_id_cached;
    }
};

TEST_F(NfaTest, SingleState) {
    Nfa* nfa = new Nfa("a");
    EXPECT_EQ(nfa->start_state->id, 0);
    EXPECT_EQ(nfa->start_state->outgoing_transitions.size(), 1);
    EXPECT_EQ(nfa->start_state->outgoing_transitions[0]->value, "a");
}

TEST_F(NfaTest, Concatenate) {
    Nfa *nfa0 = new Nfa("a");
    Nfa *nfa1 = new Nfa("b");

    Nfa *nfa01 = Nfa::Concatenate(nfa0, nfa1);

    EXPECT_EQ(0, nfa01->start_state->id);
    EXPECT_EQ("a", nfa01->start_state->outgoing_transitions[0]->value);
    EXPECT_EQ(1, nfa01->start_state->outgoing_transitions[0]->next_state->id);
    EXPECT_EQ("", nfa01->start_state->outgoing_transitions[0]->next_state->outgoing_transitions[0]->value);
    EXPECT_EQ(2, nfa01->start_state->outgoing_transitions[0]->next_state->outgoing_transitions[0]->next_state->id);
    EXPECT_EQ("b", nfa01->start_state->outgoing_transitions[0]->next_state->outgoing_transitions[0]->next_state->
            outgoing_transitions[0]->value);
    EXPECT_EQ(3, nfa01->start_state->outgoing_transitions[0]->next_state->outgoing_transitions[0]->next_state->
            outgoing_transitions[0]->next_state->id);
}

TEST_F(NfaTest, Star) {
    Nfa* nfa = new Nfa("a");
    Nfa* nfa_stared = Nfa::Star(nfa);

    EXPECT_EQ(nfa->start_state->id, 0);
    EXPECT_EQ(nfa->start_state->outgoing_transitions.size(), 1);
    EXPECT_EQ(nfa->start_state->outgoing_transitions[0]->value, "a");
}


class NfaTestToString : public ::NfaTest { };

TEST_F(NfaTestToString, OneState) {
    Nfa* nfa = new Nfa("a");
    EXPECT_EQ(nfa->ToString(),
              "0: ('a', 1) \n"
                      "1: \n");
}

TEST_F(NfaTestToString, TwoStatesConcatenated) {
    Nfa* nfa_a = new Nfa("a");
    Nfa* nfa_b = new Nfa("b");
    Nfa* nfa_ab = Nfa::Concatenate(nfa_a, nfa_b);

    EXPECT_EQ(nfa_ab->ToString(),
              "0: ('a', 1) \n"
                      "1: ('', 2) \n"
                      "2: ('b', 3) \n"
                      "3: \n");
}

TEST_F(NfaTestToString, TwoStatesParallel) {
    Nfa* nfa_a = new Nfa("a");
    Nfa* nfa_b = new Nfa("b");
    Nfa* nfa_a_or_b = Nfa::Parallel(nfa_a, nfa_b);

    EXPECT_EQ(nfa_a_or_b->ToString(),
              "4: ('', 0) ('', 2) \n"
                      "0: ('a', 1) \n"
                      "2: ('b', 3) \n"
                      "1: ('', 5) \n"
                      "3: ('', 5) \n"
                      "5: \n");
}

TEST_F(NfaTestToString, FourStatesParallelAtOnce) {
    Nfa* nfa_a = new Nfa("a");
    Nfa* nfa_b = new Nfa("b");
    Nfa* nfa_c = new Nfa("c");
    Nfa* nfa_d = new Nfa("d");
    Nfa* nfa_or_abcd = Nfa::Parallel(vector<Nfa*> {nfa_a, nfa_b, nfa_c, nfa_d});

    cout << nfa_or_abcd->ToString() << endl;
    EXPECT_EQ(nfa_or_abcd->ToString(),
              "8: ('', 0) ('', 2) ('', 4) ('', 6) \n"
                      "0: ('a', 1) \n"
                      "2: ('b', 3) \n"
                      "4: ('c', 5) \n"
                      "6: ('d', 7) \n"
                      "1: ('', 9) \n"
                      "3: ('', 9) \n"
                      "5: ('', 9) \n"
                      "7: ('', 9) \n"
                      "9: \n");
}

TEST_F(NfaTestToString, Star) {
    Nfa* nfa = new Nfa("a");
    Nfa* nfa_stared = Nfa::Star(nfa);

    cout << nfa_stared->ToString() << endl;
}

class NfaGeneratorFromRegularDefinition : public ::NfaTest { };

TEST_F(NfaGeneratorFromRegularDefinition, SimpleOring) {
    string sample = "(a|b|c)";
    Nfa* solved_nfa = Nfa::Solver(RegularDefinition::Tokenize(sample));

    EXPECT_EQ(solved_nfa->ToString(),
              "8: ('', 6) \n"
                      "6: ('', 4) ('', 2) ('', 0) \n"
                      "4: ('c', 5) \n2: ('b', 3) \n"
                      "0: ('a', 1) \n"
                      "5: ('', 7) \n"
                      "3: ('', 7) \n"
                      "1: ('', 7) \n"
                      "7: ('', 9) \n"
                      "9: \n");

}

TEST_F(NfaGeneratorFromRegularDefinition, NestedParenthesesWithStarAndPlus) {
    string sample = "(a*(k|l))+";
    Nfa* solved_nfa = Nfa::Solver(RegularDefinition::Tokenize(sample));

    cout << solved_nfa->ToString() << endl;
}

TEST_F(NfaGeneratorFromRegularDefinition, NestedParenthesesWithStarEnclosed) {
    string sample = "(a*(k|l))";
    Nfa* solved_nfa = Nfa::Solver(RegularDefinition::Tokenize(sample));

    cout << solved_nfa->ToString() << endl;
}

TEST_F(NfaGeneratorFromRegularDefinition, SingleNfaEnclosedWithManyParentheses) {
    string sample = "(((a)))";
    Nfa* solved_nfa = Nfa::Solver(RegularDefinition::Tokenize(sample));

    cout << solved_nfa->ToString() << endl;
}

TEST_F(NfaGeneratorFromRegularDefinition, Solver) {
    string sample = "(a*(k|l|(mn|k))*l)+";
    Nfa* solved_nfa = Nfa::Solver(RegularDefinition::Tokenize(sample));

    cout << solved_nfa->ToString() << endl;
}

TEST_F(NfaGeneratorFromRegularDefinition, Solver5) {
    string sample = "(a*|b)+";
    Nfa* solved_nfa = Nfa::Solver(RegularDefinition::Tokenize(sample));

    cout << solved_nfa->ToString() << endl;

    cout << solved_nfa->terminal_state->is_acceptence << endl;
}

TEST_F(NfaGeneratorFromRegularDefinition, Concatenation) {
    string sample = "abc";
    Nfa* solved_nfa = Nfa::Solver(RegularDefinition::Tokenize(sample));

    cout << solved_nfa->ToString() << endl;
}

TEST_F(NfaGeneratorFromRegularDefinition, SingleState) {
    string sample = "ba*";
    Nfa* solved_nfa = Nfa::Solver(RegularDefinition::Tokenize(sample));

    cout << solved_nfa->ToString() << endl;
}

TEST_F(NfaGeneratorFromRegularDefinition, OrWithoutParentheses) {
    string sample = "a|b|c";
    Nfa* solved_nfa = Nfa::Solver(RegularDefinition::Tokenize(sample));

    cout << solved_nfa->ToString() << endl;

}

TEST_F(NfaGeneratorFromRegularDefinition, EscapeCharacter) {
    string sample = "\\+|\\-";
    Nfa* solved_nfa = Nfa::Solver(RegularDefinition::Tokenize(sample));

    cout << solved_nfa->ToString() << endl;
}

