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
        // Make cluster
        clusters.push_back(new Cluster(i,centroids.at(i),curvesFlag));

        // TODO maybe delete those: (and assignment data member of points/curves)
        if(!curvesFlag)
            ((Point*)centroids.at(i))->assign((Point*)centroids.at(i));
        else{
            //cout << "centroid curve: ";
            //((Curve*)centroids.at(i))->printCoordinates();
            ((Curve*)centroids.at(i))->assign((Curve*)centroids.at(i));
        }
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
    clusters.push_back(new Cluster(0,dataset.at(randNumber),curvesFlag));
    // TODO maybe delete those: (and assignment data member of points/curves)
    if(!curvesFlag)
        ((Point*)dataset.at(randNumber))->assign((Point*)dataset.at(randNumber));
    else
        ((Curve*)dataset.at(randNumber))->assign((Curve*)dataset.at(randNumber));


  
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
                else                                                // if we have curves
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
        // Make cluster
        clusters.push_back(new Cluster(cIt,nextCentroid,curvesFlag));
        // TODO maybe delete those: (and assignment data member of points/curves)
        if(!curvesFlag)
            ((Point*)nextCentroid)->assign((Point*)nextCentroid);
        else
            ((Curve*)nextCentroid)->assign((Curve*)nextCentroid);
    }
}

int Clustering::assignLloyd(){
    cout << "Assigning to clusters..." << endl;

    // For every item
    for(int j=0; j<dataset.size(); j++){

        //if(curvesFlag) cout << "We at ::" <<((Curve*)dataset.at(j))->getId()  <<  endl;

        // If its not centroid
        if(!isCentroid(dataset.at(j))){
            // Find the centroid with the least distance and assign it
            double min = numeric_limits<double>::max();
            int pos = -1;
            for(int i=0; i<clusters.size(); i++){
                double dist;
                if(!curvesFlag){
                    dist = manhattanDistance(((Point*)dataset.at(j))->getCoordinates(),(((Point*)(clusters.at(i)->getCentroid()))->getCoordinates()));
                    if(dist<min){
                        min = dist;
                        pos = i;
                        ((Point*)dataset.at(j))->assign((Point*)(clusters.at(i)->getCentroid()));
                    }
                } 
                else{
                    dist = getValueDTW((Curve*)dataset.at(j),(Curve*)(clusters.at(i)->getCentroid()));
                    //cout << " Distance between " << ((Curve*)dataset.at(j))->getId() << " and " << ((Curve*)(clusters.at(i)->getCentroid()))->getId() << " is " << dist << endl;
                    if(dist<min){
                        min = dist;
                        pos = i;
                        ((Curve*)dataset.at(j))->assign((Curve*)(clusters.at(i)->getCentroid()));
                    }
                }
            }
            clusters.at(pos)->addItem(dataset.at(j)); //TODO remove item from previous cluster
            //if(curvesFlag) cout << "Closest: " <<((Curve*)dataset.at(j))->getCentroid()->getId() << " with distance " << min   <<  endl;
        }
    }
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


double Clustering::pamCost(vector<void*> items,int centroidIndex){
    double sum = 0;
    for(int i=0; i<items.size(); i++){
        if(i!=centroidIndex){
            if(!curvesFlag)
                sum += manhattanDistance(((Point*)items.at(i))->getCoordinates(),(((Point*)(items.at(centroidIndex)))->getCoordinates()));
            else
                sum += getValueDTW((Curve*)items.at(i),(Curve*)items.at(centroidIndex));
        }
    }
    return sum;
}

int Clustering::updatePAM(){
    // For every cluster
    for(int i=0; i<clusters.size(); i++){
        vector<void*> items = clusters.at(i)->getItems();

        // For every point in the cluster: compute the cost that the cluster
        //would have if this point was the centroid, and find the minimum
        double minCost = numeric_limits<double>::max();
        int minIndex=-1;
        for(int centroidIndex=0; centroidIndex<items.size(); centroidIndex++){
            double cost = pamCost(items,centroidIndex);
            //cout << "Cost of " << centroidIndex << ": " << cost << endl;
            if(cost < minCost){
                minCost = cost;
                minIndex=centroidIndex;
            }
        }
        //cout << "MinCost: " << minCost << " MinIndex: " << minIndex << endl;

        // If a better centroid was found
        if(items.at(minIndex) != clusters.at(i)->getCentroid()){
            clusters.at(i)->setCentroid(items.at(minIndex));
        }
    }
}

int Clustering::updateMean(){
    cout << "updateMean coming soon..." << endl;
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

    cout << "Clusters after assignment:" << endl;
    printClusters();
    cout << endl;

    // Update
    if (!updateMethod.compare("pam")){
        updatePAM();
    }else if (!updateMethod.compare("mean")){
        updateMean();
    }else{
        cout << "Unknown updateMethod" << endl;
        return -1;
    }

    cout << "Centroids after update:" << endl;
    printCentroids();
}

void Clustering::printCentroids(){
    /*for(int i=0; i<centroids.size(); i++){
        if(!curvesFlag)
            cout << ((Point*)centroids.at(i))->getId() << ", "<<  endl;
        else
            cout << ((Curve*)centroids.at(i))->getId() << ", "<<  endl;
    }*/
    for(int i=0; i<clusters.size(); i++){
        if(!curvesFlag)
            cout << ((Point*)clusters.at(i)->getCentroid())->getId() << ", "<<  endl;
        else
            cout << ((Curve*)clusters.at(i)->getCentroid())->getId() << ", "<<  endl;
    }
}

void Clustering::printClusters(){
    for(int i=0; i<clusters.size(); i++){
        cout << "Cluster of " << clusters.at(i)->getId() << ": "<<  endl;
        clusters.at(i)->printItems();
        
    }
}

// TODO del
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

// TODO del
#if 0
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
#endif

Cluster::Cluster(int id, void *centroid, bool curvesFlag):id(id),centroid(centroid), curvesFlag(curvesFlag){
    //cout << "New Cluster with id " << id << endl;
    addItem(centroid);
}

void Cluster::addItem(void *item){
    items.push_back(item); 
    if(!curvesFlag)
        ((Point*)item)->assign((Point*)centroid);
    else
        ((Curve*)item)->assign((Curve*)centroid);
}

bool Cluster::removeItem(string id){
    for(int i=0; i<items.size(); i++){
        if(!curvesFlag)
            if(((Point*)items.at(i))->getId() == id){
                items.erase(items.begin()+i);
                return true;
            }
        else     
            if(((Curve*)items.at(i))->getId() == id){
                items.erase(items.begin()+i);
                return true;
            }
    }
    return false;
}

void *Cluster::getCentroid(){
    return centroid;
}

void Cluster::setCentroid(void *item){
    centroid=item;

    // If its not in the items, add it
    if(find(items.begin(), items.end(), item) == items.end()){
        cout << "Setting a centroid that is not part of the cluster." << endl;
        addItem(item);
    }
}

vector<void*> Cluster::getItems(){
    return items;
}

int Cluster::getId(){
    return id;
}

void Cluster::printItems(){
    for(int i=0; i<items.size(); i++){
        if(!curvesFlag){
            cout << "{" << ((Point*)items.at(i))->getId() << "}, ";
        }else{
            cout << "{" << ((Curve*)items.at(i))->getId() << "}, ";
        }
    }
    cout << endl;
}


