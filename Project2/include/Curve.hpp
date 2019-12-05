#pragma once
#include <vector>
#include <string>

#include "Point.hpp"

using namespace std;

class Curve{
    private:
        string id;
        int numberOfCoordinates; /* TODO number and listOfPoints? */
        vector<Point*> listOfCoordinates;
        Cluster *cluster;

        // Fore the reverse assignment
        bool clusterChanged;
        Cluster *previousCluster;
        double dist;
    public:
        Curve();
        ~Curve();
        void setId(string Id);
        string getId(void);
        void printCoordinates();
        void setNumberOfCoordinates(int number);
        int getNumberOfCoordinates(void);
        //vector<Point*> get_listOfCoordinates();
        void DisplayVectorContents();
        void PushToVector(Point* aPoint);
        double getSpecificXCoord(int position);
        double getSpecificYCoord(int position);
        void setCluster(Cluster *);
        Cluster *getCluster();
        void setDist(double dist);
        double getDist();
        void setChanged();
        bool getChanged();
        void prepareAssignment();
        Cluster *getPreviousCluster();
};
