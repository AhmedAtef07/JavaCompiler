#include <iostream>
#include <iomanip>
#include <fstream>
#include <RegularExpression.h>
#include <RegularDefinition.h>

using namespace std;

int main() {
    cout << "Hi! This is the main." << endl;
    cout << "If you wanna run something in particular, run its tests." << endl;

    cout << "Opening the file through the Regular Expression class." << endl;
    RegularExpression* regular_expression = new RegularExpression("../lexical/lexical_input.txt");

    cout << "Converting the Regular Expression to NFA." << endl;
    cout << "Tokenzing: " << regular_expression->regular_expressions.size() << endl;
    Nfa* nfa = Nfa::Solver(RegularDefinition::Tokenize(regular_expression->regular_expressions.begin()->second));

    cout << nfa->ToString() << endl;

    return 0;
}
