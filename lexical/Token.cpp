//
// Created by Ahmed Barakat on 108 / 17 / 16.
//

#include <cstdlib>
#include <stdexcept>
#include "Token.h"

set<int> Token::priorities;

Token::Token() {
}

Token::Token(string name, int priority) {
    this->name = name;
    if(Token::priorities.find(priority) != Token::priorities.end()) {
        throw std::invalid_argument("'" + to_string(priority) + "' Repeated priority");
    } else if(priority < 1) {
        throw std::invalid_argument( "'" + to_string(priority) + "' Priority must be POSITIVE" );
    } else {
        this->priority = priority;
        Token::priorities.insert(priority);
    }
}

void Token::delete_token() {
    Token::priorities.erase(Token::priorities.find(this->priority), Token::priorities.end());
    free(this);
}