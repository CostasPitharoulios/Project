#include <bitset>
#include <cmath>
#include <ctime>
#include <iostream>
#include <random>
#include <set>
#include "HC.hpp"
#include "../dist.hpp"

using namespace std;

HC::HC(int w, int d, int k, int dd, int hd):w(w), d(d), k(k), dd(dd), hd(hd){
    //random_device rd; // seed
    //mt19937 gen(rd());
    //uniform_int_distribution<> dis(0,1);

    for (int i=0; i<dd; i++){
        // Create the i-th g()
        G g_i(w, d, k);
        g.push_back(g_i);

        // Create the i-th f() and save it to the vector
        unordered_map<uint32_t,bool> f_i;
        f.push_back(f_i);

        // Generate 2^32 random bools
        // BASIKA OXI, AUTO 8A GINEI KATA TO HASHING
        /*for (int key=0; key<pow(2,32); key++){
            f_i[key] = dis(gen);
            cout << "f" << i << "[" << key << "] = " << f_i[key] << endl;
        }
        */
    }
}


void HC::insert(Point p){
    Point *ptr = new Point(p);
    // Save point to the dataset vector
    dataset.push_back(ptr);
    // Insert it(its pointer) on every hashtable, according to g hashes

    uint32_t hashkey = hash(p); // Hashkey is in [0,2^dd)
    //cout << "hashkey=" << (bitset<32>(hashkey)) << endl;

    cube.insert(make_pair(hashkey, ptr));
}

uint32_t HC::hash(Point p){
    uint32_t key=0;
    for (int i=0; i<dd; i++){
        uint32_t gp = g.at(i).hash(p);
        //cout << "g(" << i << ") = " << (bitset<32>(gp)) << endl;

        // Look if g_i(p) exists as key in f_i(). If not, insert it
        if (f.at(i).find(gp) == f.at(i).end()){
            f.at(i)[gp] = rand()%2; // rand()%2 is uniform
            //cout << "New set f" << i << "[" << gp << "] = " << f.at(i)[gp] << endl;
        }
        //else{
            //cout << "Old set f" << i << "[" << gp << "] = " << f.at(i)[gp] << endl;
        //}

        // Push back the f() bit to the key
        key = key<<1;
        key = key | f.at(i)[gp];
    }
    return key;
}

// Recursice function to find near Vertices of the hypercube with
// Hamming distance = probes
set<uint32_t> nearVertices(uint32_t num, int length, int probes){
    set<uint32_t> s;
    s.insert(num);
    if(probes == 0)
        return s;

    // Loop over the bits of num
    uint32_t mask,num1;
    for (int i=0; i<length; i++){
        // Mask to get one bit
        mask = pow(2,i);
        //cout << "mask=\t" <<  bitset<32>(mask) << endl;

        // Flip the i-th bit in num
        num1 = num^mask;
        //cout << "=>num1=\t" <<  bitset<32>(num1) << endl;

        set<uint32_t> s_deeper = nearVertices(num1, length, probes-1);

        // Unite s with s_deeper
        s.insert(s_deeper.begin(), s_deeper.end());
    }
    return s;
}

void HC::nearestNeighbour(Point p){
    cout << "Finding Nearest Neighbour...\n";
    
    uint32_t hashkey = hash(p);
    cout << "hashkey=" << (bitset<32>(hashkey)) << endl;
    double min = numeric_limits<double>::max();
    int min_id=-1;

    // Compute a set of vertices with hamming distance < hd
    set<uint32_t> s = nearVertices(hashkey, dd, hd);
    set<uint32_t>::iterator itr;
    // Loop over the points that were hashed in the same vertice, or in a 
    // vertice with a certain hamming distance.
    // TODO : stop after 3L points
    int pointscount = 0; 
    int verticescount = 0; 
    for(itr = s.begin(); itr!=s.end(); itr++){
        uint32_t vertice = (*itr);
 
        pair<mapIt, mapIt> it = cube.equal_range(vertice);
        mapIt it1 = it.first;

        while (it1 != it.second){
            // Compute the distance between the two points
            double dist = manhattanDistance(p.getCoordinates(), it1->second->getCoordinates());
            if (dist < min){
                min = dist;
                min_id = it1->second->getId();
            }
            pointscount++;
            it1++;
        }
        verticescount++;
    }
    cout << "Examined " << verticescount << " vertices. (" << pointscount << " Points in total)." << endl;

    if (min_id!=-1)
        cout << "NN of " << p.getId() << " is " << min_id << " with distance " << min << endl;
    else
        cout << "NN of " << p.getId() << " is was not found " << endl;
}

void HC::printCube(){
    cout << "Cube:\n";
    mapIt it = cube.begin(); 
  
    for (; it != cube.end(); it++) 
        cout << "<" << it->first << ", " << it->second 
             << ">  "; 
  
    cout << endl;
}
