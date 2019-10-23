#pragma once
#include <string>
#include "Grid.hpp"
#include "Curve.hpp"
#include "../Point.hpp"
#include "../LSH/LSH.hpp"

using namespace std;

// LSH for Curves
class LSHC{
    private:
        vector<Curve*> allCurves;
        LSH *lsh;
        int d; //Dimension of the points of the curves
        double delta;
        vector<Grid> grids; // L grids
        //vector<unordered_multiman< >> hashTables; // L hashTables

    public:
        LSHC(double delta, int d);
        
        void readData(string path); // Read curves from file path
        void lshInsertAll();
        int maxCurveLength();
        Point* vectorCurveToPoint(Curve* hashedCurve); // We have already created a grid vector of curve, so with this function we convert the vector to a single point and we finally get a pointer to this.
    
        double getDTWfromPoints(Point* pointA, Point* pointB);
};
