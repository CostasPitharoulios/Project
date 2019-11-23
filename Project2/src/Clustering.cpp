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
    
    //=======================================================================================
    // The kmeans++ algorithm
    // 1. Pick the first centroid randomly from the data dataset
    // 2. To choose the second centroid, for each item of dataset, calculate the distances
    //    from the closest centroid
    // 3. Make the item with the maximun distance of the nearest centroid, next centroid
    // 4. Repeat for the rest of the Centroids
    //=======================================================================================
    
    cout << "Kmeans++ is here bitchessss" << endl;
    
    // check if the number of clusters given is greater than zero
    if (n_clusters <= 0){
        cout << "ERROR: Number of clusters given is incorrect" << endl;
        return -1;
    }
    
    srand(time(NULL));
    centroids.clear();
 
    
    // we add the first possible centroid to the vector list
    // we are doing this by randomly picking a point/curve of the dataset
    int numbData = dataset.size();
    int randNumber = rand()%(numbData+1);                           // range is [0...maximun number of items-1]
    if(!curvesFlag)                                                 // if we have points
        centroids.push_back((Point*)dataset.at(randNumber));
    else                                                            // if we have curves
        centroids.push_back((Curve*)dataset.at(randNumber));

  
    // computing the remaining n_clusters-1 centroids
    for (int cIt=1; cIt < n_clusters; cIt++){
        
        void* nextCentroid;
        for (int i=0; i< numbData; i++){
            
            // computing all the distances from this item to each centroid
            // and then keeping the shortest distance
            double maxOfMinDistances =  std::numeric_limits<double>::min();
            double minDistance =  std::numeric_limits<double>::max();
            for (int j=0; j< centroids.size(); j++){
                double tempDistance;
                if(!curvesFlag)                                     // if we have points
                    tempDistance = manhattanDistance(((Point*)dataset.at(i))->getCoordinates(), ((Point*)centroids.at(j))->getCoordinates());
                else                                                // if we haev curves
                    tempDistance = getValueDTW((Curve*)dataset.at(i),(Curve*)centroids.at(j));
               
                if (tempDistance < minDistance)
                    minDistance = tempDistance;
            }
            // Our aim is, to keep the item with the longest distance from the closest centroid
            if (minDistance > maxOfMinDistances){
                maxOfMinDistances = minDistance;
                if (!curvesFlag)                                     // if we have points
                    nextCentroid = ((Point*)dataset.at(i));
                else                                                 // if we have curves
                    nextCentroid = ((Curve*)dataset.at(i));
            }
        }
        // pushing back new centroid to the vector list of centroids
        if (!curvesFlag)                                     // if we have points
            centroids.push_back((Point*)nextCentroid);
        else                                                  // if we have curves
            centroids.push_back((Curve*)nextCentroid);
    }
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

double Clustering::getValueDTW(Curve* queryCurve,Curve* inputCurve){
    int m1,m2;
    m1 = queryCurve->getNumberOfCoordinates(); // m1 keeps the number of coordinates of query curve
    m2 = inputCurve->getNumberOfCoordinates(); // m2 keeps the number of coordinates of input curve
    
    double arrayDTW[m1][m2];
    
    
    // initialization  first line
    double previousSum = 0.0; // keeps the sum of previous items
    double x1,y1; // cordinates of first point of query curve
    x1 = queryCurve->getSpecificXCoord(0);
    y1 = queryCurve->getSpecificYCoord(0);
    for (int i=0; i< m2; i++){
        double x2,y2;
        x2 = inputCurve->getSpecificXCoord(i);
        y2 = inputCurve->getSpecificYCoord(i);
        arrayDTW[0][i] = previousSum + distance(x1,x2,y1,y2);
        
        previousSum += arrayDTW[0][i];
    }
    
    //initializing first column
    previousSum = arrayDTW[0][0];
    double x2, y2;
    x2 = inputCurve->getSpecificXCoord(0);
    y2 = inputCurve->getSpecificYCoord(0);
    for (int i=1; i<m1; i++){
        x1 = queryCurve->getSpecificXCoord(i);
        y1 = queryCurve->getSpecificYCoord(i);
        arrayDTW[i][0] = previousSum + distance(x1,x2,y1,y2);
        
        previousSum += arrayDTW[i][0];
    }
    
    for (int i=1; i<m1; i++ ){
        for (int j=1; j<m2; j++){
            x1 = queryCurve->getSpecificXCoord(i);
            x2 = inputCurve->getSpecificXCoord(j);
            y1 = queryCurve->getSpecificYCoord(i);
            y2 = inputCurve->getSpecificYCoord(j);
            arrayDTW[i][j] = min(min(arrayDTW[i-1][j],arrayDTW[i-1][j-1]), arrayDTW[i][j-1]) + distance(x1,x2,y1,y2);
        }
    }
    
    //cout << "dtw of curve is: " << arrayDTW[m1-1][m2-1];
    
    return arrayDTW[m1-1][m2-1];
    
    
}



