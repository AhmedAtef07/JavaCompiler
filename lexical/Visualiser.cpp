//
// Created by ahmedatef on 4/17/16.
//

#include "Visualiser.h"
#include "State.h"
#include "Dfa.h"
#include <queue>
#include <map>

struct JsonState {
    State * state;
    int order_y; // Order in the depth.
    int order_x; // Order in the sibling generation.
};

string Visualiser::JsonFromNfa(Nfa *nfa) {
    return JsonFromState(nfa->start_state);
}


string Visualiser::JsonFromDfa(Dfa *dfa) {
    return JsonFromState(dfa->start_state);
}

string Visualiser::JsonFromState(State *state) {
    set<State *> visited_states;
    queue<JsonState> bfs;
    bfs.push({ state, 0 , 0 });
    visited_states.insert(state);
    string result = "";

    string json = "{ \n";

    string nodes = "\"nodes\":[ \n";
    string transitions = "\"links\":[ \n";
    int level = 1;
    int last_x_level = 1;
    map<int, int> node_indexat;
    int node_index = 0;

    while(!bfs.empty()) {
        JsonState front_json_state = bfs.front();
        State* front_state = front_json_state.state;
        bfs.pop();

        string outgoing_states = to_string(front_state->id) + ": ";

        string node = "{ \n";
        string isAcceptenceState = front_state->is_acceptence ? "true" : "false";
        node += " \"isAcceptState\":" + isAcceptenceState + ",  \n";
        node += " \"text\": \"" + to_string(front_state->id) + "\",  \n";
        node += " \"y\":" + to_string(200 + front_json_state.order_y * 120) + ",  \n";
        node += " \"x\":" + to_string(200 + front_json_state.order_x * 120) + "  \n";
        node += "}, \n";
        nodes += node;

        set_index_of_node(node_indexat, node_index, front_state);

        int number_of_siblings = 0;
        for(Transition* transition: front_state->outgoing_transitions) {

            if(front_state->id == transition->next_state->id) {
                string link = "{ \n";
                // selflink
                link += " \"type\": \"SelfLink\", \n";
                set_index_of_node(node_indexat, node_index, transition->next_state);
                link += " \"node\": " + to_string(node_indexat.at(transition->next_state->id)) + ", \n";
                link += " \"text\": \"" + transition->value + "\", \n";
                link += " \"anchorAngle\": " + to_string(-0.2852221988545617) + " \n";
                link += "}, \n";

                transitions += link;
            }
            /*if(nfa->start_state->id == front_state->id) {
                cout << "nfa_start_state:" << nfa->start_state->id << ", front_state:" << front_state->id << endl;
                string link = "{ \n";
                // startlink
                link += " \"type\": \"StartLink\", \n";
                set_index_of_node(node_indexat, node_index, front_state);
                link += " \"node\": " + to_string(node_indexat.at(front_state->id)) + ", \n";
                link += " \"text\": \"" + is_epsilon(transition->value) + "\", \n";
                link += " \"deltaX\": " + to_string(-40) + ", \n";
                link += " \"deltaY\": " + to_string(-67) + " \n";
                link += "}, \n";

                transitions += link;
            }*/
            if(front_state->id != transition->next_state->id) {
                string link = "{ \n";
                // link
                link += " \"type\": \"Link\", \n";
                set_index_of_node(node_indexat, node_index, front_state);
                set_index_of_node(node_indexat, node_index, transition->next_state);
                link += " \"nodeA\": " + to_string(node_indexat.at(front_state->id)) + ", \n";
                link += " \"nodeB\": " + to_string(node_indexat.at(transition->next_state->id)) + ", \n";
                link += " \"text\": \"" + is_epsilon(transition->value) + "\", \n";
                link += " \"lineAngleAdjust\": " + to_string(0) + ", \n";
                link += " \"parallelPart\": " + to_string(0.5) + ", \n";
                link += " \"perpendicularPart\": " + to_string(0) + " \n";
                link += "}, \n";

                transitions += link;
            }


             outgoing_states += "('" + transition->value + "', ";
             outgoing_states += to_string(transition->next_state->id) + ") ";
            if(visited_states.find(transition->next_state) == visited_states.end()) {
                bfs.push({ transition->next_state, front_json_state.order_y + 1, number_of_siblings++ });
                visited_states.insert(transition->next_state);
            }
        }
         if(front_state->is_acceptence) outgoing_states += "\t[Accepted State]";
         outgoing_states += "\n";
         result += outgoing_states;

        last_x_level++;
    }

    nodes[nodes.length() - 3] = ' ';
    transitions[transitions.length() - 3] = ' ';
    nodes += "], \n";
    transitions += "]  \n";

    json += nodes;
    json += transitions;

    json += "}";

    // cout << result << endl;
    return json;
}

void Visualiser::set_index_of_node(map<int, int> &node_indexat, int &node_index, const State *front_state) {
    if(node_indexat.find(front_state->id) == node_indexat.end()) {
            node_indexat[front_state->id] = node_index++;
        }
}

string Visualiser::is_epsilon(string v) {
    return v.length() ? v : "epsilon";
}




