// Author: Arjun Nair
// Program to find epsilon close of nfa and convert it to nfa
// Uses input file states.txt
// Format of states.txt:
// N M
// <N Final states space separated>
// <M Transitions in the form <from> <input_char> <to>>
//

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>

using namespace std;

set<int> final_states;

struct transition {
    int from, to;
    char input;

    void print() { cout<<from<<"--"<<input<<"->"<<to<<endl; }

    bool operator< (const transition &right) const {
        return (from < right.from ||
                (from == right.from && input < right.input) ||
                (from == right.from && input == right.input &&
                    to < right.to));
    }
};
set<transition> trans;


set<int> states;
map<int, set<int>> eclose;


void find_eclose(int state) {

    eclose[state].insert(state);

    size_t eclose_size = 0;
    while(eclose_size != eclose[state].size()) {
        eclose_size = eclose[state].size();

        for(transition t: trans) {
            if(t.input == 'e') {
                if(eclose[state].find(t.from) != eclose[state].end()) {
                    eclose[state].insert(t.to);
                }
            }
        }
    }
}


void print_details() {
    cout<<"States: ";
    for(int state: states) {
        cout<<state<<" ";
    }
    cout<<endl;

    cout<<"Final states: ";
    for(int state: final_states) {
        cout<<state<<" ";
    }
    cout<<endl;

    cout<<endl;

    cout<<"Transitions: "<<endl;
    for(transition t: trans) {
        t.print();
    }

    cout<<endl;
}

int main() {

    ifstream file("./states.txt");

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
        transition t;
        file>>t.from>>t.input>>t.to;
        trans.insert(t);

        states.insert(t.from);
        states.insert(t.to);
    }

    print_details();

    // Find and print eclose for all the states
    for(int state: states) {
        find_eclose(state);

        cout<<"ECLOSE("<<state<<"): ";
        for(int st: eclose[state]) {
            cout<<st<<" ";
        }
        cout<<endl;
    }


    cout<<endl<<endl;
    cout<<"=== Converting E-NFA to NFA ===="<<endl<<endl;

    for(int state: states) {
        // If any of the closure elements is final state then state is final
        for(int st: eclose[state]) {
            if(final_states.find(st) != final_states.end()) {
                final_states.insert(state);
            }
        }

        // Any transition in eclose is made to be a transition from the state directly
        for(transition t: trans) {
            if(eclose[state].find(t.from) != eclose[state].end()) {
                transition t1 { state, t.to, t.input };
                trans.insert(t1);
            }
        }
    }


    set<transition> no_eps_trans;
    for(transition t: trans) {
        if(t.input != 'e') {
            no_eps_trans.insert(t);
        }
    }
    trans = no_eps_trans;

    print_details();

    return 0;
}
