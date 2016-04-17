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
    int priority = 1000;
    for(string keyword: regular_expression->keywords) {
        lexical->AddDfa(new Nfa(keyword), new Token(keyword, priority--));
    }

    for(pair<string, string> re: regular_expression->regular_expressions) {
        lexical->AddDfa(Nfa::Solver(RegularDefinition::Tokenize(re.second)), new Token(re.first, priority--));
    }

    for(string symbol: regular_expression->punctuations) {
        lexical->AddDfa(new Nfa(symbol), new Token("Punctuation", priority--));
    }

    Lexical::Output output = lexical->ParseInput(
            "int sum , count , pass , mnt; while (pass != 10) {pass = pass + 1 ; }");

    cout << "Error Exists: " << output.error_found << endl;
    cout << "# of Tokens: " << output.tokens.size() << endl;
    cout << "Error String Remaning: " << output.error_string << endl;

    return 0;
}
