#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

#include "Curve.hpp"
#include "../Point.hpp"
#include "readingFunctions.hpp"
#include "DTW.hpp"
#include "curveHashing.hpp"
#include "LSHC.hpp"

using namespace std;

int main(int argc,char *argv[]){
    string inputFile, outputFile, queryFile;
    int r=-1;

    // Handling arguments
    if (argc == 5 || argc == 7){
        int i;
        for(i=1 ; i<argc ; i++){
            if(!strcmp(argv[i],"-d"))
                inputFile = argv[i+1];
            if(!strcmp(argv[i],"-q"))
                queryFile = argv[i+1];
            if(!strcmp(argv[i],"-o"))
                outputFile = argv[i+1];
            if(!strcmp(argv[i],"-r"))
                r = stoi(argv[i+1]);
        }
    }
    else{
        cerr << "Wrong number of arguments" << endl;
        return 1;
    }
    
    
    LSHC lshc(0.0005,2,5);
    cout << "Reading input file..." << endl;
    lshc.readData(inputFile);
    cout << "Reading complete." << endl;
    //lshc.printAllCurves();
    cout << "Inserting data to the hashtable..." << endl;
    lshc.lshInsertAll();
    cout << "Inserting complete." << endl;
    lshc.readQueries(queryFile);

    return 0;
}
