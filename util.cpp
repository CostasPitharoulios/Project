#include <iostream>
#include "util.hpp"

// a%b but positive
int mod(int a, int b){
    return (a%b + b) % b;
}

void printOutput(ofstream& out, int q_id, int nn_id, double lsh_dist, double true_dist, double lsh_time, double true_time, vector<Point*> rnn){
    if (!out)
        return;

    out << "Query: " << q_id << endl;
    out << "Nearest neighbour: " << nn_id << endl;
    out << "distanceLSH: " << lsh_dist << endl;
    out << "distanceTrue: " << true_dist << endl;
    out << "tLSH: " << lsh_time << " ms" << endl;
    out << "tTrue: " << true_time << " ms" << endl;
    
    // r-near neighbors:
    if (rnn.size()>0){
        out << "R-near neighbours:" << endl;
        out << rnn.at(0)->getId();
        for(int i=1; i<rnn.size(); i++){
            out << ", " << rnn.at(i)->getId();
        }
        out << endl;
    }
    out << endl;
}
