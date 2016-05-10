//
// Created by Ahmed Barakat on 122 / 1 / 16.
//

#include <Symbol.h>


//Symbol::Symbol(const string &name) : name(name), type(kTerminal) { }

Symbol::Symbol(GrammarRule* grammar_rule) : grammar_rule(grammar_rule), name(grammar_rule->name), type(kNonTerminal) {}

Symbol::Symbol(const string &name) : grammar_rule(NULL), name(name), type(kTerminal) {}

Symbol* Symbol::GetSynchSymbol() {
    Symbol* symbol = new Symbol();
    symbol->name = "/Synch/";
    symbol->type = Type::kSynch;
    return symbol;
}

Symbol::Symbol() { }