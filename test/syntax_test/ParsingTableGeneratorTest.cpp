//
// Created by ahmedatef on 5/3/16.
//

#include <ContextFreeGrammar.h>
#include <ParsingTableGenerator.h>
#include "gtest/gtest.h"

TEST(ParsingTableCalculatingFirsts, SimpleFirst) {
    string grammar = ""
            "# A = 'id'\n"
            "# B = A | '(' ')'";

    ContextFreeGrammar *cfg = new ContextFreeGrammar();
    cfg->AddRulesFromString(grammar);

    ParsingTableGenerator* ptg = new ParsingTableGenerator(cfg->rules);

    cout << cfg->rules.size() << endl;
    cout << ptg->firsts.size() << endl;
}
