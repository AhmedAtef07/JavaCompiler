//
// Created by Ahmed Barakat on 129 / 8 / 16.
//

#include <ContextFreeGrammar.h>
#include <ParsingTableGenerator.h>
#include <PredictiveParser.h>
#include <Lexical.h>
#include <RegularExpression.h>
#include "gtest/gtest.h"

class PredictiveParserGeneratorFromLexical : public ::testing::Test {

protected:
    Lexical* lexical;
    ParsingTableGenerator* ptg;
    PredictiveParser *pp;

    PredictiveParserGeneratorFromLexical() : Test() {
        string grammar = ""
                "# METHOD_BODY = STATEMENT_LIST\n"
                "# STATEMENT_LIST = STATEMENT | STATEMENT_LIST STATEMENT\n"
                "# STATEMENT = DECLARATION\n"
                "| IF\n"
                "| WHILE\n"
                "| ASSIGNMENT\n"
                "# DECLARATION = PRIMITIVE_TYPE 'id' ';'\n"
                "# PRIMITIVE_TYPE = 'int' | 'float'\n"
                "# IF = 'if' '(' EXPRESSION ')' '{' STATEMENT '}' 'else' '{' STATEMENT '}'\n"
                "# WHILE = 'while' '(' EXPRESSION ')' '{' STATEMENT '}'\n"
                "# ASSIGNMENT = 'id' '=' EXPRESSION ';'\n"
                "# EXPRESSION = SIMPLE_EXPRESSION\n"
                "| SIMPLE_EXPRESSION 'relop' SIMPLE_EXPRESSION\n"
                "# SIMPLE_EXPRESSION = TERM | SIGN TERM | SIMPLE_EXPRESSION 'addop' TERM\n"
                "# TERM = FACTOR | TERM 'mulop' FACTOR\n"
                "# FACTOR = 'id' | 'num' | '(' EXPRESSION ')' "
                "# SIGN = '+' | '-'";

        ContextFreeGrammar *cfg = new ContextFreeGrammar();
        cfg->AddRulesFromString(grammar);

        cout << endl << endl;
        ptg = new ParsingTableGenerator(cfg->rules);

        ptg->print_firsts();
        ptg->print_follows();
        ptg->print_table();

        pp = new PredictiveParser(ptg->table, ptg->rules_indexes, ptg->terminals_indexes);


        RegularExpression* regular_expression = new RegularExpression("../lexical/lexical_input.txt");

        lexical = new Lexical();
        int priority = 900000, i = 0;

        for(string keyword: regular_expression->keywords) {
            lexical->AddDfa(Nfa::Solver(RegularDefinition::Tokenize(keyword)), new Token(keyword, priority--));
        }

        for(pair<string, string> p : regular_expression->regular_expressions) {
            Nfa *n = Nfa::Solver(RegularDefinition::Tokenize(p.second));
            lexical->AddDfa(n, new Token(p.first, priority--));
        }

        for(string symbol: regular_expression->punctuations) {
            Nfa *a = Nfa::Solver(RegularDefinition::Tokenize(symbol));
            lexical->AddDfa(a, new Token("Punctuation", priority--));
        }

        Nfa *space = Nfa::Solver(RegularDefinition::Tokenize(" "));
        lexical->AddDfa(space, new Token("Blanks", priority--));
        Nfa *new_tab = Nfa::Solver(RegularDefinition::Tokenize("\t"));
        lexical->AddDfa(new_tab, new Token("Blanks", priority--));
        Nfa *new_line = Nfa::Solver(RegularDefinition::Tokenize("\n"));
        lexical->AddDfa(new_line, new Token("Blanks", priority--));
    }
};

TEST_F(PredictiveParserGeneratorFromLexical, ReturningToStartStateTest) {
    string code_program_sample = ""
            "int x;\n"
            "X = 5;\n"
            "if(x >2) {\n"
            "\tX = 0;\n"
            "} else {\n"
            "\ty = 0;\n"
            "}\n"
            "\\$";

    cout << endl << "Parsing Stack:" << endl;

    Lexical::Output output = lexical->ParseInput(code_program_sample);

    EXPECT_TRUE(pp->parse(output.tokens));

    cout << ptg->GetFirstsInHtmlFormat() << endl;
    cout << ptg->GetFollowsInHtmlFormat() << endl;
    cout << ptg->GetParsingTableInHtmlFormat() << endl;
}

TEST_F(PredictiveParserGeneratorFromLexical, ErrorRecovery_int_x_i) {
    string code_program_sample = ""
            "int x i;"
            "\\$";

    cout << endl << "Parsing Stack:" << endl;

    Lexical::Output output = lexical->ParseInput(code_program_sample);

    EXPECT_TRUE(pp->parse(output.tokens));
}

TEST_F(PredictiveParserGeneratorFromLexical, ErrorRecovery_Assignment) {
    string code_program_sample = ""
            "int x;"
            "x = ;"
            "\\$";

    cout << endl << "Parsing Stack:" << endl;

    Lexical::Output output = lexical->ParseInput(code_program_sample);

    EXPECT_TRUE(pp->parse(output.tokens));
}

TEST(PredectiveParserGenerater, BasicTest) {
    string grammar = ""
            "# A = B C\n"
            "# B = 'int' | 'float'\n"
            "# C = 'id'";

    GrammarRule *A = new GrammarRule();
    A->name = "A";
    Symbol *A_symbol = new Symbol(A);

    GrammarRule *B = new GrammarRule();
    B->name = "B";
    Symbol *B_symbol = new Symbol(B);

    GrammarRule *C = new GrammarRule();
    C->name = "C";
    Symbol *C_symbol = new Symbol(C);

    Symbol *id_symbol = new Symbol("id");
    Symbol *int_symbol = new Symbol("int");
    Symbol *float_symbol = new Symbol("float");
    vector<Symbol*> temp_1 = {B_symbol, C_symbol};
    vector<Symbol*> temp_11 = {C_symbol, B_symbol};
    vector<Symbol*> temp_2 = {int_symbol};
    vector<Symbol*> temp_3 = {float_symbol};
    vector<Symbol*> temp_4 = {id_symbol};
    A->productions.push_back(temp_1);
//    A->productions.push_back(temp_11);
    B->productions.push_back(temp_2);
    B->productions.push_back(temp_3);
    C->productions.push_back(temp_4);

    vector<GrammarRule*> rules = {A, B, C};

    ParsingTableGenerator* ptg = new ParsingTableGenerator(rules);

    ptg->print_firsts();
    ptg->print_follows();
    ptg->print_table();

    PredictiveParser *pp = new PredictiveParser(ptg->table, ptg->rules_indexes, ptg->terminals_indexes);


    Token *t1 = new Token("int", 1);
    Token *t2 = new Token("id", 2);

    vector<Token*> v;
    v.push_back(t1);
    v.push_back(t2);

    cout << endl << "Parsing Stack:" << endl;

    bool succeeded = pp->parse(v);
    if(succeeded) {
        cout << "succeeded" << endl;
    }
    EXPECT_TRUE(succeeded);
}
