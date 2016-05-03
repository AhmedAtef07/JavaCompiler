//
// Created by ahmedatef on 5/2/16.
//

#include <stdexcept>
#include "GrammarRule.h"
#include "ParsingFunctions.h"

GrammarRule::GrammarRule(string name, ContextFreeGrammar* cfg) : name(name), cfg(cfg) {
    if(!cfg->FindExistingGrammarRule(name)) {
        cfg->rules.push_back(this);
    }
}

vector<string> GrammarRule::parse_or_tokens(string &s) {
    s += " |"; // To avoid handling last token.

    vector<string> or_tokens_;

    for(int i = 0, last = 0, len = s.length(); i != s.size(); ++i) {
        // Escape character. So we gonna escape the next char.
        if(s[i] == '\\') {
            ++i;
        } else if(s[i] == '|') {
            string token = s.substr(last, i - 1 - last);
            trim_(token);
            or_tokens_.push_back(token);
            last = i + 1;
        }
    }
    return or_tokens_;
}

GrammarRule::GrammarStringToken GrammarRule::ParseGrammarString(string rule) {
    // Finding the assignment operator. "=" or "::=".
    string assign_op = "=";
    size_t assign_op_ind = rule.find(assign_op);
    if(assign_op_ind == string::npos) {
        throw invalid_argument("Invalid Grammar Rule; All grammar rules must have an assignment operator.");
    }

    string rule_name = rule.substr(0, assign_op_ind - 1);

    string rule_production = rule.substr(assign_op_ind + 1 + assign_op.length());

    GrammarStringToken gst = { rule_name, rule_production };

    return gst;
}

void GrammarRule::AddProductionsFromString(string rule_production) {
    vector<string> or_tokens = parse_or_tokens(rule_production);

    for(string or_token : or_tokens) {
        productions.push_back(parse_following_tokens(or_token));
    }
}

// Assuming there exist no terminal symbol with spaces includes; ie: 'any thing' will never occur.
vector<Symbol*> GrammarRule::parse_following_tokens(string &s) {
    vector<string> tokens = split(s, ' ', true);

    vector<Symbol*> res;

    for(string token : tokens) {
        trim_(token);
        if(token[0] == '\'') {
            // Removing the quotes from around the terminal token name. 'id' -> id.
            res.push_back(new Symbol(token.substr(1, token.length() - 2)));
        } else {
            // Grammar Rule Name.
            if(GrammarRule* gr = cfg->FindExistingGrammarRule(token)) { // Does Exist.
                res.push_back(new Symbol(gr));
            } else { // Undefined grammar rule.
                // Make new GrammarRule with only a name.
                GrammarRule* new_gr = new GrammarRule(token, cfg);

                // Adding the reference to of the new Grammar Rule into the tokens of this Grammar.
                res.push_back(new Symbol(new_gr));
            };
        }
    }

    return res;
}

GrammarRule::GrammarRule() { }
