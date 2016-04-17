//
// Created by Ahmed Barakat on 108 / 17 / 16.
//

#include <Nfa.h>
#include <Dfa.h>
#include <Token.h>
#include <gtest/gtest.h>
#include <Lexical.h>


TEST(ParsingInputTest, MaximalMunchRule) {
    //    "b+|a+b+"
    //    "ab|a+b+"
    //    "(a|b)+bcd"

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
    Dfa *dfa1 = new Dfa(nfa_ababbcd, new Token("(a|b)+bcd", 70));

//    "ab|a+b+"
    Nfa *nfa_a2 = new Nfa("a");
    Nfa *nfa_b3 = new Nfa("b");
    Nfa *nfa_a1 = new Nfa("a");
    Nfa *nfa_b1 = new Nfa("b");

    Nfa *nfa_ab2 = Nfa::Concatenate(nfa_a2, nfa_b3);
    Nfa *nfa_aa = Nfa::Plus(nfa_a1);
    Nfa *nfa_bb = Nfa::Plus(nfa_b1);
    Nfa *nfa_aabb = Nfa::Concatenate(nfa_aa, nfa_bb);
    Nfa *nfa_abaabb = Nfa::Parallel(nfa_ab2, nfa_aabb);
    Dfa *dfa2 = new Dfa(nfa_abaabb, new Token("ab|a+b+", 71));

//    "b+|a+b+"
    Nfa *nfa_a3 = new Nfa("a");
    Nfa *nfa_b4 = new Nfa("b");
    Nfa *nfa_b5 = new Nfa("b");

    Nfa *nfa_aa3 = Nfa::Plus(nfa_a3);
    Nfa *nfa_bb3 = Nfa::Plus(nfa_b4);
    Nfa *nfa_bb5 = Nfa::Plus(nfa_b5);
    Nfa *nfa_aabb2 = Nfa::Concatenate(nfa_aa3, nfa_bb3);
    Nfa *nfa_abaabb2 = Nfa::Parallel(nfa_bb5, nfa_aabb2);
    Dfa *dfa3 = new Dfa(nfa_abaabb2, new Token("b+|a+b+", 72));

    string input = "aaaabbbbbb";
    string error_string = "";
    cout << input << endl << endl;
    Token *highest_token = nullptr;
    vector<Token*> answer;
    int last_position = 0, highest_priority = -1;
    bool running_bools[3] = {true, true, true};
    Dfa *running_dfas[3] = {dfa1, dfa2, dfa3};
    bool has_running = true, error_found = false;
    while(input.length() != 0) {
        fill(running_bools, running_bools + 3, true);
        last_position = 0;
        highest_priority = -1;
        highest_token = nullptr;
        has_running = true;
        for(int i = 0; i <= input.length(); ++i) {
            if((!has_running || i == input.length()) && highest_token != nullptr) {
                highest_token->pattern = input.substr (0, last_position + 1);
                answer.push_back(highest_token);
                highest_priority = -1;
                highest_token = nullptr;
                input.erase(0, last_position + 1);
                break;
            } else if ((!has_running || i == input.length()) && highest_token == nullptr) {
                cout << "Error!!!  >  ";
                error_found = true;
                error_string = input;
                break;
            }
            has_running = false;
            string curr_string = string(1, input[i]);
            for(int j = 0; j < 3; ++j) {
                if(running_bools[j]) {
                    has_running = true;
                    if(!running_dfas[j]->has_next_state(curr_string)) {
                        running_dfas[j]->initialize_current_state();
                        running_bools[j] = false;
                    } else {
                        Token *t = running_dfas[j]->go_to(curr_string);
                        if(t != nullptr) {
                            if(t->priority > highest_priority || i > last_position) {
                                highest_priority = t->priority;
                                highest_token = t;
                                last_position = i;
                            }
                        }
                    }
                }
            }
        }
        if(error_found) break;
    }

    EXPECT_EQ(answer.size(), 1);
    EXPECT_EQ(error_found, false);
    EXPECT_EQ(error_string, "");
    for(Token *t : answer) {
        cout << t->name << "  >  " << t->pattern << endl;
        EXPECT_EQ(t->name, "b+|a+b+");
        EXPECT_EQ(t->pattern, "aaaabbbbbb");
    }
    cout << endl << "finished" << endl << endl;
}



