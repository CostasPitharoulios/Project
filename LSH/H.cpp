#include <cmath>
#include <iostream>
#include <random>
#include "../util.hpp"
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
        //cout << "s[" << i << "]=" << s[i] << " ";
    }
    //cout << endl;

    // Compute m[i]'s so that m[i] = m[1]^i
    // We do modM on every step, instead of once, to prevent overflow
    // The result will be correct because of the multiplicaiton property of mod
    m[0]=1;
    m[1]= (int) (((long)pow(2,32)-5)%M);
    for (int i=2; i<d; i++){
        m[i] = (m[i-1]*m[1])%M;
        //cout << "m[" << i << "]=" << m[i] << endl;
    }
}

H::~H(){
    delete[] s;
    delete[] m;
}

H::H(const H &h2){
    w = h2.w;
    d = h2.d;
    M = h2.M;

    s = new double[d];
    m = new int[d];

    for (int i=0; i<d; i++){
        s[i] = h2.s[i];
        m[i] = h2.m[i];
    }
}

uint32_t H::hash(Point p){
    vector<int> a;
    // Compute the a_i's
    // Formula: a_i = floor( (x_i - s_i)/w )
    for (int i=0; i<d; i++){
        a.push_back(floor((p.getCoordinate(i)-s[i])/(double)w)); 
        //cout << "a_" << i << "=" << a.at(i) << endl;
    }

    // h(p) = [ a_(d-1) + m a_(d-2) + ... + m^(d-1) a_0 ] mod M
    // We do modM on every step, instead of once, to prevent overflow
    // The result will be correct because of the multiplicaiton property of mod
    uint32_t hp;
    for (int i=0; i<d; i++){
        hp += mod(mod(a.at(d-i-1),M)*m[i],M);
        hp = mod(hp,M);
    }
    return hp;
}
