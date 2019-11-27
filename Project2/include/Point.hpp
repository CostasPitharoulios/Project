#pragma once
#include <vector>

class Cluster;

using namespace std;

class Point{
    private:
        string id;
        int d; // Dimensions
        vector<double> listOfCoordinates;
        Cluster *cluster;
    public:
        Point(string id="-1");
        void addCoordinate(double x);
        string getId();
        void setId(string x);
        int getD();
        void setD(int dim);
        void printPoint();
        double getCoordinate(int i);
        vector<double> getCoordinates();
        void setX(double x);
        void setY(double y);
        double getX();
        double getY();
        void addPadding(int new_d); // Add 0's to reach new_d dimensions
        void setCluster(Cluster *);
        Cluster *getCluster();
};
