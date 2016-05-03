#include <iostream>
#include <iomanip>
#include <fstream>
#include <RegularExpression.h>
#include <RegularDefinition.h>
#include <Lexical.h>
#include <Visualiser.h>
#include <ContextFreeGrammar.h>
#include <cstring>

using namespace std;

int main(int argc, char * argv[]) {
    string path = "";
    // get the path from: ../bin/main => bin/
    int len = (int) (strlen(argv[0]) - 4);
    for(int i = 0; i < len; i++) {
        path += argv[0][i];
    }
    if(argc < 2) {
        cerr << "Invalid Format, you should run it: main lexical-input-file" << endl;
        return -1;
    }

    ifstream lexical_file(argv[1]);
    if(! lexical_file) {
        cerr << "Lexical File doesn't exist." << endl;
        return -1;
    }


    // Opening the file through the Regular Expression class.
    RegularExpression* regular_expression = new RegularExpression(argv[1]);

    Lexical* lexical = new Lexical();
    int priority = 1000000, i = 0;

    for(string keyword: regular_expression->keywords) {
        lexical->AddDfa(Nfa::Solver(RegularDefinition::Tokenize(keyword)), new Token(keyword, priority--));
    }

//    for(map<string, string>::iterator iterator = regular_expression->regular_expressions.begin();
//        iterator != regular_expression->regular_expressions.end(); iterator++) {
    for(pair<string, string> p : regular_expression->regular_expressions) {
        Nfa *n = Nfa::Solver(RegularDefinition::Tokenize(p.second));
        lexical->AddDfa(n, new Token(p.first, priority--));
    }
//    }
    for(string symbol: regular_expression->punctuations) {
        Nfa *a = Nfa::Solver(RegularDefinition::Tokenize(symbol));
        lexical->AddDfa(a, new Token("Punctuation", priority--));
    }
    ifstream ifs(path + "input.java");
    ofstream ofs(path + "input.java_lexemes");
    ofstream detailed_report(path + "input.java_lexemes_detailed");
    ofstream outjson(path + "dfa.js");

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

    cout << "lexemes: " << path + "input.java_lexemes" << endl;
    cout << "lexemes_detailed: " << path + "input.java_lexemes_detailed" << endl;
    cout << "dfa: " << path + "dfa.js" << endl;

    //system("google-chrome-stable ../report/index.html"); // more general
//    system("google-chrome-stable ../report/index.html"); // more general
    // system("xdg-open ../report/index.html"); // for linux
//     system("open ../report/index.html");  // for mac

//    cout << "Error Exists: " << output.error_found << endl;
//    cout << "Error String Remaning: " << output.error_string << endl << endl;
//    cout << "# of Tokens: " << output.tokens.size() << endl;

//    ContextFreeGrammar *cfg = new ContextFreeGrammar("../syntax/CFG.txt");

    return 0;
}

