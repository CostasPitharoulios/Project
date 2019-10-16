#pragma once

#include <vector>
#include "Curve.hpp"


double getValueDTW(vector<Curve *>::iterator queryCurve,vector<Curve *>::iterator inputCurve);
double distance(float x1, float x2, float y1, float y2);
