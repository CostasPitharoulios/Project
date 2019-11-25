#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "../include/Point.hpp"
#include "../include/Clustering.hpp"
#include "../include/Curve.hpp"
#include "../include/util.hpp"

using namespace std;

int main(int argc,char *argv[]){
    string inputFile, outputFile, confFile;

    // Handling arguments
    if ( argc != 7 && argc != 8 ){
        cerr << "Wrong number of arguments" << endl;
        return 1;
    }
    for(int i=1 ; i<argc ; i++){
        if(!strcmp(argv[i],"-i"))
            inputFile = argv[i+1];
        if(!strcmp(argv[i],"-o"))
            outputFile = argv[i+1];
        if(!strcmp(argv[i],"-c"))
            confFile = argv[i+1];
    }

    // Read configuration file
    int n_clusters =-1, n_grids=2, L=3, k=4;
    ifstream cin(confFile.c_str());
    if (!cin){
        cerr << "Cannot open the configuration file " << confFile << endl;
        return 1;
    }
    string str,token,val;
    while(getline(cin,str)){
        istringstream ss(str);
        ss >> token;
        ss >> val;

        if(!token.compare("number_of_clusters:")){
            n_clusters = stoi(val);
        }else if(!token.compare("number_of_grids:")){
            n_grids = stoi(val);
        }else if(!token.compare("number_of_vector_hash_tables:")){
            L = stoi(val);
        }else if(!token.compare("number_of_vector_hash_functions:")){
            k = stoi(val);
        }else{
            cout << "Unknown argument in config file : " << token << endl;
        }
    }
    if(n_clusters == -1){
        cout << "Error: number_of_clusters argument is neccessary in the config file" << endl;
        return 1;
    }

    vector<void*> dataset;
    bool curvesFlag;
    cout << "Reading input dataset..." << endl;
    readDataset(inputFile,dataset,curvesFlag);
    cout << "Reading complete." << endl;

    if (dataset.size() < n_clusters){
        cout << "Error: input dataset is smaller than the number of clusters" << endl;
        return 2;
    }

    // Make a Clustering instance
    Clustering clustering(curvesFlag,dataset,n_clusters,"random");

    // KMeans
    clustering.KMeans();

    cout << "Process complete. The output is written on file " << outputFile << endl;

    return 0;
}
