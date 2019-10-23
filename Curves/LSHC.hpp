#include "Grid.hpp"
#include "Curve.hpp"

using namespace std;

// LSH for Curves
class LSHC{
    private:
        vector<Curve *> allCurves;

        double delta;
        vector<Grid> grids; // L grids


    public:
        LSHC(double delta, int d);
};