TEST(ParsingInputTest, PeriorityRule) {
    //    "ab|a+b+"
    //    "b+|a+b+"
    //    "(a|b)+bcd"

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
    Dfa *dfa1 = new Dfa(nfa_ababbcd, new Token("(a|b)+bcd", 4));

//    "b+|a+b+"
    Nfa *nfa_a3 = new Nfa("a");
    Nfa *nfa_b4 = new Nfa("b");
    Nfa *nfa_b5 = new Nfa("b");

    Nfa *nfa_aa3 = Nfa::Plus(nfa_a3);
    Nfa *nfa_bb3 = Nfa::Plus(nfa_b4);
    Nfa *nfa_bb5 = Nfa::Plus(nfa_b5);
    Nfa *nfa_aabb2 = Nfa::Concatenate(nfa_aa3, nfa_bb3);
    Nfa *nfa_abaabb2 = Nfa::Parallel(nfa_bb5, nfa_aabb2);
    Dfa *dfa3 = new Dfa(nfa_abaabb2, new Token("b+|a+b+", 5));

//    "ab|a+b+"
    Nfa *nfa_a2 = new Nfa("a");
    Nfa *nfa_b3 = new Nfa("b");
    Nfa *nfa_a1 = new Nfa("a");
    Nfa *nfa_b1 = new Nfa("b");

    Nfa *nfa_ab2 = Nfa::Concatenate(nfa_a2, nfa_b3);
    Nfa *nfa_aa = Nfa::Plus(nfa_a1);
    Nfa *nfa_bb = Nfa::Plus(nfa_b1);
    Nfa *nfa_aabb = Nfa::Concatenate(nfa_aa, nfa_bb);
    Nfa *nfa_abaabb = Nfa::Parallel(nfa_ab2, nfa_aabb);
    Dfa *dfa2 = new Dfa(nfa_abaabb, new Token("ab|a+b+", 6));

    string input = "aaaabbbbbb";
    string error_string = "";
    cout << input << endl << endl;
    Token *highest_token = nullptr;
    vector<Token*> answer;
    int last_position = 0, highest_priority = -1;
    bool running_bools[3] = {true, true, true};
    Dfa *running_dfas[3] = {dfa1, dfa2, dfa3};
    bool has_running = true, error_found = false;
    while(input.length() != 0) {
        fill(running_bools, running_bools + 3, true);
        last_position = 0;
        highest_priority = -1;
        highest_token = nullptr;
        has_running = true;
        for(int i = 0; i <= input.length(); ++i) {
            if((!has_running || i == input.length()) && highest_token != nullptr) {
                highest_token->pattern = input.substr (0, last_position + 1);
                answer.push_back(highest_token);
                highest_priority = -1;
                highest_token = nullptr;
                input.erase(0, last_position + 1);
                break;
            } else if ((!has_running || i == input.length()) && highest_token == nullptr) {
                cout << "Error!!!  >  ";
                error_found = true;
                error_string = input;
                break;
            }
            has_running = false;
            string curr_string = string(1, input[i]);
            for(int j = 0; j < 3; ++j) {
                if(running_bools[j]) {
                    has_running = true;
                    if(!running_dfas[j]->has_next_state(curr_string)) {
                        running_dfas[j]->initialize_current_state();
                        running_bools[j] = false;
                    } else {
                        Token *t = running_dfas[j]->go_to(curr_string);
                        if(t != nullptr) {
                            if(t->priority > highest_priority || i > last_position) {
                                highest_priority = t->priority;
                                highest_token = t;
                                last_position = i;
                            }
                        }
                    }
                }
            }
        }
        if(error_found) break;
    }

    EXPECT_EQ(answer.size(), 1);
    EXPECT_EQ(error_found, false);
    EXPECT_EQ(error_string, "");
    for(Token *t : answer) {
        cout << t->name << "  >  " << t->pattern << endl;
        EXPECT_EQ(t->name, "ab|a+b+");
        EXPECT_EQ(t->pattern, "aaaabbbbbb");
    }
    cout << endl << "finished" << endl << endl;
}



