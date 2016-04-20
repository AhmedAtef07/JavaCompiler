#include <iostream>
#include <iomanip>
#include <fstream>
#include <RegularExpression.h>
#include <RegularDefinition.h>
#include <Lexical.h>
#include <Visualiser.h>

using namespace std;

int main() {
    // Opening the file through the Regular Expression class.
    RegularExpression* regular_expression = new RegularExpression("../lexical/lexical_input.txt");

    Lexical* lexical = new Lexical();
    int priority = 1000000, i = 0;

    for(string keyword: regular_expression->keywords) {
        lexical->AddDfa(Nfa::Solver(RegularDefinition::Tokenize(keyword)), new Token(keyword, priority--));
    }

    for(string symbol: regular_expression->punctuations) {
        Nfa *a = Nfa::Solver(RegularDefinition::Tokenize(symbol));
        lexical->AddDfa(a, new Token("Punctuation", priority--));
    }

    for(map<string, string>::iterator iterator = regular_expression->regular_expressions.begin();
        iterator != regular_expression->regular_expressions.end(); iterator++) {
            lexical->AddDfa(Nfa::Solver(RegularDefinition::Tokenize(iterator->second)),
                            new Token(iterator->first, priority--));
    }
    ifstream ifs("input.java");
    ofstream ofs("input.java_lexemes");

    ofstream outjson("outjson.json");
    outjson << "[";
    for (vector<Dfa *>::iterator it = lexical->dfas.begin(); it != lexical->dfas.end(); ++it) {
        Dfa* d = *it;
        outjson << Visualiser::JsonFromDfa(d);
        if (it != lexical->dfas.end() - 1)
            outjson << ", ";
    }
    outjson << "]";
    outjson.close();


    string current_line;
    while(getline(ifs, current_line)) {
        Lexical::Output output = lexical->ParseInput(current_line);
        for(Token *k : output.tokens) {
            ofs << k->name << "  >  " << k->pattern << endl;
        }
        ofs << endl << "Error Exists: " << output.errors_found << endl;
        for(string error : output.errors_strings) {
            ofs << "Error String Remaning: " << error << endl;
        }
        ofs << "---------------------------------------------------------------------------" << endl << endl;
    }

//    cout << "Error Exists: " << output.error_found << endl;
//    cout << "Error String Remaning: " << output.error_string << endl << endl;
//    cout << "# of Tokens: " << output.tokens.size() << endl;

    return 0;
}
