#include <cmath>
#include <iostream>
#include <random>
#include "G.hpp"

using namespace std;

G::G(int w, int d, int k):w(w), d(d), k(k){
    cout << "Whatap G" << endl;
    // Create k sub-hashfunctions
    for (int i=0; i<k; i++){
        H h_i(w, d, pow(2,32/k));
        h.push_back(h_i);
    }
}

G::~G(){}

int G::hash(Point p){
    return h.at(1).hash(p);
}
