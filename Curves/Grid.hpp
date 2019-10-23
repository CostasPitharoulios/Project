#include <vector>

using namespace std;

class Grid {
    private: 
        double delta;
        vector<double> t; // Shift each dimension by t.at(i)
    public:
        Grid(double delta, int d);
        //Curve curveHash(Curve in);
};
