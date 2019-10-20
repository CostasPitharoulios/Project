#include <bitset>
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

uint32_t G::hash(Point p){
    //uint mask = pow(2,32/k)-1; // Mask of 32/k true bits

    uint32_t hashkey = 0;
    for (int i=0; i<k; i++){
        // Compute h_i(p)
        uint32_t h_i = h.at(i).hash(p);

        // Shift it to the right position
        h_i = h_i << ((32/k)*(k-i-1));
        //cout << "h_" << i << "(p) = \t" << bitset<32>(h_i) << endl;

        // Logical OR, to copy it into the hashkey
        hashkey = hashkey | h_i;
        //cout << "hashkey = \t" << bitset<32>(hashkey) << endl;
    }

    return hashkey;
}
