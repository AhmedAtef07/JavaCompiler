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

