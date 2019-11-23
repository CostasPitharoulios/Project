#include <algorithm>
#include <iostream>
#include <limits>
#include <random>
#include "../include/Clustering.hpp"
#include "../include/dist.hpp"

using namespace std;

Clustering::Clustering(bool curvesFlag, vector<void*> dataset, int n_clusters, string i, string a, string u):curvesFlag(curvesFlag),dataset(dataset),n_clusters(n_clusters),initMethod(i),assignMethod(a),updateMethod(u){
    cout << "New instance of Clustering(" << initMethod << "," << assignMethod << "," << updateMethod << ")\n";
}

int Clustering::initRandom(){
    cout << "Random initialization..." << endl;

    centroids.clear();

    // Shuffle the dataset into a new vector
    vector<void*> shuffledDataset = dataset;
    random_device rd;
    default_random_engine rng(rd());
    shuffle(begin(shuffledDataset), end(shuffledDataset), rng);

    // Pick the first k elements from the shuffled vector
    shuffledDataset.resize(n_clusters);
    centroids = shuffledDataset;

    // For every centroid: assign it to it self
    for(int i=0; i<centroids.size(); i++){
        if(!curvesFlag)
            ((Point*)centroids.at(i))->assign((Point*)centroids.at(i));
        else
            ((Curve*)centroids.at(i))->assign((Curve*)centroids.at(i));
    }
    
}

int Clustering::initKMeanspp(){
    cout << "Kmeans++ is here bitchessss" << endl;
    
    if (n_clusters <= 0){
        cout << "ERROR: Number of clusters given is incorrect" << endl;
        return -1;
    }
    
    centroids.clear();
    centroids = dataset;
    printCentroids();
#if 0
    // we add the first possible centroid to the vector list
    // we are doing this by randomly picking a point/curve of the dataset
    int randNumber = rand()%(n_clusters+1); // range is [0...n_clusters
    //centroids.push_back((Point*)dataset.at(randNumber));
    ((Point*)centroids.at(0))->assign((Point*)dataset.at(randNumber));
    this->printCentroids();
    
    
    int numbData = dataset.size();
    cout << "number of data:" << numbData << endl;
    // computing the remaining n_clusters-1 centroids
    for (int cIt=1; cIt <n_clusters; cIt++){
        // creating a vector to store distances of data points/curves from nearest centroid
        //vector<double> dist;
        cout << "heyyyyyyyyyy" << endl;
        Point* nextCentroid;
        for (int i=0; i< numbData; i++){
            
            // computing all the distances from this point to each centroid
            // and then keeping the shortest distance
            double maxOfMinDistances =  std::numeric_limits<double>::min();
            double minDistance =  std::numeric_limits<double>::max();
            for (int j=0; j< 2; j++){
                double tempDistance = manhattanDistance(((Point*)dataset.at(i))->getCoordinates(), ((Point*)centroids.at(j))->getCoordinates());
                cout << "TempdISTANCE:" << tempDistance << endl;
                if (tempDistance < minDistance)
                    minDistance = tempDistance;
            }
           // dist.push_back(minDistance);
            if (minDistance > maxOfMinDistances){
                maxOfMinDistances = minDistance;
                nextCentroid = ((Point*)dataset.at(i));
            }
            cout << "MIN: " << minDistance << endl;
            
        }
       // cout << "NEXT" <<
        centroids.push_back((Point*)nextCentroid);
        cout << "NOW" <<endl;
        this->printCentroids();
    }
    cout << "SIZE: " << centroids.size() << endl;
    this->printCentroids();
    cout << "end" << endl;
#endif
}

