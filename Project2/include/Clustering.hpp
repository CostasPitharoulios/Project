#include <vector>
#include <time.h>
#include <limits>
#include "Point.hpp"
#include "Curve.hpp"
#include "dist.hpp"
using namespace std;

class Cluster;

class Clustering{ // TODO name it KMeans? and the function: fit
    private:
        bool curvesFlag; // Define Clustering item type. False: Points, True: Curves
        vector<void*> dataset;

        int n_clusters;
        string initMethod;
        string assignMethod;
        string updateMethod;

        vector<void*> centroids; // TODO delete
        vector<Cluster*> clusters;
    
        double manhattanDistance(vector<double> a, vector<double> b); // to calculate distance between points

    public:
        Clustering(bool curvesFlag, vector<void*>, int n_clusters, string initMethod="random", string assignMethod="lloyd", string updateMethod="mean");

        // Basic functions for clustering
        int KMeans();
        int initRandom();
        int initKMeanspp();
        int assignLloyd();
        int assignReverse();
        int updatePAM();
        int updateMean();

        // Assisting functions
        bool isCentroid(void* item);
        void printCentroids();
        void printClusters();
        double pamCost(vector<void*> items,int centroidIndex);
};

class Cluster{
    private:
        int id;
        void *centroid;
        vector<void*> items;
        bool curvesFlag;

    public:
        Cluster(int id, void *centroid, bool curvesFlag);
        bool assign(void *item);
        void setCentroid(void *item);
        bool removeItem(string id);
        void *getCentroid();
        int getId();
        vector<void*> getItems();
        void printItems();
};
