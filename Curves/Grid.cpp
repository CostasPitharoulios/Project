#include "Grid.hpp"

using namespace std;

Grid::Grid(double delta, int d):delta(delta){
    cout << "New grid" << endl;
    double t_dummy = 0.5;
    t.push_back(t_dummy);
    t.push_back(t_dummy);
}
