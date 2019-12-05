#include <vector>
#include "Curve.hpp"

using namespace std;

// Manhattan distance
double manhattanDistance(vector<double>, vector<double>);

// Dynamic Time Wrapping (for curves)
double getValueDTW(Curve *queryCurve,Curve *inputCurve);
double getDTWfromPoints(Point* pointA, Point* pointB);
vector<Point*> getBestTraversalDTW(Curve *queryCurve,Curve *inputCurve);
//double getDTWfromPoints(Point* pointA, Point* pointB);
double distance(double x1, double x2, double y1, double y2);
