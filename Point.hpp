#pragma once
#include <vector>

using namespace std;

class Point{
    private:
        int id;
        vector<double> listOfCoordinates;
    public:
        Point();
        ~Point();
        void addCoordinate(double x);
        void setId(int x);
        int getId();
        void printCoordinates();
        vector<double> getCoordinates();
        void setX(double x);
        void setY(double y);
        double getX();
        double getY();
        
};
