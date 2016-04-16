#include <iostream>
#include <fstream>
#include "Nfa.h"
#include "RegularExpression.h"

#include <iomanip>

using namespace std;

/*
 * 1. Eliminate all parentheses.
 * 2.
 */
int main() {
    /*
    string test = "(a*(k|l|(mn|k))*l)+";
    cout << test << endl;
    cout << endl << endl;

    Nfa* nfa0 = new Nfa("a");
    Nfa* nfa1 = new Nfa("b");

    Nfa* nfa01 = Nfa::Concatenate(nfa0, nfa1);

    cout << nfa01->start_state->id << endl;
    cout << nfa01->start_state->outgoing_transitions[0]->value << endl;
    cout << nfa01->start_state->outgoing_transitions[0]->next_state->id << endl;
    cout << nfa01->start_state->outgoing_transitions[0]->next_state->outgoing_transitions[0]->value << endl;
    cout << nfa01->start_state->outgoing_transitions[0]->next_state->outgoing_transitions[0]->next_state->id << endl;
    cout << nfa01->start_state->outgoing_transitions[0]->next_state->outgoing_transitions[0]->next_state->
            outgoing_transitions[0]->value << endl;
    cout << nfa01->start_state->outgoing_transitions[0]->next_state->outgoing_transitions[0]->next_state->
            outgoing_transitions[0]->next_state->id << endl;

     */

    RegularExpression * re = new RegularExpression("/home/ramytamer/kolia/plt/project/phase-1/JavaCompiler/src/lexical_input.txt");


    /*for (set<string>::iterator i = re->keywords.begin(); i != re->keywords.end(); i++) {
        string element = *i;
        cout << "element: " << element << endl;
    }*/

    /*cout << "\nDefinetions:" << endl;
    for(map<string, string>::const_iterator it = re->regular_definetions.begin(); it != re->regular_definetions.end(); ++it)
    {
        cout << "'" << it->first << "'" << setw(20) << "'" << it->second << "'" << endl;
    }

    cout << "\nEXPRESSIONS:" << endl;
    for(map<string, string>::const_iterator it = re->regular_expressions.begin(); it != re->regular_expressions.end(); ++it)
    {
        cout << "'" << it->first << "'" << setw(20) << "'" << it->second << "'" << endl;
    }*/

    cout << "\n\nTESTING:" << endl;
    cout << "\nRegular Definetions:" << endl;
    cout << setw(35) << "isset letter:" << setw(35) << (re->regular_definetions.count("letter") ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "isset digit:" << setw(35) << (re->regular_definetions.count("digit") ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "isset digits:" << setw(35) << (re->regular_definetions.count("digits") ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "isset equals:" << setw(35) << (re->regular_definetions.count("equals") ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "isset notequals:" << setw(35) << (re->regular_definetions.count("notequals") ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "isset larger:" << setw(35) << (re->regular_definetions.count("larger") ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "isset smaller:" << setw(35) << (re->regular_definetions.count("smaller") ? "TRUE" : "FALSE") << endl;

    cout << endl;
    cout << setw(35) << "Assert Definetions of letter:" << setw(35) << (re->regular_definetions.at("letter") == "(a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z)|(A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z)" ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "Assert Definetions of digits:" << setw(35) << (re->regular_definetions.at("digit") == "(0|1|2|3|4|5|6|7|8|9)"  ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "Assert Definetions of digits:" << setw(35) << (re->regular_definetions.at("digits") == "((0|1|2|3|4|5|6|7|8|9))+" ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "Assert Definetions of equals:" << setw(35) << (re->regular_definetions.at("equals") == "\\=\\=" ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "Assert Definetions of notequals:" << setw(35) << (re->regular_definetions.at("notequals") == "!\\=" ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "Assert Definetions of larger:" << setw(35) << (re->regular_definetions.at("larger") == ">|>\\=" ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "Assert Definetions of smaller:" << setw(35) << (re->regular_definetions.at("smaller") == "<|<\\=" ? "TRUE" : "FALSE") << endl;

    cout << "\nRegular Expressions:" << endl;
    cout << setw(35) << "isset num: " << setw(35) << (re->regular_expressions.count("num") ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "isset id: " << setw(35) << (re->regular_expressions.count("id") ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "isset relop: " << setw(35) << (re->regular_expressions.count("relop") ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "isset assign: " << setw(35) << (re->regular_expressions.count("assign") ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "isset addop: " << setw(35) << (re->regular_expressions.count("addop") ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "isset mulop: " << setw(35) << (re->regular_expressions.count("mulop") ? "TRUE" : "FALSE") << endl;

    cout << endl;

    cout << setw(35) << "Assert Expression of num: " << setw(35) << (re->regular_expressions.at("num") == "((0|1|2|3|4|5|6|7|8|9))+|((0|1|2|3|4|5|6|7|8|9))+.(((0|1|2|3|4|5|6|7|8|9))+)(\\L|E(((0|1|2|3|4|5|6|7|8|9))+))" ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "Assert Expression of id: " << setw(35) << (re->regular_expressions.at("id") == "(((a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z)|(A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z))|_|$)(((a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z)|(A|B|C|D|E|F|G|H|I|J|K|L|M|N|O|P|Q|R|S|T|U|V|W|X|Y|Z))|((0|1|2|3|4|5|6|7|8|9))|_|$)*" ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "Assert Expression of relop: " << setw(35) << (re->regular_expressions.at("relop") == "(\\=\\=)|(!\\=)|(>|>\\=)|(<|<\\=)" ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "Assert Expression of assign: " << setw(35) << (re->regular_expressions.at("assign") == "\\=" ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "Assert Expression of addop: " << setw(35) << (re->regular_expressions.at("addop") == "\\+|\\-" ? "TRUE" : "FALSE") << endl;
    cout << setw(35) << "Assert Expression of mulop: " << setw(35) << (re->regular_expressions.at("mulop") == "\\*|/" ? "TRUE" : "FALSE") << endl;

    cout << endl;
    cout << "\nKeywords:" << endl;
    cout << setw(35) << "Assert Keywords size(49): " << setw(35) << (re->keywords.size() == 49 ? "TRUE" : "FALSE") << endl;


    cout << endl;
    cout << "\nPuncituations:" << endl;
    cout << setw(35) << "Assert Puncituations size(6): " << setw(35) << (re->punctuations.size() == 6 ? "TRUE" : "FALSE") << endl;

    return 0;
}



/*
 * TODO: Nfa, State, Transition classes;
 * TODO: operations on NFAs.
 */