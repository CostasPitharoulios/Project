#include <bitset>
#include <iostream>
#include <limits>
#include "LSH.hpp"
#include "../dist.hpp"

using namespace std;

LSH::LSH(int w, int d, int k, int L):w(w), d(d), k(k), L(L){
    //cout << "Whatap LSH\n";
    for (int i=0; i<L; i++){
        // Create the i-th g() and save it to the vector G
        G g_i(w, d, k);
        g.push_back(g_i);

        // Create the i-th hashaTable and save it to the vector hashTables
        unordered_multimap<uint32_t,Point *> ht;
        hashTables.push_back(ht);
    }
}

LSH::~LSH(){ 
    //cout << "      LSH destructor" << endl;
    for (vector<Point *>::iterator it=dataset.begin(); it != dataset.end(); it++){
        delete *it;
    }
}

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

// TODO mhpws na epestrefe sketo Point? wste o ap e3w na mhn exei prosvash 
// sto dataset. Alla etsi den 3erw ti prepei na epistrepsei otan den vre8ei nn
// (isws ena Point me id = -1)
Point *LSH::nearestNeighbour(Point p, string distFunc, double &min_dist){
    cout << "Finding Nearest Neighbour...\n";
    
    // Loop over the points that have this hash key, and find the nearest
    // TODO : stop after 3L points
    double min = numeric_limits<double>::max();
    Point *min_ptr = nullptr;
    for (int i=0; i<L; i++){
        //cout << "g(" << i << ") = " << (bitset<32>(g.at(i).hash(p))) << endl;
        uint32_t hashkey = g.at(i).hash(p);

        pair<mapIt, mapIt> it = hashTables.at(i).equal_range(hashkey);
        mapIt it1 = it.first;

        int count = 0; 
        while (it1 != it.second){
            count++;

            // Compute the distance between the two points
            double dist;
            if(!distFunc.compare("manh"))
               dist = manhattanDistance(p.getCoordinates(), it1->second->getCoordinates());
            else if(!distFunc.compare("dtw"))
               dist = getDTWfromPoints(&p, it1->second);
            else{
                cout << "Wrong distFunc argument" << endl;
                return nullptr;
            }

            
            if (dist < min){
                min = dist;
                min_ptr = it1->second;
            }
            it1++;
        }
        cout << "Points in the same bucket on g(" << i << "): " << count << endl;; 
    }
    min_dist = min;
    return min_ptr;
}


vector<Point *> LSH::nearestNeighbours(Point p, string distFunc, double r, vector<double>& min_dist){
    cout << "Finding Nearest Neighbours in radious r...\n";
    vector<Point *> neighbours;
    min_dist.clear();
    
    // Loop over the points that have this hash key, and find the nearest
    // TODO : stop after 3L points
    for (int i=0; i<L; i++){
        //cout << "g(" << i << ") = " << (bitset<32>(g.at(i).hash(p))) << endl;
        uint32_t hashkey = g.at(i).hash(p);

        pair<mapIt, mapIt> it = hashTables.at(i).equal_range(hashkey);
        mapIt it1 = it.first;

        int count = 0; 
        while (it1 != it.second){
            count++;

            // Compute the distance between the two points
            double dist;
            if(!distFunc.compare("manh"))
               dist = manhattanDistance(p.getCoordinates(), it1->second->getCoordinates());
            else if(!distFunc.compare("dtw"))
               dist = getDTWfromPoints(&p, it1->second);
            else{
                cout << "Wrong distFunc argument" << endl;
                return neighbours;
            }

            
            if (dist <= r){
                // We found a point in radius r

                // If it has not been already pushed, push it
                bool exists = false;
                for (int i=0; i<neighbours.size(); i++){
                    if (neighbours.at(i)->getId() == it1->second->getId())
                        exists = true;
                }
                if (!exists){
                    neighbours.push_back(it1->second);
                    min_dist.push_back(dist);
                }
            }
            it1++;
        }
        cout << "Points in the same bucket on g(" << i << "): " << count << endl;; 
    }
    return neighbours;
}
