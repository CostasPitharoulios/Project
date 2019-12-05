#pragma once
#include <vector>

class Cluster;
class Curve;

using namespace std;

class Point{
    private:
        string id;
        int d; // Dimensions
        vector<double> listOfCoordinates;
        Cluster *cluster;
        Curve *origin; // Curve from which this point is originated(in case of LSHC)

        // For the reverse assignment
        bool clusterChanged;
        Cluster *previousCluster;
        double dist;
    public:
        Point(string id="-1");
        void addCoordinate(double x);
        string getId();
        void setId(string x);
        int getD();
        void setD(int dim);
        void setDist(double dist);
        double getDist();
        void setChanged();
        bool getChanged();
        void prepareAssignment();
        void printPoint();
        double getCoordinate(int i);
        vector<double> getCoordinates();
        Curve *getOrigin();
        void setOrigin(Curve *ptr);
        void setCoordinates(vector<double> Coordinates);
        void setX(double x);
        void setY(double y);
        void changeX(double X);
        void changeY(double Y);
        double getX();
        double getY();
        void addPadding(int new_d); // Add 0's to reach new_d dimensions
        void setCluster(Cluster *);
        Cluster *getCluster();
        Cluster *getPreviousCluster();
        Point* copyPoint(void);
        Point* dublicatePoint(void);
};
