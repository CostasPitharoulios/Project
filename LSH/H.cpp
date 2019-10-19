#include <cmath>
#include <iostream>
#include <random>
#include "H.hpp"

using namespace std;

H::H(int w, int d, int M):w(w), d(d), M(M){
    s = new double[d];
    m = new int[d];

    // Pick s[i]'s randomly, according to uniform distribution in [0,w)
    random_device rd; // seed
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0,w);

    for (int i=0; i<d; i++){
        s[i] = dis(gen);
        cout << "s[" << i << "]=" << s[i] << endl;
    }

    // Compute m[i]'s so that m[i] = m[1]^i
    // We do %M on every step, instead of once, to prevent overflow
    // The result will be correct because of the multiplicaiton property of mod
    m[0]=1;
    m[1]= (int) (((long)pow(2,32)-5)%M);
    cout << "m[1]=" << m[1] << endl;
    for (int i=2; i<d; i++){
        m[i] = (m[i-1]*m[1])%M;
        cout << "m[" << i << "]=" << m[i] << endl;
    }
    cout << "M=" << M << endl;
}

H::~H(){
    delete[] s;
}

int H::hash(Point p){
    vector<int> a;
    // Compute the a_i's
    // Formula: a_i = floor( (x_i - s_i)/w )
    for (int i=0; i<d; i++){
        a.push_back(floor((p.getCoordinate(i)-s[i])/(double)w)); 
    }

    // h(p) = a_(d-1) + m a_(d-2) + ... + m^(d-1) a_0
    int hp;
    for (int i=0; i<d; i++){
        hp += ((a.at(d-i-1)%M)*m[i])%M;
        hp = hp%M;
    }
    return hp;
}
