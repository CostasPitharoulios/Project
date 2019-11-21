#include <vector>
#include "Point.hpp"

using namespace std;

class VectorClustering{
    private:
        vector<Point*> dataset;
        
        int n_clusters;
        string initMethod;
        string assignMethod;
        string updateMethod;

        vector<Point*> centroids;
    public:
        VectorClustering(vector<Point*>, int n_clusters, string initMethod="random", string assignMethod="lloyd", string updateMethod="pam");
        int KMeans();
        int initRandom();
        int initKMeanspp();
        void printCentroids();
};

/*
class CurveClustering{
    private:
        vector<Curve*> dataset;
        
        string initMethod;
        string assignMethod;
        string updateMethod;
    public:
        CurveClustering(vector<Curve*>,string,string,string);
};
*/
