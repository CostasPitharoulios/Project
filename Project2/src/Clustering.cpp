#include <algorithm>
#include <iostream>
#include <limits>
#include <random>
#include <unistd.h>
#include "../include/Clustering.hpp"
#include "../include/dist.hpp"

using namespace std;



//=====================================================================================
//          *** Class Clustering ***
//=====================================================================================

Clustering::Clustering(bool curvesFlag, vector<void*> dataset, int n_clusters, string i, string a, string u):curvesFlag(curvesFlag),dataset(dataset),n_clusters(n_clusters),initMethod(i),assignMethod(a),updateMethod(u){
    //cout << "New instance of Clustering(" << initMethod << "," << assignMethod << "," << updateMethod << ")\n";
}

int Clustering::initRandom(){
    centroids.clear();

    // Shuffle the dataset into a new vector
    vector<void*> shuffledDataset = dataset;
    random_device rd;
    default_random_engine rng(rd());
    shuffle(begin(shuffledDataset), end(shuffledDataset), rng);

    // Pick the first k elements from the shuffled vector
    shuffledDataset.resize(n_clusters);
    centroids = shuffledDataset;

    // For every centroid, make a cluster
    for(int i=0; i<centroids.size(); i++)
        clusters.push_back(new Cluster(i,centroids.at(i),curvesFlag));
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
    
    //cout << "Kmeans++ is here bitchessss" << endl;
    
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
    int randNumber = rand()%(numbData);                           // range is [0...maximun number of items-1]
    if(!curvesFlag)                                                 // if we have points
        centroids.push_back((Point*)dataset.at(randNumber));
    else                                                            // if we have curves
        centroids.push_back((Curve*)dataset.at(randNumber));
    clusters.push_back(new Cluster(0,dataset.at(randNumber),curvesFlag));
  
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
    }
}

int Clustering::assignLloyd(){
    int changed = 0; // Counts how many items changed cluster
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
                    }
                } 
                else{
                    dist = getValueDTW((Curve*)dataset.at(j),(Curve*)(clusters.at(i)->getCentroid()));
                    //cout << " Distance between " << ((Curve*)dataset.at(j))->getId() << " and " << ((Curve*)(clusters.at(i)->getCentroid()))->getId() << " is " << dist << endl;
                    if(dist<min){
                        min = dist;
                        pos = i;
                    }
                }
            }

            // Assign point to cluster
            if(clusters.at(pos)->assign(dataset.at(j)))
                changed++;

            //TODO if old cluster == new cluster, dont make assignment.. else do, and count them and return the count
            //if(curvesFlag) cout << "Closest: " <<((Curve*)dataset.at(j))->getCentroid()->getId() << " with distance " << min   <<  endl;
        }
        
    }
    return changed;
}

