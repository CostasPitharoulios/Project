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
        int w;
        int k;

    public:
        CurveHashing(int w, double delta, int d, int k,int L);
        virtual ~CurveHashing();

        void readData(string path); // Read curves from file path
        void printAllCurves();
        int maxCurveLength();
        Point* vectorCurveToPoint(Curve* hashedCurve, Curve *origin); // Convert vector of curve to a single point
        vector<Curve*> getAllCurves(void);
        void readQueries(string path, string outputFile, string hf);
        void answerQuery(Curve *aCurve, string hf, ofstream& out);
        Curve *nearestNeighbourCurveBruteForce(Curve *, double &min_dist);
        virtual void hashAll() = 0; //pure virtual functions
        virtual Curve *nearestNeighbourCurve(Curve *, double &min_dist) = 0;

};

// LSH for Curves
class LSHC: public CurveHashing{
    private:
        vector<LSH*> lsh;

    public:
        LSHC(int w,double delta, int d, int k, int L);
        ~LSHC();
        
        void hashAll() override; // Insert all curves to the LSH hash tables
        Curve *nearestNeighbourCurve(Curve *, double &min_dist) override; 
};

// HyperCube for Curves
class HCC: public CurveHashing{
    private:
        vector<HC*> hc;
        int dd; // Number of f_i's
        int probes; // Max vertices examined
        int M; // Max points examined

    public:
        HCC(int w,double delta, int d, int k, int L, int dd, int probes, int M);
        ~HCC();
        
        void hashAll() override; // Insert all curves to the LSH hash tables
        Curve *nearestNeighbourCurve(Curve *, double &min_dist) override; 
};
