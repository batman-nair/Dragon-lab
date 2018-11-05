#include <iostream>
#include <fstream>
#include <set>
#include <map>

using namespace std;

struct nfa_state_char {
    int input_state;
    char input;

    bool operator< (const nfa_state_char &right) const {
        return (input_state < right.input_state ||
                (input_state == right.input_state && input < right.input));
    }
};
map<nfa_state_char, set<int>> nfa_table;



struct dfa_state_char {
    set<int> input_states;
    char input;

    bool operator< (const dfa_state_char &right) const {
        return (input_states < right.input_states ||
                (input_states == right.input_states && input < right.input));
    }
};
map<dfa_state_char, set<int>> dfa_table;
set<set<int>> dfa_states;


void add_dfa_state(const set<int> &state_list) {
            map<char, set<int>> new_maps;

            for(auto reval: nfa_table) {
                if(state_list.find(reval.first.input_state) != state_list.end()) {
                    // if(!new_maps[reval.first.input].empty()) {
                        new_maps[reval.first.input].insert(reval.second.begin(), reval.second.end());
                    // }
                }
            }

            dfa_states.insert(state_list);
            for(auto vals: new_maps) {
                dfa_state_char cell{state_list, vals.first};
                dfa_table[cell] = vals.second;

                if(dfa_states.find(vals.second) == dfa_states.end()) {
                    add_dfa_state(vals.second);
                }
            }
}


set<int> final_states;

int main() {
    ifstream file("states.txt");

    int n_final_states, n_transitions;
    file>>n_final_states>>n_transitions;

    // Read all the final states
    for(int i = 0; i < n_final_states; ++i) {
        int state;
        file>>state;
        final_states.insert(state);
    }

    // Read all the transitions for the nfa
    for(int i = 0; i < n_transitions; ++i) {
        nfa_state_char nfa_cell;
        int state;
        file>>nfa_cell.input_state;
        file>>nfa_cell.input;

        file>>state;
        nfa_table[nfa_cell].insert(state);
    }

    // Print NFA table
    cout<<"State\tinput\tOutput"<<endl;
    for(auto val: nfa_table) {
        cout<<val.first.input_state;
        cout<<"\t"<<val.first.input<<"\t";

        for(int state: val.second) {
            cout<<state<<" ";
        }
        cout<<endl;
    }


    //Building DFA from NFA
    for(auto val: nfa_table) {
        dfa_state_char st{{val.first.input_state}, val.first.input};
        dfa_table[st] = val.second;

        dfa_states.insert(st.input_states);


        if(val.second.size() > 1) {
            add_dfa_state(val.second);
        }
    }

    cout<<endl<<endl;
    cout<<"DFA table after converting NFA"<<endl<<endl;

    cout<<"State\tinput\tOutput"<<endl;
    for(auto val: dfa_table) {
        for(int state: val.first.input_states) {
            cout<<state<<" ";
        }

        cout<<"\t"<<val.first.input<<"\t";

        for(int state: val.second) {
            cout<<state<<" ";
        }
        cout<<endl;
    }



    return 0;
}
