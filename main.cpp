#include <iostream>
#include <iomanip>
#include <fstream>
#include <RegularExpression.h>
#include <RegularDefinition.h>
#include <Lexical.h>

using namespace std;

int main() {
//    cout << "size of state: " << sizeof(State) << endl;
//    cout << "size of Transition: " << sizeof(Transition) << endl;
//    cout << "size of Nfa: " << sizeof(Nfa) << endl;
//    cout << "size of Dfa: " << sizeof(Dfa) << endl;
//    cout << "size of Lexical: " << sizeof(Lexical) << endl;
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
        cout << iterator->first << ": " << iterator->second << endl;
    }
    cout << endl;

//    for(map<string, string>::iterator iterator = regular_expression->regular_expressions.begin();
//        iterator != regular_expression->regular_expressions.end(); iterator++) {
//        if(i != 2 && i != 4 && i != 5) {
//            lexical->AddDfa(Nfa::Solver(RegularDefinition::Tokenize(iterator->second)),
//                            new Token(iterator->first, priority--));
//        } else {
//            cout << "not: " << iterator->first << ": " << iterator->second << endl;
//        }
//        ++i;
//    }


    Lexical::Output output = lexical->ParseInput(
            "int while (short != 10) {pass = pass + 1 ; }");

    cout << "Error Exists: " << output.error_found << endl;
    cout << "Error String Remaning: " << output.error_string << endl << endl;
    cout << "# of Tokens: " << output.tokens.size() << endl;
    for(Token *k : output.tokens) {
        cout << k->name << "  >  " << k->pattern << endl;
    }

    return 0;
}
