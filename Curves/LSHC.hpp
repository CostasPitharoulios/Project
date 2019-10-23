#pragma once
#include <string>
#include "Grid.hpp"
#include "Curve.hpp"

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
        Point curveToPoint(Curve c);
};
