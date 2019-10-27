#include <bitset>
#include <ctime>
#include <cmath>
#include <ctime>
#include <iostream>
#include <random>
#include <set>
#include "HC.hpp"
#include "../dist.hpp"

using namespace std;

HC::HC(int w, int d, int k, int dd, int hd, double r):w(w), d(d), k(k), dd(dd), hd(hd), r(r){
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

HC::~HC(){
    for(int i=0; i<dataset.size(); i++){
        delete dataset.at(i);
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
// Hamming distance = probes //TODO kanonika prepei na einai probes ta sunolika vertices pou 8a elextoun
// ... ara probes <= 2^n - 1
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

Point *HC::nearestNeighbour(Point p, string distFunc, double &min_dist){
    cout << "Finding Nearest Neighbour...\n";
    
    uint32_t hashkey = hash(p);
    //cout << "hashkey=" << (bitset<32>(hashkey)) << endl;
    double min = numeric_limits<double>::max();
    Point *min_ptr=nullptr;

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
            pointscount++;
            it1++;
        }
        verticescount++;
    }
    cout << "Examined " << verticescount << " vertices. (";
    cout << pointscount << " Points in total)." << endl;
    min_dist = min;
    return min_ptr;
}

vector<Point *> HC::nearestNeighbours(Point p, string distFunc, vector<double> &min_dist){
    cout << "Finding Nearest Neighbours in radius r...\n";
    
    uint32_t hashkey = hash(p);
    //cout << "hashkey=" << (bitset<32>(hashkey)) << endl;
    vector<Point *> neighbours;
    min_dist.clear(); 

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
            pointscount++;
            it1++;
        }
        verticescount++;
    }
    cout << "Examined " << verticescount << " vertices. (";
    cout << pointscount << " Points in total)." << endl;
    return neighbours;
}

void HC::printCube(){
    cout << "Cube:\n";
    mapIt it = cube.begin(); 
  
    for (; it != cube.end(); it++) 
        cout << "<" << it->first << ", " << it->second 
             << ">  "; 
  
    cout << endl;
}


void HC::answerQuery(Point p){
    clock_t start = clock();
    // Find nearest neighbour(s)
    if ( r==-1){ // if r is not given as argument
        // Find its A-NN
        double dist;
        Point *nn = nearestNeighbour(p,"manh",dist);

        if (nn!=nullptr)
            cout << "NN of " << p.getId() << " is " << nn->getId() << " with distance " << dist << endl;
        else
            cout << "NN of " << p.getId() << " is was not found " << endl;
    }else{
        vector<double> dist;
        vector<Point *> rnn = nearestNeighbours(p,"manh",dist);

        if ( rnn.size()==0 ){
            cout << "NN of " << p.getId() << " in radius " << r << " is was not found " << endl;
        }else{
            cout << "NN of " << p.getId() << " in radius " << r << " are: " << endl;
            for (int i=0; i<rnn.size(); i++){
                cout << "- " << rnn.at(i)->getId() << " with distance " << dist.at(i) << endl;
            }
        }
    }
    clock_t end = clock();
    long double time_ms = 1000.0 * (end-start) / CLOCKS_PER_SEC;
    cout << "CPU time: " << time_ms << " ms" << endl;
}