TEST(ParsingInputTest, ManyTokens) {
    //    "b+|a+b+"
    //    "ab|a+b+"
    //    "(a|b)+bcd"

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
//    Dfa *dfa1 = new Dfa(nfa_ababbcd, new Token("(a|b)+bcd", 7));

//    "ab|a+b+"
    Nfa *nfa_a2 = new Nfa("a");
    Nfa *nfa_b3 = new Nfa("b");
    Nfa *nfa_a1 = new Nfa("a");
    Nfa *nfa_b1 = new Nfa("b");

    Nfa *nfa_ab2 = Nfa::Concatenate(nfa_a2, nfa_b3);
    Nfa *nfa_aa = Nfa::Plus(nfa_a1);
    Nfa *nfa_bb = Nfa::Plus(nfa_b1);
    Nfa *nfa_aabb = Nfa::Concatenate(nfa_aa, nfa_bb);
    Nfa *nfa_abaabb = Nfa::Parallel(nfa_ab2, nfa_aabb);
//    Dfa *dfa2 = new Dfa(nfa_abaabb, new Token("ab|a+b+", 8));

//    "b+|a+b+"
    Nfa *nfa_a3 = new Nfa("a");
    Nfa *nfa_b4 = new Nfa("b");
    Nfa *nfa_b5 = new Nfa("b");

    Nfa *nfa_aa3 = Nfa::Plus(nfa_a3);
    Nfa *nfa_bb3 = Nfa::Plus(nfa_b4);
    Nfa *nfa_bb5 = Nfa::Plus(nfa_b5);
    Nfa *nfa_aabb2 = Nfa::Concatenate(nfa_aa3, nfa_bb3);
    Nfa *nfa_abaabb2 = Nfa::Parallel(nfa_bb5, nfa_aabb2);
//    Dfa *dfa3 = new Dfa(nfa_abaabb2, new Token("b+|a+b+", 9));

    string input = "aaaabbbbbbcdbbbbb";

    Lexical* lexical = new Lexical();
    lexical->AddDfa(nfa_ababbcd, new Token("(a|b)+bcd", 7));
    lexical->AddDfa(nfa_abaabb, new Token("ab|a+b+", 8));
    lexical->AddDfa(nfa_abaabb2, new Token("b+|a+b+", 9));

    Lexical::Output output = lexical->ParseInput(input);
    vector<Token*> answer = output.tokens;

    EXPECT_EQ(answer.size(), 2);
    EXPECT_EQ(output.error_found, false);
    EXPECT_EQ(output.error_string, "");
    int curr = 0;
    for(Token *t : answer) {
        cout << t->name << "  >  " << t->pattern << endl;
        if(curr == 0) {
            EXPECT_EQ(t->name, "(a|b)+bcd");
            EXPECT_EQ(t->pattern, "aaaabbbbbbcd");
        } else if(curr == 1) {
            EXPECT_EQ(t->name, "b+|a+b+");
            EXPECT_EQ(t->pattern, "bbbbb");
        }
        ++curr;
    }
    cout << endl << "finished" << endl << endl;
}



TEST(ParsingInputTest, WrongInput) {
    //    "b+|a+b+"
    //    "ab|a+b+"
    //    "(a|b)+bcd"

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
//    Dfa *dfa1 = new Dfa(nfa_ababbcd, new Token("(a|b)+bcd", 10));

//    "ab|a+b+"
    Nfa *nfa_a2 = new Nfa("a");
    Nfa *nfa_b3 = new Nfa("b");
    Nfa *nfa_a1 = new Nfa("a");
    Nfa *nfa_b1 = new Nfa("b");

    Nfa *nfa_ab2 = Nfa::Concatenate(nfa_a2, nfa_b3);
    Nfa *nfa_aa = Nfa::Plus(nfa_a1);
    Nfa *nfa_bb = Nfa::Plus(nfa_b1);
    Nfa *nfa_aabb = Nfa::Concatenate(nfa_aa, nfa_bb);
    Nfa *nfa_abaabb = Nfa::Parallel(nfa_ab2, nfa_aabb);
//    Dfa *dfa2 = new Dfa(nfa_abaabb, new Token("ab|a+b+", 11));

//    "b+|a+b+"
    Nfa *nfa_a3 = new Nfa("a");
    Nfa *nfa_b4 = new Nfa("b");
    Nfa *nfa_b5 = new Nfa("b");

    Nfa *nfa_aa3 = Nfa::Plus(nfa_a3);
    Nfa *nfa_bb3 = Nfa::Plus(nfa_b4);
    Nfa *nfa_bb5 = Nfa::Plus(nfa_b5);
    Nfa *nfa_aabb2 = Nfa::Concatenate(nfa_aa3, nfa_bb3);
    Nfa *nfa_abaabb2 = Nfa::Parallel(nfa_bb5, nfa_aabb2);
//    Dfa *dfa3 = new Dfa(nfa_abaabb2, new Token("b+|a+b+", 12));

    string input = "cbda";

    Lexical* lexical = new Lexical();
    lexical->AddDfa(nfa_ababbcd, new Token("(a|b)+bcd", 10));
    lexical->AddDfa(nfa_abaabb, new Token("ab|a+b+", 11));
    lexical->AddDfa(nfa_abaabb2, new Token("b+|a+b+", 12));

    Lexical::Output output = lexical->ParseInput(input);
    vector<Token*> answer = output.tokens;

    EXPECT_EQ(answer.size(), 0);
    EXPECT_EQ(output.error_found, true);
    EXPECT_EQ(output.error_string, "cbda");
}



