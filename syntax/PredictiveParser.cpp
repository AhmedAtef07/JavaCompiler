//
// Created by Ahmed Barakat on 129 / 8 / 16.
//

#include "PredictiveParser.h"

PredictiveParser::PredictiveParser(vector<Symbol *> ***table, map<string, int> rules_indexes,
                                   map<string, int> terminals_indexes, Symbol *start_symbol) {
    this->start_symbol = start_symbol;
    this->table = table;
    this->rules_indexes = rules_indexes;
    this->terminals_indexes = terminals_indexes;
    initialize_the_stack();
}

void PredictiveParser::initialize_the_stack() {
    the_stack.clear();
    // TODO: Check the language will never have '\\$'.
    the_stack.push_back(new Symbol("\\$"));
}

// Just for delivering the project.
void PredictiveParser::ErrorHandler(string error_msg, Token* token) {
    cout << "@@@ error @@@: " << error_msg << endl;
    cout << "@@@ stack top @@@: " << the_stack.back()->name << endl;
    cout << "@@@ token @@@: " << token->name << endl;
}

bool PredictiveParser::parse(vector<Token *> tokens) {
    bool error_recovery_exist  = false;
    /*
     <div class="panel-group" id="accordion" role="tablist" aria-multiselectable="true">
      <div class="panel panel-default">
        <div class="panel-heading" role="tab" id="headingOne">
          <h4 class="panel-title">
            <a role="button" data-toggle="collapse" data-parent="#accordion" href="#token-1" aria-expanded="false" aria-controls="token-1">
              Collapsible Group Item #1
            </a>
          </h4>
        </div>
        <div id="token-1" class="panel-collapse collapse in" role="tabpanel" aria-labelledby="headingOne">
          <div class="panel-body">first token</div>
        </div>
      </div>
    </div>
     */
    open_current_token_tag(tokens[0]->name, 0);

    for(int i = 0; i < tokens.size(); ) {
        Token *token = tokens[i];


        if(the_stack.size() == 1 && the_stack.back()->name == "\\$" && token->name != "\\$") {
            the_stack.push_back(start_symbol);
            print_the_stack(token->name, false, i);
        }
        if(the_stack.back()->type == Symbol::Type::kTerminal) {
            if(the_stack.back()->name == "\\L") {
                the_stack.pop_back();
                continue;
            }
            if(the_stack.back()->name == token->name) {
                print_message_in_current_tag("<b>Matched:</b>&nbsp;&nbsp;&nbsp;" + token->name + "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"
                                             + the_stack.back()->name);
                close_current_token_tag();
                //              cout << "matched: " << token->name << " " << the_stack.back()->name << endl;
                the_stack.pop_back();
                ++i;
                if(i < tokens.size()) {
                    print_the_stack(tokens[i]->name, true, i);
                } else {
                    print_the_stack("", false, i);
                }
            } else {
                // Mismatch Error.
                ErrorHandler("Mismatched Terminal with input token", token);
                error_recovery_exist = true;
                the_stack.pop_back();
                print_message_in_current_tag("Mismatched Top of The Stack Terminal With Input Token. "
                                                     "<b>Top of The Stack Popped.</b>");
                print_the_stack(token->name, false, i);
                continue;
            }
        } else {
            // Non-terminal on the top of the stack.
            int current_token_index;
            if(terminals_indexes.find(token->name) != terminals_indexes.end()) {
                current_token_index = terminals_indexes[token->name];
            } else {
                ErrorHandler("Unknown Token", token);
                error_recovery_exist = true;
                ++i;
                print_message_in_current_tag("Unknown token found. <b>Current Token Skipped.</b>");
                close_current_token_tag();
                if(i < tokens.size()) {
                    print_the_stack(tokens[i]->name, true, i);
                } else {
                    print_the_stack("", false, i);
                }
                continue;
            }
            vector<Symbol *> v = *this->table[rules_indexes[the_stack.back()->name]][current_token_index];
            if(v.size() == 0) {
                // Empty Table Cell Error.
                ErrorHandler("Empty Table Cell", token);
                error_recovery_exist = true;
                print_message_in_current_tag("Empty Table Cell. <b>Current Token Skipped.</b>");
                close_current_token_tag();
                ++i;
                if(i < tokens.size()) {
                    print_the_stack(tokens[i]->name, true, i);
                } else {
                    print_the_stack("", false, i);
                }
                continue;
            } else if(v[0]->type == Symbol::Type::kSynch) {
                // Synch symbol found. Dropping from the stack.
                ErrorHandler("Synch Cell", token);
                error_recovery_exist = true;
                the_stack.pop_back();
                print_message_in_current_tag("Synch Cell Found. <b>Top of The Stack Popped.</b>");
                print_the_stack(token->name, false, i);
            } else {
                // Vector of symbols found in the table cell.
                the_stack.pop_back();
                for(int j = v.size() - 1; j != -1; --j) {
                    the_stack.push_back(v[j]);
                }
                print_the_stack(token->name, false, i);
            }
        }


    }

    cout << "no_error_recovery: " << (error_recovery_exist ? "False" : "True") << endl;

    if(the_stack.size() == 0 || (the_stack.size() == 1 && the_stack.back()->name == "\\$")) {
        cout << "input_belongs_to_grammar: True" << endl;
        return true;
    }
    cout << "input_belongs_to_grammar: False" << endl;
    return false;
}

