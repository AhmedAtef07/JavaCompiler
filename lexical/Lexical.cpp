//
// Created by ahmedatef on 4/17/16.
//

#include "Lexical.h"

const vector<string> Lexical::alphabet = {
        " ", "!", "\"", "#", "$", "%", "&", "'", "(", ")", "*", "+", ",", "-", ".", "/", "0", "1", "2", "3", "4", "5",
        "6", "7", "8", "9", ";", "<", "=", ">", "?", "@", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L",
        "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "[", "\\", "]", "^", "_", "`", "a", "b",
        "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x",
        "y", "z", "{", "|", "}", "~", ":", " ", "\t", "\n" };

void Lexical::AddDfa(Nfa* nfa, Token* token) {
    dfas.push_back(new Dfa(nfa, token));
}

Lexical::Output Lexical::ParseInput(string input) {
    vector<string> error_strings;
    Token *highest_token = nullptr;
    vector<Token*> answer;
    int last_position = 0, highest_priority = -1, errors_found = 0;

    bool running_bools[dfas.size()];
    fill(running_bools, running_bools + dfas.size(), true);

    bool has_running = true;

    while(input.length() != 0) {
        fill(running_bools, running_bools + dfas.size(), true);
        last_position = 0;
        highest_priority = -1;
        highest_token = nullptr;
        has_running = true;
        for(int j = 0; j < dfas.size(); ++j) {
            dfas[j]->initialize_current_state();
        }
        for(int i = 0; i <= input.length(); ++i) {
            string curr_string = string(1, input[i]);

            if((!has_running || i == input.length())
               && highest_token != nullptr) {
                highest_token->pattern = input.substr(0, last_position + 1);
                if(highest_token->name != "Blanks") {
                    if(highest_token->name == "Punctuation") {
                        highest_token->name = highest_token->pattern;
                    } else if(highest_token->name == "id") {
                        symbol_table[highest_token->pattern];
                    }
                    answer.push_back(highest_token);
                }
                highest_priority = -1;
                highest_token = nullptr;
                input.erase(0, last_position + 1);
                if((curr_string == " " || curr_string == "\n" || curr_string == "\t") && last_position == i - 1) {
                    input.erase(0, 1);
                }
                break;
            } else if ((!has_running || i == input.length()) && highest_token == nullptr) {
                ++errors_found;
                error_strings.push_back(input);
                input.erase(0, 1);
                break;
            }
            has_running = false;
            for(int j = 0; j < dfas.size(); ++j) {
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
                                highest_token = new Token();
                                highest_token->name = t->name;
                                last_position = i;
                            }
                        }
                    }
                }
            }
        }
    }



    Output output = { answer, errors_found, error_strings };
    return output;
}
