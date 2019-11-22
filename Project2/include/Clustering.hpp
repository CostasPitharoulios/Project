#include <vector>
#include "Point.hpp"
#include "Curve.hpp"

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
        int assignLloyd();
        int assignReverse();
        void printCentroids();
};

class CurveClustering{
    private:
        vector<Curve*> dataset;
        
        int n_clusters;
        string initMethod;
        string assignMethod;
        string updateMethod;

        vector<Curve*> centroids;
    public:
        CurveClustering(vector<Curve*>, int n_clusters, string initMethod="random", string assignMethod="lloyd", string updateMethod="pam");
        int KMeans();
        int initRandom();
        int initKMeanspp();
        void printCentroids();
};
