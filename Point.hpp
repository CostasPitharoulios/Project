#pragma once
#include <vector>

using namespace std;

class Point{
    private:
    vector<double> listOfCoordinates;
    public:
        Point();
        ~Point();
        void setX(double x);
        void setY(double y);
        double getX();
        double getY();
};
