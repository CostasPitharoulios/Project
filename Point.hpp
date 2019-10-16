#pragma once
#include <vector>

using namespace std;

class Point{
    private:
    vector<double> listOfCoordinates;
    public:
        Point();
        ~Point();
        void addCoordinate(double x);
        void printCoordinates();
        void setX(double x);
        void setY(double y);
        double getX();
        double getY();
        
};
