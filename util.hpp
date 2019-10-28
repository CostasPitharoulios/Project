#include <fstream>
#include "Point.hpp"

int mod(int a, int b);
void printOutput(ofstream& out, int q_id, int nn_id, double lsh_dist, double true_dist, double lsh_time, double true_time, vector<Point*> rnn);
void printOutput(ofstream& out, string q_id, string hf, string nn_id, string true_id, double dist, double true_dist );
