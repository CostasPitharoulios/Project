#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "../include/Point.hpp"
#include "../include/Clustering.hpp"

using namespace std;

int main(int argc,char *argv[]){
    string inputFile, outputFile, configFile;

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
            configFile = argv[i+1];
    }

    // Open input file
    ifstream in(inputFile.c_str());
    if (!in){
        cerr << "Cannot open the input file " << inputFile << endl;
        return 1;
    }

    // Read the first line
    string str,token;
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
    VectorClustering vc(dataset,4,"random");

    vc.KMeans();

    //cout << "Process complete. The output is written on file " << outputFile << endl;

    in.close();
    return 0;
}
