#pragma once
#include <vector>

using namespace std;

class Point{
    private:
        int id;
        int d; // Dimensions
        vector<double> listOfCoordinates;
    public:
        Point();
        ~Point();
        void addCoordinate(double x);
        void setId(int x);
        int getId();
        int getD();
        void printPoint();
        double getCoordinate(int i);
        vector<double> getCoordinates();
        void setX(double x);
        void setY(double y);
        double getX();
        double getY();
        
};
