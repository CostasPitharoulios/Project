#pragma once
#include <string>
#include "Grid.hpp"
#include "Curve.hpp"
#include "../Point.hpp"

using namespace std;

// LSH for Curves
class LSHC{
    private:
        vector<Curve *> allCurves;

        double delta;
        vector<Grid> grids; // L grids
        //vector<unordered_multiman< >> hashTables; // L hashTables

    public:
        LSHC(double delta, int d);

        void readData(string path); // Read curves from file path
        //void insert

        Point* vectorCurveToPoint(Curve* hashedCurve); // We have already created a grid vector of curve, so with this function we convert the vector to a single point ang we finally get a pointer to this.
};