int Clustering::assignLloyd(){
    cout << "Assigning to centroids..." << endl;

    // For every item
    for(int j=0; j<dataset.size(); j++){

        //if(curvesFlag) cout << "We at ::" <<((Curve*)dataset.at(j))->getId()  <<  endl;

        // If its not centroid
        if(!isCentroid(dataset.at(j))){
            // Find the centroid with the least distance and assign it
            double min = numeric_limits<double>::max();
            for(int i=0; i<centroids.size(); i++){
                double dist;
                if(!curvesFlag){
                    dist = manhattanDistance(((Point*)dataset.at(j))->getCoordinates(),((Point*)centroids.at(i))->getCoordinates());
                    if(dist<min){
                        min = dist;
                        ((Point*)dataset.at(j))->assign((Point*)centroids.at(i));
                    }
                } 
                else{
                    dist = getValueDTW((Curve*)dataset.at(j),(Curve*)centroids.at(i));
                    //cout << " Distance between " << ((Curve*)dataset.at(j))->getId() << " and " << ((Curve*)centroids.at(i))->getId() << " is " << dist << endl;
                    if(dist<min){
                        min = dist;
                        ((Curve*)dataset.at(j))->assign((Curve*)centroids.at(i));
                    }
                }
            }
            //if(curvesFlag) cout << "Closest: " <<((Curve*)dataset.at(j))->getCentroid()->getId() << " with distance " << min   <<  endl;
        }
    }
    printClusters();
    cout << endl;
}

bool Clustering::isCentroid(void* item){
    if(!curvesFlag)
        return (((Point*)item)->getCentroid() == (Point*)item);
    else
        return (((Curve*)item)->getCentroid() == (Curve*)item);
}

int Clustering::assignReverse(){
    cout << "Assign Reverse coming soon..." << endl;
}

int Clustering::KMeans(){
    // Initialization
    if (!initMethod.compare("random")){
        initRandom();
    }else if (!initMethod.compare("k-means++")){
        initKMeanspp();
    }else{
        cout << "Unknown initMethod" << endl;
        return -1;
    }

    cout << "Initial Centroids:" << endl;
    printCentroids();

    // Assignment
    if (!assignMethod.compare("lloyd")){
        assignLloyd();
    }else if (!assignMethod.compare("reverse")){
        assignReverse();
    }else{
        cout << "Unknown assignMethod" << endl;
        return -1;
    }
}

void Clustering::printCentroids(){
    for(int i=0; i<centroids.size(); i++){
        if(!curvesFlag)
            cout << ((Point*)centroids.at(i))->getId() << ", "<<  endl;
        else
            cout << ((Curve*)centroids.at(i))->getId() << ", "<<  endl;
    }
}

void Clustering::printClusters(){
    for(int i=0; i<centroids.size(); i++){
        if(!curvesFlag){
            cout << "Cluster of ";
            cout << ((Point*)centroids.at(i))->getId() << ": "<<  endl;
            for(int j=0; j<dataset.size(); j++){
                if(((Point*)dataset.at(j))->getCentroid() == (Point*)centroids.at(i)){
                    cout << "{" << ((Point*)dataset.at(j))->getId() << "}, ";
                }
            }
            cout << endl;
        }else{
            cout << "Cluster of ";
            cout << ((Curve*)centroids.at(i))->getId() << ": "<<  endl;
            for(int j=0; j<dataset.size(); j++){
                if(((Curve*)dataset.at(j))->getCentroid() == (Curve*)centroids.at(i)){
                    cout << "{" << ((Curve*)dataset.at(j))->getId() << "}, ";
                }
            }
            cout << endl;
        }
    }
}

double Clustering::manhattanDistance(vector<double> a, vector<double> b){
    double dist = 0;
    if (a.size() < b.size()){
        for (int i=0; i<a.size(); i++){
            dist += abs(a.at(i) - b.at(i));
           // cout <<"INSIDE " << a.at(i) << " " << b.at(i) << endl;
        }
    }
    else {
        for (int i=0; i<b.size(); i++){
            dist += abs(a.at(i) - b.at(i));
            //cout <<"INSIDE " << a.at(i) << " " << b.at(i) << endl;
        }
    }
    return dist;
}
