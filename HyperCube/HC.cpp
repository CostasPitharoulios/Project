#include <bitset>
#include <ctime>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <random>
#include <set>
#include "HC.hpp"
#include "../dist.hpp"
#include "../util.hpp"

using namespace std;

HC::HC(int w, int d, int k, int dd, int probes, int M, double r):w(w), d(d), k(k), dd(dd), probes(probes), M(M), r(r){
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

// return vertices of Hamming distance == hd
set<uint32_t> nearVertices(uint32_t num, int length, int hd){
    set<uint32_t> s;
    if(hd == 0){
        s.insert(num);
        return s;
    }

    // Loop over the bits of num
    uint32_t mask,num1;
    for (int i=0; i<length; i++){
        // Mask to get one bit
        mask = pow(2,i);
        //cout << "mask=\t" <<  bitset<32>(mask) << endl;

        // Flip the i-th bit in num
        num1 = num^mask;
        //cout << "=>num1=\t" <<  bitset<32>(num1) << endl;

        set<uint32_t> s_deeper = nearVertices(num1, length, hd-1);

        // Unite s with s_deeper
        s.insert(s_deeper.begin(), s_deeper.end());
    }
    return s;
}





// Recursice function to find near Vertices of the hypercube with
// Hamming distance = probes //TODO kanonika prepei na einai probes ta sunolika vertices pou 8a elextoun
// ... ara probes <= 2^n - 1
/*set<uint32_t> nearVertices(uint32_t num, int length, int probes){
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
}*/

Point *HC::nearestNeighbour(Point p, string distFunc, double &min_dist){
    //cout << "Finding Nearest Neighbour...\n";
    
    uint32_t hashkey = hash(p);
    //cout << "hashkey=" << (bitset<32>(hashkey)) << endl;
    double min = numeric_limits<double>::max();
    Point *min_ptr=nullptr;

    // Compute a set of vertices with hamming distance < hd
    // Loop over the points that were hashed in the same vertice, or in a 
    // vertice with a certain hamming distance.
    int pointscount = 0; 
    int verticescount = 0; 

    int hd=0;
    // Loop over vertices of hamming distance == hd (starting at 0)
    while(verticescount<probes && pointscount<M){
        set<uint32_t> s = nearVertices(hashkey, dd, hd);
        set<uint32_t>::iterator itr;

        // For every vertive in hamming distance hd, check the points
        for(itr = s.begin(); itr!=s.end(); itr++){
            if(verticescount>=probes || pointscount>=M) 
                break;

            uint32_t vertice = (*itr);
            //cout << "  Checking vertice " << vertice  << " " << bitset<32>(vertice)<< endl;
     
            pair<mapIt, mapIt> it = cube.equal_range(vertice);
            mapIt it1 = it.first;

            // Loop over the points of this vertice
            while (it1 != it.second){

                if(pointscount>=M)
                    break;

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
        hd++;
    }
    //cout << "Examined " << verticescount << " vertices. (";
    //cout << pointscount << " Points in total)." << endl;
    min_dist = min;
    return min_ptr;
}

vector<Point *> HC::nearestNeighbours(Point p, string distFunc, vector<double> &min_dist){
    //cout << "Finding Nearest Neighbours in radius r...\n";
    
    uint32_t hashkey = hash(p);
    //cout << "hashkey=" << (bitset<32>(hashkey)) << endl;
    vector<Point *> neighbours;
    min_dist.clear(); 

    // Compute a set of vertices with hamming distance < hd
    // Loop over the points that were hashed in the same vertice, or in a 
    // vertice with a certain hamming distance.
    int pointscount = 0; 
    int verticescount = 0; 

    int hd=0;
    // Loop over vertices of hamming distance == hd (starting at 0)
    while(verticescount<probes && pointscount<M){
        set<uint32_t> s = nearVertices(hashkey, dd, hd);
        set<uint32_t>::iterator itr;

        // For every vertive in hamming distance hd, check the points
        for(itr = s.begin(); itr!=s.end(); itr++){
            if(verticescount>=probes || pointscount>=M) 
                break;

            uint32_t vertice = (*itr);
            //cout << "  Checking vertice " << vertice  << " " << bitset<32>(vertice)<< endl;
     
            pair<mapIt, mapIt> it = cube.equal_range(vertice);
            mapIt it1 = it.first;

            // Loop over the points of this vertice
            while (it1 != it.second){

                if(pointscount>=M)
                    break;

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
        hd++;
    }

    //cout << "Examined " << verticescount << " vertices. (";
    //cout << pointscount << " Points in total)." << endl;
    return neighbours;
}

Point *HC::nearestNeighbourBruteForce(Point p, string distFunc, double &min_dist){
    //cout << "Finding Nearest Neighbour with brute force...\n";

    double min = numeric_limits<double>::max();
    Point *min_ptr = nullptr;
    vector<double> coords = p.getCoordinates();
    for (int i=0; i<dataset.size(); i++){
        double dist = manhattanDistance(dataset.at(i)->getCoordinates(), coords);
        if (dist < min){
            min = dist;
            min_ptr = dataset.at(i);
        }
    }
    min_dist = min;
    return min_ptr;
}

void HC::printCube(){
    cout << "Cube:\n";
    mapIt it = cube.begin(); 
  
    for (; it != cube.end(); it++) 
        cout << "<" << it->first << ", " << it->second 
             << ">  "; 
  
    cout << endl;
}


void HC::answerQuery(Point p, ofstream& out){
    clock_t start = clock();
    double dist, true_dist;
    vector<Point *> rnn;

    // Find its A-NN
    Point *nn = nearestNeighbour(p,"manh",dist);
    clock_t end = clock();

    /*if (nn!=nullptr)
        cout << "NN of " << p.getId() << " is " << nn->getId() << " with distance " << dist << endl;
    else
        cout << "NN of " << p.getId() << " is was not found " << endl;
        */

    // Find neighbours in radius r
    if(r>=0){
        vector<double> dist;
        rnn = nearestNeighbours(p,"manh",dist);

        /*if ( rnn.size()==0 ){
            cout << "NN of " << p.getId() << " in radius " << r << " is was not found " << endl;
        }else{
            cout << "NN of " << p.getId() << " in radius " << r << " are: " << endl;
            for (int i=0; i<rnn.size(); i++){
                cout << "- " << rnn.at(i)->getId() << " with distance " << dist.at(i) << endl;
            }
        }
        */
    }

    long double time_ms = 1000.0 * (end-start) / CLOCKS_PER_SEC;
    //cout << "CPU time: " << time_ms << " ms" << endl;

    // Find its NN using brute force
    start = clock();
    Point *true_nn = nearestNeighbourBruteForce(p,"manh",true_dist);
    end = clock();
    double true_time_ms = 1000.0 * (end-start) / CLOCKS_PER_SEC;

    printOutput(out, p.getId(), nn->getId(), dist, true_dist, time_ms, true_time_ms, rnn);
}
