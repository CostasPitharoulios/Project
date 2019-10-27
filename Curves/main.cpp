#include <iostream>
#include <limits>
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
    double r=-1,delta=0.0005; 
    int k = 4, L=5,w=4000, M=numeric_limits<int>::max(),d=2,dd=8,hd=2;

    // Handling arguments
    int n=0;
    for(int i=1 ; i<argc ; i++){
        if(!strcmp(argv[i],"-d")){
            inputFile = argv[i+1];
            n++;
        }
        if(!strcmp(argv[i],"-q")){
            queryFile = argv[i+1];
            n++;
        }
        if(!strcmp(argv[i],"-o"))
            outputFile = argv[i+1];
        if(!strcmp(argv[i],"-r"))
            r = stod(argv[i+1]);
        if(!strcmp(argv[i],"-k"))
            k = stoi(argv[i+1]);
        if(!strcmp(argv[i],"-L"))
            L = stoi(argv[i+1]);
        if(!strcmp(argv[i],"-w"))
            w = stoi(argv[i+1]);
        if(!strcmp(argv[i],"-dd"))
            dd = stoi(argv[i+1]);
        if(!strcmp(argv[i],"-hd"))
            hd = stoi(argv[i+1]);
        if(!strcmp(argv[i],"-M"))
            M = stoi(argv[i+1]);
        if(!strcmp(argv[i],"-delta"))
            delta = stod(argv[i+1]);
    }
    if ( n < 2){
        cerr << "Expected the necessary arguments -d [inputFile], -q [queryFile]" << endl;
        return 1;
    }   
    
    CurveHashing *ch;
    //ch = new LSHC(delta,d,L);
    ch = new HCC(delta,d,L, dd, hd);
    cout << "Reading input file..." << endl;
    ch->readData(inputFile);
    cout << "Reading complete." << endl;
    //ch->printAllCurves();
    cout << "Inserting data to the hashtable..." << endl;
    ch->hashAll();
    cout << "Inserting complete." << endl;
    ch->readQueries(queryFile);

    delete ch;

    return 0;
}
