#pragma once

#include <vector>
#include "Curve.hpp"


double getValueDTW(vector<Curve *>::iterator queryCurve,vector<Curve *>::iterator inputCurve);
double distance(int x1, int x2, int y1, int y2);
