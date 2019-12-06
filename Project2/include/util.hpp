#include <vector>
#include "Point.hpp"

using namespace std;

void readDataset(string inputFile, vector<void*> &dataset, bool &curvesFlag);
bool isCentroid(void* item, bool curvesFlag);
int mod(int a, int b);
void printOutput(ofstream& out, string q_id, string nn_id, double lsh_dist, double true_dist, double lsh_time, double true_time, vector<Point*> rnn);
void printOutput(ofstream& out, string q_id, string hf, string nn_id, string true_id, double dist, double true_dist);
