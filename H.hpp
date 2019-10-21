#pragma once
#include "Point.hpp"

using namespace std;

// H is the class of the sub hash functions of LSH
class H{
    private:
        int d; // Dimension of points
        int w; // Grid cell size
        double *s; // Array that saves how much each dimension is shifted
        int *m;
        int M;
    public:
        H(int w, int d, int M);
        ~H();
        H(const H &h2);

        uint32_t hash(Point p);
};
