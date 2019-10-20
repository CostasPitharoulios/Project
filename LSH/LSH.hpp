#include <unordered_map>
#include "../Point.hpp"
#include "G.hpp"

using namespace std;

class LSH{
    private:
        vector<Point> dataset;
        vector<G> g; // g_1(), g_2(), ..., g_L()
        vector<unordered_multimap<uint32_t,Point *>> hashTables;// L hashtables
        int d; // Dimension of points
        int w; // Grid cell size
        int L; // Number of hashfunctions
        int k; // Number of sub-hashfunctions
    public:
        LSH(int w, int d, int k,int L);
        ~LSH();

        void insert(Point p);
        void printG(int i);
        //nearestNeighbor(Point p);
};
