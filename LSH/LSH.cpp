#include <bitset>
#include <iostream>
#include "LSH.hpp"

using namespace std;

typedef unordered_multimap<uint32_t,Point *>::iterator mapIt;

LSH::LSH(int w, int d, int maxN, int k, int L):w(w), d(d),maxN(maxN), k(k), L(L){
    cout << "Whatap LSH\n";
    for (int i=0; i<L; i++){
        G g_i(w, d, k);
        g.push_back(g_i);

        unordered_multimap<uint32_t,Point *> ht;
        hashTables.push_back(ht);
    }

    // This is important because we dont want the addresses
    // of the points in the dataset to change, since the
    // hashtable entries are pointers to Points.
    dataset.reserve(maxN);
} 

LSH::~LSH(){}

void LSH::insert(Point p){
    cout << "Inserting point " << p.getId() << endl;
    // Save point to the dataset vector
    dataset.push_back(p);
    
    Point *ptr = &dataset.back(); // Pointer to this new point in the vector

    // Insert it(its pointer) on every hashtable, according to g hashes
    for (int i=0; i<L; i++){
        //cout << "g(" << i << ") = " << (bitset<32>(g.at(i).hash(p))) << endl;
        uint32_t hashkey = g.at(i).hash(p);
        hashTables.at(i).insert(make_pair(hashkey, ptr));
    }
    cout << "Point " << ptr->getId() << " was inserted!" << endl;

    cout << "Dataset: ";
    for (int i=0; i<dataset.size(); i++){
        dataset.at(i).printPoint();
        cout << " ";
    }
    cout << endl;


    printG(0);
}

void LSH::printG(int i){
    mapIt it = hashTables.at(i).begin();

    while ( it!=hashTables.at(i).end()){
        cout << "<" << bitset<32>(it->first) << ", ";
        it->second->printPoint();
        cout  << ">  \n"; 
        it++;
    }
}
