#include "../Point.hpp"
#include "H.hpp"

using namespace std;

// G is the class of the hash functions of LSH
// The hash key of g is the concatenation of the keys of the sub
// hash functions h_i() : g(p) = h_1(p)|h_2(p)|...|h_k(p)
class G{
    private:
        vector<H> h; // h_1(), h_2(), ..., h_k()
        int d; // Dimension of points
        int w; // Grid cell size
        int k; // Number of sub-hashfunctions
    public:
        G(int w, int d, int k);
        ~G();

        int hash(Point p);
};
