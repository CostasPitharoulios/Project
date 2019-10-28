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
    string inputFile, outputFile="output.txt", queryFile, hf;
    double delta=0.0005; 
    int k = 4, L=2,w=4000, M=100,d=2,dd=8,probes=3;

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
        if(!strcmp(argv[i],"-hf")){
            hf = argv[i+1];
            n++;
        }
        if(!strcmp(argv[i],"-o"))
            outputFile = argv[i+1];
        if(!strcmp(argv[i],"-k"))
            k = stoi(argv[i+1]);
        if(!strcmp(argv[i],"-L"))
            L = stoi(argv[i+1]);
        if(!strcmp(argv[i],"-w"))
            w = stoi(argv[i+1]);
        if(!strcmp(argv[i],"-dd"))
            dd = stoi(argv[i+1]);
        if(!strcmp(argv[i],"-probes"))
            probes = stoi(argv[i+1]);
        if(!strcmp(argv[i],"-M"))
            M = stoi(argv[i+1]);
        if(!strcmp(argv[i],"-delta"))
            delta = stod(argv[i+1]);
    }
    if ( n < 3){
        cerr << "Expected the necessary arguments -d [inputFile], -q [queryFile], -hf [LSH/HC]" << endl;
        return 1;
    }
    
    CurveHashing *ch;

    // Make an instance of LSHC or HCC
    if(!hf.compare("LSH"))
        ch = new LSHC(w,delta,d,k,L);
    else if(!hf.compare("HC"))
        ch = new HCC(w,delta,d,k,L, dd, probes, M);
    else
        ch = new LSHC(w,delta,d,k,L);
    cout << "Reading input file..." << endl;
    ch->readData(inputFile);
    cout << "Reading complete." << endl;
    //ch->printAllCurves();
    cout << "Inserting data to the hashtable..." << endl;
    ch->hashAll();
    cout << "Inserting complete." << endl;
    ch->readQueries(queryFile,outputFile);

    delete ch;

    return 0;
}
