#include <random>
#include <vector>
#include <set>
#include <unordered_map>
#include "../G.hpp"
#include "../Point.hpp"

using namespace std;

typedef unordered_multimap<uint32_t,Point *>::iterator mapIt;

// Class for the implemetation of HyperCube algorithm
class HC{
    private:
        vector<Point*> dataset;
        vector<G> g; // g_1(), g_2(), ..., g_dd()
        vector<unordered_map<uint32_t,bool>> f; // f_1(), f_2(), ..., f_dd()
        unordered_multimap<uint32_t,Point*> cube; // The hashtable
        int dd; // The new dimension that the point is projected to (dd<32)
        int w;
        int d;
        int k;  // Number of f_i's   
        int probes; // Max number of near vertices examined
        int M; // Max number of points examined
        double r; // (radius)

    public:
        HC(int w, int d, int k, int dd, int hd, int M, double r);
        ~HC();

        void insert(Point p);
        uint32_t hash(Point p); // returns a key < 2^dd
        Point *nearestNeighbour(Point p, string distFunc, double &min_dist);
        vector<Point*> nearestNeighbours(Point p, string distFunc, vector<double>& min_dist);
        Point *nearestNeighbourBruteForce(Point p, string distFunc, double &min_dist);
        void answerQuery(Point p, ofstream& out);
        void printCube();
};

set<uint32_t> nearVertices(uint32_t num, int length, int probes);