bool Clustering::isCentroid(void* item){
    if(!curvesFlag)
        if(((Point*)item)->getCluster() == nullptr)
            return false;
        else
            return (((Point*)item)->getCluster()->getCentroid() == item);
    else
        if(((Curve*)item)->getCluster() == nullptr)
            return false;
        else
            return (((Curve*)item)->getCluster()->getCentroid() == item);
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
    cout << "updateMean is here bitcheeees" << endl;
    
  
    int counter = 0; // this counts new centroids and we use it to make new ids of centroids
    for (int cl=0; cl < clusters.size(); cl++){              // for each cluster
        
        
        // -------------------------------------------------------------
        // first of all we are calculating lamda
        // -------------------------------------------------------------
        
        vector<void*> items = clusters.at(cl)->getItems();  // getting all items of cluster
        int n = items.size();                               // n keeps the number of items of cluster
        int sumOfLengths = 0;
        
        
        for (int i=0; i<n; i++){
            if(curvesFlag){ // if we have Curves
                Curve* itemCurve;
                itemCurve = (Curve*) items.at(i);
                sumOfLengths += itemCurve->getNumberOfCoordinates(); // adds the number of coordinates of curve to the sum of coordinates of all curves of cluster
            }
            else{ // if we have Point
                Point* itemPoint;
                itemPoint = (Point*) items.at(i);
                sumOfLengths += itemPoint->getD();
            }
        }
      
        int lamda = sumOfLengths/n;                         // calculating lamda
        //cout << "Lamda = " << lamda << endl;

        // -------------------------------------------------------------
        // here we are going to find a random sequence with length >= lamda
        // in order to initialize C
        // -------------------------------------------------------------
       
       
       // Point* oversizedP;
        if(curvesFlag){ // if we have Curves
            int randomI= rand()%n;
            Curve* oversizedC; // holds a pointer to the random item with legth >= lamda
            oversizedC = (Curve*) items.at(randomI);
            while (1){
                if ( oversizedC->getNumberOfCoordinates() >= lamda)
                    break;
                else{
                    randomI = rand()%n;
                    oversizedC =(Curve*) items.at(randomI);
                }
            }


        // -------------------------------------------------------------
        // going to shuffle C and take lamda random points
        // -------------------------------------------------------------
     
            Curve* C;
            //C = oversizedC->copyCurve();
            C = oversizedC->dublicateCurve();
            
            vector<Point*> shuffledOversizedC = C->getListOfCoordinates();
            random_device rd;
            default_random_engine rng(rd());
            shuffle(begin(shuffledOversizedC), end(shuffledOversizedC), rng);
            
            // Pick the first k elements from the shuffled vector
            shuffledOversizedC.resize(lamda);
            C->setListOfCoordinates(shuffledOversizedC);
            C->setNumber(lamda);
            
            string newId = "NEWid";
            newId += to_string(counter);
            counter++;
            C->setId(newId);
   
        
        // -------------------------------------------------------------
        // repeatedly calculate C since it does not change much
        // -------------------------------------------------------------
            double previousDistance =  std::numeric_limits<double>::max();
            while(1){
                //cout << "heloooooo\n\n\n\n";
                // storing C Curve to tempC - this is a dublicate with new points
                Curve* tempC = C->dublicateCurve();
                

                vector< vector<Point*> > arrayA(lamda); // Array of lamda pointsets
                for (int i=0; i<n; i++){ // for each one of the Curves of this cluster
                    vector<Point*> setIPairs; // this keeps index-pairs of best traversal(C,Si)
                    
                    Curve* itemCurve;
                    itemCurve = (Curve*) items.at(i);
                    setIPairs = getBestTraversalDTW(C,itemCurve); // gets the pointers to best traversal points
            
                    
                    for (int j=0; j< setIPairs.size(); j++){
                        int x = setIPairs.at(j)->getX();
                        int y = setIPairs.at(j)->getY();
                        Point* tempPoint = itemCurve->getSpecificPoint(y);
                        arrayA[x].push_back(tempPoint);
                    }
                
                }

                
                for (int j=0; j<lamda; j++){
                    double sumX = 0.0;
                    double sumY = 0.0;
                    for (int i=0; i< arrayA[j].size(); i++){
                        sumX += arrayA[j][i]->getX();
                        sumY += arrayA[j][i]->getY();
                    }
                    double avX, avY;
                    avX = sumX / (double)arrayA[j].size();
                    avY = sumY / (double)arrayA[j].size();
                    
                    C->setSpecificXCoord(j, avX);
                    C->setSpecificYCoord(j, avY);
                }
                
                newId = "NEWid";
                newId += to_string(counter);
                counter++;
                C->setId(newId);
            
               
                
                double currentDistance = getValueDTW(C, tempC);
                if ((double)(abs(previousDistance-currentDistance))/100.0 < 0.1){
                    tempC->~Curve();
                    break;
                }
                previousDistance = currentDistance;
                tempC->~Curve();
                
        
                
            
            } // end of while loop
            clusters.at(cl)->setCentroid(C);
        } // end of curve section
        else{ // if we  have vectors
            Point *P = new Point("newCentroid");
            P->setD(0);
            P->setCluster(clusters.at(cl));
            
            for (int j=0; j< lamda; j++){
                double sum = 0.0;
                int counter = 0;
                for (int i=0; i<n; i++){
                    Point* itemPoint;
                    itemPoint = (Point*) items.at(i);
                    if ( itemPoint->getD() <= j)
                        continue;
                    else{
                        sum += itemPoint->getCoordinate(j);
                        counter++;
                    }
                }
                sum = sum / (double)counter;
                P->addCoordinate(sum);
            }
            cout << "new Point Centroid:" << endl;
            P->printPoint();
            clusters.at(cl)->setCentroid(P);
        } // end of vectors
      
        // NOTE: AT THE END WE UPDATE THE NEW CENTROID TO ALL ITEMS OF CLUSTER

    }
    
    assignLloyd();
    
}

