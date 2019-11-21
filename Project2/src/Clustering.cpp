#include <algorithm>
#include <random>
#include <iostream>
#include "../include/Clustering.hpp"

using namespace std;

VectorClustering::VectorClustering(vector<Point*> dataset, int n_clusters, string i, string a, string u):dataset(dataset),n_clusters(n_clusters),initMethod(i),assignMethod(a),updateMethod(u){
    cout << "New instance of Vector Clustering(" << initMethod << "," << assignMethod << "," << updateMethod << ")\n";
}

int VectorClustering::initRandom(){
    cout << "Random initialization..." << endl;

    centroids.clear();

    // Shuffle the dataset into a new vector
    vector<Point*> shuffledDataset = dataset;
    random_device rd;
    default_random_engine rng(rd());
    shuffle(begin(shuffledDataset), end(shuffledDataset), rng);

    // Pick the first k elements from the shuffled vector
    shuffledDataset.resize(n_clusters);
    centroids = shuffledDataset;
}

int VectorClustering::initKMeanspp(){
    cout << "coming soon..." << endl;
}

int VectorClustering::KMeans(){
    // Initialization
    if (!initMethod.compare("random")){
        initRandom();
    }else if (!initMethod.compare("k-means++")){
        initKMeanspp();
    }else{
        cout << "Unknown initMethod" << endl;
        return -1;
    }
}

void VectorClustering::printCentroids(){
    for(int i=0; i<centroids.size(); i++){
        cout << "Point " << centroids.at(i)->getId() << " "<<  endl;
    }
}