TEST(ParsingInputTest, CorrectTokenAndWrongSubstring) {
    //    "b+|a+b+"
    //    "ab|a+b+"
    //    "(a|b)+bcd"

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
    Dfa *dfa1 = new Dfa(nfa_ababbcd, new Token("(a|b)+bcd", 13));

//    "ab|a+b+"
    Nfa *nfa_a2 = new Nfa("a");
    Nfa *nfa_b3 = new Nfa("b");
    Nfa *nfa_a1 = new Nfa("a");
    Nfa *nfa_b1 = new Nfa("b");

    Nfa *nfa_ab2 = Nfa::Concatenate(nfa_a2, nfa_b3);
    Nfa *nfa_aa = Nfa::Plus(nfa_a1);
    Nfa *nfa_bb = Nfa::Plus(nfa_b1);
    Nfa *nfa_aabb = Nfa::Concatenate(nfa_aa, nfa_bb);
    Nfa *nfa_abaabb = Nfa::Parallel(nfa_ab2, nfa_aabb);
    Dfa *dfa2 = new Dfa(nfa_abaabb, new Token("ab|a+b+", 14));

//    "b+|a+b+"
    Nfa *nfa_a3 = new Nfa("a");
    Nfa *nfa_b4 = new Nfa("b");
    Nfa *nfa_b5 = new Nfa("b");

    Nfa *nfa_aa3 = Nfa::Plus(nfa_a3);
    Nfa *nfa_bb3 = Nfa::Plus(nfa_b4);
    Nfa *nfa_bb5 = Nfa::Plus(nfa_b5);
    Nfa *nfa_aabb2 = Nfa::Concatenate(nfa_aa3, nfa_bb3);
    Nfa *nfa_abaabb2 = Nfa::Parallel(nfa_bb5, nfa_aabb2);
    Dfa *dfa3 = new Dfa(nfa_abaabb2, new Token("b+|a+b+", 15));

    string input = "abcbda";
    string error_string = "";
    cout << input << endl << endl;
    Token *highest_token = nullptr;
    vector<Token*> answer;
    int last_position = 0, highest_priority = -1;
    bool running_bools[3] = {true, true, true};
    Dfa *dfas[3] = {dfa1, dfa2, dfa3};
    bool has_running = true, error_found = false;
    while(input.length() != 0) {
        fill(running_bools, running_bools + 3, true);
        last_position = 0;
        highest_priority = -1;
        highest_token = nullptr;
        has_running = true;
        for(int i = 0; i <= input.length(); ++i) {
            if((!has_running || i == input.length()) && highest_token != nullptr) {
                highest_token->pattern = input.substr (0, last_position + 1);
                answer.push_back(highest_token);
                highest_priority = -1;
                highest_token = nullptr;
                input.erase(0, last_position + 1);
                break;
            } else if ((!has_running || i == input.length()) && highest_token == nullptr) {
                cout << "Error!!!  >  ";
                error_found = true;
                error_string = input;
                break;
            }
            has_running = false;
            string curr_string = string(1, input[i]);
            for(int j = 0; j < 3; ++j) {
                if(running_bools[j]) {
                    has_running = true;
                    if(!dfas[j]->has_next_state(curr_string)) {
                        dfas[j]->initialize_current_state();
                        running_bools[j] = false;
                    } else {
                        Token *t = dfas[j]->go_to(curr_string);
                        if(t != nullptr) {
                            if(t->priority > highest_priority || i > last_position) {
                                highest_priority = t->priority;
                                highest_token = t;
                                last_position = i;
                            }
                        }
                    }
                }
            }
        }
        if(error_found) break;
    }

    EXPECT_EQ(answer.size(), 1);
    EXPECT_EQ(error_found, true);
    EXPECT_EQ(error_string, "cbda");
    cout << error_string << endl << endl;
    for(Token *t : answer) {
        cout << t->name << "  >  " << t->pattern << endl;
        EXPECT_EQ(t->name, "b+|a+b+");
        EXPECT_EQ(t->pattern, "ab");
    }
    cout << endl << "finished" << endl << endl;
}