int Clustering::KMeans(){
    if(!curvesFlag)
        cout << "Starting KMeans for Points ";
    else
        cout << "Starting KMeans for Curves ";
    cout << "with initMethod=" << initMethod << ", assignMethod=" << assignMethod << ", updateMethod=" << updateMethod << "\n";

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
    cout << endl;
    
    int changed=-1, it=1;
    while(changed){

        // Assignment
        
        cout << "Assigning items..." << endl;
        if (!assignMethod.compare("lloyd")){
            changed = assignLloyd();
        }else if (!assignMethod.compare("reverse")){
            changed = assignReverse();
        }else{
            cout << "Unknown assignMethod" << endl;
            return -1;
        }


        // Update
        cout << "Updating clusters..." << endl;
        if (!updateMethod.compare("pam")){
            updatePAM();
        }else if (!updateMethod.compare("mean")){
            updateMean();
        }else{
            cout << "Unknown updateMethod" << endl;
            return -1;
        }


        cout << "Iteration " << it << " complete." << endl;
        for(int i=0; i<clusters.size(); i++)
            clusters.at(i)->printStats();
        cout << "(" << changed << " items changed clusters)" << endl << endl;

        //sleep(1);
        it++;
    }
    
    Silhouette();

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



int Clustering::Silhouette(void){
    
    cout << "\nBegining Silhuette...\n\n" << endl;
    
    int numberOfClusters = clusters.size(); // holds the number of clusters
    
    // if we got only one cluster, there is no need for us to try to find
    // closest cluster etc.
    if (numberOfClusters == 1){
        cout << "Your option is only one cluster." << endl;
        return 0;
    }
    
    //--------------------------------------------------------------------
    // for each cluster, we are searching for next closest neighbor cluster
    // we are doing this by finding the closest Centroid
    //--------------------------------------------------------------------
    int* closestNeighbor = (int*) malloc(numberOfClusters *sizeof(int)); // closestNeighbor[0] has the iterator of closest neighbor of cluster 0 and so goes on.
    

    for(int cl1=0; cl1<clusters.size(); cl1++){ // do the same calculations for each cluster
        
        cout << "Silhouette of cluster " << cl1 << ": "<< endl;
        
        double minDistance = numeric_limits<double>::max(); // holds the minimun distance of the next closest cluster to an item.
        void* currentCentroid; // this keeps out current centroid of cluster.
        if(!curvesFlag)
            currentCentroid = ((Point*)clusters.at(cl1)->getCentroid());
        else
            currentCentroid = ((Curve*)clusters.at(cl1)->getCentroid());
        
        void* tempCentroid;
        int closestCluster;
        for (int cl2=0; cl2<clusters.size(); cl2++){ // for each one of the clusters (except cl1 cluster)
           
            if (cl1 == cl2) // we donts want to compare the same cluster
                continue;
            
            double distance;
            if(!curvesFlag){                                 // if we have points
                tempCentroid = ((Point*)clusters.at(cl2)->getCentroid());
                distance = manhattanDistance(((Point*)currentCentroid)->getCoordinates(), ((Point*)tempCentroid)->getCoordinates());
            }
            else{                                                // if we have curves
                tempCentroid = ((Curve*)clusters.at(cl2)->getCentroid());
                distance = getValueDTW(((Curve*)currentCentroid), ((Curve*)tempCentroid));
            }
            if (distance < minDistance){
                minDistance = distance;
                closestCluster = cl2;
            }
            
        }
        
        closestNeighbor[cl1] = closestCluster; // this is now the next closest cluster to this cluster
        cout << "Closest cluster: " << closestCluster << " Minimum Distance: " << minDistance << endl;
        
        ///--------------------------------------------------------------------
        // for each item i of cluster we are calculating a(i) and b(i)
        // a(i): average distance of item i from all items of its cluster
        // b(i): average distance of item i from all items of nearest cluster
        //--------------------------------------------------------------------
        
        vector<void*> items = clusters.at(cl1)->getItems();
        int numberOfItems = items.size();
        
        
        double alpha, beta;
        
        double sumS=0.0;
        for (int i=0; i< numberOfItems; i++){
            double sumOfDistance = 0;
            // calculating a(i)
            for (int j=0; j< numberOfItems; j++){
                if (i==j)
                    continue;
                
                if(!curvesFlag)
                    sumOfDistance += manhattanDistance(((Point*)items.at(i))->getCoordinates(),((Point*)items.at(j))->getCoordinates());
                else
                    sumOfDistance += getValueDTW(((Curve*)items.at(i)),((Curve*)items.at(j)));
            }
            if (numberOfItems <= 1)
                alpha = 0;
            else
                alpha = sumOfDistance/(numberOfItems-1);
            //cout << "alpha[" << i << "] = " << alpha;
            
            // calculating b(i)
            vector<void*> itemsClosestCluster = clusters.at(closestNeighbor[cl1])->getItems();
            sumOfDistance = 0;
            for (int j=0; j< itemsClosestCluster.size(); j++){
                
                if(!curvesFlag)
                    sumOfDistance += manhattanDistance(((Point*)items.at(i))->getCoordinates(),((Point*)itemsClosestCluster.at(j))->getCoordinates());
                else
                    sumOfDistance += getValueDTW(((Curve*)items.at(i)),((Curve*)itemsClosestCluster.at(j)));
            }
            beta = sumOfDistance / itemsClosestCluster.size();
           // cout << " beta[" << i << "] = " << beta;
            
            //--------------------------------------------------------------------
            // For each item i of cluster calculating s(i).
            // s(i): [b(i)-a(i)] / max{a(i), b(i)} in [-1, 1]
            //--------------------------------------------------------------------
            double s;
            if (alpha < beta)
                s = 1 - (alpha/beta);
            else if (alpha == beta)
                s = 0.0;
            else
                s = (beta/alpha)-1;
            
            sumS += s;
            
            //cout << " s[" << i << "] = " << s  << " ";
            
            
        }
        
        ///--------------------------------------------------------------------
        // Calculating average s(i) over all i in some cluster (for each cluster)
        //--------------------------------------------------------------------
        double averageS = sumS / numberOfItems;
        cout << "AverageS[" << cl1 << "] = " << averageS  << "\n" << endl;;
        
        
    }
    
    free(closestNeighbor);
}



//=====================================================================================
//          *** Class Cluster ***
//=====================================================================================
Cluster::Cluster(int id, void *centroid, bool curvesFlag):id(id),centroid(centroid), curvesFlag(curvesFlag){
    //cout << "New Cluster with id " << id << endl;
    assign(centroid);
}


// Assigns this cluster to item
bool Cluster::assign(void *item){
    // Find whether the item was in a different cluster or not
    bool changed=false;
    if(!curvesFlag){
        if(((Point*)item)->getCluster() != this)
            changed=true;
    }else{
        if(((Curve*)item)->getCluster() != this)
            changed=true;
    }

    if(!changed)
        return false;

    // Remove it from the previous cluster
    if(!curvesFlag){
        if(((Point*)item)->getCluster() != nullptr)
            ((Point*)item)->getCluster()->removeItem(((Point*)item)->getId());
    }else
        if(((Curve*)item)->getCluster() != nullptr)
            ((Curve*)item)->getCluster()->removeItem(((Curve*)item)->getId());

    // Add it to the new cluster
    items.push_back(item); 

    // Save its cluster
    if(!curvesFlag)
        ((Point*)item)->setCluster(this);
    else
        ((Curve*)item)->setCluster(this);

    return true;
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
    return this->centroid;
}

void Cluster::setCentroid(void *item){
    centroid=item;

    // If its not in the items, add it
    if(find(items.begin(), items.end(), item) == items.end()){
        cout << "Setting a centroid that is not part of the cluster." << endl;
        assign(item);
    }
}

vector<void*> Cluster::getItems(){
    return items;
}

int Cluster::getId(){
    return id;
}

void Cluster::printStats(){
    cout << "Cluster " << id << ":  size: " << items.size();
    if(!curvesFlag)
        cout << "  centroid: " << ((Point*)centroid)->getId() << endl;
    else
        cout << "  centroid: " << ((Curve*)centroid)->getId() << endl;
        
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



