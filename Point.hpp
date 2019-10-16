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
        vector<double> getCoordinates();
        void setX(double x);
        void setY(double y);
        double getX();
        double getY();
        
};
