#include <vector>
#include "Curves/Curve.hpp"

using namespace std;

// Manhattan distance
double manhattanDistance(vector<double>, vector<double>);

// Dynamic Time Wrapping (for curves)
double getValueDTW(Curve *queryCurve,Curve *inputCurve);
double getDTWfromPoints(Point* pointA, Point* pointB);
double distance(float x1, float x2, float y1, float y2);
