#include <iostream>
#include "util.hpp"

// a%b but positive
int mod(int a, int b){
    return (a%b + b) % b;
}

void printOutput(ofstream& out, int q_id, int nn_id, double dist, double true_dist, double time, double true_time, vector<Point*> rnn){
    if (!out)
        return;

    out << "Query: " << q_id << endl;
    out << "Nearest neighbour: " << nn_id << endl;
    out << "distanceLSH: " << dist << endl;
    out << "distanceTrue: " << true_dist << endl;
    out << "tLSH: " << time << " ms" << endl;
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

void printOutput(ofstream& out, int q_id, string hf, int nn_id, int true_id, double dist, double true_dist ){
    if (!out)
        return;

    out << "Query: " << q_id << endl;
    out << "HashFunction: " << hf << endl;
    out << "Found Nearest neighbour: " << nn_id << endl;
    out << "True Nearest neighbour: " << true_id << endl;
    out << "distanceFound: " << dist << endl;
    out << "distanceTrue: " << true_dist << endl;
    
    out << endl;
}
