#include <unordered_map>
#include "../Point.hpp"
#include "../G.hpp"

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
        void printG(int i);
        
        Point *nearestNeighbour(Point p /* in */, string distFunc /* in */, double& min_dist /* out */); // A-NN
        vector<Point *>nearestNeighbours(Point p /* in */, string distFunc /* in */, vector<double>& min_dist /* out */);
        void answerQuery(Point p);
};

typedef unordered_multimap<uint32_t,Point *>::iterator mapIt;
