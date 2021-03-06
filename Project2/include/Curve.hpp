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
       // vector<Point*> listOfCoordinates;
        Curve();
        ~Curve();
        void setId(string Id);
        string getId(void);
        void printCoordinates();
        void setNumberOfCoordinates(int number);
        void setNumber(int number);
        int getNumberOfCoordinates(void);
        //vector<Point*> get_listOfCoordinates();
        void DisplayVectorContents();
        void PushToVector(Point* aPoint);
        double getSpecificXCoord(int position);
        double getSpecificYCoord(int position);
        void setSpecificXCoord(int position, double x);
        void setSpecificYCoord(int position, double y);
        //void assign(Curve *);
        Curve *getCentroid();
        vector<Point*> getListOfCoordinates(void);
        void setListOfCoordinates(vector <Point*>);
        void setCluster(Cluster *);
        Cluster *getCluster();
        void setDist(double dist);
        double getDist();
        void setChanged();
        bool getChanged();
        void prepareAssignment();
        Cluster *getPreviousCluster();
        Point* getSpecificPoint(int position);
        //prinCurve* copyCurve(void); // this makes a new curve by keeping pointers to old points
        Curve* dublicateCurve(void); // this makes a new curve from scratch
        //Curve* copyCurve(Curve* beforeCurve);
};
