#pragma once
#include <vector>
//#include "Curves/Curve.hpp"

using namespace std;

class Point{
    private:
        int id;
        int d; // Dimensions
        vector<double> listOfCoordinates;
 //       Curve *origin; // Curve from which this point is originated(in case of LSHC)
    public:
        Point(int id=-1);
        ~Point();
        void addCoordinate(double x);
        int getId();
        void setId(int x);
        int getD();
   //     void setOrigin(Curve *ptr);
  //      Curve *getOrigin();
        void printPoint();
        double getCoordinate(int i);
        vector<double> getCoordinates();
        void setX(double x);
        void setY(double y);
        double getX();
        double getY();
        void addPading(int new_d); // Add 0's to reach new_d dimensions
};