TEST(ParsingInputTest, CorrectTokensAndWrongSubstring) {
    //    "b+|a+b+"
    //    "ab|a+b+"
    //    "(a|b)+bcd"

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
    Dfa *dfa1 = new Dfa(nfa_ababbcd, new Token("(a|b)+bcd", 16));

//    "ab|a+b+"
    Nfa *nfa_a2 = new Nfa("a");
    Nfa *nfa_b3 = new Nfa("b");
    Nfa *nfa_a1 = new Nfa("a");
    Nfa *nfa_b1 = new Nfa("b");

    Nfa *nfa_ab2 = Nfa::Concatenate(nfa_a2, nfa_b3);
    Nfa *nfa_aa = Nfa::Plus(nfa_a1);
    Nfa *nfa_bb = Nfa::Plus(nfa_b1);
    Nfa *nfa_aabb = Nfa::Concatenate(nfa_aa, nfa_bb);
    Nfa *nfa_abaabb = Nfa::Parallel(nfa_ab2, nfa_aabb);
    Dfa *dfa2 = new Dfa(nfa_abaabb, new Token("ab|a+b+", 17));

//    "b+|a+b+"
    Nfa *nfa_a3 = new Nfa("a");
    Nfa *nfa_b4 = new Nfa("b");
    Nfa *nfa_b5 = new Nfa("b");

    Nfa *nfa_aa3 = Nfa::Plus(nfa_a3);
    Nfa *nfa_bb3 = Nfa::Plus(nfa_b4);
    Nfa *nfa_bb5 = Nfa::Plus(nfa_b5);
    Nfa *nfa_aabb2 = Nfa::Concatenate(nfa_aa3, nfa_bb3);
    Nfa *nfa_abaabb2 = Nfa::Parallel(nfa_bb5, nfa_aabb2);
    Dfa *dfa3 = new Dfa(nfa_abaabb2, new Token("b+|a+b+", 18));

    string input = "aaaabbbbbbcdbbbbbdcc";
    string error_string = "";
    cout << input << endl << endl;
    Token *highest_token = nullptr;
    vector<Token*> answer;
    int last_position = 0, highest_priority = -1;
    bool running_bools[3] = {true, true, true};
    Dfa *dfas[3] = {dfa1, dfa2, dfa3};
    bool has_running = true, error_found = false;
    while(input.length() != 0) {
        fill(running_bools, running_bools + 3, true);
        last_position = 0;
        highest_priority = -1;
        highest_token = nullptr;
        has_running = true;
        for(int i = 0; i <= input.length(); ++i) {
            if((!has_running || i == input.length()) && highest_token != nullptr) {
                highest_token->pattern = input.substr (0, last_position + 1);
                answer.push_back(highest_token);
                highest_priority = -1;
                highest_token = nullptr;
                input.erase(0, last_position + 1);
                break;
            } else if ((!has_running || i == input.length()) && highest_token == nullptr) {
                cout << "Error!!!  >  ";
                error_found = true;
                error_string = input;
                break;
            }
            has_running = false;
            string curr_string = string(1, input[i]);
            for(int j = 0; j < 3; ++j) {
                if(running_bools[j]) {
                    has_running = true;
                    if(!dfas[j]->has_next_state(curr_string)) {
                        dfas[j]->initialize_current_state();
                        running_bools[j] = false;
                    } else {
                        Token *t = dfas[j]->go_to(curr_string);
                        if(t != nullptr) {
                            if(t->priority > highest_priority || i > last_position) {
                                highest_priority = t->priority;
                                highest_token = t;
                                last_position = i;
                            }
                        }
                    }
                }
            }
        }
        if(error_found) break;
    }

    EXPECT_EQ(answer.size(), 2);
    EXPECT_EQ(error_found, true);
    EXPECT_EQ(error_string, "dcc");
    cout << error_string << endl << endl;
    int curr = 0;
    for(Token *t : answer) {
        cout << t->name << "  >  " << t->pattern << endl;
        if(curr == 0) {
            EXPECT_EQ(t->name, "(a|b)+bcd");
            EXPECT_EQ(t->pattern, "aaaabbbbbbcd");
        } else if(curr == 1) {
            EXPECT_EQ(t->name, "b+|a+b+");
            EXPECT_EQ(t->pattern, "bbbbb");
        }
        ++curr;
    }
    cout << endl << "finished" << endl << endl;
}