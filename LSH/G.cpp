#include <cmath>
#include <iostream>
#include <random>
#include "G.hpp"

using namespace std;

G::G(int w, int d, int M):w(w), d(d), k(k){
    cout << "Whatap G" << endl;
    // Create k sub-hashtables
    for (int i=0; i<k; i++){
        H h_i(w, d, pow(2,32/k));
        h.push_back(h_i);
    }
}

G::~G(){}

int G::hash(Point p){
    return 69;
}

