#include <vector>
#include <time.h>
#include <limits>
#include "Point.hpp"
#include "Curve.hpp"
using namespace std;

class Clustering{
    private:
        bool curvesFlag; // Define Clustering item type. False: Points, True: Curves
        vector<void*> dataset;

        int n_clusters;
        string initMethod;
        string assignMethod;
        string updateMethod;

        vector<void*> centroids;
    
        double manhattanDistance(vector<double> a, vector<double> b); // to calculate distance between points
    double getValueDTW(Curve* queryCurve,Curve* inputCurve);
    public:
        Clustering(bool curvesFlag, vector<void*>, int n_clusters, string initMethod="random", string assignMethod="lloyd", string updateMethod="pam");

        // Basic functions for clustering
        int KMeans();
        int initRandom();
        int initKMeanspp();
        int assignLloyd();
        int assignReverse();

        // Assisting functions
        bool isCentroid(void* item);
        void printCentroids();
        void printClusters();
};