void PredictiveParser::close_current_token_tag() {
    outputInHtmlFormat += "        </ul>\n";
    outputInHtmlFormat += "      </div>\n";
    outputInHtmlFormat += "    </div>\n";
    outputInHtmlFormat += "  </div>\n";
    outputInHtmlFormat += "</div>\n";
}

void PredictiveParser::print_message_in_current_tag(string message) {
    outputInHtmlFormat += "          <li class=\"list-group-item\">" + message + "</li>\n";
}

void PredictiveParser::print_the_stack(string current_token_name, bool new_token_passed, int index) {
    if(new_token_passed) {
        open_current_token_tag(current_token_name, index);
    }

    string stackline = "";
    for(Symbol *s : the_stack) {
        stackline += s->name + "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
//        cout << s->name << "  ";
    }
    if (stackline.length() > 0) {
        outputInHtmlFormat += "    <li class=\"list-group-item\">" + stackline + "</li>\n";
    }

//    cout << endl;
}

void PredictiveParser::open_current_token_tag(const string &current_token_name, int index) {
    outputInHtmlFormat += "<div class=\"panel-group\" id=\"accordion\" role=\"tablist\" aria-multiselectable=\"true\">\n";
    outputInHtmlFormat += "  <div class=\"panel panel-default\">\n";
    outputInHtmlFormat += "    <div class=\"panel-heading\" role=\"tab\" id=\"headingOne\">\n";
    outputInHtmlFormat += "      <h4 class=\"panel-title\">\n";
    outputInHtmlFormat += "        <a role=\"button\" data-toggle=\"collapse\" data-parent=\"#accordion\" href=\"#token-" + to_string(index) + "\" aria-expanded=\"false\" aria-controls=\"token-" + to_string(index) + "\">\n";
    outputInHtmlFormat += "          current token:&nbsp;&nbsp;&nbsp;<b>" + current_token_name + "</b>\n";
    outputInHtmlFormat += "        </a>\n";
    outputInHtmlFormat += "      </h4>\n";
    outputInHtmlFormat += "    </div>\n";
    outputInHtmlFormat += "    <div id=\"token-" + to_string(index) + "\" class=\"panel-collapse collapse in\" role=\"tabpanel\" aria-labelledby=\"headingOne\">\n";
    outputInHtmlFormat += "      <div class=\"panel-body\">\n";
    outputInHtmlFormat += "        <ul class=\"list-group\">\n";
}

string PredictiveParser::StringifyStack() {
    string ret = "";
    for(Symbol *s : the_stack) {
        ret += s->name + " ";
    }
    return ret;
}

string PredictiveParser::GetStackInHtmlForm() {
    return this->outputInHtmlFormat;
}



