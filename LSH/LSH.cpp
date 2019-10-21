#include <bitset>
#include <iostream>
#include <limits>
#include "LSH.hpp"
#include "../dist.hpp"

using namespace std;

typedef unordered_multimap<uint32_t,Point *>::iterator mapIt;

LSH::LSH(int w, int d, int k, int L):w(w), d(d), k(k), L(L){
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
    //dataset.reserve(maxN);
} 

LSH::~LSH(){}

void LSH::insert(Point p){
    Point *ptr = new Point(p);
    // Save point to the dataset vector
    dataset.push_back(ptr);
    
    // Insert it(its pointer) on every hashtable, according to g hashes
    for (int i=0; i<L; i++){
        //cout << "g(" << i << ") = " << (bitset<32>(g.at(i).hash(p))) << endl;
        uint32_t hashkey = g.at(i).hash(p);
        hashTables.at(i).insert(make_pair(hashkey, ptr));
    }
    //cout << "Point " << ptr->getId() << " was inserted!" << endl;

    /*cout << "Dataset: ";
    for (int i=0; i<dataset.size(); i++){
        dataset.at(i)->printPoint();
        cout << " ";
    }
    cout << endl;
    */
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

void LSH::nearestNeighbour(Point p){
    
    // Loop over the points that have this hash key, and find the nearest
    // TODO : stop after 3L points
    double min = numeric_limits<double>::max();
    int min_id=-1;
    for (int i=0; i<L; i++){
        //cout << "g(" << i << ") = " << (bitset<32>(g.at(i).hash(p))) << endl;
        uint32_t hashkey = g.at(i).hash(p);

        pair<mapIt, mapIt> it = hashTables.at(i).equal_range(hashkey);
        mapIt it1 = it.first;

        int count = 0; 
        while (it1 != it.second){
            count++;

            // Compute the distance between the two points
            double dist = manhattanDistance(p.getCoordinates(), it1->second->getCoordinates());
            if (dist < min){
                min = dist;
                min_id = it1->second->getId();
            }
            it1++;
        }
        cout << "Points in the same bucket on g(" << i << "): " << count << endl;; 
    }

    if (min_id!=-1)
        cout << "NN of " << p.getId() << " is " << min_id << " with distance " << min << endl;
    else
        cout << "NN of " << p.getId() << " is was not found " << endl;
}
