#include <bitset>
#include <ctime>
#include <iostream>
#include <limits>
#include <fstream>
#include "../include/dist.hpp"
#include "../include/util.hpp"
#include "../include/LSH.hpp"
#include "../include/Clustering.hpp"

using namespace std;

LSH::LSH(int w, int d, int k, int L, double r):w(w), d(d), k(k), L(L), r(r){
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

void LSH::insert(Point *ptr){
    // Save point to the dataset vector
    dataset.push_back(ptr);
    
    // Insert it(its pointer) on every hashtable, according to g hashes
    for (int i=0; i<L; i++){
        //cout << "g(" << i << ") = " << (bitset<32>(g.at(i).hash(p))) << endl;
        uint32_t hashkey = g.at(i).hash(*ptr);
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

// Assign every point that is on the same bucket with centroid p to it
void LSH::assignBucket(Point *p){
    string distFunc="manh";
    for (int i=0; i<L; i++){
        //cout << "g(" << i << ") = " << (bitset<32>(g.at(i).hash(p))) << endl;
        uint32_t hashkey = g.at(i).hash(*p);

        pair<mapIt, mapIt> it = hashTables.at(i).equal_range(hashkey);
        mapIt it1 = it.first;

        int count = 0;
        while (it1 != it.second){
            //cout << "Point " << it1->second->getId() << " is in the same bucket(" << i << ")" << endl;
            count++;

            // If its not a centroid
            if(!isCentroid((void*) it1->second, false)){

                // Compute the distance between the two points
                double dist = manhattanDistance(p->getCoordinates(), it1->second->getCoordinates());

                // If it is the first assignment, do it
                if(!it1->second->getChanged()){
                    //cout << "Point " << it1->second->getId() << " will be assigned to " << p->getCluster()->getId() << endl;
                    p->getCluster()->assign(it1->second);
                    it1->second->setChanged();
                    it1->second->setDist(dist);
                }else{
                    //cout << "Point " << it1->second->getId() << " was already done" << endl;
                   
                    // If its closer, assign it to this new cluster 
                    //cout << dist << " vs " << it1->second->getDist() << endl;
                    if (dist < it1->second->getDist()){
                        p->getCluster()->assign(it1->second);
                        it1->second->setDist(dist);
                    }
                }
            }
            it1++;
        }
        //cout << "Points in the same bucket on g(" << i << "): " << count << endl; 
    }
}

// Assign every Curve that is on the same bucket with centroid p to it
void LSH::assignBucketCurves(Point *p){
    for (int i=0; i<L; i++){
        //cout << "g(" << i << ") = " << (bitset<32>(g.at(i).hash(*p))) << endl;
        uint32_t hashkey = g.at(i).hash(*p);

        pair<mapIt, mapIt> it = hashTables.at(i).equal_range(hashkey);
        mapIt it1 = it.first;

        int count = 0;
        while (it1 != it.second){
            //cout << "Point " << it1->second->getId() << " is in the same bucket(" << i << ")" << endl;
            count++;

            // If its not a centroid
            if(!isCentroid((void*) it1->second->getOrigin(), true)){

                // Compute the distance between the two points
                double dist = getDTWfromPoints(p, it1->second);

                // If it is the first assignment, do it
                if(!it1->second->getOrigin()->getChanged()){
                    //cout << "Point " << it1->second->getId() << " will be assigned to " << p->getCluster()->getId() << endl;
                    p->getOrigin()->getCluster()->assign(it1->second->getOrigin());
                    it1->second->getOrigin()->setChanged();
                    it1->second->getOrigin()->setDist(dist);
                }else{
                   
                    // If its closer, assign it to this new cluster 
                    //cout << dist << " vs " << it1->second->getOrigin()->getDist() << endl;
                    if (dist < it1->second->getOrigin()->getDist()){
                        //cout << "Curve " << it1->second->getOrigin()->getId() << " will change cluster" << endl;
                        p->getOrigin()->getCluster()->assign(it1->second->getOrigin());
                        it1->second->getOrigin()->setDist(dist);
                    }
                }
            }
            it1++;
        }
        //cout << "Points in the same bucket on g(" << i << "): " << count << endl; 
    }
}


Point *LSH::nearestNeighbour(Point p, string distFunc, double &min_dist){
    //cout << "Finding Nearest Neighbour...\n";
    
    // Loop over the points that have this hash key, and find the nearest
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
        //cout << "Points in the same bucket on g(" << i << "): " << count << endl;; 
    }
    min_dist = min;
    return min_ptr;
}

Point *LSH::nearestNeighbourBruteForce(Point p, string distFunc, double &min_dist){
    //cout << "Finding Nearest Neighbour with Brute Force...\n";

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


vector<Point *> LSH::nearestNeighbours(Point p, string distFunc, vector<double>& min_dist){
    //cout << "Finding Nearest Neighbours in radious r...\n";
    vector<Point *> neighbours;
    min_dist.clear();
    
    // Loop over the points that have this hash key, and find the nearest
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
        //cout << "Points in the same bucket on g(" << i << "): " << count << endl;; 
    }
    return neighbours;
}

void LSH::answerQuery(Point p, ofstream& out){
    double dist, true_dist;
    vector<Point*> rnn;

    // Find its A-NN
    clock_t start = clock();
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

        /*
        if ( rnn.size()==0 ){
            cout << "NN of " << p.getId() << " in radius " << r << " is was not found " << endl;
        }else{
            cout << "NN of " << p.getId() << " in radius " << r << " are: " << endl;
            for (int i=0; i<rnn.size(); i++){
                cout << "- " << rnn.at(i)->getId() << " with distance " << dist.at(i) << endl;
            }
        }
        */
    }
    double time_ms = 1000.0 * (end-start) / CLOCKS_PER_SEC;
    //cout << "CPU time: " << time_ms << " ms" << endl;

    // Find its NN using brute force
    start = clock();
    Point *true_nn = nearestNeighbourBruteForce(p,"manh",true_dist);
    end = clock();
    double true_time_ms = 1000.0 * (end-start) / CLOCKS_PER_SEC;

    printOutput(out, p.getId(), nn->getId(), dist, true_dist, time_ms, true_time_ms, rnn);

}

