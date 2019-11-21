#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "../include/Point.hpp"
#include "../include/Clustering.hpp"

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
        }else if(!token.compare("number_of_vector_hash_functions")){
            k = stoi(val);
        }else{
            cout << "Unknown argument in config file : " << token;
        }
    }
    if(n_clusters == -1){
        cout << "Error: number_of_clusters argument is neccessary in the config file" << endl;
        return 1;
    }

    // Open input file
    ifstream in(inputFile.c_str());
    if (!in){
        cerr << "Cannot open the input file " << inputFile << endl;
        return 1;
    }

    // Read the first line
    //Point p1;
    if(getline(in,str)){
        if(!str.compare("vectors")){
            cout << "Its all about vectors" << endl;
        }
        else if(!str.compare("curves")){
            cout << "Its all about Curves" << endl;
        }
        else{
            cerr << "Expected \"curves\" or \"vectors\" as the first line of the input file " << inputFile << endl;
            return 1;
        }
    }else{
        cerr << "Input file " << inputFile << " is empty." << endl;
        return 1;
    }


    // For Vectors
    vector<Point*> dataset;
    
    // Read input file line by line
    cout << "Reading input dataset..." << endl;
    while(getline(in,str)){
        istringstream ss(str);
        ss >> token;

        //Read item id
        int id;
        sscanf(token.c_str(),"item%d",&id);

        Point p(id);

        //Read coordinates
        while( ss >> token )
            p.addCoordinate(stod(token));

        // Save it to the dataset list
        dataset.push_back(new Point(p));
    }
    cout << "Reading complete." << endl;

    // Make a VectorClustering instance
    VectorClustering vc(dataset,n_clusters,"random");

    vc.KMeans();

    //cout << "Process complete. The output is written on file " << outputFile << endl;

    in.close();
    return 0;
}
