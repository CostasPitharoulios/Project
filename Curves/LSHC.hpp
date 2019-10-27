#pragma once
#include <string>
#include "Grid.hpp"
#include "Curve.hpp"
#include "../Point.hpp"
#include "../LSH/LSH.hpp"
#include "../HyperCube/HC.hpp"

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
        virtual ~CurveHashing();

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
        ~LSHC();
        
        void hashAll() override; // Insert all curves to the LSH hash tables
        void nearestNeighbourCurve(Curve *) override; 
};

// HyperCube for Curves
class HCC: public CurveHashing{
    private:
        vector<HC*> hc;
        int dd; // Number of f_i's
        int hd; // Hamming distance of near vertices

    public:
        HCC(double delta, int d, int L, int dd, int hd);
        ~HCC();
        
        void hashAll() override; // Insert all curves to the LSH hash tables
        void nearestNeighbourCurve(Curve *) override; 
};
