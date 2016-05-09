//
// Created by Ahmed Barakat on 129 / 8 / 16.
//

#include <ContextFreeGrammar.h>
#include <ParsingTableGenerator.h>
#include <PredictiveParser.h>
#include <Lexical.h>
#include <RegularExpression.h>
#include "gtest/gtest.h"

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

    cout << "firsts: " << endl;
    for(vector<set<string>> v : ptg->firsts) {
        for(set<string> s : v) {
            for(string st : s) {
                cout << st << "  ";
            }
        }
        cout << endl;
    }
    cout << endl;

    cout << "follows: " << endl;
    for(set<string> s : ptg->follows) {
        for(string st : s) {
            cout << st << "  ";
        }
        cout << endl;
    }
    cout << endl;

    PredictiveParser *pp = new PredictiveParser(ptg->table, ptg->rules_indexes, ptg->terminals_indexes);


    Token *t1 = new Token("int", 1);
    Token *t2 = new Token("id", 2);

    vector<Token*> v;
    v.push_back(t1);
    v.push_back(t2);

    cout << endl << "Parsing Stack:" << endl;

    if(pp->parse(v)) {
        cout << "succedded" << endl;
    }
}

TEST(ExampleParsingTest, ReturningToStartStateTest) {
    string grammer = "# METHOD_BODY = STATEMENT_LIST\n"
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
            "# FACTOR = 'id' | 'num' | '(' EXPRESSION ')' # SIGN = '+' | '-'";
    ContextFreeGrammar *cfg = new ContextFreeGrammar();
    cfg->AddRulesFromString(grammer);

    cout << endl << cfg->rules.size() << endl;

    ParsingTableGenerator* ptg = new ParsingTableGenerator(cfg->rules);

    cout << endl;

    cout << "firsts: " << endl;
    for(vector<set<string>> v : ptg->firsts) {
        for(set<string> s : v) {
            for(string st : s) {
                cout << st << "  ";
            }
        }
        cout << endl;
    }
    cout << endl;

    cout << "follows: " << ptg->follows.size() << endl;
    for(set<string> s : ptg->follows) {
        for(string st : s) {
            cout << st << "  ";
        }
        cout << endl;
    }
    cout << endl;

    PredictiveParser *pp = new PredictiveParser(ptg->table, ptg->rules_indexes, ptg->terminals_indexes);



    RegularExpression* regular_expression = new RegularExpression("../lexical/lexical_input.txt");

    Lexical* lexical = new Lexical();
    int priority = 1000000, i = 0;

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

    ifstream ifs("input.java");
    ofstream ofs("input.java_lexemes");
    ofstream detailed_report("input.java_lexemes_detailed");

    string current_line;
    while(getline(ifs, current_line)) {
        Lexical::Output output = lexical->ParseInput(current_line);
        cout << endl << "Parsing Stack:" << endl;
        if(pp->parse(output.tokens)) {
            cout << "succedded" << endl;
        }
        for(Token *k : output.tokens) {
            detailed_report << k->name << "  >  " << k->pattern << endl;
            ofs << k->name << "  " << k->pattern << endl;
        }
        detailed_report << endl << "Error Exists: " << output.errors_found << endl;
        for(string error : output.errors_strings) {
            detailed_report << "Error String Remaning: " << error << endl;
        }

        detailed_report << "---------------------------------------------------------------------------" << endl << endl;
    }

}