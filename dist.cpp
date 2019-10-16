#include <cmath>
#include <iostream>
#include <vector>
#include "dist.hpp"

using namespace std;

double manhattanDistance(vector<double> a, vector<double> b){
    double dist = 0;
    if (a.size() != b.size())
        return -1;

    for (int i=0; i<a.size(); i++)
        dist += abs(a.at(i) - b.at(i));

    return dist;
}
