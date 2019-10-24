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
        vector<Curve*> allCurves; // stores dataset
        vector<LSH*> lsh;
        int d; //Dimension of the points of the curves
        double delta;
        vector<Grid> grids;
        int L; // ammout of grids

    public:
        LSHC(double delta, int d, int L);
        
        void readData(string path); // Read curves from file path
        void readQueries(string path);
        void printAllCurves();
        void lshInsertAll(); // Insert all curves to the LSH hash tables
        int maxCurveLength();
        Point* vectorCurveToPoint(Curve* hashedCurve, Curve *origin); // We have already created a grid vector of curve, so with this function we convert the vector to a single point and we finally get a pointer to this.
        void nearestNeighbourCurve(Curve *);
        vector<Curve*> getAllCurves(void);
};
