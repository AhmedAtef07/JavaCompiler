#include <iostream>
#include <iomanip>
#include <fstream>
#include <RegularExpression.h>
#include <RegularDefinition.h>
#include <Lexical.h>

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

    string current_line;
    while(getline(ifs, current_line)) {
        Lexical::Output output = lexical->ParseInput(current_line);
        for(Token *k : output.tokens) {
            ofs << k->name << "  >  " << k->pattern << endl;
        }
    }

//    cout << "Error Exists: " << output.error_found << endl;
//    cout << "Error String Remaning: " << output.error_string << endl << endl;
//    cout << "# of Tokens: " << output.tokens.size() << endl;

    return 0;
}
