#include <iostream>
#include <iomanip>
#include <fstream>
#include <RegularExpression.h>
#include <RegularDefinition.h>
#include <Lexical.h>
#include <Visualiser.h>
#include <ContextFreeGrammar.h>

using namespace std;

// TODO: Symbol Table.
// TODO: Error Recovery.
// TODO: Report. Finish UI.

int main() {
    // Opening the file through the Regular Expression class.
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

    ofstream outjson("../report/dfa.js");
    outjson << "var dfas = {";
    int k = 0;
    for (vector<Dfa *>::iterator it = lexical->dfas.begin(); it != lexical->dfas.end(); ++it) {
        Dfa* d = *it;

        outjson << "\"" + d->token->name + "_" + to_string(k++)  +"\":";
        outjson << Visualiser::JsonFromDfa(d);
        if (it != lexical->dfas.end() - 1)
            outjson << ", ";
    }
    outjson << "}";
    outjson.close();


    string current_line;
    while(getline(ifs, current_line)) {
        Lexical::Output output = lexical->ParseInput(current_line);
        for(Token *k : output.tokens) {
            detailed_report << k->name << "  >  " << k->pattern << endl;
            ofs << k->name << "  " << k->pattern << endl;
        }
        detailed_report << endl << "Error Exists: " << output.errors_found << endl;
        for(string error : output.errors_strings) {
            detailed_report << "Error String Remaning: " << error << endl;
        }

        detailed_report << "---------------------------------------------------------------------------" << endl << endl;
//        ofs << endl;
    }


    //system("google-chrome-stable ../report/index.html"); // more general
//    system("google-chrome-stable ../report/index.html"); // more general
    // system("xdg-open ../report/index.html"); // for linux
//     system("open ../report/index.html");  // for mac

    return 0;
}

