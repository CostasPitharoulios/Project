#pragma once
#include <string>
#include "Grid.hpp"
#include "Curve.hpp"
#include "../Point.hpp"
#include "../LSH/LSH.hpp"

using namespace std;

class CurveHashing{
    protected:
        vector<Curve*> allCurves; // stores dataset
        int d; //Dimension of the points of the curves
        double delta;
        vector<Grid> grids;
        int L; // ammout of grids

    public:
        CurveHashing(double delta, int d, int L);
        void readData(string path); // Read curves from file path
        void printAllCurves();
        int maxCurveLength();
        Point* vectorCurveToPoint(Curve* hashedCurve, Curve *origin); // Convert vector of curve to a single point
        vector<Curve*> getAllCurves(void);
        void readQueries(string path);
        virtual void hashAll() = 0; //pure virtual functions
        virtual void nearestNeighbourCurve(Curve *) = 0;

};

// LSH for Curves
class LSHC: public CurveHashing{
    private:
        vector<LSH*> lsh;

    public:
        LSHC(double delta, int d, int L);
        
        void hashAll(); // Insert all curves to the LSH hash tables
        void nearestNeighbourCurve(Curve *) override; 
};
