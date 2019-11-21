#pragma once
#include <vector>

using namespace std;

class Point{
    private:
        int id;
        int d; // Dimensions
        vector<double> listOfCoordinates;
    public:
        Point(int id=-1);
        void addCoordinate(double x);
        int getId();
        void setId(int x);
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
};
