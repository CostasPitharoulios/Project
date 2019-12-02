#pragma once
#include <unordered_map>
#include <fstream>
#include "Point.hpp"
#include "G.hpp"

using namespace std;

// Class for the implementation of LSH hashing algorithm
class LSH{
    private:
        vector<Point*> dataset;
        vector<G> g; // g_1(), g_2(), ..., g_L()
        vector<unordered_multimap<uint32_t,Point *> > hashTables;// L hashtables
        int d; // Dimension of points
        int w; // Grid cell size
        int L; // Number of hashfunctions
        int k; // Number of sub-hashfunctions
        double r; // (Radius)
    public:
        LSH(int w, int d, int k,int L, double r);
        ~LSH();

        void insert(Point p);
        void insert(Point *p);
        void printG(int i);
        
        void assignBucket(Point *p);
        Point *nearestNeighbour(Point p /* in */, string distFunc /* in */, double& min_dist /* out */); // A-NN
        vector<Point *>nearestNeighbours(Point p /* in */, string distFunc /* in */, vector<double>& min_dist /* out */);
        Point *nearestNeighbourBruteForce(Point p /* in */, string distFunc /* in */, double& min_dist /* out */); // NN
        void answerQuery(Point p, ofstream& out);
        //void printOutput(ofstream& out, int q_id, int nn_id, double lsh_dist, double true_dist, double lsh_time, double true_time, vector<Point*> rnn);
};

typedef unordered_multimap<uint32_t,Point *>::iterator mapIt;
